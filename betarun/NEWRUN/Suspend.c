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

/* CheckReferences:
 *  Used for updating stackobject allocated directly in AOA.
 */
static void CheckReferences(struct Object **theCell, struct Object *theObj)
{
  /* theCell is known to be in AOA (part of stack object in AOA) */
  if (inIOA(theObj)) AOAtoIOAInsert(theCell);
}


void Susp(struct Object *this, long prevSP, long RA, long SPz)
{
   struct StackObject *sObj; 
   struct Component *returnComp;
   struct Object *returnObj;

   long SPx, SPy, i;

   DEBUG_CODE(NumSusp++);

   /* Get SPy. Do NOT pop, since this will confuse a GC during AlloSO below */
   SPy = *(CompSP-2);

   /* Allocate stackobject for ActiveComponent.
    * Must be done before changing ActiveComponent, since
    * a possible GC during AlloSO relies on 
    * ActiveComponent->CallerObj being the item that was current
    * before *attach*.
    */
   Protect(this, sObj = AlloSO(SPy - SPz, (long *)prevSP));

   comppop(SPx); /* fprintf(output, "comppop SPx: 0x%x\n", SPx); */
   comppop(SPy); /* fprintf(output, "comppop SPy: 0x%x\n", SPy); */
   returnComp = ActiveComponent->CallerComp;
   returnObj  = ActiveComponent->CallerObj;

   /* Remember what was current object before suspend */
   AssignReference(&ActiveComponent->CallerObj, this); 
   /* Remember where ActiveComponent where in the code */
   ActiveComponent->CallerLSC = RA;

   /* copy SPz[0],  SPz[1], ... , SPz[(SPy-SPz-4)/4] = SPy[-1] */
   for (i=0;  i < (SPy-SPz)/4; i++)
     *((long *)sObj->Body+i) = *((long *)SPz+i);
   /* Save size of top frame in sObj->StackSize.
    * Used by ProcessStackObj in stack.c.
    */
   sObj->StackSize = (long)prevSP - (long)SPz;

   if (!inIOA(sObj)){
     /* sObj was allocated directly in AOA */
     ProcessStackObj(sObj, CheckReferences);
   }

   /* Save sObj in ActiveComponent */
   AssignReference((long *)&ActiveComponent->StackObj, (struct Item *)sObj);   

   /* Switch ActiveComponent */
   ActiveComponent = ActiveComponent->CallerComp; 
   CallBetaEntry((long)returnComp->CallerLSC, 
		 (void *)SPx, 
		 returnObj); 
}
