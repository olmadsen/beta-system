/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

#ifdef sparc

#if 0 
#define TRACE_ATTACH() \
{ printf("\nAttach: comp: 0x%08x\n", comp); \
  printf("Attach: comp->CallerLSC: 0x%08x\n", comp->CallerLSC); \
  printf("Attach: ActiveComponent: 0x%08x\n", ActiveComponent); \
  printf("Attach: ActiveComponent->CallerLSC: 0x%08x\n", ActiveComponent->CallerLSC); \
  fflush(stdout); \
}
#else
#define TRACE_ATTACH()
#endif

#define CLOBBER(var) \
  /* Fool gcc into believing that var is used */ \
  __asm__(""::"r" (var))

#define FLUSH_REGWINS() \
  __asm__("ta 3")

#define ASM_ASSIGN(var, val) \
  __asm__ volatile ("mov %1,%0": "=r" (var): "r" (val))
 

/* IMPORTANT NOTE: I have departed from the former practice
   of saving LSC of the caller in the called component.
   CallerLSC now always denotes the point in the code to where
   control should be transfered when the component is reactivated.
   Notice, that on the SPARC you should add 8 to this address.
   */

ParamThisComp(Component *, Att)
{
  long * entryAdr;
  register CallBackFrame *callBackFrame __asm__("%l5");
  register long          *nextCompBlock __asm__("%l6");
  register long           level         __asm__("%l7");
  long first = comp->CallerLSC == 0;
  
  register long          *tmp __asm__("%i1") 
    /* Needed for lastCompBlock assignment */;
  
  FetchThisComp();

  DEBUG_CODE(NumAtt++);

  Ck(comp); Ck(this);
  
  if (comp->StackObj == (StackObject *) -1)
    BetaError(RecursiveAttErr, this);
  if ((!first) && (comp->StackObj == 0)){
    /* printf("\nAttach: comp->StackObj == 0, comp=%x", (long)comp); */
    BetaError(CompTerminatedErr, this);
  }
  
  TRACE_ATTACH();
  getret(ActiveComponent->CallerLSC);		/* Save our return address */
  
  AssignReference((long *)&comp->CallerComp, (Item *) ActiveComponent);
  AssignReference((long *)&comp->CallerObj, (Item *) this);
  
  /* -1 tells that ActiveComponent is active */
  DEBUG_CODE({
    if (ActiveComponent 
	&& ActiveComponent->StackObj 
	&& (long)ActiveComponent->StackObj != -1) {
      ActiveComponent->StackObj->StackSize=0;
    }
  });
  ActiveComponent->StackObj = (StackObject *) -1;
  
  /* Push a new Component Block. (It lives in our RegWin) */
  /* level = 0; */
  /* nextCompBlock = (long *) lastCompBlock; */
  ASM_ASSIGN(nextCompBlock, lastCompBlock);
  /* callBackFrame = ActiveCallBackFrame; */
  ASM_ASSIGN(callBackFrame, ActiveCallBackFrame);
  
  ActiveCallBackFrame = 0; /* Clear the CallBackFrame list */
  CLOBBER(tmp);
  lastCompBlock = (ComponentBlock *) StackPointer;
  CLOBBER(tmp);
  
  if (first) {
    /* Hack to indicate that comp has now been attached once.
     * If this attachment of comp does not execute a suspend, there is no
     * other way to check this!
     */
    comp->CallerLSC = (pc_t)-1;

    /* Indicate that comp is now active */
    comp->StackObj = (StackObject *) -1;

    ActiveComponent = comp;
    CLOBBER(tmp);
    
    entryAdr = (long*)OBJPROTOFIELD(ComponentItem(comp), TopMpart);

#ifdef RTVALHALLA
    if (valhallaIsStepping) {
      ValhallaCallBetaEntry(entryAdr, ComponentItem(comp), RTS_ATTACH);
    } else {
      CallBetaEntry(entryAdr, ComponentItem(comp));
    }
#else
    CallBetaEntry(entryAdr, ComponentItem(comp));
#endif

    CLOBBER(level);
    CLOBBER(nextCompBlock);
    CLOBBER(callBackFrame);

    /* TerminateComponent: */
    DEBUG_CODE(NumTermComp++);
    comp = ActiveComponent;
    /* printf("\nAttach: comp TERMINATED: 0x%08x\n", comp);
     * fflush(stdout);
     */
    CLOBBER(tmp);
    ActiveComponent  = comp->CallerComp;
    CLOBBER(tmp);
    this             = comp->CallerObj;
    comp->StackObj   = 0;
    comp->CallerComp = 0;
    comp->CallerObj  = 0;
    
    /* Pop the Component Block */
    ActiveCallBackFrame = callBackFrame;
    CLOBBER(tmp);
    lastCompBlock = (ComponentBlock *) nextCompBlock;
    CLOBBER(tmp);
    setret(ActiveComponent->CallerLSC);
    
    return comp;  /* maintain %o0 ?? */
  } /* End first */

  ActiveComponent = comp;
  CLOBBER(tmp);
  
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
    StackObject * theStackObj = ActiveComponent->StackObj;
    long size = theStackObj->StackSize * 4 - 4;
    RegWin * rw;

    ActiveComponent->StackObj = (StackObject *) -1;
    
    CLOBBER(tmp);
    
    StackPointer = (long*)((char *)StackPointer - size);
    dest = (char *)FramePointer - size;
    memcpy(dest, theStackObj->Body+1, size);
    
    /* Now correct all frame pointers in the restored stackpart */
    delta = dest - (char *)theStackObj->Body[0];
    rw = (RegWin *) dest;
    while ((long *)rw < FramePointer) {
      if ((rw->fp += delta) == (long)FramePointer) {
	goto ok;
      }
      rw = (RegWin *) rw->fp;
    }
    DEBUG_CODE(fprintf(stderr, "Upps, stack handling gone crazy\n"));
  ok:
    lastCompBlock = (ComponentBlock *) rw;
    CLOBBER(tmp);
    /* Update ComponentBlock in the restored RegWin */
    rw->l5 = (long) callBackFrame;
    CLOBBER(tmp);
    rw->l6 = (long) nextCompBlock;
    CLOBBER(tmp);
    rw->l7 = level;
    FLUSH_REGWINS();
    FramePointer = (long*)((char *)FramePointer - size);

#ifdef RTVALHALLA
    if (valhallaIsStepping)
      ValhallaOnProcessStop ((long *)comp->CallerLSC,0,0,0,RTS_ATTACH);
#endif

    setret(comp->CallerLSC);
    
    CLOBBER(level);
    CLOBBER(nextCompBlock);
    CLOBBER(callBackFrame);

    return comp; /* still ?? */
  }
}
#endif /* sparc */
#endif /* MT */
