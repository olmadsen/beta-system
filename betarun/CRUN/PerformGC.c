/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"



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
		  "\tSTWS,MA\t%r3,4(0,%r14)\n"
		  "\tSTWS,MA\t%r4,4(0,%r14)\n" /* maybe not CallReg?? */
		  /*"\tSTWS,MA\t%r5,4(0,%r14)\n"*/
		  "\tSTWS,MA\t%r6,4(0,%r14)\n"
		  "\tSTWS,MA\t%r7,4(0,%r14)\n"
		  /*"\tSTWS,MA\t%r8,4(0,%r14)\n"*/
		  "\tSTW\t%r14,RR'RefSP(0,%r1)\n"
		  );
    IOAGc();
    asm volatile ("\tLDIL\tLR'RefSP,%r1\n"
		  "\tLDW\tRR'RefSP(%r1),%r14\n"
		  /*"\tLDWS,MB\t-4(0,%r14),%r8\n"*/
		  "\tLDWS,MB\t-4(0,%r14),%r7\n"
		  "\tLDWS,MB\t-4(0,%r14),%r6\n"
		  /*"\tLDWS,MB\t-4(0,%r14),%r5\n"*/
		  "\tLDWS,MB\t-4(0,%r14),%r4\n"
		  "\tLDWS,MB\t-4(0,%r14),%r3\n"
		  "\tSTW\t%r14,RR'RefSP(0,%r1)\n"
		  );
#endif
    asmemptylabel(EndGC);
}

void DoGC() /* The one called directly from betaenv */
{ 
  /* This wrapper adds an activation record around doGC, which skips two AR's */
  ReqObjectSize = 0;
  doGC();
}
