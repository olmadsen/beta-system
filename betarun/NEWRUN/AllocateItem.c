/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"
extern void doGC(long *SP, struct Object *this, unsigned long NumLongs);

struct Item *AlloI(struct Object *origin, struct ProtoType *proto, long *SP)
{
  struct Item *item=0;
  unsigned long size = ItemSize(proto);

  DEBUG_ALLOI(fprintf(output,
		      "AlloI: origin=0x%x (%s), proto=0x%x (%s)\n",
		      (int)origin, 
		      ProtoTypeName(origin->Proto), 
		      (int)proto, 
		      ProtoTypeName(proto)));

  Ck(origin);
  DEBUG_CODE(NumAlloI++; Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloI allocates in AOA\n"));
    push(origin);
    item = (struct Item *)AOAcalloc(size, SP);
    pop(origin);
    DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
  }
  if (!item) {
    /* Inlined IOAcalloc */
    DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));
    DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAcalloc: (size&7)==0"));
    DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAcalloc: (IOATop&7)==0"));
    
    push(origin);
    while ((char *) IOATop+size > (char *)IOALimit) {
      doGC(SP, GetThis(SP), size / 4);
    }
    pop(origin);
    
    item = (struct Item *)IOATop;
    IOATopOff += size;
    
    long_clear(item->Body, size-headsize(Item));
    DEBUG_CODE(zero_check(item->Body, size-headsize(Item)));
  }

  /* The new Item is now allocated, but not initialized yet! */
  
  setup_item(item, proto, origin); 
  if (proto->GenPart){
    Protect(item, CallGPart(proto->GenPart, item, SP));
  }
  Ck(item);
  return item;
}


/* AlloH:
 * Like AlloI, but does not have an origin, and does not 
 * call G-entry ("AllocateHeap") 
 */

struct Item *AlloH(struct ProtoType *proto, long *SP)
{
  struct Item *item = (struct Item *) IOAcalloc(ItemSize(proto), SP);
  
  /* The new Object is now allocated, but not initialized yet! */
  
  setup_item(item, proto, 0);
  
  Ck(item);
  
  return item;
}


