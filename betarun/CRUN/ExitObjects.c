/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

#ifdef sparc
asmlabel(ExO, 
	 "mov     %i1, %o1; "
	 "ba       "CPREF"ExitO; "
	 "mov     %i0, %o2; "
	 );
/* Note: The offset parameter is complely ignored. It's not needed
   on the SPARC */

void CExitO(long exitAddr, Object * exitObj, Object * theObj)
{
  Component * theComp;
  RegWin * rw;		/* Callers Register Window */

  /* Save global vars in case of error */
  Component *OrigActiveComponent          = ActiveComponent;
  CallBackFrame *OrigActiveCallBackFrame  = ActiveCallBackFrame;
  ComponentBlock *OrigLastCompBlock       = lastCompBlock;

  DEBUG_CODE(NumExO++);

  Ck(exitObj); 

  /* FIXME: Compiler currently (v384) generates offset in thoObj parameter
   * Ck(theObj);
   */

  /* We need to read the stack, thus this trap to flush regwins */
  __asm__("ta 3");
  rw = (RegWin *) FramePointer;

  if (theObj == exitObj)
    return;			/* to exitAddr */
    
  while ((theObj = (Object *) rw->i0) != exitObj) {
#ifdef LEAVE_ACROSS_CALLBACK
    if ((CallBackFrame *)rw == ActiveCallBackFrame){
      /* This is AR of HandleCB. Update ActiveCallBackFrame.   */
      ActiveCallBackFrame = (CallBackFrame *)  rw->l5;
      rw = (RegWin *)rw->l6 /* skip to betaTop */;
      DEBUG_CODE(fprintf(output, "RTS: Leaving callback.\n"));
    } else {
#endif
      /* Ordinary BETA activation record */
      if ((Object *) ActiveComponent->Body == theObj) {
	/* Passing a component. As in AttachComponent: */
	/* Terminate theComp. */
	DEBUG_CODE(NumTermComp++);
	theComp = ActiveComponent;
	if (theComp->CallerComp == 0){
	  /* Attempt to leave basic component! */
	  /* Restore global variables to ensure correct dump.
	   * FramePointer and StackPointer are still unchanged 
	   * at this point.
	   */
	  ActiveComponent     = OrigActiveComponent;
	  ActiveCallBackFrame = OrigActiveCallBackFrame;
	  lastCompBlock       = OrigLastCompBlock;
	  BetaError(LeaveBasicCompErr,theObj);
	}
	ActiveComponent = theComp->CallerComp; theComp->CallerComp = 0;
	theObj          = theComp->CallerObj;  theComp->CallerObj  = 0;
	theComp->StackObj = 0;
	
	/* Pop the Component Block */
	rw = (RegWin *) rw->fp;	/* RegWin of CAttach */
	ActiveCallBackFrame = (CallBackFrame *)  rw->l5;
	lastCompBlock       = (ComponentBlock *) rw->l6;
      } 
      /* go one step back */
      rw = (RegWin *) rw->fp;
#ifdef LEAVE_ACROSS_CALLBACK
    }
#endif
  }

  /* ActiveCallbackFrame, lastCompBlock, ActiveComponent have all
   * been incrementally updated above.
   */

  /* We return to exitAddr (the -8 is the SPARC convention) */
  setret(exitAddr-8);
  /* Unwind stack */
  FramePointer = (long *) rw;
}

#endif /* sparc */

#endif /* MT */
