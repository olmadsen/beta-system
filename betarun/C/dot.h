/* dot.h
 * =====
 *
 * Created by Soren Brandt.
 *
 * DOT, the Debugger Object Table, is used to keep track of objects
 * without preventing these from being garbage collected. This means
 * that if an object contained in DOT is moved during a garbage collection,
 * the reference in DOT is updated by the garbage collector. If the DOT
 * contains references to objects becoming garbage, these references are
 * set to NULL by the garbage collector.
 *
 * DOT is planned to be used in the following situations:
 * 
 *    1. Valhalla. Valhalla needs to keep track of viewed objects as
 *       they move around, without preventing the objects from being
 *       garbage collected.
 * 
 *    2. Distribution. The distribution mechanism needs to keep track
 *       of proxy objects to make sure that different proxy objects
 *       in the same process actually refer to different remote objects.
 *       On the other hand, proxy objects should be garbage collected
 *       in case they are not used locally anymore.
 *
 *    3. Any situation where you need to keep track of a BETA object from C.
 *       The only limit is your imagination (and the runtime system :-). 
 * 
 * DOT is a two-level table. The lower level is the actual DOT table as seen 
 * by the garbage collector. The upper level hands out handles to the users 
 * of the DOT table to achieve that compaction of the DOT can be performed 
 * transparently to the users.
 * 
 * This header file defines an interface to the upper level DOT table. */



/* DOTonDelete
 * ===========
 * 
 * Type of procedure called when it is found that the object corresponding
 * to some handle has been deleted. This may happen during DOThandleLookup
 * or during DOThandlePerformCompaction. The parameter given is the handle
 * whose corresponding object was deleted. When a DOTonDelete method
 * has been called, the handle supplied as parameter may no longer be used 
 * as parameter to DOThandleLookup as a later DOThandleInsert may reuse the 
 * handle. */

typedef void (*DOTonDelete) (int);



/* DOTinit
 * =======
 * 
 * Should be called before attempting any operations on DOT. */

extern void DOTinit (void);



/* DOThandlePerformCompaction
 * ==========================
 *
 * If DOThandleInsert returns -1, the DOT table needs a compaction.
 * In that case DOThandlePerformCompaction should be called before 
 * calling DOThandleInsert again. If onDelete is not NULL, only elements
 * with onDelete as callback function may get thrown out of the table
 * during the compaction. */

extern void DOThandlePerformCompaction (DOTonDelete onDelete);


/* DOTscan
 * =======
 *
 * Scans over all elements in dot, calling a function for each element giving
 * the handle, the object address and the onDelete function for that object. */

typedef void (*DOTforEach) (int,int,DOTonDelete);
     /* handle,address,onDelete */
     
extern void DOTscan (DOTforEach foreach);


/* DOThandleInsert
 * =============== 
 *
 * Inserts an object in the DOT table and returns a handle to be used when
 * looking up the object. The function parameter onDelete is called when
 * it is found that the object has become garbage and thus no longer
 * exists. When onDelete has been called, it is no longer allowed to lookup
 * the handle as it may have been reused.
 *
 * If -1 is returned, DOThandlePerformCompaction should be called before
 * calling DOThandleInsert again. This can be prevented by setting 
 * allowCompaction to FALSE. */
   
extern int DOThandleInsert (long ObjRef, DOTonDelete onDelete, 
			    int allowCompaction);

/* DOThandleDelete
 * ===============
 *
 * Deletes an object in the DOT table. The callback function associated with
 * the deleted handle will be called as usual. */

extern void DOThandleDelete (int handle);

/* DOThandleLookup
 * ===============
 *
 * Returns the actual object reference given a handle earlier returned by 
 * DOThandleInsert. If NONE is returned, the object no longer exists, and 
 * the corresponding onDelete function has been called. */

extern long DOThandleLookup (int handle);

/* ProcessDOT
 * ==========
 *
 * Process References in DOT.
 * Used by IOAGc().
 */

extern void ProcessDOT(void);
