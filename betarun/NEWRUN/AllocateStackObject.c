/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct StackObject *AlloSO(unsigned size, long *SP)
{
    struct StackObject *theStack;

    DEBUG_CODE(NumAlloSO++);

    theStack = (struct StackObject *)IOAalloc(StackObjectSize(size), SP);

    theStack->Proto = StackObjectPTValue;
    theStack->GCAttr = 1;
    theStack->BodySize = size;
    theStack->StackSize = size; /* always identical to BodySize in NEWRUN */

    /*fprintf(output, "AlloSO: theObj: 0x%x, size=0x%x\n", theStack, size);*/

    Ck(theStack);

    return theStack;
}


