/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"
extern void doGC(long *SP, Object *this, unsigned long NumLongs);

static void infoalloi(Object *origin, ProtoType *proto, long *SP)
{
  DEBUG_CODE({
    fprintf(output, "AlloI#%d: origin=0x%x", NumAlloI, (int)origin);
    fflush(output);
    fprintf(output, " (%s), proto=0x%x", ProtoTypeName(GETPROTO(origin)), (int)proto);
    fflush(output);
    fprintf(output, " (%s)\n", ProtoTypeName(proto));
    fflush(output);
  });
}
    

Item *AlloI(Object *origin, ProtoType *proto, long *SP)
{
  Item *item=0;
  unsigned long size;

  DEBUG_CODE(NumAlloI++);
  DEBUG_ALLOI(infoalloi(origin,proto,SP));

  Ck(origin);
  DEBUG_CODE(Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

  push(origin);
  size = ItemSize(proto);
  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloI allocates in AOA\n"));
      item = (Item *)AOAcalloc(size);
      DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!item) {
      DEBUG_CODE(Claim(size>0, "AlloI: size>0"));
      DEBUG_CODE(Claim( ((long)size&7)==0 , "AlloI: (size&7)==0"));
      DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "AlloI: (IOATop&7)==0"));
      if (do_unconditional_gc && (DoUGC) && ActiveComponent /* don't do this before AttBC */){
	doGC(SP, GetThis(SP), size / 4);
      }
      if ((char *) IOATop+size > (char *)IOALimit) {
	doGC(SP, GetThis(SP), size / 4);
      }
      if ((char *) IOATop+size <= (char *)IOALimit) {
	item = (Item *)IOATop;
	IOATopOff += size;
      }
    }
  } while (!item);

  pop(origin);
  DEBUG_CODE(zero_check((char*)item->Body, size-headsize(Item)));

  /* The new Item is now allocated, but not initialized yet! */
  
  setup_item(item, proto, origin); 
  if (proto->GenPart){
    Protect(item, CallGPart(proto->GenPart, item, SP));
  }
  Ck(item);

  DEBUG_ALLOI(fprintf(output, "AlloI#%d: item=0x%x\n", NumAlloI, (int)item));

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
  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloH allocates in AOA\n"));
      item = (Item *) AOAcalloc(size);
      DEBUG_AOA(if (!item) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!item){
      item = (Item *) IOATryAlloc(size, SP);
    }
  } while (!item);

  /* The new Object is now allocated, but not initialized yet! */
  
  setup_item(item, proto, 0);
  
  Ck(item);
  
  return item;
}


