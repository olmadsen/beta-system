/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: AttachBasicComponent.c, rel: 1, date: 7/20/92, SID: 1.4
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

static TerminateBasicComponent() { BetaExit(0); }

void AttBC(ref(Component) theComp)
{
    register void (*entrypoint)();

    register ref(CallBackFrame) callBackFrame asm("%l5");
    register ref(RegWin)	nextCompBlock asm("%l6");
    register long 		level 	      asm("%l7");

    GCable_Entry

    Ck(theComp);
    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    BasicItem = cast(Item) &theComp->Body;

    ActiveCallBackFrame = 0; lastCompBlock = cast(ComponentBlock) StackPointer;
    
    getret(theComp->CallerLSC);

    ActiveComponent = theComp;

    entrypoint = ((void (**)()) BasicItem->Proto)[-1];
    /* ?? should set theComp = 0 as done in Att.BasicComp.run */
    (*entrypoint)(&theComp->Body);

    /* TerminateBasicComponent: */
    BetaExit(0);

    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    asm(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
}

