#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#ifndef VALHALLA_FINDCOMP_H
#define VALHALLA_FINDCOMP_H
#include "beta.h"

/* Possible values of the stacktype:
 *
 * These constants are replicated in ~debugger/processCommCodes.bet. */

#define CS_PROCESSORSTACK  1  /* component stack on processor stack. */
#define CS_ACTIVECOMPONENT 2  /* component is the currently active.  */
#define CS_STACKOBJ        3  /* component stack in stack object.    */
#define CS_NOSTACK         4  /* component has no stack.             */



/* forEachCallType
 * ===============
 *
 * Type of function parameter to scanComponentStack. Called for each
 * (returnAdr,returnObj) pair found on the stack scanned.
 *
 * If returnObj==0, this is a C return address. */


/* scanComponentStack
 * ==================
 *
 * Scans the stack part corresponding to the component.
 * curObj is the current object, and PC is the current PC - these
 * are used in case that comp is active component.
 * Calls forEach for each (returnAdr,returnObj) pair found on the stack 
 * scanned. 
 * Returns the stack type (one of the above CS_*
 */

int scanComponentStack (Component* comp, 
			Object *curObj,
			int pc,
			CellDisplayFunc forEach);

#endif /* VALHALLA_FINDCOMP_H */
#endif /* RTVALHALLA */
