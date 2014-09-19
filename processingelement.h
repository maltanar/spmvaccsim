#ifndef PROCESSINGELEMENT_H
#define PROCESSINGELEMENT_H

#include <systemc.h>
#include <QList>
#include "spmvocmsimulation.h"
#include "spmvoperation.h"
#include "utilities.h"

class SpMVOCMSimulation;

class ProcessingElement : public sc_module
{
    SC_HAS_PROCESS(ProcessingElement);
public:
    ProcessingElement(sc_module_name name, int peID, int maxOutstandingRequests, int cacheWordsTotal, CacheMode cacheMode, SpMVOCMSimulation * parentSim);

    void assignWork(SpMVOperation * spmv, int peCount);
    void setAccessedElementList(QList<quint32> indList, QList<quint32> rowlenList);

    void setRequestFIFO(sc_fifo<MemoryOperation *> * fifo);
    void setResponseFIFO(sc_fifo<MemoryOperation *> * fifo);
    void sendReadRequests();

    // statistics
    int getAssignedElemCount();
    uint64_t getCyclesWithResponse();
    uint64_t getCyclesWithRequest();
    sc_time getAverageMemLatency();
    uint64_t getCacheMisses();
    uint64_t getCacheHits();

protected:
    QList<VectorIndex> m_vectorIndexList;
    QList<quint32> m_rowLenList;
    sc_fifo<MemoryOperation *> * m_requests;
    sc_fifo<MemoryOperation *> * m_responses;
    int m_peID, m_maxOutstandingRequests;
    int m_maxAlive;
    // start addresses for input data
    quint64 m_rowPtrBase, m_matrixValBase, m_colIndBase, m_denseVecBase;
    // stride values for input data (to support interleaved mapping)
    int m_rowPtrStride, m_matrixValStride, m_colIndStride, m_denseVecStride;
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
