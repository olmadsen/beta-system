/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: cbfa.c,v $, rel: %R%, date: $Date: 1992-06-12 14:51:20 $, SID: $Revision: 1.1 $
 * by Lars Bak.
 */
#include "beta.h"
long AllocateHeap();

void CBFAAlloc()
{
  /* Allocate the Call Back Functions Area.
   * It is organized as follows:
   *  |---|---|---|---|---|---|0---|
   *  ^CBFA                     |
   *                            |----> |---|---|---|----------------|--|
   *                                                ^CBFATop         ^CBFALimit

   * In each CallbackEntry ( |---| ) the first long is a pointer to the beta struct.
   * If this is zero, the NEXT long is a pointer to the next CBFA block.
   */
  if( !AllocateHeap( &CBFA,     &CBFATop,     &CBFALimit, CBFABlockSize ) ){
    fprintf(output,"#Beta: Couldn't allocate CBFA (%dKb)\n", CBFABlockSize/Kb);
    exit(1);
  }
  ((long *) CBFALimit) -= 2; /* Make sure there is room for a zero and a pointer to next block */
}

void CBFArelloc ()
{
  /* BetaError(-11, 0); */

  /* Allocate new CBFA block, almost like AllocateHeap().
   * Make the cell just after CBFATop point to the new block.
   */
  if( ( *( ((long *)CBFATop)+1 ) = (long) malloc(CBFABlockSize) ) != 0){
    CBFATop = cast(CallBackEntry) *( ((long *)CBFATop)+1 );
    CBFALimit = CBFATop + CBFABlockSize;
    ((long *) CBFALimit) -= 2; /* Make sure there is room for a zero and a pointer to next block */
  } else {
    fprintf(output,"#Beta: Couldn't allocate new CBFA block (%dKb)\n", CBFABlockSize/Kb);
    exit(1);
  }
  INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", CBFABlockSize/Kb); );
}
