/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: CInterface.c, rel: 1, date: 7/24/92, SID: 1.7
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

extern void CinitT() asm("CinitT");
void CinitT(void)
{
    CTextPoolEnd = CTextPool;
}

asmlabel(CpkVT, "
	mov %o0, %o1
        ba _CCpkVT
	mov %i0, %o0
");

char *CCpkVT(ref(Object) theObj, ref(ValRep) theRep)
{
    long bodysize = ByteRepBodySize(theRep->HighBorder);
    long i;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    Ck(theObj); Ck(theRep);
    if (bodysize > (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(-35, theObj);
    
    /* Copy the contents of the repetition to the CTextPool. */
    for (i = 0; i < bodysize/4; ++i)
      *((long *)CTextPoolEnd)++ = theRep->Body[i];

    return CTextPoolEnd - bodysize;
}

/* Temporary alias */
asmlabel(CpkVTS, "
	mov %o2, %o3
	mov %o1, %o2
	mov %o0, %o1
        ba _CCpkSVT
	mov %i0, %o0
");

asmlabel(CpkSVT, "
	mov %o2, %o3
	mov %o1, %o2
	mov %o0, %o1
        ba _CCpkSVT
	mov %i0, %o0
");

/* CCpkSVT: Copy Slice of variable text (byte rep) to C */
char *CCpkSVT(ref(Object) currentObj, ref(ValRep) theRep, unsigned low, unsigned high)
{
    long bodysize;
    long i;
    unsigned char *oldBody;

    Ck(currentObj); Ck(theRep);
    if (low<theRep->LowBorder) BetaError(-6, currentObj);
    if (high<theRep->LowBorder) BetaError(-7, currentObj);
    if (low>theRep->HighBorder) BetaError(-6, currentObj);
    if (high>theRep->HighBorder) BetaError(-7, currentObj);
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = ByteRepBodySize(high);
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize > (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(-35, currentObj);
    
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
    for (i = 0;  i < high; i+=1)
      *(((unsigned char *)CTextPoolEnd)++) = *(unsigned char *)((unsigned)oldBody+i);
    *(((unsigned char *)CTextPoolEnd)++) = 0; /* NULL termination */
    (long)CTextPoolEnd = (((long)CTextPoolEnd+3)/4)*4; /* long align next text */

    return CTextPoolEnd - bodysize;
}
