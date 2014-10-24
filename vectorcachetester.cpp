#include "vectorcachetester.h"
#include "spmvoperation.h"

using namespace std;

VectorCacheTester::VectorCacheTester(sc_module_name name) :
    sc_module(name), vecCache("vec$"), clkSource("clk", PE_CLOCK_CYCLE),
    readRspFIFO(RDRSP_FIFO_SIZE),
    memReadReqFIFO(MEMRDREQ_FIFO_SIZE), memReadRspFIFO(MEMRDRSP_FIFO_SIZE),
    writeReqFIFO(WRITE_FIFO_SIZE), memWriteReqFIFO(WRITE_FIFO_SIZE)
{
    simFinished = false;
    m_mainMemory = NULL;

    clk(clkSource);

    vecCache.clk(clk);
    vecCache.reset(reset);

    vecCache.readResp.bind(readRspFIFO);
    vecCache.readRespInd.bind(readRspInd);
    vecCache.memoryReadReq.bind(memReadReqFIFO);
    vecCache.memoryReadResp.bind(memReadRspFIFO);

    vecCache.writeData.bind(writeDataOut);
    vecCache.writeReq.bind(writeReqFIFO);

    vecCache.memoryWriteData.bind(memWriteDataOut);
    vecCache.memoryWriteReq.bind(memWriteReqFIFO);

    vecCache.connectReadReqSignals(m_readReqData, m_readReqReady, m_readReqValid);

    reset = true;

    SC_CTHREAD(generateReset, clk.pos());
    SC_CTHREAD(pushReadRequests, clk.pos());
    SC_CTHREAD(pullReadResponses, clk.pos());
    SC_CTHREAD(handleDRAM, clk.pos());
}

VectorCacheTester::~VectorCacheTester()
{
    delete m_mainMemory;
}

void VectorCacheTester::setAccessList(QList<VectorIndex> list)
{
    m_accessList = list;
}

void VectorCacheTester::initializeMemory(unsigned int numElements, VectorValue initValue)
{
    m_allocatedMemorySize = numElements;
    m_mainMemory = new VectorValue[numElements];

    for(unsigned int i = 0; i < numElements; i++)
        m_mainMemory[i] = initValue;
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
    // DEBUG cout << "Reset completed at " << sc_time_stamp() << endl;
}

void VectorCacheTester::pushReadRequests()
{
    wait(resetComplete);
    wait(vecCache.cacheReady);

    // make copy of m_accessList to avoid overwriting
    // call function to create a new list without RAW hazards
    QList<VectorIndex> readReqList = SpMVOperation::insertHazardAvoidanceBubbles(m_accessList, GlobalConfig::getHazardWindowSize());

    while(!readReqList.empty())
    {
        /*readReqFIFO.write(readReqList.first());
        // DEBUG cout << "Request to " << readReqList.first() << " written at " << sc_time_stamp() << endl;
        readReqList.removeFirst();*/

        // make data available if we have some
        bool canIssueThisCycle = true; // TODO use this for request rate limitation


        if(readReqList.first() == BUBBLE_INDEX)
        {
            // do not generate valid for bubble indices
            m_readReqValid = false;
            m_readReqData = 0xdeadbeef; // use this to detect erronous behavior
            // remove bubble from request list
            readReqList.removeFirst();
        }
        else if(!readReqList.empty() && canIssueThisCycle)
        {
            // issue request
            m_readReqValid = true;
            m_readReqData = readReqList.first();
        }
        else
        {
            // no data to issue this cycle
            m_readReqValid = false;
            m_readReqData = 0xdeadbeef; // use this to detect erronous behavior
        }

        wait(1);

        // pop request if ready asserted
        if(m_readReqReady && !readReqList.empty())
        {
            // DEBUG cout << "Request to " << readReqList.first() << " popped by V$ at " << sc_time_stamp() << endl;
            readReqList.removeFirst();
        }
    }
}

void VectorCacheTester::pullReadResponses()
{
    wait(resetComplete);
    wait(vecCache.cacheReady);

    QList<VectorIndex> reqsToPop = m_accessList;

    while(!reqsToPop.empty())
    {
        wait(1);

        if(readRspFIFO.num_available() > 0)
        {
            VectorValue val = readRspFIFO.read();
            // DEBUG cout << "Response " << val << " at " << sc_time_stamp() << endl;
            // order checking: responses should be issued in the same order
            // as the requests
            sc_assert(val == memoryRead(reqsToPop.first()));
            sc_assert(readRspInd == reqsToPop.first());
            reqsToPop.removeFirst();
        }
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
            memReadRspFIFO.write(memoryRead(ind));
            // DEBUG cout << "Memory response for " << ind << " written at " << sc_time_stamp() << endl;
        }

        wait(1);

        if(memReadReqFIFO.nb_read(ind))
        {
            // schedule response after fixed delay
            double time_disp = (sc_time_stamp() + DRAM_RESP_LATENCY).to_double();
            m_memRespToDispatch[time_disp] = ind;
            // DEBUG cout << "Memory request for " << ind << " received at " << sc_time_stamp() << endl;
        }
    }
}


VectorValue VectorCacheTester::memoryRead(VectorIndex addr)
{
    sc_assert(addr < m_allocatedMemorySize);
    return m_mainMemory[addr];
}

void VectorCacheTester::memoryWrite(VectorIndex addr, VectorValue data)
{
    sc_assert(addr < m_allocatedMemorySize);
    m_mainMemory[addr] = data;
}
