#include "beta.h"

#if defined(NONMOVEAOAGC)

/* LOCAL FUNCTIONS */

/* IMPLEMENTATION */

/* Build a linked list of all objects reachable from root in the
 * GCfield of the objects.  It is now checked whether an object has
 * been visited in the same way as in IOAGc, namely by checking if the
 * value of the GCAttribute is larger that IOAMaxAge, in which case it
 * is a forward pointer or a link pointer meaning that it has been
 * moved.
 */

static ptr(Object) head;   /* Head of list build by collectList */
static ptr(Object) tail;   /* Tail of list build by collectList */
static long totalsize;

#ifndef KEEP_STACKOBJ_IN_IOA
static void (*StackRefAction)(REFERENCEACTIONARGSTYPE);
void StackRefActionWrapper(struct Object **theCell,struct Object *theObj)
{
  if (theObj
      && inBetaHeap(theObj)
      && isObject(theObj)) {
    StackRefAction(theCell);
  }
}
#endif /* KEEP_STACKOBJ_IN_IOA */

ref (Object) getRealObject(ref (Object) obj)
{
    long Distance;
    ref(Object) AutObj;
    if (obj -> GCAttr < 0) {
        GetDistanceToEnclosingObject(obj, Distance);
        AutObj = (ref(Object)) Offset(obj, Distance);
        return AutObj;
    } else {
        return obj;
    }
}

void checkNotInList(Object *target) 
{
    Object *current;

    current = head;
    
    while ((long) current != LISTEND) {
        if (current == target) {
            fprintf(output, "checkNotInList: 0x%X is in list!\n", (int)(target));
        }
        current = (Object *)(current -> GCAttr);
    }
}
    
/* Append objects to the list regardless of where they are */
void appendToList(Object *target)
{
    long GCAttribute;
    
    /* We are about to append 'target' to the list. We will only do so
     * if target points to an object that is not already part of the
     * list. Whether this is the case can be inferred by looking at
     * the GC-Attribute. The GCAttribute can be,

     (1) Before AOAGc the value of the GCAttribute of all objects that
     is reachable should be DEADOBJECT. This goes for all autonomous
     objects, but not staticly inlined objects. The GCAttr of staticly
     inlined objects contains the offset to the enclosing object. This
     offset is a negative offset allways.

     (2) During AOAGc all live objects are linked together in their GC
     attribute. Of course only autonomous objects may be linked
     together. Thus if we have a reference to a staticly inlined
     object we should not link this object into the list but link the
     enclosing object into the list.

     */

    /* Since this is a highly central function for the GC'er, we do
       not check for NULL refrences in the normal case. It is the
       responsibillity of the caller. */

    GCAttribute = target -> GCAttr;
    
    if (GCAttribute == DEADOBJECT) {
        /* Normal case. All objects in AOA are initially dead and
         * not linked into the list.
         */
        if (tail->GCAttr == LISTEND) {
            tail->GCAttr = (long) target;
            tail=target;
            tail->GCAttr = LISTEND;
            totalsize += 4 * ObjectSize(target);
        } else {
            fprintf(output, "appendToList: List is not proberly terminated!\n");
            BetaExit(1);
        }
    } else if (GCAttribute == LISTEND) {
        /* target is already in the list (it is the tail actually) */
        ;
    } else if (GCAttribute < 0) {
        /* We have encountered a staticly inlined object or a component. */
        appendToList(getRealObject(target));
    } else {
        /* 'target' has a reference in it's GCField. Thus it is allready in the list. */
        DEBUG_AOA(
            if ((GCAttribute == LIVEOBJECT) ||
                (GCAttribute == FREECHUNCK) ||
                (GCAttribute == (long) NULL)) {
                fprintf(output,"appendToList: UNexpected GCAttribute\n");
                BetaExit(1);
                Illegal();
                BetaExit(1);
            });
        return;
    }
}

/* Append objects to the list not including objects in IOA */
void appendToListNoIOA(REFERENCEACTIONARGSTYPE)
{
    DEBUG_AOA(
        if (!*theCell) {
            fprintf(output,"appendToListNoIOA: Target is NULL!\n");
            Illegal();
        });
    
    if (!inIOA(*theCell)) {
        appendToList(*theCell);
    }
}

/* Append objects to the list including only objects in AOA. */
void appendToListInAOA(REFERENCEACTIONARGSTYPE)
{
    DEBUG_AOA(
        if (!*theCell) {
            fprintf(output,"appendToListInAOA: Target is NULL!\n");
            Illegal();
        }
        
        if (!inAOA(theCell)) {
            fprintf(output,"appendToListInAOA: TheCell is not in AOA!\n");
            Illegal();
        });
    
    if (inToSpace(*theCell)) {
        /* insert theCell in AOAtoIOAtable. */
        AOAtoIOAInsert(theCell);
        
    } else {
        /* The cell is assumed to be in AOA if not in IOA. */
        
        DEBUG_AOA(
            if (!inAOA(*theCell)) {
                fprintf(output,"appendToListInAOA: Target points into unknown space!\n");
                Illegal();
            });
        appendToList(*theCell);
    }
}

void initialCollectList(ptr(Object) root,
                        void referenceAction(REFERENCEACTIONARGSTYPE))
{
    ptr(Object) theObj;

    /* If root is a pointer to a staticly inlined part object, then
     * 'getRealObject' will return the enclosing object.
     */

    root = getRealObject(root);
    
    /* If called with root=NULL, just initialize to empty list */
    if (!root) {
        totalsize = 0;
        head = tail = (Object *)LISTEND;
        return;
    }
    
    if (!inAOA(root)) {
        fprintf(output,"initialCollectList: root not in AOA\n");
        DEBUG_AOA(Illegal());
    }
    
    /* set_start_time("initialCollectList"); */
    
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
    tail -> GCAttr = LISTEND;
    
    /* Head is the first object in the list. All objects in the
     * list may be reached through head.  
     */
    head = root;
    
    /* There are no objects in the list yet. */
    totalsize = 0;
    
    for (theObj = root; !isEnd((long)theObj); theObj=(struct Object*)(theObj->GCAttr)) {
        scanObject(theObj, referenceAction, TRUE);
    }
    /* set_end_time("initialCollectList"); */
}

void extendCollectList(ptr(Object) root,
                       void referenceAction(REFERENCEACTIONARGSTYPE))
{
    ptr(Object) theObj;

    /* set_start_time("extendCollectList"); */
    
    DEBUG_AOA(Claim((int)tail, "extendCollectList without initialCollectList"));

    DEBUG_AOA(
        if (!inAOA(root)) {
            fprintf(output,"extendCollectList: root not in AOA\n");
            Illegal();
        });
    
    appendToList(root);
    
    /* root has now been appended to the list, if not already
     * there.
     */
    
    for (theObj = tail; !isEnd((long)theObj); theObj=(struct Object*)(theObj->GCAttr)) {
        /* if root has not been appended to the list, then we scan
         * tail again, which must have been scanned previously. This
         * should not matter as no new objects will be appended since
         * they allready have been appended previously.
         */
        
        scanObject(theObj, referenceAction, TRUE);
    }
    /* set_end_time("extendCollectList"); */
}

void scanList(ref (Object) root, void (foreach)(ref (Object) current))
{
    ref (Object) cur;
    ref (Object) next;
    
    cur = root;
    while (!isEnd((long)cur)) {
        next = (ref(Object))(cur->GCAttr);
        foreach(cur);
	cur = next;
    }
}

void scanObject(struct Object *obj,
                       void referenceAction(REFERENCEACTIONARGSTYPE),
                       int doPartObjects)
{
    ptr (ProtoType) theProto;
    
    theProto = obj->Proto;
    if (!isSpecialProtoType(theProto)) {
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
            long *pointer = (long *)((long)obj + offset);
            /* long refType = (*refs_ofs) & 3; */
            /* sbrandt 24/1/1994: 2 least significant bits in prototype 
             * dynamic offset table masked out. As offsets in this table are
             * always multiples of 4, these bits may be used to distinguish
             * different reference types. */ 
            if (*pointer) {
                referenceAction((struct Object **)pointer);
            }
        }
    } else {
        switch (SwitchProto(theProto)) {
          case SwitchProto(ByteRepPTValue):
          case SwitchProto(ShortRepPTValue):
          case SwitchProto(DoubleRepPTValue):
          case SwitchProto(LongRepPTValue): 
              break; /* No references in this type of object, so do nothing */
              
          case SwitchProto(DynItemRepPTValue):
          case SwitchProto(DynCompRepPTValue): {
              long *pointer;
              long size, index;
              
              /* Process iOrigin */
              referenceAction(&(((ObjectRep *)obj) -> iOrigin));
              
              /* Process rest of repetition */
              size = ((ObjectRep *)obj)->HighBorder;
              pointer = (long *)&((ObjectRep *)obj)->Body[0];
              
              for (index=0; index<size; index++) {
                  if (*pointer) {
                      referenceAction((Object **)pointer);
                  }
                  pointer++;
              }
              break;
          }
          
          case SwitchProto(RefRepPTValue): 
              /* Scan the repetition and apply referenceAction */
          {
              long *pointer;
              long offset, offsetTop;
              
              offset =  (char*)(&toRefRep(obj)->Body[0]) - (char*)obj;
              offsetTop = offset + 4 * toRefRep(obj)->HighBorder;
              
              while (offset < offsetTop) {
                  pointer = (long *)((long)obj + offset);
                  if (*pointer) {
                      referenceAction((Object **)pointer);
                  }
                  offset += 4;
              }
              break;
          }
          
          case SwitchProto(ComponentPTValue):
          {
              ref(Component) theComponent;
              
              theComponent = Coerce( obj, Component);
#if (defined(CRUN) || defined(RUN) || defined(NEWRUN))
              if ((theComponent->StackObj) &&
                  (long)(theComponent->StackObj) != -1) {
                  referenceAction((Object **)&(theComponent->StackObj));
              }
#else
#error liniarize of stack object not implemented on this platform
#endif /* CRUN || RUN */
              if (theComponent->CallerComp) {
                  referenceAction((Object **)&(theComponent->CallerComp));
              }
              if (theComponent->CallerObj) {
                  referenceAction(&(theComponent->CallerObj));
              }
              scanObject((struct Object *)ComponentItem( theComponent),
                         referenceAction, TRUE);
              break;
          }
          case SwitchProto(StackObjectPTValue):
#ifdef KEEP_STACKOBJ_IN_IOA
	    { 
	      static int once = 0;
	      if (!once) {
		fprintf(output, "(Warning:liniarize.c: StackObjectPTValue not handled)\n");
		once = 0;
	      }
	    }
	    /* Illegal(); */
#else
	   StackRefAction = referenceAction;
	   ProcessStackObj((struct StackObject *)obj, StackRefActionWrapper);
#endif
	    break;
              
          case SwitchProto(StructurePTValue):
              referenceAction(&((toStructure(obj))->iOrigin));
              break;
              
          case SwitchProto(DopartObjectPTValue):
              referenceAction(&((cast(DopartObject)(obj))->Origin));
              break;
        }
    } 
}


#endif /* NONMOVEAOAGC */
