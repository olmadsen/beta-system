/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamThisComp(void, AttBC)
/* = void AttBC(struct Object *this, struct Component *comp) */
{
#ifdef sparc
    register ref(CallBackFrame) callBackFrame asm("%l5");
    register ref(RegWin)	nextCompBlock asm("%l6");
    register long 		level 	      asm("%l7");
#endif

#ifdef hppa
    long		   dummy; /* don't move without changing SnakeAdditions.S */
    struct ComponentBlock  cb
	/* Used to hold value of lastCompBlock at time of Attach.
	 * This value is used by Susp to find out which parts of
	 * machine stack and ref-stack to pack.
	 */
	/* don't move without changing SnakeAdditions.S */;
    comp = cast(Component)getCallReg();
#endif

    GCable_Entry();

    Ck(comp);

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

#ifdef crts
    lastCompBlock = (void *)RefSP;
    GetStackPointer(baseStackPtr);
    getret(comp->CallerLSC);
#endif

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

#ifdef crts
    CallBetaEntry( *((long *)((long)(BasicItem->Proto)+sizeof(struct ProtoType)+4)), &comp->Body);
#else
    /* ?? should set comp = 0 as done in AttachBasicComponent.run */
    CallBetaEntry( *((long *)BasicItem->Proto-1), &comp->Body);
#endif

    /* TerminateBasicComponent: */
    BetaExit(0);

#ifdef sparc
    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    asm(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
#endif
}

