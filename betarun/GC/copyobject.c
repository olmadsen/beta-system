/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * copyobject.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"

/* tempToSpaceToAOAalloc:
 *  Not enough room for the ToSpaceToAOA table in ToSpace.
 *  Instead allocate offline and copy existing part of table over
 */

void tempToSpaceToAOAalloc()
{
    ptr(long) oldPtr;
    ptr(long) pointer = ToSpaceLimit; /* points to end of old table */
    
    if ( ! (tempToSpaceToAOA = (long *) MALLOC(IOASize)) ){
	fprintf(output, "Could not allocate ToSpaceToAOA table.\n");
	exit(1);
    } 
    ToSpaceToAOALimit = (long *) ((char *) tempToSpaceToAOA + IOASize);
    INFO_IOA( fprintf(output,
		      "#IOA: temporary ToSpaceToAOA table allocated %dKb.\n", IOASize/Kb));
    
    oldPtr = ToSpaceToAOAptr; /* start of old table */
    ToSpaceToAOAptr = ToSpaceToAOALimit; /* end of new table */
    
    /* Copy old table backwards */
    while(pointer > oldPtr) *--ToSpaceToAOAptr = *--pointer; 
}

void tempToSpaceToAOAfree()
{
    FREE(tempToSpaceToAOA);
    tempToSpaceToAOA = NULL;
    INFO_IOA(fprintf(output, "#IOA: freed temporary ToSpaceToAOA table\n"));
}

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
    
    if (!isStackObject(theObj))
      IOAAgeTable[theObj->GCAttr-1] += size;
    else {
	IOAStackObjectSum += size;
	IOAStackObjectNum++;
    }
      
    
    DEBUG_AOA( IOAcopied += size );
    
    {
	register ptr(long) src;
	register ptr(long) dst;
	register ptr(long) theEnd;
	
	newObj     = (ref(Object)) ToSpaceTop;
	theEnd     = (ptr(long)) (((long) newObj) + size); 
	
	ToSpaceTop = theEnd;
#ifdef AO_Area
	if( !tempToSpaceToAOA &&
	   (char *) ToSpaceTop+size > (char *) ToSpaceToAOAptr )
	  tempToSpaceToAOAalloc();
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
    if (isValRep(theObj)) {
	
	/* THIS SHOULDN'T BE NECESSARY: should be handled at allocation time */
	if( ((ref(ValRep)) theObj)->HighBorder > LARGE_REP_SIZE){
	    /* A large val rep was detected in the IOA heap */
	    ref(Object) newObj; 
	    if (newObj = CopyObjectToLVRA(theObj)) {
		newObj->GCAttr = (long) theCell; /* Preserve the LVRA-Cycle */
		DEBUG_LVRA( Claim( isValRep(cast(ValRep)*theCell),
				  "NewCopyObject: isValRep(cast(ValRep)*theCell)" ));
		return newObj;
	    } else {
		/* CopyObjectToLVRA failed */
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
		/* Insert theCell in ToSpaceToAOA table. 
		 * Used as roots in mark-sweep if an AOA GC is invoked after IOAGc.
		 */
		if (theCell)
		  SaveToSpaceToAOAref(theCell);
		return newObj;
	    } else {
		return CopyObject(theObj);
	    }
	}
    }
#endif
    /* theObj is not copied to LVRA, not copied to AOA, or theObj is a stack object */
    return CopyObject(theObj);
}
