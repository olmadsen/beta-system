/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyCtext.c,v $, rel: %R%, date: $Date: 1992-08-27 15:45:40 $, SID: $Revision: 1.10 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(CopyCT, "ba _CCopyCT; mov %l0, %o0");

ref(ValRep) CCopyCT(unsigned char *textPtr)
{
    DeclReference1(struct ValRep *theRep);
    register unsigned range, size, i;

    GCable_Entry();

      /* Allocate a ValueRepetition and initialize it with some text.    */

    range = strlen(textPtr);
    size = ByteRepSize(range);

    /* LVRA ?? */
    theRep = cast(ValRep) IOAalloc(size);

    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    /* Assign the text to the body part of the repetition. */

    for (i = 0; i < (size-headsize(ValRep)); i++) {
	theRep->Body[i] = *((long *)textPtr + i);
    }

    /* hack hack. Olm wants the result in %i2 */
    __asm__("ret;restore %0, 0, %%i2"::"r" (theRep));

    return theRep; /* dummy, keeps gcc happy */
}


