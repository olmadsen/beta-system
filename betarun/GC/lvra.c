/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $Id: lvra.c,v 1.27 1992-10-07 15:59:38 beta Exp $
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

static LVRACompaction();
#ifdef RTDEBUG
int LVRAAlive();
#endif
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

#ifdef RTDEBUG
int LVRAAlive(theRep)
     ref(ValRep) theRep;
{
  int alive;

  if(!isValRep(theRep) ){
    DEBUG_LVRA( Claim( theRep->GCAttr == 0,"LVRAAlive: theRep->GCAttr == 0"));
    return FALSE;
  }
  alive = theRep->GCAttr && ((long) theRep == *((long *) theRep->GCAttr));
  DEBUG_LVRA(Claim(!alive || theRep->GCAttr ,
		   "LVRAAlive: !alive || theRep->GCAttr != 0"));
  
  return alive;
}
#else
#define LVRAAlive(rep) \
  (isValRep(rep) && (rep)->GCAttr && (long) (rep) == *(long *) (rep)->GCAttr)
#endif

long LVRARepSize(rep)
     struct ValRep *rep;
{
  if (LVRAAlive(rep))
    return DispatchValRepSize(rep->Proto, rep->HighBorder-rep->LowBorder+1);
  else {
    /* 'rep' died behind our backs. Maintain LVRARep invariant:
     *  if alive then
     *    size = DispatchValRepSize....
     *  else
     *    size = rep->HighBorder
     */
    if (rep->GCAttr) {
      rep->GCAttr = 0;
      rep->HighBorder =
	DispatchValRepSize(rep->Proto, rep->HighBorder-rep->LowBorder+1);
    }
    DEBUG_LVRA( Claim( rep->HighBorder, "LVRARepSize: rep->HighBorder!=0"));
    return rep->HighBorder;
  }
}

/* RepCopy copies a repetition from src to dst. This is it's own
   routine to keep some of the size confusion in one place
*/
static void RepCopy(dst, src)
     struct ValRep *dst, *src;
{
  /* size is in longs, DispatchValRepSize in bytes */
  int size = DispatchValRepSize(src->Proto, src->HighBorder-src->LowBorder+1)
    / sizeof(long);
  int i, *d = (int *) dst, *s = (int *) src;
  Claim( dst!=src, "RepCopy: dst!=src");
  for (i = 0; i < size; ++i) *d++ = *s++;
}

/************************ THE LVRA FREE LIST ********************************
 * When a repetition 'rep' is in the free list, rep->Proto points to next
 * free element, rep->GCattr is 0 (the rep is not alive), and rep->highborder
 * is the number of BYTES in the entire repetition.
 */


/* LVRAtableIndex find a index in the Table in the range [0..TableMAX].
 * The index is a sort of a log2 function.
 * f(16) = 0; f(32) = 1 ..... f(64Kb) = 12; f(128Kb) = 13 etc.
 * The returned value is <= TableMAX.
 */
static int LVRATableIndex(size)
     int size;
{ int index = 0; size >>= 4;
  while ((size >>= 1) != 0) index++;
  if (index > TableMAX) index = TableMAX;
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
  index = LVRATableIndex(freeRep->HighBorder);
  /* Insert the repetition as the first element in the list. */
  DEBUG_LVRA( { struct ValRep *cur = LVRATable[index];
		while( cur ){ Claim( cur != freeRep,"LVRAInsert"); 
			      cur = (struct ValRep *) cur->Proto;}
		
	      } );
  headRep = LVRATable[index];  LVRATable[index] = freeRep;
  freeRep->Proto  = (ref(ProtoType)) headRep;
  freeRep->GCAttr = 0; 
  DEBUG_CODE( if( index == TableMAX )
	     fprintf(output, "(LVRAInsertFreeElement: size=%d (0x%x))", 
		     freeRep->HighBorder,
		     freeRep->HighBorder));
  DEBUG_CODE(LVRATabNum[index]++);
}

/* LVRAFindInFree tries to find space for at repetition with size given by
 * proto and range.
 * A first shut is to find a equally sized repetition in the free list.
 * Second try is to find a larger repetition in the free list and split it
 * into two repetitions. 
 * If none of the above tries succeed, the function returns 0.
 */
static ref(ValRep) LVRAFindInFree(proto, range, size)
     ref(ProtoType) proto ;
     long range;
     long size;
{
  ref(ValRep) currentRep;
  ptr(long)   takenFrom;
  int index = LVRATableIndex(size);
  DEBUG_CODE(int oldBorder);
  
  DEBUG_LVRA(Claim(size == DispatchValRepSize(proto, range),
		   "proto+range => size\n"));
  takenFrom = (ptr(long)) &LVRATable[index];
  currentRep = (ref(ValRep)) LVRATable[index];
  while( currentRep ){
    if( currentRep->HighBorder == size) {
      /* Update the chain in the freeList. */
      *takenFrom = (long) currentRep->Proto;
      
      DEBUG_CODE(LVRATabNum[index]--);
      /* Initialize the returned repetition. */
      currentRep->Proto      = proto;
      currentRep->GCAttr     = 0;
      currentRep->LowBorder  = 1;
      currentRep->HighBorder = range;

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
      if( currentRep->HighBorder >= size) {
        /* Update the chain in the freeList. */
	*takenFrom = (long) currentRep->Proto;
	
        DEBUG_CODE( LVRATabNum[index]--);
        DEBUG_CODE( oldBorder = currentRep->HighBorder );
	
	rest = currentRep->HighBorder - size;
	
        currentRep->Proto      = proto;
	currentRep->GCAttr     = 0;
	currentRep->LowBorder  = 1;
	currentRep->HighBorder = range;
	
        /* Use the rest to a new repetition, and insert it in the free list. */
	restRep = (ref(ValRep)) Offset(currentRep, size);
        restRep->Proto      = 0;
        restRep->GCAttr     = 0;
	restRep->LowBorder  = 1;
	restRep->HighBorder = rest;
	LVRAInsertFreeElement(restRep);
        DEBUG_LVRA(Claim(oldBorder == 
			 (DispatchValRepSize(currentRep->Proto,
					     currentRep->HighBorder)
			  + restRep->HighBorder),
			 "#LVRAFindInFree: old = new + rest"));
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
  ref(LVRABlock)  theBlock = LVRABaseBlock;
  
  while (theBlock) {
    if (inLVRABlock(theBlock, theObj)) return TRUE;
    theBlock = theBlock->next;
  }
  return FALSE;
}

/* Needs to be non-static, since ~beta/Xt/.../private/external/getarg.c
 * uses it
 */
long LVRARestInBlock(theBlock)
     ref(LVRABlock) theBlock;
{
  return (long) theBlock->limit - (long) theBlock->top;
}

/* Allocate repetition with range in LVRATopBlock->[top..limit]. */
static ref(ValRep)LVRAAllocInBlock(proto, range, size)
     ref(ProtoType) proto;
     long           range;
     long           size;
{
  ref(ValRep) newRep;
  ptr(long)   newTop;
  
  DEBUG_LVRA(Claim(size == DispatchValRepSize(proto, range),
		   "proto+range => size\n"));
  newRep = (ref(ValRep)) LVRATopBlock->top;
  if( (newTop = (ptr(long)) Offset(newRep,size))<= LVRATopBlock->limit){
    LVRATopBlock->top  = newTop;
    newRep->Proto      = proto;
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
     ref(ProtoType)  proto;
     long range;
{
  ref(ValRep)    newRep;
  long           size = DispatchValRepSize(proto, range);
  ref(LVRABlock) block;
  long           rest;

  DEBUG_LVRA(fprintf(output, 
		     "#LVRAAlloc(proto= %d, range= %d, size= %d (0x%x))\n",
		     proto, range, size, size));
  DEBUG_LVRA(Claim(isSpecialProtoType(proto), "isSpecialProtoType(proto)"));  
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
    if( newRep = LVRAFindInFree(proto, range, size) ) return newRep;
  
  /* Allocation in freeList failed. Try allocation in top block */
  if( newRep = LVRAAllocInBlock(proto, range, size) ) return newRep;
  
  /* Allocation in top block failed. Mark rest of top block as free */
  rest = LVRARestInBlock(LVRATopBlock);
  if( rest > 0 ){
    newRep = (ref(ValRep)) LVRATopBlock->top;
    newRep->Proto      = 0;
    newRep->GCAttr     = 0;
    newRep->LowBorder  = 1;
    newRep->HighBorder = rest;
    LVRATopBlock->top =  LVRATopBlock->limit;
    if (LVRALastIOAGc == NumIOAGc)	/* Freelist will not be constructed */
      LVRAInsertFreeElement(newRep);	/* below. Remember this free space  */
  }
  
  if (LVRALastIOAGc != NumIOAGc){
    /* Try redoing the free list */
    LVRAConstructFreeList();
    /* Try allocation by the new freelist */
    if( newRep = LVRAFindInFree(proto, range, size) ) return newRep;
    
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
  if( newRep = LVRAFindInFree(proto, range, size) ) return newRep;
  
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
  DEBUG_LVRA(fprintf(output, "#LVRAAlloc failed!\n"));
  return 0;
}

void LVRAkill(rep)
     struct ValRep *rep;
{
  rep->HighBorder = DispatchValRepSize(rep->Proto,
				       rep->HighBorder-rep->LowBorder+1);
  rep->Proto = 0;
  rep->GCAttr = 0;
}

/* CopyObjectToLVRA: called from NewCopyObject */

ref(ValRep) CopyObjectToLVRA(theRep)
     ref(ValRep) theRep;
{
  ref(ValRep) newRep;
  
  DEBUG_LVRA(fprintf(output, "#CopyObjectToLVRA(%d, %d)\n",
		     theRep->Proto,
		     theRep->HighBorder-theRep->LowBorder+1
		     ));
  if (newRep = LVRAAlloc(theRep->Proto,
			 theRep->HighBorder-theRep->LowBorder+1)) {
      RepCopy(newRep, theRep);
      newRep->GCAttr = 0;
      /* Set one forward reference in theObj to newObj */
      theRep->GCAttr = (long) newRep;
  }
  /* Return the new object in ToSpace */
  DEBUG_LVRA(fprintf(output, "#COPYObjectToLVRA: newRep=0x%x\n", newRep));
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
  long           srcSize;
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
      srcSize = LVRARepSize(srcRep);
      if (alive = LVRAAlive(srcRep)) {
	if (srcRep != dstRep) {
	  long rest;
	  /* srcRep is alive. Find place to move it to in dstBlock 
	   * (if possible)
	   */
	  while( Offset( dstRep, srcSize) > (long) dstBlock->limit){
	    /* Not room for srcRep in dstBlock.
	     * Put rest of dstBlock in free list
	     */
	    dstBlock->top = (ptr(long)) dstRep;
	    rest = LVRARestInBlock(LVRATopBlock);
	    if( rest > 0 ){
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

	  /* Move srcRep */
	  if (srcRep == dstRep){
	    /* srcRep could not be moved "down" in the LVRA */
	  } else {
	    /* Preserve the LVRA-cycle */
	    *((ptr(long)) srcRep->GCAttr) = (long) dstRep;
	    RepCopy(dstRep, srcRep);
	  }

	} /* srcRep != dstRep */
	dstRep = (ref(ValRep)) ((long) dstRep + srcSize );

      } /* srcRep alive */
      srcRep = (ref(ValRep)) (((long) srcRep) + srcSize);

    } /* while */
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
    
    while (((ptr(long))currentValRep) < currentLVRABlock->top) {
      theObjectSize = LVRARepSize(currentValRep);
      alive = LVRAAlive(currentValRep);
      if (startRep) {
	if (alive) { 
	  LVRAInsertFreeElement(startRep);
	  saved += startRep->HighBorder;
          DEBUG_LVRA( Claim( (saved > 0) && (saved <= sizeBlocks),
			    "#LVRAMakeFree: (saved > 0) && (saved <= sizeBlocks)"));
          startRep = 0;
	} else {
	  /* Connect [startRep..currentRep] to one object, by enlarging the 
	   * startRep HighBorder
	   */
	  startRep->HighBorder += currentValRep->HighBorder;
	}
      } else {
	if (!alive)
	  startRep = currentValRep;
      }
      currentValRep = (ref(ValRep)) (((long) currentValRep)+theObjectSize);
    }
    if( startRep ){
      LVRAInsertFreeElement( startRep );
      saved += startRep->HighBorder;
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
  DEBUG_AOA(if (LVRACreateNewBlock) fprintf(output, " (new block needed) "));
  
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
  ref(ValRep)    rep;
  int theObjectSize;
  
  theBlock = LVRABaseBlock;
  while( theBlock ){    
    /* traverse currentLVRABlock. */
    rep = (ref(ValRep)) LVRABlockStart(theBlock);
    while ((long *)rep < theBlock->top) {
      theObjectSize = LVRARepSize(rep);
      rep = (struct ValRep *) ((long)rep + theObjectSize);
    }
    Claim( (long *) rep == theBlock->top,
          "#LVRACheck: rep == theBlock->top");
    /* Take the next element in the LVRA block chain. */
    theBlock = theBlock->next;
  }
} 
#endif
