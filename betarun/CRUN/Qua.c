/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Oerbaek, Tommy Thorn, and Jacob Seligmann
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

#ifdef sparc
asmlabel(Qua,
	 "mov %i1,%o2;" /* dstQuaProto */
	 "ba "CPREF"Qua;"
	 "mov %i0,%o3;" /* This */
	 );
void CQua(ref(Object) dstQuaOrigin,
	  struct Object **theCell,
	  ref(ProtoType) dstQuaProto,
	  ref(Object) this)
#else
void Qua(ref(ProtoType) dstQuaProto,
	 struct Object **theCell,
	 ref(Object) dstQuaOrigin,
	 ref(Object) this)
#endif
{
  ref(Object) src;
    /* the source can be found in theCell since the assignment *has* been done. */
  ref(ProtoType) srcProto;
  GCable_Entry();

#ifdef hppa
  this = cast(Object)getThisReg();
  dstQuaProto = cast(ProtoType)getCallReg();
  /*dstQuaOrigin = cast(Object)getOriginReg();*/
#endif

  src = *theCell;

  /* Ck(src); */
#ifdef RTDEBUG
  if ((src) && !(inIOA(src) || inAOA(src) || inLVRA(src) || isLazyRef(src))) {
    char buf[100];
    sprintf (stderr, "Qua: src check failed. src = %d, theCell = %d\n", 
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

    /* 2. Qua Check */
#ifdef RTLAZY
    if (srcProto == 0) {
      /* src was not a dangler so its prototype has not been looked up yet. */
#endif
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


/* Strict qua-check, also checking origins */

#if 0 /* OQua not up-to-date */
#ifdef sparc
asmlabel(OQua,
	 "mov %i1,%o2;" /* dstQuaProto */
	 "ba "CPREF"OQua;"
	 "mov %i0,%o3;" /* This */
	 );
void COQua(ref(Object) dstQuaOrigin,
	   struct Object **theCell,
	   ref(ProtoType) dstQuaProto,
	   ref(Object) this)
#else
void OQua(struct Object **theCell,
	  ref(Object) this, 
	  ref(ProtoType) dstQuaProto,
	  ref(Object) dstQuaOrigin)
#endif
{
  ref(Object) src;
    /* the source can be found in theCell since the assignment *has* been done. */
  ref(ProtoType) srcProto;
  ref(Object)    srcOrigin;
  GCable_Entry();

#ifdef hppa
  this = cast(Object)getThisReg();
  dstQuaProto = cast(ProtoType)getCallReg();
  dstQuaOrigin = cast(Object)getOriginReg();
#endif

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
      else if (isLazyRef(src)) {
	negAOArefsINSERT((long)theCell);
	fprintf (stderr, "Aaarghh: Strict QUA check on lazy reference -- Goodbye cruel world\n");
	exit (99);
      }
#endif
    
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
    
    /* Check for eqS */
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
	      Protect(dstQuaOrigin, src = cast(Object) CAlloSI(cast(Structure)src, 0, 0, 0, 0));
#endif
#ifdef hppa
	      Protect(dstQuaOrigin, src = cast(Object) CAlloSI(cast(Structure)src));
#endif
#ifdef crts
	      Protect(dstQuaOrigin, src = cast(Object) AlloSI(cast(Structure)src));
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
#endif /* 0 */
