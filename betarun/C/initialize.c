/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * initialize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */
#include "beta.h"

#ifdef DMALLOC
GLOBAL(long mcheck_line);
#endif

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

#ifdef MAC
#include <Quickdraw.h>
#include <TextEdit.h>
#include <Fonts.h>
#include <Dialogs.h>
#include <CursorCtl.h>
#include <Menus.h>
#include <Windows.h>
#include <SegLoad.h>
#include <StdLib.h>
#include <String.h>
extern void _DataInit();
QDGlobals qd;

#define CPromptID 7130

void EnlargeMacHeap(char *buf)
{
  char buf1[300];
  char buf2[300];
  char buf3[300];
  char buf4[300];
  Notify(buf);
  if (StandAlone){
  	
    sprintf(buf1, "\nTry enlarging the application heap");
	sprintf(buf2, "\nusing the Info box in the Finder.");
	sprintf(buf3, "\nOr try quitting other aplications to free");
	sprintf(buf4, "\nmemory for this application.");
	CPrompt(buf1, buf2, buf3, buf4);
  } else {
    sprintf(buf1, "\nTry enlarging the heap of MPW");
    sprintf(buf2, "\nusing the Info box in the Finder.");
	CPrompt(buf1, buf2, NULL, NULL);
  }
}

/* Prompt four C Strings */
void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4)
{ 
  if (StandAlone){
    Str255 m1, m2, m3, m4;
    if (msg1) sprintf((char*)m1, "%c%s", strlen(msg1), msg1);
    if (msg2) sprintf((char*)m2, "%c%s", strlen(msg2), msg2);
    if (msg3) sprintf((char*)m3, "%c%s", strlen(msg3), msg3);
    if (msg4) sprintf((char*)m4, "%c%s", strlen(msg4), msg4);
    ParamText(m1, m2, m3, m4);
    Alert(CPromptID,0);
  } else {
    fprintf(output, "%s%s%s%s\n", msg1, msg2, msg3, msg4);
	fflush(output);
  }
}
#else
#define EnlargeMacHeap(buf) 
#endif /* MAC */

#ifdef PE
#if defined(MAC)
/* The following data was created using C/scramble.c with template
#define SCRAMBLETEMPLATE "\n\
Note:\n\nThis program was compiled using a Personal Edition of the \
Mj\277lner BETA System and may not be used for commercial purposes"
*/
#define PESTRING {\
0x36, 0xa1, 0xf7, 0xac, 0xf2, 0xf1, 0x25, 0x51, 0x2e, 0x6f, \
0x2f, 0x85, 0xce, 0xe7, 0xbe, 0xfa, 0xc6, 0xdd, 0xe5, 0xb1, \
0xba, 0xf6, 0xc0, 0xdc, 0x25, 0x6f, 0x29, 0x6d, 0x46, 0x58, \
0x5d, 0x61, 0x2e, 0x37, 0x6b, 0x41, 0x51, 0x68, 0x38, 0x41, \
0x49, 0x92, 0xeb, 0xb7, 0xee, 0xc6, 0xd2, 0xe5, 0xad, 0xea, \
0xf3, 0xdf, 0xe4, 0xb6, 0xeb, 0xab, 0xed, 0xac, 0xb5, 0x03, \
0x8e, 0xd7, 0xcc, 0xcd, 0xd1, 0x1a, 0x80, 0x13, 0xd5, 0xe2, \
0xb5, 0xf9, 0xb4, 0xbd, 0x28, 0x96, 0xeb, 0xd3, 0x1c, 0x78, \
0x2a, 0x82, 0x1f, 0xa3, 0xf7, 0x00, 0x8a, 0x0d, 0x92, 0xdb, \
0xdf, 0xe7, 0xc7, 0x10, 0xa7, 0xf1, 0xae, 0xb7, 0xfe, 0xc4, \
0x0d, 0xa1, 0xfb, 0xc7, 0xcc, 0x15, 0x9c, 0x1c, 0x97, 0xe0, \
0xac, 0xec, 0xaa, 0xf0, 0xbe, 0xf5, 0xbf, 0xff, 0xc7, 0xd4, \
0x1d, 0x96, 0x0c, 0xa7, 0x00, 0x98, 0x14, 0x9a, 0x12 }
#define PELEN 129
#define PECHK 11835
#else
#ifdef nti
#include <windows.h>
/* The following data was created using C/scramble.c with template
#define TEMPLATE "\
Note:\n\nThis program was compiled using a Personal Edition of the\n\
Mjølner BETA System and may not be used for commercial\npurposes\n\
"
*/
#define PESTRING {\
0x77, 0x41, 0x5e, 0x64, 0x87, 0xb6, 0xe5, 0xda, 0xdb, 0xdb, \
0xd1, 0x1a, 0x93, 0x0a, 0x8e, 0x12, 0x89, 0x11, 0xa5, 0xae, \
0x02, 0x8c, 0x28, 0x31, 0x7b, 0x3d, 0x79, 0x32, 0x84, 0x11, \
0x9d, 0x22, 0x2b, 0x87, 0x1d, 0x9d, 0x1c, 0xa4, 0xad, 0xf5, \
0xfe, 0xd7, 0xdb, 0xd2, 0xca, 0xce, 0xc9, 0xd1, 0xe6, 0xef, \
0xd3, 0xe0, 0xb2, 0xef, 0xaf, 0xe9, 0xb0, 0xb9, 0xff, 0xc2, \
0x0b, 0xa8, 0xe9, 0xb5, 0xe8, 0xce, 0xcd, 0x5e, 0x5b, 0x5e, \
0x64, 0x3f, 0x48, 0x33, 0x9f, 0xf4, 0xde, 0x27, 0x9d, 0x0d, \
0xa7, 0xfc, 0xc2, 0xd8, 0x21, 0x69, 0x30, 0x7d, 0x86, 0x14, \
0x9e, 0x10, 0x59, 0x60, 0x38, 0x75, 0x7e, 0x45, 0x49, 0x92, \
0x10, 0x8c, 0x12, 0x9f, 0xe8, 0xb7, 0x01, 0x9c, 0xe5, 0xaf, \
0xe9, 0xad, 0xe9, 0xb5, 0xf0, 0xbc, 0xfe, 0xc8, 0xcd, 0xf0, \
0xa9, 0x05, 0xa0, 0xf9, 0xbf, 0xf5, 0xb9, 0xf3, 0x22 }
#define PELEN 129
#define PECHK 11839
#else
/* The following data was created using C/scramble.c with template
#define TEMPLATE "\n\
*******************************************************************\n\
* Note: This program was compiled using a Personal Edition of the *\n\
* Mjolner BETA System and may not be used for commercial purposes *\n\
*******************************************************************\n\
\n"
*/
#define PESTRING {\
0x33, 0x42, 0x91, 0xe4, 0xf7, 0x06, 0x55, 0xa8, 0xab, 0xaa, \
0xa9, 0xac, 0xaf, 0xae, 0xad, 0xb0, 0xc3, 0x12, 0x61, 0x74, \
0x87, 0xd6, 0x25, 0x38, 0x3b, 0x3a, 0x39, 0x3c, 0x3f, 0x3e, \
0x3d, 0x40, 0x93, 0xe2, 0xf1, 0x04, 0x57, 0xa6, 0xb5, 0xc8, \
0x0b, 0x4a, 0x89, 0xcc, 0x0f, 0x4e, 0x8d, 0xd0, 0x23, 0x32, \
0x41, 0x94, 0xe7, 0xf6, 0x05, 0x58, 0x9b, 0xda, 0x19, 0x5c, \
0x9f, 0xde, 0x1d, 0x60, 0x73, 0x82, 0xd1, 0x24, 0x57, 0xa6, \
0xaf, 0x0a, 0x8e, 0x23, 0x6f, 0x7e, 0x87, 0xfc, 0xbd, 0xfd, \
0xb7, 0xc0, 0xd9, 0xd4, 0xe4, 0xac, 0x07, 0x8f, 0x0b, 0x54, \
0x4c, 0x56, 0x4e, 0x97, 0x1d, 0x9b, 0x1f, 0x98, 0x1a, 0x9f, \
0x23, 0x70, 0x79, 0x35, 0x6f, 0x2f, 0x6a, 0x36, 0x3f, 0x87, \
0xd0, 0xa9, 0xf5, 0xb0, 0xec, 0xac, 0xeb, 0xb3, 0x08, 0x51, \
0x3d, 0x82, 0x14, 0x89, 0x09, 0x8f, 0x0a, 0x53, 0x65, 0x2c, \
0x35, 0x6a, 0x2b, 0x77, 0x80, 0xd3, 0x02, 0x51, 0x9a, 0x00, \
0x93, 0x25, 0x72, 0x45, 0x49, 0x64, 0x6d, 0x58, 0x46, 0x3b, \
0xa3, 0xac, 0x28, 0x7a, 0x32, 0x6f, 0x33, 0x87, 0xd0, 0xda, \
0xdd, 0xe2, 0xeb, 0xaf, 0xf7, 0xb7, 0xc0, 0xd7, 0xe1, 0xbe, \
0xc7, 0xce, 0xd4, 0x1d, 0x91, 0x0b, 0x97, 0x1c, 0x65, 0x2c, \
0x6c, 0x47, 0x90, 0x1c, 0x9c, 0x1a, 0xa0, 0xee, 0xc5, 0xcf, \
0xcf, 0xd7, 0xe4, 0xed, 0xc6, 0xdc, 0xd7, 0xd0, 0xe8, 0xc4, \
0xca, 0xe2, 0xeb, 0xea, 0x09, 0x4c, 0x8f, 0xce, 0x0d, 0x50, \
0xa3, 0xb2, 0xc1, 0x14, 0x67, 0x76, 0x85, 0xd8, 0x1b, 0x5a, \
0x99, 0xdc, 0x1f, 0x5e, 0x9d, 0xe0, 0xf3, 0x02, 0x51, 0xa4, \
0xb7, 0xc6, 0x15, 0x68, 0x6b, 0x6a, 0x69, 0x6c, 0x6f, 0x6e, \
0x6d, 0x70, 0x83, 0xd2, 0x21, 0x34, 0x47, 0x96, 0xe5, 0xf8, \
0xfb, 0xfa, 0xf9, 0xfc, 0xff, 0xfe, 0xfd, 0x00, 0x53, 0xa2, \
0xb1, 0xc4, 0x17, 0x66, 0x75, 0x88, 0xcb, 0x0a, 0x49, 0x8c, \
0xcf, 0x0e, 0x2d, 0x50 }
#define PELEN 274
#define PECHK 17700
#endif /* nti */
#endif /* mac */
#endif /* PE */

static void
AllocateHeapFailed(char *name, int numbytes)
{
  char buf[300];
  sprintf(buf,
	  "%s: Cannot allocate the %s (%dKb)\n", 
	  ArgVector[0],
	  name,
	  (int)numbytes/Kb);
#ifdef MAC
  EnlargeMacHeap(buf);
#else
  Notify(buf);
#endif
  BetaExit(1);
}

static long 
AllocateHeap(ptr(long) base, 
	     ptr(long) top,
	     ptr(long) limit,
	     long numbytes,  
	     char *name
	     )
{
  if((*base = (long)MALLOC(numbytes)) != 0){
    INFO_ALLOC(numbytes);
    *top   = *base;
    *limit = *base + numbytes;
    return *base;
  } else {
    AllocateHeapFailed(name, numbytes);
    return 0;
  }
}

#ifdef PE
static char *unscrambleString(unsigned char *p, int len, int sum)
{
  int i, chk;
  unsigned char c;
  char *q;
  
  q = MALLOC(len+1);
  chk = 0;
  for (i=0; i<len; i++) {
    c = (p[i] - 41) ^ (i?p[i-1]:0);
    chk += c;
    q[i] = c;
  }
  q[len] = '\0';
  if (chk != sum)
    BetaExit(1);
  return q;
}
#endif /* PE */

/* 
 * Initialize: called from main.
 */
void Initialize()
{
  long *tmpIOA, *tmpIOATop;
  
#ifdef nti_gnu
  output = stderr;
#endif

#ifdef MT
  setbuf(stdout,0); /* disable buffering of output */
  setbuf(stderr,0);
#endif


  MT_CODE(initSynchVariables());

  /* This hack is to cope with the sparc, where
   * IOA and IOATop(off) is register vars
   */
   
#ifdef macppc
  InitGraf((Ptr) &qd.thePort);
  InitFonts();
  InitWindows();
  InitMenus();
  TEInit();
  InitDialogs(nil);
  InitCursor();
  InitTheCursor();
#endif

  GetBetaEnv();

  if (NoCatchException) {
    DEBUG_CODE(fprintf(output, "Signal Handlers Disabled\n"));
  } else { 
    SetupBetaSignalHandlers();
	SetupFPU();
  }

#ifdef MT
if (NumIOASlices) {
  IOASliceSize = IOASize / NumIOASlices;
} else {
  if (IOASliceSize) {
    NumIOASlices = IOASize / IOASliceSize;
  }
}
/* IOASize, NumIOASlices, and IOASliceSize now match */
if (NumIOASlices < numProcessors(TRUE)){
  /* There should at least be one slice per scheduler */
  NumIOASlices = numProcessors(TRUE);
  IOASliceSize = IOASize / NumIOASlices;
}
IOASliceSize = ObjectAlignDown(IOASliceSize);
#endif

#ifdef PE  
  {
    char *p;
    unsigned char peMessage[] = PESTRING;

    p = unscrambleString(peMessage,PELEN, PECHK);
#ifdef MAC
    CPrompt(p,"","","");
#else
#ifdef nti
    MessageBox(GetActiveWindow(),p,"Personal Edition Note",MB_OK);
#else
    printf("%s", p);
#endif /* nti */
#endif /* mac */
    FREE(p);
  }
#endif /* PE */

  InterpretItem[0] = 0;
  InterpretItem[1] = 0;
  
#ifdef RTDEBUG
  { 
    char buf[200];
    sprintf(buf, "RTS: Version %s\nRTS: Garbage collector may perform consistency checks on heaps (use BETART).",BETARUN_ID);
    Notify(buf);
  }
#endif
  
  INFO( fprintf( output, "#(Heap info: IOA=2*%dKb", (int)IOASize/Kb) );
  INFO( fprintf( output, ", AOABlock=%dKb", (int)AOABlockSize/Kb) );
  INFO( fprintf( output, ", LVRABlock=%dKb", (int)LVRABlockSize/Kb) );
  INFO( fprintf( output, ", CBFABlock=%dKb\n", (int)CBFABlockSize/Kb) );

  /* Adjust CBFA block size to fit an integral number of CallbackEntries */
  CBFABlockSize 
    = ((CBFABlockSize+CallBackEntrySize)/CallBackEntrySize)*CallBackEntrySize;
  DEBUG_CBFA(fprintf(output, "CBFABlockSize: %d\n", (int)CBFABlockSize));
  
  /* Allocate the IOA heap (Infant Object Area) */
  if ( IOASize <= 0 ) {
    char buf[100];
    sprintf(buf,"Too small IOA size specified: %dKb", (int)IOASize/Kb);
    Notify2(buf, "Check your BETART environment variable.");
    BetaExit(1);
  }
  AllocateHeap((long*)&tmpIOA,
	       (long*)&tmpIOATop,
	       (long*)&GLOBAL_IOALimit, 
	       IOASize,
	       "IOA heap");
#if defined(sparc) || defined(NEWRUN)
#ifdef MT
  gIOA = tmpIOA;
  gIOATop = tmpIOATop;
#else
  IOA = tmpIOA;
  IOATopOff = tmpIOATop - IOA;
#endif /* MT */
#else
  IOA = tmpIOA;
  IOATop = tmpIOATop;
#endif
  /* Clear the initial IOA heap */
  memset(GLOBAL_IOATop, 0, IOASize);
  INFO_HEAP_USAGE(PrintHeapUsage("after IOA heap allocation"));

  AllocateHeap((long*)&ToSpace, 
	       (long*)&ToSpaceTop, 
	       (long*)&ToSpaceLimit, 
	       IOASize,
	       "ToSpace heap");
  INFO_HEAP_USAGE(PrintHeapUsage("After ToSpace heap allocation"));

#ifdef NEWRUN
  /* Allocate the internal Reference Stack */
  ReferenceStack = (struct Object **)MALLOC(REFSTACKSIZE*sizeof(struct Object *));
  if (!ReferenceStack){
    AllocateHeapFailed("Reference Stack",REFSTACKSIZE*sizeof(struct Object *));
  }
  INFO_HEAP_USAGE(PrintHeapUsage("after ReferenceStack allocation"));
  RefSP = &ReferenceStack[0]; /* points to first free element */

  CompStack = (long *)MALLOC(REFSTACKSIZE*sizeof(long));
  if (!CompStack){
    AllocateHeapFailed("Component Stack",REFSTACKSIZE*sizeof(long));
  }
  INFO_HEAP_USAGE(PrintHeapUsage("after CompStack allocation"));
  CompSP = &CompStack[0]; /* points to first free element */
#endif /* NEWRUN */
  
  /* Allocate the Callback Function Area */
  CBFAalloc();

  InfoS_Start();

#ifndef nti_bor
#ifdef RTVALHALLA
  if (valhallaID) valhallaInit (0);
#endif /* RTVALHALLA */
#endif /* nti_bor */
 
}
