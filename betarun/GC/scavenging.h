/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: scavenging.h,v $, rel: %R%, date: $Date: 1992-08-27 16:01:23 $, SID: $Revision: 1.3 $
 * by Lars Bak.
 */
extern ref(Object) NewCopyObject();

/* Traverse the StackArea [low..high] and Process all references within it. */
void ProcessStackPart();

extern void ProcessStack();

/*
 * IOAGc:
 *  Called from PerformGC in the assembly part of the runtime system.
 *  Make a scavenging garbage collection on IOA.
 */
extern void IOAGc();

/*
 * ProcessReference:
 *  Takes as input a reference to a cell residing outside IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 *  TIPS: USE theObj instead of newObj and inline GetDistanceToEnc....
 */
extern void ProcessReference();

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverse the object and process all the references in it.    
 */
extern void ProcessObject();

#ifdef AO_Area
/*
 * ProcessAOAReference:
 *  Takes as input a reference to a cell residing outside IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 */
extern void ProcessAOAReference();

/*
 * ProcessAOAObject:
 *  Takes as input a reference to an object residing in the AOA.
 *  It traverse the object and process all the references in it.    
 */
extern void ProcessAOAObject();
#endif

/*
 * CompleteScavenging:
 *  Process all the objects in the ToSpace, which has not been handled yet.
 *  The reason is to ensure the locallity of related objects, to avoid
 *  unneseccary swapping. 
 */

extern void CompleteScavenging();

/*
 * GetDistanceToEnclosingObject:
 *  Find the offset (negative) to the most inclosing object e.g.
 *  the offset to the autonomous object in which theObj reside.  
 */
   
extern int GetDistanceToEnclosingObject();

/* Safe way to save ToSpaceToAOA references */
#define SaveToSpaceToAOAref(cell)				\
  ((ToSpaceTop == ToSpaceToAOAptr)?tempToSpaceToAOAalloc():0,	\
   *--ToSpaceToAOAptr = (long) (cell))

extern void tempToSpaceToAOAalloc();
extern void tempToSpaceToAOAfree();
     
#ifdef RTDEBUG
extern void IOACheck();

extern void IOACheckObject();

extern void IOACheckReference();

#endif
