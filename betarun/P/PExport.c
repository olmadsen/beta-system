#include "beta.h"

#ifdef PERSIST
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "specialObjectsTable.h"
#include "storageblock.h"
#include "pit.h"
#include "proto.h"

/* Get definition of ntohl */
#if defined(sun4s) || defined(sgi) || defined(linux)
#include <sys/types.h>
#include <netinet/in.h>
#else
#if defined(nti)
#include "winsock.h"
#else

#define ntohl(x) x
#define htonl(x) x
#define ntohs(x) x
#endif
#endif 

/* From proto.c */
extern CAStorage *currentcsb;
extern void protoAddrToID(ProtoType *theProto, unsigned long *group, unsigned long *protoNo);

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

   /* The tagging of the reType is currently not used */
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
   if (obj -> GCAttr) {
      obj -> GCAttr = ntohl(obj -> GCAttr);
   }

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
           
            /* Endian convert the reference */
            *pointer = ntohl(*pointer);
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
                  *((unsigned long*)obj+offset) = ntohl(*((unsigned long*)obj+offset));
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
                     *((unsigned long*)obj+offset) = ntohl(*((unsigned long*)obj+offset));
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
               *(unsigned short*)((char*)obj+*ptr) = ntohs(*(unsigned short*)((char*)obj+*ptr));
               ptr++;
            }
            ptr++;
         }
        
         if (do_real64) {
            while (*ptr) {
               unsigned long x = ntohl(*(unsigned long*)((char*)obj+*ptr));
               *(unsigned long*)((char*)obj+*ptr) = 
                  ntohl(*(unsigned long*)((char*)obj+*ptr+4));
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
           long offset, offsetTop;
           u_long HighBorder = ((ValRep*)(obj)) -> HighBorder;
           
           ((ValRep*)(obj)) -> LowBorder = ntohl(((ValRep*)(obj)) -> LowBorder);
           ((ValRep*)(obj)) -> HighBorder = ntohl(((ValRep*)(obj)) -> HighBorder);

           switch (SwitchProto(theProto)) {
             case SwitchProto(ShortRepPTValue):
             {
                unsigned short *pointer;
                
                offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 2 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned short*)((char*)obj + offset);
                   *pointer = ntohs(*pointer);
                   offset += 2;
                }
                break;
             }
             case SwitchProto(DoubleRepPTValue):
             {
                unsigned long *pointer, x;
	
                offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 8 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned long*)((char*)obj + offset);
                   x = ntohl(*pointer);
                   *pointer = ntohl(*(pointer+1));
                   *(pointer+1) = x;
                   offset += 8;
                }
                break;
             }
             case SwitchProto(LongRepPTValue):     
             {
                unsigned long *pointer;
                
                offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
                offsetTop = offset + 4 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned long *)((char*)obj + offset);
                   *pointer = ntohl(*pointer);
                   offset += 4;
                }
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
                      *pointer = ntohl(*pointer);
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
                
                /* Process iOrigin */
                refhandler(&(((ObjectRep *)obj) -> iOrigin), REFTYPE_ORIGIN);
                (((ObjectRep *)obj) -> iOrigin) = (Object *)ntohl((u_long)((ObjectRep *)obj) -> iOrigin);
                
                /* Process rest of repetition */
                size = HighBorder;
                pointer = (long *)&((ObjectRep *)obj)->Body[0];
                
                for (index=0; index<size; index++) {
                   if (*pointer) {
                      refhandler((Object **)pointer, REFTYPE_OFFLINE);
                      *pointer = ntohl(*pointer);
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
              theComponent->StackObj = (StackObject *)ntohl((u_long)theComponent->StackObj);
           }
           if (theComponent->CallerComp) {
              refhandler((Object **)&(theComponent->CallerComp), REFTYPE_DYNAMIC);
              theComponent->CallerComp = (Component *)ntohl((u_long)theComponent->CallerComp);
           }
           if (theComponent->CallerObj) {
              refhandler(&(theComponent->CallerObj), REFTYPE_DYNAMIC);
              theComponent->CallerObj = (Object *)ntohl((u_long)theComponent->CallerObj);
           }
           if (doPartObjects) { 
              exportScanObject((Object *)ComponentItem( theComponent), TRUE);
           }
           ((Component*)obj) -> CallerLSC = ntohl(((Component*)obj) -> CallerLSC);
           break;
        }
        case SwitchProto(StackObjectPTValue):
        {
           StackRefAction = refhandler;
           ProcessStackObj((StackObject *)obj, StackRefActionWrapper);
           StackRefAction = NULL;

           ((StackObject *)obj) -> BodySize = ntohl(((StackObject *)obj) -> BodySize);
           ((StackObject *)obj) -> StackSize = ntohl(((StackObject *)obj) -> StackSize);

           break;
        }
        case SwitchProto(StructurePTValue):
        {
           refhandler(&(((Structure*)(obj))->iOrigin), REFTYPE_ORIGIN);
           ((Structure*)(obj))->iOrigin = (Object *)ntohl((u_long)((Structure*)(obj))->iOrigin);

           /* Export the proto type */
           {
              unsigned long group;
              unsigned long protoNo;
              
              protoAddrToID(((Structure*)(obj))->iProto,
                            &group,
                            &protoNo);
              
              if (group == -1) {
                 /* the prototype is a special prototype and thus no conversion
                    is necessary */
#ifdef PSENDIAN
                 ((Structure*)(obj))->iProto = (ProtoType *)htonl((u_long)((Structure*)(obj))->iProto);
#endif
              } else {
                 Claim(protoNo != -1, "exportProtoType: Export of proto pointer failed");
                 Claim(group < ( 1 << 16), "exportProtoType: Group too large");
                 Claim(protoNo < ( 1 << 16), "exportProtoType: protoNo too large");
#ifdef PSENDIAN
                 ((Structure*)(obj))->iProto = (ProtoType *)htonl((unsigned long)((group << 16) | protoNo));
#else
                 ((Structure*)(obj))->iProto = (ProtoType *)((group << 16) | protoNo);
#endif
              }
           }
           break;
        }
        case SwitchProto(DopartObjectPTValue):
        {
           refhandler(&(((DopartObject *)(obj))->Origin), REFTYPE_ORIGIN);
           ((DopartObject *)(obj))->Origin = (Object *)ntohl((u_long)((DopartObject *)(obj))->Origin);
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
