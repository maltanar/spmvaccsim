#include "utilities.h"

// allocate space for global static variables from singleton
int GlobalConfig::m_peFreq;
QString GlobalConfig::m_dramChipType;
QMap<QString, QString> GlobalConfig::m_configFiles;
QMap<QString, int> GlobalConfig::m_memIOClkMHz;


QString getMatrixFilename(QString matrixName)
{
    // only retrieving dense vector access pattern for now
    return "/home/maltanar/spm-data/colinds/" + matrixName.replace("/", "-");
}

MemoryOperation * makeReadRequest(int origin, quint64 address, int tag)
{
    MemoryOperation * newOp = new MemoryOperation;
    newOp->address = address;
    newOp->data = 0;
    newOp->isResponse = false;
    newOp->isWrite = false;
    newOp->origin = origin;
    newOp->latency = sc_time(0, SC_NS);
    newOp->tag = tag;

    return newOp;
}

MemoryOperation * makeReadResponse(int origin, quint64 address, quint64 data)
{
    MemoryOperation * newOp = new MemoryOperation;
    newOp->address = address;
    newOp->data = data;
    newOp->isResponse = true;
    newOp->isWrite = false;
    newOp->origin = origin;
    newOp->latency = sc_time(0, SC_NS);
    newOp->tag = 0; // TODO -- should be taken from request

    return newOp;
}

MemoryOperation * makeWriteRequest(int origin, quint64 address, quint64 data, int tag)
{
    MemoryOperation * newOp = new MemoryOperation;
    newOp->address = address;
    newOp->data = data;
    newOp->isResponse = false;
    newOp->isWrite = true;
    newOp->origin = origin;
    newOp->latency = sc_time(0, SC_NS);
    newOp->tag = tag;

    return newOp;
}

void freeRequest(MemoryOperation *req)
{
    delete req;
}


QMap<QString, QString> getDefaultDRAMSimConfig()
{
    QMap<QString, QString> defaultConfig;

    // number of *logically independent* channels (i.e. each with a separate memory controller), should be a power of 2
    defaultConfig["NUM_CHANS"]="1";
    // Always 64 for DDRx, if you want multiple *ganged* channels, set this to N*64"
    defaultConfig["JEDEC_DATA_BUS_BITS"]="64";
    // transaction queue, i.e., CPU-level commands such as:  READ 0xbeef"
    defaultConfig["TRANS_QUEUE_DEPTH"]="32";
    // command queue, i.e., DRAM-level commands such as: CAS 544, RAS 4"
    defaultConfig["CMD_QUEUE_DEPTH"]="32";
    // length of an epoch in cycles (granularity of simulation)";
    defaultConfig["EPOCH_LENGTH"]="100000";
    // close_page or open_page
    defaultConfig["ROW_BUFFER_POLICY"]="open_page";
    // valid schemes 1-7, for multiple independent channels, use scheme7 since it has the most parallelism
    defaultConfig["ADDRESS_MAPPING_SCHEME"]="scheme7";
    // bank_then_rank_round_robin or rank_then_bank_round_robin
    defaultConfig["SCHEDULING_POLICY"]="rank_then_bank_round_robin";
    //per_rank or per_rank_per_bank
    defaultConfig["QUEUING_STRUCTURE"]="per_rank";

    //for true/false, please use all lowercase"
    defaultConfig["DEBUG_TRANS_Q"]="false";
    defaultConfig["DEBUG_CMD_Q"]="false";
    defaultConfig["DEBUG_ADDR_MAP"]="true";
    defaultConfig["DEBUG_BUS"]="false";
    defaultConfig["DEBUG_BANKSTATE"]="false";
    defaultConfig["DEBUG_BANKS"]="false";
    defaultConfig["DEBUG_POWER"]="false";
    defaultConfig["VIS_FILE_OUTPUT"]="false";

    // go into low power mode when idle?"
    defaultConfig["USE_LOW_POWER"]="true";
    // should be false for normal operation"
    defaultConfig["VERIFICATION_OUTPUT"]="false";
    // maximum number of open page requests to send to the same row before forcing a row close (to prevent starvation)
    defaultConfig["TOTAL_ROW_ACCESSES"]="4";

    return defaultConfig;
}


void GlobalConfig::setPEFreqMHz(int f) {m_peFreq = f;}

int GlobalConfig::getPEFreqMHz() {return m_peFreq;}

void GlobalConfig::setDRAMConfig(QString dramChipType)
{
    m_dramChipType = dramChipType;
}

QString GlobalConfig::getMemConfigFile()
{
    return m_configFiles[m_dramChipType] + ".ini";
}

int GlobalConfig::getMemIOClkFreqMHz()
{
    return m_memIOClkMHz[m_dramChipType];
}

GlobalConfig::GlobalConfig()
{
    m_peFreq=100;
    m_dramChipType="DDR2-667-16M-8x8";

    m_configFiles["DDR2-667-16M-8x8"] = "DDR2_micron_16M_8b_x8_sg3E";
    m_configFiles["DDR2-667-32M-4x4"] = "DDR2_micron_32M_4B_x4_sg3E";
    m_configFiles["DDR2-800-32M-8x4"] = "DDR2_micron_32M_8B_x4_sg25E";
    m_configFiles["DDR3-1333-8M-8x16"] = "DDR3_micron_8M_8B_x16_sg15";
    m_configFiles["DDR3-1333-16M-8x8"] = "DDR3_micron_16M_8B_x8_sg15";
    m_configFiles["DDR3-1333-32M-8x4"] = "DDR3_micron_32M_8B_x4_sg15";
    m_configFiles["DDR3-1600-32M-8x4"] = "DDR3_micron_32M_8B_x4_sg125";
    m_configFiles["DDR3-1333-32M-8x8"] = "DDR3_micron_32M_8B_x8_sg15";
    m_configFiles["DDR3-800-32M-8x8"] = "DDR3_micron_32M_8B_x8_sg25E";
    m_configFiles["DDR3-1333-64M-8x4"] = "DDR3_micron_64M_8B_x4_sg15";

    m_memIOClkMHz["DDR2-667-16M-8x8"] = 333;
    m_memIOClkMHz["DDR2-667-32M-4x4"] = 333;
    m_memIOClkMHz["DDR2-800-32M-8x4"] = 400;
    m_memIOClkMHz["DDR3-1333-8M-8x16"] = 666;
    m_memIOClkMHz["DDR3-1333-16M-8x8"] = 666;
    m_memIOClkMHz["DDR3-1333-32M-8x4"] = 666;
    m_memIOClkMHz["DDR3-1600-32M-8x4"] = 800;
    m_memIOClkMHz["DDR3-1333-32M-8x8"] = 666;
    m_memIOClkMHz["DDR3-800-32M-8x8"] = 400;
    m_memIOClkMHz["DDR3-1333-64M-8x4"] = 666;
}
