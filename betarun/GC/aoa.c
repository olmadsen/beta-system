/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * aoa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

static void FollowObject();
static void Phase1();
static void Phase2();
static void Phase3();

/* EXPORTING:
 *
 *  CopyObjectToAOA move an object to AOA and return the address of the new location
 *  If the allocation in AOA failed the function returns 0;
 *
 *    ref(Object) CopyObjectToAOA( theObj)
 *      ref(Object) theObj;
 *
 *  AOAGc perform a mark/sweep garbagecollection on the AOA heap.
 *  Should be called after IOAGc when AOANeedCompaction == TRUE;
 *
 *    void AOAGc();
 */

long AOACreateNewBlock = FALSE;


/* AOAalloc allocate 'size' number of bytes in the Adult object area.
 * If the allocation succeeds the function returns a reference to the allocated
 * object, 0 otherwise.
 * The actual allocation depends on AOAState:
 *  == 0: Means allocate a new AOABlock and do the allocation inside that block.
 *  == 1: Means try to allocate the object inside the Block AOATopBlock refers.
 *  == 2: We are out of memory, so return 0.
 */
static ref(Object) AOAalloc( size)
     long size;
{
  ptr(long)  oldTop;

DEBUG_AOA(if (AOATopBlock) 
	  fprintf(output, "AOATopBlock 0x%x, diff 0x%X\n",
		  AOATopBlock, (long)AOATopBlock->limit - (long)AOATopBlock->top));
  
  if( AOABaseBlock == 0){
    if( MallocExhausted || (AOABlockSize == 0) ) return 0;
    /* Check if the AOAtoIOAtable is allocated. If not the allocate it. */
    if( AOAtoIOAtable == 0 ) 
      if( AOAtoIOAAlloc() == 0 ){
	MallocExhausted = TRUE;
	INFO_AOA( fprintf(output,
			  "#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
			  AOAtoIOAtableSize));
	return 0;
      }
    /* Try to allocate a new AOA block. */
    if( AOABaseBlock = newBlock(AOABlockSize) ){
      INFO_AOA( fprintf( output, "#(AOA: new block allocated %dKb.)\n",
			AOABlockSize/Kb));
      AOATopBlock  = AOABaseBlock;
    }else{
      MallocExhausted = TRUE;
      INFO_AOA( fprintf( output, "#(AOA: block allocation failed %dKb.)\n",
			AOABlockSize/Kb));
      return 0;
    }
  }
  /* Try to find space between AOATopBlock->top and AOATopBlock->limit. */
  oldTop = AOATopBlock->top;
  if( areaSize(oldTop,AOATopBlock->limit) > size){
    AOATopBlock->top = (ptr(long)) Offset( oldTop, size);
    return (ref(Object)) oldTop;
  }else{
    /* maybe there is a free block AOATopBlock->next. */
    if( AOATopBlock->next ){
      AOATopBlock = AOATopBlock->next;
      oldTop = AOATopBlock->top;
      if( areaSize(oldTop,AOATopBlock->limit) > size){
	AOATopBlock->top = (ptr(long)) Offset( oldTop, size);
	return (ref(Object)) oldTop;
      }
    }
  }
  
  if( AOACreateNewBlock ){
    if( AOATopBlock->next = newBlock( AOABlockSize) ){
      INFO_AOA( fprintf( output, "#(AOA: new block allocated %dKb.)\n",
			AOABlockSize/Kb) );
      AOATopBlock = AOATopBlock->next;
      oldTop = AOATopBlock->top;
      AOACreateNewBlock = FALSE;
      if( areaSize(oldTop,AOATopBlock->limit) > size){
	AOATopBlock->top = (ptr(long)) Offset( oldTop, size);
	return (ref(Object)) oldTop;
      }else{
	fprintf( output, "#AOA warning: Object size is larger then AOABlockSize\n"); 
	return 0;
      }
    }else{
      MallocExhausted = TRUE;
      INFO_AOA( fprintf( output, "#(AOA: block allocation failed %dKb.)\n",
			AOABlockSize/Kb));
      AOANeedCompaction = TRUE;
      return 0;
    }
  }else{
    AOANeedCompaction = TRUE;
    return 0;
  }    
}

ref(Object) CopyObjectToAOA( theObj)
     ref(Object) theObj;
{
  ref(Object) newObj;
  long        size;
  register ptr(long) src;
  register ptr(long) dst;
  register ptr(long) theEnd;
  
  
  size = 4*ObjectSize( theObj);
  if( (newObj = AOAalloc( size)) == 0 ) return 0;
  
  theEnd = (ptr(long)) (((long) newObj) + size); 
  
  src = (ptr(long)) theObj; dst = (ptr(long)) newObj; 
  while( dst < theEnd) *dst++ = *src++; 
  
  newObj->GCAttr = 0;
  
  /* Set one forward reference in theObj to newObj */
  theObj->GCAttr = (long) newObj;
  
  DEBUG_AOA( AOAcopied += size );
  DEBUG_AOA( fprintf( output, "#ToAOA: IOA address %x AOA address %x size %d\n", theObj, newObj, size));
  
  /* Return the new object in ToSpace */
  return newObj;
}


void AOAGc()
{
  /* Remember that AOAGc is called before ToSpace <-> IOA, so
   * all reachable objects is in ToSpace, and IOA is junk.
   * The space in IOA is used during the Mark Sweep.
   */
  long blocks, size, used;
  
  NumAOAGc++;

#ifdef RTLAZY
  /* Reset the table of fields in AOA containing negative references: */
  negAOArefsRESET ();
#endif

  INFO_AOA( fprintf( output, "\n#(AOA-%d ", NumAOAGc); fflush(output) );
  /* Mark all reachable objects within AOA and reverse all pointers. */
#ifdef macintosh
  RotateTheCursorBack();
#endif
  DEBUG_AOA( fprintf( output, "1"); fflush(output) );
  Phase1();  
  /* Calculate new addresses for the reachable objects and reverse pointers. */
#ifdef macintosh
  RotateTheCursorBack();
#endif
  DEBUG_AOA( fprintf( output, "2"); fflush(output) );
  Phase2( &blocks, &size, &used); 
  /* Copy all reachable objects to their new locations. */
#ifdef macintosh
  RotateTheCursorBack();
#endif
  DEBUG_AOA( fprintf( output, "3"); fflush(output) );
  Phase3();  
#ifdef macintosh
  RotateTheCursorBack();
#endif
  AOANeedCompaction = FALSE;
  
  if( AOAMinFree ){
    if( (size - used) < AOAMinFree )
      /* if freeArea < AOAMinFree  then ... */
      AOACreateNewBlock = TRUE;
    else
      AOACreateNewBlock = FALSE;
  }else{
    if( (100 - (100 * used)/size) < AOAPercentage )
      /* if freeArea < AOAPercentage  then ... */
      AOACreateNewBlock = TRUE;
    else
      AOACreateNewBlock = FALSE;
  }
  DEBUG_AOA( if( AOACreateNewBlock )fprintf( output, " new block needed, "));

#ifdef hppa
  {
      long **pointer = (long **)AOArootsLimit;

      /*
       * Restore the tag bits saved from stackobjects in Phase1 from the
       * AOAroots table. See Phase1() for a comment. - poe.
       */
      while ((long *)pointer > AOArootsPtr) {
	  pointer--;
	  if((long)*pointer & 1) {
	      (long)*pointer &= ~1; /* clear tag bit in table */
	      **pointer |= 1;	    /* set it in stackobject */
	  }
      }
  }
#endif
  
  INFO_AOA( fprintf( output, "%dKb in %d blocks, %d%% free)\n", 
		    toKb(size), blocks, 100 - (100 * used)/size); fflush(output));
  asmemptylabel(EndAOA);
}

/* ReverseAndFollow is used during Phase1 of the Mark-Sweep GC. 
 * It reverse the pointer and calls FollowObject iff the refered
 * object has not been followed.
 */
static ReverseAndFollow( theCell)
     handle(Object) theCell;
{
  ref(Object) theObj = *theCell;
  ref(Object) autObj;
  
  if( inAOA( theObj) ){
    if( theObj->GCAttr == 0 ){
      /* theObj is autonomous and not marked. */
      *theCell = (ref(Object)) 1; theObj->GCAttr = (long) theCell;
      FollowObject( theObj);
      return;
    }
    if( !(isStatic(theObj->GCAttr)) ){
      /* theObj is marked. */
      *theCell = (ref(Object)) theObj->GCAttr; theObj->GCAttr = (long) theCell;
      return;
    }
    /* theObj-GCAttr < 0, so theObj is a static Item. */
    autObj = theObj;
    while( isStatic(autObj->GCAttr) )
      autObj = (struct Object *) Offset( autObj, autObj->GCAttr*4 );
    if( autObj->GCAttr == 0){
      /* The autonomous objects is not marked: so mark it and follow the object.
       */
      autObj->GCAttr = 1;    
      *theCell = (ref(Object)) theObj->GCAttr; theObj->GCAttr = (long) theCell;
      FollowObject( autObj);
    }else{
      *theCell = (ref(Object)) theObj->GCAttr; theObj->GCAttr = (long) theCell;
    }
  }else{
    if(  inAOA(theCell) && inLVRA( theObj) ){
      /* Save the theCell for later use */
      AOAtoLVRAtable[AOAtoLVRAsize++] = (long) theCell;
      DEBUG_LVRA( Claim( isValRep(*theCell), "Phase1: LVRA cycle"));
      DEBUG_LVRA( Claim( (*theCell)->GCAttr == (long) theCell,
			"Phase1: LVRA cycle"));
      if( AOAtoLVRAsize > (IOASize/4) ) BetaError(AOAtoLVRAfullErr, 0);
    }
  }
}

static FollowItem( theObj)
     ref(Item) theObj;
{ 
  ref(ProtoType) theProto  = theObj->Proto;
  
  ptr(short)     Tab;
  ptr(long)      theCell;
  
  /* Calculate a pointer to the GCTable inside the ProtoType. */
  Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
  
  while( *Tab != 0 ){
    if( *Tab == -Tab[1] ) 
      FollowObject( Offset( theObj, *Tab * 4));
    Tab += 4;
  }
  Tab++;
  
  /* Handle all the references in the Object. */
  while( *Tab != 0 ){
    theCell = (ptr(long)) Offset( theObj, *Tab++ );
#ifdef RTLAZY
    if( *theCell > 0 ) ReverseAndFollow( theCell );
    else if (isLazyRef (*theCell)) negAOArefsINSERT (theCell);
#else
    if( *theCell != 0 ) ReverseAndFollow( theCell );
#endif
  }
}

/* FollowObject is used during Phase1 of the Mark-Sweep GC. 
 * For each referernce inside theObj it calls ReverseAndFollow.
 */

static void FollowObject( theObj)
     ref(Object) theObj;
{ 
  ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( (long) theProto < 0 ){  
    switch( (long) theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return;
      /* No references in a Value Repetition, so do nothing*/
      
    case (long) RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	
	for(index=0; index<size; index++) 
#ifdef RTLAZY
	  if( *pointer > 0) ReverseAndFollow( pointer++ );
	  else 
	    if (isLazyRef (*pointer))
	      negAOArefsINSERT (pointer++);
	    else
	      pointer++;
#else
	if( *pointer != 0) ReverseAndFollow( pointer++ );
	else pointer++;
#endif
      }
      return;
      
    case (long) ComponentPTValue:
      { ref(Component) theComponent;
	
	theComponent = Coerce( theObj, Component);
	ReverseAndFollow( &theComponent->StackObj);
	ReverseAndFollow( &theComponent->CallerComp);
	ReverseAndFollow( &theComponent->CallerObj);
	FollowItem( ComponentItem( theComponent));
      }
      return;
      
    case (long) StackObjectPTValue:
      fprintf( output,"FollowObject: OOPS a StackObject in AOA.\n");
      return;
      
    case (long) StructurePTValue:
      ReverseAndFollow( &(toStructure(theObj))->iOrigin );
      return;

    case (long) DopartObjectPTValue:
      ReverseAndFollow( &(cast(DopartObject)(theObj))->Origin );
      return;
    }
  }else FollowItem( theObj);
}

/* Phase1 of the Mark-Sweep GC, reverse:
 * all cells in root(AOA),
 * all cells in AOA, where cells point into AOA
 */
static void Phase1()
{ /* Call FollowReference for each root to AOA. */
  ptr(long) pointer = AOArootsLimit;
  
  /* temporarily use IOA for table. Only ToSpace contains usefull informations */
  AOAtoLVRAtable = (ptr(long)) Offset(IOA, IOASize/2) ;
  AOAtoLVRAsize  = 0;
  
#ifdef RTDEBUG
  { /* Make sure that there are no duplicate AOA roots! */
    long old=0;
    WordSort(AOArootsPtr, AOArootsLimit-AOArootsPtr);
    while (pointer > AOArootsPtr){
#ifdef hppa
      /* See below... */
      if(*((long *)*(pointer-1)) & 1) {
	*((long *)*(pointer-1)) &= ~1; /* clear tag bit */
	*(pointer-1) |= 1;		   /* set it in table */
      }
#endif
      if (old == *--pointer){
	INFO_AOA(fprintf(output, "Phase1: Duplicate AOA root: 0x%x\n", old));
      } else {
	old = *pointer;
	ReverseAndFollow(*pointer & ~1);
      }
    }
  }
#else /* RTDEBUG */
  while( pointer > AOArootsPtr) {
    pointer--;
#ifdef hppa
    /*
     * Dreadful hack. We have to remove the tag bits from those references
     * in stackobjects that have them, so the Follow*() can handle them,
     * but we have to save them somewhere. They are saved in the LSB of
     * the pointers in the AOAroots table. They are restored just
     * before the AOAGc finishes in AOAGc().
     */
    if(*((long *)*pointer) & 1) {
      *((long *)*pointer) &= ~1; /* clear tag bit in stackobject */
      *pointer |= 1;	     /* set it in table */
    }
#endif
    ReverseAndFollow( *pointer & ~1);
  }
#endif
}

#define isAlive(x)  (toObject(x)->GCAttr != 0)
#define isMarked(x) (x->GCAttr == 1)
#define endChain(x) (( -0xFFFF <= ((long) (x))) && (((long) (x)) <= 1))

static handleAliveStatic( theObj, freeObj )
     ref(Object) theObj;
     ref(Object) freeObj;
{
  handle(Object) theCell;
  handle(Object) nextCell;
  ref(ProtoType) theProto = theObj->Proto;
  ptr(short)     Tab;
  
  nextCell = (handle(Object)) theObj->GCAttr;
  while( !endChain(theCell = nextCell)){
    nextCell = (handle(Object)) *theCell;
    *theCell = freeObj;
  }
  theObj->GCAttr = (long) theCell; /* Save forward pointer to Phase3. */
  DEBUG_AOA( Claim( theObj->GCAttr < 0, "handleAliveStatic:  theObj->GCAttr < 0"));
  
  if( (long) theProto > 0){
    /* theObj is an item. */
    /* Calculate a pointer to the GCTable inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ){ 
	handleAliveStatic( Offset( theObj, *Tab * 4), Offset( freeObj, *Tab * 4) );
	DEBUG_AOA( Claim( *(ptr(long)) Offset( theObj, *Tab * 4 + 4)
			 == (long) Tab[1],
			 "AOACheckObject: EnclosingObject match GCTab entry."));
      }
      Tab += 4;
    }
  }else{
    /* This is a component so update theObj and Proto to Item. */
    if( theProto == ComponentPTValue )
      handleAliveStatic( ComponentItem( theObj), ComponentItem( freeObj) );
  } 
}

static handleAliveObject( theObj, freeObj)
     ref(Object) theObj;
     ref(Object) freeObj;
{
  handle(Object) theCell;
  handle(Object) nextCell;
  ref(ProtoType) theProto = theObj->Proto;
  ptr(short)     Tab;
  
  nextCell = (handle(Object)) theObj->GCAttr;
  while( !endChain(theCell = nextCell)){
    nextCell = (handle(Object)) *theCell;
    *theCell = freeObj;
  }
  DEBUG_AOA( Claim( (long) theCell == 1,
		   "handleAliveObject:  chainEnd == 0 or 1"));
  theObj->GCAttr = (long) freeObj; /* Save forward pointer to Phase3. */
  
  if( (long) theProto > 0){
    /* theObj is an item. */
    /* Calculate a pointer to the GCTable inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ){
	handleAliveStatic( Offset( theObj, *Tab * 4), Offset( freeObj, *Tab * 4) );
	DEBUG_AOA( Claim( *(ptr(long)) Offset( theObj, *Tab * 4 + 4)
			 == (long) Tab[1],
			 "AOACheckObject: EnclosingObject match GCTab entry."));
      }
      Tab += 4;
    }
  }else{
    /* This is a component so update theObj and Proto to Item. */
    if( theProto == ComponentPTValue )
      handleAliveStatic( ComponentItem( theObj), ComponentItem( freeObj) );
  } 
}



static void Phase2( numAddr, sizeAddr, usedAddr)
     ptr(long) numAddr;
     ptr(long) sizeAddr;
     ptr(long) usedAddr;
{
  ref(Block)  theBlock  = AOABaseBlock;
  ref(Block)  freeBlock = AOABaseBlock;
  ref(Object) theObj;
  ref(Object) freeObj;
  long        theObjectSize;
  long        numOfBlocks = 0;
  
  long        usedSpace = 0;
  long        allSpace  = 0;
  
  freeObj   = (ref(Object)) BlockStart( freeBlock);
  
  while( theBlock ){
    numOfBlocks++;
    theObj = (ref(Object)) BlockStart(theBlock);
    while( (ptr(long)) theObj < theBlock->top ){
      theObjectSize = 4*ObjectSize( theObj);
      if( isAlive( theObj)){
	/* update freeObj if no space is available. */
	if( (ptr(long)) Offset( freeObj, theObjectSize) > freeBlock->limit){
	  freeBlock->info.nextTop = (ptr(long)) freeObj;
	  freeBlock = freeBlock->next;
	  freeObj   = (ref(Object)) BlockStart(freeBlock);
	}
	handleAliveObject( theObj, freeObj);
	freeObj = (ref(Object)) Offset(freeObj, theObjectSize);
	usedSpace += theObjectSize;
      }
      theObj = (ref(Object)) Offset( theObj, theObjectSize);
      allSpace += theObjectSize;
    }
    theBlock = theBlock->next;
  }
  freeBlock->info.nextTop = (ptr(long)) freeObj;
  
  /* After AOAGc should freeBlock be the new AOATopBlock. */
  AOATopBlock = freeBlock;
  
  /* If there exists Blocks after freeBlock, make them empty. */
  freeBlock = freeBlock->next;
  while( freeBlock ){
    freeBlock->info.nextTop = BlockStart(freeBlock);
    freeBlock = freeBlock->next;
  }
  
  *numAddr  = numOfBlocks;
  *sizeAddr = allSpace;
  *usedAddr = usedSpace;

  if( DOT ){
    /* The Debugger Object Table is in use, so traverse this table. */
    ptr(long) current = DOT;
    while( current < DOTTop){
      if( *current ) {
	if (!inIOA(*current)){
	  INFO_DOT(fprintf(output, "#DOT: updating AOA reference 0x%x\n", *current));
	  *current = (cast(Object)(*current))->GCAttr;
	}
      }
      current++;
    }
  }
} 

static FindInterval( table, size, block, startAddr, stopAddr)
     ptr(long) table;
     long size;
     ref(Block) block;
     ptr(long) startAddr;
     ptr(long) stopAddr;
{
  /* Finds an interval in table, where all elements are inside block.
   * We assume that the table is sorted in increasing order.
   */
  long start, stop;
  
  start = 0;
  while( (start < size) && (table[start] < (long)block)) start++;
  stop = start;
  while( (stop < size) && (table[stop] < (long)block->limit)) stop++;
  *startAddr = start;
  *stopAddr  = stop;
}

/* Phase 3:
 *  Update the AOAtoIOATable,
 *  then sort the Table in area[ToSpaceLimit..ToSpaceTop].
 */
static void Phase3()
{
  ptr(long)   table;
  
  /* Calculate the size of table. */
  AOAtoIOACount = 0;
  {
    long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    for(i=0; i<AOAtoIOAtableSize; i++) {
#ifdef RTLAZY
      if( *pointer > 0) AOAtoIOACount++;
      pointer++;
#else
      if( *pointer++ ) AOAtoIOACount++;
#endif
    }
  }
  
  if( ((long) IOALimit - (long) IOA) > (AOAtoIOACount * 8) )
    /* Only use half of IOA area. */
    table = IOA;
  else {
    if( !(table = (ptr(long)) MALLOC( AOAtoIOACount * 4))){
      fprintf(output,"#Phase3: malloc failed %d longs\n", AOAtoIOACount);
      exit(-1);
    }
    INFO_AOA( fprintf( output, "#(AOA: new block for table %d longs)\n",
		      AOAtoIOACount));
  }
  
  /* Move compact(AOAtoIOAtable) -> table. */
  {
    long i, counter = 0;  ptr(long) pointer = BlockStart( AOAtoIOAtable);
    for(i=0; i < AOAtoIOAtableSize; i++){
#ifdef RTLAZY
      if( *pointer > 0) table[counter++] = *pointer;
#else
      if( *pointer ) table[counter++] = *pointer;
#endif
      pointer++;
    }
    DEBUG_AOA( Claim( counter == AOAtoIOACount,"Phase3: counter == AOAtoIOACount"));
  }
  
  DEBUG_AOA( fprintf( output,"(AOAtoIOA#%d)", AOAtoIOACount));
  DEBUG_AOA( fprintf( output,"(AOAtoLVRA#%d)", AOAtoLVRAsize));
  
  /* Clear the AOAtoIOAtable. */
  AOAtoIOAClear();
  
  WordSort(table, AOAtoIOACount);
  WordSort(AOAtoLVRAtable, AOAtoLVRAsize);
#ifdef RTLAZY
  if (negAOArefs)
    WordSort (negAOArefs, negAOAsize);
#endif


  {
    ref(Block)  theBlock;
    ref(Object) theObj;
    ref(Object) nextObj;
    long        theObjectSize;
    long        start, stop;
    long        start1, stop1;
#ifdef RTLAZY
    long        start2, stop2;
#endif
    
    theBlock = AOABaseBlock;
    while( theBlock ){
      theObj = (ref(Object)) BlockStart(theBlock);
      
      FindInterval( table, AOAtoIOACount, theBlock, &start, &stop);
      FindInterval( AOAtoLVRAtable, AOAtoLVRAsize, theBlock, &start1, &stop1);
#ifdef RTLAZY
      if (negAOArefs)
	FindInterval( negAOArefs, negAOAsize, theBlock, &start2, &stop2);
#endif
      
      while( (ptr(long)) theObj < theBlock->top ){
	theObjectSize = 4*ObjectSize( theObj);
	nextObj = (ref(Object)) Offset( theObj, theObjectSize); 
	
	DEBUG_AOA( if( start<stop ) Claim( table[start] > (long) theObj,
					  "Phase3: table[start] > (long) theObj"));
	if( theObj->GCAttr ){
	  /* The forward pointer is present, so theObj is alive. */
	  struct Object *newObj = (ref(Object)) theObj->GCAttr;
	  long diff = (long) theObj - (long) newObj;

	  if (diff) {
	    DEBUG_AOA( Claim( theObj > newObj, "#Phase3: theObj > newObj"));
	    /* theObj need a new location in AOA, so move it. */
	    MACRO_CopyBlock( theObj, newObj, theObjectSize/4);
	  }
	  /* update the AOAtoIOAtable. */
	  while ((start<stop) && (table[start] < (long)nextObj)) {
	    if (inToSpace( *(ptr(long)) (table[start]-diff)))
	      AOAtoIOAInsert( table[start]-diff);
	      
	    start++;
	  }
	  while( (start1<stop1) && (AOAtoLVRAtable[start1] < (long)nextObj) ){
	    DEBUG_AOA( Claim( inLVRA( *(ptr(long))(AOAtoLVRAtable[start1]-diff)),
			     "Phase3: Pointer is in LVRA"));
	    (*((handle(ValRep)) (AOAtoLVRAtable[start1]-diff)))->GCAttr =
	      AOAtoLVRAtable[start1]-diff;
	    start1++;
	  }
#ifdef RTLAZY
	  if (negAOArefs)
	    /* update the negAOArefs table. */
	    while( (start2<stop2) && ((long)negAOArefs[start2] < (long)nextObj) ){
	      negAOArefs[start2] = negAOArefs[start2] - diff;
	      start2++;
	    }
#endif
	  newObj->GCAttr = 0;
	} else {
	  /* theObj is not reachable. */
	  while ((start<stop) && (table[start] < (long)nextObj)) start++;
	  
	  while( (start1<stop1) && (AOAtoLVRAtable[start1] < (long)nextObj) ){
	    DEBUG_AOA( Claim( inLVRA( *(ptr(long))(AOAtoLVRAtable[start1])),
			     "Phase3: Pointer is in LVRA"));
	    LVRAkill(*(struct ValRep **) AOAtoLVRAtable[start1]);
	    start1++;
	  }
	}
	theObj = nextObj;
      }
      theBlock->top = theBlock->info.nextTop;
      theBlock = theBlock->next;
    }
  }
  
  /* if table was allocated with malloc, please free it. */
  if( table != IOA ){
    FREE( table);
    INFO_AOA( fprintf( output, "#(AOA: block for table freed %d longs)\n",
		      AOAtoIOACount));
  }
}

#ifdef RTDEBUG
void AOACheck()
{
  ref(Block)  theBlock  = AOABaseBlock;
  ref(Object) theObj;
  long        theObjectSize;
  
  while( theBlock ){
    theObj = (ref(Object)) BlockStart(theBlock);
    while( (ptr(long)) theObj < theBlock->top ){
      theObjectSize = 4*ObjectSize( theObj);
      AOACheckObject( theObj);
      theObj = (ref(Object)) Offset( theObj, theObjectSize);
    }
    theBlock = theBlock->next;
  }
} 

void AOACheckObject( theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  Claim( !inBetaHeap(theProto),"#AOACheckObject: !inBetaHeap(theProto)");
  
  if( (long) theProto < 0 ){  
    switch( (long)  theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return; /* No references in the type of object, so do nothing*/
      
    case (long) RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	
	for(index=0; index<size; index++) 
#ifdef RTLAZY
	  if( *pointer > 0) AOACheckReference( pointer++ );
#else
	  if( *pointer != 0) AOACheckReference( pointer++ );
#endif
	  else pointer++;
      }
      
      return;
      
    case (long) ComponentPTValue:
      { ref(Component) theComponent;
	
	theComponent = Coerce( theObj, Component);
	if (theComponent->StackObj == (ref(StackObject))-1) {
	  /* printf("\nAOACheckObject: theComponent->StackObj=-1, skipped!\n"); */
	} else {
	  AOACheckReference( &theComponent->StackObj);
	}
	AOACheckReference( &theComponent->CallerComp);
	AOACheckReference( &theComponent->CallerObj);
	AOACheckObject( ComponentItem( theComponent));
      }
      return;   
    case (long) StackObjectPTValue:
      Claim( FALSE, "AOACheckObject: theObj should not be StackObject.");
      return; 
    case (long) StructurePTValue:
      AOACheckReference( &(toStructure(theObj))->iOrigin );
      return;
    case (long) DopartObjectPTValue:
      AOACheckReference( &(cast(DopartObject)(theObj))->Origin );
      return;
    }
  }else{
    ptr(short)  Tab;
    ptr(long)   theCell;
    
    /* Calculate a pointer to the GCTable inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .word Distance_To_Inclosing_Object
     *   .long T_entry_point
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessObject on static objects
     * on 1 level. The recursion in ProcessObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */
    
    while( *Tab != 0 ){
      Claim( *(ptr(long)) Offset( theObj, *Tab * 4 + 4) == (long) Tab[1],
	    "AOACheckObject: EnclosingObject match GCTab entry.");
      if( *Tab == -Tab[1] ) 
	AOACheckObject( Offset( theObj, *Tab * 4));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
#ifdef RTLAZY
      if( *theCell > 0 ) AOACheckReference( theCell );
#else
      if( *theCell != 0 ) AOACheckReference( theCell );
#endif
    }
  }
}

void AOACheckReference( theCell)
     handle(Object) theCell;
{
  long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
  long found = FALSE;

#ifdef RTLAZY
  if( *theCell > 0){
#else
  if ( *theCell ){
#endif
    Claim( inAOA(*theCell) || inIOA(*theCell) || inLVRA(*theCell),
	  "AOACheckReference: *theCell in IOA, AOA or LVRA");
    if( inIOA( *theCell) ){
      IOACheckObject( *theCell);
      for(i=0; (i < AOAtoIOAtableSize) && (!found); i++){
	if( *pointer ) found = (*pointer == (long) theCell);
	pointer++;
      }
      Claim( found, "AOACheckReference: *theCell in IOA but not in AOAtoIOAtable");
    }
    if( inLVRA(*theCell) )
      Claim( ((ref(ValRep)) *theCell)->GCAttr == (long) theCell,
	    "IOACheckReference:  ((ref(ValRep)) *theCell)->GCAttr == theCell");
  }
}

void AOACheckObjectSpecial( theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  Claim( !inBetaHeap(theProto),"#AOACheckObjectSpecial: !inBetaHeap(theProto)");
  
  if( (long) theProto < 0 ){  
    switch( (long) theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return;
    case (long) RefRepPTValue: return;
    case (long) ComponentPTValue:
      AOACheckObjectSpecial( ComponentItem( theObj));
      return;
    case (long) StackObjectPTValue:
      Claim( FALSE, "AOACheckObjectSpecial: theObj must not be StackObject.");
      return;
    case (long) StructurePTValue:
      return;
    case (long) DopartObjectPTValue:
      return;
    default:
      Claim( FALSE, "AOACheckObjectSpecial: theObj must be KNOWN.");
    }
  }else{
    ptr(short)  Tab;
    ptr(long)   theCell;
    
    /* Calculate a pointer to the GCTable inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .word Distance_To_Inclosing_Object
     *   .long T_entry_point
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessObject on static objects
     * on 1 level. The recursion in ProcessObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ) 
	AOACheckObjectSpecial( Offset( theObj, *Tab * 4));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
    }
  }
}

#endif
