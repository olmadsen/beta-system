/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * copyobject.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

/*
 * CopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 */

static ref(Object) CopyObject(ref(Object) theObj)
{
    ref(Object) newObj;
    long        size;
    
    size = 4*ObjectSize( theObj);
#if 0
    fprintf(output, "theObj: 0x%x, proto: 0x%x, size: 0x%x\n", theObj, theObj->Proto, size);
#endif
    DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#CopyObject: ObjectSize(theObj) > 0") );
    
    /* Assure that theObj->GCAttr <= IOAMaxAge. */
    DEBUG_IOA( Claim( theObj->GCAttr<=IOAMaxAge,
		     "CopyObject: Age of object<=IOAMaxAge."));
    
#ifdef KEEP_STACKOBJ_IN_IOA
    if (!isStackObject(theObj))
      IOAAgeTable[theObj->GCAttr-IOAMinAge] += size;
    else {
	IOAStackObjectSum += size;
	IOAStackObjectNum++;
    }
#else
    IOAAgeTable[theObj->GCAttr-IOAMinAge] += size;
#endif
      
    
    DEBUG_AOA( IOAcopied += size );
    
    {
	register ptr(long) src;
	register ptr(long) dst;
	register ptr(long) theEnd;
	
	newObj     = (ref(Object)) ToSpaceTop;
	theEnd     = (ptr(long)) (((long) newObj) + size); 
	
	DEBUG_IOA( Claim(theEnd<=ToSpaceLimit, "theEnd<=ToSpaceLimit") );
	
	ToSpaceTop = theEnd;

	/* Check if ToSpace grows into AOAroots table 
	 * (residing in upper part of ToSpace) 
	 */
	if( !tempAOAroots &&
	   (char *) ToSpaceTop+size > (char *) AOArootsPtr ){
	  tempAOArootsAlloc();
	}

	src = (ptr(long)) theObj; dst = (ptr(long)) newObj; 

	while( dst < theEnd) *dst++ = *src++; 
	
    }
    /* Increase the age of the object */
    if( newObj->GCAttr < IOAMaxAge ) newObj->GCAttr++;
    
    /* Set one forward reference in theObj to newObj */
    theObj->GCAttr = (long) newObj;
    
    /* Return the new object in ToSpace */
    return newObj;
}

/*
 * NewCopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 *  If theCell is not 0 it should be treated as an AOA root, in case
 *  theObj is moved to AOA.
 *  The function is used by IOAGc.
 * 
 * FIXME: better parameters: (struct Object **theCell, int useForAOAroot)
 *        will allow for all LVRA reps in ioa to be handled (and will
 *        be more readable)
 */
ref(Object) NewCopyObject(ref(Object) theObj, handle(Object) theCell)
{
  
#ifdef CHECK_LVRA_IN_IOA
  if (isValRep(theObj)) {
    if( ((ref(ValRep)) theObj)->HighBorder > LARGE_REP_SIZE){
      /* A large val rep was detected in the IOA heap */
      if (theCell){
	/* Can only do this if theCell was supplied as
	 * argument, since we cannot establish LVRA cycle
	 * otherwise. And NewCopyObject is called from e.g. 
	 * ProcessAOAObject with theCell==0.
	 */
	ref(Object) newObj; 
	if ((newObj = CopyObjectToLVRA((ref(ValRep))theObj))) {
	  newObj->GCAttr = (long) theCell; /* Preserve the LVRA-Cycle */
	  DEBUG_LVRA( Claim( isValRep(cast(ValRep)*theCell),
			    "NewCopyObject: isValRep(cast(ValRep)*theCell)" ));
	  return newObj;
	}
      } 
    }
  }
#endif /* CHECK_LVRA_IN_IOA */
    
  if( theObj->GCAttr >= IOAtoAOAtreshold ){
    /* theObj is old enough to go into AOA */
    ref(Object) newObj;
    
#ifdef KEEP_STACKOBJ_IN_IOA
    if( isStackObject(theObj) ) return CopyObject(theObj);
#endif
    
    if( (newObj = CopyObjectToAOA(theObj)) ){
      /* Insert theCell in AOAroots table. 
       * Used as roots in mark-sweep if an AOA GC is invoked after IOAGc.
       */
      
#if 0
      if (newObj->Proto==RefRepPTValue){
	int i;
	struct RefRep * r = (struct RefRep*)newObj;

	fprintf(output, "\n\n***Moved RefRef to AOA. Contents:\n");
	for (i=0; i<r->HighBorder; i++){
	  struct Object *o = (struct Object *)((long*)r+4+i);
	  fprintf(output, "  [%d] 0x%x: 0x%x", i, (int)o, *(int*)o);
	  if (inIOA(o)){
	    fprintf(output, " (in IOA)\n");
	  } else {
	    fprintf(output, " (not in IOA)\n");
	  }
	}
	fprintf(output, "\n\n");
      }
#endif

      if (theCell) {
	MCHECK();
	saveAOAroot(theCell);
	MCHECK();
      }
      return newObj;
    } else {
      /* CopyObjectToAOA failed */
      return CopyObject(theObj);
    }
  } else {
    /* theObj is not old enough for AOA */
    return CopyObject(theObj);
  }
}
