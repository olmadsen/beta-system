/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: aoatoioa.c,v $, rel: %R%, date: $Date: 1991-02-06 08:21:08 $, SID: $Revision: 1.2 $
 * by Lars Bak
 */
#include "beta.h"

AOAtoIOAInsert( theCell)
  handle( Object) theCell;
{
  ptr(long) table = BlockStart( AOAtoIOAtable);
  long      index, count;

  DEBUG_AOA( Claim( inAOA( theCell),"AOAtoIOAInsert theCell outside AOA"));

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
  BetaError(-33,0);
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
      Claim( inAOA( *pointer),"AOAtoIOACheck: *pointer outsize AOA" );
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
