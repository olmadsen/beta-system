/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Oerbaek, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef PERSIST
#include "PException.h"
#include "unswizzle.h"
#endif /* PERSIST */

/* Qua check.
 * The reference assignment src[]->dst[] has just been made. 
 * dst resides in theCell.
 * Perform.
 *   1. CheckReferenceAssigment
 *   2. Qua Check: Check if the actual qualification of src is less than or 
 *                 equal than qualification of dst, as given by dstQuaProto 
 *                 and dstQuaOrigin.
 */

/* Sloppy qua-check, only prototypes are considered.
 * Called from stub Qua in betaenv.o.
 */

void CQua(Object *dstQuaOrigin,
	  ProtoType *dstQuaProto,
	  Object **theCell,
	  long *SP
	  )
{
  Object *src;
  /* the source can be found in theCell since the assignment *has* been done */
  ProtoType *srcProto;

  DEBUG_CODE(NumQua++);

  /* fprintf(output, "\nQua called with dstQuaProto=0x%x, theCell=0x%x, dstQuaOrigin=0x%x\n",
   * 	  dstQuaProto, theCell, dstQuaOrigin); 
   * fflush(output);
   */

  src = *theCell;

#ifdef PERSIST
  /* If src is to an unloaded persistent object, we load the object */
  if (inPIT((void *)src)) {
    *theCell = src = unswizzleReference((void *)src);
  }
#endif /* PERSIST */

#ifdef RTDEBUG
  if ((src) && !(inIOA(src) || inAOA(src))) {
    char buf[512];
    sprintf (buf, "Qua: *theCell not in heap: *theCell=0x%x, theCell=0x%x\n", 
	     (int) src, (int) theCell);
    fprintf(output, "%s", buf); fflush(output); return;
    /* Notify(buf); */
  }
#endif /* RTDEBUG */
  
  if (src) {
    /* If src is NONE, all is well */
    
    /* 1. Check reference assignment */
    if (! inIOA(theCell) && inIOA(src))
      AOAtoIOAInsert(theCell);
    
    Ck(src);

    /* 2. Qua Check */
    switch(SwitchProto(GETPROTO(src))){
    case SwitchProto(StructurePTValue):
      /* It was a pattern variable assignment: src is a struc-object */
      srcProto  = ((Structure *)src)->iProto;
      break;
    case SwitchProto(ComponentPTValue):
      /* It was a componentreference assignment: src points to a component */
      src       = (Object *)((Component *)src)->Body;
      srcProto  = GETPROTO(src);
      break;
    default:
      /* It was a normal reference assignment: src is normal object */
      srcProto  = GETPROTO(src);
      break;
    }
    
    /* Check for eqS */
    if (srcProto == dstQuaProto){
      /* Structures are identical. All is OK */
    } else {
      do {
	/* Inlined version of ltS without struc objects,
	 * and not checking origins 
	 */
	ProtoType *proto1 = srcProto;
	
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
      /* dstQuaProto is not a prefix of srcProto - call BetaError.*/
      QuaSrc = src;
      QuaDstOrigin = dstQuaOrigin;
      QuaDstProto = dstQuaProto;
      BetaError(QuaErr, 0, SP, 0); /* this and PC is found in BetaError */
    }
  }

  Ck(src);

}

