#include "beta.h"
#include "trie.h"

void proto_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

/* */
#ifdef PERSIST
#include <sys/types.h>

/* LOCAL TYPES */
typedef struct protoID {
  u_long group;
  u_long protoNo;
} protoID;

/* LOCAL FUNCTION DECLARATIONS */
static ProtoType *PrototypeNoToProto(group_header *gh, u_long protoNo);

/* Maps prototype references to prototype ID's (group, protoNo) */
static Node *PtoICache;
static Node *ItoPCache;

void initProtoHandling(void)
{
  PtoICache = TInit();
  ItoPCache = TInit();
}

static void freeFunc(void *contents)
{
  free(contents);
}

void freeProtoHandling(void)
{
  TIFree(PtoICache, freeFunc);
  TIFree(ItoPCache, NULL);
}

void protoAddrToID(ProtoType *theProto, u_long *group, u_long *protoNo)
{
  group_header *gh;
  protoID *id;
  
  if ((id = TILookup((u_long)theProto, PtoICache))) {
    *group = id -> group;
    *protoNo = id -> protoNo;
    return;
  }
  
  if (isSpecialProtoType(theProto)) {
    *group = -1; /* Mark indicating special prototype */
    *protoNo = (u_long)theProto;
    
  } else {
    u_long count;
    
    *group = 0;
    *protoNo = -1; /* Mark as illegal proto id. If the proto is not
		    * found this will signal error to caller. */
    gh = NextGroup(0);
    count = 0;
    while (gh) {
      u_long pNo;
      
      if ((pNo = IsPrototypeOfGroup(gh, (long)theProto)) > 0) {
	*group = count;
	*protoNo = pNo - 1;
	
	/* Save this mapping for later */
	{
	  id=(protoID *)malloc(sizeof(protoID));
	  
	  id -> group = *group;
	  id -> protoNo = *protoNo;
	  
	  TInsert((u_long)theProto, (void *)id, PtoICache, (u_long)theProto);
	}
	return;
      }
      count++;
      gh = NextGroup(gh);
    }
  }
  /* Failing Lookups are not cached */
}

ProtoType *IDtoProtoAddr(u_long group, u_long protoNo)
{
  group_header *gh;
  u_long count, key;
  ProtoType *theProto;
  
  Claim(group < 0xFFFF, "group too large");
  Claim(protoNo < 0xFFFF, "protoNo too large");
  
  key = ((group << 16) | protoNo);
  if ((theProto = TILookup(key, ItoPCache))) {
    return theProto;
  }
  
  gh = NextGroup(0);
  count = 0;
  
  while ((count < group) && (gh)) {
    count++;
    gh = NextGroup(gh);
  }
  
  if (gh) {
    theProto = PrototypeNoToProto(gh, protoNo);
    TInsert(key, (void *)theProto, ItoPCache, key);
    return theProto;
  }
  
  return 0;
}

static ProtoType *PrototypeNoToProto(group_header *gh, u_long protoNo) 
{ 
  long* proto=&gh->protoTable[1];
  int NoOfPrototypes;
  
  NoOfPrototypes = gh->protoTable[0];
  if (protoNo < NoOfPrototypes) {
    return (ProtoType *)proto[protoNo];
  } else {
    return 0;
  }
  return 0;
}

static void exportProtoType(Object *theObj)
{
  u_long group;
  u_long protoNo;
  
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
  void (*temp)(Object *theObj);
	
  temp = objectAction; 
  objectAction = exportProtoType;
  scanObject(theObj,
	     NULL,
	     TRUE);
  objectAction = temp;
}

ProtoType *translateStoreProto(ProtoType *theProto)
{
  u_long group;
  u_long protoNo;
  
  if (isSpecialProtoType(theProto)) {
    return theProto;
  } else {
    group = (u_long)(theProto) >> 16;
    protoNo = (u_long)(theProto) & 0x0000FFFF;
    
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
  void (*temp)(Object *theObj);
  
  temp = objectAction;
  objectAction = importProtoType;
  dontCheckProtoTypes = TRUE;
  scanObject(theObj,
	     NULL,
	     TRUE);
  dontCheckProtoTypes = FALSE;
  objectAction = temp;
}

u_long StoreObjectSize(Object * theObj)
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
