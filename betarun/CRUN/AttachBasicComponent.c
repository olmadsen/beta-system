/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamThisComp(void, AttBC)
/* = void AttBC(Object *this, Component *comp) */
{
#ifdef sparc
    register CallBackFrame * callBackFrame __asm__("%l5");
    register struct RegWin *	nextCompBlock __asm__("%l6");
    register long 		level 	      __asm__("%l7");
#endif

#ifdef hppa
    __attribute__((unused)) long dummy; /* don't move without changing SnakeAdditions.S */
    ComponentBlock  cb
	/* Used to hold value of lastCompBlock at time of Attach.
	 * This value is used by Susp to find out which parts of
	 * machine stack and ref-stack to pack.
	 */
	/* don't move without changing SnakeAdditions.S */;
#endif

    FetchThisComp();

    Ck(comp);

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

#ifdef sparc
    __asm__ volatile ("clr %0": "=r" (callBackFrame));
    __asm__ volatile ("clr %0": "=r" (nextCompBlock));
    __asm__ volatile ("clr %0": "=r" (level));

    lastCompBlock = (ComponentBlock *) StackPointer;
    StackStart = (long)StackPointer;
    
    getret(comp->CallerLSC);
#endif
#ifdef hppa
    cb.callBackFrame = (CallBackFrame *) 0;
    cb.next = (ComponentBlock *) 0;
    cb.level = 0;
    cb.RefBlock = (void *)/*getRefSP()*/RefSP;
    StackStart = (long)RefSP;
    lastCompBlock = (void *)RefSP;
    comp->CallerLSC = (pc_t)1;
#endif

    BasicItem = (Item *) &comp->Body;

    /* ActiveCallBackFrame = 0; */
    ActiveComponent = comp;
    ActiveComponent->StackObj = (StackObject *) -1;

    /* ?? should set comp = 0 as done in AttachBasicComponent.run */
    CallBetaEntry( OBJPROTOFIELD(BasicItem,TopMpart), &comp->Body);

    /* TerminateBasicComponent: */
    BetaExit(0);

#ifdef sparc
    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    __asm__(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
#endif
}

#endif /* MT */
