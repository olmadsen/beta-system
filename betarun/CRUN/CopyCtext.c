/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyCtext.c,v $, rel: %R%, date: $Date: 1992-06-06 03:57:23 $, SID: $Revision: 1.2 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(CopyCtext, "ba _CCopyCtext; mov %l0, %o0");

ref(ValRep) CCopyCtext(unsigned char *textPtr)
{
  register ref(ValRep) theRep;
  register unsigned size, i;

  /* Allocate a ValueRepetition and initialize it with some text.    */

  size = strlen(textPtr);

  /* LVRA ?? */
  /* Allocate a value repetition with bodysize = Size. */
  theRep = cast(ValRep) IOAalloc(headsize(ValRep) + size*4);

  theRep->Proto = cast(ProtoType) -3;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = size;

  /* Assign the text to the body part of the repetition. */

  for (i = 0; i < size; ++i)
    theRep->Body[i] = textPtr[i];

  asm("mov %0, %%i1"::"r" (theRep)); /* hack hack ?? */
  return theRep;
}


