/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: MakeTextObj.c,v 1.10 1992-09-03 12:56:11 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:4.
 * It is 4 and not 3 because of 64 bit alignment. 
 */
#define REP_OFF 4

void MkTO() asm("MkTO");

#ifdef hppa
#  define TextProto _TextProto
#endif

void MkTO(char *cText,
	  ref(Item) theItem,
	  unsigned offset /* i ints */ )
{
    DeclReference1(struct Item *, theText);
    GCable_Entry();
    
    Ck(theItem); Ck(BasicItem);
    Protect(theItem, theText = CAlloI((struct Object *)BasicItem, TextProto));
    
    AssignReference((long *)theItem + offset, theText);
    
    /* Prepare for copying of the asciz into the repetition of the text object */
    
    Protect(theText, CopyT(cText, theText, REP_OFF)); 
    
    /* store range in lgth.
     * store range in pos.
     */
    ((long *)theText)[REP_OFF+1] =
      ((long *)theText)[REP_OFF+2] =
	(casthandle(ValRep)theText)[REP_OFF]->HighBorder;
}

