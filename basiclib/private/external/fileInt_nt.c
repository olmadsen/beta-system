#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <io.h>
#if defined(nti_bor) || defined(nti_gnu)
#  include <utime.h>
#  ifdef nti_gnu
#    define ENOTSAM EXDEV
#  endif
#else /* it is nti_ms */
#include <sys/utime.h>
#define S_IXUSR _S_IEXEC
#define S_IWUSR _S_IWRITE
#define S_IRUSR _S_IREAD
#define S_IFBLK (-1) /* ??? */
#define ENOTSAM EXDEV

#endif


#include <malloc.h>
#include <windows.h>

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

int isEntryDir(char *path)
{ 
#if 0
  struct stat statBuffer; 
  int entryType;
  if (stat(path,&statBuffer)<0) return -1;
  return (int) (statBuffer.st_mode & S_IFMT) == S_IFDIR;
#else
  int attr = GetFileAttributes(path);
  if (attr==-1) return -1;
  return ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0);
#endif
} 

int isEntryFile(char *path)
{ 
#if 0
  struct stat statBuffer; 
  int entryType;
  if (stat(path,&statBuffer)<0) return -1;
  return (int) (statBuffer.st_mode & S_IFMT) == S_IFREG;
#else
  int attr = GetFileAttributes(path);
  if (attr==-1) return -1;
  return ((attr & FILE_ATTRIBUTE_DIRECTORY) == 0);
#endif
}

int getEntrySize(char *path)
{ 
  struct stat statBuffer; 
  int entryType;
  if (stat(path,&statBuffer)<0) return -1;
  return (int) statBuffer.st_size;
} 

int touchEntry(path)
     char *path;
{
  if((char)(*path)=='\0')
    return 0;                      /* test for empty string */
  if(utime(path,NULL)<0)
    return -1;
}

int getEntryModtime(char *path)
{ 
  struct stat statBuffer; 
  int entryType;
  if (stat(path,&statBuffer)<0) return -1;
  return (int) statBuffer.st_mtime;
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

#ifndef nti_gnu
# define F_OK (00)
# define X_OK (01)
# define W_OK (02)
# define R_OK (04)
#endif

int entryExists(path, follow)
     char *path;
     int follow /* not used */;
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
