/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

Component *AlloC(Object *origin, ProtoType *proto, long *SP)
{
  Component *comp=0;
  unsigned long size;

  DEBUG_CODE(NumAlloC++);

  Ck(origin);
  
  DEBUG_ALLOI(fprintf(output,
		      "AlloC#%d: origin=0x%x (%s), proto=0x%x (%s)\n",
		      (int)NumAlloC,
		      (int)origin, 
		      origin ? ProtoTypeName(GETPROTO(origin)) : 0, 
		      (int)proto, 
		      ProtoTypeName(proto)));

  DEBUG_CODE( Claim(proto->Size > 0, "AlloC: proto->Size > 0") );
  
  push(origin);
  size = ComponentSize(proto);
  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloC allocates in AOA\n"));
      comp = (Component *)AOAcalloc(size);
      DEBUG_AOA(if (!comp) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!comp) {
      comp = (Component *)IOATryAlloc(size, SP);
      if (comp && IOAMinAge!=0) comp->GCAttr = IOAMinAge;
    }
  } while (!comp);
  pop(origin);

  /* The new Component is now allocated, but not initialized yet! */
  
  /* Initialize the structual part; prototype, age etc. */
  SETPROTO(comp, ComponentPTValue);
  /* comp->GCAttr set above if in IOA */
  
  setup_item((Item *)&comp->Body, proto, origin);
  
  ((Item *)&comp->Body)->GCAttr = -((headsize(Component))/4);
  
  if (proto->GenPart){
    Protect(comp, CallGPart((long)proto->GenPart, &comp->Body, SP));
  }
  Ck(comp);
  
  return comp;
}


