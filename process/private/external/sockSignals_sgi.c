/* ------------------------- FILE sockSignals.c ------------------------- */

/*
 * COPYRIGHT
 *       Copyright Mjolner Informatics, 1994
 *       All rights reserved.
 */


/*******************
 *                 *
 * Common includes *
 *                 *
 *******************/


#include <stdlib.h>		/* to see getenv() */
#include <signal.h>		/* to see signal() */


/***************************
 *                         *
 * Architecture dependance *
 *                         *
 ***************************/


#include "arch_sgi.h"

#if defined(A_HP) || defined(A_SUN4S)
#  define RESIGNAL(sig,fp) signal(sig,fp)
#else
#  define RESIGNAL(sig,fp)
#endif


/********************************
 *                              *
 * Debug & cond.compile defines *
 *                              *
 ********************************/


/* A readable and not too long filespec, for debug(gish) output */
#define FILE_ID "process/v1.3.9.1/.../sockSignals.c"

/* Enable {in,de}crementing counter by means of the USR{1,2} signals */
#define SUPPORT_ASYNCHLEVEL

/* #define DO_ECHO_ERROR */
/* #define MAKE_CTRL_C_A_KILLER */
/* #define DO_SHOW_SIGIO */
/* #define DO_SHOW_SIGALRM */

/* BEFORE include "echoError.h": redirect error output to stdout */
#define STDERR stdout
#include "echoError.h"

/* Make sure 'broken pipe' signal doesn't kill us */
#define USE_SIGPIPE_HANDLER


/********************************************************************
 *                                                                  *
 * Signal handling functions                                        *
 *                                                                  *
 ********************************************************************/


/* function 'catchSIGUSR' installs handlers for asynchronous, 
 * process-external control of the counter returned by 
 * 'asynchLevel()'. This can be used to control debug-output
 * level at run-time, etc.
 *
 * args
 *   none
 *
 * return value
 *   none
 *
 *
 * The associated function 'asynchLevel' has the following
 * interface:
 *
 * args
 *   none
 *
 * return value
 *   level, reflecting received USR1 (level++) and USR2 (level--) signals
 */
#ifdef SUPPORT_ASYNCHLEVEL

  static int SIGUSR_installed=0;
  int asynch_level=0;

  int asynchLevel(void)
  {
    return asynch_level;
  }

  static void onSigUsr1(SIGNALPARM)
  {
    signal(SIGUSR1,onSigUsr1);
    asynch_level++;
  }

  static void onSigUsr2(SIGNALPARM)
  {
    signal(SIGUSR2,onSigUsr2);
    if (asynch_level)
      asynch_level--;
  }

  static void catchSIGUSR(void)
  {
    if (!SIGUSR_installed) {
      SIGUSR_installed=1;
      signal(SIGUSR1,onSigUsr1);
      signal(SIGUSR2,onSigUsr2);
    }
  }

#  define CATCHSIGUSR catchSIGUSR()
#else

  int asynchLevel(void)
  {
    return 0;
  }

#  define CATCHSIGUSR
#endif


/* function 'catchSIGINT' provokes a segmentation fault, when
 * user presses ^C. This may be useful, for discovering where
 * the program execution is spending its time. To use it: #define
 * 'MAKE_CTRL_C_A_KILLER'. Purely a hack, only for debugging,
 * but handy!
 *
 * args
 *   none
 *
 * return value
 *   none
 */
#ifdef MAKE_CTRL_C_A_KILLER

  static int SIGINT_installed=0;

  static void onSigInt(SIGNALPARM)
  {
    char *p=0;
    *p=87;			/* as promised - a killer */
  }
  
  static void catchSIGINT(void)
  {
    if (!SIGINT_installed) {
      SIGINT_installed=1;
      signal(SIGINT,onSigInt);
    }
  }

#  define CATCHSIGINT catchSIGINT()
#else
#  define CATCHSIGINT
#endif


/* function 'catchSIGALRM' prints a message, whenever the SIGALRM signal
 * is raised. Used temporarily in May 1993 to see, why on earth an
 * OODB-client (w/hypermedia) seems to get this signal without asking for it.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
#ifdef SHOW_SIGALRM
  static void onSigAlrm(SIGNALPARM)
  {
    RESIGNAL(SIGALRM,onSigAlrm);
    puts("\t<<SIGALRM raised>>");
  }

  static void catchSIGALRM(void)
  {
    signal(SIGALRM,onSigAlrm);
  }

#  define CATCHSIGALRM catchSIGALRM()
#else
#  define CATCHSIGALRM
#endif


/* function 'catchSIGIO' checks to see if a SIGIO handler is installed
 * (by cWaitForIO). If not, such one gets installed, and the OS is asked
 * to generate SIGIO's.
 *
 * args
 *   none
 *
 * return value
 *   none
 *
 * IMPORTANT NOTE: Using 'catchSIGIO' will uninstall any previously
 * installed SIGIO handler.
 *
 */
#ifdef USE_SIGIO_HANDLER

  static void onSigIO(SIGNALPARM)
  {
    RESIGNAL(SIGIO,onSigIO);
#   ifdef SHOW_SIGIO
      puts("<<SIGIO>>");
#   endif
  }

  static void catchSIGIO(void)
  {
    static int HandlerInstalled=0;

    if (!HandlerInstalled) {
      signal(SIGIO,onSigIO);
      HandlerInstalled=1;
    }
  }

#  define CATCHSIGIO catchSIGIO()
#else
#  define CATCHSIGIO
#endif 


/* function 'catchSIGPIPE' installs a SIGPIPE handler, to cope with 
 * signals generated in response to writes on dead sockets. (And
 * perhaps other pathologic circumstances about sockets, for which
 * we don't want to get killed!)
 *
 * args
 *   none
 *
 * return value
 *   none
 *
 * IMPORTANT NOTE: Using 'catchSIGPIPE' will uninstall any previously
 * installed SIGPIPE handler.
 *
 */
#ifdef USE_SIGPIPE_HANDLER

  static void onSigPipe(SIGNALPARM)
  {
    RESIGNAL(SIGPIPE,onSigPipe);
#   ifdef SHOW_SIGPIPE
      puts("<<SIGPIPE>>");
#   endif
  }

  void catch_SIGPIPE()
  {
    signal(SIGPIPE,onSigPipe);
  }

#  define CATCHSIGPIPE catch_SIGPIPE()
#else
#  define CATCHSIGPIPE
#endif 


/********************************************************************
 *                                                                  *
 * Initialization of this module                                    *
 *                                                                  *
 ********************************************************************/


/* function 'initSockSignals' initializes signal handlers etc.
 * in accordance with the on/off defines ().
 * It is idempotent.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
void initSockSignals(void)
{
  static initialized=0;

  if (!initialized) {
    initialized = 1;

    /* These macros initialize the requested handlers */
    CATCHSIGUSR;
    CATCHSIGINT;
    CATCHSIGALRM;
    CATCHSIGIO;
    CATCHSIGPIPE;

#ifdef SUPPORT_ASYNCHLEVEL

    /* Initialize asynch_level from environment */
    {
      char *envvar = getenv("INITIAL_ASYNCH_LEVEL");

      if (envvar) {		/* INITIAL_ASYNCH_LEVEL is defined */
	asynch_level = atoi(envvar);
      }
    }
    
#endif
    
  }
}


/* ------------------------- END sockSignals.c ------------------------- */
