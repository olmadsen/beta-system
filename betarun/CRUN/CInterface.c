/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CInterface.c,v $, rel: %R%, date: $Date: 1992-07-20 11:46:23 $, SID: $Revision: 1.4 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* PackConstTextToC does nothing: it just hands over the asciz address */
char *CpkCT(char *asciz)
{ 
  return asciz;
}

extern void CinitT() asm("CinitT");
void CinitT(void)
{
    CTextPoolEnd = CTextPool;
}

extern char *CpkVT() asm("CpkVT");
char *CpkVT(ref(Object) theObj, handle(ValRep) theRepHandle)
{
    ref(ValRep) theRep = *theRepHandle;
    int i;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (theRep->HighBorder+1 < (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(-35, theObj);
    
    /* Copy the contents of the repetition to the CTextPool. */
    for (i = 0; i < theRep->HighBorder; ++i)
      *CTextPoolEnd++ = theRep->Body[i];

    *CTextPoolEnd++ = 0; /* C null-termination */

    return CTextPoolEnd - (theRep->HighBorder+1);
}

/*asmlabel(UnPackCText, "
	mov %i0, %o0
	call _BetaError
	mov -101, %o1
");*/

