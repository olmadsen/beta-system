/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Suspend.c,v $, rel: %R%, date: $Date: 1992-08-01 20:23:51 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(Component) Susp(ref(Object) theObj)
{
  ref(RegWin) rw; 	/* Pointer to the saved reg.window of last frame */
  ref(Component) caller;
  ref(Component) called;
  int Size;
  ref(StackObject) theStackObj;
  
  
  /* Before the block on the stack is packed, we must ensure
   * that ActiveComponent do not envolve callBacks.
   * Suspending a component involving callBacks _must_ result
   * in an error.
   */
  
  if (ActiveCallBackFrame) BetaError(-13, theObj);
  
  /* This situation is this:
     sp -> Suspend..RegWin
     ..
     fp -> Caller..RegWin
     ..
     lastCompBlock -> Attach..RegWin
     ..
     lastCompBlock->fp -> CallerComp..RegWin
     */
  
  /* Pack the top most component block into 'ActiveComponent.StackObj',
   * that is, fp to lastCompBlock->fp
   */
  
  /* Add one for the 'orig start' */
  asm("ta 3");
  Size = (long *) (cast(RegWin)lastCompBlock)->fp - FramePointer + 1;

  /* printf("\nSuspend: ActiveComponent = %x", ActiveComponent); */
  
  theStackObj = ActiveComponent->StackObj;
  if ((int)theStackObj == 0
      || (int)theStackObj == -1
      || Size > theStackObj->ObjectSize)
    {
      /*printf("\nSuspend: Allocating stack object for component %d", (long)ActiveComponent);*/
      theStackObj = AlloSO(5+Size);
      AssignReference((long *)&ActiveComponent->StackObj, cast(Item) theStackObj);
    }
  /* FillStackObj */
  theStackObj->StackSize = Size;
  theStackObj->Body[0] = (long) FramePointer;
  memcpy(theStackObj->Body+1, FramePointer, Size*4 - 4);
  
  caller = ActiveComponent->CallerComp;
  if (caller == 0)
    /* This is the case if the basic component is suspended. */
    /* Then leave the program a nice way. */
    BetaExit(0);
  
  rw = cast(RegWin) lastCompBlock;
  ActiveCallBackFrame = cast(CallBackFrame) rw->l5;
  lastCompBlock = cast(ComponentBlock) rw->l6;	/* See AttachBasic...*/
  FramePointer = (long *) rw->fp;
  
  theObj = ActiveComponent->CallerObj;
  ActiveComponent->CallerObj =  cast(Object) 0;
  ActiveComponent->CallerComp = cast(Component) 0;
  getret(ActiveComponent->CallerLSC);
  called = ActiveComponent;
  ActiveComponent = caller;
  setret(ActiveComponent->CallerLSC);
  return called; /* maintain %o0 across 'call Att' */
}
