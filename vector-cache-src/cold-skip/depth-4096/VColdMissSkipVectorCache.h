// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VColdMissSkipVectorCache_H_
#define _VColdMissSkipVectorCache_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"
class VColdMissSkipVectorCache__Syms;

//----------

SC_MODULE(VColdMissSkipVectorCache) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool>	clk;
    sc_in<bool>	reset;
    sc_out<bool>	io_readPort_readReq_ready;
    sc_in<bool>	io_readPort_readReq_valid;
    sc_in<bool>	io_readPort_readResp_ready;
    sc_out<bool>	io_readPort_readResp_valid;
    sc_out<bool>	io_writePort_writeReq_ready;
    sc_in<bool>	io_writePort_writeReq_valid;
    sc_in<bool>	io_memRead_memReq_ready;
    sc_out<bool>	io_memRead_memReq_valid;
    sc_out<bool>	io_memRead_memResp_ready;
    sc_in<bool>	io_memRead_memResp_valid;
    sc_in<bool>	io_memWrite_memWriteReq_ready;
    sc_out<bool>	io_memWrite_memWriteReq_valid;
    sc_in<bool>	io_flushCache;
    sc_out<bool>	io_cacheActive;
    sc_in<uint32_t>	io_readPort_readReq_bits;
    sc_out<uint32_t>	io_readPort_readRespInd;
    sc_in<uint32_t>	io_writePort_writeReq_bits;
    sc_out<uint32_t>	io_memRead_memReq_bits;
    sc_out<uint32_t>	io_memWrite_memWriteReq_bits;
    sc_out<uint32_t>	io_readCount;
    sc_out<uint32_t>	io_readMissCount;
    sc_out<uint32_t>	io_writeCount;
    sc_out<uint32_t>	io_writeMissCount;
    sc_out<uint32_t>	io_coldSkipCount;
    sc_out<vluint64_t>	io_readPort_readResp_bits;
    sc_in<vluint64_t>	io_writePort_writeData;
    sc_in<vluint64_t>	io_memRead_memResp_bits;
    sc_out<vluint64_t>	io_memWrite_memWriteData;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__controller__DOT__state,3,0);
    VL_SIG8(v__DOT__controller__DOT__T22,0,0);
    VL_SIG8(v__DOT__controller__DOT__T23,0,0);
    VL_SIG8(v__DOT__controller__DOT__T26,0,0);
    VL_SIG8(v__DOT__controller__DOT__T28,0,0);
    VL_SIG8(v__DOT__controller__DOT__T32,0,0);
    VL_SIG8(v__DOT__controller__DOT__T33,0,0);
    VL_SIG8(v__DOT__controller__DOT__T36,0,0);
    VL_SIG8(v__DOT__controller__DOT__T37,0,0);
    VL_SIG8(v__DOT__controller__DOT__T43,0,0);
    VL_SIG8(v__DOT__controller__DOT__T46,0,0);
    VL_SIG8(v__DOT__controller__DOT__T47,0,0);
    VL_SIG8(v__DOT__controller__DOT__T51,0,0);
    VL_SIG8(v__DOT__controller__DOT__T54,0,0);
    VL_SIG8(v__DOT__controller__DOT__T56,0,0);
    VL_SIG8(v__DOT__controller__DOT__T60,0,0);
    VL_SIG8(v__DOT__controller__DOT__T61,0,0);
    VL_SIG8(v__DOT__controller__DOT__T64,0,0);
    VL_SIG8(v__DOT__controller__DOT__T66,0,0);
    VL_SIG8(v__DOT__controller__DOT__T67,0,0);
    VL_SIG8(v__DOT__controller__DOT__T69,0,0);
    VL_SIG8(v__DOT__controller__DOT__T70,0,0);
    VL_SIG8(v__DOT__controller__DOT__T80,0,0);
    VL_SIG8(v__DOT__controller__DOT__T83,0,0);
    VL_SIG8(v__DOT__controller__DOT__T84,0,0);
    VL_SIG8(v__DOT__controller__DOT__T85,0,0);
    VL_SIG8(v__DOT__controller__DOT__T87,0,0);
    VL_SIG8(v__DOT__controller__DOT__T97,0,0);
    VL_SIG8(v__DOT__controller__DOT__T101,0,0);
    VL_SIG8(v__DOT__controller__DOT__T116,0,0);
    VL_SIG8(v__DOT__controller__DOT__enableReadRespReg,0,0);
    //char	__VpadToAlign155[1];
    VL_SIG16(v__DOT__controller__DOT__initCtr,11,0);
    VL_SIG16(v__DOT__controller__DOT__T76,11,0);
    VL_SIG16(v__DOT__controller__DOT__T90,11,0);
    VL_SIG16(v__DOT__tagMem__DOT__T0,12,0);
    VL_SIG16(v__DOT__tagMem__DOT__T2,12,0);
    //char	__VpadToAlign166[2];
    VL_SIG(v__DOT__controller__DOT__coldSkipCount,31,0);
    VL_SIG(v__DOT__controller__DOT__writeMissCount,31,0);
    VL_SIG(v__DOT__controller__DOT__writeCount,31,0);
    VL_SIG(v__DOT__controller__DOT__readMissCount,31,0);
    VL_SIG(v__DOT__controller__DOT__readCount,31,0);
    VL_SIG(v__DOT__controller__DOT__prevReadRequestReg,23,0);
    VL_SIG64(v__DOT__dataMem__DOT__R4,63,0);
    VL_SIG64(v__DOT__dataMem__DOT__T5,63,0);
    VL_SIG64(v__DOT__dataMem__DOT__cacheLines[4096],63,0);
    VL_SIG16(v__DOT__tagMem__DOT__tagStorage[4096],12,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__v__clk,0,0);
    VL_SIG8(__Vcellinp__v__io_flushCache,0,0);
    VL_SIG8(__Vcellinp__v__io_memWrite_memWriteReq_ready,0,0);
    VL_SIG8(__Vcellinp__v__io_memRead_memResp_valid,0,0);
    VL_SIG8(__Vcellinp__v__io_writePort_writeReq_valid,0,0);
    VL_SIG8(__Vcellinp__v__io_readPort_readResp_ready,0,0);
    VL_SIG8(__Vcellinp__v__io_readPort_readReq_valid,0,0);
    VL_SIG8(__Vcellinp__v__reset,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__v__clk,0,0);
    //char	__VpadToAlign41181[3];
    VL_SIG(__Vcellinp__v__io_writePort_writeReq_bits,23,0);
    VL_SIG(__Vcellinp__v__io_readPort_readReq_bits,24,0);
    VL_SIG64(__Vcellinp__v__io_memRead_memResp_bits,63,0);
    VL_SIG64(__Vcellinp__v__io_writePort_writeData,63,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    //char	__VpadToAlign41212[4];
    VColdMissSkipVectorCache__Syms*	__VlSymsp;		// Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VColdMissSkipVectorCache& operator= (const VColdMissSkipVectorCache&);	///< Copying not allowed
    VColdMissSkipVectorCache(const VColdMissSkipVectorCache&);	///< Copying not allowed
  public:
    SC_CTOR(VColdMissSkipVectorCache);
    virtual ~VColdMissSkipVectorCache();
    
    // USER METHODS
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VColdMissSkipVectorCache__Syms* symsp, bool first);
  private:
    static IData	_change_request(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__1(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__12(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__15(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__4(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__6(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__9(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_eval(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_eval_initial(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_eval_settle(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__10(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__13(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__16(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__3(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__7(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__11(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__14(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__17(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__5(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__8(VColdMissSkipVectorCache__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
