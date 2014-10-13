#ifndef VECTORCACHETESTER_H
#define VECTORCACHETESTER_H

#include "utilities.h"
#include "vectorcachewrapper.h"

#define RDREQ_FIFO_SIZE     16
#define RDRSP_FIFO_SIZE     16
#define MEMRDREQ_FIFO_SIZE    2
#define MEMRDRSP_FIFO_SIZE    2

class VectorCacheTester : public sc_module
{
    SC_HAS_PROCESS(VectorCacheTester);
public:
    VectorCacheTester(sc_module_name name);

    void generateReset();
    void pushReadRequests();
    void pullReadResponses();
    void handleDRAM();

protected:
    VectorCacheWrapper vecCache;
    sc_clock clkSource;
    sc_in_clk clk;
    sc_signal<bool> reset;
    sc_event resetComplete;

    sc_fifo<VectorIndex> readReqFIFO, memReadReqFIFO;
    sc_fifo<VectorValue> readRspFIFO, memReadRspFIFO;
};

#endif // VECTORCACHETESTER_H
