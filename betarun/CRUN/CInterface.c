/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void CinitT(void)
{
    CTextPoolEnd = (char *)CTextPool;
}

#ifndef MAC
asmlabel(CpkVT, "
	mov %o0, %o1
        ba "CPREF"CpkVT
	mov %i0, %o0
");
#endif

char *
#ifdef sparc
      CCpkVT(ref(Object) currentObj, ref(ValRep) theRep)
#endif
#ifdef hppa
      CpkVT(ref(ValRep) theRep)
#endif
#ifdef crts
      CpkVT(struct Object *currentObj, ref(ValRep) theRep)
#endif
{
    long bodysize = ByteRepBodySize(theRep->HighBorder);
    long i;

#ifdef hppa
    ref(Object) currentObj;
    currentObj = cast(Object) getThisReg();
#endif

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    Ck(currentObj); Ck(theRep);
    if (bodysize > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, currentObj);
    
    /* Copy the contents of the repetition to the CTextPool */
    for (i = 0; i < bodysize/4; ++i)
      *((long *)CTextPoolEnd)++ = theRep->Body[i];

    return CTextPoolEnd - bodysize;
}

#ifndef MAC
asmlabel(CpkSVT, "
	mov %o2, %o3
	mov %o1, %o2
	mov %o0, %o1
        ba "CPREF"CpkSVT
	mov %i0, %o0
");
#endif

/* CCpkSVT: Copy Slice of variable text (byte rep) to C */
char *
#ifdef sparc
      CCpkSVT(ref(Object) currentObj, ref(ValRep) theRep, unsigned low,
	      long high)
#endif
#ifdef hppa
      CpkSVT(ref(ValRep) theRep, unsigned low, long high)
#endif
#ifdef crts
      CpkSVT(struct Object *currentObj, ref(ValRep) theRep, unsigned low, long high)
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
    if (low<theRep->LowBorder) 
      BetaError(RepLowRangeErr, currentObj);
    if (high>theRep->HighBorder) 
      BetaError(RepHighRangeErr, currentObj);
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = ByteRepBodySize(high);
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, currentObj);
    
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
    for (i = 0;  i < high; i+=1)
      *(((unsigned char *)CTextPoolEnd))++ = *(unsigned char *)((unsigned)oldBody+i);
    *(((unsigned char *)CTextPoolEnd))++ = 0; /* NULL termination */
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

#ifdef hppa
    asm volatile ("COPY %0,%%r26" : /* no out */ 
		  : "r" (CTextPoolEnd - bodysize) : "r26");
#endif

    /* The following will only work in all cases for the first
     * parameter if CTextPool is long aligned.
     * See CInitT and data.gen
     */

    return CTextPoolEnd - bodysize; 
}

#ifdef MAC
unsigned char * PpkVT(struct Object *currentObj, ref(ValRep) theRep)
{
    long bodysize = theRep->HighBorder;
    long i;
    unsigned char *oldBody,*res;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    Ck(currentObj); Ck(theRep);
    if (bodysize+1 > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, currentObj);
    
	res=(unsigned char *)CTextPoolEnd;
	/* Set the first byte in the pascal string eq the length */
	*((unsigned char *)CTextPoolEnd)++ = (char)bodysize;
    
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (unsigned char *)((unsigned)theRep->Body);
    for (i = 0;  i < bodysize; i+=1)
      *(((unsigned char *)CTextPoolEnd))++ = *(unsigned char *)((unsigned)oldBody+i);
	  
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

    return res;
}

unsigned char * PpkSVT(struct Object *currentObj, ref(ValRep) theRep, unsigned low, long high)
{
    long bodysize;
    long i;
    unsigned char *oldBody,*res;

    Ck(currentObj); Ck(theRep);
    if (low<theRep->LowBorder) BetaError(RepLowRangeErr, currentObj);
    if (high>theRep->HighBorder) BetaError(RepHighRangeErr, currentObj);
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = high;
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize+1 > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, currentObj);
    
	res=(unsigned char *)CTextPoolEnd;
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));

	/* Set the first byte in the pascal string eq the length */
	*((unsigned char *)CTextPoolEnd)++ = (char)high;

    for (i = 0;  i < high; i+=1)
      *(((unsigned char *)CTextPoolEnd))++ = *(unsigned char *)((unsigned)oldBody+i);
	  
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

    return res;
}

unsigned char * PpkCT(struct Object *currentObj, char *text)
{
    long bodysize = strlen(text);
    unsigned char *res;
    long i;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    if (bodysize+1 > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, currentObj);
    
	res=(unsigned char *)CTextPoolEnd;
	/* Set the first byte in the pascal string eq the length */
	*((char *)CTextPoolEnd)++ = (char)bodysize;
    
	/* Copy the contents of the repetition to the CTextPool. */
    for (i = 0; i < bodysize; ++i)
      *((char *)CTextPoolEnd)++ = text++;
	  
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

    return res;
}


#endif
