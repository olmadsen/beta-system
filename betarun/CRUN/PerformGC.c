/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: PerformGC.c,v $, rel: %R%, date: $Date: 1992-08-31 10:04:57 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void DoGC()
{
#ifdef sparc
    GCable_Entry();

    StackEnd = StackPointer;
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
  BetaError(-8, getD0Reg());
}
#endif
    
