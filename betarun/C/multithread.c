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
  unsigned lock;
  unsigned value;
  unsigned inGC;
};


/* synchronization variables */
mutex_t lvra_lock;
mutex_t aoa_lock;
mutex_t aoatoioa_lock;
mutex_t cbfa_lock;

void initSynchVariables(void)
{
  mutex_init(&lvra_lock, USYNC_THREAD, NULL);
  mutex_init(&aoa_lock,  USYNC_THREAD, NULL);
  mutex_init(&aoatoioa_lock,  USYNC_THREAD, NULL);
  mutex_init(&cbfa_lock, USYNC_THREAD, NULL);
}

void create_TSD(void)
{
  TSDreg = MALLOC(sizeof(TSD));
  if (!TSDReg){
    fprintf(output, "create_TSD failed for thread %d\n", thr_self());
    return;
  }
  MallocExhausted = 0;
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

int attToProcessor(struct Component *comp)
{
  return 0;
}

struct S_PreemptionLevel PreemptionLevel;

void SetupVirtualTimer(unsigned usec);
GLOBAL(int AlarmOccured) = 0;
void AlarmHandler(int sig, siginfo_t *sip, void *uap)
{
  AlarmOccured++;
  
  /* FIXME: should be a tryLock. */
  if (!PreemptionLevel.lock && !PreemptionLevel.value) { 
    if (!PreemptionLevel.inGC) { /* We cannot reset IOALimit while GC'ing */
      IOALimit = 0;
      DEBUG_MT(fprintf(output, "IOALimit=0x%x\n", (int)IOALimit));
    }
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
    printf("sigaction failed. Errno=%d (%s)\n", errno, strerror(errno));
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
    printf("setitimer failed. Errno=%d (%s)\n", errno, strerror(errno));
    BetaExit(1);
  }  
}

#endif /* MT */
