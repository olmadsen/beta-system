/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Attach.c,v $, rel: %R%, date: $Date: 1992-07-21 17:16:52 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

/* IMPORTANT NOTE: I have departed from the former practice
   of saving LSC of the caller in the called component.
   CallerLSC now always denotes the point in the code to where
   control should be transfered when the component is reactivated.
   Notice, that on the SPARC you should add 8 to this address.
*/

#include "beta.h"
#include "crun.h"

asmlabel(Att, "ba _CAtt; mov %i0, %o1");

void CAtt(ref(Component) theComp, ref(Object) theObj)
{
    register ref(CallBackFrame)  callBackFrame asm("%l5");
    register long              * nextCompBlock asm("%l6");
    register long                level         asm("%l7");
    int first = theComp->CallerLSC == 0;
    void (*entrypoint)();

    getret(ActiveComponent->CallerLSC);

    AssignReference((long *)theComp->CallerComp, cast(Item) ActiveComponent);
    AssignReference((long *)theComp->CallerObj, cast(Item) theObj);

    /* -1 tells that ActiveComponent is active (what else??) */
    ActiveComponent->StackObj = cast(StackObject) -1;

    /* Push a new Component Block. */
    level = 0;
    nextCompBlock = (long *) lastCompBlock;
    callBackFrame = ActiveCallBackFrame;

    lastCompBlock = cast(ComponentBlock) StackPointer;
    ActiveCallBackFrame = 0;

    if (first) {
	ActiveComponent = theComp;
	entrypoint = ((void (**)())
		      (cast(Item) &theComp->Body)->Proto)[-1];
	(*entrypoint)(cast(Item) &theComp->Body);

	/* Fool gcc into believing that level, next.. is used */
	asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));

	/* TerminateComponent: */
	theComp = ActiveComponent;
	ActiveComponent = theComp->CallerComp;
	theObj          = theComp->CallerObj;
	theComp->StackObj   = 0;
	theComp->CallerComp = 0;
	theComp->CallerObj  = 0;
	
	/* Pop the Component Block */
	ActiveCallBackFrame = callBackFrame;
	lastCompBlock = cast(ComponentBlock) nextCompBlock;
	setret(ActiveComponent->CallerLSC);
	return;
    } 
    if (theComp->StackObj == 0)
      BetaError(-2, theObj);
    ActiveComponent = theComp;

    /* Unpack 'ActiveComponent.StackObj' on top of the stack.
       
      The situation is this:

      sp ->	Attach...RegWin
      		...
      fp ->	...caller...RegWin
      		...
    */

    {
	long delta;
	char *dest;
	ref(StackObject) theStackObj = ActiveComponent->StackObj;
	int size = theStackObj->StackSize * 4 - 4;
	ref(RegWin) rw;

	((char *)StackPointer) -= size;
	dest = (char *)FramePointer - size;
	memcpy(dest, theStackObj->Body+1, size);
	
	/* Now correct all frame pointers */
	delta = dest - (char *)theStackObj->Body[0];
	rw = cast(RegWin) dest;
	while ((long *)rw < FramePointer) {
	    if ((rw->fp += delta) == (int)FramePointer) {
		lastCompBlock = cast(ComponentBlock) rw;
		goto ok;
	    }
	    rw = cast(RegWin) rw->fp;
	}
	fprintf(stderr, "Upps, stack handling gone crazy\n");
      ok:
	asm("ta 3");
	((char *)FramePointer) -= size;
    }
    
    setret(theComp->CallerLSC);
    /* Fool gcc into believing that level, next.. is used */
    asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));
}

