/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExitObjects.c,v $, rel: %R%, date: $Date: 1992-07-20 11:49:06 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExitO, "
	ba	_CExitO
	mov	%i0, %o2
");

void CExitO(ref(Object) exitObj, long exitAddr, ref(Object) theObj)
{
    ref(Component) theComp;
    ref(RegWin) rw; /* Callers Register Window */

    /* We return to exitAddr */
    setret(exitAddr);

    /* We need to read the stack, thus this trap to flush regwins */
    asm("ta 3");
    rw = cast(RegWin) FramePointer;

    if (theObj == exitObj)
      return; /* to exitAddr */
    
    while ((theObj = cast(Object) rw->i0) != exitObj) {
	if (cast(Object) ActiveComponent->Body == theObj) {
	    /* Passing a component. As in AttachComponent: */
	    /* Terminate theComp. */
	    theComp = ActiveComponent;
	    ActiveComponent = theComp->CallerComp; theComp->CallerComp = 0;
	    theObj          = theComp->CallerObj;  theComp->CallerObj  = 0;
	    theComp->StackObj = 0;
	    
	    /* Pop the Component Block */
	    rw = cast(RegWin) rw->fp;		/* RegWin of CAttach */
	    ActiveCallBackFrame = cast(CallBackFrame)  rw->l5;
	    lastCompBlock       = cast(ComponentBlock) rw->l6;
	}
	/* go one step back */
	rw = cast(RegWin) rw->fp;
    }
    FramePointer = (long *) rw;
}

