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

  Protect(origin, item = (Item *) AOAcalloc(ItemSize(proto)));

  /* The new Item is now allocated, but not initialized yet! */
  
  setup_item(item, proto, origin); 

#ifndef COM
    item->Proto = (ProtoType *)((long)(item->Proto)+DISP_OFF);
#endif /* COM */

  if (proto->GenPart){
    Protect(item, CallGPart(proto->GenPart, item, SP));
  }
  Ck(item);

  return item;
}

