/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * aoa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann 
 * and S|ren Brandt
 */
#include "beta.h"

#define REP ((struct ObjectRep *)theObj)

static void FollowObject(Object * theObj);
static void Phase1(void);
static void Phase2(long *numAddr, long *sizeAddr, long *usedAddr);
static void Phase3(void);
#ifdef NEWRUN
extern void DoGC(long *SP);
#endif

/* tempAOArootsAlloc:
 *  Not enough room for the AOAroots table in ToSpace.
 *  Instead allocate offline and copy existing part of table over
 */

void tempAOArootsAlloc(void)
{
    ptr(long) oldPtr;
    ptr(long) pointer = ToSpaceLimit; /* points to end of old table */

    if ( ! (tempAOAroots = (long *) MALLOC(IOASize)) ){
      char buf[300];
      sprintf(buf, "Could not allocate temporary AOAroots table.");
#ifdef macintosh
      EnlargeMacHeap(buf);
#endif
      Notify(buf);
      exit(1);
    } 
    AOArootsLimit = (long *) ((char *) tempAOAroots + IOASize);
    INFO_IOA(fprintf(output, "\nallocated temporary AOAroots table, "));
    DEBUG_IOA(fprintf(output, " [0x%x] ", tempAOAroots));
    oldPtr = AOArootsPtr; /* start of old table */
    AOArootsPtr = AOArootsLimit; /* end of new table */
    
    /* Copy old table backwards */
    while(pointer > oldPtr) *--AOArootsPtr = *--pointer; 

}

void tempAOArootsFree(void)
{
#ifdef RTDEBUG
  long roots = (long)tempAOAroots;
  Claim(tempAOAroots!=NULL, "tempAOArootsFree: tempAOAroots allocated");
#endif
  FREE(tempAOAroots);
  tempAOAroots = NULL;
  INFO_IOA(fprintf(output, "freed temporary AOAroots table\n"));
  DEBUG_IOA(fprintf(output, " [0x%x]", roots));
}

long AOACreateNewBlock = FALSE;

/* AOAallocate allocate 'size' number of bytes in the Adult object area.
 * If the allocation succeeds the function returns a reference to the allocated
 * object, 0 otherwise.
 */
static struct Object *AOAallocate(long numbytes)
{
  ptr(long)  oldTop;

  DEBUG_CODE( Claim(numbytes > 0, "AOAallocate: numbytes > 0") );
  /*DEBUG_AOA(if (AOATopBlock) 
	    fprintf(output, "AOATopBlock 0x%x, diff 0x%X\n",
		    AOATopBlock, (long)AOATopBlock->limit - (long)AOATopBlock->top));*/
  
  if( AOABaseBlock == 0){
    if( MallocExhausted || (AOABlockSize == 0) ) return 0;
    /* Check if the AOAtoIOAtable is allocated. If not then allocate it. */
    if( AOAtoIOAtable == 0 ) 
      if( AOAtoIOAAlloc() == 0 ){
	MallocExhausted = TRUE;
	INFO_AOA( fprintf(output,
			  "#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
			  (int)AOAtoIOAtableSize));
	return 0;
      }
    /* Try to allocate a new AOA block. */
    if( (AOABaseBlock = newBlock(AOABlockSize)) ){
      INFO_AOA( fprintf(output, "#(AOA: new block allocated %dKb.)\n",
			(int)AOABlockSize/Kb));
      AOATopBlock  = AOABaseBlock;
    }else{
      MallocExhausted = TRUE;
      INFO_AOA( fprintf(output, "#(AOA: block allocation failed %dKb.)\n",
			(int)AOABlockSize/Kb));
      return 0;
    }
  }
  /* Try to find space between AOATopBlock->top and AOATopBlock->limit. */
  oldTop = AOATopBlock->top;
  if( areaSize(oldTop,AOATopBlock->limit) > numbytes){
    AOATopBlock->top = (ptr(long)) Offset( oldTop, numbytes);
    return (ref(Object)) oldTop;
  }else{
    /* maybe there is a free block AOATopBlock->next. */
    if( AOATopBlock->next ){
      AOATopBlock = AOATopBlock->next;
      oldTop = AOATopBlock->top;
      if( areaSize(oldTop,AOATopBlock->limit) > numbytes){
	AOATopBlock->top = (ptr(long)) Offset( oldTop, numbytes);
	return (ref(Object)) oldTop;
      }
    }
  }
  
  if( AOACreateNewBlock ){
    if( (AOATopBlock->next = newBlock( AOABlockSize)) ){
      INFO_AOA( fprintf( output, "#(AOA: new block allocated %dKb.)\n",
			(int)AOABlockSize/Kb) );
      AOATopBlock = AOATopBlock->next;
      oldTop = AOATopBlock->top;
      AOACreateNewBlock = FALSE;
      if( areaSize(oldTop,AOATopBlock->limit) > numbytes){
	AOATopBlock->top = (ptr(long)) Offset( oldTop, numbytes);
	return (ref(Object)) oldTop;
      }else{
	Notify("#AOA warning: Object size is larger then AOABlockSize"); 
	return 0;
      }
    }else{
      MallocExhausted = TRUE;
      INFO_AOA( fprintf( output, "#(AOA: block allocation failed %dKb.)\n",
			(int)AOABlockSize/Kb));
      AOANeedCompaction = TRUE;
      return 0;
    }
  }else{
    AOANeedCompaction = TRUE;
    return 0;
  }    
}

#ifdef NEWRUN

struct Object *AOAalloc(long numbytes, long *SP)
{
  struct Object *theObj = AOAallocate(numbytes);
  DEBUG_CODE(NumAOAAlloc++);
  if (!theObj){
    /* AOAallocate failed. This means that AOANeedCompaction will be
     * true now. Force an IOAGc.
     */
    DEBUG_AOA(fprintf(output, "AOAalloc: forcing IOAGc and AOAGc\n"));
    DoGC(SP);
    /* Try again */
    theObj = AOAallocate(numbytes);
  }
  return theObj;
}
struct Object *AOAcalloc(long numbytes, long *SP)
{
  struct Object *theObj = AOAalloc(numbytes, SP);
  if (theObj) long_clear(theObj, numbytes);
  return theObj;
}
#endif


/* CopyObjectToAOA:
 *  move an object to AOA and return the address of the new location
 *  If the allocation in AOA failed the function returns 0;
 */
ref(Object) CopyObjectToAOA( theObj)
     ref(Object) theObj;
{
  ref(Object) newObj;
  long        size;
  register ptr(long) src;
  register ptr(long) dst;
  register ptr(long) theEnd;
  
#if 0
  if (theObj->Proto == RefRepPTValue){
    fprintf(output, "ToAOA: RefRep=0x%x\n", theObj);
    fprintf(output, "  0x%x\n", *((long*)theObj));
    fprintf(output, "  0x%x\n", *((long*)theObj+1));
    fprintf(output, "  0x%x\n", *((long*)theObj+2));
    fprintf(output, "  0x%x\n", *((long*)theObj+3));
    fprintf(output, "  0x%x\n", *((long*)theObj+4));
    fprintf(output, "  0x%x\n", *((long*)theObj+5));
    fprintf(output, "  0x%x\n", *((long*)theObj+6));
    fprintf(output, "  0x%x\n", *((long*)theObj+7));
    fprintf(output, "  ...\n");
  }
#endif

  size = 4*ObjectSize( theObj); 
  DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#ToAOA: ObjectSize(theObj) > 0") );

  if( (newObj = AOAallocate( size)) == 0 ) return 0;
  
  theEnd = (ptr(long)) (((long) newObj) + size); 
  
  src = (ptr(long)) theObj; dst = (ptr(long)) newObj; 
  while( dst < theEnd) *dst++ = *src++; 
  
  newObj->GCAttr = 0;
  
  /* Set one forward reference in theObj to newObj */
  theObj->GCAttr = (long) newObj;
  
  DEBUG_AOA( AOAcopied += size );

  DEBUG_AOA(if(isStackObject(theObj)) 
	    fprintf(output, 
		    "CopyObjectToAOA: moved StackObject to 0x%x\n", newObj));

  /* DEBUG_AOA( fprintf(output, "#ToAOA: IOA-address: 0x%x AOA-address: 0x%x proto: 0x%x size: %d\n", 
		     (int)theObj, (int)newObj, (int)(theObj->Proto), (int)size)); */

#if 0
  if (theObj->Proto == RefRepPTValue){
    fprintf(output, "ToAOA: RefRep=0x%x\n", newObj);
  }
#endif
 
  /* Return the new object in AOA */
  return newObj;
}

/*
 *  AOAGc: perform a mark/sweep garbagecollection on the AOA heap.
 *  Should be called after IOAGc when AOANeedCompaction == TRUE;
 */
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
  if (negAOArefs)
    negAOArefsRESET ();
#endif

  INFO_AOA( fprintf(output, "\n#(AOA-%d ", (int)NumAOAGc); fflush(output) );
  /* Mark all reachable objects within AOA and reverse all pointers. */
#if defined(macintosh) ||defined(MAC)
  RotateTheCursorBack();
#endif
  DEBUG_AOA( fprintf( output, "1"); fflush(output) );
  Phase1();  
  /* Calculate new addresses for the reachable objects and reverse pointers. */
#if defined(macintosh) ||defined(MAC)
  RotateTheCursorBack();
#endif
  DEBUG_AOA( fprintf( output, "2"); fflush(output) );
  Phase2( &blocks, &size, &used); 
  /* Copy all reachable objects to their new locations. */
#if defined(macintosh) ||defined(MAC)
  RotateTheCursorBack();
#endif
  DEBUG_AOA( fprintf( output, "3"); fflush(output) );
  Phase3();  
#if defined(macintosh) ||defined(MAC)
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

#ifdef UseRefStack
  {
      long **pointer = (long **)AOArootsLimit;

      /*
       * Restore the tag bits saved from stackobjects in Phase1 from the
       * AOAroots table. See Phase1() for a comment. - poe.
       */
      while ((long *)pointer > AOArootsPtr) {
	  pointer--;
	  if(!isLazyRef(*pointer) && ((long)*pointer & 1)) {
	      (long)*pointer &= ~1; /* clear tag bit in table */
	      **pointer |= 1;       /* set it in stackobject */
	  }
      }
  }
#endif
  
  INFO_AOA( fprintf(output, "%dKb in %d blocks, %d%% free)\n", 
		    (int)toKb(size), 
		    (int)blocks, 
		    (int)(100 - used/(size/100))); 
	   fflush(output));
}


static long *RAFStackBase;
static long *RAFStackTop;
static long *RAFStackLimit;

static void extendRAFStackArea(void)
/* Extend (temporary) space used to hold unprocessed reverse-and-follow references. */
{
  long oldSize;
  long newSize;
  long *newBase;

  oldSize = (long)RAFStackTop - (long)RAFStackBase;
  newSize = oldSize * 2;
  if ((newBase = (long *)MALLOC(newSize)) != NULL) {
    INFO_AOA(fprintf(output, 
		     "#(AOA: RAF stack area allocated: %d longs)\n", 
		     (int)newSize/4));
  } else {
    char buf[300];
    sprintf(buf,
	    "AOA GC: Failed to allocate RAF stack area: %d longs.", 
	    (int)newSize/4);
#ifdef macintosh
    EnlargeMacHeap(buf);
#endif
    Notify(buf);
    exit(-1);
  }
  memcpy(newBase, RAFStackBase, oldSize);
  if (RAFStackBase != IOA) {
    FREE(RAFStackBase);
    INFO_AOA(fprintf(output, 
		     "#(AOA: RAF stack area freed: %d longs)\n", (int)oldSize/4));
  }
  RAFStackBase = newBase;
  RAFStackLimit = (long*) ((long)RAFStackBase + newSize);
  RAFStackTop = (long*)((long)RAFStackBase + oldSize);
}

static void freeRAFStackArea(void)
/* Free any external space allocated to hold unprocessed RAF-references */
{
  if (RAFStackBase != IOA) {
    FREE(RAFStackBase);
    INFO_AOA(fprintf(output, "#(AOA: RAF stack area freed: %d longs)\n", 
		     (int)((long)RAFStackLimit - (long)RAFStackBase)/4));
  }
}

#define RAFPush(p) { \
    if (RAFStackTop >= RAFStackLimit) \
      extendRAFStackArea(); \
    *RAFStackTop++ = (long)(p); \
  }

/* ReverseAndFollow is used during Phase1 of the Mark-Sweep GC. 
 * It reverses the pointer and calls FollowObject iff the referenced 
 * object has not been followed.
 */

static void ReverseAndFollow(void)
{
  handle(Object) theCell;
  ref(Object) theObj;
  ref(Object) autObj;

  while (RAFStackTop > RAFStackBase) {
    theCell = casthandle(Object)(*--RAFStackTop);
    theObj = *theCell;
  
    if( inAOA( theObj) ){
      if( theObj->GCAttr == 0 ){
	/* theObj is autonomous and not marked. */
	*theCell = (ref(Object)) 1; 
	theObj->GCAttr = (long) theCell;
	FollowObject( theObj);
	continue;
      }
      if( !(isStatic(theObj->GCAttr)) ){
	/* theObj is marked. */
	*theCell = (ref(Object)) theObj->GCAttr; 
	theObj->GCAttr = (long) theCell;
	continue;
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
      if (inAOA(theCell) && inLVRA(theObj)) { 
	/* Save the theCell for later use */
	if ((long *)RAFStackTop >= AOAtoLVRAtable)
	  if (AOAtoLVRAtable > IOA) 
	    extendRAFStackArea(); 
	  else
#ifdef NEWRUN	   
	    BetaError(AOAtoLVRAfullErr, CurrentObject, StackEnd);
#else
	    BetaError(AOAtoLVRAfullErr, 0);
#endif
	*--AOAtoLVRAtable = (long)theCell;
	AOAtoLVRAsize++;
	if (RAFStackBase == IOA)
	  RAFStackLimit--;
	DEBUG_LVRA( Claim( isValRep(*theCell), "Phase1: LVRA cycle"));
	DEBUG_LVRA( Claim( (*theCell)->GCAttr == (long) theCell,
			  "Phase1: LVRA cycle"));
      }
    }
  }
}

static void FollowItem(ref(Item) theObj)
{ 
  ref(ProtoType) theProto  = theObj->Proto;
  
  ptr(short)     Tab;
  ptr(long)      theCell;
  
  /* Calculate a pointer to the GCTable inside the ProtoType. */
  Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
  
  while( *Tab != 0 ){
    if( *Tab == -Tab[1] ) 
      FollowObject( (struct Object*)Offset( theObj, *Tab * 4));
    Tab += 4;
  }
  Tab++;
  
  /* Handle all the references in the Object. */
  while( *Tab != 0 ){
    theCell = (ptr(long)) Offset( theObj, ((*Tab++) & (short) ~3) );
    /* sbrandt 24/1/1994: 2 least significant bits in prototype 
     * dynamic offset table masked out. As offsets in this table are
     * always multiples of 4, these bits may be used to distinguish
     * different reference types. */ 
#ifdef RTLAZY
    if (isPositiveRef(*theCell))
      {RAFPush(theCell);}
    else 
      if (isLazyRef (*theCell)) 
	negAOArefsINSERT ((long) theCell);
#else
    if (*theCell != 0) 
      RAFPush(theCell);
#endif
  }
}

#ifndef KEEP_STACKOBJ_IN_IOA
/* PushAOACell:
 *  Used to process stackobjects in AOA object.
 */
static void PushAOACell(struct Object **theCell, struct Object *theObj)
{
  Ck(theObj);
  if(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell)) {
    if (isObject(*theCell))
      RAFPush(theCell);
  }
}
#ifdef RTDEBUG
static void CheckAOACell(struct Object **theCell, struct Object *theObj)
{
  Ck(theObj);
  if(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell)) {
    if (isObject(*theCell))
      AOACheckReference(theCell);
  }
}
#endif
#endif

/* FollowObject is used during Phase1 of the Mark-Sweep GC. 
 * For each referernce inside theObj it calls ReverseAndFollow.
 */

static void FollowObject(ref(Object) theObj)
{ 
  ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( isNegativeRef(theProto) ){  
    switch( (long) theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return;
      /* No references in a Value Repetition, so do nothing*/
      
    case (long) DynItemRepPTValue:
    case (long) DynCompRepPTValue:
#ifdef STATIC_OBJECT_REPETITIONS
    case (long) StatItemRepPTValue:
    case (long) StatCompRepPTValue:
#endif /* STATIC_OBJECT_REPETITIONS */
      /* Follow the iOrigin */
#ifdef RTLAZY
      if( isPositiveRef(REP->iOrigin) ) 
	{RAFPush(&REP->iOrigin);} 
      else 
	if (isLazyRef (REP->iOrigin))
	  negAOArefsINSERT ((long)&REP->iOrigin);
#else
      /* no need to test for zero - the object is always there */
      RAFPush(&REP->iOrigin);
#endif
      /* Follow rest of repetition */
      switch( (long) theProto ){
      case (long) DynItemRepPTValue:
      case (long) DynCompRepPTValue:
	{ long *pointer;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { 
	    size = REP->HighBorder;
	    pointer = (long *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
#ifdef RTLAZY
	      if( isPositiveRef(*pointer) ) 
		{RAFPush(pointer);} 
	      else 
		if (isLazyRef (*pointer))
		  negAOArefsINSERT ((long)pointer);
#else
	      /* no need to test for zero - the object is always there */
	      RAFPush(pointer);
#endif
	      pointer++;
	    }
	  }
	}
	break;
#ifdef STATIC_OBJECT_REPETITIONS
      case (long) StatItemRepPTValue:
	{ struct Item *theItem;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { 
	    size = REP->HighBorder;
	    theItem = (struct Item *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
	      FollowItem(theItem);
	      theItem = (struct Item *)((long)theItem + ItemSize(REP->iProto));
	    }
	  }
	}
	break;
      case (long) StatCompRepPTValue:
	{ struct Component *theComp;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { 
	    size = REP->HighBorder;
	    theComp = (struct Component *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
	      FollowObject((Object * )theComp);
	      theComp = (struct Component *)((long)theComp + ComponentSize(REP->iProto));
	    }
	  }
	}
	break;
#endif /* STATIC_OBJECT_REPETITIONS */
      }
      return;

    case (long) RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	
	for (index=0; index<size; index++) {
#ifdef RTLAZY
	  if( isPositiveRef(*pointer) ) 
	    {RAFPush(pointer);} 
	  else 
	    if (isLazyRef (*pointer))
	      negAOArefsINSERT ((long)pointer);
#else
	  if( *pointer != 0) 
	    RAFPush(pointer);
#endif
	  pointer++;
	}
      }
      return;
      
    case (long) ComponentPTValue:
      { ref(Component) theComponent;
	
	theComponent = Coerce( theObj, Component);
	RAFPush(&theComponent->StackObj);
	RAFPush(&theComponent->CallerComp);
	RAFPush(&theComponent->CallerObj);
	FollowItem( ComponentItem( theComponent));
      }
      return;
      
    case (long) StackObjectPTValue:
#ifdef KEEP_STACKOBJ_IN_IOA
      Notify("FollowObject: Error: StackObject in AOA.");
#else
      /* Machine dependant stackobj processing */
#ifdef crts
      /* Scan the StackObject for object references and follow all entries */
      { ref(StackObject) theStackObject;
        handle(Object)   theCell; 
        long             *stackptr; 
        long             size;
        
        theStackObject = Coerce(theObj, StackObject);
        
        stackptr = &theStackObject->Body[1] + theStackObject->StackSize;
	size = theStackObject->BodySize-theStackObject->StackSize-1;
	for(; size > 0; size--, stackptr++) {
          theCell = (handle(Object)) stackptr;
	  PushAOACell(theCell, *theCell);
        }
      }
#endif /* crts */
#ifdef NEWRUN
      ProcessStackObj((struct StackObject *)theObj, PushAOACell);
#endif /* NEWRUN */
#endif /* KEEP_STACKOBJ_IN_IOA */
      return;
      
    case (long) StructurePTValue:
      RAFPush(&(toStructure(theObj))->iOrigin);
      return;

    case (long) DopartObjectPTValue:
      RAFPush(&(cast(DopartObject)(theObj))->Origin);
      return;
    }
  }else FollowItem( (struct Item*) theObj);
}

/* Phase1 of the Mark-Sweep GC, reverse:
 * all cells in root(AOA),
 * all cells in AOA, where cells point into AOA
 */
static void Phase1(void)
{ /* Call FollowReference for each root to AOA. */

  /*  During AOA GC, IOA (ie. from-space) is unused; during Phase 1, it is   */
  /*  utilized as follows:                                                   */
  /*  Unprocessed reverse-and-follow references are stored from IOA upwards; */
  /*  references from AOA to LVRA are stored from IOALimit downwards.        */
  /*  On clash, RAF area is allocated externally and freed at end of phase.  */
  /*  If RAF area runs full, it is dynamically resized; if AOA-to-LVRA       */
  /*  reference table runs full, AOAtoLVRAfullErr error is signalled.        */
  /*                                                                         */
  /*  IOA                                AOAtoLVRAtable          IOALimit    */
  /*  v                                  v                       v           */
  /*  +----------------+----------------+-----------------------+            */
  /*  |xxxxxxxxxxxxxxxx|                |xxxxxxxxxxxxxxxxxxxxxxx|            */
  /*  +----------------+----------------+-----------------------+            */
  /*  ^                 ^                ^                                   */
  /*  RAFStackBase      RAFStackTop      RAFStackLimit                       */

  ptr(long) pointer = AOArootsLimit;

  AOAtoLVRAtable = IOALimit;
  AOAtoLVRAsize = 0;
  RAFStackBase = IOA;
  RAFStackTop = IOA;
  RAFStackLimit = AOAtoLVRAtable;
  
#ifdef RTDEBUG
  { /* Make sure that there are no duplicate AOA roots! */
    long old=0;
    WordSort((unsigned long *)AOArootsPtr, AOArootsLimit-AOArootsPtr);
    while (pointer > AOArootsPtr){
#ifdef UseRefStack
      /* See below... */
      if(!isLazyRef(*((long *)*(pointer-1))) && (*((long *)*(pointer-1)) & 1)) {
	*((long *)*(pointer-1)) &= ~1; /* clear tag bit */
	*(pointer-1) |= 1;                 /* set it in table */
      }
#endif
      if (old == *--pointer){
	INFO_AOA(fprintf(output, "Phase1: Duplicate AOA root: 0x%x\n", (int)old));
      } else {
	old = *pointer;
	RAFPush(*pointer & ~1);
      }
    }
  }
#else /* RTDEBUG */
  while( pointer > AOArootsPtr) {
    pointer--;
#ifdef UseRefStack
    /*
     * Dreadful hack. We have to remove the tag bits from those references
     * in stackobjects that have them, so the Follow*() can handle them,
     * but we have to save them somewhere. They are saved in the LSB of
     * the pointers in the AOAroots table. They are restored just
     * before the AOAGc finishes in AOAGc().
     */
    if(!isLazyRef(*((long *)*pointer)) && (*((long *)*pointer) & 1)) {
      *((long *)*pointer) &= ~1; /* clear tag bit in stackobject */
      *pointer |= 1;         /* set it in table */
    }
#endif
    RAFPush(*pointer & ~1);
  }
#endif /* RTDEBUG */
  ReverseAndFollow();
  freeRAFStackArea();
}

#define isAlive(x)  (toObject(x)->GCAttr != 0)
#define isMarked(x) (x->GCAttr == 1)
#define endChain(x) (( -0xFFFF <= ((long) (x))) && (((long) (x)) <= 1))

static void handleAliveStatic(ref(Object) theObj, ref(Object) freeObj)
{
  handle(Object) theCell;
  handle(Object) nextCell;
  ref(ProtoType) theProto = theObj->Proto;
  ptr(short)     Tab;
  
  theCell = (handle(Object)) theObj->GCAttr;
  while( !endChain(theCell)){
    nextCell = (handle(Object)) *theCell;
    *theCell = freeObj;
    theCell = nextCell;
  }
  theObj->GCAttr = (long) theCell; /* Save forward pointer to Phase3. */
  DEBUG_AOA( Claim( theObj->GCAttr < 0, "handleAliveStatic:  theObj->GCAttr < 0"));
  
  if( !isNegativeRef(theProto)){
    /* theObj is an item. */
    /* Calculate a pointer to the GCTable inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ){ 
	handleAliveStatic( (struct Object*) Offset( theObj, *Tab * 4),(struct Object*) Offset( freeObj, *Tab * 4) );
	DEBUG_AOA( Claim( *(ptr(long)) Offset( theObj, *Tab * 4 + 4)
			 == (long) Tab[1],
			 "AOACheckObject: EnclosingObject match GCTab entry."));
      }
      Tab += 4;
    }
  }else{
    /* This is a component so update theObj and Proto to Item. */
    if( theProto == ComponentPTValue )
      handleAliveStatic( (struct Object*)ComponentItem( theObj), (struct Object*)ComponentItem( freeObj) );
  } 
}

static void handleAliveObject(ref(Object) theObj, ref(Object) freeObj)
{
  handle(Object) theCell;
  handle(Object) nextCell;
  ref(ProtoType) theProto = theObj->Proto;
  ptr(short)     Tab;
  
  theCell = (handle(Object)) theObj->GCAttr;
  while( !endChain(theCell)){
    nextCell = (handle(Object)) *theCell;
    *theCell = freeObj;
    theCell = nextCell;
  }
  DEBUG_AOA( Claim( (long) theCell == 1,
		   "handleAliveObject:  chainEnd == 0 or 1"));
  theObj->GCAttr = (long) freeObj; /* Save forward pointer to Phase3. */
  
  if( !isNegativeRef(theProto)){
    /* theObj is an item. */
    /* Calculate a pointer to the GCTable inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ){
	handleAliveStatic( (struct Object*)Offset( theObj, *Tab * 4), (struct Object*)Offset( freeObj, *Tab * 4) );
	DEBUG_AOA( Claim( *(ptr(long)) Offset( theObj, *Tab * 4 + 4)
			 == (long) Tab[1],
			 "AOACheckObject: EnclosingObject match GCTab entry."));
      }
      Tab += 4;
    }
  }else{
    /* This is a component so update theObj and Proto to Item. */
    if( theProto == ComponentPTValue )
      handleAliveStatic( (struct Object*)ComponentItem( theObj), (struct Object*)ComponentItem( freeObj) );
  } 
}



static void Phase2(ptr(long) numAddr, ptr(long) sizeAddr, ptr(long) usedAddr)
{
  ref(Block)  theBlock  = AOABaseBlock;
  ref(Block)  freeBlock = AOABaseBlock;
  ref(Object) theObj;
  ref(Object) freeObj;
  ref(Object) enclObj;
  long        theObjectSize;
  long        numOfBlocks = 0;
  
  long        usedSpace = 0;
  long        allSpace  = 0;

  int enclDist;
  
  freeObj   = (ref(Object)) BlockStart( freeBlock);
  
  while( theBlock ){
    numOfBlocks++;
    theObj = (ref(Object)) BlockStart(theBlock);
    while( (ptr(long)) theObj < theBlock->top ){
#if 0
      fprintf(output, "phase2: theObj=0x%x\n", theObj); fflush(output);
#endif
      theObjectSize = 4*ObjectSize( theObj);
      DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#Phase2: ObjectSize(theObj) > 0") );
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
	if (!inToSpace(*current)){

	  theObj = cast(Object)(*current);
	  if (isStatic(theObj->GCAttr)) {
	    GetDistanceToEnclosingObject(theObj,enclDist);
	    enclObj = cast(Object) Offset(theObj,enclDist);
	    if (enclObj->GCAttr)
	      theObj = cast(Object) Offset(enclObj->GCAttr,-enclDist);
	    else
	      theObj = 0; /* Enclosing object is dead */
	  } else {
	    /* It it not a static part object, so either the GCAttr is a
             * forward reference to the objects new position, or it is
             * NONE if the object is dead. */
	    theObj = cast(Object) theObj->GCAttr;
	  }
	    
	  INFO_DOT(fprintf(output, 
			   "#DOT: updating AOA reference 0x%x to 0x%x\n", 
			   (int)(*current), (int)theObj));
	  *current = (long) theObj;
	  if (!theObj) DOTSize--; /* Element was deleted. */

	  DEBUG_AOA( Claim( (theObj == 0) || inAOA (theObj) ,"DOT element NONE or in AOA "));

	}
      }
      current++;
    }
  }
} 

static void FindInterval(long * table, long size, ref(Block) block, long * startAddr, long * stopAddr)
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
  long *   table;
  
  /* Calculate the size of table. */
  AOAtoIOACount = 0;
  {
    long i; long * pointer = BlockStart( AOAtoIOAtable);
    for(i=0; i<AOAtoIOAtableSize; i++) {
#ifdef RTLAZY
      if( isPositiveRef(*pointer) ) AOAtoIOACount++;
      pointer++;
#else
      if( *pointer++ ) AOAtoIOACount++;
#endif
    }
  }
  
  if ((long)AOAtoLVRAtable - (long)IOA > AOAtoIOACount * 4)
    table = IOA;
  else {
    if( !(table = (long *) MALLOC( AOAtoIOACount * 4))){
      char buf[300];
      sprintf(buf,"#Phase3: allocation failed %d longs\n", (int)AOAtoIOACount);
#ifdef macintosh
      EnlargeMacHeap(buf);
#endif
      Notify(buf);
      exit(-1);
    }
    INFO_AOA( fprintf(output, "#(AOA: new block for table %d longs)\n",
		      (int)AOAtoIOACount));
  }
  
  /* Move compact(AOAtoIOAtable) -> table. */
  {
    long i, counter = 0;  long * pointer = BlockStart( AOAtoIOAtable);
    for(i=0; i < AOAtoIOAtableSize; i++){
#ifdef RTLAZY
      if( isPositiveRef(*pointer) ) table[counter++] = *pointer;
#else
      if( *pointer ) table[counter++] = *pointer;
#endif
      pointer++;
    }
    DEBUG_AOA( Claim( counter == AOAtoIOACount,"Phase3: counter == AOAtoIOACount"));
  }
  
  DEBUG_AOA( fprintf(output,"(AOAtoIOA#%d)", (int)AOAtoIOACount));
  DEBUG_AOA( fprintf(output,"(AOAtoLVRA#%d)", (int)AOAtoLVRAsize));
  
  /* Clear the AOAtoIOAtable. */
  AOAtoIOAClear();
  
  WordSort((unsigned long*)table, AOAtoIOACount);
  WordSort((unsigned long*)AOAtoLVRAtable, AOAtoLVRAsize);
#ifdef RTLAZY
  if (negAOArefs)
    WordSort((unsigned long*)negAOArefs, negAOAsize);
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
      
      while( (long *) theObj < theBlock->top ){
	theObjectSize = 4*ObjectSize( theObj);
	DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#Phase3: ObjectSize(theObj) > 0") );
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
	    if (inToSpace( *(long *) (table[start]-diff)))
	      AOAtoIOAInsert( (handle(Object))(table[start]-diff));
	      
	    start++;
	  }
	  while( (start1<stop1) && (AOAtoLVRAtable[start1] < (long)nextObj) ){
	    DEBUG_AOA( Claim( inLVRA( (ref(Object))(*(long *)(AOAtoLVRAtable[start1]-diff))),
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
	    DEBUG_AOA( Claim( inLVRA( (ref(Object))(*(long *)(AOAtoLVRAtable[start1]))),
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
    INFO_AOA( fprintf(output, "#(AOA: block for table freed %d longs)\n",
		      (int)AOAtoIOACount));
  }
}

#ifdef RTDEBUG
void AOACheck()
{
  ref(Block)  theBlock  = AOABaseBlock;
  ref(Object) theObj;
  long        theObjectSize;
  
  /* if (theBlock != 0)
     fprintf(output, "AOACheck: AOABaseBlock: 0x%x, top: 0x%x\n", (int)AOABaseBlock, (int)(AOABaseBlock->top)); */
  while( theBlock ){
    theObj = (ref(Object)) BlockStart(theBlock);
    while( (long *) theObj < theBlock->top ){
      theObjectSize = 4*ObjectSize( theObj);
      /* fprintf(output,"AOACheck: ObjectSize=0x%x, ", (int)theObjectSize); */
      Claim(ObjectSize(theObj) > 0, "#AOACheck: ObjectSize(theObj) > 0");
      AOACheckObject( theObj);
      theObj = (ref(Object)) Offset( theObj, theObjectSize);
    }
    theBlock = theBlock->next;
    /* if (theBlock != 0)
      fprintf(output, "AOACheck: block: 0x%x, top: 0x%x\n", (int)theBlock, (int)(theBlock->top)); */
  }
} 

void AOACheckObject( theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;

  Claim( !inBetaHeap((ref(Object))theProto),
	"#AOACheckObject: !inBetaHeap(theProto)");
  
  if( isNegativeRef(theProto) ){  
    switch( (long)  theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return; /* No references in the type of object, so do nothing*/
      
    case (long) DynItemRepPTValue:
    case (long) DynCompRepPTValue:
#ifdef STATIC_OBJECT_REPETITIONS
    case (long) StatItemRepPTValue:
    case (long) StatCompRepPTValue:
#endif /* STATIC_OBJECT_REPETITIONS */
      /* Check iOrigin */
#ifdef RTLAZY
      if( isPositiveRef(REP->iOrigin) ) 
	AOACheckReference( (handle(Object))(&REP->iOrigin) );
#else
      AOACheckReference( (handle(Object))(&REP->iOrigin) );
#endif
      /* Check rest of repetition */
      switch((long)theProto){
      case (long) DynItemRepPTValue:
      case (long) DynCompRepPTValue:
	{ long *pointer;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { 
	    size = REP->HighBorder;
	    pointer = (long *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
#ifdef RTLAZY
	      if( isPositiveRef(*pointer) ) 
		AOACheckReference( (handle(Object))(pointer) );
#else
	      AOACheckReference( (handle(Object))(pointer) );
#endif
	      pointer++;
	    }
	  }
	}
	break;
#ifdef STATIC_OBJECT_REPETITIONS
      case (long) StatItemRepPTValue:
	{ struct Item *theItem;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { 
	    size = REP->HighBorder;
	    theItem = (struct Item *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
	      AOACheckObject((struct Object *)theItem);
	      theItem = (struct Item *)((long)theItem + ItemSize(REP->iProto));
	    }
	  }
	}
	break;
      case (long) StatCompRepPTValue:
	{ struct Component *theComp;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { 
	    size = REP->HighBorder;
	    theComp = (struct Component *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
	      AOACheckObject((struct Object *)theComp);
	      theComp = (struct Component *)((long)theComp + ComponentSize(REP->iProto));
	    }
	  }
	}
	break;
#endif /* STATIC_OBJECT_REPETITIONS */
      }
      return;

    case (long) RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { long * pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (long *) &toRefRep(theObj)->Body[0];
	
	for(index=0; index<size; index++) {
#ifdef RTLAZY
	  if( isPositiveRef(*pointer) ) AOACheckReference( (handle(Object))(pointer++) );
#else
	  if( *pointer != 0) AOACheckReference( (handle(Object))(pointer++) );
#endif
	  else pointer++;
	}
      }
      
      return;
      
    case (long) ComponentPTValue:
      { ref(Component) theComponent;
	
	theComponent = Coerce( theObj, Component);
	if (theComponent->StackObj == (ref(StackObject))-1) {
	  /* printf("\nAOACheckObject: theComponent->StackObj=-1, skipped!\n"); */
	} else {
#if 0
	  fprintf(output, 
		  "AOACheckObject: &theComponent->StackObj: 0x%x, theComponent->StackObj: 0x%x\n", 
		  (int)&theComponent->StackObj, (int)theComponent->StackObj);
#endif
	  AOACheckReference( (handle(Object))(&theComponent->StackObj));
	}
#if 0
	fprintf(output, 
		"AOACheckObject: &theComponent->CallerComp: 0x%x\n", 
		(int)&theComponent->CallerComp);
#endif
	AOACheckReference( (handle(Object))(&theComponent->CallerComp));
#if 0
	fprintf(output, 
		"AOACheckObject: &theComponent->CallerObj: 0x%x\n", 
		(int)&theComponent->CallerObj);
#endif
	AOACheckReference( (handle(Object))(&theComponent->CallerObj));
	AOACheckObject( (ref(Object))(ComponentItem( theComponent)));
      }
      return;   
    case (long) StackObjectPTValue:
#ifdef KEEP_STACKOBJ_IN_IOA
      Claim( FALSE, "AOACheckObject: theObj should not be StackObject.");
#else
#ifdef crts
      /* CRTS */
      /* Scan the StackObject for object references and follow all entries */
      { ref(StackObject) theStackObject;
        handle(Object)   theCell; 
        long             *stackptr; 
        long             size;
        
        theStackObject = Coerce(theObj, StackObject);
        
        stackptr = &theStackObject->Body[1] + theStackObject->StackSize;
	size = theStackObject->BodySize-theStackObject->StackSize-1;
	for(; size > 0; size--, stackptr++) {
          theCell = (handle(Object)) stackptr;
	  if(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell)) {
	     if (isObject(*theCell))
               AOACheckReference((handle(Object))stackptr);
	  }
        }
      }
#endif /* crts */
#ifdef NEWRUN
      ProcessStackObj((struct StackObject *)theObj, CheckAOACell);
#endif /* NEWRUN */
#if !(defined(crts)||defined(NEWRUN))
      fprintf(output, 
	      "AOACheckObject: no check of stackobject 0x%x\n", theObj);
#endif
#endif /* KEEP_STACKOBJ_IN_IOA */
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
    long *   theCell;
    
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
      Claim( *(long *) Offset( theObj, *Tab * 4 + 4) == (long) Tab[1],
	    "AOACheckObject: EnclosingObject match GCTab entry.");
      if( *Tab == -Tab[1] ) 
	AOACheckObject( (ref(Object))(Offset( theObj, *Tab * 4)));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (long *) Offset( theObj, ((*Tab++) & (short) ~3) );
      /* sbrandt 24/1/1994: 2 least significant bits in prototype 
       * dynamic offset table masked out. As offsets in this table are
       * always multiples of 4, these bits may be used to distinguish
       * different reference types. */ 
#ifdef RTLAZY
      if( isPositiveRef(*theCell) ) AOACheckReference( (handle(Object))theCell );
#else
      if( *theCell != 0 ) AOACheckReference( (handle(Object))theCell );
#endif
    }
  }
}

void AOACheckReference( theCell)
     handle(Object) theCell;
{
  long i; long * pointer = BlockStart( AOAtoIOAtable);
  long found = FALSE;

#ifdef RTLAZY
  if( isPositiveRef(*theCell) ){
#else
  if ( *theCell ){
#endif
    Claim(inAOA(*theCell) || inIOA(*theCell) || inLVRA(*theCell),
	  "AOACheckReference: *theCell in IOA, AOA or LVRA");
    if( inIOA( *theCell) ){
      IOACheckObject( *theCell);
      for(i=0; (i < AOAtoIOAtableSize) && (!found); i++){
	if( *pointer ) found = (*pointer == (long) theCell);
	pointer++;
      }
      if (!found){
	char buf[100];
	sprintf(buf, 
		"AOACheckReference: *theCell [*(0x%x)] in IOA but not in AOAtoIOAtable",
		theCell);
	Claim( found, buf);
      }
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
  
  Claim( !inBetaHeap((ref(Object))theProto),
	"#AOACheckObjectSpecial: !inBetaHeap(theProto)");
  
  if( isNegativeRef(theProto) ){  
    switch( (long) theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return;
#ifdef STATIC_OBJECT_REPETITIONS
    case (long) StatItemRepPTValue: return;
    case (long) StatCompRepPTValue: return;
#endif /* STATIC_OBJECT_REPETITIONS */
    case (long) DynItemRepPTValue: return;
    case (long) DynCompRepPTValue: return;
    case (long) RefRepPTValue: return;
    case (long) ComponentPTValue:
      AOACheckObjectSpecial( (ref(Object))(ComponentItem( theObj)));
      return;
    case (long) StackObjectPTValue:
#ifdef KEEP_STACKOBJ_IN_IOA
      Claim( FALSE, "AOACheckObjectSpecial: theObj must not be StackObject.");
#else
      fprintf(output, 
	      "AOACheckObjectSpecial: no check of stackobject 0x%x\n", theObj);
#endif
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
    long *   theCell;
    
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
	AOACheckObjectSpecial( (ref(Object))(Offset( theObj, *Tab * 4)));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (long *) Offset( theObj, ((*Tab++) & (short) ~3) );
      /* sbrandt 24/1/1994: 2 least significant bits in prototype 
       * dynamic offset table masked out. As offsets in this table are
       * always multiples of 4, these bits may be used to distinguish
       * different reference types. */ 
    }
  }
}

#endif
