/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#if (defined(sparc) && (!defined(RTDEBUG)))
/* An extra nop is needed before retl in case Return is called directly
 * from a runtime routine. This is the case for e.g. an empty program.
 * If you try to do this with an __asm__("nop") in a C function, the C function
 * will NOT become a leaf routine. Thus we do it manually her.
 */
#ifdef sun4s
asmlabel(Return, "nop; retl; nop");
#else
asmlabel(_Return, "nop; retl; nop");
#endif /* sun4s */
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
Item *SPARC_AlloSI(Structure *s, int i1, int i2, int i3, int i4)
{
  Item *CAlloSI(Structure *s, int i1, int i2, int i3, int i4);
  GCable_Entry();
  return CAlloSI(s, i1, i2 ,i3, i4);
  GCable_Exit(1);
}

Component *SPARC_AlloC(Object *origin, int i1, ProtoType *proto, int i3, int i4)
{
  Component *CAlloC(Object *origin, 
			   int i1, 
			   ProtoType *proto, 
			   int i3, 
			   int i4);
  GCable_Entry();
  return CAlloC(origin, i1, proto, i3, i4);
  GCable_Exit(1);
}

Item *SPARC_AlloI(Object *origin, int i1, ProtoType *proto, int i3, int i4)
{ Item *CAlloI(Object *origin, int i1, ProtoType *proto, int i3, int i4);
  GCable_Entry();
  MCHECK();
  return CAlloI(origin, i1, proto, i3, i4);
  MCHECK();
  GCable_Exit(1);
}
#endif /* MT */

#endif /* sparc */

void RefNone(Object * theObj)
{
#if (defined(hppa) && defined(RTLAZY))
  /* Called with the possible dangling reference in %r31 */
  __asm__ volatile ("\tCOPY\t%%r31,%0\n" : "=r" (theObj));
  if (isLazyRef(theObj){
    /* save reference registers in case of dangling reference */
    PushGCRegs();
    CkReg("RefNone", *(RefSP-1), "%r7");
    CkReg("RefNone", *(RefSP-2), "%r6");
    CkReg("RefNone", *(RefSP-3), "%r5");
    CkReg("RefNone", *(RefSP-4), "%r4");
    CkReg("RefNone", *(RefSP-5), "%r3");
    /* Save data registers on machine stack in case of dangling reference */
    pushReg((void *)getD1Reg());
    pushReg((void *)getD2Reg());
    pushReg((void *)getD3Reg());
    pushReg((void *)getD4Reg());
    pushReg((void *)getR8Reg()); /* R8 is NOT to be GC'ed */
    
    LazyDangler = (long)theObj; /* dangling reference */
    CallBetaEntry(LazyItem->Proto->TopMpart, LazyItem);
    
    setR8Reg((long)popReg());
    setD4Reg((long)popReg());
    setD3Reg((long)popReg());
    setD2Reg((long)popReg());
    setD1Reg((long)popReg());
    PopGCRegs();
  } else {
    /* Reference was NONE */
    theObj = (Object *)getThisReg(); /* Get current object */
    BetaError(RefNoneErr, theObj);
  }
#else
#ifdef hppa
    theObj = (Object *)getThisReg(); /* Get current object */
#endif
  BetaError(RefNoneErr, theObj);
#endif /* hppa && RTLAZY */
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

#ifdef sparc
#ifdef sun4s
asmlabel(FailureExit, 
	 "mov	%i0, %o1; "
	 "call	BetaError; "
	 "mov	-8, %o0; "
	 );
#else
asmlabel(_FailureExit, 
	 "mov	%i0, %o1; "
	 "call	_BetaError; "
	 "mov	-8, %o0; "
	 );
#endif
#endif

#ifdef hppa
void FailureExit()
{
  BetaError(StopCalledErr, (Object *)(getThisReg()));
}
#endif

