/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef sparc
asmlabel(CopyCT,
	 "clr %o0;"
	 "clr %o1;"
	 "clr %o3;"
	 "clr %o4;"
	 "ba "CPREF"CopyCT;"
	 "mov %l0, %o2;"
);
ref(ValRep) CCopyCT(int i0, int i1, unsigned char *textPtr)
#else
ref(ValRep) CopyCT(unsigned char *textPtr)
#endif
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned range, size, i;

    GCable_Entry();

#ifdef hppa
    textPtr = (unsigned char *) getD0Reg();
#endif

    /* Allocate a ValueRepetition and initialize it with some text.    */

    range = textPtr ? strlen(textPtr) : 0;
    size = ByteRepSize(range);

    /* LVRA missing */
    theRep = cast(ValRep) IOAalloc(size);

    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    /* Assign the text to the body part of the repetition. */

    strcpy((char *)theRep->Body, textPtr);

#ifdef hppa
    setOriginReg(theRep);
#endif

    return theRep;
}
