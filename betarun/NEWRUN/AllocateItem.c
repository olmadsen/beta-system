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
  unsigned long size;

  DEBUG_CODE(int num = ++NumAlloI);
  DEBUG_ALLOI(fprintf(output,
		      "AlloI#%d: origin=0x%x (%s), proto=0x%x (%s)\n",
		      num,
		      (int)origin, 
		      ProtoTypeName(origin->Proto), 
		      (int)proto, 
		      ProtoTypeName(proto)));

  Ck(origin);
  DEBUG_CODE(Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

  push(origin);
  size = ItemSize(proto);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloI allocates in AOA\n"));
    item = (struct Item *)AOAcalloc(size, SP);
    DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
  }
  if (!item) {
    /* Inlined IOAcalloc */
    DEBUG_CODE(Claim(size>0, "AlloI: size>0"));
    DEBUG_CODE(Claim( ((long)size&7)==0 , "AlloI: (size&7)==0"));
    DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "AlloI: (IOATop&7)==0"));
    while ((char *) IOATop+size > (char *)IOALimit) {
      doGC(SP, GetThis(SP), size / 4);
    }
    item = (struct Item *)IOATop;
    IOATopOff += size;
    long_clear(item->Body, size-headsize(Item));
    DEBUG_CODE(zero_check(item->Body, size-headsize(Item)));
  }
  pop(origin);

  /* The new Item is now allocated, but not initialized yet! */
  
  setup_item(item, proto, origin); 
  if (proto->GenPart){
    Protect(item, CallGPart(proto->GenPart, item, SP));
  }
  Ck(item);

  DEBUG_ALLOI(fprintf(output, "AlloI#%d: item=0x%x\n", num, (int)item));

  return item;
}


/* AlloH:
 * Like AlloI, but does not have an origin, and does not 
 * call G-entry ("AllocateHeap") 
 */

struct Item *AlloH(struct ProtoType *proto, long *SP)
{
  struct Item *item=0;
  unsigned long size;

  size= ItemSize(proto);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloH allocates in AOA\n"));
    item = (struct Item *) AOAcalloc(size, SP);
    DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
  }
  if (!item){
    item = (struct Item *) IOAcalloc(size, SP);
  }
  
  /* The new Object is now allocated, but not initialized yet! */
  
  setup_item(item, proto, 0);
  
  Ck(item);
  
  return item;
}


