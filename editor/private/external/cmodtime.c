#include <sys/types.h>
#ifndef nti
#include <sys/file.h>
#endif
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#ifndef nti
#include <sys/param.h>
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef hpux
#define SYSV
#endif

#if defined(linux) || defined(nti)
#include <utime.h>
#endif


int setEntryModtime(path, time)
     char *path;
     time_t time;
{
  if((char)(*path)=='\0')
    return -1; 			   /* test for empty string */
#if defined(SYSV) || defined(nti)
  { struct utimbuf times;
    times.actime=times.modtime=time;
    if(utime(path,&times)<0) return -1;
  }
#else
  { struct timeval times[2];
    times[0].tv_sec = times[1].tv_sec = time;
    times[0].tv_usec = times[1].tv_usec = 0;
    if(utimes(path,times)<0) return -1;
  }
#endif
  return 0;
}
