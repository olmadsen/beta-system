
#ifdef hp9000s400
#  include <strings.h>
#else
#  include <sys/types.h>
#endif

#ifdef apollo
#  include <sys/dir.h>
#  define DIRENT direct
#else
#  define DIRENT dirent
#  include <dirent.h>
#endif

#ifdef nti
#  include <malloc.h>
#  include <dir.h>
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

int findUnixEntry(path,name)
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

int createUnixDirectory(path)
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


int deleteUnixDirectory(path)
char *path;
{if((char)(*path) == '\0')
   return 0;                    /* test for empty string */
 if(rmdir(path)<0)
   return -1;
 return 1;
}

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


