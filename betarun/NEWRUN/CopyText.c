/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* Allocate a ValueRepetition and initialize it with some text.    */
  
Item *CopyT(char *asciz,
		   Item *theItem,
		   unsigned offset /* in longs */, 
		   long *SP
		   )
{
  ValRep * theRep=0;
  register unsigned range, size, i;
  
  DEBUG_CODE(NumCopyT++);

  Ck(theItem);
  range = strlen(asciz);
  size = ByteRepSize(range);
  
  if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
    DEBUG_AOA(fprintf(output, "CopyT allocates in AOA\n"));
    theRep = (ValRep *)LVRAAlloc(ByteRepPTValue, range);
    *(ValRep **)((long *)theItem + offset) = theRep;
  } else {
    /* Allocate in IOA */
    push(theItem);
    theRep = (ValRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge; /* In IOA */
    pop(theItem);
  
    theRep->Proto = ByteRepPTValue;
    /* theRep->GCAttr set above */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)theItem + offset, (Item *)theRep);
  }
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    theRep->Body[i] = *((long *)asciz + i);
  }
  
  /* return the (possibly moved) item */
  Ck(theItem);
  return theItem;
}
