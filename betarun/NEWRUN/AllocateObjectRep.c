/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen.
 */

#include "beta.h"
#include "crun.h"


void AlloORR(struct Object *origin,
	     struct ProtoType *proto,
	     struct Object *theObj,
	     unsigned offset /* in bytes */,
	     int range,
	     long *SP
	     )
{
  /* AllocateObjectRepetitionReference: 
   * Allocate repetition of offline items
   */
  struct ObjectRep *theRep=0;
  struct Item *item;
  unsigned long size;

  DEBUG_CODE(NumAlloORR++);
  Ck(theObj); Ck(origin);
  
  /* Allocate the object repetition. Here we need to use the functions,
   * that return the cleared object, since a GC may occur before all
   * the element references are allocated.
   */
  size = DynObjectRepSize(range);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloORR allocates in AOA\n"));
    theRep = (struct ObjectRep *)AOAcalloc(size);
    DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
  } 
  if (!theRep) {
    Protect2(theObj, origin, theRep = (struct ObjectRep *)IOAcalloc(size, SP));
    theRep->GCAttr = 1;
  }

  Ck(theObj); Ck(origin); Ck(theRep);

  /* Set up the header */
  theRep->Proto = DynItemRepPTValue;
  /* theRep->GCAttr set above if in IOA */
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  AssignReference(&theRep->iOrigin, origin);

  /* Assign the repetition into theObj */
  AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

  /* Allocate items and assign them into the repetition */
  while(--range>=0){
    Protect(theRep, item = AlloI(theRep->iOrigin, proto, SP));
    AssignReference((long *)((long)&theRep->Body[0]+range*4), item);
  }
}

void AlloORRC(struct Object *origin,
	      struct ProtoType *proto,
	      struct Object *theObj,
	      unsigned offset /* in bytes */,
	      int range,
	      long *SP
	      )
{
  /* AllocateObjectRepetitionComponent: 
   * Allocate repetition of offline components
   */
  struct ObjectRep *theRep=0;
  struct Component *comp;
  unsigned long size;

  DEBUG_CODE(NumAlloORRC++);

  /* Allocate the object repetition. Here we need to use the functions,
   * that return the cleared object, since a GC may occur before all
   * the element references are allocated.
   */
  size = DynObjectRepSize(range);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloORRC allocates in AOA\n"));
    theRep = (struct ObjectRep *)AOAcalloc(size);
    DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
  } 
  if (!theRep){
    Protect2(theObj, origin, theRep = (struct ObjectRep *)IOAcalloc(size, SP));
    theRep->GCAttr = 1;
  }

  Ck(theObj); Ck(origin); Ck(theRep);

  /* Set up the header */
  theRep->Proto = DynCompRepPTValue;
  /* theRep->GCAttr set above if in IOA */
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  AssignReference(&theRep->iOrigin, origin);

  /* Assign the repetition into theObj */
  AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

  /* Allocate components and assign them into the repetition */
  while(--range>=0){
    Protect(theRep, comp = AlloC(theRep->iOrigin, proto, SP));
    AssignReference((long *)((long)&theRep->Body + range*4), 
		    (struct Item *)comp);
  }
}
