#include "utilities.h"




QString getMatrixFilename(QString matrixName)
{
    // only retrieving dense vector access pattern for now
    return "/home/maltanar/spm-data/colinds/" + matrixName.replace("/", "-");
}

MemoryOperation * makeReadRequest(int origin, quint64 address)
{
    MemoryOperation * newOp = new MemoryOperation;
    newOp->address = address;
    newOp->data = 0;
    newOp->isResponse = false;
    newOp->isWrite = false;
    newOp->origin = origin;
    newOp->latency = sc_time(0, SC_NS);

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

    return newOp;
}

MemoryOperation * makeWriteRequest(int origin, quint64 address, quint64 data)
{
    MemoryOperation * newOp = new MemoryOperation;
    newOp->address = address;
    newOp->data = data;
    newOp->isResponse = false;
    newOp->isWrite = true;
    newOp->origin = origin;
    newOp->latency = sc_time(0, SC_NS);

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
