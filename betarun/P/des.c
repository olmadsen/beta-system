#include "beta.h"

#ifdef sun4s
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "PSfile.h"
#include "des.h"
#include "error.h"

/* Local function definitions */
static u_long /* error code */ create(DEStorage *des,
                                      char *host,
                                      char *path);
static void transport(DEStorage *des, 
		      u_long from, 
		      u_long to,
		      u_long nb);
static void extend(DEStorage *des, 
		   u_long areaID,
		   u_long minSize);

/* local variables */
u_long reads;
static u_long writes;

/* Public operations on dynamic extendable storage areas. 
 */

void DESInit(void)
{
    reads = 0;
    writes = 0;
}

DEStorage *DEScreate(char *host, char *path, u_long createFile)
{
   DEStorage *des;
   u_long rcode;
   
   des = (DEStorage *)malloc(sizeof(struct destorage));
   des -> host = host;
   des -> path = path;
   des -> fd = -1;
   des -> areaTable = (AreaTable *)malloc(sizeof(struct areaTable));
   des -> areaTable -> storageTop = 0;
   des -> areaTable -> tableSize = 0;
   des -> areaTable -> table = NULL;
   
   if (createFile) {
      rcode = create(des, host, path);
      
      if (rcode == 0) {
         return des;
      } else {
         return (DEStorage *)rcode;
      }
   } else {
      return des;
   }
}

void DESdestroy(DEStorage *des)
{
    if (des -> host) {
        free(des -> host);
    }
  
    if (des -> path) {
        free(des -> path);
    }

    if (des -> areaTable -> table) {
        free(des -> areaTable -> table);
    }
    
    free(des -> areaTable);
    close(des -> fd);
    free(des);
}

void DESflush(DEStorage *des)
{
    Rewind(des -> fd);
    writeLong(des -> fd, &des -> areaTable -> magic);
    writeLong(des -> fd, &des -> areaTable -> storageTop);
    writeLong(des -> fd, &des -> areaTable -> tableSize);
    writeSome(des -> fd,
              des -> areaTable -> table,
              des -> areaTable -> tableSize * sizeof(struct areaTableEntry));
}

u_long /* error code */ DESattach(DEStorage *des,
                                  char *host,
                                  char *path)
{
   int fd;
   
   if (des -> host == NULL) {
      if (des -> path == NULL) {
         if (fileExists(path)) {
            if ((fd = open(path,
                           O_RDWR
#ifdef nti
                           | _O_BINARY
#endif
                           , S_IWRITE | S_IREAD)) < 0) {
               return ACCESSERRORERROR;
            } else {
               u_long magic;
               
               readLong(fd, &magic);
               if (magic == MAGIC) {
                  u_long storageTop;
                  u_long tableSize;
                  
                  /* Chances are that we have opened an existing storage area. */
                  des -> host = strdup(host);
                  des -> path = strdup(path);
                  des -> fd = fd;
                  
                  if (des -> areaTable) {
                     readLong(fd, &storageTop);
                     readLong(fd, &tableSize);
              
                     if (des -> areaTable -> table == NULL) {
                        des -> areaTable -> magic = magic;
                        des -> areaTable -> storageTop = storageTop;
                        des -> areaTable -> tableSize = tableSize;
                        
                        des -> areaTable -> table = (AreaTableEntry *)
                           malloc(sizeof(struct areaTableEntry) * tableSize);
                        
                        readSome(fd, 
                                 des -> areaTable -> table, 
                                 sizeof(struct areaTableEntry) * tableSize);
                        return 0;
                        
                     } else {
                        return ACCESSERRORERROR;
                     }
                  } else {
                     return ACCESSERRORERROR;
                  }
               } else {
                  return ACCESSERRORERROR;
               }
            }
         } else {
            return NOTFOUNDERROR;
         }
      } else {
         return ACCESSERRORERROR;
      }
   } else {
      return ACCESSERRORERROR;
   }
}

u_long /* areaID */ DESarea(DEStorage *des,
			    u_long minSize)
{
    /* Check that area is attached to a file */
    if (des -> fd) {
        u_long count;
    
        for (count = 0; count < des -> areaTable -> tableSize; count++) {
            AreaTableEntry *current;
      
            current = des -> areaTable -> table + count;
      
            if (current -> allocated == 0) {
                /* Area unallocated */
                current -> storageOffset = des -> areaTable -> storageTop;
                des -> areaTable -> storageTop += minSize;
                current -> areaTop = 0;
                current -> areaSize = minSize;
                current -> allocated = 1;
                return count;
            }
        }
    } else {
        perror("DESarea: Storage not attached");
    }
  
    fprintf(stderr, 
            "DESarea: Maximum area allocation count exceeded (%d)\n",
            (int)(des -> areaTable -> tableSize));
    perror("DESarea:");
  
    return 0;
}

u_long /* area offset */ DESallocate(DEStorage *des,
				     u_long areaID,
				     u_long nb,
                                     u_long alignment)
{
    if (des -> fd) {
        if (areaID < des -> areaTable -> tableSize) {
            AreaTableEntry *area;
            u_long mask;

            area = des -> areaTable -> table + areaID;
            
            /* check alignment */
            mask = (1 << alignment) - 1;
            
            if ((area -> areaTop & mask) + nb <= (1 << alignment)) {
                /* there is enough room in the block */
                if (area -> areaTop + nb <= area -> areaSize) {
                    area -> areaTop += nb;
                    return area -> areaTop - nb;
                } else {
                    extend(des, areaID, area -> areaSize * 2);
                    return DESallocate(des, areaID, nb, alignment);
                }
            } else {
                /* there is not enough room in the block */
                DESallocate(des,
                            areaID,
                            (1 << alignment) - (area -> areaTop & mask),
                            alignment);
                return DESallocate(des, areaID, nb, alignment);
            }
        } else {
            perror("DESallocate: Illegal areaID (Where did you get that from?)");
        }
    } else {
        perror("DESallocate: Storage not attached");
    }
    return 0;
}

void DESload(DEStorage *des, 
             u_long areaID,
             char *buffer,
             u_long offset,
             u_long nb)
{
    if (des -> fd) {
        if (areaID < des -> areaTable -> tableSize) {
            AreaTableEntry *area;
            
            area = des -> areaTable -> table + areaID;
            
            if (offset + nb <= area -> areaSize) {
                windTo(des -> fd, area -> storageOffset + offset);
                reads++;
                readSome(des -> fd, buffer, nb);
            } else {
                perror("DESload: trying to load beyond boundry");
            }
        } else {
            perror("DESload: Illegal areaID");
        }
    } else {
        perror("DESload: Storage not attached");
    }
}

void DESsave(DEStorage *des, 
	     u_long areaID,
	     char *buffer,
	     u_long offset,
	     u_long nb)
{
    if (des -> fd) {
        if (areaID < des -> areaTable -> tableSize) {
            AreaTableEntry *area;
      
            area = des -> areaTable -> table + areaID;
      
            if (offset + nb <= area -> areaSize) {
                windTo(des -> fd, area -> storageOffset + offset);
                writes++;
                writeSome(des -> fd, buffer, nb);
            } else {
                perror("DESsave: trying to write beyond boundry");
            }
        } else {
            perror("DESsave: Illegal areaID");
        }
    } else {
        perror("DESsave: Storage not attached");
    }
}

u_long /* area size */ DESsize(DEStorage *des, u_long areaID)
{
    if (des -> fd) {
        if (areaID < des -> areaTable -> tableSize) {
            AreaTableEntry *area;
            
            area = des -> areaTable -> table + areaID;
            return area -> areaTop;
        } else {
            perror("DESsize: Illegal areaID");
        }
    } else {
        perror("DESsize: Storage not attached");
    }
    return 0;
}

/* Private utility operations on dynamic extendable storage areas.
 */

static void transport(DEStorage *des, 
		      u_long from, 
		      u_long to,
		      u_long nb)
{  
    u_long bufferSize, count;
    char *buffer;
  
    bufferSize = preferredBufferSize(des -> fd);
    buffer = (char *)malloc(sizeof(char) * bufferSize);
  
    count = 0;
    while (count < nb) {
        windTo(des -> fd, from + count);
        if (count + bufferSize <= nb) {
            readSome(des -> fd, buffer, bufferSize);
            windTo(des -> fd, to + count);
            writeSome(des -> fd, buffer, bufferSize);
            count += bufferSize;
        } else {
            readSome(des -> fd, buffer, nb - count);
            windTo(des -> fd, to + count);
            writeSome(des -> fd, buffer, nb - count);
            count += nb - count;
        }
    }
    free(buffer);
}

static void extend(DEStorage *des, 
		   u_long areaID,
		   u_long minSize)
{
    AreaTableEntry *area;
  
    area = des -> areaTable -> table + areaID;
  
    if (area -> allocated) {
        if (area -> areaSize < minSize) {
            transport(des, 
                      area -> storageOffset, 
                      des -> areaTable -> storageTop,
                      area -> areaTop);
      
            area -> storageOffset = des -> areaTable -> storageTop;
            des -> areaTable -> storageTop += minSize;
            area -> areaSize = minSize;
        } else {
            perror("extend: New size must be larger than old size");
        }
    } else {
        perror("extend: Deallocating unallocated area");
    }
}

static u_long create(DEStorage *des,
                     char *host,
                     char *path)
{
   int fd;
   
   if ((fd = open(path, 
                  O_RDWR | O_CREAT
#ifdef nti
                  | _O_BINARY
#endif
                  , S_IWRITE | S_IREAD))<0) {
      return ACCESSERRORERROR;
   } else {
      des -> host = strdup(host);
      des -> path = strdup(path);
      des -> fd = fd;
    
      if (des -> areaTable) {
         if (des -> areaTable -> table == NULL) {
            u_long count;
        
            des -> areaTable -> magic = MAGIC;
            des -> areaTable -> tableSize = DEFAULTTABLESIZE;
        
            des -> areaTable -> table = (AreaTableEntry *)
               calloc(DEFAULTTABLESIZE, sizeof(struct areaTableEntry));
            
            for (count = 0; count < DEFAULTTABLESIZE; count++) {
               AreaTableEntry *current;
          
               current = des -> areaTable -> table + count;
          
               current -> allocated = 0;
            }
        
            des -> areaTable -> storageTop = 
               sizeof(u_long) * 3 +
               sizeof(struct areaTableEntry) * DEFAULTTABLESIZE;
        
            writeLong(fd, &des -> areaTable -> magic);
            writeLong(fd, &des -> areaTable -> storageTop);
            writeLong(fd, &des -> areaTable -> tableSize);
	
            writeSome(fd, 
                      des -> areaTable -> table, 
                      sizeof(struct areaTableEntry) * DEFAULTTABLESIZE);
        
            /* The storage is not appended to the file at this point. It
             * will be created by the operating system as it is accessed.
             */

            return 0;
         } else {
            return ACCESSERRORERROR;
         }
      } else {
         return ACCESSERRORERROR;
      }
   }
}

void DESend(void)
{
    fprintf(stderr,"loads: %d\n", (int)reads);
    fprintf(stderr,"saves: %d\n", (int)writes);
}

#endif /* sun4s */
