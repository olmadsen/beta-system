/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * aoatoioa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

/* Some primes to use as the size of the AOAtoIOAtable. */
/* primes(n+1) ~~ primes(n) * 1.5                          */
static long primes[] = 
{ 5879,  8821, 13241, 19867, 29803, 44711, 67079, 99991, 0 };

static long prim_index = 0;
/* Allocates the initial AOAtoIOAtable. */
long AOAtoIOAAlloc()
{
    AOAtoIOAtableSize = primes[0];
    if( AOAtoIOAtable = newBlock(AOAtoIOAtableSize * sizeof(long)) ){
	AOAtoIOAtable->top = AOAtoIOAtable->limit;
	AOAtoIOAClear();
	INFO_AOA( fprintf( output, "#(AOA: AOAtoIOAtable allocated %d longs.)\n",
			  AOAtoIOAtableSize));
	return 1;
    } else
      return 0;
}

/* Allocate a larger AOAtoIOAtable based on the next entry in primes. */
void AOAtoIOAReAlloc()
{
    /* Save the old table. */
    ref(Block) oldBlock      = AOAtoIOAtable;
    long        oldBlockSize  = AOAtoIOAtableSize;
    
    /* Exit if we can't find a new entry in prims. */
    if( primes[++prim_index] == 0 ) BetaError(AOAtoIOAfullErr, 0);
    
    /* Allocate a new and larger block to hold AOAtoIOA references. */
    AOAtoIOAtableSize = primes[prim_index];
    if( AOAtoIOAtable = newBlock(AOAtoIOAtableSize * sizeof(long)) ){
	AOAtoIOAtable->top = AOAtoIOAtable->limit;
	AOAtoIOAClear();
	INFO_AOA( fprintf( output, "#(AOAtoIOAtable resized %d longs.)\n",
			  AOAtoIOAtableSize));
    } else {
	/* If the allocation of the new AOAtoIOAtable failed please
	   terminate the program execution. */
	BetaError(AOAtoIOAallocErr, 0);
    }
    
    /* Move all entries from the old table into to new. */
    { 
      long i;
      ptr(long) pointer = BlockStart( oldBlock);
      for(i=0; i < oldBlockSize; i++){
	if( *pointer ) AOAtoIOAInsert( *pointer );
	pointer++;
      }
    }
    
    /* Deallocate the old table. */
    freeBlock( oldBlock);    
}

void AOAtoIOAInsert( theCell)
     handle( Object) theCell;
{
    ptr(long) table = BlockStart( AOAtoIOAtable);
    long      index, count;
    
    DEBUG_AOA( Claim( inAOA( theCell),"AOAtoIOAInsert: theCell in AOA"));
    
    /* First Hash function. */
    index = ((long) theCell) % AOAtoIOAtableSize;
    if( table[index] == 0){ table[index] = (long) theCell; return; }
    if( table[index] == (long) theCell ) return;
    
    /* Second Hash function. */
    index = (((long) theCell)<<4) % AOAtoIOAtableSize;
    if( table[index] == 0 ){ table[index] = (long) theCell; return; }
    if( table[index] == (long) theCell ) return;
    
    count = 0;
    while( count < 100 ){
	count++; index = (count + (long) theCell) % AOAtoIOAtableSize;
	if( table[index] == 0 ){ table[index] = (long) theCell; return; }
	if( table[index] == (long) theCell ) return;
    }
    AOAtoIOAReAlloc();
    AOAtoIOAInsert( theCell);
}

void AOAtoIOAClear()
{ 
    long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    for(i=0;i<AOAtoIOAtableSize;i++) *pointer++ = 0;
}

#ifdef RTDEBUG
void AOAtoIOACheck()
{ 
    long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    
    /* fprintf(output, "#AOAtoIOACheck: AOAtoIOAtableSize: %d\n", AOAtoIOAtableSize); */ 
    for(i=0; i<AOAtoIOAtableSize; i++){
	if( pointer[i] ){
	    /* fprintf( output, "0x%x\n", pointer[i]); */
	    Claim( inAOA( pointer[i]),"AOAtoIOACheck: *pointer in AOA" );
	}
    }
}

void AOAtoIOAReport()
{ 
    long used = 0;
    if( AOAtoIOAtable ){
	MACRO_ScanBlock( AOAtoIOAtable, if( *thisCell) used++ );
	fprintf( output, "#AOAtoIOATable size=%d filled=%d%%\n",
	       AOAtoIOAtableSize, (100*used)/AOAtoIOAtableSize);
    }
}

#endif
