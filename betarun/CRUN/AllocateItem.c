/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateItem.c,v $, rel: %R%, date: $Date: 1992-08-19 15:44:05 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ref(Item) AlloI(ref(ProtoType) prototype, ref(Object) origin)
{
    ref(Item) theItem;

    GCable_Entry

    Ck(origin);

    theItem = cast(Item) IOAcalloc(4*prototype->Size);

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(theItem, prototype, origin);

    /* (* (void (*)())prototype->GenPart)(theItem);
     *
     * Jump to it instead; Avoid RunTime Stack in the middle.
     */

    asm("jmpl %0, %%g0;restore %1, 0, %%o0"::
	"r" (prototype->GenPart), "r" (theItem));
    
    return theItem;
}


