#ifndef _DES_H_
#define _DES_H_

#ifndef ppcmac
#include <sys/types.h>
#endif


#define MAGIC 0x26174306
#define DEFAULTTABLESIZE 8

/* The following two types describes how a dynamic extendable storage
 * is represented on disk. 
 */

typedef struct areaTableEntry {
  u_long allocated;
  u_long storageOffset;
  u_long areaTop;
  u_long areaSize;
} AreaTableEntry;

typedef struct areaTable {
  u_long magic;
  u_long storageTop;
  u_long tableSize;
  AreaTableEntry *table;
} AreaTable;

/* The following type is used to hold transient information about
 * attached files.
 */

typedef struct destorage {
  char *host;
  char *path;
  int fd;
  AreaTable *areaTable;
} DEStorage;

void DESInit(void);
DEStorage *DEScreate(char *host, char *path, u_long createFile);
void DESdestroy(DEStorage *des);
void DESflush(DEStorage *des);
u_long /* error code */ DESattach(DEStorage *des,
                                  char *host,
                                  char *path);
u_long /* areaID */ DESarea(DEStorage *des, u_long minSize);
u_long /* area offset */ DESallocate(DEStorage *des,
                                     u_long areaID,
                                     u_long nb,
                                     u_long alignment);
u_long /* area size */ DESsize(DEStorage *des, u_long areaID);
void DESload(DEStorage *des, u_long areaID, char *buffer, u_long offset, u_long nb);
void DESsave(DEStorage *des, u_long areaID, char *buffer, u_long offset, u_long nb);
void DESend(void);

#endif /* _DES_H_ */
