/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AttachBasicComponent.c,v $, rel: %R%, date: $Date: 1992-07-20 11:45:03 $, SID: $Revision: 1.4 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

static TerminateBasicComponent() { BetaExit(0); }

void AttBC(ref(Component) theComp)
{
    register void (*entrypoint)();

    register ref(Item)		betaenv	      asm("%l4");
    register ref(CallBackFrame) callBackFrame asm("%l5");
    register ref(RegWin)	nextCompBlock asm("%l6");
    register long 		level 	      asm("%l7");

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

    betaenv = cast(Item) theComp->Body; /* Save betaenv obj. for mkTextObj */ 
    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    BasicItemHandle = StackPointer - 4; /* Needs to be thought about !! */

    ActiveCallBackFrame = 0; lastCompBlock = cast(ComponentBlock) StackPointer;

    
    getret(theComp->CallerLSC);

    ActiveComponent = theComp;

    entrypoint = ((void (**)()) (cast(Item)&theComp->Body)->Proto)[-1];
    /* ?? should set theComp = 0 as done in Att.BasicComp.run */
    (*entrypoint)(&theComp->Body);

    /* TerminateBasicComponent: */
    BetaExit(0);

    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    asm(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
}

