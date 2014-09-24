#include "burstmemoryport.h"

BurstMemoryPort::BurstMemoryPort(sc_module_name name, int portId, MemRequestTag tag, MemorySystem * memSys, int mshrCount)
    : MemoryPort(name, portId, tag, memSys, mshrCount)
{
}

quint64 BurstMemoryPort::alignStartAddressForBurst(quint64 addr)
{
    if(addr % MEMPORT_TOTAL_BURST_LEN != 0)
        addr += MEMPORT_TOTAL_BURST_LEN - (addr % MEMPORT_TOTAL_BURST_LEN);

    return addr;
}

void BurstMemoryPort::createRequests()
{
    // only read in from input FIFO if we have enough addresses available for a burst
    // must ensure input FIFOs generate addresses quickly enough in order not to become a bottleneck

    int maxReqFIFOtoMSHRPerCycle = m_maxReqFIFOtoMSHRPerCycle;
    while(peInput.num_available() >= MEMPORT_WORDS_PER_BURST && m_availableMSHRCount > 0)
    {
        // actually create a request for the first entrty
        quint64 prev = peInput.read(), now = 0;
        sc_assert(prev % MEMPORT_TOTAL_BURST_LEN == 0);   // ensure start address is aligned to burst length
        addOutstandingRequest(prev);

        // just get rid of the following n-1 entries (included in burst read command)
        for(int i = 0; i < MEMPORT_WORDS_PER_BURST-1; i++)
        {
            now = peInput.read();
            sc_assert(prev + DRAM_ACCESS_WIDTH_BYTES == now);  // make sure requests are consecutive, otherwise burst doesn't make sense
            prev = now;
        }

        if(--maxReqFIFOtoMSHRPerCycle == 0)
            break;
    }
}

void BurstMemoryPort::issueRequests()
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
            MemoryOperation * op = makeReadRequest(m_portID, m_mshrEntries[i].address, m_reqTag, MEMPORT_TOTAL_BURST_LEN);
            m_memSys->addRequest(op);
            m_requests++;

            // mark MSHR as issued
            m_mshrEntries[i].memRequestIssued = true;

            // limit request injection rate
            if(--maxReqMSHRtoMemSysPerCycle == 0)
                break;
        }
    }
}

void BurstMemoryPort::handleResponses()
{
    // each response from memory system maps into multiple words on the output
    // make sure we have enough room in the output FIFO

    // move responses to output FIFO
    int maxRespFromMemSysPerCycle = m_maxRespFromMemSysPerCycle;

    while(m_memSysResponseFIFO->num_available() > 0 && peOutput.num_free() >= MEMPORT_WORDS_PER_BURST)
    {
        MemoryOperation * op = m_memSysResponseFIFO->read();
        m_responses++;

        // add consecutive entries from burst
        for(int i = 0; i < MEMPORT_WORDS_PER_BURST; i++)
        {
            peOutput.write(op->address + DRAM_ACCESS_WIDTH_BYTES * i);
        }

        // TODO log statistics

        // free memory and MSHR entry
        int ind = findMSHRForResponse(op->address);
        m_mshrEntries[ind].valid = false;
        m_mshrEntries[ind].memRequestIssued = false;
        m_availableMSHRCount++;

        freeRequest(op);

        // limit response rate
        if(--maxRespFromMemSysPerCycle == 0)
            break;
    }
}
