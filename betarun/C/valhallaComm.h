#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#ifndef VALHALLACOMM_H
#define VALHALLACOMM_H

#include "beta.h"

/* VALHALLAINIT
 * ============
 * 
 * Called e.g. from Initialize (initialize.c) when connection to valhalla 
 * should be setup. If valhalla is already running, valhallaID is expected
 * to contain the PID of the valhalla process is textual form. */

void valhallaInit ();



/* int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
 *                            long sig, long errorNumber)
 * ====================================================================
 *
 * Called in the following situations:
 *
 *  1. From exit.c immediately before the process terminates. In this case
 *     PC is set to 0 to signal that the process is dying. All other parameters
 *     are 0 as well. In this case valhalla will close the connection!
 * 
 *  2. From outpattern.c to inform that some error occurred.
 *
 *  3. From Attach.c, to inform that some BETA coroutine is about to be attached.
 *     In this case, PC is the BETA code address where control is being transferred,
 *     SP, curObj and sig are undefined, and errorNumber is RTS_ATTACH.
 *
 *  4. From Callback.c, to inform that some BETA external entry is about to be
 *     called. In this case,  PC is the BETA code address where control is being 
 *     transferred, SP, curObj and sig are undefined, and errorNumber is RTS_CBFA.
 *
 *  5. From Suspend.c, to inform that some BETA coroutine was suspended, and we are
 *     about to return to the calling component. In this case,  PC is the BETA code 
 *     address where control is being transferred, SP, curObj and sig are undefined, and
 *     errorNumber is RTS_SUSPEND.
 * 
 * In any case calls back to valhalla to inform that this process has stopped.
 *
 *
 * Possible return values:
 *     CONTINUE, TERMINATE. */

int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
			   long sig, long errorNumber);

/* Values of errorNumber in cases 3 and 4 of calling ValhallaOnProcessStop. */
#define  RTS_ATTACH 1
#define RTS_CBFA 2
#define RTS_SUSPEND 3

/* Return values from ValhallaOnProcessStop */

#define CONTINUE 0
#define TERMINATE 1

#endif VALHALLACOMM_H
#endif RTVALHALLA 
