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
static void appendToList(struct Object *theObj, struct Object **theCell);
static void appendToListNoIOA(struct Object *theObj, struct Object **theCell);
static void initialCollectList(ptr(Object) root,
                               void (referenceAction)(struct Object *obj,
                                                      struct Object **theCell));
static void extendCollectList(ptr(Object) root,
                              void (referenceAction)(struct Object *obj,
                                                     struct Object **theCell));
static void collectLiveObjectsInAOA(void);
static void scanList(ref (Object) root, void (foreach)(ref (Object) current));
static struct liniarization *createLiniarization(void);
static void freeLiniarization(struct liniarization *l);
static long copyObjectToLiniarization(struct liniarization *l, struct Object *theObj);
static void scanObject(struct Object *obj,
                       void (referenceAction)(struct Object *obj,
                                              struct Object **theCell),
                       int doPartObjects);
static void copyLeaveOffset(ref (Object) current);
static void leaveForward(ref (Object) current);
static void redirectPointers(struct Object *obj,
                             struct Object **theCell);
static void redirectPointersToLinearization(ref (Object) current);
static long fileExists(char *name); 
static long fileOpen(char *name); 
static void dumpToDisk(struct liniarization *l);
static void loadFromDisk(struct liniarization *l);
static long getRoot(struct liniarization *l) ;

/* GLOBAL FUNCTIONS */
long linearizeAbsoluteMove(struct Object *root);
void redirectPointersInAOA(void);
void assignRefNoGC(struct Object **theCell, long id);
void dumpLiniarizationToDisk(void);
long linOpenRead(char *name);
long linClose(void);
long linOpenWrite(char *name);
long linCreate(char *name);
long loadLiniarizationFromDisk(void);

/* LOCAL MACROS */

#define FILEACCESSERROR -1
#define FILENOTFOUND -2
#define FILEALREADYOPEN -3
#define FILEOK -4
#define FILEEXISTS -5

/* Copied in proxyRef.c, make sure to update if you change below */
#define INITIALLINLENGTH 4

/* GLOBAL VARIABLES */
struct liniarization *l = NULL;

/* Build a linked list of all objects reachable from root in the
 * GCfield of the objects.  This often conflicts with the GC'er, so be
 * careful...  The refernces are negated when written to GCAttr so
 * that they can be distinguished from forward pointers left by the
 * GC.  THIS COMMENT IS NO LONGER VALID
 *
 * Instead it is now checked whether an object has been visited in the
 * same way as in IOAGc, namely by checking if the value of the
 * GCAttribute is larger that IOAMaxAge, in which case it is a forward
 * pointer or a link pointer meaning that it has been moved.
 */

static ptr(Object) head;   /* Head of list build by collectList */
static ptr(Object) tail;   /* Tail of list build by collectList */
static long totalsize;

/* How to append objects to the list regardless where they are */

static void appendToList(struct Object *theObj, struct Object **theCell)
{
    ptr(Object) obj = (struct Object *)(*theCell);

    if ((tail != obj) && obj->GCAttr < IOAMaxAge) {
        /* Not in the list yet: Append it. */
        tail->GCAttr = (long)obj;
        tail=obj;
    }
}

static void appendToListNoIOA(struct Object *theObj, struct Object **theCell)
{
    ptr(Object) obj = (struct Object *)(*theCell);

    if (!inIOA(theObj)) {
        if ((tail != obj) && obj->GCAttr < IOAMaxAge) {
            /* Not in the list yet: Append it. */
            tail->GCAttr = (long)obj;
            tail=obj;
        }
    }
}

static void initialCollectList(ptr(Object) root,
                               void (referenceAction)(struct Object *obj,
                                                      struct Object **theCell))
{
    ptr(Object) theObj;

    set_start_time("initialCollectList");
    
    /* point to self to end list.
     * Cannot be zero-term, as that would make it look unmarked
     * for the scanner.
     */
    root->GCAttr = (long)root; 
    
    /* Tail is where new objects are appended to the list.
     * Objects after tail in the list have not been processed yet.
     */
    tail = root;

    /* Head is the first object in the list. All objects in the
     * list may be reached through head.  
     */
    head = root;

    /* There are no objects in the list yet. */
    totalsize = 0;

    
    for (theObj = root; theObj; theObj=(struct Object*)(theObj->GCAttr)) {
        totalsize += ObjectSize(theObj);
        scanObject(theObj, referenceAction, TRUE);
    }
    /* NULL ternimate list: */
    tail->GCAttr=0;

    set_end_time("initialCollectList");
}

static void extendCollectList(ptr(Object) root,
                              void (referenceAction)(struct Object *obj,
                                                     struct Object **theCell))
{
    ptr(Object) theObj;

    set_start_time("extendCollectList");
    
    DEBUG_CODE(Claim((int)tail, "extendCollectList without initialCollectList"));

    /* Check that root is not already marked as being in the list */
    if ((tail != root) && root->GCAttr <= IOAMaxAge) {

        /* point to self to end list.
         * Cannot be zero-term, as that would make it look unmarked
         * for the scanner.
         */
        root->GCAttr = (long)root; 
        
        /* Append root to list */
        tail->GCAttr = (long)root;
        tail = root;
        
        for (theObj = root; theObj; theObj=(struct Object*)(theObj->GCAttr)) {
            totalsize += ObjectSize(theObj);
            scanObject(theObj, referenceAction, TRUE);
        }
        /* NULL terminate list: */
        tail->GCAttr=0;
    }
    set_end_time("extendCollectList");
}

/* collectLiveObjectsInAOA:
 */

static void collectLiveObjectsInAOA(void) 
{
    /* All live objects in AOA are linked together in their GCattr */
    
    ptr(long) pointer = AOArootsLimit;
    
    pointer--;
    
    initialCollectList((ref (Object))*pointer, appendToListNoIOA);
    
    while( pointer > AOArootsPtr) {
        pointer--;
        /* Now *pointer is a root reference */
        extendCollectList((ref (Object))*pointer, appendToListNoIOA);
    }
    
    /* *AOArootsLimit now points to the head in the list of all live
       objects in AOA */
}

/* scanList:
 */

static void scanList(ref (Object) root, void (foreach)(ref (Object) current))
{
    ref (Object) cur;
    
    for (cur = root; cur; cur = (ref (Object)) (cur -> GCAttr)) {
        foreach(cur);
    }
}

/* : Methods on liniarizations.
 */

static struct liniarization *createLiniarization()
{
    struct liniarization *l = (struct liniarization *)calloc(1, sizeof(struct liniarization));

    l -> fd = -1;
    l -> name = NULL;
    
    /* id counts from 0 and upwards */
    l -> liniarizationTop = INITIALLINLENGTH;
    l -> liniarizationLength = INITIALLINLENGTH;
    l -> liniarization = (char *)memalign(4, INITIALLINLENGTH);
    
    l -> noObjects = 0;
    
    return l;
}

static void freeLiniarization(struct liniarization *l)
{
    if (l) {
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

static long copyObjectToLiniarization(struct liniarization *l, struct Object *theObj)
{
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
              /* Scan the repetition and apply referenceAction */
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

static void copyLeaveOffset(ref (Object) current) 
{
    current -> Proto = (ref(ProtoType))
        copyObjectToLiniarization(l, current);
}

static void leaveForward(ref (Object) current) 
{
    current -> GCAttr = (long)
        (l -> liniarization + (long) current -> Proto);
}

static void redirectPointers(struct Object *obj,
                             struct Object **theCell)
{
    if (inLIN((*theCell) -> GCAttr)) {
        *theCell = (ref (Object))((*theCell) -> GCAttr);
    }
}

static void redirectPointersToLinearization(ref (Object) current) 
{
    scanObject(current, redirectPointers, TRUE);
    current -> GCAttr = 0;
}

void redirectPointersInAOA(void) 
{
    /* step 5 */
    collectLiveObjectsInAOA();
    
    /* step 6 */
    scanList((ref (Object))*AOArootsLimit, redirectPointersToLinearization);
}

long linearizeAbsoluteMove(struct Object *root)
{
    /* Clean up previous data, if any */
    if (l) {
        freeLiniarization(l);
        l = NULL;
    }
    
    /* l will point to the liniarization into
     * wich the objects are moved
     */

    /* This function copies the transitive closure of 'root' into the
       linearization and redirects all pointers to these objects in
       all heaps (not entirely correct since LVRA, amongst other
       areas, are not supported) to their copy in the
       linearization. Thus the transitive closure is in fact 'moved'
       to the linearization, and the original copies are no longer
       accessible to anyone ever again. This is done in the following
       steps,

       1) The transitive closure is linked together in the
       GCattributes of the objects

       2) This list is scanned and all objects copied to the
       linearization, leaving the offset of (the copy of the object in
       the linearization) in the prototype pointer of the object. The
       absolute address cannot be left at this point since the
       linearization may extend itself several times.
       
       3) After 2) where all the objects has been copied to the
       linearization, the size of the linearization is fixed, and
       objects within it will not move anymore. Thus a second scan of
       the transitive closure is made and an absolute forward pointer
       is left in the GCAttr of the objects.
       
       4) An ioaGC is executed. This will automaticly redirect all
       references from IOA to objects now residing in the
       linearization. Also IOAGc builds a list of AOAroots.
       
       5) Based on the list of AOARoots all live objects in AOA are
       linked together in their GCAttribute.
       
       6) All live objects in AOA are scanned and any references to
       objects now residing in the linearization are redirected. At
       the same time the GCAttribute is cleared.
       
    */
    
    /* step 1 */
    initialCollectList(root, appendToList);
    
    /* step 2 */
    scanList(root, copyLeaveOffset);
    
    /* step 3 */
    scanList(root, leaveForward);

    /* step 4 */
    doRedirectPointersInAOA = TRUE;
    IOAGc();

    /* step 5 */

    /* step 6 */
    
    /* step 5 and 6 are both execute by IOAGc which calls
     * 'redirectPointersInAOA' above
     */
    
    return getRoot(l);
}

void assignRefNoGC(struct Object **theCell, long id)
{
    *(long *)theCell = (long)id;
}

void dumpLiniarizationToDisk(void)
{
    set_start_time("dumpLiniarizationToDisk");
    dumpToDisk(l);
    set_end_time("dumpLiniarizationToDisk");
}

static long fileExists(char *name) 
{
    int fd;
    
    fd = open(name, O_RDONLY);
    if (fd < 0) {
        return 0;
    } 
    close(fd);
    return 1;
}

static long fileOpen(char *name) 
{
    if (l -> name) {
        if (strcmp(l -> name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

long linOpenRead(char *name)
{
    if (fileOpen(name)) {
        return FILEALREADYOPEN;
    }

    if (!fileExists(name)) {
        return FILENOTFOUND;
    }

    freeLiniarization(l);
    l = createLiniarization();
    
    if ((l -> fd = open(name, O_RDONLY)) < 0) {
        return FILEACCESSERROR;
    }

    l -> name = strdup(name);
    return FILEOK;
}

long linOpenWrite(char *name)
{
    if (fileOpen(name)) {
        return FILEALREADYOPEN;
    }
    
    if (!fileExists(name)) {
        return FILENOTFOUND;
    }

    freeLiniarization(l);
    l = createLiniarization();
    
    if ((l -> fd = open(name, O_RDWR)) < 0) {
        return FILEACCESSERROR;
    }
    
    l -> name = strdup(name);
    return FILEOK;
}

long linClose(void) 
{
    if (l) {
        close(l -> fd);
    }
    freeLiniarization(l);
    return FILEOK;
}

long linCreate(char *name)
{

    if (fileOpen(name)) {
        return FILEALREADYOPEN;
    }
    
    if (fileExists(name)) {
        return FILEEXISTS;
    }

    freeLiniarization(l);
    l = createLiniarization();
    
    if ((l -> fd = open(name, O_RDWR | O_CREAT)) < 0) {
        return FILEACCESSERROR;
    }
    
    l -> name = strdup(name);
    return FILEOK;
}
    
static void dumpToDisk(struct liniarization *l)
{
    int fd;
    
    fd = l -> fd;
    
    if (fd != -1) {
        /* write the 'liniarizationTop' to the file */
        write(fd, (void *)&(l -> liniarizationTop), sizeof(long));
        
        /* write the 'liniarizationLength' to the file */
        write(fd, (void *)&(l -> liniarizationLength), sizeof(long));
        
        /* write the liniarization to the file */
        write(fd, (void *)(l -> liniarization), l -> liniarizationLength);
        
        /* write the 'noObjects' to the file */
        write(fd, (void *)&(l -> noObjects), sizeof(long));
        
    } else {
        fprintf(output, "dumpToDisk:file not open\n");
    }
}

static void loadFromDisk(struct liniarization *l)
{
    int fd;
    
    fd = l -> fd;
    
    if (fd != -1) {
        /* go to beginning of file */
        lseek(fd, 0, SEEK_SET);
        
        /* read the 'liniarizationTop' from the file */
        read(fd, (void *)&(l -> liniarizationTop), sizeof(long));
        
        /* read the 'liniarizationLength' from the file */
        read(fd, (void *)&(l -> liniarizationLength), sizeof(long));
        
        /* read the liniarization from the file */
        l -> liniarization = (char *)memalign(4, l -> liniarizationLength);
        read(fd, (void *)(l -> liniarization), l -> liniarizationLength);
        
        /* read the 'noObjects' from the file */
        read(fd, (void *)&(l -> noObjects), sizeof(long));
        
    } else {
        fprintf(output, "loadFromDisk: could not read from file. Not open?\n");
    }
}

static long getRoot(struct liniarization *l) 
{
    return (long) (l->liniarization + 4);
}

long loadLiniarizationFromDisk(void)
{
    set_start_time("loadLiniarizationFromDisk");
    loadFromDisk(l);
    set_end_time("loadLiniarizationFromDisk");
    
    return getRoot(l);
}

        
#endif /* LIN */
