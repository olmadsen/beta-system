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

#ifdef RTDEBUG
void PrintRefStack(void)
{
  long *theCell = (long *)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;
  fprintf(output, "RefStk: [%x .. %x[\n", (int)&ReferenceStack[0], (int)RefSP);
  for(; size > 0; size--, theCell++){
    if (((*theCell)!=ExternalMarker) && (*theCell & 1)){ 
      /* Used in beta.dump */
      fprintf(output, "  0x%08x: 0x%08x #\n", (int)theCell, (int)(*theCell));
    } else {
      fprintf(output, "  0x%08x: 0x%08x\n", (int)theCell, (int)(*theCell));
    }
  }
}
#endif

void ProcessRefStack(unsigned size, Object **bottom, CellProcessFunc func)
{
  long i=0;
  Object **theCell;

  DEBUG_IOA(PrintRefStack());
  theCell = bottom;
  for(; size > 0; size--, theCell++) {
    i = ((unsigned)*theCell & 1);
    *theCell = (Object *)((unsigned)*theCell & ~1);

#ifdef RTVALHALLA
    /* If i=1 then the cell is tagged, and the previous cell that was
     * processed was actually a return address. This can newer be confused with
     * a BETA object, so it does not matter except for speed.
     */
#endif
    DEBUG_IOA(fprintf(output, "ProcessRefStack: 0x%08x: 0x%08x\n", 
		      (int)theCell, (int)(*theCell)));
    func(theCell, *theCell);
    DEBUG_CODE({
      if (*theCell
	  && !inBetaHeap(*theCell) && !isObject(*theCell)
	  && !isProto(*theCell) /* e.g. AlloI is called with prototype in ref. reg. */
	  && !isCode(*theCell)  /* e.g. at INNER a ref. reg contains code address */
	  && (*theCell!=(Object *)ExternalMarker)
	  ) {
	fprintf(output, "[ProcessRefStack: ***Illegal: 0x%x: 0x%x]\n", 
		(int)theCell, 
		(int)*theCell);
	ILLEGAL;
      }
    });
    *theCell = (Object *)((unsigned)*theCell | i);
  }
}

void
GeneralProcessStack(CellProcessFunc func)
{
  ProcessRefStack(((unsigned)RefSP-(unsigned)&ReferenceStack[0]) >> 2,
                  (Object **)ReferenceStack, 
		  func);
}

/*
 * ProcessHPPAStackObj
 * A stackobject on the snake looks like this:
 * Header
 * Body (the runtime stack-section)
 * RefStackLength
 * RefStack section
 */
void
ProcessStackObj(StackObject *sObj, CellProcessFunc func)
{
  long *        theEnd;
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

  Claim(sObj->StackSize <= sObj->BodySize, "StackObject: Stack <= Object");

  theEnd = &sObj->Body[0] + sObj->StackSize;

  ProcessRefStack(*theEnd, (Object **)(theEnd+1), func);

  DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj));
  DEBUG_CODE(DebugStack=oldDebugStack);
}

/************ beta.dump/valhalla/exception stuff below *****************/
void DisplayHPPAStack(long *thePC) 
{
  /* FIXME: Could possibly use ProcessHPPAStack with appropriate func */

#ifdef UseRefStack
  /*
   * The ReferenceStack way of tracing the Beta stack.
   */
  Object **theCell = /*getRefSP()*/ (Object **)(RefSP-1);
  Object *theObj;
  long   *pc=thePC;
  
  while((void **)theCell > &ReferenceStack[0]) {
    if ((*theCell)==(Object *)ExternalMarker){
      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
    } else if ((unsigned)*theCell & 1) {
      /* The reference is tagged: Should appear in beta.dump */
      theObj = (Object *)((unsigned)*theCell & ~1);
      pc = 0; /* No way to tell the PC ?? */
#if 0 /* not yet */
#ifdef RTVALHALLA
      theCell--;
      pc = (long *)*theCell
#endif
#endif
	if(theObj && isObject(theObj)) {
	  /* Check if theObj is inlined in a component */
	  if (!isComponent(theObj) && IsComponentItem(theObj)) {
	    DisplayObject(output, 
			  (Object *)EnclosingComponent(theObj), 
			  (long)pc);
	    if (theObj==(Object *)BasicItem) break;
	  } else {
	    DisplayObject(output, theObj, (long)pc);
	  }
	} else {
	  if (theObj) fprintf(output, "  [Damaged object!: %x]\n", (int)theObj);
	}
    }
    theCell--;
  }
  fflush(output);
#else
#error DisplayHPPAStack not implemented
#endif /* UseRefStack */
}

int scanComponentStack (Component* comp,
			Object *curObj,
			int pc,
			CellDisplayFunc forEach)
{ 
  fprintf(output, "scanComponentStack: NYI\n");
  return 0;
}

#endif /* MT */
