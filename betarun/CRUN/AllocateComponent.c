/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(struct Component *,AlloC)
{
  /* AlloC calls BETA code, thus we need to make sure GC can
     find and update the reference in comp. */

    DeclReference1(struct Component *, comp);
    GCable_Entry();
    FetchOriginProto

    Ck(origin);

    DEBUG_CODE( Claim(proto->Size > 0, "AlloC: proto->Size > 0") );

    Protect(origin, 
	    comp = cast(Component) IOAcalloc(ComponentSize(proto->Size)));    

    /* The new Component is now allocated, but not initialized yet! */

    /* Initialize the structual part; prototype, age etc. */
    comp->Proto = ComponentPTValue;
    comp->GCAttr = 1;
    comp->StackObj = cast(StackObject) 0;
    comp->CallerObj = cast(Object) 0;
    comp->CallerComp = cast(Component) 0;
    comp->CallerLSC = 0;

    setup_item(cast(Item) &comp->Body, proto, origin);

    (cast(Item) &comp->Body)->GCAttr = -((headsize(Component))/4);

    Protect(comp, CallBetaEntry(proto->GenPart,&comp->Body));

    Ck(comp);

    GCable_Exit(1);

    RETURN(comp);
}

