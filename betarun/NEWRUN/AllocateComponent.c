/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct Component *AlloC(struct Object *origin, struct ProtoType *proto, long *SP)
{
  struct Component *comp;

  DEBUG_CODE(NumAlloC++);

  Ck(origin);
  
  DEBUG_CODE( Claim(proto->Size > 0, "AlloC: proto->Size > 0") );
  
  Protect(origin, 
	  comp = (struct Component *)IOAcalloc(ComponentSize(proto), SP));

  /* The new Component is now allocated, but not initialized yet! */
  
  /* Initialize the structual part; prototype, age etc. */
  comp->Proto = ComponentPTValue;
  comp->GCAttr = 1;
  comp->StackObj = (struct StackObject *)0;
  comp->CallerObj = (struct Object *)0;
  comp->CallerComp = (struct Component *)0;
  comp->CallerLSC = 0;
  
  setup_item((struct Item *)&comp->Body, proto, origin);
  
  ((struct Item *)&comp->Body)->GCAttr = -((headsize(Component))/4);
  
  if (proto->GenPart){
    Protect(comp, CallGPart((long)proto->GenPart, &comp->Body, SP));
  }
  Ck(comp);
  
  return comp;
}


