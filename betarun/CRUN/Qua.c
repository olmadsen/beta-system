/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: Qua.c,v 1.3 1992-11-09 15:05:51 poe Exp $
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
asmlabel(Qua,
	 "mov %i1,%o1;"
	 "mov %i2,%o2;"
	 "mov %o0,%o3;"
	 "b _CQua;"
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
    if (src->Proto == StructurePTValue){
      /* It was a pattern variable assignment: src is a struc-object */
      srcProto  = (cast(Structure)src)->iProto;
      srcOrigin = (cast(Structure)src)->iOrigin;
    } else {
      /* It was a normal reference assignment: src is normal object */
      srcProto  = src->Proto;
      srcOrigin = cast(Object)((long *)src)[srcProto->OriginOff];
    }
    
    /* Check for EqS */
    if (srcProto == dstQuaProto && srcOrigin == dstQuaOrigin ){
      /* Structures are identical. All is OK */
    } else {
      int less=FALSE;
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
	      Protect(dstQuaOrigin, src = cast(Object) CAlloSI(src));
	    }
	    less = (cast(Object)((long*)src)[dstQuaProto->OriginOff] == dstQuaOrigin);
	    break;
	  }
	}
      } while (FALSE);
      if (!less) 
	BetaError(QuaErr, this);
    }
  }
}
