/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-2002 Mjolner Informatics Aps.
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

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

#ifdef ALLOC_TRACE
# include "trace-types.h"
  void init_alloc_trace();
#endif

#ifdef MAC
extern void _DataInit();

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

#else
#define EnlargeMacHeap(buf) 
#endif /* MAC */

void FixupPrefetch();


static void AllocateHeapFailed(char *name, int numbytes)
{
  char buf[512];
#ifdef USEMMAP
  sprintf(buf,
	  "%s: Cannot reserve virtual space for %s (%dKb)\n", 
	  ArgVector[0],
	  name,
	  (int)numbytes/Kb);
#else
  sprintf(buf,
	  "%s: Cannot allocate the %s (%dKb)\n", 
	  ArgVector[0],
	  name,
	  (int)numbytes/Kb);
#endif
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
#ifdef nti
  /* Windows sometimes gives you unaligned allocations.  This trick
   * fixes it, but it means you can't free these areas!
   */
  if ((*base = (long)MALLOC(numbytes + 8)) != 0) {
    *base = ObjectAlign((unsigned long)(*base));
    INFO_ALLOC(numbytes);
    *top   = *base;
    *limit = *base + numbytes;
    return *base;
  }
#else
  if ((*base = (long)MALLOC(numbytes)) != 0) {
    if (ObjectAlign((unsigned long)(*base)) != (unsigned long)(*base)) {
      fprintf(output, "Allocated unaligned heap\n");
      BetaExit(1);
    }
    INFO_ALLOC(numbytes);
    *top   = *base;
    *limit = *base + numbytes;
    return *base;
  }
#endif
  else {
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
    /* Set limit to reflect the amount requested */
    (*BaseBlock)->limit = (long*)((char*)((*BaseBlock)->top) + numbytes);
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


/* 
 * Initialize: called from main.
 */
 
#ifdef MAC
void increaseStackSize(Size extrabytes)
{
	
	Ptr currentStackEnd;
	Ptr newStackEnd;
	
	currentStackEnd = GetApplLimit();
	
	SetApplLimit(currentStackEnd - extrabytes);
	newStackEnd = GetApplLimit();
}

#endif

void Initialize()
{
  long *tmpIOA, *tmpIOATop;
  
  
#ifdef MAC
	increaseStackSize(2*1024*1024);
#endif

  
  if (!output)  
    output = stderr;

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
  InitToolbox();
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

  INFO( fprintf( output, "#(Heap info: IOA=2*%dKb", (int)IOASize/Kb) );
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
  if (!InsertGuardPage()) {
    AllocateHeapFailed("InsertGuardPage", MMAPPageSize);
  }
  mmapAllocateHeap(&IOABaseBlock, IOASize, "IOA heap");
  if (!InsertGuardPage()) {
    AllocateHeapFailed("AOAtoIOATable", IOASize);
  }
  mmapAllocateHeap(&ToSpaceBaseBlock, IOASize, "ToSpace heap");
  if (!InsertGuardPage()) {
    AllocateHeapFailed("InsertGuardPage", MMAPPageSize);
  }
  if (!AOAtoIOAalloc()) {
    AllocateHeapFailed("AOAtoIOATable", 2*12977971*8);
  }
  if (!InsertGuardPage()) {
    AllocateHeapFailed("InsertGuardPage", MMAPPageSize);
  }

  AOAMaxSize = mmapUnusedSize();
  AOAMaxSize -= PERSIST_MAXENTRIES; /* Leave room for persistense */
  AOAMaxSize -= 64 * MMAPPageSize; /* Leave 64 pages for other things */
  AOABaseBlock = reserveBlock(AOAMaxSize);
  AOABlocks++;
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

#ifdef ALLOC_TRACE
  init_alloc_trace();
#endif
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
 * -- 
 * EC
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
      char *alloipage2 = &AlloIEnd;

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

#ifdef ALLOC_TRACE

FILE *alloc_trace_handle;

/* Set environment variable ALLOC_TRACE_FILE to a filename
 * to output trace info to that file.
 * Set it to '| command' to send output to that command.
 */

void
init_alloc_trace()
{
    char *atf = getenv("ALLOC_TRACE_FILE");
    if (atf) {
	int i;
	if (*atf == '|') {
	    alloc_trace_handle = popen(atf+1, "w");
	} else {
	    alloc_trace_handle = fopen(atf, "w");
	}
	if (!alloc_trace_handle) {
	    perror("Open of ALLOC_TRACE_FILE failed\n");
	}
	i = TRACE_EXE_FILENAME;
	fwrite(&i, 4, 1, alloc_trace_handle);
	for(i = 0; i < strlen(ArgVector[0]); i+=4)
	    fwrite(ArgVector[0] + i, 4, 1, alloc_trace_handle);
	i = 0;
	fwrite(&i, 4, 1, alloc_trace_handle);
	i = TRACE_INIT_IOA;
	fwrite(&i, 4, 1, alloc_trace_handle);
	fwrite(&IOA, 4, 1, alloc_trace_handle);
	i = (int)IOA + IOASize;
	fwrite(&i, 4, 1, alloc_trace_handle);
	i = TRACE_INIT_IOA;
	fwrite(&i, 4, 1, alloc_trace_handle);
	fwrite(&ToSpace, 4, 1, alloc_trace_handle);
	i = (int)ToSpace + IOASize;
	fwrite(&i, 4, 1, alloc_trace_handle);
    }
}

#endif /* ALLOC_TRACE */
