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

typedef void (*forEachCallType) (int,int);
/* int returnAdr;  Return address 
 * int returnObj;  Current object corresponding to returnAdr.
 *                 If returnObj==0, this is a C return address. */



/* scanComponentStack
 * ==================
 *
 * Scans the stack part corresponding to the component.
 * PC is the current PC.
 * Calls forEach for each (returnAdr,returnObj) pair found on the stack 
 * scanned. 
 * Returns the stack type (one of the above CS_*
 */

int scanComponentStack (struct Component* comp, 
			int PC,
			forEachCallType forEach);

#endif /* VALHALLA_FINDCOMP_H */
#endif /* RTVALHALLA */
