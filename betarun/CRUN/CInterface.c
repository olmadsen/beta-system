/* File: CInterface.c
 * $Id: CInterface.c,v 1.1 1992-06-06 03:36:36 beta Exp $
 */

/* PackConstTextToC does nothing ?? */
extern void InitCprocText() asm("InitCprocText");

void InitCprocText(void)
{
    CTextPoolEnd = CTextPool;
}

extern char *PackVarTextToC() asm("PackVarTextToC");

char *PackVarTextToC(ref(Object) theObj, handle(ValRep) theRepHandle)
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

asmlabel(UnPackCText, "
	mov %i0, %o0
	call _BetaError
	mov -101, %o1
");

