/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif

/* TODO: check for suspend involving callback */

/*
 * STACK LAYOUT at suspend:
 * 
 *          |_______________|
 *          |  X:           |
 *          |  calling      |
 *          |  component    |
 *          |_______________|
 *          |  BETA item    |
 *          |  frames       |
 *          |_______________|
 *          |  topX item    |
 *          |               |
 *    SPx ->|_______________|
 *          |///////////////|
 *          |   Att frame   |
 *    SPy ->|///////////////|
 *          |               |
 *          |  Y: BETA      |
 *          |  component    |
 *          |  frame        |
 *          |_______________|
 *          |               |
 *          |  BETA item    |
 *          |  frames       |
 * prevSP ->|_______________|
 *          |               |
 *          |  topY item    |
 *    SPz ->|_______________|
 *          |///////////////|
 *          |  Susp frame   |
 *     SP ->|///////////////|
 *          |               |
 */

void Susp(struct Object *this, long prevSP, long RA, long SPz)
{
   struct StackObject *sObj; 
   struct Component *returnComp;
   struct Object *returnObj;

   long SPx, SPy, i;

   DEBUG_CODE(NumSusp++);

   SPx = ActiveComponent->CallerComp->SPx;  
   SPy = ActiveComponent->CallerComp->SPy;  

   /* Allocate stackobject for ActiveComponent.
    * Must be done before changing ActiveComponent, since
    * a possible GC during AlloSO relies on 
    * ActiveComponent->CallerObj being the item that was current
    * before *attach*.
    */
   Protect(this, sObj = AlloSO(SPy - SPz, (long *)prevSP));

   returnComp = ActiveComponent->CallerComp;
   returnObj  = ActiveComponent->CallerObj;

   /* Remember what was current object before suspend */
   ActiveComponent->CallerObj = this; 
   /* Remember where ActiveComponent where in the code */
   ActiveComponent->CallerLSC = RA;

   /* copy SPz[0],  SPz[1], ... , SPz[(SPy-SPz-4)/4] = SPy[-1] */
   for (i=0;  i < (SPy-SPz)/4; i++)
     *((long *)sObj->Body+i) = *((long *)SPz+i);
   /* Save size of top frame in sObj->StackSize.
    * Used by ProcessStackObj in stack.c.
    */
   sObj->StackSize = (long)prevSP - (long)SPz;
   /* Save sObj in ActiveComponent */
   AssignReference((long *)&ActiveComponent->StackObj, (struct Item *)sObj);   

   /* Switch ActiveComponent */
   ActiveComponent = ActiveComponent->CallerComp; 
   CallBetaEntry((long)returnComp->CallerLSC, 
		 (void *)SPx, 
		 returnObj); 
}
