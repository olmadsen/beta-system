/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateComponent.c,v $, rel: %R%, date: $Date: 1992-08-22 02:08:25 $, SID: $Revision: 1.13 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(AlloC)
{
  /* AlloC calls BETA code, thus we need to make sure GC can
     find and update the reference in comp. */

    DeclReferences1(struct Component *comp) 
    GCable_Entry
    FetchOriginProto

#ifdef DEBUG_IOA
    if (origin) /* origin is none first time, and only there */
      Ck(origin);
#endif

    comp = cast(Component) IOAcalloc(ComponentSize(proto->Size));

    /* The new Component is now allocated, but not initialized yet! */

    /* printf("\nAllocateComponent: comp = %x", comp); */

    /* Initialize the structual part; prototype, age etc. */
    comp->Proto = ComponentPTValue;
    comp->GCAttr = 1;
    comp->StackObj = cast(StackObject) 0;
    comp->CallerObj = cast(Object) 0;
    comp->CallerComp = cast(Component) 0;
    comp->CallerLSC = 0;

    setup_item(cast(Item) &comp->Body, proto, origin);

    (cast(Item) &comp->Body)->GCAttr = - headsize(Component)/4;

    CallBetaEntry(proto->GenPart,&comp->Body);

    ReturnDual(comp);
}
