/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* Allocate a ValueRepetition and initialize it with some text.    */
  
struct Item *CopyT(char *asciz,
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
    /* Allocate in IOA/AOA */
    push(theItem);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopyT allocates in AOA\n"));
      theRep = (struct ValRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAalloc failed\n"));
    }
    if (theRep) {
      theRep->GCAttr = 0; /* In AOA */
    } else {
      theRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theItem);
  
    theRep->Proto = ByteRepPTValue;
    /* theRep->GCAttr set above */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
  }
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    theRep->Body[i] = *((long *)asciz + i);
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)theRep);

  /* return the (possibly moved) item */
  Ck(theItem);
  return theItem;
}
