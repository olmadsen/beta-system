/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * floats.c: floating point aspects of BETA runtime system
 * by Peter Andersen
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

#ifdef nti_ms
#define FPU_ZERODIVISION  _EM_ZERODIVIDE
#define FPU_INVALID       _EM_INVALID
#define FPU_DENORMALIZED  _EM_DENORMAL
#define FPU_OVERFLOW      _EM_OVERFLOW
#define FPU_UNDERFLOW     _EM_UNDERFLOW
#define FPU_PRECISIONLOST _EM_INEXACT
#define EnableFPUexceptions(mask) _controlfp((mask), _MCW_EM)
#endif /* nti_ms */

#ifdef nti_bor
/* The following is necessary in order to get printf to
 * work with floats in e.g. putreal on borland.
 * If not you may get a message like:
 *     printf: floating formats not linked
 * at run time.
 */
#include <stdlib.h>
#pragma extref _floatconvert
#define FPU_ZERODIVISION  EM_ZERODIVIDE
#define FPU_INVALID       EM_INVALID
#define FPU_DENORMALIZED  EM_DENORMAL
#define FPU_OVERFLOW      EM_OVERFLOW
#define FPU_UNDERFLOW     EM_UNDERFLOW
#define FPU_PRECISIONLOST EM_INEXACT
#define EnableFPUexceptions(mask) _control87((mask), MCW_EM)
#endif

#ifdef sun4s
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
#include <i386/fpu_control.h>
#define FPU_ZERODIVISION  _FPU_MASK_ZM
#define FPU_INVALID       _FPU_MASK_IM
#define FPU_DENORMALIZED  _FPU_MASK_DM
#define FPU_OVERFLOW      _FPU_MASK_OM
#define FPU_UNDERFLOW     _FPU_MASK_UM
#define FPU_PRECISIONLOST _FPU_MASK_PM
#define EnableFPUexceptions(mask) __setfpucw(_FPU_DEFAULT & ~(mask))
#endif

#ifdef sgi
  /* see set_fpc_csr(3c), handle_sigfpes(3c) */
#endif

#ifdef sun4
  /* see ieee_handler(3M), sigfpe */
#endif


#ifndef EnableFPUexceptions
#define EnableFPUexceptions(mask) \
  fprintf(output, "setupfpu: floating point exceptions not enabled\n");
#endif


void SetupFPU(void)
{
  /* Enable floating point exceptions */
  EnableFPUexceptions(FPU_ZERODIVISION |
		      FPU_INVALID |
		      FPU_DENORMALIZED |
		      FPU_OVERFLOW |
		      FPU_UNDERFLOW |
		      /* FPU_PRECISIONLOST */
		      0
		      );
}
