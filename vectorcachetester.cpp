#include "vectorcachetester.h"

using namespace std;

VectorCacheTester::VectorCacheTester(sc_module_name name) :
    sc_module(name), vecCache("vec$"), clkSource("clk", PE_CLOCK_CYCLE),
    readReqFIFO(RDREQ_FIFO_SIZE), readRspFIFO(RDRSP_FIFO_SIZE),
    memReadReqFIFO(MEMRDREQ_FIFO_SIZE), memReadRspFIFO(MEMRDRSP_FIFO_SIZE)
{
    simFinished = false;

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

void VectorCacheTester::setAccessList(QList<VectorIndex> list)
{
    m_accessList = list;
    m_accessListSize = list.size();
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
    cout << "Reset completed at " << sc_time_stamp() << endl;
}

void VectorCacheTester::pushReadRequests()
{
    wait(resetComplete);
    wait(vecCache.cacheReady);

    while(!m_accessList.empty())
    {
        wait(1);
        readReqFIFO.write(m_accessList.first());
        cout << "Request to " << m_accessList.first() << " written at " << sc_time_stamp() << endl;
        m_accessList.removeFirst();
    }
}

void VectorCacheTester::pullReadResponses()
{
    wait(resetComplete);
    wait(vecCache.cacheReady);

    unsigned int reqsToPop = m_accessListSize;

    while(reqsToPop)
    {
        wait(1);
        VectorValue val = readRspFIFO.read();
        cout << "Response " << val << " at " << sc_time_stamp();
        reqsToPop--;
    }

    // responses determine the finish condition
    simFinished = true;

    // print final cache stats
    vecCache.printCacheStats();

    sc_stop();
}

void VectorCacheTester::handleDRAM()
{
    wait(resetComplete);
    // fixed-latency path between memReadReqFIFO and memReadRspFIFO
    while(!simFinished)
    {
        double time_now = sc_time_stamp().to_double();
        VectorIndex ind = 0;

        if(m_memRespToDispatch.contains(time_now))
        {
            ind = m_memRespToDispatch[time_now];
            // TODO mem r/w consistency issues here?
            memReadRspFIFO.write(memoryLookup(ind));
            cout << "Memory response for " << ind << " written at " << sc_time_stamp() << endl;
        }

        wait(1);

        if(memReadReqFIFO.nb_read(ind))
        {
            // schedule response after fixed delay
            double time_disp = (sc_time_stamp() + DRAM_RESP_LATENCY).to_double();
            m_memRespToDispatch[time_disp] = ind;
            cout << "Memory request for " << ind << " received at " << sc_time_stamp() << endl;
        }

    }
}


VectorValue VectorCacheTester::memoryLookup(VectorIndex ind)
{
    // TODO return real values here
    return (VectorValue) ind;
}
