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
  struct Component *comp = ActiveComponent;
  struct Object *callerObj;
  long RA;
  long SPx;
  
  /* printf("\ncomp TERMINATED: 0x%08x\n", comp); fflush(stdout); */
  DEBUG_CODE(NumTermComp++);

  comppop(SPx);
  CompSP -= 1; /* SPy not needed */

  callerObj        = ActiveComponent->CallerObj;
  ActiveComponent  = ActiveComponent->CallerComp;
  RA               = ActiveComponent->CallerLSC;
  
  /* indicate that comp (old ActiveComponent) is terminated */
  comp->CallerLSC  = -2; 
  comp->StackObj   = 0;
  comp->CallerComp = 0;
  comp->CallerObj  = 0;

  /* we must return a proper a0 and a1, since th and SP are set after Att */
#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop ((long*)RA,0,0,0,RTS_ATTACH);
#endif
  CallBetaEntry(RA, SPx, callerObj);
}

#ifdef ppcmac

/*************************** Solution using doAtt *********************/

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
  
  TerminateActiveComponent();
}

#else

/************************ Solution NOT using doAtt *******************/

void Att(struct Object *this, struct Component *comp, long RA, long SPx)
{
  struct Object *compObj;
  struct StackObject *sObj=0;
  long address, arg0, arg1;
  long SPy,SPz;
  int isFirst,i;

  DEBUG_CODE(NumAtt++);

#if 0
  fprintf(output, "Att(this=0x%x, comp=0x%x, RA=0x%x, SPx=0x%x\n",
	  this, comp, RA, SPx);
  fprintf(output, "Att: comp= 0x%x, CallerLSC=0x%x\n", 
	  (int)comp, 
	  (int)comp->CallerLSC);
#endif

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
#if 0
    fprintf(output, 
	    "Susp: comp=0x%x, CallerLSC set to 0x%x\n",
	    (int)ActiveComponent,
	    RA);
#endif
    comppush(SPy); /* fprintf(output, "comppush SPy: 0x%x\n", SPy); */
    comppush(SPx); /* fprintf(output, "comppush SPx: 0x%x\n", SPx); */
  } else { 
    DEBUG_CODE(fprintf(output, "ActiveComponent == 0\n"); Illegal());
  };
   
  isFirst = (comp->CallerLSC == 0);
  if (isFirst) { 
    compObj = (struct Object *)comp->Body;
    address = (long)compObj->Proto->TopMpart;
    arg0    = (long)comp;
    arg1    = (long)compObj;
  } else {
    sObj = comp->StackObj;
    SPz = SPy - sObj->BodySize; 
    address = (long)comp->CallerLSC;
    arg0    = (long)SPz;
    arg1    = (long)comp->CallerObj; 
  }
  
  AssignReference(&comp->CallerComp, ActiveComponent); /* may call AOAtoIOAinsert */
  AssignReference(&comp->CallerObj, this); /* may call AOAtoIOAinsert */
  comp->StackObj   = 0;
  comp->CallerLSC = -1; /* indicate that comp is attached */

#if 0
  fprintf(output, "Att: comp=0x%x, CallerLSC set to -1\n", comp);
#endif

  ActiveComponent = comp;

  if (sObj){
    /* Unpack sObj on stack. Must be done as the last thing to prevent
     * calls to other functions to destroy the new stack part.
     */
#if 0
    fprintf(output, "Att: unpacking stack object:\n");
    for (i=0; i < sObj->BodySize/4; i++){
      fprintf(output, 
	      "  *0x%x=0x%x\n", 
	      (long)((long *)SPz+i), 
	      *((long *)sObj->Body+i));
    }
#endif
    for (i=0; i < sObj->BodySize/4; i++){
      *((long *)SPz+i) = *((long *)sObj->Body+i);
    }

#ifdef macppc
    {
      /* on PPC the stack contains SP pointers that links stack segments;
       * these have been made relative, since the stack may be unpacked
       * at another place in memory
       */
      long spLoc = 0; 
      long sp = ((long *)SPz)[spLoc];
      ((long *) SPz)[spLoc] = SPz + sp;
      while (sp < sObj->BodySize) {
	spLoc = sp;
	sp = ((long *)SPz)[sp / 4];
	((long *) SPz)[spLoc / 4] = SPz + ((long *) SPz)[spLoc / 4];
      }
    }
#endif /* macppc */

  }
  /* Execute comp.
   * 1st call starts at M111FOO; arg0=comp, arg1=ca.
   * Subsequent attachments: arg0=SPz, arg1=ca;
   */
#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop ((long*)address,0,0,0,RTS_ATTACH);
#endif
  if (isFirst){
    CallB((struct Object *)arg0, (struct Object *)arg1, address, 0);
  } else {
    CallBetaEntry(address, arg0, arg1);
  }

  TerminateActiveComponent();
}

#endif /* ppcmac */
