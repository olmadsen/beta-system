#include "beta.h"
#include "trie.h"
#include "storageblock.h"

/* */
#ifdef PERSIST

#ifndef MAC
#include <sys/types.h>
#endif

/* Get definition of ntohl */
#if defined(sun4s) || defined(sgi) || defined(linux)
#include <sys/types.h>
#include <netinet/in.h>
#else
#if defined(nti)
#include "winsock.h"
#else
#error Include definition of ntohl, please
#endif
#endif 

CAStorage *currentcsb;

/* LOCAL TYPES */
typedef struct protoID {
  unsigned long group;
  unsigned long protoNo;
} protoID;

/* LOCAL FUNCTION DECLARATIONS */
static ProtoType *PrototypeNoToProto(group_header *gh, unsigned long protoNo);

/* Maps prototype references to prototype ID's (group, protoNo) */
static Trie *PtoICache;
static Trie *ItoPCache;

void initProtoHandling(void)
{
  PtoICache = TInit();
  ItoPCache = TInit();
}

static void freeFunc(unsigned long contents)
{
  free((void *)contents);
}

void freeProtoHandling(void)
{
  TIFree(PtoICache, freeFunc);
  TIFree(ItoPCache, NULL);
}

void AddProtoToCache(unsigned long group, 
		     unsigned long protono, 
		     ProtoType* theProto)
{
  protoID *id = (protoID *)malloc(sizeof(protoID));
  
  id -> group = group;
  id -> protoNo = protono;
  
  TInsert((unsigned long)theProto, (unsigned long)id,
	  &PtoICache, (unsigned long)theProto);
}

char *FindNameByGroupID(unsigned long group, CAStorage *store)
{
    /* The id 'group' is an offset into the groupname area in the
     * store.
     */
    u_long length;
    
    return SBGNlookup((CAStorage *)store, group, &length);
}

unsigned long FindGroupIDByName(char *name)
{
    u_long length, top, offset = 0;
    char *current;
    
    top = SBGNtop(currentcsb);
    
    while(offset < top) {
        current = SBGNlookup((CAStorage *)currentcsb, offset, &length);
        if (strcmp(current,name) == 0) {
            return offset;
        }
        offset += length + sizeof(u_long);
    }
    
    DEBUG_CODE(Claim(offset == top, "FindGroupIDByName: passed end."));
    
    /* Not found in table.  Add new entry. */
    return SBGNcreate((CAStorage *)currentcsb, name);
}

void protoAddrToID(ProtoType *theProto, unsigned long *group, unsigned long *protoNo)
{
  group_header *gh;
  protoID *id;
  
  if ((id = (protoID *)TILookup((unsigned long)theProto, PtoICache))) {
    *group = id -> group;
    *protoNo = id -> protoNo;
    return;
  }
  
  if (isSpecialProtoType(theProto)) {
    *group = -1; /* Mark indicating special prototype */
    *protoNo = (unsigned long)theProto;
    
  } else {
    *group = 0;
    *protoNo = -1; /* Mark as illegal proto id. If the proto is not
		    * found this will signal error to caller. */

    for (gh = NextGroup(0); gh; gh = NextGroup(gh)) {
      unsigned long pNo;
      
      if ((pNo = IsPrototypeOfGroup(gh, (long)theProto)) > 0) {
	char *name = NameOfGroupMacro(gh);
	*group = FindGroupIDByName(name);
	*protoNo = pNo - 1;
	
	AddProtoToCache(*group, *protoNo, theProto);
	return;
      }
    }
  }
  /* Failing Lookups are not cached */
}

ProtoType *IDtoProtoAddr(unsigned long group, unsigned long protoNo, CAStorage *store)
{
  group_header *gh;
  unsigned long key;
  ProtoType *theProto;
  char *groupname;

  Claim(group <= 0xFFFF, "group too large");
  Claim(protoNo < 0xFFFF, "protoNo too large");
  
  key = ((group << 16) | protoNo);
  if ((theProto = (ProtoType *)TILookup(key, ItoPCache))) {
    return theProto;
  }
  
  if (group == 0xFFFF) {
    /* isSpecialProtoType */
    return (ProtoType*)protoNo;
  }

  groupname = FindNameByGroupID(group, store);

  for (gh = NextGroup(0); gh; gh = NextGroup(gh)) {
    if (!strcmp(NameOfGroupMacro(gh), groupname)) {
      break;
    }
  }
  
  if (gh) {
    theProto = PrototypeNoToProto(gh, protoNo);
    TInsert(key, (unsigned long)theProto, &ItoPCache, key);
    return theProto;
  }
  
  return NULL;
}

static ProtoType *PrototypeNoToProto(group_header *gh, unsigned long protoNo) 
{ 
  long* proto=&gh->protoTable[1];
  unsigned long NoOfPrototypes;
  
  NoOfPrototypes = gh->protoTable[0];
  if (protoNo < NoOfPrototypes) {
    return (ProtoType *)proto[protoNo];
  } else {
    return NULL;
  }
  return NULL;
}

void exportProtoType(Object *theObj)
{
   unsigned long group;
   unsigned long protoNo;
  
   protoAddrToID(GETPROTO(theObj),
                 &group,
                 &protoNo);
  
   if (group == -1) {
      /* the prototype is a special prototype and thus no conversion
         is necessary */
#ifdef PSENDIAN
      theObj->vtbl = (long *)htonl((unsigned long)GETPROTO(theObj));
#endif
   } else {
      Claim(protoNo != -1, "exportProtoType: Export of proto pointer failed");
      Claim(group < ( 1 << 16), "exportProtoType: Group too large");
      Claim(protoNo < ( 1 << 16), "exportProtoType: protoNo too large");
#ifdef PSENDIAN
      theObj->vtbl = (long *)htonl((unsigned long)((group << 16) | protoNo));
#else
      SETPROTO(theObj, (ProtoType *)((group << 16) | protoNo));
#endif
   }
}

void exportProtoTypes(Object *theObj, CAStorage *store)
{
   currentcsb = store;
   scanObject(theObj,
              NULL,
              exportProtoType,
              TRUE);
   currentcsb = NULL;
}

ProtoType *translateStoreProto(ProtoType *theProto, CAStorage *store)
{
   unsigned long group;
   unsigned long protoNo;
   
   if (isSpecialProtoType(theProto)) {
      return theProto;
   } else {
      group = (unsigned long)(theProto) >> 16;
      protoNo = (unsigned long)(theProto) & 0x0000FFFF;
      
      return IDtoProtoAddr(group, protoNo, store);
   }
}

void importProtoType(Object *theObj)
{ 
#ifdef PSENDIAN
   SETPROTO(theObj, translateStoreProto((ProtoType*)
                                        ntohl((unsigned long)theObj->vtbl), currentcsb));
#else
   SETPROTO(theObj, translateStoreProto(GETPROTO(theObj), currentcsb));
#endif
   Claim(GETPROTO(theObj) != NULL, "Could not find prototype");
}

void importProtoTypes(Object *theObj, CAStorage *store)
{
   currentcsb = store;
   dontCheckProtoTypes = TRUE;
   scanObject(theObj,
              NULL,
              importProtoType,
              TRUE);
   dontCheckProtoTypes = FALSE;
   currentcsb = NULL;
}

unsigned long StoreObjectSize(Object * theObj, CAStorage *store)
{ 
#ifdef PSENDIAN
   ProtoType * theProto = (ProtoType*)ntohl((unsigned long)theObj->vtbl);
#else
   ProtoType * theProto = GETPROTO(theObj);
#endif
  
   if (isNotSpecialProtoType(theProto)) {
      /* This is an item, so find the size in the protoType. */
      theProto = translateStoreProto(theProto, store);
      Claim(theProto != NULL, "Could not find prototype");
      return theProto->Size;
   } else {
      switch(SwitchProto(theProto)){
        case SwitchProto(ShortRepPTValue):
           return ShortRepSize(((ValRep*)theObj)->HighBorder) >> 2;
          
        case SwitchProto(ByteRepPTValue):
           return ByteRepSize(((ValRep*)theObj)->HighBorder) >> 2;
      
        case SwitchProto(DoubleRepPTValue):
           return DoubleRepSize(((ValRep*)theObj)->HighBorder) >> 2;
              
        case SwitchProto(LongRepPTValue):
           return LongRepSize(((ValRep*)theObj)->HighBorder) >> 2;
      
        case SwitchProto(DynItemRepPTValue):
        case SwitchProto(DynCompRepPTValue):
           return DynObjectRepSize(((ObjectRep *)theObj)->HighBorder) >> 2;
      
        case SwitchProto(RefRepPTValue):
           return RefRepSize(((RefRep*)theObj)->HighBorder) >> 2;
      
        case SwitchProto(ComponentPTValue):
           theProto = translateStoreProto(GETPROTO(ComponentItem(theObj)), store);
           Claim(theProto != NULL, "Could not find prototype");
           
           return ComponentSize(theProto) >> 2;
           
        case SwitchProto(StackObjectPTValue):
           return StackObjectSize(((StackObject*)theObj)->BodySize) >> 2;
           
        case SwitchProto(StructurePTValue):
           return StructureSize >> 2;
              
        case SwitchProto(DopartObjectPTValue):
           return DopartObjectSize(((DopartObject *)(theObj))->Size) >> 2;
        default:
           DEBUG_CODE(
              fprintf(stderr, 
                      "ObjectSize: Error: Unknown ProtoType %d for object 0x%08x\n",
                      (int)theProto, 
                      (int)theObj);
              );
      }
   }
   return 0;
}

#endif /* PERSIST */
