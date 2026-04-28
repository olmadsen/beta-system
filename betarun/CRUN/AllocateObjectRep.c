/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen.
 */

#include "beta.h"
#include "crun.h"

/* parameters:
 *   prim1 = originReg = origin, 
 *   prim2 = callReg = proto, NOTE that on some platforms,
 *                         e.g. sparc, prim2 <> callReg
 *                         so proto is then NOT in prim2 (is in %i1)
 *   prim3 = off, 
 *   prim4 = range,
 *   prim5 = this (SGI/PPC)
 *   prim6 = SP   (SGI/PPC)
 */

ParamObjOriginProtoOffRange(AlloVRI)
{
  /* Allocate repetition of offline items */
  DeclReference1(ObjectRep *, theRep);
  Item *item;
  FetchObjOriginProtoOffRange();

  DEBUG_CODE(NumAlloVRI++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = (ObjectRep *)IOAalloc(DynObjectRepSize(range)));

  SETPROTO(theRep,DynItemRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  SaveVar(theObj);

  while(--range>=0){
#ifdef sparc
#ifdef MT
    Protect(theRep, 
	    item = (Item *)
	    CallVEntry((void (*)())(theRep->iProto), theRep->iOrigin));
#else
    Protect(theRep, 
	    item = OAlloI((Object *) theRep->iOrigin, 0, theRep->iProto, 0, 0));
#endif /* MT */
#endif
#ifdef hppa
    Protect(theRep, 
	    item = CAlloI((Object *) theRep->iOrigin, theRep->iProto));
#endif
    AssignReference((long *)((long)&theRep->Body + range*4), item);
  }

  RestoreVar(theObj);

  AssignReference((long *)((char *)theObj + offset), (Item *) theRep);

  Ck(theObj); Ck(theRep);
}



ParamObjOriginProtoOffRange(AlloVRC)
{
  /* AllocateObjectRepetitionComponent: Allocate repetition of offline components
   */
  DeclReference1(ObjectRep *, theRep);
  Component *comp;
  FetchObjOriginProtoOffRange();

  DEBUG_CODE(NumAlloVRC++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = (ObjectRep *)IOAalloc(DynObjectRepSize(range)));

  SETPROTO(theRep,DynCompRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  SaveVar(theObj);

  while(--range>=0){
#ifdef sparc
#ifdef MT
    Protect(theRep, 
	    comp = CallAlloC(theRep->iProto, theRep->iOrigin));
#else
    Protect(theRep, 
	    comp = OAlloC((Object *) theRep->iOrigin, 0, theRep->iProto, 0, 0));
#endif /* MT */
#endif
#ifdef hppa
    Protect(theRep, 
	    comp = CAlloC((Object *) theRep->iOrigin, theRep->iProto));
#endif
    AssignReference((long *)((long)&theRep->Body + range*4), 
		    (Item *)comp);
  }

  RestoreVar(theObj);

  AssignReference((long *)((char *)theObj + offset), (Item *) theRep);

  Ck(theObj); Ck(theRep);
}
