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

int getEntryDevice(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_dev;
} 

int getEntryInode(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_ino;
} 
