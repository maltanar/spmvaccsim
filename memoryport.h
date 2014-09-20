#ifndef MEMORYPORT_H
#define MEMORYPORT_H

#define MEMPORT_RESPONSE_FIFO_SIZE      32

#include "memorysystem.h"
#include "utilities.h"

class MemoryPort : public sc_module
{
    SC_HAS_PROCESS(MemoryPort);

public:
    MemoryPort(sc_module_name name,     // name for SystemC module
               int portId,              // identifier for this port
               MemorySystem * memSys,   // target memory system
               int mshrCount);          // number of MSHRs
    ~MemoryPort();

    // interface towards the processing element
    sc_fifo_in<quint64> peInput;
    sc_fifo_out<quint64> peOutput;

    virtual void memoryPortBehavior();

protected:
    virtual quint64 translateToAddress(quint64 val);

    MemorySystem * m_memSys;
    int m_portID, m_mshrCount;
    sc_fifo<MemoryOperation *> * m_memSysResponseFIFO;

    // TODO add data structures and functions for MSHRs and MSHA
};

#endif // MEMORYPORT_H
