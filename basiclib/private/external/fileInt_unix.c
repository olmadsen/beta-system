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

#ifdef sparc
extern int utimes(char *file, struct timeval *tvp);
#endif

#if defined(linux)
#include <utime.h>
#endif

#include <malloc.h>

#ifdef sun
#define BSIZE MAXBSIZE
#endif

#ifdef linux
#define BSIZE BUFSIZ
#endif

#ifdef sgi
#define BSIZE BBSIZE
#endif

#ifdef hpux
#define SYSV
#endif


int entryStatus(path,status,follow)
/* In essence an "lstat" call on the entry with absolute path, path.
 * The status of the entry is passed on to Beta by means of the
 * two buffers, status and permission. A return of -1 indicates
 * an error in the stat call, whereas a return of 1 means succes.
 */
     char *path;       /* IN par. The path of the entry to be stat'ed */
     int  *status;     /* OUT par. The buffer must be allocated by Beta. */
     int follow;       /* follow links ? */
{
  int entryType;
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0 ) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0 ) 
      return -1;
  }
  
  /* fill in the status buffer */
  status[0]=(int) statBuffer.st_dev;
  status[1]=(int) statBuffer.st_ino;
  
  /* The type of the entry */
  entryType=statBuffer.st_mode & S_IFMT;
  status[2]=( S_IFDIR  == entryType ) ? 1 : 0;
  status[3]=( S_IFCHR  == entryType ) ? 1 : 0;
  status[4]=( S_IFBLK  == entryType ) ? 1 : 0;
  status[5]=( S_IFREG  == entryType ) ? 1 : 0;
  status[6]=( S_IFLNK  == entryType ) ? 1 : 0;
  status[7]=( S_IFSOCK == entryType ) ? 1 : 0;
  /* status[8]=0; /* currently not used */
  /* status[9]=0; /* currently not used */
  status[10]=(int) statBuffer.st_nlink;
  status[11]=(int) statBuffer.st_uid;
  status[12]=(int) statBuffer.st_gid;
  status[13]=(int) statBuffer.st_rdev;
  status[14]=(int) statBuffer.st_size;
  status[15]=(int) statBuffer.st_atime;
  status[16]=(int) statBuffer.st_mtime;
  status[17]=(int) statBuffer.st_ctime;
  status[18]=(int) statBuffer.st_blksize;
  status[19]=(int) statBuffer.st_blocks;
  
  return 1;
} 

/* Constants giving the mode in which files are opened */ 

int readMode()
{
  return O_RDONLY;
}

int readWriteCreateMode()
{
  return O_RDWR | O_CREAT;
}

int writeCreateMode()
{
  return O_WRONLY | O_CREAT | O_TRUNC;
}

int appendCreateMode()
{
  return O_WRONLY | O_CREAT | O_APPEND;
}

int readAppendCreateMode()
{
  return O_WRONLY | O_CREAT | O_APPEND;
}

/* Constants giving the permission attached files that are created
 * in an open call.
 */

int noExecPerm()
     /* This constant gives write/read permission to all.
      * Note that "open" will clear bits in this mode
      * as specified in "umask".
      */
{
  return S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
}

int execPerm()
     /* This constant gives write/read/exec permission to all.
      * Note that "open" will clear bits in this mode
      * as specified in "umask".
      */
{
  return S_IRWXU | S_IRWXG | S_IRWXO;
}

#ifndef linux
int EOFpeek(str)
     FILE *str;
{
  /* A dirty and possibly highly machine dependent way of testing for
     EOF. The problem is that the end of a Beta stream is encountered
     when the NEXT char is EOF. It is then necessary to peek into
     the FILE buffer to see if the next char to be read is the EOF
     char. One (obvious) way to do that is to just read the next char
     and then ungetc it back to the stream. The problem with that 
     approach is however that ungetc may provoke deletion of a char 
     if the next opeartion on the stream is fseek. So instead the 
     char is written back by direct manipulation of the FILE buffer.
     _cnt denotes the number of chars left in the buffer and _ptr
     is a pointer into the buffer.
     */
  if(getc(str)==EOF)
    return 1;
  else
    {str->_cnt++;
    str->_ptr--;
    return 0;
    }
}
#else
/* Too dirty for linux !! */
int EOFpeek(str)
     FILE *str;
{
  int ch;
  if((ch=getc(str))==EOF){
    return 1;
  } else {
    ungetc(ch,str);
    return 0;
  }
}
#endif


int touchEntry(path)
     char *path;
{
  if((char)(*path)=='\0')
    return -1;                  /* test for empty string */
#ifdef SYSV
  if(utime(path,NULL)<0) return -1;
#else
  if(utimes(path,NULL)<0) return -1;
#endif
  return 0;
}

int isEntryDir(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0 ) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0 ) 
      return -1;
  }
  /* The type of the entry */
  return (statBuffer.st_mode & S_IFMT) == S_IFDIR;
} 

int isEntryFile(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0 ) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0 ) 
      return -1;
  }
  /* The type of the entry */
  return (statBuffer.st_mode & S_IFMT) == S_IFREG;
} 

int getEntrySize(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_size;
} 

int getEntryModtime(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_mtime;
} 


int setEntryModtime(path, time)
     char *path;
     time_t time;
{
  if((char)(*path)=='\0')
    return -1;                  /* test for empty string */
#if defined(SYSV)
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


int renameUnixEntry(old,new)
     char *old,*new;
{
  if( ((char)(*old)=='\0') || ((char)(*new)=='\0') )
    return -1;                  /* test for empty string */
  if(rename(old,new)<0)
    if (errno==EXDEV){
      /* cross device link: try copy instead */
      int s1, s2;
      signed char x;
      struct stat oldstat; 
      if (stat(old,&oldstat)<0) return -1;
      s1 = open(old, O_RDONLY);
      if(s1 < 0) return -1;
      
      s2 = open(new, O_RDWR | O_TRUNC | O_CREAT, oldstat.st_mode & 0777);
      if(s2 < 0) return -1;
      for(;;) {
        char buf[BSIZE];
        x = read(s1, buf, BSIZE);
        if(x == 0) break;
        if(x < 0) return -1;
        if(write(s2, buf, x) < 0) return -1;
      }
      (void)close(s1); 
        (void)close(s2);
        if(unlink(old) < 0) return -1;
    } else {
      return -1;
    }
  return 1;
}

int chownUnixEntry(path, owner, group)
     char *path;
     int owner;
     int group;
{
  if( ((char)(*path)=='\0') )
    return -1;                  /* test for empty string */
  if(chown(path,owner,group)<0)
    return -1;
  return 1;
}

int entryExists(path, follow)
     char *path;
     int follow;
{
  struct stat statBuffer;
  if((char)(*path)=='\0')
    return -1;                  /* test for empty string */
  if (follow){
    if( access(path,F_OK)<0) return 0;
    return 1;
  } else {
    if ( (lstat(path, &statBuffer)) == 0) return 1;
    if (errno==ENOENT) return 0;
    return -1;
  }
}

int deleteUnixFile(path)
     char *path;
{
  if((char)(*path) == '\0')
    return 0;                   /* test for empty string */
  if((unlink(path))<0){
    return -1;
  }
  return 1;
}

int createUnixFile(path)
     char *path;
{int fd;
if((char)(*path)=='\0')
  return 0;                     /* test for empty string */
if((fd=open(path,O_CREAT,0666))<0)
  return -1;
if(close(fd)<0)
  return -1;
return 1;
}

int changeProtection(path,protection)
     char *path;
     int *protection;
     /* The mode of the entry denoted by the full path name, path, is 
        is changed according to the supplied protection buffer, protection.
        The buffer is an array of 9 integers (each 1 or 0). The first 3 are 
        related to the mode for the "other" category, the next 3 give the mode
        for "group" and the last 3 denote the mode of "owner". The integers 
        should be inetrpreted as follows :
        
        |other                |group                |owner
        -----------------------------------------------------------------
        protection :exec | write | read  | exec | write | read | exec | write | read
        ---------------------------------------------------------------
        
        If for example the (other,exec) integer is 1, the "other" category are
        given execute permission to the entry.
        */
{ register i,mask=0;

for(i=0;i<9;i++)
  if(protection[i]) 
    mask = mask | ( 1 << i);
if(chmod(path,mask)<0) 
  return -1;
return 1;
}


int makeSymLink(src, dst)
     char *src;
     char *dst;
     /* Make src point to dst. exits -1 if an error occurred */
{
  return symlink(dst, src);
}

