/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
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

#ifdef crts
void Return() {}
#endif

#ifdef sparc
     /* The first nop is needed in case Return is called directly from a 
      * runtime ruotine. This is the case for e.g. an empty program.
      */
#ifdef sun4s
     asmlabel(Return, "nop; retl; nop");
#else
     asmlabel(_Return, "nop; retl; nop");
#endif
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
	set "USCORE"ArgCount, %g1
	st %i0, [%g1]
	set "USCORE"ArgVector, %g1
	retl
	st %i1, [%g1]
");
#endif


/* GC/PerformGC.c: Not declared in function.h, doGC should only be 
 * called from IOA(c)lloc or DoGC.
 */
extern void doGC();


#ifndef RTDEBUG
/* inline */
#endif
char *
  IOAalloc(unsigned size)
{
  register char *p;
  
  GCable_Entry();
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
#if (defined(sparc) || defined(hppa))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAalloc: (IOATop&7)==0"));
#endif
  
  while ((char *)IOATop+size > (char *)IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  }
  
  p = (char *)IOATop;
#ifdef hppa
  setIOATopoffReg(getIOATopoffReg() + size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef crts
  IOATop += size;
#endif
  
  return p;
}

#ifndef RTDEBUG
/* inline */
#endif
char *
  IOAcalloc(unsigned size)
{
  register char *p;
  
  GCable_Entry();
  
  DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));
#if (defined(sparc) || defined(hppa))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAcalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAcalloc: (IOATop&7)==0"));
#endif
  
  while ((char *) IOATop+size > (char *)IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  }
  
  p = (char *)IOATop;
#ifdef hppa
  setIOATopoffReg(getIOATopoffReg() + size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef crts
  IOATop += size;
#endif
  
  long_clear(p, size);
  return p;
}

#ifdef sparc
#ifdef sun4s
asmlabel(FailureExit, "
	mov	%i0, %o1
	call	BetaError
	mov	-8, %o0
");
#else
asmlabel(_FailureExit, "
	mov	%i0, %o1
	call	_BetaError
	mov	-8, %o0
");
#endif
#endif

#ifdef hppa
void FailureExit()
{
  BetaError(StopCalledErr, cast(Object)(getD0Reg()));
}
#endif

#ifdef RTDEBUG
#ifndef hppa
void CCk(ref(Object) r)
{
  if(r) 
    Claim(inIOA(r) || inAOA(r) || inLVRA(r) || isLazyRef(r),
	  "Reference none or inside IOA, AOA, or LVRA");
}
#endif
#endif

#ifdef crts

/* Global address registers */
long *a0,*a1,*a2,*a3,*a4,*a7;
int leave;

/* New RT routines for crts */
static long *refstack[1000];
static long reftop=0;

void pushAdr(a)
     long *a;
{
  refstack[reftop] = a;
  reftop=reftop+1;
}

long *popAdr()
{
  reftop=reftop-1;
  return (long *)refstack[reftop];
}  

int CallBackPar(off)
     int off;
{
}

int GetByte(int a,int byteNo)
{}
int GetShort(int a,int shortNo)
{}
int PutBits(int a,int b,int c,int d)
{}
int GetBits(int a,int b,int c)
{}
int GetSignedBits(int a,int b,int c)
{}
int SignExtByte(int a)
{}
int SignExtWord(int a)
{}

#endif /* crts */
