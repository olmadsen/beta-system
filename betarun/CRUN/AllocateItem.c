/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateItem.c,v $, rel: %R%, date: $Date: 1992-08-27 15:20:59 $, SID: $Revision: 1.12 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(struct Item *,AlloI)
{
    DeclReference1(struct Item *item);
    GCable_Entry();
    FetchOriginProto

    Ck(origin);

    item = (struct Item *) IOAcalloc(4*proto->Size);

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin);

    CallBetaEntry(proto->GenPart,item);

    ForceVolatileRef(item);
    Ck(item);
    
    return item;
}
