/* File: ExitObjects.c
 * $Id: ExitObjects.c,v 1.1 1992-06-06 03:36:42 beta Exp $
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExitObjects, "
	ba	_CExitObjects
	mov	%i0, %o2
");

void CExitObjects(ref(Object) exitObj, long exitAddr, ref(Object) theObj)
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

