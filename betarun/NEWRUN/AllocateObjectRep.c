/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen.
 */

#include "beta.h"
#include "crun.h"


void AlloVRI(struct Object *origin,
	     struct ProtoType *proto,
	     unsigned offset /* in bytes */, 
	     int range, 
	     struct Object* theObj, 
	     long *SP)
{
  /* AllocateObjectRepetitionReference: 
   * Allocate repetition of offline items
   */
  struct ObjectRep *theRep=0;
  struct Item *item;
  unsigned long size;

  DEBUG_CODE(NumAlloVRI++);
  Ck(theObj); Ck(origin);
  
  /* Allocate the object repetition. Here we need to use the functions,
   * that return the cleared object, since a GC may occur before all
   * the element references are allocated.
   */
  size = DynObjectRepSize(range);
  push(theObj);
  push(origin); 
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloVRI allocates in AOA\n"));
    theRep = (struct ObjectRep *)AOAcalloc(size, SP);
    DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
  } 
  if (!theRep) {
    theRep = (struct ObjectRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  }
  pop(origin);
  pop(theObj);

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

  Ck(theObj); Ck(origin); Ck(theRep);

}

void AlloVRC(struct Object *origin,
	     struct ProtoType *proto,
	     unsigned offset /* in bytes */, 
	     int range, 
	     struct Object* theObj, 
	     long *SP)
{
  /* AllocateObjectRepetitionComponent: 
   * Allocate repetition of offline components
   */
  struct ObjectRep *theRep=0;
  struct Component *comp;
  unsigned long size;

  DEBUG_CODE(NumAlloVRC++);
  Ck(theObj); Ck(origin);

  /* Allocate the object repetition. Here we need to use the functions,
   * that return the cleared object, since a GC may occur before all
   * the element references are allocated.
   */
  size = DynObjectRepSize(range);
  push(theObj);
  push(origin); 
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloVRC allocates in AOA\n"));
    theRep = (struct ObjectRep *)AOAcalloc(size, SP);
    DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
  } 
  if (!theRep){
    theRep = (struct ObjectRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  }
  pop(origin);
  pop(theObj);

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

  Ck(theObj); Ck(origin); Ck(theRep);
}
