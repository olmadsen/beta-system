/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef STATIC_OBJECT_REPETITIONS
ParamObjOriginProtoOffRange(AlloORG)
{
  /* AllocateObjectRepetitionGeneral: Allocate repetition of plain items,
   * inlined in repetition 
   */
  DeclReference1(struct ObjectRep *, theRep);
  struct Item *item;
  GCable_Entry();
#ifdef hppa
  range  = getD1Reg();
  origin = (struct Object *)getOriginReg();
  proto  = (struct ProtoType *)getCallReg();
  theObj = (struct Object *)getThisReg();
  offset = getD0Reg();
#endif

  DEBUG_CODE(NumAlloORG++);

  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = cast(ObjectRep)IOAcalloc(StatItemRepSize(range,proto)));
  Ck(theObj);

  theRep->Proto = StatItemRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  SaveVar(theObj);

  while(--range>=0){
    item=(struct Item *)((long)(&theRep->Body) + range*ItemSize(proto));
    setup_item(item, proto, origin); 
    if (proto->GenPart){
      Protect(theRep, CallBetaEntry(proto->GenPart,item));
    }
  }

  RestoreVar(theObj);

  AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

  return;
}

ParamObjOriginProtoOffRange(AlloORGC)
{
  /* AllocateObjectRepetitionGeneralComponent: Allocate repetition of plain components,
   * inlined in repetition 
   */
  DeclReference1(struct ObjectRep *, theRep);
  struct Component *comp;
  GCable_Entry();
#ifdef hppa
  range  = getD1Reg();
  origin = (struct Object *)getOriginReg();
  proto  = (struct ProtoType *)getCallReg();
  theObj = (struct Object *)getThisReg();
  offset = getD0Reg();
#endif

  DEBUG_CODE(NumAlloORGC++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = cast(ObjectRep)IOAcalloc(StatCompRepSize(range,proto)));
  Ck(theObj);

  theRep->Proto = StatCompRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  theRep->iProto = proto;
  theRep->iOrigin = origin;

  SaveVar(theObj);

  while(--range>=0){
    comp=(struct Component *)((long)(&theRep->Body) + range*ComponentSize(proto));

    comp->Proto = ComponentPTValue;
    comp->GCAttr = 1;
    comp->StackObj = cast(StackObject) 0;
    comp->CallerObj = cast(Object) 0;
    comp->CallerComp = cast(Component) 0;
    comp->CallerLSC = 0;

    setup_item(cast(Item) &comp->Body, proto, origin);
    (cast(Item) &comp->Body)->GCAttr = -((headsize(Component))/4);

    if (proto->GenPart){
      Protect(theRep, CallBetaEntry(proto->GenPart,&comp->Body));
    }
  }

  RestoreVar(theObj);

  AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

  return;
}
#endif /* STATIC_OBJECT_REPETITIONS */

ParamObjOriginProtoOffRange(AlloORR)
{
  /* AllocateObjectRepetitionReference: Allocate repetition of offline items
   */
  DeclReference1(struct ObjectRep *, theRep);
  struct Item *item;
  GCable_Entry();
#ifdef hppa
  range  = getD1Reg();
  origin = (struct Object *)getOriginReg();
  proto  = (struct ProtoType *)getCallReg();
  theObj = (struct Object *)getThisReg();
  offset = getD0Reg();
#endif

  DEBUG_CODE(NumAlloORR++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = cast(ObjectRep)IOAcalloc(DynObjectRepSize(range)));
  Ck(theObj);

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

  return;
}

ParamObjOriginProtoOffRange(AlloORRC)
{
  /* AllocateObjectRepetitionComponent: Allocate repetition of offline components
   */
  DeclReference1(struct ObjectRep *, theRep);
  struct Component *comp;
  GCable_Entry();
#ifdef hppa
  range  = getD1Reg();
  origin = (struct Object *)getOriginReg();
  proto  = (struct ProtoType *)getCallReg();
  theObj = (struct Object *)getThisReg();
  offset = getD0Reg();
#endif

  DEBUG_CODE(NumAlloORRC++);
  Ck(theObj);
  Protect2(theObj, origin,  
	  theRep = cast(ObjectRep)IOAcalloc(DynObjectRepSize(range)));
  Ck(theObj);

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

  return;
}
