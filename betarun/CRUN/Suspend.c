/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif

#ifdef sparc
ParamThis(struct Component *, Susp)
{
  ref(RegWin) rw; 	/* Pointer to the saved reg.window of last frame */
  ref(Component) caller;
  ref(Component) called;
  long Size;
  ref(StackObject) theStackObj;

  GCable_Entry();
  FetchThis();
  
  DEBUG_CODE(NumSusp++);

  /* Before the block on the stack is packed, we must ensure
   * that ActiveComponent do not envolve callBacks.
   * Suspending a component involving callBacks _must_ result
   * in an error.
   */
  Ck(this);
  if (ActiveCallBackFrame)
    if (SuspCont) {
      /* This is a test. On SPARC it should work to suspend components
       * even if they involve callbacks. */
      DEBUG_STACK(fprintf(stderr,
			  "Suspending component involving callback.\n"));
    } else
      BetaError(CompCallBackErr, this);
  
  
  /* This situation is this:
     sp -> Suspend..RegWin
     ..
     fp -> Caller..RegWin
     ..
     lastCompBlock -> Attach..RegWin
     ..
     lastCompBlock->fp -> CallerComp..RegWin
     */
  
  /* Pack the topmost component block into 'ActiveComponent.StackObj',
   * that is, fp to lastCompBlock->fp
   */
  
  /* Add one for the 'orig start' */
  __asm__("ta 3");
  Size = (long *) (cast(RegWin)lastCompBlock)->fp - FramePointer + 1;

  theStackObj = ActiveComponent->StackObj;
  if ((long)theStackObj == 0
      || (long)theStackObj == -1
      || Size > theStackObj->BodySize)
    {
      theStackObj = AlloSO(Size);
      AssignReference((long *)&ActiveComponent->StackObj, cast(Item) theStackObj);
    }
  /* FillStackObj */
  theStackObj->StackSize = Size;
  theStackObj->Body[0] = (long) FramePointer;
  MEMCPY(theStackObj->Body+1, FramePointer, Size*4 - 4);
  
  caller = ActiveComponent->CallerComp;
  if (caller == 0)
    /* This is the case if the basic component is suspended. */
    /* Then leave the program a nice way. */
    BetaExit(0);
  
  rw = cast(RegWin) lastCompBlock;
  ActiveCallBackFrame = cast(CallBackFrame) rw->l5;
  lastCompBlock = cast(ComponentBlock) rw->l6;	/* See AttachBasic...*/
  FramePointer = (long *) rw->fp;
  
  this = ActiveComponent->CallerObj;
  ActiveComponent->CallerObj =  cast(Object) 0;
  ActiveComponent->CallerComp = cast(Component) 0;
  /* Save %i7 (where Suspend was called from) in ActiveComponent->CallerLSC: */
  getret(ActiveComponent->CallerLSC);

  /*
   * printf("\nSuspend: ActiveComponent: 0x%08x\n", ActiveComponent);
   * printf("Suspend: ActiveComponent->CallerLSC: 0x%08x\n", ActiveComponent->CallerLSC);
   * printf("Suspend: caller: 0x%08x\n", caller);
   * printf("Suspend: caller->CallerLSC: 0x%08x\n", caller->CallerLSC);
   * fflush(stdout);
   */
  
  /* Change active component */
  called = ActiveComponent;
  ActiveComponent = caller; 

#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop((long*)ActiveComponent->CallerLSC,0,0,0,RTS_SUSPEND);
#endif

  setret(ActiveComponent->CallerLSC);
  return called; /* maintain %o0 across 'call Att' */
}
#endif /* sparc */
#endif /* MT */
