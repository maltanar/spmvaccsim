#include "coldmissskipcachewrapper.h"

ColdMissSkipCacheWrapper::ColdMissSkipCacheWrapper(sc_module_name name) : VectorCacheWrapper(name)
{
    cmsVecCache = NULL;
}

ColdMissSkipCacheWrapper::~ColdMissSkipCacheWrapper()
{
    if(cmsVecCache)
        delete cmsVecCache;
}

void ColdMissSkipCacheWrapper::initialize()
{
    cmsVecCache = new VColdMissSkipVectorCache("vcache");

    // bind clock and reset
    cmsVecCache->clk(clk);
    cmsVecCache->reset(reset);
    // bind cache flush port
    flushCache = false;
    cmsVecCache->io_flushCache(flushCache);
    // bind status ports
    cmsVecCache->io_cacheActive(cacheActive);
    cmsVecCache->io_readMissCount(readMissCount);
    cmsVecCache->io_readCount(readCount);
    cmsVecCache->io_writeCount(writeCount);
    cmsVecCache->io_writeMissCount(writeMissCount);
    cmsVecCache->io_coldSkipCount(coldSkipCount);
    // bind the FIFO interfaces
    // processor read response port
    readRespAdapter.bindFIFOOutput(readResp);
    cmsVecCache->io_readPort_readRespInd(readRespInd);
    // memory read port
    memoryReadReqAdapter.bindFIFOOutput(memoryReadReq);
    memoryReadRespAdapter.bindFIFOInput(memoryReadResp);
    // processor write port
    writeReqAdapter.bindFIFOInput(writeReq);
    // memory write port
    memoryWriteReqAdapter.bindFIFOOutput(memoryWriteReq);

    // bind the broken-out (ready,valid,data) FIFO interfaces

    readRespAdapter.bindSignalInterface(cmsVecCache->io_readPort_readResp_valid, cmsVecCache->io_readPort_readResp_ready,
                                        cmsVecCache->io_readPort_readResp_bits);

    memoryReadRespAdapter.bindSignalInterface(cmsVecCache->io_memRead_memResp_valid, cmsVecCache->io_memRead_memResp_ready,
                                              cmsVecCache->io_memRead_memResp_bits);
    memoryReadReqAdapter.bindSignalInterface(cmsVecCache->io_memRead_memReq_valid, cmsVecCache->io_memRead_memReq_ready,
                                             cmsVecCache->io_memRead_memReq_bits);


    writeReqAdapter.bindSignalInterface(cmsVecCache->io_writePort_writeReq_valid, cmsVecCache->io_writePort_writeReq_ready,
                                        cmsVecCache->io_writePort_writeReq_bits);
    cmsVecCache->io_writePort_writeData(writeData);

    memoryWriteReqAdapter.bindSignalInterface(cmsVecCache->io_memWrite_memWriteReq_valid, cmsVecCache->io_memWrite_memWriteReq_ready,
                                              cmsVecCache->io_memWrite_memWriteReq_bits);
    cmsVecCache->io_memWrite_memWriteData(memoryWriteData);

    // clock for input FIFO adapters
    memoryReadRespAdapter.clk(clk);
    writeReqAdapter.clk(clk);

    //SC_METHOD(printCacheStats);
    //sensitive << clk.pos();

    SC_METHOD(triggerCacheActive);
    sensitive << cacheActive.value_changed_event();
}

void ColdMissSkipCacheWrapper::connectReadReqSignals(sc_signal<VectorIndex> &data, sc_signal<bool> &ready, sc_signal<bool> &valid)
{
    cmsVecCache->io_readPort_readReq_bits(data);
    cmsVecCache->io_readPort_readReq_ready(ready);
    cmsVecCache->io_readPort_readReq_valid(valid);
}

void ColdMissSkipCacheWrapper::printCacheStats()
{
    VectorCacheWrapper::printCacheStats();
    cout << "total cold skips = " << coldSkipCount << endl;
}

void ColdMissSkipCacheWrapper::saveCacheStats()
{
    VectorCacheWrapper::saveCacheStats();
    GlobalConfig::getInstance().setResultData("coldSkipCount", coldSkipCount.read());
}
