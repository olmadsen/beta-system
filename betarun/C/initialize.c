/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * initialize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */
#include "beta.h"

#ifdef __linux__
# include <sys/mman.h>   /* for mprotect */
# include <limits.h> /* for pagesize */
# ifndef PAGESIZE
#   define PAGESIZE 4096
# endif
#endif

#ifdef nti
# include <winbase.h>
# include <winnt.h>
#endif

#ifdef DMALLOC
GLOBAL(long mcheck_line);
#endif /* DMALLOC */

#ifdef PERSIST
extern void initObjectTable(void);
extern void initReferenceTable(void);
#endif /* PERSIST */

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
  char buf1[512];
  char buf2[512];
  char buf3[512];
  char buf4[512];
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

void FixupPrefetch();

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

static void AllocateHeapFailed(char *name, int numbytes)
{
  char buf[512];
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

#ifndef USEMMAP
static long  AllocateHeap(long * base, 
	     long * top,
	     long * limit,
	     long numbytes,  
	     char *name
	     )
{
  if((*base = (long)MALLOC(numbytes)) != 0){
    if (ObjectAlign((unsigned long)(*base)) != (unsigned long)(*base)) {
      fprintf(output, "Allocated unaligned heap\n");
      BetaExit(1);
    }
    INFO_ALLOC(numbytes);
    *top   = *base;
    *limit = *base + numbytes;
    return *base;
  } else {
    AllocateHeapFailed(name, numbytes);
    return 0;
  }
}
#else
static int mmapAllocateHeap(Block **BaseBlock, 
			    long numbytes, char *name)
{
  long size = (numbytes+sizeof(Block)+MMAPPageSize-1) & ~(MMAPPageSize-1);
  *BaseBlock = AllocateBlock(size);
  if (*BaseBlock) {
    return 1;
  } else {
    AllocateHeapFailed(name, size);
    return 0;
  }
}

#if 0
static int ReserveHeap(Block **BaseBlock, 
		       long numbytes, char *name)
{
  long size = (numbytes+sizeof(Block)+MMAPPageSize-1) & ~(MMAPPageSize-1);
  *BaseBlock = reserveBlock(size);
  if (*BaseBlock) {
    return 1;
  } else {
    AllocateHeapFailed(name, size);
    return 0;
  }
}
#endif /* 0 */
#endif /* USEMMAP */

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
  
  if (!output)  
    output = stderr;
#ifdef nti_gnu
  if (!beta_instance){
    beta_instance = (long)GetModuleHandle(0);
  }
#endif

#ifdef MT
  setbuf(stdout,0); /* disable buffering of output */
  setbuf(stderr,0);
#endif


  MT_CODE(initSynchVariables());

  /* This hack is to cope with the sparc, where
   * IOA and IOATop(off) is register vars
   */

#if defined(__linux__) && defined(__i386__)
  FixupPrefetch();
#endif
   
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

#ifdef INTERPRETER
  InterpretItem[0] = 0;
  InterpretItem[1] = 0;
#endif /* INTERPRETER */
  
#ifdef RTDEBUG
  { 
    char buf[512];
    sprintf(buf, "RTS: Version %s\nRTS: Garbage collector may perform consistency checks on heaps (use BETART).",BETARUN_ID);
    Notify(buf);
    if (do_unconditional_gc){
      sprintf(buf, "RTS: Doing unconditional GC at every allocation!\n");
      Notify(buf);
    }
  }
#endif

  INFO( fprintf( output, "#(Heap info: IOA=2*%dKb", (int)IOASize/Kb) );
  INFO( fprintf( output, ", AOABlock=%dKb", (int)AOABlockSize/Kb) );
  INFO( fprintf( output, ", CBFABlock=%dKb\n", (int)CBFABlockSize/Kb) );

  /* Adjust CBFA block size to fit an integral number of CallbackEntries */
  CBFABlockSize 
    = ((CBFABlockSize+CallBackEntrySize)/CallBackEntrySize)*CallBackEntrySize;
  DEBUG_CBFA(fprintf(output, "CBFABlockSize: %d\n", (int)CBFABlockSize));
  
  /* Allocate the IOA heap (Infant Object Area) */
  if ( IOASize <= 0 ) {
    char buf[512];
    sprintf(buf,"Too small IOA size specified: %dKb", (int)IOASize/Kb);
    Notify2(buf, "Check your BETART environment variable.");
    BetaExit(1);
  }

  AOAInit();
  
#ifdef USEMMAP
  mmapInitial(MMAPMaxSize);
  /* The order of allocation here determines the order of adresses. */
  InsertGuardPage();
  mmapAllocateHeap(&IOABaseBlock, IOASize, "IOA heap");
  InsertGuardPage();
  mmapAllocateHeap(&ToSpaceBaseBlock, IOASize, "ToSpace heap");
  InsertGuardPage();
  AOAtoIOAalloc();
  InsertGuardPage();
#endif /* USEMMAP */

#ifdef USEMMAP
  tmpIOA          = IOABaseBlock->top;
  tmpIOATop       = IOABaseBlock->top;
  GLOBAL_IOALimit = IOABaseBlock->limit;
#else /* USEMMAP */
  tmpIOA = NULL;
  while((long)tmpIOA <= IOASize) {
    AllocateHeap((long*)&tmpIOA,
                 (long*)&tmpIOATop,
                 (long*)&GLOBAL_IOALimit, 
                 IOASize,
                 "IOA heap");
  }
#endif /* USEMMAP */

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

#ifdef USEMMAP
  ToSpace      = ToSpaceBaseBlock->top;
  ToSpaceTop   = ToSpaceBaseBlock->top;
  ToSpaceLimit = ToSpaceBaseBlock->limit;
#else /* USEMMAP */
  AllocateHeap((long*)&ToSpace, 
	       (long*)&ToSpaceTop, 
	       (long*)&ToSpaceLimit, 
	       IOASize,
	       "ToSpace heap");
  INFO_HEAP_USAGE(PrintHeapUsage("After ToSpace heap allocation"));
#endif /* USEMMAP */

#if defined(NEWRUN) || (defined(RTVALHALLA) && defined(intel))
  /* Allocate the internal Reference Stack */
  ReferenceStack = (Object **)MALLOC(REFSTACKSIZE*sizeof(Object *));
  if (!ReferenceStack){
    AllocateHeapFailed("Reference Stack",REFSTACKSIZE*sizeof(Object *));
  }
  INFO_HEAP_USAGE(PrintHeapUsage("after ReferenceStack allocation"));
  RefSP = &ReferenceStack[0]; /* points to first free element */

#endif /* NEWRUN || (RTVALHALLA && intel) */

#ifdef NEWRUN
  /* Allocate the internal Component Stack */
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

#ifdef PERSIST
  initObjectTable();
  initReferenceTable();
#endif /* PERSIST */
}

#if (defined(__linux__) && defined(__i386__)) || defined(nti)

/*
 * The AMD Athlon (K7) and later and the Pentium III and later support
 * prefetch instructions.  Some of the earlier processors can ignore
 * the prefetch instructions, but not all.  Eg. the 486 can't ignore it
 * and gives an invalid instruction error.  So we remove it for processors
 * that don't support it.
 *
 * An Intel (or other) processor supports prefetch if it has the "kni"
 * (Katmai New Instructions = Streaming SSE extensions) flag set.
 *
 * An AMD processor also supports prefetch if it is CPU family 6 or later.
 * This is because the Athlon does have prefetch, but it doesn't have the
 * other KNI instructions.  The Prefetch in 3dNow is a different instruction
 * (Athlon has both) which we don't support.  For older (2.0) Linux kernels
 * there is no 'cpu family' field in cpuinfo, but a 'cpu' field which can
 * be 586, 686, etc.
 *
 * It would be nice to fix the SSE prefetch instructions to use 3DNow!
 * prefetch instructions on the K6.  This would mean amending the 0f 18
 * ModR/M insn sequence to 0f 0d ModR/M and setting bits 5:3 of the Mod/RM
 * byte to be 001.  See AMD Ordernumber/PDF 21928 page 56 (66 in pdf), 
 * the "3dNow! Technology Manual".  Don't have a machine to test on right now.
 *
 * I don't use the cpuid insn because you have to do some tests first
 * to determine whether your processor supports cpuid :-(.
 *
 */

extern char AlloIEnd;
extern char AlloIPrefetch;
extern char AlloIPrefetchEnd;

#if defined(__linux__) && defined(__i386__)

static void removeprefetch();
static void convertprefetchto3dnow();

static int
hasflag(const char *buffer, const char *keyword)
{
  char spkeyword[1000];
  char *flagsposn = strstr(buffer, "\nflags");

  sprintf(spkeyword, " %s%c", keyword, 0);
  if (flagsposn && isspace(flagsposn[6])) {
      char *newlineposn = strstr(flagsposn, "\n");
      char *keywordposn;
      findkeyword:
      keywordposn = strstr(flagsposn, spkeyword);
      if (keywordposn && keywordposn < newlineposn) {
	  if (keywordposn[strlen(keyword)+1] == 0 ||
	      isspace(keywordposn[strlen(keyword)+1])) {
	      return 1;
	  }
	  else {
	      flagsposn = keywordposn + 1;
	      goto findkeyword;
	  }
      }
  }
  return 0;
}

void FixupPrefetch()
{
  FILE *fp;
  int dofixup = 1;
  int do3dnowfixup = 0;
  int mprotectfailure = 0;
  fp = fopen("/proc/cpuinfo", "r");
  if(fp) {
      char buffer[2048];
      int bytesread = fread(buffer, 1, 2047, fp);
      fclose(fp);

      buffer[(bytesread >= 0) ? bytesread : 0] = 0;
      if (hasflag(buffer, "kni"))
          dofixup = 0;
      if (dofixup && strstr(buffer, "AuthenticAMD")) {
          char *cpufamilyposn = strstr(buffer, "\ncpu family");
	  int cpufamily;
          if (cpufamilyposn && isspace(cpufamilyposn[11])) {
	      cpufamilyposn += 11;
	      while (cpufamilyposn[0] && cpufamilyposn[0] != ':')
	          cpufamilyposn++;
	      while (cpufamilyposn[0] && isspace(cpufamilyposn[1]))
	          cpufamilyposn++;
              cpufamily = atoi(cpufamilyposn);
	      if (cpufamily >= 6) dofixup = 0;
	  } else {
              cpufamilyposn = strstr(buffer, "\ncpu");
	      if (cpufamilyposn && isspace(cpufamilyposn[4])) {
		  cpufamilyposn += 4;
		  while (cpufamilyposn[0] && cpufamilyposn[0] != ':')
		      cpufamilyposn++;
		  while (cpufamilyposn[0] && isspace(cpufamilyposn[1]))
		      cpufamilyposn++;
		  cpufamily = atoi(cpufamilyposn);
		  if (cpufamily >= 686) dofixup = 0;
	      }
	  }
      }
      if (dofixup && hasflag(buffer, "3dnow")) {
          do3dnowfixup = 1;
	  dofixup = 0;
      }
  }

  if (getenv("BETANO3DNOW") && do3dnowfixup) {
      do3dnowfixup = 0;
      dofixup = 1;
  }
  if (getenv("BETASSEPREFETCH")) {
      do3dnowfixup = 0;
      dofixup = 0;
  }
  if (getenv("BETANOPREFETCH")) {
      do3dnowfixup = 0;
      dofixup = 1;
  }
  if (getenv("BETA3DNOWPREFETCH")) {
      do3dnowfixup = 1;
      dofixup = 0;
  }
  
  if (dofixup || do3dnowfixup) {
      char *alloipage = &AlloIPrefetch;
      char *alloipage2 = &AlloIPrefetchEnd;

      alloipage = (char *) (((long)alloipage) & ~(PAGESIZE-1));
      alloipage2 = (char *) (((long)alloipage2) & ~(PAGESIZE-1));
      mprotectfailure =
          mprotect(alloipage, PAGESIZE, PROT_WRITE | PROT_READ | PROT_EXEC);
      if(!mprotectfailure && alloipage != alloipage2) mprotectfailure =
          mprotect(alloipage2, PAGESIZE, PROT_WRITE | PROT_READ | PROT_EXEC);
      if (mprotectfailure) {
          perror("mprotect");
	  fprintf(stderr, "Warning: could not fix up prefetch info\n");
      }
  }

  if (dofixup && !mprotectfailure) {
      removeprefetch();
  } else if (do3dnowfixup && !mprotectfailure) {
      convertprefetchto3dnow();
  }
}

/* Should work on both linux and nti */

static void
removeprefetch()
{
  int shiftdistance = &AlloIPrefetchEnd - &AlloIPrefetch;
#ifndef RTDEBUG
  int codelength =  &AlloIEnd - &AlloIPrefetchEnd;
#endif
  /* fprintf(stderr, "Removing prefetch instructions\n"); */
#ifdef RTDEBUG
  /* In the debug version we do this in order to make it easier to
   * debug.  Costs a little in performance, but who cares in the DEBUG
   * version.
   *
   * Otherwise, we don't use this method right now, but we might need it if
   * AlloI at some point can't just be block copied down to a lower
   * address because it contains non-relative jumps.  The advantage
   * of the memmove method is that it costs nothing on older processors
   *
   */
  AlloIPrefetch = (char)0xeb;  /* JMP rel8 */
  (&AlloIPrefetch)[1] = shiftdistance - 2;
  memset((&AlloIPrefetch) + 2,
	  0x90,   /* NOP */
	  shiftdistance - 2);
#else
  /*
   * Zero cost fixup:  We move the code at program start, removing the
   * prefetch code altogether.  Insert some NOPs to make disassembler output
   * look nicer.
   */

  memmove(&AlloIPrefetch, &AlloIPrefetchEnd, codelength);
  memset(&AlloIEnd - shiftdistance, 0x90 /* NOP */, shiftdistance);
#endif
}

/* Should work on both linux and nti */

static void
convertprefetchto3dnow()
{
  char *alloipage = &AlloIPrefetch;
  char *alloipage2 = &AlloIPrefetchEnd;
  alloipage--;

  /* fprintf(stderr, "Fixing prefetch to use 3DNow! insns\n"); */

#define GETBYTE alloipage++; if (alloipage >= alloipage2) goto donefixing3dnow

/* This is a little x86 instruction parser that can convert SSE prefetch
* instructions to 3DNow! prefetch instructions.  That is, it converts
* 0f 18 ModR/M to 0f 0d ModR/M and knows how many bytes of immediate data
* to skip.  It's done from page 26-6 in MG's big 486 reference manual.
*
* Right now it doesn't understand any other instructions, and it stops when
* it hits an instruction it doesn't understand, so you have to teach it 
* more instructions if you want it to scan past more stuff.
*/

startofinstruction:
  GETBYTE;
  if (*alloipage == 0x0f) goto twobyteprefixrecognised;
  goto donefixing3dnow;
twobyteprefixrecognised:
  GETBYTE;
  if (*alloipage == 0x18) {
      /* Fix SSE prefetch 0f 18 to be 3dNow prefetch 0f 0d */
      *alloipage = 0x0d;
      goto sseprefetchrecognised;
  }
  goto donefixing3dnow;
sseprefetchrecognised:
  GETBYTE;
  /* Fix up SSE prefetch ModR/M byte to 3DNow prefetch ModR/M byte */
  *alloipage &= 0xc7;  /* Delete bits that control cache level in SSE */
  *alloipage |= 0x08;  /* This line converts prefetch to prefetchw */
  alloipage--;
  goto modrmbyte;
modrmbyte:
  GETBYTE;
  if ((*alloipage & 0xc7) == 0x04) goto sibbytedisp32;
  else if ((*alloipage & 0xc7) == 0x44) goto sibbytedisp8;
  else if ((*alloipage & 0xc7) == 0x84) goto sibbytedisp32;
  if ((*alloipage & 0xc7) == 0x09) alloipage += 4;
  else if ((*alloipage & 0xc0) == 0x40) alloipage += 1;
  else if ((*alloipage & 0xc0) == 0x80) alloipage += 4;
  goto startofinstruction;
sibbytedisp32:
  GETBYTE;
  if ((*alloipage & 0x07) == 5) alloipage += 4;
  goto startofinstruction;
sibbytedisp8:
  GETBYTE;
  if ((*alloipage & 0x07) == 5) alloipage += 1;
  goto startofinstruction;
donefixing3dnow:
  ;
}

#else /* ifdef nti */
#ifdef thisnticodeisntfinishedyet

void
FixupPrefetch()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	/* assume x86 */
	if(sysinfo.dwProcessorType >= 586) {
		/* Now we know we support CPUID command */
		/* http://x46.deja.com/=dnc/getdoc.xp?AN=337951009 */
		/* Apparently you can't use dwProcessorLevel */
		/* http://x46.deja.com/=dnc/getdoc.xp?AN=448372088 */
		/* Now we just need to call CPUid and check the flags... */
	}
}

#endif /* thisnticodeisntfinishedyet */
#endif /* linux/nti */

#endif  /* defined(__linux__) && defined(__i386__) || defined(nti) */

#ifdef sparc
int _init(void)
{
  return 0;
}

int _info(void)
{
  return 0;
}

int _fini(void)
{
  return 0;
}


#endif /* sparc */
