/* File: AllocateItem.c
 * $Id: AllocateItem.c,v 1.1 1992-06-06 03:36:31 beta Exp $
 */

#include "beta.h"
#include "crun.h"

ref(Item)
AllocateItem(ref(ProtoType) prototype,
	     ref(Object) origin
	     )
{
    register ref(Item) theItem;

    theItem = cast(Item) IOAcalloc(prototype->Size*4
				   +headsize(Item)
				   -sizeof(void *));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(theItem, prototype, origin);

    (* (void (*)())prototype->GenPart)(theItem);
    return theItem;
}


