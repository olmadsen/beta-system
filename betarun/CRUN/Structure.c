/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Structure.c,v $, rel: %R%, date: $Date: 1992-06-12 14:58:17 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(Structure) AllocateStruc(ref(ProtoType) proto,
			     ref(Object) origin
			     )
{
    register ref(Structure) newStruct;

    /* Allocate a StructObject. */

    newStruct = cast(Structure) IOAalloc(headsize(Structure));
    newStruct->Proto = StructurePTValue;
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
    newStruct->Proto = StructurePTValue;
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


asmlabel(eqStruc, "
	ld	[%sp+18*4], %o0
	ld	[%sp+16*4], %o1
	ba	_CeqStruc
	inc	16, %sp
");

int CeqStruc(ref(Structure) arg1,
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


asmlabel(neStruc, "
	ld	[%sp+18*4], %o0
	ld	[%sp+16*4], %o1
	ba	_CneStruc
	inc	16, %sp
");

int CneStruc(ref(Structure) arg1,
	     ref(Structure) arg2
	     )
{
    return !eqStruc(arg1, arg2);
}


asmlabel(ltStruc, "
	ld	[%sp+18*4], %o0
	ld	[%sp+16*4], %o1
	ba	_CltStruc
	inc	16, %sp
");

int CltStruc(ref(Structure) arg1,
	     ref(Structure) arg2
	     )
{
    fprintf(stderr, "ltStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}


asmlabel(gtStruc, "
	ld	[%sp+18*4], %o0
	ld	[%sp+16*4], %o1
	ba	_CgtStruc
	inc	16, %sp
");

int CgtStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    fprintf(stderr, "gtStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}


asmlabel(leStruc, "
	ld	[%sp+18*4], %o0
	ld	[%sp+16*4], %o1
	ba	_CleStruc
	inc	16, %sp
");

int CleStruc(ref(Structure) arg1,
	ref(Structure) arg2
	)
{
    fprintf(stderr, "leStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}


asmlabel(geStruc, "
	ld	[%sp+18*4], %o0
	ld	[%sp+16*4], %o1
	ba	_CgeStruc
	inc	16, %sp
");

int CgeStruc(ref(Structure) arg1,
	     ref(Structure) arg2
	     )
{
    fprintf(stderr, "geStruc: Unfinished code, doesn't work\n");
    return 0; /* Hmm, I got bored (??) */
}

