/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: MakeTextObj.c,v $, rel: %R%, date: $Date: 1992-06-16 23:47:56 $, SID: $Revision: 1.1 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:3. */
#define REP_OFF 3

void mkTextObj(char *cText,
	       ref(Item) theItem,
	       unsigned offset /* i ints */ )
{
  ref(Item) theText;

  theText = AllocateItem(TextProto, *BasicItemHandle);
  
  (casthandle(Item)theItem)[offset] = theText;

  if (!inIOA(theItem))
    CheckReferenceAssignment(casthandle(Item)theItem + offset);

  /* Prepare for copying of the asciz into the repetition of the text object */
  
  CopyText(cText, theText, REP_OFF); 

  /* store range in lgth. TEXT ATTRIBUTE HARDCODED:16.
     store range in pos. TEXT ATTRIBUTE HARDCODED:20.
     (headsize(Item) + 2*sizeof(long) == 16) */
  theItem->Body[2] =
    theItem->Body[3] = (casthandle(ValRep)theText)[REP_OFF]->HighBorder;
}

