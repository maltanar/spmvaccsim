#ifndef VECTORCACHEWRAPPER_H
#define VECTORCACHEWRAPPER_H

#include "utilities.h"
#include "fifoinbreakout.h"
#include "fifooutbreakout.h"
#include "vector-cache-src/VSimpleDMVectorCache.h"

class VectorCacheWrapper : public sc_module
{
    SC_HAS_PROCESS(VectorCacheWrapper);

public:
    VectorCacheWrapper(sc_module_name name);
    ~VectorCacheWrapper();

    virtual void initialize();

    sc_in_clk clk;
    sc_in<bool> reset;

    sc_event cacheReady;

    virtual void printCacheStats();
    void triggerCacheActive();
    void flush();

    virtual void connectReadReqSignals(sc_signal<VectorIndex> & data, sc_signal<bool> & ready, sc_signal<bool> & valid);
    //void connectWriteReqSignals(sc_signal<VectorIndex> & addr, sc_signal<VectorValue> & data, sc_signal<bool> & ready, sc_signal<bool> & valid);

    // write requests (addr) and data
    sc_fifo_in<VectorIndex> writeReq;
    sc_in<VectorValue> writeData;

    // read responses
    sc_fifo_out<VectorValue> readResp;
    sc_out<VectorIndex> readRespInd;

    // memory read requests and responses
    sc_fifo_out<VectorIndex> memoryReadReq;
    sc_fifo_in<VectorValue> memoryReadResp;

    // memory write requests (addr) and data
    sc_fifo_out<VectorIndex> memoryWriteReq;
    sc_out<VectorValue> memoryWriteData;

protected:
    // wrapped vector cache instance
    VSimpleDMVectorCache * vecCache;
    // signals to monitor cache statistics
    sc_signal<quint32> readCount, readMissCount;
    sc_signal<quint32> writeCount, writeMissCount;
    sc_signal<bool> cacheActive;
    // cache flush signal
    sc_signal<bool> flushCache;

    // FIFO adapters
    FIFOOutBreakout<VectorValue> readRespAdapter;

    FIFOInBreakout<VectorValue> memoryReadRespAdapter;
    FIFOOutBreakout<VectorIndex> memoryReadReqAdapter;

    FIFOInBreakout<VectorIndex> writeReqAdapter;
    FIFOOutBreakout<VectorIndex> memoryWriteReqAdapter;


};

#endif // VECTORCACHEWRAPPER_H

