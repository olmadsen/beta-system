/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateComponent.c,v $, rel: %R%, date: $Date: 1992-07-23 17:18:04 $, SID: $Revision: 1.9 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(Component) AlloC(ref(ProtoType) prototype,
		     ref(Object) origin
		     )
{
    register ref(Component) theComp;

    theComp = cast(Component) IOAcalloc(ComponentSize(prototype->Size));

    /* The new Component is now allocated, but not initialized yet! */

    /* printf("\nAllocateComponent: theComp = %x", theComp); */

    /* Initialize the structual part; prototype, age etc. */
    theComp->Proto = ComponentPTValue;
    theComp->GCAttr = 1;
    theComp->StackObj = cast(StackObject) 0;
    theComp->CallerObj = cast(Object) 0;
    theComp->CallerComp = cast(Component) 0;
    theComp->CallerLSC = 0;

    setup_item(cast(Item) &theComp->Body, prototype, origin);

    (cast(Item) &theComp->Body)->GCAttr = - headsize(Component)/4;

    (* (void (*)())prototype->GenPart)(cast(Item) &theComp->Body);
    return theComp;
}


