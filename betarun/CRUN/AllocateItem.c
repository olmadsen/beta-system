/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamOriginProto(Item *,AlloI)
/* = Item * AlloI(Object *origin, ProtoType *proto) */
{
    DeclReference1(Item *, item); /*= Item * item; */
    GCable_Entry();
    MCHECK();
    FetchOriginProto();

    DEBUG_CODE(NumAlloI++);

    Ck(origin);

#if (defined(hppa) && defined(RTDEBUG))
    if((unsigned)/*getRefSP()*/RefSP > (unsigned)ReferenceStack + 990*4) {
      Notify("ReferenceStack overflow!!!");
    }
#endif

    Claim((long)proto->Size>0, "proto->Size>0");

    Protect(origin, item = (Item *) IOAalloc(ItemSize(proto)));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin); 

    if (proto->GenPart){
#ifdef RTDEBUG
      Protect2(origin, item, CallBetaEntry(proto->GenPart,item));
#else
      Protect(item, CallBetaEntry(proto->GenPart,item));
#endif
    }

    Ck(origin);
    Ck(item);

    MCHECK();

    GCable_Exit(1);    
#ifdef sparc
    return_in_i1(item);
#else
    RETURN(item);
#endif
}


/* AlloH:
 * Like AlloI, but does not have an origin, and does not 
 * call G-entry ("AllocateHeap") 
 */

ParamOriginProto(Item *,AlloH)
{
    DeclReference1(Item *, item);
    GCable_Entry();
    FetchOriginProto();

#if defined(hppa) && defined(RTDEBUG)
    if((unsigned)/*getRefSP()*/RefSP > (unsigned)ReferenceStack + 990*4) {
      Notify("ReferenceStack overflow!!!");
    }
#endif

    item = (Item *) IOAalloc(4*proto->Size);

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, /*origin*/ 0);


    Ck(item);

    GCable_Exit(1);    

#ifdef sparc
    return_in_i1(item);
#else
    RETURN(item);
#endif
}


#endif /* MT */
