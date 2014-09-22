#include <QCommandLineParser>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <systemc.h>

#include "spmvocmsimulation.h"

// needed by DRAMSim
int SHOW_SIM_OUTPUT=0;

int sc_main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("spmv-ocm-sim");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Simulation tool for FPGA SpMV OCM");;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption peCountOption("n", "Number of processing elements", "pecount", "1");
    QCommandLineOption spmOption("m", "Sparse matrix to process", "spm");
    QCommandLineOption maxOutstandingReqOption("o", "Maximum outstanding requests from each PE", "maxoutstanding", "1");
    QCommandLineOption verboseDRAMSimOption("V", "Verbose DRAMsim");
    QCommandLineOption cacheModeOption("c", "Cache mode (0 -> none, 1 -> DM, 2 -> 2 way, 3 -> 4 way, 4 -> stream buffer", "cachemode", "0");
    QCommandLineOption cacheSizeOption("s", "Cache size per PE, in number of elements", "cachesize", "128");
    QCommandLineOption dramSimOverrideOption("x", "DRAMSim option override, e.g -x TOTAL_ROW_ACCESSES=1", "override", "");
    QCommandLineOption databaseNameOption("d", "Name of sqlite database to dump results into", "db", "results.db");
    QCommandLineOption peClockFreqOption("f", "PE clock frequency (MHz)", "pefreq", "100");

    parser.addOption(peCountOption);
    parser.addOption(spmOption);
    //parser.addOption(useInterleavedOption);
    parser.addOption(maxOutstandingReqOption);
    parser.addOption(cacheModeOption);
    parser.addOption(cacheSizeOption);
    parser.addOption(verboseDRAMSimOption);
    parser.addOption(dramSimOverrideOption);
    parser.addOption(databaseNameOption);
    parser.addOption(peClockFreqOption);

    parser.process(app);

    int peCount = parser.value(peCountOption).toInt();
    int maxOutstandingReqs = parser.value(maxOutstandingReqOption).toInt();
    CacheMode cacheMode = (CacheMode) parser.value(cacheModeOption).toInt();
    int cachePerPE = parser.value(cacheSizeOption).toInt();
    QString spm = parser.value(spmOption);
    QString databaseName = parser.value(databaseNameOption);


    int peFreq = parser.value(peClockFreqOption).toInt();
    GlobalConfig::getInstance().setPEFreq(peFreq);

    QMap<QString, QString> memsysOverrides;
    QString overrideString;

    foreach(overrideString, parser.values(dramSimOverrideOption))
    {
        QStringList fields = overrideString.split("=");
        memsysOverrides[fields[0]] = fields[1];
    }


    if(parser.isSet(verboseDRAMSimOption))
        SHOW_SIM_OUTPUT=1;

    if(spm.isEmpty() || !QFile::exists(getMatrixFilename(spm)))
    {
        qDebug() << "SpM " << getMatrixFilename(spm ) << "not found";
        parser.showHelp(0);
    }

    if(maxOutstandingReqs < 1)
    {
        qDebug() << "max outstanding requests must be minimum 1";
        maxOutstandingReqs = 1;
    }

    if(peCount < 1)
    {
        qDebug() << "PE count must be minimum 1";
        peCount = 1;
    }


    SpMVOCMSimulation sim(spm, peCount, maxOutstandingReqs, cacheMode, cachePerPE, memsysOverrides);

    sim.run();

    sim.saveStatisticsToDB(databaseName);

    return 0;
}
