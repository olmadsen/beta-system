/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: lvra.c,v $, rel: %R%, date: $Date: 1991-01-30 10:51:16 $, SID: $Revision: 1.1 $
 * by Lars Bak
 */
#include "beta.h"

#define TabelMAX 15

struct LVRABlock *LVRABaseBlock;
struct LVRABlock *LVRATopBlock;

long LVRAFreeListAvailable = FALSE;
long LVRACreateNewBlock    = FALSE;
long LVRANumOfBlocks       = 0;

long LVRAFreeListMemory;

#define LVRABigRange 100 * 256    /* ~ValRepSize > 100 Kb. */

ref(ValRep) LVRATabel[TabelMAX+1];

DEBUG_CODE( long LVRATabNum[16] )

#define ValRepSize( range) (range*4 + 16)

/* LVRAtabelIndex find a index in the Tabel in the range [0..TabelMAX].
 * The index is a sort of a log2 function.
 * f(16) = 0; f(32) = 1 ..... f(64Kb) = 12 etc.
 * The returned value is <= TabelMAX.
 */
int LVRATabelIndex( range )
  int range;
{ int index = 0; range >>= 4;
  while( ( range >>= 1 ) != 0) index++;
  if( index > TabelMAX ) index = TabelMAX;
  return index; 
}

/* LVRACleanTable initialize the Free List Table */
LVRACleanTabel()
{ int index;
  for(index=0;index <= TabelMAX; index++) LVRATabel[index] = 0;
  DEBUG_CODE( for(index=0;index <= TabelMAX; index++) LVRATabNum[index] = 0 );
}

/* LVRAInsertFreeElement add a value repetition to the 
 * Free List Table. 
 */
LVRAInsertFreeElement( freeRep)
  ref(ValRep) freeRep;
{ int index; 
  ref(ValRep) headRep;

  index = LVRATabelIndex( freeRep->HighBorder );
  /* Insert the repetition as the first element in the list. */
  headRep = LVRATabel[index];  LVRATabel[index] = freeRep;
  DEBUG_CODE( LVRATabNum[index]++);
  freeRep->Proto  = 0; 
  freeRep->GCAttr = (long) headRep;
}

/* LVRAFindInFree try to find space for at repetition with range 'range'.
 * A first shut is to find a equal sized repetition in the free list.
 * Second find a larger repetition in the free list and split it into 
 * two repetitions. 
 * If none of the above tries succeed the function returns 0.
 */
ref(ValRep) LVRAFindInFree( range)
     long range;
{
  ref(ValRep) currentRep;
  ptr(long)   takenFrom;
  ref(ValRep) restRep;
  long rest;
  int index;

  index = LVRATabelIndex( range );
  takenFrom = (ptr(long)) &LVRATabel[index];
  currentRep = (ref(ValRep)) LVRATabel[index];
  while( currentRep != 0 ){
    if( currentRep->HighBorder == range ){
      /* Update the chain in the freeList. */
      *takenFrom = currentRep->GCAttr;

      DEBUG_CODE( LVRATabNum[index]--);
      /* Initialize the returned repetition. */
      currentRep->Proto      = (ref(ProtoType)) -3;
      currentRep->GCAttr     = LVRAIOAAge;

      return currentRep;
    }
    takenFrom = &currentRep->GCAttr;
    currentRep = (ref(ValRep)) currentRep->GCAttr;
  }

  do{
    takenFrom = (ptr(long)) &LVRATabel[index];
    currentRep = (ref(ValRep)) LVRATabel[index];
    while( currentRep != 0 ){
      if( currentRep->HighBorder >= range + 4 ){
        /* Update the chain in the freeList. */
	*takenFrom = currentRep->GCAttr;

        DEBUG_CODE( LVRATabNum[index]--);

	rest = currentRep->HighBorder - range;
	
        currentRep->Proto      = (ref(ProtoType)) -3;
	currentRep->GCAttr     = LVRAIOAAge;
	currentRep->LowBorder  = 1;
	currentRep->HighBorder = range;

        /* Used the rest to a new repetition, and insert it i the free list. */
	restRep = (ref(ValRep)) Offset(currentRep, 4*(range+4));
        restRep->Proto      = 0;
	restRep->LowBorder  = 1;
	restRep->HighBorder = rest-4;
	LVRAInsertFreeElement( restRep);
	return currentRep;
      }
      takenFrom = &currentRep->GCAttr;
      currentRep = (ref(ValRep)) currentRep->GCAttr;
    }
    index++;
  }while( index <= TabelMAX );
  return 0;
}

#define inLVRABlock( theB, addr) (LVRABlockStart( theB) <= (ptr(long)) addr \
                                  && (ptr(long)) addr < theB->top)

ref(LVRABlock) newLVRABlock( size )
  int size;
{
  ref(LVRABlock) theBlock;

  /* Insert printout */

  theBlock = (ref(LVRABlock)) malloc( sizeof(struct LVRABlock) + size );
  
  if( theBlock != 0 ){
    INFO_LVRA( fprintf( output, "#(LVRA: new block allocated %dKb)\n",
		       toKb(size))); 
    LVRANumOfBlocks++;

    theBlock->next  = 0;
    theBlock->state = 0;
    theBlock->top   = LVRABlockStart( theBlock );
    theBlock->limit = (ptr(long)) ((long) LVRABlockStart( theBlock) + (long) size);
  }else{
    INFO_LVRA( fprintf( output ,"#(LVRA: failed to allocate new block %dKb)\n", 
		       toKb(size))); 
  }
  return theBlock;
}

int inLVRA( theObj )
  ref(Object) theObj;
{
  ref(LVRABlock)  theBlock;

  theBlock = LVRABaseBlock;

  while( theBlock ){
    if( inLVRABlock( theBlock, theObj) ) return TRUE;
    theBlock = theBlock->next;
  }
  return FALSE;
}


ref(ValRep)LVRAinitValRep( newRep, range)
 ref(ValRep) newRep;
 long        range;
{
  newRep->Proto      = (ref(ProtoType)) -3;
  newRep->GCAttr     = LVRAIOAAge;
  newRep->LowBorder  = 1;
  newRep->HighBorder = range;
  return newRep;
}

long LVRARestInBlock( theBlock)
  ref(LVRABlock) theBlock;
{
  return theBlock->limit - theBlock->top;
}

/* Allocate repetition with range in LVRATopBlock->[top..limit]. */
ref(ValRep)LVRAAllocInBlock( range)
 long        range;
{
  ref(ValRep) newRep;
  ptr(long)   newTop;
 
  newRep = (ref(ValRep)) LVRATopBlock->top;
  if( (newTop = (ptr(long)) Offset(newRep,ValRepSize(range)))
     <= LVRATopBlock->limit){
    LVRATopBlock->top = newTop;
    newRep->Proto      = (ref(ProtoType)) -3;
    newRep->GCAttr     = LVRAIOAAge;
    newRep->LowBorder  = 1;
    newRep->HighBorder = range;
    return newRep;
  }
  return 0;
}

/* LVRAAlloc allocate a Value repetition in the LVRArea. */
ref(ValRep) LVRAAlloc( range)
  long range;
{
  ptr(long)   newTop;
  ref(ValRep) newRep;
  long        size;
  long        rest;

  if( LVRABaseBlock == 0 ){
    if( LVRABlockSize == 0) return 0;
    if( MallocExhausted ) return 0;
    if( ValRepSize(range) > LVRABlockSize) size = ValRepSize(range);
    else size = LVRABlockSize;
    if( (LVRABaseBlock = newLVRABlock( size) ) == 0 ){
      MallocExhausted = TRUE; return 0;
    }
    LVRATopBlock = LVRABaseBlock;
  }
  if( LVRAFreeListAvailable )
    if( newRep = LVRAFindInFree(range) ) return newRep;
  if( newRep = LVRAAllocInBlock( range) ) return newRep;
  rest = (LVRARestInBlock(LVRATopBlock)/4) - 4;
  if( rest >= 0 ){
      newRep = (ref(ValRep)) LVRATopBlock->top;
      newRep->Proto      = 0;
      newRep->GCAttr     = 0;
      newRep->LowBorder  = 1;
      newRep->HighBorder = rest;
      LVRATopBlock->top =  (ptr(long)) 
	Offset(LVRATopBlock->top, ValRepSize(rest));
  }
  LVRAConstructFreeList();
  if( newRep = LVRAFindInFree(range) ) return newRep;
  if( LVRATopBlock->next ){
    LVRATopBlock = LVRATopBlock->next;
    if( newRep = LVRAAllocInBlock( range) ) return newRep;       
  }
  if( (LVRACreateNewBlock&&(LVRANumOfBlocks < 2)) || (range > LVRABigRange) ){
    if( MallocExhausted ) return 0;
    if( ValRepSize(range) > LVRABlockSize) size = ValRepSize(range);
    else size = LVRABlockSize;
    if( (LVRATopBlock->next = newLVRABlock( size) ) == 0 ){
      MallocExhausted = TRUE; return 0;
    }
    LVRATopBlock = LVRATopBlock->next;
    LVRACreateNewBlock = FALSE;
    if( newRep = LVRAAllocInBlock( range) ) return newRep;
  };
  LVRANeedCompaction = TRUE;
  return 0;
}

LVRACompaction()
{
  ref(LVRABlock) srcBlock;
  ref(LVRABlock) dstBlock;

  ref(ValRep)    srcRep;
  ref(ValRep)    dstRep;

  long           rest;
  long           alive;
  long           saved;
  long           theObjectSize;
  long           numBlocks;
  long           sizeBlocks;

  LVRANumOfBlocks = 0;

  /* An error occurs if we call LVRACompaction and the IOAGc was called
   * during {CopyValRep,CopySliceValRep,ExtendValRep} and the source
   * reptition resides in LVRA. 
   * IN THIS CASE THE SOURCE REPETITION HAS 2 ROOTS!!!!
   * the variable theValRepSource points to the source repetition, during
   * during {CopyValRep,CopySliceValRep,ExtednValRep}.
   */

  if( theValRepSource != 0)
    if( inLVRA( theValRepSource ) ) return;
 
  /* Run compaction elements in LVRABlock{->next}*  */
  INFO_LVRA( fprintf( output, "#(LVRA: compaction") ); 

  LVRACleanTabel();

  saved = 0; numBlocks = 0; sizeBlocks = 0; 

  srcBlock = LVRABaseBlock;
  dstBlock = LVRABaseBlock; dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);

  while( srcBlock != 0){
    numBlocks++; 
    sizeBlocks += (long) srcBlock->limit - (long) srcBlock;
    /* traverse srcBlock. */
    srcRep = (ref(ValRep)) LVRABlockStart(srcBlock);
    while( ((ptr(long)) srcRep) < srcBlock->limit){
      alive =  LVRAAlive( srcRep );
      theObjectSize = ValRepSize(srcRep->HighBorder);
      if( alive ){
       DEBUG_LVRA( Claim( ((long) srcRep) = *((ptr(long)) srcRep->Proto),
			 "LVRACompaction: srcRep == *srcRep->Proto"));
       if( srcRep != dstRep ){
	 long size, index, rest;
	 ptr(long) src;
	 ptr(long) dst;

         while( Offset( dstRep, theObjectSize) > (long) dstBlock->limit){
           /* Not possible to allocate object in dstBlock. */
           dstBlock->top = (ptr(long)) dstRep;
	   rest = (LVRARestInBlock(LVRATopBlock)/4) - 4;
	   if( rest >= 0 ){
	     dstRep = (ref(ValRep)) LVRATopBlock->top;
	     dstRep->Proto      = 0;
	     dstRep->GCAttr     = 0;
	     dstRep->LowBorder  = 1;
	     dstRep->HighBorder = rest;
	     dstBlock->top =  (ptr(long)) 
	       Offset(dstBlock->top, ValRepSize(rest));
             saved += ValRepSize(rest);
	   }
           dstBlock = dstBlock->next;
	   DEBUG_LVRA( Claim( dstBlock != 0, "LVRACompaction: dstBlock == 0"));
	   dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);
	 }
	 size = srcRep->HighBorder;

	 *((ptr(long)) srcRep->Proto) = (long) dstRep;

	 dstRep->Proto      = srcRep->Proto;
	 dstRep->GCAttr     = srcRep->GCAttr;
	 dstRep->LowBorder  = srcRep->LowBorder;
	 dstRep->HighBorder = srcRep->HighBorder;

	 src = &srcRep->Body[0]; dst = &dstRep->Body[0];
	 for(index=0; index<size; index++) *dst++ = *src++;
       }
       dstRep = (ref(ValRep)) ((long) dstRep + theObjectSize );
     }
      srcRep = (ref(ValRep)) (((long) srcRep)+theObjectSize);
    }
    /* Take the next element in the LVRA block chain. */
    srcBlock = srcBlock->next;
  }
  dstBlock->top = (ptr(long)) dstRep;
  sizeBlocks += (long) dstBlock->limit - (long) dstBlock->top;

  LVRATopBlock = dstBlock;
  dstBlock = dstBlock->next;
  while( dstBlock ){
    dstBlock->top = LVRABlockStart(dstBlock);
    saved += (long) dstBlock->limit - (long) dstBlock->top;
    dstBlock = dstBlock->next;
  }

  LVRACreateNewBlock = ((saved * 100)/sizeBlocks < 20); 

  INFO_LVRA( fprintf( output, " used %dKb in %d blocks, free %dKb)\n",
		     toKb(sizeBlocks), numBlocks, toKb(saved)));
}

LVRAAlive( theRep)
     ref(ValRep) theRep;
{
  if( theRep->Proto == 0 ) return FALSE;
#ifdef AO_Area
  if( inAOA(theRep->Proto) ) return TRUE;
#endif
  if( IOAActive )
    return theRep->GCAttr >= LVRAIOAAge - 1;
  else
    return theRep->GCAttr == LVRAIOAAge;
}

LVRAConstructFreeList()
{
  ref(LVRABlock) currentLVRABlock;
  ref(ValRep)    currentValRep;
  ref(ValRep)    startRep;
  long           rest;
  long           saved;
  long           alive;
  long           theObjectSize;
  long           numBlocks;
  long           sizeBlocks;

  INFO_LVRA( fprintf( output, "#(LVRA: make free list")); 

  LVRACleanTabel();

  saved = 0; numBlocks = 0; sizeBlocks = 0;
  startRep = 0;
  currentLVRABlock = LVRABaseBlock;

  while( currentLVRABlock != 0){    
    numBlocks++; 
    sizeBlocks += (long) currentLVRABlock->limit - (long) currentLVRABlock;
    /* traverse currentLVRABlock. */
    currentValRep = (ref(ValRep)) LVRABlockStart(currentLVRABlock);
    while( ((ptr(long))currentValRep) < currentLVRABlock->top){
      alive =  LVRAAlive( currentValRep );
      theObjectSize = ValRepSize(currentValRep->HighBorder);

      DEBUG_LVRA( 
	if( alive )
	  Claim( ((long) currentValRep) = *((ptr(long)) currentValRep->Proto),
		"LVRACompaction: The cycle for live ValRep is not preserved")
      );
      if( startRep ){
	if( alive ){ 
	  LVRAInsertFreeElement( startRep );
	  saved += ValRepSize( startRep->HighBorder);
	  startRep = 0;
	}else{
	  /* Connect [startRep..currentRep] to one object, by enlarging the 
	   * startRep HighBorder
	   */
	  startRep->HighBorder += ValRepStructSize + currentValRep->HighBorder;
	}
      }else if( !alive )startRep = currentValRep;

      currentValRep = (ref(ValRep)) (((long) currentValRep)+theObjectSize);
    }
    if( startRep ){
      LVRAInsertFreeElement( startRep );
      saved += ValRepSize( startRep->HighBorder);
    }

    /* Take the next element in the LVRA block chain. */
    currentLVRABlock = currentLVRABlock->next;
  
    LVRACreateNewBlock = ((saved*100)/sizeBlocks) < 20;
  }
  INFO_LVRA( fprintf( output, "  %dKb in %d blocks, %dKb free)\n",
		     toKb(sizeBlocks), numBlocks, toKb(saved)));
}

LVRAStatistics()
{
}

ref(ValRep) CopyObjectToLVRA( theRep)
  ref(ValRep) theRep;
{
  ref(ValRep) newRep;
  long size, index;
  ptr(long) src;
  ptr(long) dst;

  size = theRep->HighBorder;
  if( (newRep = LVRAAlloc( size )) != 0 ){

    src = &theRep->Body[0]; dst = &newRep->Body[0];
    for(index=0; index<size; index++) *dst++ = *src++;

    newRep->GCAttr = LVRAIOAAge;
    /* Set one forward reference in theObj to newObj */
    theRep->GCAttr = (long) newRep;
  }
  /* Return the new object in ToSpace */
  return newRep;
}

