/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Oerbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

#ifdef PERSIST
#include "../P/PException.h"
#include "../P/unswizzle.h"
#endif /* PERSIST */

/* Qua check.
 * The reference assignment src[]->dst[] has just been made. dst resides in 
 * theCell.
 * Perform.
 *   1. CheckReferenceAssigment
 *   2. Qua Check: Check if the actual qualification of src is less than 
 *      or equal to qualification of dst, as given by dstQuaProto and 
 *      dstQuaOrigin.
 */

/* Sloppy qua-check, only prototypes are considered */

ParamProtoCellOriginThis(Qua)
{
  Object * src;
  /* the source can be found in theCell since the assignment *has* been done */
  ProtoType * srcProto;
  FetchParamProtoCellOriginThis();

  DEBUG_CODE(NumQua++);

  src = *theCell;
  
#ifdef PERSIST
  /* If src is to an unloaded persistent object, we load the object */
  if (inPIT((void *)src)) {
    *theCell = src = unswizzleReference((void *)src);
  }
#endif /* PERSIST */
  
  DEBUG_CODE({
    if (src && !inBetaHeap(src)){
      fprintf(output, 
	      "Qua: theCell: 0x%08x, *theCell: 0x%x\n",
	      (int)theCell,
	      (int)*theCell);
      Claim(0, "inBetaHeap(*theCell)");
    }
  });
  
  if (src) {
    /* If src is NONE or indirect, all is well */
    
#ifdef RTLAZY
    srcProto = 0;
    /* 1. Check reference assignment */
    if (isLazyRef(src)) {
      /* Qua check on lazy reference */
      if (! inIOA(theCell)) /* inAOA? */
	/* in AOA area. */
	negAOArefsINSERT((long)theCell);
      srcProto = (ProtoType *) findDanglingProto((int)src);
    } else {
#endif /* RTLAZY */
      if (! inIOA(theCell) /* inAOA? */&& inIOA(src)){
#ifdef MT
	MT_AOAtoIOAInsert(theCell);
#else /* MT */
	AOAtoIOAInsert(theCell);
#endif /* MT */
      }
#ifdef RTLAZY
    }
#endif /* RTLAZY */

    Ck(src);
    
    /* 2. Qua Check */
#ifdef RTLAZY
    if (srcProto == 0) {
      /* src was not a dangler so its prototype has not been looked up yet. */
#endif
      switch(SwitchProto(GETPROTO(src))){
      case SwitchProto(StructurePTValue):
	/* It was a pattern variable assignment: src is a struc-object */
	srcProto  = ((Structure *)src)->iProto;
	break;
      case SwitchProto(ComponentPTValue):
	/* It was a component-reference assignment: src points to a component */
	src       = (Object *)((Component *)src)->Body;
	srcProto  = GETPROTO(src);
	break;
      default:
	/* It was a normal reference assignment: src is normal object */
	srcProto  = GETPROTO(src);
	break;
      }
#ifdef RTLAZY
    }
#endif
    
    /* Check for eqS */
    if (srcProto == dstQuaProto){
      /* Structures are identical. All is OK */
    } else {
      do {
	/* Inlined version of ltS without struc objects, and not checking origins */
	ProtoType * proto1 = srcProto;
	
	if (dstQuaProto->Prefix == dstQuaProto){
	  /* dstQuaProto is Object## */
	  return;
	}
	
	/* Prefix of srcProto is the first try */
	for (proto1 = proto1->Prefix;
	     proto1 != proto1->Prefix; /* proto1 != Object## */
	     proto1 = proto1->Prefix) {
	  if (proto1 == dstQuaProto) {
	    /* dstQuaProto is a prefix of srcProto; all is OK */
	    return; /* ignore origins */
	  }
	}
      } while (FALSE);
      /* dstQuaProto is not a prefix of srcProto */
      BetaError(QuaErr, this);
    }
  }
}
