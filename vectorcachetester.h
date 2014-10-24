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

class VectorCacheTester : public sc_module
{
    SC_HAS_PROCESS(VectorCacheTester);
public:
    VectorCacheTester(sc_module_name name);

    void setAccessList(QList<VectorIndex> list);

    void generateReset();
    void pushReadRequests();
    void pullReadResponses();
    void handleDRAM();

protected:
    QList<VectorIndex> m_accessList;

    VectorCacheWrapper vecCache;
    bool simFinished;
    sc_clock clkSource;
    sc_in_clk clk;
    sc_signal<bool> reset;
    sc_event resetComplete;

    sc_fifo<VectorIndex> memReadReqFIFO;
    sc_fifo<VectorValue> readRspFIFO, memReadRspFIFO;

    sc_fifo<VectorIndex> writeReqFIFO, memWriteReqFIFO;
    sc_signal<VectorValue> writeDataOut, memWriteDataOut;

    // signals to control read request interface
    sc_signal<VectorIndex> m_readReqData;
    sc_signal<bool> m_readReqReady, m_readReqValid;

    // DRAM behavior
    QMap<double, VectorIndex> m_memRespToDispatch;
    VectorValue memoryLookup(VectorIndex);
};

#endif // VECTORCACHETESTER_H
