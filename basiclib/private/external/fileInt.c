#ifndef MAC
#ifndef nti

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

#if defined(linux) || defined(nti)
#include <utime.h>
#endif

#ifdef apollo
#define S_IRUSR 0000400         /* read permission, owner */
#define S_IWUSR 0000200         /* write permission, owner */
#define S_IXUSR 0000100         /* execute/search permission, owner */
#define S_IRGRP 0000040         /* read permission, group */
#define S_IWGRP 0000020         /* write permission, grougroup */
#define S_IXGRP 0000010         /* execute/search permission, group */
#define S_IROTH 0000004         /* read permission, other */
#define S_IWOTH 0000002         /* write permission, other */
#define S_IXOTH 0000001         /* execute/search permission, other */
#define S_ENFMT 0000000         /* enforcement-mode locking not implemented */

extern  char    *malloc();
extern  char    *realloc();
#else
#include <malloc.h>
#endif

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

struct stat statBuffer;        /* used for all calls to stat */

int entryStatus(path,status,permission,follow)
     char *path;       /* IN par. denoting the path of the entry to be statted */
     int  *status;     /* OUT par. The buffer must be allocated by Beta. */
     int  *permission; /* OUT par. ---------------||-------------------- */ 
     /* In essence an "lstat" call on the entry with absolute path, path.
        The status of the entry is passed on to Beta by means of the
        two buffers, status and permission. A return of -1 indicates
        an error in the stat call, whereas a return of 1 means succes.
        */
     int follow; /* follow links ? */
{ int entryType;
  
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
  
/* The mode of the entry denoted by the full path name, path, is 
   is changed according to the supplied permission buffer.
   The buffer is an array of 9 integers (each 1 or 0). The first 3 are 
   related to the mode for the "other" category, the next 3 give the mode
   for "group" and the last 3 denote the mode of "owner". The integers 
   should be inetrpreted as follows :
     
   |other                |group                |owner
   -----------------------------------------------------------------
   protection :exec | write | read  | exec | write | read | exec | write | read
   -----------------------------------------------------------------
     
   If for example the (other,exec) integer is 1, the "other" category are
   given execute permission to the entry.
   */
  
/* fill in the permission buffer */
permission[0]=( S_IXOTH & statBuffer.st_mode ) ? 1 : 0;
permission[1]=( S_IWOTH & statBuffer.st_mode ) ? 1 : 0;
permission[2]=( S_IROTH & statBuffer.st_mode ) ? 1 : 0;
permission[3]=( S_IXGRP & statBuffer.st_mode ) ? 1 : 0;
permission[4]=( S_IWGRP & statBuffer.st_mode ) ? 1 : 0;
permission[5]=( S_IRGRP & statBuffer.st_mode ) ? 1 : 0;
permission[6]=( S_IXUSR & statBuffer.st_mode ) ? 1 : 0;
permission[7]=( S_IWUSR & statBuffer.st_mode ) ? 1 : 0;
permission[8]=( S_IRUSR & statBuffer.st_mode ) ? 1 : 0;
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

#ifdef nti
int renameNtEntry(old,new)
#else
     int renameUnixEntry(old,new)
#endif
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

#ifdef nti
int chownNtEntry(path, owner, group)
#else
     int chownUnixEntry(path, owner, group)
#endif
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

#ifdef nti
int deleteNtFile(path)
#else
     int deleteUnixFile(path)
#endif
     char *path;
{
  if((char)(*path) == '\0')
    return 0;                   /* test for empty string */
  if((unlink(path))<0){
    return -1;
  }
  return 1;
}

#ifdef nti
int createNtFile(path)
#else
     int createUnixFile(path)
#endif
     char *path;
{int fd;
if((char)(*path)=='\0')
  return 0;                     /* test for empty string */
if((fd=open(path,O_CREAT,0644))<0)
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

#else

/********** WINDOWS NT INTERFACE ************/

#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <io.h>
#ifdef nti_bor
#include <utime.h>
#else
#include <sys/utime.h>
#define S_IXUSR _S_IEXEC
#define S_IWUSR _S_IWRITE
#define S_IRUSR _S_IREAD
#define S_IFBLK (-1) /* ??? */
#define ENOTSAM EXDEV
#endif

#include <malloc.h>

#define BSIZE BUFSIZ

/* Return NT variable errno */
int getErrno()
{
  return errno;
}

/* This function will try to determine whether a text file really is
 * a text file. Used like this... Change
 *   fopen(name, text ? "rt" : "rb");
 * To
 *   fopen(name, text && textfile_is_text(name) ? "rt" : "rb");
 */
int textfile_is_text(char *name)
{
  FILE *f=fopen(name,"rb");
  if (f) {
    char *buf = malloc(512);
    int size=fread(buf,1,512,f);
    int i;
    fclose(f);
    for (i = 1; i < size; i++)
      if (buf[i] == '\n') {
        free(buf);
        return buf[i-1] == '\r';
      }
    free(buf);
  }
  return 1;
}

struct stat statBuffer;        /* used for all calls to stat */

int entryStatus(path,status,permission,follow)
     char *path;       /* IN par. denoting the path of the entry to be statted */
     int  *status;     /* OUT par. The buffer must be allocated by Beta. */
     int  *permission; /* OUT par. ---------------||-------------------- */ 
     /* In essence an "lstat" call on the entry with absolute path, path.
        The status of the entry is passed on to Beta by means of the
        two buffers, status and permission. A return of -1 indicates
        an error in the stat call, whereas a return of 1 means succes.
        */
     int follow; /* follow links ? Ignored by Windows NT*/
{ int entryType;
  
if (stat(path,&statBuffer)<0 ) 
  return -1;
  
/* fill in the status buffer */
status[0]=(int) statBuffer.st_dev;
status[1]=(int) statBuffer.st_ino;
  
/* The type of the entry */
entryType=statBuffer.st_mode & S_IFMT;
status[2]=( S_IFDIR  == entryType ) ? 1 : 0;
status[3]=( S_IFCHR  == entryType ) ? 1 : 0;
status[4]=( S_IFBLK  == entryType ) ? 1 : 0;
status[5]=( S_IFREG  == entryType || !entryType) ? 1 : 0;
/* status[6]=0; /* currently not used */
/* status[7]=0; /* currently not used */
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
/* status[18]= /* currently not used */
/* status[19]= /* currently not used */
  
/* The mode of the entry denoted by the full path name, path, is 
   is changed according to the supplied permission buffer.
   The buffer is an array of 9 integers (each 1 or 0). The first 3 are 
   related to the mode for the "other" category, the next 3 give the mode
   for "group" and the last 3 denote the mode of "owner". The integers 
   should be inetrpreted as follows :
     
   |other                |group                |owner
   -----------------------------------------------------------------
   protection :exec | write | read  | exec | write | read | exec | write | read
   -----------------------------------------------------------------
     
   If for example the (other,exec) integer is 1, the "other" category are
   given execute permission to the entry.
   */
  
/* fill in the permission buffer */
/* permission[0] * currently not used */
/* permission[1] * currently not used */
/* permission[2] * currently not used */
/* permission[3] * currently not used */
/* permission[4] * currently not used */
/* permission[5] * currently not used */
permission[6]=( S_IXUSR & statBuffer.st_mode ) ? 1 : 0;
permission[7]=( S_IWUSR & statBuffer.st_mode ) ? 1 : 0;
permission[8]=( S_IRUSR & statBuffer.st_mode ) ? 1 : 0;
return 1;
} 

/* Constants giving the mode in which files are opened */ 

int readMode(int binary)
{
  return O_RDONLY | (binary ? O_BINARY : O_TEXT);
}
     
int readWriteCreateMode(int binary)
{
  return O_RDWR | O_CREAT | (binary ? O_BINARY : O_TEXT);
}
     
int writeCreateMode(int binary)
{
  return O_WRONLY | O_CREAT | O_TRUNC | (binary ? O_BINARY : O_TEXT);
}
     
int appendCreateMode(int binary)
{
  return O_WRONLY | O_CREAT | O_APPEND | (binary ? O_BINARY : O_TEXT);
}
     
int readAppendCreateMode(int binary)
{
  return O_WRONLY | O_CREAT | O_APPEND | (binary ? O_BINARY : O_TEXT);
}
     
/* Constants giving the permission attached files that are created
 * in an open call.
 */
     
/* This constant gives write/read permission to owner and
 * read permission to group and others.
 */
int noExecPerm()
{
  return S_IREAD|S_IWRITE;
}

/* Also read/write to owner and read to other and group, but
 * in addition all three categories have execution permission.
 */
int execPerm()
{
  return S_IREAD|S_IWRITE|S_IEXEC;
}

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


int touchEntry(path)
     char *path;
{
  if((char)(*path)=='\0')
    return 0;                      /* test for empty string */
  if(utime(path,NULL)<0)
    return -1;
}

int setEntryModtime(path, time)
     char *path;
     time_t time;
{
  if((char)(*path)=='\0')
    return -1;                  /* test for empty string */
  {
    struct utimbuf times;
    times.actime=times.modtime=time;
    if(utime(path,&times)<0) return -1;
  }
  return 0;
}

int renameNtEntry(old,new)
     char *old,*new;
{
  if( ((char)(*old)=='\0') || ((char)(*new)=='\0') )
    return -1;                      /* test for empty string */
  if(rename(old,new)<0)
    if (errno==ENOTSAM){
      /* cross device link: try copy instead */
      int s1, s2;
      int x;
      struct stat oldstat; 
      if (stat(old,&oldstat)<0) return -1;
      s1 = open(old, O_RDONLY);
      if(s1 < 0) return -1;
      
      s2 = open(new, O_RDWR | O_TRUNC | O_CREAT | O_BINARY, oldstat.st_mode & 0777);
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

int chownNtEntry(path, owner, group)
     char *path;
     int owner;
     int group;
{
  return -1;
}

#define F_OK (00)
#define X_OK (01)
#define W_OK (02)
#define R_OK (04)

int entryExists(path, follow)
     char *path;
     int follow;
{
  if((char)(*path)=='\0')
    return -1;                     /* test for empty string */
  if( access(path,F_OK)<0) return 0;
  return 1;
}

int deleteNtFile(path)
     char *path;
{
  if((char)(*path) == '\0')
    return 0;                   /* test for empty string */
  if((unlink(path))<0){
    return -1;
  }
  return 1;
}

int createNtFile(path)
     char *path;
{int fd;
if((char)(*path)=='\0')
  return 0;                   /* test for empty string */
if((fd=open(path,O_CREAT,S_IREAD|S_IWRITE))<0)
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
        protection :exec | write | read  | exec | write | read | exec | write |read
        ---------------------------------------------------------------
        
        If for example the (other,exec) integer is 1, the "other" category are
        given execute permission to the entry.
        */
{ register i,mask=0;
  
for(i=6;i<9;i++)
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
  return -1;
}

#endif

#else

/********** MAC INTERFACE ************/

#include <types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdLib.h>
#include <memory.h>
#include <Files.h>
#include <Errors.h>
#include <Packages.h>
#include <OSUtils.h>

/***** Return variable errno *************/

int getErrno()
     
{
  return errno;}

/* Return information about constants that are defined in the
   header files. Such constants may have different values on
   different operating systems
   */

/* Constants giving the mode in which files are opened */ 

int readMode(){
  return O_RDONLY;}
     
int readWriteCreateMode(){
  return O_RDWR | O_CREAT;}
     
int writeCreateMode(){
  return O_WRONLY | O_CREAT | O_TRUNC;}
     
int appendCreateMode(){
  return O_WRONLY | O_CREAT | O_APPEND;}
     
int readAppendCreateMode(){
  return O_WRONLY | O_CREAT | O_APPEND;} 
     
     
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
    {
      str->_cnt++;
      str->_ptr--;
      return 0;
    }
}

int EOFvalue() {
  return EOF; }
     
int EOFfunction(FILE *F) {
  return feof(F); }
     
     
/* ----------------- Functions supporting Stream.GetText -------------------- */
     
static char *OutOfMemError="Out of memory during StreamGetText\n";
     
#define INITBUFFERSIZE  500   /* Initial size of Buffer. */
     
static char *Buffer;          /* Nuffer space allocate here. */
static int  BufferSize=0;     /* Current size of Buffer. */
     
     
void InitBuffer()
{
  BufferSize=INITBUFFERSIZE;
  Buffer=(char *)malloc(BufferSize);
  if(!Buffer)
    {
      fputs(OutOfMemError,stderr);
      exit(147);
    }
}


void EnlargeBuffer()
     /* Double the size of Buffer or allocate an initial Buffer. */
{
  BufferSize*=2;
  Buffer=realloc(Buffer,BufferSize);
  if(!Buffer)
    {
      fputs(OutOfMemError,stderr);
      exit(147);
    }
}


static char streamStatus;


int StreamError()
     /* Return whether or not last call to GetTExtFromStream succeeded. */
{
  return(streamStatus==EOF);
}


char *GetTextFromStream(F,toEOL)
     /* Read a string from the file. If toEOL is true then read to end of line,
        else read to first space. Skip the character (eol or space) that causes
        reading to stop.
        Call StreamError afterwards to see if operation succeeded.
        */
     FILE *F;
     int  toEOL;
{
  register FILE *F1;            /* We use a lot of registers for efficiency. */
  register char *Buffer1;
  register int  i,ch;
  int           oldSize;
  
  if(!BufferSize)               /* The first time, initialize Buffer. */
    InitBuffer();
  F1=F;
  oldSize=0;                    /* This much of Buffer currently used. */
  if(!toEOL)                    /* Skip to first non-blank. */
    {
      while((ch=getc(F1))<=' ' && ch!=EOF) 
        /* SKIP */ ;
      if(ch==EOF || ungetc(ch,F1)==EOF)
        {
          streamStatus=ch;
          return("");
        }
    }
  while(1)
    {
      Buffer1=Buffer+oldSize;   /* Insert from this place in Buffer. */
      i=BufferSize-oldSize;
      if(toEOL)                 /* We have two almost identical copies of the
                                   inner loop, one reading to eol the other to
                                   a blank.
                                   */
        {
          while(i--)            /* While more room in Buffer. */
            {
              if((*Buffer1++=ch=getc(F1))=='\n' || ch==EOF)
                {
                  streamStatus=ch;
                  Buffer1[-1]=0; /* Skip the stop char. */
                  return(Buffer);
                }
            }
        }
      else
        {
          while(i--)            /* While more room in Buffer. */
            {
              if((*Buffer1++=ch=getc(F1))<=' ' || ch==EOF)
                {
                  streamStatus=ch;
                  Buffer1[-1]=0; /* Skip the stop char. */
                  return(Buffer);
                }
            }
        }
      oldSize=BufferSize;
      EnlargeBuffer();
    }
}

#define longint long

/**************** pStrcat / pStrCpy *************************************
 *
 *     A couple of utility routines. C is thoughtless enough to not really 
 *     support P-strings. In order to perform string copies and concatenations,
 *     these routines are provided.
 *
 ************************************************************************/

char *pStrcat(s,t)
     unsigned char *s, *t;
{
  BlockMove(t + 1, s + *s + 1, (longint) *t);
  *s += *t;
  return (s);
}

char *pStrcpy(s,t)
     unsigned char *s, *t;
{
  BlockMove(t, s, (longint) *t + 1); 
  return (s);
}

short GetEntryInfo(char *name, CInfoPBPtr block)
{
  short vRefNum;
  Str255 volName;
  WDPBRec       myBlock;
  
  if (getvol(&volName , &vRefNum) != noErr) return -1;
  myBlock.ioNamePtr = nil;
  myBlock.ioVRefNum = vRefNum;
  myBlock.ioWDIndex = 0;
  myBlock.ioWDProcID = 0;
  PBGetWDInfo(&myBlock,false);
  
  c2pstr(name);
  block->dirInfo.ioNamePtr = name;
  block->dirInfo.ioDrDirID = myBlock.ioWDDirID;
  block->dirInfo.ioVRefNum = myBlock.ioWDVRefNum;
  block->dirInfo.ioFDirIndex = 0;
  
  return PBGetCatInfo(block,false);
}
long isDir(char *name)
{
  short err; 
  CInfoPBRec    block;
  err = GetEntryInfo(name,&block);
  if (err == noErr) {
    if (block.dirInfo.ioFlAttrib & 16) return 1; else return 0;
  } else {
    return err;
  }
}

long isLocked(char *name)
{
  short err;
  CInfoPBRec    block;
  err = GetEntryInfo(name,&block);
  if (err == noErr) {
    if (block.dirInfo.ioFlAttrib & 1) return 1; else return 0;
  } else {
    return err;
  }
}

long entryExists(char *name)
{
  short err;
  CInfoPBRec    block;
  err = GetEntryInfo(name,&block);
  switch (err) {
  case noErr:    return 1;
  case fnfErr:
  case dirNFErr: return 0;
  default:       return err;
  }
}

long getmodtime(char *name)
{
  short err;
  CInfoPBRec    block;
  unsigned long time;
  err = GetEntryInfo(name,&block);
  if (err==noErr) {
    if (block.dirInfo.ioFlAttrib & 16) {
      /* it's a directory */
      time= block.dirInfo.ioDrMdDat;
    } else {
      /* it's a file  */
      time= block.hFileInfo.ioFlMdDat;
    }
    return time & ~(1<<31);
  } else {
    errno=err;
    return -1;
  }
}

void getdatestring(long time, Str255 pstr)
{   
  Str255 secsStr;
  time=time | (1<<31);  /* to make a time from modtime correct */
  IUDateString(time,1,pstr);  /* 1 is long format  */
  IUTimeString(time,true,secsStr); /* get hours, minutes, and seconds */
  pStrcat(pstr,"\p ");
  pStrcat(pstr,secsStr);
}

int setEntryModtime(char *name, unsigned long secs)
{
  short err;
  CInfoPBRec block;
  short vRefNum;
  Str255 volName;
  WDPBRec myBlock;
        
  if (getvol(&volName , &vRefNum) != noErr) return -1;
  myBlock.ioNamePtr = nil;
  myBlock.ioVRefNum = vRefNum;
  myBlock.ioWDIndex = 0;
  myBlock.ioWDProcID = 0;
  PBGetWDInfo(&myBlock,false);
  c2pstr(name);
  block.dirInfo.ioNamePtr = name;
  block.dirInfo.ioDrDirID = myBlock.ioWDDirID;
  block.dirInfo.ioVRefNum = myBlock.ioWDVRefNum;
  block.dirInfo.ioFDirIndex = 0;
        
  err= PBGetCatInfo(&block,false);
  if (err==noErr) {
    if (block.dirInfo.ioFlAttrib & 16) {
      /* it's a directory */
      block.dirInfo.ioDrMdDat=secs;
    } else {
      /* it's a file */
      block.hFileInfo.ioFlMdDat=secs;
    }
    block.dirInfo.ioDrDirID = 0; /* we got the path in ioNamePtr */
    block.dirInfo.ioVRefNum = 0;
    block.dirInfo.ioFDirIndex = 0;
    err=PBSetCatInfo(&block,false);
    if (err!=noErr) {
      errno=err;
      return 0; 
    } else 
      return 1;
  } else {
    errno=err;
    return 0;
  }
}

long entryTouch(char *name)
{       
  unsigned long secs;
  GetDateTime(&secs);
  return setEntryModtime(name, secs);
}

long entryRename(char *name, char *newname)
{
  short err;
  HParamBlockRec block;
  short vRefNum;
  Str255 volName;
  WDPBRec myBlock;
        
  if (getvol(&volName , &vRefNum) != noErr) return -1;
  myBlock.ioNamePtr = nil;
  myBlock.ioVRefNum = vRefNum;
  myBlock.ioWDIndex = 0;
  myBlock.ioWDProcID = 0;
  PBGetWDInfo(&myBlock,false);
  c2pstr(name);
  block.ioParam.ioNamePtr = name;
  block.fileParam.ioDirID = myBlock.ioWDDirID;
  block.ioParam.ioVRefNum = myBlock.ioWDVRefNum;
  c2pstr(newname);
  block.ioParam.ioMisc = newname;
  err= PBHRename(&block,false);
  if (err=noErr) {
    return 1;
  } else {
    errno=err;
    printf("rename failed: %d\n",err);
    return -11;
  }
}

#endif 
