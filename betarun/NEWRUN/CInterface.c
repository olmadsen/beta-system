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
      BetaError(CTextPoolErr, GetThis(SP), SP, 0);
    
    /* Copy the contents of the repetition to the CTextPool */
    for (i = 0; i < bodysize/4; ++i, CTextPoolEnd += 4)
      *((long *)CTextPoolEnd) = theRep->Body[i];

    return CTextPoolEnd - bodysize;
}

/* CpkSVT: Copy Slice of variable text (byte rep) to C */
char *CpkSVT(struct ValRep *theRep, unsigned low, long high, long *SP)
{
    long bodysize;
    long i;
    unsigned char *oldBody;

    DEBUG_CODE(NumCpkSVT++);

    /* printf("CpkSVT: theRep=0x%x, low=0x%x, high=0x%x, SP=0x%x\n", theRep, low, high, SP); */
    Ck(theRep);
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, GetThis(SP), SP, 0);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
      BetaError(RepHighRangeErr, GetThis(SP), SP, 0);
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = ByteRepBodySize(high);
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, GetThis(SP), SP, 0);
    
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


#ifdef MAC

char * PpkVT(ref(ValRep) theRep, long *SP)
{
    long bodysize = ByteRepBodySize(theRep->HighBorder);
    long i;
    char *oldBody,*res;

    DEBUG_CODE(NumPpkVT++);
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    Ck(theRep);
    if (bodysize+1 > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, GetThis(SP), SP, 0);
    
	res=(char *)CTextPoolEnd;
	/* Set the first byte in the pascal string eq the length */
	*((char *)CTextPoolEnd)++ = (char)theRep->HighBorder;
    
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (char *)(theRep->Body);
    for (i = 0;  i < bodysize; i++)
      *(((char *)CTextPoolEnd))++ = *(char *)((long)oldBody+i);
	  
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */
	
#if 0
	fprintf(output, "PpkVT: returning pascal string at address 0x%x with length %d\n", res, *(char*)res);
	fprintf(output, "Characters:\n");
	for (i=0; i<(unsigned)*(char*)res; i++){
		fprintf(output, "0x%x\t'%c'\n", (unsigned)*((char*)res+i+1), *((char*)res+i+1));
	}
	fflush(output);
#endif

    return res;
}

char * PpkSVT(struct ValRep *theRep, unsigned low, long high, long *SP)
{
    long bodysize;
    long i;
    char *oldBody,*res;

    /* printf("PpkSVT: theRep=0x%x, low=0x%x, high=0x%x, SP=0x%x\n", theRep, low, high, SP); */
    Ck(theRep);
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, GetThis(SP), SP, 0);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
      BetaError(RepHighRangeErr, GetThis(SP), SP, 0);
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = ByteRepBodySize(high);
     /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    if (bodysize+1 > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, GetThis(SP), SP, 0);
    
	res=(char *)CTextPoolEnd;
    /* Copy the contents of the repetition to the CTextPool. */
    oldBody = (char *)((long)theRep->Body+(low-theRep->LowBorder));

	/* Set the first byte in the pascal string eq the length */
	*((char *)CTextPoolEnd)++ = (char)high;

    for (i = 0;  i < high; i++)
      *(((char *)CTextPoolEnd))++ = *(char *)((long)oldBody+i);
	  
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

#if 0
    fprintf(output, "PpkSVT: returning pascal string at address 0x%x with length %d\n", res, *(char*)res);
	fprintf(output, "Characters:\n");
	for (i=0; i<(unsigned)*(char*)res; i++){
		fprintf(output, "0x%x\t'%c'\n", (unsigned)*((char*)res+i+1), *((char*)res+i+1));
	}
	fflush(output);
#endif

    return res;
}

char * PpkCT(char *text, long *SP)
{
    long bodysize = strlen(text);
    char *res;
    long i;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    if (bodysize+1 > ((char *)CTextPool + MAXCTEXTPOOL) - CTextPoolEnd)
      BetaError(CTextPoolErr, GetThis(SP), SP, 0);
    
	res=(char *)CTextPoolEnd;
	/* Set the first byte in the pascal string eq the length */
	*((char *)CTextPoolEnd)++ = (char)bodysize;
    
	/* Copy the contents of the string to the CTextPool. */
	strcpy(CTextPoolEnd, text);
	  
    CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

    return res;
}


#endif
