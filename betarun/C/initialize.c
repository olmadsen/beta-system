/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * initialize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */
#include "beta.h"

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
#include <StdLib.h>
extern void _DataInit();

#define PromptID  7129
#define CPromptID 7130

/* Prompt four C Strings */
void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4)
{ Str255 m1, m2, m3, m4;
  if (msg1) sprintf(m1, "%c%s", strlen(msg1), msg1);
  if (msg2) sprintf(m2, "%c%s", strlen(msg2), msg2);
  if (msg3) sprintf(m3, "%c%s", strlen(msg3), msg3);
  if (msg4) sprintf(m4, "%c%s", strlen(msg4), msg4);
  ParamText(m1, m2, m3, m4);
  Alert(CPromptID,0);
}
/* Prompt four Pascal Strings */
void Prompt(char *msg1, char *msg2, char *msg3, char *msg4)
{
  ParamText(msg1, msg2, msg3, msg4);
  Alert(PromptID,0);
}
#endif

#ifdef DEMO
#ifdef macintosh

#define DEMOSTRING1 "\p\
Mj\277lner BETA System - DEMO VERSION rel. 2.6\n\
\n\
This program is constructed using a DEMO version "

#define DEMOSTRING2 "\p\
of the Mj\277lner BETA System and may only be used \
for evaluation purposes and not for any teaching \
or commercial purposes. Use of the program is "

#define DEMOSTRING3 "\p\
subject to the restrictions in the demo license."

#define DEMOSTRING4 ""
#else
#define DEMOSTRING "\n\
  ******************************************************\n\
  *    Mjolner BETA System - DEMO VERSION rel. 2.6     *\n\
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
  CouldAlert(CPromptID);
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

#ifdef linux
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

#ifndef sun4s
#ifdef UNIX
   { /* Setup signal handles for the Beta system */
     signal( SIGFPE,  BetaSignalHandler);
     signal( SIGILL,  BetaSignalHandler);
     signal( SIGBUS,  BetaSignalHandler);
     signal( SIGSEGV, BetaSignalHandler);
#ifndef linux
     signal( SIGEMT,  BetaSignalHandler);
#endif
#ifdef apollo
     signal( SIGINT,  BetaSignalHandler);
     signal( SIGQUIT, BetaSignalHandler);
#endif
   }
#endif

#else /* sun4s */
  /* sbrandt 9/7 93. See man sigaction and <sys/signal.h>. */
  { /* Setup signal handlers for the Beta system */
    struct sigaction sa;

    /* Specify that we want full info about the signal, and that
     * the handled signal should not be blocked while being handled: */
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;

    /* No further signals should be blocked while handling the specified
     * signals. */
    sigemptyset(&sa.sa_mask); 

    /* Specify handler: */
    sa.sa_handler = BetaSignalHandler;
    
    sigaction( SIGFPE,  &sa, 0);
    sigaction( SIGILL,  &sa, 0);
    sigaction( SIGBUS,  &sa, 0);
    sigaction( SIGSEGV, &sa, 0);
    sigaction( SIGEMT,  &sa, 0);
  }
#endif /* sun4s */

  InfoS_Start();
}

