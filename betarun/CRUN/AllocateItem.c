/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(struct Item *,AlloI)
{
    DeclReference1(struct Item *, item);
    GCable_Entry();
    FetchOriginProto

    Ck(origin);

#if defined(hppa) && defined(RTDEBUG)
    if((unsigned)getRefSP() > (unsigned)ReferenceStack + 990*4) {
      fprintf(stderr,"#ReferenceStack overflow!!!\n");
    }
#endif

    DEBUG_CODE( Claim(proto->Size > 0, "AlloI: proto->Size > 0") );

    Protect(origin, item = (struct Item *) IOAcalloc(4*proto->Size));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin);

    Protect(item, CallBetaEntry(proto->GenPart,item));

    Ck(item);

    GCable_Exit(1);    
    RETURN(item);
}


/* AlloH:
 * Like AlloI, but does not have an origin, and does not 
 * call G-entry ("AllocateHeap") 
 */

ParamOriginProto(struct Item *,AlloH)
{
    DeclReference1(struct Item *, item);
    GCable_Entry();
    FetchOriginProto

    /*Ck(origin);*/

#if defined(hppa) && defined(RTDEBUG)
    if((unsigned)getRefSP() > (unsigned)ReferenceStack + 990*4) {
      fprintf(stderr,"#ReferenceStack overflow!!!\n");
    }
#endif

    /*Protect(origin, item = (struct Item *) IOAcalloc(4*proto->Size));*/
    item = (struct Item *) IOAcalloc(4*proto->Size);

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, /*origin*/ 0);

    /*Protect(item, CallBetaEntry(proto->GenPart,item));*/

    Ck(item);

    GCable_Exit(1);    
    RETURN(item);
}
