// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSimpleDMVectorCache_H_
#define _VSimpleDMVectorCache_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"
class VSimpleDMVectorCache__Syms;

//----------

SC_MODULE(VSimpleDMVectorCache) {
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
    sc_out<vluint64_t>	io_readPort_readResp_bits;
    sc_in<vluint64_t>	io_writePort_writeData;
    sc_in<vluint64_t>	io_memRead_memResp_bits;
    sc_out<vluint64_t>	io_memWrite_memWriteData;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__controller__DOT__state,2,0);
    VL_SIG8(v__DOT__controller__DOT__T20,0,0);
    VL_SIG8(v__DOT__controller__DOT__T21,0,0);
    VL_SIG8(v__DOT__controller__DOT__T24,0,0);
    VL_SIG8(v__DOT__controller__DOT__T26,0,0);
    VL_SIG8(v__DOT__controller__DOT__T30,0,0);
    VL_SIG8(v__DOT__controller__DOT__T31,0,0);
    VL_SIG8(v__DOT__controller__DOT__T34,0,0);
    VL_SIG8(v__DOT__controller__DOT__T35,0,0);
    VL_SIG8(v__DOT__controller__DOT__T41,0,0);
    VL_SIG8(v__DOT__controller__DOT__T44,0,0);
    VL_SIG8(v__DOT__controller__DOT__T45,0,0);
    VL_SIG8(v__DOT__controller__DOT__T49,0,0);
    VL_SIG8(v__DOT__controller__DOT__T52,0,0);
    VL_SIG8(v__DOT__controller__DOT__T53,0,0);
    VL_SIG8(v__DOT__controller__DOT__T56,0,0);
    VL_SIG8(v__DOT__controller__DOT__T57,0,0);
    VL_SIG8(v__DOT__controller__DOT__T61,0,0);
    VL_SIG8(v__DOT__controller__DOT__T62,0,0);
    VL_SIG8(v__DOT__controller__DOT__T63,0,0);
    VL_SIG8(v__DOT__controller__DOT__T73,0,0);
    VL_SIG8(v__DOT__controller__DOT__T76,0,0);
    VL_SIG8(v__DOT__controller__DOT__T77,0,0);
    VL_SIG8(v__DOT__controller__DOT__T78,0,0);
    VL_SIG8(v__DOT__controller__DOT__T80,0,0);
    VL_SIG8(v__DOT__controller__DOT__T86,0,0);
    VL_SIG8(v__DOT__controller__DOT__T90,0,0);
    VL_SIG8(v__DOT__controller__DOT__T105,0,0);
    VL_SIG8(v__DOT__controller__DOT__enableReadRespReg,0,0);
    //char	__VpadToAlign149[1];
    VL_SIG16(v__DOT__controller__DOT__initCtr,13,0);
    VL_SIG16(v__DOT__controller__DOT__T69,13,0);
    VL_SIG16(v__DOT__controller__DOT__T81,13,0);
    VL_SIG16(v__DOT__tagMem__DOT__T0,10,0);
    VL_SIG16(v__DOT__tagMem__DOT__T2,10,0);
    VL_SIG(v__DOT__controller__DOT__writeMissCount,31,0);
    VL_SIG(v__DOT__controller__DOT__writeCount,31,0);
    VL_SIG(v__DOT__controller__DOT__readMissCount,31,0);
    VL_SIG(v__DOT__controller__DOT__readCount,31,0);
    VL_SIG(v__DOT__controller__DOT__prevReadRequestReg,23,0);
    //char	__VpadToAlign180[4];
    VL_SIG64(v__DOT__dataMem__DOT__R4,63,0);
    VL_SIG64(v__DOT__dataMem__DOT__T5,63,0);
    VL_SIG64(v__DOT__dataMem__DOT__cacheLines[16384],63,0);
    VL_SIG16(v__DOT__tagMem__DOT__tagStorage[16384],10,0);
    
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
    //char	__VpadToAlign164053[3];
    VL_SIG(__Vcellinp__v__io_writePort_writeReq_bits,23,0);
    VL_SIG(__Vcellinp__v__io_readPort_readReq_bits,23,0);
    VL_SIG64(__Vcellinp__v__io_memRead_memResp_bits,63,0);
    VL_SIG64(__Vcellinp__v__io_writePort_writeData,63,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    //char	__VpadToAlign164084[4];
    VSimpleDMVectorCache__Syms*	__VlSymsp;		// Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VSimpleDMVectorCache& operator= (const VSimpleDMVectorCache&);	///< Copying not allowed
    VSimpleDMVectorCache(const VSimpleDMVectorCache&);	///< Copying not allowed
  public:
    SC_CTOR(VSimpleDMVectorCache);
    virtual ~VSimpleDMVectorCache();
    
    // USER METHODS
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VSimpleDMVectorCache__Syms* symsp, bool first);
  private:
    static IData	_change_request(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__1(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__12(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__15(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__4(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__6(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_combo__TOP__9(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_eval(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_eval_initial(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_eval_settle(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__10(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__13(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__3(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__7(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__11(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__14(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__16(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__5(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
    static void	_settle__TOP__8(VSimpleDMVectorCache__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
