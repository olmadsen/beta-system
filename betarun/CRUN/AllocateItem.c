/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateItem.c,v $, rel: %R%, date: $Date: 1992-08-24 02:31:01 $, SID: $Revision: 1.11 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamOriginProto(AlloI)
{
    DeclReferences1(struct Item *item)
    GCable_Entry
    FetchOriginProto

    Ck(origin);

    item = (struct Item *) IOAcalloc(4*proto->Size);

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin);

    CallBetaEntry(proto->GenPart,item);
    
    return item;
}
