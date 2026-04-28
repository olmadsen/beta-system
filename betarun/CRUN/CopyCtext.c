/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ParamAsciz(ValRep *, CopyCT)
{
  DeclReference1(ValRep *, theRep);
  register unsigned range, size;
  
  FetchAsciz();
  
  DEBUG_CODE(NumCopyCT++);
  
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = asciz ? strlen((char*)asciz) : 0;
  size = ByteRepSize(range);
  theRep = NULL;

  do {
      if (range > LARGE_REP_SIZE) {
          theRep = (ValRep *)LVRAAlloc(ByteRepPTValue, range);
      }
      
      if (!theRep) {
          theRep = (ValRep *)IOATryAlloc(size);
          if (theRep) {
              SETPROTO(theRep, ByteRepPTValue);
              if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
              theRep->LowBorder = 1;
              theRep->HighBorder = range;
          }
      }
  } while (!theRep);
  
  /* Assign the text to the body part of the repetition. */
  
  if (asciz) strcpy((char *)theRep->Body, (char *)asciz);
  
  Ck(theRep);
  
#ifdef hppa
  setOriginReg(theRep);
#endif
  
  return theRep;
}

ParamAsciz(ValRep *, CopyCT_W)
{
  DeclReference1(ValRep *, theRep);
  register unsigned range, size;
  int i;
  
  FetchAsciz();
  
  DEBUG_CODE(NumCopyCT++);
  
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = asciz ? strlen((const char *)asciz) : 0;
  size = ShortRepSize(range);
  theRep = NULL;

  do {
      if (range > LARGE_REP_SIZE) {
          theRep = (ValRep *)LVRAAlloc(ShortRepPTValue, range);
      }
      
      if (!theRep) {
          theRep = (ValRep *)IOATryAlloc(size);
          if (theRep) {
              SETPROTO(theRep, ShortRepPTValue);
              if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
              theRep->LowBorder = 1;
              theRep->HighBorder = range;
          }
      }
  } while (!theRep);
  
  /* Assign the text to the body part of the repetition. */
  for (i = 0; i < (size-headsize(ValRep)); i++){
    /* printf("CopyCT_W: %c\n", asciz + i); */
    *((unsigned short*)theRep->Body[0]+i) = *(asciz + i);
  }
  
  Ck(theRep);
  
#ifdef hppa
  setOriginReg(theRep);
#endif
  
  return theRep;
}
