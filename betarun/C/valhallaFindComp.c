#include "beta.h"

#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#include "valhallaFindComp.h"

/* Trace scanComponentStack() */
#define TRACE_SCAN(code) TRACE_DUMP(code)

#ifdef intel
static int compfound;
static CellDisplayFunc DoForEach;

static void ShowCell(long pc, Object *theObj)
{
  if (!strongIsObject(theObj)) {
    fprintf(output, "(showcell: strongIsObject failed!?)\n") ;
    return;
  }
  if (compfound) DoForEach(pc, theObj);
}

int scanComponentStack (Component* comp,
			Object *curObj,
			int pc,
			CellDisplayFunc forEach)
{
  /* scan through the stackpart corresponding to the comp parameter.
   * PC is the top code-address.
   * calling "forEach" for each (code-address, object) pair on the stack.
   */
  int stacktype;
  
  DEBUG_VALHALLA(fprintf(output, 
			 "scanComponentStack(comp=0x%x, obj=0x%x, PC=0x%x)\n",
			 (int)comp, (int)curObj, pc));

  compfound = 0;
  DoForEach = forEach;

  if ((long)(comp->StackObj)>0 /* -1 means active */
      && (comp!=ActiveComponent) /* ActiveComponent may have a stack object,
				  * if it has previously been suspended.
				  */
      ){
    StackObject *sObj = comp->StackObj;
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: scanning stackObject 0x%x\n", (int)comp->StackObj));
    DisplayStackPart((long*)sObj->Body, 
		     (long*)((long)sObj->Body + sObj->StackSize),
		     0, 
		     ShowCell);
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: stackObject done\n"));
    return CS_STACKOBJ;
  }

  if (comp==ActiveComponent) {
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: scanning ActiveComponent\n"));
    compfound = TRUE;
    stacktype = CS_ACTIVECOMPONENT;
    DEBUG_VALHALLA(fprintf(output, "Pair: PC=0x%x, obj=0x%x\n", (int)pc, (int)curObj));
    ShowCell(pc, curObj);
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: ActiveComponent done\n"));
  } else {
    compfound=0;
    stacktype=0;
  }

  DEBUG_VALHALLA(fprintf(output, "scanComponentStack: scanning machinestack\n"));
  /* Scan through the machine stack. This is an adaption of
   * DisplayBetaStack from outpattern.c - see comments in the code
   * there, especially for the small constants added or subtracted
   * from the stack positions.
   * See also doc/RunDoc.txt for a figure of the stack layout.
   */
  { 
    long           *low;
    long           *high;
    CallBackFrame  *cbFrame;
    ComponentBlock *currentBlock;
    Object         *currentObject;
    Component      *currentComponent;
    
    /* First handle the topmost component block */
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: topmost component block\n"));
    currentObject    = curObj;
    currentComponent = ActiveComponent;
    low              = (long *) StackEnd;
    high             = (long *) lastCompBlock;
    cbFrame          = ActiveCallBackFrame; 

    /* First check for errors occured outside BETA */
    if (!IsBetaCodeAddrOfProcess(pc)){
      if ((StackEnd<BetaStackTop) && (BetaStackTop<(long*)StackStart)){
	/* BetaStackTop is in the active stack. Try continuing from there.
	 * This will work if BETA called a C routine, but not if the error
	 * occurred in a runtime routine - BetaStackTop is not set, when
	 * runtime routines are called.
	 * This might also fail if we are returning from a callback chain,
	 * since BetaStackTop is not adjusted as we pop off callback frames.
	 * Should be handled, though, by the requirement that BetaStackTop 
	 * must be between StackStart and StackEnd.
	 */
	low = BetaStackTop;
	TRACE_DUMP({
	  fprintf(output, 
		  ">>>DisplayINTELStack: adjusting low to BetaStackTop: 0x%x\n",
		  (int)BetaStackTop);
	});
      }
      low += 3;
      /* low+3 because the compiler pushes %edx, %edi, %ebp, %esi
       * before setting BetaStackTop.
       * Of these we only want to see %edx (current object).
       */

      /* Since a new lastObj will be met by DisplayStackPart before 
       * any other PC corresponding to currentObject, the current object that
       * called C will not be displayed by DisplayStackPart.
       * So we display it here.
       */
      forEach(0 /*pc*/, currentObject);
    }
    
    if (cbFrame){
      low = DisplayCallbackFrames(cbFrame, low, currentObject, ShowCell);
    }
    DisplayStackPart(low, high-3, currentObject, ShowCell); 
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: topmost component block done\n"));
    
    /* Then handle the remaining component blocks */
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: other component blocks\n"));
    currentBlock     = lastCompBlock;
    currentObject    = currentComponent->CallerObj;
    pc               = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
    
    while (currentBlock->next){
      /* handle next component block */
      if (compfound){
	DEBUG_VALHALLA(fprintf(output, "Relevant component block completed - returning\n"));
	break;
      }
      if (currentComponent==comp) compfound=TRUE;
      low  = (long *)((long)currentBlock+sizeof(ComponentBlock))+1;
      high = (long *) currentBlock->next;
      cbFrame  = currentBlock->callBackFrame;
      if (!cbFrame) {
	DEBUG_VALHALLA(fprintf(output, "Pair: PC=0x%x, obj=0x%x\n", (int)pc, (int)currentObject));
	ShowCell(pc, currentObject);
      }
      if (cbFrame){
	low = DisplayCallbackFrames(cbFrame, low, currentObject, ShowCell);
      }
      DisplayStackPart(low, high-3, currentObject, ShowCell); 
      currentBlock     = currentBlock->next;
      currentObject    = currentComponent->CallerObj;
      pc               = currentComponent->CallerLSC;
      currentComponent = currentComponent->CallerComp;
    }
    DEBUG_VALHALLA(fprintf(output, "scanComponentStack: other component blocks done\n"));
  }
  DEBUG_VALHALLA(fprintf(output, "scanComponentStack: machinestack done\n"));

  if (!stacktype){
    if (compfound){
      stacktype=CS_PROCESSORSTACK;
    } else {
      stacktype=CS_NOSTACK;
    }
  }
  DEBUG_VALHALLA(fprintf(output, "scanComponentStack: returning %d\n", (int)stacktype));
  return stacktype;
 
}
#endif /* intel */

#endif /* RTVALHALLA */
