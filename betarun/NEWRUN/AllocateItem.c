/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct Item *AlloI(struct Object *origin, struct ProtoType *proto, long *SP)
{
  struct Item *item=0;
  unsigned long size = ItemSize(proto);

  Ck(origin);
  DEBUG_CODE(NumAlloI++;
	     Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloI allocates in AOA\n"));
    item = (struct Item *)AOAcalloc(size);
    DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
  }
  if (!item) {
    Protect(origin, item = (struct Item *) IOAcalloc(size, SP));
  }

  /* The new Object is now allocated, but not initialized yet! */
  
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


