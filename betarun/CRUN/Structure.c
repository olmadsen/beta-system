/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: Structure.c,v 1.24 1992-10-23 15:24:32 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(struct Structure *, AlloS)
{
  register ref(Structure) newStruct;
  
  GCable_Entry();
  FetchOriginProto
    
    /* Allocate a StructObject. */
    
    Ck(origin);
  Protect(origin, newStruct = cast(Structure) IOAalloc(StructureSize));
  Ck(origin);
  
  newStruct->Proto = StructurePTValue;
  newStruct->GCAttr = 1;
  newStruct->iOrigin = origin;
  newStruct->iProto = proto;
  
  RETURN(newStruct);
}

ref(Structure) ThisS(ref(Object) this)
{
  /* Allocate a structObject for thisObject. */
  
  register ref(Structure) newStruct;
  register ref(Object) origin;
  
  GCable_Entry();
  
#ifdef hppa
  this = cast(Object) getCallReg();
#endif
  
  /* Allocate a StructObject. */
  
  Ck(this);
  Protect(this, newStruct = cast(Structure) IOAalloc(StructureSize));
  Ck(this);
  
  newStruct->Proto = StructurePTValue;
  newStruct->GCAttr = 1;
  
  origin = (casthandle(Object)this)[this->Proto->OriginOff];
  /* origin is the object we really want orgin and proto of */
  
  newStruct->iProto = origin->Proto;
  newStruct->iOrigin = (casthandle(Object)origin)[origin->Proto->OriginOff];
  
#ifdef sparc
  /* Fixed in compiler */
  /* asm volatile ("restore %0, %%g0, %%l0;retl;nop"::"r" (newStruct)); */
#endif
#ifdef hppa
  /* setD0Reg((int)newStruct); */
#endif
  return newStruct;
}

ParamStruc(struct Item *, AlloSI)
{
  struct Item *ss;
  
  GCable_Entry();
  FetchStruc
    Ck(struc);
  Protect(struc, 
	  ss = CAlloI(cast(Object) struc->iOrigin, struc->iProto));
  RETURN(ss);
}

ParamStruc(struct Component *, AlloSC)
{
  struct Component *ss;
  
  GCable_Entry();
  FetchStruc
    Ck(struc);
  Protect(struc, 
	  ss = CAlloC(cast(Object) struc->iOrigin, struc->iProto));
  RETURN(ss);
}    

int EqS(ref(Structure) arg1, ref(Structure) arg2)
{
  GCable_Entry();
  
  Ck(arg1); Ck(arg2);
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
  GCable_Entry();
  
  Ck(arg1); Ck(arg2);
  return !EqS(arg1, arg2);
}

int LtS(ref(Structure) arg1, ref(Structure) arg2)
{
  GCable_Entry();
  
  Ck(arg1); Ck(arg2);
  return GtS(arg2, arg1);
}


int LeS(ref(Structure) arg1, ref(Structure) arg2)
{ 
  GCable_Entry();
  
  Ck(arg1); Ck(arg2);
  return (EqS(arg1, arg2) || LtS(arg1, arg2));
}


int GeS(ref(Structure) arg1, ref(Structure) arg2)
{ 
  GCable_Entry();
  
  Ck(arg1); Ck(arg2);
  return (EqS(arg1, arg2) || GtS(arg1, arg2));
}

int GtS(ref(Structure) arg1, ref(Structure) arg2)
{
  ref(ProtoType) proto1;
  ref(ProtoType) proto2;
  DeclReference1(struct Item *, newObject);
  
  GCable_Entry();
  
  Ck(arg1); Ck(arg2);
  if (!arg1) return 0;
  if (!arg2) return 0;
  
  proto1 = arg1->iProto;
  proto2 = arg2->iProto;
  
  if (proto1 == proto2)
    return 0;

  if (proto1->Prefix == proto1) /* proto1 is Object## */
    return 1;
  
  /* Prefix of proto2 is the first try */
  
  for (proto2 = proto2->Prefix;
       proto2 != proto2->Prefix; /* proto2 != Object## */
       proto2 = proto2->Prefix) {
	 if (proto1 == proto2) {
	   /* Now there is some hope, now we need to check if origins are equal. */
	   
	   if (proto1->OriginOff == arg2->iProto->OriginOff){
	     /* The prototypes have same origin offset (same prefix level), so
		the result is (arg1->iOrigin == arg2->iOrigin) */
	     return arg1->iOrigin == arg2->iOrigin;
	   }
	   
	   /* If proto1 and proto2 has different Origin Prefix
	    * we need to generate an object from arg2 and then
	    * test the resulting origin from the new object.
	    *   
	    * We need to generate a new item, as this is currently the only
	    * way we can get the origin.
	    * The problem is that there are several origins (one per prefixlevel).
	    * So we generate an object corresponding to arg2 and find the origin
	    * at the offset determined *by the prefix* (proto1). This should be the
	    * same as origin of arg1.
	    */
	   
	   Protect(arg1, newObject = CAlloSI(arg2));
	   return cast(Object)((long*)newObject)[proto1->OriginOff] == (arg1->iOrigin);
	 }
       }
  return 0; 
}
