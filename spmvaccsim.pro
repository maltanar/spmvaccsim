#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T16:11:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spmvaccsim
TEMPLATE = app

DEFINES += NO_STORAGE

SOURCES += main.cpp\
        mainwindow.cpp \
    spmvoperation.cpp \
    utilities.cpp \
    processingelement.cpp \
    memorysystem.cpp \
    DRAMSim2/AddressMapping.cpp \
    DRAMSim2/Bank.cpp \
    DRAMSim2/BankState.cpp \
    DRAMSim2/BusPacket.cpp \
    DRAMSim2/ClockDomain.cpp \
    DRAMSim2/CommandQueue.cpp \
    DRAMSim2/IniReader.cpp \
    DRAMSim2/MemoryController.cpp \
    DRAMSim2/MemorySystem.cpp \
    DRAMSim2/MultiChannelMemorySystem.cpp \
    DRAMSim2/Rank.cpp \
    DRAMSim2/SimulatorObject.cpp \
    DRAMSim2/Transaction.cpp \
    spmvocmsimulation.cpp

HEADERS  += mainwindow.h \
    spmvoperation.h \
    utilities.h \
    processingelement.h \
    memorysystem.h \
    DRAMSim2/AddressMapping.h \
    DRAMSim2/Bank.h \
    DRAMSim2/BankState.h \
    DRAMSim2/BusPacket.h \
    DRAMSim2/Callback.h \
    DRAMSim2/ClockDomain.h \
    DRAMSim2/CommandQueue.h \
    DRAMSim2/CSVWriter.h \
    DRAMSim2/DRAMSim.h \
    DRAMSim2/IniReader.h \
    DRAMSim2/MemoryController.h \
    DRAMSim2/MemorySystem.h \
    DRAMSim2/MultiChannelMemorySystem.h \
    DRAMSim2/PrintMacros.h \
    DRAMSim2/Rank.h \
    DRAMSim2/SimulatorObject.h \
    DRAMSim2/SystemConfiguration.h \
    DRAMSim2/Transaction.h \
    spmvocmsimulation.h

FORMS    += mainwindow.ui

SYSTEMC_ROOT = /home/maltanar/systemc
SYSTEMC_ARCH = linux64

QMAKE_INCDIR += $$SYSTEMC_ROOT/include
QMAKE_LIBDIR += $$SYSTEMC_ROOT/lib-$$SYSTEMC_ARCH

LIBS += -lsystemc -lpthread
