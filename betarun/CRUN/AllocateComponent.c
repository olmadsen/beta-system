/* File: AllocateComponent.c
 * $Id: AllocateComponent.c,v 1.1 1992-06-06 03:36:30 beta Exp $
 */

#include "beta.h"
#include "crun.h"

ref(Component) AllocateComponent(ref(ProtoType) prototype,
				 ref(Object) origin
				 )
{
    register ref(Component) theComp;

    theComp = cast(Component) IOAcalloc(prototype->Size*4
					+ headsize(Component)
					- sizeof(void *));

    /* The new Component is now allocated, but not initialized yet! */

    /* Initialize the structual part; prototype, age etc. */
    theComp->Proto = cast(ProtoType) -1;
    theComp->GCAttr = 1;
    theComp->StackObj = cast(StackObject) 0;
    theComp->CallerObj = cast(Object) 0;
    theComp->CallerComp = cast(Component) 0;
    theComp->CallerLSC = 0;

    setup_item(cast(Item) &theComp->Body, prototype, origin);

    (cast(Item) &theComp->Body)->GCAttr = -6; /* what does -6 mean?? */

    (* (void (*)())prototype->GenPart)(cast(Item) &theComp->Body);
    return theComp;
}


