/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: MakeTextObj.c,v $, rel: %R%, date: $Date: 1992-08-27 15:48:22 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:3. */
#define REP_OFF 3

void MkTO() asm("MkTO");

void MkTO(char *cText,
	  ref(Item) theItem,
	  unsigned offset /* i ints */ )
{
    DeclReference1(struct Item *theText);
    GCable_Entry();
    
    Ck(theItem); Ck(BasicItem);
    theText = CAlloI(BasicItem, TextProto);
    
    AssignReference((long *)theItem + offset, theText);
    
    /* Prepare for copying of the asciz into the repetition of the text object */
    
    CopyT(cText, theText, REP_OFF); 
    
    /* store range in lgth. TEXT ATTRIBUTE HARDCODED:16.
     * store range in pos. TEXT ATTRIBUTE HARDCODED:20.
     * (headsize(Item) + 2*sizeof(long) == 16)
     */
    theText->Body[2] =
      theText->Body[3] = (casthandle(ValRep)theText)[REP_OFF]->HighBorder;
}

