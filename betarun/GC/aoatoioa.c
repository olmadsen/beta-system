/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * aoatoioa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */
#include "beta.h"

/* Max number of linear probes in AOAtoIOAInsert */
#define MAX_PROBES 100

/* Some primes to use as the size of the AOAtoIOAtable. */
/* primes(n+1) ~~ primes(n) * 1.5                          */
GLOBAL(static long primes[]) = 
       { 5879,  8821, 13241, 19867, 29803, 44711, 67079, 99991,
	 149993, 224993, 337511, 506269, 759431, 1139191, 
	 1708943, 2563441, 3845279, 5767999, 8651977, 0 };
GLOBAL(static long prim_index) = 0;

#ifdef MT
static void AOAtoIOAInsert(handle( Object) theCell);
#endif

/* Allocates the initial AOAtoIOAtable. */
long AOAtoIOAalloc()
{
    AOAtoIOAtableSize = primes[0];
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
   * AOAtoIOAReAlloc to be called in which case entries will be LOST!!!
   */

  /* Save the old table. */
  ref(Block) oldBlock      = AOAtoIOAtable;
  long        oldBlockSize  = AOAtoIOAtableSize;
  
  /* Exit if we can't find a new entry in prims. */
  if (primes[++prim_index] == 0) 
#ifdef NEWRUN
    BetaError(AOAtoIOAfullErr, CurrentObject, StackEnd, 0);
#else
    BetaError(AOAtoIOAfullErr, 0);
#endif
  
  /* Allocate a new and larger block to hold AOAtoIOA references. */
  AOAtoIOAtableSize = primes[prim_index];
  if ((AOAtoIOAtable = newBlock(AOAtoIOAtableSize * sizeof(long)))){
    AOAtoIOAtable->top = AOAtoIOAtable->limit;
    AOAtoIOAClear();
    INFO_AOA( fprintf(output, "#(AOAtoIOAtable resized to %d entries",
		      (int)AOAtoIOAtableSize));
  } else {
    /* If the allocation of the new AOAtoIOAtable failed please
       terminate the program execution. */
#ifdef NEWRUN
    BetaError(AOAtoIOAallocErr, CurrentObject, StackEnd, 0);
#else /* NEWRUN */
    BetaError(AOAtoIOAallocErr, 0);
#endif /* NEWRUN */
  }
  
  /* Move all entries from the old table into to new. */
  { 
    long i;
    ptr(long) pointer = BlockStart( oldBlock);
    for(i=0; i < oldBlockSize; i++){
      if (*pointer) 
	if (inIOA(**(long**)pointer) || inToSpace(**(long**)pointer))
	  AOAtoIOAInsert( (handle(Object))(*pointer));
      pointer++;
    }
  }
  
  INFO_AOA(
	   {
	     long i = 0;
	     long used = 0;
	     long *pointer = BlockStart(oldBlock);
	     while (i++<oldBlockSize)
	       if(*(pointer++)) 
		 used++;
	     fprintf(output, ", %ld entries (=%ld%%) used before", 
		     used,100*used/oldBlockSize);
	     
	     i = 0;
	     used = 0;
	     pointer = BlockStart(AOAtoIOAtable);
	     while (i++<AOAtoIOAtableSize)
	       if(*(pointer++)) 
		 used++;
	     fprintf(output, ", %ld entries (=%ld%%) used now.)\n", 
		     used, 100*used/AOAtoIOAtableSize);
	   }
	   );

  /* Deallocate the old table. */
  freeBlock( oldBlock);    
}

#ifdef RTDEBUG
void reportAsgRef(handle( Object) theCell)
{
  if (!inIOA(theCell)){
    fprintf(output, "\n*** AsgRef: 0x%x: 0x%x", (int)theCell, (int)*theCell);
  }
}
#endif

#ifdef MT
static 
#endif
void AOAtoIOAInsert(handle( Object) theCell)
{
    unsigned long *table;
    unsigned long index, count;

    DEBUG_CODE(if (!inAOA( theCell)) {
      fprintf(output, "AOAtoIOAInsert: 0x%x not in AOA!\n", (int)theCell);
      Illegal(); /* useful to break in */
    });

#ifdef RTLAZY
    if ( isNegativeRef(*theCell)) {
      /* This could happen if called from extobjinterface.assignRef. */
      negAOArefsINSERT ((long) theCell);
      return;
    }
#endif

    DEBUG_AOA( Claim( inAOA( theCell),"AOAtoIOAInsert: theCell in AOA"));
    
#if 0
    DEBUG_CODE(fprintf(output, "\n*** AOAtoIOAInsert(0x%x)\n", (int)theCell));
#endif

    table = (unsigned long *)BlockStart( AOAtoIOAtable);
    /* First Hash function. */
    index = ((unsigned long) theCell) % AOAtoIOAtableSize;
    if (table[index] == 0){ 
      table[index] = (unsigned long) theCell;
      goto exit;
    }
    if (table[index] == (unsigned long) theCell) {
      goto exit;
    }
    
    /* Second Hash function. */
    index = (((unsigned long) theCell)<<4) % AOAtoIOAtableSize;
    if (table[index] == 0){ 
      table[index] = (unsigned long) theCell; 
      goto exit; 
    }
    if (table[index] == (unsigned long) theCell) {
      goto exit;
    }
    
    DEBUG_AOA(fprintf(output, "\nAOAtoIOAInsert collision"));
    /* linear search at most MAX_PROBES forward */
    count = MAX_PROBES;
    index = ((unsigned long) theCell+1) % AOAtoIOAtableSize;
    do {
      DEBUG_AOA(fprintf(output, "[%d]", MAX_PROBES-(int)count));
      if (table[index]==0){
	/* Found free */
	table[index] = (unsigned long) theCell; 
	DEBUG_AOA(fprintf(output, "\n"));
	goto exit;
      }
      if (table[index]==(unsigned long) theCell){
	/* Already there */
	DEBUG_AOA(fprintf(output, "\n"));
	goto exit;
      }
      index++;
      if (index==(unsigned long)AOAtoIOAtableSize) index=0
	/* cheaper than modulus */;
    } while(--count);

    /* Both functions failed */
    AOAtoIOAReAlloc();

    /* Try again */
    AOAtoIOAInsert( theCell);

exit:
    return;
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
    long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    for(i=0;i<AOAtoIOAtableSize;i++) *pointer++ = 0;
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
    fflush(output);
    Illegal();
    BetaExit(1);
  }
}

void AOAtoIOACheck(void)
{ 
    long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    
    /* fprintf(output, "#AOAtoIOACheck: AOAtoIOAtableSize: %d\n", AOAtoIOAtableSize); */ 
    for(i=0; i<AOAtoIOAtableSize; i++){
	if (pointer[i]){
	    /* fprintf( output, "0x%x\n", pointer[i]); */
	    Claim( inAOA( pointer[i]),"AOAtoIOACheck: *pointer in AOA" );
	}
    }
}

void AOAtoIOAReport(void)
{ 
    long used = 0;
    if (AOAtoIOAtable){
	MACRO_ScanBlock( AOAtoIOAtable, if (*thisCell) used++ );
	fprintf(output, "#AOAtoIOATable size=%d filled=%d%%\n",
		(int)AOAtoIOAtableSize, (int)((100*used)/AOAtoIOAtableSize));
    }
}

#endif
