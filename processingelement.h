#ifndef PROCESSINGELEMENT_H
#define PROCESSINGELEMENT_H

#include <systemc.h>
#include <QList>
#include "spmvocmsimulation.h"
#include "spmvoperation.h"
#include "utilities.h"
#include "memoryport.h"

class SpMVOCMSimulation;

class ProcessingElement : public sc_module
{
    SC_HAS_PROCESS(ProcessingElement);
public:
    ProcessingElement(sc_module_name name, int peID, int maxOutstandingRequests, int cacheWordsTotal,
                      CacheMode cacheMode, SpMVOCMSimulation * parentSim, QList<MemRequestTag> bypass = QList<MemRequestTag>());
    ~ProcessingElement();

    // assign work from SpMV operation to this PE
    void assignWork(SpMVOperation * spmv, int peCount);
    // connect PE to memory system instance
    void connectToMemorySystem(MemorySystem * memsys);

    // statistics
    int getAssignedElemCount();
    uint64_t getCyclesWithResponse();
    uint64_t getCyclesWithRequest();
    sc_time getAverageMemLatency();
    uint64_t getCacheMisses();
    uint64_t getCacheHits();

protected:
    void createPortsAndFIFOs();
    // SystemC threads
    void rowPtrAddrGen();
    void rowPtrValueSplit();
    void matrixValueAddrGen();
    void colIndAddrGen();
    void denseVectorAddrGen();
    void progress();

    MemorySystem * m_memorySystem;

    MemoryPort * m_rowPtrPort;
    MemoryPort * m_matrixValuePort;
    MemoryPort * m_colIndPort;
    MemoryPort * m_denseVectorPort;

    sc_fifo<quint64> * m_rowPtrAddr, * m_rowPtrValueRaw, * m_rowPtrValue;
    sc_fifo<quint64> * m_matrixValueAddr, * m_matrixValue;
    sc_fifo<quint64> * m_colIndAddr, * m_colIndValue;
    sc_fifo<quint64> * m_denseVectorAddr, * m_denseVectorValue;

    quint64 m_peNZCount;
    VectorIndex m_peRowCount;
    QList<VectorIndex> m_vectorIndexList;
    QList<quint32> m_rowLenList;

    int m_peID, m_maxOutstandingRequests;

    // flags for bypassing DRAM requests to some streams
    QList<MemRequestTag> m_requestBypassEnable;

    // for maximum aliveness analysis
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

    // lifetime analysis functions
    void colLifetimeAnalysis();
};

#endif // PROCESSINGELEMENT_H
