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


int getEntryPermissions(path,permission,follow)
/* In essence a "stat/lstat" call on the entry with absolute path, path.
 * The permissions of the entry is passed on to Beta by means of the
 * buffer permission. A return of -1 indicates
 * an error in the stat call, whereas a return of 1 means succes.
 */
     char *path;       /* IN par. The path of the entry to be stat'ed */
     int  *permission; /* OUT par. The buffer must be allocated by Beta. */
     int follow;       /* follow links ? */
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0 ) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0 ) 
      return -1;
  }
  
  /* The mode of the entry denoted by the full path name, path,
     is changed according to the supplied permission buffer.
     The buffer is an array of 9 integers (each 1 or 0). The first 3 are 
     related to the mode for the "other" category, the next 3 give the mode
     for "group" and the last 3 denote the mode of "owner". The integers 
     should be interpreted as follows :
     
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

int getEntryHardLinks(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_nlink;
} 

int getEntryOwner(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_uid;
} 

int getEntryGroup(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_gid;
} 

int getEntryDeviceType(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_rdev;
} 

int getEntryAccessTime(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_atime;
} 

int getEntryStatusTime(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_ctime;
} 

int getEntryOptBlockSize(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_blksize;
} 

int getEntryBlocks(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return statBuffer.st_blocks;
} 



int isEntryCharSpecial(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return (statBuffer.st_mode & S_IFMT) == S_IFCHR;
} 

int isEntryBlockSpecial(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return (statBuffer.st_mode & S_IFMT) == S_IFBLK;
} 

int isEntrySymLink(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return (statBuffer.st_mode & S_IFMT) == S_IFLNK;
} 

int isEntrySocket(char *path, int follow)
{
  struct stat statBuffer;
  
  if (follow){
    if (stat(path,&statBuffer)<0) 
      return -1;    
  } else {
    if (lstat(path,&statBuffer)<0) 
      return -1;
  }
  return (statBuffer.st_mode & S_IFMT) == S_IFSOCK;
} 
