#include "beta.h"

#if defined(LIN)
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "liniarize.h"


#define USEREFSTACK 0

/* GC/objectsize.c */
/* extern long ObjectSize(ref(Object)); */

/* data.h */
/* extern   long     noAOAGC  ; */

/* sighandler.c */
extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);

/* LOCAL MACROS */

#define MAPTOINDEX(id) ((id * -1) - 1)
#define KnownMask 0x80900000
#define instructionOk(instruction) ((instruction & KnownMask) == (KnownMask))
#define sourceReg(instruction) (instruction & 0x0000001F)

/* LOCAL TYPE DEFINITIONS */

#if USEREFSTACK
typedef struct stackElement {
    /* a stack element identifies a reference in an object that needs
     * to be handled. This reference is identified by the id of the
     * object and the offset of the cell containing the reference
     */
    long id;
    long offset; /* Offset in bytes */
} stackElement;
#endif

/* GLOBAL FUNCTION DECLARATIONS */

long scanFromRoot(struct Object *root);
void assignIndirRef(struct Object **theCell, long id);
void initIndirTrapHandler (void);
void doPrintLiniarizationStatistics();
void dumpLiniarizationToDisk(void);
long loadLiniarizationFromDisk(void);

/* And more of those by MG:  Use GC field for linked list */
void copyToLiniarization(ptr(Object) root);
long createIndirTable(ptr(Object) root);
void SwizzleToIndirect(void);
void linearizeInGC(ptr(Object) root);


/* LOCAL FUNCTION DECLARATIONS */

#if USEREFSTACK
static long scanRefs(struct Object *theObj); */
static void pushRef(struct stackElement ***stack,
                    int *t,
                    int *l,
                    struct stackElement *next);
static struct stackElement *popRef(struct stackElement **stack, int *t, int *l);
static struct stackElement *allocStackElement(long id, long offset);
#endif

static long copyObjectToLiniarization(struct liniarization *l, struct Object *theObj);
static void insertIndirTableEntry(struct liniarization *l, long id, long byteOffset);
static long getNextId(struct liniarization *l);
static struct liniarization *createLiniarization();
static void freeLiniarization(struct liniarization *l);
static void indirTrap(long sig, siginfo_t *info, ucontext_t *ucon);
static void swizzleIndirOrigins(struct liniarization *l);
static void setStartOfLiniarization(struct liniarization *l);
static void setEndOfLiniarization(struct liniarization *l);
static void printLiniarizationStatistics(struct liniarization *l);
static void dumpToDisk(struct liniarization *l);
static struct liniarization *loadFromDisk(void);
static void unSwizzleIndirOrigins(struct liniarization *l);
static void insertInOriginTable(long byteOffset,
                                long indirRef,
                                struct liniarization *l);
static long getLoadTime(struct liniarization *l);
static long getSaveTime(struct liniarization *l);
static void setStartOfLoad(struct liniarization *l);
static void setEndOfLoad(struct liniarization *l);
static void setStartOfSave(struct liniarization *l);
static void setEndOfSave(struct liniarization *l);

/* GLOBAL VARIABLES */

struct liniarization *l = NULL;
long returnPC, returnSP, absAddr;

/* LOCAL VARIABLES */
#if USEREFSTACK
static struct stackElement **stack = NULL;
static int top = 0;
static int length = 0;
#endif

long indirRefsFollowed = 0;

/* scanFromRoot: Wrapper for use from beta */
long scanFromRoot(struct Object *root)
{
    long id;

    linearizeInGC(root);
    copyToLiniarization(root);
    id = createIndirTable(root);
    SwizzleToIndirect();

    return id;
}


/* Copy all objects reachable from root into newly created liniarization.
 * Assumes that 
 *      linearizeInGC(root);
 * has just been performed and that no mutator/garbage collector work has 
 * taken place since that, so that the linked list in still valid.
 */

void copyToLiniarization(ptr(Object) root) 
{
    ptr(Object) next;
    ptr(Object) obj;
    long offset;
    
    /* Clean up previous data, if any */
    if (l) {
        freeLiniarization(l);
        l = NULL;
    }
    
    /* l will point to the liniarization into
     * wich the objects are moved
     */
    l = createLiniarization();
    setStartOfLiniarization(l);

    /* While there still are unhandled objects in the list */
    for (obj = root; obj; obj = next) {
        next = (ptr(Object))(obj->GCAttr);
        
        /* The object is now moved to the liniarization */
        offset = copyObjectToLiniarization(l, obj);

        /* Overwrite linked list in original objects with
         * offset in liniarization.  (A forwarding pointer)
         */
        obj->GCAttr = offset;
    }
}

#define LIN_OFFSETTOOBJECT(l, offset) ((ptr(Object))(l -> liniarization + offset))

long createIndirTable(ptr(Object) root)
{
    long id, offset;
    ptr(Object) origobj;
    ptr(Object) copyobj;

    origobj = root;

    while (origobj) {
        id = getNextId(l);

        /* Find copied object from original */
        offset = origobj->GCAttr;
        copyobj = LIN_OFFSETTOOBJECT(l, offset);

        /* We indicate in the indirection table that object with id 'id'
         * is located in the liniarization at offset 'offset'
         */
        insertIndirTableEntry(l, id, offset);

        /* Mark the original object with its own id for reverse lookup */
        origobj->GCAttr = id;

        /* Next. */
        origobj = (ptr(Object))(copyobj->GCAttr);

        /* Mark the copy of the object with its own id for reverse lookup */
        copyobj->GCAttr = id;
    }
    
    /* return id of root */
    return root->GCAttr;
}

        
void SwizzleToIndirect(void)
{
    long id, index,offset;
    ptr(Object) obj;
    ptr (ProtoType) theProto;

    for (id = -1; id > l->nextId; id--) {
        index = MAPTOINDEX(id);
        offset = (l -> indirTable)[index].byteOffset;
        obj = LIN_OFFSETTOOBJECT(l, offset);

        theProto = obj->Proto;
        if (isSpecialProtoType(theProto)) {
            switch (SwitchProto(theProto)) {
              case SwitchProto(ByteRepPTValue):
              case SwitchProto(ShortRepPTValue):
              case SwitchProto(DoubleRepPTValue):
              case SwitchProto(LongRepPTValue): 
                  break; /* No references in this type of object, so do nothing*/
                  
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
                          *pointer  = ((struct Object*)(*pointer))->GCAttr;
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
        
            for (;tab->StaticOff; ++tab) {
                if (tab->StaticOff == -tab->OrigOff) {
                    /* What should be done here?
                     * If all refs are in the table handled below,
                     * there is nothing to do.  Otherwise, there must
                     * be refs that can only be found be scanning the ref
                     * tables of these partobjects...?
                     */
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
                    *theCell = ((struct Object*)(*theCell))->GCAttr;
                }
            }
        }
    }

    /* l now contains the liniarization of the transitive closure of
       the root. All references within this liniarization has been
       changed to indirect references. The ref-none check made by the
       system will catch all indirect references and if a proper
       traphandler is installed this traphandler can calculate the
       current absolute address of the referred object. This is true
       for all dynamic references, but not for origin references. Thus
       origin references cannot be indirect when the liniarization is
       in memory, but they still have to be when the liniarization is
       on disk. Thus when a liniarization enters memory all indirect
       origin references has to be swizzeled, and when the
       liniarization leaves memory all absolute origin references into
       the liniarization has to be unswizzled. IF all absolute origin
       references into the liniarization all originates from objects
       in the liniarization, all is well, BUT if an absolute origin
       reference has been passed on and saved somwhere outside the
       liniarization this reference cannot be unswzzeled! How often
       and in which cases is an origin reference copied outside the
       liniarization?  */
    
    swizzleIndirOrigins(l);
    
    setEndOfLiniarization(l);
}

 

void assignIndirRef(struct Object **theCell, long id) {
    *(long *)theCell = (long)id;
}

/* : Methods on liniarizations.
 */

static struct liniarization *createLiniarization() {
    struct liniarization *l = (struct liniarization *)calloc(1, sizeof(struct liniarization));
    
    /* id counts from -1 and downwards */
    l -> nextId = -1;
    
    l -> indirTableLength = 0;
    l -> indirTable = NULL;
    
    l -> liniarizationTop = 0;
    l -> liniarizationLength = 0;
    l -> liniarization = NULL;
    
    l -> noObjects = 0;
    
    l -> originTableTop = 0;
    l -> originTableLength = 0;
    l -> originTable = NULL;
        
    return l;
}

/* getNextId: */
static long getNextId(struct liniarization *l) {

    /* id counts from -1 and downwards */
    return (l -> nextId--);
}

/* insertIndirTableEntry: */ 
static void insertIndirTableEntry(struct liniarization *l, long id, long byteOffset) {
    int i;
    
    /* Extend indirTable if nessecary */
    
    /* id counts from -1 and downwards, this is mapped to
     * count from 0 and upwards
     */
    while (MAPTOINDEX(id) >= l -> indirTableLength) {
        long newLength = l -> indirTableLength * 2 + 1;
        struct indirTableEntry *new =
            (struct indirTableEntry *)malloc(sizeof(struct indirTableEntry)*newLength);

        /* copy old table to new table */
        memcpy(new, l -> indirTable, sizeof(struct indirTableEntry) * l -> indirTableLength);
        
        /* clear the remaining entries */
        for(i = l -> indirTableLength; i < newLength; i++) {
            new[i].byteOffset = -1;
        }
        
        if (l -> indirTable) {
            free(l -> indirTable);
            l -> indirTable = NULL;
        }
        l -> indirTable = new;
        l -> indirTableLength = newLength;
    }
    
    /* insert in table */
    (l -> indirTable)[MAPTOINDEX(id)].byteOffset = byteOffset;
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

static void freeLiniarization(struct liniarization *l) {
    if (l) {
        if (l -> indirTable) {
            free(l -> indirTable);
            l -> indirTable = NULL;
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

/* indirTrap:
 */
static void indirTrap(long sig, siginfo_t *info, ucontext_t *ucon) {
    int instruction;
    long indirRef;
    long offset;
    
    
    if (info->si_trapno-0x80 == 17  /* solaris 2.3, 2.4, 2.5 */ || 
        info->si_trapno-0x100 == 17 /* solaris 2.5.1, 2.6? */
        ) {
        /* Ok, the signal was caused by a "tle 17" trap, meaning either
         * "reference is NONE" or dereference of an indirect reference */
        
        /* Fetch the 'tst %lm' instruction. */
        instruction = (* (long *) (ucon->uc_mcontext.gregs[REG_PC] - 4));
        
        if (instructionOk(instruction)) {
            /* PC to jump to when fetch has completed: */
            returnPC = ucon->uc_mcontext.gregs[REG_PC] - 4; 
            /* SP to restore when fetch has completed: */
            returnSP = ucon->uc_mcontext.gregs[REG_SP]; 
            
            /* flush register windows to stack and fetch value of register causing
             * the trap. */
            __asm__ volatile  ("ta 3");
            
            indirRef = ((int *) returnSP)[sourceReg(instruction) - 16];
            indirRefsFollowed++;
            
            if (isIndirRef(indirRef)) {
                
                /* Ok, so this is a genuine indirect reference, and
                 * not simply a NONE reference.
                 */

                /* Calculate absolute address by looking in the indirtable */
                
                offset = l -> indirTable[MAPTOINDEX(indirRef)].byteOffset;
                absAddr = (long) (l -> liniarization + offset);
                
                /* Return to trap window. */
                __asm__ volatile ("restore; restore ! return to trap window");
                
                /* Now we are back in the register window where the trap occurred.
                 * Only global registers may be changed. Now reset correct sp. (UNIX 
                 * pushed some information on the stack). */
                __asm__ volatile ("sethi %hi(returnSP),%g1 ! reset sp to returnSP");
                __asm__ volatile ("ld [%g1+%lo(returnSP)],%sp");
                
                /* Allocate a new register window to avoid changing trap registers. */
                __asm__ volatile ("save %sp,-64,%sp ! save trap window");
                
                /* Tell compiler to assume nothing about register contents: */
                __asm__ volatile ("" : : : "i0", "i1", "i2", "i3", "i4", "i5", "fp", "i7",\
                                  "o0", "o1", "o2", "o3", "o4", "o5", "sp", "o7", \
                                  "l0", "l1", "l2", "l3", "l4", "l5", "l6", "l7");
                
                /* Get back to returnPC and continue from there. */
                __asm__ volatile ("sethi %hi(returnPC),%g1  ! Jump back to before trap");
                __asm__ volatile ("ld [%g1+%lo(returnPC)],%g1");
                __asm__ volatile ("restore");
                
                /* load the register containing the indirect reference with
                 * the absolute address.  
                 *
                 * sethi i1, %0
                 * ior i1, %0, i1
                 */
                
                __asm__ volatile ("sethi %hi(absAddr),%i2");
                __asm__ volatile ("ld [%i2+%lo(absAddr)],%i2");
                /* try again */
                __asm__ volatile ("jmp %g1; nop");
            }
        } 
    }
    
    /* If we get here, it was not a lazy reference. Call the usual 
     * BetaSignalHandler. */
    BetaSignalHandler (sig, info, ucon);
    indirRef = 0; 
}


/* initIndirTrapHandler:
 */
void initIndirTrapHandler (void) { 
    struct sigaction sa;

    /* Inirreferences are not yet handled by AOAGC */
    noAOAGC = TRUE;

    /* Specify that we want full info about the signal, and that
     * the handled signal should not be blocked while being handled: */
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    
    /* No further signals should be blocked while handling the specified
     * signals. */
    sigemptyset(&sa.sa_mask); 
    
    /* Specify handler: */
    sa.sa_handler = indirTrap;
    
    sigaction (SIGILL,&sa,0);
}

/* swizzleIndirOrigins:
 */

void swizzleIndirOrigins(struct liniarization *l) {
    /* scan each object in the liniarization and swizzle the origin
       reference */
    int i;
    struct Object *theObj;
    long absAddr;
    long byteOffset;
    long indirOriginRef;
    long absOriginRef;
    long *origin;
    short originOffset;
    
    for (i = 0; i < l -> indirTableLength; i++) {
        byteOffset = l -> indirTable[i].byteOffset;
        
        if (byteOffset != -1) {
            
            /* get a pointer to the object in the liniarization */
            absAddr = (long) (l -> liniarization + byteOffset);
            theObj = (struct Object *)absAddr;
            
            /* get a pointer to the cell holding the origin */
            originOffset = theObj -> Proto -> OriginOff;
            origin = (long *)((char *)theObj + originOffset*4);
            
            /* get the origin reference */
            indirOriginRef = *origin;
            
            /* save enough info to enable unswizzling */
            insertInOriginTable((long) ((char *)origin - l -> liniarization), indirOriginRef, l);
            
            /* calculate the absolute address instead */
            byteOffset = l -> indirTable[MAPTOINDEX(indirOriginRef)].byteOffset;
            absOriginRef = (long) (l -> liniarization + byteOffset);
            
            /* set the origin reference */
            *origin = absOriginRef;
        }
    }
}

/* unSwizzleIndirOrigins:
 */

static void unSwizzleIndirOrigins(struct liniarization *l) {
    /* scan each object in the liniarization and unswizzle the origin
       reference */
    int i;
    
    for (i = 0; i < l -> originTableTop; i++) {
        *(long *)(l -> liniarization + l -> originTable[i].byteOffset) =
            l -> originTable[i].indirRef;
    }
}

#if 0
/* ScanRefs:
 *
 * Given a reference to an object all reference slots in this object
 * are scanned and pushed on the stack.
 *
 * - theObj is the reference to the object
 * */

static long scanRefs(struct Object *theObj) { 
    ptr(ProtoType) theProto;
    long id;
    
    /* Allocate new id to this object */
    id = getNextId(l);
    
    /* Mark object as visited by writing the new id in the
     * GCAttribute of the referred object. If this object should
     * be encountered later we can detect that it has been handled
     */
        
    theObj -> GCAttr = id;
    
    theProto = theObj->Proto;
    
    if( isSpecialProtoType(theProto) ){  
        switch( SwitchProto(theProto) ){
          case SwitchProto(ByteRepPTValue):
          case SwitchProto(ShortRepPTValue):
          case SwitchProto(DoubleRepPTValue):
          case SwitchProto(LongRepPTValue): 
              return id; /* No references in this type of object, so do nothing*/
              
          case SwitchProto(DynItemRepPTValue):
              fprintf(output, "liniarize.c: DynItemRepPTValue not handled\n");
              return id;
              
          case SwitchProto(DynCompRepPTValue):
              fprintf(output, "liniarize.c: DynCompRepPTValue not handled\n");
              return id;
              
          case SwitchProto(RefRepPTValue):
              /* Scan the repetition and follow all entries */
          { ptr(long) pointer;
          register long size, index;
          
          size = toRefRep(theObj)->HighBorder;
          pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
          
          for(index=0; index<size; index++) 
              if( *pointer ) {
                  pushRef(&stack,
                          &top,
                          &length,
                          allocStackElement(id, (long) (handle(Object))(pointer++)) - (long)theObj);
              }
              else {
                  pointer++;
              }
          }
          return id;
          
          case SwitchProto(ComponentPTValue):
              fprintf(output, "liniarize.c: ComponentPTValue not handled\n");
              return id;
              
          case SwitchProto(StackObjectPTValue):
              fprintf(output, "liniarize.c: StackObjectPTValue not handled\n");
              return id;
              
          case SwitchProto(StructurePTValue):
              fprintf(output, "liniarize.c: StructurePTValue not handled\n");
              return id;
              
          case SwitchProto(DopartObjectPTValue):
              pushRef(&stack,
                      &top,
                      &length,
                      allocStackElement(id, (long)&(cast(DopartObject)(theObj))->Origin - (long) theObj) );
              return id;
        }
    } else {
        struct GCEntry *tab =
            (struct GCEntry *) ((char *) theProto + theProto->GCTabOff);
        short *refs_ofs;
        struct Object **theCell;
        
        /* Handle all the static objects. 
         *
         * The static table, tab[0], tab[1], 0,
         * contains all static objects on all levels.
         * Here we only need to perform ProcessObject on static objects
         * on 1 level. The recursion in ProcessObject handle other
         * levels. 
         * The way to determine the level of an static object is to 
         * compare the Offset (StaticOff) and the
         * Distance_To_Inclosing_Object (OrigOff).
         */
        
        for (;tab->StaticOff; ++tab) {
            if (tab->StaticOff == -tab->OrigOff) {
                /* Static part objects are handled right away.
                 */
                scanRefs((struct Object *)((long *)theObj + tab->StaticOff)); 
            }
        }
        
        /* Handle all the references in the Object. */
        for (refs_ofs = (short *)&tab->StaticOff + 1; *refs_ofs; ++refs_ofs) {
            theCell = (struct Object **) ((char *) theObj + ((*refs_ofs) & (short) ~3));
            /* sbrandt 24/1/1994: 2 least significant bits in prototype 
             * dynamic offset table masked out. As offsets in this table are
             * always multiples of 4, these bits may be used to distinguish
             * different reference types. */ 
            if (*theCell) {
                pushRef(&stack,
                        &top,
                        &length,
                        allocStackElement(id, (long) theCell - (long) theObj));
            }
        }
        return id;
    }
    return 0;
}


/* pushRef, popRef: Implements a simple efficient stack
 */

static void pushRef(struct stackElement ***stack,
                    int *t,
                    int *l,
                    struct stackElement *next) {
    if (*t>=*l) {
        int newLength = 2 * (*l) + 1;
        struct stackElement **new =
            (struct stackElement **)malloc(sizeof(struct stackElement *) * newLength);
        int count;
        
        for(count = 0; count<*l; count++) {
            new[count]=(*stack)[count];
        }
        if (*stack) {
            free(*stack);
            *stack = NULL;
        }
        *stack = new;
        *l = newLength;
    }
    (*stack)[*t]=next;
    *t = *t + 1;
}

static struct stackElement *popRef(struct stackElement **stack, int *t, int *l) {
    if (*t) {
        *t = *t - 1;
        return stack[*t];
    }
    return NULL;
}

static struct stackElement *allocStackElement(long id, long offset) {    
    struct stackElement *next;
    
    next = (struct stackElement *)malloc(sizeof(struct stackElement));
    next -> id = id;
    next -> offset = offset;
    return next;
}
#endif

static void setStartOfLiniarization(struct liniarization *l) {
    gettimeofday(&(l -> startOfLastLiniarize), NULL);
}

static void setEndOfLiniarization(struct liniarization *l) {
    gettimeofday(&(l -> endOfLastLiniarize), NULL);
}

static void setStartOfLoad(struct liniarization *l) {
    gettimeofday(&(l -> startOfLastLoad), NULL);
}

static void setEndOfLoad(struct liniarization *l) {
    gettimeofday(&(l -> endOfLastLoad), NULL);
}

static void setStartOfSave(struct liniarization *l) {
    gettimeofday(&(l -> startOfLastSave), NULL);
}

static void setEndOfSave(struct liniarization *l) {
    gettimeofday(&(l -> endOfLastSave), NULL);
}

static long getLiniarizationTime(struct liniarization *l) {
    long microStart, microEnd, microDiff;
    
    microStart = l -> startOfLastLiniarize.tv_sec * 1000000 + l -> startOfLastLiniarize.tv_usec;
    microEnd = l -> endOfLastLiniarize.tv_sec * 1000000 + l -> endOfLastLiniarize.tv_usec;
    
    microDiff = microEnd - microStart;
    
    return microDiff;
}

static long getLoadTime(struct liniarization *l) {
    long microStart, microEnd, microDiff;
    
    microStart = l -> startOfLastLoad.tv_sec * 1000000 + l -> startOfLastLoad.tv_usec;
    microEnd = l -> endOfLastLoad.tv_sec * 1000000 + l -> endOfLastLoad.tv_usec;
    
    microDiff = microEnd - microStart;
    
    return microDiff;
}

static long getSaveTime(struct liniarization *l) {
    long microStart, microEnd, microDiff;
    
    microStart = l -> startOfLastSave.tv_sec * 1000000 + l -> startOfLastSave.tv_usec;
    microEnd = l -> endOfLastSave.tv_sec * 1000000 + l -> endOfLastSave.tv_usec;
    
    microDiff = microEnd - microStart;
    
    return microDiff;
}

void doPrintLiniarizationStatistics() {
    if (l) {
        printLiniarizationStatistics(l);
    }
}

static void printLiniarizationStatistics(struct liniarization *l) {
    printf("Time to liniarize (usec) = %lu\n", getLiniarizationTime(l));
    printf("Time to liniarize (sec)  = %lu\n", getLiniarizationTime(l)/1000000);
    printf("Time to load (usec)      = %lu\n", getLoadTime(l));
    printf("Time to load (sec)       = %lu\n", getLoadTime(l)/1000000);
    printf("Time to save (usec)      = %lu\n", getSaveTime(l));
    printf("Time to save (sec)       = %lu\n", getSaveTime(l)/1000000);
    printf("Objects liniarized       = %lu\n", l -> noObjects);
    printf("Size of objects          = %lu\n", l -> liniarizationTop);
    printf("Size of liniarization    = %lu\n",
           l -> liniarizationLength +
           l -> indirTableLength * sizeof(struct indirTableEntry));
    printf("Indir ref followed times = %lu\n", indirRefsFollowed);
}

void dumpLiniarizationToDisk(void) {
    setStartOfSave(l);
    unSwizzleIndirOrigins(l);
    dumpToDisk(l);
    setEndOfSave(l);
}

static void dumpToDisk(struct liniarization *l) {
    int fd;
    
    fd = open("psstore", O_WRONLY | O_CREAT);
    
    if (fd != -1) {
        /* write the 'nextId' to the file */
        write(fd, (void *)&(l -> nextId), sizeof(long));
        
        /* write the 'indirTableLength' to the file */
        write(fd, (void *)&(l -> indirTableLength), sizeof(long));
        
        /* write the indirection table to the file */
        write(fd, (void *)(l -> indirTable), sizeof(indirTableEntry) * l -> indirTableLength);

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
    if (l) {
        freeLiniarization(l);
        l = NULL;
    }
    l = loadFromDisk();
    swizzleIndirOrigins(l);
    setEndOfLoad(l);
    indirRefsFollowed = 0;
    
    /* The root always has id = -1 */
    return -1;
}

static struct liniarization *loadFromDisk(void) {
    int fd;
    struct liniarization *l;
    
    fd = open("psstore", O_RDONLY);
    l = (struct liniarization *)calloc(1, sizeof(struct liniarization));

    setStartOfLoad(l);
    if (fd != -1) {
        /* go to beginning of file */
        lseek(fd, 0, SEEK_SET);
        
        /* read the 'nextId' from the file */
        read(fd, (void *)&(l -> nextId), sizeof(long));
        
        /* read the 'indirTableLength' from the file */
        read(fd, (void *)&(l -> indirTableLength), sizeof(long));
        
        /* read the indirection table from the file */
        l -> indirTable = (struct indirTableEntry *)malloc(sizeof(struct indirTableEntry)*
                                                           (l -> indirTableLength));
        read(fd, (void *)(l -> indirTable), sizeof(indirTableEntry) * l -> indirTableLength);

        /* read the 'liniarizationTop' from the file */
        read(fd, (void *)&(l -> liniarizationTop), sizeof(long));
        
        /* read the 'liniarizationLength' from the file */
        read(fd, (void *)&(l -> liniarizationLength), sizeof(long));
        
        /* read the liniarization from the file */
        l -> liniarization = (char *)memalign(4, l -> liniarizationLength);
        read(fd, (void *)(l -> liniarization), l -> liniarizationLength);

        l -> originTableTop = 0;
        l -> originTableLength = 0;
        l -> originTable = NULL;
        
        /* read the 'noObjects' from the file */
        read(fd, (void *)&(l -> noObjects), sizeof(long));
        
        close(fd);
    } else {
        fprintf(output, "could not open file for read\n");
    }

    return l;
}

static void insertInOriginTable(long byteOffset,
                                long indirRef,
                                struct liniarization *l) {
    if (l -> originTableTop >= l -> originTableLength) {
        int newLength = 2 * l -> originTableLength + 1;
        struct originRefIndicator *new = (struct originRefIndicator *)
            malloc(sizeof(struct originRefIndicator)*newLength);
        int count;
        
        for (count = 0; count < l -> originTableLength; count++) {
            new[count]=l -> originTable[count];
        }
        if (l -> originTable) {
            free(l -> originTable);
            l -> originTable = NULL;
        }
        l -> originTable = new;
        l -> originTableLength = newLength;
    }
    l -> originTable[l -> originTableTop].byteOffset=byteOffset;
    l -> originTable[l -> originTableTop].indirRef=indirRef;
    l -> originTableTop = l -> originTableTop + 1;
}

/* MG: */

static long minIndirRef = -1000000;  /* minimum indirectref. */

/* Build a linked list of all objects reachable from root
 * in the GCfield of the objects.
 * This often conflicts with the GC'er, so be careful...
 */

void linearizeInGC(ptr(Object) root)
{
    ptr(Object) tail;
    ptr(Object) theObj;
    ptr(ProtoType) theProto;

    /* point to self to end list.
     * Cannot be zero-term, as that would make it look unmarked
     * for the scanner.
     */
    root->GCAttr = (long)root; 

    /* Tail is where new objects are appended to the list. */
    tail = root;
    
    for (theObj = root; theObj; theObj=(struct Object*)(theObj->GCAttr)) {
        theProto = theObj->Proto;
        if (isSpecialProtoType(theProto)) {
            switch (SwitchProto(theProto)) {
              case SwitchProto(ByteRepPTValue):
              case SwitchProto(ShortRepPTValue):
              case SwitchProto(DoubleRepPTValue):
              case SwitchProto(LongRepPTValue): 
                  break; /* No references in this type of object, so do nothing*/
                  
              case SwitchProto(DynItemRepPTValue):
                  fprintf(output, "liniarize.c: DynItemRepPTValue not handled\n");
                  break;
                  
              case SwitchProto(DynCompRepPTValue):
                  fprintf(output, "liniarize.c: DynCompRepPTValue not handled\n");
                  break;
                  
              case SwitchProto(RefRepPTValue):
                  /* Scan the repetition and follow all entries */
              {
                  ptr(long) pointer;
                  register long size, index;
                  
                  size = toRefRep(theObj)->HighBorder;
                  pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
                  
                  for (index=0; index<size; index++) {
                      if (*pointer) {
                          ptr(Object) obj = (struct Object*)(*pointer);
                          
                          if (obj->GCAttr > minIndirRef) {
                              /* Not in the list yet: Append it. */
                              tail->GCAttr = (long)obj;
                              tail=obj;
                          }
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
            short *refs_ofs;
            long *theCell;
        
            /* Handle all the static objects. 
             *
             * The static table, tab[0], tab[1], 0,
             * contains all static objects on all levels.
             * Here we only need to perform ProcessObject on static objects
             * on 1 level. The recursion in ProcessObject handle other
             * levels. 
             * The way to determine the level of an static object is to 
             * compare the Offset (StaticOff) and the
             * Distance_To_Inclosing_Object (OrigOff).
             */
        
            for (;tab->StaticOff; ++tab) {
                /* Do nothing; they ARE statically inlined,
                 * and does as such get included in the list
                 * through their container.
                 */
            }
        
            /* Handle all the references in the Object. */
            for (refs_ofs = (short *)&tab->StaticOff+1; *refs_ofs; ++refs_ofs) {
                const int REFTYPE_DYNAMIC = 0;
                const int REFTYPE_OFFLINE = 1;
                const int REFTYPE_ORIGIN = 2;

                /* sbrandt 24/1/1994: 2 least significant bits in prototype 
                 * dynamic offset table masked out. As offsets in this table are
                 * always multiples of 4, these bits may be used to distinguish
                 * different reference types. */ 
                long refType = (*refs_ofs) & 3;
                theCell = (long *) ((char *)theObj + *refs_ofs - refType);
                /* All types of references are followed here */
                if (*theCell) {
                    ptr(Object) obj = (struct Object*)(*theCell);
                    if (obj->GCAttr > minIndirRef) {
                        /* Not in the list yet: Append it. */
                        tail->GCAttr = (long)obj;
                        tail=obj;
                    }
                }
            }
        }
    }
    /* NULL ternimate list: */
    tail->GCAttr=0;
}

   

#endif /* LIN */
