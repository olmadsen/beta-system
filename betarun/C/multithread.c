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


/* synchronization variables */
mutex_t tsd_lock;
mutex_t ioa_lock;
mutex_t lvra_lock;
mutex_t aoa_lock;
mutex_t aoatoioa_lock;
mutex_t cbfa_lock;

void initSynchVariables(void)
{
  mutex_init(&tsd_lock, USYNC_THREAD, NULL);
  mutex_init(&ioa_lock, USYNC_THREAD, NULL);
  mutex_init(&lvra_lock, USYNC_THREAD, NULL);
  mutex_init(&aoa_lock,  USYNC_THREAD, NULL);
  mutex_init(&aoatoioa_lock,  USYNC_THREAD, NULL);
  mutex_init(&cbfa_lock, USYNC_THREAD, NULL);
}

long NumTSD=0;
TSD  **TSDlist=0;
long TSDlistlen=0;

void create_TSD(void)
{
  TSDReg = MALLOC(sizeof(TSD));
  if (!TSDReg){
    fprintf(output, "create_TSD failed for thread %d\n", thr_self());
    return;
  }
  ThreadId = thr_self();
  MallocExhausted = 0;
  IOALimit = NULL;
  IOATop = NULL;
  ActiveComponent = NULL;
  ActiveStack = NULL;

  /* insert newly created TSD into TSDlist */
  mutex_lock(&tsd_lock);
  NumTSD++;
  if (TSDlistlen < NumTSD){
    TSDlistlen += numProcessors(TRUE);
    TSDlist = REALLOC(TSDlist, TSDlistlen);
  }
  TSDlist[NumTSD] = TSDReg;
  mutex_unlock(&tsd_lock);
}

struct Object *doGC(unsigned numbytes);

struct Object *getNewIOASlice(unsigned long numbytes)
{
  /* Allocate an IOA slice. 
   * -Attempts to allocate max(numbytes,IOASliceSize) bytes.
   * -At least numbytes are allocated.
   *  A GC is triggered, if there is not room for max(numbytes,IOASliceSize).
   */

  struct Object *newObj;
  unsigned long reqsize = numbytes;

  mutex_lock(&ioa_lock);

  if (reqsize < IOASliceSize)
    reqsize = IOASliceSize;

  if (!IOATop) {
    /* IOATop is zero => this thread either has not had a slice yet,
     * or a GC has occured in another thread.  
     */
    IOATop = gIOATop;
  } 
  
  if (gIOALimit < (long*)((long)IOATop + reqsize)) {
    /* FIXME: Stop all other threads! */

    /* Force GC */
    newObj = doGC(numbytes);

    /* FIXME: Restart all threads. 
     * -They should set their IOALimit to 0, to make sure they 
     *  do not alloc in old heap 
     */

    IOATop = gIOATop; /* size of object is already added in doGC */ 
    gIOATop = (long*)((long)gIOATop + reqsize-numbytes); /* size of slice */
    if (gIOALimit < gIOATop) {
      gIOATop = gIOALimit;
    }
  } else {
    /* max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ */
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
  }

  IOALimit =  gIOATop;
  
  mutex_unlock(&ioa_lock);

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
		 THR_NEW_LWP|THR_DETACHED                   /* flags      */,
		 &tid                           /* id         */)){
    fprintf(output, "Failed to create thread for component 0x%x\n", (int)comp);
    fflush(output);
    exit (1);
  }
  DEBUG_MT(fprintf(output, 
		   "[Created thread 0x%x for comp 0x%x]\n", 
		   (int)tid, 
		   (int)comp);
	   fflush(output););
    
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

void SetupVirtualTimerHandler(unsigned usec)
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
  SetupVirtualTimer(usec);
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
