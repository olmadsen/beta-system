/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void CinitT(void)
{
    DEBUG_CODE(NumCinitT++);
    CTextPoolEnd = (char *)CTextPool;
}

char *CpkVT(struct ValRep * theRep, long *SP)
{
    long bodysize = ByteRepBodySize(theRep->HighBorder);
    long i;

    DEBUG_CODE(NumCpkVT++);
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    Ck(theRep);
    if (bodysize > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, GetThis(SP), SP);
    
    /* Copy the contents of the repetition to the CTextPool */
    for (i = 0; i < bodysize/4; ++i, CTextPoolEnd += 4)
      *((long *)CTextPoolEnd) = theRep->Body[i];

    return CTextPoolEnd - bodysize;
}

/* CCpkSVT: Copy Slice of variable text (byte rep) to C */
char *CpkSVT(struct ValRep *theRep, unsigned low, long high, long *SP)
{
    long bodysize;
    long i;
    unsigned char *oldBody;
    unsigned char *retPtr;

    DEBUG_CODE(NumCpkSVT++);

    /* printf("CCpkSVT: theRep=0x%x, low=0x%x, high=0x%x, SP=0x%x\n", theRep, low, high, SP); */
    Ck(theRep);
    if (low<theRep->LowBorder) BetaError(RepLowRangeErr, GetThis(SP), SP);
    if (high>theRep->HighBorder) BetaError(RepHighRangeErr, GetThis(SP), SP);
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = ByteRepBodySize(high);
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, GetThis(SP), SP);
    
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));

    for (i = 0;  i < high; i++, CTextPoolEnd+=1)
      *(((unsigned char *)CTextPoolEnd)) = *(unsigned char *)((unsigned)oldBody+i);
    *(((unsigned char *)CTextPoolEnd)) = 0; /* NULL termination */
    CTextPoolEnd+=1;
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

    /* The following will only work in all cases for the first
     * parameter if CTextPool is long aligned.
     * This is now ensured in data.gen.
     */

    return CTextPoolEnd - bodysize; 
}
