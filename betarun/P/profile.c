#include "beta.h"

void profile_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

#include <errno.h>
#include <ucontext.h>
#include <signal.h>
#include <siginfo.h>
#include <sys/regset.h>
#include <string.h>
#include <stdlib.h>

#include "profile.h"

/* LOCAL FUNCTION DECLARATION */

static void AlarmHandler(long sig, siginfo_t *info, ucontext_t *ucon);
static void SetupVirtualTimerHandler(void);
static void SetupVirtualTimer(unsigned usec);

/* LOCAL VARIABLES */
static u_long inHandler;
u_long isSim = UNKNOWN;
u_long ticks[MAXTICKS];

char *tickNames[] = {
  "UNKNOWN",
  "LOOKUPREFERENCEENTRY",
  "CREATECROSSSTORETABLE",
  "SAVECURRENTCROSSSTORETABLE",
  "SETCURRENTCROSSSTORETABLE",
  "NEWSTOREPROXY",
  "LOOKUPSTOREPROXY",
  "CREATEOBJECTSTORE",
  "SAVECURRENTOBJECTSTORE",
  "SETCURRENTOBJECTSTORE",
  "NEWSTOREOBJECT",
  "LOOKUPSTOREOBJECT",
  "SETSTOREOBJECT",
  "LOADOBJECT",
  "MAXTICKS"

};

/* FUNCTION DEFINITIONS */
static void AlarmHandler(long sig, siginfo_t *info, ucontext_t *ucon)
{
  /* Do your thing, but do it quickly */
    
  if (!inHandler) {
        
    inHandler = 1;
        
    if (isSim < MAXTICKS) {
      ticks[isSim]++;
    } else {
      ticks[UNKNOWN]++;
    }
    inHandler = 0;
  } else {
    Claim(FALSE, "AlarmHandler reentered\n");
  }
}

static void SetupVirtualTimerHandler()
{
  struct sigaction sa;
  
  /* Specify that we want full info about the signal */
  sa.sa_flags = SA_SIGINFO;
  
  /* No further signals should be blocked while handling the specified
   * signals. */
  sigemptyset(&sa.sa_mask); 
  
  /* the handler */
  sa.sa_handler = AlarmHandler; 
  
  if (sigaction(SIGVTALRM, &sa, NULL)) {
    perror("SetupVirtualTimerHandler");
    Claim(FALSE, "Error during profiling\n");
  }
}

static void SetupVirtualTimer(unsigned usec)
{
  struct itimerval interval;

  /* setup timer to trigger each usec microseconds */
  interval.it_value.tv_sec = 0;
  interval.it_value.tv_usec = usec;
  interval.it_interval.tv_sec = 0;
  interval.it_interval.tv_usec = usec;
  
  if (setitimer(ITIMER_VIRTUAL, &interval, NULL)) {
    perror("SetupVirtualTimer");
    Claim(FALSE, "Error during profiling\n");
  }  
}

void start_vtimer(void)
{
    SetupVirtualTimer(1000);
    SetupVirtualTimerHandler();
    inHandler = 0;
    memset(ticks, 0, sizeof(u_long)*MAXTICKS);
}

void show_vtimer(void)
{
    u_long totalticks;
    u_long count;

    totalticks = 0;
    for (count = 0; count < MAXTICKS; count++) {
        totalticks += ticks[count];
    }
    
    if (totalticks == 0) {
        totalticks = 1;
    }
        
    fprintf(output, "[VTimer profile:\n");
    for (count = 0; count < MAXTICKS; count++) {
        char *s = (char *)calloc(16, sizeof(char));
        u_long c;
        double percent;
        
        percent = (double)ticks[count] * 100.0 / (double)totalticks;
        if (percent > 0.009) {
            memset(s, ' ', 15);
            
            for(c=0;(c<strlen(tickNames[count])) && c < 15;c++) {
                s[c] = tickNames[count][c];
            }
            
            fprintf(output, " %s : %d (%f%%)\n",
		    s,
		    (int)ticks[count],
		    percent);
        }
        free(s);
    }
    fprintf(output, "]\n");
}

#endif /* PERSIST */
