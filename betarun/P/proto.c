#include "beta.h"
#include "trie.h"

/* */
#ifdef PERSIST
#include <sys/types.h>
#include "PStore.h"

extern PStoreHeader *currentPStore;

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


char *FindNameByGroupID(unsigned long group)
{
  unsigned long idx = 1;
  char *current = currentPStore->protoNames.names;
  char *end = current+currentPStore->protoNames.top;
  while (current<end) {
    if (idx == group) {
      return current;
    }
    current += strlen(current)+1;
    idx++;
  }
  fprintf(output, "Got groupindex outside range in use\n");
  DEBUG_CODE(Illegal());
  BetaExit(1);
  return NULL;
}

unsigned long FindGroupIDByName(char *name)
{
  unsigned long idx = 1;
  char *current = currentPStore->protoNames.names;
  char *end = current+currentPStore->protoNames.top;
  while (current<end) {
    if (!strcmp(current,name)) {
      return idx;
    }
    current += strlen(current)+1;
    idx++;
  }
  DEBUG_CODE(Claim(current == end, "FindGroupIDByName: passed end."));

  /* Not found in table.  Add new entry. */
  {
    unsigned long len = strlen(name) + 1;
    if (currentPStore->protoNames.top + len > currentPStore->protoNames.size) {
      /* Make room for more groupnames now! */
      /* FIXME!  Do this... */
      fprintf(output,
	      "FindGroupIDByName: NYI: Make room for more groupnames\n");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    } 
    
    DEBUG_CODE({
      Claim(currentPStore->protoNames.top + len 
	    <= currentPStore->protoNames.size,
	    "FindGroupIDByName: Did not get enough room");
    });
    
    memcpy(current, name, len);
    currentPStore->protoNames.top += len;
    return idx;
  }
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

ProtoType *IDtoProtoAddr(unsigned long group, unsigned long protoNo)
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

  groupname = FindNameByGroupID(group);

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

static void exportProtoType(Object *theObj)
{
  unsigned long group;
  unsigned long protoNo;
  
  protoAddrToID(GETPROTO(theObj),
		&group,
		&protoNo);
  
  if (group == -1) {
    /* the prototype is a special prototype and thus no conversion
       is necessary */
    ; 
  } else {
    Claim(protoNo != -1, "exportProtoType: Export of proto pointer failed");
    Claim(group < ( 1 << 16), "exportProtoType: Group too large");
    Claim(protoNo < ( 1 << 16), "exportProtoType: protoNo too large");
    SETPROTO(theObj, (ProtoType *)((group << 16) | protoNo));
  }
}

void exportProtoTypes(Object *theObj)
{
  scanObject(theObj,
	     NULL,
	     exportProtoType,
	     TRUE);
}

ProtoType *translateStoreProto(ProtoType *theProto)
{
  unsigned long group;
  unsigned long protoNo;
  
  if (isSpecialProtoType(theProto)) {
    return theProto;
  } else {
    group = (unsigned long)(theProto) >> 16;
    protoNo = (unsigned long)(theProto) & 0x0000FFFF;
    
    return IDtoProtoAddr(group, protoNo);
  }
}

static void importProtoType(Object *theObj)
{ 
  SETPROTO(theObj, translateStoreProto(GETPROTO(theObj)));
  Claim(GETPROTO(theObj) != NULL, "Could not find prototype");
}

void importProtoTypes(Object *theObj) 
{
  dontCheckProtoTypes = TRUE;
  scanObject(theObj,
	     NULL,
	     importProtoType,
	     TRUE);
  dontCheckProtoTypes = FALSE;
}

unsigned long StoreObjectSize(Object * theObj)
{ 
  ProtoType * theProto = GETPROTO(theObj);
  
  if (isNotSpecialProtoType(theProto)) {
    /* This is an item, so find the size in the protoType. */
    theProto = translateStoreProto(theProto);
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
      theProto = translateStoreProto(GETPROTO(ComponentItem(theObj)));
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
