/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef crts
extern long a0;
struct Component * Susp(struct Object * this)
/* ParamThis(struct Component *, Susp) */
{
  struct Component * caller;
  struct Component * called;
  long sizeToMove, sizeOfRefStack;
  struct StackObject * theStackObj;
  long suspStackSize;
  char * suspSaveArea;
  long * newSP, *SP, *FP, RA;
  
  /* Strategy:
   *  (1) Save Susp stack area on the heap.
   *  (2) Pack current component block to stack.
   *  (3) Pack current reference stack at the same stack object as above.
   *  (4) Restore the suspend area at top of the stack at a location above the new component
   *  (5) Move the new component block from the stack object to the stack below the Susp area.
   *  (6) Restore the reference stack from the stack object.
   *  (7) Update stackpointer and framepointer according to the new stack  layout and return
   *      to the new component.
   */
  
  getret_Susp(RA); /* Fetch return address */ 

  GCable_Entry();
  Ck(this);
  push(this); /* Push this (=a0) to reference stack */

  if (ActiveCallBackFrame)
    BetaError(CompCallBackErr, this);
  ActiveComponent->CallerLSC = RA; /* Store return value in CallerLSC */

  SaveCompState_sparc(); /* Save current registers to stack */
  /* Save the Susp part of the stack */
  GetStackPointer(SP);
  GetFramePointer(FP);
  suspStackSize = ((long)FP-(long)SP)/4;
  suspSaveArea = malloc(suspStackSize*4);
  memcpy(suspSaveArea, SP+1, suspStackSize*4);

  /* Pack current component block to stack */
  theStackObj = ActiveComponent->StackObj;
  sizeToMove = ((long)baseStackPtr-(long)FP)/4; /* Number of longs on run-time stack */
  sizeOfRefStack = ((long)RefSP - (long)baseRefSP)/4; /* Number of longs on reference stack */
  if ( ((long)theStackObj == 0) || ((long)theStackObj == -1) || 
      ((sizeToMove+sizeOfRefStack) > theStackObj->BodySize) ){
    push(this);
    theStackObj = AlloSO(sizeToMove+sizeOfRefStack+1);
    pop(this);
    AssignReference((long *)&ActiveComponent->StackObj, (struct Item *) theStackObj);
  }
  theStackObj->StackSize = sizeToMove; /* Saved as longs, as GC expect this! */
  theStackObj->Body[0] = (long) FP;
  memcpy(theStackObj->Body+1, FP+1, sizeToMove*4);

  /* Pack current reference stack to stack. */
  memcpy(theStackObj->Body+1+sizeToMove, baseRefSP, sizeOfRefStack*4);
    
  caller = ActiveComponent->CallerComp;
  if (caller == 0){
    /* This is the case if the basic component is suspended. Leave the program in a nice way. */
    BetaExit(0);
  }
  if (caller->StackObj == 0){
    free(suspSaveArea);
    BetaError(CompTerminatedErr, this);
  }
  theStackObj = caller->StackObj;
  sizeToMove = theStackObj->StackSize; /* sizeToMove is now number of longs! */

  /* Restore the Susp part of the stack */
  newSP = baseStackPtr-sizeToMove;
  memcpy(newSP-suspStackSize+1, suspSaveArea, suspStackSize*4);
  SetStackPointer(newSP-suspStackSize);
  SetFramePointer(newSP);

  /* Activate new componont: caller */
  memcpy(newSP+1, theStackObj->Body+1, sizeToMove*4);
  
  /* Restore reference stack */
  sizeOfRefStack = theStackObj->BodySize-theStackObj->StackSize-1; /* In longs! */
  memcpy(baseRefSP, theStackObj->Body+1+sizeToMove, sizeOfRefStack*4);
  RefSP = baseRefSP + sizeOfRefStack;
  a0=(long)popAdr();

  ActiveComponent->CallerObj = (struct Object *)0;
  ActiveComponent->CallerComp = (struct Component *)0;
  
  /* Change active component */
  called = ActiveComponent;
  ActiveComponent = caller;
  free(suspSaveArea);

  setret_Susp(ActiveComponent->CallerLSC); 

  return called;  

}
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
  /* Save %i7 (where Suspend was called from) in ActiveComponent->CallerLSC: */
  getret(ActiveComponent->CallerLSC);

  /*
  printf("\nSuspend: ActiveComponent: 0x%08x\n", ActiveComponent);
  printf("Suspend: ActiveComponent->CallerLSC: 0x%08x\n", ActiveComponent->CallerLSC);
  printf("Suspend: caller: 0x%08x\n", caller);
  printf("Suspend: caller->CallerLSC: 0x%08x\n", caller->CallerLSC);
  fflush(stdout);
  */
  
  /* Change active component */
  called = ActiveComponent;
  ActiveComponent = caller; 
  setret(ActiveComponent->CallerLSC);
  asmemptylabel(SuspEnd);
  return called; /* maintain %o0 across 'call Att' */
}
#endif /* sparc */
