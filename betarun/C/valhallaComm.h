#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#ifndef VALHALLACOMM_H
#define VALHALLACOMM_H

#include "beta.h"

/* Opcodes for communication between valhalla and debugged process.
 *
 * VOP_* constants are replicated in
 *
 *    ~debugger/processCommCodes.bet
 * 
 * A protocol description including parameters and return value is
 * found in processCommCodes.bet as well.
 */

#define VOP_SCANGROUPS          1 
#define VOP_KILL                2 
#define VOP_GETDATAMEM          3 
#define VOP_GETINSTRUCTIONMEM   4 
#define VOP_SETDATAMEM          5 
#define VOP_GETDATAWORDS        6 
#define VOP_CONTINUE            7
#define VOP_DOTINSERT           9
#define VOP_GETPROTOINFO       10
#define VOP_DOTDELETE          11
#define VOP_SCANSTACK          12
#define VOP_OBJADRCANONIFY     13
#define VOP_BETARUN            14
#define VOP_DATASTART_obsolete 15
#define VOP_MEMALLOC           16
#define VOP_MEMFREE            17
#define VOP_EXECUTEOBJECT      18
#define VOP_ADDGROUP           19
#define VOP_LOOKUP_SYM_OFF     20
#define VOP_LOOKUP_ADDRESS     21
#define VOP_MAIN_PHYSICAL      22
#define VOP_HEAPINFO           23
#define VOP_PROGRAM_PATH       24

#define VOP_EXT_HEAPINFO       40
#define VOP_SCANHEAPS          41
#define VOP_GETREFSTO          42
#define VOP_STOPPED            50


/* VALHALLAINIT
 * ============
 * 
 * Called e.g. from Initialize (initialize.c) when connection to valhalla 
 * should be setup. If valhalla is already running, valhallaID is expected
 * to contain the PID of the valhalla process is textual form. */

extern void valhallaInit (int debug_valhalla);
extern void valhalla_create_buffers(void);
extern void valhalla_init_sockets (int valhallaport);
extern void valhalla_await_connection(void);
extern void valhalla_writebytes (const char* buf, int bytes);
extern void valhalla_writeint(int val);
extern void valhalla_fill_buffer (void);
extern void valhalla_readbytes (char* buf, int bytes);
extern int  valhalla_readint(void);

/* int ValhallaOnProcessStop (long*  PC, long* SP, Object * curObj, 
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

int ValhallaOnProcessStop (long*  pc, long* sp, Object * curObj, 
			   long sig, long errorNumber);

/* Values of errorNumber in cases 3 and 4 of calling ValhallaOnProcessStop. */
#define  RTS_ATTACH 1
#define RTS_CBFA 2
#define RTS_SUSPEND 3

/* Return values from ValhallaOnProcessStop */

#define CONTINUE 0
#define TERMINATE 1

#endif /* VALHALLACOMM_H */
#endif /* RTVALHALLA */
