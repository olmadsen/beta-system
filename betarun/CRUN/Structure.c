/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT
ParamOriginProto(Structure *, AlloS)
{
  register Structure * newStruct;
  
  FetchOriginProto();

  DEBUG_CODE(NumAlloS++);

  /* Allocate a StructObject. */
    
  Ck(origin);
  Protect(origin, newStruct = (Structure *) IOAalloc(StructureSize));
  
  SETPROTO(newStruct,StructurePTValue);
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  newStruct->iOrigin = origin;
  newStruct->iProto = proto;

  Ck(newStruct); Ck(origin);
  
  SPARC_CODE(return_in_i1(newStruct));
  RETURN(newStruct);
}

Structure *VAlloS(ProtoType *proto, long *SP, pc_t PC)
{
  Structure *newStruct;
  DEBUG_CODE(NumAlloS++);
#ifdef sparc
  newStruct = (Structure *) IOAallocToSP(StructureSize, SP, PC);
  SETPROTO(newStruct,StructurePTValue);
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  /* newStruct->iOrigin will be set in valhallaComm.c */
  newStruct->iProto = proto;
#endif /* sparc */
#ifdef hppa
  /* Valhalla not yet supported */
  fprintf(output, "valhalla_AlloS: NYI for hppa\n");
  newStruct = NULL;
#endif /* hppa */
  Ck(newStruct);
  return newStruct;
}

ParamStruc(Item *, AlloSI)
{
  Item *ss;
  
  FetchStruc();

  DEBUG_CODE(NumAlloSI++);

  Ck(struc); Ck(struc->iOrigin);
  SPARC_CODE(ss = OAlloI((Object *) struc->iOrigin, 0, struc->iProto, 0, 0));
  HPPA_CODE(ss = CAlloI((Object *) struc->iOrigin, struc->iProto));

  Ck(ss); 

  SPARC_CODE(return_in_i1(ss));
  RETURN(ss);
}

ParamStruc(Component *, AlloSC)
{
  Component *ss;
  
  FetchStruc();

  DEBUG_CODE(NumAlloSC++);

  Ck(struc);
#ifdef sparc
  ss = OAlloC((Object *) struc->iOrigin, 0, struc->iProto, 0, 0);
#endif
#ifdef hppa
  ss = CAlloC((Object *) struc->iOrigin, struc->iProto);
#endif

  Ck(ss);

  SPARC_CODE(return_in_i1(ss));
  RETURN(ss);
}    

Structure * ObjS(Object * theObj)
{
  /* Allocate a structObject for theObj. 
   * Used in this way:
   *
   * R: ^T
   * R##
   *
   */
  
  register Structure * newStruct;
  
  /* Allocate a StructObject. */

  DEBUG_CODE(NumObjS++);

#ifdef RTDEBUG
  if (GETPROTO(theObj) == DopartObjectPTValue){
    fprintf(output, "ObjS: called with DoPartObject: 0x%x\n", (int)theObj);
    theObj = ((DopartObject *)theObj)->Origin; /* the "real" object */
  }
#endif
  
  Ck(theObj);
  Protect(theObj, newStruct = (Structure *) IOAalloc(StructureSize));
  
  SETPROTO(newStruct,StructurePTValue);
  if (IOAMinAge!=0) newStruct->GCAttr = IOAMinAge;
  newStruct->iProto = GETPROTO(theObj);
  newStruct->iOrigin = ((Object **)theObj)[OBJPROTOFIELD(theObj,OriginOff)];

  Ck(newStruct); Ck(theObj);
  
  return newStruct; 
}
#endif /* MT */


long eqS(Structure * arg1, Structure * arg2)
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

long neS(Structure * arg1, Structure * arg2)
{
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
long CltS(Structure * arg1, Structure * arg2)
#else /* not sparc */
long ltS(Structure * arg1, Structure * arg2)
#endif
{
  ProtoType * proto1;
  ProtoType * proto2;
  DeclReference1(Item *, newObject);

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
	   ProtoType *tmpProto1 = GetProto(arg1); 
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
		   newObject = (Item *)
		   CallVEntry((void (*)())(arg1->iProto), arg1->iOrigin));
#else
	   Protect(arg2, newObject = OAlloSI(arg1, 0, 0, 0, 0));
#endif
#endif
#ifdef hppa
	   Protect(arg2, newObject = CAlloSI(arg1));
#endif
	   Ck(arg2);
	   return (Object *)((long*)newObject)[proto2->OriginOff] == (arg2->iOrigin);
	 }
       }
  Ck(arg1); Ck(arg2);
  return 0; 
}




#ifdef MT
asmlabel(gtS,
	 CallAndPush_I0_I1(gtS)
	 ); 
long CgtS(Structure * arg1, Structure * arg2)
#else
long gtS(Structure * arg1, Structure * arg2)
#endif
{
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
long CleS(Structure * arg1, Structure * arg2)
#else
long leS(Structure * arg1, Structure * arg2)
#endif
{ 
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
long CgeS(Structure * arg1, Structure * arg2)
#else
long geS(Structure * arg1, Structure * arg2)
#endif
{ 
  DEBUG_CODE(NumgeS++);
  Ck(arg1); Ck(arg2);
#ifdef MT
  return (eqS(arg1, arg2) || CgtS(arg1, arg2));
#else
  return (eqS(arg1, arg2) || gtS(arg1, arg2));
#endif
}
