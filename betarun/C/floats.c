/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-99, 2001 Mjolner Informatics Aps.
 * floats.c: 
 *   IEEE 754 floating-point aspects of BETA runtime system
 *   by Peter Andersen
 */

#include "beta.h"

#if 0
#define FPU_ZERODIVISION  
#define FPU_INVALID       
#define FPU_DENORMALIZED  
#define FPU_OVERFLOW      
#define FPU_UNDERFLOW     
#define FPU_PRECISIONLOST 
#define EnableFPUexceptions(mask) 
#endif


#if defined(nti_ms) || defined(nti_gnu)
#include <float.h>
#define FPU_ZERODIVISION  _EM_ZERODIVIDE
#define FPU_INVALID       _EM_INVALID
#define FPU_DENORMALIZED  _EM_DENORMAL
#define FPU_OVERFLOW      _EM_OVERFLOW
#define FPU_UNDERFLOW     _EM_UNDERFLOW
#define FPU_PRECISIONLOST _EM_INEXACT
#define EnableFPUexceptions(mask) _controlfp((unsigned int)~(mask), _MCW_EM)
#endif /* nti_gnu || nti_ms */

#ifdef nti_bor
/* The following is necessary in order to get printf to
 * work with floats in e.g. putreal on borland.
 * If not you may get a message like:
 *     printf: floating formats not linked
 * at run time.
 */
#include <stdlib.h>
#include <float.h>
#pragma extref _floatconvert
#define FPU_ZERODIVISION  EM_ZERODIVIDE
#define FPU_INVALID       EM_INVALID
#define FPU_DENORMALIZED  EM_DENORMAL
#define FPU_OVERFLOW      EM_OVERFLOW
#define FPU_UNDERFLOW     EM_UNDERFLOW
#define FPU_PRECISIONLOST EM_INEXACT
#define EnableFPUexceptions(mask) _control87(~(mask), MCW_EM)
#endif

#if (defined(sun4s) || defined(x86sol))
#include <ieeefp.h>
#define FPU_ZERODIVISION  FP_X_DZ
#define FPU_INVALID       FP_X_INV
#define FPU_DENORMALIZED  0
#define FPU_OVERFLOW      FP_X_OFL
#define FPU_UNDERFLOW     FP_X_UFL
#define FPU_PRECISIONLOST FP_X_IMP
#define EnableFPUexceptions(mask) fpsetmask(mask)
#endif

#ifdef linux
#include <fpu_control.h> /* Changed from <i386/fpu_control.h> -mannan */
#define FPU_ZERODIVISION  _FPU_MASK_ZM
#define FPU_INVALID       _FPU_MASK_IM
#define FPU_DENORMALIZED  _FPU_MASK_DM
#define FPU_OVERFLOW      _FPU_MASK_OM
#define FPU_UNDERFLOW     _FPU_MASK_UM
#define FPU_PRECISIONLOST _FPU_MASK_PM
/* changed from by mannan
 * #define EnableFPUexceptions(mask) __setfpucw(_FPU_DEFAULT & ~(mask))
 */
void mysetfpucw(int word) {  _FPU_SETCW(word); }
#define EnableFPUexceptions(mask) mysetfpucw(_FPU_DEFAULT & ~(mask))

#endif

#ifdef hpux9pa
/* See chapter 6 in "HP Precision Architecture and Instruction Set 
 * Reference Manual
 * Floating Point Status Register: see table 6-1 and figure 6-6.
 */
#define FPU_ZERODIVISION  (1L<<3)
#define FPU_INVALID       (1L<<4)
#define FPU_DENORMALIZED  0
#define FPU_OVERFLOW      (1L<<2)
#define FPU_UNDERFLOW     (1L<<1)
#define FPU_PRECISIONLOST (1L<<0)
#define EnableFPUexceptions(mask) \
{ \
  unsigned long fpsr; /* gdb's name for this register */\
  register unsigned long *addr; \
  addr = &fpsr; \
  __asm__ volatile ("FSTWS %%fr0,0(0,%0)" :: "r" (addr)); \
  /*fprintf(output, "SetupFPU: old: 0x%08x\n", (int)fpsr);*/ \
  fpsr |= (mask); \
  /*fprintf(output, "SetupFPU: new: 0x%08x\n", (int)fpsr);*/ \
  addr = &fpsr; \
  __asm__ volatile ("FLDWS 0(0,%0),%%fr0" :: "r" (addr)); \
}
#endif

#ifdef sgi
/* see <sys/fpu.h> */
#define FPU_INVALID       (1<<11)
#define FPU_ZERODIVISION  (1<<10)
#define FPU_DENORMALIZED  0
#define FPU_OVERFLOW      (1<<9)
#define FPU_UNDERFLOW     (1<<8)
#define FPU_PRECISIONLOST (1<<7)
extern unsigned int get_fpc_csr(void);
extern unsigned int set_fpc_csr(unsigned int csr);
#define EnableFPUexceptions(mask)   \
{                                   \
  unsigned int csr = get_fpc_csr(); \
  set_fpc_csr((mask) | csr);        \
}
#endif /* sgi */

#if defined(ppcmac)
#include <fenv.h>
#define FPU_ZERODIVISION  FE_DIVBYZERO
#define FPU_INVALID       FE_INVALID
#define FPU_DENORMALIZED  0
#define FPU_OVERFLOW      FE_OVERFLOW
#define FPU_UNDERFLOW     FE_UNDERFLOW
#define FPU_PRECISIONLOST FE_INEXACT
#define EnableFPUexceptions(mask) feraiseexcept(mask) 
#endif /* ppcmac */

#if defined(macosx)
/* See 
 * http://developer.apple.com/techpubs/mac/PPCNumerics/PPCNumerics-154.html 
 * and table 5-17 in PowerPC 601 ref. manual
 */
#define FPU_ZERODIVISION  (1L << 27) /* ZE bit */
#define FPU_INVALID       (1L << 24) /* VE bit */
#define FPU_DENORMALIZED  0
#define FPU_OVERFLOW      (1L << 25) /* OE bit */
#define FPU_UNDERFLOW     (1L << 26) /* UE bit */
#define FPU_PRECISIONLOST (1L << 28) /* XE bit */

static void EnableIEEE754Exceptions(mask)
{      
#if 0
  register unsigned long msr;
  /* Need to set MSR bits too, but mfmsr/mtmsr are supervisor only!*/
  /* The stuff below is like get_msr()/set_msr() in <architecture/ppc_basic_regs.h> */
  __asm__ __volatile("mfmsr %0" : "=r" (msr)); 
  msr |= (1L<<(31-23)) /*FE1*/| (1L<<(31-20)) /*FE0*/;
  __asm__ __volatile("mtmsr %0" : : "r" (msr)); 
#endif

  if (mask & FPU_ZERODIVISION)  __asm__ __volatile("mtfsb1 27"); 
  if (mask & FPU_INVALID)       __asm__ __volatile("mtfsb1 24"); 
  if (mask & FPU_OVERFLOW)      __asm__ __volatile("mtfsb1 25"); 
  if (mask & FPU_UNDERFLOW)     __asm__ __volatile("mtfsb1 26"); 
  if (mask & FPU_PRECISIONLOST) __asm__ __volatile("mtfsb1 28"); 
}
#define EnableFPUexceptions(mask) EnableIEEE754Exceptions(mask)

#endif /* macosx */



#ifndef EnableFPUexceptions
#define EnableFPUexceptions(mask) \
  fprintf(output, "setupfpu: floating point exceptions not enabled\n");
#endif


void SetupFPU(void)
{
  /* Enable floating point exceptions */
  EnableFPUexceptions(FPU_ZERODIVISION |
		      FPU_INVALID |
		      /* FPU_DENORMALIZED | */
		      /* FPU_OVERFLOW | */
		      /* FPU_UNDERFLOW | */
		      /* FPU_PRECISIONLOST */
		      0
		      );
}
 
void DisableFPUexceptions(void)
{
  EnableFPUexceptions(0);
}
