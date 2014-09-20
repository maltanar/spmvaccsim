#include "memoryport.h"

MemoryPort::MemoryPort(sc_module_name name, int portId, MemorySystem *memSys, int mshrCount) : sc_module(name)
{
    m_memSys = memSys;
    m_portID = portId;
    m_mshrCount = mshrCount;

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

void MemoryPort::memoryPortBehavior()
{
    // TODO add memory port behavior here
    // handle requests:
    // - read in entries from peInput if:
    //      * input FIFO not empty
    //      * at least one MSHR available
    //      * can issue request to memory system
    //      * output FIFO not full (too conservative?)
    // - create outgoing request and MSHR entry
    // handle responses:
    // - read in entries from memSysResponseFIFO if:
    //      * memSysResponseFIFO not empty
    //      * output FIFO not full
    // - check if entry corresponds to existing filled MSHR
    // - log statistics
    // - free up MSHR and put response data onto output FIFO

}

quint64 MemoryPort::translateToAddress(quint64 val)
{
    // translate given value to address
    // default implementation is identity function
    // override as needed

    return val;
}
