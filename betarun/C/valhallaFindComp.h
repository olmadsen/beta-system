#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#ifndef VALHALLA_FINDCOMP_H
#define VALHALLA_FINDCOMP_H
#include "beta.h"

/* Possible values of the ComponentStack.stacktype field:
 *
 * These constants are replicated in ~debugger/processCommCodes.bet. */

#define CS_PROCESSORSTACK  1  /* component stack on processor stack. */
#define CS_ACTIVECOMPONENT 2  /* component is the currently active.  */
#define CS_STACKOBJ        3  /* component stack in stack object.    */
#define CS_NOSTACK         4  /* component has no stack.             */


struct ComponentStack{
  struct Component *comp; /* The component */
  int stacktype;          /* One of CS_*   */
  int returnAdr;          /* The address to return to when this component 
			   * starts running the next time. */
  union {
    struct { /* if stacktype==CS_PROCESSORSTACK or CS_ACTIVECOMPONENT: */
#ifdef sparc
      /* FirstAR is the largest address that is not part of the stack of comp.
       * lastAR is the least RegWin that *is* part of the stack, i.e. the 
       * StackEnd for this component stack. Notice that the stack grows 
       * downwards. 
       * I.e. to scan the stack, scan from (and including) lastAR to firstAR.
       * activeCBF is the active callback frame of this component.
       */
      struct RegWin* firstAR;
      struct RegWin* lastAR;
      struct RegWin* activeCBF;
#else
      int dummy;
#endif /* sparc */
    } if_onstack;
    /* if stacktype==CS_STACKOBJ: */
    struct StackObject *stackObj; 
  } info;
};






/* findComponentStack
 * ==================
 *
 * Fills in the structure compStack. compStack->comp should point to a 
 * component object. PC is expected to be the current BETA PC, and is
 * used to set compStack->returnAdr in case compStack->comp is the
 * active component.
 *
 * The implementation of findComponentStack assumes that it has been called
 * via some other runtime routine that correctly set up the StackEnd
 * variable to point to the top of the current BETA stack. This is
 * e.g. the case with BetaError or BetaSignalHandler.
 */

void findComponentStack (struct ComponentStack* compStack, int PC);



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
 * Scans the stack compStack previously filled out by "findComponentStack".
 * Calls forEarch for each (returnAdr,returnObj) pair found on the stack 
 * scanned. */

void scanComponentStack (struct ComponentStack* compStack, 
			 forEachCallType forEach);

#endif /* VALHALLA_FINDCOMP_H */
#endif /* RTVALHALLA */
