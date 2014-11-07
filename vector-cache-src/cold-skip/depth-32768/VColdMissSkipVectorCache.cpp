// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VColdMissSkipVectorCache.h for the primary calling header

#include "VColdMissSkipVectorCache.h" // For This
#include "VColdMissSkipVectorCache__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(VColdMissSkipVectorCache)
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
      io_coldSkipCount("io_coldSkipCount"), io_readPort_readResp_bits("io_readPort_readResp_bits"), 
      io_writePort_writeData("io_writePort_writeData"), 
      io_memRead_memResp_bits("io_memRead_memResp_bits"), 
      io_memWrite_memWriteData("io_memWrite_memWriteData")
#endif
 {
    VColdMissSkipVectorCache__Syms* __restrict vlSymsp = __VlSymsp = new VColdMissSkipVectorCache__Syms(this, name());
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
    __Vcellinp__v__io_readPort_readReq_bits = VL_RAND_RESET_I(25);
    __Vcellinp__v__io_readPort_readReq_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__reset = VL_RAND_RESET_I(1);
    __Vcellinp__v__clk = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__state = VL_RAND_RESET_I(4);
    v__DOT__controller__DOT__initCtr = VL_RAND_RESET_I(15);
    v__DOT__controller__DOT__T22 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T23 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T26 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T28 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T32 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T33 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T36 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T37 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T43 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T46 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T47 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T51 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T54 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T56 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T60 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T61 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T64 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T66 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T67 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T69 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T70 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T76 = VL_RAND_RESET_I(15);
    v__DOT__controller__DOT__T80 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T83 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T84 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T85 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T87 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T90 = VL_RAND_RESET_I(15);
    v__DOT__controller__DOT__coldSkipCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__writeMissCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__T97 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__T101 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__writeCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__readMissCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__readCount = VL_RAND_RESET_I(32);
    v__DOT__controller__DOT__T116 = VL_RAND_RESET_I(1);
    v__DOT__controller__DOT__prevReadRequestReg = VL_RAND_RESET_I(24);
    v__DOT__controller__DOT__enableReadRespReg = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<32768; ++__Vi0) {
	    v__DOT__dataMem__DOT__cacheLines[__Vi0] = VL_RAND_RESET_Q(64);
    }}
    v__DOT__dataMem__DOT__R4 = VL_RAND_RESET_Q(64);
    v__DOT__dataMem__DOT__T5 = VL_RAND_RESET_Q(64);
    v__DOT__tagMem__DOT__T0 = VL_RAND_RESET_I(10);
    { int __Vi0=0; for (; __Vi0<32768; ++__Vi0) {
	    v__DOT__tagMem__DOT__tagStorage[__Vi0] = VL_RAND_RESET_I(10);
    }}
    v__DOT__tagMem__DOT__T2 = VL_RAND_RESET_I(10);
    __Vclklast__TOP____Vcellinp__v__clk = VL_RAND_RESET_I(1);
}

void VColdMissSkipVectorCache::__Vconfigure(VColdMissSkipVectorCache__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

VColdMissSkipVectorCache::~VColdMissSkipVectorCache() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void VColdMissSkipVectorCache::eval() {
    VColdMissSkipVectorCache__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate VColdMissSkipVectorCache::eval\n"); );
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

void VColdMissSkipVectorCache::_eval_initial_loop(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
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

void VColdMissSkipVectorCache::_combo__TOP__1(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_combo__TOP__1\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memRead_memResp_valid, vlTOPp->io_memRead_memResp_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readPort_readReq_valid, vlTOPp->io_readPort_readReq_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_readPort_readResp_ready, vlTOPp->io_readPort_readResp_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_flushCache, vlTOPp->io_flushCache);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready, vlTOPp->io_memWrite_memWriteReq_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VColdMissSkipVectorCache::_sequent__TOP__3(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_sequent__TOP__3\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__controller__DOT__state,3,0);
    VL_SIG8(__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1,0,0);
    VL_SIG8(__Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0,0,0);
    VL_SIG16(__Vdly__v__DOT__controller__DOT__initCtr,14,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v0,14,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v1,14,0);
    VL_SIG16(__Vdlyvdim0__v__DOT__tagMem__DOT__tagStorage__v0,14,0);
    VL_SIG16(__Vdlyvval__v__DOT__tagMem__DOT__tagStorage__v0,9,0);
    //char	__VpadToAlign38[2];
    VL_SIG(__Vdly__v__DOT__controller__DOT__coldSkipCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__writeMissCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__writeCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__readMissCount,31,0);
    VL_SIG(__Vdly__v__DOT__controller__DOT__readCount,31,0);
    //char	__VpadToAlign60[4];
    VL_SIG64(__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v0,63,0);
    VL_SIG64(__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v1,63,0);
    // Body
    __Vdly__v__DOT__controller__DOT__coldSkipCount 
	= vlTOPp->v__DOT__controller__DOT__coldSkipCount;
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
    // ALWAYS at ColdMissSkipVectorCache.v:476
    vlTOPp->v__DOT__controller__DOT__enableReadRespReg 
	= ((~ (IData)(vlTOPp->__Vcellinp__v__reset)) 
	   & (IData)(vlTOPp->v__DOT__controller__DOT__T116));
    // ALWAYS at ColdMissSkipVectorCache.v:532
    vlTOPp->v__DOT__dataMem__DOT__R4 = vlTOPp->v__DOT__dataMem__DOT__T5;
    // ALWAYS at ColdMissSkipVectorCache.v:441
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__coldSkipCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T67) {
	    __Vdly__v__DOT__controller__DOT__coldSkipCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__coldSkipCount);
	}
    }
    // ALWAYS at ColdMissSkipVectorCache.v:464
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__readMissCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T37) {
	    __Vdly__v__DOT__controller__DOT__readMissCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__readMissCount);
	}
    }
    // ALWAYS at ColdMissSkipVectorCache.v:469
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__readCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T116) {
	    __Vdly__v__DOT__controller__DOT__readCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__readCount);
	}
    }
    // ALWAYS at ColdMissSkipVectorCache.v:446
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__writeMissCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T101) {
	    __Vdly__v__DOT__controller__DOT__writeMissCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeMissCount);
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T97) {
		__Vdly__v__DOT__controller__DOT__writeMissCount 
		    = ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeMissCount);
	    }
	}
    }
    // ALWAYS at ColdMissSkipVectorCache.v:453
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__writeCount = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T101) {
	    __Vdly__v__DOT__controller__DOT__writeCount 
		= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T84) {
		__Vdly__v__DOT__controller__DOT__writeCount 
		    = ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
	    } else {
		if (vlTOPp->v__DOT__controller__DOT__T97) {
		    __Vdly__v__DOT__controller__DOT__writeCount 
			= ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
		} else {
		    if (vlTOPp->v__DOT__controller__DOT__T80) {
			__Vdly__v__DOT__controller__DOT__writeCount 
			    = ((IData)(1) + vlTOPp->v__DOT__controller__DOT__writeCount);
		    }
		}
	    }
	}
    }
    // ALWAYS at ColdMissSkipVectorCache.v:474
    vlTOPp->v__DOT__controller__DOT__prevReadRequestReg 
	= (0xffffff & vlTOPp->__Vcellinp__v__io_readPort_readReq_bits);
    // ALWAYS at ColdMissSkipVectorCache.v:528
    if (((IData)(vlTOPp->v__DOT__controller__DOT__T84) 
	 | (IData)(vlTOPp->v__DOT__controller__DOT__T80))) {
	__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v0 
	    = vlTOPp->__Vcellinp__v__io_writePort_writeData;
	__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0 = 1;
	__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v0 
	    = (0x7fff & vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits);
    }
    if (((IData)(vlTOPp->v__DOT__controller__DOT__T69) 
	 | (IData)(vlTOPp->v__DOT__controller__DOT__T67))) {
	__Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v1 
	    = ((IData)(vlTOPp->v__DOT__controller__DOT__T67)
	        ? VL_ULL(0) : vlTOPp->__Vcellinp__v__io_memRead_memResp_bits);
	__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1 = 1;
	__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v1 
	    = vlTOPp->v__DOT__controller__DOT__T90;
    }
    // ALWAYS at ColdMissSkipVectorCache.v:430
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__initCtr = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T32) {
	    __Vdly__v__DOT__controller__DOT__initCtr = 0;
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T22) {
		__Vdly__v__DOT__controller__DOT__initCtr 
		    = (0x7fff & ((IData)(1) + (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)));
	    } else {
		if (vlTOPp->v__DOT__controller__DOT__T28) {
		    __Vdly__v__DOT__controller__DOT__initCtr 
			= (0x7fff & ((IData)(1) + (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)));
		} else {
		    if ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state))) {
			__Vdly__v__DOT__controller__DOT__initCtr 
			    = (0x7fff & ((IData)(1) 
					 + (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)));
		    }
		}
	    }
	}
    }
    // ALWAYS at ColdMissSkipVectorCache.v:576
    if (((IData)(vlTOPp->v__DOT__controller__DOT__T69) 
	 | ((IData)(vlTOPp->v__DOT__controller__DOT__T67) 
	    | (0 == (IData)(vlTOPp->v__DOT__controller__DOT__state))))) {
	__Vdlyvval__v__DOT__tagMem__DOT__tagStorage__v0 
	    = ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state))
	        ? 0 : (1 | (0x3fe & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
				     >> 0xe))));
	__Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0 = 1;
	__Vdlyvdim0__v__DOT__tagMem__DOT__tagStorage__v0 
	    = vlTOPp->v__DOT__controller__DOT__T76;
    }
    // ALWAYS at ColdMissSkipVectorCache.v:407
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__controller__DOT__state = 0;
    } else {
	if (vlTOPp->v__DOT__controller__DOT__T69) {
	    __Vdly__v__DOT__controller__DOT__state = 1;
	} else {
	    if (vlTOPp->v__DOT__controller__DOT__T61) {
		__Vdly__v__DOT__controller__DOT__state = 5;
	    } else {
		if (vlTOPp->v__DOT__controller__DOT__T67) {
		    __Vdly__v__DOT__controller__DOT__state = 1;
		} else {
		    if (vlTOPp->v__DOT__controller__DOT__T56) {
			__Vdly__v__DOT__controller__DOT__state 
			    = ((0x1000000 & vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)
			        ? 8 : 3);
		    } else {
			if (((IData)(vlTOPp->v__DOT__controller__DOT__T51) 
			     & (~ (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid)))) {
			    __Vdly__v__DOT__controller__DOT__state = 4;
			} else {
			    if (vlTOPp->v__DOT__controller__DOT__T37) {
				__Vdly__v__DOT__controller__DOT__state = 2;
			    } else {
				if (vlTOPp->v__DOT__controller__DOT__T32) {
				    __Vdly__v__DOT__controller__DOT__state = 6;
				} else {
				    if (((IData)(vlTOPp->v__DOT__controller__DOT__T22) 
					 & (0 == (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)))) {
					__Vdly__v__DOT__controller__DOT__state = 1;
				    } else {
					if (vlTOPp->v__DOT__controller__DOT__T28) {
					    __Vdly__v__DOT__controller__DOT__state = 7;
					} else {
					    if (((0 
						  == (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
						 & (0x7fff 
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
    }
    vlTOPp->v__DOT__controller__DOT__coldSkipCount 
	= __Vdly__v__DOT__controller__DOT__coldSkipCount;
    vlTOPp->v__DOT__controller__DOT__readMissCount 
	= __Vdly__v__DOT__controller__DOT__readMissCount;
    vlTOPp->v__DOT__controller__DOT__readCount = __Vdly__v__DOT__controller__DOT__readCount;
    vlTOPp->v__DOT__controller__DOT__writeMissCount 
	= __Vdly__v__DOT__controller__DOT__writeMissCount;
    vlTOPp->v__DOT__controller__DOT__writeCount = __Vdly__v__DOT__controller__DOT__writeCount;
    // ALWAYSPOST at ColdMissSkipVectorCache.v:529
    if (__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v0) {
	vlTOPp->v__DOT__dataMem__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v0)] 
	    = __Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v0;
    }
    if (__Vdlyvset__v__DOT__dataMem__DOT__cacheLines__v1) {
	vlTOPp->v__DOT__dataMem__DOT__cacheLines[(IData)(__Vdlyvdim0__v__DOT__dataMem__DOT__cacheLines__v1)] 
	    = __Vdlyvval__v__DOT__dataMem__DOT__cacheLines__v1;
    }
    // ALWAYSPOST at ColdMissSkipVectorCache.v:578
    if (__Vdlyvset__v__DOT__tagMem__DOT__tagStorage__v0) {
	vlTOPp->v__DOT__tagMem__DOT__tagStorage[(IData)(__Vdlyvdim0__v__DOT__tagMem__DOT__tagStorage__v0)] 
	    = __Vdlyvval__v__DOT__tagMem__DOT__tagStorage__v0;
    }
    vlTOPp->v__DOT__controller__DOT__initCtr = __Vdly__v__DOT__controller__DOT__initCtr;
    vlTOPp->v__DOT__controller__DOT__state = __Vdly__v__DOT__controller__DOT__state;
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readResp_valid, vlTOPp->v__DOT__controller__DOT__enableReadRespReg);
    VL_ASSIGN_SQQ(64,vlTOPp->io_readPort_readResp_bits, vlTOPp->v__DOT__dataMem__DOT__R4);
    VL_ASSIGN_SII(32,vlTOPp->io_coldSkipCount, vlTOPp->v__DOT__controller__DOT__coldSkipCount);
    VL_ASSIGN_SII(32,vlTOPp->io_readMissCount, vlTOPp->v__DOT__controller__DOT__readMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__controller__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeMissCount, vlTOPp->v__DOT__controller__DOT__writeMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeCount, vlTOPp->v__DOT__controller__DOT__writeCount);
    VL_ASSIGN_SII(24,vlTOPp->io_readPort_readRespInd, vlTOPp->v__DOT__controller__DOT__prevReadRequestReg);
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T28 = ((0 != (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    & (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T26 = ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    | (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_combo__TOP__4(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_combo__TOP__4\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memRead_memResp_bits, vlTOPp->io_memRead_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writePort_writeData, vlTOPp->io_writePort_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits, vlTOPp->io_writePort_writeReq_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid, vlTOPp->io_writePort_writeReq_valid);
    VL_ASSIGN_ISI(25,vlTOPp->__Vcellinp__v__io_readPort_readReq_bits, vlTOPp->io_readPort_readReq_bits);
}

void VColdMissSkipVectorCache::_settle__TOP__5(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_settle__TOP__5\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_memRead_memResp_bits, vlTOPp->io_memRead_memResp_bits);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__io_writePort_writeData, vlTOPp->io_writePort_writeData);
    VL_ASSIGN_ISI(24,vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits, vlTOPp->io_writePort_writeReq_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid, vlTOPp->io_writePort_writeReq_valid);
    VL_ASSIGN_ISI(25,vlTOPp->__Vcellinp__v__io_readPort_readReq_bits, vlTOPp->io_readPort_readReq_bits);
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readResp_valid, vlTOPp->v__DOT__controller__DOT__enableReadRespReg);
    VL_ASSIGN_SQQ(64,vlTOPp->io_readPort_readResp_bits, vlTOPp->v__DOT__dataMem__DOT__R4);
    VL_ASSIGN_SII(32,vlTOPp->io_coldSkipCount, vlTOPp->v__DOT__controller__DOT__coldSkipCount);
    VL_ASSIGN_SII(32,vlTOPp->io_readMissCount, vlTOPp->v__DOT__controller__DOT__readMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_readCount, vlTOPp->v__DOT__controller__DOT__readCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeMissCount, vlTOPp->v__DOT__controller__DOT__writeMissCount);
    VL_ASSIGN_SII(32,vlTOPp->io_writeCount, vlTOPp->v__DOT__controller__DOT__writeCount);
    VL_ASSIGN_SII(24,vlTOPp->io_readPort_readRespInd, vlTOPp->v__DOT__controller__DOT__prevReadRequestReg);
    VL_ASSIGN_SII(1,vlTOPp->io_cacheActive, (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T28 = ((0 != (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    & (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T26 = ((0 == (IData)(vlTOPp->v__DOT__controller__DOT__state)) 
					    | (6 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__tagMem__DOT__T0 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(0x7fff & vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)];
    VL_ASSIGN_SII(24,vlTOPp->io_memRead_memReq_bits, 
		  (0xffffff & vlTOPp->__Vcellinp__v__io_readPort_readReq_bits));
    vlTOPp->v__DOT__controller__DOT__T23 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T26)) 
					    & (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T36 = ((IData)(vlTOPp->v__DOT__controller__DOT__T26) 
					    | (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_combo__TOP__6(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_combo__TOP__6\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__tagMem__DOT__T0 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(0x7fff & vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)];
    VL_ASSIGN_SII(24,vlTOPp->io_memRead_memReq_bits, 
		  (0xffffff & vlTOPp->__Vcellinp__v__io_readPort_readReq_bits));
    vlTOPp->v__DOT__controller__DOT__T85 = (((0x1ff 
					      & (vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits 
						 >> 0xf)) 
					     == (0x1ff 
						 & (IData)(
							   ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T0)) 
							    >> 1)))) 
					    & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T0)));
}

void VColdMissSkipVectorCache::_sequent__TOP__7(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_sequent__TOP__7\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T23 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T26)) 
					    & (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T36 = ((IData)(vlTOPp->v__DOT__controller__DOT__T26) 
					    | (7 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T33 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T36)) 
					    & (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T54 = ((IData)(vlTOPp->v__DOT__controller__DOT__T36) 
					    | (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_settle__TOP__8(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_settle__TOP__8\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T85 = (((0x1ff 
					      & (vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits 
						 >> 0xf)) 
					     == (0x1ff 
						 & (IData)(
							   ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T0)) 
							    >> 1)))) 
					    & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T0)));
    vlTOPp->v__DOT__controller__DOT__T90 = (0x7fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T23)
					        ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
					        : ((IData)(vlTOPp->v__DOT__controller__DOT__T28)
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T22 = ((IData)(vlTOPp->v__DOT__controller__DOT__T23) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__controller__DOT__T33 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T36)) 
					    & (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T54 = ((IData)(vlTOPp->v__DOT__controller__DOT__T36) 
					    | (1 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T32 = ((IData)(vlTOPp->v__DOT__controller__DOT__T33) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_flushCache));
    vlTOPp->v__DOT__controller__DOT__T47 = ((IData)(vlTOPp->v__DOT__controller__DOT__T33) 
					    & (~ (IData)(vlTOPp->__Vcellinp__v__io_flushCache)));
    vlTOPp->v__DOT__controller__DOT__T51 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T54)) 
					    & (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T60 = ((IData)(vlTOPp->v__DOT__controller__DOT__T54) 
					    | (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_combo__TOP__9(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_combo__TOP__9\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T90 = (0x7fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T23)
					        ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
					        : ((IData)(vlTOPp->v__DOT__controller__DOT__T28)
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T22 = ((IData)(vlTOPp->v__DOT__controller__DOT__T23) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__controller__DOT__T32 = ((IData)(vlTOPp->v__DOT__controller__DOT__T33) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_flushCache));
    vlTOPp->v__DOT__controller__DOT__T47 = ((IData)(vlTOPp->v__DOT__controller__DOT__T33) 
					    & (~ (IData)(vlTOPp->__Vcellinp__v__io_flushCache)));
    vlTOPp->v__DOT__dataMem__DOT__T5 = vlTOPp->v__DOT__dataMem__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__controller__DOT__T90)];
    vlTOPp->v__DOT__controller__DOT__T76 = (0x7fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T22)
					        ? ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
						   - (IData)(1))
					        : (
						   (0 
						    == (IData)(vlTOPp->v__DOT__controller__DOT__state))
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T46 = ((IData)(vlTOPp->v__DOT__controller__DOT__T47) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readReq_valid));
    vlTOPp->v__DOT__controller__DOT__T83 = ((IData)(vlTOPp->v__DOT__controller__DOT__T47) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
}

void VColdMissSkipVectorCache::_sequent__TOP__10(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_sequent__TOP__10\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T51 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T54)) 
					    & (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T60 = ((IData)(vlTOPp->v__DOT__controller__DOT__T54) 
					    | (2 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T66 = ((IData)(vlTOPp->v__DOT__controller__DOT__T60) 
					    | (4 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_settle__TOP__11(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_settle__TOP__11\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__dataMem__DOT__T5 = vlTOPp->v__DOT__dataMem__DOT__cacheLines
	[(IData)(vlTOPp->v__DOT__controller__DOT__T90)];
    vlTOPp->v__DOT__controller__DOT__T76 = (0x7fff 
					    & ((IData)(vlTOPp->v__DOT__controller__DOT__T22)
					        ? ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
						   - (IData)(1))
					        : (
						   (0 
						    == (IData)(vlTOPp->v__DOT__controller__DOT__state))
						    ? (IData)(vlTOPp->v__DOT__controller__DOT__initCtr)
						    : vlTOPp->__Vcellinp__v__io_readPort_readReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T46 = ((IData)(vlTOPp->v__DOT__controller__DOT__T47) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readReq_valid));
    vlTOPp->v__DOT__controller__DOT__T83 = ((IData)(vlTOPp->v__DOT__controller__DOT__T47) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
    VL_ASSIGN_SII(1,vlTOPp->io_writePort_writeReq_ready, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T51)
		    ? (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T47) 
		       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready))));
    vlTOPp->v__DOT__controller__DOT__T87 = ((IData)(vlTOPp->v__DOT__controller__DOT__T51) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
    vlTOPp->v__DOT__controller__DOT__T56 = (((~ (IData)(vlTOPp->v__DOT__controller__DOT__T60)) 
					     & (4 == (IData)(vlTOPp->v__DOT__controller__DOT__state))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__controller__DOT__T66 = ((IData)(vlTOPp->v__DOT__controller__DOT__T60) 
					    | (4 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__tagMem__DOT__T2 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(IData)(vlTOPp->v__DOT__controller__DOT__T76)];
    vlTOPp->v__DOT__controller__DOT__T80 = ((IData)(vlTOPp->v__DOT__controller__DOT__T83) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T85));
    vlTOPp->v__DOT__controller__DOT__T97 = ((IData)(vlTOPp->v__DOT__controller__DOT__T83) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T85)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    vlTOPp->v__DOT__controller__DOT__T67 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T66)) 
					    & (8 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T64 = ((IData)(vlTOPp->v__DOT__controller__DOT__T66) 
					    | (8 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_combo__TOP__12(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_combo__TOP__12\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_writePort_writeReq_ready, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T51)
		    ? (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T47) 
		       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready))));
    vlTOPp->v__DOT__controller__DOT__T87 = ((IData)(vlTOPp->v__DOT__controller__DOT__T51) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_writePort_writeReq_valid));
    vlTOPp->v__DOT__controller__DOT__T56 = (((~ (IData)(vlTOPp->v__DOT__controller__DOT__T60)) 
					     & (4 == (IData)(vlTOPp->v__DOT__controller__DOT__state))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready));
    vlTOPp->v__DOT__tagMem__DOT__T2 = (IData)(vlTOPp->v__DOT__tagMem__DOT__tagStorage)
	[(IData)(vlTOPp->v__DOT__controller__DOT__T76)];
    vlTOPp->v__DOT__controller__DOT__T80 = ((IData)(vlTOPp->v__DOT__controller__DOT__T83) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T85));
    vlTOPp->v__DOT__controller__DOT__T97 = ((IData)(vlTOPp->v__DOT__controller__DOT__T83) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T85)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    vlTOPp->v__DOT__controller__DOT__T84 = ((IData)(vlTOPp->v__DOT__controller__DOT__T87) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T85));
    vlTOPp->v__DOT__controller__DOT__T101 = ((IData)(vlTOPp->v__DOT__controller__DOT__T87) 
					     & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T85)) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWrite_memWriteData, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T56)
		    ? vlTOPp->v__DOT__dataMem__DOT__R4
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T22)
		        ? vlTOPp->v__DOT__dataMem__DOT__R4
		        : vlTOPp->__Vcellinp__v__io_writePort_writeData)));
    VL_ASSIGN_SII(24,vlTOPp->io_memWrite_memWriteReq_bits, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T56)
		    ? ((0xff8000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
					     >> 1)) 
				    << 0xf)) | (0x7fff 
						& vlTOPp->__Vcellinp__v__io_readPort_readReq_bits))
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T22)
		        ? ((0xff8000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
						 >> 1)) 
					<< 0xf)) | 
			   (0x7fff & ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
				      - (IData)(1))))
		        : vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T43 = ((((0x1ff 
					       & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						  >> 0xf)) 
					      == (0x1ff 
						  & (IData)(
							    ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							     >> 1)))) 
					     & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readResp_ready));
}

void VColdMissSkipVectorCache::_sequent__TOP__13(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_sequent__TOP__13\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T67 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T66)) 
					    & (8 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T64 = ((IData)(vlTOPp->v__DOT__controller__DOT__T66) 
					    | (8 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T61 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T64)) 
					    & (3 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T70 = ((~ ((IData)(vlTOPp->v__DOT__controller__DOT__T64) 
						| (3 
						   == (IData)(vlTOPp->v__DOT__controller__DOT__state)))) 
					    & (5 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
}

void VColdMissSkipVectorCache::_settle__TOP__14(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_settle__TOP__14\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->v__DOT__controller__DOT__T84 = ((IData)(vlTOPp->v__DOT__controller__DOT__T87) 
					    & (IData)(vlTOPp->v__DOT__controller__DOT__T85));
    vlTOPp->v__DOT__controller__DOT__T101 = ((IData)(vlTOPp->v__DOT__controller__DOT__T87) 
					     & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T85)) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memWrite_memWriteReq_ready)));
    VL_ASSIGN_SQQ(64,vlTOPp->io_memWrite_memWriteData, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T56)
		    ? vlTOPp->v__DOT__dataMem__DOT__R4
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T22)
		        ? vlTOPp->v__DOT__dataMem__DOT__R4
		        : vlTOPp->__Vcellinp__v__io_writePort_writeData)));
    VL_ASSIGN_SII(24,vlTOPp->io_memWrite_memWriteReq_bits, 
		  ((IData)(vlTOPp->v__DOT__controller__DOT__T56)
		    ? ((0xff8000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
					     >> 1)) 
				    << 0xf)) | (0x7fff 
						& vlTOPp->__Vcellinp__v__io_readPort_readReq_bits))
		    : ((IData)(vlTOPp->v__DOT__controller__DOT__T22)
		        ? ((0xff8000 & ((IData)(((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
						 >> 1)) 
					<< 0xf)) | 
			   (0x7fff & ((IData)(vlTOPp->v__DOT__controller__DOT__initCtr) 
				      - (IData)(1))))
		        : vlTOPp->__Vcellinp__v__io_writePort_writeReq_bits)));
    vlTOPp->v__DOT__controller__DOT__T43 = ((((0x1ff 
					       & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						  >> 0xf)) 
					      == (0x1ff 
						  & (IData)(
							    ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							     >> 1)))) 
					     & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_readPort_readResp_ready));
    vlTOPp->v__DOT__controller__DOT__T61 = ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T64)) 
					    & (3 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    vlTOPp->v__DOT__controller__DOT__T70 = ((~ ((IData)(vlTOPp->v__DOT__controller__DOT__T64) 
						| (3 
						   == (IData)(vlTOPp->v__DOT__controller__DOT__state)))) 
					    & (5 == (IData)(vlTOPp->v__DOT__controller__DOT__state)));
    VL_ASSIGN_SII(1,vlTOPp->io_memWrite_memWriteReq_valid, 
		  (1 & ((IData)(vlTOPp->v__DOT__controller__DOT__T56)
			 ? (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))
			 : ((IData)(vlTOPp->v__DOT__controller__DOT__T101) 
			    | ((IData)(vlTOPp->v__DOT__controller__DOT__T97) 
			       | ((IData)(vlTOPp->v__DOT__controller__DOT__T22) 
				  & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))))));
    vlTOPp->v__DOT__controller__DOT__T37 = ((IData)(vlTOPp->v__DOT__controller__DOT__T46) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T43)) 
					       & (((0x1ff 
						    & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						       >> 0xf)) 
						   != 
						   (0x1ff 
						    & (IData)(
							      ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							       >> 1)))) 
						  | (~ (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))));
    vlTOPp->v__DOT__controller__DOT__T116 = ((IData)(vlTOPp->v__DOT__controller__DOT__T46) 
					     & (IData)(vlTOPp->v__DOT__controller__DOT__T43));
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memReq_valid, vlTOPp->v__DOT__controller__DOT__T61);
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memResp_ready, vlTOPp->v__DOT__controller__DOT__T70);
    vlTOPp->v__DOT__controller__DOT__T69 = ((IData)(vlTOPp->v__DOT__controller__DOT__T70) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memRead_memResp_valid));
}

void VColdMissSkipVectorCache::_combo__TOP__15(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_combo__TOP__15\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_memWrite_memWriteReq_valid, 
		  (1 & ((IData)(vlTOPp->v__DOT__controller__DOT__T56)
			 ? (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))
			 : ((IData)(vlTOPp->v__DOT__controller__DOT__T101) 
			    | ((IData)(vlTOPp->v__DOT__controller__DOT__T97) 
			       | ((IData)(vlTOPp->v__DOT__controller__DOT__T22) 
				  & (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))))));
    vlTOPp->v__DOT__controller__DOT__T37 = ((IData)(vlTOPp->v__DOT__controller__DOT__T46) 
					    & ((~ (IData)(vlTOPp->v__DOT__controller__DOT__T43)) 
					       & (((0x1ff 
						    & (vlTOPp->__Vcellinp__v__io_readPort_readReq_bits 
						       >> 0xf)) 
						   != 
						   (0x1ff 
						    & (IData)(
							      ((QData)((IData)(vlTOPp->v__DOT__tagMem__DOT__T2)) 
							       >> 1)))) 
						  | (~ (IData)((QData)(vlTOPp->v__DOT__tagMem__DOT__T2))))));
    vlTOPp->v__DOT__controller__DOT__T116 = ((IData)(vlTOPp->v__DOT__controller__DOT__T46) 
					     & (IData)(vlTOPp->v__DOT__controller__DOT__T43));
    vlTOPp->v__DOT__controller__DOT__T69 = ((IData)(vlTOPp->v__DOT__controller__DOT__T70) 
					    & (IData)(vlTOPp->__Vcellinp__v__io_memRead_memResp_valid));
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readReq_ready, vlTOPp->v__DOT__controller__DOT__T116);
}

void VColdMissSkipVectorCache::_sequent__TOP__16(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_sequent__TOP__16\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memReq_valid, vlTOPp->v__DOT__controller__DOT__T61);
    VL_ASSIGN_SII(1,vlTOPp->io_memRead_memResp_ready, vlTOPp->v__DOT__controller__DOT__T70);
}

void VColdMissSkipVectorCache::_settle__TOP__17(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_settle__TOP__17\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_readPort_readReq_ready, vlTOPp->v__DOT__controller__DOT__T116);
}

void VColdMissSkipVectorCache::_eval(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_eval\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__16(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__v__clk = vlTOPp->__Vcellinp__v__clk;
}

void VColdMissSkipVectorCache::_eval_initial(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_eval_initial\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VColdMissSkipVectorCache::final() {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::final\n"); );
    // Variables
    VColdMissSkipVectorCache__Syms* __restrict vlSymsp = this->__VlSymsp;
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VColdMissSkipVectorCache::_eval_settle(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_eval_settle\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    vlTOPp->_settle__TOP__5(vlSymsp);
    vlTOPp->_settle__TOP__8(vlSymsp);
    vlTOPp->_settle__TOP__11(vlSymsp);
    vlTOPp->_settle__TOP__14(vlSymsp);
    vlTOPp->_settle__TOP__17(vlSymsp);
}

IData VColdMissSkipVectorCache::_change_request(VColdMissSkipVectorCache__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VColdMissSkipVectorCache::_change_request\n"); );
    VColdMissSkipVectorCache* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
