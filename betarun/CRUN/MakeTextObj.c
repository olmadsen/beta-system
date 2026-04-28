/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT
/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:3. */
#define REP_OFF 3

#ifdef sparc
asmlabel(MkTO,
	 "mov %o0,%o5;"	       /* asciz */
	 "mov %o1,%o0;"	       /* theItem */
	 /* "mov %o2,%o2;" */  /* offset already in place */
         "clr %o1;"
	 "clr %o3;"
	 "ba "CPREF"MkTO;"
         "clr %o4;"
);	
void CMkTO(Item * theItem,
	   int i1,
	   unsigned offset, /* i ints */
	   int i3,
	   int i4,
	   char *asciz)
#endif /* sparc */

#ifdef hppa
void MkTO(char *asciz,
	  Item * theItem,
	  unsigned offset /* i ints */ )
#endif /* hppa */

{
    TextObject* theText;
    unsigned long range, i, repsize, size;
    ValRep *theRep;

    DEBUG_CODE(NumMkTO++);

    Ck(theItem); Ck(BasicItem);
    range = strlen(asciz);
    repsize = ByteRepSize(range);

    if (range > LARGE_REP_SIZE) {
      theRep = (ValRep *)LVRAAlloc(ByteRepPTValue, range);
      /* theRep is now allocated, and the header of it is initialized */
      size = ItemSize(TextProto);
      theText=(TextObject*)AOAcalloc(size);
    } else {
      /* Allocate both theText and theRep in IOA */
      size=ItemSize(TextProto) + repsize;

      /* Allocate in IOA/AOA */
      SaveVar(theItem);
      if (size>IOAMAXSIZE) {
        DEBUG_AOA(fprintf(output, "MkTO allocates in AOA\n"));
        theText=(TextObject*)AOAcalloc(size);
      } else {
        theText=(TextObject*)IOAalloc(size);
        if (IOAMinAge!=0) {
          theText->GCAttr = IOAMinAge;
        }
      }
      RestoreVar(theItem);
      /* An uninitialized value repetition is at the end of theText */
      theRep = (ValRep *)((long)theText+ItemSize(TextProto));
      SETPROTO(theRep,ByteRepPTValue);
      if (IOAMinAge!=0) {
        theRep->GCAttr = IOAMinAge;
      }
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
    }

    /* The new TextObject and Repetition are now allocated */
    /* No need to call setup_item - no inlined partobjects in Text */
    SETPROTO(theText,TextProto);
    /* theText->GCAttr set above if in IOA */
    theText->Origin = (Object *)BasicItem;   

    /* No need to call Gpart - the repetition will be overwritten anyway */

    AssignReference((long *)theItem + offset, (Item *)theText);
      
    /* Assign the text to the body part of the repetition. */
    for (i = 0; i < (repsize-headsize(ValRep))/4; i++){
      theRep->Body[i] = *((long *)asciz + i);
    }
  
    /* No need for AssignReference. 
     * theText and theRep are in the same heap.
     */
    theText->T = theRep;

    /* store range in lgth and pos */
    theText->Pos = range;
    theText->Lgth = range;

    Ck(theText);
    Ck(theRep);
}

#endif /* MT */
