#include "vectorcachetester.h"

using namespace std;

VectorCacheTester::VectorCacheTester(sc_module_name name) :
    sc_module(name), vecCache("vec$"), clkSource("clk", PE_CLOCK_CYCLE),
    readReqFIFO(RDREQ_FIFO_SIZE), readRspFIFO(RDRSP_FIFO_SIZE),
    memReadReqFIFO(MEMRDREQ_FIFO_SIZE), memReadRspFIFO(MEMRDRSP_FIFO_SIZE)
{
    clk(clkSource);

    vecCache.clk(clk);
    vecCache.reset(reset);

    vecCache.readReq.bind(readReqFIFO);
    vecCache.readResp.bind(readRspFIFO);
    vecCache.memoryReadReq.bind(memReadReqFIFO);
    vecCache.memoryReadResp.bind(memReadRspFIFO);

    reset = true;

    SC_CTHREAD(generateReset, clk.pos());
    SC_CTHREAD(pushReadRequests, clk.pos());
    SC_CTHREAD(pullReadResponses, clk.pos());
    SC_CTHREAD(handleDRAM, clk.pos());
}

void VectorCacheTester::generateReset()
{
    // assume active high reset
    reset = true;
    // keep for 10 cycles
    wait(10);
    reset = false;
    // notify other threads so they can start
    resetComplete.notify();
}

void VectorCacheTester::pushReadRequests()
{
    wait(resetComplete);

    unsigned int reqsToPush = 100;

    while(reqsToPush)
    {
        wait(1);
        readReqFIFO.write(reqsToPush * 5);
        reqsToPush--;
    }
}

void VectorCacheTester::pullReadResponses()
{
    wait(resetComplete);

    unsigned int reqsToPop = 100;

    while(reqsToPop)
    {
        wait(1);
        VectorValue val = readRspFIFO.read();
        cout << "Response " << val << " at " << sc_time_stamp();
        reqsToPop--;
    }
}

void VectorCacheTester::handleDRAM()
{
    wait(resetComplete);
    // TODO create fixed-latency path between memReadReqFIFO and memReadRspFIFO
}
