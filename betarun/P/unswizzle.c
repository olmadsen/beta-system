#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "PImport.h"
#include "proto.h"
#include "unswizzle.h"
#include "transitObjectTable.h"
#include "misc.h"
#include "storageblock.h"
#include "dot.h"
#include "pit.h"

/* */

#define MAXPERSISTENTBYTES 2048 * Kb

/* LOCAL VARIABLES */
static unsigned long loadedBytes = 0;
static unsigned long forceAOACompaction = 0;

/* GLOBAL VARIABLES */
int betaenvHandle; 
int programHandle;
u_long speciallookup;

/* LOCAL FUNCTION DECLARATIONS */
Object *USloadObject(CAStorage *store,
                     unsigned long offset, 
                     unsigned long inx,
                     u_long follow);

/* FUNCTIONS */
void USstart(void)
{
   speciallookup = 0;
}

void USend(void)
{
   fprintf(stderr, "special: %d\n", (int)speciallookup);
}

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */
void showUnswizzleStatistics(void)
{
   ;
}

Object *unswizzleReference(void *ip, u_long follow)
{
   RefInfo *refInfo;
   
   refInfo = PITlookup(ip);

   if (refInfo -> objInTransit) {
      Claim(AOAISPERSISTENT(refInfo -> objInTransit), "Object not persistent?");
      
      return refInfo -> objInTransit;
   } else {
      if (!isOutReference(refInfo -> offset)) {
         if (!isSpecialReference(refInfo -> offset)) {
            refInfo -> objInTransit = USloadObject(refInfo -> store, refInfo -> offset, -1, follow);
            return refInfo -> objInTransit;
         } else {
            /* handle special reference */
            perror("unswizzleReference: unbound special reference");
            return NULL;
         }
      } else {
         /* handle cross store offset */
         /* Open referred store, not implemented yet */
         perror("unswizzleReference: out reference binding not implemented yet");
         return NULL;
      }
   }
}

#ifdef PSENDIAN
static void EndianconvertFromStoreProc(REFERENCEACTIONARGSTYPE)
{
   *theCell = (Object*)ntohl((unsigned long)*theCell);
}

void EndianconvertFromStore(Object *obj)
{
   ProtoType * theProto;
  
   theProto = GETPROTO(obj);
   
   if (!isSpecialProtoType(theProto)) {
      unsigned char *ebits, b, do_int16, do_real64;
      unsigned long offset, pos;
      short * refs_ofs;
      short *ptr;
      int numbytes;
      GCEntry *tab =
         (GCEntry *) ((char *) theProto + theProto->GCTabOff);

      /* Handle all reference fields in obj: */
      scanObject(obj, EndianconvertFromStoreProc, NULL, TRUE);
      /* Skip part-object table: */
      for (;tab->StaticOff; ++tab) {
         ;
      }
      /* Skip dynrefs : */
      for (refs_ofs = (short *)&tab->StaticOff+1; *refs_ofs; refs_ofs++) {
         ;
      }

      /* Handle all longs: */
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
   } else {
      switch (SwitchProto(theProto)) {
        case SwitchProto(LongRepPTValue):     
        {
           unsigned long *pointer;
           long offset, offsetTop;
              
           offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
           offsetTop = offset + 4 * ((ValRep*)(obj))->HighBorder;

           while (offset < offsetTop) {
              pointer = (unsigned long *)((char*)obj + offset);
              *pointer = ntohl(*pointer);
              offset += 4;
           }
           break;
        }

        case SwitchProto(DoubleRepPTValue):
        {
           unsigned long *pointer, x;
           long offset, offsetTop;
	
           offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
           offsetTop = offset + 8 * ((ValRep*)(obj))->HighBorder;
	
           while (offset < offsetTop) {
              pointer = (unsigned long*)((char*)obj + offset);
              x = ntohl(*pointer);
              *pointer = ntohl(*(pointer+1));
              *(pointer+1) = x;
              offset += 8;
           }
           break;
        }
        case SwitchProto(ShortRepPTValue):
        {
           unsigned short *pointer;
           long offset, offsetTop;
              
           offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
           offsetTop = offset + 2 * ((ValRep*)(obj))->HighBorder;
	
           while (offset < offsetTop) {
              pointer = (unsigned short*)((char*)obj + offset);
              *pointer = ntohs(*pointer);
              offset += 2;
           }
           break;
        }
      }
   }
}
#endif /* PSENDIAN */

Object *USloadObject(CAStorage *store,
                     unsigned long offset,
                     unsigned long inx,
                     u_long follow)
{
   unsigned long size, distanceToPart;
   Object *theStoreObj, *theRealStoreObj, *theRealObj;
   
   theStoreObj = (Object *)SBOBJlookup(store, offset);
   
   Claim(theStoreObj != NULL, "Could not look up store object");
   
   theRealStoreObj = getRealObject(theStoreObj);
   distanceToPart = (unsigned long)theStoreObj - (unsigned long)theRealStoreObj;
   
   if (distanceToPart == 0) {
      forceAOAAllocation = TRUE; /* The following allocation must not fail*/
      size = 4*StoreObjectSize(theRealStoreObj, store);
      theRealObj = AOAallocate(2*size);
      loadedBytes += 2*size;
      if (loadedBytes > MAXPERSISTENTBYTES) {
         loadedBytes = 0;
         forceAOACompaction = TRUE;
         DEBUG_CODE(fprintf(output, "Max persistent bytes exceeded\n"));
      }
      if (forceAOACompaction) {
         DEBUG_CODE(fprintf(output, "Requesting GC at next allocation\n"));
         /* Request GC at next IOAAllocation */
         AOANeedCompaction = TRUE;
         forceAOACompaction = FALSE;
#if defined(NEWRUN) || defined(sparc)
         IOATopOff = (char *)IOALimit  - (char *) IOA;
#else
         IOATop = IOALimit;
#endif
      }
      memcpy(theRealObj, theRealStoreObj, size);
      importProtoTypes(theRealObj, store);
      
      /* A copy of the object is saved after the object it self. This
         copy is still in store format apart from the prototypes which
         are in in memory format. */
      memcpy((char*)theRealObj+size, theRealObj, size);
      /* The copy is marked as alive. This marking is only used to
	 indicate to the GC'er that it should not free the space taken
	 up by the object. */
      ((Object*)((char*)theRealObj+size))->GCAttr = LISTEND;
      
      /* The real object is imported */
#ifdef PSENDIAN
      EndianconvertFromStore(theRealObj);
#endif
      importStoreObject(theRealObj, store, offset, inx, follow);
        
      INFO_PERSISTENCE(objectsLoaded++);
      return theRealObj;
   } else {
      Object *theRealObj;
      
      theRealObj = USloadObject(store,
                                offset - distanceToPart,
                                -1,
                                follow);
      return (Object *)((unsigned long)theRealObj + distanceToPart);
   }
}

Object *handleSpecialReference(unsigned long specRef)
{
   unsigned long tag, distanceToPart;
   Object *target = NULL;
  
   Claim(isSpecialReference(specRef),
         "handleSpecialReference: Is not special reference");
  
   tag = specRef >> 24;
   distanceToPart = (specRef & 0x00FFFF00) >> 8;
  
   /* Below we reenter BETA code while we are in the midst of loading
      an object. While in BETA code additional object loads might be
      issued, and GCs, both IOAGC amd AOAGC, might occur. While it
      should be possible to support all these events only an IOAGC is
      legal at this point in time. */
  
   if (tag == BETAENVOBJ) {
      target = DOThandleLookup(betaenvHandle);
   } else if (tag == PRGOBJ) {
      target = DOThandleLookup(programHandle);
   } else {
      BETAREENTERED = TRUE;
      if (callRebinderC) {
         target = callRebinderC(tag);
         BETAREENTERED = FALSE;
         speciallookup++;
      } else {
         fprintf(output,
                 "handleSpecialReference: Store is not initialized");
         BetaExit(1);
      }
   }
   if (target) {
      target = (Object *)((unsigned long)getRealObject(target)
                          + distanceToPart);
   } else {
      fprintf(output, 
              "handleSpecialReference: User code failed to rebind\n"
              "reference to special object tagged %d. Make sure\n"
              "the 'rebindSpecialReference' virtual has been implemented\n"
              "correctly.\n", (int)tag);
      BetaExit(1);
   }
   return target;
}

void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long tag))
{
   callRebinderC = rebinderFunc;
}

void registerBETAENVandPROGRAM(Component *theProgram)
{
   Object *betaenvObj, *programObj;
   programObj = (Object *)ComponentItem(theProgram);
   betaenvObj = *(Object **)((unsigned long)programObj + 0x8);

   DOTinit();

   /* */
   if ((betaenvHandle = DOThandleInsert(betaenvObj, (void (*)(int handle))0, TRUE)) == -1) {
      fprintf(output, "registerBETAENVandPROGRAM: Failed to insert betaenvObj in dot!");
      BetaExit(1);
   }
  
   if ((programHandle = DOThandleInsert(programObj, (void (*)(int handle))0, TRUE)) == -1) {
      fprintf(output, "registerBETAENVandPROGRAM: Failed to insert programObj in dot!");
      BetaExit(1);
   }
  
   markSpecialObject(betaenvObj, BETAENVOBJ);
   markSpecialObject(programObj, PRGOBJ);
}
#endif /* PERSIST */
