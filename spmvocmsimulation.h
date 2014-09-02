#ifndef SPMVOCMSIMULATION_H
#define SPMVOCMSIMULATION_H

#include <systemc.h>
#include <QMap>
#include "memorysystem.h"
#include "processingelement.h"

class ProcessingElement;

class SpMVOCMSimulation : public sc_module
{
public:
    SpMVOCMSimulation(QString matrixName, int peCount, int maxOutstandingMemReqsPerPE, CacheMode cacheMode, bool useInterleavedMapping, QMap<QString, QString> memsysOverrides);
    ~SpMVOCMSimulation();

    void run();
    void signalFinishedPE(int peID);

    // statistics
    double getAverageLatency();
    double getAveragePowerBackground();
    double getAveragePowerBurst();
    double getAveragePowerRefresh();
    double getAveragePowerActPre();

protected:
    QString m_matrixName;
    int m_peCount, m_maxOutstandingMemReqsPerPE;
    CacheMode m_cacheMode;
    bool m_useInterleavedMapping;
    int m_reqFIFOSize, m_respFIFOSize;

    MemorySystem * m_memorySystem;
    sc_fifo<MemoryOperation *> * m_requestFIFO;
    QList<ProcessingElement *> m_processingElements;
    QList<sc_fifo<MemoryOperation *> *> m_responseFIFOs;
    QList<bool> m_finished;


};

#endif // SPMVOCMSIMULATION_H
