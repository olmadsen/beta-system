/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: Attach.c, rel: 1, date: 8/1/92, SID: 1.7
 * by Peter Andersen and Tommy Thorn.
 */

/* IMPORTANT NOTE: I have departed from the former practice
   of saving LSC of the caller in the called component.
   CallerLSC now always denotes the point in the code to where
   control should be transfered when the component is reactivated.
   Notice, that on the SPARC you should add 8 to this address.
*/

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamThisComp(Att)
{
    register ref(CallBackFrame)  callBackFrame asm("%l5");
    register long              * nextCompBlock asm("%l6");
    register long                level         asm("%l7");
    int first = comp->CallerLSC == 0;
/*    void (*entrypoint)();*/
    
    GCable_Entry
    FetchThisComp

    /* printf("\nAttach: comp = %x", comp); */

    Ck(comp); Ck(this);
    getret(ActiveComponent->CallerLSC);

    AssignReference((long *)&comp->CallerComp, cast(Item) ActiveComponent);
    AssignReference((long *)&comp->CallerObj, cast(Item) this);

    /* -1 tells that ActiveComponent is active */
    ActiveComponent->StackObj = cast(StackObject) -1;

    /* Push a new Component Block. */
    level = 0;
    nextCompBlock = (long *) lastCompBlock;
    callBackFrame = ActiveCallBackFrame;

    lastCompBlock = cast(ComponentBlock) StackPointer;
    ActiveCallBackFrame = 0;

    if (first) {
	ActiveComponent = comp;
	CallBetaEntry(((void (**)())(cast(Item) &comp->Body)->Proto)[-1],
		      &comp->Body);

/*	entrypoint = ((void (**)())
		      (cast(Item) &comp->Body)->Proto)[-1];
	(*entrypoint)(cast(Item) &comp->Body);  Activate the Comp */

	/* Fool gcc into believing that level, next.. is used */
	asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));

	/* TerminateComponent: */
	comp = ActiveComponent;
	ActiveComponent  = comp->CallerComp;
	this             = comp->CallerObj;
	comp->StackObj   = 0;
	comp->CallerComp = 0;
	comp->CallerObj  = 0;
	
	/* Pop the Component Block */
	ActiveCallBackFrame = callBackFrame;
	lastCompBlock = cast(ComponentBlock) nextCompBlock;
	setret(ActiveComponent->CallerLSC);
	return comp;  /* maintain %o0 ?? */
    } 
    if (comp->StackObj == 0){
      /* printf("\nAttach: comp->StackObj == 0, comp=%x", (long)comp); */
      BetaError(-2, this);
    }
    ActiveComponent = comp;

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
    
    setret(comp->CallerLSC);
    /* Fool gcc into believing that level, next.. is used */
    asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));

    return comp; /* still ?? */
}
