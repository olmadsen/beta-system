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
    struct TextObject* theText;
    unsigned long range, i, repsize;
    struct ValRep *theRep;
    
    DEBUG_CODE(NumMkTO++);

    Ck(theItem); Ck(BasicItem);
    range = strlen(asciz);

    repsize=ByteRepSize(range);

    /* LVRA missing */

    Protect(theItem, 
	    theText=(struct TextObject*)IOAcalloc(ItemSize(TextProto)+repsize, SP));

    /* The new TextObject and Repetition are now allocated */
    /* No need to call setup_item - no inlined partobjects in Text */
    theText->Proto = TextProto;
    theText->GCAttr = 1; 
    theText->Origin = BasicItem;   

    /* No need to call Gpart - the repetition will be overwritten anyway */
    AssignReference((long *)theItem + offset, (struct Item *)theText);
      
    /* Get the value repetition */
    theRep = (struct ValRep *)((long)theText+ItemSize(TextProto));
    
    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    /* Assign the text to the body part of the repetition. */
    for (i = 0; i < (repsize-headsize(ValRep))/4; i++){
      theRep->Body[i] = *((long *)asciz + i);
    }
  
    /* No need for AssignReference - both are in IOA */
    theText->T = theRep;

    /* store range in lgth and pos */
    theText->Pos = range;
    theText->Lgth = range;

    Ck(theText);
    Ck(theRep);
}

