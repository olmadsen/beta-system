#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#include "objectTable.h"
#include "transitObjectTable.h"
#include "PException.h"
#include "PImport.h"
#include "unswizzle.h"
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

/* LOCAL TYPES */
    
/* LOCAL VARIABLES */
static u_long prefetch;
static Object *importScanObjectTop;
static u_long importScanObjectSize;


/* LOCAL FUNCTION DECLARATIONS */
/* 'refhandler' is called for each reference in the object that is
 * being imported
 */
static void refhandler(REFERENCEACTIONARGSTYPE, ObjInfo *objInfo);

/* FUNCTIONS */
void PIstart(void)
{
   prefetch = 0;
}

void PIend(void)
{
   fprintf(stderr, "prefetch: %d\n", (int)prefetch);
}

static void refhandler(REFERENCEACTIONARGSTYPE, ObjInfo *objInfoEnc)
{
   u_long offset;
   /* '*theCell' is either an offset in the object area to another
    * object in the same storage block, or it might be an offset
    * within the out references area.
    */
    
   /* When this reference was exported one (1) was added to it's
    * value, in order to distinquish zero offsets from none
    * references.
    */
   offset = (u_long)(*theCell) - 1;
   if (offset - objInfoEnc->offset >= 0
       && offset - objInfoEnc->offset <= importScanObjectSize) {
     /* Reference to somewhere in the same object,
      * e.g partobject of origin reference.
      */
#ifdef DEBUG_PERSISTENCE
     printf("Import-refhandler: Internal reference 0x%08x 0x%08x %d %d %d\n",
            (int)theCell,
            (int)((char*)importScanObjectTop
                  + offset - objInfoEnc->offset),
            (int)offset, (int)objInfoEnc->offset, (int)importScanObjectSize);
#endif
     *theCell = (Object*)((char*)importScanObjectTop
                          + offset - objInfoEnc->offset);
     return;
   }

   if (!isOutReference(offset)) {
      CAStorage *store;
      store = objInfoEnc -> store;
      if (!isSpecialReference(offset)) {            
         void *ip;
         /* Do we have a reference for this object ? */
         if ((refType != REFTYPE_DYNAMIC) ||
             ((ip = lookupReferenceInfo(store, offset)) == NULL)) {
            ObjInfo *objInfo;
            /* No, check if the object is in memory already */
            if ((objInfo = lookupObjectInfo(store, offset)) == NULL) {
               /* It is not, so we create a reference for it */

               /* Check if the cell is an offline or origin reference */
               if (AllowLazyFetch && refType == REFTYPE_DYNAMIC) {
                  /* It is not, so we create a reference for it */
                  ip = referenceInfo(store, offset);
                  *theCell = (Object *)ip;
                  newAOAcell(ip, theCell);
               } else {
		 /* offline or origin reference */
                  /* We cannot create an indirect reference for such
                   * reference types, thus we have to load the object */
                  *theCell = USloadObject(store,
                                          offset,
                                          -1,
                                          1);
                  currentcsb = objInfoEnc -> store;
               }
            } else {
               /* The referenced object is in memory already. Note that the object
                * info returned above is the object info of the enclosing
                * object.
                */
               *theCell = (Object *)((unsigned long)(objInfo -> theObj) +
                                     (offset - objInfo -> offset));
            }
         } else {
            /* A proxy reference already exist for the object */
            *theCell = (Object *)ip;
            newAOAcell(ip, theCell);
         }
      }  else {
	/* special object referenced; e.g. betaenv */
         if (inIOA(*theCell = handleSpecialReference(offset))) {
            AOAtoIOAInsert( theCell);
         }
      }
   } else {
#ifdef RTDEBUG
     /* Cross store reference, currently not implemented */
     fprintf(output, "Cross store reference, currently not implemented\n");
     
#endif
   }
}

static void updateTransitObjectTable(Object *theObj, ObjInfo *objInfo, u_long forced)
{
   unsigned long distanceToPart;

   /* We are importing an object and must insert a notification in the
    * transit objects table that this particular object has been
    * imported. This goes for the object itself as well as for any
    * static part objects of the object. This function is called by
    * 'scanObject' for the object itself and all its static parts.
    */
  
   distanceToPart = (unsigned long)theObj - (unsigned long)(objInfo -> theObj);
   
   if (!forced) {
      insertObjectInTransit(objInfo -> store,
                            objInfo -> offset + distanceToPart,
                            theObj);
   }
   
   insertObject(objInfo -> store,
                objInfo -> offset + distanceToPart,
                objInfo);
   
}

extern void (*StackRefAction)(REFERENCEACTIONARGSTYPE, ObjInfo *objInfo);

static void importScanObject(Object *obj,
                             int doPartObjects,
                             ObjInfo *objInfo,
                             u_long forced)
{
   ProtoType *theProto;
   
   /* Import from disk format, fix prototypes, endian convert, etc.
    *
    * - The proto type
    * - The GCAtrribute
    * - All references
    * - All Values
    */
    
   /* The proto type */
   importProtoType(obj);   
   theProto = GETPROTO(obj);
  
   /* The GCAttribute */
#ifdef PSENDIAN
   obj -> GCAttr = ntohl(obj -> GCAttr);
#endif
   updateTransitObjectTable(obj, objInfo, forced);

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
            importScanObject((Object *)((long *)obj + tab->StaticOff), FALSE, objInfo, forced);
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
#ifdef PSENDIAN
            /* Endian convert the reference */
            *pointer = ntohl((u_long)*pointer);
#endif
            /* Import the reference */
            refhandler((Object **)pointer, refType, objInfo);
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
        
         numbytes = ((ObjectSize(obj)-1) / 8);
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
           ValRep *vobj = (ValRep *)obj;
#ifdef PSENDIAN
           long offset, offsetTop;
#endif
           u_long HighBorder;
           
#ifdef PSENDIAN
           vobj -> LowBorder = ntohl((u_long)vobj -> LowBorder);
           vobj -> HighBorder = ntohl((u_long)vobj -> HighBorder);
#endif
           HighBorder = vobj -> HighBorder;
           
           switch (SwitchProto(theProto)) {
             case SwitchProto(ShortRepPTValue):
             {
#ifdef PSENDIAN
                unsigned short *pointer;
                
                offset =  (char*)(&vobj->Body[0]) - (char*)vobj;
                offsetTop = offset + 2 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned short*)((char*)vobj + offset);
                   *pointer = ntohs(*pointer);
                   offset += 2;
                }
#endif
                break;
             }
             case SwitchProto(DoubleRepPTValue):
             {
#ifdef PSENDIAN
                unsigned long *pointer, x;
	
                offset =  (char*)(&vobj->Body[0]) - (char*)vobj;
                offsetTop = offset + 8 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned long*)((char*)vobj + offset);
                   x = ntohl(*pointer);
                   *pointer = ntohl(*(pointer+1));
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
                
                offset =  (char*)(&vobj->Body[0]) - (char*)vobj;
                offsetTop = offset + 4 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (unsigned long *)((char*)vobj + offset);
                   *pointer = ntohl(*pointer);
                   offset += 4;
                }
#endif
                break;
             }
             case SwitchProto(RefRepPTValue): 
             {
                long *pointer;
                long offset, offsetTop;
                
                offset =  (char*)(&((RefRep*)vobj)->Body[0]) - (char*)vobj;
                offsetTop = offset + 4 * HighBorder;
                
                while (offset < offsetTop) {
                   pointer = (long *)((char*)vobj + offset);
                   if (*pointer) {
#ifdef PSENDIAN
                      *pointer = ntohl(*pointer);
#endif
                      refhandler((Object **)pointer, REFTYPE_DYNAMIC, objInfo);
                   }
                   offset += 4;
                }
                break;
             }
             case SwitchProto(DynItemRepPTValue):
             case SwitchProto(DynCompRepPTValue):
             {
                ObjectRep *robj = (ObjectRep*)obj;
                long *pointer;
                long size, index;
#ifdef PSENDIAN
		robj->iProto = translateStoreProto((ProtoType*)
                                                   ntohl((u_long)robj->iProto),
                                                   objInfo -> store);
#else
		robj->iProto = translateStoreProto(robj->iProto,
                                                   objInfo -> store);
#endif
		
                /* Process iOrigin */
#ifdef PSENDIAN
                (robj -> iOrigin) = (Object *)ntohl((u_long)robj -> iOrigin);
#endif
                refhandler(&(robj -> iOrigin), REFTYPE_ORIGIN, objInfo);

                /* Process rest of repetition */
                size = HighBorder;
                pointer = (long *)&robj->Body[0];
                
                for (index=0; index<size; index++) {
                   if (*pointer) {
#ifdef PSENDIAN
                      *pointer = ntohl(*pointer);
#endif
                      refhandler((Object **)pointer, REFTYPE_OFFLINE, objInfo);
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
#ifdef PSENDIAN
           theComponent->StackObj = (StackObject *)ntohl((u_long)theComponent->StackObj);
#endif
           if ((theComponent->StackObj) &&
               (long)(theComponent->StackObj) != -1) {
              DEBUG_STACKOBJ({
                 fprintf(output, 
                         "Processing stackobj 0x%08x of component 0x%08x "
                         "with func=0x%08x\n",
                         (int)theComponent->StackObj, (int)theComponent, 
                         (int)refhandler);
              });
              refhandler((Object **)&(theComponent->StackObj), REFTYPE_DYNAMIC, objInfo);
           }
           if (theComponent->CallerComp) {
#ifdef PSENDIAN
              theComponent->CallerComp = (Component *)ntohl((u_long)theComponent->CallerComp);
#endif
              refhandler((Object **)&(theComponent->CallerComp), REFTYPE_DYNAMIC, objInfo);
           }
           if (theComponent->CallerObj) {
#ifdef PSENDIAN
              theComponent->CallerObj = (Object *)ntohl((u_long)theComponent->CallerObj);
#endif
              refhandler(&(theComponent->CallerObj), REFTYPE_DYNAMIC, objInfo);

           }
           if (doPartObjects) { 
              importScanObject((Object *)ComponentItem( theComponent), TRUE, objInfo, forced);
           }
#ifdef PSENDIAN
           ((Component*)obj) -> CallerLSC = (pc_t)(ntohl((long)((u_long)((Component*)obj) -> CallerLSC)));
#endif
           break;
        }
        case SwitchProto(StackObjectPTValue):
        {
#ifdef PSENDIAN
           ((StackObject *)obj) -> BodySize = ntohl((u_long)((StackObject *)obj) -> BodySize);
           ((StackObject *)obj) -> StackSize = ntohl((u_long)((StackObject *)obj) -> StackSize);
#endif
	   /* FIXME: does not work - no swizzling of instruction pointers etc. */
           StackRefAction = refhandler;
           ProcessStackObj((StackObject *)obj, StackRefActionWrapper);
           StackRefAction = NULL;

           break;
        }
        case SwitchProto(StructurePTValue):
        {

#ifdef PSENDIAN
           ((Structure*)(obj))->iOrigin = (Object *)ntohl((u_long)((Structure*)(obj))->iOrigin);
           ((Structure*)(obj))->iProto = translateStoreProto((ProtoType*)
                                                             ntohl((u_long)((Structure*)(obj))->iProto),
                                                             objInfo -> store);
#else
           ((Structure*)(obj))->iProto = translateStoreProto(((Structure*)(obj))->iProto,
                                                             objInfo -> store);
#endif
           refhandler(&(((Structure*)(obj))->iOrigin), REFTYPE_ORIGIN, objInfo);
           break;
        }
        case SwitchProto(DopartObjectPTValue):
        {
#ifdef PSENDIAN
           ((DopartObject *)(obj))->Origin = (Object *)ntohl((u_long)((DopartObject *)(obj))->Origin);
#endif
           refhandler(&(((DopartObject *)(obj))->Origin), REFTYPE_ORIGIN, objInfo);
           break;
        }
        default:
           Claim( FALSE, "importScanObject: theObj must be KNOWN.");
      }
   }
}

void importStoreObject(Object *theObj,
                       CAStorage *store,
                       u_long offset,
                       u_long size,
                       u_long forced)
{
   /* 'theObj' 
    *
    * Is an object in store format. This means that all references
    * within 'theObj' to objects in the same store as 'theObj' are
    * implemented as offsets. References to objects in other stores can
    * be identified as such and are implemented as offsets to a proxy
    * object. The task of 'importStoreObject' is to translate all
    * references in 'theObj' to in-memory format.
    *
    * 'store' 
    *
    * Is the context local store id of the store holding 'theObj'.
    *
    * 'offset'
    *
    * Is the offset of 'theObj' in the store.
    *
    * 'size'
    *
    * Is passed to enable the refhandler to resolve references internal
    * to the object from offsets.
    */

   ObjInfo *objInfo;

   Claim(theObj -> GCAttr == 0, "Unexpected part object?");
   
   /* Create an object info object for the object */
   
   objInfo = (ObjInfo *)AOAallocate(sizeof(struct _ObjInfo), TRUE);
   SETPROTO(objInfo, ObjInfoPTValue);
   
   objInfo -> flags = FLAG_INSTORE;   
   objInfo -> theObj = theObj;
   objInfo -> store = currentcsb = store;
   objInfo -> offset = offset;

#ifdef DEBUG_PERSISTENCE
   printf("importScanObjectTop=%d, importScanObjectSize=%d, %d\n",
          (int)theObj, (int)size, (int)offset);
#endif

   importScanObjectTop  = theObj;
   importScanObjectSize = size;
   
   importScanObject(theObj, TRUE, objInfo, forced);
   
   currentcsb = NULL;
   
   theObj -> GCAttr = (u_long)PUTOI(objInfo);
}

#endif /* PERSIST */
