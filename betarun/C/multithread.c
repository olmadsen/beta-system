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

static long TSDlistlen=0;

void create_TSD(void)
{
  mutex_lock(&tsd_lock);
  TSDReg = MALLOC(sizeof(TSD));
  ThreadId = thr_self();
  Nums = MALLOC(sizeof(nums));

  /* insert newly created TSD into TSDlist */
  if (TSDlistlen <= NumTSD){
    int expand =  numProcessors(TRUE);
    TSDlist = REALLOC(TSDlist, TSDlistlen + expand);
    memset(TSDlist + (TSDlistlen * sizeof(TSD*)), 0, expand * sizeof(TSD*));  
    TSDlistlen += expand;
  }
  
  for (TSDinx = 0; TSDlist[TSDinx]; TSDinx++)
    ;
  TSDlist[TSDinx] = TSDReg;
  NumTSD++;
  
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
  IOALimit =  gIOATop;

  return newObj;
}

struct Object *doGC(unsigned numbytes);

struct Object *getNewIOASlice(unsigned long numbytes)
{
  /* Allocate an IOA slice. 
   * -Attempts to allocate max(numbytes,IOASliceSize) bytes.
   * -At least numbytes are allocated.
   *  A GC is triggered, if there is not room for max(numbytes,IOASliceSize).
   */

  static volatile int numReadyToGC;
  struct Object *newObj;
  unsigned long reqsize = numbytes;

  mutex_lock(&ioa_lock); /* IOA_CRITICAL_START */
  DEBUG_MT(fprintf(output,"TId=%d: Lock ioa_lock.\n", (int)ThreadId);
	   fflush(output);
	   )
  if (reqsize < IOASliceSize)
    reqsize = IOASliceSize;

  if (!IOATop) {
    /* IOATop is zero => this thread has not had a slice yet. */
    IOATop = gIOATop;
  } 
  
  if (gIOALimit < (long*)((long)IOATop + reqsize)) {
    /* GC NEEDED */
    DEBUG_MT(fprintf(output,"TId=%d: GC Needed.\n", (int)ThreadId);
	     fflush(output);
	     )
    
    if (!mutex_trylock(&GC_lock)) {
      /* I'm the first thread that discoveres the need to GC */
      /* Get Ready to GC now:
       * 1) Only one threads will get in HERE for each GC.
       * 2) Setup variables & locks so that only this thread will do the GC.
       * 3) Then release ioa_lock, ie. let the other pass IOA_CRITICAL_START,
       *    where they have been blocked so far.
       * 4) Then wait for the last of the other threads to signal start_gc.
       * 5) doGC
       * 6) Allocate object and slice for this thread.
       * 7) signal gc_done to all other threads.
       */
      
      DEBUG_MT(fprintf(output,"TId=%d: Acquired GC_lock.\n", (int)ThreadId);
	       fflush(output);
	       )
      /* (2) */
      numReadyToGC = 1;                  
      
      /* (3) */
      DEBUG_MT(fprintf(output,"TId=%d: UNLock ioa_lock.\n", (int)ThreadId);
	       fflush(output);
	       )
      mutex_unlock(&ioa_lock);
      
      /* (4) */
      mutex_lock(&cond_startGC_lock);
      while (numReadyToGC != NumTSD)
	cond_wait(&cond_startGC, &cond_startGC_lock);
      mutex_unlock(&GC_lock); 

      DEBUG_MT(fprintf(output,"TId=%d: Starting doGC.\n", (int)ThreadId);
	       fflush(output);
	       )
      /* Now all other thread is sleeping */      
      /* (5) */
      newObj = doGC(numbytes);           

      DEBUG_MT(fprintf(output,"TId=%d: GC completed.\n", (int)ThreadId);
	       fflush(output);
	       )
      /* (6) */
      IOATop = gIOATop; /* size of object is already added in doGC */ 
      gIOATop = (long*)((long)gIOATop + reqsize-numbytes); /* size of slice */
      if (gIOALimit < gIOATop) {
	gIOATop = gIOALimit;
      }
      IOALimit =  gIOATop;
      /* (7) */
      DEBUG_MT(fprintf(output,"TId=%d: Broadcast on GCdone.\n", (int)ThreadId);
	       fflush(output);
	       )

      cond_broadcast(&cond_GCdone);
    } 
    else {
      DEBUG_MT(fprintf(output,"TId=%d: Increment and signal.\n", (int)ThreadId);
	       fflush(output);
	       )
      numReadyToGC++;
      cond_signal(&cond_startGC);
      DEBUG_MT(fprintf(output,"TId=%d: UNLock ioa_lock.\n", (int)ThreadId);
	       fflush(output);
	       )
      mutex_unlock(&ioa_lock);

      DEBUG_MT(fprintf(output,"TId=%d: Wait for GC to complete.\n", (int)ThreadId);
	       fflush(output);
	       )
      mutex_lock(&cond_GCdone_lock);
      while (cond_wait(&cond_GCdone, &cond_GCdone_lock))
	;
      DEBUG_MT(fprintf(output,"TId=%d: Received GCdone.\n", (int)ThreadId);
	       fflush(output);
	       )
      /* Update All registers and TSD variables that might be invalid by now. */
      if (gIOALimit < (long*)((long)IOATop + reqsize)) {
	fprintf(output, "FATAL: Missing alloc in AOA");
	newObj = NULL;
      }
      else {
	/* There is room for my request, as
	 * max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ 
	 */
	newObj = AllocObjectAndSlice(numbytes, reqsize);
      }
      DEBUG_MT(fprintf(output,"TId=%d: Unlocking GCdone_lock\n", (int)ThreadId);
	       fflush(output);
	       )
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
