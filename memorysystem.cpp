#include <QDebug>
#include <QMapIterator>
#include "memorysystem.h"
#include "utilities.h"

using namespace DRAMSim;

double MemorySystem::m_powerSum[4];
uint64_t MemorySystem::m_powerSamples;

MemorySystem::MemorySystem(sc_module_name name) : sc_module(name)
{
    m_systemConfigFile = "system.ini";
    m_megsOfMemory = GlobalConfig::getInstance().getMemorySizeMB();

    // convert the override map to std::map
    QMapIterator<QString, QString> it(GlobalConfig::getInstance().getMemSysConfig());
    IniReader::OverrideMap overrideStdMap;

    while(it.hasNext())
    {
        it.next();
        overrideStdMap[it.key().toStdString()] = it.value().toStdString();
    }

    // create the DRAMSim2 memory system instance
    m_DRAMSim = getMemorySystemInstance(GlobalConfig::getInstance().getMemConfigFile().toStdString(), m_systemConfigFile.toStdString(),
                                        INI_CONFIG_DIR, "example_app", m_megsOfMemory, NULL, &overrideStdMap);

    m_readCB = new Callback<MemorySystem, void, unsigned, uint64_t, uint64_t>(this, &MemorySystem::readComplete);
    m_writeCB = new Callback<MemorySystem, void, unsigned, uint64_t, uint64_t>(this, &MemorySystem::writeComplete);

    // register callback functions
    // m_DRAMSim->RegisterCallbacks(m_readCB, m_writeCB, NULL);
    // TODO re-enable write callback if desired
    m_DRAMSim->RegisterCallbacks(m_readCB, NULL, &powerCallback);

    // TODO set correct CPU speed here
    // 0 assumes memory controller and CPU running at the same clock speed
    // right now we assume 100 MHz PEs
    m_DRAMSim->setCPUClockSpeed(PE_TICKS_PER_SECOND);

    // declare the runMemorySystem functions as a SystemC thread
    SC_THREAD(runMemorySystem);


    // statistics-related variables
    m_latencySamples = 0;
    m_latencySum = 0;
    m_powerSamples = 0;
    m_powerSum[0] = m_powerSum[1] = m_powerSum[2] = m_powerSum[3] = 0;

    m_epochSamplesOfType[memReqColInd] = 0.0;
    m_epochSamplesOfType[memReqMatrixData] = 0.0;
    m_epochSamplesOfType[memReqRowLen] = 0.0;
    m_epochSamplesOfType[memReqVectorData] = 0.0;

    m_epochLatencySamplesOfType[memReqColInd] = sc_time(0, SC_NS);
    m_epochLatencySamplesOfType[memReqMatrixData] = sc_time(0, SC_NS);
    m_epochLatencySamplesOfType[memReqRowLen] = sc_time(0, SC_NS);
    m_epochLatencySamplesOfType[memReqVectorData] = sc_time(0, SC_NS);

    m_numEpochSamples = 0.0;
}

MemorySystem::~MemorySystem()
{
    delete m_DRAMSim;
    delete m_readCB;
    delete m_writeCB;
}

void MemorySystem::setRequestFIFO(sc_fifo<MemoryOperation *> *fifo)
{
    m_requests = fifo;
}

void MemorySystem::setResponseFIFO(int originID, sc_fifo<MemoryOperation *> *fifo)
{
    m_responseFIFOs[originID] = fifo;
}

bool MemorySystem::canAddRequest()
{
    return (m_requests->num_free() > 0);
}

void MemorySystem::addRequest(MemoryOperation *op)
{
    m_requests->write(op);

    // uncomment this (at the risk of becoming overflooded with data) to see the requests made to the memory system
    // qDebug() << "memreq: " << op->address << " from " << op->origin << " at " << QString::fromStdString(sc_time_stamp().to_string());
}

void MemorySystem::readComplete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
    // hacky lazy way to return the transaction obj, but oh well...
    Transaction * t = (Transaction *) address;
    // retrieve the corresponding MemoryOperation
    if(!m_reqsInFlight.contains(t))
    {
        qDebug() << "error: Transaction has no matching MemoryOperation!";
        exit(EXIT_FAILURE);
        return;
    }
    MemoryOperation * op = m_reqsInFlight[t];

    // delete the map entry
    m_reqsInFlight.remove(t);

    op->isResponse = true;
    // TODO return real data to the requesters?

    // add response to the appropriate FIFO
    if(!m_responseFIFOs.contains(op->origin))
    {
        qDebug() << "error: Cannot find response FIFO for origin ID " << op->origin;
        exit(EXIT_FAILURE);
    }

    if(!m_responseFIFOs[op->origin]->nb_write(op))
    {
        qDebug() << "error: Response FIFO is full for origin ID " << op->origin;
        exit(EXIT_FAILURE);
    }

    // add latency info to MemoryOperation and statistics
    op->latency = (clock_cycle - t->timeAdded) * MEMC_CLOCK_CYCLE;
    m_latencySum += (clock_cycle - t->timeAdded);
    m_latencySamples++;

    addEpochSample(op);

    // DRAMsim will deallocate the Transaction
    // the originating PE will deallocate the MemoryOperation
}

void MemorySystem::writeComplete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
    // TODO DRAMsim doesn't seem to keep the write transaction objects intact,
    // so we'll have to handle these differently.
}

void MemorySystem::powerCallback(double background, double burst, double refresh, double actpre)
{
    //qDebug() << "power callback " << background << burst << refresh << actpre;

    m_powerSum[0] += background;
    m_powerSum[1] += burst;
    m_powerSum[2] += refresh;
    m_powerSum[3] += actpre;
    m_powerSamples++;
}

double MemorySystem::getAveragePowerBackground()
{
    return m_powerSum[0] / (double) m_powerSamples;
}

double MemorySystem::getAveragePowerBurst()
{
    return m_powerSum[1] / (double) m_powerSamples;
}

double MemorySystem::getAveragePowerRefresh()
{
    return m_powerSum[2] / (double) m_powerSamples;
}

double MemorySystem::getAveragePowerActPre()
{
    return m_powerSum[3] / (double) m_powerSamples;
}

void MemorySystem::addEpochSample(MemoryOperation *op)
{
    static sc_time lastEpoch = sc_time(0, SC_NS);
    m_numEpochSamples += 1.0;

    m_epochSamplesOfType[op->tag] += 1.0;
    m_epochLatencySamplesOfType[op->tag] += op->latency;

    double peakBW = GlobalConfig::getPeakBandwidthMBs()/1024;

    if(m_numEpochSamples == 10000)
    {
        // print statistics
        double epochLengthInSecs = (sc_time_stamp() - lastEpoch) / sc_time(1, SC_SEC);
        double avgBW = (m_numEpochSamples*DRAM_ACCESS_WIDTH_BYTES / epochLengthInSecs) / (1024.0 * 1024.0 * 1024.0);

        qDebug() << "*****************************************************************************************";
        qDebug() << "average aggregate DRAM bandwidth: " << avgBW << "GB/s (" << 100*avgBW/peakBW  << "% of peak, which is " << peakBW << " GB∕s)";
        qDebug() << "Percentage of requests in epoch:";
        qDebug() << "Matrix data requests: " << 100*m_epochSamplesOfType[memReqMatrixData] / m_numEpochSamples << "%";
        qDebug() << "Column index requests: " << 100* m_epochSamplesOfType[memReqColInd] / m_numEpochSamples << "%";
        qDebug() << "Row pointer requests: " << 100* m_epochSamplesOfType[memReqRowLen] / m_numEpochSamples << "%";
        qDebug() << "Vector data requests: " << 100* m_epochSamplesOfType[memReqVectorData] / m_numEpochSamples << "%";

        qDebug() << "\nAverage latency by request type:";
        qDebug() << "Matrix data requests: " << QString::number(((m_epochLatencySamplesOfType[memReqMatrixData] / m_epochSamplesOfType[memReqMatrixData])/sc_time(1,SC_NS))) << " ns";
        qDebug() << "Column index requests: " << QString::number(((m_epochLatencySamplesOfType[memReqColInd] / m_epochSamplesOfType[memReqColInd])/sc_time(1,SC_NS))) << " ns";
        qDebug() << "Row pointer requests: " << QString::number(((m_epochLatencySamplesOfType[memReqRowLen] / m_epochSamplesOfType[memReqRowLen])/sc_time(1,SC_NS))) << " ns";
        qDebug() << "Vector data requests: " << QString::number(((m_epochLatencySamplesOfType[memReqVectorData] / m_epochSamplesOfType[memReqVectorData])/sc_time(1,SC_NS))) << " ns";

        // reset counters
        m_epochSamplesOfType[memReqColInd] = 0.0;
        m_epochSamplesOfType[memReqMatrixData] = 0.0;
        m_epochSamplesOfType[memReqRowLen] = 0.0;
        m_epochSamplesOfType[memReqVectorData] = 0.0;

        m_epochLatencySamplesOfType[memReqColInd] = sc_time(0, SC_NS);
        m_epochLatencySamplesOfType[memReqMatrixData] = sc_time(0, SC_NS);
        m_epochLatencySamplesOfType[memReqRowLen] = sc_time(0, SC_NS);
        m_epochLatencySamplesOfType[memReqVectorData] = sc_time(0, SC_NS);

        m_numEpochSamples = 0.0;
        lastEpoch = sc_time_stamp();
    }
}

double MemorySystem::getAverageReqRespLatency()
{
    return (double) m_latencySum / (double) m_latencySamples;
}

void MemorySystem::runMemorySystem()
{
    while(1)
    {
        // this loop means that up to TRANS_QUEUE_DEPTH (e.g 32) requests per memory system cycle
        // will be entered into the DRAM transaction queue
        while(m_requests->num_available() > 0 && m_DRAMSim->willAcceptTransaction())
        {
            // pop the operation from the FIFO
            MemoryOperation * op = m_requests->read();
            // accesses must be at least as wide as the DRAM
            sc_assert(op->totalBytes >= DRAM_ACCESS_WIDTH_BYTES);
            Transaction * trans = new Transaction(op->isWrite ? DATA_WRITE : DATA_READ,
                                                  op->address, NULL, 8);

            // add transaction to DRAMsim's queue
            m_DRAMSim->addTransaction(trans);

            if(!op->isWrite)
            {
                // add a mapping entry between the DRAMsim transaction and our memory operation
                m_reqsInFlight.insert(trans, op);
            }
        }

        // advance SystemC time by 1 cc
        wait(PE_CLOCK_CYCLE);
        // advance DRAMSim simulation time by 1 cc
        m_DRAMSim->update();
    }
}

void MemorySystem::printFinalStats()
{
    double totalDataVolumeBytes = 8.0 * m_latencySamples;
    double totalSecsElapsed = sc_time_stamp() / sc_time(1, SC_SEC);
    double peakBW = GlobalConfig::getPeakBandwidthMBs()/1024;
    double avgBW = (totalDataVolumeBytes / totalSecsElapsed) / (1024.0 * 1024.0 * 1024.0);
    qDebug() << "average aggregate DRAM bandwidth: " << avgBW << "GB/s (" << 100*avgBW/peakBW  << "% of peak, which is " << peakBW << " GB∕s)";
    qDebug() << "total responses generated: " << m_latencySamples;

    // m_DRAMSim->printStats(true);
}
