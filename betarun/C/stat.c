/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * by Lars Bak
 */
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

/* Routines to make statistic for the garbagecollector.
 * There are 4 checkpoints during the program execution.
 * 1. At program start:                    StatRecordStart
 * 2. At beginning of a garbagecollection: StatRecordLabA
 * 3. At end of a garbagecollection:       StatRecordLabB
 * 4. At end of the program execution:     StatRecordEnd
 * The call sequenze of the StatRecord routines should be:
 *   Start { LabA LabB }* End
 */

struct TimeStamp {
  struct timeval utime;      /* user time used */
  struct timeval stime;      /* system time used */
  int            minflt;     /* Page faults without I/O */
  int            majflt;     /* Page faults with I/O */
};

GLOBAL(static struct TimeStamp  labTime, startTime);

GLOBAL(static struct TimeStamp BetaTime, GCTime, AllTime);

static ZeroTime( theTime )
     struct TimeStamp *theTime;
{ 
  theTime->utime.tv_sec = 0; theTime->utime.tv_usec = 0;
  theTime->stime.tv_sec = 0; theTime->stime.tv_usec = 0;
  theTime->minflt = 0;
  theTime->majflt = 0;
}

static SetTime( theTime )
     struct TimeStamp *theTime;
{ struct rusage tmp_rusage;

  getrusage( RUSAGE_SELF, &tmp_rusage );
  theTime->utime = tmp_rusage.ru_utime;
  theTime->stime = tmp_rusage.ru_stime;
  theTime->minflt = tmp_rusage.ru_minflt;
  theTime->majflt = tmp_rusage.ru_majflt;
}


static timevalInterval( a,b,c)
     struct timeval *a, *b, *c;
{
  if( a->tv_sec >= b->tv_sec ) c->tv_sec = 0;
  else c ->tv_sec = b->tv_sec - a->tv_sec;

  if( a->tv_usec >= b->tv_usec ){
    if( c->tv_sec == 0 ) c->tv_usec = 0;
    else{
      c->tv_sec--;
      c->tv_usec = 1000000 - a->tv_usec + b->tv_usec;
    }
  }else{
    c->tv_usec = b->tv_usec - a->tv_usec;
  }
}

static TimeInterval( timeA, timeInt )
     struct TimeStamp *timeA, *timeInt;
     /* Compute the time between timeA and timeB and store 
      * the result in timeInt. */
{ struct TimeStamp timeB;

  SetTime( &timeB);

  timevalInterval( &timeA->utime, &timeB.utime, &timeInt->utime);
  timevalInterval( &timeA->stime, &timeB.stime, &timeInt->stime);
  timeInt->minflt = timeB.minflt - timeA->minflt;
  timeInt->majflt = timeB.majflt - timeA->majflt;

}

static timevalAdd( a,b)
     struct timeval *a, *b;
{
  b->tv_sec += a->tv_sec; b->tv_usec += a->tv_usec;
  if( b->tv_usec >= 1000000 ){ b->tv_sec++; b->tv_usec -= 1000000; }
}

static AddInterval( intA, intB)
     struct TimeStamp *intA, *intB;
     /* Add the interval intA to the interval intB. */
{
  timevalAdd( &intA->utime, &intB->utime);
  timevalAdd( &intA->stime, &intB->stime);
  intB->minflt += intA->minflt;
  intB->majflt += intA->majflt;
}

static int NumOfGC;

StatRecordStart()
{
  ZeroTime( &BetaTime);
  ZeroTime( &GCTime );
  ZeroTime( &AllTime );
  SetTime( &labTime);
  SetTime( &startTime);
  NumOfGC = 0;
}


StatRecordLabA()
{ struct TimeStamp theInterval;

  TimeInterval( &labTime, &theInterval);
  SetTime( &labTime);
  AddInterval( &theInterval,  &BetaTime);  
}

StatRecordLabB()
{ struct TimeStamp theInterval;

  TimeInterval( &labTime, &theInterval);
  SetTime( &labTime);
  AddInterval( &theInterval,  &GCTime);  

  NumOfGC++;
}

static printInterval( theInt )
     struct TimeStamp *theInt;
{
  fprintf(stderr,"user=%d,%02d  system=%d,%02d faults=(%d,%d)\n", 
         theInt->utime.tv_sec, theInt->utime.tv_usec / 10000,
	 theInt->stime.tv_sec, theInt->stime.tv_usec / 10000,
         theInt->minflt,       theInt->majflt );
}

StatRecordEnd()
{ struct TimeStamp theInterval;

  TimeInterval( &labTime, &theInterval);
  AddInterval( &theInterval,  &BetaTime);  

  TimeInterval( &startTime, &theInterval);

  fprintf(stderr,"--<InfoS>------------------------------\n");
  fprintf(stderr,"NumOfGC: %d \n", NumOfGC);
  fprintf(stderr,"Beta: "); printInterval( &BetaTime );
  fprintf(stderr,"IOA:  "); printInterval( &GCTime ); 
  fprintf(stderr,"All:  "); printInterval( &theInterval);
  fprintf(stderr,"--<InfoS>------------------------------\n");
}
