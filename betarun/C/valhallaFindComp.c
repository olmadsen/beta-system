#include "beta.h"

#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#include "valhallaFindComp.h"

/* Trace scanComponentStack() */
#define TRACE_SCAN(code) TRACE_DUMP(code)

#if defined(MT) || defined(hppa)
int scanComponentStack (Component* comp,
			Object *curObj,
			int pc,
			CellDisplayFunc forEach)
{ 
  fprintf(output, "scanComponentStack: NYI\n");
  return 0;
}
#endif

#ifdef intel
static int compfound;
static CellDisplayFunc DoForEach;

static void ShowCell(long pc, Object *theObj)
{
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
	     if (isObject(theObj)){
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



#ifdef sparc

#ifndef MT


typedef struct ComponentStack {
  Component *comp; /* The component */
  int stacktype;          /* One of CS_*   */
  int returnAdr;          /* The address to return to when this component 
			   * starts running the next time. */
  union {
    struct { /* if stacktype==CS_PROCESSORSTACK or CS_ACTIVECOMPONENT: */
      /* FirstAR is the largest address that is not part of the stack of comp.
       * lastAR is the least RegWin that *is* part of the stack, i.e. the 
       * StackEnd for this component stack. Notice that the stack grows 
       * downwards. 
       * I.e. to scan the stack, scan from (and including) lastAR to firstAR.
       * activeCBF is the active callback frame of this component.
       */
      RegWin* firstAR;
      RegWin* lastAR;
      RegWin* activeCBF;
    } if_onstack;
    /* if stacktype==CS_STACKOBJ: */
    StackObject *stackObj; 
  } info;
} ComponentStack;

/* findComponentStack (SPARC)
 *
 * Fills in the structure compStack. compStack->comp should point to a 
 * component object. PC is expected to be the current BETA PC, and is
 * used to set compStack->returnAdr in case compStack->comp is the
 * active component.
 *
 * The implementation of findComponentStack assumes that it has been called
 * via some other runtime routine that correctly set up the StackEnd
 * variable to point to the top of the current BETA stack. This is
 * e.g. the case with BetaError or BetaSignalHandler.
 * ========================== 
 */

static void findComponentStack (ComponentStack* compStack, int pc)
{ 
  RegWin *thisCompBlock = (RegWin *) lastCompBlock;
  RegWin *prevCompBlock = 0;
  Component *thisComponent = ActiveComponent;

  DEBUG_VALHALLA(fprintf (output,"Entering findComponentStack (SPARC)\n"));

  while (thisCompBlock) {
    if (compStack->comp == thisComponent){
      /* comp found on processor stack. */
      
      compStack->info.if_onstack.firstAR 
	= (RegWin *) thisCompBlock/*->fp (pa/gram 07/01/2000)*/;
      
      if (prevCompBlock) { 
	
	compStack->stacktype = CS_PROCESSORSTACK; 
	compStack->info.if_onstack.lastAR
	  = (RegWin *) prevCompBlock->fp;
	compStack->returnAdr = thisComponent->CallerLSC;
	compStack->info.if_onstack.activeCBF 
	  = (RegWin *) prevCompBlock->l5;

      } else {
	/* comp is the active component. */

	compStack->stacktype = CS_ACTIVECOMPONENT;
	compStack->info.if_onstack.lastAR = (RegWin *) StackEnd;

	compStack->info.if_onstack.activeCBF 
	  = (RegWin *) ActiveCallBackFrame;
	compStack->returnAdr = pc;
	
      }
      DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
      return;
    } else {
      prevCompBlock = thisCompBlock;
      thisCompBlock = (RegWin *) thisCompBlock->l6; /* See SparcDoc.c */
      thisComponent = thisComponent->CallerComp;
    }
  }

  /* Component not found on the processor stack.
   * If the component has ever been attached and suspended, it should have
   * been assigned a stack object.
   * Otherwise it has no stack at all. */

  switch ((int) (compStack->info.stackObj = compStack->comp->StackObj)) {
  case 0:
  case -1:
    compStack->stacktype = CS_NOSTACK;
    compStack->returnAdr = 0;
    break;
  default:
    compStack->stacktype = CS_STACKOBJ;
    compStack->returnAdr = compStack->comp->CallerLSC;
    break;
  }
  DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
}


int scanComponentStack (Component* comp,
			Object *curObj,
			int pc,
			CellDisplayFunc forEach)
{ 
  struct ComponentStack compStack;

  compStack.comp = comp;

  DEBUG_VALHALLA(fprintf (output,"Entering scanComponentStack. \n"));

  findComponentStack (&compStack,pc);

  DEBUG_VALHALLA(fprintf (output,"FindComponentStack done. stacktype = %d. \n",compStack.stacktype));

  switch (compStack.stacktype) {
  case CS_NOSTACK: 
    break;
  case CS_STACKOBJ:
    { StackObject *theStack = compStack.info.stackObj;
      RegWin *theAR;
      int lastReturnAdr = compStack.returnAdr; 
      
      /* ASSUMES THAT THERE ARE NO CALLBACK FRAMES IN A COMPONENT OBJECT.
       * IF THIS CHANGES, SO SHOULD THE CODE BELOW. */
      
      /* Start at theStack->Body[1], since theStack->Body[0] 
       * is saved FramePointer */
      long delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];
      
      for (theAR =  (RegWin *) &theStack->Body[1];
	   theAR != (RegWin *) &theStack->Body[theStack->StackSize];
	   theAR =  (RegWin *) (theAR->fp + delta))
	{
	  DisplayAR(theAR, lastReturnAdr, forEach);
	  lastReturnAdr = theAR->i7+8;
	}
    };
    break;
  case CS_PROCESSORSTACK:
  case CS_ACTIVECOMPONENT:
    { RegWin *theAR = compStack.info.if_onstack.lastAR;
      RegWin *nextCBF = compStack.info.if_onstack.activeCBF;
      int lastReturnAdr = compStack.returnAdr;

      DEBUG_VALHALLA(fprintf(output,"BetaStackTop = %d\n",(int)BetaStackTop));

      if (!IsBetaCodeAddrOfProcess(pc))
	/* Skip external code on top of stack: */
	while ((unsigned int) theAR < (unsigned int) BetaStackTop) {
	  DEBUG_VALHALLA(fprintf(output,"External return address: "));
	  forEach (lastReturnAdr,0);
	  lastReturnAdr = theAR->i7+8;
	  theAR = (RegWin *) theAR->fp;
	}
      
      for (;
	   theAR != compStack.info.if_onstack.firstAR;
	   theAR = (RegWin *) theAR->fp){
	if (theAR == nextCBF) {
	  /* This is AR of HandleCB. Skip this and
	   * skip to betaTop and update nextCBF
	   */
	  nextCBF = (RegWin *) theAR->l5;
	  { /* Wind down the stack until betaTop is reached. Needed in 
	     * order to update lastReturnAdr. */
	    RegWin *cAR;
	    forEach (lastReturnAdr,0);
	    lastReturnAdr = theAR->i7+8;
	    for (cAR = theAR;
		 cAR != (RegWin *) theAR->l6;
		 cAR = (RegWin *) cAR->fp) {
	      forEach (lastReturnAdr,0);
	      lastReturnAdr = cAR->i7+8;
	    }
	  }
	  theAR = (RegWin *) theAR->l6; /* Skip to betaTop */
	}
	DisplayAR(theAR, lastReturnAdr, forEach);
	lastReturnAdr = theAR->i7+8; /* First return address used is actually PC of the process. 
				      * For other return addresses, add 8. */
      };
      break;
    }
  }
  return compStack.stacktype;
}
#endif /* MT */
#endif /* sparc */

static ProtoType *activation_proto;
static Object *activation_object;
static void find_foreach(long PC, Object *theObj)
{
  if (activation_object) return;
  if (!theObj) return;
  if (GETPROTO(theObj) == activation_proto){
    /* exact qualification found */
    activation_object = theObj;
    return;
  } else {
    /* See if prefix matches */
    ProtoType *proto = GETPROTO(theObj);
    if (proto->Prefix == proto){
      /* proto is Object## */
      return;
    }
    for (proto = proto->Prefix;
	 proto != proto->Prefix; /* proto != Object## */
	 proto = proto->Prefix) {
      if (proto == activation_proto) {
	/* proto is a prefix of activation_proto */
	activation_object = theObj;
	return; 
      }
    }
  }
}

#if defined(sparc) || defined(linux)
/* Usage:
 *  throw:
 *    INCLUDE '~beta/sysutils/objinterface';
 *    (# proto: @integer;
 *       theTry: ^try;
 *     do try## -> getProtoTypeForStruc -> proto;
 *        proto -> find_activation -> obj;
 * 	  (if obj<>0 then
 *            obj -> addressToObject -> theTry[];
 *        if);
 *        ...
 *    #)
 */
Object *find_activation(ProtoType *proto)
{
  StackEnd = BetaStackTop;
  activation_object = 0;
  activation_proto = proto;
  scanComponentStack (ActiveComponent, 0, 0, find_foreach);
  return activation_object;
}
#endif /* sparc */

#endif /* RTVALHALLA */
