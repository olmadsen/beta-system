/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamOriginProto(Component *,AlloC)
{
  /* AlloC calls BETA code, thus we need to make sure GC can
     find and update the reference in comp. */

    DeclReference1(Component *, comp);
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
      Protect(comp, CallBetaEntry(proto->GenPart,&comp->Body));
    }

    /* origin cannot be Ck'ed since it is not protected during call above */
    Ck(comp);

    SPARC_CODE(return_in_i1(comp));
    RETURN(comp);
}


#endif /* MT */
