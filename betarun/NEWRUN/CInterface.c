/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

static void extendCTextPool(int size);

#define CHECK_AND_EXTEND_POOL(size) { \
  if (size > ((char *)CTextPool + Maxctextpool) - CTextPoolEnd) \
     extendCTextPool(size); \
}


static int CTextPoolSize = 1;
static int Maxctextpool = 0;

static void extendCTextPool(int size)
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

char *CCpkVT(ValRep * theRep, long *SP)
{
  long bodysize = ByteRepBodySize(theRep->HighBorder);
  long i;

  DEBUG_CODE(NumCpkVT++);
  Ck(theRep);
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */

  CHECK_AND_EXTEND_POOL(bodysize);
  
  /* Copy the contents of the repetition to the CTextPool */
  for (i = 0; i < bodysize/4; ++i, CTextPoolEnd += 4)
    *((long *)CTextPoolEnd) = theRep->Body[i];

  Ck(theRep);
  return CTextPoolEnd - bodysize;
}

/* CCpkSVT: Copy Slice of variable text (byte rep) to C */
char *CCpkSVT(ValRep *theRep, unsigned low, long high, long *SP)
{
  long bodysize;
  long i;
  unsigned char *oldBody;

  DEBUG_CODE(NumCpkSVT++);
  Ck(theRep);

  /* printf("CpkSVT: theRep=0x%x, low=0x%x, high=0x%x, SP=0x%x\n", theRep, low, high, SP); */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ){ 
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
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

  for (i = 0;  i < high; i++, CTextPoolEnd+=1)
    *(((unsigned char *)CTextPoolEnd)) = *(unsigned char *)((unsigned)oldBody+i);
  *(((unsigned char *)CTextPoolEnd)) = 0; /* NULL termination */
  CTextPoolEnd+=1;
  CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

  /* The following will only work in all cases for the first
   * parameter if CTextPool is long aligned.
   * This is now ensured in data.gen.
   */

  Ck(theRep);
  return CTextPoolEnd - bodysize; 
}

char *CCpkVT_W(ValRep * theRep, long *SP)
{
  long bodysize = ShortRepBodySize(theRep->HighBorder);
  long i;

  DEBUG_CODE(NumCpkVT++);
  Ck(theRep);
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

  Ck(theRep);
  return CTextPoolEnd - bodysize;
}

/* CCpkSVT_W: Copy Slice of variable text (byte rep) to C as wide text */
char *CCpkSVT_W(ValRep *theRep, unsigned low, long high, long *SP)
{
  long bodysize;
  long i;
  unsigned char *oldBody;

  DEBUG_CODE(NumCpkSVT++);
  Ck(theRep);

  /* printf("CpkSVT_W: theRep=0x%x, low=0x%x, high=0x%x, SP=0x%x\n", theRep, low, high, SP); */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ){ 
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
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

  for (i = 0;  i < high; i++, CTextPoolEnd+=2){
    *(((unsigned short *)CTextPoolEnd)) = *(unsigned char *)((unsigned)oldBody+i);
  }
#if 0
  *(((unsigned char *)CTextPoolEnd)) = 0; /* NULL termination */
  CTextPoolEnd+=1;
#endif
  CTextPoolEnd = (char*)((((long)CTextPoolEnd+3)/4)*4); /* long align next text */

  /* The following will only work in all cases for the first
   * parameter if CTextPool is long aligned.
   * This is now ensured in data.gen.
   */

  Ck(theRep);
  return CTextPoolEnd - bodysize; 
}


#if defined(MAC) || defined(macosx)

char * PpkVT(ValRep *theRep, long *SP)
{
  long bodysize = ByteRepBodySize(theRep->HighBorder);
  long i;
  char *oldBody,*res;

  DEBUG_CODE(NumPpkVT++);
  Ck(theRep);
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */

  CHECK_AND_EXTEND_POOL(bodysize+1);
  
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

  Ck(theRep);
  return res;
}

char * PpkSVT(ValRep *theRep, unsigned low, long high, long *SP)
{
  long bodysize;
  long i;
  char *oldBody,*res;

  /* printf("PpkSVT: theRep=0x%x, low=0x%x, high=0x%x, SP=0x%x\n", theRep, low, high, SP); */
  Ck(theRep);

  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) { 
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }
  high = high - low + 1;
  if (high<0) high=0;

  bodysize = ByteRepBodySize(high);
  /* Check range overflow on CTextPool.
   * nextText is used as a tmp. register only.
   * Size_left_in_CTextPool = (CTextPool + MAXCTEXTPOOL) - CTextPoolEnd.
   */
  CHECK_AND_EXTEND_POOL(bodysize+1);
  
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
  
  Ck(theRep);
  return res;
}

#endif
