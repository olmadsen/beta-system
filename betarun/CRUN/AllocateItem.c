/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateItem.c,v $, rel: %R%, date: $Date: 1992-07-20 11:44:37 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(Item) AlloI(ref(ProtoType) prototype, ref(Object) origin)
{
    register ref(Item) theItem;

    theItem = cast(Item) IOAcalloc((prototype->Size+1)*4);

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(theItem, prototype, origin);

    (* (void (*)())prototype->GenPart)(theItem);
    return theItem;
}


