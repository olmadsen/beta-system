/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CInterface.c,v 1.16 1992-09-24 10:38:39 datpete Exp $
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

char *
#ifdef sparc
      CCpkVT(ref(Object) theObj, ref(ValRep) theRep)
#else
       CpkVT(ref(ValRep) theRep)
#endif
{
    long bodysize = ByteRepBodySize(theRep->HighBorder);
    long i;

#ifdef hppa
    ref(Object) theObj;
    theObj = cast(Object) getThisReg();
#endif

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
char *
#ifdef sparc
      CCpkSVT(ref(Object) currentObj, ref(ValRep) theRep, unsigned low,
	      int high)
#else
       CpkVTS(ref(ValRep) theRep, unsigned low, int high)
#endif
{
    long bodysize;
    long i;
    unsigned char *oldBody;
#ifdef hppa
    ref(Object) currentObj;
    currentObj = cast(Object) getThisReg();
#endif

    Ck(currentObj); Ck(theRep);
    if (low<theRep->LowBorder) BetaError(-6, currentObj);
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

#ifdef hppa
    asm volatile ("COPY %0,%%r26" : /* no out */ 
		  : "r" (CTextPoolEnd - bodysize) : "r26");
#endif
    return CTextPoolEnd - bodysize;
}
