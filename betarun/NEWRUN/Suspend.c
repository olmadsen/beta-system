/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif

void Susp(struct Object *this, long dummy, long RA, long SPz)
{
   struct Component *returnComp;
   struct Object    *returnObj;
   struct StackObject *sObj; 
   long SPx, SPy, i;

   DEBUG_CODE(NumSusp++);

   returnComp = ActiveComponent->CallerComp;
   returnObj  = ActiveComponent->CallerObj;

   SPx = returnComp->SPx;  
   SPy = returnComp->SPy;  

   ActiveComponent->CallerObj = this;
   ActiveComponent->CallerLSC =  RA;
   
   /* pack stack SPz - SPy to  activeCompSP*/
   sObj = AlloSO(SPy - SPz, (long *)SPz);

   /* copy SPz[0],  SPz[1], ... , SPz[(SPy-SPz-4)/4] = SPy[-1] */
   for (i=0;  i < (SPy-SPz)/4; i++)
     *((long *)sObj->Body+i) = *((long *)SPz+i);

   ActiveComponent->StackObj = (struct StackObject *)sObj;
   ActiveComponent = ActiveComponent->CallerComp;
   /* ActiveComponent->CallerComp = 0;*/
   
   CallBetaEntry((long)returnComp->CallerLSC, (void *)SPx, returnObj); 
}
