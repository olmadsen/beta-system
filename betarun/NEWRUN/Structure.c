/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

Structure *AlloS(Object *origin, ProtoType *proto, long *SP)
{
  register Structure *newStruct;

  DEBUG_CODE(NumAlloS++);

  /* Allocate a StructObject. */
    
  /* No need to check for IOAMAXSIZE */
  Ck(origin);
  Protect(origin, newStruct = (Structure *)IOAalloc(StructureSize, SP));
  
  SETPROTO(newStruct, StructurePTValue);
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  AssignReference(&newStruct->iOrigin, origin);
  newStruct->iProto = proto;

  Ck(origin); Ck(newStruct);
  return newStruct;
}

Structure *VAlloS(ProtoType *proto, long *SP, pc_t PC)
{
  return AlloS(0, proto, SP);
}

Item *AlloSI(long dummy, Structure *struc, long *SP)
{
  Item *ss;
  DEBUG_CODE(NumAlloSI++);

  Ck(struc);
  Ck(struc->iOrigin);
  ss = AlloI((Object *)struc->iOrigin, struc->iProto, SP);
  Ck(ss);
  return ss;
}

Component *AlloSC(Structure *struc, long *SP)
{
  Component *ss;
  DEBUG_CODE(NumAlloSC++);

  Ck(struc);
  Ck(struc->iOrigin);
  ss = AlloC((Object *)struc->iOrigin, struc->iProto, SP);
  Ck(ss);
  return ss;
}    

Structure *ObjS(Object *theObj, long *SP)
{
  /* Allocate a structObject for theObj. 
   * Used in this way:
   *
   * R: ^T
   * R##
   */
  
  register Structure *newStruct;
  
  DEBUG_CODE(NumObjS++);

  /* Allocate a StructObject. */
  
  /* No need to check for IOAMAXSIZE */
  Ck(theObj);
  Protect(theObj, newStruct= (Structure *)IOAalloc(StructureSize, SP));
  
  SETPROTO(newStruct, StructurePTValue);
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  
  newStruct->iProto = GETPROTO(theObj);
  AssignReference(&newStruct->iOrigin, ((Object **)theObj)[GETPROTO(theObj)->OriginOff]);

  Ck(theObj); Ck(newStruct);
  
  return newStruct;
}

long eqS(Structure *arg1, Structure *arg2)
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

long neS(Structure *arg1, Structure *arg2)
{
  DEBUG_CODE(NumneS++);
  Ck(arg1); Ck(arg2);
  return !eqS(arg1, arg2);
}

long leS(Structure *arg1, Structure *arg2, long *SP)
{ 
  DEBUG_CODE(NumleS++);
  Ck(arg1); Ck(arg2);
  return (eqS(arg1, arg2) || ltS(arg1, arg2, SP));
}


long geS(Structure *arg1, Structure *arg2, long *SP)
{ 
  DEBUG_CODE(NumgeS++);
  Ck(arg1); Ck(arg2);
  return (eqS(arg1, arg2) || gtS(arg1, arg2, SP));
}

long gtS(Structure *arg1, Structure *arg2, long *SP)
{
  DEBUG_CODE(NumgtS++);
  Ck(arg1); Ck(arg2);
  return ltS(arg2, arg1, SP);
}

long ltS(Structure *arg1, Structure *arg2, long *SP)
{
  ProtoType *proto1;
  ProtoType *proto2;
  Item * newObject;

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
	   Ck(arg2);
	   return (Object *)((long*)newObject)[proto2->OriginOff] == (arg2->iOrigin);
	 }
       }

  Ck(arg1); Ck(arg2);
  return 0; 
}

