/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: lvra.c, rel: 1, date: 3/9/91, SID: 1.6
 * by Lars Bak
 */
#include "beta.h"

#define TabelMAX 15

struct LVRABlock *LVRABaseBlock;
struct LVRABlock *LVRATopBlock;

long LVRAFreeListAvailable = FALSE;
long LVRACreateNewBlock    = FALSE;
long LVRANumOfBlocks       = 0;

/* LVRALastIOAGc contains the value of NumIOAGc last time
 * LVRAConstructFreeList was executed.
 */
long LVRALastIOAGc         = 0;

long LVRAFreeListMemory;

#define LVRABigRange 100 * 256    /* ~ValRepSize > 100 Kb. */

ref(ValRep) LVRATabel[TabelMAX+1];

DEBUG_CODE( long LVRATabNum[16] )

#define ValRepSize( range) (range*4 + 16)

/* LVRAtabelIndex find a index in the Tabel in the range [0..TabelMAX].
 * The index is a sort of a log2 function.
 * f(16) = 0; f(32) = 1 ..... f(64Kb) = 12; f(128Kb) = 13 etc.
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
  LVRAFreeListAvailable = FALSE;
  DEBUG_CODE( for(index=0;index <= TabelMAX; index++) LVRATabNum[index] = 0 );
}

#ifdef RTDEBUG
LVRADisplayTable()
{ int index;
  fprintf( output, "#(LVRAFreeList: ");
  for(index=0;index <= TabelMAX; index++)
    if( LVRATabel[index] )
      fprintf( output, "%d:%d ", index, LVRATabNum[index]);
  fprintf( output, ")\n");
}
#endif

/* LVRAInsertFreeElement add a value repetition to the 
 * Free List Table. 
 */
LVRAInsertFreeElement( freeRep)
  ref(ValRep) freeRep;
{ int index; 
  ref(ValRep) headRep;

  LVRAFreeListAvailable = TRUE;
  index = LVRATabelIndex( freeRep->HighBorder );
  /* Insert the repetition as the first element in the list. */
  DEBUG_LVRA( { struct ValRep *cur = LVRATabel[index];
               while( cur ){ Claim( cur != freeRep,"LVRAInsert"); 
			     cur = (struct ValRep *) cur->Proto;}

	      } );
  headRep = LVRATabel[index];  LVRATabel[index] = freeRep;
  freeRep->Proto  = (ref(ProtoType)) headRep;
  freeRep->GCAttr = 0; 
  DEBUG_CODE( if( index == TabelMAX )
	        fprintf( output, "(LVRAInsert=%d)", freeRep->HighBorder));
  DEBUG_CODE( LVRATabNum[index]++);
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
  DEBUG_CODE( int oldBorder);

  index = LVRATabelIndex( range );
  takenFrom = (ptr(long)) &LVRATabel[index];
  currentRep = (ref(ValRep)) LVRATabel[index];
  while( currentRep ){
    if( currentRep->HighBorder == range ){
      /* Update the chain in the freeList. */
      *takenFrom = (long) currentRep->Proto;

      DEBUG_CODE( LVRATabNum[index]--);
      /* Initialize the returned repetition. */
      currentRep->Proto      = (ref(ProtoType)) -3;
      currentRep->GCAttr     = 0;

      return currentRep;
    }
    takenFrom =  (ptr(long))   &currentRep->Proto;
    currentRep = (ref(ValRep))  currentRep->Proto;
  }

  do{
    takenFrom = (ptr(long)) &LVRATabel[index];
    currentRep = (ref(ValRep)) LVRATabel[index];
    while( currentRep != 0 ){
      if( currentRep->HighBorder >= range + 4 ){
        /* Update the chain in the freeList. */
	*takenFrom = (long) currentRep->Proto;

        DEBUG_CODE( LVRATabNum[index]--);
        DEBUG_CODE( oldBorder = currentRep->HighBorder );

	rest = currentRep->HighBorder - range;
	
        currentRep->Proto      = (ref(ProtoType)) -3;
	currentRep->GCAttr     = 0;
	currentRep->LowBorder  = 1;
	currentRep->HighBorder = range;

        /* Used the rest to a new repetition, and insert it i the free list. */
	restRep = (ref(ValRep)) Offset(currentRep, 4*(range+4));
        restRep->Proto      = 0;
        restRep->GCAttr     = 0;
	restRep->LowBorder  = 1;
	restRep->HighBorder = rest-4;
	LVRAInsertFreeElement( restRep);
        DEBUG_LVRA( Claim( ValRepSize( oldBorder) ==
			  (ValRepSize(currentRep->HighBorder)
			   + ValRepSize(restRep->HighBorder)),
			  "#LVRAFindInFree: old = new + rest"));	      
	return currentRep;
      }
      takenFrom =  (ptr(long))   &currentRep->Proto;
      currentRep = (ref(ValRep))  currentRep->Proto;
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
  newRep->GCAttr     = 0;
  newRep->LowBorder  = 1;
  newRep->HighBorder = range;
  return newRep;
}

long LVRARestInBlock( theBlock)
  ref(LVRABlock) theBlock;
{
  return (long) theBlock->limit - (long) theBlock->top;
}

/* Allocate repetition with range in LVRATopBlock->[top..limit]. */
ref(ValRep)LVRAAllocInBlock( range)
 long        range;
{
  ref(ValRep) newRep;
  ptr(long)   newTop;
 
  newRep = (ref(ValRep)) LVRATopBlock->top;
  if( (newTop = (ptr(long)) Offset(newRep,4*(range+4)))
     <= LVRATopBlock->limit){
    LVRATopBlock->top = newTop;
    newRep->Proto      = (ref(ProtoType)) -3;
    newRep->GCAttr     = 0;
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
  ref(ValRep) newRep;
  long        size;
  long        rest;

  INFO_LVRA_ALLOC( fprintf( output, "<%d>", range) );
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
      LVRATopBlock->top =  (ptr(long)) Offset(LVRATopBlock->top, 4*(rest+4));
  }
  if( LVRALastIOAGc != NumIOAGc){
    LVRAConstructFreeList();
    if( newRep = LVRAFindInFree(range) ) return newRep;
    if( LVRATopBlock->next ){
      LVRATopBlock = LVRATopBlock->next;
      if( newRep = LVRAAllocInBlock( range) ) return newRep;       
    }
    if( LVRACreateNewBlock || (range > LVRABigRange) ){
      if( MallocExhausted ) return 0;
      if( ValRepSize(range) > LVRABlockSize) size = ValRepSize(range);
      else size = LVRABlockSize;
      if( (LVRATopBlock->next = newLVRABlock( size) ) == 0 ){
	MallocExhausted = TRUE; return 0;
      }
      LVRATopBlock = LVRATopBlock->next;
      LVRACreateNewBlock = FALSE;
      if( newRep = LVRAAllocInBlock( range) ) return newRep;
    }
  }
  LVRACompaction();
  if( newRep = LVRAAllocInBlock( range) ) return newRep;
  if( newRep = LVRAFindInFree(range) ) return newRep;
  if( MallocExhausted ) return 0;
  if( ValRepSize(range) > LVRABlockSize) size = ValRepSize(range);
  else size = LVRABlockSize;
  if( (LVRATopBlock->next = newLVRABlock( size) ) == 0 ){
    MallocExhausted = TRUE; return 0;
  }
  LVRATopBlock = LVRATopBlock->next;
  LVRACreateNewBlock = FALSE;
  if( newRep = LVRAAllocInBlock( range) ) return newRep;
  return 0;
}

LVRACompaction()
{
  ref(LVRABlock) srcBlock;
  ref(LVRABlock) dstBlock;

  ref(ValRep)    srcRep;
  ref(ValRep)    dstRep;

  long           alive;
  long           saved;
  long           theObjectSize;
  long           numBlocks;
  long           sizeBlocks;

#ifdef macintosh
  RotateTheCursor();
#endif

  NumLVRAGc++;
  /* Run compaction elements in 'LVRABlock{->next}*'  */
  INFO_LVRA( fprintf( output, "#(LVRA-%d ", NumLVRAGc) ); 

  LVRANumOfBlocks = 0;

  LVRACleanTabel();

  saved = 0; numBlocks = 0; sizeBlocks = 0; 

  srcBlock = LVRABaseBlock;
  dstBlock = LVRABaseBlock; dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);

  while( srcBlock != 0){
    numBlocks++; 
    sizeBlocks += (long) srcBlock->limit - (long) srcBlock;
    /* traverse srcBlock. */
    srcRep = (ref(ValRep)) LVRABlockStart(srcBlock);
    while( ((ptr(long)) srcRep) < srcBlock->top){
      alive =  LVRAAlive( srcRep );
      theObjectSize = ValRepSize(srcRep->HighBorder);
      if( alive ){
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
	     LVRAInsertFreeElement( dstRep);
	   }
           dstBlock = dstBlock->next;
	   DEBUG_LVRA( Claim( dstBlock, "LVRACompaction: dstBlock"));
	   dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);
	 }
	 size = srcRep->HighBorder;

	 /* Preserve the LVRA-cycle */

	 *((ptr(long)) srcRep->GCAttr) = (long) dstRep;

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

  LVRATopBlock = dstBlock;
  dstBlock = dstBlock->next;
  while( dstBlock ){
    dstBlock->top = LVRABlockStart(dstBlock);
    saved += (long) dstBlock->limit - (long) dstBlock->top;
    dstBlock = dstBlock->next;
  }

  if( LVRAMinFree ){
    if( saved < LVRAMinFree )
      /* if freeArea < LVRAMinFree  then ... */
      LVRACreateNewBlock = TRUE;
    else
      LVRACreateNewBlock = FALSE;
  }else{
    if( (100*saved)/sizeBlocks < LVRAPercentage )
      /* if freeArea < LVRAPercentage  then ... */
      LVRACreateNewBlock = TRUE;
    else
      LVRACreateNewBlock = FALSE;
  }
  DEBUG_AOA( if( LVRACreateNewBlock ) fprintf( output, "new block needed, "));

  INFO_LVRA( fprintf( output, " %dKb in %d blocks, %d%% free)\n",
		     toKb(sizeBlocks), numBlocks, (100*saved)/sizeBlocks));
  LVRALastIOAGc = 0;
}

LVRAAlive( theRep)
     ref(ValRep) theRep;
{
  if( (long) theRep->Proto != -3 ){
    DEBUG_LVRA( Claim( theRep->GCAttr == 0,"LVRAAlive: theRep->GCAttr == 0"));
    return FALSE;
  }
  DEBUG_LVRA( Claim( theRep->GCAttr , "LVRAAlive: theRep->GCAttr != 0"));
  
  return ((long) theRep == *((long *) theRep->GCAttr));
}

LVRAConstructFreeList()
{
  ref(LVRABlock) currentLVRABlock;
  ref(ValRep)    currentValRep;
  ref(ValRep)    startRep;
  long           saved;
  long           alive;
  long           theObjectSize;
  long           numBlocks;
  long           sizeBlocks;

#ifdef macintosh
  RotateTheCursor();
#endif

  INFO_LVRA( fprintf( output, "#(LVRA: make free list")); 

  LVRACleanTabel();

  saved = 0; numBlocks = 0; sizeBlocks = 0;
  currentLVRABlock = LVRABaseBlock;

  while( currentLVRABlock != 0){    
    numBlocks++; 
    sizeBlocks += (long) currentLVRABlock->limit -
      (long) currentLVRABlock - (long) sizeof(struct LVRABlock);
    /* traverse currentLVRABlock. */
    currentValRep = (ref(ValRep)) LVRABlockStart(currentLVRABlock);
    startRep = 0;

    while( ((ptr(long))currentValRep) < currentLVRABlock->top){
      alive =  LVRAAlive( currentValRep );
      theObjectSize = ValRepSize(currentValRep->HighBorder);

      if( startRep ){
	if( alive ){ 
	  LVRAInsertFreeElement( startRep );
	  saved += ValRepSize( startRep->HighBorder);
          DEBUG_LVRA( Claim( (saved > 0) && (saved <= sizeBlocks),
			    "#LVRAMakeFree: (saved > 0) && (saved <= sizeBlocks)"));
          startRep = 0;
	}else{
	  /* Connect [startRep..currentRep] to one object, by enlarging the 
	   * startRep HighBorder
	   */
	  startRep->HighBorder += ValRepStructSize + currentValRep->HighBorder;
	}
      }else{
	if( !alive )
	  startRep = currentValRep;
      }

      currentValRep = (ref(ValRep)) (((long) currentValRep)+theObjectSize);
    }
    if( startRep ){
      LVRAInsertFreeElement( startRep );
      saved += ValRepSize( startRep->HighBorder);
      DEBUG_LVRA( Claim( (saved > 0) && (saved <= sizeBlocks),
			"#LVRAMakeFree: (saved > 0) && (saved <= sizeBlocks)"));
    }

    /* Take the next element in the LVRA block chain. */
    currentLVRABlock = currentLVRABlock->next;
      
  }

  if( LVRAMinFree ){
    if( saved < LVRAMinFree )
      /* if freeArea < LVRAMinFree  then ... */
      LVRACreateNewBlock = TRUE;
    else
      LVRACreateNewBlock = FALSE;
  }else{
    if( (100*saved)/sizeBlocks < LVRAPercentage )
      /* if freeArea < LVRAPercentage  then ... */
      LVRACreateNewBlock = TRUE;
    else
      LVRACreateNewBlock = FALSE;
  }
  DEBUG_AOA( if( LVRACreateNewBlock ) fprintf( output, "new block needed, "));

  INFO_LVRA( fprintf( output, "  %dKb in %d blocks, %dKb free)\n",
		     toKb(sizeBlocks), numBlocks, toKb(saved)));
  DEBUG_LVRA( LVRADisplayTable() );
  LVRALastIOAGc = NumIOAGc;
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

    newRep->GCAttr = 0;
    /* Set one forward reference in theObj to newObj */
    theRep->GCAttr = (long) newRep;
  }
  /* Return the new object in ToSpace */
  return newRep;
}

#ifdef RTDEBUG
LVRACheck()
{ ref(LVRABlock) theBlock;
  ref(ValRep)    currentValRep;
  int theObjectSize;

  theBlock = LVRABaseBlock;
  while( theBlock ){    
    /* traverse currentLVRABlock. */
    currentValRep = (ref(ValRep)) LVRABlockStart(theBlock);
    while( ((ptr(long))currentValRep) < theBlock->top){
      theObjectSize = ValRepSize(currentValRep->HighBorder);
      currentValRep = (ref(ValRep)) (((long) currentValRep)+theObjectSize);
    }
    Claim( (long *) currentValRep == theBlock->top,
          "#LVRACheck: currentValRep == theBlock->top");
    /* Take the next element in the LVRA block chain. */
    theBlock = theBlock->next;
  }
} 
#endif
