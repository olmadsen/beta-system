#include "beta.h"

#if defined(LIN)
#include <sys/ucontext.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "linStats.h"
#include "proxyRef.h"
#include "liniarize.h"

/* LOCAL FUNCTIONS */
/* Main functionality */
static void collectList(ptr(Object) root);
static void scanList(ref (Object) root, void (foreach)(ref (Object) current));
static void repairObjects(void);
static void copyObjects(struct liniarization *l,
                        void (redirect)(struct Object *obj, struct Object **theCell));
static void copyObjectsAbsolute(struct liniarization *l);
static void copyObjectsIndirect(struct liniarization *l);

/* Assisting functions */
static long copyObjectToLiniarization(struct liniarization *l, struct Object *theObj);
static void insertInInfoTable(ref (Object) current);
static void assignIds(ref (Object) root);
static struct liniarization *createLiniarization();
static long getNextId(struct liniarization *l);
static void insertInfoTableEntry(struct liniarization *l,
                                 long id,
                                 long oldGC,
                                 long *original);
static void freeLiniarization(struct liniarization *l);
static void scanObject(struct Object *obj,
                       void (referenceAction)(struct Object *obj,
                                              struct Object **theCell),
                       int doPartObjects);
static void redirectAbsolute(ref (Object) obj,
                             handle (Object) theCell);
static void redirectIndirect(ref (Object) obj,
                             handle (Object) theCell);
static void scanOrigins(void);
static void checkLinearization(void);
static void dumpToDisk(struct liniarization *l);
static struct liniarization *loadFromDisk(void);

/* GLOBAL FUNCTIONS */
long linearizeAbsolute(struct Object *root);
long linearizeIndirect(struct Object *root);
void assignIndirRef(struct Object **theCell, long id);
void dumpLiniarizationToDisk(void);
long loadLiniarizationFromDisk(void);

/* LOCAL MACROS */

#define LIN_IDTOOBJECT(l, id) ((ptr(Object))(l -> liniarization + l -> infoTable[id].byteOffset))

/* Copied in proxyRef.c, make sure to update if you change below */
#define MAPTOINDIRECT(id) ((id * -1) - 1)

#define INITIALLINLENGTH 4

/* GLOBAL VARIABLES */
struct liniarization *l = NULL;

/* MG: */

static long minIndirRef = -200000;  /* minimum indirectref. */

/* Build a linked list of all objects reachable from root
 * in the GCfield of the objects.
 * This often conflicts with the GC'er, so be careful...
 * The refernces are negated when written to GCAttr so that they can
 * be distinguished from forward pointers left by the GC.
 */

static ptr(Object) tail;

void appendToList(struct Object *theObj, struct Object **theCell)
{
    ptr(Object) obj = (struct Object *)(*theCell);
    
    if ((tail != obj) && obj->GCAttr > minIndirRef) {
        /* Not in the list yet: Append it. */
        tail->GCAttr = -(long)obj;
        tail=obj;
    }
}

static void collectList(ptr(Object) root)
{
    ptr(Object) theObj;

    set_start_time("collectList");
    
    /* point to self to end list.
     * Cannot be zero-term, as that would make it look unmarked
     * for the scanner.
     */
    root->GCAttr = -(long)root; 
    
    /* Tail is where new objects are appended to the list. */
    tail = root;
    
    for (theObj = root; theObj; theObj=(struct Object*)(-theObj->GCAttr)) {
        scanObject(theObj, appendToList, TRUE);
    }
    /* NULL ternimate list: */
    tail->GCAttr=0;

    set_end_time("collectList");
}

/* scanList:
 */

void scanList(ref (Object) root, void (foreach)(ref (Object) current))
{
    ref (Object) current;
    
    for (current = root; current; current = (ref (Object)) (current -> GCAttr * -1)) {
        foreach(current);
    }
}

/* assignIds:
 */

void insertInInfoTable(ref (Object) current)
{
    long id;
    long *original;

    id = getNextId(l);
    original = (long *)current;

    insertInfoTableEntry(l, id, 0, original);
}
    
void assignIds(ref (Object) root)
{
    set_start_time("assignIds");
    scanList(root, insertInInfoTable);
    set_end_time("assignIds");
}

/* repairObjects:
 */

void repairObjects(void)
{
    long i;

    set_start_time("repairObjects");
    for (i = 0; i < l -> infoTableLength; i++) {
        if (l -> infoTable[i].original) {
            ((ref (Object)) (l -> infoTable[i].original)) -> GCAttr =
                l -> infoTable[i].oldGC;
        }
    }
    set_end_time("repairObjects");
}
 
/* : Methods on liniarizations.
 */

static struct liniarization *createLiniarization()
{
    struct liniarization *l = (struct liniarization *)calloc(1, sizeof(struct liniarization));
    
    /* id counts from 0 and upwards */
    l -> nextId = 0;
    
    l -> infoTableLength = 0;
    l -> infoTable = NULL;
    
    l -> liniarizationTop = INITIALLINLENGTH;
    l -> liniarizationLength = INITIALLINLENGTH;
    l -> liniarization = (char *)memalign(4, INITIALLINLENGTH);
    
    l -> noObjects = 0;
    
    l -> originTableTop = 0;
    l -> originTableLength = 0;
    l -> originTable = NULL;
        
    return l;
}

/* getNextId: */
static long getNextId(struct liniarization *l) {

    /* id counts from 0 and upwards */
    return (l -> nextId++);
}

/* insertInfoTableEntry: */ 
static void insertInfoTableEntry(struct liniarization *l,
                                  long id,
                                  long oldGC,
                                  long *original) {
    int i;
    
    /* Extend infoTable if nessecary */
#if 0
    fprintf(stderr, "insertInfoTableEntry: original = 0x%X\n", (int) original);
#endif
    while (id >= l -> infoTableLength) {
        long newLength = l -> infoTableLength * 2 + 1;
        struct infoTableEntry *new =
            (struct infoTableEntry *)malloc(sizeof(struct infoTableEntry)*newLength);
        
        /* copy old table to new table */
        memcpy(new, l -> infoTable, sizeof(struct infoTableEntry) * l -> infoTableLength);
        
        /* clear the remaining entries */
        for(i = l -> infoTableLength; i < newLength; i++) {
            new[i].original = 0;
            new[i].byteOffset = -1;
            new[i].oldGC = 0;
        }
        
        if (l -> infoTable) {
            free(l -> infoTable);
            l -> infoTable = NULL;
        }
        l -> infoTable = new;
        l -> infoTableLength = newLength;
    }
    
    /* insert in table */
    (l -> infoTable)[id].byteOffset = -1;
    (l -> infoTable)[id].oldGC = oldGC;
    (l -> infoTable)[id].original = original;
}


static void freeLiniarization(struct liniarization *l) {
    if (l) {
        if (l -> infoTable) {
            free(l -> infoTable);
            l -> infoTable = NULL;
        }
        if (l -> liniarization) {
            free(l -> liniarization);
            l -> liniarization = NULL;
        }
        if (l -> originTable) {
            free(l -> originTable);
            l -> originTable = NULL;
        }
        free(l);
    }
}

static long copyObjectToLiniarization(struct liniarization *l, struct Object *theObj) {
    long        size;
    long        offset;
    
    offset = l -> liniarizationTop;

    size = 4*ObjectSize( theObj);     
    
    /* Extend liniarization if nessecary */
    
    while (l -> liniarizationLength - l -> liniarizationTop < size) {
        long newLength = l -> liniarizationLength * 2 + 1;
        char *new =
            (char *)memalign(4, newLength);
        
        /* copy old liniarization to new table */
        memcpy(new, l -> liniarization, l -> liniarizationLength);
        
        if (l -> liniarization) {
            free(l -> liniarization);
            l -> liniarization = NULL;
        }
        l -> liniarization = new;
        l -> liniarizationLength = newLength;
    }
    
    /* copy the object to the liniarization */
    
    {
        struct Object *newObj;
        register long *src;
        register long *dst;
        register long *theEnd;
        
        newObj = (struct Object *)&(l -> liniarization)[l -> liniarizationTop];
        theEnd = (long *)(((long) newObj) + size);
        src = (long *) theObj;
        dst = (long *) newObj;
        while( dst < theEnd) *dst++ = *src++; 
        l -> liniarizationTop = l -> liniarizationTop + size;
    }

    l -> noObjects++;
    return offset;
}

static void scanObject(struct Object *obj,
                       void (referenceAction)(struct Object *obj,
                                              struct Object **theCell),
                       int doPartObjects)
{
    ptr (ProtoType) theProto;
    
#if 0
    fprintf(stderr, "scanObject: Scanning object 0x%X\n", (int) obj);
#endif
    
    theProto = obj->Proto;
    if (isSpecialProtoType(theProto)) {
        switch (SwitchProto(theProto)) {
          case SwitchProto(ByteRepPTValue):
          case SwitchProto(ShortRepPTValue):
          case SwitchProto(DoubleRepPTValue):
          case SwitchProto(LongRepPTValue): 
              break; /* No references in this type of object, so do nothing */
              
          case SwitchProto(DynItemRepPTValue):
              fprintf(output, "liniarize.c: DynItemRepPTValue not handled\n");
              break;
              
          case SwitchProto(DynCompRepPTValue):
              fprintf(output, "liniarize.c: DynCompRepPTValue not handled\n");
              break;
              
          case SwitchProto(RefRepPTValue):
              /* Scan the repetition and change them to indirect */
          {
              ptr(long) pointer;
              register long size, index;
              
              size = toRefRep(obj)->HighBorder;
              pointer =  (ptr(long)) &toRefRep(obj)->Body[0];
              
              for (index=0; index<size; index++) {
                  if (*pointer) {
                      referenceAction(obj, (struct Object **)pointer);
                  }
                  pointer++;
              }
              break;
          }
          
          case SwitchProto(ComponentPTValue):
              fprintf(output, "liniarize.c: ComponentPTValue not handled\n");
              break;
              
          case SwitchProto(StackObjectPTValue):
              fprintf(output, "liniarize.c: StackObjectPTValue not handled\n");
              break;
              
          case SwitchProto(StructurePTValue):
              fprintf(output, "liniarize.c: StructurePTValue not handled\n");
              break;
              
          case SwitchProto(DopartObjectPTValue):
              break;
        }
    } else {
        struct GCEntry *tab =
            (struct GCEntry *) ((char *) theProto + theProto->GCTabOff);
        ptr(short) refs_ofs;
        ptr(long)  theCell;
        
        /* Handle all the static objects. 
         *
         * The static table, tab[0], tab[1], ..., 0,
         * contains all static objects on all levels.
         * The way to determine the level of an static object is to 
         * compare the Offset (StaticOff) and the
         * Distance_To_Inclosing_Object (OrigOff).
         */

        if (doPartObjects) {
            for (;tab->StaticOff; ++tab) {
                scanObject((ref(Object))((long *)obj + tab->StaticOff), referenceAction, FALSE);
            }
        }
        else {
            for (;tab->StaticOff; ++tab) {
                ;
            }
        }
        
        /* Handle all the references in the Object. */
        for (refs_ofs = (short *)&tab->StaticOff+1; *refs_ofs; ++refs_ofs) {
            long refType = (*refs_ofs) & 3;
            theCell = (ptr(long)) ((char *)obj + *refs_ofs - refType);
            /* sbrandt 24/1/1994: 2 least significant bits in prototype 
             * dynamic offset table masked out. As offsets in this table are
             * always multiples of 4, these bits may be used to distinguish
             * different reference types. */ 
            if (*theCell) {
                referenceAction(obj, (struct Object **)theCell);
            }
        }
    }
}

static void copyObjects(struct liniarization *l,
                        void (redirect)(struct Object *obj, struct Object **theCell)) {
    long i;
    long id;
    long absAddr;
    
    /* Copy objects to linearization and leave forward pointer */
    for (i = 0; i < l -> infoTableLength; i++) {
        if (l -> infoTable[i].original) {
            l -> infoTable[i].byteOffset =
                copyObjectToLiniarization(l, (ref (Object)) (l -> infoTable[i].original));
            ((ref (Object)) (l -> infoTable[i].original)) -> GCAttr = i;
        }
    }
    
    /* scan and redirect all pointers */
    for (i=0; i < l -> infoTableLength; i++) {
        if (l -> infoTable[i].original) {
            id = ((ref (Object)) (l -> infoTable[i].original)) -> GCAttr;
            absAddr = (long) LIN_IDTOOBJECT(l, id);
            scanObject((ref (Object))absAddr, redirect, TRUE);
        }
    }
}

static void redirectAbsolute(ref (Object) obj,
                             handle (Object) theCell) {
    *theCell = LIN_IDTOOBJECT(l, ((*theCell) -> GCAttr));
}


static void redirectIndirect(ref (Object) obj,
                             handle (Object) theCell) {
    *theCell = (ref (Object)) MAPTOINDIRECT((*theCell) -> GCAttr);
}


static void copyObjectsAbsolute(struct liniarization *l) {
    copyObjects(l, redirectAbsolute);
}

static void copyObjectsIndirect(struct liniarization *l) {
    set_start_time("copyObjectsIndirect");
    copyObjects(l, redirectIndirect);
    set_end_time("copyObjectsIndirect");
}

/* linearizeAbsolute: Wrapper for use from beta */
long linearizeAbsolute(struct Object *root) {
    long newRoot;

    /* Clean up previous data, if any */
    if (l) {
        freeLiniarization(l);
        l = NULL;
    }
    
    /* l will point to the liniarization into
     * wich the objects are moved
     */
    collectList(root);
    
    l = createLiniarization();
    assignIds(root);
    copyObjectsAbsolute(l);
    repairObjects();
    
    newRoot = (long) LIN_IDTOOBJECT(l, 0);
    return newRoot;
}

/* linearizeIndirect: Wrapper for use from beta */
long linearizeIndirect(struct Object *root) {

    /* Clean up previous data, if any */
    if (l) {
        freeLiniarization(l);
        l = NULL;
    }
    
    /* l will point to the liniarization into
     * wich the objects are moved
     */
    collectList(root);
    
    l = createLiniarization();
    assignIds(root);
    copyObjectsIndirect(l);
    repairObjects();
    
    return (long) -1;
}

void assignIndirRef(struct Object **theCell, long id) {
    *(long *)theCell = (long)id;
}

static void scanOrigins(void) {
    /* scan each object in the liniarization and print the origin
       reference */
    int i;
    long absAddr, byteOffset, originOffset, indirOriginRef;
    ref (Object) theObj;
    long *origin;
    
    for (i = 0; i < l -> infoTableLength; i++) {
        if (l -> infoTable[i].original) {
            byteOffset = l -> infoTable[i].byteOffset;

            /* get a pointer to the object in the liniarization */
            absAddr = (long) (l -> liniarization + byteOffset);
            theObj = (struct Object *)absAddr;
            
            /* get a pointer to the cell holding the origin */
            if (!isSpecialProtoType(theObj -> Proto))
            {
                originOffset = theObj -> Proto -> OriginOff;
                origin = (long *)((char *)theObj + originOffset*4);
                
                /* get the origin reference */
                indirOriginRef = *origin;
                
                if (indirOriginRef) {
                    printf("id = %lu, contents = %lu, offset = %lu, referredObj = 0x%X\n",
                           (long) i,
                           MAPTOINDIRECT(indirOriginRef),
                           (long) originOffset,
                           (int) LIN_IDTOOBJECT(l, i));
                }
            }
        }
    }
}

void checkIndirReference(struct Object *obj, struct Object **theCell) {

    if ((int) *theCell > 0) {
        fprintf(stderr, "checkIndirReference: ref at offset %lu in object 0x%X should be indirect (%lu)\n",
                (long) theCell - (long) obj, (int) obj, (long) *theCell);
#if 0
    } else {
        fprintf(stderr, "checkIndirReference: ref at offset %lu in object 0x%X is OK (%lu)\n",
                (long) theCell - (long) obj, (int) obj, (long) *theCell);
#endif
    }
}

static void checkLinearization(void) {
    long i;
    
    for (i = 0; i < l -> infoTableLength; i++) {
        if (l -> infoTable[i].original) {
            scanObject(LIN_IDTOOBJECT(l, i), checkIndirReference, TRUE);
        }
    }
}

void dumpLiniarizationToDisk(void) {
    set_start_time("dumpLiniarizationToDisk");
    dumpToDisk(l);
    set_end_time("dumpLiniarizationToDisk");
}

static void dumpToDisk(struct liniarization *l) {
    int fd;
    
    fd = open("psstore", O_WRONLY | O_CREAT);
    
    if (fd != -1) {
        /* write the 'nextId' to the file */
        write(fd, (void *)&(l -> nextId), sizeof(long));
        
        /* write the 'infoTableLength' to the file */
        write(fd, (void *)&(l -> infoTableLength), sizeof(long));
        
        /* write the info table to the file */
        write(fd, (void *)(l -> infoTable), sizeof(infoTableEntry) * l -> infoTableLength);

        /* write the 'liniarizationTop' to the file */
        write(fd, (void *)&(l -> liniarizationTop), sizeof(long));
        
        /* write the 'liniarizationLength' to the file */
        write(fd, (void *)&(l -> liniarizationLength), sizeof(long));
        
        /* write the liniarization to the file */
        write(fd, (void *)(l -> liniarization), l -> liniarizationLength);
        
        /* write the 'noObjects' to the file */
        write(fd, (void *)&(l -> noObjects), sizeof(long));
        
        close(fd);
    } else {
        fprintf(output, "could not open file for write\n");
    }
}

long loadLiniarizationFromDisk(void) {
    set_start_time("loadLiniarizationFromDisk");
    if (l) {
        freeLiniarization(l);
        l = NULL;
    }
    l = loadFromDisk();
    set_end_time("loadLiniarizationFromDisk");
    
    /* The root always has id = -1 */
    return -1;
}

static struct liniarization *loadFromDisk(void) {
    int fd;
    struct liniarization *l;
    
    fd = open("psstore", O_RDONLY);
    l = (struct liniarization *)calloc(1, sizeof(struct liniarization));
    
    if (fd != -1) {
        /* go to beginning of file */
        lseek(fd, 0, SEEK_SET);
        
        /* read the 'nextId' from the file */
        read(fd, (void *)&(l -> nextId), sizeof(long));
        
        /* read the 'infoTableLength' from the file */
        read(fd, (void *)&(l -> infoTableLength), sizeof(long));
        
        /* read the infoection table from the file */
        l -> infoTable = (struct infoTableEntry *)malloc(sizeof(struct infoTableEntry)*
                                                           (l -> infoTableLength));
        read(fd, (void *)(l -> infoTable), sizeof(infoTableEntry) * l -> infoTableLength);

        /* read the 'liniarizationTop' from the file */
        read(fd, (void *)&(l -> liniarizationTop), sizeof(long));
        
        /* read the 'liniarizationLength' from the file */
        read(fd, (void *)&(l -> liniarizationLength), sizeof(long));
        
        /* read the liniarization from the file */
        l -> liniarization = (char *)memalign(4, l -> liniarizationLength);
        read(fd, (void *)(l -> liniarization), l -> liniarizationLength);

        /* read the 'noObjects' from the file */
        read(fd, (void *)&(l -> noObjects), sizeof(long));
        
        close(fd);
    } else {
        fprintf(output, "could not open file for read\n");
    }
    return l;
}
        
#endif /* LIN */
