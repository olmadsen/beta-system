/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * aoa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann 
 * and S|ren Brandt
 */
#include "beta.h"

#define REP ((struct ObjectRep *)theObj)

#ifdef NEWRUN
extern void DoGC(long *SP);
#else
extern void DoGC(void);
#endif

/* GLOBAL FUNCTIONS, declared in C/function.h
 *
 *  void tempAOArootsAlloc(void)
 *  void tempAOArootsFree(void)
 *  struct Object *AOAallocate(long numbytes)
 *  struct Object *AOAalloc(AOA_ALLOC_PARAMS)
 *  struct Object *AOAcalloc(AOA_ALLOC_PARAMS)
 *  ref(Object) CopyObjectToAOA( ref(Object) theObj theObj)
 *  long sizeOfAOA(void)
 *  void AOAGc()
 *  #ifdef nti 
 *  void DoGC()
 *  #endif
 *  #ifdef RTDEBUG
 *  void AOACheck()
 *  void AOACheckObject(ref(Object) theObj)
 *  void AOACheckReference(handle(Object) theCell)
 *  void AOACheckObjectSpecial(ref(Object) theObj)
 *  #endif
 */

/* LOCAL FUNCTIONS */
static long AllocateBaseBlock(void);
static void markObjectAlive(ref (Object) obj);
static void AOANewBlock(long newBlockSize);

/* LOCAL VARIABLES */
static long totalFree = 0;
static long totalAOASize = 0;

/* tempAOArootsAlloc:
 *  Not enough room for the AOAroots table in ToSpace.
 *  Instead allocate offline and copy existing part of table over
 */
void tempAOArootsAlloc(void)
{
    ptr(long) oldPtr;        /* start of old table */
    ptr(long) oldlimitPtr;   /* points to end of old table */
    long size;
    
    if (tempAOAroots) {
        DEBUG_CODE(Claim(AOArootsPtr == tempAOAroots, "AOArootsPtr == tempAOAroots"));
        oldPtr = AOArootsPtr;
        oldlimitPtr = AOArootsLimit;
        size = 2 * ((long)oldlimitPtr - (long)oldPtr);
        
        MCHECK();
        
        if (!(tempAOAroots = (long *) MALLOC(size))) {
            char buf[512];
            sprintf(buf, "Could not allocate temporary AOAroots table.");
#ifdef MAC
            EnlargeMacHeap(buf);
#else
            Notify(buf);
#endif
            BetaExit(1);
        } 
        AOArootsLimit = (long *) ((long)tempAOAroots + size);
        AOArootsPtr = AOArootsLimit; /* end of new table */
        INFO_IOA(fprintf(output, 
                         "\nReallocated temporary AOAroots table: %dKb, ",
                         (int)size/1024
                         ));
        DEBUG_IOA(fprintf(output, " [0x%x] ", (int)tempAOAroots));
        
        MCHECK();
        /* Copy old table backwards */
        while(oldlimitPtr > oldPtr) *--AOArootsPtr = *--oldlimitPtr; 
        MCHECK();
        FREE(oldPtr);
    } else {
        oldPtr = AOArootsPtr;
        oldlimitPtr = ToSpaceLimit; 
        size = 2 * ((long)oldlimitPtr - (long)oldPtr);
        if (size < IOASize) {
            size = IOASize;
        }
        
        MCHECK();
        if (!(tempAOAroots = (long *) MALLOC(size))) {
            char buf[512];
            sprintf(buf, "Could not allocate temporary AOAroots table.");
#ifdef MAC
            EnlargeMacHeap(buf);
#else
            Notify(buf);
#endif
            BetaExit(1);
        } 
        AOArootsLimit = (long *) ((long)tempAOAroots + size);
        INFO_IOA(fprintf(output, 
                         "\nallocated temporary AOAroots table: %dKb, ",
                         (int)size/1024
                         ));
        DEBUG_IOA(fprintf(output, " [0x%x] ", (int)tempAOAroots));
        oldPtr = AOArootsPtr; /* start of old table */
        AOArootsPtr = AOArootsLimit; /* end of new table */
        
        MCHECK();
        /* Copy old table backwards */
        while(oldlimitPtr > oldPtr) *--AOArootsPtr = *--oldlimitPtr; 
        MCHECK();
    }
}

void tempAOArootsFree(void)
{
#ifdef RTDEBUG
    long roots = (long)tempAOAroots;
    Claim(tempAOAroots!=NULL, "tempAOArootsFree: tempAOAroots allocated");
#endif
    MCHECK();
    FREE(tempAOAroots);
    MCHECK();
    tempAOAroots = NULL;
    INFO_IOA(fprintf(output, "freed temporary AOAroots table\n"));
    DEBUG_IOA(fprintf(output, " [0x%x]", (int)roots));
}

/* AllocateBaseBlock:
 * Some of The functionality has been taken out of 'AOAallocate below
 * and put in a function by itself. This function is only called the
 * first time around where it allocates the first block in AOA. The
 * jump to this code is very rarely taken. In shuch cases it improves
 * both performance and readabillity to put such code in a function by
 * itself.
 */

static long AllocateBaseBlock(void)
{
    if( MallocExhausted || (AOABlockSize == 0) ) return 0;
    /* Check if the AOAtoIOAtable is allocated. If not then allocate it. */
    if( AOAtoIOAtable == 0 ) 
        if( AOAtoIOAalloc() == 0 ){
            MallocExhausted = TRUE;
            INFO_AOA( fprintf(output,
                              "#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
                              (int)AOAtoIOAtableSize));
            return 1;
        }
    /* Try to allocate a new AOA block. */
    if( (AOABaseBlock = newBlock(AOABlockSize)) ){
        INFO_AOA( fprintf(output, "#(AOA: new block allocated %dKb.)\n",
                          (int)AOABlockSize/Kb));
        AOATopBlock  = AOABaseBlock;
        AOABlocks++;
        totalFree += AOABlockSize;
        totalAOASize += AOABlockSize;
        
        /* Insert the new block in the freelist */
        AOAInsertFreeBlock((char *)AOATopBlock -> top, AOABlockSize);
        INFO_HEAP_USAGE(PrintHeapUsage("after new AOA block"));
    }else{
        MallocExhausted = TRUE;
        INFO_AOA( fprintf(output, "#(AOA: block allocation failed %dKb.)\n",
                          (int)AOABlockSize/Kb));
        return 1;
    }
    return 0;
}

/* AOAallocate allocate 'size' number of bytes in the Adult object area.
 * If the allocation succeeds the function returns a reference to the allocated
 * object, 0 otherwise.  */
struct Object *AOAallocate(long numbytes)
{
    Object *newObj;
    
    DEBUG_CODE( Claim(numbytes > 0, "AOAallocate: numbytes > 0") );
    
    if( AOABaseBlock == 0) {
        if (AllocateBaseBlock()) {
            INFO_AOA(fprintf(output,"Could not allocate AOABaseBlock\n"));
            return 0;
        }
        INFO_AOA(fprintf(output,"Allocated AOABaseBlock\n"));
    }
    
    /* Try to find a chunck of memory in the freelist */
    newObj = AOAAllocateFromFreeList(numbytes);
    if (newObj) {
        totalFree -= numbytes;
        newObj->GCAttr = DEADOBJECT;
        
        if (totalFree < AOAMinFree) {
            AOANeedCompaction = TRUE;
        }
        
        return newObj;
        
    } else {
        /* We add a new block and indicate that we want an AOAGC ASAP */
        long newBlockSize;
        
        newBlockSize = (AOABlockSize < numbytes) ? numbytes : AOABlockSize;

        INFO_AOA(fprintf(output,"Could not allocate %lu bytes, doing AOAGC\n",numbytes));
        AOANewBlock(newBlockSize);
        
        if ((newObj = AOAallocate(numbytes))) {
            AOANeedCompaction = TRUE;
            return newObj;
        }
    }
    return 0;
}

#ifdef NEWRUN
#define AOA_ALLOC_PARAMS long numbytes, long *SP
#else
#define AOA_ALLOC_PARAMS long numbytes
#endif 

#ifdef nti /*RUN*/ 
/* FIXME:  We cannot call DoGC, as it is declared in RUN.
 * But we do not really need to, as long as AOAGC is disabled.
 */
void DoGC()
{
    fprintf(output, "ERROR: Ignoring DoGC from AOA(c)alloc\n");
}
#endif

struct Object *AOAalloc(AOA_ALLOC_PARAMS)
{
    struct Object *theObj;

    MT_CODE(mutex_lock(&aoa_lock));

    DEBUG_CODE(NumAOAAlloc++);
    INFO_AOA(fprintf(output,"AOAalloc(numbytes=%d)",(int)numbytes));
    theObj = AOAallocate(numbytes);
    if (!theObj){
        /* AOAallocate failed. This means that AOANeedCompaction will be
         * true now. Force an IOAGc.
         */
        INFO_AOA(fprintf(output, "AOAalloc: forcing IOAGc and AOAGc\n"));
#ifdef MT
        fprintf(output,"FIXME:AOAalloc failed, has to GC here!!\n");
        /*    ReqObjectSize = numbytes/4;
              IOAGc(); */
#else
#ifdef NEWRUN
        DoGC(SP);
#else
        DoGC();
#endif
#endif /* MT */
        /* Try again */
        theObj = AOAallocate(numbytes);
    }
    if (!theObj){
        /* Arrgh. FIXME */
        fprintf(output, "AOAalloc: cannot allocate 0x%x bytes\n", (int)numbytes);
        BetaExit(1);
    }

    MT_CODE(mutex_unlock(&aoa_lock));

    return theObj;
}

struct Object *AOAcalloc(AOA_ALLOC_PARAMS)
{
    struct Object *theObj;
    long gca;
#ifdef NEWRUN
    theObj = AOAalloc(numbytes, SP);
#else
    theObj = AOAalloc(numbytes);
#endif
    /* No need to check theObj!=0 since this is done in AOAalloc */
    gca = theObj->GCAttr;
    memset(theObj, 0, numbytes);
    theObj->GCAttr = gca;
    return theObj;
}

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
  
    size = 4*ObjectSize( theObj); 
    Claim(ObjectSize(theObj) > 0, "#ToAOA: ObjectSize(theObj) > 0");
    Claim((size&7)==0, "#ToAOA: (size&7)==0 ");
  
#ifdef KEEP_STACKOBJ_IN_IOA
    DEBUG_CODE(
	       if (theObj -> Proto == StackObjectPTValue) {
		 fprintf(output,"CopyObjectToAOA: Trying to move stack object to AOA\n");
		 Illegal();
	       });
#endif /* NEWRUN */
      
    if( (newObj = AOAallocate( size)) == 0 ) return 0;
  
    theEnd = (ptr(long)) (((long) newObj) + size); 
  
    src = (ptr(long)) theObj; dst = (ptr(long)) newObj; 
    while( dst < theEnd) *dst++ = *src++; 
  
    if (!HandledInAOAHead) {
        /* Start new list */
        HandledInAOAHead = newObj;
        HandledInAOATail = newObj;

    } else {
        /* append new object to list */
        HandledInAOATail -> GCAttr = (long) newObj;
        HandledInAOATail = newObj;
    }
    newObj->GCAttr = LISTEND;
    
    /* Set one forward reference in theObj to newObj */
    theObj->GCAttr = (long) newObj;
  
    DEBUG_AOA( AOAcopied += size );
  
    DEBUG_AOA(if(isStackObject(theObj)) 
              fprintf(output, 
                      "CopyObjectToAOA: moved StackObject to 0x%x\n", (int)newObj));
  
    /* Return the new object in AOA */
    return newObj;
}

static void markObjectAlive(ref (Object) obj)
{
    obj -> GCAttr = LIVEOBJECT;
}

long sizeOfAOA(void)
{
    ref (Block) current;
    long numbytes = 0;
    
    current = AOABaseBlock;
    
    while(current) {
        numbytes += 4*(current -> limit - current -> top);
        current = current -> next;
    }

    return numbytes;
}

/*
 *  AOAGc: perform a mark/sweep garbagecollection on the AOA heap.
 *  Should be called after IOAGc when AOANeedCompaction == TRUE;
 */

void AOAGc()
{
    long *pointer;
    ptr(long) cellptr;
    ptr(Object) target;
    ptr(Object) root;
    ref(Block) currentBlock;

    NumAOAGc++;
    
    INFO_AOA(fprintf(output,"(AOA - %lu:",NumAOAGc));
    INFO_AOA(AOADisplayFreeList());
    
    /* Based on the AOARoots all objects reachable from those roots
     * are collected in a linked list. After that AOA is scanned and
     * objects not in the list are considered dead and inserted in the
     * free lists.
     */
    
    /* When collecting the list of live objects, only objects in AOA
     * are considered.
     */
    
    pointer = AOArootsPtr;
    
    root = NULL;

    /* Clear AOAtoIOAtable. This will be rebuild by extend- and
       initialCollectList. */
    AOAtoIOAClear();
    
    if (pointer < AOArootsLimit) {
        /* Make cellptr point to the cell that contains an AOAroot. */
        cellptr = (long*)(*pointer & ~1);
        
        /* Make target point to the actual object in AOA. */
        root = target = (ptr(Object))*cellptr;
        
        /* It is necessary to call a special collecter the first
         * time.
         */
        initialCollectList(target,
                           appendToListInAOA);
        
        pointer++;
        
        /* Afterwards we call extendCollectList. */
        while (pointer < AOArootsLimit) {
            cellptr = (long*)(*pointer & ~1);
            target = (ptr(Object))*cellptr;
            extendCollectList(target,
                              appendToListInAOA);
            pointer++;
        }
    }
    
    /* The object pointed to by the first entry in AOArootsPtr is now
     * the head of the linked list of all live objects in AOA.
     */
    
    /* All objects in the list are marked ALIVE */
    /* If root is actually a staticly inlined part object
       'getRealObject' will return the enclosing object.
    */
    if (root) {
      scanList(getRealObject(root), markObjectAlive);
    
    /* Scan AOA and insert dead objects in the freelist */
    
    /* Clear the free lists */
      AOACleanFreeList();

      /* All space is alive until proven dead */
      totalFree = 0;

      /* Scan each block in AOA. */
      currentBlock = AOABaseBlock;
    
      while (currentBlock) {
        /* Then each chunck in the block is examined */
        long freeInBlock;

        freeInBlock = AOAScanMemoryArea(currentBlock -> top, currentBlock -> limit);
        totalFree += freeInBlock;
        
        INFO_AOA(fprintf(output,"  Freed "));
        INFO_AOA(fprintf(output,"%lu",collectedMem));
        INFO_AOA(fprintf(output," bytes,"));
        INFO_AOA(fprintf(output,"  Free in block "));
        INFO_AOA(fprintf(output,"%lu",freeInBlock));
        INFO_AOA(fprintf(output," bytes\n"));
        
        currentBlock = currentBlock -> next;
      }
    }
    
    while ((totalFree/(totalAOASize/100) < AOAPercentage) ||
           (totalFree < AOAMinFree)) {
      AOANewBlock(AOABlockSize);
    }
    
    INFO_AOA(fprintf(output,"AOAGC finished, free space "));
    INFO_AOA(fprintf(output,"%lu",totalFree));
    INFO_AOA(fprintf(output," bytes)\n"));
    
    /* Now all blocks have been scanned and all dead objects inserted
       in the freelists */

    AOANeedCompaction = FALSE;
    
    return;
}

static void AOANewBlock(long newBlockSize) 
{
    ref(Block) newblock;
    if ((newblock = newBlock(newBlockSize))) {
        totalFree += newBlockSize;
        totalAOASize += newBlockSize;
        
        AOABlocks++;
        AOATopBlock -> next = newblock;
        AOATopBlock = newblock;
        /* Insert the new block in the freelist */
        AOAInsertFreeBlock((char *)AOATopBlock -> top, newBlockSize);
        INFO_AOA(fprintf(output,"Allocated new block of %lu bytes\n",newBlockSize));
        
    } else {
        DEBUG_CODE(fprintf(output,"MallocExhausted\n"));
        INFO_AOA(fprintf(output,"MallocExhausted\n"));
        MallocExhausted = TRUE;
    }
}
    
#ifdef RTDEBUG
static void CheckAOACell(struct Object **theCell,struct Object *theObj)
{
  DEBUG_CODE(if (!CheckHeap) Ck(theObj));
  AOACheckReference(theCell);
}

ref(Object) lastAOAObj=0;

static FILE *dump_aoa_file=NULL;
#define AOA_DUMP(code) { code; }
#define AOA_DUMP_TEXT(text) \
if (dump_aoa){ fprintf(dump_aoa_file, "%s", text); }
#define AOA_DUMP_LONG(num) \
if (dump_aoa){ fprintf(dump_aoa_file, "0x%08x", (int)num); }
#define AOA_DUMP_INT(num) \
if (dump_aoa){ fprintf(dump_aoa_file, "%d", (int)num); }

/* AOACheck: Consistency check on entire AOA area */
void AOACheck()
{
    ref(Block)  theBlock  = AOABaseBlock;
    ref(Object) theObj;
    long        theObjectSize;

    if (dump_aoa) {
        char name[16];
        if (dump_aoa_file) {
            fclose(dump_aoa_file);
        }
        sprintf(name,"aoa_dump%04d", (int)NumAOAGc);
        dump_aoa_file = fopen(name, "w+");
        if (!dump_aoa_file) {
            fprintf(output, "failed to open aoa_dump_file\n");
            dump_aoa=0;
        } else {
            AOA_DUMP_TEXT("========AOA-");
            AOA_DUMP_LONG(NumAOAGc);
            AOA_DUMP_TEXT("========\n");
            AOA_DUMP_TEXT(" Object   : Proto    : size     :GCAttr: Name :\n");
        }
    }  

    lastAOAObj=0;
    while( theBlock ){
        theObj = (ref(Object)) BlockStart(theBlock);
        while( (long *) theObj < theBlock->top ){
            theObjectSize = 4*ObjectSize(theObj);
	    Claim((theObjectSize&7)==0, "#AOACheck: (TheObjectSize&7)==0 ");
            Claim(ObjectSize(theObj) > 0, "#AOACheck: ObjectSize(theObj) > 0");
            AOACheckObject( theObj);
            lastAOAObj=theObj;
            theObj = (ref(Object)) Offset( theObj, theObjectSize);
        }
        theBlock = theBlock->next;
    }
    dump_aoa = 0;
} 

/* AOACheckObject: Consistency check on AOA object */
void AOACheckObject( theObj)
ref(Object) theObj;
{ ref(ProtoType) theProto;
  
 theProto = theObj->Proto;

#ifdef MT
 /* The way part objects are allocated in V-entries
  * may leave part objects with uninitialized prototypes.
  */
 if (!theProto) return;
#endif

 Claim( !inBetaHeap((ref(Object))theProto),
	"#AOACheckObject: !inBetaHeap(theProto)");

 AOA_DUMP_TEXT(":");
 AOA_DUMP_LONG(theObj);
 AOA_DUMP_TEXT(":");
 AOA_DUMP_LONG(theProto);
 AOA_DUMP_TEXT(":");
 AOA_DUMP_LONG(ObjectSize(theObj));
 AOA_DUMP_TEXT(":");
 AOA_DUMP_INT(theObj->GCAttr);
 AOA_DUMP_TEXT(":");
 AOA_DUMP_TEXT(ProtoTypeName(theProto));
 if (theProto==ComponentPTValue){
     AOA_DUMP_TEXT(" ");
     AOA_DUMP_TEXT(ProtoTypeName((ComponentItem(theObj))->Proto));
 }
 AOA_DUMP_TEXT(":\n");
  
 if( isSpecialProtoType(theProto) ){  
     switch( SwitchProto(theProto) ){
       case SwitchProto(ByteRepPTValue):
       case SwitchProto(ShortRepPTValue):
       case SwitchProto(DoubleRepPTValue):
       case SwitchProto(LongRepPTValue): return; /* No references in the type of object, so do nothing*/
      
       case SwitchProto(DynItemRepPTValue):
       case SwitchProto(DynCompRepPTValue):
           /* Check iOrigin */
           AOACheckReference( (handle(Object))(&REP->iOrigin) );
           /* Check rest of repetition */
           switch(SwitchProto(theProto)){
             case SwitchProto(DynItemRepPTValue):
             case SwitchProto(DynCompRepPTValue):
             { long *pointer;
             register long size, index;
	  
             /* Scan the repetition and follow all entries */
             { 
                 size = REP->HighBorder;
                 pointer = (long *)&REP->Body[0];
	    
                 for (index=0; index<size; index++) {
                     AOACheckReference( (handle(Object))(pointer) );
                     pointer++;
                 }
             }
             }
             break;
           }
           return;

       case SwitchProto(RefRepPTValue):
           /* Scan the repetition and follow all entries */
       { long * pointer;
       register long size, index;
	
       size = toRefRep(theObj)->HighBorder;
       pointer =  (long *) &toRefRep(theObj)->Body[0];
	
       for(index=0; index<size; index++) {
           AOACheckReference( (handle(Object))(pointer) );
           pointer++;
       }
       }
      
       return;
      
       case SwitchProto(ComponentPTValue):
       { ref(Component) theComponent;
	
       theComponent = Coerce( theObj, Component);
       if (theComponent->StackObj == (ref(StackObject))-1) {
           /* printf("\nAOACheckObject: theComponent->StackObj=-1, skipped!\n"); */
       } else {
           AOACheckReference( (handle(Object))(&theComponent->StackObj));
       }
       AOACheckReference( (handle(Object))(&theComponent->CallerComp));
       AOACheckReference( (handle(Object))(&theComponent->CallerObj));
       AOACheckObject( (ref(Object))(ComponentItem( theComponent)));
       }
       return;   
       case SwitchProto(StackObjectPTValue):
#ifdef KEEP_STACKOBJ_IN_IOA
           Claim( FALSE, "AOACheckObject: theObj should not be StackObject.");
#else
           ProcessStackObj((struct StackObject *)theObj, CheckAOACell);
#endif /* KEEP_STACKOBJ_IN_IOA */
           return; 
       case SwitchProto(StructurePTValue):
           AOACheckReference( &(toStructure(theObj))->iOrigin );
           return;
       case SwitchProto(DopartObjectPTValue):
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
         AOACheckReference( (handle(Object))theCell );
     }
 }
}

/* AOACheckReference: Consistency check on AOA reference */
void AOACheckReference( theCell)
handle(Object) theCell;
{
    long i; long * pointer = BlockStart( AOAtoIOAtable);
    long found = FALSE;

#ifdef RTLAZY
    if (isLazyRef(*theCell)){
        int i;
        int found=0;
        for (i=0; i<negAOAsize; i++){
            if ((*(long*)negAOArefs[i])==(long)*theCell){
                found=1; break;
            }
        }
        if (!found){
            fprintf(output, 
                    "Dangler in AOA, but NOT in negAOArefs table: 0x%x: %d\n", 
                    (int)theCell, 
                    (int)*theCell);
            Illegal();
        }
        return;
    }
#endif
    if ( *theCell ){
        Claim(inAOA(*theCell) || inIOA(*theCell),
              "AOACheckReference: *theCell in IOA, AOA");
        if( inIOA( *theCell) ){
            IOACheckObject( *theCell);
            for(i=0; (i < AOAtoIOAtableSize) && (!found); i++){
                if( *pointer ) found = (*pointer == (long) theCell);
                pointer++;
            }
            if (!found){
                char buf[512];
                sprintf(buf, 
                        "AOACheckReference: *theCell [*(0x%x)] in IOA but not in AOAtoIOAtable",
                        (int)theCell);
                Claim( found, buf);
            }
        }
    }
}

/* AOACheckObjectSpecial: Weak consistency check on AOA object */
void AOACheckObjectSpecial( theObj)
ref(Object) theObj;
{ ref(ProtoType) theProto;
  
 theProto = theObj->Proto;

#ifdef MT
 /* The way part objects are allocated in V-entries
  * may leave part objects with uninitialized prototypes.
  */
 if (!theProto) return;
#endif
  
 Claim( !inBetaHeap((ref(Object))theProto),
	"#AOACheckObjectSpecial: !inBetaHeap(theProto)");
  
 if( isSpecialProtoType(theProto) ){  
     switch(SwitchProto(theProto)){
       case SwitchProto(ByteRepPTValue):
       case SwitchProto(ShortRepPTValue):
       case SwitchProto(DoubleRepPTValue):
       case SwitchProto(LongRepPTValue): return;
       case SwitchProto(DynItemRepPTValue): return;
       case SwitchProto(DynCompRepPTValue): return;
       case SwitchProto(RefRepPTValue): return;
       case SwitchProto(ComponentPTValue):
           AOACheckObjectSpecial( (ref(Object))(ComponentItem( theObj)));
           return;
       case SwitchProto(StackObjectPTValue):
#ifdef KEEP_STACKOBJ_IN_IOA
           Claim( FALSE, "AOACheckObjectSpecial: theObj must not be StackObject.");
#else
           fprintf(output, 
                   "AOACheckObjectSpecial: no check of stackobject 0x%x\n", (int)theObj);
#endif
           return;
       case SwitchProto(StructurePTValue):
           return;
       case SwitchProto(DopartObjectPTValue):
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

