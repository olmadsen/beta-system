/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module
#include "beta.h"
#include "crun.h"

#ifdef sparc

asmlabel(ExO, "
        mov     %i1, %o1
        ba       "CPREF"ExitO
        mov     %i0, %o2
");
/* Note: The offset parameter is complely ignored. It's not needed
   on the SPARC */

void CExitO(long exitAddr, ref(Object) exitObj, ref(Object) theObj)
{
    ref(Component) theComp;
    ref(RegWin) rw; /* Callers Register Window */

    GCable_Entry();

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
	    if (theComp->CallerComp == 0){
	       /* attempt to leave basic component! */
	       BetaError(LeaveBasicCompErr,theObj);
	    }
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

#endif /* sparc */
