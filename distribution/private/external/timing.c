#ifdef sun4s
#include <sys/time.h>
#include <stdio.h>

static hrtime_t lastTime[10];
static hrtime_t accumTime[10];

void timing_reset ()
{ int i;
  for (i = 0; i < 10; i++)
    accumTime[i] = 0;
}

void timing_before (int category)
{
  lastTime[category] = gethrtime();
}

void timing_after (int category)
{
  accumTime[category] += (gethrtime() - lastTime[category]);
}

void timing_printTimes ()
{ int i;
  
  for (i = 0; i < 10; i++)
    printf ("Total time in category %d: %lld\n", i, accumTime[i]);
}

#else
void timing_reset ()
{ 
}

void timing_before (int category)
{
}

void timing_after (int category)
{
}

void timing_printTimes ()
{ 
}

#endif
