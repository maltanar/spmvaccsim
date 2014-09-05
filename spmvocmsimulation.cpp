#include <QProcessEnvironment>
#include <QDebug>
#include "spmvoperation.h"
#include "spmvocmsimulation.h"

SpMVOCMSimulation::SpMVOCMSimulation(QString matrixName, int peCount, int maxOutstandingMemReqsPerPE, CacheMode cacheMode, uint64_t cacheWordsPerPE, bool useInterleavedMapping, QMap<QString, QString> memsysOverrides) :
    sc_module(sc_module_name("top"))
{
    // tone down the SystemC verbosity
    sc_report_handler::set_actions (SC_WARNING, SC_DO_NOTHING);
    sc_report_handler::set_actions (SC_INFO, SC_DO_NOTHING);

    m_reqFIFOSize = 32;
    m_respFIFOSize = 32;

    // TODO use the maxOutstandingMemReqsPerPE and cacheMode params as well

    m_matrixName = matrixName;
    m_peCount = peCount;
    m_maxOutstandingMemReqsPerPE = maxOutstandingMemReqsPerPE;
    m_cacheMode = cacheMode;
    m_useInterleavedMapping = useInterleavedMapping;
    m_cacheWordsPerPE = cacheWordsPerPE;

    // instantiate the memory system simulator (DRAMsim)
    m_requestFIFO = new sc_fifo<MemoryOperation *>(m_reqFIFOSize);
    m_memorySystem = new MemorySystem("memsys", memsysOverrides);
    m_memorySystem->setRequestFIFO(m_requestFIFO);

    // load the sparse matrix to create the access patterns
    SpMVOperation * spmv = new SpMVOperation(matrixName);

    // create the desired setup
    for(int i = 0; i < m_peCount; i++)
    {
        m_finished.push_back(false);
        sc_fifo<MemoryOperation *> * newRespFIFO = new sc_fifo<MemoryOperation *>(m_respFIFOSize);
        m_memorySystem->setResponseFIFO(i, newRespFIFO);

        ProcessingElement * newPE = new ProcessingElement("pe", i, m_maxOutstandingMemReqsPerPE, m_cacheWordsPerPE, cacheMode, this);

        newPE->setRequestFIFO(m_requestFIFO);
        newPE->setResponseFIFO(newRespFIFO);

        // create the access pattern for the PE
        newPE->setAccessedElementList(spmv->getDVAccessPattern(i, peCount, useInterleavedMapping));

        m_responseFIFOs.push_back(newRespFIFO);
        m_processingElements.push_back(newPE);
    }

    delete spmv;
}

SpMVOCMSimulation::~SpMVOCMSimulation()
{
    // deallocate objects
    for(int i = 0; i < m_peCount; i++)
    {
        delete m_responseFIFOs[i];
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
    uint64_t totalCycles = 0;
    m_finished[peID] = true;

    if(m_finished.count(true) == m_peCount)
    {
        // all PEs finished
        totalCycles = sc_time_stamp() / PE_CLOCK_CYCLE;
        sc_stop();

        qDebug() << "total cycles " << totalCycles;
        // TODO control the dumping of these statistics
        for(int i = 0; i < m_peCount; i++)
        {
            ProcessingElement * pe = m_processingElements[i];
            qDebug() << "PE #" << i << " : \t\t" <<  pe->getCyclesWithResponse() << (float)(pe->getCyclesWithResponse())/(float)totalCycles << pe->getAverageMemLatency() / PE_CLOCK_CYCLE
                        << "\t" << pe->getCacheHits() << pe->getCacheMisses() << (float)pe->getCacheHits()/(float)(pe->getCacheHits()+pe->getCacheMisses());
        }
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
