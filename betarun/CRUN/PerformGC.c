/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef crts
extern long a0;
extern long a1;
extern long a2;
extern long a3;
extern long a4;
#endif 

void doGC() /* The one called from IOA(c)alloc */
{
#ifdef crts
    PushGCRegs();
    CkReg("doGC", *(RefSP-1), "a4");
    CkReg("doGC", *(RefSP-2), "a3");
    CkReg("doGC", *(RefSP-3), "a2");
    CkReg("doGC", *(RefSP-4), "a1");
    CkReg("doGC", *(RefSP-5), "a0");
    IOAGc();
    PopGCRegs();
#endif
#ifdef sparc
    GCable_Entry();
    StackEnd = (long *)((struct RegWin *) StackPointer);
    IOAGc();
#endif
#ifdef hppa
#ifndef REFSTACK
    StackEnd = (long *)getSPReg();
#endif REFSTACK
    PushGCRegs();
    CkReg("doGC", *(RefSP-1), "%r7");
    CkReg("doGC", *(RefSP-2), "%r6");
    CkReg("doGC", *(RefSP-3), "%r5");
    CkReg("doGC", *(RefSP-4), "%r4");
    CkReg("doGC", *(RefSP-5), "%r3");
    IOAGc();  /* saves r8 */
    PopGCRegs();
#endif
    asmemptylabel(EndGC);
}

#ifdef sparc
/* IOA(c)alloc is now in-lined.
 * That is, ProcessStack does not skip the regwin of IOA(c)alloc,
 * and thus there is no need for the extra regwin around doGC anymore.
 */
#ifdef sun4s
asmlabel(DoGC,
	 "sethi  %hi(ReqObjectSize), %g1\n"
	 "ba     doGC\n"
         "clr    [ %g1 + %lo(ReqObjectSize) ]\n");
#else
asmlabel(_DoGC,
	 "sethi  %hi(_ReqObjectSize), %g1\n"
	 "ba     _doGC\n"
         "clr    [ %g1 + %lo(_ReqObjectSize) ]\n");
#endif
#else
void DoGC() /* The one called directly from betaenv */
  ReqObjectSize = 0;
  doGC();
}
#endif

#ifdef RTDEBUG
void DoGC_UseCk()
{
  Ck(0);
}
#endif
