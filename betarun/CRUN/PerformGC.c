/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void doGC() /* The one called from IOA(c)alloc */
{
#ifdef crts
    fprintf(output,"\n\ndoGC NYI\n\n");
    exit(1);
#endif
#ifdef sparc
    GCable_Entry();

    StackEnd = (long *)((struct RegWin *) StackPointer);
    
    IOAGc();
#endif
#ifdef hppa
    StackEnd = (long *)getSPReg();
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

void DoGC() /* The one called directly from betaenv */
{ 
  /* This wrapper adds an activation record around doGC, which skips two AR's */
  ReqObjectSize = 0;
  doGC();
}
