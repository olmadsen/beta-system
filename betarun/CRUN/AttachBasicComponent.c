/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamThisComp(void, AttBC)
/* = void AttBC(struct Object *this, struct Component *comp) */
{
#ifdef sparc
    register ref(CallBackFrame) callBackFrame __asm__("%l5");
    register ref(RegWin)	nextCompBlock __asm__("%l6");
    register long 		level 	      __asm__("%l7");
#endif

#ifdef hppa
    long dummy; /* don't move without changing SnakeAdditions.S */
    struct ComponentBlock  cb
	/* Used to hold value of lastCompBlock at time of Attach.
	 * This value is used by Susp to find out which parts of
	 * machine stack and ref-stack to pack.
	 */
	/* don't move without changing SnakeAdditions.S */;
#endif

    GCable_Entry();
    FetchThisComp();

    Ck(comp);

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

#ifdef sparc
    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    lastCompBlock = cast(ComponentBlock) StackPointer;
    StackStart = (long)StackPointer;
    
    getret(comp->CallerLSC);
#endif
#ifdef hppa
    cb.callBackFrame = cast(CallBackFrame) 0;
    cb.next = cast(ComponentBlock) 0;
    cb.level = 0;
    cb.RefBlock = (void *)/*getRefSP()*/RefSP;
    StackStart = (long)RefSP;
    lastCompBlock = (void *)RefSP;
    comp->CallerLSC = 1;
#endif

    BasicItem = cast(Item) &comp->Body;

    /* ActiveCallBackFrame = 0; */
    ActiveComponent = comp;

    /* ?? should set comp = 0 as done in AttachBasicComponent.run */
    CallBetaEntry( BasicItem->Proto->TopMpart, &comp->Body);

    /* TerminateBasicComponent: */
    BetaExit(0);

#ifdef sparc
    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    __asm__(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
#endif
}

#endif /* MT */
