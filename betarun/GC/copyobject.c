/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: copyobject.c,v $, rel: %R%, date: $Date: 1992-08-19 11:54:31 $, SID: $Revision: 1.6 $
 * by Lars Bak.
 */

#include "beta.h"

/*
 * CopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 */

static ref(Object) CopyObject( theObj)
     ref(Object) theObj;
{
  ref(Object) newObj;
  long        size;
  
  size = 4*ObjectSize( theObj);
  
  /* Assume that theObj->GCAttr <= IOAMaxAge. */
  DEBUG_IOA( Claim( theObj->GCAttr<=IOAMaxAge,
		   "CopyObject: Age of object > IOAMaxAge."));
  
  IOAAgeTable[theObj->GCAttr-1] += size;
  
  
  DEBUG_AOA( IOAcopied += size );
  
  {
    register ptr(long) src;
    register ptr(long) dst;
    register ptr(long) theEnd;
    
    newObj     = (ref(Object)) ToSpaceTop;
    theEnd     = (ptr(long)) (((long) newObj) + size); 
    
    ToSpaceTop = theEnd;
#ifdef AO_Area
    if( ToSpaceTop >= ToSpacePtr ){
      /* Not enough room for the ToSpaceToAOAtable in ToSpace.
       * Instead allocate offline and copy existing part of table over
       */
      ptr(long) oldPtr;
      ptr(long) pointer = ToSpaceToAOAtable; /* points to start of old table */

      if ( ! (ToSpaceToAOAtable = (long) malloc(IOASize)) ){
	fprintf(output, "Could not allocate ToSpaceToAOAtable.\n");
	exit(1);
      } 
      INFO_AOA( fprintf(output,"#(AOA: temporary ToSpaceToAOAtable allocated %dKb.)\n", IOASize/Kb));
      
      oldPtr = ToSpacePtr; /* end of old table */
      ToSpacePtr = ToSpaceToAOAtable; /* start of new table */
      while(pointer > oldPtr) *--ToSpacePtr = *--pointer;
    }
#endif
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
 *  The function used by IOAGc.
 */
ref(Object) NewCopyObject( theObj, theCell)
     ref(Object)    theObj;
     handle(Object) theCell;
{
#ifdef LVR_Area
  extern ref(Object) CopyObjectToLVRA(); 
  if( isValRep( theObj) ){
    if( ((ref(ValRep)) theObj)->HighBorder > LARGE_REP_SIZE){
      /* A large val rep was detected in the IOA heap */
      ref(Object) newObj; 
      if( newObj = CopyObjectToLVRA( theObj) ){
	newObj->GCAttr = (long) theCell; /* Preserve the LVRA-Cycle */
	DEBUG_LVRA( Claim( isValRep(ref(ValRep)*theCell),
			  "NewCopyObject: isValRep(ref(ValRep)*theCell)" ));
	return newObj;
      } else {
	/* The ValRep was not large */
	return CopyObject( theObj);
      }
    }
  }
#endif
  
#ifdef AO_Area
  if( theObj->GCAttr >= IOAtoAOAtreshold ){
    /* theObj is old enough to go into AOA */
    extern ref(Object) CopyObjectToAOA(); 
    if( !isStackObject(theObj) ){
      ref(Object) newObj; 
      if( newObj = CopyObjectToAOA( theObj) ){
        /* Insert theCell in ToSpaceToAOAtable. 
	 * Used as roots in mark-sweep if an AOA GC is invoked after IOAGc.
	 */
        if( ToSpacePtr && theCell ) *--ToSpacePtr = (long) theCell;
	return newObj;
      } else {
	return CopyObject( theObj);
      }
    }
  }
#endif
  return CopyObject( theObj);
}
