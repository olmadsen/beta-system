/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void MkTO(char *asciz,
	  struct Item *theItem,
	  unsigned offset /* in longs */,
	  long *SP
	  )
{
    struct TextObject* theText=0;
    unsigned long range, i, repsize, size, isInAOA;
    struct ValRep *theRep=0;
    
    DEBUG_CODE(NumMkTO++);

    Ck(theItem); Ck(BasicItem);
    range = strlen(asciz);
    repsize = ByteRepSize(range);

    if (range > LARGE_REP_SIZE) {
      DEBUG_LVRA(fprintf(output, "MkTO allocates in LVRA\n"));
      theRep = (struct ValRep *)LVRAAlloc(ByteRepPTValue, range);
    }

    if (theRep) {
      DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
		       "MkTO: lvra structure ok"));
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      theRep->GCAttr = (long) ((long *) theItem + offset);
      *(struct ValRep **)((long *)theItem + offset) = theRep;
      /* theRep is now allocated, and the header of it is initialized */
      
      /* Allocate only theText in IOA */
      size = ItemSize(TextProto);
    } else {
      /* Allocate both theText and theRep in IOA */
      size=ItemSize(TextProto) + repsize;
    }

    /* Allocate in IOA/AOA */
    push(theItem);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "MkTO allocates in AOA\n"));
      theText=(struct TextObject*)AOAcalloc(size, SP);
      DEBUG_AOA(if (!theText) fprintf(output, "AOAcalloc failed\n"));
    }
    if (theText) {
      isInAOA=1;
    } else {
      isInAOA=0;
      theText=(struct TextObject*)IOAcalloc(size, SP);
      theText->GCAttr = 1;
    }
    pop(theItem);

    /* The new TextObject and Repetition are now allocated */
    /* No need to call setup_item - no inlined partobjects in Text */
    theText->Proto = TextProto;
    /* theText->GCAttr set above if in IOA */
    theText->Origin = (struct Object *)BasicItem;   

    /* No need to call Gpart - the repetition will be overwritten anyway */

    AssignReference((long *)theItem + offset, (struct Item *)theText);
      
    if (!theRep){
      /* An uninitialized value repetition is at the end of theText */
      theRep = (struct ValRep *)((long)theText+ItemSize(TextProto));
      theRep->Proto = ByteRepPTValue;
      if (!isInAOA) theRep->GCAttr = 1;
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
    }
    
    /* Assign the text to the body part of the repetition. */
    for (i = 0; i < (repsize-headsize(ValRep))/4; i++){
      theRep->Body[i] = *((long *)asciz + i);
    }
  
    /* No need for AssignReference. Either both theText and theRep are in IOA/AOA
     * or theText is in IOA/AOA and theRep in LVRA.
     */
    theText->T = theRep;

    /* store range in lgth and pos */
    theText->Pos = range;
    theText->Lgth = range;

    Ck(theText);
    Ck(theRep);
}

