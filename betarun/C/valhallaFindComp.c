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

#ifdef NEWRUN

GLOBAL(static int CompFound);
GLOBAL(static int CompDone);
GLOBAL(static Component *TheComponent);
GLOBAL(static CellDisplayFunc DoForEach);
GLOBAL(static int BasicItemShown);

static void ShowCell(int pc, Object *theObj)
{
  if (theObj==(Object *)BasicItem){
    if (!BasicItemShown){
      TRACE_SCAN(fprintf(output, ", PC=0x%x *\n", pc));
      DoForEach(pc, theObj);
      BasicItemShown=TRUE;
    }
  } else {
    TRACE_SCAN(fprintf(output, ", PC=0x%x *\n", pc));
    if (!strongIsObject(theObj)) {
      TRACE_SCAN(fprintf(output, "(strongIsObject failed!?)\n"));
      return;
    }
    DoForEach(pc, theObj);
  }
}

static void HandleStackCell(Object **theCell,Object *theObj)
{ 
  /* FIXME: This function does pretty much the same as function DumpCell
   * in outpattern.c. An abstraction could be useful (i.e. having
   * DumpCell take a CellDisplayFunc pointer as argument).
   */
  register long pc;
  long *sp;

  TRACE_SCAN(fprintf(output, 
		     ">>>HandleStackCell: theCell=0x%x, theObj=0x%x",
		     theCell, theObj);
	     fflush(output);
	     if (strongIsObject(theObj)){
	       PrintRef(theObj);
	       fprintf(output, ", proto=0x%x", GETPROTO(theObj));
	       fflush(output);
	     });

  if (CompDone) {
    TRACE_SCAN(fprintf(output, " comp is done - ignored\n"));
    return;
  }
  
  /* theObj is dyn in a frame. This is the current object in the 
   * previous frame. 
   */
  if (CompFound){
    /* We are processing the relevant part of the stack */
    
    /* First check if theObj is CALLBACKMARK/GENMARK */
    if ((theObj==CALLBACKMARK)||(theObj==GENMARK)){
      TRACE_SCAN(fprintf(output, "  cb/allo: "));
      /* Since ProcessStackFrames now skips to previous frame before
       * BETA called C, we will not see the current object in the
       * frame before C as a dyn-pointer in any frame (it is hidden
       * by this CALLBACKMARK).
       * So we have to go to this previous frame ourselves and
       * find the current object for that frame and dump it.
       * See figure in stack.c.
       */
      sp = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
      sp = (long*)GetSPbeta(sp);   /* SP-beta */
      if (sp==0){
      /* We passed the main+CallB frames */
      return;
      }
      theObj = GetThis(sp);
      pc = 0;  /* not known - is somewhere in the C frames */
    } else {
      sp = (long *)theCell+DYN_OFF; /* Frame starts DYN_O longs above dyn */
      pc = *((long *)sp+PC_OFF);
    }
    
    /* Check if theObj IS a component */
    if (theObj && (GETPROTO(theObj)==ComponentPTValue)){
      TRACE_SCAN(fprintf(output, " found a component 0x%08x\n", (int)theObj));

      CompDone=TRUE;

      
      return;
    } 
    ShowCell(pc, theObj);
  } else {
    /* Not yet found */
    if (theObj==(Object *)TheComponent){
      /* Found: The real dyn is found as theComp->CallerObj 
       * - see stack.c for details.
       * In this case, the component was not met as a caller
       * component of some other component (see if-clause below).
       * Can happen, e.g., if TheComponent==ActiveComponent.
       */	
      TRACE_SCAN(fprintf(output, " comp found\n"));
      CompFound=TRUE;
      pc = ((Component *)theObj)->CallerComp->CallerLSC;
      theObj = ((Component *)theObj)->CallerObj;
      ShowCell(pc, theObj);
      return;
    } 
    if (theObj && (GETPROTO(theObj)==ComponentPTValue)){
      TRACE_SCAN(fprintf(output, 
			 " Test if it is TheComponent 0x%08x\n", 
			 (int)TheComponent));
      if (((Component*)theObj)->CallerComp == TheComponent){
	/* We found a component on stack, which was attached from TheComponent.
	 * To enable ShowCell for all objects on the stack of TheComponent,
	 * we must NOW set CompFound=TRUE.
	 */
	TRACE_SCAN(fprintf(output, " CallerComp is comp to scan\n"));
	CompFound = TRUE;
	pc = ((Component *)theObj)->CallerComp->CallerLSC;
	theObj = ((Component *)theObj)->CallerObj;
	ShowCell(pc, theObj);
	return;
      } 
    }
    TRACE_SCAN(fprintf(output, " comp not yet found\n"));
  }
}

int scanComponentStack (Component* comp,
			Object *curObj,
			int pc,
			CellDisplayFunc forEach)
{ /* scan through the stackpart corresponding to the comp parameter.
   * pc is the top code-address.
   * calling "forEach" for each (code-address, object) pair on the stack.
   */
  int stacktype=0;

  CompFound=FALSE;
  CompDone=FALSE;
  DoForEach = forEach;
  TheComponent = comp;
  BasicItemShown=0;

  DEBUG_VALHALLA(fprintf(output, 
			 "scanComponentStack(comp=0x%x, obj=0x%x, PC=0x%x)\n",
			 (int)comp, (int)curObj, pc));

  if (comp->StackObj){
    StackObject *sObj = comp->StackObj;
    /* See ProcessStackObj in stack.c */
    CompFound = TRUE;

    /* Process top object in stack object */
    forEach(comp->CallerLSC, /* PC in comp top item */
	    GetThis( (long *)((long)sObj->Body+(long)sObj->StackSize) )
	    );

    ProcessStackFrames((long)sObj->Body+(long)sObj->StackSize, /* top */
		       (long)sObj->Body+(long)sObj->BodySize,  /* bottom */
		       TRUE, 
		       TRUE,
		       HandleStackCell
		       );
    return CS_STACKOBJ;
  }

  if (comp==ActiveComponent) {
    CompFound = TRUE;
    stacktype = CS_ACTIVECOMPONENT;
    forEach(pc, curObj);
  }
  /* FIXME: What about PC outside BETA, compare code in outpattern.c */
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, HandleStackCell);
  if (!stacktype){
    if (CompFound){
      stacktype=CS_PROCESSORSTACK;
    } else {
      stacktype=CS_NOSTACK;
    }
  }
  return stacktype;
}
#endif /* NEWRUN */

#endif /* RTVALHALLA */
