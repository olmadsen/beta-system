/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Structure.c,v $, rel: %R%, date: $Date: 1992-07-21 17:16:16 $, SID: $Revision: 1.8 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(Structure) AlloS(ref(ProtoType) proto, ref(Object) origin)
{
    register ref(Structure) newStruct;

    /* Allocate a StructObject. */

    newStruct = cast(Structure) IOAalloc(headsize(Structure));
    newStruct->Proto = StructurePTValue;
    newStruct->GCAttr = 1;
    newStruct->iOrigin = origin;
    newStruct->iProto = proto;
    return newStruct;
}

extern ref(Structure)	ThisStruc() asm("ThisStruc"); /* temporary alias */
ref(Structure) ThisStruc(ref(Object) this)
{
  return ThisS(this);
}

ref(Structure) ThisS(ref(Object) this)
{
    /* Allocate a structObject for thisObject. */

    register ref(Structure) newStruct;
    register ref(Object) origin;

    /* Allocate a StructObject. */

    newStruct = cast(Structure) IOAalloc(headsize(Structure));
    newStruct->Proto = StructurePTValue;
    newStruct->GCAttr = 1;

    origin = (casthandle(Object)this)[this->Proto->OriginOff];
    /* origin is the object we really want orgin and proto of */

    newStruct->iProto = origin->Proto;
    newStruct->iOrigin = (casthandle(Object)origin)[origin->Proto->OriginOff];

    /* MP */
    asm volatile ("restore %0, %%g0, %%l0;retl;nop"::"r" (newStruct));
    return newStruct;
}

ref(Item) AlloSI(ref(Structure) theStruct)
{
  return AlloI(theStruct->iProto, cast(Object) theStruct->iOrigin);
}

ref(Component) AlloSC(ref(Structure) theStruct)
{
  return AlloC(theStruct->iProto, cast(Object) theStruct->iOrigin);
}

int EqS(ref(Structure) arg1, ref(Structure) arg2)
{
    if (!arg1) {
	if (!arg2)
	  return 1;
	return 0;
    }
    if (!arg2)
      return 0;
    if (arg1->iProto != arg2->iProto)
      return 0;
    if (arg1->iOrigin != arg2->iOrigin)
      return 0;
    return 1;
}

int NeS(ref(Structure) arg1, ref(Structure) arg2)
{
    return !EqS(arg1, arg2);
}

int LtS(ref(Structure) arg1, ref(Structure) arg2)
{
  return GtS(arg2, arg1);
}


int LeS(ref(Structure) arg1, ref(Structure) arg2)
{ 
  return (EqS(arg1, arg2) || LtS(arg1, arg2));
}


int GeS(ref(Structure) arg1, ref(Structure) arg2)
{ 
  return (EqS(arg1, arg2) || GtS(arg1, arg2));
}

int GtS(ref(Structure) arg1, ref(Structure) arg2)
{
  ref(ProtoType) proto1;
  ref(ProtoType) proto2;
  ref(Item)      newObject;

  if (!arg1) return 0;
  if (!arg2) return 0;

  proto1 = arg1->iProto;
  proto2 = arg2->iProto;
  
  if (proto1 == proto2) return 0;
  
  /* Prefix of proto2 is the first try */

  
  for (proto2 = proto2->Prefix;
       proto2 != proto2->Prefix;
       proto2 = proto2->Prefix) /* proto2 != Object## */
    if (proto1 == proto2) {
      
      /* Now there is some hope, now we need to check if origins are equal. */
      
      if (proto1->OriginOff == proto2->OriginOff)
	
	/* The prototypes have same origin offset, so
	   the result is (arg1->iOrigin == arg2->iOrigin) */
	
	return arg1->iOrigin == arg2->iOrigin;

      /* If proto1 and proto2 has different Origin Prefix
	 we need to generate an object from arg2 and then
	 test the resulting origin from the new object.

	 We need to generate a new item, as this is currently the only
	 way we can get the origin. */
      
      newObject = AlloSI(arg2);
      return cast(Object)((long*)newObject)[proto2->OriginOff]==arg1->iOrigin;
    }
  return 0; 
}

