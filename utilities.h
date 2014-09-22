#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QMap>
#include <systemc.h>

#define     VectorIndex         quint32
#define     VectorValue         double

#define     PE_CLOCK_CYCLE      (sc_time(10, SC_NS) / ((float)(GlobalConfig::getInstance().getPEFreq()) / 100.0   ) )
#define     MEMC_CLOCK_CYCLE    sc_time(3, SC_NS)
#define     PE_TICKS_PER_SECOND (uint64_t)(sc_time(1000, SC_MS)/PE_CLOCK_CYCLE)
#define     INI_CONFIG_DIR      "/home/maltanar/sandbox/spmvaccsim/ini"

QString getMatrixFilename(QString matrixName);
QMap<QString, QString> getDefaultDRAMSimConfig();

typedef struct {
    bool isResponse;
    bool isWrite;
    quint64 address;
    quint64 data;
    int origin;
    sc_time latency;
    int tag;
} MemoryOperation;

typedef enum {
    cacheModeNone,
    cacheModeDirectMapped,
    cacheMode2WayAssoc,
    cacheMode4WayAssoc,
    cacheModeStreamBuffer,
} CacheMode;

MemoryOperation * makeReadRequest(int origin, quint64 address, int tag);
MemoryOperation * makeReadResponse(int origin, quint64 address, quint64 data);
MemoryOperation * makeWriteRequest(int origin, quint64 address, quint64 data, int tag);

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

        static void setPEFreq(int f) {m_peFreq = f;};
        static int getPEFreq() {return m_peFreq;};

    private:
        GlobalConfig() {m_peFreq=100;};                   // Constructor? (the {} brackets) are needed here.
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        GlobalConfig(GlobalConfig const&);              // Don't Implement
        void operator=(GlobalConfig const&); // Don't implement

        static int m_peFreq;
};


#endif // UTILITIES_H
