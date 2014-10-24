// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimpleDMVectorCache.h for the primary calling header

#include "VSimpleDMVectorCache.h" // For This
#include "VSimpleDMVectorCache__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(VSimpleDMVectorCache)
#if (SYSTEMC_VERSION>20011000)
    : clk("clk"), reset("reset"), io_readReq_ready("io_readReq_ready"), 
      io_readReq_valid("io_readReq_valid"), io_readResp_ready("io_readResp_ready"), 
      io_readResp_valid("io_readResp_valid"), io_writeReq_ready("io_writeReq_ready"), 
      io_writeReq_valid("io_writeReq_valid"), io_memReq_ready("io_memReq_ready"), 
      io_memReq_valid("io_memReq_valid"), io_memResp_ready("io_memResp_ready"), 
      io_memResp_valid("io_memResp_valid"), io_memWriteReq_ready("io_memWriteReq_ready"), 
      io_memWriteReq_valid("io_memWriteReq_valid"), 
      io_cacheActive("io_cacheActive"), io_readReq_bits("io_readReq_bits"), 
      io_writeReq_bits("io_writeReq_bits"), io_memReq_bits("io_memReq_bits"), 
      io_memWriteReq_bits("io_memWriteReq_bits"), io_readCount("io_readCount"), 
      io_missCount("io_missCount"), io_readResp_bits("io_readResp_bits"), 
      io_writeData("io_writeData"), io_memResp_bits("io_memResp_bits"), 
      io_memWriteData("io_memWriteData")
#endif
 {
    VSimpleDMVectorCache__Syms* __restrict vlSymsp = __VlSymsp = new VSimpleDMVectorCache__Syms(this, name());
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << reset;
    sensitive << io_readReq_valid;
    sensitive << io_readReq_bits;
    sensitive << io_readResp_ready;
    sensitive << io_writeReq_valid;
    sensitive << io_writeReq_bits;
    sensitive << io_writeData;
    sensitive << io_memReq_ready;
    sensitive << io_memResp_valid;
    sensitive << io_memResp_bits;
    sensitive << io_memWriteReq_ready;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__io_memWriteReq_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_memResp_bits = VL_RAND_RESET_Q(64);
    __Vcellinp__v__io_memResp_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_memReq_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_writeData = VL_RAND_RESET_Q(64);
    __Vcellinp__v__io_writeReq_bits = VL_RAND_RESET_I(24);
    __Vcellinp__v__io_writeReq_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_readResp_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_readReq_bits = VL_RAND_RESET_I(24);
    __Vcellinp__v__io_readReq_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__reset = VL_RAND_RESET_I(1);
    __Vcellinp__v__clk = VL_RAND_RESET_I(1);
    v__DOT__missCount = VL_RAND_RESET_I(32);
    v__DOT__T2 = VL_RAND_RESET_I(1);
    v__DOT__currentReqEntry = VL_RAND_RESET_I(12);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
	    v__DOT__tagStorage[__Vi0] = VL_RAND_RESET_I(12);
    }}
    v__DOT__T9 = VL_RAND_RESET_I(1);
    v__DOT__state = VL_RAND_RESET_I(2);
    v__DOT__initCtr = VL_RAND_RESET_I(13);
    v__DOT__T25 = VL_RAND_RESET_I(1);
    v__DOT__T28 = VL_RAND_RESET_I(1);
    v__DOT__T29 = VL_RAND_RESET_I(1);
    v__DOT__readCount = VL_RAND_RESET_I(32);
    v__DOT__T33 = VL_RAND_RESET_I(1);
    v__DOT__T37 = VL_RAND_RESET_I(1);
    v__DOT__currentWriteReqEntry = VL_RAND_RESET_I(12);
    v__DOT__T39 = VL_RAND_RESET_I(1);
    v__DOT__T42 = VL_RAND_RESET_Q(64);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
	    v__DOT__cacheLines[__Vi0] = VL_RAND_RESET_Q(64);
    }}
    v__DOT__bramReadAddrReg = VL_RAND_RESET_I(13);
    v__DOT__enableWriteOutputReg = VL_RAND_RESET_I(1);
    __Vclklast__TOP____Vcellinp__v__clk = VL_RAND_RESET_I(1);
}

void VSimpleDMVectorCache::__Vconfigure(VSimpleDMVectorCache__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

VSimpleDMVectorCache::~VSimpleDMVectorCache() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void VSimpleDMVectorCache::eval() {
    VSimpleDMVectorCache__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate VSimpleDMVectorCache::eval\n"); );
    int __VclockLoop = 0;
    IData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_PRINTF(" Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void VSimpleDMVectorCache::_eval_initial_loop(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    IData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

void VSimpleDMVectorCache::_combo__TOP__1(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__1\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memWriteReq_ready, vlTOPp->io_memWriteReq_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memResp_valid, vlTOPp->io_memResp_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_writeReq_valid, vlTOPp->io_writeReq_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memReq_ready, vlTOPp->io_memReq_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readReq_valid, vlTOPp->io_readReq_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readResp_ready, vlTOPp->io_readResp_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VSimpleDMVectorCache::_sequent__TOP__3(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__3\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdlyvset__v__DOT__tagStorage__v0,0,0);
    VL_SIG8(__Vdly__v__DOT__state,1,0);
    VL_SIG8(__Vdlyvset__v__DOT__cacheLines__v0,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__cacheLines__v1,0,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__tagStorage__v0,12,0);
    VL_SIG16(__Vdlyvval__v__DOT__tagStorage__v0,11,0);
    VL_SIG16(__Vdly__v__DOT__initCtr,12,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__cacheLines__v0,12,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__cacheLines__v1,12,0);
    //char	__VpadToAlign38[2];
    VL_SIG(__Vdly__v__DOT__missCount,31,0);
    VL_SIG(__Vdly__v__DOT__readCount,31,0);
    VL_SIG64(__Vdlyvval__v__DOT__cacheLines__v0,63,0);
    VL_SIG64(__Vdlyvval__v__DOT__cacheLines__v1,63,0);
    // Body
    __Vdly__v__DOT__readCount = vlTOPp->v__DOT__readCount;
    __Vdly__v__DOT__missCount = vlTOPp->v__DOT__missCount;
    __Vdly__v__DOT__initCtr = vlTOPp->v__DOT__initCtr;
    __Vdly__v__DOT__state = vlTOPp->v__DOT__state;
    __Vdlyvset__v__DOT__cacheLines__v0 = 0;
    __Vdlyvset__v__DOT__cacheLines__v1 = 0;
    __Vdlyvset__v__DOT__tagStorage__v0 = 0;
    // ALWAYS at SimpleDMVectorCache.v:219
    vlTOPp->v__DOT__enableWriteOutputReg = ((~ (IData)(vlTOPp->__Vcellinp__v__reset)) 
					    & (IData)(vlTOPp->v__DOT__T33));
    // ALWAYS at SimpleDMVectorCache.v:208
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__readCount = 0;
    } else {
	if (vlTOPp->v__DOT__T33) {
	    __Vdly__v__DOT__readCount = ((IData)(1) 
					 + vlTOPp->v__DOT__readCount);
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:187
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__missCount = 0;
    } else {
	if (vlTOPp->v__DOT__T2) {
	    __Vdly__v__DOT__missCount = ((IData)(1) 
					 + vlTOPp->v__DOT__missCount);
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:203
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__initCtr = 0;
    } else {
	if ((0 == (IData)(vlTOPp->v__DOT__state))) {
	    __Vdly__v__DOT__initCtr = (0x1fff & ((IData)(1) 
						 + (IData)(vlTOPp->v__DOT__initCtr)));
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:217
    vlTOPp->v__DOT__bramReadAddrReg = (0x1fff & vlTOPp->__Vcellinp__v__io_readReq_bits);
    // ALWAYS at SimpleDMVectorCache.v:194
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__state = 0;
    } else {
	if (vlTOPp->v__DOT__T9) {
	    __Vdly__v__DOT__state = 1;
	} else {
	    if (vlTOPp->v__DOT__T2) {
		__Vdly__v__DOT__state = 2;
	    } else {
		if (((0 == (IData)(vlTOPp->v__DOT__state)) 
		     & (0x1fff == (IData)(vlTOPp->v__DOT__initCtr)))) {
		    __Vdly__v__DOT__state = 1;
		}
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:213
    if (vlTOPp->v__DOT__T9) {
	__Vdlyvval__v__DOT__cacheLines__v0 = vlTOPp->__Vcellinp__v__io_memResp_bits;
	__Vdlyvset__v__DOT__cacheLines__v0 = 1;
	__Vdlyvdim0__v__DOT__cacheLines__v0 = (0x1fff 
					       & vlTOPp->__Vcellinp__v__io_readReq_bits);
    }
    if (((IData)(vlTOPp->v__DOT__T39) & (IData)(vlTOPp->v__DOT__T37))) {
	__Vdlyvval__v__DOT__cacheLines__v1 = vlTOPp->__Vcellinp__v__io_writeData;
	__Vdlyvset__v__DOT__cacheLines__v1 = 1;
	__Vdlyvdim0__v__DOT__cacheLines__v1 = (0x1fff 
					       & vlTOPp->__Vcellinp__v__io_writeReq_bits);
    }
    // ALWAYS at SimpleDMVectorCache.v:192
    if (vlTOPp->v__DOT__T9) {
	__Vdlyvval__v__DOT__tagStorage__v0 = (1 | (0xffe 
						   & (vlTOPp->__Vcellinp__v__io_readReq_bits 
						      >> 0xc)));
	__Vdlyvset__v__DOT__tagStorage__v0 = 1;
	__Vdlyvdim0__v__DOT__tagStorage__v0 = (0x1fff 
					       & vlTOPp->__Vcellinp__v__io_readReq_bits);
    }
    vlTOPp->v__DOT__readCount = __Vdly__v__DOT__readCount;
    vlTOPp->v__DOT__missCount = __Vdly__v__DOT__missCount;
    vlTOPp->v__DOT__initCtr = __Vdly__v__DOT__initCtr;
    vlTOPp->v__DOT__state = __Vdly__v__DOT__state;
    // ALWAYSPOST at SimpleDMVectorCache.v:214
    if (__Vdlyvset__v__DOT__cacheLines__v0) {
	vlTOPp->v__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__cacheLines__v0)] 
	    = __Vdlyvval__v__DOT__cacheLines__v0;
    }
    if (__Vdlyvset__v__DOT__cacheLines__v1) {
	vlTOPp->v__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__cacheLines__v1)] 
	    = __Vdlyvval__v__DOT__cacheLines__v1;
    }
    // ALWAYSPOST at SimpleDMVectorCache.v:193
    if (__Vdlyvset__v__DOT__tagStorage__v0) {
	vlTOPp->v__DOT__tagStorage[(IData)(__Vdlyvdim0__v__DOT__tagStorage__v0)] 
	    = __Vdlyvval__v__DOT__tagStorage__v0;
    }
    VL_ASSIGN_SII(1,vlTOPp->io_readResp_valid, vlTOPp->v__DOT__enableWriteOutputReg);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_missCount, vlTOPp->v__DOT__missCount);
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T29 = ((0 != (IData)(vlTOPp->v__DOT__state)) 
			   & (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T42 = vlTOPp->v__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__bramReadAddrReg)];
}

void VSimpleDMVectorCache::_combo__TOP__4(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__4\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memResp_bits, vlTOPp->io_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writeData, vlTOPp->io_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writeReq_bits, vlTOPp->io_writeReq_bits);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_readReq_bits, vlTOPp->io_readReq_bits);
    vlTOPp->v__DOT__T9 = (((~ ((0 == (IData)(vlTOPp->v__DOT__state)) 
			       | (1 == (IData)(vlTOPp->v__DOT__state)))) 
			   & (2 == (IData)(vlTOPp->v__DOT__state))) 
			  & (IData)(vlTOPp->__Vcellinp__v__io_memResp_valid));
}

void VSimpleDMVectorCache::_settle__TOP__5(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__5\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memResp_bits, vlTOPp->io_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writeData, vlTOPp->io_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writeReq_bits, vlTOPp->io_writeReq_bits);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_readReq_bits, vlTOPp->io_readReq_bits);
    VL_ASSIGN_SII(1,vlTOPp->io_readResp_valid, vlTOPp->v__DOT__enableWriteOutputReg);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_missCount, vlTOPp->v__DOT__missCount);
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T9 = (((~ ((0 == (IData)(vlTOPp->v__DOT__state)) 
			       | (1 == (IData)(vlTOPp->v__DOT__state)))) 
			   & (2 == (IData)(vlTOPp->v__DOT__state))) 
			  & (IData)(vlTOPp->__Vcellinp__v__io_memResp_valid));
    vlTOPp->v__DOT__T29 = ((0 != (IData)(vlTOPp->v__DOT__state)) 
			   & (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T42 = vlTOPp->v__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__bramReadAddrReg)];
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWriteData, vlTOPp->__Vcellinp__v__io_writeData);
    VL_ASSIGN_SII(24,vlTOPp->io_memWriteReq_bits, vlTOPp->__Vcellinp__v__io_writeReq_bits);
    vlTOPp->v__DOT__currentWriteReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_writeReq_bits)];
    vlTOPp->v__DOT__currentReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_readReq_bits)];
    VL_ASSIGN_SII(1,vlTOPp->io_memResp_ready, vlTOPp->v__DOT__T9);
    VL_ASSIGN_SII(1,vlTOPp->io_writeReq_ready, ((IData)(vlTOPp->v__DOT__T29) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready)));
    vlTOPp->v__DOT__T39 = ((IData)(vlTOPp->v__DOT__T29) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_writeReq_valid));
    vlTOPp->v__DOT__T28 = ((IData)(vlTOPp->v__DOT__T29) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readReq_valid));
    VL_ASSIGN_SQQ(64,vlTOPp->io_readResp_bits, vlTOPp->v__DOT__T42);
}

void VSimpleDMVectorCache::_combo__TOP__6(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__6\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWriteData, vlTOPp->__Vcellinp__v__io_writeData);
    VL_ASSIGN_SII(24,vlTOPp->io_memWriteReq_bits, vlTOPp->__Vcellinp__v__io_writeReq_bits);
    vlTOPp->v__DOT__currentWriteReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_writeReq_bits)];
    vlTOPp->v__DOT__currentReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_readReq_bits)];
    VL_ASSIGN_SII(1,vlTOPp->io_memResp_ready, vlTOPp->v__DOT__T9);
    VL_ASSIGN_SII(1,vlTOPp->io_writeReq_ready, ((IData)(vlTOPp->v__DOT__T29) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready)));
    vlTOPp->v__DOT__T39 = ((IData)(vlTOPp->v__DOT__T29) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_writeReq_valid));
    vlTOPp->v__DOT__T28 = ((IData)(vlTOPp->v__DOT__T29) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readReq_valid));
    vlTOPp->v__DOT__T37 = (((0x7ff & (vlTOPp->__Vcellinp__v__io_writeReq_bits 
				      >> 0xd)) == (0x7ff 
						   & ((IData)(vlTOPp->v__DOT__currentWriteReqEntry) 
						      >> 1))) 
			   & (IData)(vlTOPp->v__DOT__currentWriteReqEntry));
    vlTOPp->v__DOT__T25 = ((((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
				       >> 0xd)) == 
			     (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
				       >> 1))) & (IData)(vlTOPp->v__DOT__currentReqEntry)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readResp_ready));
}

void VSimpleDMVectorCache::_sequent__TOP__7(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__7\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SQQ(64,vlTOPp->io_readResp_bits, vlTOPp->v__DOT__T42);
}

void VSimpleDMVectorCache::_settle__TOP__8(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__8\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__T37 = (((0x7ff & (vlTOPp->__Vcellinp__v__io_writeReq_bits 
				      >> 0xd)) == (0x7ff 
						   & ((IData)(vlTOPp->v__DOT__currentWriteReqEntry) 
						      >> 1))) 
			   & (IData)(vlTOPp->v__DOT__currentWriteReqEntry));
    vlTOPp->v__DOT__T25 = ((((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
				       >> 0xd)) == 
			     (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
				       >> 1))) & (IData)(vlTOPp->v__DOT__currentReqEntry)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readResp_ready));
    VL_ASSIGN_SII(1,vlTOPp->io_memWriteReq_valid, ((IData)(vlTOPp->v__DOT__T39) 
						   & (~ (IData)(vlTOPp->v__DOT__T37))));
    vlTOPp->v__DOT__T33 = ((IData)(vlTOPp->v__DOT__T28) 
			   & (IData)(vlTOPp->v__DOT__T25));
    vlTOPp->v__DOT__T2 = ((IData)(vlTOPp->v__DOT__T28) 
			  & ((~ (IData)(vlTOPp->v__DOT__T25)) 
			     & ((((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
					    >> 0xd)) 
				  != (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
					       >> 1))) 
				 | (~ (IData)(vlTOPp->v__DOT__currentReqEntry))) 
				& (IData)(vlTOPp->__Vcellinp__v__io_memReq_ready))));
}

void VSimpleDMVectorCache::_combo__TOP__9(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__9\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_memWriteReq_valid, ((IData)(vlTOPp->v__DOT__T39) 
						   & (~ (IData)(vlTOPp->v__DOT__T37))));
    vlTOPp->v__DOT__T33 = ((IData)(vlTOPp->v__DOT__T28) 
			   & (IData)(vlTOPp->v__DOT__T25));
    vlTOPp->v__DOT__T2 = ((IData)(vlTOPp->v__DOT__T28) 
			  & ((~ (IData)(vlTOPp->v__DOT__T25)) 
			     & ((((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
					    >> 0xd)) 
				  != (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
					       >> 1))) 
				 | (~ (IData)(vlTOPp->v__DOT__currentReqEntry))) 
				& (IData)(vlTOPp->__Vcellinp__v__io_memReq_ready))));
    VL_ASSIGN_SII(1,vlTOPp->io_readReq_ready, vlTOPp->v__DOT__T33);
    VL_ASSIGN_SII(1,vlTOPp->io_memReq_valid, vlTOPp->v__DOT__T2);
    VL_ASSIGN_SII(24,vlTOPp->io_memReq_bits, ((IData)(vlTOPp->v__DOT__T2)
					       ? vlTOPp->__Vcellinp__v__io_readReq_bits
					       : 0));
}

void VSimpleDMVectorCache::_settle__TOP__10(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__10\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_readReq_ready, vlTOPp->v__DOT__T33);
    VL_ASSIGN_SII(1,vlTOPp->io_memReq_valid, vlTOPp->v__DOT__T2);
    VL_ASSIGN_SII(24,vlTOPp->io_memReq_bits, ((IData)(vlTOPp->v__DOT__T2)
					       ? vlTOPp->__Vcellinp__v__io_readReq_bits
					       : 0));
}

void VSimpleDMVectorCache::_eval(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_eval\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    vlTOPp->_combo__TOP__6(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__7(vlSymsp);
    }
    vlTOPp->_combo__TOP__9(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__v__clk = vlTOPp->__Vcellinp__v__clk;
}

void VSimpleDMVectorCache::_eval_initial(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_eval_initial\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VSimpleDMVectorCache::final() {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::final\n"); );
    // Variables
    VSimpleDMVectorCache__Syms* __restrict vlSymsp = this->__VlSymsp;
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VSimpleDMVectorCache::_eval_settle(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_eval_settle\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    vlTOPp->_settle__TOP__5(vlSymsp);
    vlTOPp->_settle__TOP__8(vlSymsp);
    vlTOPp->_settle__TOP__10(vlSymsp);
}

IData VSimpleDMVectorCache::_change_request(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_change_request\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
