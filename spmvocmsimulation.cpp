#include <QProcessEnvironment>
#include <QDebug>
#include "spmvoperation.h"
#include "spmvocmsimulation.h"

// includes for dumping data to the database
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

SpMVOCMSimulation::SpMVOCMSimulation(QString matrixName, int peCount, int maxOutstandingMemReqsPerPE,
                                     CacheMode cacheMode, uint64_t cacheWordsPerPE, QMap<QString, QString> memsysOverrides,
                                     QList<MemRequestTag> bypass) :
    sc_module(sc_module_name("top"))
{
    // tone down the SystemC verbosity
    sc_report_handler::set_actions (SC_WARNING, SC_DO_NOTHING);
    sc_report_handler::set_actions (SC_INFO, SC_DO_NOTHING);

    m_reqFIFOSize = 32;
    m_totalCycles = 0;

    m_matrixName = matrixName;
    m_peCount = peCount;
    m_maxOutstandingMemReqsPerPE = maxOutstandingMemReqsPerPE;
    m_cacheMode = cacheMode;
    m_cacheWordsPerPE = cacheWordsPerPE;

    // instantiate the memory system simulator (DRAMsim)
    // TODO move request directly inside MemorySystem?
    m_requestFIFO = new sc_fifo<MemoryOperation *>(m_reqFIFOSize);
    m_memorySystem = new MemorySystem("memsys", memsysOverrides);
    m_memorySystem->setRequestFIFO(m_requestFIFO);

    // load the sparse matrix to create the access patterns
    SpMVOperation * spmv = new SpMVOperation(matrixName);

    // create the desired setup
    for(int i = 0; i < m_peCount; i++)
    {
        m_finished.push_back(false);

        ProcessingElement * newPE = new ProcessingElement("pe", i, m_maxOutstandingMemReqsPerPE, m_cacheWordsPerPE, cacheMode, this, bypass);

        // assign work for this new PE from the SpMV operation
        newPE->assignWork(spmv, m_peCount);
        newPE->connectToMemorySystem(m_memorySystem);

        m_processingElements.push_back(newPE);
    }

    delete spmv;
}

SpMVOCMSimulation::~SpMVOCMSimulation()
{
    // deallocate objects
    for(int i = 0; i < m_peCount; i++)
    {
        delete m_processingElements[i];

    }
    delete m_memorySystem;
    delete m_requestFIFO;
}

void SpMVOCMSimulation::run()
{
    sc_start();
}

void SpMVOCMSimulation::signalFinishedPE(int peID)
{
    m_finished[peID] = true;

    if(m_finished.count(true) == m_peCount)
    {
        // all PEs finished
        m_totalCycles = sc_time_stamp() / PE_CLOCK_CYCLE;
        sc_stop();


        qDebug() << "total cycles " << m_totalCycles;
        // TODO control the dumping of these statistics
        for(int i = 0; i < m_peCount; i++)
        {
            ProcessingElement * pe = m_processingElements[i];
            qDebug() << "PE #" << i << " : \t\t" <<  pe->getCyclesWithResponse() << (float)(pe->getCyclesWithResponse())/(float)m_totalCycles << pe->getAverageMemLatency() / PE_CLOCK_CYCLE
                        << "\t" << pe->getCacheHits() << pe->getCacheMisses() << (float)pe->getCacheHits()/(float)(pe->getCacheHits()+pe->getCacheMisses());
        }

        SHOW_SIM_OUTPUT = 1;
        m_memorySystem->printFinalStats();
    }
}

double SpMVOCMSimulation::getAverageLatency()
{
    return m_memorySystem->getAverageReqRespLatency();
}

double SpMVOCMSimulation::getAveragePowerBackground()
{
    return m_memorySystem->getAveragePowerBackground();
}

double SpMVOCMSimulation::getAveragePowerBurst()
{
    return m_memorySystem->getAveragePowerBurst();
}

double SpMVOCMSimulation::getAveragePowerRefresh()
{
    return m_memorySystem->getAveragePowerRefresh();
}

double SpMVOCMSimulation::getAveragePowerActPre()
{
    return m_memorySystem->getAveragePowerActPre();
}

void SpMVOCMSimulation::saveStatisticsToDB(QString dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if(!db.open())
    {
        qDebug() << "failed to open DB: " << db.lastError();
        return;
    }

    createDBTables();

    QSqlQuery q;

    // create the global (average) results entry
    q.prepare("INSERT INTO avgResults (matrix, pecount, outstandingReqs, cachemode, cachePerPE, totalCycles, avgMemRespLatency, avgPowerBkg, avgPowerBurst, avgPowerRefresh, avgPowerActPre) "
              "VALUES (:matrix, :pecount, :outstandingReqs, :cachemode, :cachePerPE, :totalCycles, :avgMemRespLatency, :avgPowerBkg, :avgPowerBurst, :avgPowerRefresh, :avgPowerActPre)");

    q.bindValue(":matrix", m_matrixName);
    q.bindValue(":pecount", m_peCount);
    q.bindValue(":outstandingReqs", m_maxOutstandingMemReqsPerPE);
    q.bindValue(":cachemode", m_cacheMode);
    q.bindValue(":cachePerPE", m_cacheWordsPerPE);
    q.bindValue(":totalCycles", m_totalCycles);
    q.bindValue(":avgMemRespLatency", getAverageLatency() );
    q.bindValue(":avgPowerBkg", getAveragePowerBackground() );
    q.bindValue(":avgPowerBurst", getAveragePowerBurst() );
    q.bindValue(":avgPowerRefresh", getAveragePowerRefresh() );
    q.bindValue(":avgPowerActPre", getAveragePowerActPre() );

    if(!q.exec())
        qDebug() << "Error while executing avgResults query: " << q.lastError();

    QVariant resultId = q.lastInsertId();

    // add per-PE results
    q.prepare("INSERT INTO perPEResults (expId, peId, numElements, cyclesWithResponse, cacheHits, avgMemLatency) VALUES "
              "(:expId, :peId, :numElements, :cyclesWithResponse, :cacheHits, :avgMemLatency)");


    for(int i = 0; i < m_peCount; i++)
    {
        ProcessingElement * pe = m_processingElements[i];

        q.bindValue(":expId", resultId);
        q.bindValue(":peId", i);
        q.bindValue(":numElements", pe->getAssignedElemCount());
        q.bindValue(":cyclesWithResponse", (quint64) pe->getCyclesWithResponse());
        q.bindValue(":cacheHits", (quint64) pe->getCacheHits());
        q.bindValue(":avgMemLatency", pe->getAverageMemLatency() / PE_CLOCK_CYCLE);

        if(!q.exec())
            qDebug() << "error while executing perPEResults query: " << q.lastError();

    }

    db.close();

    qDebug() << "Experiment saved into database with ID #" << resultId.toInt();
}

void SpMVOCMSimulation::createDBTables()
{
    QSqlQuery q;

    bool ret = q.exec("CREATE TABLE IF NOT EXISTS avgResults (  id INTEGER PRIMARY KEY, matrix VARCHAR(30), pecount INTEGER, "
                      "outstandingReqs INTEGER, cachemode INTEGER, cachePerPE INTEGER, totalCycles INTEGER, avgMemRespLatency REAL,"
                      "avgPowerBkg REAL, avgPowerBurst REAL, avgPowerRefresh REAL, avgPowerActPre REAL )");

    if (!ret)
        qDebug() << "Error while creating average results table: " << q.lastError();

    ret = q.exec("CREATE TABLE IF NOT EXISTS perPEResults ( id INTEGER PRIMARY KEY, expId INTEGER, peId INTEGER, numElements INTEGER, "
                 "cyclesWithResponse INTEGER, cacheHits INTEGER, avgMemLatency REAL)");

    if (!ret)
        qDebug() << "Error while creating per-PE results table: " << q.lastError();
}
