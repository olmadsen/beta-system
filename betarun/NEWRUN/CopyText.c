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
  struct ValRep * theRep=0;
  register unsigned range, size, i;
  
  DEBUG_CODE(NumCopyT++);

  Ck(theItem);
  range = strlen(asciz);
  size = ByteRepSize(range);
  
  if (range > LARGE_REP_SIZE) {
    /* Allocate in LVRA */
    DEBUG_LVRA(fprintf(output, "CopyT allocates in LVRA\n"));
    theRep = (struct ValRep *)LVRAAlloc(ByteRepPTValue, range);
  }
    
  if (theRep) {
    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
		       "CopyT: lvra structure ok"));
    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
    theRep->GCAttr = (long) ((long *) theItem + offset);
    *(struct ValRep **)((long *)theItem + offset) = theRep;
  } else {
    /* Allocate in IOA */
    Protect(theItem, theRep = (struct ValRep *)IOAalloc(size, SP));
    Ck(theItem);
  
    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
  }
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    theRep->Body[i] = *((long *)asciz + i);
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)theRep);
}
