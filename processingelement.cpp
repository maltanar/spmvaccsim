#include <QSet>
#include <QDebug>
#include "processingelement.h"
#include "utilities.h"


ProcessingElement::ProcessingElement(sc_module_name name, int peID, int maxOutstandingRequests, int cacheWordsTotal,
                                     CacheMode cacheMode, SpMVOCMSimulation *parentSim, QList<MemRequestTag> bypass) :
    sc_module(name)
{
    m_parentSim = parentSim;
    m_peID = peID;
    m_maxOutstandingRequests = maxOutstandingRequests;
    m_streamBufferHeadPos = 0;
    m_maxAlive = 0;
    m_requestBypassEnable = bypass;

    setupCache(cacheMode, cacheWordsTotal);

    m_cyclesWithRequest = 0;
    m_cyclesWithResponse = 0;
    m_memLatencySamples = 0;
    m_memLatencySum = sc_time(0, SC_NS);
    m_cacheHits = m_cacheMisses = 0;

    m_peNZCount = 0;
    m_peRowCount = 0;

    // declare SystemC threads
    SC_THREAD(rowPtrAddrGen);
    SC_THREAD(matrixValueAddrGen);
    SC_THREAD(colIndAddrGen);
    SC_THREAD(progress);
}

void ProcessingElement::assignWork(SpMVOperation *spmv, int peCount)
{
    quint32 startingRow;
    quint64 startingNZ;
    spmv->assignWorkToWorker(m_peID, peCount, startingRow, startingNZ, m_vectorIndexList, m_rowLenList);

    // calculate global start addresses for input data
    // assume SpMV data linearly laid out in memory
    // TODO support interleaved mapping to the SpM?
    quint64 rowPtrStart = 0;

    quint64 colIndStart = rowPtrStart + sizeof(VectorIndex)*(spmv->rowCount()+1);
    colIndStart = BurstMemoryPort::alignStartAddressForBurst(colIndStart);

    quint64 matrixValStart = colIndStart + sizeof(VectorIndex)*(spmv->nzCount());
    matrixValStart = BurstMemoryPort::alignStartAddressForBurst(matrixValStart);

    // won't do burst accesses on dense vec, but just in case...
    quint64 denseVecStart = matrixValStart + sizeof(VectorValue)*(spmv->nzCount());
    denseVecStart = BurstMemoryPort::alignStartAddressForBurst(denseVecStart);

    // assigns local start addresses (for this particular PE)
    m_rowPtrBase = BurstMemoryPort::alignStartAddressForBurst(rowPtrStart + startingRow * sizeof(VectorIndex));
    m_matrixValBase = BurstMemoryPort::alignStartAddressForBurst(matrixValStart + startingNZ * sizeof(VectorValue));
    m_colIndBase = BurstMemoryPort::alignStartAddressForBurst(colIndStart + startingNZ * sizeof(VectorIndex));
    m_denseVecBase = BurstMemoryPort::alignStartAddressForBurst(denseVecStart);

    // set defauls for memory strides
    m_rowPtrStride = sizeof(VectorIndex);
    m_matrixValStride = sizeof(VectorValue);
    m_colIndStride = sizeof(VectorIndex);
    m_denseVecStride = sizeof(VectorValue);

    m_peNZCount = m_vectorIndexList.size();
    m_peRowCount = m_rowLenList.size();
}

ProcessingElement::~ProcessingElement()
{
    delete m_matrixValueAddr;
    delete m_matrixValue;
    delete m_colIndAddr;
    delete m_colIndValue;
    delete m_denseVectorAddr;
    delete m_denseVectorValue;

    delete m_matrixValuePort;
    delete m_colIndPort;
    delete m_denseVectorPort;
}

uint64_t ProcessingElement::getCyclesWithResponse()
{
    return m_cyclesWithResponse;
}

uint64_t ProcessingElement::getCyclesWithRequest()
{
    return m_cyclesWithRequest;
}

sc_time ProcessingElement::getAverageMemLatency()
{
    return m_memLatencySum / m_memLatencySamples;
}

uint64_t ProcessingElement::getCacheMisses()
{
    return m_cacheMisses;
}

uint64_t ProcessingElement::getCacheHits()
{
    return m_cacheHits;
}

void ProcessingElement::connectToMemorySystem(MemorySystem *memsys)
{
    m_memorySystem = memsys;

    createPortsAndFIFOs();

    // must be done after FIFOs are created
    SC_METHOD(denseVectorAddrGen);
    sensitive << m_colIndValue->data_written_event() << m_denseVectorAddr->data_read_event();
    dont_initialize();

    SC_METHOD(rowPtrValueSplit);
    sensitive << m_rowPtrValueRaw->data_written_event() << m_rowPtrValue->data_read_event();
}

void ProcessingElement::createPortsAndFIFOs()
{
    m_rowPtrPort = new BurstMemoryPort("rpp", m_peID, memReqRowLen, m_memorySystem,
                                       m_maxOutstandingRequests, sizeof(VectorIndex));
    m_matrixValuePort = new BurstMemoryPort("mvp", 100 + m_peID, memReqMatrixData, m_memorySystem,
                                            m_maxOutstandingRequests, sizeof(VectorValue));
    m_colIndPort  = new BurstMemoryPort("cip", 200 + m_peID, memReqColInd, m_memorySystem,
                                        m_maxOutstandingRequests, sizeof(VectorIndex));
    m_denseVectorPort = new MemoryPort("dvp", 300 + m_peID, memReqVectorData, m_memorySystem, m_maxOutstandingRequests);

    // TODO parametrize these FIFO lengths
    m_rowPtrAddr = new sc_fifo<quint64>(16);
    m_rowPtrValue = new sc_fifo<quint64>(16);

    m_rowPtrValueRaw = new sc_fifo<quint64>(16);
    m_matrixValueAddr = new sc_fifo<quint64>(16);
    m_matrixValue = new sc_fifo<quint64>(16);
    m_colIndAddr = new sc_fifo<quint64>(16);
    m_colIndValue = new sc_fifo<quint64>(16);
    m_denseVectorAddr = new sc_fifo<quint64>(16);
    m_denseVectorValue = new sc_fifo<quint64>(16);

    m_rowPtrPort->peInput.bind(*m_rowPtrAddr);
    m_rowPtrPort->peOutput.bind(*m_rowPtrValueRaw);

    m_matrixValuePort->peInput.bind(*m_matrixValueAddr);
    m_matrixValuePort->peOutput.bind(*m_matrixValue);

    m_colIndPort->peInput.bind(*m_colIndAddr);
    m_colIndPort->peOutput.bind(*m_colIndValue);

    m_denseVectorPort->peInput.bind(*m_denseVectorAddr);
    m_denseVectorPort->peOutput.bind(*m_denseVectorValue);

    // set bypass flags according to parameters
    m_rowPtrPort->setBypassMode( m_requestBypassEnable.contains(memReqRowLen) );
    m_matrixValuePort->setBypassMode( m_requestBypassEnable.contains(memReqMatrixData) );
    m_colIndPort->setBypassMode( m_requestBypassEnable.contains(memReqColInd) );
    m_denseVectorPort->setBypassMode( m_requestBypassEnable.contains(memReqVectorData) );
}

void ProcessingElement::rowPtrAddrGen()
{
    VectorIndex rowCount = m_peRowCount, currentRow = 0;

    // since the rowptr requests are generated by a BurstMemoryPort, we have to generate
    // enough requests to fill a burst
    int rowPtrsPerBurst = m_rowPtrPort->getPEDataUnitsPerBurst();
    rowCount += rowPtrsPerBurst -(m_peRowCount % rowPtrsPerBurst);

    while(rowCount)
    {
        // fill in as many addresses as possible into the FIFO
        while(m_rowPtrAddr->nb_write(m_rowPtrBase + currentRow * m_rowPtrStride))
        {
            rowCount--;
            currentRow++;
        }

        // drain rate for the address FIFO will eventually depend on the drain rate
        // of the value FIFO (rowPtrValue), which is determined by the progress() process
        wait(PE_CLOCK_CYCLE);
    }
}

void ProcessingElement::rowPtrValueSplit()
{
    // generate actual row length data from the "raw" row lengths

    while(m_rowPtrValue->num_free() > 0 && m_rowPtrValueRaw->num_available() > 0)
    {
        VectorIndex rowNum = (m_rowPtrValueRaw->read() - m_rowPtrBase) / m_rowPtrStride;

        // avoid shooting over the assigned rows to this PE, since the addrgen
        // has to round up to the closest burst
        if(rowNum < m_peRowCount)
            sc_assert(m_rowPtrValue->nb_write(rowNum));
    }
}

void ProcessingElement::matrixValueAddrGen()
{
    quint64 nzCount = m_peNZCount, currentNZ = 0;
    // since the matrix val requests are generated by a BurstMemoryPort, we have to generate
    // enough requests to fill a burst
    int matrixValsPerBurst = m_matrixValuePort->getPEDataUnitsPerBurst();
    nzCount += matrixValsPerBurst -(m_peNZCount % matrixValsPerBurst);

    while(nzCount)
    {
        // fill in as many addresses as possible into the FIFO
        while(m_matrixValueAddr->nb_write(m_matrixValBase + currentNZ * m_matrixValStride))
        {
            nzCount--;
            currentNZ++;
        }

        wait(PE_CLOCK_CYCLE);
    }
}

void ProcessingElement::colIndAddrGen()
{
    // this is separate from matrixValueAddrGen since the FIFOs may drain at different rates
    // as a performance optimization it should be possible to combine them into the same SC_THREAD though
    quint64 nzCount = m_peNZCount, currentNZ = 0;
    // since the rowptr requests are generated by a BurstMemoryPort, we have to generate
    // enough requests to fill a burst
    int colIndsPerBurst = m_colIndPort->getPEDataUnitsPerBurst();
    nzCount += colIndsPerBurst -(m_peNZCount % colIndsPerBurst);


    while(nzCount > 0)
    {
        // fill in as many addresses as possible into the FIFO
        while(m_colIndAddr->nb_write(m_colIndBase + currentNZ * m_colIndStride) && nzCount > 0)
        {
            currentNZ++;
            nzCount--;
        }


        wait(PE_CLOCK_CYCLE);
    }
}

void ProcessingElement::denseVectorAddrGen()
{
    // this SC_METHOD gets triggered every time a colIndValue is written
    // translates the colIndValue (actually addr) into a denseVectorAddr

    // TODO add cache support here - for cache hits, bypass memory port and
    // write to denseVectorValues directly. for cache misses, watch the output of
    // denseVectorValues and add them to cache.

    while(m_denseVectorAddr->num_free() > 0 && m_colIndValue->num_available() > 0)
    {
        quint64 ind =  0;
        sc_assert(m_colIndValue->nb_read(ind));

        // memory ports return the address of read data for now
        // convert address back into col index index
        VectorIndex baseV = (ind - m_colIndBase) / m_colIndStride;

        // do some filtering since colind will generate extra requests to round up to
        // burst length
        if(baseV < m_peNZCount)
        {
            // lookup dense vector index from internal table and generate address
            quint64 dvAddr = m_denseVecBase + m_denseVecStride * m_vectorIndexList[baseV];
            sc_assert(m_denseVectorAddr->nb_write(dvAddr));
        }
    }
}

void ProcessingElement::progress()
{
    // increment progress if both matrixValue and denseVectorValue are nonempty
    // and if we have some rowlen data available
    quint64 nzCount = m_peNZCount;
    // keep track of nonzeroes left in row
    VectorIndex nzLeftInRow = 0;

    sc_time last = sc_time(0,SC_NS);

    while(1)
    {
        // keep track of current row
        if(m_rowPtrValue->num_available() > 0 && nzLeftInRow == 0)
        {
            VectorIndex row = m_rowPtrValue->read();
            nzLeftInRow = m_rowLenList[row];
        }

        // TODO enable multiple NZs per cycle?
        if(m_matrixValue->num_available() > 0 && m_denseVectorValue->num_available() > 0 && nzLeftInRow > 0)
        {
            m_matrixValue->read();

            m_memLatencySum += sc_time_stamp() - last;
            m_memLatencySamples++;
            last = sc_time_stamp();

            m_denseVectorValue->read();
            nzCount--;
            nzLeftInRow--;
        }

        // break when have issued enough ops
        if(!nzCount)
        {
            break;
        }

        wait(PE_CLOCK_CYCLE);
    }

    m_parentSim->signalFinishedPE(m_peID);
}


void ProcessingElement::setupCache(CacheMode cacheMode, uint64_t totalSizeInWords)
{
    m_cacheMode = cacheMode;
    m_cacheTotalWords = totalSizeInWords;

    // number of sets depends on cache mode
    switch(m_cacheMode)
    {
    case cacheModeNone:
        m_numCacheSetCount = 0;
        m_numCacheSetSize = 0;
        return;
    case cacheModeStreamBuffer:
    case cacheModeDirectMapped:
        m_numCacheSetCount = 1;
        break;
    case cacheMode2WayAssoc:
        m_numCacheSetCount = 2;
        break;
    case cacheMode4WayAssoc:
        m_numCacheSetCount = 4;
        break;
    }

    // calculate allocated storage in words per set
    m_numCacheSetSize = totalSizeInWords / m_numCacheSetCount;

    // allocate cache entries and sets
    CacheSet set;
    CacheEntry emptyEntry;
    emptyEntry.index = 0;
    emptyEntry.valid = false;

    ReplacementQueue replQueue;
    for(int i = 0; i < m_numCacheSetCount; i++)
        replQueue.append(i);


    for(int i = 0; i < m_numCacheSetSize; i++)
    {
        set.append(emptyEntry);
        m_cacheLRUEntry.append(replQueue);
    }


    for(int i = 0; i < m_numCacheSetCount; i++)
    {
        m_cacheSets.append(set);
    }
}

bool ProcessingElement::cacheCheck(VectorIndex index)
{
    if(m_cacheMode == cacheModeNone)
        return false;

    VectorIndex mappedIndex = index % m_numCacheSetSize;

    for(int set = 0; set < m_numCacheSetCount; set++)
    {
        CacheEntry entry = m_cacheSets[set][mappedIndex];
        if(entry.valid && entry.index == index)
        {
            // TODO can we do update-on-write instead, and call cacheAdd every time?
            // update LRU entry -- move set to end of queue
            m_cacheLRUEntry[mappedIndex].removeAll(set);
            m_cacheLRUEntry[mappedIndex].append(set);
            m_cacheHits++;
            return true;
        }
    }

    m_cacheMisses++;

    return false;
}

void ProcessingElement::cacheAdd(quint32 index)
{
    if(m_cacheMode == cacheModeNone)
        return;

    VectorIndex mappedIndex = index % m_numCacheSetSize;

    int victimSet = m_cacheLRUEntry[mappedIndex].takeFirst();
    // evict the victim entry
    m_cacheSets[victimSet][mappedIndex].index = index;
    m_cacheSets[victimSet][mappedIndex].valid = true;
    // update LRU entry -- move set to end of queue
    m_cacheLRUEntry[mappedIndex].append(victimSet);
}

void ProcessingElement::colLifetimeAnalysis()
{
    // generate set of unique indices
    QSet<VectorIndex> uniqueInds = m_vectorIndexList.toSet();
    qDebug() << "created set";
    VectorIndex ind, minIndex = m_vectorIndexList[0];
    int * alivenessChanges = new int[m_vectorIndexList.size()];
    memset(alivenessChanges,0,sizeof(int)*m_vectorIndexList.size());

    int singleUseValues = 0;
    // build a sorted map structure that contains the start/end locations
    // of each unique index
    foreach(ind, uniqueInds)
    {
        int firstIndex = m_vectorIndexList.indexOf(ind);
        int lastIndex = m_vectorIndexList.lastIndexOf(ind);
        if(firstIndex != lastIndex)
        {
            alivenessChanges[firstIndex] =  +1;
            alivenessChanges[lastIndex] = -1;
        } else
            singleUseValues++;
        // find the min index (initial value of stream buffer head)
        minIndex = (ind < minIndex ? ind : minIndex);
    }

    // iterate over the aliveness changes, adding each value as we proceed
    // and find the maximum sum
    int alive = 0;
    for(int i = 0; i < m_vectorIndexList.size(); i++)
    {
        alive += alivenessChanges[i];
        m_maxAlive = (m_maxAlive < alive ? alive : m_maxAlive);
        // TODO the total aliveness at each step can also be exploited if it varies a lot
    }

    // TODO should we add 1 to the maxAlive to account for the single-use values?

    delete [] alivenessChanges;

    qDebug() << "PE #" << m_peID << " maxAlive = " << m_maxAlive;
    if(singleUseValues)
        qDebug() << singleUseValues << " single use values";

    if(m_cacheMode == cacheModeStreamBuffer && m_maxAlive > m_cacheTotalWords)
    {
        qDebug() << "error: not enough memory in PE#" << m_peID << " to use stream buffer scheme";
        qDebug() << "max alive = " << m_maxAlive << ", available = " << m_cacheTotalWords;
    }
}

int ProcessingElement::getAssignedElemCount()
{
    return m_vectorIndexList.size();
}
