/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: Attach.c,v 1.13 1992-10-02 14:45:12 beta Exp $
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

ParamThisComp(struct Component *, Att)
{
    register ref(CallBackFrame)  callBackFrame asm("%l5");
    register long              * nextCompBlock asm("%l6");
    register long                level         asm("%l7");
    int first = comp->CallerLSC == 0;
    
    GCable_Entry();
    FetchThisComp
    Ck(comp); Ck(this);

    getret(ActiveComponent->CallerLSC);		/* Save our return address */

    AssignReference((long *)&comp->CallerComp, cast(Item) ActiveComponent);
    AssignReference((long *)&comp->CallerObj, cast(Item) this);

    /* -1 tells that ActiveComponent is active */
    ActiveComponent->StackObj = cast(StackObject) -1;

    /* Push a new Component Block. (It lives in our RegWin) */
    level = 0;
    nextCompBlock = (long *) lastCompBlock;
    callBackFrame = ActiveCallBackFrame;

    ActiveCallBackFrame = 0;			/* Clear the CallBackFrame list */
    lastCompBlock = cast(ComponentBlock) StackPointer;

    if (first) {
	ActiveComponent = comp;

	/* comp->Body is the Object and comp->Body->Proto[-1] is the M-entry address */
	CallBetaEntry(((void (**)())(cast(Item) &comp->Body)->Proto)[-1],
		      &comp->Body);

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
	
	/* Now correct all frame pointers in the restored stackpart */
	delta = dest - (char *)theStackObj->Body[0];
	rw = cast(RegWin) dest;
	while ((long *)rw < FramePointer) {
	    if ((rw->fp += delta) == (int)FramePointer) {
		goto ok;
	    }
	    rw = cast(RegWin) rw->fp;
	}
	fprintf(stderr, "Upps, stack handling gone crazy\n");
      ok:
	lastCompBlock = cast(ComponentBlock) rw;
	/* Update ComponentBlock in the restored RegWin */
	rw->l5 = (long) callBackFrame;
	rw->l6 = (long) nextCompBlock;
	rw->l7 = level;
	asm("ta 3");
	((char *)FramePointer) -= size;
    
	setret(comp->CallerLSC);
	/* Fool gcc into believing that level, next.. is used */
	asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));
	
	return comp; /* still ?? */
      }
}
