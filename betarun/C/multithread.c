/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-96 Mjolner Informatics Aps.
 * multithread.c
 * by Peter Andersen, Morten Grouleff
 */

#include "beta.h"

#ifdef MT

#if defined(UNIX) || defined(nti)
#include <signal.h>
#endif /* UNIX || nti */

#ifdef sun4s
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#endif

#include <errno.h>
#include <unistd.h>

struct S_PreemptionLevel {
  unsigned long lock;
  unsigned long value;
  unsigned long inGC;
};



void initSynchVariables(void)
{
  mutex_init(&tsd_lock, USYNC_THREAD, NULL);
  mutex_init(&ioa_lock, USYNC_THREAD, NULL);
  mutex_init(&lvra_lock, USYNC_THREAD, NULL);
  mutex_init(&aoa_lock,  USYNC_THREAD, NULL);
  mutex_init(&aoatoioa_lock,  USYNC_THREAD, NULL);
  mutex_init(&cbfa_lock, USYNC_THREAD, NULL);
  mutex_init(&GC_lock, USYNC_THREAD, NULL);

  cond_init (&cond_startGC, USYNC_THREAD, NULL);
  mutex_init(&cond_startGC_lock, USYNC_THREAD, NULL);
  cond_init (&cond_GCdone, USYNC_THREAD, NULL);
  mutex_init(&cond_GCdone_lock, USYNC_THREAD, NULL);
}


void create_TSD(void)
{
  mutex_lock(&tsd_lock);
  TSDReg = MALLOC(sizeof(TSD));
  ThreadId = thr_self();
  Nums = MALLOC(sizeof(nums));

  /* insert newly created TSD into TSDlist */
  if (TSDlistlen <= NumTSD){
    int expand = numProcessors(TRUE); 
    TSDlist = REALLOC(TSDlist, (TSDlistlen + expand)*sizeof(TSD*));
    memset(TSDlist + (TSDlistlen * sizeof(TSD*)), 0, expand * sizeof(TSD*));  
    TSDlistlen += expand;
  }
  NumTSD++;
  
  while (NumIOASlices < NumTSD) {
    NumIOASlices += numProcessors(TRUE);
    IOASliceSize = IOASize / NumIOASlices;
    DEBUG_MT(fprintf(output,
		     "create_TSD: NumIOASlices changed to %d\n", 
		     (int)NumIOASlices));
  }

  for (TSDinx = 0; TSDlist[TSDinx]; TSDinx++)
    ;
  TSDlist[TSDinx] = TSDReg;
  
  mutex_unlock(&tsd_lock);
}

void destroy_TSD(void)
{
  long inx = TSDinx;

  if (!TSDReg)__asm__("unimp 0");
  /* mutex_lock(&tsd_lock); */
  while(mutex_trylock(&tsd_lock))
    sleep(1);
  if (!TSDReg)__asm__("unimp 0");
 
  free(Nums);
  if (!TSDReg)__asm__("unimp 0");
  free(TSDReg);
  TSDlist[inx] = NULL;
  TSDReg = NULL;
  NumTSD--;

  mutex_unlock(&tsd_lock);
}

static struct Object *AllocObjectAndSlice(unsigned int numbytes, unsigned int reqsize)
{
  /* ASSUMPTION: that max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ */

  struct Object *newObj;
  
  if (IOALimit == gIOATop){
    /* No other threads have been given a new slice since we got 
     * our last slice. So we can extend the current slice, and thus
     * utilize the remaining space in this slice, even though numbytes 
     * may be bigger.
     */
    newObj = (struct Object*)IOATop;
    IOATop = (long*)((long)IOATop + numbytes); /* size of object */
    gIOATop = (long*)((long)IOATop + reqsize-numbytes); /* size of slice */
  } else {
    newObj = (struct Object*)gIOATop;
    IOATop = (long*)((long)gIOATop + numbytes); /* size of object */
    gIOATop = (long*)((long)gIOATop + reqsize); /* size of slice */
  }
  savedIOALimit = IOALimit = gIOATop;

  return newObj;
}

struct Object *doGC(unsigned long numbytes)
{
  /* Allocate an IOA slice. 
   * -Attempts to allocate max(numbytes,IOASliceSize) bytes.
   * -At least numbytes are allocated.
   *  A GC is triggered, if there is not room for max(numbytes,IOASliceSize).
   */

  static volatile int numReadyToGC;
  struct Object *newObj;
  unsigned long reqsize = numbytes;
  int i;
  
  mutex_lock(&ioa_lock); /* IOA_CRITICAL_START */
  DEBUG_MT(fprintf(output,"TId=%d: Lock ioa_lock.\n", (int)ThreadId);
	   fflush(output);
	   );
  if (reqsize < IOASliceSize)
    reqsize = IOASliceSize;
  
  if (!IOATop) {
    /* IOATop is zero => this thread has not had a slice yet. */
    IOATop = gIOATop;
  } 
  
  if (gIOALimit < (long*)((long)gIOATop + reqsize)) {
    /* GC NEEDED */
    DEBUG_MT(fprintf(output,"TId=%d: GC Needed.\n", (int)ThreadId);
	     fflush(output);
	     );
    if (ActiveStack) {
      ActiveStack->refTopOff = (long)RefTopOffReg;
      ActiveStack->dataTopOff = (long)DataTopOffReg;
    }

    if (!mutex_trylock(&GC_lock)) {
      /* I'm the first thread that discoveres the need to GC */
      /* Get Ready to GC now:
       * 1) Only one threads will get in HERE for each GC.
       * 2) Setup variables & locks so that only this thread will do the GC.
       *    Also force all threads to run out of heap at next allocation, so
       *    that they will not use the rest of their slice.
       * 3) Then release ioa_lock, ie. let the other pass IOA_CRITICAL_START,
       *    where they have been blocked so far.
       * 4) Then wait for the last of the other threads to signal start_gc.
       * 5) Try IOAGc'ing at most three times.
       * 6) Allocate object and slice for this thread.
       * 7) signal gc_done to all other threads.
       */
      
      DEBUG_MT(fprintf(output,"TId=%d: Acquired GC_lock.\n", (int)ThreadId);
	       fflush(output);
	       );
      /* (2) */
      mutex_lock(&tsd_lock);
      for (i = 0; i < TSDlistlen; i++) {
	if (TSDlist[i]) {
	  TSDlist[i]->_IOALimit = gIOA; /* Makes all other threads run out of mem */
	}
      }
      mutex_unlock(&tsd_lock);
      numReadyToGC = 1;                  
      
      /* (3) */
      DEBUG_MT(fprintf(output,"TId=%d: UNLock ioa_lock.\n", (int)ThreadId);
	       fflush(output);
	       );
      mutex_unlock(&ioa_lock);
      
      /* (4) */
      mutex_lock(&cond_startGC_lock);
      while (numReadyToGC != NumTSD)
	cond_wait(&cond_startGC, &cond_startGC_lock);
      mutex_unlock(&cond_startGC_lock); 
      mutex_unlock(&GC_lock); 

      DEBUG_MT(fprintf(output,"TId=%d: Starting doGC.\n", (int)ThreadId);
	       fflush(output);
	       );
      /* Now all other threads are sleeping */      
      /* (5) */
      ReqObjectSize = numbytes/4;

      /* Try up to 3 IOAGcs to mature enough object to go into AOA */
      for (i=0; i<2; i++){
	IOAGc();
	if ((long*)((long)gIOATop + reqsize) <= gIOALimit) {
	  /* (6.0) */
	  IOATop = gIOATop; 
	  gIOATop = (long*)((long)gIOATop + reqsize); /* size of slice */
	  newObj = (struct Object *)IOATop;
	  IOATop += numbytes;
	  savedIOALimit = IOALimit = gIOATop;
	  break;
	}

	INFO_IOA(fprintf(output, "[%d]\n", i+1));
	if (i==1){
	  /* Have now done two IOAGc's without freeing enough space.
	   * Make sure that all objects go to AOA in the next GC.
	   */
	  IOAtoAOAtreshold=2;
	  DEBUG_IOA(fprintf(output, "Forcing all objects in IOA to AOA\n"));
	  IOAGc();

	  IOATop = gIOATop; 
	  if ((long*)((long)gIOATop + reqsize) <= gIOALimit) {
	  /* (6.1) */
	    gIOATop = (long*)((long)gIOATop + reqsize); /* size of slice */
	    newObj = (struct Object *)IOATop;
	    IOATop += numbytes;
	    savedIOALimit = IOALimit = gIOATop;
	    break;
	  }
	  
	  /* Have now tried everything to get enough space in IOA */
	  /* Aber dann haben wir anderen metoden! */
	  /* (6.2) */
	  newObj = AOAcalloc(numbytes);
	  IOATop = gIOATop;
	  gIOATop = (long*)((long)gIOATop + IOASliceSize); /* size of slice */
	  savedIOALimit = IOALimit = gIOATop;
	}
	/* Not reached */
	DEBUG_CODE(Claim(TRUE, "doGC: end not reached"));
	newObj = NULL;
      }
      
      DEBUG_MT(fprintf(output,"TId=%d: GC completed.\n", (int)ThreadId);
	       fflush(output);
	       );
      /* (7) */
      DEBUG_MT(fprintf(output,"TId=%d: Broadcast on GCdone.\n", (int)ThreadId);
	       fflush(output);
	       );
      mutex_lock(&cond_GCdone_lock);
      cond_broadcast(&cond_GCdone);
      mutex_unlock(&cond_GCdone_lock);      
    } 
    else {
      DEBUG_MT(fprintf(output,"TId=%d: Increment and signal.\n", (int)ThreadId);
	       fflush(output);
	       );
      numReadyToGC++;
      DEBUG_MT(fprintf(output,"TId=%d: UNLock ioa_lock.\n", (int)ThreadId);
	       fflush(output);
	       );
      DEBUG_MT(fprintf(output,"TId=%d: Wait for GC to complete.\n", (int)ThreadId);
	       fflush(output);
	       );
      mutex_lock(&cond_GCdone_lock);
      cond_signal(&cond_startGC);
      mutex_unlock(&ioa_lock);
      /* FIXME: problem: The thread GC'ing may finish before I get to wait... */
      while (cond_wait(&cond_GCdone, &cond_GCdone_lock))
	;
      DEBUG_MT(fprintf(output,"TId=%d: Received GCdone.\n", (int)ThreadId);
	       fflush(output);
	       );

      if (gIOALimit < (long*)((long)gIOATop + reqsize)) {
	/* Not enough room in IOA. Allocate object in AOA, and return empty slice */
	DEBUG_MT(fprintf(output,"TId=%d: Alloced in AOA\n", (int)ThreadId);
		 fflush(output);
		 );
	newObj = AOAcalloc(numbytes);
	IOATop = gIOATop;
	savedIOALimit = IOALimit = gIOATop;
      }
      else {
	/* There is room for my request, as
	 * max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ 
	 */
	newObj = AllocObjectAndSlice(numbytes, reqsize);
      }
      DEBUG_MT(fprintf(output,"TId=%d: Unlocking GCdone_lock\n", (int)ThreadId);
	       fflush(output);
	       );
      mutex_unlock(&cond_GCdone_lock);
    }
  } 
  else {
    /* No need to GC, as 
     * max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ 
     */
    newObj = AllocObjectAndSlice(numbytes, reqsize);
    DEBUG_MT(fprintf(output,"TId=%d: UNLock ioa_lock\n", (int)ThreadId);
	     fflush(output);
	     )
    mutex_unlock(&ioa_lock);
  }

  return newObj;
}

void DoGC() /* The one called directly from betaenv */
{
  doGC(0);
}


int numProcessors(int online)
{
  if (online){
    /* report #processors currently online */
    return sysconf(_SC_NPROCESSORS_ONLN);
  } else {
    /* report #processors configured */
    return sysconf(_SC_NPROCESSORS_CONF);
  }
}

extern void *AttTC(void *);

thread_t attToProcessor(struct Component *comp)
{ 
  thread_t tid;
  if (thr_create(NULL                           /* stack base */,
		 0                              /* stack size */,
		 (void *(*)(void *))AttTC       /* func       */,
		 (void *)comp                   /* arg        */,
		 THR_NEW_LWP|THR_DETACHED       /* flags      */,
		 &tid                           /* id         */)){
    fprintf(output, "Failed to create thread for component 0x%x\n", (int)comp);
    fflush(output);
    exit (1);
  }
  /* FIXME: why does this make 'threads' fail when run with BETART=DebugMt? */
#if 0
  DEBUG_MT(fprintf(output, 
		   "[Created thread 0x%x for comp 0x%x]\n", 
		   (int)tid, 
		   (int)comp);
	   fflush(output););
#endif

  return tid;
}

#ifdef RTDEBUG
void ReportMainStarted(void)
{
  DEBUG_MT(fprintf(output, 
		   "[MAIN thread 0x%x started]\n", 
		   (int)thr_self());
	   fflush(output));
}
#endif

static __inline__ int TryLock(unsigned long* l)
{ 
  register int v;
  __asm__ volatile ("ldstub\t[%1],%0" : "=r" (v) : "r" (l));
  return !v; 
}
static __inline__ void UnLock(unsigned long* l)
{ 
  __asm__ volatile ("stbar\n"
		    "stb\t%%g0,[%0]" : /* no outs */ : "r" (l));
}

struct S_PreemptionLevel PreemptionLevel;

void SetupVirtualTimer(unsigned usec);
GLOBAL(int AlarmOccured) = 0;
void AlarmHandler(int sig, siginfo_t *sip, void *uap)
{
  AlarmOccured++;
  
  if (TryLock(&PreemptionLevel.lock)){
    if (!PreemptionLevel.value) { 
      if (!PreemptionLevel.inGC) { /* We cannot reset IOALimit while GC'ing */
	IOALimit = 0;
	DEBUG_MT(fprintf(output, "IOALimit=0x%x\n", (int)IOALimit));
      }
    }
    UnLock(&PreemptionLevel.lock);
  }
}

void SetupVirtualTimerHandler()
{
  struct sigaction act;

  PreemptionLevel.lock = 0;
  PreemptionLevel.value = 1;
  act.sa_handler = NULL;            /* Unused */
  act.sa_sigaction = &AlarmHandler; /* the handler */
  act.sa_flags = SA_SIGINFO;        /* Use sa_sigaction, not sa_handler */ 
  sigemptyset(&act.sa_mask);        /* Block no other signals in handler */

  if (sigaction(SIGVTALRM, &act, NULL)) {
    fprintf(output,"sigaction failed. Errno=%d (%s)\n", errno,strerror(errno));
    BetaExit(1);
  }
}

void SetupVirtualTimer(unsigned usec)
{
  struct itimerval interval;

  /* setup timer tu trigger each usec microseconds */
  interval.it_value.tv_sec = 0;
  interval.it_value.tv_usec = usec;
  interval.it_interval.tv_sec = 0;
  interval.it_interval.tv_usec = usec;

  if (setitimer(ITIMER_VIRTUAL, &interval, NULL)) {
    fprintf(output,"setitimer failed. Errno=%d (%s)\n", errno,strerror(errno));
    BetaExit(1);
  }  
}

void* MT_malloc(int size) 
{ 
  void* p = memalign(64, (size));
  DEBUG_MT(fprintf(output,"[malloc at 0x%0x]\n", (int)p));
  memset(p, 0, (size));
  return p;
}

#endif /* MT */
