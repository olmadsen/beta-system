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

#ifdef sparc
extern int utimes(char *file, struct timeval *tvp);
#endif

#if defined(linux)
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
{
  int entryType;
  
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

{return errno;}

/* Return information about constants that are defined in the
   header files. Such constants may have different values on
   different operating systems
   */

/* Constants giving the mode in which files are opened */ 

int readMode(){return O_RDONLY;}

int readWriteCreateMode(){return O_RDWR | O_CREAT;}

int writeCreateMode(){return O_WRONLY | O_CREAT | O_TRUNC;}

int appendCreateMode(){return O_WRONLY | O_CREAT | O_APPEND;}

int readAppendCreateMode(){return O_WRONLY | O_CREAT | O_APPEND;} 


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

int EOFvalue() { return EOF; }

int EOFfunction(FILE *F) { return feof(F); }


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
  register FILE *F1;        /* We use a lot of registers for efficiency. */
  register char *Buffer1;
  register int  i,ch;
  int           oldSize;

  if(!BufferSize)            /* The first time, initialize Buffer. */
    InitBuffer();
  F1=F;
  oldSize=0;                 /* This much of Buffer currently used. */
  if(!toEOL)                 /* Skip to first non-blank. */
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
      Buffer1=Buffer+oldSize; /* Insert from this place in Buffer. */
      i=BufferSize-oldSize;
      if(toEOL)               /* We have two almost identical copies of the
                                 inner loop, one reading to eol the other to
                                 a blank.
				 */
        {
	  while(i--)           /* While more room in Buffer. */
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
	  while(i--)           /* While more room in Buffer. */
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

extern char *pStrcat(unsigned char *s, unsigned char *t);
extern char *pStrcpy(unsigned char *s, unsigned char *t);

short FSpIsDir(FSSpec *fs)
{
  short err; 
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr = fs->name;
  block.hFileInfo.ioVRefNum = fs->vRefNum;
  block.hFileInfo.ioDirID   = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) 
    if (block.dirInfo.ioFlAttrib & 16) return 1; else return 0;
  else return err;
}

long FSpGetDirID(FSSpec *fs)
{
  short err;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr = fs->name;
  block.hFileInfo.ioVRefNum = fs->vRefNum;
  block.hFileInfo.ioDirID   = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    return block.dirInfo.ioDrDirID;
  } else {
    return err;
  }
}

short FSpIsLocked(FSSpec *fs)
{
  short err;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr   = fs->name;
  block.hFileInfo.ioVRefNum   = fs->vRefNum;
  block.hFileInfo.ioDirID     = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    if (block.hFileInfo.ioFlAttrib & 1) return 0; else return 1;
  } else {
    return err;
  }
}

long FSpEntryExists(FSSpec *fs)
{
  short err;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr   = fs->name;
  block.hFileInfo.ioVRefNum   = fs->vRefNum;
  block.hFileInfo.ioDirID     = fs->parID;
  /* printf("name: %s, vol: %d, parID: %d\n",p2cstr(fs->name), fs->vRefNum, fs->parID); */
  err = PBGetCatInfo(&block,false);
  switch (err) {
  case noErr:    return 1;
  case fnfErr:   return 0;
  case dirNFErr: return 0;
  default:       return err;
  }
}

long FSpGetModTime(FSSpec *fs)
{
  short err;
  unsigned long time;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr   = fs->name;
  block.hFileInfo.ioVRefNum   = fs->vRefNum;
  block.hFileInfo.ioDirID     = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err==noErr) {
    if (block.dirInfo.ioFlAttrib & 16) {
      /* it's a directory */
      time = block.dirInfo.ioDrMdDat;
    } else {
      /* it's a file */
      time = block.hFileInfo.ioFlMdDat;
    }
    return time & ~(1<<31);
  } else {
    errno = err;
    return -1;
  }
}

OSErr FSpEntryTouch(FSSpec *fs)
{
  short           err;
  CInfoPBRec      block;
  unsigned        long secs;

  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr = fs->name;
  block.hFileInfo.ioVRefNum = fs->vRefNum;
  block.hFileInfo.ioDirID   = fs->parID;

  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    GetDateTime(&secs);
    if (block.dirInfo.ioFlAttrib & 16) {
      block.dirInfo.ioDrMdDat = secs;
    } else {
      block.hFileInfo.ioFlMdDat = secs;
    }
    err = PBSetCatInfo(&block,false);
  };
  return err;
}

OSErr FSpEntryRename(FSSpec *fs,char *newname)
{
  OSErr             err;
  CInfoPBRec block;

  memset(&block,0,sizeof(CInfoPBRec));
  c2pstr(newname);
  err = HRename(fs->vRefNum,fs->parID,fs->name,newname);
  if (err == noErr) {
    memset(&fs->name,0,64);
    block.dirInfo.ioVRefNum   = fs->vRefNum;
    block.dirInfo.ioDrDirID   = fs->parID;
    block.dirInfo.ioFDirIndex = -1;
    err = PBGetCatInfo(&block,false);
    if (err == noErr){
      block.dirInfo.ioNamePtr = newname;
      block.dirInfo.ioFDirIndex = 0;
      err = PBGetCatInfo(&block,false);       
      if (err == noErr){
	if (block.dirInfo.ioFlAttrib & 16) {
	  block.dirInfo.ioFDirIndex = -1;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    strncpy(&fs->name,block.dirInfo.
		    ioNamePtr,64);
	  }                                       
	  
	} else {
	  Str255 filename;
	  short    i = 0;
	  short    last = 0;

	  while (i <= newname[0]) {
	    i++;
	    if (newname[i] == ':') {
	      last = i;
	    }
	  }
	  i = 1;
	  while (last+i <= newname[0]) {
	    filename[i] = newname[last+i];
	    i++;
	  }
	  memset(&filename,0,256);
	  filename[0] = newname[0]-last;
	  block.hFileInfo.ioVRefNum   = fs->vRefNu
	    m;
	  block.hFileInfo.ioDirID     = fs->parID;
	  block.hFileInfo.ioNamePtr   = newname;
	  block.hFileInfo.ioFDirIndex = 0;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    strncpy(&fs->name,block.hFileInfo.ioNamePtr,64);
	  }                                       
	  
	}
      }
    }
  }
  return err;     
}

long CountEntries (long dirID,short vRefNum)
{
  OSErr err;
  short index  = 1;
  long    result = 0;
  CInfoPBRec      block;

  do 
    {
      memset(&block,0,sizeof(CInfoPBRec));
      block.hFileInfo.ioFDirIndex = index;
      block.hFileInfo.ioDirID     = dirID;     
      block.hFileInfo.ioVRefNum   = vRefNum;     
      err = PBGetCatInfo(&block,false);
      if (err == noErr) {
	result++;
	index++;
      }
    } while (err == noErr);
  return result;
} 

StringPtr GetIndEntryName (long Target,short vRefNum,long inx)
{
  OSErr           err;
  CInfoPBRec      block;
  Str255          name;
  long result = 0;

  memset(&block,0,sizeof(CInfoPBRec));
  memset(&name,0,256);
  block.hFileInfo.ioFDirIndex = inx;
  block.hFileInfo.ioDirID     = Target;     
  block.hFileInfo.ioVRefNum   = vRefNum; 
  block.hFileInfo.ioNamePtr   = name;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    return block.hFileInfo.ioNamePtr;
  }
} 

OSErr HMakeFSSpec(short vRefNum,long dirID,char *name,FSSpec *fs)
{ 
  OSErr           err;
  CInfoPBRec      block;
  short                   nofound = 1;
  short                   i = 1;

  memset(&block,0,sizeof(CInfoPBRec));
  c2pstr(name);

  while (i <= name[0] && nofound) {
    if (name[i] == ':' && nofound) {
      nofound = 0;
    }
    i++;    
  }

  if (!nofound && i>2) {          
    /* it's a full path */
    HParamBlockRec  vInfo;
    Str255                  namecopy;       /* changed by PBHGetVInf
					       o */
    memset(&vInfo,0,sizeof(HParamBlockRec));
    strncpy(&namecopy,name,256);
    vInfo.volumeParam.ioNamePtr  = namecopy;
    vInfo.volumeParam.ioVolIndex = -1;
    err = PBHGetVInfo(&vInfo,false);
    if (err == noErr) {
      block.dirInfo.ioNamePtr = name;
      block.dirInfo.ioVRefNum = vInfo.volumeParam.ioVRefNum;
    } else {
      return err;
    }                       
    err = PBGetCatInfo(&block,false);
    if (err == noErr){ 
      block.dirInfo.ioFDirIndex = -1;
      err = PBGetCatInfo(&block,false);
      if (err == noErr){ 
	fs->vRefNum = block.dirInfo.ioVRefNum;
	fs->parID   = block.dirInfo.ioDrParID;
	strncpy(&fs->name,block.dirInfo.ioNamePtr,64);
      } else {
	Str255  filename;
	short           i = 1;
	short           last = 0;
	while (i <= name[0]) {
	  if (name[i] == ':') {
	    last = i;
	  }
	  i++;
	}
	memset(&filename,0,256);
	i = 1;
	while (last+i <= name[0]) {
	  filename[i] = name[last+i];
	  i++;
	}
	filename[0] = name[0]-last;
	block.hFileInfo.ioVRefNum   = block.dirInfo.ioVR
	  efNum;
	block.hFileInfo.ioNamePtr   = name;
	block.hFileInfo.ioFDirIndex = 0;
	err = PBGetCatInfo(&block,false);
	if (err == noErr){
	  fs->vRefNum = block.hFileInfo.ioVRefNum;
	  fs->parID   = block.hFileInfo.ioFlParID;
	  strncpy(&fs->name,&filename,64);
	} else {
	  return err;
	}
      }
    } else {
      OSErr           localerr;
      Str255  parname,entryname;
      short           i = 1;
      short           last = name[0];
      
      while (i <= name[0]) {
	if (name[i] == ':') {
	  last = i;
	}
	i++;
      }
      memset(&parname,0,256);
      memset(&entryname,0,256);
      if (last<name[0]) {
	strncpy(&parname,name,last+1);
	parname[0] = last;
	BlockMove(name+last+1,&entryname,name[0]-last);
      } else {
	BlockMove(name+1,&entryname,name[0]);
      }
      c2pstr(&entryname);
      block.dirInfo.ioNamePtr = &parname;
      localerr = PBGetCatInfo(&block,false);
      if (localerr == noErr){
	fs->vRefNum = block.dirInfo.ioVRefNum;
	fs->parID   = block.dirInfo.ioDrDirID;
	strncpy(&fs->name,&entryname,64);
      } else {
	return localerr;
      }               
    }
  } else {                
    /* it's a partial path */
    if (vRefNum && dirID) {
      block.dirInfo.ioVRefNum = vRefNum;
      block.dirInfo.ioDrDirID = dirID;
    } else {
      WDPBRec wdInfo;
      memset(&wdInfo,0,sizeof(WDPBRec));
      err = PBHGetVol(&wdInfo,false);
      if (err == noErr){
	wdInfo.ioVRefNum = wdInfo.ioWDVRefNum;
	dirID = wdInfo.ioWDDirID;
	err = PBGetWDInfo(&wdInfo,false);
	if (err == noErr){
	  block.dirInfo.ioVRefNum   = wdInfo.ioVRe
	    fNum;
	  block.dirInfo.ioDrDirID   = dirID;
	} else {
	  return err;
	}
      } else {
	return err;
      }
    }
    block.dirInfo.ioFDirIndex = -1;
    err = PBGetCatInfo(&block,false);
    if (err == noErr){
      block.dirInfo.ioNamePtr = name;
      block.dirInfo.ioFDirIndex = 0;
      err = PBGetCatInfo(&block,false);
      if (err == noErr){
	if (block.dirInfo.ioFlAttrib & 16) {
	  block.dirInfo.ioFDirIndex = -1;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    fs->vRefNum = block.dirInfo.ioVR
	      efNum;
	    fs->parID   = block.dirInfo.ioDr
	      ParID;
	    strncpy(&fs->name,block.dirInfo.
		    ioNamePtr,64);
	  }                                       
	  
	} else {
	  Str255  filename;
	  short           i = 1;
	  short           last = 0;
	  while (i <= name[0]) {
	    i++;
	    if (name[i] == ':') {
	      last = i;
	    }
	  }
	  memset(&filename,0,256);
	  i = 1;
	  while (last+i <= name[0]) {
	    filename[i] = name[last+i];
	    i++;
	  }
	  filename[0] = name[0]-last;
	  block.hFileInfo.ioVRefNum   = block.dirI
	    nfo.ioVRefNum;
	  block.hFileInfo.ioDirID     = dirID;
	  block.hFileInfo.ioNamePtr   = name;
	  block.hFileInfo.ioFDirIndex = 0;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    fs->vRefNum = block.hFileInfo.io
	      VRefNum;
	    fs->parID   = block.hFileInfo.io
	      FlParID;
	    strncpy(&fs->name,&filename,64);
	  }                                       
	  
	}
      } else {
	OSErr           localerr;
	Str255  parname,entryname;
	short           i = 1;
	short           last = name[0];
	
	while (i <= name[0]) {
	  if (name[i] == ':') {
	    last = i;
	  }
	  i++;
	}
	memset(&parname,0,256);
	memset(&entryname,0,256);
	if (last<name[0]) {
	  strncpy(&parname,name,last+1);
	  parname[0] = last;
	  BlockMove(name+last+1,&entryname,name[0]
		    -last);
	} else {
	  BlockMove(name+1,&entryname,name[0]);
	}
	c2pstr(&entryname);
	block.dirInfo.ioNamePtr = &parname;
	localerr = PBGetCatInfo(&block,false);
	if (localerr == noErr){
	  fs->vRefNum = block.dirInfo.ioVRefNum;
	  fs->parID   = block.dirInfo.ioDrDirID;
	  strncpy(&fs->name,&entryname,64);
	} else {
	  block.dirInfo.ioFDirIndex = -1;
	  localerr = PBGetCatInfo(&block,false);
	  if (localerr == noErr){
	    fs->vRefNum = block.dirInfo.ioVR
	      efNum;
	    fs->parID   = block.dirInfo.ioDr
	      DirID;
	    strncpy(&fs->name,&entryname,64)
	      ;
	  };
	}               
      }
    }
  }
  return err;
}


#endif /* MAC */
