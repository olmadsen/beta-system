/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-98 Mjolner Informatics Aps.
 * aoatoioa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn,
 * Jacob Seligmann, S|ren Brandt and Morten Grouleff.
 */
#include "beta.h"

/* Max number of linear probes in AOAtoIOAInsert */
#define MAX_PROBES 60

/* Some primes to use as the size of the AOAtoIOAtable.
 * primes(n+1) ~~ primes(n) * 1.5
 */
GLOBAL(static long primes[]) = 
       { 2617, 3919, 5879,  8821, 13241, 19867, 29803, 44711, 67079,
	 99991, 149993, 224993, 337511, 506269, 759431, 1139191, 
	 1708943, 2563441, 3845279, 5767999, 8651977, 
	 12977971, 19466939, 29200411, 43800607, 65700907,
	 98551357, 150000001, 225000011, 333000001, 500000003,
	 0 
       };
GLOBAL(static long prim_index) = 0;

/* Local function prototypes: */
static int AOAtoIOAInsertImpl(Object **theCell);
#ifdef MT
static void AOAtoIOAInsert(handle( Object) theCell);
#endif


/* Allocates the initial AOAtoIOAtable. */
long AOAtoIOAalloc()
{
    AOAtoIOAtableSize = primes[prim_index];
    if (AOAtoIOAtable) {
      freeBlock(AOAtoIOAtable);
    }
    if ((AOAtoIOAtable = newBlock(AOAtoIOAtableSize * sizeof(long)))){
	AOAtoIOAtable->top = AOAtoIOAtable->limit;
	AOAtoIOAClear();
	INFO_AOA( fprintf(output, "#(AOA: AOAtoIOAtable allocated %d longs.)\n",
			  (int)AOAtoIOAtableSize));
	return 1;
    } else
      return 0;
}

/* Allocate a larger AOAtoIOAtable based on the next entry in primes. */
static void AOAtoIOAReAlloc(void)
{
  /* FIXME: POTENTIAL ERROR: The AOAtoIOAInsert call below may cause 
   *   AOAtoIOAReAlloc to be called in which case entries will be LOST!!!
   *
   * FIXED: Should be ok now, but the situation where the problem arises
   *   is difficult to trigger, so it has not been tested. --mg.
   */

  /* Save the old table. */
  Block * oldBlock      = AOAtoIOAtable;
  long    oldBlockSize  = AOAtoIOAtableSize;
  long    numUsed;
  long    i;
  long    largerList = 0;
  long    starttime;

  INFO_AOA(starttime = getmilisectimestamp());

  /* Count the number of used entries in the old table. */
  {
    long * pointer = BlockStart(oldBlock);
    long lastused = -1;
    numUsed = 0;

    for (i=0; i < oldBlockSize; i++) {
      if (*pointer
	  && (inIOA(**(long**)pointer) 
	      || inToSpace(**(long**)pointer))) {
	numUsed++;
	if (lastused==-1) {
	  lastused=i;
	}
	if (MAX_PROBES/2-1 <= i-lastused) {
	  largerList = 1;
	  break;
	}
      } else {
	lastused=-1;
      }
      pointer++;
    }
  }

  /* Make sure it is not freed yet */
  AOAtoIOAtable = NULL;

Retry:

  if (numUsed > AOAtoIOAtableSize/5 || largerList) {
    prim_index++;
  }

  /* Exit if we can't find a new entry in prims. */
  if (primes[prim_index] == 0) 
#ifdef NEWRUN
    BetaError(AOAtoIOAfullErr, CurrentObject, StackEnd, 0);
#else
    BetaError(AOAtoIOAfullErr, 0);
#endif
  
  /* Allocate a new and larger block to hold AOAtoIOA references. */
  AOAtoIOAtableSize = primes[prim_index];
  if (AOAtoIOAtable) {
    freeBlock(AOAtoIOAtable);
  }
  if ((AOAtoIOAtable = newBlock(AOAtoIOAtableSize * sizeof(long)))){
    AOAtoIOAtable->top = AOAtoIOAtable->limit;
    AOAtoIOAClear();
    INFO_AOA( fprintf(output, "#(AOAtoIOAtable resized from %d to %d entries",
		      (int)oldBlockSize, (int)AOAtoIOAtableSize));
  } else {
    /* If the allocation of the new AOAtoIOAtable failed please
       terminate the program execution. */
#ifdef NEWRUN
    BetaError(AOAtoIOAallocErr, CurrentObject, StackEnd, 0);
#else /* NEWRUN */
    BetaError(AOAtoIOAallocErr, 0);
#endif /* NEWRUN */
  }

  /* If the new buffer gets full, try a larger one. */
  largerList = 1;
  /* Move all entries from the old table into to new. */
  { 
    long *pointer = BlockStart(oldBlock);
    long *end = pointer + oldBlockSize;
    for ( ; pointer < end; pointer++) {
      if (*pointer) {
	if (inIOA(**(long**)pointer) || inToSpace(**(long**)pointer)) {
	  if (AOAtoIOAInsertImpl((Object **)(*pointer))) {
	    goto Retry;
	  }
	}
      }
    }
  }
  
  INFO_AOA({
    long *pointer = BlockStart(oldBlock);
    long *end = pointer + oldBlockSize;
    long used = 0;

    fprintf(output, "(AOAtoIOAReAlloc:time=%dms)\n", 
	    (int)(getmilisectimestamp() - starttime));

    for ( ; pointer<end; pointer++) {
      if(*pointer) 
	used++;
    }
    fprintf(output, ", %ld entries (=%ld%%) used before", 
	    used,100*used/oldBlockSize);
    
    pointer = BlockStart(AOAtoIOAtable);
    end = pointer + AOAtoIOAtableSize;
    used = 0;
    for ( ; pointer<end; pointer++) {
      if(*pointer) 
	used++;
    }
    fprintf(output, ", %ld entries (=%ld%%) used now.)\n", 
	    used, 100*used/AOAtoIOAtableSize);
  });
  
  /* Deallocate the old table. */
  freeBlock(oldBlock);    
}

#ifdef RTDEBUG
void reportAsgRef(Object **theCell)
{
  if (!inIOA(theCell)){
    fprintf(output, "\n*** AsgRef: 0x%x: 0x%x", (int)theCell, (int)*theCell);
  }
}
#endif

static int AOAtoIOAInsertImpl(Object **theCell)
{
    unsigned long *table;
    unsigned long index, count;
    DEBUG_CODE(long conflictcount);

    DEBUG_CODE(if (!inAOA(theCell)) {
      fprintf(output, 
	      "AOAtoIOAInsert: the cell 0x%x is not in AOA! ", 
	      (int)theCell);
      PrintWhichHeap((Object*)theCell);
      fprintf(output, "\n\n");
      Illegal(); /* useful to break in */
    });

#ifdef RTDEBUG    
    if (*(long*)theCell & 7) {
      fprintf(output, "\n*theCell is not 8-aligned. Proto=0x%08X\n",
	      (int)(GETPROTO(*(Object**)theCell)));
      Illegal(); /* useful to break in */
    }
#endif
            
#ifdef RTLAZY
    if ( isNegativeRef(*theCell)) {
        /* This could happen if called from extobjinterface.assignRef. */
        negAOArefsINSERT ((long) theCell);
        return 0;
    }
#endif

    Claim(inAOA(theCell),"AOAtoIOAInsert: theCell in AOA");
    
#if 0
    DEBUG_CODE(fprintf(output, "\n*** AOAtoIOAInsert(0x%x)\n", (int)theCell));
#endif

    table = (unsigned long *)BlockStart( AOAtoIOAtable);
    /* First Hash function. */
    index = ((unsigned long) theCell) % AOAtoIOAtableSize;
    if (table[index] == 0){ 
      table[index] = (unsigned long) theCell;
      DEBUG_AOAtoIOA(fprintf(output, "\n(AOAtoIOAInsertstat=0)"));
      return 0;
    }
    if (table[index] == (unsigned long) theCell) {
      DEBUG_AOAtoIOA(fprintf(output, "\n(AOAtoIOAInsertstat=1)"));
      return 0;
    }
    
    /* Second Hash function. */
    index = (((unsigned long) theCell)<<4) % AOAtoIOAtableSize;
    if (table[index] == 0){ 
      table[index] = (unsigned long) theCell; 
      DEBUG_AOAtoIOA(fprintf(output, "\n(AOAtoIOAInsertstat=2)"));
      return 0;
    }
    if (table[index] == (unsigned long) theCell) {
      DEBUG_AOAtoIOA(fprintf(output, "\n(AOAtoIOAInsertstat=3)"));
      return 0;
    }
    
    DEBUG_AOAtoIOA(fprintf(output, "\nAOAtoIOAInsert collision"));
    /* linear search at most MAX_PROBES forward */
    count = MAX_PROBES;
    index = ((unsigned long)theCell + 1) % AOAtoIOAtableSize;
    DEBUG_CODE(conflictcount = 4);
    do {
      DEBUG_AOAtoIOA(fprintf(output, "[%d]", MAX_PROBES-(int)count));
      if (table[index]==0){
	/* Found free */
	table[index] = (unsigned long)theCell; 
	DEBUG_AOAtoIOA(fprintf(output, "\n(AOAtoIOAInsertstat=%d)",
			       (int)conflictcount));
	return 0;
      }
      if (table[index]==(unsigned long)theCell){
	/* Already there */
	DEBUG_AOAtoIOA(fprintf(output, "\n(AOAtoIOAInsertstat=%d)",
			       (int)(conflictcount+1)));
	return 0;
      }
      DEBUG_CODE(conflictcount+=2);
      index++;
      /* much cheaper than modulus */;
      if (index==(unsigned long)AOAtoIOAtableSize) index=0;
    } while(--count);

    return 1;
}

#ifdef MT
static 
#endif
void AOAtoIOAInsert(Object **theCell)
{
  while (AOAtoIOAInsertImpl(theCell)) {
    /* Insert failed. Clean up or allocate more room and retry */
    AOAtoIOAReAlloc();
  }
}

#ifdef MT
void MT_AOAtoIOAInsert(handle( Object) theCell)
{
  mutex_lock(&aoatoioa_lock);
  AOAtoIOAInsert(theCell);
  mutex_unlock(&aoatoioa_lock);
}
#endif

void AOAtoIOAClear(void)
{ 
  memset(BlockStart(AOAtoIOAtable), 0, sizeof(long*)*AOAtoIOAtableSize);
}

#ifdef RTDEBUG

void CheckAOAtoIOAtableSize(long *theCell, long PC)
{
  if (AOAtoIOAtableSize==0){
    fprintf(output, "Error: AOAtoIOAtableSize is zero in ChkRA.\n");
    fprintf(output, 
	    "ChkRA failed at PC 0x%x for the cell 0x%x", 
	    (int)PC, 
	    (int)theCell);
    if (inToSpace(*theCell)) 
      fprintf(output, " (is in ToSpace).\n");
    else
      fprintf(output, " (is not in ToSpace).\n");
    Illegal();
    BetaExit(1);
  }
}

void AOAtoIOACheck(void)
{ 
    long i; long * pointer = BlockStart( AOAtoIOAtable);
    
    /* fprintf(output, "#AOAtoIOACheck: AOAtoIOAtableSize: %d\n", (int)AOAtoIOAtableSize); */
    for(i=0; i<AOAtoIOAtableSize; i++){
	if (pointer[i]){
	  /* fprintf( output, "0x%x\n", (int)pointer[i]); */
	  Claim( inAOA( pointer[i]),"AOAtoIOACheck: *pointer in AOA" );
	  Claim((((*(long*)(pointer[i])) & 7)==0), "AOAToIOACheck: **pointer 8 aligned");
	}
    }
}

void AOAtoIOAReport(void)
{ 
  long used = 0;
  if (AOAtoIOAtable){
    long *thisCell = (long *)((long)AOAtoIOAtable + sizeof(Block));
    long *e = AOAtoIOAtable->top;
    while (thisCell < e){
      if (*thisCell) used++;  thisCell++;
    }
    fprintf(output, "#AOAtoIOATable size=%d filled=%d%%\n",
	    (int)AOAtoIOAtableSize, (int)((100*used)/AOAtoIOAtableSize));
  }
}

#endif




/* MACRO_ScanBlock traverse the block, and for each element 
 * code is called, thisCell refers the element in question.
 */
#define MACRO_ScanBlock( block, code) \
{ long *thisCell=(long *)((long)block + sizeof(Block)), *XXe=block->top;\
  while( thisCell < XXe){  code;  thisCell++; }\
}
