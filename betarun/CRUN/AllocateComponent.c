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
    FetchOriginProto();

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

#ifdef sparc
    return_in_i1(comp);
#else
    RETURN(comp);
#endif
}

#ifdef sparc
/* Functions used to call RT routines directly from C.
 * Needed because %i1 in calling regwin is destroyed by (C)AlloC
 */

struct Component *SPARC_AlloC(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4)
{
  GCable_Entry();
  return CAlloC(origin, i1, proto, i3, i4);
  GCable_Exit(1);
}

#endif
