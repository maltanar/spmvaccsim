#ifndef VECTORCACHETESTER_H
#define VECTORCACHETESTER_H

#include "utilities.h"
#include "vectorcachewrapper.h"
#include <QMap>
#include <QList>

#define RDRSP_FIFO_SIZE         16
#define MEMRDREQ_FIFO_SIZE      2
#define MEMRDRSP_FIFO_SIZE      2
#define WRITE_FIFO_SIZE         16
#define DRAM_RESP_LATENCY       (10 * PE_CLOCK_CYCLE)
#define DATAPATH_LATENCY        (GlobalConfig::getHazardWindowSize() * PE_CLOCK_CYCLE)


class VectorCacheTester : public sc_module
{
    SC_HAS_PROCESS(VectorCacheTester);
public:
    VectorCacheTester(sc_module_name name);
    ~VectorCacheTester();

    void setAccessList(QList<VectorIndex> list);
    void initializeMemory(unsigned int numElements, VectorValue initValue);

    void generateReset();
    void pushReadRequests();
    void pullReadResponses();
    void handleDRAMReads();
    void handleDRAMWrites();
    void handleDatapath();

protected:
    QList<VectorIndex> m_accessList;
    VectorValue * m_mainMemory;

    VectorCacheWrapper vecCache;
    bool simFinished;
    sc_clock clkSource;
    sc_in_clk clk;
    sc_signal<bool> reset;
    sc_event resetComplete;

    sc_fifo<VectorIndex> memReadReqFIFO;
    sc_fifo<VectorValue> readRspFIFO, memReadRspFIFO;
    sc_signal<VectorIndex> readRspInd;

    sc_fifo<VectorIndex> writeReqFIFO, memWriteReqFIFO;
    sc_signal<VectorValue> writeDataOut, memWriteDataOut;

    // signals to control read request interface
    sc_signal<VectorIndex> m_readReqData;
    sc_signal<bool> m_readReqReady, m_readReqValid;

    // DRAM behavior
    QMap<double, VectorIndex> m_memRespToDispatch;
    unsigned int m_allocatedMemorySize;
    VectorValue memoryRead(VectorIndex addr);
    void memoryWrite(VectorIndex addr, VectorValue data);

    // datapath behavior
    QMap<double, VectorIndex> m_writeReqToDispatch;
    QList<VectorValue> m_writeDataToDispatch;
};

#endif // VECTORCACHETESTER_H
