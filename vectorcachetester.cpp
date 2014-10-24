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
    //SC_CTHREAD(pullReadResponses, clk.pos());
    SC_CTHREAD(handleDRAMReads, clk.pos());
    SC_CTHREAD(handleDRAMWrites, clk.pos());
    SC_CTHREAD(handleDatapath, clk.pos());
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
    cout << "Reset completed at " << sc_time_stamp() << endl;
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
        cout << "Request to " << readReqList.first() << " written at " << sc_time_stamp() << endl;
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
            cout << "Request to " << readReqList.first() << " popped by V$ at " << sc_time_stamp() << endl;
            readReqList.removeFirst();
        }
    }

    m_readReqValid = false;
    m_readReqData = 0xdeadbeef;
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
            cout << "Response " << val << " at " << sc_time_stamp() << endl;
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

void VectorCacheTester::handleDRAMReads()
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

void VectorCacheTester::handleDRAMWrites()
{
    wait(resetComplete);

    QList<VectorIndex> reqsToPop = m_accessList;

    while(!reqsToPop.empty())
    {
        VectorIndex ind = 0;

        if(memWriteReqFIFO.nb_read(ind))
        {
            // check that write requests appear in correct order
            sc_assert(ind == reqsToPop.first());
            cout << "Memory write to " << ind << " data " << writeDataOut << " at " << sc_time_stamp() << endl;
            memoryWrite(ind, writeDataOut);
            reqsToPop.removeFirst();
        }

        wait(1);
    }

    // responses determine the finish condition
    simFinished = true;

    // print final cache stats
    vecCache.printCacheStats();

    // stop the simulation
    sc_stop();
}

void VectorCacheTester::handleDatapath()
{
    // fixed-latency path between readRespFIFO and writeReqFIFO
    while(!simFinished)
    {
        double time_now = sc_time_stamp().to_double();
        VectorIndex ind = 0;
        VectorValue val = 0;

        if(m_writeReqToDispatch.contains(time_now))
        {
            ind = m_writeReqToDispatch[time_now];
            val = m_writeDataToDispatch.takeFirst();

            writeReqFIFO.write(ind);
            writeDataOut = val;
            cout << "Write request to " << ind << " value " << val << " written at " << sc_time_stamp() << endl;
        }

        wait(1);

        if(readRspFIFO.nb_read(val))
        {
            // schedule response after fixed delay
            double time_disp = (sc_time_stamp() + DATAPATH_LATENCY).to_double();
            m_writeReqToDispatch[time_disp] = readRspInd;
            // our datapath just performs the operation val = val + 1
            m_writeDataToDispatch.push_back(val + 1);
            cout << "Read response for " << readRspInd << " value " << val << " received at " << sc_time_stamp() << endl;
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
