/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-98 Mjolner Informatics Aps.
 * aoatoioa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn,
 * Jacob Seligmann, S|ren Brandt and Morten Grouleff.
 */
#include "beta.h"

/* Enable/Disable statistics: */
#if 0
#define DEBUG_AOAtoIOA_STAT(code) { code; }
#else
#define DEBUG_AOAtoIOA_STAT(code) 
#endif

/* Max number of linear probes in AOAtoIOAInsert */
#define MAX_PROBES 128

#ifdef USEMMAP
/* When set other than zero, the two tables are preallocated to this size
 * and never extended. The program will terminate if this limit is reached.
 * Beware: The amount of virtual memory reserved is 8 times the number
 * of entries, so do not set this too high...
 */
#define MAXAOATOIOAPRIM	     21 /* refers 12977971 entries. */
#if MAXAOATOIOAPRIM
static long maxprim = 0;
#endif
#endif /* USEMMAP */

#ifdef PERSIST
#include "PException.h"
#endif /* PERSIST */

/* Some primes to use as the size of the AOAtoIOAtable.
 * primes(n+1) ~~ primes(n) * 1.5
 */
static long prim_index = 1;
static long primes[] = 
       { 101, 151, 227, 347, 521, 773, 1163, 1741,
	 2617, 3919, 5879,  8821, 13241, 19867, 29803, 44711, 67079,
	 99991, 149993, 224993, 337511, 506269, 759431, 1139191, 
	 1708943, 2563441, 3845279, 5767999, 8651977, 
	 12977971, 19466939, 29200411, 43800607, 65700907,
	 98551357, 150000001, 225000011, 333000001, 500000003,
	 0 
       };

/* The currently unused semispace: */
static Block *alternateAOAtoIOAtable = NULL;
#if !MAXAOATOIOAPRIM
static long alternateAOAtoIOAtableSize = 0;
#endif

#if MAXAOATOIOAPRIM
static void AllocateFromReserve(void)
{
  if (maxprim < prim_index) {
    long numbytes = primes[prim_index] - primes[maxprim];
    if (maxprim == 0) {
      numbytes = primes[prim_index];
    }
    numbytes *= 4;
    extendBlock(alternateAOAtoIOAtable, numbytes);
    alternateAOAtoIOAtable->top = alternateAOAtoIOAtable->limit;
    extendBlock(AOAtoIOAtable, numbytes);
    AOAtoIOAtable->top = AOAtoIOAtable->limit;
    maxprim = prim_index;
  }
}
#endif

/* Allocates the initial AOAtoIOAtable. */
long AOAtoIOAalloc()
{
    AOAtoIOAtableSize = primes[prim_index];

#if MAXAOATOIOAPRIM
    {
      long numbytes = primes[MAXAOATOIOAPRIM] * sizeof(long*);
      numbytes = (numbytes + sizeof(Block) + 8191) & ~8191;
      INFO_AOA(fprintf(output, "\n\n#(AOA: AOAtoIOAtable reserving 2*%d longs.)\n\n",
		       (int)primes[MAXAOATOIOAPRIM]));
      alternateAOAtoIOAtable = reserveBlock(numbytes);
      if (alternateAOAtoIOAtable) {
	if (InsertGuardPage()) {
	  AOAtoIOAtable = reserveBlock(numbytes);
	  if (AOAtoIOAtable) {
	    AllocateFromReserve();
	  }
	}
      }
    }
#else
    if (AOAtoIOAtable) {
      freeBlock(AOAtoIOAtable);
    }
    AOAtoIOAtable = newBlock(AOAtoIOAtableSize * sizeof(long*));
#endif

    if (AOAtoIOAtable) {
      AOAtoIOAtable->top = AOAtoIOAtable->limit;
      AOAtoIOAClear();
      INFO_AOA(fprintf(output, "#(AOA: AOAtoIOAtable allocated %d longs.)\n",
		       (int)AOAtoIOAtableSize));
      return 1;
    }

    return 0;
}



/* Allocate a larger AOAtoIOAtable based on the next entry in primes.
 * Or, if it is possible, just wash out the entries pointing to AOA.
 */
static void AOAtoIOAReAlloc(void)
{
  /* Save the old table. */
  Block * oldBlock      = AOAtoIOAtable;
  long    oldBlockSize  = AOAtoIOAtableSize;
  long    numUsed;
  long    i;
  long    largerList = 0;
  long    starttime = 0;

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

  if (numUsed > AOAtoIOAtableSize/4 || largerList) {
    prim_index++;
  } else if (numUsed < AOAtoIOAtableSize/10 && !largerList) {
    if (prim_index>0)
      prim_index--;
  }


  /* If the new buffer gets full, try a larger one. */
  largerList = 1;

  /* Exit if we can't find a new entry in prims. */
  if (primes[prim_index] == 0
#if MAXAOATOIOAPRIM
      || prim_index > MAXAOATOIOAPRIM
#endif
      ) {
#ifdef NEWRUN
    BetaError(AOAtoIOAfullErr, CurrentObject, StackEnd, 0);
#else
    BetaError(AOAtoIOAfullErr, 0);
#endif
  }
  
  /* Allocate a new possibly larger block to hold AOAtoIOA references. */
  AOAtoIOAtableSize = primes[prim_index];
#if MAXAOATOIOAPRIM
  INFO_AOA(fprintf(output, "#(AOA: AOAtoIOAtable extending to %d longs.)\n",
		   (int)AOAtoIOAtableSize));
  if (AOAtoIOAtable) {
    alternateAOAtoIOAtable = oldBlock;
    AllocateFromReserve();
    alternateAOAtoIOAtable = NULL;
  } else {
    AOAtoIOAtable = alternateAOAtoIOAtable;
    alternateAOAtoIOAtable = oldBlock;
    AllocateFromReserve();
    alternateAOAtoIOAtable = NULL;
  }
  AOAtoIOAClear();
#else
  INFO_AOA(fprintf(output, "#(AOA: AOAtoIOAtable allocating to %d longs.)\n",
		   (int)AOAtoIOAtableSize));
  if (AOAtoIOAtableSize == alternateAOAtoIOAtableSize) {
    AOAtoIOAtable = alternateAOAtoIOAtable;
    alternateAOAtoIOAtable = NULL;
    alternateAOAtoIOAtableSize = 0;
    AOAtoIOAClear();
  } else {
    if (alternateAOAtoIOAtableSize) {
      freeBlock(alternateAOAtoIOAtable);
      alternateAOAtoIOAtable = NULL;
      alternateAOAtoIOAtableSize = 0;
    }
    if (!AOAtoIOAalloc()) {
      /* If the allocation of the new AOAtoIOAtable failed please
	 terminate the program execution. */
      NEWRUN_CODE(BetaError(AOAtoIOAallocErr, CurrentObject, StackEnd, 0));
      NOTNEWRUN_CODE(BetaError(AOAtoIOAallocErr, 0));
    }
  }
#endif
  
  /* Move all entries from the old table into to new. */
  { 
    long *pointer = BlockStart(oldBlock);
    long *end = pointer + oldBlockSize;
    for ( ; pointer < end; pointer++) {
      if (*pointer) {
	if (inIOA(**(long**)pointer) || inToSpace(**(long**)pointer)) {
	  if (AOAtoIOAInsertImpl((Object **)(*pointer))) {
	    INFO_AOA(fprintf(output, "AOAtoIOAReAlloc: retrying allocation\n"));
	    DEBUG_CODE(fprintf(output, "AOAtoIOAReAlloc: retrying allocation\n"));
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

    fprintf(output, "(AOAtoIOAReAlloctime=%dms)\n", 
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
  
#if MAXAOATOIOAPRIM
    /* Save as semispace for next clean */
    alternateAOAtoIOAtable = oldBlock;
#else
  if (AOAtoIOAtableSize == oldBlockSize) {
    /* Save as semispace for next clean */
    alternateAOAtoIOAtable = oldBlock;
    alternateAOAtoIOAtableSize = oldBlockSize;
  } else {
    /* Deallocate the old table. */
    freeBlock(oldBlock);    
  }
#endif
}

/* AOAtoIOAfree:
 */
void AOAtoIOAfree(void)
{
  /* Free everything allocated by AOAtoIOA */
  if (alternateAOAtoIOAtable) freeBlock(alternateAOAtoIOAtable);
  if (AOAtoIOAtable) freeBlock(AOAtoIOAtable);
  return;
}


void AOAtoIOACleanup(void)
{
  INFO_AOA(fprintf(output, "AOAtoIOACleanup starting\n"));

  AOAtoIOAReAlloc();
}


#ifdef RTDEBUG
void reportAsgRef(Object **theCell)
{
  if (!inIOA(theCell)){
    fprintf(output, "\n*** AsgRef: 0x%x: 0x%x", (int)theCell, (int)*theCell);
  }
}
#endif

int AOAtoIOAInsertImpl(Object **theCell)
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
      ILLEGAL; /* useful to break in */
    });

#ifdef RTDEBUG    
      if (*(long*)theCell & 7) {
	fprintf(output, "\n*theCell is not 8-aligned. Proto=0x%08X\n",
		(int)(GETPROTO(*(Object**)theCell)));
	ILLEGAL; /* useful to break in */
      }
#endif

    table = (unsigned long *)BlockStart( AOAtoIOAtable);
    /* First Hash function. */
    index = ((unsigned long) theCell) % AOAtoIOAtableSize;
    if (table[index] == 0){ 
      table[index] = (unsigned long) theCell;
      DEBUG_AOAtoIOA_STAT(fprintf(output, "\n(AOAtoIOAInsertstat=0)"));
      return 0;
    }
    if (table[index] == (unsigned long) theCell) {
      DEBUG_AOAtoIOA_STAT(fprintf(output, "\n(AOAtoIOAInsertstat=1)"));
      return 0;
    }
    
#if 0  /* Not exactly friendly towards the cache... */
    /* Second Hash function. */
    index = (((unsigned long) theCell)<<4) % AOAtoIOAtableSize;
    if (table[index] == 0){ 
      table[index] = (unsigned long) theCell; 
      DEBUG_AOAtoIOA_STAT(fprintf(output, "\n(AOAtoIOAInsertstat=2)"));
      return 0;
    }
    if (table[index] == (unsigned long) theCell) {
      DEBUG_AOAtoIOA_STAT(fprintf(output, "\n(AOAtoIOAInsertstat=3)"));
      return 0;
    }
#endif
    
    DEBUG_AOAtoIOA_STAT(fprintf(output, "\nAOAtoIOAInsert collision"));
    /* linear search at most MAX_PROBES forward */
    count = MAX_PROBES;
    index = ((unsigned long)theCell + 1) % AOAtoIOAtableSize;
    DEBUG_CODE(conflictcount = 4);
    do {
      DEBUG_AOAtoIOA_STAT(fprintf(output, "[%d]", MAX_PROBES-(int)count));
      Claim(((0<=index) && (index<(unsigned long)AOAtoIOAtableSize)), "Index must be inside range");
      if (table[index]==0){
	/* Found free */
	table[index] = (unsigned long)theCell; 
	DEBUG_AOAtoIOA_STAT(fprintf(output, "\n(AOAtoIOAInsertstat=%d)",
			       (int)conflictcount));
	return 0;
      }
      if (table[index]==(unsigned long)theCell){
	/* Already there */
	DEBUG_AOAtoIOA_STAT(fprintf(output, "\n(AOAtoIOAInsertstat=%d)",
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

void AOAtoIOAInsert(Object **theCell)
{
#ifdef RTINFO
  NumAOAtoIOAInsert++;
#endif
  while (AOAtoIOAInsertImpl(theCell)) {
    DEBUG_AOAtoIOA(fprintf(output, "AOAtoIOAInsert(0x%x) failed. Realloc'ing\n", (int)theCell); fflush(output));
    /* Insert failed. Clean up or allocate more room and retry */
    AOAtoIOAReAlloc();
    DEBUG_AOAtoIOA(fprintf(output, "AOAtoIOAInsert(0x%x) retry\n", (int)theCell); fflush(output));
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
    ILLEGAL;
    BetaExit(1);
  }
}

void AOAtoIOACheck(void)
{ 
    long i; long * pointer = BlockStart( AOAtoIOAtable);
    
    /* fprintf(output, "#AOAtoIOACheck: AOAtoIOAtableSize: %d\n", (int)AOAtoIOAtableSize); */
    for(i=0; i<AOAtoIOAtableSize; i++){
      if (pointer[i]){
	  Claim( inAOA( pointer[i]),"AOAtoIOACheck: *pointer in AOA" );
#ifdef PERSIST
	  if (!inPIT((void *)*(long*)(pointer[i]))) {
#endif /* PERSIST */
	    DEBUG_CODE({
	      if ((((*(long*)(pointer[i])) & 7)!=0)){
		fprintf(output, 
			"AOAToIOACheck: *pointer[i] NOT 8 aligned"
			"pointer=0x%x, i=%d, &pointer[i]=0x%x\n",
			(int)pointer,
			(int)i,
			(int)&pointer[i]);
	      }
	    });
#ifdef PERSIST
	  }
#endif /* PERSIST */
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
