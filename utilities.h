#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QMap>
#include <systemc.h>
#include "verilated.h"

#define     VectorIndex         unsigned int
#define     VectorValue         unsigned long

#define     PE_CLOCK_CYCLE      (sc_time(10, SC_NS) / ((float)(GlobalConfig::getInstance().getPEFreqMHz()) / 100.0   ) )
#define     MEMC_CLOCK_CYCLE    (sc_time(3, SC_NS) / ((float)(GlobalConfig::getInstance().getMemIOClkFreqMHz()) / 333.0   ) )
#define     PE_TICKS_PER_SECOND (uint64_t)(sc_time(1000, SC_MS)/PE_CLOCK_CYCLE)
#define     INI_CONFIG_DIR      "/home/maltanar/sandbox/spmvaccsim/ini"

// TODO make customizable
#define DRAM_ACCESS_WIDTH_BYTES     8

QString getMatrixFilename(QString matrixName);
QMap<QString, QString> getDefaultDRAMSimConfig();

typedef enum {
    memReqOther,
    memReqRowLen,
    memReqMatrixData,
    memReqColInd,
    memReqVectorData
} MemRequestTag;

typedef struct {
    bool isResponse;
    bool isWrite;
    quint64 address;
    quint64 data;
    int origin;
    int desiredBytes;
    sc_time latency;
    MemRequestTag tag;
} MemoryOperation;

typedef enum {
    cacheModeNone,
    cacheModeDirectMapped,
    cacheMode2WayAssoc,
    cacheMode4WayAssoc,
    cacheModeStreamBuffer,
} CacheMode;

typedef struct {
    QString configFileName;
    int ioClkMHz;
    int capacityMB;
    int interfaceWidthBits;
    int numBanks;
    int burstLength;
} DRAMChipInfo;

MemoryOperation * makeReadRequest(int origin, quint64 address, MemRequestTag tag, int desiredBytes);

void freeRequest(MemoryOperation *req);

class GlobalConfig
{
    public:
        static GlobalConfig& getInstance()
        {
            static GlobalConfig    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }

        static void setPEFreqMHz(int f);
        static int getPEFreqMHz();

        static void setMemorySizeMB(int memSize);
        static int getMemorySizeMB();

        static void setDRAMConfig(QString dramChipType);
        static DRAMChipInfo getDRAMConfig();

        static QString getMemConfigFile();
        static int getMemIOClkFreqMHz();

        static int getDevicesPerRank();
        static int getTotalRanks();

        static float getPeakBandwidthMBs();

        static void setMemSysConfig(QMap<QString, QString> cfg);
        QMap<QString, QString> getMemSysConfig();


    private:
        GlobalConfig();                   // Constructor? (the {} brackets) are needed here.
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        GlobalConfig(GlobalConfig const&);              // Don't Implement
        void operator=(GlobalConfig const&); // Don't implement

        static int m_peFreq;
        static int m_memorySizeMB;

        static QString m_dramChipType;
        static QMap<QString, DRAMChipInfo> m_chipInfo;
        static QMap<QString, QString> m_memSysConfig;
};


#endif // UTILITIES_H
