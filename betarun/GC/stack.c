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
#ifdef NEWRUN
  if ((theObj==CALLBACKMARK)||(theObj==GENMARK)){
    /* OK */
    return;
  } 
#endif
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
	ILLEGAL;
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

#endif /* RTVALHALLA */

/************************* ProcessStack: ***************************/
void ProcessStack(void)
{
    GeneralProcessStack(DoStackCell);
}


/************************* find_activation: ************************/

static ProtoType *activation_proto;
static Object *activation_object;
static Object *activation_start;
static int     activation_start_found;

static void find_foreach(long PC, Object *theObj)
{
  ProtoType *proto;
  if (activation_object) return; /* already found! */

  TRACE_FINDACTIVATION({
    fprintf(output, "find_foreach(theObj=0x%x) ", (int)theObj); 
    PrintRef(theObj);
    fprintf(output, "\n");
    fflush(output);
  });

  if (!theObj) return;

  proto = GETPROTO(theObj);
  if (isSpecialProtoType(proto)) {
    if (proto==DopartObjectPTValue){
      TRACE_FINDACTIVATION({
	fprintf(output, "find_foreach: jumping out of DopartObject\n");
	fprintf(output, "find_foreach(theObj=0x%x) ", (int)theObj); 
      });
      theObj=((DopartObject*)theObj)->Origin;
      proto = GETPROTO(theObj);
    } else {
      /* This cannot be the object sought */
      return;
    }
  }

  if (activation_start){
    if (activation_start == theObj){
      /* Found start object */
      if (activation_start_found){
	TRACE_FINDACTIVATION({
	  fprintf(output, 
		  "find_foreach: found start object 0x%x AGAIN - ignored\n",
		  (int)activation_start);
	});
	return;
      } else {
	TRACE_FINDACTIVATION({
	  fprintf(output, 
		  "find_foreach: found start object 0x%x\n", 
		  (int)activation_start);
	});
	activation_start_found = 1;
	/* Do not consider this object */
	return;
      }
    }
    if (!activation_start_found) return;
  }

  if (proto == activation_proto){
    /* exact qualification found */
    activation_object = theObj;
    return;
  } else {
    /* See if prefix matches */
    if (proto->Prefix == proto){
      /* proto is Object## */
      return;
    }
    for (proto = proto->Prefix;
	 proto != proto->Prefix; /* proto != Object## */
	 proto = proto->Prefix) {
      if (proto == activation_proto) {
	/* proto is a prefix of activation_proto */
	activation_object = theObj;
	return; 
      }
    }
  }
}

/* Usage:
 *  throw:
 *    INCLUDE '~beta/sysutils/objinterface';
 *    (# proto: @integer;
 *       theTry: ^try;
 *     do try## -> getProtoTypeForStruc -> proto;
 *        (proto, @@startTry) -> find_activation -> obj;
 * 	  (if obj<>0 then
 *            obj -> addressToObject -> theTry[];
 *        if);
 *        ...
 *    #)
 */
Object *find_activation(ProtoType *proto, Object *startObj)
{
  Component *comp = ActiveComponent;
  long *oldStackEnd = StackEnd;
  
  TRACE_FINDACTIVATION({
    fprintf(output, 
	    "***find_activation(proto=0x%x, startObj=0x%x)\n", 
	    (int)proto, 
	    (int)startObj); 
    PrintProto(proto);
    fprintf(output, "\n");
    if (startObj){
      PrintRef(startObj);
      fprintf(output, "\n");
    };
  });
#ifdef hppa
  fprintf(output, "find_activation: NYI\n");
  return 0;
#endif
#ifdef NEWRUN
  StackEnd = BetaStackTop[0];
#else /* !NEWRUN */
  StackEnd = BetaStackTop;
#endif /* NEWRUN */
  activation_object = 0;
  activation_proto = proto;
  activation_start = startObj;
  activation_start_found = 0;
  while (!activation_object && comp){
    TRACE_FINDACTIVATION({
      fprintf(output, 
	      "--------------------------\n"
	      "find_activation(0x%x, 0x%x): "
	      "calling scanComponentStack(comp=0x%x)\n", 
	      (int)proto, 
	      (int)startObj,
	      (int)comp); 
    });
    scanComponentStack (comp, 0, 0, find_foreach);
    comp = comp->CallerComp;
  }
  StackEnd = oldStackEnd;
  return activation_object;
}


#endif /* MT */
