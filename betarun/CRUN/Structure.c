/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT
ParamOriginProto(struct Structure *, AlloS)
{
  register ref(Structure) newStruct;
  
  GCable_Entry();
  FetchOriginProto();

  DEBUG_CODE(NumAlloS++);

  /* Allocate a StructObject. */
    
  Ck(origin);
  Protect(origin, newStruct = cast(Structure) IOAalloc(StructureSize));
  
  newStruct->Proto = StructurePTValue;
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  newStruct->iOrigin = origin;
  newStruct->iProto = proto;

  Ck(newStruct); Ck(origin);
  
#ifdef sparc
    return_in_i1(newStruct);
#else
  RETURN(newStruct);
#endif
}

ParamStruc(struct Item *, AlloSI)
{
  struct Item *ss;
  
  GCable_Entry();
  FetchStruc();

  DEBUG_CODE(NumAlloSI++);

  Ck(struc); Ck(struc->iOrigin);
#ifdef sparc
  ss = SPARC_AlloI(cast(Object) struc->iOrigin, 0, struc->iProto, 0, 0);
#endif
#ifdef hppa
  ss = CAlloI(cast(Object) struc->iOrigin, struc->iProto);
#endif

  Ck(ss); 

#ifdef sparc
  return_in_i1(ss);
#else
  RETURN(ss);
#endif
}

ParamStruc(struct Component *, AlloSC)
{
  struct Component *ss;
  
  GCable_Entry();
  FetchStruc();

  DEBUG_CODE(NumAlloSC++);

  Ck(struc);
#ifdef sparc
  ss = SPARC_AlloC(cast(Object) struc->iOrigin, 0, struc->iProto, 0, 0);
#endif
#ifdef hppa
  ss = CAlloC(cast(Object) struc->iOrigin, struc->iProto);
#endif

  Ck(ss);

#ifdef sparc
  return_in_i1(ss);
#else
  RETURN(ss);
#endif
}    

ref(Structure) ObjS(ref(Object) theObj)
{
  /* Allocate a structObject for theObj. 
   * Used in this way:
   *
   * R: ^T
   * R##
   *
   */
  
  register ref(Structure) newStruct;
  
  GCable_Entry();
  
  /* Allocate a StructObject. */

  DEBUG_CODE(NumObjS++);

#ifdef RTDEBUG
  if (theObj->Proto == DopartObjectPTValue){
    fprintf(output, "ObjS: called with DoPartObject: 0x%x\n", (int)theObj);
    theObj = ((struct DopartObject *)theObj)->Origin; /* the "real" object */
  }
#endif
  
  Ck(theObj);
  Protect(theObj, newStruct = cast(Structure) IOAalloc(StructureSize));
  
  newStruct->Proto = StructurePTValue;
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  newStruct->iProto = theObj->Proto;
  newStruct->iOrigin = (casthandle(Object)theObj)[theObj->Proto->OriginOff];

  Ck(newStruct); Ck(theObj);
  
  return newStruct; 
}
#endif /* MT */


long eqS(ref(Structure) arg1, ref(Structure) arg2)
{
  /*GCable_Entry();*/
  
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

long neS(ref(Structure) arg1, ref(Structure) arg2)
{
  /* GCable_Entry(); */
  
  DEBUG_CODE(NumneS++);
  Ck(arg1); Ck(arg2);
  return !eqS(arg1, arg2);
}



#ifdef sparc
#ifdef MT
asmlabel(ltS,
	 CallAndPush_I0_I1(ltS)
	 ); 
#else
asmlabel(ltS, 
	 "clr %o2; "
         "clr %o3; "
         "ba   "CPREF"ltS; "
         "clr %o4");
#endif
long CltS(ref(Structure) arg1, ref(Structure) arg2)
#else /* not sparc */
long ltS(ref(Structure) arg1, ref(Structure) arg2)
#endif
{
  ref(ProtoType) proto1;
  ref(ProtoType) proto2;
  DeclReference1(struct Item *, newObject);


  GCable_Entry();
  
  DEBUG_CODE(NumltS++);
  Ck(arg1); Ck(arg2);
  if (!arg1) return 0;
  if (!arg2) return 0;
  
  proto1 = GetProto(arg1);
  proto2 = GetProto(arg2);
  
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
	   /* Now there is some hope.
	    * We need to check if origins are equal.
	    */
	   struct ProtoType *tmpProto1 = GetProto(arg1); 
	   if (proto2->OriginOff == tmpProto1->OriginOff){
	     /* The original prototypes have same origin offset 
	      * (same prefix level), so the result is 
	      * (arg1->iOrigin == arg2->iOrigin) 
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
	   
#ifdef sparc
#ifdef MT
	   Protect(arg2, 
		   newObject = (struct Item *)
		   CallVEntry((void (*)())(arg1->iProto), arg1->iOrigin));
#else
	   Protect(arg2, newObject = SPARC_AlloSI(arg1, 0, 0, 0, 0));
#endif
#endif
#ifdef hppa
	   Protect(arg2, newObject = CAlloSI(arg1));
#endif
	   Ck(arg2);
	   return cast(Object)((long*)newObject)[proto2->OriginOff] == (arg2->iOrigin);
	 }
       }
  Ck(arg1); Ck(arg2);
  return 0; 
}




#ifdef MT
asmlabel(gtS,
	 CallAndPush_I0_I1(gtS)
	 ); 
long CgtS(ref(Structure) arg1, ref(Structure) arg2)
#else
long gtS(ref(Structure) arg1, ref(Structure) arg2)
#endif
{
  GCable_Entry();
  
  DEBUG_CODE(NumgtS++);
  Ck(arg1); Ck(arg2);
#ifdef MT
  return CltS(arg2, arg1);
#else /* MT */
  return ltS(arg2, arg1);
#endif /* MT */
}




#ifdef MT
asmlabel(leS,
	 CallAndPush_I0_I1(leS)
	 ); 
long CleS(ref(Structure) arg1, ref(Structure) arg2)
#else
long leS(ref(Structure) arg1, ref(Structure) arg2)
#endif
{ 
  GCable_Entry();
  
  DEBUG_CODE(NumleS++);
  Ck(arg1); Ck(arg2);
#ifdef MT
  return (eqS(arg1, arg2) || CltS(arg1, arg2));
#else /* MT */
  return (eqS(arg1, arg2) || ltS(arg1, arg2));
#endif /* MT */
}




#ifdef MT
asmlabel(geS,
	 CallAndPush_I0_I1(geS)
	 ); 
long CgeS(ref(Structure) arg1, ref(Structure) arg2)
#else
long geS(ref(Structure) arg1, ref(Structure) arg2)
#endif
{ 
  GCable_Entry();
  
  DEBUG_CODE(NumgeS++);
  Ck(arg1); Ck(arg2);
#ifdef MT
  return (eqS(arg1, arg2) || CgtS(arg1, arg2));
#else
  return (eqS(arg1, arg2) || gtS(arg1, arg2));
#endif
}
