/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: AllocateStackObject.c,v 1.9 1992-09-03 12:55:29 beta Exp $
 * by Peter Andersen, Peter Orbaek and Tommy Thorn.
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


