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

static void TerminateActiveComponent(void)
{ 
  Component *comp = ActiveComponent;
  Object *callerObj;
  pc_t RA;
  long SPx;
  
  /* printf("\ncomp TERMINATED: 0x%08x\n", comp); fflush(stdout); */
  DEBUG_CODE(NumTermComp++);

  comppop(SPx);
  CompSP -= 1; /* SPy not needed */

  callerObj        = ActiveComponent->CallerObj;
  ActiveComponent  = ActiveComponent->CallerComp;
  RA               = ActiveComponent->CallerLSC;
  
  /* indicate that comp (old ActiveComponent) is terminated */
  comp->CallerLSC  = (pc_t) -2; 
  comp->StackObj   = 0;
  comp->CallerComp = 0;
  comp->CallerObj  = 0;

  /* we must return a proper a0 and a1, since th and SP are set after Att */
#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop (RA,0,0,0,RTS_ATTACH);
#endif
  CallBetaEntry(RA, SPx, callerObj);
}

#if defined(ppcmac) || defined(macosx)

/*************************** Solution using doAtt *********************/

void Att(Object *this, Component *comp, pc_t RA, long SPx)
{
  long SPy;
  int isFirst = (comp->CallerLSC == 0);
  StackObject *sObj = comp->StackObj;
  Object *topObject = 0;
  long entry = 0;
  long address = 0;

  DEBUG_CODE(NumAtt++);

  TRACE_ATT(
  fprintf(output, "Att#%d(this=0x%x, comp=0x%x, RA=0x%x, SPx=0x%x) (%s)\n",
	  NumAtt, this, comp, (int)RA, SPx, isFirst?"first":"not first");
  fprintf(output, "Att#%d: comp= 0x%x, CallerLSC=0x%x\n",
          NumAtt,
	  (int)comp, 
	  (int)comp->CallerLSC));

  if ((pc_t)comp->CallerLSC == (pc_t)-2) {
    /* CallerLCS is set to -2 in ExitObjects.c when the component terminates.
     * So we are attempting to attach a component, that is terminated.
     */
    long SPoff;
    /* adjust SPx to be SP of previous frame. */
    GetSPoff(SPoff, CodeEntry(GETPROTO(this), RA)); 
    SPx = ((long)SPx+SPoff);
    BetaError(CompTerminatedErr, this, (long *)SPx, RA); 
  }

  if (((long)comp->CallerLSC != 0) && ((long)comp->StackObj==0)) {
    /* comp has a resume address but no stack object.
     * This means that is is active.
     */
    long SPoff;
    /* adjust SPx to be SP of previous frame. */
    GetSPoff(SPoff, CodeEntry(GETPROTO(this), RA)); 
    SPx = ((long)SPx+SPoff);
    BetaError(RecursiveAttErr, this, (long *)SPx, RA);
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
    DEBUG_CODE(fprintf(output, "ActiveComponent == 0\n"); ILLEGAL);
  };
  
  if (!isFirst){
     topObject=comp->CallerObj;
     entry = (long)comp->CallerLSC;
  }
     
  AssignReference(&comp->CallerComp, ActiveComponent); /* may call AOAtoIOAinsert */
  AssignReference(&comp->CallerObj, this); /* may call AOAtoIOAinsert */
  comp->StackObj   = 0;
  comp->CallerLSC = (pc_t)-1; /* indicate that comp is attached */

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
     CallB((Object *)comp, 
           (Object *)comp->Body, 
	   OBJPROTOFIELD(((Object *)comp->Body), TopMpart), 
	   0);    
  } else {
    long spSize = sObj->BodySize;
    long SPz = SPy - spSize;
       
    TRACE_SO({ int i;
    fprintf(output, "Att#%d: about to unpack stack object:\n", NumAtt);
    fprintf(output, "proto   = %d\n",   GETPROTO(sObj));
    fprintf(output, "gc      = %d\n",   sObj->GCAttr);
    fprintf(output, "size    = 0x%x\n", sObj->BodySize);
    fprintf(output, "topsize = 0x%x\n", sObj->StackSize);
    for (i=0; i < sObj->BodySize/4; i++){
      fprintf(output, "  stack[%d]:\t0x%x\n", i, *((long *)sObj->Body+i));
    }
    fflush(output);});

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
      fprintf(output, "proto   = %d\n",   GETPROTO(sObj));
      fprintf(output, "gc      = %d\n",   sObj->GCAttr);
      fprintf(output, "size    = 0x%x\n", sObj->BodySize);
      fprintf(output, "topsize = 0x%x\n", sObj->StackSize);
      for (i=0; i < sObj->BodySize/4; i++){
        fprintf(output, "  stack[%d]:\t0x%x\n", i, *((long *)sObj->Body+i));
      }
      fflush(output);});
   }

   TRACE_ATT(fprintf(output, "doAtt(0x%x, 0x%x, 0x%x, 0x%x, 0x%x)\n",
                     (int)SPz, (int)topObject, spSize, (int)sObj->Body, entry));
  
   /* Call doAtt to unpack the stack part and execute the component */
   doAtt(SPz, topObject, spSize, sObj->Body, entry);

  }
  
  TerminateActiveComponent();
}

#else

#include "Attach_sgi.c"

#endif /* ppcmac */
