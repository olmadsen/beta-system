/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct Structure *AlloS(struct Object *origin, struct ProtoType *proto, long *SP)
{
  register struct Structure *newStruct;

  DEBUG_CODE(NumAlloS++);

  /* Allocate a StructObject. */
    
  /* No need to check for IOAMAXSIZE */
  Ck(origin);
  Protect(origin, newStruct = (struct Structure *)IOAalloc(StructureSize, SP));
  Ck(origin);
  
  newStruct->Proto = StructurePTValue;
  newStruct->GCAttr = 1;
  AssignReference(&newStruct->iOrigin, origin);
  newStruct->iProto = proto;

  Ck(newStruct);
  return newStruct;
}

struct Item *AlloSI(long dummy, struct Structure *struc, long *SP)
{
  struct Item *ss;
  DEBUG_CODE(NumAlloSI++);

  Ck(struc);
  Ck(struc->iOrigin);
  ss = AlloI((struct Object *)struc->iOrigin, struc->iProto, SP);
  Ck(ss);
  return ss;
}

struct Component *AlloSC(struct Structure *struc, long *SP)
{
  struct Component *ss;
  DEBUG_CODE(NumAlloSC++);

  Ck(struc);
  Ck(struc->iOrigin);
  ss = AlloC((struct Object *)struc->iOrigin, struc->iProto, SP);
  Ck(ss);
  return ss;
}    


struct Structure *ThisS(struct Object *this, long *SP)
{
  /* Allocate a structObject for thisObject. 
   * Used in this way:
   *
   * object: (# struc: (# ... do ... TOS'ThisS' ... #) do ... #)
   * R: ^T
   * R.struc
   *
   * Since ThisS is called from within the struc pattern, we must use
   * the origin in the generated struc object.
   */
  
  register struct Structure *newStruct;
  register struct Object *origin;
  
  DEBUG_CODE(NumThisS++);

  /* Allocate a StructObject. */
  
  /* No need to check for IOAMAXSIZE */
  Ck(this);
  Protect(this, newStruct = (struct Structure *)IOAalloc(StructureSize, SP));
  Ck(this);
  
  newStruct->Proto = StructurePTValue;
  newStruct->GCAttr = 1;
  
  origin = ((struct Object **)this)[this->Proto->OriginOff];
  /* origin is the object we really want orgin and proto of */
  
  newStruct->iProto = origin->Proto;
  AssignReference(&newStruct->iOrigin, ((struct Object **)origin)[origin->Proto->OriginOff]);
  
  Ck(newStruct);

  return newStruct;
}

struct Structure *ObjS(struct Object *theObj, long *SP)
{
  /* Allocate a structObject for theObj. 
   * Used in this way:
   *
   * R: ^T
   * R##
   *
   * Unlike ThisS the object and not the origin should be used in the 
   * generated struc object.
   */
  
  register struct Structure *newStruct;
  
  DEBUG_CODE(NumObjS++);

  /* Allocate a StructObject. */
  
  /* No need to check for IOAMAXSIZE */
  Ck(theObj);
  Protect(theObj, newStruct = (struct Structure *)IOAalloc(StructureSize, SP));
  Ck(theObj);
  
  newStruct->Proto = StructurePTValue;
  newStruct->GCAttr = 1;
  
  newStruct->iProto = theObj->Proto;
  AssignReference(&newStruct->iOrigin, ((struct Object **)theObj)[theObj->Proto->OriginOff]);

  Ck(newStruct);
  
  return newStruct;
}

long eqS(struct Structure *arg1, struct Structure *arg2)
{
  DEBUG_CODE(NumeqS++);

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

long neS(struct Structure *arg1, struct Structure *arg2)
{
  DEBUG_CODE(NumneS++);
  Ck(arg1); Ck(arg2);
  return !eqS(arg1, arg2);
}

long leS(struct Structure *arg1, struct Structure *arg2, long *SP)
{ 
  DEBUG_CODE(NumleS++);
  Ck(arg1); Ck(arg2);
  return (eqS(arg1, arg2) || ltS(arg1, arg2, SP));
}


long geS(struct Structure *arg1, struct Structure *arg2, long *SP)
{ 
  DEBUG_CODE(NumgeS++);
  Ck(arg1); Ck(arg2);
  return (eqS(arg1, arg2) || gtS(arg1, arg2, SP));
}

long gtS(struct Structure *arg1, struct Structure *arg2, long *SP)
{
  DEBUG_CODE(NumgtS++);
  Ck(arg1); Ck(arg2);
  return ltS(arg2, arg1, SP);
}

long ltS(struct Structure *arg1, struct Structure *arg2, long *SP)
{
  struct ProtoType *proto1;
  struct ProtoType *proto2;
  struct Item * newObject;

  DEBUG_CODE(NumltS++);
  Ck(arg1); Ck(arg2);
  if (!arg1) return 0;
  if (!arg2) return 0;
  
  proto1 = arg1->iProto;
  proto2 = arg2->iProto;
  
  if (proto1 == proto2)
    return 0;

  if (proto2->Prefix == proto2){
    /* proto2 is Object## */
    return 1;
  }
  
  /* Prefix of proto1 is the first try */
  
  for (proto1 = proto1->Prefix;
       proto1 != proto1->Prefix; /* proto1 != Object## */
       proto1 = proto1->Prefix) {
	 if (proto1 == proto2) {
	   /* There is some hope, now we need to check if origins are equal. */
	   
	   if (proto2->OriginOff == arg1->iProto->OriginOff){
	     /* The original prototypes have same origin offset 
	      * i.e. (same prefix level),
	      * so the result is (arg1->iOrigin == arg2->iOrigin) 
	      */
	     return arg1->iOrigin == arg2->iOrigin;
	   }
	   
	   /* If proto1 and proto2 has different Origin Prefix
	    * we need to generate an object from arg1 and then
	    * test the resulting origin from the new object.
	    *   
	    * We need to generate a new item, as this is currently the only
	    * way we can get the origin.
	    * The problem is that there are several origins 
	    * (one per prefixlevel).
	    * So we generate an object corresponding to arg1 and find the 
	    * origin at the offset determined *by the prefix* (proto2). 
	    * This should be the same as origin of arg2.
	    */
	   
	   Protect(arg2, newObject = AlloSI(0,arg1, SP));
	   return (struct Object *)((long*)newObject)[proto2->OriginOff] == (arg2->iOrigin);
	 }
       }

  return 0; 
}

