/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif

#ifdef crts

#ifdef MAC
#  define SPStartOff 0
#else
#  define SPStartOff 1
#endif

extern long a0;
extern void PackAndFreeJmpBuf(long);
extern void UnPackAndAllocateJmpBuf(long, long);
extern long GetJumpStackSize(void);

struct Component * Susp(struct Object * this)
/* ParamThis(struct Component *, Susp) */
{
  struct Component * caller;
  struct Component * called;
  long sizeToMove, sizeOfRefStack;
  long jump_stack_size;
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
  suspSaveArea = MALLOC(suspStackSize*4);
  INFO_ALLOC(suspStackSize*4);
  MEMCPY(suspSaveArea, SP+SPStartOff, suspStackSize*4);

  /* Pack current component block to stack */
  theStackObj = ActiveComponent->StackObj;
  sizeToMove = ((long)baseStackPtr-(long)FP)/4; /* Number of longs on run-time stack */
  sizeOfRefStack = ((long)RefSP - (long)baseRefSP)/4; /* Number of longs on reference stack */
  jump_stack_size = GetJumpStackSize();
  
  DEBUG_IOA(fprintf(output,"Suspend: stacksize: %d\n",jump_stack_size));

  if ( ((long)theStackObj == 0) || ((long)theStackObj == -1) || 
      ((sizeToMove+jump_stack_size+sizeOfRefStack) > theStackObj->BodySize) ){
    push(this);
    theStackObj = AlloSO(sizeToMove+jump_stack_size+sizeOfRefStack+1);
    pop(this);
    AssignReference((long *)&ActiveComponent->StackObj, (struct Item *) theStackObj);
  }
    /* Save as number of longs as GC expects this! */
  theStackObj->StackSize = sizeToMove+jump_stack_size; /* Saved as longs, as GC expect this! */
  theStackObj->Body[0] = sizeToMove; /* save size of machine stack; was FP(not used?) */
  MEMCPY(theStackObj->Body+1, FP+SPStartOff, sizeToMove*4);

  /* save jump stack from Misc.c */
  PackAndFreeJmpBuf(&theStackObj->Body[1+sizeToMove]); 
	
  /* Pack current reference stack to stack. */
  MEMCPY(theStackObj->Body+1+sizeToMove+jump_stack_size, baseRefSP, sizeOfRefStack*4);
    
  caller = ActiveComponent->CallerComp;
  if (caller == 0){
    /* This is the case if the basic component is suspended. Leave the program in a nice way. */
    BetaExit(0);
  }
  if (caller->StackObj == 0){
    FREE(suspSaveArea);
    BetaError(CompTerminatedErr, this);
  }
  theStackObj = caller->StackObj;
  caller->StackObj = cast(StackObject) 0; /* clear cell for b2c */
  jump_stack_size = theStackObj->StackSize; /* jump_stack_size is sum of machine and jump stack */
  sizeToMove = theStackObj->Body[0];
  jump_stack_size = jump_stack_size - sizeToMove;

  /* Restore the Susp part of the stack */
  newSP = baseStackPtr-sizeToMove;
  MEMCPY(newSP-suspStackSize+SPStartOff, suspSaveArea, suspStackSize*4);
  SetStackPointer(newSP-suspStackSize);
  SetFramePointer(newSP);

  /* Activate new componont: caller */
  MEMCPY(newSP+SPStartOff, theStackObj->Body+1, sizeToMove*4);
  
  /* Restore jump stack. no_of_buffers is first */
  UnPackAndAllocateJmpBuf(&theStackObj->Body[1+sizeToMove+1], theStackObj->Body[1+sizeToMove]);

  /* Restore reference stack */
  sizeOfRefStack = theStackObj->BodySize-theStackObj->StackSize-1; /* In longs! */
  MEMCPY(baseRefSP, theStackObj->Body+1+sizeToMove+jump_stack_size, sizeOfRefStack*4);
  RefSP = baseRefSP + sizeOfRefStack;
  a0=(long)popAdr();

  ActiveComponent->CallerObj = (struct Object *)0;
  ActiveComponent->CallerComp = (struct Component *)0;
  
  /* Change active component */
  called = ActiveComponent;
  ActiveComponent = caller;
  FREE(suspSaveArea);

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
  printf("\nSuspend: ActiveComponent: 0x%08x\n", ActiveComponent);
  printf("Suspend: ActiveComponent->CallerLSC: 0x%08x\n", ActiveComponent->CallerLSC);
  printf("Suspend: caller: 0x%08x\n", caller);
  printf("Suspend: caller->CallerLSC: 0x%08x\n", caller->CallerLSC);
  fflush(stdout);
  */
  
  /* Change active component */
  called = ActiveComponent;
  ActiveComponent = caller; 

#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop (ActiveComponent->CallerLSC,0,0,0,RTS_SUSPEND);
#endif

  setret(ActiveComponent->CallerLSC);
  asmemptylabel(SuspEnd);
  return called; /* maintain %o0 across 'call Att' */
}
#endif /* sparc */
