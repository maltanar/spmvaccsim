// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _VSimpleDMVectorCache__Syms_H_
#define _VSimpleDMVectorCache__Syms_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "VSimpleDMVectorCache.h"

// SYMS CLASS
class VSimpleDMVectorCache__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool	__Vm_activity;		///< Used by trace routines to determine change occurred
    bool	__Vm_didInit;
    //char	__VpadToAlign10[6];
    
    // SUBCELL STATE
    VSimpleDMVectorCache*          TOPp;
    
    // COVERAGE
    
    // SCOPE NAMES
    
    // CREATORS
    VSimpleDMVectorCache__Syms(VSimpleDMVectorCache* topp, const char* namep);
    ~VSimpleDMVectorCache__Syms() {};
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    inline bool getClearActivity() { bool r=__Vm_activity; __Vm_activity=false; return r;}
    
} VL_ATTR_ALIGNED(64);

#endif  /*guard*/
