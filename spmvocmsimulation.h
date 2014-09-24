#ifndef SPMVOCMSIMULATION_H
#define SPMVOCMSIMULATION_H

#include <systemc.h>
#include <QMap>
#include <QSqlDatabase>
#include "memorysystem.h"
#include "processingelement.h"

class ProcessingElement;

class SpMVOCMSimulation : public sc_module
{
public:
    SpMVOCMSimulation(QString matrixName, int peCount, int maxOutstandingMemReqsPerPE, CacheMode cacheMode, uint64_t cacheWordsPerPE,
                      QList<MemRequestTag> bypass);
    ~SpMVOCMSimulation();

    void run();
    void signalFinishedPE(int peID);

    // statistics
    double getAverageLatency();
    double getAveragePowerBackground();
    double getAveragePowerBurst();
    double getAveragePowerRefresh();
    double getAveragePowerActPre();

    void saveStatisticsToDB(QString dbName);

protected:
    QString m_matrixName;
    int m_peCount, m_maxOutstandingMemReqsPerPE;
    CacheMode m_cacheMode;
    int m_reqFIFOSize;
    int m_cacheWordsPerPE;

    MemorySystem * m_memorySystem;
    sc_fifo<MemoryOperation *> * m_requestFIFO;
    QList<ProcessingElement *> m_processingElements;
    QList<bool> m_finished;

    void createDBTables();

    // statistics
    quint64 m_totalCycles;


};

#endif // SPMVOCMSIMULATION_H
