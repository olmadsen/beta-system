/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

static void extendCTextPool(long size);

#define CHECK_AND_EXTEND_POOL(size) { \
  if (size > ((char *)CTextPool + Maxctextpool) - CTextPoolEnd) \
     extendCTextPool(size); \
}


static int CTextPoolSize = 1;
static int Maxctextpool = 0;

static void extendCTextPool(long size)
{
  char *newpool;
  do {
    CTextPoolSize *= 2;
  } while (CTextPoolSize < size+10);
  
  newpool = (char*)malloc(CTextPoolSize);
  memset(newpool, 0, CTextPoolSize);

  /* Insert link to previous pool: */
  *(char **)newpool = CTextPool;
  CTextPool = newpool;
  CTextPoolEnd = (char *)CTextPool + sizeof(char*);
  Maxctextpool = CTextPoolSize - 4;
}


void CinitT(void)
{
  DEBUG_CODE(NumCinitT++);
  if (CTextPool) {
    char **oldpool, **pool = *(char ***)CTextPool;
    while (pool) {
      oldpool = pool;
      pool = (char **)*pool;
      free(oldpool);
    }
    CTextPoolEnd = (char *)CTextPool + sizeof(char*);
    *(char **)CTextPool = NULL;
  }
}

/* CpkVT: 
 */
#ifdef sparc
asmlabel(CpkVT, 
	 "mov %o0, %o1; "
	 "ba "CPREF"CpkVT; "
	 "mov %i0, %o0; "
	 );
char *CCpkVT(Object * currentObj, ValRep * theRep)
#endif
#ifdef hppa
char *CpkVT(ValRep * theRep)
#endif
{
  long bodysize = ByteRepBodySize(theRep->HighBorder);
  long i;
  
#ifdef hppa
  Object * currentObj;
  currentObj = (Object *) getThisReg();
#endif
  
  DEBUG_CODE(NumCpkVT++);
  Ck(currentObj); Ck(theRep);
  
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */
  
  CHECK_AND_EXTEND_POOL(bodysize);
  
  /* Copy the contents of the repetition to the CTextPool */
  for (i = 0; i < bodysize/4; ++i, CTextPoolEnd+=4){
    *((long *)CTextPoolEnd) = theRep->Body[i];
  }
  
  return CTextPoolEnd - bodysize;
}

/* CpkSVT: 
 * Copy Slice of variable text (byte rep) to C
 */
#ifdef sparc
asmlabel(CpkSVT, 
	 "mov %o2, %o3; "
	 "mov %o1, %o2; "
	 "mov %o0, %o1; "
	 "ba "CPREF"CpkSVT; "
	 "mov %i0, %o0; "
	 );
char *CCpkSVT(Object * currentObj, 
	      ValRep * theRep, 
	      unsigned low,
	      long high)
#endif
#ifdef hppa
char *CpkSVT(ValRep * theRep, 
	     unsigned low, 
	     long high)
#endif
{
  long bodysize;
  long i;
  unsigned char *oldBody;
#ifdef hppa
  Object * currentObj;
  currentObj = (Object *) getThisReg();
#endif
  
  DEBUG_CODE(NumCpkSVT++);
  
  Ck(currentObj); Ck(theRep);
  if (low<theRep->LowBorder){
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, currentObj);
  }
  if (high>theRep->HighBorder) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, currentObj);
  }
  high = high - low + 1;
  if (high<0) high=0;
  
  bodysize = ByteRepBodySize(high);
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */
  CHECK_AND_EXTEND_POOL(bodysize);
  
  /* Copy the contents of the repetition to the CTextPool. */
  oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
  for (i = 0;  i < high; i+=1, CTextPoolEnd+=1)
    *(((unsigned char *)CTextPoolEnd)) = *(unsigned char *)((unsigned)oldBody+i);
  *(((unsigned char *)CTextPoolEnd)) = 0; /* NULL termination */
  CTextPoolEnd+=1;
  CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */
  
#ifdef hppa
  __asm__ volatile ("COPY %0,%%r26" : /* no out */ 
		    : "r" (CTextPoolEnd - bodysize) : "r26");
#endif
  
  /* The following will only work in all cases for the first
   * parameter if CTextPool is long aligned.
   * See CInitT and data.gen
   */
  
  return CTextPoolEnd - bodysize; 
}


/* CpkVT_W: 
 */
#ifdef sparc
asmlabel(CpkVT_W, 
	 "mov %o0, %o1; "
	 "ba "CPREF"CpkVT_W; "
	 "mov %i0, %o0; "
	 );
char *CCpkVT_W(Object * currentObj, ValRep * theRep)
#endif
#ifdef hppa
char *CpkVT_W(ValRep * theRep)
#endif
{
  long bodysize = ShortRepBodySize(theRep->HighBorder);
  long i;
  
#ifdef hppa
  Object * currentObj;
  currentObj = (Object *) getThisReg();
#endif
  
  DEBUG_CODE(NumCpkVT++);
  Ck(currentObj); Ck(theRep);
  
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */
  
  CHECK_AND_EXTEND_POOL(bodysize);

  /* Copy the contents of the repetition to the CTextPool */
  for (i = 0; i < bodysize; i++, CTextPoolEnd+=2){
    /* printf("CpkVT_W: %c\n", ascii + i); */
    *((unsigned short*)CTextPoolEnd) = theRep->Body[i];
  }
  
  return CTextPoolEnd - bodysize;
}

/* CpkSVT_W: 
 * Copy Slice of variable text (byte rep) to C as wide text
*/
#ifdef sparc
asmlabel(CpkSVT_W, 
	 "mov %o2, %o3; "
	 "mov %o1, %o2; "
	 "mov %o0, %o1; "
	 "ba "CPREF"CpkSVT_W; "
	 "mov %i0, %o0; "
	 );
char *CCpkSVT_W(Object * currentObj, 
		ValRep * theRep, 
		unsigned low,
		long high)
#endif
#ifdef hppa
char *CpkSVT_W(ValRep * theRep, 
	       unsigned low, 
	       long high)
#endif
{
  long bodysize;
  long i;
  unsigned char *oldBody;
#ifdef hppa
  Object * currentObj;
  currentObj = (Object *) getThisReg();
#endif
  
  DEBUG_CODE(NumCpkSVT++);
  
  Ck(currentObj); Ck(theRep);
  if (low<theRep->LowBorder){
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, currentObj);
  }
  if (high>theRep->HighBorder) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, currentObj);
  }
  high = high - low + 1;
  if (high<0) high=0;
  
  bodysize = ShortRepBodySize(high);
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */
  CHECK_AND_EXTEND_POOL(bodysize);
  
  /* Copy the contents of the repetition to the CTextPool. */
  oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
  for (i = 0;  i < high; i+=1, CTextPoolEnd+=2){
    *(((unsigned short *)CTextPoolEnd)) = *(unsigned char *)((unsigned)oldBody+i);
  }
#if 0
  *(((unsigned char *)CTextPoolEnd)) = 0; /* NULL termination */
  CTextPoolEnd+=1;
#endif
  CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */
  
#ifdef hppa
  __asm__ volatile ("COPY %0,%%r26" : /* no out */ 
		    : "r" (CTextPoolEnd - bodysize) : "r26");
#endif
  
  /* The following will only work in all cases for the first
   * parameter if CTextPool is long aligned.
   * See CInitT and data.gen
   */
  
  return CTextPoolEnd - bodysize; 
}

#ifdef MAC
unsigned char * PpkVT(Object *currentObj, ValRep * theRep)
{
    long bodysize = theRep->HighBorder;
    long i;
    unsigned char *oldBody,*res;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */

    Ck(currentObj); Ck(theRep);
    CHECK_AND_EXTEND_POOL(bodysize+1);
    
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

unsigned char * PpkSVT(Object *currentObj, ValRep * theRep, unsigned low, long high)
{
    long bodysize;
    long i;
    unsigned char *oldBody,*res;

    Ck(currentObj); Ck(theRep);
    if (low<theRep->LowBorder) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, currentObj);
    }
    if (high>theRep->HighBorder) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, currentObj);
    }
    high = high - low + 1;
    if (high<0) high=0;

    bodysize = high;
    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    CHECK_AND_EXTEND_POOL(bodysize+1);
    
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

unsigned char * PpkCT(Object *currentObj, char *text)
{
    long bodysize = strlen(text);
    unsigned char *res;
    long i;

    /* Check range overflow on CTextPool.
     * nextText is used as a tmp. register only.
     * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
     */
    CHECK_AND_EXTEND_POOL(bodysize+1);
    
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
