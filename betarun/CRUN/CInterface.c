/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CInterface.c,v $, rel: %R%, date: $Date: 1992-07-23 15:04:19 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

extern void CinitT() asm("CinitT");
void CinitT(void)
{
    CTextPoolEnd = CTextPool;
}

extern char *CpkVT() asm("CpkVT");
char *CpkVT(ref(Object) theObj, handle(ValRep) theRepHandle)
{
    ref(ValRep) theRep = *theRepHandle;
    long bodysize = ByteRepBodySize(theRep->HighBorder);
    long i;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize > (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(-35, theObj);
    
    /* Copy the contents of the repetition to the CTextPool. */
    for (i = 0; i < bodysize/4; ++i)
      *((long *)CTextPoolEnd)++ = theRep->Body[i];

    return CTextPoolEnd - bodysize;
}
