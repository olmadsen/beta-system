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
