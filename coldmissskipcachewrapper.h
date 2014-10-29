#ifndef COLDMISSSKIPCACHEWRAPPER_H
#define COLDMISSSKIPCACHEWRAPPER_H

#include "vectorcachewrapper.h"
#include "VColdMissSkipVectorCache.h"

class ColdMissSkipCacheWrapper : public VectorCacheWrapper
{
    SC_HAS_PROCESS(ColdMissSkipCacheWrapper);
public:
    ColdMissSkipCacheWrapper(sc_module_name name);
    ~ColdMissSkipCacheWrapper();

    virtual void initialize();
    virtual void connectReadReqSignals(sc_signal<VectorIndex> & data, sc_signal<bool> & ready, sc_signal<bool> & valid);
    virtual void printCacheStats();

protected:
    sc_signal<quint32> coldSkipCount;

    VColdMissSkipVectorCache * cmsVecCache;
};

#endif // COLDMISSSKIPCACHEWRAPPER_H
