/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExitObjects.c,v $, rel: %R%, date: $Date: 1992-08-24 02:31:10 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExitO, "
	mov	%i1, %o0
	mov	%i2, %o1
	b	_CExitO
	mov	%i0, %o2
");

/* Note: The offset parameter is complely ignored. It's not needed
   on the SPARC */

void CExitO(ref(Object) exitObj, long exitAddr, ref(Object) theObj)
{
    ref(Component) theComp;
    ref(RegWin) rw; /* Callers Register Window */

    Ck(exitObj); Ck(theObj);
    /* We return to exitAddr (the -8 is the SPARC convention) */
    setret(exitAddr-8);

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

