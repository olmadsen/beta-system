#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/param.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef hpux
#define SYSV
#endif

#ifdef linux
#include <utime.h>
#endif


int setEntryModtime(path, time)
     char *path;
     time_t time;
{
  if((char)(*path)=='\0')
    return -1; 			   /* test for empty string */
#ifdef SYSV
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
