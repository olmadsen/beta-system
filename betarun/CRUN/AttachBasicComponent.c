/* File: AttachBasicComponent.c
 * $Id: AttachBasicComponent.c,v 1.1 1992-06-06 03:36:35 beta Exp $
 */

#include "beta.h"
#include "crun.h"

static TerminateBasicComponent() { BetaExit(0); }

void AttachBasicComponent(ref(Component) theComp)
{
    register void (*entrypoint)();

    register ref(CallBackFrame) callBackFrame asm("%l5");
    register ref(RegWin)	nextCompBlock asm("%l6");
    register long 		level 	      asm("%l7");

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    StackStart = StackPointer;

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

