/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void MkTO(char *asciz,
	  Item *theItem,
	  unsigned offset /* in longs */,
	  long *SP
	  )
{
    TextObject* theText=0;
    unsigned long range, i, repsize, size;
    ValRep *theRep=0;
    
    DEBUG_CODE(NumMkTO++);

    Ck(theItem); Ck(BasicItem);
    range = strlen(asciz);
    repsize = ByteRepSize(range);

    size=ItemSize(TextProto) + repsize;
    while(1) {
      if (size > LARGE_REP_SIZE) {
	theText=(TextObject*)AOAcalloc(size);
	if (theText) {
	  /* An uninitialized value repetition is at the end of theText */
	  theRep = (ValRep *)((long)theText+ItemSize(TextProto));
	  theRep->GCAttr = DEADOBJECT;
	  SETPROTO(theRep, ByteRepPTValue);
	  theRep->LowBorder = 1;
	  theRep->HighBorder = range;
	  break;
	} 
      }
      if (!theText) {
	/* Allocate both theText and theRep in IOA */
	SaveVar(theItem);
	theText=(TextObject*)IOATryAlloc(size, SP);
	RestoreVar(theItem);
	if (theText) {
	  if (IOAMinAge!=0) {
	    theText->GCAttr = IOAMinAge;
	  }
	  /* An uninitialized value repetition is at the end of theText */
	  theRep = (ValRep *)((long)theText+ItemSize(TextProto));
	  SETPROTO(theRep, ByteRepPTValue);
	  if (IOAMinAge!=0) {
	    theRep->GCAttr = IOAMinAge;
	  }
	  theRep->LowBorder = 1;
	  theRep->HighBorder = range;
	  break;
	}
      }
    }

    /* The new TextObject and Repetition are now allocated */
    /* No need to call setup_item - no inlined partobjects in Text */
    SETPROTO(theText, TextProto);
    /* theText->GCAttr set above if in IOA */
    theText->Origin = (Object *)BasicItem;   

    /* No need to call Gpart - the repetition will be overwritten anyway */

    AssignReference((long *)theItem + offset, (Item *)theText);
      
    /* Assign the text to the body part of the repetition. */
    for (i = 0; i < (repsize-headsize(ValRep))/4; i++){
      theRep->Body[i] = *((long *)asciz + i);
    }
  
    /* No need for AssignReference. Either both theText and theRep are in IOA/AOA
     * or theText is in IOA/AOA and theRep in AOA.
     */
    theText->T = theRep;

    /* store range in lgth and pos */
    theText->Pos = range;
    theText->Lgth = range;

    Ck(theText);
    Ck(theRep);
}

