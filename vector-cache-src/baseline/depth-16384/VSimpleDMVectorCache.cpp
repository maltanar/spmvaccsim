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
    : clk("clk"), reset("reset"), io_readPort_readReq_ready("io_readPort_readReq_ready"), 
      io_readPort_readReq_valid("io_readPort_readReq_valid"), 
      io_readPort_readResp_ready("io_readPort_readResp_ready"), 
      io_readPort_readResp_valid("io_readPort_readResp_valid"), 
      io_writePort_writeReq_ready("io_writePort_writeReq_ready"), 
      io_writePort_writeReq_valid("io_writePort_writeReq_valid"), 
      io_memRead_memReq_ready("io_memRead_memReq_ready"), 
      io_memRead_memReq_valid("io_memRead_memReq_valid"), 
      io_memRead_memResp_ready("io_memRead_memResp_ready"), 
      io_memRead_memResp_valid("io_memRead_memResp_valid"), 
      io_memWrite_memWriteReq_ready("io_memWrite_memWriteReq_ready"), 
      io_memWrite_memWriteReq_valid("io_memWrite_memWriteReq_valid"), 
      io_flushCache("io_flushCache"), io_cacheActive("io_cacheActive"), 
      io_readPort_readReq_bits("io_readPort_readReq_bits"), 
      io_readPort_readRespInd("io_readPort_readRespInd"), 
      io_writePort_writeReq_bits("io_writePort_writeReq_bits"), 
      io_memRead_memReq_bits("io_memRead_memReq_bits"), 
      io_memWrite_memWriteReq_bits("io_memWrite_memWriteReq_bits"), 
      io_readCount("io_readCount"), io_readMissCount("io_readMissCount"), 
      io_writeCount("io_writeCount"), io_writeMissCount("io_writeMissCount"), 
      io_readPort_readResp_bits("io_readPort_readResp_bits"), 
      io_writePort_writeData("io_writePort_writeData"), 
      io_memRead_memResp_bits("io_memRead_memResp_bits"), 
      io_memWrite_memWriteData("io_memWrite_memWriteData")
#endif
 {
    VSimpleDMVectorCache__Syms* __restrict vlSymsp = __VlSymsp = new VSimpleDMVectorCache__Syms(this, name());
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << reset;
    sensitive << io_readPort_readReq_valid;
    sensitive << io_readPort_readReq_bits;
    sensitive << io_readPort_readResp_ready;
    sensitive << io_writePort_writeReq_valid;
    sensitive << io_writePort_writeReq_bits;
    sensitive << io_writePort_writeData;
    sensitive << io_memRead_memResp_valid;
    sensitive << io_memRead_memResp_bits;
    sensitive << io_memWrite_memWriteReq_ready;
    sensitive << io_flushCache;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__io_flushCache = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_memWrite_memWriteReq_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_memRead_memResp_bits = VL_RAND_RESET_Q(64);
    __Vcellinp__v__io_memRead_memResp_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_writePort_writeData = VL_RAND_RESET_Q(64);
    __Vcellinp__v__io_writePort_writeReq_bits = VL_RAND_RESET_I(24);
    __Vcellinp__v__io_writePort_writeReq_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_readPort_readResp_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_readPort_readReq_bits = VL_RAND_RESET_I(24);
    __Vcellinp__v__io_readPort_readReq_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__reset = VL_RAND_RESET_I(1);
    __Vcellinp__v__clk = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__state = VL_RAND_RESET_I(3);
    v__DOT__controller__DOT__initCtr = VL_RAND_RESET_I(14);
    v__DOT__controller__DOT__T20 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T21 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T24 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T26 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T30 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T31 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T34 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T35 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T41 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T44 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T45 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T49 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T52 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T53 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T56 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T57 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T61 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T62 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T63 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T69 = VL_RAND_RESET_I(14);
    v__DOT__controller__DOT__T73 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T76 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T77 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T78 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T80 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T81 = VL_RAND_RESET_I(14);
    v__DOT__controller__DOT__writeMissCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__T86 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T90 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__writeCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__readMissCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__readCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__T105 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__prevReadRequestReg = VL_RAND_RESET_I(24);
    v__DOT__controller__DOT__enableReadRespReg = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<16384; ++__Vi0) {
	    v__DOT__dataMem__DOT__cacheLines[__Vi0] = VL_RAND_RESET_Q(64);
    }}
    v__DOT__dataMem__DOT__R4 = VL_RAND_RESET_Q(64);
    v__DOT__dataMem__DOT__T5 = VL_RAND_RESET_Q(64);
    v__DOT__tagMem__DOT__T0 = VL_RAND_RESET_I(11);
    { int __Vi0=0; for (; __Vi0<16384; ++__Vi0) {
	    v__DOT__tagMem__DOT__tagStorage[__Vi0] = VL_RAND_RESET_I(11);
    }}
    v__DOT__tagMem__DOT__T2 = VL_RAND_RESET_I(11);
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
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memRead_memResp_valid, vlTOPp->io_memRead_memResp_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readPort_readReq_valid, vlTOPp->io_readPort_readReq_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readPort_readResp_ready, vlTOPp->io_readPort_readResp_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_flushCache, vlTOPp->io_flushCache);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready, vlTOPp->io_memWrite_memWriteReq_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VSimpleDMVectorCache::_sequent__TOP__3(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__3\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__controller__DOT__state,2,0);
    VL_SIG8(__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0,0,0);
    VL_SIG16(__Vdly__v__DOT__controller__DOT__initCtr,13,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v0,13,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v1,13,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__tagMem__DOT__tagStorage__v0,13,0);
    VL_SIG16(__Vdlyvval__v__DOT__tagMem__DOT__tagStorage__v0,10,0);
    //char	__VpadToAlign38[2];
    VL_SIG(__Vdly__v__DOT__controller__DOT__writeMissCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__writeCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__readMissCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__readCount,31,0);
    VL_SIG64(__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v0,63,0);
    VL_SIG64(__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v1,63,0);
    // Body
    __Vdly__v__DOT__controller__DOT__readMissCount 
	= vlTOPp->v__DOT__controller__DOT__readMissCount;
    __Vdly__v__DOT__controller__DOT__readCount = vlTOPp->v__DOT__controller__DOT__readCount;
    __Vdly__v__DOT__controller__DOT__writeMissCount 
	= vlTOPp->v__DOT__controller__DOT__writeMissCount;
    __Vdly__v__DOT__controller__DOT__writeCount = vlTOPp->v__DOT__controller__DOT__writeCount;
    __Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0 = 0;
    __Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1 = 0;
    __Vdly__v__DOT__controller__DOT__initCtr = vlTOPp->v__DOT__controller__DOT__initCtr;
    __Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0 = 0;
    __Vdly__v__DOT__controller__DOT__state = vlTOPp->v__DOT__controller__DOT__state;
    // ALWAYS at SimpleDMVectorCache.v:437
    vlTOPp->v__DOT__controller__DOT__enableReadRespReg 
	= ((~ (IData)(vlTOPp->__Vcellinp__v__reset)) 
	   & (IData)(vlTOPp->v__DOT__controller__DOT__T105));
    // ALWAYS at SimpleDMVectorCache.v:425
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__readMissCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T35) {
	    __Vdly__v__DOT__controller__DOT__readMissCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__readMissCount);
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:493
    vlTOPp->v__DOT__dataMem__DOT__R4 = vlTOPp->v__DOT__dataMem__DOT__T5;
    // ALWAYS at SimpleDMVectorCache.v:430
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__readCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T105) {
	    __Vdly__v__DOT__controller__DOT__readCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__readCount);
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:407
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__writeMissCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T90) {
	    __Vdly__v__DOT__controller__DOT__writeMissCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeMissCount);
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T86) {
		__Vdly__v__DOT__controller__DOT__writeMissCount 
		    = ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeMissCount);
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:414
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__writeCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T90) {
	    __Vdly__v__DOT__controller__DOT__writeCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T77) {
		__Vdly__v__DOT__controller__DOT__writeCount 
		    = ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
	    } else {
		if (vlTOPp->v__DOT__controller__DOT__T86) {
		    __Vdly__v__DOT__controller__DOT__writeCount 
			= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
		} else {
		    if (vlTOPp->v__DOT__controller__DOT__T73) {
			__Vdly__v__DOT__controller__DOT__writeCount 
			    = ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
		    }
		}
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:435
    vlTOPp->v__DOT__controller__DOT__prevReadRequestReg 
	= vlTOPp->__Vcellinp__v__io_readPort_readReq_bits;
    // ALWAYS at SimpleDMVectorCache.v:489
    if (((IData)(vlTOPp->v__DOT__controller__DOT__T77) 
	 | (IData)(vlTOPp->v__DOT__controller__DOT__T73))) {
	__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v0 
	    = vlTOPp->__Vcellinp__v__io_writePort_writeData;
	__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0 = 1;
	__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v0 
	    = (0x3fff & vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits);
    }
    if (vlTOPp->v__DOT__controller__DOT__T62) {
	__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v1 
	    = vlTOPp->__Vcellinp__v__io_memRead_memResp_bits;
	__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1 = 1;
	__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v1 
	    = vlTOPp->v__DOT__controller__DOT__T81;
    }
    // ALWAYS at SimpleDMVectorCache.v:396
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__initCtr = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T30) {
	    __Vdly__v__DOT__controller__DOT__initCtr = 0;
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T20) {
		__Vdly__v__DOT__controller__DOT__initCtr 
		    = (0x3fff & ((IData)(1) + (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)));
	    } else {
		if (vlTOPp->v__DOT__controller__DOT__T26) {
		    __Vdly__v__DOT__controller__DOT__initCtr 
			= (0x3fff & ((IData)(1) + (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)));
		} else {
		    if ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state))) {
			__Vdly__v__DOT__controller__DOT__initCtr 
			    = (0x3fff & ((IData)(1) 
					 + (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)));
		    }
		}
	    }
	}
    }
    // ALWAYS at SimpleDMVectorCache.v:537
    if (((IData)(vlTOPp->v__DOT__controller__DOT__T62) 
	 | (0 == (IData)(vlTOPp->v__DOT__controller__DOT__state)))) {
	__Vdlyvval__v__DOT__tagMem__DOT__tagStorage__v0 
	    = ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state))
	        ? 0 : (1 | (0x7fe & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
				     >> 0xd))));
	__Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0 = 1;
	__Vdlyvdim0__v__DOT__tagMem__DOT__tagStorage__v0 
	    = vlTOPp->v__DOT__controller__DOT__T69;
    }
    // ALWAYS at SimpleDMVectorCache.v:375
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__state = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T62) {
	    __Vdly__v__DOT__controller__DOT__state = 1;
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T57) {
		__Vdly__v__DOT__controller__DOT__state = 5;
	    } else {
		if (vlTOPp->v__DOT__controller__DOT__T53) {
		    __Vdly__v__DOT__controller__DOT__state = 4;
		} else {
		    if (((IData)(vlTOPp->v__DOT__controller__DOT__T49) 
			 & (~ (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid)))) {
			__Vdly__v__DOT__controller__DOT__state = 3;
		    } else {
			if (vlTOPp->v__DOT__controller__DOT__T35) {
			    __Vdly__v__DOT__controller__DOT__state = 2;
			} else {
			    if (vlTOPp->v__DOT__controller__DOT__T30) {
				__Vdly__v__DOT__controller__DOT__state = 6;
			    } else {
				if (((IData)(vlTOPp->v__DOT__controller__DOT__T20) 
				     & (0 == (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)))) {
				    __Vdly__v__DOT__controller__DOT__state = 1;
				} else {
				    if (vlTOPp->v__DOT__controller__DOT__T26) {
					__Vdly__v__DOT__controller__DOT__state = 7;
				    } else {
					if (((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					     & (0x3fff 
						== (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)))) {
					    __Vdly__v__DOT__controller__DOT__state = 1;
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    vlTOPp->v__DOT__controller__DOT__readMissCount 
	= __Vdly__v__DOT__controller__DOT__readMissCount;
    vlTOPp->v__DOT__controller__DOT__readCount = __Vdly__v__DOT__controller__DOT__readCount;
    vlTOPp->v__DOT__controller__DOT__writeMissCount 
	= __Vdly__v__DOT__controller__DOT__writeMissCount;
    vlTOPp->v__DOT__controller__DOT__writeCount = __Vdly__v__DOT__controller__DOT__writeCount;
    // ALWAYSPOST at SimpleDMVectorCache.v:490
    if (__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0) {
	vlTOPp->v__DOT__dataMem__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v0)] 
	    = __Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v0;
    }
    if (__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1) {
	vlTOPp->v__DOT__dataMem__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v1)] 
	    = __Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v1;
    }
    // ALWAYSPOST at SimpleDMVectorCache.v:539
    if (__Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0) {
	vlTOPp->v__DOT__tagMem__DOT__tagStorage[(IData)(__Vdlyvdim0__v__DOT__tagMem__DOT__tagStorage__v0)] 
	    = __Vdlyvval__v__DOT__tagMem__DOT__tagStorage__v0;
    }
    vlTOPp->v__DOT__controller__DOT__initCtr = __Vdly__v__DOT__controller__DOT__initCtr;
    vlTOPp->v__DOT__controller__DOT__state = __Vdly__v__DOT__controller__DOT__state;
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readResp_valid, vlTOPp->v__DOT__controller__DOT__enableReadRespReg);
    VL_ASSIGN_SII(32,vlTOPp->io_readMissCount, vlTOPp->v__DOT__controller__DOT__readMissCount);
    VL_ASSIGN_SQQ(64,vlTOPp->io_readPort_readResp_bits, vlTOPp->v__DOT__dataMem__DOT__R4);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__controller__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeMissCount, vlTOPp->v__DOT__controller__DOT__writeMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeCount, vlTOPp->v__DOT__controller__DOT__writeCount);
    VL_ASSIGN_SII(24,vlTOPp->io_readPort_readRespInd, vlTOPp->v__DOT__controller__DOT__prevReadRequestReg);
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T26 = ((0 != (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    & (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T24 = ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    | (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VSimpleDMVectorCache::_combo__TOP__4(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__4\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memRead_memResp_bits, vlTOPp->io_memRead_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writePort_writeData, vlTOPp->io_writePort_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits, vlTOPp->io_writePort_writeReq_bits);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_readPort_readReq_bits, vlTOPp->io_readPort_readReq_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid, vlTOPp->io_writePort_writeReq_valid);
}

void VSimpleDMVectorCache::_settle__TOP__5(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__5\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memRead_memResp_bits, vlTOPp->io_memRead_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writePort_writeData, vlTOPp->io_writePort_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits, vlTOPp->io_writePort_writeReq_bits);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_readPort_readReq_bits, vlTOPp->io_readPort_readReq_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid, vlTOPp->io_writePort_writeReq_valid);
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readResp_valid, vlTOPp->v__DOT__controller__DOT__enableReadRespReg);
    VL_ASSIGN_SII(32,vlTOPp->io_readMissCount, vlTOPp->v__DOT__controller__DOT__readMissCount);
    VL_ASSIGN_SQQ(64,vlTOPp->io_readPort_readResp_bits, vlTOPp->v__DOT__dataMem__DOT__R4);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__controller__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeMissCount, vlTOPp->v__DOT__controller__DOT__writeMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeCount, vlTOPp->v__DOT__controller__DOT__writeCount);
    VL_ASSIGN_SII(24,vlTOPp->io_readPort_readRespInd, vlTOPp->v__DOT__controller__DOT__prevReadRequestReg);
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T26 = ((0 != (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    & (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T24 = ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    | (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__tagMem__DOT__T0 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(0x3fff & vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)];
    VL_ASSIGN_SII(24,vlTOPp->io_memRead_memReq_bits, vlTOPp->__Vcellinp__v__io_readPort_readReq_bits);
    vlTOPp->v__DOT__controller__DOT__T21 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T24)) 
					    & (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T34 = ((IData)(vlTOPp->v__DOT__controller__DOT__T24) 
					    | (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VSimpleDMVectorCache::_combo__TOP__6(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__6\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__tagMem__DOT__T0 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(0x3fff & vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)];
    VL_ASSIGN_SII(24,vlTOPp->io_memRead_memReq_bits, vlTOPp->__Vcellinp__v__io_readPort_readReq_bits);
    vlTOPp->v__DOT__controller__DOT__T78 = (((0x3ff 
					      & (vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits 
						 >> 0xe)) 
					     == (0x3ff 
						 & (IData)(
							   ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T0)) 
							    >> 1)))) 
					    & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T0)));
}

void VSimpleDMVectorCache::_sequent__TOP__7(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__7\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T21 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T24)) 
					    & (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T34 = ((IData)(vlTOPp->v__DOT__controller__DOT__T24) 
					    | (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T31 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T34)) 
					    & (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T52 = ((IData)(vlTOPp->v__DOT__controller__DOT__T34) 
					    | (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VSimpleDMVectorCache::_settle__TOP__8(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__8\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T78 = (((0x3ff 
					      & (vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits 
						 >> 0xe)) 
					     == (0x3ff 
						 & (IData)(
							   ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T0)) 
							    >> 1)))) 
					    & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T0)));
    vlTOPp->v__DOT__controller__DOT__T81 = (0x3fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T21)
					        ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
					        : ((IData)(vlTOPp->v__DOT__controller__DOT__T26)
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T20 = ((IData)(vlTOPp->v__DOT__controller__DOT__T21) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__controller__DOT__T31 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T34)) 
					    & (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T52 = ((IData)(vlTOPp->v__DOT__controller__DOT__T34) 
					    | (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T30 = ((IData)(vlTOPp->v__DOT__controller__DOT__T31) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_flushCache));
    vlTOPp->v__DOT__controller__DOT__T45 = ((IData)(vlTOPp->v__DOT__controller__DOT__T31) 
					    & (~ (IData)(vlTOPp->__Vcellinp__v__io_flushCache)));
    vlTOPp->v__DOT__controller__DOT__T49 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T52)) 
					    & (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T56 = ((IData)(vlTOPp->v__DOT__controller__DOT__T52) 
					    | (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VSimpleDMVectorCache::_combo__TOP__9(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__9\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T81 = (0x3fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T21)
					        ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
					        : ((IData)(vlTOPp->v__DOT__controller__DOT__T26)
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T20 = ((IData)(vlTOPp->v__DOT__controller__DOT__T21) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__controller__DOT__T30 = ((IData)(vlTOPp->v__DOT__controller__DOT__T31) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_flushCache));
    vlTOPp->v__DOT__controller__DOT__T45 = ((IData)(vlTOPp->v__DOT__controller__DOT__T31) 
					    & (~ (IData)(vlTOPp->__Vcellinp__v__io_flushCache)));
    vlTOPp->v__DOT__dataMem__DOT__T5 = vlTOPp->v__DOT__dataMem__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__controller__DOT__T81)];
    vlTOPp->v__DOT__controller__DOT__T69 = (0x3fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T20)
					        ? ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
						   - (IData)(1))
					        : (
						   (0 
						    == (IData)(vlTOPp->v__DOT__controller__DOT__state))
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T44 = ((IData)(vlTOPp->v__DOT__controller__DOT__T45) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readReq_valid));
    vlTOPp->v__DOT__controller__DOT__T76 = ((IData)(vlTOPp->v__DOT__controller__DOT__T45) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
}

void VSimpleDMVectorCache::_sequent__TOP__10(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__10\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T49 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T52)) 
					    & (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T56 = ((IData)(vlTOPp->v__DOT__controller__DOT__T52) 
					    | (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T53 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T56)) 
					    & (3 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T61 = ((IData)(vlTOPp->v__DOT__controller__DOT__T56) 
					    | (3 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VSimpleDMVectorCache::_settle__TOP__11(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__11\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__dataMem__DOT__T5 = vlTOPp->v__DOT__dataMem__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__controller__DOT__T81)];
    vlTOPp->v__DOT__controller__DOT__T69 = (0x3fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T20)
					        ? ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
						   - (IData)(1))
					        : (
						   (0 
						    == (IData)(vlTOPp->v__DOT__controller__DOT__state))
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T44 = ((IData)(vlTOPp->v__DOT__controller__DOT__T45) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readReq_valid));
    vlTOPp->v__DOT__controller__DOT__T76 = ((IData)(vlTOPp->v__DOT__controller__DOT__T45) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
    VL_ASSIGN_SII(1,vlTOPp->io_writePort_writeReq_ready, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T49)
		    ? (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T45) 
		       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready))));
    vlTOPp->v__DOT__controller__DOT__T80 = ((IData)(vlTOPp->v__DOT__controller__DOT__T49) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
    vlTOPp->v__DOT__controller__DOT__T53 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T56)) 
					    & (3 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T61 = ((IData)(vlTOPp->v__DOT__controller__DOT__T56) 
					    | (3 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__tagMem__DOT__T2 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(IData)(vlTOPp->v__DOT__controller__DOT__T69)];
    vlTOPp->v__DOT__controller__DOT__T73 = ((IData)(vlTOPp->v__DOT__controller__DOT__T76) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T78));
    vlTOPp->v__DOT__controller__DOT__T86 = ((IData)(vlTOPp->v__DOT__controller__DOT__T76) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T78)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memReq_valid, vlTOPp->v__DOT__controller__DOT__T53);
    vlTOPp->v__DOT__controller__DOT__T63 = ((~ ((IData)(vlTOPp->v__DOT__controller__DOT__T61) 
						| (4 
						   == (IData)(vlTOPp->v__DOT__controller__DOT__state)))) 
					    & (5 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T57 = (((~ (IData)(vlTOPp->v__DOT__controller__DOT__T61)) 
					     & (4 == (IData)(vlTOPp->v__DOT__controller__DOT__state))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
}

void VSimpleDMVectorCache::_combo__TOP__12(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__12\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_writePort_writeReq_ready, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T49)
		    ? (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T45) 
		       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready))));
    vlTOPp->v__DOT__controller__DOT__T80 = ((IData)(vlTOPp->v__DOT__controller__DOT__T49) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
    vlTOPp->v__DOT__tagMem__DOT__T2 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(IData)(vlTOPp->v__DOT__controller__DOT__T69)];
    vlTOPp->v__DOT__controller__DOT__T73 = ((IData)(vlTOPp->v__DOT__controller__DOT__T76) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T78));
    vlTOPp->v__DOT__controller__DOT__T86 = ((IData)(vlTOPp->v__DOT__controller__DOT__T76) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T78)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    vlTOPp->v__DOT__controller__DOT__T57 = (((~ (IData)(vlTOPp->v__DOT__controller__DOT__T61)) 
					     & (4 == (IData)(vlTOPp->v__DOT__controller__DOT__state))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__controller__DOT__T77 = ((IData)(vlTOPp->v__DOT__controller__DOT__T80) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T78));
    vlTOPp->v__DOT__controller__DOT__T90 = ((IData)(vlTOPp->v__DOT__controller__DOT__T80) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T78)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    vlTOPp->v__DOT__controller__DOT__T41 = ((((0x3ff 
					       & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						  >> 0xe)) 
					      == (0x3ff 
						  & (IData)(
							    ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							     >> 1)))) 
					     & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readResp_ready));
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWrite_memWriteData, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T57)
		    ? vlTOPp->v__DOT__dataMem__DOT__R4
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T20)
		        ? vlTOPp->v__DOT__dataMem__DOT__R4
		        : vlTOPp->__Vcellinp__v__io_writePort_writeData)));
    VL_ASSIGN_SII(24,vlTOPp->io_memWrite_memWriteReq_bits, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T57)
		    ? ((0xffc000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
					     >> 1)) 
				    << 0xe)) | (0x3fff 
						& vlTOPp->__Vcellinp__v__io_readPort_readReq_bits))
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T20)
		        ? ((0xffc000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
						 >> 1)) 
					<< 0xe)) | 
			   (0x3fff & ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
				      - (IData)(1))))
		        : vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)));
}

void VSimpleDMVectorCache::_sequent__TOP__13(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_sequent__TOP__13\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memReq_valid, vlTOPp->v__DOT__controller__DOT__T53);
    vlTOPp->v__DOT__controller__DOT__T63 = ((~ ((IData)(vlTOPp->v__DOT__controller__DOT__T61) 
						| (4 
						   == (IData)(vlTOPp->v__DOT__controller__DOT__state)))) 
					    & (5 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memResp_ready, vlTOPp->v__DOT__controller__DOT__T63);
}

void VSimpleDMVectorCache::_settle__TOP__14(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__14\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T77 = ((IData)(vlTOPp->v__DOT__controller__DOT__T80) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T78));
    vlTOPp->v__DOT__controller__DOT__T90 = ((IData)(vlTOPp->v__DOT__controller__DOT__T80) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T78)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    vlTOPp->v__DOT__controller__DOT__T41 = ((((0x3ff 
					       & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						  >> 0xe)) 
					      == (0x3ff 
						  & (IData)(
							    ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							     >> 1)))) 
					     & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readResp_ready));
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWrite_memWriteData, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T57)
		    ? vlTOPp->v__DOT__dataMem__DOT__R4
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T20)
		        ? vlTOPp->v__DOT__dataMem__DOT__R4
		        : vlTOPp->__Vcellinp__v__io_writePort_writeData)));
    VL_ASSIGN_SII(24,vlTOPp->io_memWrite_memWriteReq_bits, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T57)
		    ? ((0xffc000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
					     >> 1)) 
				    << 0xe)) | (0x3fff 
						& vlTOPp->__Vcellinp__v__io_readPort_readReq_bits))
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T20)
		        ? ((0xffc000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
						 >> 1)) 
					<< 0xe)) | 
			   (0x3fff & ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
				      - (IData)(1))))
		        : vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)));
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memResp_ready, vlTOPp->v__DOT__controller__DOT__T63);
    vlTOPp->v__DOT__controller__DOT__T62 = ((IData)(vlTOPp->v__DOT__controller__DOT__T63) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memRead_memResp_valid));
    VL_ASSIGN_SII(1,vlTOPp->io_memWrite_memWriteReq_valid, 
		  (1 & ((IData)(vlTOPp->v__DOT__controller__DOT__T57)
			 ? (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))
			 : ((IData)(vlTOPp->v__DOT__controller__DOT__T90) 
			    | ((IData)(vlTOPp->v__DOT__controller__DOT__T86) 
			       | ((IData)(vlTOPp->v__DOT__controller__DOT__T20) 
				  & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))))));
    vlTOPp->v__DOT__controller__DOT__T35 = ((IData)(vlTOPp->v__DOT__controller__DOT__T44) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T41)) 
					       & (((0x3ff 
						    & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						       >> 0xe)) 
						   != 
						   (0x3ff 
						    & (IData)(
							      ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							       >> 1)))) 
						  | (~ (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))));
    vlTOPp->v__DOT__controller__DOT__T105 = ((IData)(vlTOPp->v__DOT__controller__DOT__T44) 
					     & (IData)(vlTOPp->v__DOT__controller__DOT__T41));
}

void VSimpleDMVectorCache::_combo__TOP__15(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_combo__TOP__15\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T62 = ((IData)(vlTOPp->v__DOT__controller__DOT__T63) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memRead_memResp_valid));
    VL_ASSIGN_SII(1,vlTOPp->io_memWrite_memWriteReq_valid, 
		  (1 & ((IData)(vlTOPp->v__DOT__controller__DOT__T57)
			 ? (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))
			 : ((IData)(vlTOPp->v__DOT__controller__DOT__T90) 
			    | ((IData)(vlTOPp->v__DOT__controller__DOT__T86) 
			       | ((IData)(vlTOPp->v__DOT__controller__DOT__T20) 
				  & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))))));
    vlTOPp->v__DOT__controller__DOT__T35 = ((IData)(vlTOPp->v__DOT__controller__DOT__T44) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T41)) 
					       & (((0x3ff 
						    & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						       >> 0xe)) 
						   != 
						   (0x3ff 
						    & (IData)(
							      ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							       >> 1)))) 
						  | (~ (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))));
    vlTOPp->v__DOT__controller__DOT__T105 = ((IData)(vlTOPp->v__DOT__controller__DOT__T44) 
					     & (IData)(vlTOPp->v__DOT__controller__DOT__T41));
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readReq_ready, vlTOPp->v__DOT__controller__DOT__T105);
}

void VSimpleDMVectorCache::_settle__TOP__16(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_settle__TOP__16\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readReq_ready, vlTOPp->v__DOT__controller__DOT__T105);
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
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__10(vlSymsp);
    }
    vlTOPp->_combo__TOP__12(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__13(vlSymsp);
    }
    vlTOPp->_combo__TOP__15(vlSymsp);
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
    vlTOPp->_settle__TOP__11(vlSymsp);
    vlTOPp->_settle__TOP__14(vlSymsp);
    vlTOPp->_settle__TOP__16(vlSymsp);
}

IData VSimpleDMVectorCache::_change_request(VSimpleDMVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleDMVectorCache::_change_request\n"); );
    VSimpleDMVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
