/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

void doGC() /* The one called from IOAalloc */
{
#ifdef sparc
  DEBUG_CODE(extern pc_t frame_PC);
  MCHECK();
  /* Flush register windows to stack */
  __asm__("ta 3");
  StackEnd = (long *)((struct RegWin *) StackPointer);
  /* StackEnd points to the activation record of doGC, which in turn was 
   * either branched to from DoGC, or called from inlined IOAalloc.
   */
  DEBUG_CODE(frame_PC=(pc_t)(((RegWin *) StackEnd)->i7 +8));
  StackEnd = (long *)((RegWin *) StackEnd)->fp; /* Skip AR of doGC() */
  MCHECK();
  IOAGc();
  MCHECK();
#endif
#ifdef hppa
#ifndef UseRefStack
  StackEnd = (long *)getSPReg();
#endif /* UseRefStack */
  PushGCRegs();
  CkReg("doGC", *(RefSP-1), "%r7");
  CkReg("doGC", *(RefSP-2), "%r6");
  CkReg("doGC", *(RefSP-3), "%r5");
  CkReg("doGC", *(RefSP-4), "%r4");
  CkReg("doGC", *(RefSP-5), "%r3");
  IOAGc();  /* saves r8 */
  PopGCRegs();
#endif
}

/* doGCtoSP:
 * Like doGC, but stop stack traversal at the specified SP.
 * PC must be PC corresponding to frame that ends in SP.
 */
void doGCtoSP(long *SP, pc_t PC) 
{
#ifdef sparc
  DEBUG_CODE(extern pc_t frame_PC);
  MCHECK();
  /* Flush register windows to stack */
  __asm__("ta 3");
  DEBUG_CODE(frame_PC=PC);
  StackEnd = SP;
  MCHECK();
  IOAGc();
  MCHECK();
#endif
#ifdef hppa
#ifndef UseRefStack
  StackEnd = SP;
#endif /* UseRefStack */
  PushGCRegs();
  CkReg("doGC", *(RefSP-1), "%r7");
  CkReg("doGC", *(RefSP-2), "%r6");
  CkReg("doGC", *(RefSP-3), "%r5");
  CkReg("doGC", *(RefSP-4), "%r4");
  CkReg("doGC", *(RefSP-5), "%r3");
  IOAGc();  /* saves r8 */
  PopGCRegs();
#endif
}

#ifdef sparc
/* IOAalloc is now in-lined.
 * That is, ProcessStack does not skip the regwin of IOAalloc,
 * and thus there is no need for the extra regwin around doGC anymore.
 * So we just branch to doGC with ReqObjectSize=0.
 */
asmlabel(DoGC,
	 "sethi  %hi(ReqObjectSize),%g1\n"
	 "ba     doGC\n"
         "clr    [%g1+%lo(ReqObjectSize)]\n");
#else /* ! sparc */
void DoGC() /* The one called directly from betaenv */
{
  ReqObjectSize = 0;
  doGC();
}
#endif /* ! sparc */

#ifdef RTDEBUG
void DoGC_UseCk()
{
  Ck(0);
}
#endif

#endif /* Not MT */
