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

   SPy = (long)GetSP();
   if (ActiveComponent) {
     ActiveComponent->CallerLSC = RA;
     comppush(SPy); /* fprintf(output, "comppush SPy: 0x%x\n", SPy); */
     comppush(SPx); /* fprintf(output, "comppush SPx: 0x%x\n", SPx); */
   } else { 
     DEBUG_CODE(fprintf(output, "ActiveComponent == 0\n"); Illegal());
   };
   
   if ((long)comp->CallerLSC == -1) {
     BetaError(RecursiveAttErr, this, (long *)SPx);
     /* TODO: Probably SPx should be adjusted for SPoff */
   }

   if ((long)comp->CallerLSC == -2) {
     BetaError(CompTerminatedErr, this, (long *)SPx); 
     /* TODO: Probably SPx should be adjusted for SPoff */
   }

   isFirst = (comp->CallerLSC == 0);
   if (isFirst) { 
     compObj = (struct Object *)comp->Body;
     address = (*((long *)compObj->Proto-1))-4;
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

   ActiveComponent = comp;

   if (sObj){
     /* Unpack sObj on stack. Must be done as the last thing to prevent
      * calls to other functions to destroy the new stack part.
      */
     for (i=0; i < sObj->BodySize/4; i++){
       *((long *)SPz+i) = *((long *)sObj->Body+i);
     }
   }
   /* Execute comp.
    * 1st call starts at M111FOO-4; arg0=comp, arg1=ca.
    * Subsequent attachments: arg0=SPz, arg1=ca;
    */
   CallBetaEntry(address, arg0, arg1);

   /* TerminateComponent: */
   /* we get here when the component terminates
    */
   comp = ActiveComponent;
   /* printf("\nAttach: comp TERMINATED: 0x%08x\n", comp);fflush(stdout); */
   ActiveComponent  = comp->CallerComp;
   this             = comp->CallerObj;
   comp->CallerLSC  = -2; /* indicate that comp is terminated */
   comp->StackObj   = 0;
   comp->CallerComp = 0;
   comp->CallerObj  = 0;
   CompSP -= 2;

   /* we must return a proper a0 and a1, since th and SP are set after Att */
   CallBetaEntry(RA, SPx, this);
}
