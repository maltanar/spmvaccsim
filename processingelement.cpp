#include <QSet>
#include <QDebug>
#include "processingelement.h"

ProcessingElement::ProcessingElement(sc_module_name name, int peID, int maxOutstandingRequests, int cacheWordsTotal, CacheMode cacheMode, SpMVOCMSimulation *parentSim) :
    sc_module(name)
{
    m_parentSim = parentSim;
    m_requests = NULL;
    m_responses = NULL;
    m_peID = peID;
    m_maxOutstandingRequests = maxOutstandingRequests;
    m_streamBufferHeadPos = 0;
    m_maxAlive = 0;

    // TODO make total cache size configurable
    setupCache(cacheMode, cacheWordsTotal);

    m_cyclesWithRequest = 0;
    m_cyclesWithResponse = 0;
    m_memLatencySamples = 0;
    m_memLatencySum = sc_time(0, SC_NS);
    m_cacheHits = m_cacheMisses = 0;


    SC_THREAD(sendReadRequests);
    // TODO add thread for writes, they behave differently (no need to wait on result)
}

void ProcessingElement::assignWork(SpMVOperation *spmv, int peCount)
{
    quint32 startingRow;
    quint64 startingNZ;
    spmv->assignWorkToWorker(m_peID, peCount, startingRow, startingNZ, m_vectorIndexList, m_rowLenList);

    // calculate global start addresses for input data
    // assume SpMV data linearly laid out in memory
    // TODO support interleaved data mode?
    quint64 rowPtrStart = 0;
    quint64 colIndStart = rowPtrStart + sizeof(VectorIndex)*(spmv->rowCount()+1);
    quint64 matrixValStart = colIndStart + sizeof(VectorIndex)*(spmv->nzCount());
    quint64 denseVecStart = matrixValStart + sizeof(VectorValue)*(spmv->nzCount());

    // assigns local start addresses (for this particular PE)
    m_rowPtrBase = rowPtrStart + startingRow * sizeof(VectorIndex);
    m_matrixValBase = matrixValStart + startingNZ * sizeof(VectorValue);
    m_colIndBase = colIndStart + startingNZ * sizeof(VectorIndex);
    m_denseVecBase = denseVecStart;

    // set defauls for memory strides
    m_rowPtrStride = sizeof(VectorIndex);
    m_matrixValStride = sizeof(VectorValue);
    m_colIndStride = sizeof(VectorIndex);
    m_denseVecStride = sizeof(VectorValue);
}

void ProcessingElement::setRequestFIFO(sc_fifo<MemoryOperation *> *fifo)
{
    m_requests = fifo;
}

void ProcessingElement::setResponseFIFO(sc_fifo<MemoryOperation *> *fifo)
{
    m_responses = fifo;
}

void ProcessingElement::sendReadRequests()
{
    VectorIndex elementsLeft = m_vectorIndexList.size(), currentIndex = 0;
    int rowsLeft = m_rowLenList.size(), currentRow = 0, elementsInRow = m_rowLenList[currentRow];

    int requestsInFlight = 0;

    while(elementsLeft > 0)
    {
        // TODO use loops if we want more than 1 request/response per cycle

        // handle incoming responses, if any
        if(m_responses->num_available() > 0)
        {
            // log statistics for this particular request / per-cycle statistics
            MemoryOperation * op = m_responses->read();
            m_memLatencySum += op->latency;
            m_memLatencySamples++;
            freeRequest(op);

            // we got response for a request
            requestsInFlight--;
            elementsLeft--;

            // TODO move this to outside the if for multiple requests per cycle
            // and use a flag
            m_cyclesWithResponse++;

            // this was a cache miss, add it to the cache
            cacheAdd((VectorIndex) op->address);

            // handle end-of-row stuff
            elementsInRow--;
            if(elementsInRow == 0)
            {
                rowsLeft--;
                if(rowsLeft)
                {
                    currentRow++;
                    elementsInRow = m_rowLenList[currentRow];
                }
            }
            // TODO issue other reads to matrix data
        }

        // add new request if possible
        if(requestsInFlight < m_maxOutstandingRequests && m_requests->num_free() > 0
                && elementsLeft && currentIndex < m_vectorIndexList.size())
        {
            // send out request only on cache miss
            if(!cacheCheck(m_vectorIndexList[currentIndex]))
            {
                MemoryOperation * op = makeReadRequest(m_peID, (quint64) m_vectorIndexList[currentIndex]);
                m_requests->write(op);
                requestsInFlight++;

                // TODO move this to outside the if for multiple requests per cycle
                // and use a flag
                m_cyclesWithRequest++;
            }
            else
            {
                elementsLeft--;
            }

            currentIndex++;

        }

        wait(PE_CLOCK_CYCLE);
    }

    // notify parent that we are finished
    m_parentSim->signalFinishedPE(m_peID);
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
