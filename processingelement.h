#ifndef PROCESSINGELEMENT_H
#define PROCESSINGELEMENT_H

#include <systemc.h>
#include <QList>
#include "spmvocmsimulation.h"
#include "utilities.h"

class SpMVOCMSimulation;

class ProcessingElement : public sc_module
{
    SC_HAS_PROCESS(ProcessingElement);
public:
    ProcessingElement(sc_module_name name, int peID, int maxOutstandingRequests, int cacheWordsTotal, CacheMode cacheMode, SpMVOCMSimulation * parentSim);

    void setAccessedElementList(QList<VectorIndex> list);
    void setRequestFIFO(sc_fifo<MemoryOperation *> * fifo);
    void setResponseFIFO(sc_fifo<MemoryOperation *> * fifo);
    void sendReadRequests();

    // statistics
    uint64_t getCyclesWithResponse();
    uint64_t getCyclesWithRequest();
    sc_time getAverageMemLatency();
    uint64_t getCacheMisses();
    uint64_t getCacheHits();

protected:
    QList<VectorIndex> m_vectorIndexList;
    sc_fifo<MemoryOperation *> * m_requests;
    sc_fifo<MemoryOperation *> * m_responses;
    int m_peID, m_maxOutstandingRequests;
    int m_maxAlive;
    // to notify parent when we are finished
    SpMVOCMSimulation * m_parentSim;

    // cache settings and state
    CacheMode m_cacheMode;
    int m_numCacheSetCount, m_numCacheSetSize, m_cacheTotalWords;
    typedef struct {bool valid; VectorIndex index;} CacheEntry;
    typedef QList<CacheEntry> CacheSet;
    typedef QList<int> ReplacementQueue;
    QList<CacheSet> m_cacheSets;
    QList<ReplacementQueue> m_cacheLRUEntry;
    VectorIndex m_streamBufferHeadPos;
    void setupCache(CacheMode cacheMode, uint64_t totalSizeInWords);
    bool cacheCheck(VectorIndex index);
    void cacheAdd(VectorIndex index);

    // variables for statistics keeping
    uint64_t m_cyclesWithRequest, m_cyclesWithResponse;
    uint64_t m_memLatencySamples;
    sc_time m_memLatencySum;
    uint64_t m_cacheHits, m_cacheMisses;
};

#endif // PROCESSINGELEMENT_H
