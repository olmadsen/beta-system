/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyCtext.c,v $, rel: %R%, date: $Date: 1992-07-23 15:05:35 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(CopyCT, "ba _CCopyCT; mov %l0, %o0");

ref(ValRep) CCopyCT(unsigned char *textPtr)
{
  register ref(ValRep) theRep;
  register unsigned range, size, i;

  /* Allocate a ValueRepetition and initialize it with some text.    */

  range = strlen(textPtr);
  size = ByteRepSize(range);

  /* LVRA ?? */
  theRep = cast(ValRep) IOAalloc(size);

  theRep->Proto = ValRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;

  /* Assign the text to the body part of the repetition. */

  for (i = 0; i < (size-headsize(ValRep)); i++){
    theRep->Body[i] = *((long *)textPtr + i);
  }

  asm("mov %0, %%i1"::"r" (theRep)); /* hack hack. Olm wants the
				        result in %o1 */
  return theRep;
}


