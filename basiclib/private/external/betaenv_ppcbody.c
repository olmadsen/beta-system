#include <types.h>
#include <memory.h>
#include <QuickDraw.h>

extern long StandAlone;

getStandAlone()
{
  return (StandAlone);
}

Ptr getqd()
{
  return (Ptr)(&qd);
}

unsigned char *pStrcat(s,t)
     unsigned char *s, *t;
{
  BlockMove(t + 1, s + *s + 1, (long) *t);
  *s += *t;
  return (s);
}

unsigned char *pStrcpy(s,t)
     unsigned char *s, *t;
{
  BlockMove(t, s, (long) *t + 1); 
  return (s);
}

