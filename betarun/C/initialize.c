/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: initialize.c,v $, rel: %R%, date: $Date: 1992-07-23 15:09:52 $, SID: $Revision: 1.12 $
 * by Lars Bak.
 */
#include "beta.h"
extern CBFAAlloc();

#ifdef UNIX
#include <signal.h>
#endif

long AllocateHeap( base, top, limit, size)
  ptr(long) base; /* points out a cell which should refer the base. */
  ptr(long) top;
  ptr(long) limit;
  long size;      /* the size of the requested heap in bytes.       */
{
  if( (*base = (long) MALLOC( size)) != 0){
    *top   = *base;

    *limit = *base + size; 
    return *base;
  }else
    return 0;
}

Initialize()
{
  /* This hack is to cope with the sparc, where
     IOA and IOATop(off) is register vars */

  long *tmpIOA, *tmpIOATop;
#ifdef macintosh
  InitTheCursor();
#endif

  GetBetaEnv();

  INFO( fprintf( output, "#(Heap info: IOA=2*%dKb", IOASize/Kb) );
#ifdef AO_Area
  INFO( fprintf( output, ", AOABlock=%dKb", AOABlockSize/Kb) );
#endif
#ifdef LVR_Area
  INFO( fprintf( output, ", LVRABlock=%dKb", LVRABlockSize/Kb) );
#endif
  INFO( fprintf( output, ", CBFABlock=%dKb\n", CBFABlockSize/Kb) );

  /* Setup the Infant Object Area */
  if( !AllocateHeap( &tmpIOA,     &tmpIOATop,     &IOALimit, IOASize ) ){
    fprintf(output,"#Beta: Couldn't allocate IOA (%dKb)\n", IOASize/Kb);
    exit(1);
  }
  IOA = tmpIOA;
#ifdef sparc
  IOATopoff = tmpIOATop - IOA;
#else
  IOATop = tmpIOATop;
#endif
  if( !AllocateHeap( &ToSpace, &ToSpaceTop, &ToSpaceLimit, IOASize ) ){
    fprintf(output,"#Beta: Couldn't allocate ToSpace (%dKb)\n", IOASize/Kb);
    exit(1);
  }

  /* Allocate the Callback Function Area */
  CBFAAlloc();

  /* Allocate the Debug Object Table. */
  if( DOTSize > 0 )
    if( !AllocateHeap( &DOT,     &DOTTop,     &DOTLimit,  DOTSize ) ){
      fprintf(output,"#Beta: Couldn't allocate DOT (%d)\n", DOTSize);
      exit(1);
    }

#ifdef UNIX
   { /* Setup signal handles for the Beta system */
     extern SignalHandler();
     signal( SIGFPE,  SignalHandler);
     signal( SIGILL,  SignalHandler);
     signal( SIGBUS,  SignalHandler);
     signal( SIGSEGV, SignalHandler);
#ifdef apollo
     signal( SIGINT,  SignalHandler);
     signal( SIGQUIT, SignalHandler);
#endif
   }
#endif

  InfoS_Start();
}

