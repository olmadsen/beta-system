/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
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
  
  while (1) {
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      DEBUG_AOA(fprintf(output, "CopyT allocates in AOA\n"));
      theRep = (ValRep *)LVRAAlloc(ByteRepPTValue, range);
      if (theRep) {
	*(ValRep **)((long *)theItem + offset) = theRep;
	break;
      }
    } 

    /* Allocate in IOA */
    push(theItem);
    theRep = (ValRep *)IOATryAlloc(size, SP);
    pop(theItem);
    if (theRep) {
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge; /* In IOA */
    
      SETPROTO(theRep, ByteRepPTValue);
      /* theRep->GCAttr set above */
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
    
      AssignReference((long *)theItem + offset, (Item *)theRep);
      break;
    }
  }  
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    theRep->Body[i] = *((long *)asciz + i);
  }
  
  /* return the (possibly moved) item */
  Ck(theItem);
  return theItem;
}

Item *CopyT_W(char *asciz,
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
  size = ShortRepSize(range);
  
  while (1) {
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      DEBUG_AOA(fprintf(output, "CopyT_W allocates in AOA\n"));
      theRep = (ValRep *)LVRAAlloc(ShortRepPTValue, range);
      if (theRep) {
	*(ValRep **)((long *)theItem + offset) = theRep;
	break;
      }
    } 

    /* Allocate in IOA */
    push(theItem);
    theRep = (ValRep *)IOATryAlloc(size, SP);
    pop(theItem);
    if (theRep) {
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge; /* In IOA */
    
      SETPROTO(theRep, ShortRepPTValue);
      /* theRep->GCAttr set above */
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
    
      AssignReference((long *)theItem + offset, (Item *)theRep);
      break;
    }
  }  
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep)); i++){
    /* printf("CopyT_W: %c\n", asciz + i); */
    *((unsigned short*)theRep->Body[0]+i) = *(asciz + i);
  }
  
  /* return the (possibly moved) item */
  Ck(theItem);
  return theItem;
}
