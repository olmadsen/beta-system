/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

/* #ifndef MT */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(struct Item *,AlloI)
/* = struct Item * AlloI(struct Object *origin, struct ProtoType *proto) */
{
    DeclReference1(struct Item *, item); /*= struct Item * item; */
    GCable_Entry();
    FetchOriginProto();

    DEBUG_CODE(NumAlloI++);

#if 0
    if ((NumAlloI > 15000) && (NumAlloI<20000)) {
      fprintf(output, "AlloI\n");
      fprintf(output, "NumAlloI: %d\n", (int)NumAlloI);
    }
#endif

    Ck(origin);

#if (defined(hppa) && defined(RTDEBUG)) || defined(crts)
    if((unsigned)/*getRefSP()*/RefSP > (unsigned)ReferenceStack + 990*4) {
      Notify("ReferenceStack overflow!!!");
    }
#endif

    DEBUG_CODE( Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

    Protect(origin, item = (struct Item *) IOAcalloc(ItemSize(proto)));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin); 

    if (proto->GenPart){
      Protect(item, CallBetaEntry(proto->GenPart,item));
    }

    Ck(item);

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

ParamOriginProto(struct Item *,AlloH)
{
    DeclReference1(struct Item *, item);
    GCable_Entry();
    FetchOriginProto();

#if defined(hppa) && defined(RTDEBUG)
    if((unsigned)/*getRefSP()*/RefSP > (unsigned)ReferenceStack + 990*4) {
      Notify("ReferenceStack overflow!!!");
    }
#endif

    item = (struct Item *) IOAcalloc(4*proto->Size);

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


/* #endif */ /* MT */
