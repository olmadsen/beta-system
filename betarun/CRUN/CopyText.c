/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyText.c,v $, rel: %R%, date: $Date: 1992-06-08 23:55:43 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* ?? As far as I can tell, this does about the same
 * as CopyCtext with the aditional IOA checking.
 * I better check this, though.
 */

ref(ValRep) CopyText(char *theText,
		     ref(Item) theItem,
		     unsigned offset /* i ints */
		     )
{
    register ref(ValRep) theRep;
    register unsigned size, i;

    /* Allocate a ValueRepetition and initialize it with some text.    */

    size = strlen(theText);

    /* Allocate a value repetition with bodysize = Size. */
    theRep = cast(ValRep) IOAalloc(headsize(ValRep) + size*4);

    theRep->Proto = cast(ProtoType) -3;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = size;

    /* Assign the text to the body part of the repetition. */

    for (i = 0; i < size; ++i)
      theRep->Body[i] = theText[i];

    (casthandle(ValRep) theItem)[offset] = theRep;


    if (!inIOA(theItem))
      CheckReferenceAssignment((int *)theItem + offset);
}

