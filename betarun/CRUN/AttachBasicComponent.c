/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: AttachBasicComponent.c, rel: 1, date: 7/20/92, SID: 1.4
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

static TerminateBasicComponent() { BetaExit(0); }

ParamThisComp(void, AttBC)
{
    register long *entrypoint;

#ifdef sparc
    register ref(CallBackFrame) callBackFrame asm("%l5");
    register ref(RegWin)	nextCompBlock asm("%l6");
    register long 		level 	      asm("%l7");
#endif

    GCable_Entry();
    FetchThisComp

    Ck(comp);
    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    BasicItem = cast(Item) &comp->Body;

    ActiveCallBackFrame = 0; lastCompBlock = cast(ComponentBlock) StackPointer;
    
    getret(comp->CallerLSC);

    ActiveComponent = comp;

    /* ?? should set comp = 0 as done in Att.BasicComp.run */
    CallBetaEntry( *((long *)BasicItem->Proto-1), &comp->Body);

    /* TerminateBasicComponent: */
    BetaExit(0);


#ifdef sparc
    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    asm(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
#endif
}

