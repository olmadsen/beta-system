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

/* DoStackCell:
 *  Used by the routines that traverse the stack.
 */
void
DoStackCell(Object **theCell,Object *theObj)
{    
#ifdef intel
  DEBUG_STACK({ 
    fprintf(output, "0x%08x: ", (int)theCell);
    PrintObject(theObj);
    fprintf(output, "\n");
  });
#endif /* intel */
  if (!theObj) {
    return;
  }
  if (inBetaHeap(theObj)) {
    if (isObject(theObj)){
      DEBUG_CODE(if (!CheckHeap) Ck(theObj));
      ProcessReference(theCell, REFTYPE_DYNAMIC);
      CompleteScavenging();
    } else {
      DEBUG_CODE({
        fprintf(output, "[DoStackCell: ***Illegal: 0x%x: 0x%x]\n", 
                (int)theCell,
                (int)theObj);
        ILLEGAL;
      });
    }
  } else {
    /* Object pointing outside BETA heaps. Maybe a COM reference? */
    DEBUG_CODE({
      fprintf(output, 
	      "0x%08x: 0x%08x stack cell points outside BETA. COM?\n", 
	      (int)theCell, 
	      (int)theObj);
      NEWRUN_CODE({
	/* Because of the very well-defined structure of stackframes
	 * there should be no GC-able cells, that refer outside BETA heaps.
	 */
	if ((theObj!=CALLBACKMARK)&&(theObj!=GENMARK)){
	  ILLEGAL;
	}
      });
    });
  }
}

#ifdef RTVALHALLA
/************************* CollectStackRoots: **************************/
/* Will return NULL-terminated list of stack adresses between 
 * StackStart and SPcontaining roots for GC. 
 * Caller must free list after use.
 */
static long *StackRoots = 0;
static int   StackRootsTop = 0;
static int   StackRootsSize = 128;

static void SaveStackCell(long theCell)
{
  if (StackRootsTop>=StackRootsSize){
    StackRootsSize *=2;
    StackRoots = (long*)REALLOC(StackRoots, StackRootsSize*sizeof(long*));
  }
  StackRoots[StackRootsTop++]=theCell;
}

static void CollectStackCell(Object **theCell,Object *theObj)
{    
  if (!theObj) {
    return;
  }
  if (inBetaHeap(theObj)) {
    if (isObject(theObj)){
      /* Found a root */
      SaveStackCell((long)theCell);
    }
  }
}

long *CollectStackRoots(long *SP)
{ 
  StackEnd = SP;
  StackRootsTop = 0;
  StackRootsSize = 128;
  StackRoots = (long*)MALLOC(StackRootsSize*sizeof(long*));
#ifdef sparc
  __asm__("ta 3");
  DEBUG_CODE(frame_PC = 0);
#endif /* sparc */
  GeneralProcessStack(CollectStackCell);
  /* NULL terminate */
  SaveStackCell(0);
  return StackRoots;
}

/************************* ProcessStack: ***************************/
void ProcessStack(void)
{
    GeneralProcessStack(DoStackCell);
}


#endif /* RTVALHALLA */

#endif /* MT */
