/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * initialize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */
#include "beta.h"
extern CBFAAlloc();

#ifdef UNIX
#include <signal.h>
#endif

#ifdef macintosh
#include <SegLoad.h>
extern void _DataInit();
#endif

#ifdef DEMO
#define DEMOSTRING "\n\
                      **********************************\n\
                      Mjolner BETA System - DEMO Version\n\
                      **********************************\n\
This software is provided \"as is\", without warranties of any kind, and with no\n\
provisions for support or future enhancements. Neither Mjolner Informatics or \n\
any of its employees has liabilities in connection with the use of the software.\n\
\n\
This DEMO version is restricted to be used by one person, and only for non-\n\
commercial research or investigation purposes. It is not legal to distribute the\n\
software and associated documentation, or any portion or derivatives thereof, to\n\
anybody else.\n\
\n\
Using the Mjolner BETA System for commercial purposes is only legal after having\n\
purchased the commercially available Mjolner BETA System.\n\
\n\
                      **********************************\n\
\n"
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
  UnloadSeg((Ptr)_DataInit); /* Unload %A5Init% segment */
#endif

  GetBetaEnv();

#ifdef DEMO
  fprintf(stdout, DEMOSTRING);
#endif

  INFO( fprintf( output, "#(Heap info: IOA=2*%dKb", IOASize/Kb) );
#ifdef AO_Area
  INFO( fprintf( output, ", AOABlock=%dKb", AOABlockSize/Kb) );
#endif
#ifdef LVR_Area
  INFO( fprintf( output, ", LVRABlock=%dKb", LVRABlockSize/Kb) );
#endif
  INFO( fprintf( output, ", CBFABlock=%dKb\n", CBFABlockSize/Kb) );

  /* Setup the Infant Object Area */
  if ( IOASize <= 0 ) {
      fprintf(output,"#Beta: Too small IOA size specified: %dKb\n", IOASize/Kb);
      fprintf(output,"#Beta: Check your BETART environment variable\n");
      exit(1);
  }
  if( !AllocateHeap( &tmpIOA,     &tmpIOATop,     &IOALimit, IOASize ) ){
    fprintf(output,"#Beta: Couldn't allocate IOA (%dKb)\n", IOASize/Kb);
    exit(1);
  }

#ifdef hppa
  setIOAReg(tmpIOA);
  setIOATopoffReg(tmpIOATop - tmpIOA);
  setRefSP((void *)&ReferenceStack[0]);
#endif

#ifdef mc68020
  IOA = tmpIOA;
  IOATop = tmpIOATop;
#endif

#ifdef sparc
  IOA = tmpIOA;
  IOATopoff = tmpIOATop - IOA;
#endif

  if( !AllocateHeap( &ToSpace, &ToSpaceTop, &ToSpaceLimit, IOASize ) ){
    fprintf(output,"#Beta: Couldn't allocate ToSpace (%dKb)\n", IOASize/Kb);
    exit(1);
  }

  /* Allocate the Callback Function Area */
  CBFAAlloc();

#ifdef UNIX
   { /* Setup signal handles for the Beta system */
     extern void SignalHandler();
     signal( SIGFPE,  SignalHandler);
     signal( SIGILL,  SignalHandler);
     signal( SIGBUS,  SignalHandler);
     signal( SIGSEGV, SignalHandler);
     signal( SIGEMT,  SignalHandler);
#ifdef apollo
     signal( SIGINT,  SignalHandler);
     signal( SIGQUIT, SignalHandler);
#endif
   }
#endif

  InfoS_Start();
}

