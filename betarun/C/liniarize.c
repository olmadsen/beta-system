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
                       void referenceAction(REFERENCEACTIONARGSTYPE),
                       int doPartObjects);
static void redirectLinObjects(void);
static void redirectAOARoots(void);

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
void appendToList(REFERENCEACTIONARGSTYPE)
{
    if ((tail != target)
        && 0 <= target->GCAttr && target->GCAttr <= IOAMaxAge + 1) {
        /* Not in the list yet.*/
        if (!isAnchorProto(target->Proto)) {
            /* Not an anchor, insert. */
            tail->GCAttr = (long)target;
            tail=target;
        }
    }
}

/* Append objects to the list not including objects in IOA */
void appendToListNoIOA(REFERENCEACTIONARGSTYPE)
{
    if (!inIOA(target)) {
        appendToList(REFERENCEACTIONARGS);
    }
}

/* Append objects to the list including only objects in AOA */
void appendToListInAOA(REFERENCEACTIONARGSTYPE)
{
    if (inAOA(target)) {
        appendToList(REFERENCEACTIONARGS);
    } 
}


void initialCollectList(ptr(Object) root,
                        void referenceAction(REFERENCEACTIONARGSTYPE))
{
    ptr(Object) theObj;

    /* If called with root=NULL, just initialize to empty list */
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
    /* This is not the case anymore, as append explicitly checks
     * that tail is not reinserted, tail=root until root->GCAttr is set.
     * root->GCAttr = (long)root; 
     */
    
    /* Tail is where new objects are appended to the list.
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
                       void referenceAction(REFERENCEACTIONARGSTYPE))
{
    ptr(Object) theObj;

    set_start_time("extendCollectList");
    
    DEBUG_CODE(Claim((int)tail, "extendCollectList without initialCollectList"));

    /* Check that root is not already marked as being in the list */
    if ((tail != root) 
	&& 0 <= root->GCAttr && root->GCAttr <= IOAMaxAge+1) {

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
    
    cur = root;
    while (cur) {
        next = (ref(Object))(cur->GCAttr);
        foreach(cur);
	cur = next;
    }
}

/* NEGative versions of the above:  Use negated value in GCAttr. */
void appendToListNeg(REFERENCEACTIONARGSTYPE)
{
    if ((tail != target)
        && 0 <= target->GCAttr && target->GCAttr <= IOAMaxAge + 1) {
        /* Not in the list yet.*/
        if (!isAnchorProto(target->Proto)) {
            /* Not an anchor, insert. */
            tail->GCAttr = -(long)target;
            tail=target;
        }
    }
}

/* Append objects to the list not including objects in IOA */
void appendToListNoIOANeg(REFERENCEACTIONARGSTYPE)
{
    if (!inIOA(target)) {
        appendToListNeg(REFERENCEACTIONARGS);
    }
}

/* Append objects to the list including only objects in AOA */
void appendToListInAOANeg(REFERENCEACTIONARGSTYPE)
{
    if (inAOA(target)) {
        appendToListNeg(REFERENCEACTIONARGS);
    } 
}

void initialCollectListNeg(ptr(Object) root,
                        void referenceAction(REFERENCEACTIONARGSTYPE))
{
    ptr(Object) theObj;

    if (!root) {
        totalsize = 0;
        head = tail = NULL;
        return;
    }
        
    set_start_time("initialCollectList");
    
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

    
    for (theObj = root; theObj; theObj=(struct Object*)(-theObj->GCAttr)) {
        totalsize += 4 * ObjectSize(theObj);
        scanObject(theObj, referenceAction, TRUE);
    }
    /* NULL ternimate list: */
    tail->GCAttr=0;

    set_end_time("initialCollectList");
}

void extendCollectListNeg(ptr(Object) root,
                       void referenceAction(REFERENCEACTIONARGSTYPE))
{
    ptr(Object) theObj;

    set_start_time("extendCollectList");
    
    DEBUG_CODE(Claim((int)tail, "extendCollectList without initialCollectList"));

    /* Check that root is not already marked as being in the list */
    if ((tail != root) 
	&& 0 <= root->GCAttr && root->GCAttr <= IOAMaxAge+1) {

        /* Append root to list */
        tail->GCAttr = -(long)root;
        tail = root;
        
        for (theObj = root; theObj; theObj=(struct Object*)(-theObj->GCAttr)) {
            totalsize += 4 * ObjectSize(theObj);
            scanObject(theObj, referenceAction, TRUE);
        }
        /* NULL terminate list: */
        tail->GCAttr=0;
    }
    set_end_time("extendCollectList");
}

static void scanListNeg(ref(Object) root, void (foreach)(ref(Object) current))
{
    ref (Object) cur;
    ref (Object) next;
    
    cur = root;
    while (cur) {
        next = (ref(Object))(-cur->GCAttr);
        foreach(cur);
	cur = next;
    }
}

static void scanObject(struct Object *obj,
                       void referenceAction(REFERENCEACTIONARGSTYPE),
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
              long target;
              long offset, offsetTop;
              
              offset =  (char*)(&toRefRep(obj)->Body[0]) - (char*)obj;
              offsetTop = offset + 4 * toRefRep(obj)->HighBorder;
              
              while (offset < offsetTop) {
                  target = *(long*)((char*)obj + offset);
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
        
        /* Handle all the static objects. 
         *
         * The static table, tab[0], tab[1], ..., 0,
         * contains all static objects on all levels.
	 * We call recursively on every one, is we're told
	 * to do so. When we do so, we make sure that there is no 
	 * further recursion going on.
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
        
        /* Handle all the non-static references in the object. */
        for (refs_ofs = (short *)&tab->StaticOff+1; *refs_ofs; refs_ofs++) {
            long offset  = (*refs_ofs) & ~3;
            long target = *(long*)((char *)obj + offset);
            /* long refType = (*refs_ofs) & 3; */
            /* sbrandt 24/1/1994: 2 least significant bits in prototype 
             * dynamic offset table masked out. As offsets in this table are
             * always multiples of 4, these bits may be used to distinguish
             * different reference types. */ 
            if (target) {
                referenceAction(obj, offset, (struct Object *)target);
            }
        }
    }
}

void assignRefNoGC(struct Object **theCell, long id)
{
    *(long *)theCell = (long)id;
}

ref (Object) copyObjectToLinearizationInAOA(ref (Object) theObj, long size) 
{
    long *newObj;
    
    /* Assuming that a block with the proper size has been allocated
     * previously to hold the linearization, this function will copy
     * theObj to the end of that linearization.
     */

    /* This function is called from 'CopyObjectToAOA' in aoa.c, which
     *  in turn is called from 'NewCopyObject' in objectsize, which in
     *  turn is called from 'IOAGc' in ioa.c.
     *
     * It is also used by AOAgc for the same purpose.     
     */
    
    newObj = AOALinTop;
    AOALinTop = (ptr(long)) (((long)newObj) + size); 
    Claim(AOALinTop <= AOALinLimit, "Ran out of LINspace");
    memcpy(newObj, theObj, size);
    
    return (ref (Object))newObj;
}

void allocateLinearizationInAOA(long bytesize) 
{
    if ((AOALinStart = (long*)AOAallocate(bytesize))) {
        AOALinTop = AOALinStart;
        AOALinLimit = AOALinTop + bytesize/4;
    } else {
        fprintf(stderr,"allocateLinearizationInAOA: failed to allocate block of bytesize %lu\n", bytesize);
#ifdef RTDEBUG
        Illegal();
#else
        exit(0);
#endif
    }
}

/* Take IOA members out of the list and make them very old */
void markIOARelinkAOA(ref (Object) current) 
{
    if (inIOA(current)) {
        /* Mark that this object should be moved to the linearization in AOA
           at the next IOAGc */
        current -> GCAttr = IOAMaxAge + 1;
        
    } else {
        if (!head) {
            head = current;
            tail = head;
        } else {
            tail -> GCAttr = (long)current;
            tail = current;
        }
    }
}

void linearizeAbsoluteMove(ref (Object) root)
{
    long sizeOfLinearizationInAOA;
    
    /* Step 1: Collect the transitive closure of the root in a linked
     * list.
     */
    initialCollectList(root, appendToList);
    sizeOfLinearizationInAOA = totalsize;
    
    /* Step 2: Mark in the GCAttribute of the objects in IOA that they
     *  should be moved to the linearization at the next IOAGc.
     */
    head = NULL;
    tail = NULL;
    scanList(root, markIOARelinkAOA);
    /* Now head points to the head of a new linked list containing
     * those objects in the transitive closure that does not reside in
     * IOA, and lets hope most of them are in AOA, since those are the
     * only ones we know how to handle...
     */
       
    AOAListHead = (long*)head;

    /* Step 3: Allocate space in AOA for the linearization.  */
    allocateLinearizationInAOA(sizeOfLinearizationInAOA);
    
    /* Now we are ready to do an IOAGc. This will move those objects
     * in the transitive closure that reside in IOA to the
     * linearization in AOA.
     *
     * We cannot start the IOAGc here, as it needs to know about
     * the stack-layout, so we return to BETA, which must then doGC...
     */

    return;

    /* And after that IOAGc a new AOAGC will be forced, which will take 
     * care of the objects in AOA, that should go into the linearization:
     *
     * A: CollectLiveOjbectsNegAOA.
     *    This creates a list of all live objects in AOA excluding
     *    those in the linearization.  This is the first step of
     *    the non-moving GC in AOA.
     *
     * B: AOAMoveToLin.
     *    This moves the rest of the objects that should go there
     *    into the linearization.
     *
     * C: redirectPosForward
     *    Works on the list collected in A.  This repairs all pointers
     *    from those objects to the objects moved in B.
     *
     * D: redirectLinObjects.
     *    Runs through the objects that were moved in B in the
     *    linearization fixing pointers internally in them.
     *
     * E: redirectAOARoots.
     *    Check all AOARoots for references to objects that have been moved.
     *
     * F: NonMoveGCKillDead.
     *    Sweep through entire AOA one object at a time.  If the GCAttr is 0,
     *    the Object is dead. Insert in some sort of freelist-implementation.
     *    Otherwise set GCAttr to 0 to prepare for next run.
     */
}

void AOAMoveToLin(ref(Object) current)
{
    long forward;

    forward = (long) copyObjectToLinearizationInAOA(current,
                                                    4*ObjectSize(current));
    current->GCAttr = forward;
}


void redirectPosForwardRef(REFERENCEACTIONARGSTYPE)
{
    if (target->GCAttr > IOAMaxAge+1) {
        *(long*)((char*)obj + offset) = target->GCAttr;
    }
}

void redirectPosForward(ref(Object) current)
{
    scanObject(current, redirectPosForwardRef, TRUE);
}


void copyAOAObjectToLinearizationInAOA(void)
{
    /* Copy all objects on the list to LIN-in-AOA */
    scanList((ref(Object))AOAListHead, AOAMoveToLin);

    /* Scan all live objects in AOA except LIN-in-AOA 
     * and redirect their pointers ot the copies
     */
    scanListNeg(head, redirectPosForward);

    /* Redirect pointers within LIN-in-AOA */
    redirectLinObjects();

    /* Redirect pointers to LIN-in-AOA in cells outside AOA */
    redirectAOARoots();
}

/* Scan through the objects in the linearization and redirect
 * pointers that have become invalid by the recent move of
 * objects from AOA to LIN-in-AOA.  
 * We have to scan all objects in the LIN, as they are 
 * not visited by the other scans, and those moved there
 * by IOAGc were moved before the recent move.
 */
static void redirectLinObjects(void)
{
    ref(Object) current = AOALinStart;
    
    while((long*)current < (long*)AOALinTop) {
        scanObject(current, redirectPosForwardRef, TRUE);
        current = (ref(Object))((long*)current + ObjectSize(current));
    }
}

/* Run through AOARoots and redirect them, if we've moved the objects */
static void redirectAOARoots(void)
{
    long *pointer = AOArootsPtr;
    ptr(long) cellptr;
    ptr(Object) target;
    
    while (pointer < AOArootsLimit) {
        cellptr = (long*)(*pointer & ~1);
        target = (ptr(Object))*cellptr;
        if (target->GCAttr > IOAMaxAge + 1) {
            *cellptr = target->GCAttr;
        }
        pointer++;
    }
}

#endif /* LIN */

/* A more thorough explanation of whats going on.
   (For now just to document the code, but might make it into my thesis)

===initialCollectList and extendCollectList make a single linked list from
   the transitive colsure of a set of connected graphs of objects.  The
   list is stored within the objects in the field reserved for the garbage
   collector, the GCAttr.

   Time and Space: The algorithm uses no storage space apart from the cell
   in every object, which is there for other reasons.  It scans every
   object included in the list once. It looks at the GCAttr of every object
   in the transitive closure as many times as there are references to the
   object. The complexity is O(m+n) where m is the number of objects
   included in the list, and n is the sum of the number of references in
   the m objects.

   Requirements: The GCAttr must have a value that is distinguishable
   from the object addresses.  In practice, it is allowed to be in the
   interval 0 through IOAMaxAge+1.

   Parameters: "root" and "appendAction".  

   root is the object to start building the list from.  root is included in
   the list unconditionally by initialcollectlist, whereas
   extendcollectlist only includes root if it is not already there.

   appendAction is called on every reference encountered during the search
   through the transitive closure. appendAction has to decide if it wants
   to include the refered object and in that case append it to the list.

   Domains are supported in the following sense: Domaines are charectarized
   by their anchors.  Anchors are registered through their prototypes.  It
   is possible to write an appendAction that checks if the object in
   question happens to have the prototype of an Anchor in which case hte
   object is ignored.  Our AppendToList is such an appendAction.  For
   largescale use, a number of improvements are necessary.  When
   registrering an AnchorType, it may be desireable to have the system
   register all subtypes of that type as well.  This is much more efficient
   that having to check the supertypes for every object encountered.  The
   datastructure used to store the Anchorprototypes has to be improved as
   well.  Good solutions include marking directly in the prototype, if
   there is a free bit, or using an efficient hashtable.  The number of
   prototypes in a program is limited, and the number of prototypes
   registered as Anchors is probaly always a lot smaller.

   The list-building algorithm works like this: There are three pointer
   into the list.  "head" is set to point at the first object in the list
   and is never moved.  "tail" is the insertion point for new objects. It
   always points at the last element in the list.  "theObj" (local in
   collectLists) points at the object being scanned for references and is
   always somehwere between head and tail.  Objects are inserte at the end
   only and no objects are removed from the list.  When theObj reaches tail
   and finds no successor, the list is complete.

   

*/





