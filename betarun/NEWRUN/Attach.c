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
   struct Object *topObj;
   struct ProtoType *compProto;
   struct StackObject *sObj;
   long compAdr;
   long SPy,SPz;
   int isFirst,i;

   DEBUG_CODE(NumAtt++);

   SPy = (long)GetSP();
   if (ActiveComponent) {
     ActiveComponent->CallerLSC = RA;
     ActiveComponent->SPx = SPx;
     ActiveComponent->SPy = SPy;
   } else { 
     DEBUG_CODE(printf("ActiveComponent == 0 \n"));
   };
   
   if ((long)comp->CallerLSC == -1) 
     BetaError(CompTerminatedErr, this, (long *)SPx); 

   isFirst = (comp->CallerLSC == 0);
   compObj = (struct Object *)comp->Body;
   if (isFirst) { 
     compAdr = (*((long *)compObj->Proto-1))-4;
     topObj = compObj;
   } else {
     compAdr = (long)comp->CallerLSC;     
     topObj  = comp->CallerObj; 
     /* pack current component to stack object */
     sObj = comp->StackObj;

     SPz = SPy - sObj->BodySize; 
     for (i=0; i < sObj->BodySize/4; i++)
       *((long *)SPz+i) = *((long *)sObj->Body+i);
   }
  
   /* if (ActiveComponent != 0) ActiveComponent->StackObj =  -1;  /* ? */
   comp->CallerComp = ActiveComponent;
   comp->CallerObj = this;
   comp->CallerLSC = -1; 

   ActiveComponent = comp;

   /* Execute comp.
    * 1st call starts at M111FOO; a0=dummy, a1=ca; i.e a0 is not used
    * in this situation, since M111FOO adjusts SP as usual.
    * Subsequent calls after Attach; a0=SPz, a1=ca;
    */
   CallBetaEntry(compAdr, SPz, topObj);

   /* TerminateComponent: */
   /* we get here when the component terminates
    */
   comp = ActiveComponent;
   /*printf("\nAttach: comp TERMINATED: 0x%08x\n", comp);fflush(stdout);*/
   comp->CallerLSC  = -1; 
   ActiveComponent  = comp->CallerComp;
   this             = comp->CallerObj;
   comp->StackObj   = 0;
   comp->CallerComp = 0;
   comp->CallerObj  = 0;

   /* we must return a proper a0 and a1, since th and SP are set after Att */
   CallBetaEntry(RA, SPx, this);
}
