/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

#if (defined(sparc) && (!defined(RTDEBUG)))
/* An extra nop is needed before retl in case Return is called directly
 * from a runtime routine. This is the case for e.g. an empty program.
 * If you try to do this with an __asm__("nop") in a C function, the C function
 * will NOT become a leaf routine. Thus we do it manually her.
 */
asmlabel(Return, "nop; retl; nop");
#else
void Return() 
{
  DEBUG_CODE(NumReturn++);
  return;
}
#endif

#ifdef sparc
/* Functions used to call RT routines directly from C.
 * Needed because %i1 in calling regwin is destroyed by (C)AlloSI
 * Must be here away from the corresponding CAlloXXX functions
 * to prevent gcc from inlining it.
 */

#ifndef MT
Item *OAlloSI(Structure *s, int i1, int i2, int i3, int i4)
{
  Item *CAlloSI(Structure *s, int i1, int i2, int i3, int i4);
  Item *i= CAlloSI(s, i1, i2 ,i3, i4);
  return_i1_in_o0();
  return i; /* Keep gcc happy */
}

Component *OAlloC(Object *origin, int i1, ProtoType *proto, int i3, int i4)
{
  Component *CAlloC(Object *origin, int i1, ProtoType *proto, int i3, int i4);
  Component *c=CAlloC(origin, i1, proto, i3, i4);
  return_i1_in_o0();
  return c; /* Keep gcc happy */
}

Item *OAlloI(Object *origin, int i1, ProtoType *proto, int i3, int i4)
{ 
  Item *CAlloI(Object *origin, int i1, ProtoType *proto, int i3, int i4);
  Item *i = CAlloI(origin, i1, proto, i3, i4);
  return_i1_in_o0();
  return i; /* Keep gcc happy */
}
#endif /* !MT */
#endif /* sparc */

void RefNone(Object * theObj)
{
#ifdef hppa
  theObj = (Object *)getThisReg(); /* Get current object */
#endif
  BetaError(RefNoneErr, theObj);
}

#ifdef sparc
/* Need to do this in assembler, as the arguments to
   my caller normally isn't accesseable */
asmlabel(SetArgValues, 
	 "set "USCORE"ArgCount, %g1; "
	 "st %i0, [%g1]; "
	 "set "USCORE"ArgVector, %g1; "
	 "retl; "
	 "st %i1, [%g1]; "
	 );
#else
void SetArgValues(int argc, char *argv[])
{
#ifdef __powerc
  if (StandAlone) {
    ArgCount = 0;
    ArgVector = 0;
  } else {
    ArgCount = argc;
    ArgVector = argv;
  }
#else
  ArgCount = argc;
  ArgVector = argv;
#endif
}
#endif

#ifndef __GNUC__
#include "IOAalloc.h"
#endif

#ifdef sun4s
asmlabel(FailureExit, 
	 "mov	%i0, %o0; "
	 "save  %sp,-112,%sp; " /* using 112 as gcc does -  */
	 "mov	%i0, %o1; "
	 "call	BetaError; "
	 "mov	-8, %o0; "
	 "ret; "
	 "restore; "
	 );
#endif

#ifdef sun4s
asmlabel(DumpStack, 
	 "mov	%i0, %o0; "
	 "save  %sp,-112,%sp; " /* using 112 as gcc does -  */
	 "mov	%i0, %o1; "
	 "call	BetaError; "
	 "mov	-39, %o0; "
	 "ret; "
	 "restore; "
	 );
#endif

#ifdef hppa
void FailureExit()
{
  BetaError(StopCalledErr, (Object *)(getThisReg()));
}

void DumpStack()
{
  BetaError(DumpStackErr, (Object *)(getThisReg()));
}
#endif

