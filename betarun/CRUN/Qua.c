/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Oerbaek, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

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
  ref(Object) src;
  /* the source can be found in theCell since the assignment *has* been done */
  ref(ProtoType) srcProto;
  GCable_Entry();
  FetchParamProtoCellOriginThis();

  DEBUG_CODE(NumQua++);

  src = *theCell;

#ifdef RTDEBUG
  if ((src) && !(inIOA(src) || inAOA(src) || inLVRA(src) || isLazyRef(src))) {
    char buf[100];
    sprintf (buf, "Qua: src check failed. src = %d, theCell = %d\n", 
	     (int) src, (int) theCell);
    Notify(buf);
  }
#endif    
  
  if (src){
    /* If src is NONE, all is well */
    
#ifdef RTLAZY
    srcProto = 0;
    /* 1. Check reference assignment */
    if (isLazyRef(src)) {
      /* Qua check on lazy reference */
      if (! inIOA(theCell)) 
	/* in AOA area. */
	negAOArefsINSERT((long)theCell);
      srcProto = cast(ProtoType) findDanglingProto((int)src);
    } else 
#endif
      if (! inIOA(theCell) && inIOA(src))
	AOAtoIOAInsert(theCell);

    Ck(src);

    /* 2. Qua Check */
#ifdef RTLAZY
    if (srcProto == 0) {
      /* src was not a dangler so its prototype has not been looked up yet. */
#endif
      switch(SwitchProto(src->Proto)){
      case SwitchProto(StructurePTValue):
	/* It was a pattern variable assignment: src is a struc-object */
	srcProto  = (cast(Structure)src)->iProto;
	break;
      case SwitchProto(ComponentPTValue):
	/* It was a component-reference assignment: src points to a component */
	src       = cast(Object)(cast(Component)src)->Body;
	srcProto  = src->Proto;
	break;
      default:
	/* It was a normal reference assignment: src is normal object */
	  srcProto  = src->Proto;
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
	ref(ProtoType) proto1 = srcProto;
	
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
