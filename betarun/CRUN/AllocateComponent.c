/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamOriginProto(Component *,AlloC)
{
  /* AlloC calls BETA code, thus we need to make sure GC can
     find and update the reference in comp. */

    DeclReference1(Component *, comp);
    GCable_Entry();
    FetchOriginProto();

    DEBUG_CODE(NumAlloC++);
    Ck(origin);

    Claim((long)proto->Size>0, "proto->Size > 0");

    Protect(origin, 
	    comp = (Component *) IOAalloc(ComponentSize(proto)));    

    /* The new Component is now allocated, but not initialized yet! */

    /* Initialize the structual part; prototype, age etc. */
    SETPROTO(comp,ComponentPTValue);
    if (IOAMinAge!=0) comp->GCAttr = IOAMinAge;

    setup_item((Item *) &comp->Body, proto, origin);

    ((Item *) &comp->Body)->GCAttr = -((headsize(Component))/4);

    if (proto->GenPart){
#ifdef RTDEBUG
      Protect2(origin, comp, CallBetaEntry(proto->GenPart,&comp->Body));
#else
      Protect(comp, CallBetaEntry(proto->GenPart,&comp->Body));
#endif
    }

    Ck(origin); Ck(comp);

    GCable_Exit(1);

#ifdef sparc
    return_in_i1(comp);
#else
    RETURN(comp);
#endif
}


#endif /* MT */
