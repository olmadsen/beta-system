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
 * In any case calls back to valhalla to inform that this process has stopped.
 *
 *
 * Possible return values:
 *     CONTINUE, TERMINATE. */

int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
			   long sig, long errorNumber);


/* Return values from ValhallaOnProcessStop */

#define CONTINUE 0
#define TERMINATE 1

#endif VALHALLACOMM_H
#endif RTVALHALLA 
