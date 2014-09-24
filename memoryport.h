#ifndef MEMORYPORT_H
#define MEMORYPORT_H

#define MEMPORT_RESPONSE_FIFO_SIZE      32

#include "memorysystem.h"
#include "utilities.h"

// TODO the MSHR / multiple outstanding reqs version should actually
// be implemented in a derived class, not here in this base class

class MemoryPort : public sc_module
{
    SC_HAS_PROCESS(MemoryPort);

public:
    MemoryPort(sc_module_name name,     // name for SystemC module
               int portId,              // identifier for this port
               MemRequestTag tag,       // tag to identify requests from this port
               MemorySystem * memSys,   // target memory system
               int mshrCount);          // number of MSHRs
    ~MemoryPort();

    // interface towards the processing element
    sc_fifo_in<quint64> peInput;
    sc_fifo_out<quint64> peOutput;

    void stop();
    void setBypassMode(bool enable);

    virtual void memoryPortBehavior();

protected:
    virtual quint64 translateToAddress(quint64 val);
    virtual void createRequests();
    virtual void issueRequests();
    virtual void handleResponses();

    MemorySystem * m_memSys;
    int m_portID, m_mshrCount;
    bool m_stop;
    bool m_bypassEnabled;
    MemRequestTag m_reqTag;

    // FIFO for receiving responses from the memory system
    sc_fifo<MemoryOperation *> * m_memSysResponseFIFO;
    // request-response rate control settings
    int m_maxReqFIFOtoMSHRPerCycle, m_maxReqMSHRtoMemSysPerCycle, m_maxRespFromMemSysPerCycle;

    // data structures and functions for MSHRs / MHA
    typedef struct {
        bool valid;
        bool memRequestIssued;
        quint64 address;
    } MSHREntry;
    QList<MSHREntry> m_mshrEntries;
    int m_availableMSHRCount;
    void addOutstandingRequest(quint64 val);
    int findMSHRForResponse(quint64 addr);

    quint64 m_requests, m_responses;
};

#endif // MEMORYPORT_H
