/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyText.c,v $, rel: %R%, date: $Date: 1992-07-21 17:17:47 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

extern void CopyText() asm("CopyText"); /* Alias */
void CopyText(handle(Object) theObjHandle)
{
  CopyT(theObjHandle);
}

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

    AssignReference((long *)theItem + offset, cast(Item) theRep);
}
