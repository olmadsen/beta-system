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

  /* FIXME: Compiler currently (v384) generates offset in theObj parameter
   * Ck(theObj);
   */

#if 0
  fprintf(output, "\nExO: ");
  fprintf(output, "\n  exitAddr:"); PrintCodeAddress((long)exitAddr);
  fprintf(output, "\n  exitObj: "); PrintObject(exitObj);
  fprintf(output, "\n  theObj:  "); PrintObject(theObj);
  fprintf(output, "\n");
  fflush(output);
#define TRACE_EXO() \
 fprintf(output, "File %s; Line %d", __FILE__, __LINE__);       \
 fprintf(output, "\nNew RegWin: 0x%08x", (int)rw);              \
 fprintf(output, "\nNew object:"); PrintObject(theObj);            \
 fprintf(output, "\n");                                         \
 fflush(output)
 
#else
#define TRACE_EXO()
#endif

  /* We need to read the stack, thus this trap to flush regwins */
  __asm__("ta 3");

  /* Start from framepointer (skip frame of CExitO) */
  rw = (RegWin *) FramePointer;

  if (theObj == exitObj)
    return;			/* to exitAddr */
    
  while ((theObj = (Object *) rw->i0) != exitObj) {
#ifdef LEAVE_ACROSS_CALLBACK
    if ((CallBackFrame *)rw == ActiveCallBackFrame){
      DEBUG_CODE(fprintf(output, "ExO: Passing callback\n"));;
      DEBUG_CODE(fflush(output));
      /* This is AR of HandleCB. Update ActiveCallBackFrame.   */
      ActiveCallBackFrame = (CallBackFrame *)  rw->l5;
      rw = (RegWin *)rw->l6 /* skip to betaTop */;
    } else {
#endif
      /* Ordinary BETA activation record */
      if ((Object *) ActiveComponent->Body == theObj) {
	/* Passing a component. As in AttachComponent: */
	/* Terminate theComp. */
	DEBUG_CODE(NumTermComp++);
	theComp = ActiveComponent;
	DEBUG_CODE(fprintf(output, "ExO: passing comp 0x%x\n", (int)theComp));
	DEBUG_CODE(fflush(output));
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
    TRACE_EXO();
  }

  /* ActiveCallbackFrame, lastCompBlock, ActiveComponent have all
   * been incrementally updated above.
   */

  /* We return to exitAddr (the -8 is the SPARC convention) */
  setret(exitAddr-8);
  /* Unwind stack */
  FramePointer = (long *) rw;
  return; /* Will jump to exitAddr and restore SP from FramePointer */
}

#endif /* sparc */

#endif /* MT */
