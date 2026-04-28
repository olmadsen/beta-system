/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ParamItemAscii(Item *, CopyT)
{
  DeclReference1(ValRep *, theRep);
  register unsigned range, size, i;
  
  DEBUG_CODE(NumCopyT++);

  Ck(theItem);
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = strlen(ascii);
  
  /* Allocate a value repetition */
  size = ByteRepSize(range);

  Protect(theItem, theRep = (ValRep *) IOAalloc(size));
  
  SETPROTO(theRep,ByteRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    /* printf("CopyT: %.4s\n", (long *)ascii + i); */
    theRep->Body[i] = *((long *)ascii + i);
  }
  
  AssignReference((long *)theItem + offset, (Item *) theRep);

  /* return the (possibly moved) item */
  return theItem;

}

ParamItemAscii(Item *, CopyT_W)
{
  DeclReference1(ValRep *, theRep);
  register unsigned range, size, i;
  
  DEBUG_CODE(NumCopyT++);

  Ck(theItem);
  /* Allocate a ShortRepetition and initialize it with some wide text.    */
  
  range = strlen(ascii);
  
  /* Allocate a value repetition */
  size = ShortRepSize(range);

  Protect(theItem, theRep = (ValRep *) IOAalloc(size));
  
  SETPROTO(theRep,ShortRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  
  for (i = 0; i < (size-headsize(ValRep)); i++){
    /* printf("CopyT_W: %c\n", ascii + i); */
    *((unsigned short*)theRep->Body[0]+i) = *(ascii + i);
  }
  
  AssignReference((long *)theItem + offset, (Item *) theRep);

  /* return the (possibly moved) item */
  return theItem;

}
