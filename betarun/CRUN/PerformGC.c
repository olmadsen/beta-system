/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: PerformGC.c,v 1.9 1993-02-12 13:57:33 datpete Exp $
 * by Peter Andersen and Tommy Thorn.
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
    asm volatile ("\tSTWS,MB\t%r3,4(0,%r14)\n"
        "\tSTWS,MB\t%r4,4(0,%r14)\n" /* maybe not CallReg?? */
        "\tSTWS,MB\t%r5,4(0,%r14)\n"
        "\tSTWS,MB\t%r6,4(0,%r14)\n"
        "\tSTWS,MB\t%r7,4(0,%r14)\n");
    IOAGc();
    asm volatile ("\tLDWS,MA\t-4(0,%r14),%r7\n"
        "\tLDWS,MA\t-4(0,%r14),%r6\n"
        "\tLDWS,MA\t-4(0,%r14),%r5\n"
        "\tLDWS,MA\t-4(0,%r14),%r4\n"
        "\tLDWS,MA\t-4(0,%r14),%r3\n");
#endif
}

void DoGC() /* The one called directly from betaenv */
{ 
  /* This wrapper adds an activation record around doGC, which skips two AR's */
  doGC();
}
