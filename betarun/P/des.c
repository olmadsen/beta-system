#include "beta.h"

#ifdef PERSIST
#ifndef MAC
#include <sys/types.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef nti
#include <io.h>
#endif

#include "PSfile.h"
#include "des.h"
#include "error.h"

#if defined(MAC)

static char *strdup(char *str)
{
	char *newstr;
	int i;
	
	newstr = malloc(strlen(str)+1);
	i = 0;
	while(newstr[i]=str[i])
		i++;
	return newstr;
}


#endif


/* Local function definitions */
static u_long /* error code */ create(DEStorage *des,
                                      char *host,
                                      char *path);
static void transport(DEStorage *des, 
		      u_long from, 
		      u_long to,
		      u_long nb);
static void doextend(DEStorage *des, 
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

static void DESWriteAreaTable(DEStorage *des)
{
  /*fprintf(output, 
	  "DESWriteAreaTable, magic = 0x%X\n"
	  "              storageTop = 0x%X\n"
	  "               tableSize = 0x%X\n",
	  (int)des -> areaTable -> magic,
	  (int)des -> areaTable -> storageTop,
	  (int)des -> areaTable -> tableSize);*/

   /* Write header information */
   Rewind(des -> fd);
   writeLong(des -> fd, &des -> areaTable -> magic);
   writeLong(des -> fd, &des -> areaTable -> storageTop);
   writeLong(des -> fd, &des -> areaTable -> tableSize);
   
   /* Write table entries */
   {
      u_long count;
      
      for (count = 0; count < des -> areaTable -> tableSize; count++) {
         AreaTableEntry *current;
         
         current = des -> areaTable -> table + count;
         
         writeLong(des -> fd, &current -> allocated);
         writeLong(des -> fd, &current -> storageOffset);
         writeLong(des -> fd, &current -> areaTop);
         writeLong(des -> fd, &current -> areaSize);
      }
   }
}
                     
static u_long DESReadAreaTable(DEStorage *des)
{
   readLong(des -> fd, &des -> areaTable -> magic);
   /*fprintf(output, "read storagetop 1: 0x%0x8\n", (int)des -> areaTable -> storageTop);*/
   
   if (des -> areaTable -> magic == MAGIC) {
      readLong(des -> fd, &des -> areaTable -> storageTop);
      readLong(des -> fd, &des -> areaTable -> tableSize);
      
      if (des -> areaTable -> table == NULL) {
         des -> areaTable -> table = (AreaTableEntry *)
            malloc(sizeof(struct areaTableEntry) * des -> areaTable -> tableSize);

         /* Read table entries */
         {
            u_long count;
            
            for (count = 0; count < des -> areaTable -> tableSize; count++) {
               AreaTableEntry *current;
               
               current = des -> areaTable -> table + count;
               
               readLong(des -> fd, &current -> allocated);
               readLong(des -> fd, &current -> storageOffset);
               readLong(des -> fd, &current -> areaTop);
               readLong(des -> fd, &current -> areaSize);
            }
         }
         return 0;
      } else {
         return ACCESSERRORERROR;
      }
   } else {
      return ACCESSERRORERROR;
   }
}

void DESflush(DEStorage *des)
{
   /* Writes the state of the areatable to disk */
   DESWriteAreaTable(des);
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
#ifndef MAC
                           , S_IWRITE | S_IREAD
#endif
							)) < 0) {
               return ACCESSERRORERROR;
            } else {
               des -> host = (char *) strdup(host);
               des -> path = (char *) strdup(path);
               des -> fd = fd;
               return DESReadAreaTable(des);
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
		/*fprintf(output, "storagetop 2: 0x%0x8\n", (int)des -> areaTable -> storageTop);*/
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
            
            if ((u_long)((area -> areaTop & mask) + nb) <=
                (u_long)(1 << alignment)) {
                /* there is enough room in the block */
                if (area -> areaTop + nb <= area -> areaSize) {
                    area -> areaTop += nb;
                    return area -> areaTop - nb;
                } else {
                    doextend(des, areaID, area -> areaSize * 2);
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

static void doextend(DEStorage *des, 
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
	    /*fprintf(output, "storagetop 3: 0x%0x8\n", (int)des -> areaTable -> storageTop);*/
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
#ifndef MAC
                  , S_IWRITE | S_IREAD
#endif 
				))<0) {
      return ACCESSERRORERROR;
   } else {
      des -> host = (char *) strdup(host);
      des -> path = (char *) strdup(path);
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
	    /*fprintf(output, "default storagetop: 0x%0x8\n", (int)des -> areaTable -> storageTop);*/
        
            DESWriteAreaTable(des);
            
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

#endif /* PERSIST */
