/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * copyobject.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef PERSIST
#include "specialObjectsTable.h"
#include "objectTable.h"
#endif /* PERSIST */

#ifdef ALLOC_TRACE
#include "trace-types.h"
#endif

/*
 * CopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 */

static Object * CopyObject(Object * theObj)
{
    Object * newObj;
    long        size;
    
    size = 4*ObjectSize( theObj);
    Claim(isObject(theObj), "isObject(theObj)");
    
    
    /* Assure that IOAMinAge <= theObj->GCAttr <= IOAMaxAge. */
    Claim(IOAMinAge <= theObj->GCAttr,
	  "CopyObject: IOAMinAge <= Age of object.");
    Claim(theObj->GCAttr<=IOAMaxAge,
	  "CopyObject: Age of object<=IOAMaxAge.");
    
    if (theObj->GCAttr==IOAMaxAge) theObj->GCAttr--;
    IOAAgeTable[theObj->GCAttr-IOAMinAge] += size;
    
    DEBUG_AOA( IOAcopied += size );

    {
	register long * src;
	register long * dst;
	register long * theEnd;
	
	newObj     = (Object *) ToSpaceTop;
	theEnd     = (long *) (((long) newObj) + size); 
	
	Claim(theEnd<=ToSpaceLimit, "theEnd<=ToSpaceLimit");
	
	ToSpaceTop = theEnd;

	/* Check if ToSpace grows into AOAroots table 
	 * (residing in upper part of ToSpace) 
	 */
	if( !tempAOAroots &&
            (char *) ToSpaceTop+size > (char *) AOArootsPtr ){
            tempAOArootsAlloc();
	}
        
	src = (long *) theObj; dst = (long *) newObj; 

#       ifdef ALLOC_TRACE
	    if(alloc_trace_handle) {
		int i = TRACE_MOVE_OBJECT_IN_IOA;
		fwrite(&i, 4, 1, alloc_trace_handle);
		fwrite(&theObj, 4, 1, alloc_trace_handle);
		fwrite(&newObj, 4, 1, alloc_trace_handle);
	    }
#       endif
        
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
 */
Object * NewCopyObject(Object * theObj, Object ** theCell, int forceAOAAllocation)
{
  MCHECK();
  
  if (theObj->GCAttr < IOAtoAOAtreshold) {
    /* theObj is not old enough for AOA */
    return CopyObject(theObj);
    
  } else {
    /* theObj is old enough to go into AOA */
    Object * newObj;
#ifdef PERSIST
    long GCAttribute;
#endif /* PERSIST */
    MCHECK();

#ifdef PERSIST
    GCAttribute = theObj -> GCAttr;
#endif /* PERSIST */

    if ((newObj = CopyObjectToAOA(theObj, NULL, forceAOAAllocation))) {
      /* Insert theCell in AOAroots table. 
       * Used as roots in AOA GC if invoked after IOAGc.
       */
      MCHECK();
      if (theCell) {
	Claim(!inAOA(theCell), "!inAOA(theCell)");
	MCHECK();
	saveAOAroot(theCell);
	MCHECK();
      }

#ifdef PERSIST
      if (GCAttribute == IOASpecial) {
	insertSpecialObject(getTagForObject(theObj), newObj);
      } else if (GCAttribute == IOAPersist) {
	/* The object was a persistent object that has been moved to
	 * AOA. The object info for the object has been allocated,
	 * but is no longer correct since it has been moved. The info
	 * will be updated after the IOAGc has finished */
	;
      }     
#endif /* PERSIST */
      return newObj;
      
    } else {
      /* CopyObjectToAOA failed */
#ifdef PERSIST
      if ((GCAttribute == IOASpecial) || (GCAttribute  == IOAPersist)) {
	Object *theAOAObj;
	
	/* This will force an allocation of a new aoablock */
	theAOAObj = NewCopyObject(theObj, theCell, TRUE);
	
	Claim(inAOA(theAOAObj), "Where is theAOAObj?");
	
	return theAOAObj;
      } else {
	return CopyObject(theObj);
      } 
#else 
      return CopyObject(theObj);
#endif /* PERSIST */
    }
  }
}
