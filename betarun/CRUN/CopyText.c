/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopyText.c,v 1.14 1993-02-19 09:40:32 datpete Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef sparc
/* Ensure that %i0 and %i1 are beta-references: rotate arguments */
asmlabel(CopyT,
	 "clr [%sp+0x6c];" /* ClearCParams */
	 "clr [%sp+0x68];"
	 "clr [%sp+0x64];"
	 "clr [%sp+0x60];"
	 "clr [%sp+0x5c];"
	 "clr [%sp+0x58];"
	 "clr [%sp+0x54];"
	 "clr [%sp+0x50];"
	 "clr [%sp+0x4c];"
	 "clr [%sp+0x48];"
	 "clr [%sp+0x44];"
	 "clr [%sp+0x40];"
	 "mov %o0,%g1;"	
	 "mov %o1,%o0;"
	 "mov %o2,%o1;"
	 "ba _CCopyT;"
         "mov %g1,%o2;"
         );	
void CCopyT(ref(Item) theItem,
	    unsigned offset, /* i ints */
	    char *asciz
           )
#else
void CopyT(char *asciz,
	   ref(Item) theItem,
	   unsigned offset /* i ints */
	   )
#endif
{
  DeclReference1(struct ValRep *, theRep);
  register unsigned range, size, i;
  
  GCable_Entry();
  
  Ck(theItem);
  /* Allocate a ValueRepetition and initialize it with some text.    */
  
  range = strlen(asciz);
  
  /* LVRA missing */
  
  /* Allocate a value repetition */
  size = ByteRepSize(range);

  Protect(theItem, theRep = cast(ValRep) IOAalloc(size));
  
  Ck(theItem);
  
  theRep->Proto = ByteRepPTValue;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  /* Assign the text to the body part of the repetition. */
  
  for (i = 0; i < (size-headsize(ValRep))/4; i++){
    /* printf("CopyT: %.4s\n", (long *)asciz + i); */
    theRep->Body[i] = *((long *)asciz + i);
  }
  
  AssignReference((long *)theItem + offset, cast(Item) theRep);
}
