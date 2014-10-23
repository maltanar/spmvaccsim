#include <QCommandLineParser>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <systemc.h>

#include "spmvocmsimulation.h"

// needed by DRAMSim
int SHOW_SIM_OUTPUT=0;

#include "vectorcachetester.h"

int sc_main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("spmv-ocm-sim");
    QCoreApplication::setApplicationVersion("1.0");

    // tone down the SystemC verbosity
    sc_report_handler::set_actions (SC_WARNING, SC_DO_NOTHING);
    sc_report_handler::set_actions (SC_INFO, SC_DO_NOTHING);

    QCommandLineParser parser;
    parser.setApplicationDescription("Simulation tool for FPGA SpMV Vector Cache");;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption spmOption("m", "Sparse matrix to process", "spm");
    QCommandLineOption peClockFreqOption("f", "PE clock frequency (MHz)", "pefreq", "100");


    parser.addOption(spmOption);
    parser.addOption(peClockFreqOption);

    parser.process(app);

    QString spm = parser.value(spmOption);
    int peFreq = parser.value(peClockFreqOption).toInt();
    GlobalConfig::getInstance().setPEFreqMHz(peFreq);


    if(spm.isEmpty() || !QFile::exists(getMatrixFilename(spm)))
    {
        qDebug() << "SpM " << getMatrixFilename(spm ) << "not found";
        parser.showHelp(0);
    }

    // TODO restrict operation to symmetric matrices --
    // SpMVOperation was built for row-major stuff, but col-major
    // of symmetric is equal to row major anyway
    SpMVOperation * op = new SpMVOperation(spm);
    if(op->rowCount() != op->colCount())
    {
        cout << "Cannot work with non-symmetric SpMs for the moment, sorry!" << endl;
        delete op;
        return 1;
    }

    // assign work
    QList<VectorIndex> rowInds, colLens;
    VectorIndex startCol;
    quint64 startNZ;
    op->assignWorkToWorker(0, 1, startCol, startNZ, rowInds, colLens);
    delete op;

    VectorCacheTester tester("main");

    tester.setAccessList(rowInds);

    sc_start();

    return 0;
}
