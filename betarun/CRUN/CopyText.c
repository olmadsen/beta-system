/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyText.c,v $, rel: %R%, date: $Date: 1992-07-20 11:47:28 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(ValRep) CopyT(char *asciz,
		  ref(Item) theItem,
		  unsigned offset /* i ints */
		  )
{
    register ref(ValRep) theRep;
    register unsigned range, bodysize, i;

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = strlen(asciz);

    /* Allocate a value repetition with bodysize = ((range+1+3)/4)*4. */
    bodysize = ((range+4)/4)*4;
    theRep = cast(ValRep) IOAalloc(headsize(ValRep) + bodysize);

    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    /* Assign the text to the body part of the repetition. */

    for (i = 0; i < bodysize; ++i)
      theRep->Body[i] = asciz[i];

    (casthandle(ValRep) theItem)[offset] = theRep;

    if (!inIOA((int *)theItem + offset))
      ChkRA((int *)theItem + offset);
}
