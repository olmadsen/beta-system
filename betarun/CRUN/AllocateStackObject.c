/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateStackObject.c,v $, rel: %R%, date: $Date: 1992-08-31 10:04:02 $, SID: $Revision: 1.8 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ref(StackObject)
AlloSO(unsigned size)
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


