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
    // bind cache flush port
    flushCache = false;
    vecCache.io_flushCache(flushCache);
    // bind status ports
    vecCache.io_cacheActive(cacheActive);
    vecCache.io_readMissCount(readMissCount);
    vecCache.io_readCount(readCount);
    vecCache.io_writeCount(writeCount);
    vecCache.io_writeMissCount(writeMissCount);
    // bind the FIFO interfaces
    // processor read response port
    readRespAdapter.bindFIFOOutput(readResp);
    vecCache.io_readPort_readRespInd(readRespInd);
    // memory read port
    memoryReadReqAdapter.bindFIFOOutput(memoryReadReq);
    memoryReadRespAdapter.bindFIFOInput(memoryReadResp);
    // processor write port
    writeReqAdapter.bindFIFOInput(writeReq);
    // memory write port
    memoryWriteReqAdapter.bindFIFOOutput(memoryWriteReq);

    // bind the broken-out (ready,valid,data) FIFO interfaces

    readRespAdapter.bindSignalInterface(vecCache.io_readPort_readResp_valid, vecCache.io_readPort_readResp_ready,
                                        vecCache.io_readPort_readResp_bits);

    memoryReadRespAdapter.bindSignalInterface(vecCache.io_memRead_memResp_valid, vecCache.io_memRead_memResp_ready,
                                              vecCache.io_memRead_memResp_bits);
    memoryReadReqAdapter.bindSignalInterface(vecCache.io_memRead_memReq_valid, vecCache.io_memRead_memReq_ready,
                                            vecCache.io_memRead_memReq_bits);


    writeReqAdapter.bindSignalInterface(vecCache.io_writePort_writeReq_valid, vecCache.io_writePort_writeReq_ready,
                                        vecCache.io_writePort_writeReq_bits);
    vecCache.io_writePort_writeData(writeData);

    memoryWriteReqAdapter.bindSignalInterface(vecCache.io_memWrite_memWriteReq_valid, vecCache.io_memWrite_memWriteReq_ready,
                                              vecCache.io_memWrite_memWriteReq_bits);
    vecCache.io_memWrite_memWriteData(memoryWriteData);

    // clock for input FIFO adapters
    memoryReadRespAdapter.clk(clk);
    writeReqAdapter.clk(clk);

    SC_METHOD(printCacheStats);
    //sensitive << clk.pos();

    SC_METHOD(triggerCacheActive);
    sensitive << cacheActive.value_changed_event();
}

void VectorCacheWrapper::printCacheStats()
{
    /* little hack for per-cycle monitoring without spewing
     * too much data

    static bool cacheActiveFlag = false;
    if(cacheActive)
        cacheActiveFlag=true;

    if(!cacheActiveFlag)
        return;
    */

    cout << endl << "**********************************************************" << endl;
    cout << "Statistics at time " << sc_time_stamp() << endl;
    cout << "cache active = " << cacheActive << endl;
    cout << "total reads = " << readCount << endl;
    cout << "total read misses = " << readMissCount<< endl;
    cout << "total writes = " << writeCount << endl;
    cout << "total write misses = " << writeMissCount << endl;
}

void VectorCacheWrapper::triggerCacheActive()
{
    if(cacheActive)
        cacheReady.notify();
}

void VectorCacheWrapper::flush()
{
    // wait until we are in sActive
    while(!cacheActive)
        wait(PE_CLOCK_CYCLE);

    cout << "Cache flush starting at " << sc_time_stamp() << endl;

    flushCache = true;
    wait(10*PE_CLOCK_CYCLE);

    // wait until back into sActive
    // (flush complete)
    while(!cacheActive)
        wait(PE_CLOCK_CYCLE);
    flushCache = false;

    cout << "Cache flush completed at " << sc_time_stamp() << endl;
}

void VectorCacheWrapper::connectReadReqSignals(sc_signal<VectorIndex> &data, sc_signal<bool> &ready,
                                               sc_signal<bool> &valid)
{
    vecCache.io_readPort_readReq_bits(data);
    vecCache.io_readPort_readReq_ready(ready);
    vecCache.io_readPort_readReq_valid(valid);
}

/*
void VectorCacheWrapper::connectWriteReqSignals(sc_signal<VectorIndex> &addr, sc_signal<VectorValue> &data, sc_signal<bool> &ready, sc_signal<bool> &valid)
{
    vecCache.io_writePort_writeReq_bits(addr);
    vecCache.io_writeData(data);
    vecCache.io_writePort_writeReq_ready(ready);
    vecCache.io_writePort_writeReq_valid(valid);
}
*/
