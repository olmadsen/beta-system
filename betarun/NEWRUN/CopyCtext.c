/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

/* FIXME: eliminate in compiler; does the same as CopyT,
 * but the parameters are different.
 */


#include "beta.h"
#include "crun.h"

ValRep *CopyCT(unsigned char *textPtr, long *SP)
{
    ValRep *theRep;
    register unsigned range, size;

    DEBUG_CODE(NumCopyCT++);

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = textPtr ? strlen((char*)textPtr) : 0;
    size = ByteRepSize(range);

#ifdef RTDEBUG
    if (range > LARGE_REP_SIZE) {
      fprintf(output, "CopyCT: should allocate in AOA (range=%d)\n", range);
    }
    /* FIXME: Allocate in AOA
     */
#endif

    theRep = (ValRep *)IOAalloc(size, SP);

    SETPROTO(theRep, ByteRepPTValue);
    if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    /* Assign the text to the body part of the repetition. */
    if (textPtr) strcpy((char *)theRep->Body, (char*)textPtr);

    Ck(theRep);

    return theRep;
}

ValRep *CopyCT_W(unsigned char *textPtr, long *SP)
{
    ValRep *theRep;
    register unsigned range, size;

    DEBUG_CODE(NumCopyCT++);

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = textPtr ? strlen((char*)textPtr) : 0;
    size = ShortRepSize(range);

#ifdef RTDEBUG
    if (range > LARGE_REP_SIZE) {
      fprintf(output, "CopyCT_W: should allocate in AOA (range=%d)\n", range);
    }
    /* FIXME: Allocate in AOA
     */
#endif

    theRep = (ValRep *)IOAalloc(size, SP);

    SETPROTO(theRep, ShortRepPTValue);
    if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    /* Assign the text to the body part of the repetition. */
    for (i = 0; i < (size-headsize(ValRep)); i++){
      /* printf("CopyCT_W: %c\n", textPtr + i); */
      *((unsigned short*)theRep->Body[0]+i) = *(textPtr + i);
    }

    Ck(theRep);

    return theRep;
}
