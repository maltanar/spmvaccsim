#include <QDebug>
#include "memoryport.h"

MemoryPort::MemoryPort(sc_module_name name, int portId, MemorySystem *memSys, int mshrCount) : sc_module(name)
{
    m_memSys = memSys;
    m_portID = portId;
    m_mshrCount = mshrCount;
    m_availableMSHRCount = mshrCount;
    m_stop = false;

    // set default rate control settings
    // TODO make these customizable
    m_maxReqFIFOtoMSHRPerCycle = 1;
    m_maxReqMSHRtoMemSysPerCycle = 1;
    m_maxRespFromMemSysPerCycle = 1;

    // allocate MSHR entries
    MSHREntry emptyMSHREntry;
    emptyMSHREntry.address = 0;
    emptyMSHREntry.valid = false;
    emptyMSHREntry.memRequestIssued = false;
    for(int i = 0; i < m_mshrCount; i++)
        m_mshrEntries.push_back(emptyMSHREntry);

    // allocate FIFO for responses from memory system
    m_memSysResponseFIFO = new sc_fifo<MemoryOperation *>(MEMPORT_RESPONSE_FIFO_SIZE);

    // register our response FIFO with the memory system
    m_memSys->setResponseFIFO(m_portID, m_memSysResponseFIFO);

    // declare the SystemC threads
    SC_THREAD(memoryPortBehavior);
}

MemoryPort::~MemoryPort()
{
    delete m_memSysResponseFIFO;
}

void MemoryPort::stop()
{
    m_stop = true;
}

void MemoryPort::memoryPortBehavior()
{
    // main SystemC thread that implements memory port behavior

    while(!m_stop)
    {
        createRequests();
        issueRequests();
        handleResponses();

        wait(PE_CLOCK_CYCLE);
    }
}

quint64 MemoryPort::translateToAddress(quint64 val)
{
    // translate given value to address
    // default implementation is identity function
    // override as needed

    return val;
}

void MemoryPort::createRequests()
{
    // handle requests:
    // - read in entries from peInput if:
    //      * input FIFO not empty
    //      * at least one MSHR available
    //      * can issue request to memory system
    //      * output FIFO not full (too conservative?)
    // - create outgoing request and MSHR entry

    // move requests from input FIFO to MSHRs
    int maxReqFIFOtoMSHRPerCycle = m_maxReqFIFOtoMSHRPerCycle;
    while(peInput.num_available() > 0 && m_availableMSHRCount > 0)
    {
        addOutstandingRequest(peInput.read());
        if(--maxReqFIFOtoMSHRPerCycle == 0)
            break;
    }
}

void MemoryPort::issueRequests()
{
    // do not issue requests to memory system is output is clogged
    // TODO is this too conservative?
    if(peOutput.num_free() == 0)
        return;

    // move requests from MSHRs to memory system
    int maxReqMSHRtoMemSysPerCycle = m_maxReqMSHRtoMemSysPerCycle;
    for(int i=0; i < m_mshrCount; i++)
    {
        if(m_mshrEntries[i].valid && !m_mshrEntries[i].memRequestIssued && m_memSys->canAddRequest())
        {
            // issue request to memory system
            MemoryOperation * op = makeReadRequest(m_portID, m_mshrEntries[i].address, 0);
            m_memSys->addRequest(op);

            // mark MSHR as issued
            m_mshrEntries[i].memRequestIssued = true;

            // limit request injection rate
            if(--maxReqMSHRtoMemSysPerCycle == 0)
                break;
        }
    }
}

void MemoryPort::handleResponses()
{
    // handle responses:
    // - read in entries from memSysResponseFIFO if:
    //      * memSysResponseFIFO not empty
    //      * output FIFO not full
    // - check if entry corresponds to existing filled MSHR
    // - log statistics
    // - free up MSHR and put response data onto output FIFO

    // move responses to output FIFO
    int maxRespFromMemSysPerCycle = m_maxRespFromMemSysPerCycle;
    while(m_memSysResponseFIFO->num_available() > 0 && peOutput.num_free() > 0)
    {
        MemoryOperation * op = m_memSysResponseFIFO->read();

        // TODO return actual data instead of the address
        peOutput.write(op->address);

        // TODO log statistics

        // free memory and MSHR entry
        int ind = findMSHRForResponse(op->address);
        m_mshrEntries[ind].valid = false;
        m_mshrEntries[ind].memRequestIssued = false;
        m_availableMSHRCount++;

        delete op;

        // limit response rate
        if(--maxRespFromMemSysPerCycle == 0)
            break;
    }
}

void MemoryPort::addOutstandingRequest(quint64 val)
{
    // TODO maybe add support for detecting already-made requests?
    // requires a content-addressable memory in hardware implementation
    // (although out-of-order miss handling may need that anyway)

    // error out if no MSHRs available
    if(m_availableMSHRCount == 0)
    {
        qDebug() << "Error: memport" << m_portID << "has no MSHRs left!";
        exit(1);
    }

    // free MSHR available, make entry
    // locate the free MSHR. in hw we would use a queue instead of searching
    // to keep track of the free MSHRs
    int freeIndex = -1;
    for(int i=0; i < m_mshrCount; i++)
    {
        if(m_mshrEntries[i].valid == false)
        {
            freeIndex = i;
        }
    }

    // sanity check to see if we actually found a free MSHR
    if(freeIndex == -1)
    {
        qDebug() << "Error: memport" << m_portID << "has no MSHRs left!";
        exit(1);
    }

    // add the entry
    m_mshrEntries[freeIndex].valid = true;
    m_mshrEntries[freeIndex].memRequestIssued = false;
    m_mshrEntries[freeIndex].address = translateToAddress(val);

    // decrement free MSHR count
    m_availableMSHRCount--;
}

int MemoryPort::findMSHRForResponse(quint64 addr)
{
    int mshrInd = -1;
    for(int i=0; i < m_mshrCount; i++)
    {
        if(m_mshrEntries[i].valid && m_mshrEntries[i].memRequestIssued && m_mshrEntries[i].address == addr)
        {
            mshrInd = i;
            break;
        }
    }

    if(mshrInd == -1)
    {
        qDebug() << "Error: memport" << m_portID << "cannot find MSHR for" << addr;
        exit(1);
    }

    return mshrInd;
}
