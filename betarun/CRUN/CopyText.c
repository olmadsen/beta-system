/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyText.c,v $, rel: %R%, date: $Date: 1992-08-19 15:44:48 $, SID: $Revision: 1.8 $
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
    register unsigned range, size, i;

    GCable_Entry

#define theRep (cast(ValRep) GCreg3)

      Ck(theItem);
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
