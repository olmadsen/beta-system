/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"
extern void doGC(long *SP, Object *this, unsigned long NumLongs);

Item *AlloCOM(Object *origin, ProtoType *proto, long *SP)
{
  Item *item;

  DEBUG_CODE(NumAlloCOM++);
  Ck(origin);
  DEBUG_CODE(Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

#ifndef COM
  fprintf(output, "\n\n***WARNING: Using AlloCOM with COM symbol undefined. GC may fail!\n\n");
#endif

  push(origin);
  item = (Item *) AOAcalloc(ItemSize(proto));
  pop(origin);

  /* The new Item is now allocated, but not initialized yet! */
  
  setup_item(item, proto, origin); 

#ifndef COM
    item->Proto = (ProtoType *)((long)(item->Proto)+DISP_OFF);
#endif /* COM */

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

Item *AlloH(ProtoType *proto, long *SP)
{
  Item *item=0;
  unsigned long size;

  size= ItemSize(proto);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloH allocates in AOA\n"));
    item = (Item *) AOAcalloc(size, SP);
    DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
  }
  if (!item){
    item = (Item *) IOAalloc(size, SP);
  }
  
  /* The new Object is now allocated, but not initialized yet! */
  
  setup_item(item, proto, 0);
  
  Ck(item);
  
  return item;
}


