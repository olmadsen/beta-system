/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
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

    /*
    printf("\nAttachBasicComponent: comp: 0x%08x\n", comp);
    printf("AttachBasicComponent: comp->CallerLSC: 0x%08x\n", comp->CallerLSC);
    fflush(stdout);
    */

    Ck(comp);

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

#ifdef crts
    fprintf(output, "CRTS: AttBC: No ComponentBlock placed on stack (NYI)\n");
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
    cb.RefBlock = (void *)getRefSP();
    lastCompBlock = (void *)getSPReg();
    StackStart = (long)getSPReg();  /* Should be start of Ref Stack though */
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

