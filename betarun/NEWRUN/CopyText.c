/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* Allocate a ValueRepetition and initialize it with some text.    */
  
void CopyT(char *asciz,
	   struct Item *theItem,
	   unsigned offset /* in longs */, 
	   long *SP
	   )
{
  struct ValRep * theRep;
  register unsigned range, size, i;
  
  DEBUG_CODE(NumCopyT++);

  Ck(theItem);
  range = strlen(asciz);
  
  /* LVRA missing */
  
  /* Allocate a value repetition */
  size = ByteRepSize(range);

  Protect(theItem, theRep = (struct ValRep *)IOAalloc(size, SP));
  
  Ck(theItem);
  
  theRep->Proto = ByteRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    theRep->Body[i] = *((long *)asciz + i);
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)theRep);
}
