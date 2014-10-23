#include "vectorcachewrapper.h"

using namespace std;

VectorCacheWrapper::VectorCacheWrapper(sc_module_name name) :
    sc_module(name), memoryReadReqAdapter("mrreqadp"),
    memoryReadRespAdapter("mrrespadp"), readRespAdapter("rrespadp"), vecCache("vcache")

{
    // bind clock and reset
    vecCache.clk(clk);
    vecCache.reset(reset);
    // bind status ports
    vecCache.io_cacheActive(cacheActive);
    vecCache.io_missCount(missCount);
    vecCache.io_readCount(readCount);
    // bind the FIFO interfaces
    readRespAdapter.bindFIFOOutput(readResp);
    memoryReadReqAdapter.bindFIFOOutput(memoryReadReq);
    memoryReadRespAdapter.bindFIFOInput(memoryReadResp);
    // bind the broken-out (ready,valid,data) FIFO interfaces
    readRespAdapter.bindSignalInterface(vecCache.io_readResp_valid, vecCache.io_readResp_ready,
                                        vecCache.io_readResp_bits);
    memoryReadRespAdapter.bindSignalInterface(vecCache.io_memResp_valid, vecCache.io_memResp_ready,
                                              vecCache.io_memResp_bits);
    memoryReadReqAdapter.bindSignalInterface(vecCache.io_memReq_valid, vecCache.io_memReq_ready,
                                            vecCache.io_memReq_bits);

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

void VectorCacheWrapper::connectReadReqSignals(sc_signal<unsigned int> &data, sc_signal<bool> &ready,
                                               sc_signal<bool> &valid)
{
    vecCache.io_readReq_bits(data);
    vecCache.io_readReq_ready(ready);
    vecCache.io_readReq_valid(valid);
}
