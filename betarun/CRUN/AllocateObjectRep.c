/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

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
  DeclReference1(struct ObjectRep *, theRep);
  struct Item *item;
  GCable_Entry();
  FetchObjOriginProtoOffRange();

  DEBUG_CODE(NumAlloVRI++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = cast(ObjectRep)IOAalloc(DynObjectRepSize(range)));

  theRep->Proto = DynItemRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  SaveVar(theObj);

  while(--range>=0){
#ifdef sparc
    Protect(theRep, 
	    item = SPARC_AlloI(cast(Object) theRep->iOrigin, 0, theRep->iProto, 0, 0));
#endif
#ifdef hppa
    Protect(theRep, 
	    item = CAlloI(cast(Object) theRep->iOrigin, theRep->iProto));
#endif
#ifdef crts
    Protect(theRep, 
	    item = AlloI(cast(Object) theRep->iOrigin, theRep->iProto));
#endif
    AssignReference((long *)((long)&theRep->Body + range*4), item);
  }

  RestoreVar(theObj);

  AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

  Ck(theObj); Ck(theRep);
}

ParamObjOriginProtoOffRange(AlloVRC)
{
  /* AllocateObjectRepetitionComponent: Allocate repetition of offline components
   */
  DeclReference1(struct ObjectRep *, theRep);
  struct Component *comp;
  GCable_Entry();
  FetchObjOriginProtoOffRange();

  DEBUG_CODE(NumAlloVRC++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = cast(ObjectRep)IOAalloc(DynObjectRepSize(range)));

  theRep->Proto = DynCompRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  SaveVar(theObj);

  while(--range>=0){
#ifdef sparc
    Protect(theRep, 
	    comp = SPARC_AlloC(cast(Object) theRep->iOrigin, 0, theRep->iProto, 0, 0));
#endif
#ifdef hppa
    Protect(theRep, 
	    comp = CAlloC(cast(Object) theRep->iOrigin, theRep->iProto));
#endif
#ifdef crts
    Protect(theRep, 
	    comp = AlloC(cast(Object) theRep->iOrigin, theRep->iProto));
#endif
    AssignReference((long *)((long)&theRep->Body + range*4), 
		    (struct Item *)comp);
  }

  RestoreVar(theObj);

  AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

  Ck(theObj); Ck(theRep);
}

#endif /* MT */
