/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: Qua.c,v 1.6 1993-02-16 14:59:38 datpete Exp $
 * by Peter Andersen, Peter Oerbaek, and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* Qua check.
 * The reference assignment src[]->dst[] has just been made. dst resides in theCell.
 * Perform.
 *   1. CheckReferenceAssigment
 *   2. Qua Check: Check if the actual qualification of src is less than or equal than
 *                 qualification of dst, as given by dstQuaProto and dstQuaOrigin.
 */

/* Sloppy qua-check, only prototypes are considered */

asmlabel(Qua,
	 "mov %i1,%o1;"
	 "mov %i2,%o2;"
	 "mov %o0,%o3;"
	 "ba _CQua;"
	 "mov %i0,%o0;");

#ifdef hppa
void Qua(struct Object **theCell,
	 ref(Object) this, 
	 ref(ProtoType) dstQuaProto,
	 ref(Object) dstQuaOrigin)
#else
void CQua(ref(Object) this, 
	  ref(ProtoType) dstQuaProto,
	  ref(Object) dstQuaOrigin, 
	  struct Object **theCell)
#endif
{
  ref(Object) src;
    /* the source can be found in theCell since the assignment *has* been done. */
  ref(ProtoType) srcProto;
  GCable_Entry();

#ifdef hppa
  this = getThisReg();
  dstQuaProto = getCallReg();
  dstQuaOrigin = getOriginReg();
#endif

  src = *theCell;

  Ck(src);
  
  if (src){
    /* If src is NONE, all is well */
    
    /* 1. Check reference assignment */
    if (! inIOA(theCell) && inIOA(src)) 
      AOAtoIOAInsert(theCell);
    
    /* 2. Qua Check */
    switch((long) src->Proto){
    case (long) StructurePTValue:
      /* It was a pattern variable assignment: src is a struc-object */
      srcProto  = (cast(Structure)src)->iProto;
      break;
    case (long) ComponentPTValue:
      /* It was a component-reference assignment: src points to a component */
      src       = cast(Object)(cast(Component)src)->Body;
      srcProto  = src->Proto;
      break;
    default:
      /* It was a normal reference assignment: src is normal object */
      srcProto  = src->Proto;
      break;
    }
    
    /* Check for EqS */
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


/* Strict qua-check, also checking origins */

asmlabel(OQua,
	 "mov %i1,%o1;"
	 "mov %i2,%o2;"
	 "mov %o0,%o3;"
	 "ba _COQua;"
	 "mov %i0,%o0;");

#ifdef hppa
void OQua(struct Object **theCell,
	 ref(Object) this, 
	 ref(ProtoType) dstQuaProto,
	 ref(Object) dstQuaOrigin)
#else
void COQua(ref(Object) this, 
	  ref(ProtoType) dstQuaProto,
	  ref(Object) dstQuaOrigin, 
	  struct Object **theCell)
#endif
{
  ref(Object) src;
    /* the source can be found in theCell since the assignment *has* been done. */
  ref(ProtoType) srcProto;
  ref(Object)    srcOrigin;
  GCable_Entry();

#ifdef hppa
  this = getThisReg();
  dstQuaProto = getCallReg();
  dstQuaOrigin = getOriginReg();
#endif

  src = *theCell;

  Ck(src);
  Ck(dstQuaOrigin);
  
  if (src){
    /* If src is NONE, all is well */
    
    /* 1. Check reference assignment */
    if (! inIOA(theCell) && inIOA(src)) 
      AOAtoIOAInsert(theCell);
    
    /* 2. Qua Check */
    switch((long) src->Proto){
    case (long) StructurePTValue:
      /* It was a pattern variable assignment: src is a struc-object */
      srcProto  = (cast(Structure)src)->iProto;
      srcOrigin = (cast(Structure)src)->iOrigin;
      break;
    case (long) ComponentPTValue:
      /* It was a component-reference assignment: src points to a component */
      src       = cast(Object)(cast(Component)src)->Body;
      srcProto  = src->Proto;
      srcOrigin = cast(Object)((long *)src)[srcProto->OriginOff];
      break;
    default:
      /* It was a normal reference assignment: src is normal object */
      srcProto  = src->Proto;
      srcOrigin = cast(Object)((long *)src)[srcProto->OriginOff];
      break;
    }
    
    /* Check for EqS */
    if (srcProto == dstQuaProto && srcOrigin == dstQuaOrigin ){
      /* Structures are identical. All is OK */
    } else {
      long less=FALSE;
      long isPrefix=FALSE;
      do {
	/* Inlined version of ltS without struc objects */
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
	    /* Now there is some hope, now we need to check if origins are equal. */
	    isPrefix=TRUE;
	    
	    if (dstQuaProto->OriginOff == srcProto->OriginOff){
	      /* The original prototypes have same origin offset (same prefix level), 
		 so the result is (srcOrigin == dstQuaOrigin) */
	      less = (srcOrigin==dstQuaOrigin);
	      break;
	    }
	    
	    /* Src may have several origins (one per prefixlevel).
	     * We find the origin at the offset determined *by the prefix* (dstQuaProto). 
	     * This should be the same as the origin of the qualification of dst. 
	     */
	    if (src->Proto == StructurePTValue){
#ifdef sparc
	      Protect(dstQuaOrigin, src = cast(Object) CAlloSI(src, 0, 0, 0, 0));
#else
	      Protect(dstQuaOrigin, src = cast(Object) CAlloSI(src));
#endif
	    }
	    less = (cast(Object)((long*)src)[dstQuaProto->OriginOff] == dstQuaOrigin);
	    break;
	  }
	}
      } while (FALSE);
      if (!less) 
	if (isPrefix)
	  BetaError(QuaOrigErr, this);
	else
	  BetaError(QuaErr, this);
    }
  }
}
