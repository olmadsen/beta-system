/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamItemAscii(struct Item *, CopyT)
{
  DeclReference1(struct ValRep *, theRep);
  register unsigned range, size, i;
  
  GCable_Entry();
  
  DEBUG_CODE(NumCopyT++);

  Ck(theItem);
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = strlen(ascii);
  
  /* LVRA missing */
  
  /* Allocate a value repetition */
  size = ByteRepSize(range);

  Protect(theItem, theRep = cast(ValRep) IOAalloc(size));
  
  theRep->Proto = ByteRepPTValue;
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    /* printf("CopyT: %.4s\n", (long *)ascii + i); */
    theRep->Body[i] = *((long *)ascii + i);
  }
  
  AssignReference((long *)theItem + offset, cast(Item) theRep);

  /* return the (possibly moved) item */
  return theItem;

}
