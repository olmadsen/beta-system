/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef crts
extern long a0;
struct Component * Att(struct Object *this, struct Component *comp)
/* ParamThisComp(struct Component *, Att) */
{  
  long first =  comp->CallerLSC == 0;
  long attachStackSize;
  long sizeToMove, sizeOfRefStack;
  char * attachSaveArea;
  struct StackObject * theStackObj;
  long * newSP, *SP, *FP, RA;

  getret(RA); /* Fetch return address */
    
  /* fprintf(output, "\n Attach: Activecomponent: 0x%x \n", (int)ActiveComponent);
  fprintf(output, " Attach: component: 0x%x \n",(int)comp); */

  GCable_Entry();
  FetchThisComp();
  Ck(comp); 
  Ck(this);
  push(this); /* Push this (=a0) to refrence stack */

  if (comp->StackObj == cast(StackObject) -1 || comp == ActiveComponent)
    BetaError(RecursiveAttErr, this);
  ActiveComponent->CallerLSC = RA;	/* Save our return address */

  AssignReference((long *)&comp->CallerComp, cast(Item) ActiveComponent);
  AssignReference((long *)&comp->CallerObj, cast(Item) this);
  
  /* -1 tells that ActiveComponent is active */
  ActiveComponent->StackObj = cast(StackObject) -1; 
  
  if (first) {
    /* Hack to indicate that comp has now been attached once.
     * If this attachment of comp does not execute a suspend, there is no
     * other way to check this!
     */
    comp->CallerLSC = -1;

    SaveCompState_sparc(); /* Save registers of current component on stack */
    /* Pack current component block to stack */
    theStackObj = ActiveComponent->StackObj;
    GetFramePointer(FP);
    sizeToMove = ((long)baseStackPtr-(long)FP)/4;/*Number of longs on run-time stack */
    sizeOfRefStack = ((long)RefSP - (long)baseRefSP)/4; /* Number of longs on reference stack */
    if ( ((long)theStackObj == 0) || ((long)theStackObj == -1) || 
	((sizeToMove+sizeOfRefStack) > theStackObj->BodySize) ){
      push(comp);
      push(this);
      theStackObj = AlloSO(sizeToMove+sizeOfRefStack+1);
      pop(this);
      pop(comp);
      AssignReference((long *)&(ActiveComponent->StackObj), (struct Item *) theStackObj);
    }
    /* Save as number of longs as GC expects this! */
    theStackObj->StackSize = sizeToMove; 

    theStackObj->Body[0] = (long) FP; 
    memcpy(theStackObj->Body+1, FP+1, sizeToMove*4);

    /* Save referene stack */
    memcpy(theStackObj->Body+1+sizeToMove, baseRefSP, sizeOfRefStack*4);

    /* fprintf(output," Attach: ActiveComponent->StackObj = 0x%x \n",(int)ActiveComponent->StackObj); */

    ActiveComponent = comp;

    /* Move the Att part of the stack to the bottom of the stack */
    GetStackPointer(SP);
    attachStackSize = ((long)FP-(long)SP)/4;

    memcpy(baseStackPtr-attachStackSize+1, SP+1, attachStackSize*4);
    SetFramePointer(baseStackPtr);
    SetStackPointer(baseStackPtr - attachStackSize);

    push(this);
    CallBetaEntry(*((long *)((long)((cast(Item) &comp->Body)->Proto)+sizeof(struct ProtoType)+4)), &comp->Body);
    pop(this);

    /* When the attached component terminates the following code is executed.  */

    comp = ActiveComponent;
    a1 = (long)ActiveComponent;
    ActiveComponent = comp->CallerComp;
    a0 = (long)comp->CallerObj;

    SaveCompState_sparc(); /* Save current registers to stack */
    /* Save the Attach part of the stack */
    GetStackPointer(SP);
    GetFramePointer_Att(FP);
    attachStackSize = ((long)FP-(long)SP)/4;
    attachSaveArea = malloc(attachStackSize);
    memcpy(attachSaveArea, SP+1, attachStackSize*4);
  
    if (ActiveComponent->StackObj == (struct StackObject *)0){
      free(attachSaveArea);
      BetaError(CompTerminatedErr, this);
    }
    theStackObj = ActiveComponent->StackObj;
    sizeToMove = theStackObj->StackSize; /* SizeToMove now number of longs */

    /* Restore the Attach part of the stack */
    newSP = baseStackPtr-sizeToMove;
    memcpy(newSP-attachStackSize+1, attachSaveArea, attachStackSize*4);
    free(attachSaveArea);
    SetFramePointer(newSP);
    SetStackPointer(newSP - attachStackSize);

    /* Activate new componont */
    memcpy(newSP+1, theStackObj->Body+1, sizeToMove*4);

    /* Restore reference stack */
    sizeOfRefStack = theStackObj->BodySize-theStackObj->StackSize-1; /* In longs ! */
    memcpy(baseRefSP, theStackObj->Body+1+sizeToMove, sizeOfRefStack*4);
    RefSP = baseRefSP + sizeOfRefStack;
    a0=(long)popAdr();

    /* fprintf(output,"\nAttach: comp TERMINATED: 0x%08x\n", (int)comp); 
    fflush(stdout); */

    /* TerminateComponent: */
    comp->StackObj   = 0;
    comp->CallerComp = 0;
    comp->CallerObj  = 0;
    
    setret(ActiveComponent->CallerLSC);
    return comp;  
  }
  /* This is what happens below:
   * (1) Save the Att part of the stack.
   * (2) Move the component block and activations to the stack.
   * (3) Save the reference stack in the stack object belowe the runtime activations.
   * (4) Restore the Att part of the stack at a location above the new component block.
   * (5) Move the new component block from the heap to the stack.
   * (6) Restore the component stack.
   * (7) Restore stackpointer and framepointer according to the new stack layout and
   *     set return address to the new component.
   * (8) Return to the new component.
   */

  SaveCompState_sparc(); /* Save current registers to stack */
  /* Save the Attach part of the stack */
  GetStackPointer(SP);
  GetFramePointer(FP);
  attachStackSize = ((long)FP-(long)SP)/4;
  attachSaveArea = malloc(attachStackSize*4);
  memcpy(attachSaveArea, SP+1, attachStackSize*4);
  
  /* Pack current component block to stack */
  theStackObj = ActiveComponent->StackObj;
  sizeToMove = ((long)baseStackPtr-(long)FP)/4; /* Number of longs on run-time stack */
  sizeOfRefStack = ((long)RefSP - (long)baseRefSP)/4; /* Number of longs on reference stack */
  if ( ((long)theStackObj == 0) || ((long)theStackObj == -1) || 
      ((sizeToMove+sizeOfRefStack) > theStackObj->BodySize) ){
    push(this); push(comp);
    theStackObj = AlloSO(sizeToMove+sizeOfRefStack+1);
    pop(comp); pop(this);
    AssignReference((long *)&(ActiveComponent->StackObj), (struct Item *) theStackObj);
  }
  theStackObj->StackSize = sizeToMove; /* Saved as number of longs, as GC expect this ! */
  theStackObj->Body[0] = (long)FP;
  memcpy(theStackObj->Body+1, FP+1, sizeToMove*4);
  memcpy(theStackObj->Body+1+sizeToMove, baseRefSP, sizeOfRefStack*4);
  
  ActiveComponent = comp;
  if (ActiveComponent->StackObj == (struct StackObject *)0){
    free(attachSaveArea);
    BetaError(CompTerminatedErr, this);
  }
  theStackObj = ActiveComponent->StackObj;
  sizeToMove = theStackObj->StackSize; /* sizeToMove now number of longs! */
  
  /* Restore the Attach part of the stack */
  newSP = baseStackPtr-sizeToMove;
  memcpy(newSP-attachStackSize+1, attachSaveArea, attachStackSize*4);
  SetStackPointer(newSP - attachStackSize);
  SetFramePointer(newSP);
  free(attachSaveArea);
  
  /* Activate new componont */
  memcpy(newSP+1, theStackObj->Body+1, sizeToMove*4);

  /* Restore reference stack */
  sizeOfRefStack = theStackObj->BodySize-theStackObj->StackSize-1; /* In longs! */
  RefSP = baseRefSP + sizeOfRefStack;
  memcpy(baseRefSP, theStackObj->Body+1+sizeToMove, sizeOfRefStack*4);
  a0=(long)popAdr();

  setret(comp->CallerLSC);
  return comp;
}
#endif

#ifdef sparc

/* IMPORTANT NOTE: I have departed from the former practice
   of saving LSC of the caller in the called component.
   CallerLSC now always denotes the point in the code to where
   control should be transfered when the component is reactivated.
   Notice, that on the SPARC you should add 8 to this address.
   */

ParamThisComp(struct Component *, Att)
{
  register ref(CallBackFrame)  callBackFrame asm("%l5");
  register long              * nextCompBlock asm("%l6");
  register long                level         asm("%l7");
  long first = comp->CallerLSC == 0;
  
  register long              * tmp asm("%i1") 
    /* Needed for lastCompBlock assignment */;
  
  GCable_Entry();
  FetchThisComp();
  Ck(comp); Ck(this);
  
  if (comp->StackObj == cast(StackObject) -1 || comp == ActiveComponent)
    BetaError(RecursiveAttErr, this);
  
  /*
  printf("\nAttach: comp: 0x%08x\n", comp);
  printf("Attach: comp->CallerLSC: 0x%08x\n", comp->CallerLSC);
  printf("Attach: ActiveComponent: 0x%08x\n", ActiveComponent);
  printf("Attach: ActiveComponent->CallerLSC: 0x%08x\n", ActiveComponent->CallerLSC);
  fflush(stdout);
  */

  getret(ActiveComponent->CallerLSC);		/* Save our return address */
  
  AssignReference((long *)&comp->CallerComp, cast(Item) ActiveComponent);
  AssignReference((long *)&comp->CallerObj, cast(Item) this);
  
  /* -1 tells that ActiveComponent is active */
  ActiveComponent->StackObj = cast(StackObject) -1;
  
  /* Push a new Component Block. (It lives in our RegWin) */
  level = 0;
  nextCompBlock = (long *) lastCompBlock;
  /* Fool gcc into believing that %i1 is used */
  asm(""::"r" (tmp));
  callBackFrame = ActiveCallBackFrame;
  /* Fool gcc into believing that %i1 is used */
  asm(""::"r" (tmp));
  
  ActiveCallBackFrame = 0;		    /* Clear the CallBackFrame list */
  /* Fool gcc into believing that %i1 is used */
  asm(""::"r" (tmp));
  lastCompBlock = cast(ComponentBlock) StackPointer;
  /* Fool gcc into believing that %i1 is used */
  asm(""::"r" (tmp));
  
  if (first) {
    /* Hack to indicate that comp has now been attached once.
     * If this attachment of comp does not execute a suspend, there is no
     * other way to check this!
     */
    comp->CallerLSC = -1;

    ActiveComponent = comp;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    
    asmemptylabel(AttFirst);
    /* comp->Body is the Object and comp->Body->Proto[-1] is the M-entry address */
    CallBetaEntry(((void (**)())(cast(Item) &comp->Body)->Proto)[-1],
		  &comp->Body);
    
    /* Fool gcc into believing that level, next.. is used */
    asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));
    
    /* TerminateComponent: */
    comp = ActiveComponent;
    /*printf("\nAttach: comp TERMINATED: 0x%08x\n", comp);*/
    fflush(stdout);
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    ActiveComponent  = comp->CallerComp;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    this             = comp->CallerObj;
    comp->StackObj   = 0;
    comp->CallerComp = 0;
    comp->CallerObj  = 0;
    
    /* Pop the Component Block */
    ActiveCallBackFrame = callBackFrame;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    lastCompBlock = cast(ComponentBlock) nextCompBlock;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    setret(ActiveComponent->CallerLSC);
    
    asmemptylabel(AttEnd);
    return comp;  /* maintain %o0 ?? */
  } 
  if (comp->StackObj == 0){
    /* printf("\nAttach: comp->StackObj == 0, comp=%x", (long)comp); */
    BetaError(CompTerminatedErr, this);
  }
  ActiveComponent = comp;
  /* Fool gcc into believing that %i1 is used */
  asm(""::"r" (tmp));
  
  /* Unpack 'ActiveComponent.StackObj' on top of the stack.
     
     The situation is this:
     
     sp ->	Attach...RegWin
     ...
     fp ->	...caller...RegWin
     ...
     */
  
  {
    long delta;
    char *dest;
    ref(StackObject) theStackObj = ActiveComponent->StackObj;
    long size = theStackObj->StackSize * 4 - 4;
    ref(RegWin) rw;
    
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    
    ((char *)StackPointer) -= size;
    dest = (char *)FramePointer - size;
    memcpy(dest, theStackObj->Body+1, size);
    
    /* Now correct all frame pointers in the restored stackpart */
    delta = dest - (char *)theStackObj->Body[0];
    rw = cast(RegWin) dest;
    while ((long *)rw < FramePointer) {
      if ((rw->fp += delta) == (long)FramePointer) {
	goto ok;
      }
      rw = cast(RegWin) rw->fp;
    }
#ifdef RTDEBUG
    fprintf(stderr, "Upps, stack handling gone crazy\n");
#endif
  ok:
    lastCompBlock = cast(ComponentBlock) rw;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    /* Update ComponentBlock in the restored RegWin */
    rw->l5 = (long) callBackFrame;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    rw->l6 = (long) nextCompBlock;
    /* Fool gcc into believing that %i1 is used */
    asm(""::"r" (tmp));
    rw->l7 = level;
    asm("ta 3");
    ((char *)FramePointer) -= size;
    
    setret(comp->CallerLSC);
    /* Fool gcc into believing that level, next.. is used */
    asm(""::"r" (level), "r" (nextCompBlock), "r" (callBackFrame));
    
    asmemptylabel(AttSecond);
    return comp; /* still ?? */
  }
}
#endif /* sparc */
