/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * lvra.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

static void LVRACompaction(void);
static void LVRAConstructFreeList(void);

#define TableMAX 16

/* non-static since referred from heapview.c */
GLOBAL(struct LVRABlock *LVRABaseBlock);
GLOBAL(static struct LVRABlock *LVRATopBlock);

GLOBAL(static long LVRAFreeListAvailable) = FALSE;
GLOBAL(static long LVRACreateNewBlock)    = FALSE;
/* non-static since referred from heapview.c */
GLOBAL(long LVRANumOfBlocks)       = 0;

/* LVRALastIOAGc contains the value of NumIOAGc last time
 * LVRAConstructFreeList was executed.
 */
GLOBAL(static long LVRALastIOAGc)         = 0;

#define LVRABigRange 100 * 256    /* ~ValRepSize > 100 Kb. */

GLOBAL(static struct ValRep *LVRATable[TableMAX+1]);

DEBUG_CODE(GLOBAL(long LVRATabNum[TableMAX+1]))

#ifdef RTDEBUG

void LVRACheck(void);
void LVRAStatistics(void);

long LVRAAlive(ref(ValRep) theRep)
{
  if(!isValRep(theRep) ){
    return FALSE;
  }

  if (!theRep->GCAttr){
    return FALSE;
  }
  
  /* FIXME: Why does this make lvra go bananas?
  if (inToSpace(theRep->GCAttr)){
    / LVRAAlive is never called during IOAGc, so pointers from ToSpace are not roots /
    return FALSE;
  }
  */

  if (! ((long) theRep == *((long *) theRep->GCAttr))){
    return FALSE;
  }

  return TRUE;
}
#else
#define LVRAAlive(rep) \
  (isValRep(rep) && (rep)->GCAttr && (long) (rep) == *(long *) (rep)->GCAttr)
#endif

long LVRARepSize(struct ValRep *rep)
{
  if (LVRAAlive(rep)) {
    /* rep->GCAttr <> 0 */
    return DispatchValRepSize(rep->Proto, rep->HighBorder-rep->LowBorder+1);
  } else {
    /* rep->GCAttr may be 0 */
    if (rep->GCAttr) {
      /* 'rep' died behind our backs. Maintain LVRARep invariant:
       *  if alive then
       *    LVRARepSize = DispatchValRepSize.... (size in BYTES)
       *  else
       *    rep->GCAttr = 0
       *    LVRARepSize = rep->HighBorder (size in bytes previously calculated)
       */
      rep->GCAttr = 0;
      rep->HighBorder =
	DispatchValRepSize(rep->Proto, rep->HighBorder-rep->LowBorder+1);
      /* FIXME: Use LVRAKill instead !!! */
    }
    /* rep->GCAttr == 0 */
    DEBUG_LVRA( Claim( rep->HighBorder>= headsize(ValRep), 
		      "LVRARepSize: rep->HighBorder>= headsize(ValRep) for dead rep"));
    return rep->HighBorder;
  }
}

/* RepCopy copies a repetition from src to dst. This is its own
 * routine to keep some of the size confusion in one place
 */
static void RepCopy(struct ValRep *dst, struct ValRep *src)
{
  DEBUG_LVRA(Claim( dst!=src, "RepCopy: dst!=src"));
  memcpy(dst, src, DispatchValRepSize(src->Proto, src->HighBorder-src->LowBorder+1)); 
  /* Old code contained in comments below. TO BE REMOVED */
  /* size is in longs, DispatchValRepSize in bytes */
  /* long size = DispatchValRepSize(src->Proto, src->HighBorder-src->LowBorder+1)
     / sizeof(long); */
  /* long i, *d = (long *) dst, *s = (long *) src; */
  /* for (i = 0; i < size; ++i) *d++ = *s++; */
}

/************************ THE LVRA FREE LIST ********************************
 * When a repetition 'rep' is in the free list, rep->Proto points to next
 * free element, rep->GCattr is 0 (the rep is not alive), and rep->highborder
 * is the number of BYTES in the entire repetition (invariant).
 */


/* LVRAtableIndex finds an index in the Table in the range [0..TableMAX].
 * The index is a sort of a log2 function.
 * f(16) = 0; f(32) = 1 ..... f(64Kb) = 12; f(128Kb) = 13 etc.
 * The returned value is <= TableMAX.
 */
static long LVRATableIndex(unsigned long size)
{ long index = 0; 
  size >>= 4;
  while ((size >>= 1) != 0) index++;
  if (index > TableMAX) index = TableMAX;
  return index; 
}


/* LVRACleanTable initializes the Free List Table */
static void LVRACleanTable(void)
{ 
  long index;
  
  for (index=0; index<=TableMAX; index++) 
    LVRATable[index] = 0;
  LVRAFreeListAvailable = FALSE;
  DEBUG_CODE(for(index=0;index <= TableMAX; index++) LVRATabNum[index]=0 );
}

#ifdef RTDEBUG
static void LVRADisplayTable(void)
{ 
  long index;

  fprintf(output, "#(Free reps in LVRATable: ");
  for(index=0;index <= TableMAX; index++)
    if(LVRATable[index] )
      fprintf(output, "%d:%d ", (int)index, (int)LVRATabNum[index]);
  fprintf(output, ")\n");
}
#endif


/* LVRAInsertFreeElement adds a value repetition to the Free List Table. 
 * Precondition: freeRep->GCattr==0 AND freeRep->Highborder is
 * the total size of freeRep i BYTES.
 */
static void LVRAInsertFreeElement(ref(ValRep) freeRep)
{ long index; 
  ref(ValRep) headRep;
  
  DEBUG_LVRA(Claim(!LVRAAlive(freeRep), "#LVRAInsertFreeElement: !LVRAAlive(freeRep)"));
  DEBUG_LVRA(Claim(freeRep->HighBorder>=headsize(ValRep), 
		   "#LVRAInsertFreeElement: freeRep->HighBorder>=headsize(ValRep)"));
  LVRAFreeListAvailable = TRUE;
  index = LVRATableIndex(freeRep->HighBorder);
  /* Insert the repetition as the first element in the list. */
  DEBUG_LVRA( { struct ValRep *cur = LVRATable[index];
		while( cur ){ Claim( cur != freeRep,"LVRAInsert"); 
			      cur = (struct ValRep *) cur->Proto;}
		
	      } );
  headRep = LVRATable[index];  LVRATable[index] = freeRep;
  freeRep->Proto  = (ref(ProtoType)) headRep;
  freeRep->GCAttr = 0; /* FIXME: NOT NEEDED always done before this func is called? Change into assumption */
  DEBUG_CODE( if( index == TableMAX )
	     fprintf(output, "(LVRAInsertFreeElement: size=%d (0x%x))", 
		     (int)freeRep->HighBorder,
		     (int)freeRep->HighBorder));
  DEBUG_CODE(LVRATabNum[index]++);
}

/* LVRAFindInFree tries to find space for a repetition with size given by
 * proto and range.
 * A first shot is to find an equally sized repetition in the free list.
 * Second try is to find a larger repetition in the free list and split it
 * into two repetitions. 
 * If none of the above tries succeed, the function returns 0.
 */
static ref(ValRep) 
LVRAFindInFree(ref(ProtoType) proto, long range, unsigned long size)
{
  ref(ValRep) currentRep;
  ptr(long)   takenFrom;
  long index = LVRATableIndex(size);
  DEBUG_CODE(long oldBorder);
  
  DEBUG_LVRA(Claim(isSpecialProtoType(proto), "isSpecialProtoType(proto)"));
  DEBUG_LVRA(Claim(size == DispatchValRepSize(proto, range),
		   "proto+range => size\n"));
  takenFrom = (ptr(long)) &LVRATable[index];
  currentRep = (ref(ValRep)) LVRATable[index];
  while( currentRep ){
    if( currentRep->HighBorder == (long)size) {
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
      if( currentRep->HighBorder >= (long)(size+headsize(ValRep))) {
	/* currentRep is large enough for a repetition of size 'size', and
	 * at least an empty repetition too.
	 */

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
	restRep->HighBorder = rest; /* size in bytes */
	LVRAInsertFreeElement(restRep);
        DEBUG_LVRA(Claim(oldBorder == 
			 (long)(DispatchValRepSize(currentRep->Proto,
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

static ref(LVRABlock) newLVRABlock(long size)
{
  ref(LVRABlock) theBlock;
  long            blocksize = (size>LVRABlockSize) ? size : LVRABlockSize;
  
  theBlock = (ref(LVRABlock)) MALLOC( sizeof(struct LVRABlock) + blocksize );
  
  if( theBlock != 0 ){
    INFO_LVRA( fprintf(output, "#(LVRA: new block allocated %dKb)\n",
		       (int)toKb(blocksize))); 
    LVRANumOfBlocks++;
    
    theBlock->next  = 0;
    theBlock->state = 0;
    theBlock->top   = LVRABlockStart( theBlock );
    theBlock->limit = (ptr(long)) ((long) LVRABlockStart(theBlock) + (long) blocksize);
  } else {
    MallocExhausted = TRUE;
    INFO_LVRA(fprintf(output ,"#(LVRA: failed to allocate new block %dKb)\n", 
		      (int)toKb(blocksize))); 
  }
  return theBlock;
}

long inLVRA(ref(Object) theObj)
{
  ref(LVRABlock)  theBlock = LVRABaseBlock;
  
  while (theBlock) {
    if (inLVRABlock(theBlock, theObj)) return TRUE;
    theBlock = theBlock->next;
  }
  return FALSE;
}

static long LVRARestInBlock(ref(LVRABlock) theBlock)
{
  return (long) theBlock->limit - (long) theBlock->top;
}

/* Allocate repetition with range in LVRATopBlock->[top..limit[. */
static ref(ValRep)LVRAAllocInBlock(ref(ProtoType) proto, long range, long size)
{
  ref(ValRep) newRep;
  ptr(long)   newTop;
  
  DEBUG_LVRA(Claim(size == (long)DispatchValRepSize(proto, range),
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

/* LVRAAlloc: allocate a Value repetition in the LVRA area.
 */
ref(ValRep) LVRAAlloc(ref(ProtoType) proto, long range)
{
  ref(ValRep)    newRep;
  long           size;
  ref(LVRABlock) block;
  long           rest;

  MT_CODE(mutex_lock(&lvra_lock));

  size = DispatchValRepSize(proto, range);
  INFO_LVRA_ALLOC({
    char type[30];
    switch (SwitchProto(proto)){
    case SwitchProto(LongRepPTValue):
      sprintf(type, "integer repetition");
      break;
    case SwitchProto(ByteRepPTValue):
      sprintf(type, "char repetition");
      break;
    case SwitchProto(DoubleRepPTValue):
      sprintf(type, "real repetition");
      break;
    case SwitchProto(ShortRepPTValue):
      sprintf(type, "shortint repetition");
      break;
    default:
      sprintf(type, "repetition type %d", (int)proto);
      break;
    }
    fprintf(output, 
	    "#(LVRAAlloc: %s, range = %d, size = %d)\n",
	    type, (int)range, (int)size);
  });
  DEBUG_LVRA(Claim(isSpecialProtoType(proto), "isSpecialProtoType(proto)"));  
  if( LVRABaseBlock == 0 ){
    /* No LVRA blocks allocated yet */
    if( LVRABlockSize == 0) { newRep = 0; goto exit; }
    if( MallocExhausted ) { newRep = 0; goto exit; }
    if( (LVRABaseBlock = newLVRABlock(size) ) == 0 ){
      MallocExhausted = TRUE; 
      newRep = 0;
      goto exit;
    }
    LVRATopBlock = LVRABaseBlock;
  }
  if( LVRAFreeListAvailable )
    /* Try allocation in freeList */
    if( (newRep = LVRAFindInFree(proto, range, size)) ) goto exit;
  
  /* Allocation in freeList failed. Try allocation in top block */
  if( (newRep = LVRAAllocInBlock(proto, range, size)) ) goto exit;
  
  /* Allocation in top block failed. Mark rest of top block as free */
  rest = LVRARestInBlock(LVRATopBlock);
  if ( rest > 0 ) {
    if( rest >= headsize(ValRep) ){
      newRep = (ref(ValRep)) LVRATopBlock->top;
      newRep->Proto      = 0;
      newRep->GCAttr     = 0;
      newRep->LowBorder  = 1;
      newRep->HighBorder = rest; /* size in bytes */
      LVRATopBlock->top =  LVRATopBlock->limit;
      if (LVRALastIOAGc == NumIOAGc)	/* Freelist will not be constructed */
	LVRAInsertFreeElement(newRep);	/* below. Remember this free space  */
    } else {
      long *p;
      DEBUG_LVRA(fprintf(output, "#LVRAAlloc: LVRARestInBlock < headsize(ValRep)\n"));
      for (p=LVRATopBlock->top; p<LVRATopBlock->limit; p++) *p = 0;
    }
  }

  if (LVRALastIOAGc != NumIOAGc){
    /* Try redoing the free list */
    LVRAConstructFreeList();
    /* Try allocation by the new freelist */
    if( (newRep = LVRAFindInFree(proto, range, size)) ) goto exit;
    
    if( LVRATopBlock->next ){
      LVRATopBlock = LVRATopBlock->next;
      if( (newRep = LVRAAllocInBlock(proto, range, size)) ) goto exit;       
    }
    if( LVRACreateNewBlock || (range > LVRABigRange) ){
      if( (block = newLVRABlock(size)) == 0) {newRep = 0; goto exit; };
      block->next        = LVRATopBlock->next;
      LVRATopBlock->next = block;
      
      LVRATopBlock = LVRATopBlock->next;
      LVRACreateNewBlock = FALSE;
      if( (newRep = LVRAAllocInBlock(proto, range, size)) ) goto exit;
    }
  }
  
  /* No IOAGc's since last freelist was constructed. Do an LVRA compaction */
  LVRACompaction();
  
  /* Now try allocation in top block */
  if( (newRep = LVRAAllocInBlock(proto, range, size)) ) goto exit;
  /* Allocation in top block failed. Try using the free list */
  if( (newRep = LVRAFindInFree(proto, range, size)) ) goto exit;
  
  /* None of the above succeeded. Try allocating a new block */
  if( (block = newLVRABlock(size)) == 0) { newRep = 0; goto exit; }
  block->next        = LVRATopBlock->next;
  LVRATopBlock->next = block;
  LVRATopBlock = LVRATopBlock->next;
  LVRACreateNewBlock = FALSE;
  
  /* Try allocating in the new top block */
  if( (newRep = LVRAAllocInBlock(proto, range, size)) ) { goto exit; }
  
  /* All hope is gone ! */
  DEBUG_LVRA(fprintf(output, "#LVRAAlloc failed!\n"));

exit:
  MT_CODE(mutex_unlock(&lvra_lock));
  return newRep;
}

/* LVRACAlloc: allocate a Value repetition in the LVRA area 
 * and nullify the BODY of the repetition..
 */
ref(ValRep) LVRACAlloc(ref(ProtoType) proto, long range)     
{
  ref(ValRep) newRep = LVRAAlloc(proto, range);
  if (newRep){
    /* Clear the body of newRep */
    memset(newRep->Body, 0, DispatchValRepBodySize(proto, range));
  }
  return newRep;
}

/* LVRAXAlloc: allocate a Value repetition in the LVRA area 
 * and nullify extension part of the BODY of the repetition
 * (i.e. the elements from ]oldrange..newrange]
 */
ref(ValRep) LVRAXAlloc(ref(ProtoType) proto, long oldrange, long newrange)  
{
  ref(ValRep) newRep = LVRAAlloc(proto, newrange);
  if (newRep && (newrange>oldrange)){
    /* Clear the extension part of the body of newRep */
    long oldbodysize = DispatchValRepBodySize(proto, oldrange);
    long newbodysize = DispatchValRepBodySize(proto, newrange);
    memset((char*)(newRep->Body)+oldbodysize, 
	   0, 
	   newbodysize-oldbodysize);
  }
  return newRep;
}

/* LVRAkill is called from aoa to explicitly mark a
 * LVRA repetition as being dead
 */

void LVRAkill(struct ValRep *rep)
{
  rep->HighBorder = DispatchValRepSize(rep->Proto,
				       rep->HighBorder-rep->LowBorder+1);
  rep->Proto = 0;
  rep->GCAttr = 0;
  LVRAInsertFreeElement(rep); /* datpete 5 feb 1996 */
}

#ifdef CHECK_LVRA_IN_IOA
/* CopyObjectToLVRA: called from NewCopyObject */

ref(Object) CopyObjectToLVRA(ref(ValRep) theRep)
{
  ref(ValRep) newRep;
  
  DEBUG_LVRA(fprintf(output, "#CopyObjectToLVRA(%d, %d)\n",
		     (int)(theRep->Proto),
		     (int)(theRep->HighBorder-theRep->LowBorder+1)
		     ));
  if ((newRep = LVRAAlloc(theRep->Proto,
			 theRep->HighBorder-theRep->LowBorder+1))) {
      RepCopy(newRep, theRep);
      newRep->GCAttr = 0;
      /* Install forward reference to newObj in theObj */
      theRep->GCAttr = (long) newRep;
  }
  /* Return the new object in ToSpace */
  DEBUG_LVRA(fprintf(output, "#COPYObjectToLVRA: newRep=0x%x\n", (int)newRep));
  return cast(Object)newRep;
}
#endif

/********************** LVRA garbage collection *************************/

#ifdef RTDEBUG
void LVRAStatistics(void);
#endif /* RTDEBUG */

void LVRACompaction(void)
{
  ref(LVRABlock) srcBlock;
  ref(LVRABlock) dstBlock;
  ref(LVRABlock) prevDstBlock;
  
  ref(ValRep)    srcRep;
  ref(ValRep)    dstRep;
  
  long           saved;
  long           srcSize;
  long           sizeBlocks;
  
#ifdef RTDEBUG
  long sizeDead=0;
  long numDead=0;
  long numAlive=0;
  long numMoved=0;
  long numFree=0;
#endif
  
#if defined(MAC)
  RotateTheCursorBack();
#endif
  
  NumLVRAGc++;
  
  DEBUG_LVRA( LVRACheck() );

  /* Run compaction elements in 'LVRABlock{->next}*'  */
  
  INFO_LVRA( fprintf( output, "#(LVRA-%d ", (int)NumLVRAGc) ); 
  
  LVRACleanTable();
  saved = 0; 
  LVRANumOfBlocks = 0;
  sizeBlocks = 0; 
  
  srcBlock = LVRABaseBlock;
  dstBlock = LVRABaseBlock; 
  dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);
  prevDstBlock = NULL;
  
  while( srcBlock != 0){
    LVRANumOfBlocks++; 
    sizeBlocks += (long) srcBlock->limit - (long) srcBlock - (long) sizeof(struct LVRABlock);
    /* traverse srcBlock. */
    srcRep = (ref(ValRep)) LVRABlockStart(srcBlock);
    while( ((ptr(long)) srcRep) < srcBlock->top){
      srcSize = LVRARepSize(srcRep);
      if (LVRAAlive(srcRep)) {
	DEBUG_LVRA(numAlive++);
	if (srcRep != dstRep) {
	  long rest;
	  /* srcRep is alive. Find place to move it to in dstBlock (if possible) */
	  while (Offset(dstRep, srcSize) > (long)dstBlock->limit) {
	    /* No room for srcRep in dstBlock */
	    dstBlock->top = (ptr(long)) dstRep;
	    if (dstBlock->top == LVRABlockStart(dstBlock)) {
	      /* dstBlock entirely unused; free it */
	      ref(LVRABlock) nextBlock = dstBlock->next;
	      if (LVRABaseBlock == dstBlock)
		LVRABaseBlock = nextBlock;
	      if (prevDstBlock != NULL)
		prevDstBlock->next = nextBlock;
	      INFO_LVRA(fprintf(output, "#(LVRA: block freed %dKb)\n",
				(int)toKb((long)dstBlock->limit - (long)dstBlock)));
	      FREE(dstBlock);
	      LVRANumOfBlocks--;
	      dstBlock = nextBlock;
	    } else { 
	      /* dstBlock partially used; insert rest in free-list */
	      rest = LVRARestInBlock(dstBlock);
	      if( rest > 0 ){
		if ( rest >= headsize(ValRep) ){
		  dstRep = (ref(ValRep)) dstBlock->top;
		  dstRep->Proto      = 0;
		  dstRep->GCAttr     = 0;
		  dstRep->LowBorder  = 1;
		  dstRep->HighBorder = rest; /* size in bytes */
		  dstBlock->top =  (ptr(long)) Offset(dstBlock->top, rest);
		  saved += rest;
		  LVRAInsertFreeElement(dstRep);
#ifdef RTDEBUG
		  numFree++;
#endif
		} else {
		  long *p;
		  DEBUG_LVRA(fprintf(output, "#LVRACompaction: LVRARestInBlock < headsize(ValRep)\n"));
		  for (p=dstBlock->top; p<dstBlock->limit; p++) 
		    *p = 0;
		}
	      }
	      prevDstBlock = dstBlock;
	      dstBlock = dstBlock->next;
	    }
	    DEBUG_LVRA( Claim( (long)dstBlock, "LVRACompaction: dstBlock"));
	    dstRep = (ref(ValRep)) LVRABlockStart(dstBlock);
	  } /* while */

	  /* Slide down srcRep */
	  if (srcRep != dstRep) {
	    /* Preserve the LVRA-cycle by updating the cell referencing srcRep */
	    *((ptr(long)) srcRep->GCAttr) = (long) dstRep;
	    DEBUG_LVRA(numMoved++);
	    RepCopy(dstRep, srcRep);
	  }
	  
	} /* srcRep != dstRep */
	dstRep = (ref(ValRep)) ((long) dstRep + srcSize );

      } else {
	DEBUG_LVRA(numDead++);
	DEBUG_LVRA(sizeDead+=srcSize);
      }
      srcRep = (ref(ValRep)) (((long) srcRep) + srcSize);

    } /* while */
    /* Take the next element in the LVRA block chain. */
    srcBlock = srcBlock->next;
  }
  dstBlock->top = (ptr(long)) dstRep;
  
  /* Count saved parts of all blocks from dstBlock and forward.
   * Free all blocks *after* dstBlock. [Theoretically, dstBlock might be free 
   * itself (i.e., dstBlock->Top == LVRABlockStart(dstBlock)) in which case it 
   * could be freed as well. However, since we haven't recorded the previous 
   * block (i.e., the new LVRATopBlock) anywhere, we won't bother.]
   */
  LVRATopBlock = dstBlock;
  saved += (long) dstBlock->limit - (long) dstBlock->top;
  dstBlock = dstBlock->next;
  while(dstBlock) {
    ref(LVRABlock) nextBlock = dstBlock->next;
    saved += (long)dstBlock->limit - (long)dstBlock->top;
    INFO_LVRA(fprintf(output, "#(LVRA: block freed %dKb)\n",
		      (int)toKb((long)dstBlock->limit - (long)dstBlock)));
    FREE(dstBlock);
    LVRANumOfBlocks--;
    dstBlock = nextBlock;
  }
  LVRATopBlock->next = NULL;
  
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
  DEBUG_LVRA(if( LVRACreateNewBlock ) 
	    fprintf(output, " (new block needed in next LVRAAlloc) "));
  
  INFO_LVRA(fprintf(output, " %dKb in %d blocks, %d%% free)\n",
		    (int)toKb(sizeBlocks), 
		    (int)LVRANumOfBlocks, 
		    (int)((100*saved)/sizeBlocks)));
  DEBUG_LVRA(fprintf(output, "Dead: %d, Alive: %d, Moved: %d, FreeList: %d\n",
		     (int)numDead, (int)numAlive, (int)numMoved, (int)numFree));
  DEBUG_LVRA(fprintf(output, "Size of dead reps: %d (0x%x)\n", 
		     (int)sizeDead, (int)sizeDead));
  LVRALastIOAGc = 0;
  DEBUG_LVRA(INFO_LVRA(LVRAStatistics()));
  DEBUG_LVRA( LVRACheck() );
}

static void LVRAConstructFreeList(void)
{
  ref(LVRABlock) currentLVRABlock;
  ref(ValRep)    currentValRep;
  ref(ValRep)    startRep;
  long           saved;
  long           alive;
  long           theObjectSize;
  long           sizeBlocks;
  
#if defined(MAC)
  RotateTheCursorBack();
#endif
  
  INFO_LVRA(fprintf( output, "#(LVRA: make free list"));

  DEBUG_LVRA(LVRACheck());
  
  LVRACleanTable();
  saved = 0; 
  LVRANumOfBlocks = 0; 
  sizeBlocks = 0;
 
  currentLVRABlock = LVRABaseBlock;
  
  while( currentLVRABlock != 0){    
    LVRANumOfBlocks++; 
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
	  startRep->HighBorder += currentValRep->HighBorder;  /* size in bytes */
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
  
  INFO_LVRA( fprintf(output, "  %dKb in %d blocks, %dKb free)\n",
		     (int)toKb(sizeBlocks), 
		     (int)LVRANumOfBlocks, 
		     (int)toKb(saved)));
  DEBUG_LVRA( LVRADisplayTable() );
  LVRALastIOAGc = NumIOAGc;

  DEBUG_LVRA(LVRACheck());

}

#ifdef RTDEBUG
GLOBAL(ref(ValRep) prevRep) = cast(ValRep)0;

void LVRACheck(void)
{ ref(LVRABlock) theBlock;
  ref(ValRep)    rep;
  long theObjectSize;
  long numReps=0;
  
  theBlock = LVRABaseBlock;
  while( theBlock ){    
    /* traverse currentLVRABlock. */
    rep = (ref(ValRep)) LVRABlockStart(theBlock);
    while ((long *)rep < theBlock->top) {
      numReps++;
      theObjectSize = LVRARepSize(rep);
      prevRep = rep;
      rep = (struct ValRep *) ((long)rep + theObjectSize);
    }
    Claim( (long *) rep == theBlock->top,
          "#LVRACheck: rep == theBlock->top");
    /* Take the next element in the LVRA block chain. */
    theBlock = theBlock->next;
  }
#if 0
  fprintf(output, "#LVRACheck: %d repetitions in LVRA\n", (int)numReps);
#endif
} 

void LVRAStatistics(void)
{
  ref(LVRABlock) theBlock;
  ref(ValRep) rep;
  long theObjectSize;
  long blockNo = 0;
  long sizeAliveReps = 0;
  long sizeDeadReps = 0;
  long numAliveReps = 0;
  long numDeadReps = 0;
  
  fprintf(output,"\nTraversing LVRA...\n------------------\n");
  theBlock = LVRABaseBlock;
  while (theBlock != NULL) {
    blockNo++;
    fprintf(output, "Block %d:\n", (int)blockNo);
    rep = (ref(ValRep)) LVRABlockStart(theBlock);
    while ((long *)rep < theBlock->top) {
      theObjectSize = LVRARepSize(rep);
      if (LVRAAlive(rep)){
	fprintf(output, 
		"addr=0x%-6x type=%-7s size=%-6d LVRACycle=%s ref=%-6x (%s)\n",
		(int)rep, 
		rep->Proto==LongRepPTValue?"integer":
		rep->Proto==ByteRepPTValue?"char":
		rep->Proto==ShortRepPTValue?"short":
		rep->Proto==DoubleRepPTValue?"double":
		"???",
		(int)theObjectSize,
		((*(long*)(int)rep->GCAttr) == (long)rep) ? "ok " : "BAD",
		(int)rep->GCAttr,
		inIOA(rep->GCAttr)?"IOA":
		inAOA(rep->GCAttr)?"AOA":
		inToSpace(rep->GCAttr)?"ToSpace!!!":
		"???");
	sizeAliveReps += theObjectSize;      
	numAliveReps++;
      } else {
	fprintf(output, "addr=0x%-6x              size=%-6d            (DEAD)\n",
		(int)rep, 
		(int)theObjectSize);
	sizeDeadReps += theObjectSize;
	numDeadReps++;
      }
      rep = (struct ValRep *) ((long)rep + theObjectSize);
    }
    theBlock = theBlock->next;
  }
  fprintf(output, "Summary: %d LVRA blocks\n", (int)blockNo);
  fprintf(output, "Summary: %d alive repetitions, total size=%d\n", 
	  (int)numAliveReps, (int)sizeAliveReps);
  fprintf(output, "Summary: %d dead repetitions, total size=%d\n", 
	  (int)numDeadReps, (int)sizeDeadReps);
}
#endif /* RTDEBUG */
