/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

struct ValRep *CopyCT(unsigned char *textPtr, long *SP)
{
    struct ValRep *theRep;
    register unsigned range, size;

    DEBUG_CODE(NumCopyCT++);

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = textPtr ? strlen(textPtr) : 0;
    size = ByteRepSize(range);

    /* LVRA missing */
    theRep = (struct ValRep *)IOAalloc(size, SP);

    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    /* Assign the text to the body part of the repetition. */
    strcpy((char *)theRep->Body, textPtr);

    Ck(theRep);

    return theRep;
}
