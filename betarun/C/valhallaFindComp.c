#include "define.h"

#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#include "valhallaFindComp.h"

#if 0
/* Trace scanComponentStack() */
#define TRACE_SCAN(code) code; fflush(output)
#else
#define TRACE_SCAN(code)
#endif


#if (defined(linux) || defined(nti) || defined(mc68020)) 

/* Warning: The following has NOT been tested */

static void ShowStackPart(long *low, long *high, forEachCallType DoForEach)
{
  long          *ptr = low;
  struct Object *theObj;
  struct Object **theCell;

  while (ptr<=high){
    if(inBetaHeap((struct Object *)(*ptr))){
      theCell = (handle(Object)) ptr;
      theObj  = *theCell;
      if (inIOA(theObj) || inAOA(theObj)){
	DoForEach(*(ptr+1), (long)theObj);
      }
    } else {
      switch(*ptr){
	/* deliberately no breaks here */
      case -8: ptr++;
      case -7: ptr++;
      case -6: ptr++;
      case -5: ptr++;
	break;
      }
    }
    ptr++;
  }
}

#ifdef intel
#define IfIntel(code) code
#else
#define IfIntel(code)
#endif

int scanComponentStack (struct Component* comp,
			struct Object *curObj,
			int PC,
			forEachCallType forEach)
{
  /* scan through the stackpart corresponding to the comp parameter.
   * PC is the top code-address.
   * calling "forEach" for each (code-address, object) pair on the stack.
   */
  int stacktype, compfound;

  if (comp->StackObj){
    struct StackObject *sObj = comp->StackObj;
    ShowStackPart((long*)sObj->Body, 
		  (long*)((long)sObj->Body + sObj->StackSize),
		  forEach);
    return CS_STACKOBJ;
  }

  if (comp==ActiveComponent) {
    compfound = TRUE;
    stacktype = CS_ACTIVECOMPONENT;
    forEach(PC, (int)curObj);
  } else {
    compfound=0;
    stacktype=0;
  }

  /* Scan through the machine stack. This is an adaption of
   * DisplayBetaStack from outpattern.c - see comments in the code
   * there, especially for the small constants added or subtracted
   * from the stack positions.
   * See also doc/RunDoc.txt for a figure of the stack layout.
   */
  { 
    long                  *lowAddr;
    long                  *highAddr;
    struct CallBackFrame  *cbFrame;
    struct ComponentBlock *currentBlock;
    struct Object         *currentObject;
    struct Component      *currentComponent;
    long                  PC=0;
    
    /* First handle the topmost component block */
    currentComponent = ActiveComponent;
    lowAddr  = (long *) StackEnd;
    highAddr = (long *) lastCompBlock;
    cbFrame  = ActiveCallBackFrame; 

    while (cbFrame) {
      if (compfound) ShowStackPart((long*)lowAddr, (long *)cbFrame-2, forEach);
      lowAddr = cbFrame->betaTop;
      IfIntel(lowAddr += 4);
      cbFrame = cbFrame->next;
      if(compfound && isObject((ref(Object))(*lowAddr))) forEach(0,(*lowAddr));
      lowAddr += 2;
    }
    if (compfound) ShowStackPart(lowAddr, highAddr-3, forEach);  
    
    /* Then handle the remaining component blocks */
    currentBlock     = lastCompBlock;
    currentObject    = currentComponent->CallerObj;
    PC               = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
    
    while (currentBlock->next){
      if (currentComponent==comp) compfound=TRUE;
      lowAddr  = (long *)((long)currentBlock+sizeof(struct ComponentBlock))+1;
      highAddr = (ptr(long)) currentBlock->next;
      cbFrame  = currentBlock->callBackFrame;
      if (compfound && !cbFrame) forEach(PC, (int)currentObject);
      while (cbFrame) {
	if (compfound) ShowStackPart(lowAddr, (long *)cbFrame-2, forEach);
	lowAddr = cbFrame->betaTop;
	IfIntel(lowAddr += 4);
	cbFrame = cbFrame->next;
	if(compfound && isObject((ref(Object))(*lowAddr))){
	  forEach(0, (*lowAddr));
	}
	lowAddr += 2;
      }
      if (compfound) ShowStackPart(lowAddr, highAddr-3, forEach); 
      currentBlock     = currentBlock->next;
      currentObject    = currentComponent->CallerObj;
      PC               = currentComponent->CallerLSC;
      currentComponent = currentComponent->CallerComp;
    }
  }

  if (!stacktype){
    if (compfound){
      stacktype=CS_PROCESSORSTACK;
    } else {
      stacktype=CS_NOSTACK;
    }
  }
  return stacktype;
 
}
#endif

#ifdef NEWRUN

static int CompFound;
static int CompDone;
static Component *TheComponent;
static forEachCallType DoForEach;
static int BasicItemShown;

static void ShowCell(int PC, struct Object *theObj)
{
  if (theObj==(struct Object *)BasicItem){
    if (!BasicItemShown){
      TRACE_SCAN(fprintf(output, ", PC=0x%x *\n", PC));
      DoForEach(PC, (int)theObj);
      BasicItemShown=TRUE;
    }
  } else {
    TRACE_SCAN(fprintf(output, ", PC=0x%x *\n", PC));
    DoForEach(PC, (int)theObj);
  }
}

static void DoStackCell(struct Object **theCell,struct Object *theObj)
{ 
  register long PC;
  long *SP;

  TRACE_SCAN(fprintf(output, 
		     ">>>DoStackCell: theCell=0x%x, theObj=0x%x",
		     theCell, theObj);
	     fflush(output);
	     if (isObject(theObj)){
	       fprintf(output, ", proto=0x%x", theObj->Proto);
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
      SP = (long *)theCell+DYNOFF; /* Frame starts DYNOFF longs above dyn */
      SP = (long*)GetSPbeta(SP);   /* SP-beta */
      if (SP==0){
      /* We passed the main+CallB frames */
      return;
      }
      theObj = GetThis(SP);
      PC = 0;  /* not known - is somewhere in the C frames */
    } else {
      SP = (long *)theCell+DYNOFF; /* Frame starts DYNOFF longs above dyn */
      PC = *((long *)SP+PC_OFF);
    }
    
    /* Check if theObj is a component */
    if (theObj && (theObj->Proto==ComponentPTValue)){
      TRACE_SCAN(fprintf(output, " found next comp - stop\n"));
      /* Passing a component frame. The real dyn is found 
       * as theComp->CallerObj - see stack.c for details.
       */
      CompDone=TRUE;
      return;
    } 
    ShowCell(PC, theObj);
  } else {
    /* Not yet found */
    if (theObj==(struct Object *)TheComponent){
      /* Found: The real dyn is found as theComp->CallerObj 
       * - see stack.c for details.
       */	
      TRACE_SCAN(fprintf(output, " comp found"));
      CompFound=TRUE;
      PC = ((struct Component *)theObj)->CallerComp->CallerLSC;
      theObj = ((struct Component *)theObj)->CallerObj;
      ShowCell(PC, theObj);
    } else {
      TRACE_SCAN(fprintf(output, " comp not yet found\n"));
    }
  }
}

int scanComponentStack (struct Component* comp,
			struct Object *curObj,
			int PC,
			forEachCallType forEach)
{ /* scan through the stackpart corresponding to the comp parameter.
   * PC is the top code-address.
   * calling "forEach" for each (code-address, object) pair on the stack.
   */
  int stacktype=0;

  CompFound=FALSE;
  CompDone=FALSE;
  DoForEach = forEach;
  TheComponent = comp;
  BasicItemShown=0;

  if (comp->StackObj){
    struct StackObject *sObj = comp->StackObj;
    /* See ProcessStackObj in stack.c */
    CompFound = TRUE;

    /* Process top object in stack object */
    forEach(comp->CallerLSC, /* PC in comp top item */
	    (int)GetThis( (long *)((long)sObj->Body+(long)sObj->StackSize) )
	    );

    ProcessStackFrames((long)sObj->Body+(long)sObj->StackSize, /* top */
		       (long)sObj->Body+(long)sObj->BodySize,  /* bottom */
		       TRUE, 
		       TRUE,
		       DoStackCell
		       );
    return CS_STACKOBJ;
  }

  if (comp==ActiveComponent) {
    CompFound = TRUE;
    stacktype = CS_ACTIVECOMPONENT;
    forEach(PC, (int)curObj);
  }
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, DoStackCell);
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

# define objIsValRep(theObj) inLVRA(theObj)


struct ComponentStack{
  struct Component *comp; /* The component */
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
      struct RegWin* firstAR;
      struct RegWin* lastAR;
      struct RegWin* activeCBF;
    } if_onstack;
    /* if stacktype==CS_STACKOBJ: */
    struct StackObject *stackObj; 
  } info;
};

void handleStackPart (struct RegWin *theAR, int lastReturnAdr, forEachCallType forEach)
{ long* this, *end;
  struct Object *lastObj, *theObj;
  
  lastObj= (struct Object *) theAR->i0;
  forEach ((int) lastReturnAdr,(int) lastObj);
  
  this = (long *) (((long) theAR)+16*4);
  end = (long *) (((long) theAR->fp)-4);
  
  while (this<=end) {
    if (isCode(this[0])) {
      theObj = (struct Object *) this[2];
      if (inBetaHeap(theObj) 
	  && isObject(theObj) 
	  && !objIsValRep(theObj)) {
	/* Add 8 to get the real SPARC return address. */
	forEach (this[0]+8,(int) theObj);
	lastObj= theObj;
	this+=2;
      } else {
	forEach (this[0]+8,(int) lastObj);
      }
    }
    this+=2;
  }
}


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

static void findComponentStack (struct ComponentStack* compStack, int PC)
{ 
  struct RegWin *thisCompBlock = (struct RegWin *) lastCompBlock;
  struct RegWin *prevCompBlock = 0;
  struct Component *thisComponent = ActiveComponent;

  DEBUG_VALHALLA(fprintf (output,"Entering findComponentStack (SPARC)\n"));

  while (thisCompBlock) {
    if (compStack->comp == thisComponent){
      /* comp found on processor stack. */
      
      compStack->info.if_onstack.firstAR 
	= (struct RegWin *) thisCompBlock->fp;
      
      if (prevCompBlock) { 
	
	compStack->stacktype = CS_PROCESSORSTACK; 
	compStack->info.if_onstack.lastAR
	  = (struct RegWin *) prevCompBlock->fp;
	compStack->returnAdr = thisComponent->CallerLSC;
	compStack->info.if_onstack.activeCBF 
	  = (struct RegWin *) prevCompBlock->l5;

      } else {
	/* comp is the active component. */

	compStack->stacktype = CS_ACTIVECOMPONENT;
	compStack->info.if_onstack.lastAR = (struct RegWin *) StackEnd;

	compStack->info.if_onstack.activeCBF 
	  = (struct RegWin *) ActiveCallBackFrame;
	compStack->returnAdr = PC;
	
      }
      DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
      return;
    } else {
      prevCompBlock = thisCompBlock;
      thisCompBlock = (struct RegWin *) thisCompBlock->l6; /* See SparcDoc.c */
      thisComponent = thisComponent->CallerComp;
    }
  }

  /* Component not found on the processor stack.
   * If the component has ever been attached and suspended, it should have
   * been assigned a stack object.
   * Otherwise it has no stack at all. */

  switch ((int) compStack->info.stackObj = compStack->comp->StackObj) {
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


int scanComponentStack (struct Component* comp,
			struct Object *curObj,
			int PC,
			forEachCallType forEach)
{ struct ComponentStack compStack;

  compStack.comp = comp;

  DEBUG_VALHALLA(fprintf (output,"Entering scanComponentStack. \n"));

  findComponentStack (&compStack,PC);

  DEBUG_VALHALLA(fprintf (output,"FindComponentStack done. stacktype = %d. \n",compStack.stacktype));

  switch (compStack.stacktype) {
  case CS_NOSTACK: 
    break;
  case CS_STACKOBJ:
    { struct StackObject *theStack = compStack.info.stackObj;
      struct RegWin *theAR;
      int lastReturnAdr = compStack.returnAdr; 
      
      /* ASSUMES THAT THERE ARE NO CALLBACK FRAMES IN A COMPONENT OBJECT.
       * IF THIS CHANGES, SO SHOULD THE CODE BELOW. */
      
      /* Start at theStack->Body[1], since theStack->Body[0] 
       * is saved FramePointer */
      long delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];
      
      for (theAR =  (struct RegWin *) &theStack->Body[1];
	   theAR != (struct RegWin *) &theStack->Body[theStack->StackSize];
	   theAR =  (struct RegWin *) (theAR->fp + delta))
	{
	  handleStackPart (theAR,lastReturnAdr,forEach);
	  lastReturnAdr = theAR->i7+8;
	}
    };
    break;
  case CS_PROCESSORSTACK:
  case CS_ACTIVECOMPONENT:
    { struct RegWin *theAR = compStack.info.if_onstack.lastAR;
      struct RegWin *nextCBF = compStack.info.if_onstack.activeCBF;
      int lastReturnAdr = compStack.returnAdr;

      DEBUG_VALHALLA(fprintf(output,"BetaStackTop = %d\n",(int)BetaStackTop));
      if (nextCBF)
      /* Skip external code on top of stack: */
      while ((unsigned int) theAR < (unsigned int) BetaStackTop) {
	DEBUG_VALHALLA(fprintf(output,"External return address: "));
	forEach (lastReturnAdr,0);
	lastReturnAdr = theAR->i7+8;
	theAR = (struct RegWin *) theAR->fp;
      }	
      
      for (;theAR != compStack.info.if_onstack.firstAR;
	   theAR = (struct RegWin *) theAR->fp)
	{
	  if (theAR == nextCBF) {
	    /* This is AR of HandleCB. Skip this and
	     * skip to betaTop and update nextCBF
	     */
	    nextCBF = (struct RegWin *) theAR->l5;
	    { /* Wind down the stack until betaTop is reached. Needed in 
	       * order to update lastReturnAdr. */
	      struct RegWin *cAR;
	      forEach (lastReturnAdr,0);
	      lastReturnAdr = theAR->i7+8;
	      for (cAR = theAR;
		   cAR != (struct RegWin *) theAR->l6;
		   cAR = (struct RegWin *) cAR->fp) {
		forEach (lastReturnAdr,0);
		lastReturnAdr = cAR->i7+8;
	      }
	    }
	    theAR = (struct RegWin *) theAR->l6; /* Skip to betaTop */
	  }
	  handleStackPart (theAR,lastReturnAdr,forEach);
	  lastReturnAdr = theAR->i7+8; /* First return address used is actually PC of the process. 
					* For other return addresses, add 8. */
	};
      break;
    }
  }
  return compStack.stacktype;
}

#endif /* sparc */
#endif /* RTVALHALLA */
