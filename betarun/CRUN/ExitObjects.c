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
  RegWin *rw;		    /* Callers Register Window */

  /* Save global vars in case of error */
  Component *theComp        = ActiveComponent;
  RegWin    *nextCBF        = (RegWin*)ActiveCallBackFrame;
  RegWin    *nextCompBlock  = (RegWin*)lastCompBlock;
  Component *nextComp;

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
 fprintf(output, "\nNew object:"); PrintObject(theObj);         \
 fprintf(output, "\n");                                         \
 fflush(output)
 
#else
#define TRACE_EXO()
#endif

  /* We need to read the stack, thus this trap to flush regwins */
  __asm__("ta 3");

  /* Start from framepointer (skip frame of CExitO) */
  rw = (RegWin *) FramePointer;

  if (theObj == exitObj) return; /* to exitAddr */
    
  while ((theObj = (Object *) rw->i0) != exitObj) {
#ifdef LEAVE_ACROSS_CALLBACK
    if (rw == nextCBF){
      DEBUG_STACK({
	fprintf(output, "ExO: Passing callback\n");
	fflush(output);
      });
      /* This is AR of HandleCB. Update nextCBF.   */
      nextCBF = (CallBackFrame *)  rw->l5;
      rw = (RegWin *)rw->l6 /* skip to betaTop */;
      TRACE_EXO();
      continue;
    } 
#endif
    /* Ordinary BETA activation record */
    if (rw == nextCompBlock) {
      /* Passing a component, this is the RegWin of CAttach */
      /* Terminate theComp as in AttachComponent: */
      DEBUG_STACK({
	fprintf(output, "ExO: passing comp 0x%x\n", (int)theComp);
	fflush(output);
      });
      if (theComp->CallerComp == 0){
	/* Attempt to leave basic component! */
	BetaError(LeaveBasicCompErr,theObj);
      }
      DEBUG_CODE(NumTermComp++);
      theObj = theComp->CallerObj;  
      theComp->CallerObj  = 0;
      theComp->StackObj = 0;
      nextComp = theComp->CallerComp; 
      theComp->CallerComp = 0;
      theComp = nextComp;

      /* Pop the Component Block */
      nextCBF       = (RegWin *) rw->l5;
      nextCompBlock = (RegWin *) rw->l6;
      rw = (RegWin *) rw->fp; 
      TRACE_EXO();
      continue;
    } 
    
    /* go one step back */
    rw = (RegWin *) rw->fp;
    TRACE_EXO();
    continue;
  }

  /* Update global variables */
  lastCompBlock       = (ComponentBlock*)nextCompBlock;
  ActiveCallBackFrame = (CallBackFrame*)nextCBF;
  ActiveComponent     = theComp;

  /* We return to exitAddr (the -8 is the SPARC convention) */
  setret(exitAddr-8);
  /* Unwind stack */
  FramePointer = (long *) rw;
  return; /* Will jump to exitAddr and restore SP from FramePointer */
}




/**************** NEW VERSION(s) ******************/

/* ExOx(exitAddr, exitObject)
   - pop stack until *and including* exitObject stack frame
*/

asmlabel(ExOx, 
	 "mov     %i1, %o1; "
	 "ba       "CPREF"ExitOx; "
	 "mov     %i0, %o2; "
	 );
/* Note: The offset parameter is complely ignored. It's not needed
   on the SPARC */

void CExitOx(long exitAddr, Object * exitObj, Object * theObj)
{
  RegWin *rw;		    /* Callers Register Window */

  /* Save global vars in case of error */
  Component *theComp        = ActiveComponent;
  RegWin    *nextCBF        = (RegWin*)ActiveCallBackFrame;
  RegWin    *nextCompBlock  = (RegWin*)lastCompBlock;
  Component *nextComp;

  DEBUG_CODE(NumExO++);

  Ck(exitObj); 

  /* FIXME: Compiler currently (v384) generates offset in theObj parameter
   * Ck(theObj);
   */

#if 1
  fprintf(output, "\nExO: ");
  fprintf(output, "\n  exitAddr:"); PrintCodeAddress((long)exitAddr);
  fprintf(output, "\n  exitObj: "); PrintObject(exitObj);
  fprintf(output, "\n  theObj:  "); PrintObject(theObj);
  fprintf(output, "\n");
  fflush(output);
#define TRACE_EXOX() \
 fprintf(output, "File %s; Line %d", __FILE__, __LINE__);       \
 fprintf(output, "\nNew RegWin: 0x%08x", (int)rw);              \
 fprintf(output, "\nNew object:"); PrintObject(theObj);         \
 fprintf(output, "\n");                                         \
 fflush(output)
 
#else
#define TRACE_EXOX()
#endif

  /* We need to read the stack, thus this trap to flush regwins */
  __asm__("ta 3");

  /* Start from framepointer (skip frame of CExitO) */
  rw = (RegWin *) FramePointer;

  while ((theObj = (Object *) rw->i0) != exitObj) {
#ifdef LEAVE_ACROSS_CALLBACK
    if (rw == nextCBF){
      /* This is AR of HandleCB. Skip to betaTop and update nextCBF */
      DEBUG_STACK({
	fprintf(output, "ExO: Passing callback\n");
	fflush(output);
      });
      /* This is AR of HandleCB. Update nextCBF.   */
      nextCBF = (CallBackFrame *)  rw->l5;
      rw = (RegWin *)rw->l6 /* skip to betaTop */;
      TRACE_EXOX();
      continue;
    } 
#endif
    if (rw == nextCompBlock) {
      /* This is the AR of attach. Continue, but get
       * new values for nextCompBlock and nextCBF. 
       */
      /* Terminate theComp as in AttachComponent: */
      DEBUG_STACK({
	fprintf(output, "ExO: passing comp 0x%x\n", (int)theComp);
	fflush(output);
      });
      if (theComp->CallerComp == 0){
	/* Attempt to leave basic component! */
	BetaError(LeaveBasicCompErr,theObj);
      }
      DEBUG_CODE(NumTermComp++);
      theObj = theComp->CallerObj;  
      theComp->CallerObj  = 0;
      theComp->StackObj = 0;
      nextComp = theComp->CallerComp; 
      theComp->CallerComp = 0;
      theComp = nextComp;

      /* Pop the Component Block */
      nextCBF       = (RegWin *) rw->l5;
      nextCompBlock = (RegWin *) rw->l6;
      rw = (RegWin *) rw->fp; 
      TRACE_EXOX();
      continue;
    } 

    /* Normal Frame - investigate stack part for INNER chains.
     */
    
    
    /* go one step back */
    rw = (RegWin *) rw->fp;
    theObj = (Object *) rw->i0;
    TRACE_EXOX();
    continue;
  }

  /* ExOx: go one more step back */
  rw = (RegWin *) rw->fp;
  TRACE_EXOX();

  /* Update global variables */
  lastCompBlock       = (ComponentBlock*)nextCompBlock;
  ActiveCallBackFrame = (CallBackFrame*)nextCBF;
  ActiveComponent     = theComp;

  /* We return to exitAddr (the -8 is the SPARC convention) */
  setret(exitAddr-8);
  /* Unwind stack */
  FramePointer = (long *) rw;
  return; /* Will jump to exitAddr and restore SP from FramePointer */
}


/******** Below version not (yet) used! ***********/


static void ProcessExitStackCell(Object **theCell,Object *theObj)
{
}

static Component *SavedComp;
static RegWin    *SavedCBF;
static RegWin    *SavedCompBlock;
static Object    *ExitObj;


void CExitOx1(long exitAddr, Object * exitObj, Object * theObj)
{
  DEBUG_CODE(NumExO++);

  Ck(exitObj); 

  /* FIXME: Compiler currently (v384) generates offset in theObj parameter
   * Ck(theObj);
   */

  /* Put things in global vars */
  SavedComp       = ActiveComponent;
  SavedCBF        = (RegWin*)ActiveCallBackFrame;
  SavedCompBlock  = (RegWin*)lastCompBlock;
  ExitObj         = exitObj;

  GeneralProcessStack(ProcessExitStackCell);

  /* For this to work, GeneralProcessStack (and ProcessAR) must have a 
   * CurrentOnly flag (like NEWRUN dynOnly).
   */

}

#endif /* sparc */

#endif /* MT */
