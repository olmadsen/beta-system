/* File: Structure.c
 * $Id: Structure.c,v 1.1 1992-06-06 03:36:48 beta Exp $
 */

#include "beta.h"
#include "crun.h"

/* $Id: Structure.c,v 1.1 1992-06-06 03:36:48 beta Exp $
 */

/* params ?? */
ref(Structure)
AllocateStruc(ref(Object) origin,
	      ref(ProtoType) proto
	      )
{
    register ref(Structure) newStruct;

    /* Allocate a StructObject. */

    newStruct = cast(Structure) IOAalloc(headsize(Structure));
    newStruct->Proto = cast(ProtoType) -5;
    newStruct->GCAttr = 1;
    newStruct->iOrigin = origin; /* er dette rigtigt ?? */
    newStruct->iProto = proto;
    return newStruct;
}

ref(Structure) ThisStruc(ref(Object) this)
{
    /* Allocate a structObject for thisObject. */

    register ref(Structure) newStruct;
    register ref(Object) origin;

    /* Allocate a StructObject. */

    newStruct = cast(Structure) IOAalloc(headsize(Structure));
    newStruct->Proto = cast(ProtoType) -5;
    newStruct->GCAttr = 1;

    origin = (casthandle(Object)this)[this->Proto->OriginOff];
    /* origin is the object we really want orgin and proto of */

    newStruct->iProto = origin->Proto;
    newStruct->iOrigin = (casthandle(Object)origin)[origin->Proto->OriginOff];
    /* Correct ?? ?? ?? */

    /* MP */
    asm volatile ("restore %0, %%g0, %%l0;retl;nop"::"r" (newStruct));
    return newStruct;
}


/* params ?? */
ref(Item)
AllocateStrucItem(ref(Structure) theStruct)
{
    return AllocateItem(theStruct->iProto, cast(Object) theStruct->iOrigin);
}


/* params ?? */
ref(Component)
AllocateStrucComponent(ref(Structure) theStruct)
{
    return AllocateComponent(theStruct->iProto, cast(Object) theStruct->iOrigin);
}


/* params ?? */
int
eqStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    if (!arg1) {
	if (!arg2)
	  return 1;
	return 0;
    }
    if (!arg2)
      return 0;
    if (arg1->iProto != arg2->iProto)
      return 0;
    if (arg1->iOrigin != arg2->iOrigin)
      return 0;
    return 1;
}


/* params ?? */
int
neStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    return !eqStruc(arg1, arg2);
}


/* params ?? */
int
ltStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    fprintf(stderr, "ltStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}


/* params ?? */
int
gtStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    fprintf(stderr, "gtStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}


/* params ?? */
int
leStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    fprintf(stderr, "leStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}


/* params ?? */
int
geStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    fprintf(stderr, "geStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}

#include "beta.h"
#include "crun.h"

/* Need to do this in assembler, as the arguments to
   my caller normally isn't accesseable */
asmlabel(SetArgValues, "
	set _ArgCount, %g1
	st %i0, [%g1]
	set _ArgVector, %g1
	retl
	st %i1, [%g1]
");


