/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* FIXME: Only allocate ONCE (like in NEWRUN) */

/* long offset of rep. within text obj. TEXT ATTRIBUTE HARDCODED:3.
 */
#define REP_OFF 3


/*void MkTO() asm("MkTO");*/

#ifdef sparc

asmlabel(MkTO,
	 "mov %o0,%o5;"	
	 "mov %o1,%o0;"	
	 /* "mov %o2,%o2;" */
         "clr %o1;"
	 "clr %o3;"
	 "ba "CPREF"MkTO;"
         "clr %o4;"
);	
void CMkTO(ref(Item) theItem,
	   int i1,
	   unsigned offset, /* i ints */
	   int i3,
	   int i4,
	   char *cText)

#else

#ifdef crts
     extern long a1, a2;
#endif

void MkTO(char *cText,
	  ref(Item) theItem,
	  unsigned offset /* i ints */ )
#endif
{
    DeclReference1(struct Item *, theText);
    GCable_Entry();
    
    DEBUG_CODE(NumMkTO++);

    Ck(theItem); Ck(BasicItem);

    /* fprintf(output, "MkTO: ");
     * fflush(output);
     * fprintf(output, 
     *         "theItem: 0x%x, offset: %d, string:  '%s'\n", 
     *         theItem, offset, cText);
     * fflush(output);
    */

#ifdef sparc
    Protect(theItem, theText = SPARC_AlloI((struct Object *)BasicItem, 0, 
				      TextProto, 0, 0));
#endif
#ifdef hppa
    Protect(theItem, theText = CAlloI((struct Object *)BasicItem, TextProto));
#endif
#ifdef crts
    *RefSP++=a1;
    *RefSP++=a2;
    Protect(theItem, theText = (struct Item *)AlloI((struct Object *)BasicItem, TextProto));
    a2 = *(--RefSP);
    a1 = *(--RefSP);
#endif

    AssignReference((long *)theItem + offset, theText);
    
    /* Prepare for copying of the asciz into the repetition of the text object */
    
#ifdef sparc
    Protect(theText, CCopyT(0, theText, REP_OFF, 0, 0, cText)); 
#else
    Protect(theText, CopyT(cText, theText, REP_OFF)); 
#endif

    /* store range in lgth.
     * store range in pos.
     */
    ((long *)theText)[REP_OFF+1] =
      ((long *)theText)[REP_OFF+2] =
	(casthandle(ValRep)theText)[REP_OFF]->HighBorder;

    Ck(theText);

}

