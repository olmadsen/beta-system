/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef hppa
unsigned savedIOATopoff;
long *   savedIOA;
long *   savedRefSP;
#endif

#ifdef hppa
void Return() {}
#endif
#ifdef sparc
asmlabel(Return, "retl; nop");
#endif

void
RefNone(ref(Object) theObj)
{
    BetaError(RefNoneErr, theObj);
}

#ifdef hppa
SetArgValues(long argc, char *argv[])
{
  ArgCount = argc;
  ArgVector = argv;
}
#endif
#ifdef sparc
/* Need to do this in assembler, as the arguments to
   my caller normally isn't accesseable */
asmlabel(SetArgValues, "
	set _ArgCount, %g1
	st %i0, [%g1]
	set _ArgVector, %g1
	retl
	st %i1, [%g1]
");
#endif


/* GC/PerformGC.c: Not declared in function.h, doGC should only be 
 * called from IOA(c)lloc or DoGC.
 */
extern void doGC();


char *
IOAalloc(unsigned size)
{
  register char *p;

  GCable_Entry();

  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));

  while ((char *)IOATop+size > (char *)IOALimit) {
      ReqObjectSize = size / 4;
      doGC();
  }

  p = (char *)IOATop;
#ifdef hppa
  setIOATopoffReg(getIOATopoffReg() + size);
#else
  IOATopoff += size;
#endif

  return p;
}

char *
IOAcalloc(unsigned size)
{
  register char *p;

  GCable_Entry();

  DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));

  while ((char *) IOATop+size > (char *)IOALimit) {
      ReqObjectSize = size / 4;
      doGC();
  }

  p = (char *)IOATop;
#ifdef hppa
  setIOATopoffReg(getIOATopoffReg() + size);
#else
  IOATopoff += size;
#endif

  long_clear(p, size);
  return p;
}

#ifdef sparc
asmlabel(_FailureExit, "
	mov	%i0, %o1
	call	_BetaError
	mov	-8, %o0
");
#endif
#ifdef hppa
void FailureExit()
{
  BetaError(StopCalledErr, getD0Reg());
}
#endif

#ifdef RTDEBUG
#ifndef hppa
void CCk(ref(Object) r)
{
  if(r) 
    Claim(inIOA(r) || inAOA(r) || inLVRA(r),
	  "Checked reference none or inside IOA, AOA, or LVRA");
  }
#endif
#endif

