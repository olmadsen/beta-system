/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * floats.c: floating point aspects of BETA runtime system
 * by Peter Andersen
 */

#include "beta.h"

#ifdef nti_bor
/* The following is necessary in order to get printf to
 * work with floats in e.g. putreal on borland.
 * If not you may get a message like:
 *     printf: floating formats not linked
 * at run time.
 */
#include <stdlib.h>
#pragma extref _floatconvert
#endif

void SetupFPU(void)
{
  /* Enable floating point exceptions */
#ifdef nti_ms
  _controlfp(_EM_INVALID   | _EM_INEXACT | _EM_DENORMAL | _EM_OVERFLOW | 
	     _EM_UNDERFLOW | _EM_ZERODIVIDE, _MCW_EM);
#endif

#ifdef nti_bor
  _control87(EM_INVALID   | EM_INEXACT | EM_DENORMAL | EM_OVERFLOW | 
	     EM_UNDERFLOW | EM_ZERODIVIDE, MCW_EM);
#endif

#ifdef sun4s
#include <ieeefp.h>
  fpsetmask(FP_X_INV | FP_X_OFL | FP_X_UFL | FP_X_DZ /* | FP_X_IMP */);
#endif

#ifdef hpux9pa
  fprintf(output, "setupfpu: floating point exceptions not enabled\n");
#endif

#ifdef sun4
  /* see ieee_handler(3M), sigfpe */
  fprintf(output, "setupfpu: floating point exceptions not enabled\n");
#endif

#ifdef linux
#include <i386/fpu_control.h>
  __setfpucw(_FPU_IEEE);
#endif

#ifdef sgi
  /* see set_fpc_csr(3c), handle_sigfpes(3c) */
  fprintf(output, "setupfpu: floating point exceptions not enabled\n");
#endif

}
