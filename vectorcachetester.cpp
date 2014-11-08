#include "vectorcachetester.h"
#include "spmvoperation.h"

#include <QDebug>
#include "coldmissskipcachewrapper.h"

//#define DEBUGOUT(X) X
#define DEBUGOUT(X) 0

VectorIndex indToMonitor = -2;

using namespace std;

VectorCacheTester::VectorCacheTester(sc_module_name name, int useColdSkip) :
    sc_module(name), clkSource("clk", PE_CLOCK_CYCLE),
    readRspFIFO(RDRSP_FIFO_SIZE), writeDataFIFO(WRITE_FIFO_SIZE), memWriteDataFIFO(WRITE_FIFO_SIZE),
    memReadReqFIFO(MEMRDREQ_FIFO_SIZE), memReadRspFIFO(MEMRDRSP_FIFO_SIZE),
    writeReqFIFO(WRITE_FIFO_SIZE), memWriteReqFIFO(WRITE_FIFO_SIZE)
{
    simFinished = false;
    m_mainMemory = NULL;

    clk(clkSource);

    if(useColdSkip)
    {
        vecCache = new ColdMissSkipCacheWrapper("v$");
        m_useColdSkip = true;
    }
    else
    {
        vecCache = new VectorCacheWrapper("v$");
        m_useColdSkip = false;
    }

    vecCache->initialize();

    vecCache->clk(clk);
    vecCache->reset(reset);

    vecCache->readResp.bind(readRspFIFO);
    vecCache->readRespInd.bind(readRspInd);
    vecCache->memoryReadReq.bind(memReadReqFIFO);
    vecCache->memoryReadResp.bind(memReadRspFIFO);

    vecCache->writeData.bind(writeDataOut);
    vecCache->writeReq.bind(writeReqFIFO);

    vecCache->memoryWriteData.bind(memWriteDataOut);
    vecCache->memoryWriteReq.bind(memWriteReqFIFO);

    vecCache->connectReadReqSignals(m_readReqData, m_readReqReady, m_readReqValid);

    reset = true;

    SC_CTHREAD(generateReset, clk.pos());
    SC_CTHREAD(pushReadRequests, clk.pos());
    //SC_CTHREAD(pullReadResponses, clk.pos());
    SC_CTHREAD(handleDRAMReads, clk.pos());
    SC_CTHREAD(handleDRAMWrites, clk.pos());
    SC_CTHREAD(handleDatapath, clk.pos());

    SC_METHOD(handleWriteData);
    sensitive << writeReqFIFO.data_read_event();
    dont_initialize();

    SC_METHOD(handleMemWriteData);
    sensitive << memWriteReqFIFO.data_written_event();
    dont_initialize();
}

VectorCacheTester::~VectorCacheTester()
{
    delete m_mainMemory;
    delete vecCache;
}

void VectorCacheTester::setAccessList(QList<VectorIndex> list)
{
    m_accessList = list;
}

void VectorCacheTester::initializeMemory(unsigned int numElements)
{
    m_allocatedMemorySize = numElements;
    m_mainMemory = new VectorValue[numElements];

    for(unsigned int i = 0; i < numElements; i++)
        m_mainMemory[i] = 0;
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
    DEBUGOUT(cout << "Reset completed at " << sc_time_stamp() << endl);
}

void VectorCacheTester::pushReadRequests()
{
    wait(resetComplete);
    cout << "Reset complete at " << sc_time_stamp() << endl;
    wait(vecCache->cacheReady);
    cout << "Cache ready to accept requests at " << sc_time_stamp() << endl;
    GlobalConfig::getInstance().setResultData("cacheInitCycles", sc_time_stamp() / PE_CLOCK_CYCLE);

    // make copy of m_accessList to avoid overwriting
    // call function to create a new list without RAW hazards
    QList<VectorIndex> readReqList = SpMVOperation::insertHazardAvoidanceBubbles(m_accessList, GlobalConfig::getHazardWindowSize());

    // if desired, add start-of-row markers
    if(m_useColdSkip)
        readReqList = SpMVOperation::insertStartOfRowMarkers(readReqList);

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
            DEBUGOUT(cout << "Request to " << readReqList.first() << " popped by V$ at " << sc_time_stamp() << endl);
            readReqList.removeFirst();
            if(!readReqList.empty() && readReqList.first() == indToMonitor)
            {
                cout << readReqList.first() << " is being requested at " << sc_time_stamp() << endl;
            }
        }
    }

    m_readReqValid = false;
    m_readReqData = 0xdeadbeef;
}


void VectorCacheTester::handleDRAMReads()
{
    wait(resetComplete);
    // fixed-latency path between memReadReqFIFO and memReadRspFIFO
    while(!simFinished)
    {
        double time_now = sc_time_stamp().to_double();
        VectorIndex ind = 0;

        // correctness check: no more than 1 outstanding read req
        // (blocking cache)
        if(m_memRespToDispatch.size() > 1)
        {
            cerr << "Error: " << m_memRespToDispatch.size() << " outstanding DRAM read requests" << endl;
            sc_stop();
        }

        if(m_memRespToDispatch.contains(time_now))
        {
            ind = m_memRespToDispatch[time_now];
            m_memRespToDispatch.remove(time_now);
            // TODO mem r/w consistency issues here?
            sc_assert(memReadRspFIFO.nb_write(memoryRead(ind)));
            //cout << "Memory read response for " << ind << " written at " << sc_time_stamp() << endl;
            if(ind == indToMonitor)
                cout << "Memory read response for " << ind << " " << memoryRead(ind) <<  " written at " << sc_time_stamp() << endl;
        }

        wait(1);

        if(memReadReqFIFO.nb_read(ind))
        {
            // schedule response after fixed delay
            double time_disp = (sc_time_stamp() + DRAM_RESP_LATENCY).to_double();
            m_memRespToDispatch[time_disp] = ind;
            //cout << "Memory read request for " << ind << " received at " << sc_time_stamp() << endl;
            if(ind == indToMonitor)
                cout << "Memory read request for " << ind << " received at " << sc_time_stamp() << endl;
        }
    }
}

void VectorCacheTester::handleDRAMWrites()
{
    wait(resetComplete);

    while(!simFinished)
    {
        VectorIndex ind = 0;

        if(memWriteReqFIFO.nb_read(ind))
        {
            // also pop data from memWriteDataFIFO
            VectorValue val = 0;
            sc_assert(memWriteDataFIFO.nb_read(val));

            if(ind == indToMonitor)
            {
                cout << "Memory write to " << ind << " data " << val << " at " << sc_time_stamp() << endl;
            }

            DEBUGOUT(cout << "Memory write to " << ind << " data " << val << " at " << sc_time_stamp() << endl);
            memoryWrite(ind, val);
        }

        wait(1);
    }
}

void VectorCacheTester::handleDatapath()
{
    QList<VectorIndex> reqsToPop = m_accessList;

    // fixed-latency path between readRespFIFO and writeReqFIFO
    while(!reqsToPop.empty() || !m_writeDataToDispatch.empty())
    {
        double time_now = sc_time_stamp().to_double();
        VectorIndex ind = 0;
        VectorValue val = 0;

        if(m_writeReqToDispatch.contains(time_now))
        {
            ind = m_writeReqToDispatch[time_now];
            m_writeReqToDispatch.remove(time_now);
            val = m_writeDataToDispatch.takeFirst();

            writeReqFIFO.write(ind);
            writeDataFIFO.write(val);
            DEBUGOUT(cout << "Write request to " << ind << " value " << val << " written at " << sc_time_stamp() << endl);
            if(ind == indToMonitor)
            {
                cout << "Write request to " << ind << " value " << val << " written at " << sc_time_stamp() << endl;
            }
        }

        wait(1);

        if(readRspFIFO.nb_read(val))
        {
            // schedule response after fixed delay
            double time_disp = (sc_time_stamp() + DATAPATH_LATENCY).to_double();
            VectorIndex ind = readRspInd;

            // correctness check: read responses / write requests appear in correct order
            if(ind != reqsToPop.first())
            {
                cerr << "Error: Datapath received read response for " << ind << " while expecting for " << reqsToPop.first() << endl;
                sc_stop();
            }
            // correctness check: since our datapath always increments the result by readRspInd,
            // any values received should be dividable by readRespInd
            if (val != 0)
            {
                if (((unsigned long int) val ) % ind != 0)
                {
                    cerr << "Error: Datapath received invalid read response " << val << " for " << ind << endl;
                    sc_stop();
                }
            }

            // our datapath just performs the operation val = val + ind
            m_writeDataToDispatch.push_back(val + ind);
            m_writeReqToDispatch[time_disp] = ind;
            DEBUGOUT(cout << "Read response for " << ind << " value " << val << " received at " << sc_time_stamp() << endl);


            if(readRspInd == indToMonitor)
                cout << "Read response for " << readRspInd << " value " << val << " received at " << sc_time_stamp() << endl;


            reqsToPop.removeFirst();
        }
    }

    // cache writes determine the finish condition
    // wait until all writes have completed (i.e all write FIFOs empty)
    while(writeReqFIFO.num_available() > 0)
        wait(1);

    wait(10);

    // flush the cache
    vecCache->flush();

    // wait until all main memory writes have completed
    while(memWriteReqFIFO.num_available() > 0)
            wait(1);

    simFinished = true;

    // print final cache stats
    vecCache->printCacheStats();

    // stop the simulation
    sc_stop();

    if(checkResult())
        cout << "Result is correct!" << endl;
    else
        cout << "Result is incorrect!" << endl;
}

void VectorCacheTester::handleWriteData()
{
    // whenever a request is popped from the write req FIFO,
    // pop from the write data FIFO as well
    VectorValue data;
    sc_assert(writeDataFIFO.nb_read(data));
    writeDataOut = data;
}

void VectorCacheTester::handleMemWriteData()
{
    // whenever a request is pushed into the mem write req FIFO,
    // push the memWriteData into its own FIFO
    memWriteDataFIFO.nb_write(memWriteDataOut);
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

bool VectorCacheTester::checkResult()
{
    VectorValue * goldenMem = new VectorValue[m_allocatedMemorySize];

    // initialize all golden mem entries to zero
    for(unsigned int i = 0; i < m_allocatedMemorySize; i++)
    {
        goldenMem[i] = 0;
    }

    // compute the golden values
    for(unsigned int i = 0; i < m_accessList.size(); i++)
    {
        VectorIndex currentIndex = m_accessList[i];
        goldenMem[currentIndex] += currentIndex;
    }

    // compare against the computed result
    bool match = true;
    unsigned int mismatchCount = 0;

    for(unsigned int i = 0; i < m_allocatedMemorySize; i++)
    {
        if(goldenMem[i] != m_mainMemory[i])
        {
            match = false;
            //cout << "Golden and computed results differ at position " << i << ":" << endl;
            //cout << "Golden " << goldenMem[i] << ", computed " << m_mainMemory[i] << endl;
            mismatchCount++;
        }
    }

    delete goldenMem;

    cout << "Mismatch count " << mismatchCount << endl;

    GlobalConfig::getInstance().setResultData("mismatchCount", mismatchCount);

    return match;
}
