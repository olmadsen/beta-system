/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: aoatoioa.c, rel: 1, date: 2/6/91, SID: 1.2
 * by Lars Bak
 */
#include "beta.h"

/* Some primes to determine the size of the AOAtoIOAtable. */
/* primes(n+1) ~~ primes(n) * 1.5                          */
static int primes[] = { 5879,  8821, 13241, 19867, 29803, 44711, 0 };

ref(Block) newBlock(); /* Extern routine in block.c */
void freeBlock();      /* Extern routine in block.c */

static int prim_index = 0;
/* Allocates the initial AOAtoIOAtable. */
int AOAtoIOAAlloc()
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
AOAtoIOAReAlloc()
{
  /* Save the old table. */
  ref(Block) oldBlock      = AOAtoIOAtable;
  int        oldBlockSize  = AOAtoIOAtableSize;

  /* Exit if we can't find a new entry in prims. */
  if( primes[++prim_index] == 0 ) BetaError(-33, 0);

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
    BetaError( -36, 0);
  }
    
  /* Move all entries from the old table into to new. */
  { int i, counter = 0;  ptr(long) pointer = BlockStart( oldBlock);
    for(i=0; i < oldBlockSize; i++){
      if( *pointer ) AOAtoIOAInsert( *pointer );
      pointer++;
    }
  }

  /* Deallocate the old table. */
  freeBlock( oldBlock);    
}

AOAtoIOAInsert( theCell)
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

AOAtoIOAClear()
{ int i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
  for(i=0;i<AOAtoIOAtableSize;i++) *pointer++ = 0;
}

#ifdef RTDEBUG
AOAtoIOACheck()
{ int i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
  for(i=0;i<AOAtoIOAtableSize;i++){
    if( *pointer )
      Claim( inAOA( *pointer),"AOAtoIOACheck: *pointer in AOA" );
    pointer++;
  }
}

AOAtoIOAReport()
{ int used = 0;
  if( AOAtoIOAtable ){
    MACRO_ScanBlock( AOAtoIOAtable, if( *thisCell) used++ );
    printf( output, "#AOAtoIOATable size=%d filled=%d%%\n",
	   AOAtoIOAtableSize, (100*used)/AOAtoIOAtableSize);
  }
}

#endif
