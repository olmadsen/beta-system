#include <types.h>
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

