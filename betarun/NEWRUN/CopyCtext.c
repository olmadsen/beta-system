/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

/* FIXME: eliminate in compiler; does the same as CopyT,
 * but the parameters are different.
 */


#include "beta.h"
#include "crun.h"

ValRep *CopyCT(unsigned char *asciz, long *SP)
{
    ValRep *theRep = NULL;
    register unsigned range, size;

    DEBUG_CODE(NumCopyCT++);

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = asciz ? strlen((char*)asciz) : 0;
    size = ByteRepSize(range);

    do {
        if (range > LARGE_REP_SIZE) {
            theRep = (ValRep *)LVRAAlloc(ByteRepPTValue, range);
        }

        if (!theRep) {
            theRep = (ValRep *)IOATryAlloc(size, SP);
            if (theRep) {
                SETPROTO(theRep, ByteRepPTValue);
                if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
                theRep->LowBorder = 1;
                theRep->HighBorder = range;
            }
        }
    } while (!theRep);
    
    /* Assign the text to the body part of the repetition. */
    if (asciz) strcpy((char *)theRep->Body, (char*)asciz);

    Ck(theRep);

    return theRep;
}

ValRep *CopyCT_W(unsigned char *asciz, long *SP)
{
    ValRep *theRep = NULL;
    register unsigned range, size;
    int i;

    DEBUG_CODE(NumCopyCT++);

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = asciz ? strlen((char*)asciz) : 0;
    size = ShortRepSize(range);

    do {
        if (range > LARGE_REP_SIZE) {
            theRep = (ValRep *)LVRAAlloc(ShortRepPTValue, range);
        }

        if (!theRep) {
            theRep = (ValRep *)IOATryAlloc(size, SP);
            if (theRep) {
                SETPROTO(theRep, ShortRepPTValue);
                if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
                theRep->LowBorder = 1;
                theRep->HighBorder = range;
            }
        }
    } while (!theRep);


    /* Assign the text to the body part of the repetition. */
    for (i = 0; i < (size-headsize(ValRep)); i++){
      /* printf("CopyCT_W: %c\n", asciz + i); */
      *((unsigned short*)theRep->Body[0]+i) = *(asciz + i);
    }

    Ck(theRep);

    return theRep;
}
