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

/* Probably obsolete functions */
void collectLiveObjectsInAOA(void);

/* LOCAL FUNCTIONS */
static void scanList(ref (Object) root, void (foreach)(ref (Object) current));
static void scanObject(struct Object *obj,
                       referenceActionType referenceAction,
                       int doPartObjects);


/* Keep track of prototypes of domain anchors and other objects
 * that should not be included in the lists build.
 */
static ProtoType *anchorProtos[16];
static int lastAnchorProto = 0;

/* For now, just use a list with fixed length.  Should be a hash */
void addAnchorProto(struct ProtoType *proto)
{
    anchorProtos[lastAnchorProto++] = proto;
}

static int isAnchorProto(struct ProtoType *proto)
{
    int i;

    for (i=0; i<lastAnchorProto; i++) {
        if (proto==anchorProtos[i])
            return TRUE;
    }
    return FALSE;
}


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

/* Append objects to the list regardless of where they are */

void appendToList(REFERENCEACTIONARGS)
{
    ptr(Object) obj = (struct Object *)(*theCell);

    if ((tail != obj) && obj->GCAttr <= IOAMaxAge) {
        /* Not in the list yet.*/
        if (!isAnchorProto(obj->Proto)) {
            /* Not an anchor, insert. */
            tail->GCAttr = (long)obj;
            tail=obj;
        }
    }
}

/* Append objects to the list not including objects in IOA */
void appendToListNoIOA(REFERENCEACTIONARGS)
{
    ptr(Object) obj = (struct Object *)(*theCell);

    if (!inIOA(obj)) {
        appendToList(theObj, theCell);
    }
}

/* Append objects to the list including only objects in AOA */
void appendToListInAOA(struct Object *theObj, struct Object **theCell)
{
    ptr(Object) obj = (struct Object *)(*theCell);

    if (inAOA(obj)) {
        appendToList(theObj, theCell);
    } 
}
    

void initialCollectList(ptr(Object) root,
                        referenceActionType referenceAction)
{
    ptr(Object) theObj;

    if (!root) {
        totalsize = 0;
        head = tail = NULL;
        return;
    }
        
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
        totalsize += 4 * ObjectSize(theObj);
        scanObject(theObj, referenceAction, TRUE);
    }
    /* NULL ternimate list: */
    tail->GCAttr=0;

    set_end_time("initialCollectList");
}

void extendCollectList(ptr(Object) root,
                        referenceActionType referenceAction)
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
            totalsize += 4 * ObjectSize(theObj);
            scanObject(theObj, referenceAction, TRUE);
        }
        /* NULL terminate list: */
        tail->GCAttr=0;
    }
    set_end_time("extendCollectList");
}


static void scanList(ref (Object) root, void (foreach)(ref (Object) current))
{
    ref (Object) cur;
    ref (Object) next;
    
    for (cur = root; cur; cur = next) {
        next = (ref (Object)) (cur -> GCAttr);
        foreach(cur);
    }
}


static void scanObject(struct Object *obj,
                       referenceActionType referenceAction,
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
              ptr(long) target;
              long offset, offsetTop;
              
              offset =  (char*)(&toRefRep(obj)->Body[0]) - (char*)obj;
              offsetTop = offset + 4 * toRefRep(obj)->HighBorder;
              
              while (offset < offsetTop) {
                  target = *(long*)((char*)obj + offset)
                  if (target) {
                      referenceAction(obj, offset, (struct Object *)target);
                  }
                  offset += 4;
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
                scanObject((ref(Object))((long *)obj + tab->StaticOff),
                           referenceAction, FALSE);
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
            long offset  = (*refs_ofs) & ~3;
            long target = *(long*)((char *)obj + offset);
            /* sbrandt 24/1/1994: 2 least significant bits in prototype 
             * dynamic offset table masked out. As offsets in this table are
             * always multiples of 4, these bits may be used to distinguish
             * different reference types. */ 
            if (target) {
                referenceAction(obj, offset, (struct object *)target);
            }
        }
    }
}


void assignRefNoGC(struct Object **theCell, long id)
{
    *(long *)theCell = (long)id;
}

      
#endif /* LIN */
