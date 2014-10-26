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
      io_flushCache("io_flushCache"), io_cacheActive("io_cacheActive"), 
      io_readReq_bits("io_readReq_bits"), io_readRespInd("io_readRespInd"), 
      io_writeReq_bits("io_writeReq_bits"), io_memReq_bits("io_memReq_bits"), 
      io_memWriteReq_bits("io_memWriteReq_bits"), io_readCount("io_readCount"), 
      io_readMissCount("io_readMissCount"), io_writeCount("io_writeCount"), 
      io_writeMissCount("io_writeMissCount"), io_readResp_bits("io_readResp_bits"), 
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
    sensitive << io_flushCache;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__io_flushCache = VL_RAND_RESET_I(1);
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
    v__DOT__writeMissCount = VL_RAND_RESET_I(32);
    v__DOT__T2 = VL_RAND_RESET_I(1);
    v__DOT__T5 = VL_RAND_RESET_I(1);
    v__DOT__currentWriteReqEntry = VL_RAND_RESET_I(12);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
	    v__DOT__tagStorage[__Vi0] = VL_RAND_RESET_I(12);
    }}
    v__DOT__T8 = VL_RAND_RESET_I(1);
    v__DOT__state = VL_RAND_RESET_I(3);
    v__DOT__initCtr = VL_RAND_RESET_I(13);
    v__DOT__T28 = VL_RAND_RESET_I(1);
    v__DOT__T32 = VL_RAND_RESET_I(1);
    v__DOT__T35 = VL_RAND_RESET_I(1);
    v__DOT__T39 = VL_RAND_RESET_I(1);
    v__DOT__T40 = VL_RAND_RESET_I(1);
    v__DOT__T43 = VL_RAND_RESET_I(1);
    v__DOT__T44 = VL_RAND_RESET_I(1);
    v__DOT__T46 = VL_RAND_RESET_I(1);
    v__DOT__currentReqEntry = VL_RAND_RESET_I(12);
    v__DOT__T49 = VL_RAND_RESET_I(1);
    v__DOT__T52 = VL_RAND_RESET_I(1);
    v__DOT__T53 = VL_RAND_RESET_I(1);
    v__DOT__T55 = VL_RAND_RESET_I(1);
    v__DOT__T61 = VL_RAND_RESET_I(1);
    v__DOT__T65 = VL_RAND_RESET_I(1);
    v__DOT__T70 = VL_RAND_RESET_I(1);
    v__DOT__writeCount = VL_RAND_RESET_I(32);
    v__DOT__T74 = VL_RAND_RESET_I(1);
    v__DOT__readMissCount = VL_RAND_RESET_I(32);
    v__DOT__readCount = VL_RAND_RESET_I(32);
    v__DOT__T82 = VL_RAND_RESET_I(1);
    v__DOT__flushDataReg = VL_RAND_RESET_Q(64);
    v__DOT__T86 = VL_RAND_RESET_Q(64);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
	    v__DOT__cacheLines[__Vi0] = VL_RAND_RESET_Q(64);
    }}
    v__DOT__bramReadValue = VL_RAND_RESET_Q(64);
    v__DOT__requestReg = VL_RAND_RESET_I(24);
    v__DOT__T94 = VL_RAND_RESET_I(12);
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
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memResp_valid, vlTOPp->io_memResp_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_writeReq_valid, vlTOPp->io_writeReq_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memWriteReq_ready, vlTOPp->io_memWriteReq_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readReq_valid, vlTOPp->io_readReq_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readResp_ready, vlTOPp->io_readResp_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memReq_ready, vlTOPp->io_memReq_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_flushCache, vlTOPp->io_flushCache);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VSimpleDMVectorCache::_sequent__TOP__3(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__3\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdlyvset__v__DOT__tagStorage__v0,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__tagStorage__v1,0,0);
    VL_SIG8(__Vdly__v__DOT__state,2,0);
    VL_SIG8(__Vdlyvset__v__DOT__cacheLines__v0,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__cacheLines__v1,0,0);
    //char	__VpadToAlign29[1];
    VL_SIG16(__Vdlyvdim0__v__DOT__tagStorage__v0,12,0);
    VL_SIG16(__Vdlyvval__v__DOT__tagStorage__v0,11,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__tagStorage__v1,12,0);
    VL_SIG16(__Vdly__v__DOT__initCtr,12,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__cacheLines__v0,12,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__cacheLines__v1,12,0);
    //char	__VpadToAlign42[2];
    VL_SIG(__Vdly__v__DOT__writeMissCount,31,0);
    VL_SIG(__Vdly__v__DOT__writeCount,31,0);
    VL_SIG(__Vdly__v__DOT__readMissCount,31,0);
    VL_SIG(__Vdly__v__DOT__readCount,31,0);
    //char	__VpadToAlign60[4];
    VL_SIG64(__Vdlyvval__v__DOT__cacheLines__v0,63,0);
    VL_SIG64(__Vdlyvval__v__DOT__cacheLines__v1,63,0);
    // Body
    __Vdly__v__DOT__readCount = vlTOPp->v__DOT__readCount;
    __Vdly__v__DOT__writeMissCount = vlTOPp->v__DOT__writeMissCount;
    __Vdly__v__DOT__writeCount = vlTOPp->v__DOT__writeCount;
    __Vdly__v__DOT__readMissCount = vlTOPp->v__DOT__readMissCount;
    __Vdlyvset__v__DOT__cacheLines__v0 = 0;
    __Vdlyvset__v__DOT__cacheLines__v1 = 0;
    __Vdly__v__DOT__initCtr = vlTOPp->v__DOT__initCtr;
    __Vdlyvset__v__DOT__tagStorage__v0 = 0;
    __Vdlyvset__v__DOT__tagStorage__v1 = 0;
    __Vdly__v__DOT__state = vlTOPp->v__DOT__state;
    // ALWAYS at SimpleDMVectorCache.v:381
    vlTOPp->v__DOT__flushDataReg = vlTOPp->v__DOT__T86;
    // ALWAYS at SimpleDMVectorCache.v:388
    vlTOPp->v__DOT__enableWriteOutputReg = ((~ (IData)(vlTOPp->__Vcellinp__v__reset)) 
					    & (IData)(vlTOPp->v__DOT__T82));
    // ALWAYS at SimpleDMVectorCache.v:376
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__readCount = 0;
    } else {
	if (vlTOPp->v__DOT__T82) {
	    __Vdly__v__DOT__readCount = ((IData)(1) 
					 + vlTOPp->v__DOT__readCount);
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:323
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__writeMissCount = 0;
    } else {
	if (vlTOPp->v__DOT__T2) {
	    __Vdly__v__DOT__writeMissCount = ((IData)(1) 
					      + vlTOPp->v__DOT__writeMissCount);
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:362
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__writeCount = 0;
    } else {
	if (vlTOPp->v__DOT__T2) {
	    __Vdly__v__DOT__writeCount = ((IData)(1) 
					  + vlTOPp->v__DOT__writeCount);
	} else {
	    if (vlTOPp->v__DOT__T74) {
		__Vdly__v__DOT__writeCount = ((IData)(1) 
					      + vlTOPp->v__DOT__writeCount);
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:369
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__readMissCount = 0;
    } else {
	if (vlTOPp->v__DOT__T55) {
	    __Vdly__v__DOT__readMissCount = ((IData)(1) 
					     + vlTOPp->v__DOT__readMissCount);
	} else {
	    if (vlTOPp->v__DOT__T44) {
		__Vdly__v__DOT__readMissCount = ((IData)(1) 
						 + vlTOPp->v__DOT__readMissCount);
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:386
    vlTOPp->v__DOT__requestReg = vlTOPp->__Vcellinp__v__io_readReq_bits;
    // ALWAYS at SimpleDMVectorCache.v:382
    if (vlTOPp->v__DOT__T8) {
	__Vdlyvval__v__DOT__cacheLines__v0 = vlTOPp->__Vcellinp__v__io_memResp_bits;
	__Vdlyvset__v__DOT__cacheLines__v0 = 1;
	__Vdlyvdim0__v__DOT__cacheLines__v0 = (0x1fff 
					       & vlTOPp->__Vcellinp__v__io_readReq_bits);
    }
    if (vlTOPp->v__DOT__T74) {
	__Vdlyvval__v__DOT__cacheLines__v1 = vlTOPp->__Vcellinp__v__io_writeData;
	__Vdlyvset__v__DOT__cacheLines__v1 = 1;
	__Vdlyvdim0__v__DOT__cacheLines__v1 = (0x1fff 
					       & vlTOPp->__Vcellinp__v__io_writeReq_bits);
    }
    // ALWAYS at SimpleDMVectorCache.v:349
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__initCtr = 0;
    } else {
	if (vlTOPp->v__DOT__T39) {
	    __Vdly__v__DOT__initCtr = 0;
	} else {
	    if (vlTOPp->v__DOT__T28) {
		__Vdly__v__DOT__initCtr = (0x1fff & 
					   ((IData)(1) 
					    + (IData)(vlTOPp->v__DOT__initCtr)));
	    } else {
		if (vlTOPp->v__DOT__T35) {
		    __Vdly__v__DOT__initCtr = (0x1fff 
					       & ((IData)(1) 
						  + (IData)(vlTOPp->v__DOT__initCtr)));
		} else {
		    if ((0 == (IData)(vlTOPp->v__DOT__state))) {
			__Vdly__v__DOT__initCtr = (0x1fff 
						   & ((IData)(1) 
						      + (IData)(vlTOPp->v__DOT__initCtr)));
		    }
		}
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:328
    if (vlTOPp->v__DOT__T8) {
	__Vdlyvval__v__DOT__tagStorage__v0 = (1 | (0xffe 
						   & (vlTOPp->__Vcellinp__v__io_readReq_bits 
						      >> 0xc)));
	__Vdlyvset__v__DOT__tagStorage__v0 = 1;
	__Vdlyvdim0__v__DOT__tagStorage__v0 = (0x1fff 
					       & vlTOPp->__Vcellinp__v__io_readReq_bits);
    }
    if ((0 == (IData)(vlTOPp->v__DOT__state))) {
	__Vdlyvset__v__DOT__tagStorage__v1 = 1;
	__Vdlyvdim0__v__DOT__tagStorage__v1 = vlTOPp->v__DOT__initCtr;
    }
    // ALWAYS at SimpleDMVectorCache.v:330
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__state = 0;
    } else {
	if (vlTOPp->v__DOT__T8) {
	    __Vdly__v__DOT__state = 1;
	} else {
	    if (vlTOPp->v__DOT__T61) {
		__Vdly__v__DOT__state = 3;
	    } else {
		if (vlTOPp->v__DOT__T55) {
		    __Vdly__v__DOT__state = 2;
		} else {
		    if (vlTOPp->v__DOT__T44) {
			__Vdly__v__DOT__state = 3;
		    } else {
			if (vlTOPp->v__DOT__T39) {
			    __Vdly__v__DOT__state = 4;
			} else {
			    if (((IData)(vlTOPp->v__DOT__T28) 
				 & (0x1fff == (IData)(vlTOPp->v__DOT__initCtr)))) {
				__Vdly__v__DOT__state = 1;
			    } else {
				if (vlTOPp->v__DOT__T35) {
				    __Vdly__v__DOT__state = 5;
				} else {
				    if (((0 == (IData)(vlTOPp->v__DOT__state)) 
					 & (0x1fff 
					    == (IData)(vlTOPp->v__DOT__initCtr)))) {
					__Vdly__v__DOT__state = 1;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    vlTOPp->v__DOT__readCount = __Vdly__v__DOT__readCount;
    vlTOPp->v__DOT__writeMissCount = __Vdly__v__DOT__writeMissCount;
    vlTOPp->v__DOT__writeCount = __Vdly__v__DOT__writeCount;
    vlTOPp->v__DOT__readMissCount = __Vdly__v__DOT__readMissCount;
    // ALWAYSPOST at SimpleDMVectorCache.v:383
    if (__Vdlyvset__v__DOT__cacheLines__v0) {
	vlTOPp->v__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__cacheLines__v0)] 
	    = __Vdlyvval__v__DOT__cacheLines__v0;
    }
    if (__Vdlyvset__v__DOT__cacheLines__v1) {
	vlTOPp->v__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__cacheLines__v1)] 
	    = __Vdlyvval__v__DOT__cacheLines__v1;
    }
    // ALWAYSPOST at SimpleDMVectorCache.v:329
    if (__Vdlyvset__v__DOT__tagStorage__v0) {
	vlTOPp->v__DOT__tagStorage[(IData)(__Vdlyvdim0__v__DOT__tagStorage__v0)] 
	    = __Vdlyvval__v__DOT__tagStorage__v0;
    }
    if (__Vdlyvset__v__DOT__tagStorage__v1) {
	vlTOPp->v__DOT__tagStorage[(IData)(__Vdlyvdim0__v__DOT__tagStorage__v1)] = 0;
    }
    vlTOPp->v__DOT__initCtr = __Vdly__v__DOT__initCtr;
    vlTOPp->v__DOT__state = __Vdly__v__DOT__state;
    VL_ASSIGN_SII(1,vlTOPp->io_readResp_valid, vlTOPp->v__DOT__enableWriteOutputReg);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeMissCount, vlTOPp->v__DOT__writeMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeCount, vlTOPp->v__DOT__writeCount);
    VL_ASSIGN_SII(32,vlTOPp->io_readMissCount, vlTOPp->v__DOT__readMissCount);
    VL_ASSIGN_SII(24,vlTOPp->io_readRespInd, vlTOPp->v__DOT__requestReg);
    vlTOPp->v__DOT__bramReadValue = vlTOPp->v__DOT__cacheLines
	[(0x1fff & vlTOPp->v__DOT__requestReg)];
    vlTOPp->v__DOT__T86 = vlTOPp->v__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__initCtr)];
    vlTOPp->v__DOT__T94 = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & ((IData)(vlTOPp->v__DOT__initCtr) 
		    - (IData)(1)))];
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T35 = ((0 != (IData)(vlTOPp->v__DOT__state)) 
			   & (4 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T32 = ((0 == (IData)(vlTOPp->v__DOT__state)) 
			   | (4 == (IData)(vlTOPp->v__DOT__state)));
}

void VSimpleDMVectorCache::_combo__TOP__4(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__4\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memResp_bits, vlTOPp->io_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writeData, vlTOPp->io_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writeReq_bits, vlTOPp->io_writeReq_bits);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_readReq_bits, vlTOPp->io_readReq_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
}

void VSimpleDMVectorCache::_settle__TOP__5(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__5\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memResp_bits, vlTOPp->io_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writeData, vlTOPp->io_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writeReq_bits, vlTOPp->io_writeReq_bits);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_readReq_bits, vlTOPp->io_readReq_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_SII(1,vlTOPp->io_readResp_valid, vlTOPp->v__DOT__enableWriteOutputReg);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeMissCount, vlTOPp->v__DOT__writeMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeCount, vlTOPp->v__DOT__writeCount);
    VL_ASSIGN_SII(32,vlTOPp->io_readMissCount, vlTOPp->v__DOT__readMissCount);
    VL_ASSIGN_SII(24,vlTOPp->io_readRespInd, vlTOPp->v__DOT__requestReg);
    vlTOPp->v__DOT__bramReadValue = vlTOPp->v__DOT__cacheLines
	[(0x1fff & vlTOPp->v__DOT__requestReg)];
    vlTOPp->v__DOT__T86 = vlTOPp->v__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__initCtr)];
    vlTOPp->v__DOT__T94 = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & ((IData)(vlTOPp->v__DOT__initCtr) 
		    - (IData)(1)))];
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T35 = ((0 != (IData)(vlTOPp->v__DOT__state)) 
			   & (4 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T32 = ((0 == (IData)(vlTOPp->v__DOT__state)) 
			   | (4 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__currentWriteReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_writeReq_bits)];
    vlTOPp->v__DOT__currentReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_readReq_bits)];
    VL_ASSIGN_SQQ(64,vlTOPp->io_readResp_bits, vlTOPp->v__DOT__bramReadValue);
    vlTOPp->v__DOT__T28 = (((~ (IData)(vlTOPp->v__DOT__T32)) 
			    & (5 == (IData)(vlTOPp->v__DOT__state))) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready));
    vlTOPp->v__DOT__T43 = ((IData)(vlTOPp->v__DOT__T32) 
			   | (5 == (IData)(vlTOPp->v__DOT__state)));
}

void VSimpleDMVectorCache::_combo__TOP__6(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__6\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__currentWriteReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_writeReq_bits)];
    vlTOPp->v__DOT__currentReqEntry = (IData)(vlTOPp->v__DOT__tagStorage)
	[(0x1fff & vlTOPp->__Vcellinp__v__io_readReq_bits)];
    vlTOPp->v__DOT__T28 = (((~ (IData)(vlTOPp->v__DOT__T32)) 
			    & (5 == (IData)(vlTOPp->v__DOT__state))) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready));
    vlTOPp->v__DOT__T5 = (((0x7ff & (vlTOPp->__Vcellinp__v__io_writeReq_bits 
				     >> 0xd)) == (0x7ff 
						  & ((IData)(vlTOPp->v__DOT__currentWriteReqEntry) 
						     >> 1))) 
			  & (IData)(vlTOPp->v__DOT__currentWriteReqEntry));
    vlTOPp->v__DOT__T46 = ((~ (IData)(vlTOPp->v__DOT__currentReqEntry)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_memReq_ready));
    vlTOPp->v__DOT__T49 = ((((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
				       >> 0xd)) == 
			     (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
				       >> 1))) & (IData)(vlTOPp->v__DOT__currentReqEntry)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readResp_ready));
}

void VSimpleDMVectorCache::_sequent__TOP__7(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__7\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SQQ(64,vlTOPp->io_readResp_bits, vlTOPp->v__DOT__bramReadValue);
    vlTOPp->v__DOT__T43 = ((IData)(vlTOPp->v__DOT__T32) 
			   | (5 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T65 = ((IData)(vlTOPp->v__DOT__T43) 
			   | (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T40 = ((~ (IData)(vlTOPp->v__DOT__T43)) 
			   & (1 == (IData)(vlTOPp->v__DOT__state)));
}

void VSimpleDMVectorCache::_settle__TOP__8(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__8\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__T5 = (((0x7ff & (vlTOPp->__Vcellinp__v__io_writeReq_bits 
				     >> 0xd)) == (0x7ff 
						  & ((IData)(vlTOPp->v__DOT__currentWriteReqEntry) 
						     >> 1))) 
			  & (IData)(vlTOPp->v__DOT__currentWriteReqEntry));
    vlTOPp->v__DOT__T46 = ((~ (IData)(vlTOPp->v__DOT__currentReqEntry)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_memReq_ready));
    vlTOPp->v__DOT__T49 = ((((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
				       >> 0xd)) == 
			     (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
				       >> 1))) & (IData)(vlTOPp->v__DOT__currentReqEntry)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readResp_ready));
    vlTOPp->v__DOT__T65 = ((IData)(vlTOPp->v__DOT__T43) 
			   | (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T40 = ((~ (IData)(vlTOPp->v__DOT__T43)) 
			   & (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T8 = (((~ ((IData)(vlTOPp->v__DOT__T65) 
			       | (2 == (IData)(vlTOPp->v__DOT__state)))) 
			   & (3 == (IData)(vlTOPp->v__DOT__state))) 
			  & (IData)(vlTOPp->__Vcellinp__v__io_memResp_valid));
    vlTOPp->v__DOT__T61 = (((~ (IData)(vlTOPp->v__DOT__T65)) 
			    & (2 == (IData)(vlTOPp->v__DOT__state))) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready));
    vlTOPp->v__DOT__T39 = ((IData)(vlTOPp->v__DOT__T40) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_flushCache));
    vlTOPp->v__DOT__T53 = ((IData)(vlTOPp->v__DOT__T40) 
			   & (~ (IData)(vlTOPp->__Vcellinp__v__io_flushCache)));
}

void VSimpleDMVectorCache::_combo__TOP__9(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__9\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__T8 = (((~ ((IData)(vlTOPp->v__DOT__T65) 
			       | (2 == (IData)(vlTOPp->v__DOT__state)))) 
			   & (3 == (IData)(vlTOPp->v__DOT__state))) 
			  & (IData)(vlTOPp->__Vcellinp__v__io_memResp_valid));
    vlTOPp->v__DOT__T61 = (((~ (IData)(vlTOPp->v__DOT__T65)) 
			    & (2 == (IData)(vlTOPp->v__DOT__state))) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready));
    vlTOPp->v__DOT__T39 = ((IData)(vlTOPp->v__DOT__T40) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_flushCache));
    vlTOPp->v__DOT__T53 = ((IData)(vlTOPp->v__DOT__T40) 
			   & (~ (IData)(vlTOPp->__Vcellinp__v__io_flushCache)));
    VL_ASSIGN_SII(1,vlTOPp->io_memResp_ready, vlTOPp->v__DOT__T8);
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWriteData, ((IData)(vlTOPp->v__DOT__T61)
					        ? vlTOPp->v__DOT__bramReadValue
					        : ((IData)(vlTOPp->v__DOT__T28)
						    ? vlTOPp->v__DOT__flushDataReg
						    : vlTOPp->__Vcellinp__v__io_writeData)));
    VL_ASSIGN_SII(24,vlTOPp->io_memWriteReq_bits, ((IData)(vlTOPp->v__DOT__T61)
						    ? 
						   ((0xffe000 
						     & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
							<< 0xc)) 
						    | (0x1fff 
						       & vlTOPp->__Vcellinp__v__io_readReq_bits))
						    : 
						   ((IData)(vlTOPp->v__DOT__T28)
						     ? 
						    ((0xffe000 
						      & ((IData)(vlTOPp->v__DOT__T94) 
							 << 0xc)) 
						     | (0x1fff 
							& ((IData)(vlTOPp->v__DOT__initCtr) 
							   - (IData)(1))))
						     : vlTOPp->__Vcellinp__v__io_writeReq_bits)));
    VL_ASSIGN_SII(1,vlTOPp->io_writeReq_ready, ((IData)(vlTOPp->v__DOT__T53) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready)));
    vlTOPp->v__DOT__T70 = ((IData)(vlTOPp->v__DOT__T53) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_writeReq_valid));
    vlTOPp->v__DOT__T52 = ((IData)(vlTOPp->v__DOT__T53) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readReq_valid));
}

void VSimpleDMVectorCache::_settle__TOP__10(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__10\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_memResp_ready, vlTOPp->v__DOT__T8);
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWriteData, ((IData)(vlTOPp->v__DOT__T61)
					        ? vlTOPp->v__DOT__bramReadValue
					        : ((IData)(vlTOPp->v__DOT__T28)
						    ? vlTOPp->v__DOT__flushDataReg
						    : vlTOPp->__Vcellinp__v__io_writeData)));
    VL_ASSIGN_SII(24,vlTOPp->io_memWriteReq_bits, ((IData)(vlTOPp->v__DOT__T61)
						    ? 
						   ((0xffe000 
						     & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
							<< 0xc)) 
						    | (0x1fff 
						       & vlTOPp->__Vcellinp__v__io_readReq_bits))
						    : 
						   ((IData)(vlTOPp->v__DOT__T28)
						     ? 
						    ((0xffe000 
						      & ((IData)(vlTOPp->v__DOT__T94) 
							 << 0xc)) 
						     | (0x1fff 
							& ((IData)(vlTOPp->v__DOT__initCtr) 
							   - (IData)(1))))
						     : vlTOPp->__Vcellinp__v__io_writeReq_bits)));
    VL_ASSIGN_SII(1,vlTOPp->io_writeReq_ready, ((IData)(vlTOPp->v__DOT__T53) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready)));
    vlTOPp->v__DOT__T70 = ((IData)(vlTOPp->v__DOT__T53) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_writeReq_valid));
    vlTOPp->v__DOT__T52 = ((IData)(vlTOPp->v__DOT__T53) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_readReq_valid));
    vlTOPp->v__DOT__T74 = ((IData)(vlTOPp->v__DOT__T70) 
			   & (IData)(vlTOPp->v__DOT__T5));
    vlTOPp->v__DOT__T2 = ((IData)(vlTOPp->v__DOT__T70) 
			  & ((~ (IData)(vlTOPp->v__DOT__T5)) 
			     & (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready)));
    vlTOPp->v__DOT__T82 = ((IData)(vlTOPp->v__DOT__T52) 
			   & (IData)(vlTOPp->v__DOT__T49));
    vlTOPp->v__DOT__T44 = ((IData)(vlTOPp->v__DOT__T52) 
			   & ((~ (IData)(vlTOPp->v__DOT__T49)) 
			      & (IData)(vlTOPp->v__DOT__T46)));
    vlTOPp->v__DOT__T55 = ((IData)(vlTOPp->v__DOT__T52) 
			   & ((~ ((IData)(vlTOPp->v__DOT__T49) 
				  | (IData)(vlTOPp->v__DOT__T46))) 
			      & (((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
					    >> 0xd)) 
				  != (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
					       >> 1))) 
				 & (IData)(vlTOPp->__Vcellinp__v__io_memReq_ready))));
}

void VSimpleDMVectorCache::_combo__TOP__11(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__11\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__T74 = ((IData)(vlTOPp->v__DOT__T70) 
			   & (IData)(vlTOPp->v__DOT__T5));
    vlTOPp->v__DOT__T2 = ((IData)(vlTOPp->v__DOT__T70) 
			  & ((~ (IData)(vlTOPp->v__DOT__T5)) 
			     & (IData)(vlTOPp->__Vcellinp__v__io_memWriteReq_ready)));
    vlTOPp->v__DOT__T82 = ((IData)(vlTOPp->v__DOT__T52) 
			   & (IData)(vlTOPp->v__DOT__T49));
    vlTOPp->v__DOT__T44 = ((IData)(vlTOPp->v__DOT__T52) 
			   & ((~ (IData)(vlTOPp->v__DOT__T49)) 
			      & (IData)(vlTOPp->v__DOT__T46)));
    vlTOPp->v__DOT__T55 = ((IData)(vlTOPp->v__DOT__T52) 
			   & ((~ ((IData)(vlTOPp->v__DOT__T49) 
				  | (IData)(vlTOPp->v__DOT__T46))) 
			      & (((0x7ff & (vlTOPp->__Vcellinp__v__io_readReq_bits 
					    >> 0xd)) 
				  != (0x7ff & ((IData)(vlTOPp->v__DOT__currentReqEntry) 
					       >> 1))) 
				 & (IData)(vlTOPp->__Vcellinp__v__io_memReq_ready))));
    VL_ASSIGN_SII(1,vlTOPp->io_memWriteReq_valid, ((IData)(vlTOPp->v__DOT__T61) 
						   | ((IData)(vlTOPp->v__DOT__T2) 
						      | ((IData)(vlTOPp->v__DOT__T28) 
							 & (IData)(vlTOPp->v__DOT__T94)))));
    VL_ASSIGN_SII(1,vlTOPp->io_readReq_ready, vlTOPp->v__DOT__T82);
    VL_ASSIGN_SII(1,vlTOPp->io_memReq_valid, ((IData)(vlTOPp->v__DOT__T55) 
					      | (IData)(vlTOPp->v__DOT__T44)));
    VL_ASSIGN_SII(24,vlTOPp->io_memReq_bits, ((IData)(vlTOPp->v__DOT__T55)
					       ? vlTOPp->__Vcellinp__v__io_readReq_bits
					       : ((IData)(vlTOPp->v__DOT__T44)
						   ? vlTOPp->__Vcellinp__v__io_readReq_bits
						   : 0)));
}

void VSimpleDMVectorCache::_settle__TOP__12(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__12\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_memWriteReq_valid, ((IData)(vlTOPp->v__DOT__T61) 
						   | ((IData)(vlTOPp->v__DOT__T2) 
						      | ((IData)(vlTOPp->v__DOT__T28) 
							 & (IData)(vlTOPp->v__DOT__T94)))));
    VL_ASSIGN_SII(1,vlTOPp->io_readReq_ready, vlTOPp->v__DOT__T82);
    VL_ASSIGN_SII(1,vlTOPp->io_memReq_valid, ((IData)(vlTOPp->v__DOT__T55) 
					      | (IData)(vlTOPp->v__DOT__T44)));
    VL_ASSIGN_SII(24,vlTOPp->io_memReq_bits, ((IData)(vlTOPp->v__DOT__T55)
					       ? vlTOPp->__Vcellinp__v__io_readReq_bits
					       : ((IData)(vlTOPp->v__DOT__T44)
						   ? vlTOPp->__Vcellinp__v__io_readReq_bits
						   : 0)));
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
    vlTOPp->_combo__TOP__11(vlSymsp);
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
    vlTOPp->_settle__TOP__12(vlSymsp);
}

IData VSimpleDMVectorCache::_change_request(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_change_request\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
