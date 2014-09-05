#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QMap>
#include <systemc.h>

#define     VectorIndex         quint32
#define     PE_CLOCK_CYCLE      sc_time(10, SC_NS)
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
} MemoryOperation;

typedef enum {
    cacheModeNone,
    cacheModeDirectMapped,
    cacheMode2WayAssoc,
    cacheMode4WayAssoc,
    cacheModeStreamBuffer,
} CacheMode;

MemoryOperation * makeReadRequest(int origin, quint64 address);
MemoryOperation * makeReadResponse(int origin, quint64 address, quint64 data);
MemoryOperation * makeWriteRequest(int origin, quint64 address, quint64 data);

void freeRequest(MemoryOperation *req);

#endif // UTILITIES_H
