/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyText.c,v $, rel: %R%, date: $Date: 1992-07-23 15:06:35 $, SID: $Revision: 1.7 $
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
    register unsigned range, size, i;

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = strlen(asciz);

    /* Allocate a value repetition */
    size = ByteRepSize(range);
    theRep = cast(ValRep) IOAalloc(size);

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
