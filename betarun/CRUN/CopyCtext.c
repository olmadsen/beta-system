/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamAscii(struct ValRep *, CopyCT)
{
  DeclReference1(struct ValRep *, theRep);
  register unsigned range, size;
  
  GCable_Entry();
  
  FetchAscii();
  
  DEBUG_CODE(NumCopyCT++);
  
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = ascii ? strlen((const char *)ascii) : 0;
  size = ByteRepSize(range);
  
  /* LVRA missing */
  theRep = cast(ValRep) IOAalloc(size);
  
  theRep->Proto = ByteRepPTValue;
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  
  if (ascii) strcpy((char *)theRep->Body, (char *)ascii);
  
  Ck(theRep);
  
#ifdef hppa
  setOriginReg(theRep);
#endif
  
  return theRep;
}
