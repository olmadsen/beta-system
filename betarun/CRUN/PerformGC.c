/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef RTDEBUG
#define CkReg(value, reg)                                                        \
{ struct Object *theObj = (struct Object *)(value);                              \
  if (theObj &&                                                                  \
      !isProto(theObj) && /* e.g. AlloI is called with prototype in ref. reg. */ \
      !(inBetaHeap(theObj) && isObject(theObj)))                                 \
    fprintf(output,                                                              \
	    "DoGC: ***Illegal reference register %s: 0x%x\n", reg, theObj);      \
}
#else
#define CkReg(value, reg)
#endif

void doGC() /* The one called from IOA(c)alloc */
{
#ifdef sparc
    GCable_Entry();

    StackEnd = (long *)((struct RegWin *) StackPointer);
    
    IOAGc();
#endif
#ifdef hppa
    StackEnd = (long *)getSPReg();
    asm volatile ("\tLDIL\tLR'RefSP,%r1\n"
		  "\tLDW\tRR'RefSP(%r1),%r14\n"
		  "\tSTWS,MA\t%r3,4(0,%r14)\n"  /* r3 (th) */
		  "\tSTWS,MA\t%r4,4(0,%r14)\n"  /* r4 (ca) */
		  "\tSTWS,MA\t%r5,4(0,%r14)\n"  /* r5 */
		  "\tSTWS,MA\t%r6,4(0,%r14)\n"  /* r6 */
		  "\tSTWS,MA\t%r7,4(0,%r14)\n"  /* r7 */
		  /* r8 is NOT to be GC'ed */
		  "\tSTW\t%r14,RR'RefSP(0,%r1)\n"
		  );
    CkReg(*(RefSP-1), "%r7");
    CkReg(*(RefSP-2), "%r6");
    CkReg(*(RefSP-3), "%r5");
    CkReg(*(RefSP-4), "%r4");
    CkReg(*(RefSP-5), "%r3");
    IOAGc();
    asm volatile ("\tLDIL\tLR'RefSP,%r1\n"
		  "\tLDW\tRR'RefSP(%r1),%r14\n"
		  "\tLDWS,MB\t-4(0,%r14),%r7\n"
		  "\tLDWS,MB\t-4(0,%r14),%r6\n"
		  "\tLDWS,MB\t-4(0,%r14),%r5\n"
		  "\tLDWS,MB\t-4(0,%r14),%r4\n"
		  "\tLDWS,MB\t-4(0,%r14),%r3\n"
		  "\tSTW\t%r14,RR'RefSP(0,%r1)\n"
		  );
#endif
    asmemptylabel(EndGC);
    fprintf(output,"\n\ndoGC NYI\n\n");
    exit(1);
}

void DoGC() /* The one called directly from betaenv */
{ 
  /* This wrapper adds an activation record around doGC, which skips two AR's */
  ReqObjectSize = 0;
  doGC();
}
