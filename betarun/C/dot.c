/* dot.c
 * =====
 *
 * Created by Soren Brandt.
 *
 * As seen from the garbage collector, DOT consists of the following variables:
 *
 *    1. DOT: A pointer to a list of object references.
 *    2. DOTTop: Points out first element in DOT list not in the table.
 *    3. DOTSize:  Current number of elements in DOT. When an element is
 *       deleted by the garbage collector, DOTsize is decremented.
 *
 * Internally the following variables are used.
 *
 *    4. DOTLimit: Max. allowed value of DOTTop.
 *    5. firstFreeHandle: Identifies first handle in handletable freelist.
 *    6. nextHandle: next handle to allocate in case freelist is empty.
 *    7. handleTable: Mapping from handles to indices in the real DOT.
 *    8. onDeleteTable: Function pointers to call when an element gets deleted
 *       from the table.
 *    9. handleTableLimit: Max size of handleTable and onDeleteTable before 
 *       extension.
 */

#include <stdio.h>
#include "dot.h"
#ifdef linux
/* #include "/usr/local/lib/beta/betarun/v2.6/linux/C/beta.h" */
#else
#include "beta.h"  /* Declarations of DOT variables in data.h. */
#endif

#define DOTinitialSize 50  /* Initial size of DOT. */
#define DOTcompactLimit 25 /* Free space in DOT required to do a compaction. */

#define DOTlength (DOTLimit - DOT)
#define DOTneedsCompaction (((DOTLimit - DOT) - DOTSize) >= DOTcompactLimit)

/* handleTable
 * ==========
 * 
 * Mapping from handles as given to the users of DOT to the indices in the 
 * actual DOT table.
 * 
 * firstFreeHandle is -1 or points to the first unused index in handleTable.
 * Given an index freeInx to the nextHandle element in the freeList, the 
 * actual index in handleTable is computed by:
 * 
 *        handleTableIndex = -2-freeInx
 *    <=> freeInx = -2-handleTableIndex
 * 
 * It follows that a nextHandleIndex value of -1 means that there is
 * no next element as the corresponding handleTableIndex is -1.
 * 
 * The above coding is made to achieve that elements in the table
 * corresponding to real DOT elements are greater or equal to zero.
 * That is, if handleTable[h] = DOTinx >= 0, then DOTinx can be used
 * as index in the actual DOT to fetch the object reference. Otherwise
 * the element has at some point been deleted from the C DOT table.
 * 
 * All indices in handleTable greater of equal to next are unused. */

static int firstFreeHandle;
static int nextHandle;

/* Mapping from handles to indices in the real DOT: */
static int* handleTable;

/* Procedures to call when a handle is deleted: */
static DOTonDelete* onDeleteTable; 
   
/* Max size of handleTable and DOTonDelete before extension: */
static int handleTableLimit;


/* DOTscan
 * ======= */

void DOTscan (DOTforEach foreach)
{ int i;
  for (i=0;i<nextHandle;i++)
    if (handleTable[i]>=0) 
      foreach (i,DOT[handleTable[i]],onDeleteTable[i]);
}


/* privDOThandleDelete
 * ===================
 *
 * Private method called when a handle gets deleted. */
   
static void privDOThandleDelete (int handle)
{
  /* Inform user that the handle is being deleted: */
  onDeleteTable[handle] (handle);
  onDeleteTable[handle] = 0;

  handleTable[handle] = firstFreeHandle;
  firstFreeHandle = -2-handle;
}

void DOThandleDelete (int handle)
{
  DOT[handleTable[handle]] = 0;
  privDOThandleDelete (handle);
}



/* DOThandlePerformCompaction
 * ==========================
 *
 * Should be called by when DOThandleInsert returns -1. */

static int getHandle (int DOTindex)
{ int i;
  for (i=0;i<handleTableLimit;i++) {
    if (handleTable[i]==DOTindex)
      return i;
  }
  return -1;
}

void DOThandlePerformCompaction (DOTonDelete onDelete)
{ int *newIndices = (int *) malloc (DOTlength*sizeof(int));
  int i;

  { int limit = DOTlength;
    int cur = 0;
    int nextFree = 0;

    while (cur < limit) {
      if (DOT[cur]) 
	{ 
	  DOT[nextFree] = DOT[cur];
	  newIndices[cur] = nextFree;
	  nextFree++;
	} 
      else 
	if (onDelete) 
	  { 
	    int handle = getHandle(cur);
	    if ((handle!=-1) && (onDeleteTable[handle]!=onDelete)) 
	      { 
		DOT[nextFree] = DOT[cur];
		newIndices[cur] = nextFree;
		nextFree++;
	      } 
	    else 
	      {
		newIndices[cur] = -1;
	      }
	  } 
	else 
	  {
	    newIndices[cur] = -1;
	  }
      
      
      cur++;
    }
    
    DOTSize = nextFree;
    DOTTop = &(DOT[nextFree]);
  }

  for (i = 0; i < nextHandle; i++) 
    if (handleTable[i] >= 0) {
      handleTable[i] = newIndices[handleTable[i]];
      if (handleTable[i] == -1) privDOThandleDelete (i);
    }

  free (newIndices);
}


/* DOTinsert
 * =========
 *
 * Private method called by DOThandleInsert. 
 *
 * Inserts an object reference in DOT and returns the index of the
 * newly inserted reference.
 * 
 * Returns -1 if insertion failed and DOT should be compacted.
 * In that case the compaction should be performed, and DOTinsert
 * called again.
 * 
 * If DOTlimit has been reached and compaction would do no good, 
 * DOT is extended without further notice. */

static int DOTinsert (long objRef, int allowCompaction)
{ int inx;

  if (DOTTop == DOTLimit) {
    if (DOTneedsCompaction && allowCompaction)
      return -1;
    else {
      /* Extend DOT */
      int oldSize = (DOTLimit - DOT);
      int newSize = oldSize*2;
      DOT = (long *) realloc (DOT, newSize*sizeof(long));
      DOTTop = DOT + oldSize;
      DOTLimit = DOT + newSize;
    }
  }

  inx = (DOTTop - DOT);

  DOTTop++; DOTSize++;

  DOT[inx] = objRef;
  
  return inx;
}



/* DOTinit
 * =======
 * 
 * Should be called before attempting any operations on DOT. */

void DOTinit ()
{
  if (!DOT) {

    /* Initialize DOT */
    DOT = (long *) malloc (DOTinitialSize*sizeof(long));
    DOTTop = DOT;
    
    DOTSize = 0;
    DOTLimit = DOT + DOTinitialSize;

    /* Initialize handle "handling" */
    firstFreeHandle = -1; nextHandle = 0;

    handleTableLimit = DOTinitialSize;
    handleTable = (int*) malloc (DOTinitialSize*sizeof(int));
    onDeleteTable = (DOTonDelete*) malloc (DOTinitialSize*sizeof(DOTonDelete));
  }
}



/* DOThandleInsert
 * =============== 
 *
 * Insert an object in the DOT table and returns a handle to be used when
 * looking up the object. The function parameter onDelete is called when
 * it is found that the object has become garbage and thus no longer
 * exists. When onDelete has been called, it is no longer allowed to lookup
 * the handle as it may be reused.
 *
 * If -1 is returned, DOThandlePerformCompaction should be called before
 * calling DOThandleInsert again. */
   
int DOThandleInsert (long ObjRef, DOTonDelete onDelete, int allowCompaction)
{ int handle, DOTinx;
  
  if ((DOTinx = DOTinsert (ObjRef,allowCompaction)) == -1)
    return -1;
  
  if (firstFreeHandle == -1) {
    
    /* Nothing in freeList. */
    
    if (nextHandle >= handleTableLimit) {
      handleTable = (int*) realloc (handleTable, 2*handleTableLimit*sizeof(int));
      onDeleteTable = (DOTonDelete*) 
	realloc (onDeleteTable,2*handleTableLimit*sizeof(DOTonDelete));
      handleTableLimit = 2*handleTableLimit;
    }
    
    handle = nextHandle;
    nextHandle++;
           
  } else {
            
    handle = -2-firstFreeHandle;
    firstFreeHandle = handleTable[handle];
       
  }

  handleTable[handle] = DOTinx;
  onDeleteTable[handle] = onDelete;
        
  return handle;
}
   
 

/* DOThandleLookup
 * ===============
 *
 * Returns the actual object reference given a handle earlier returned by 
 * DOThandleInsert. If NONE is returned, the object no longer exists, and 
 * the corresponding onDelete function has been called. */

long DOThandleLookup (int handle)
{ long objAdr;
  
  objAdr = DOT[handleTable[handle]];
  if (objAdr == 0)
    privDOThandleDelete (handle);

  return objAdr;
}



