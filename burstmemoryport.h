#ifndef BURSTMEMORYPORT_H
#define BURSTMEMORYPORT_H

#include "memoryport.h"

#define MEMPORT_WORDS_PER_BURST         (GlobalConfig::getDRAMConfig().burstLength)
#define MEMPORT_TOTAL_BURST_LEN         (MEMPORT_WORDS_PER_BURST * DRAM_ACCESS_WIDTH_BYTES)

class BurstMemoryPort : public MemoryPort
{
    SC_HAS_PROCESS(BurstMemoryPort);

public:
    BurstMemoryPort(sc_module_name name,     // name for SystemC module
                    int portId,              // identifier for this port
                    MemRequestTag tag,       // tag to identify requests from this port
                    MemorySystem * memSys,   // target memory system
                    int mshrCount,           // number of MSHRs
                    int peDataUnitSize = DRAM_ACCESS_WIDTH_BYTES);     // data unit size for PE

    static quint64 alignStartAddressForBurst(quint64 addr);

    int getPEDataUnitsPerBurst();

protected:
    virtual void createRequests();
    virtual void issueRequests();
    virtual void handleResponses();

    int m_peDataUnitSize, m_peDataUnitsPerBurst;
};

#endif // BURSTMEMORYPORT_H
