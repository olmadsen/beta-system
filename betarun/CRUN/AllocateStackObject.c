/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"


#ifdef sparc

/* Dont allow size to be in a GC register */
asmlabel(AlloSO,
	 "mov %o0,%o2;"    \
	 "clr %o0;"        \
	 "clr %o1;"        \
	 "clr %o3;"        \
	 "ba  "CPREF"AlloSO;"   \
	 "clr %o4;"        \
	 );
ref(StackObject)
CAlloSO(int i0, int i1, unsigned size)
#else
ref(StackObject)
AlloSO(unsigned size)
#endif
{
    DeclReference1(struct StackObject *, theStack);

    GCable_Entry();

    theStack = cast(StackObject) IOAalloc(StackObjectSize(size));

    theStack->Proto = StackObjectPTValue;
    theStack->GCAttr = 1;
    theStack->BodySize = size;
    theStack->StackSize = 0;

    return theStack;
}


