/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: MakeTextObj.c,v $, rel: %R%, date: $Date: 1992-07-21 17:15:17 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:3. */
#define REP_OFF 3

void MkTO() asm("MkTO");

void MkTO(char *cText,
	  ref(Item) theItem,
	  unsigned offset /* i ints */ )
{
  ref(Item) theText;

  theText = AlloI(TextProto, *BasicItemHandle);
  
  AssignReference((long *)theItem + offset, theText);

  /* Prepare for copying of the asciz into the repetition of the text object */
  
  CopyT(cText, theText, REP_OFF); 

  /* store range in lgth. TEXT ATTRIBUTE HARDCODED:16.
   * store range in pos. TEXT ATTRIBUTE HARDCODED:20.
   * (headsize(Item) + 2*sizeof(long) == 16)
   */
  theItem->Body[2] =
    theItem->Body[3] = (casthandle(ValRep)theText)[REP_OFF]->HighBorder;
}

