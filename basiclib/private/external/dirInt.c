#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

#ifdef nti
#  include <io.h>
#  ifdef nti_ms
#    include <windows.h>
#    include <winbase.h>
#    include <sys/utime.h>
#    define S_IXUSR _S_IEXEC
#    define S_IWUSR _S_IWRITE
#    define S_IRUSR _S_IREAD
#    define ENOTSAM EXDEV
#    define DIRENT _DIR
#    include <malloc.h>
#  else
#    include <utime.h>
#    include <dir.h>
#    include <dirent.h>
#    define DIRENT dirent
#  endif
#else
#  include <sys/time.h>
#  include <sys/file.h>
#  include <sys/param.h>
#  include <unistd.h>
#  include <pwd.h>
#  include <dirent.h>
#  define DIRENT dirent
#  define MAX_PATH       1024
#endif

#ifndef sun
#ifndef nti_gnu
void *malloc();
void free();
#endif
#endif

#define null (void *) 0

static int strptrcmp(const void *s1, const void *s2)
{ 
  return strcmp(*(const char**)s1,*(const char**)s2);
}

#ifdef nti_ms
typedef struct _DIR
{
  WIN32_FIND_DATA entry;
  HANDLE hFile;
  int result;
  char d_name[MAX_PATH];
} DIR;

struct _DIR *opendir(char *path)
{
  char match[MAX_PATH+8];
  struct _DIR *dirp = malloc(sizeof(struct _DIR));
  int pathlen;
  strcpy(match,path);
  pathlen=strlen(match);
  if (match[pathlen-1] != '\\') {
    match[pathlen]='\\';
    match[++pathlen]=0;
  }
  match[pathlen]='*';
  match[++pathlen]='.';
  match[++pathlen]='*';
  match[++pathlen]=0;
  dirp->hFile = FindFirstFile(match, &(dirp->entry));
  if (dirp->hFile == INVALID_HANDLE_VALUE) {
    free(dirp);
    return NULL;
  }
  /* Allocated only the return value (dirp) */
  dirp->result = 1;
  return dirp;
}

struct _DIR *readdir(struct _DIR *dirp)
{
  if (dirp->result == 0) {
    return NULL;
  }
  strcpy(dirp->d_name, dirp->entry.cFileName);
  dirp->result = FindNextFile(dirp->hFile, &(dirp->entry));
  return dirp;
}

int closedir(struct _DIR *dirp)
{
  FindClose(dirp->hFile);
  free(dirp);
}
#endif /* nti_ms */


/* Scan entries in dir. 
 * Set the length of the longest entryname via *longestP, and
 * set the number of entries via *numP. 
 * Then Apply CallbackFnc to each entry found.
 * Return number of entries found, -1 if error 
 */
int ScanDir(char *dir, int *longestP, int *numP, void (*CallbackFnc)(char*)) 
{ 
  int i, dnamlen, num = 0;
  int longest = 0;
  char **list;
  int listlen = 64;
  struct _DIR *dirp; 
  char *tmp;
  struct DIRENT *dp;

  *longestP = 0;
  *numP = 0;
  
  if (!(dirp = opendir(dir)))
    return -1;

  list = (char **) malloc (listlen*sizeof(char *));

  for(dp=readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    dnamlen = strlen(dp->d_name);
    tmp = (char *)malloc(dnamlen+1);
    tmp[0] ='\0'; /* In case of empty name */
    memcpy(tmp, dp->d_name, dnamlen+1);
    if (num == listlen) {
      listlen = 2*listlen;
      list = (char **) realloc (list, listlen*sizeof(char *));
    }
    list[num++] = tmp;
    if (dnamlen > longest) longest = dnamlen;
  }

  closedir(dirp);

  if (num > 0) {
    *longestP = longest;
    *numP =num;
  } else { 
    free(list);
    return -1; 
  }

  qsort((char*)list, num, sizeof(char *), strptrcmp);

  /* Apply CallbackFnc to each entry 
   * NB: Do NOT use longestP, numP after calling a calbackfunc! 
   */
  for (i=0;i<num;i++) {
    (*CallbackFnc)(list[i]);
    free(list[i]);
  }

  free(list);
  return(num);
}

#ifdef nti
int findNtEntry(path,name)
#else
int findUnixEntry(path,name)
#endif
char *path;
char *name;
/* Locates the entry with name, name, in the directory with absolute
   path, path. 
   If the entry is not found, 0 is returned. 
   If the entry is found, 1 is returned. 
   -1 : Invalid arguments.
   -2 : Fail in opendir call.
*/
{DIR *dirp;
 int len; 
 int dnamlen;
 struct DIRENT *dp;

 if((path==NULL) || (name==NULL)) 
   return -1;
 len = strlen(name);
 if((dirp = opendir(path))==NULL) 
   return -2;
 for(dp=readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    dnamlen = strlen(dp->d_name); /* SUN4S CORRECTION !! */
    if (dnamlen  ==  len  &&  !strcmp(dp->d_name, name)) {
      closedir(dirp);
      return 1;
    }
  }
 /* Did not locate entry */
 closedir(dirp);
 return 0;
}

int isDirEmpty(path)
char *path;
/* Find out if the directory with path path is empty, i.e. contains only "." and ".."
   If the directory is not empty, 0 is returned. 
   If the directory is empty, 1 is returned. 
   -1 : Invalid arguments.
   -2 : Fail in opendir call.
*/
{DIR *dirp;
 int len; 
 int dnamlen; 
 struct DIRENT *dp;

 if(path==NULL) return -1;
 if((dirp = opendir(path))==NULL) return -2;
 for(dp=readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    dnamlen = strlen(dp->d_name); /* SUN4S CORRECTION !! */
    if( ! ((dnamlen==1  &&  !strcmp(dp->d_name, ".")) ||
           (dnamlen==2  &&  !strcmp(dp->d_name, "..")) )) 
      { closedir(dirp);
        return 0;
      }
  }
 /* Found nothing but "." and ".." */
 closedir(dirp);
 return 1;
}

int countDir(path)
char *path;
/* return the number of entries in the directory with path path or
   -1 : Invalid arguments.
   -2 : Fail in opendir call.
 */
{DIR *dirp;
 int num; 
 struct DIRENT *dp;

 if(path==NULL) return -1;
 if((dirp = opendir(path))==NULL)  return -2;
 num=0;
 for(dp=readdir(dirp); dp != NULL; dp = readdir(dirp), num++);
 closedir(dirp);
 return num;
}

#ifdef nti
int createNtDirectory(path)
#else
int createUnixDirectory(path)
#endif
char *path;
{
 if((char)(*path)=='\0')
   return 0;                     /* test for empty string */
#ifdef nti
 if(mkdir(path)<0)
#else
 if(mkdir(path,0755)<0)
#endif
   return -1;
 return 1;
}


#ifdef nti
int deleteNtDirectory(path)
#else
int deleteUnixDirectory(path)
#endif
char *path;
{if((char)(*path) == '\0')
   return 0;                    /* test for empty string */
 if(rmdir(path)<0)
   return -1;
 return 1;
}

/* entryStatus is no longer used in file implementation.
 * For selection in a directoryscan, it is, however, usefull.
 */

#ifndef nti
#ifndef ppcmac

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
  
  /* The type of the entry */
  entryType=statBuffer.st_mode & S_IFMT;
  status[0]=( S_IFDIR  == entryType ) ? 1 : 0;
  status[1]=( S_IFCHR  == entryType ) ? 1 : 0;
  status[2]=( S_IFBLK  == entryType ) ? 1 : 0;
  status[3]=( S_IFREG  == entryType ) ? 1 : 0;
  status[4]=( S_IFLNK  == entryType ) ? 1 : 0;
  status[5]=( S_IFSOCK == entryType ) ? 1 : 0;
  
  return 1;
} 
#endif /* ppcmac */
#endif /* nti */

#ifdef test
void CopyOut(buf)
     char *buf;
{
  printf("entry: %s\n", buf);
}

void Longest(longest)
     int longest;
{
  printf ("longest: %d\n",longest);
}

int main(argc, argv)
int argc;
char *argv[];
{
  ScanDir(argv[1], Longest, CopyOut);
}
#endif


