#ifndef VECTORCACHETESTER_H
#define VECTORCACHETESTER_H

#include "utilities.h"
#include "vectorcachewrapper.h"
#include <QMap>
#include <QList>

#define RDREQ_FIFO_SIZE         16
#define RDRSP_FIFO_SIZE         16
#define MEMRDREQ_FIFO_SIZE      2
#define MEMRDRSP_FIFO_SIZE      2
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
    VectorIndex m_accessListSize;

    VectorCacheWrapper vecCache;
    bool simFinished;
    sc_clock clkSource;
    sc_in_clk clk;
    sc_signal<bool> reset;
    sc_event resetComplete;

    sc_fifo<VectorIndex> readReqFIFO, memReadReqFIFO;
    sc_fifo<VectorValue> readRspFIFO, memReadRspFIFO;

    QMap<double, VectorIndex> m_memRespToDispatch;

    VectorValue memoryLookup(VectorIndex);
};

#endif // VECTORCACHETESTER_H
