
#ifdef hp9000s400
#  include <strings.h>
#else
#  include <sys/types.h>
#endif

#ifdef apollo
#  include <sys/dir.h>
#  define DIRENT direct
#else
#  ifdef nti_ms
#    include <io.h>
#    define DIRENT _DIR
#  else
#    include <dirent.h>
#    define DIRENT dirent
#  endif
#endif

#ifdef nti
#  ifdef nti_gnu
#  else
#    include <malloc.h>
#  endif
#  ifdef nti_bor
#    include <dir.h>
#  endif
#else
#  include <sys/param.h>
#  include <pwd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef nti
#  define MAX_PATH       1024
#endif

#ifndef sun
void *malloc();
void free();
#endif

#define null (void *) 0

static int strptrcmp(s1, s2)
     char **s1, **s2;
{ 
  return strcmp(*s1,*s2);
}
#ifdef nti_ms
typedef struct _DIR
{
  struct _finddata_t entry;
  long hFile;
  int result;
  char *d_name;
} DIR;

DIR *opendir(char *path)
{
  DIR *dirp = malloc(sizeof(DIR));
  char *match = malloc(strlen(path)+3);
  strcpy(match,path);
  if (match[strlen(match)-1] != '\\')
    strcat(match, "\\");
  strcat(match, "*");
  dirp->hFile = _findfirst(match, &(dirp->entry));
  if (dirp->hFile == -1L) {
    free(dirp);
    free(match);
    /* Error: nothing allocated */
    dirp->result = -1;
    return NULL;
  }
  free(match);
  /* Allocated only the return value (dirp) */
  dirp->d_name = NULL;
  dirp->result = 0;
  return dirp;
}

struct DIRENT *readdir(DIR *dirp)
{
  if (dirp->result == -1L) {
    free(dirp->d_name);
    free(dirp);
    return NULL;
  }
  dirp->d_name = realloc(dirp->d_name, strlen(dirp->entry.name)+1);
  strcpy(dirp->d_name, dirp->entry.name);
  dirp->result = _findnext(dirp->hFile, &(dirp->entry));
  return dirp;
}

int closedir(DIR *dirp)
{
  free(dirp->d_name);
  free(dirp);
}
#endif /* dir_ms */


/* Scan enties in dir. Return the length of the longest entryname via
 * LongestFnc, Apply CallbackFnc to each entry found.
 * Return number of entries found, -1 if error 
 */
int ScanDir(dir, LongestFnc, CallbackFnc) 
char *dir;
void (*CallbackFnc)();
void (*LongestFnc)();
{ int i, dnamlen, num = 0;
  int longest = 0;
  char **list;
  int listlen = 20;
  DIR *dirp; 
  char *tmp;
  struct DIRENT *dp;

  if((dirp = opendir(dir))==NULL) 
    return -1;

  list = (char **) malloc (listlen*sizeof(char **));

  for(dp=readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    dnamlen = strlen(dp->d_name);
    tmp = (char *)malloc(dnamlen+1);
    tmp[0] ='\0'; /* In case of empty name */
    strcpy(tmp, dp->d_name);
    if (num == listlen) {
      listlen = 2*listlen;
      list = (char **) realloc (list, listlen*sizeof(char **));
    }
    list[num++] = tmp;
    if (dnamlen > longest) longest = dnamlen;
  }

  closedir(dirp);

  if (num > 0) (*LongestFnc)(longest);
  else { free(list); return -1; }

  qsort((char*)list, num, sizeof(char *), strptrcmp);

  /* Apply CallbackFnc to each entry */
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
    if(dnamlen  ==  len  &&  !strcmp(dp->d_name, name)) 
      {closedir(dirp);
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

#ifdef nti
/* entryStatus is no longer used in file implementation.
 * For selection in a directoryscan, it is, however, usefull
 * on win32 too.
 */
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

extern struct stat statBuffer; /* in fileInt_nt.c */

int entryStatus(path,status)
     char *path;    /* IN par. denoting the path of the entry to be statted */
     int  *status;  /* OUT par. The buffer must be allocated by Beta. */
{ 
  int entryType;
  
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
 
  return 1;
} 
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


