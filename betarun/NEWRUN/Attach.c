/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

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
     address = (long)(compObj->Proto->TopMpart)-8;
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
   }
   /* Execute comp.
    * 1st call starts at M111FOO-4; arg0=comp, arg1=ca.
    * Subsequent attachments: arg0=SPz, arg1=ca;
    */
#ifdef RTVALHALLA
    if (valhallaIsStepping)
      ValhallaOnProcessStop ((long*)address,0,0,0,RTS_ATTACH);
#endif
    CallBetaEntry(address, arg0, arg1);

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
