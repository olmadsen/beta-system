/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

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
StackObject * CAlloSO(int i0, int i1, unsigned size)
#else
StackObject * AlloSO(unsigned size)
#endif
{
    DeclReference1(StackObject *, theStack);
    DEBUG_CODE(NumAlloSO++);

    /* Do not try to allocate directly in AOA, unless Suspend 
     * is fixed to process every reference on the stack 
     * (As NEWRUN does)
     */
    theStack = (StackObject *) IOAalloc(StackObjectSize(size));

    SETPROTO(theStack,StackObjectPTValue);
    if (IOAMinAge!=0) theStack->GCAttr = IOAMinAge;
    theStack->BodySize = size;
    /* No need: IOA is memset(0) theStack->StackSize = 0; */

    /* fprintf(output, "AlloSO: theObj: 0x%x\n", theStack); */

    Ck(theStack);

    return theStack;
}


#endif /* MT */
