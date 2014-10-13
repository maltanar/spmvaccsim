#ifndef VECTORCACHEWRAPPER_H
#define VECTORCACHEWRAPPER_H

#include "utilities.h"
#include "fifoinbreakout.h"
#include "fifooutbreakout.h"
#include "vector-cache-src/VSimpleDMVectorCache.h"

class VectorCacheWrapper : public sc_module
{
public:
    VectorCacheWrapper(sc_module_name name);

    sc_in_clk clk;
    sc_in<bool> reset;

    void printCacheStats();

    // read requests and responses
    sc_fifo_in<VectorIndex> readReq;
    sc_fifo_out<VectorValue> readResp;

    // memory read requests and responses
    sc_fifo_out<VectorIndex> memoryReadReq;
    sc_fifo_in<VectorValue> memoryReadResp;

protected:
    // wrapped vector cache instance
    VSimpleDMVectorCache vecCache;
    // signals to monitor cache statistics
    sc_signal<quint32> readCount, missCount;
    sc_signal<bool> cacheActive;
    // FIFO adapters
    FIFOInBreakout<VectorIndex> readReqAdapter;
    FIFOOutBreakout<VectorValue> readRespAdapter;
    FIFOInBreakout<VectorValue> memoryReadRespAdapter;
    FIFOOutBreakout<VectorIndex> memoryReadReqAdapter;


};

#endif // VECTORCACHEWRAPPER_H
