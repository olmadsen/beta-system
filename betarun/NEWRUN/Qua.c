/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Oerbaek, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* Qua check.
 * The reference assignment src[]->dst[] has just been made. 
 * dst resides in theCell.
 * Perform.
 *   1. CheckReferenceAssigment
 *   2. Qua Check: Check if the actual qualification of src is less than or 
 *                 equal than qualification of dst, as given by dstQuaProto 
 *                 and dstQuaOrigin.
 */

/* Sloppy qua-check, only prototypes are considered */

void Qua(struct Object *dstQuaOrigin,
	 struct ProtoType *dstQuaProto,
	 struct Object **theCell,
	 long *SP
	 )
{
  struct Object *src;
  /* the source can be found in theCell since the assignment *has* been done */
  struct ProtoType *srcProto;

  DEBUG_CODE(NumQua++);

  /* fprintf(output, "\nQua called with dstQuaProto=0x%x, theCell=0x%x, dstQuaOrigin=0x%x\n",
   * 	  dstQuaProto, theCell, dstQuaOrigin); 
   * fflush(output);
   */

  src = *theCell;

#ifdef RTDEBUG
  if ((src) && !(inIOA(src) || inAOA(src) || inLVRA(src) || isLazyRef(src))) {
    char buf[100];
    sprintf (buf, "Qua: *theCell not in heap: *theCell=0x%x, theCell=0x%x\n", 
	     (int) src, (int) theCell);
    fprintf(output, "%s", buf); fflush(output); return;
    /* Notify(buf); */
  }
  Ck(src);
#endif    
  
  if (src){
    /* If src is NONE, all is well */
    
    /* 1. Check reference assignment */
#ifdef RTLAZY
    srcProto = 0;
    if (isLazyRef(src)) {
      /* Qua check on lazy reference */
      if (! inIOA(theCell)) 
	/* in AOA area. */
	negAOArefsINSERT((long)theCell);
      srcProto = (struct ProtoType *)findDanglingProto((int)src);
    } else 
#endif
      if (! inIOA(theCell) && inIOA(src))
	AOAtoIOAInsert(theCell);

    /* 2. Qua Check */
#ifdef RTLAZY
    if (srcProto == 0) {
      /* src was not a dangler so its prototype has not been looked up yet. */
#endif
      switch((long) src->Proto){
      case (long) StructurePTValue:
	/* It was a pattern variable assignment: src is a struc-object */
	srcProto  = ((struct Structure *)src)->iProto;
	break;
      case (long) ComponentPTValue:
	/* It was a componentreference assignment: src points to a component */
	src       = (struct Object *)((struct Component *)src)->Body;
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
	/* Inlined version of ltS without struc objects,
	 * and not checking origins 
	 */
	struct ProtoType *proto1 = srcProto;
	
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
      } while (0);
      /* dstQuaProto is not a prefix of srcProto */
      BetaError(QuaErr, GetThis(SP), SP, 0);
    }
  }
}


/* Strict qua-check, also checking origins.
 * FIXME: Does not work anymore!
 */

#ifdef STRICT_QUA
void OQua(struct Object **theCell,
	  struct Object *this, 
	  struct ProtoType *dstQuaProto,
	  struct Object *dstQuaOrigin)
{
  struct Object *src;
  /* the source can be found in theCell since the assignment *has* been done */
  struct ProtoType *srcProto;
  struct Object *   srcOrigin;

  src = *theCell;

  Ck(src);
  Ck(dstQuaOrigin);
  
  if (src){
    /* If src is NONE, all is well */
    
    /* 1. Check reference assignment */
    if (! inIOA(theCell))
      if (inIOA(src))
	AOAtoIOAInsert(theCell);
#ifdef RTLAZY
      else if (isLazystruct src *) {
	negAOArefsINSERT((long)theCell);
	fprintf (output, 
		 "Error: Strict QUA check on lazy reference\n");
	BetaExit (99);
      }
#endif
    
    /* 2. Qua Check */
    switch((long) src->Proto){
    case (long) StructurePTValue:
      /* It was a pattern variable assignment: src is a struc-object */
      srcProto  = ((struct Structure *)src)->iProto;
      srcOrigin = ((struct Structure *)src)->iOrigin;
      break;
    case (long) ComponentPTValue:
      /* It was a component-reference assignment: src points to a component */
      src       = (struct Object *)((struct Component *)src)->Body;
      srcProto  = src->Proto;
      srcOrigin = (struct Object *)((long *)src)[srcProto->OriginOff];
      break;
    default:
      /* It was a normal reference assignment: src is normal object */
      srcProto  = src->Proto;
      srcOrigin = (struct Object *)((long *)src)[srcProto->OriginOff];
      break;
    }
    
    /* Check for eqS */
    if (srcProto == dstQuaProto && srcOrigin == dstQuaOrigin ){
      /* Structures are identical. All is OK */
    } else {
      long less=FALSE;
      long isPrefix=FALSE;
      do {
	/* Inlined version of ltS without struc objects */
	struct ProtoType *proto1 = srcProto;
	
	if (dstQuaProto->Prefix == dstQuaProto){
	  /* dstQuaProto is Object## */
	  return;
	}
	
	/* Prefix of srcProto is the first try */
	
	for (proto1 = proto1->Prefix;
	     proto1 != proto1->Prefix; /* proto1 != Object## */
	     proto1 = proto1->Prefix) {
	  if (proto1 == dstQuaProto) {
	    /* There is some hope, now we need to check if origins are equal */
	    isPrefix=TRUE;
	    
	    if (dstQuaProto->OriginOff == srcProto->OriginOff){
	      /* The original prototypes have same origin offset 
	       * (same prefix level), 
		 so the result is (srcOrigin == dstQuaOrigin) */
	      less = (srcOrigin==dstQuaOrigin);
	      break;
	    }
	    
	    /* Src may have several origins (one per prefixlevel).
	     * We find the origin at the offset determined *by the prefix* 
	     * (dstQuaProto). 
	     * This should be the same as the origin of the qualification 
	     * of dst. 
	     */
	    if (src->Proto == StructurePTValue){
	      Protect(dstQuaOrigin,
		      src = (struct Object *)AlloSI((struct Structure *)src));
	    }
	    less = ((struct Object *)((long*)src)[dstQuaProto->OriginOff] == dstQuaOrigin);
	    break;
	  }
	}
      } while (0);
      if (!less) 
	if (isPrefix)
	  BetaError(QuaOrigErr, GetThis(SP), 0);
	else
	  BetaError(QuaErr, GetThis(SP), 0);
    }
  }
}
#endif 
