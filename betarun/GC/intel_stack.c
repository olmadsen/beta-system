/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * stack.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 *
 * Traverse an stack parts and process all references.
 */

#include "beta.h"

#ifndef MT

extern void (*StackRefAction)(REFERENCEACTIONARGSTYPE);

/************************* Valhalla/persist reference stack ****************/
#ifdef RTVALHALLA

/* Various stuff for supporting valhalla evaluators (VOP_EXECUTEOBJECT) */

#ifdef RTDEBUG
void PrintValhallaRefStack(void)
{
  Object *theObj;
  Object **theCell = (Object **)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;

  fprintf(output, "\nReferenceStack: [%x .. %x[\n", (int)&ReferenceStack[0], (int)RefSP);
  for(; size > 0; size--, theCell++){
    theObj = *theCell;
    fprintf(output, "  0x%08x: 0x%08x\n", (int)theCell, (int)theObj);
    if (theObj && inBetaHeap(theObj) && isObject(theObj)) {
      /* Normal object */
    } else {
      if (theObj
          && !isProto(theObj) /* e.g. AlloI is called with prototype in ref. reg. */
          && !isCode(theObj)  /* e.g. at INNER a ref. reg contains code address */
          ) {
        fprintf(output, "[ProcessRefStack: ***Illegal: 0x%x: 0x%x]\n",
                (int)theCell,
                (int)theObj);
        ILLEGAL;
      }
    }
  }
}
#endif /* RTDEBUG */

void ProcessValhallaRefStack(void)
{
  Object *theObj;
  Object **theCell = (Object **)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;

  DEBUG_IOA(PrintValhallaRefStack());
  for(; size > 0; size--, theCell++) {
    theObj = *theCell;
    if (theObj && inBetaHeap(theObj) && isObject(theObj)) {
      ProcessReference(theCell, REFTYPE_DYNAMIC);
      CompleteScavenging();
    }
  }
}

#endif /* RTVALHALLA */

/************************* End Valhalla reference stack ****************/


#define MAXDATAREGSONSTACK 40 /* 4+(108/4)=31 would suffice, see fnsave */
int SkipDataRegs(long *theCell)
{
  /* Test for tagged data regs on stack. The compiler may push
   * floating point and busy %o-registers. If so it has
   * pushed a tag constructed as tag = -(n+4), where n is the number of
   * 4-byte stack-cells to skip. 
   * 
   * Returns number of longs to skip (exluding tag)
   */
  long tag = *theCell /* potential tag */;
  DEBUG_CODE(Object *ref = (Object *)tag);
  if ((-(MAXDATAREGSONSTACK+4)<=tag) && (tag<=-4)){
    DEBUG_STACK({
      long *ptr;
      long *end;
      end = theCell+(-tag-4);
      fprintf(output, 
	      "0x%08x: %d: Skipping tag and %d long (4-byte) stack cells:\n", 
	      (int)theCell,
	      (int)tag,
	      (int)-tag-4);
      for (ptr = theCell+1 /* start at cell after tag */; 
	   ptr <= end;
	   ptr++){
	fprintf(output, 
		"0x%08x: 0x%08x", 
		(int)ptr, 
		*(int*)ptr);
	if (ptr<=(end-1)){
	  fprintf(output, " %8.8g", *(double*)ptr);
	} 
	if (ref && 
	    inBetaHeap(ref) && 
	    isObject(ref) && 
	    IsPrototypeOfProcess((long)GETPROTO(ref))){ 
	  fprintf(output, "\n\t*** SUSPICIOUS STACK-SKIP!");
	  fflush(output);
	  fprintf(output, 
		  " proto: 0x%08x (%s)", 
		  (int)GETPROTO(ref), 
		  ProtoTypeName(GETPROTO(ref))); 
	} 
      }
      fprintf(output, "\n--------\n");
      fflush(output);
    });
    /* Do the skip  */
    return (-tag-4);
  } else {
    DEBUG_CODE({
      if (tag < 0 && -4 < tag) {
	fprintf(output, 
		"*** 0x%08x: %d: Negative non-tag stack cell!\n", 
		(int)theCell,
		(int)tag);
	ILLEGAL;
      }
    });
  }
  return 0;
}

/* Traverse the StackArea [low..high] and Process all references within it. */
void ProcessStackPart(long *low, 
		      long *high, 
		      CellProcessFunc whenObject, 
		      CellProcessFunc whenNotObject)
{
  long * current = low;
  Object * theObj;
  Object ** theCell;
  DEBUG_STACK({
    fprintf(output, 
	    "\n----- AR: low: 0x%08x, high: 0x%08x\n", (int)low, (int)high);
    fprintf(output, 
	    "ComponentBlock/CallbackFrame: [0x%08x, 0x%08x, 0x%08x]\n", 
	    (int)(*(high+1)), 
	    (int)(*(high+2)), 
	    (int)(*(high+3))
	    );
    });
  Claim( high <= (long *)StackStart, "ProcessStackPart: high<=StackStart" );
  
  while( current <= high ){
    if(inBetaHeap((Object *)*current)){
      theCell = (Object **) current;
      theObj  = *theCell;
      if (isObject(theObj)) {
	if (whenObject) {
	  whenObject(theCell, theObj);
	}
      } else {
	DEBUG_CODE({
	  if (!isValRep(theObj)){
	    fprintf(output, "*** SUSPICIOUS REFERENCE ON STACK:\n  0x%08x: 0x%08x", 
		    (int)current, (int)(*current));
	    if (IsPrototypeOfProcess((long)GETPROTO(theObj))){
	      fprintf(output, " Proto: 0x%08x (%s)\n",
		      (int)GETPROTO(theObj),
		      ProtoTypeName(GETPROTO(theObj)));
	    } else {
	      fprintf(output, " *** ILLEGAL PROTOTYPE: 0x%08x\n", (int)GETPROTO(theObj));
	    }
	  }
	});
      }
    } else {
      /* Not in beta heap */
      int skip = SkipDataRegs(current);
      if (skip){
	current += skip;
      } else {
	if (whenNotObject){
	  whenNotObject((Object**)current, *(Object**)current);
	} else {
	  /* Default action on non-object cells on stack */
	  DEBUG_STACK({
	    fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
	    if (*current) {
	      if (IsPrototypeOfProcess(*current)) {
		fprintf(output, ", is proto  (");
		PrintProto((ProtoType*)*current);
		fprintf(output, ")\n");
	      } else {
		fprintf(output, " ");
		PrintCodeAddress(*current);
		fprintf(output, "\n");
	      }
	    } else {
	      fprintf(output, "\n");
	    }
	  });
	}
      }
    }
    current++;
  }
}

static 
long *ProcessCallbackFrames(CallBackFrame *cbFrame, long *low)
{
  while (cbFrame){
    ProcessStackPart(low, (long *)cbFrame-1, DoStackCell, 0);
    low     = cbFrame->betaTop;
    cbFrame = cbFrame->next;
  }
  return low;
}

/* ProcessINTELStack: */
void
GeneralProcessStack(CellProcessFunc func)
{
    long *low                    = StackEnd;
    long *high                   = (long *) lastCompBlock;
    CallBackFrame *cbFrame       = ActiveCallBackFrame;
    ComponentBlock *currentBlock = lastCompBlock;
    
    DEBUG_STACK(fprintf(output, "\n ***** Trace of stack *****\n"));
    /*
     * First handle the topmost component block
     */
    if (cbFrame){ low = ProcessCallbackFrames(cbFrame, low); }
    ProcessStackPart(low, high-1, func,0);  
    
    /*
     * Then handle the remaining component blocks.
     */
    while (currentBlock->next){
	low      = (long *) ((long) currentBlock + sizeof(ComponentBlock) );
	high     = (long *) currentBlock->next;
	cbFrame  = currentBlock->callBackFrame;
	if (cbFrame){ low = ProcessCallbackFrames(cbFrame, low); }
	ProcessStackPart(low, high-1, func,0);  
	currentBlock = currentBlock->next;
    }
    DEBUG_STACK(fprintf(output, " *****  End of trace  *****\n"));
}

#ifdef RTDEBUG
static
void TraceStackObject(Object **current)
{
  if(inBetaHeap(*current)){
    Object *theObj = *current;
    if (isObject(theObj)) {
      fprintf(output, "0x%08x: ", (int)current);
      PrintObject(*(Object**)current);
      fprintf(output, "\n");
    } else {
      if (!isValRep(theObj)){
	fprintf(output, "*** SUSPICIOUS REFERENCE IN STACKOBJ: 0x%08x: 0x%08x", 
		(int)current, (int)(*current));
	if (IsPrototypeOfProcess((long)GETPROTO(theObj))){
	  fprintf(output, " Proto: 0x%08x (%s)\n",
		  (int)GETPROTO(theObj),
		  ProtoTypeName(GETPROTO(theObj)));
	} else {
	  fprintf(output, " *** ILLEGAL PROTOTYPE: 0x%08x\n", (int)GETPROTO(theObj));
	}
      }
    }
  } else {
    fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
    if (*current) {
      if (IsPrototypeOfProcess((long)*current)) {
	fprintf(output, ", is proto  (");
	PrintProto((ProtoType*)*current);
	fprintf(output, ")\n");
      } else {
	fprintf(output, " ");
	PrintCodeAddress((long)*current);
	fprintf(output, "\n");
      }
    } else {
      fprintf(output, "\n");
    }
  }
}
#endif /* RTDEBUG */

/* ProcessINTELStackObj */
void
ProcessStackObj(StackObject *sObj, CellProcessFunc func)
{ 
  long    *current; 
  long    *theEnd;
  DEBUG_CODE(long oldDebugStack=DebugStack);

  DEBUG_STACKOBJ({
      fprintf(output,
	      " *-*-* StackObject: 0x%x, size: 0x%x %s *-*-*\n", 
	      (int)sObj, 
	      (int)(sObj->StackSize),
	      WhichHeap((Object*)sObj));
      fprintf(output, "func is 0x%x", (int)func);
      PrintCodeAddress((long)func);
      fprintf(output, "\n");
      fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
      PrintCodeAddress((long)StackRefAction);
      fprintf(output, "\n");
  });
  DEBUG_CODE(if (DebugStackObj){
    DebugStack=TRUE;
  } else {
    DebugStack=FALSE;
  });
    
  Claim(sObj->StackSize <= sObj->BodySize, "sObj->StackSize <= sObj->BodySize");
	    
  theEnd = &sObj->Body[0] + sObj->StackSize;
	
  for (current = &sObj->Body[0]; current < theEnd; current++) {
    int skip = SkipDataRegs(current);
    if (skip){
      current += skip;
    } else {
      DEBUG_STACKOBJ(TraceStackObject((Object**)current)) /* DEBUG_STACKOBJ */;
      func((Object**)current, *(Object**)current);
    }
  }
  DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj));
  DEBUG_CODE(DebugStack=oldDebugStack);
}

/* beta.dump stuff below */

static Object *prevObj=0;
static CellDisplayFunc displayFunc=0;

static void objectMet(Object **theCell, Object *theObj)
{
  if (!strongIsObject(theObj)) {
        TRACE_DUMP(fprintf(output, "(strongIsObject failed!?)\n"));
	return;
  }
  if ((!inBetaHeap(*(theCell+1))) && IsBetaCodeAddrOfProcess((long)*(theCell+1))){
    /* Found an object with a PC just below it on stack */
    prevObj = theObj;
    TRACE_DUMP(fprintf(output,"new prevObj: "); DescribeObject(prevObj));
    if (!isComponent(prevObj) && IsComponentItem(prevObj)){
      prevObj = (Object*)EnclosingComponent(prevObj);
      TRACE_DUMP({
	fprintf(output, 
		" is item of component 0x%x\n", 
		(int)prevObj);
      });
    }
    TRACE_DUMP(fprintf(output, "\n"));
  } else {
    /* Probably a pushed register */
    TRACE_DUMP(fprintf(output, "(object with no PC below)\n"));
  }
}

static void nonObjectMet(Object **theCell, Object *theObj)
{
  if (IsBetaCodeAddrOfProcess((long)theObj)){
    /* Found a BETA PC */
    long pc=(long)theObj;
    TRACE_DUMP(PrintCodeAddress(pc));
    if (prevObj){
      TRACE_DUMP(fprintf(output, "\n"));
      displayFunc(pc, prevObj);
    } else {
      TRACE_DUMP(fprintf(output, " (no prevObj)"));
    }
  }
}

/* DisplayStackPart:
 * Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
void DisplayStackPart(long *low, 
		      long *high,
		      Object *currentObject,
		      CellDisplayFunc func)
{
  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackPart [0x%x..0x%x]\n", (int)low, (int)high));
  prevObj = currentObject;
  TRACE_DUMP({
    fprintf(output, ">>>TraceDump: Initial prevObj: "); 
    DescribeObject(prevObj); fprintf(output, "\n");
  });
  if (prevObj && !isComponent(prevObj) && IsComponentItem(prevObj)){
    prevObj = (Object*)EnclosingComponent(prevObj);
    TRACE_DUMP(fprintf(output, " is item of component 0x%x\n", (int)prevObj));
  }  
  displayFunc = func;
  ProcessStackPart(low, high, objectMet, nonObjectMet);
  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackPart done.\n"));
}

long *DisplayCallbackFrames(CallBackFrame *cbFrame,
			    long *low,
			    Object *currentObject,
			    CellDisplayFunc func)
{
  TRACE_DUMP({
    fprintf(output, 
	    ">>>DisplayCallbackFrames: cbFrame: 0x%x, low: 0x%x\n", 
	    (int)cbFrame,
	    (int)low);
  });
  while (cbFrame) {
    DisplayStackPart(low, (long *)cbFrame-2, currentObject, func);
    /* -2 because 2 longs are not shown:
     *    1. The last of the three pushed words in the callback frame
     *    2. The address of the call back stub.
     */
    TRACE_DUMP(fprintf(output, "  cb: "));
    if (isMakingDump){
      /* beta.dump */
      fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n"); 
    } else {
      /* valhalla/system exceptions */
    }
    low = cbFrame->betaTop;
    if (idMakingDump) {
      low += 3;
      /* low+3 because the compiler pushes %edx, %edi, %ebp, %esi
       * before setting BetaStackTop.
       * Of these we only want to see %edx (current object).
       */
    } else {
      TRACE_DUMP(fprintf(output, 
			 ">>>DisplayCallbackFrames: not skipping 3 words before callback\n"));
    }
    cbFrame = cbFrame->next;
    if (isObject((Object *)(*low))) {
      Object *obj = (Object*)(*low);
      TRACE_DUMP({
	fprintf(output, 
		">>>DisplayCallbackFrames: low: 0x%x: 0x%x ", (int)low, (int)obj);
	DescribeObject(obj);
	fprintf(output, "\n"); 
      });
      if (!isComponent(obj) && IsComponentItem(obj)){
	  obj = (Object*)EnclosingComponent(obj);
	  TRACE_DUMP({
	    fprintf(output, " is item of component 0x%x\n", (int)obj);
	  });
      }
      TRACE_DUMP({ fprintf(output, ">>>DisplayCallbackFrames: func(0, obj)\n");});
      func(0, obj); /* PC=0 since we cannot easily determine where the PC is
		     * saved when the external was called: BetaStackTop was set before 
		     * arguments to the external were pushed. So if we were to
		     * figure out where the PC was saved, we need to know how many 
		     * arguments the external has.
		     */
    }
    low += 1; /* Skip the object */
    TRACE_DUMP({
      fprintf(output, 
	      ">>>DisplayCallbackFrames: cbFrame: 0x%x, low: 0x%x\n", 
	      (int)cbFrame,
	      (int)low);
    });
  }
  TRACE_DUMP({
    fprintf(output, 
	    ">>>DisplayCallbackFrames: returning low: 0x%x\n",
	    (int)low);
  });
  return low;
}

void DisplayINTELStack(BetaErr errorNumber, 
		       Object *currentObject, 
		       long pc, 
		       long theSignal /* theSignal is zero if not applicable. */
		       )
{ 

  /* FIXME: Could possibly use ProcessINTELStack with appropriate func */
  Component       *currentComponent = ActiveComponent;
  long            *low              = (long *) StackEnd;
  long            *high             = (long *) lastCompBlock;
  CallBackFrame   *cbFrame          = ActiveCallBackFrame; 
  ComponentBlock  *currentBlock;

  /*
   * Handle the topmost component block, designated by 
   * StackEnd, ActiveCallbackFrame and lastCompBlock.
   */

  /* First check for errors occured outside BETA */
  if (!IsBetaCodeAddrOfProcess(pc)){
    fprintf(output, 
	    "  [ EXTERNAL ACTIVATION PART (address 0x%x",
	    (int)error_pc
	    );
    if (!SimpleDump) PrintCodeAddress((long)pc);
    fprintf(output, ") ]\n");
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
    /* The PC corresponding to the BETA object that called C is just 
     * above BetaStackTop.
     * NO: First comes the arguments for the external.
     * Here we cannot determine how many of these there are.
     */
    /* pc = *(BetaStackTop-1); */

    /* Adjust low to low+3 because the compiler pushes %edx, %edi, %ebp, %esi
     * before setting BetaStackTop.
     * Of these we only want to see %edx (current object).
     */
    low += 3;

    /* Since a new prevObj will be met by DisplayStackPart before 
     * any other PC corresponding to currentObject, the current object that
     * called C will not be displayed by DisplayStackPart.
     * So we display it here.
     */
    TRACE_DUMP(fprintf(output, "Displaying current object\n"));
    DisplayObject(output, currentObject, 0 /*pc*/);

  }

  if (cbFrame){
    /* Display callbackframes in the component */
    low = DisplayCallbackFrames(cbFrame, low, currentObject, DisplayCell);
  }

  /* Displays the objects from where the last callback was initiated
   * (if any) and onwards to the ComponentBlock.
   */
  DisplayStackPart(low, high-3, currentObject, DisplayCell);  
  /* -3 because 3 longs are not shown: 
   *    1. The last of the three pushed words in the comp block
   *    2. The address of the M-part for the component.
   *    3. The current object saved by the M-part.
   */
  
  /*
   * Then handle the remaining component blocks designated by the linked
   * list of ComponentBlocks from lastCompBlock and onwards.
   */
  currentBlock     = lastCompBlock;
  currentObject    = currentComponent->CallerObj;
  pc               = currentComponent->CallerLSC;
  currentComponent = currentComponent->CallerComp;
  
  while (currentBlock->next){
    low  = (long *)((long)currentBlock+sizeof(ComponentBlock))+1
      /* +1 because the compiler always pushes the component before calling
       * attach.
       */;
    high = (long *) currentBlock->next;
    cbFrame  = currentBlock->callBackFrame;
    
    /* Display current object in ComponentBlock */
    if (cbFrame){
      /* Current object will be shown along with the first CB frame */
      TRACE_DUMP(fprintf(output, ">>>TraceDump: current: 0x%x\n", (int)currentObject));
    } else {
      if (!isComponent(currentObject) && IsComponentItem(currentObject)){
	DisplayObject(output, (Object*)EnclosingComponent(currentObject), pc);
      } else {
	DisplayObject(output, currentObject, pc);
      }
    }

    if (cbFrame){
      /* Display callbackframes in the component */
      low = DisplayCallbackFrames(cbFrame, low, currentObject, DisplayCell);
    }
    
    /* Displays the objects from where the last callback was initiated
     * (if any) and onwards to the ComponentBlock.
     */
    DisplayStackPart(low, high-3, currentObject, DisplayCell); 
    /* -3 because:
     *  3 longs are not shown: 
     *    1. The last of the three pushed words in the comp block
     *    2. The address of the M-part for the component.
     *    3. The current object saved by the M-part.
     */

    currentBlock     = currentBlock->next;
    currentObject    = currentComponent->CallerObj;
    pc               = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
  }
}

#ifdef RTDEBUG

static 
void PrintStackCell(Object **theCell, Object *theObj)
{
  fprintf(output, "0x%08x: ", (int)theCell);
  PrintObject(theObj);
  fprintf(output, "\n");
}

/* PrintStackPart: (intel)
 * Traverse the StackArea [low..high] and print all references within it. 
 */
void PrintStackPart(long *low, long *high)
{
  ProcessStackPart(low, high, PrintStackCell,0);
}

/* PrintStack: (intel)
 * Notice that StackEnd MUST be supplied!
 */
void PrintStack(long *StackEnd)
{
  /* FIXME: Could find stack top from here with (e.g. &theTop),
   * but it may sometimes be useful to display from another SP.
   */
  long *          theTop;
  long *          theBottom;
  
  CallBackFrame *  theFrame;
  ComponentBlock * currentBlock;
  
  fprintf(output, "\n ***** Trace of stack *****\n");
  /*
   * First handle the topmost component block
   */
  theTop    = StackEnd;
  theBottom = (long *) lastCompBlock;
  theFrame  = ActiveCallBackFrame;
  /* Follow the stack */
  while( theFrame){
    PrintStackPart( theTop, (long *)theFrame-1);
    theTop   = theFrame->betaTop;
    theFrame = theFrame->next;
  }
  PrintStackPart( theTop, theBottom-1);  
  
  /*
   * Then handle the remaining component blocks.
   */
  currentBlock = lastCompBlock;
  while( currentBlock->next ){
    theTop    = (long *) ((long) currentBlock +
			  sizeof(ComponentBlock) );
    theBottom = (long *) currentBlock->next;
    theFrame  = currentBlock->callBackFrame;
    while( theFrame){
      PrintStackPart( theTop, (long *)theFrame-1);
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
    }
    PrintStackPart( theTop, theBottom-1);  
    currentBlock = currentBlock->next;
  }
  fprintf(output, " *****  End of trace  *****\n");
}

#endif /* RTDEBUG */

#endif /* MT */
