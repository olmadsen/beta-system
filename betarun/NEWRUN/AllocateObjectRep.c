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
  struct ObjectRep *theRep;
  struct Item *item;
  unsigned long bodyAddr;

  DEBUG_CODE(NumAlloORR++);
  
  /* Allocate the object repetition */
  Ck(theObj); Ck(origin);
  Protect2(theObj, origin,  
	   theRep = (struct ObjectRep *)IOAcalloc(DynObjectRepSize(range), SP));
  Ck(theObj); Ck(origin); Ck(theRep);

  /* Set up the header */
  theRep->Proto = DynItemRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  /* Assign the repetition into theObj */
  AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

  /* Allocate items and assign them into the repetition */
  while(--range>=0){
    Protect(theRep, item = AlloI(theRep->iOrigin, proto, SP));
    bodyAddr = (unsigned long)&theRep->Body[0];
    
  /*  printf("AlloORR: theRep=0x%x\n", theRep);
    printf("AlloORR: bodyAddr=0x%x\n", bodyAddr);
    printf("AlloORR: range=0x%x\n", range);
    printf("AlloORR: range*4=0x%x\n", range*4);
    printf("AlloORR: (bodyAddr+range*4)=0x%x\n", (bodyAddr+range*4));
    */
    AssignReference((long *)(bodyAddr+range*4), item);
  /*  printf("AlloORR: assigned item 0x%x to addr 0x%x\n",
	   item, bodyAddr + range*4);
   */
    
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
  struct ObjectRep *theRep;
  struct Component *comp;

  DEBUG_CODE(NumAlloORRC++);

  /* Allocate the object repetition */
  Ck(theObj); Ck(origin);
  Protect2(theObj, origin,  
	   theRep = (struct ObjectRep *)IOAcalloc(DynObjectRepSize(range), SP));
  Ck(theObj);

  /* Set up the header */
  theRep->Proto = DynCompRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  /* Assign the repetition into theObj */
  AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

  /* Allocate components and assign them into the repetition */
  while(--range>=0){
    Protect(theRep, comp = AlloC(theRep->iOrigin, proto, SP));
    AssignReference((long *)((long)&theRep->Body + range*4), 
		    (struct Item *)comp);
  }
}
