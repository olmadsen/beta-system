/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopyText.c,v 1.12 1992-11-27 10:46:07 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void CopyT(char *asciz,
	   ref(Item) theItem,
	   unsigned offset /* i ints */
	   )
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned range, size, i;
    
    GCable_Entry();
    
    Ck(theItem);
    /* Allocate a ValueRepetition and initialize it with some text.    */
    
    range = strlen(asciz);

    /* LVRA missing */
    
    /* Allocate a value repetition */
    size = ByteRepSize(range);
    Protect(theItem, theRep = cast(ValRep) IOAalloc(size));

    Ck(theItem);
    
    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    /* Assign the text to the body part of the repetition. */
    
    for (i = 0; i < (size-headsize(ValRep))/4; i++){
	/* printf("CopyT: %.4s\n", (long *)asciz + i); */
	theRep->Body[i] = *((long *)asciz + i);
    }
    
    AssignReference((long *)theItem + offset, cast(Item) theRep);
}
