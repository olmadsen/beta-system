/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:4.
 * It is 4 and not 3 because of 64 bit alignment. 
 */
#define REP_OFF 4


/*void MkTO() asm("MkTO");*/

#ifdef sparc

/* Ensure that %i0 and %i1 are beta-references: rotate arguments */

asmlabel(MkTO,	        			\
	 "mov %o0,%g1;"				\
	 "mov %o1,%o0;"				\
	 "mov %o2,%o1;"				\
	 "ba _CMkTO;"                           \
	 "mov %g1,%o2;"				\
);	
void CMkTO(ref(Item) theItem,
	   unsigned offset, /* i ints */
	   char *cText)

#else

void MkTO(char *cText,
	  ref(Item) theItem,
	  unsigned offset /* i ints */ )
#endif
{
    DeclReference1(struct Item *, theText);
    GCable_Entry();
    
    Ck(theItem); Ck(BasicItem);

    /* fprintf(output, "MkTO: ");
     * fflush(output);
     * fprintf(output, 
     *         "theItem: 0x%x, offset: %d, string:  '%s'\n", 
     *         theItem, offset, cText);
     * fflush(output);
    */

#ifdef sparc
    ClearCParams(); /* OK here: is not called from RT */
    Protect(theItem, theText = CAlloI((struct Object *)BasicItem, 0, 
				      TextProto, 0, 0));
#else
    Protect(theItem, theText = CAlloI((struct Object *)BasicItem, TextProto));
#endif

    AssignReference((long *)theItem + offset, theText);
    
    /* Prepare for copying of the asciz into the repetition of the text object */
    
#ifdef sparc
    /* Avoid ClearCParams in CopyT */ 
    Protect(theText, CCopyT(theText, REP_OFF, cText)); 
#else
    Protect(theText, CopyT(cText, theText, REP_OFF)); 
#endif

    /* store range in lgth.
     * store range in pos.
     */
    ((long *)theText)[REP_OFF+1] =
      ((long *)theText)[REP_OFF+2] =
	(casthandle(ValRep)theText)[REP_OFF]->HighBorder;
}

