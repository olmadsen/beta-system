/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $Id: lvra.c,v 1.20 1992-09-07 15:39:58 beta Exp $
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

static LVRACompaction();
static LVRAAlive();
static LVRAConstructFreeList();

#define TableMAX 15

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

static struct ValRep *LVRATable[TableMAX+1];

DEBUG_CODE(long LVRATabNum[16] );

/************************ THE LVRA FREE LIST ********************************
 * When a repetition 'rep' is in the free list, rep->Proto points to next
 * free element, rep->GCattr is 0 (the rep is not alive), and rep->highborder
 * is the number of BYTES in the BODY of 'rep'.
 */


/* LVRAtableIndex find a index in the Table in the range [0..TableMAX].
 * The index is a sort of a log2 function.
 * f(16) = 0; f(32) = 1 ..... f(64Kb) = 12; f(128Kb) = 13 etc.
 * The returned value is <= TableMAX.
 */
static int LVRATableIndex(range )
     int range;
{ int index = 0; range >>= 4;
  while((range >>= 1 ) != 0) index++;
  if(index > TableMAX ) index = TableMAX;
  return index; 
}


/* LVRACleanTable initialize the Free List Table */
static LVRACleanTable()
{ int index;
  for(index=0;index <= TableMAX; index++) LVRATable[index] = 0;
  LVRAFreeListAvailable = FALSE;
  DEBUG_CODE(for(index=0;index <= TableMAX; index++) LVRATabNum[index]=0 );
  ;}

#ifdef RTDEBUG
static LVRADisplayTable()
{ int index;
  fprintf(output, "#(LVRAFreeList: ");
  for(index=0;index <= TableMAX; index++)
    if(LVRATable[index] )
      fprintf(output, "%d:%d ", index, LVRATabNum[index]);
  fprintf(output, ")\n");
}
#endif


/* LVRAInsertFreeElement add a value repetition to the 
 * Free List Table. 
 */
static LVRAInsertFreeElement(freeRep)
     ref(ValRep) freeRep;
{ int index; 
  ref(ValRep) headRep;
  
  LVRAFreeListAvailable = TRUE;
  index = LVRATableIndex(freeRep->HighBorder );
  /* Insert the repetition as the first element in the list. */
  DEBUG_LVRA( { struct ValRep *cur = LVRATable[index];
		while( cur ){ Claim( cur != freeRep,"LVRAInsert"); 
			      cur = (struct ValRep *) cur->Proto;}
		
	      } );
  headRep = LVRATable[index];  LVRATable[index] = freeRep;
  freeRep->Proto  = (ref(ProtoType)) headRep;
  freeRep->GCAttr = 0; 
  DEBUG_CODE( if( index == TableMAX )
	     fprintf(output, "(LVRAInsert=%d)", freeRep->HighBorder));
  DEBUG_CODE(LVRATabNum[index]++);
}

/* LVRAFindInFree tries to find space for at repetition with size given by
 * proto and range.
 * A first shut is to find a equally sized repetition in the free list.
 * Second try is to find a larger repetition in the free list and split it
 * into two repetitions. 
 * If none of the above tries succeed, the function returns 0.
 */
static ref(ValRep) LVRAFindInFree(proto, range)
     int proto ;
     long range;
{
  ref(ValRep) currentRep;
  ptr(long)   takenFrom;
  long bodysize = DispatchValRepBodySize(cast(ProtoType)proto, range) 
    /* body size of the requested rep */;
  int index = LVRATableIndex( range );
  DEBUG_CODE(int oldBorder);
  
  takenFrom = (ptr(long)) &LVRATable[index];
  currentRep = (ref(ValRep)) LVRATable[index];
  while( currentRep ){
    if( currentRep->HighBorder == bodysize ){
      /* Update the chain in the freeList. */
      *takenFrom = (long) currentRep->Proto;
      
      DEBUG_CODE(LVRATabNum[index]--);
      /* Initialize the returned repetition. */
      currentRep->Proto      = cast(ProtoType)proto;
      currentRep->GCAttr     = 0;
      
      return currentRep;
    }
    takenFrom =  (ptr(long))   &currentRep->Proto;
    currentRep = (ref(ValRep))  currentRep->Proto;
  }
  
  /* Didn't find equally size rep. Try finding a bigger one */
  do {
    ref(ValRep) restRep;
    long rest; /* size left after split */
    
    takenFrom = (ptr(long)) &LVRATable[index];
    currentRep = (ref(ValRep)) LVRATable[index];
    while( currentRep != 0 ){
      if( currentRep->HighBorder >= bodysize + headsize(ValRep) ){
        /* Update the chain in the freeList. */
	*takenFrom = (long) currentRep->Proto;
	
        DEBUG_CODE( LVRATabNum[index]--);
        DEBUG_CODE( oldBorder = currentRep->HighBorder );
	
	rest = currentRep->HighBorder - bodysize - headsize(ValRep);
	
        currentRep->Proto      = cast(ProtoType)proto;
	currentRep->GCAttr     = 0;
	currentRep->LowBorder  = 1;
	currentRep->HighBorder = range;
	
        /* Use the rest to a new repetition, and insert it in the free list. */
	restRep = (ref(ValRep)) Offset(currentRep, headsize(ValRep)+bodysize);
        restRep->Proto      = 0;
        restRep->GCAttr     = 0;
	restRep->LowBorder  = 1;
	restRep->HighBorder = rest;
	LVRAInsertFreeElement(restRep);
        /*DEBUG_LVRA( Claim( ValRepSize( oldBorder) ==
	  (ValRepSize(currentRep->HighBorder)
	  + ValRepSize(restRep->HighBorder)),
	  "#LVRAFindInFree: old = new + rest"));*/      
	return currentRep;
      }
      takenFrom =  (ptr(long))   &currentRep->Proto;
      currentRep = (ref(ValRep))  currentRep->Proto;
    }
    index++;
  } while( index <= TableMAX );
  return 0;
}

/*************************** LVRA Blocks ***********************************/

#define inLVRABlock(theB, addr) (LVRABlockStart(theB) <= (ptr(long)) addr \
				 && (ptr(long)) addr < theB->top)

static ref(LVRABlock) newLVRABlock(size)
     int size;
{
  ref(LVRABlock) theBlock;
  int            blocksize = (size>LVRABlockSize) ? size : LVRABlockSize;
  
  theBlock = (ref(LVRABlock)) MALLOC( sizeof(struct LVRABlock) + blocksize );
  
  if( theBlock != 0 ){
    INFO_LVRA( fprintf( output, "#(LVRA: new block allocated %dKb)\n",
		       toKb(blocksize))); 
    LVRANumOfBlocks++;
    
    theBlock->next  = 0;
    theBlock->state = 0;
    theBlock->top   = LVRABlockStart( theBlock );
    theBlock->limit = (ptr(long)) ((long) LVRABlockStart(theBlock) + (long) blocksize);
  } else {
    MallocExhausted = TRUE;
    INFO_LVRA(fprintf(output ,"#(LVRA: failed to allocate new block %dKb)\n", 
		      toKb(blocksize))); 
  }
  return theBlock;
}

int inLVRA(theObj )
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

static long LVRARestInBlock(theBlock)
     ref(LVRABlock) theBlock;
{
  return (long) theBlock->limit - (long) theBlock->top;
}

/* Allocate repetition with range in LVRATopBlock->[top..limit]. */
static ref(ValRep)LVRAAllocInBlock(proto, range, size)
     int         proto;
     long        range;
     long        size;
{
  ref(ValRep) newRep;
  ptr(long)   newTop;
  
  newRep = (ref(ValRep)) LVRATopBlock->top;
  if( (newTop = (ptr(long)) Offset(newRep,size))<= LVRATopBlock->limit){
    LVRATopBlock->top  = newTop;
    newRep->Proto      = cast(ProtoType)proto;
    newRep->GCAttr     = 0;
    newRep->LowBorder  = 1;
    newRep->HighBorder = range;
    return newRep;
  }
  return 0;
}

/* LVRAAlloc: allocate a Value repetition in the LVRArea.
 */
ref(ValRep) LVRAAlloc(proto, range)
     int  proto;
     long range;
{
  ref(ValRep)    newRep;
  long           size = DispatchValRepSize(cast(ProtoType)proto, range);
  ref(LVRABlock) block;
  long           rest;
  
  INFO_LVRA_ALLOC( fprintf( output, "<%d>", range) );
  if( LVRABaseBlock == 0 ){
    /* No LVRA blocks allocated yet */
    if( LVRABlockSize == 0) return 0;
    if( MallocExhausted ) return 0;
    if( (LVRABaseBlock = newLVRABlock(size) ) == 0 ){
      MallocExhausted = TRUE; return 0;
    }
    LVRATopBlock = LVRABaseBlock;
  }
  if( LVRAFreeListAvailable )
    /* Try allocation in freeList */
    if( newRep = LVRAFindInFree(proto, range) ) return newRep;
  
  /* Allocation in freeList failed. Try allocation in top block */
  if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;
  
  /* Allocation in top block failed. Mark rest of top block as free */
  rest = LVRARestInBlock(LVRATopBlock);
  if( rest >= 0 ){
    newRep = (ref(ValRep)) LVRATopBlock->top;
    newRep->Proto      = 0;
    newRep->GCAttr     = 0;
    newRep->LowBorder  = 1;
    newRep->HighBorder = rest;
    LVRATopBlock->top =  (ptr(long)) Offset(LVRATopBlock->top, rest);
  }
  
  if( LVRALastIOAGc != NumIOAGc){
    /* Try redoing the free list */
    LVRAConstructFreeList();
    /* Try allocation by the new freelist */
    if( newRep = LVRAFindInFree(proto, range) ) return newRep;
    
    if( LVRATopBlock->next ){
      LVRATopBlock = LVRATopBlock->next;
      if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;       
    }
    if( LVRACreateNewBlock || (range > LVRABigRange) ){
      if( (block = newLVRABlock(size)) == 0) return 0;
      block->next        = LVRATopBlock->next;
      LVRATopBlock->next = block;
      
      LVRATopBlock = LVRATopBlock->next;
      LVRACreateNewBlock = FALSE;
      if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;
    }
  }
  
  /* No IOAGc's since last freelist was constructed. Do an LVRA compaction */
  LVRACompaction();
  
  /* Now try allocation in top block */
  if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;
  /* Allocation in top block failed. Try using the free list */
  if( newRep = LVRAFindInFree(proto, range) ) return newRep;
  
  /* Try the next block */
  if( LVRATopBlock->next ){
    LVRATopBlock = LVRATopBlock->next;
    if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;
  }
  
  /* None of the above succeeded. Try allocating a new block */
  if( (block = newLVRABlock(size)) == 0) return 0;
  block->next        = LVRATopBlock->next;
  LVRATopBlock->next = block;
  LVRATopBlock = LVRATopBlock->next;
  LVRACreateNewBlock = FALSE;
  
  /* Try allocating in the new top block */
  if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;
  
  /* All hope is gone ! */
  return 0;
}

/* CopyObjectToLVRA: called from NewCopyObject */

ref(ValRep) CopyObjectToLVRA(proto, theRep)
     int         proto;
     ref(ValRep) theRep;
{
  ref(ValRep) newRep;
  long range, index;
  ptr(long) src;
  ptr(long) dst;
  
  range = theRep->HighBorder;
  if( (newRep = LVRAAlloc(proto, range)) != 0 ){
    
    src = &theRep->Body[0]; dst = &newRep->Body[0];
    for(index=0; 
	index< DispatchValRepBodySize(cast(ProtoType)proto, range); 
	index++)
      *dst++ = *src++;
    
    newRep->GCAttr = 0;
    /* Set one forward reference in theObj to newObj */
    theRep->GCAttr = (long) newRep;
  }
  /* Return the new object in ToSpace */
  return newRep;
}

/********************** LVRA garbage collection *************************/

static LVRACompaction()
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
  
  LVRACleanTable();
  
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
      theObjectSize = DispatchValRepSize(srcRep->Proto, 
					 srcRep->HighBorder-srcRep->LowBorder+1
					 );
      if( alive ){
	if( srcRep != dstRep ){
	  long size, index, rest;
	  ptr(long) src;
	  ptr(long) dst;
	  
	  while( Offset( dstRep, theObjectSize) > (long) dstBlock->limit){
	    /* Not possible to allocate object in dstBlock. */
	    dstBlock->top = (ptr(long)) dstRep;
	    rest = LVRARestInBlock(LVRATopBlock);
	    if( rest >= 0 ){
	      dstRep = (ref(ValRep)) LVRATopBlock->top;
	      dstRep->Proto      = 0;
	      dstRep->GCAttr     = 0;
	      dstRep->LowBorder  = 1;
	      dstRep->HighBorder = rest;
	      dstBlock->top =  (ptr(long)) Offset(dstBlock->top, rest);
	      saved += rest;
	      LVRAInsertFreeElement(dstRep);
	    }
	    dstBlock = dstBlock->next;
	    DEBUG_LVRA( Claim( dstBlock, "LVRACompaction: dstBlock"));
	    dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);
	  }
	  size = srcRep->HighBorder-srcRep->LowBorder+1;
	  
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
      srcRep = (ref(ValRep)) (((long) srcRep) + theObjectSize);
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
  DEBUG_AOA(if( LVRACreateNewBlock ) 
	    fprintf(output, " (new block needed in next LVRAAlloc) "));
  
  INFO_LVRA(fprintf(output, " %dKb in %d blocks, %d%% free)\n",
		    toKb(sizeBlocks), numBlocks, (100*saved)/sizeBlocks));
  LVRALastIOAGc = 0;
}

static LVRAAlive(theRep)
     ref(ValRep) theRep;
{
  if(!isValRep(theRep) ){
    DEBUG_LVRA( Claim( theRep->GCAttr == 0,"LVRAAlive: theRep->GCAttr == 0"));
    return FALSE;
  }
  DEBUG_LVRA( Claim( theRep->GCAttr , "LVRAAlive: theRep->GCAttr != 0"));
  
  return ((long) theRep == *((long *) theRep->GCAttr));
}

static LVRAConstructFreeList()
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
  
  INFO_LVRA(fprintf( output, "#(LVRA: make free list")); 
  
  LVRACleanTable();
  
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
      theObjectSize = DispatchValRepSize(currentValRep->Proto, 
					 currentValRep->HighBorder);
      
      if( startRep ){
	if( alive ){ 
	  LVRAInsertFreeElement( startRep );
	  saved += DispatchValRepSize(startRep->Proto, startRep->HighBorder);
          DEBUG_LVRA( Claim( (saved > 0) && (saved <= sizeBlocks),
			    "#LVRAMakeFree: (saved > 0) && (saved <= sizeBlocks)"));
          startRep = 0;
	}else{
	  /* Connect [startRep..currentRep] to one object, by enlarging the 
	   * startRep HighBorder
	   */
	  startRep->HighBorder+=DispatchValRepSize(currentValRep->Proto,
						   currentValRep->HighBorder);
	}
      }else{
	if( !alive )
	  startRep = currentValRep;
      }
      
      currentValRep = (ref(ValRep)) (((long) currentValRep)+theObjectSize);
    }
    if( startRep ){
      LVRAInsertFreeElement( startRep );
      saved += DispatchValRepSize(startRep->Proto, startRep->HighBorder);
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
      theObjectSize = DispatchValRepSize(currentValRep->Proto,
					 currentValRep->HighBorder);
      currentValRep = (ref(ValRep)) (((long) currentValRep)+theObjectSize);
    }
    Claim( (long *) currentValRep == theBlock->top,
          "#LVRACheck: currentValRep == theBlock->top");
    /* Take the next element in the LVRA block chain. */
    theBlock = theBlock->next;
  }
} 
#endif
