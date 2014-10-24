#include "vectorcachewrapper.h"

using namespace std;

VectorCacheWrapper::VectorCacheWrapper(sc_module_name name) :
    sc_module(name), memoryReadReqAdapter("mrreqadp"),
    memoryReadRespAdapter("mrrespadp"), readRespAdapter("rrespadp"), vecCache("vcache"),
    writeReqAdapter("wrreqadp"), memoryWriteReqAdapter("mwreqadp")

{
    // bind clock and reset
    vecCache.clk(clk);
    vecCache.reset(reset);
    // bind status ports
    vecCache.io_cacheActive(cacheActive);
    vecCache.io_missCount(missCount);
    vecCache.io_readCount(readCount);
    // bind the FIFO interfaces
    // processor read port
    readRespAdapter.bindFIFOOutput(readResp);
    // memory read port
    memoryReadReqAdapter.bindFIFOOutput(memoryReadReq);
    memoryReadRespAdapter.bindFIFOInput(memoryReadResp);
    // processor write port
    writeReqAdapter.bindFIFOInput(writeReq);
    // memory write port
    memoryWriteReqAdapter.bindFIFOOutput(memoryWriteReq);

    // bind the broken-out (ready,valid,data) FIFO interfaces
    readRespAdapter.bindSignalInterface(vecCache.io_readResp_valid, vecCache.io_readResp_ready,
                                        vecCache.io_readResp_bits);
    memoryReadRespAdapter.bindSignalInterface(vecCache.io_memResp_valid, vecCache.io_memResp_ready,
                                              vecCache.io_memResp_bits);
    memoryReadReqAdapter.bindSignalInterface(vecCache.io_memReq_valid, vecCache.io_memReq_ready,
                                            vecCache.io_memReq_bits);


    writeReqAdapter.bindSignalInterface(vecCache.io_writeReq_valid, vecCache.io_writeReq_ready,
                                        vecCache.io_writeReq_bits);
    vecCache.io_writeData(writeData);

    memoryWriteReqAdapter.bindSignalInterface(vecCache.io_memWriteReq_valid, vecCache.io_memWriteReq_ready,
                                              vecCache.io_memWriteReq_bits);
    vecCache.io_memWriteData(memoryWriteData);

    SC_METHOD(printCacheStats);
    //sensitive << clk.pos();

    SC_METHOD(triggerCacheActive);
    sensitive << cacheActive.value_changed_event();
}

void VectorCacheWrapper::printCacheStats()
{
    cout << endl << "**********************************************************" << endl;
    cout << "Statistics at time " << sc_time_stamp() << endl;
    cout << "cache active = " << cacheActive << endl;
    cout << "total reads = " << readCount << endl;
    cout << "total misses = " << missCount << endl;
}

void VectorCacheWrapper::triggerCacheActive()
{
    if(cacheActive)
        cacheReady.notify();
}

void VectorCacheWrapper::connectReadReqSignals(sc_signal<VectorIndex> &data, sc_signal<bool> &ready,
                                               sc_signal<bool> &valid)
{
    vecCache.io_readReq_bits(data);
    vecCache.io_readReq_ready(ready);
    vecCache.io_readReq_valid(valid);
}

/*
void VectorCacheWrapper::connectWriteReqSignals(sc_signal<VectorIndex> &addr, sc_signal<VectorValue> &data, sc_signal<bool> &ready, sc_signal<bool> &valid)
{
    vecCache.io_writeReq_bits(addr);
    vecCache.io_writeData(data);
    vecCache.io_writeReq_ready(ready);
    vecCache.io_writeReq_valid(valid);
}
*/
