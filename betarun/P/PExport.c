#include "beta.h"

#ifdef PERSIST
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "specialObjectsTable.h"
#include "storageblock.h"
#include "pit.h"
#include "proto.h"

#ifdef PSENDIAN
/* Get definition of ntohl */
#ifdef linux
# include <sys/types.h>
# include <netinet/in.h>
#else
# include "winsock.h"
#endif 
#endif 

/* LOCAL FUNCTION DECLARATIONS */
static void refhandler(REFERENCEACTIONARGSTYPE);

/* LOCAL TYPES */
typedef struct objinfo
{
   Object *buffer;
   /* The object that is currently being exported.
    */
   u_long size;
   /* size of the buffer */
   CAStorage *store;
   /* The store in which it resides.
     */
   /* som profiling info follows */
   u_long refsfollowed;
   u_long refs;
} Objinfo;

/* LOCAL VARIABLES */
/* We need to know some particulars about the object that is currently
 * being exported. Unfortunately this info cannot be passed as
 * arguments to the object scanner, since that is also used many other
 * places, places where it would be unacceptable to pass such extra
 * arguments around. It follows that we have to make a global variable
 * holding the said info, eventhough we hate and despise global
 * variables even more.
 */
static Objinfo current = {0, 0, 0, 0, 0};

/* 'refhandler' is called for each reference in the object that is
 * being exported.
 */
static void refhandler(REFERENCEACTIONARGSTYPE)
{
   CAStorage *store;
   unsigned long offset, distanceToPart;
   Object *theObj, *realObj;
   
   theObj = *theCell;

   /* The tagging of the refType is currently not used */
   refType = NORMALREFERENCE;
   
   if (inPIT(theObj)) {
      RefInfo *refInfo;
      refInfo = (RefInfo *)PITlookup(theObj);
      store = refInfo -> store;
      offset = refInfo -> offset;
      distanceToPart = 0;        
   } else {
      realObj = getRealObject(theObj);
      distanceToPart = (unsigned long)theObj - (unsigned long)realObj;
      Claim(inAOA(realObj), "Where is the object?");
      if (AOAISPERSISTENT(realObj)) {
         ObjInfo *objInfo;
         objInfo = (ObjInfo *)GETOI(realObj -> GCAttr);
         store = objInfo -> store;
         offset = objInfo -> offset;
      } else {
	/* special object possibly not persistent */
         unsigned long tag;
         
         tag = getTag(realObj);
         
         Claim(tag < 0xFF, "Tag not found or tag too big");
         Claim(distanceToPart < 0xFFFF, "distanceToPart too big");
            
         *theCell = (Object *)(((tag << 24 ) | (distanceToPart << 8) | SPECIALREFERENCE) + 1);
         return;
      }
   }
    
   if (store == current.store) {
      if (!isOutReference(offset)) {
         /* the reference is simply replaced by the offset of the
          * referred object. One is added in order to distinquish none
          * references from zero offsets (which are possible)
          */
         *theCell = (Object *)(((offset + distanceToPart) | refType) + 1);
      } else {
         /* cross block reference */
         Claim(FALSE, "PExport: cross block references not implemented yet");
      }
   } else {
      /* cross block reference */
      Claim(FALSE, "PExport: cross block references not implemented yet");
   }

   Claim(*theCell != NULL, "Assigning NULL to cell");
}

void extendBufferSize(u_long size)
{
   if (current.buffer) {
      free(current.buffer);
   }
   current.buffer = (Object *)malloc(sizeof(char)*size);
   current.size = size;
}


/* Export the proto type */
static void exportPrototype(unsigned long *cell)
{
  unsigned long group;
  unsigned long protoNo;

  protoAddrToID(*(ProtoType**)cell, &group, &protoNo);
              
  if (group == -1) {
    /* the prototype is a special prototype 
     * and thus no conversion is necessary */
#ifdef PSENDIAN
    *cell = htonl(*cell);
#endif
  } else {
    Claim(protoNo != -1, "exportProtoType: Export of proto pointer failed");
    Claim(group < ( 1 << 16), "exportProtoType: Group too large");
    Claim(protoNo < ( 1 << 16), "exportProtoType: protoNo too large");
#ifdef PSENDIAN
    *cell = htonl((unsigned long)((group << 16) | protoNo));
#else
    *cell = ((group << 16) | protoNo);
#endif
  }
}


/* In aoa.c */
extern void (*StackRefAction)(REFERENCEACTIONARGSTYPE);

static void exportScanObject(Object *obj, int doPartObjects)
{
   ProtoType * theProto;
#ifdef PSENDIAN
   u_long objSize = ObjectSize(obj);
#endif /* PSENDIAN */
   
   /* Export and endian convert,
    *
    * - The proto type
    * - The GCAtrribute
    * - All references
    * - All Values
    */
  
   theProto = GETPROTO(obj);

   /* The proto type */
   exportProtoType(obj);
  
   /* The GCAttribute */
#ifdef PSENDIAN
      obj -> GCAttr = htonl(obj -> GCAttr);
#endif

   /* All references and values */
   if (!isSpecialProtoType(theProto)) {
      GCEntry *tab =
         (GCEntry *) ((char *) theProto + theProto->GCTabOff);
      short *refs_ofs;
     
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
            exportScanObject((Object *)((long *)obj + tab->StaticOff), FALSE);
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
         long refType = (*refs_ofs) & 3;
         /* sbrandt 24/1/1994: 2 least significant bits in prototype 
          * dynamic offset table masked out. As offsets in this table are
          * always multiples of 4, these bits may be used to distinguish
          * different reference types.
          REFTYPE_DYNAMIC: (# exit 0 #);
          REFTYPE_OFFLINE: (# exit 1 #);
          REFTYPE_ORIGIN: (# exit 2 #);
         */ 
         if (*pointer) {
            /* Export the reference */
            refhandler((Object **)pointer, refType);
           
#ifdef PSENDIAN
            /* Endian convert the reference */
            *pointer = htonl(*pointer);
#endif
         }
      }

#ifdef PSENDIAN
      /* Handle all longs: */
      {
         unsigned char *ebits, b, do_int16, do_real64;
         unsigned long offset, pos;
         int numbytes;
         short *ptr;
         
         ebits = (unsigned char*) (refs_ofs + 1);
         b = *ebits++;
         do_int16  = (b & 0x80);
         do_real64 = (b & 0x40);
     
         if (b & 0x3f) { /* Any longs in the first 8 words? */
            offset = 2;
            while (b & 0x3f) { /* Any longs in the first 8 words? */
               if (b & 0x20) {
                  *((unsigned long*)obj+offset) = htonl(*((unsigned long*)obj+offset));
               }
               b *= 2;
               offset++;
            }
         }
         pos = 8;
        
         numbytes = ((objSize-1) / 8);
         while (numbytes--) {
            b = *ebits++;
            if (b) {
               offset = pos;
               while (b) {
                  if (b & 0x80) {
                     *((unsigned long*)obj+offset) = htonl(*((unsigned long*)obj+offset));
                  }
                  offset++;
                  b *= 2;
               }
            }
            pos += 8;
         }
        
         if ((unsigned long)ebits & 1) {
            ebits++;
         }
        
         ptr = (short*)ebits;
         if (do_int16) {
            while (*ptr) {
               *(unsigned short*)((char*)obj+*ptr) = htons(*(unsigned short*)((char*)obj+*ptr));
               ptr++;
            }
            ptr++;
         }
        
         if (do_real64) {
            while (*ptr) {
               unsigned long x = htonl(*(unsigned long*)((char*)obj+*ptr));
               *(unsigned long*)((char*)obj+*ptr) = 
                  htonl(*(unsigned long*)((char*)obj+*ptr+4));
               *(unsigned long*)((char*)obj+*ptr+4) = x;
               ptr++;
            }
         }
      }
#endif /* PSENDIAN */
   } else {
      switch (SwitchProto(theProto)) {
        case SwitchProto(ByteRepPTValue):
        case SwitchProto(ShortRepPTValue):
        case SwitchProto(DoubleRepPTValue):
        case SwitchProto(LongRepPTValue): 
        case SwitchProto(RefRepPTValue): 
        case SwitchProto(DynItemRepPTValue):
        case SwitchProto(DynCompRepPTValue): 
        {
#ifdef PSENDIAN
           long offset, offsetTop;
#endif
           u_long HighBorder = ((ValRep*)(obj)) -> HighBorder;
           
#ifdef PSENDIAN
           ((ValRep*)(obj)) -> LowBorder = htonl(((ValRep*)(obj)) -> LowBorder);
           ((ValRep*)(obj)) -> HighBorder = htonl(((ValRep*)(obj)) -> HighBorder);
#endif
           switch (SwitchProto(theProto)) {
             case SwitchProto(ShortRepPTValue):
             {
#ifdef PSENDIAN
                unsigned short *pointer;
                
                offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 2 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned short*)((char*)obj + offset);
                   *pointer = htons(*pointer);
                   offset += 2;
                }
#endif
                break;
             }
             case SwitchProto(DoubleRepPTValue):
             {
#ifdef PSENDIAN
                unsigned long *pointer, x;
	
                offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 8 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned long*)((char*)obj + offset);
                   x = htonl(*pointer);
                   *pointer = htonl(*(pointer+1));
                   *(pointer+1) = x;
                   offset += 8;
                }
#endif
                break;
             }
             case SwitchProto(LongRepPTValue):     
             {
#ifdef PSENDIAN
                unsigned long *pointer;
                
                offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 4 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned long *)((char*)obj + offset);
                   *pointer = htonl(*pointer);
                   offset += 4;
                }
#endif
                break;
             }
             case SwitchProto(RefRepPTValue): 
             {
                long *pointer;
                long offset, offsetTop;
                
                offset =  (char*)(&((RefRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 4 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (long *)((long)obj + offset);
                   if (*pointer) {
                      refhandler((Object **)pointer, REFTYPE_DYNAMIC);
#ifdef PSENDIAN
                      *pointer = htonl(*pointer);
#endif
                   }
                   offset += 4;
                }
                break;
             }
             case SwitchProto(DynItemRepPTValue):
             case SwitchProto(DynCompRepPTValue):
             {
                long *pointer;
                long size, index;
                ObjectRep *robj = (ObjectRep *)obj;
                
                /* Process iOrigin */
                refhandler(&robj->iOrigin, REFTYPE_ORIGIN);
#ifdef PSENDIAN
                robj->iOrigin = (Object *)htonl((u_long)robj->iOrigin);
#endif                
                exportPrototype((unsigned long*)&(robj->iProto));

                /* Process rest of repetition */
                size = HighBorder;
                pointer = (long *)&robj->Body[0];
                
                for (index=0; index<size; index++) {
                   if (*pointer) {
                      refhandler((Object **)pointer, REFTYPE_OFFLINE);
#ifdef PSENDIAN
                      *pointer = htonl(*pointer);
#endif
                   }
                   pointer++;
                }
                break;
             }
           }
           break;
        }  
        case SwitchProto(ComponentPTValue):
        {
           Component * theComponent;
              
           theComponent = ((Component*)obj);
           if ((theComponent->StackObj) &&
               (long)(theComponent->StackObj) != -1) {
              DEBUG_STACKOBJ({
                 fprintf(output, 
                         "Processing stackobj 0x%08x of component 0x%08x "
                         "with func=0x%08x\n",
                         (int)theComponent->StackObj, (int)theComponent, 
                         (int)refhandler);
              });
              refhandler((Object **)&(theComponent->StackObj), REFTYPE_DYNAMIC);
#ifdef PSENDIAN
              theComponent->StackObj = (StackObject *)htonl((u_long)theComponent->StackObj);
#endif
           }
           if (theComponent->CallerComp) {
              refhandler((Object **)&(theComponent->CallerComp), REFTYPE_DYNAMIC);
#ifdef PSENDIAN
              theComponent->CallerComp = (Component *)htonl((u_long)theComponent->CallerComp);
#endif
           }
           if (theComponent->CallerObj) {
              refhandler(&(theComponent->CallerObj), REFTYPE_DYNAMIC);
#ifdef PSENDIAN
              theComponent->CallerObj = (Object *)htonl((u_long)theComponent->CallerObj);
#endif
           }
           if (doPartObjects) { 
              exportScanObject((Object *)ComponentItem( theComponent), TRUE);
           }
#ifdef PSENDIAN
           ((Component*)obj) -> CallerLSC = (pc_t)(htonl((long)(((Component*)obj) -> CallerLSC)));
#endif
           break;
        }
        case SwitchProto(StackObjectPTValue):
        {
           StackRefAction = refhandler;
           ProcessStackObj((StackObject *)obj, StackRefActionWrapper);
           StackRefAction = NULL;

#ifdef PSENDIAN
           ((StackObject *)obj) -> BodySize = htonl(((StackObject *)obj) -> BodySize);
           ((StackObject *)obj) -> StackSize = htonl(((StackObject *)obj) -> StackSize);
#endif
           break;
        }
        case SwitchProto(StructurePTValue):
        {
           Structure *sobj = (Structure*)obj;
          
           refhandler(&(sobj->iOrigin), REFTYPE_ORIGIN);
#ifdef PSENDIAN
           sobj->iOrigin = (Object *)htonl((u_long)sobj->iOrigin);
#endif           
           exportPrototype((unsigned long*)&(sobj->iProto));
           break;
        }
        case SwitchProto(DopartObjectPTValue):
        {
           DopartObject * dobj = (DopartObject *)obj;
          
           refhandler(&(dobj->Origin), REFTYPE_ORIGIN);
#ifdef PSENDIAN
           dobj->Origin = (Object *)htonl((u_long)dobj->Origin);
#endif
           break;
        }
        default:
           Claim( FALSE, "exportScanObject: theObj must be KNOWN.");
      }
   }
}

/* Exports the object to 'store' */
Object *exportObject(Object *theObj, CAStorage *store, u_long size)
{
   Claim(theObj == getRealObject(theObj), "expoting part object");
   
   if (current.size < size) {
      extendBufferSize(size);
   }

   currentcsb = current.store = store;
   memcpy(current.buffer, theObj, size);
   exportScanObject(current.buffer, TRUE);
   currentcsb = NULL;

   /* The GCAttribute in the store object is cleared */
   ((Object *)current.buffer) -> GCAttr = 0;

   return current.buffer;
}
#endif /* PERSIST */
