/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef crts
ParamThisComp(struct Component *, Att)
/* struct Component * Att(struct Object *this, struct Component *comp) */
{  
  /* By now the following variables are declared as locals. Should be
   * global addressable when a component stack is implemented.
   */
  register ref(CallBackFrame)  callBackFrame;
  register long              * nextCompBlock;
  register long                level; /* This is SPARC specific? Needed*/

  long first = comp->CallerLSC == 0;

  GCable_Entry();
  FetchThisComp();
  Ck(comp); 
  Ck(this);
  if (comp->StackObj == cast(StackObject) -1 || comp == ActiveComponent)
    BetaError(RecursiveAttErr, this);

  getret(ActiveComponent->CallerLSC);	/* Save our return address */
  AssignReference((long *)&comp->CallerComp, cast(Item) ActiveComponent);
  AssignReference((long *)&comp->CallerObj, cast(Item) this);
  
  /* -1 tells that ActiveComponent is active */
  ActiveComponent->StackObj = cast(StackObject) -1;
  
  /* Push a new Component Block. */
  /* This is SPARC code! The components are pushed in register windows */
  level = 0;
  nextCompBlock = (long *) lastCompBlock;
  callBackFrame = ActiveCallBackFrame;
 
  /* Clear the CallBackFrame list */
  ActiveCallBackFrame = 0;
  lastCompBlock = cast(ComponentBlock) RefSP; 

  if (first) {
    /* Hack to indicate that comp has now been attached once.
     * If this attachment of comp does not execute a suspend, there is no
     * other way to check this!
     */
    comp->CallerLSC = -1;
    ActiveComponent = comp;
    
    CallBetaEntry(*((long *)((long)((cast(Item) &comp->Body)->Proto)+sizeof(struct ProtoType)+4)), &comp->Body);
    
    /* TerminateComponent: */
    comp = ActiveComponent;
    /* printf("\nAttach: comp TERMINATED: 0x%08x\n", comp); 
    fflush(stdout); */
    ActiveComponent  = comp->CallerComp;
    this             = comp->CallerObj;
    comp->StackObj   = 0;
    comp->CallerComp = 0;
    comp->CallerObj  = 0;
    
    /* Pop the Component Block */
    ActiveCallBackFrame = callBackFrame;
    lastCompBlock = cast(ComponentBlock) nextCompBlock;
    setret(ActiveComponent->CallerLSC);
    
    return comp;  
  } 
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
