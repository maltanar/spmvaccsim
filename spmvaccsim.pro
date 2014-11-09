#-------------------------------------------------
#
# Project created by QtCreator 2014-08-21T16:11:04
#
#-------------------------------------------------

QT       += core sql

TARGET = spmvaccsim
TEMPLATE = app

SYSTEMC_ROOT = /home/maltanar/systemc
SYSTEMC_ARCH = linux64
VERILATOR_ROOT = /usr/share/verilator

# Assign default value to CACHE_DEPTH
isEmpty(CACHE_DEPTH) {
    CACHE_DEPTH = 8192
}

CMSK_VECTOR_CACHE_DIR = vector-cache-src/cold-skip/depth-$$CACHE_DEPTH
BASE_VECTOR_CACHE_DIR = vector-cache-src/baseline/depth-$$CACHE_DEPTH
DEFINES += NO_STORAGE VL_PRINTF=printf VM_TRACE=0 VM_COVERAGE=0 CACHE_DEPTH=$$CACHE_DEPTH

QMAKE_INCDIR += $$SYSTEMC_ROOT/include $$VERILATOR_ROOT/include $$VERILATOR_ROOT/include/vltstd $$CMSK_VECTOR_CACHE_DIR $$BASE_VECTOR_CACHE_DIR
QMAKE_LIBDIR += $$SYSTEMC_ROOT/lib-$$SYSTEMC_ARCH


SOURCES += main.cpp\
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
    spmvocmsimulation.cpp \
    memoryport.cpp \
    burstmemoryport.cpp \
    vectorcachewrapper.cpp \
    vector-cache-src/verilated.cpp \
    $$BASE_VECTOR_CACHE_DIR/VSimpleDMVectorCache.cpp \
    $$BASE_VECTOR_CACHE_DIR/VSimpleDMVectorCache__Syms.cpp \
    vectorcachetester.cpp \
    $$CMSK_VECTOR_CACHE_DIR/VColdMissSkipVectorCache.cpp \
    $$CMSK_VECTOR_CACHE_DIR/VColdMissSkipVectorCache__Syms.cpp \
    coldmissskipcachewrapper.cpp

HEADERS  += spmvoperation.h \
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
    spmvocmsimulation.h \
    memoryport.h \
    burstmemoryport.h \
    fifoinbreakout.h \
    fifooutbreakout.h \
    vectorcachewrapper.h \
    $$BASE_VECTOR_CACHE_DIR/VSimpleDMVectorCache.h \
    $$BASE_VECTOR_CACHE_DIR/VSimpleDMVectorCache__Syms.h \
    vectorcachetester.h \
    $$CMSK_VECTOR_CACHE_DIR/VColdMissSkipVectorCache.h \
    $$CMSK_VECTOR_CACHE_DIR/VColdMissSkipVectorCache__Syms.h \
    coldmissskipcachewrapper.h

LIBS += -lsystemc -lpthread
