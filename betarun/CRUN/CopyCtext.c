/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ParamAscii(ValRep *, CopyCT)
{
  DeclReference1(ValRep *, theRep);
  register unsigned range, size;
  
  FetchAscii();
  
  DEBUG_CODE(NumCopyCT++);
  
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = ascii ? strlen((const char *)ascii) : 0;
  size = ByteRepSize(range);
  
  theRep = (ValRep *) IOAalloc(size);
  
  SETPROTO(theRep,ByteRepPTValue);
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

ParamAscii(ValRep *, CopyCT_W)
{
  DeclReference1(ValRep *, theRep);
  register unsigned range, size;
  int i;
  
  FetchAscii();
  
  DEBUG_CODE(NumCopyCT++);
  
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = ascii ? strlen((const char *)ascii) : 0;
  size = ShortRepSize(range);
  
  theRep = (ValRep *) IOAalloc(size);
  
  SETPROTO(theRep,ShortRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep)); i++){
    /* printf("CopyCT_W: %c\n", ascii + i); */
    *((unsigned short*)theRep->Body[0]+i) = *(ascii + i);
  }
  
  Ck(theRep);
  
#ifdef hppa
  setOriginReg(theRep);
#endif
  
  return theRep;
}
