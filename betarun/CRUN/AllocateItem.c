/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: AllocateItem.c,v 1.18 1993-02-16 14:57:14 datpete Exp $
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

    Protect(origin, item = (struct Item *) IOAcalloc(4*proto->Size));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin);

    Protect(item, CallBetaEntry(proto->GenPart,item));

    Ck(item);

    GCable_Exit(1);    
    RETURN(item);
}
