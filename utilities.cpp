#include "utilities.h"

// allocate space for global static variables from singleton
int GlobalConfig::m_peFreq;
QString GlobalConfig::m_dramChipType;
QMap<QString, DRAMChipInfo> GlobalConfig::m_chipInfo;
int GlobalConfig::m_memorySizeMB;
QMap<QString, QString> GlobalConfig::m_memSysConfig;


QString getMatrixFilename(QString matrixName)
{
    // only retrieving dense vector access pattern for now
    return "/home/maltanar/spm-data/colinds/" + matrixName.replace("/", "-");
}

MemoryOperation * makeReadRequest(int origin, quint64 address, MemRequestTag tag)
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
    defaultConfig["DEBUG_ADDR_MAP"]="false";
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

void GlobalConfig::setMemorySizeMB(int memSize)
{
    m_memorySizeMB = memSize;
}

int GlobalConfig::getMemorySizeMB()
{
    return m_memorySizeMB;
}

void GlobalConfig::setDRAMConfig(QString dramChipType)
{
    m_dramChipType = dramChipType;
}

QString GlobalConfig::getMemConfigFile()
{
    return m_chipInfo[m_dramChipType].configFileName + ".ini";
}

int GlobalConfig::getMemIOClkFreqMHz()
{
    return m_chipInfo[m_dramChipType].ioClkMHz;
}

int GlobalConfig::getDevicesPerRank()
{
    return DRAM_ACCESS_WIDTH_BYTES*8 / m_chipInfo[m_dramChipType].interfaceWidthBits;
}

int GlobalConfig::getTotalRanks()
{
    // TODO number of channels is important here
    int capacityPerRankMB = getDevicesPerRank() * m_chipInfo[m_dramChipType].capacityMB;
    int ranksForWantedCapacity = m_memorySizeMB / capacityPerRankMB;
    // always need at least 1 rank
    if(ranksForWantedCapacity == 0)
        ranksForWantedCapacity = 1;

    return ranksForWantedCapacity;
}

float GlobalConfig::getPeakBandwidthMBs()
{
    // TODO number of channels important here
    return 2.0 * (float)m_chipInfo[m_dramChipType].ioClkMHz * DRAM_ACCESS_WIDTH_BYTES;
}

void GlobalConfig::setMemSysConfig(QMap<QString, QString> cfg)
{
    m_memSysConfig = cfg;
}

QMap<QString, QString> GlobalConfig::getMemSysConfig()
{
    return m_memSysConfig;
}

GlobalConfig::GlobalConfig()
{

    // defaults:
    // DDR3-1600 which gives 12.8 GB/s peak bandwidth
    // 4096 MB which gives 2 ranks
    // 100 MHz PE
    // note: the real defaults come from the command line param defaults
    m_peFreq=100;
    m_dramChipType = "DDR3-1600-32M-8x4";
    m_memorySizeMB = 4096;

    m_chipInfo["DDR2-667-16M-8x8"].configFileName = "DDR2_micron_16M_8b_x8_sg3E";
    m_chipInfo["DDR2-667-32M-4x4"].configFileName = "DDR2_micron_32M_4B_x4_sg3E";
    m_chipInfo["DDR2-800-32M-8x4"].configFileName = "DDR2_micron_32M_8B_x4_sg25E";
    m_chipInfo["DDR3-1333-8M-8x16"].configFileName = "DDR3_micron_8M_8B_x16_sg15";
    m_chipInfo["DDR3-1333-16M-8x8"].configFileName = "DDR3_micron_16M_8B_x8_sg15";
    m_chipInfo["DDR3-1333-32M-8x4"].configFileName = "DDR3_micron_32M_8B_x4_sg15";
    m_chipInfo["DDR3-1600-32M-8x4"].configFileName = "DDR3_micron_32M_8B_x4_sg125";
    m_chipInfo["DDR3-1333-32M-8x8"].configFileName = "DDR3_micron_32M_8B_x8_sg15";
    m_chipInfo["DDR3-800-32M-8x8"].configFileName = "DDR3_micron_32M_8B_x8_sg25E";
    m_chipInfo["DDR3-1333-64M-8x4"].configFileName = "DDR3_micron_64M_8B_x4_sg15";

    m_chipInfo["DDR2-667-16M-8x8"].ioClkMHz = 333;
    m_chipInfo["DDR2-667-32M-4x4"].ioClkMHz = 333;
    m_chipInfo["DDR2-800-32M-8x4"].ioClkMHz = 400;
    m_chipInfo["DDR3-1333-8M-8x16"].ioClkMHz = 666;
    m_chipInfo["DDR3-1333-16M-8x8"].ioClkMHz = 666;
    m_chipInfo["DDR3-1333-32M-8x4"].ioClkMHz = 666;
    m_chipInfo["DDR3-1600-32M-8x4"].ioClkMHz = 800;
    m_chipInfo["DDR3-1333-32M-8x8"].ioClkMHz = 666;
    m_chipInfo["DDR3-800-32M-8x8"].ioClkMHz = 400;
    m_chipInfo["DDR3-1333-64M-8x4"].ioClkMHz = 666;

    m_chipInfo["DDR2-667-16M-8x8"].numBanks = 8;
    m_chipInfo["DDR2-667-32M-4x4"].numBanks = 4;
    m_chipInfo["DDR2-800-32M-8x4"].numBanks = 8;
    m_chipInfo["DDR3-1333-8M-8x16"].numBanks = 8;
    m_chipInfo["DDR3-1333-16M-8x8"].numBanks = 8;
    m_chipInfo["DDR3-1333-32M-8x4"].numBanks = 8;
    m_chipInfo["DDR3-1600-32M-8x4"].numBanks = 8;
    m_chipInfo["DDR3-1333-32M-8x8"].numBanks = 8;
    m_chipInfo["DDR3-800-32M-8x8"].numBanks = 8;
    m_chipInfo["DDR3-1333-64M-8x4"].numBanks = 8;

    m_chipInfo["DDR2-667-16M-8x8"].interfaceWidthBits = 8;
    m_chipInfo["DDR2-667-32M-4x4"].interfaceWidthBits = 4;
    m_chipInfo["DDR2-800-32M-8x4"].interfaceWidthBits = 4;
    m_chipInfo["DDR3-1333-8M-8x16"].interfaceWidthBits = 16;
    m_chipInfo["DDR3-1333-16M-8x8"].interfaceWidthBits = 8;
    m_chipInfo["DDR3-1333-32M-8x4"].interfaceWidthBits = 4;
    m_chipInfo["DDR3-1600-32M-8x4"].interfaceWidthBits = 4;
    m_chipInfo["DDR3-1333-32M-8x8"].interfaceWidthBits = 8;
    m_chipInfo["DDR3-800-32M-8x8"].interfaceWidthBits = 8;
    m_chipInfo["DDR3-1333-64M-8x4"].interfaceWidthBits = 4;

    m_chipInfo["DDR2-667-16M-8x8"].capacityMB = 128;
    m_chipInfo["DDR2-667-32M-4x4"].capacityMB = 64;
    m_chipInfo["DDR2-800-32M-8x4"].capacityMB = 128;
    m_chipInfo["DDR3-1333-8M-8x16"].capacityMB = 128;
    m_chipInfo["DDR3-1333-16M-8x8"].capacityMB = 128;
    m_chipInfo["DDR3-1333-32M-8x4"].capacityMB = 128;
    m_chipInfo["DDR3-1600-32M-8x4"].capacityMB = 128;
    m_chipInfo["DDR3-1333-32M-8x8"].capacityMB = 256;
    m_chipInfo["DDR3-800-32M-8x8"].capacityMB = 256;
    m_chipInfo["DDR3-1333-64M-8x4"].capacityMB = 256;

}
