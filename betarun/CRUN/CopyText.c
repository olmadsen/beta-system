/* File: CopyText.c
 * $Id: CopyText.c,v 1.1 1992-06-06 03:36:41 beta Exp $
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


    if ((long *)theItem < IOA || (long *)theItem >= IOATop)
      CheckReferenceAssignment((int *)theItem + offset);
}

