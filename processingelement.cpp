#include "processingelement.h"

ProcessingElement::ProcessingElement(sc_module_name name, int peID, int maxOutstandingRequests, CacheMode cacheMode, SpMVOCMSimulation *parentSim) :
    sc_module(name)
{
    m_parentSim = parentSim;
    m_requests = NULL;
    m_responses = NULL;
    m_peID = peID;
    m_maxOutstandingRequests = maxOutstandingRequests;

    // TODO make total cache size configurable
    setupCache(cacheMode, 512*1024);

    m_cyclesWithRequest = 0;
    m_cyclesWithResponse = 0;
    m_memLatencySamples = 0;
    m_memLatencySum = sc_time(0, SC_NS);

    SC_THREAD(sendReadRequests);
    // TODO add thread for writes, they behave differently (no need to wait on result)
}

void ProcessingElement::setAccessedElementList(QList<quint32> list)
{
    m_vectorIndexList = list;
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
        }

        // add new request if possible
        if(requestsInFlight < m_maxOutstandingRequests && m_requests->num_free() > 0
                && elementsLeft && currentIndex < m_vectorIndexList.size())
        {
            m_requests->write(makeReadRequest(m_peID, (quint64) m_vectorIndexList[currentIndex]));
            currentIndex++;
            requestsInFlight++;

            // TODO move this to outside the if for multiple requests per cycle
            // and use a flag
            m_cyclesWithRequest++;
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

void ProcessingElement::setupCache(CacheMode cacheMode, uint64_t totalSizeInWords)
{
    m_cacheMode = cacheMode;

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
    for(int i = 0; i < m_numCacheSetSize; i++)
    {
        set.append(emptyEntry);
    }
    ReplacementQueue replQueue;
    replQueue.append(0);
    replQueue.append(1);
    replQueue.append(2);
    replQueue.append(3);

    for(int i = 0; i < m_numCacheSetCount; i++)
    {
        m_cacheSets.append(set);
        m_cacheLRUEntry.append(replQueue);
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
            return true;
        }
    }

    return false;
}

void ProcessingElement::cacheAdd(quint32 index)
{
    if(m_cacheMode == cacheModeNone)
        return;

    VectorIndex mappedIndex = index % m_numCacheSetSize;

    int victimSet = m_cacheLRUEntry[mappedIndex].takeFirst();
    // update LRU entry -- move set to end of queue
    m_cacheSets[victimSet][mappedIndex].index = index;
    m_cacheSets[victimSet][mappedIndex].valid = true;

    m_cacheLRUEntry[mappedIndex].append(victimSet);
}
