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

  do {
    Protect(origin, item = (Item *) AOAcalloc(ItemSize(proto)));

    if (item) {
      /* The new Item is now allocated, but not initialized yet! */
    
      setup_item(item, proto, origin); 
      /* setup_item has assigned origin, but assuming item in IOA 
       * Do it again with AssignReference
       */
      AssignReference(((long*)item)+((ProtoType*)proto)->OriginOff, 
		      (Item *)origin);
    
#ifndef COM
      item->Proto = (ProtoType *)((long)(item->Proto)+DISP_OFF);
#endif /* COM */
    
      if (proto->GenPart){
	Protect(item, CallGPart(proto->GenPart, item, SP));
      }
    } else {
      Protect(origin, IOATryAlloc(0x40000000, SP)); /* Dummy alloc to trigger GC */
    }
  } while (!item);

  Ck(item);
  return item;
}

