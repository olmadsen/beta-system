/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif

/* FIXME: check for suspend involving callback */

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

#if 0
#define TRACE_SUSP(code) code
#else
#define TRACE_SUSP(code)
#endif

#if 0
#define TRACE_SO(code) code
#else
#define TRACE_SO(code)
#endif

void Susp(struct Object *this, long prevSP, long RA, long SPz)
{
   struct StackObject *sObj; 
   struct Component *returnComp;
   struct Object *returnObj;
   long SPx, SPy, i;

   DEBUG_CODE(NumSusp++);

   TRACE_SUSP(
   fprintf(output, 
	   "Susp#%d(this=0x%x, prevSP=0x%x, RA=0x%x, SPz=0x%x, SPy=0x%x\n",
	   NumSusp, this, prevSP, RA, SPz, *(CompSP-2)));

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

   TRACE_SUSP(
   fprintf(output, 
	   "Susp#%d: comp=0x%x, CallerLSC set to 0x%x\n",
	   NumSusp,
	   (int)ActiveComponent,
	   RA));

   TRACE_SO(
   fprintf(output, "Susp#%d: packing stack object:\n", NumSusp);
   for (i=0;  i < (SPy-SPz)/4; i++)
     fprintf(output, "  0x%x=*0x%x (0x%x)\n", 
	     (long)((long *)sObj->Body+i), 
	     (long)((long *)SPz+i), 
	     *((long *)SPz+i)));

#ifdef macppc
#if 1
   {
     /* on PPC the stack contains SP pointers that links stack segments;
      * these must be made relative, since the stack may be unpacked
      * at another place in memory
      */  
	 long sp;
     long oldSP; 
	 long offset; /* distance from SPz */
	 
     sp = SPz;
     oldSP = *(long *)sp; 
     while (oldSP <= SPy) /* Don't adjust Att frame */{
	   /*fprintf(output, " sp=0x%x, oldSP=0x%x\n", sp,oldSP); fflush(output);*/
	   offset = oldSP - SPz;
       *(long *)sp = offset;
       sp = oldSP;
       oldSP = *(long *)sp;
     }
   }
#else
   {
      long sp, spLoc;
	  
      sp=(long)GetSP();
      spLoc = SPz; sp = ((long *)SPz)[0];
      while (sp <= SPy) { 
	    ((long *)spLoc)[0] = sp - SPz ;
	    spLoc = sp;
	    sp = ((long *)sp)[0];
      }
   }
#endif
#endif /* PPC */

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
#ifdef RTVALHALLA
    if (valhallaIsStepping)
      ValhallaOnProcessStop ((long*)returnComp->CallerLSC,0,0,0,RTS_SUSPEND);
#endif
   CallBetaEntry((long)returnComp->CallerLSC, 
		 (void *)SPx, 
		 returnObj); 
}
