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
#include <Quickdraw.h>
#include <TextEdit.h>
#include <Fonts.h>
#include <Dialogs.h>
#include <CursorCtl.h>
#include <Menus.h>
#include <Windows.h>
#include <SegLoad.h>
extern void _DataInit();

#define PromptID 7129

void Prompt(char *msg1, char *msg2, char *msg3, char *msg4)
{
  ParamText(msg1, msg2, msg3, msg4);
  Alert(PromptID,0);
}
#endif

#ifdef DEMO
#ifdef macintosh

#define DEMOSTRING1 "\p\
Mjølner BETA System - DEMO VERSION rel. 2.4\n\
\n\
This program is constructed using a DEMO version "

#define DEMOSTRING2 "\p\
of the Mjølner BETA System and may only be used \
for evaluation purposes and not for any teaching \
or commercial purposes. Use of the program is "

#define DEMOSTRING3 "\p\
subject to the restrictions in the demo license."

#define DEMOSTRING4 ""
#else
#define DEMOSTRING "\n\
  ******************************************************\n\
  *    Mjolner BETA System - DEMO VERSION rel. 2.4     *\n\
  ******************************************************\n\
  *  This program is constructed using a DEMO version  *\n\
  *  of the Mjolner BETA System and may only be used   *\n\
  *  for evaluation purposes and not for any teaching  *\n\
  *  or commercial purposes. Use of the program is     *\n\
  *  subject to the restrictions in the demo license   *\n\
  ******************************************************\n\
\n"
#endif
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
  InitGraf((Ptr) &qd.thePort);
  InitFonts();
  InitWindows();
  InitMenus();
  TEInit();
  InitDialogs(nil);
  InitCursor();
  InitTheCursor();
  UnloadSeg((Ptr)_DataInit); /* Unload %A5Init% segment */
  CouldAlert(PromptID);
#endif

  GetBetaEnv();

#ifdef DEMO
#ifdef macintosh
  Prompt(DEMOSTRING1, DEMOSTRING2, DEMOSTRING3, DEMOSTRING4);
#else
  fprintf(stdout, DEMOSTRING);
#endif
#endif

  INFO( fprintf( output, "#(Heap info: IOA=2*%dKb", IOASize/Kb) );
  INFO( fprintf( output, ", AOABlock=%dKb", AOABlockSize/Kb) );
  INFO( fprintf( output, ", LVRABlock=%dKb", LVRABlockSize/Kb) );
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

