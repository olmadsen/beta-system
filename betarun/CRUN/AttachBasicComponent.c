/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: AttachBasicComponent.c,v 1.9 1992-09-03 12:55:37 beta Exp $
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

#ifdef hppa
    long			dummy;
    struct ComponentBlock       cb; /* don't move without changing Attach.S */

    comp = cast(Component)getCallReg();
#endif

    GCable_Entry();

    Ck(comp);
    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */
#ifdef sparc
    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    lastCompBlock = cast(ComponentBlock) StackPointer;
    
    getret(comp->CallerLSC);
#endif
#ifdef hppa
    cb.callBackFrame = cast(CallBackFrame) 0;
    cb.next = cast(ComponentBlock) 0;
    cb.level = 0;
    cb.RefBlock = (void *)getRefSP();
    lastCompBlock = (void *)getSPReg();
    comp->CallerLSC = 1;
#endif

    BasicItem = cast(Item) &comp->Body;

    ActiveCallBackFrame = 0;
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

