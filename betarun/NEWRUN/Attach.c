/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

#if 0
#define TRACE_ATT(code) code
#else
#define TRACE_ATT(code)
#endif

#if 0
#define TRACE_SO(code) code
#else
#define TRACE_SO(code)
#endif

void Att(struct Object *this, struct Component *comp, long RA, long SPx)
{
  long SPy;
  int isFirst = (comp->CallerLSC == 0);
  struct StackObject *sObj = comp->StackObj;
  struct Object *topObject;
  long entry;

  DEBUG_CODE(NumAtt++);

  TRACE_ATT(
  fprintf(output, "Att#%d(this=0x%x, comp=0x%x, RA=0x%x, SPx=0x%x) (%s)\n",
	  NumAtt, this, comp, RA, SPx, isFirst?"first":"not first");
  fprintf(output, "Att#%d: comp= 0x%x, CallerLSC=0x%x\n",
          NumAtt,
	  (int)comp, 
	  (int)comp->CallerLSC));

  if ((long)comp->CallerLSC == -2) {
    /* CallerLCS is set to -2 in ExitObjects.c when the component terminates.
     * So we are attempting to attach a component, that is terminated.
     */
    long SPoff;
    /* adjust SPx to be SP of previous frame. */
    GetSPoff(SPoff, CodeEntry(this->Proto, RA)); 
    SPx = ((long)SPx+SPoff);
    BetaError(CompTerminatedErr, this, (long *)SPx, (long *)RA); 
  }

  if (((long)comp->CallerLSC != 0) && ((long)comp->StackObj==0)) {
    /* comp has a resume address but no stack object.
     * This means that is is active.
     */
    long SPoff;
    /* adjust SPx to be SP of previous frame. */
    GetSPoff(SPoff, CodeEntry(this->Proto, RA)); 
    SPx = ((long)SPx+SPoff);
    BetaError(RecursiveAttErr, this, (long *)SPx, (long *)RA);
  }

  SPy = (long)GetSP();
  if (ActiveComponent) {
    ActiveComponent->CallerLSC = RA;
    TRACE_ATT(
    fprintf(output, 
	    "Att#%d: ActiveComponent=0x%x, CallerLSC set to 0x%x\n",
	    NumAtt,
	    (int)ActiveComponent,
	    RA));
    comppush(SPy); /* fprintf(output, "comppush SPy: 0x%x\n", SPy); */
    comppush(SPx); /* fprintf(output, "comppush SPx: 0x%x\n", SPx); */
  } else { 
    DEBUG_CODE(fprintf(output, "ActiveComponent == 0\n"); Illegal());
  };
  
  if (!isFirst){
     topObject=comp->CallerObj;
     entry = comp->CallerLSC;
  }
     
  AssignReference(&comp->CallerComp, ActiveComponent); /* may call AOAtoIOAinsert */
  AssignReference(&comp->CallerObj, this); /* may call AOAtoIOAinsert */
  comp->StackObj   = 0;
  comp->CallerLSC = -1; /* indicate that comp is attached */

  TRACE_ATT(fprintf(output, "Att#%d: comp=0x%x, CallerLSC set to -1\n", NumAtt, comp));

  ActiveComponent = comp;

#ifdef RTVALHALLA
  /* ValhallaOnProcessStop MUST be called already here. If called after
   * the stack object is unpacked, the call will destroy the new stack part.
   */
  if (valhallaIsStepping)
    ValhallaOnProcessStop ((long*)address,0,0,0,RTS_ATTACH);
#endif

  if (isFirst){
     /* Execute comp.
      * 1st call starts at M111FOO; arg0=comp, arg1=ca.
      * Subsequent attachments: arg0=SPz, arg1=ca;
      */
     CallB((struct Object *)comp, 
           (struct Object *)comp->Body, 
	   ((struct Object *)comp->Body)->Proto->TopMpart, 
	   0);    
  } else {
    long spSize = sObj->BodySize;
    long SPz = SPy - spSize;
       
    TRACE_SO({ int i;
    fprintf(output, "Att#%d: about to unpack stack object:\n", NumAtt);
    fprintf(output, "proto   = %d\n",   sObj->Proto);
    fprintf(output, "gc      = %d\n",   sObj->GCAttr);
    fprintf(output, "size    = 0x%x\n", sObj->BodySize);
    fprintf(output, "topsize = 0x%x\n", sObj->StackSize);
    for (i=0; i < sObj->BodySize/4; i++){
      fprintf(output, "  stack[%d]:\t0x%x\n", i, *((long *)sObj->Body+i));
    }
    fflush(output);});

#ifdef ppcmac
    {
      /* on PPC the stack contains SP pointers that links stack segments;
       * these have been made relative (i.e. offsets from SPz), 
       * since the stack may be unpacked at another place in memory
       */
      long stackstart = (long)sObj->Body; 
      long offset     = 0;  /* Offset into stackpart of sObj */
      long dist       = *(long*)(stackstart+offset);
      *(long*)(stackstart+offset) += SPz;
      while (dist < spSize) {
	offset = dist;
	dist = *(long*)(stackstart+offset);
        *(long*)(stackstart+offset) += SPz;
      }
      TRACE_SO({ int i;
      fprintf(output, "Att#%d: stack object after adjustment:\n", NumAtt);
      fprintf(output, "proto   = %d\n",   sObj->Proto);
      fprintf(output, "gc      = %d\n",   sObj->GCAttr);
      fprintf(output, "size    = 0x%x\n", sObj->BodySize);
      fprintf(output, "topsize = 0x%x\n", sObj->StackSize);
      for (i=0; i < sObj->BodySize/4; i++){
        fprintf(output, "  stack[%d]:\t0x%x\n", i, *((long *)sObj->Body+i));
      }
      fflush(output);});
   }
#endif /* ppcmac */

   TRACE_ATT(fprintf(output, "doAtt(0x%x, 0x%x, 0x%x, 0x%x, 0x%x)\n",
                     (int)SPz, (int)topObject, spSize, (int)sObj->Body, entry));
  
   /* Call doAtt to unpack the stack part and execute the component */
   doAtt(SPz, topObject, spSize, sObj->Body, entry);

  }
  
  /* TerminateComponent: */
  /* we get here when the component terminates.
   * IF CHANGED: remember to change ExO too.
   */
  comp = ActiveComponent;
  /* printf("\nAttach: comp TERMINATED: 0x%08x\n", comp);fflush(stdout); */
  DEBUG_CODE(NumTermComp++);
  ActiveComponent  = comp->CallerComp;
  this             = comp->CallerObj;
  comp->CallerLSC  = -2; /* indicate that comp is terminated */
  comp->StackObj   = 0;
  comp->CallerComp = 0;
  comp->CallerObj  = 0;
  CompSP -= 2;

  /* we must return a proper a0 and a1, since th and SP are set after Att */
#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop ((long*)RA,0,0,0,RTS_ATTACH);
#endif
  CallBetaEntry(RA, SPx, this);
}
