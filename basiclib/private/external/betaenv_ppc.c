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

unsigned char *pStrcat(unsigned char *s,unsigned char *t)
{
  BlockMove(t + 1, s + *s + 1, (long) *t);
  *s += *t;
  return (s);
}

unsigned char *pStrcpy(unsigned char *s,unsigned char *t)
{
  BlockMove(t, s, (long) *t + 1); 
  return (s);
}

