/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct Component *AlloC(struct Object *origin, struct ProtoType *proto, long *SP)
{
  struct Component *comp=0;
  unsigned long size;

  DEBUG_CODE(NumAlloC++);

  Ck(origin);
  
  DEBUG_CODE( Claim(proto->Size > 0, "AlloC: proto->Size > 0") );
  
  push(origin);
  size = ComponentSize(proto);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "AlloC allocates in AOA\n"));
    comp = (struct Component *)AOAcalloc(size, SP);
    DEBUG_AOA(if (!comp) fprintf(output, "AOAcalloc failed\n"));
  }
  if (!comp) {
    comp = (struct Component *)IOAalloc(size, SP);
    if (IOAMinAge!=0) comp->GCAttr = IOAMinAge;
  }
  pop(origin);

  /* The new Component is now allocated, but not initialized yet! */
  
  /* Initialize the structual part; prototype, age etc. */
  comp->Proto = ComponentPTValue;
  /* comp->GCAttr set above if in IOA */
  
  setup_item((struct Item *)&comp->Body, proto, origin);
  
  ((struct Item *)&comp->Body)->GCAttr = -((headsize(Component))/4);
  
  if (proto->GenPart){
    Protect(comp, CallGPart((long)proto->GenPart, &comp->Body, SP));
  }
  Ck(comp);
  
  return comp;
}


