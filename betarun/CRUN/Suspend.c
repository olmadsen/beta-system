/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: Suspend.c,v 1.14 1992-11-06 16:55:25 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamThis(struct Component *, Susp)
{
  ref(RegWin) rw; 	/* Pointer to the saved reg.window of last frame */
  ref(Component) caller;
  ref(Component) called;
  long Size;
  ref(StackObject) theStackObj;

  GCable_Entry();
  FetchThis
  
  /* Before the block on the stack is packed, we must ensure
   * that ActiveComponent do not envolve callBacks.
   * Suspending a component involving callBacks _must_ result
   * in an error.
   */
  Ck(this);
  if (ActiveCallBackFrame) BetaError(CompCallBackErr, this);
  
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
  asm("ta 3");
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
  
  this = ActiveComponent->CallerObj;
  ActiveComponent->CallerObj =  cast(Object) 0;
  ActiveComponent->CallerComp = cast(Component) 0;
  getret(ActiveComponent->CallerLSC);
  called = ActiveComponent;
  ActiveComponent = caller;
  
  setret(ActiveComponent->CallerLSC);
  return called; /* maintain %o0 across 'call Att' */
}
