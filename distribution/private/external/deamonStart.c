/* 
 * This deamon skeleton is taken from 
 *
 *   W. Richard Stevens: UNIX network programming, Prentice Hall 1990
 *
 */


#include <stdio.h>
#include <signal.h>
#include <sys/param.h>
#include <errno.h>

/* When defined, enables environment variable to prevent deamonStart */
#define DEAMONSTART_PREVENTABLE

#ifdef hpux
#define _USE_SYSTEMV 1
#else
  #if (defined(sun4s) || defined(linux))
  #define _USE_SYSTEMV 1
  #else
    #ifdef SIGTSTP
    #define _USE_BSD 1
    #else
      #define _USE_SYSTEMV 1
    #endif
  #endif
#endif

#ifdef _USE_BSD
#include <sys/file.h>
#include <sys/ioctl.h>

/*
 * This is a 4.3BSD SIGCLD signal handler that can be used by a server
 * that's not interested in its child's exit status, but needs to wait for 
 * them, to avoid clogging up the system with zombies.
 *
 * Beware that the calling process may get an interrupted system call when we
 * return, so they had better handle that.
 */

#include <sys/wait.h>

int sig_child ()
{ int pid;
  union wait status;

  while ((pid = wait3 ((int *) &status, WNOHANG, (int *) 0)) > 0)
    ;
}
#endif


/* 
 * detach a deamon process from login session context
 * returns 1 if executed normally, 0 if prevented
 */

long
deamonStart (int ignsigcld)
/* ignsigcld <=> handle SIGCLDs so zombies don't clog */
{
  int childpid, fd;

#ifdef DEAMONSTART_PREVENTABLE
  if (getenv("PREVENT_DEAMONSTART")) {
    fprintf(stderr,"deamonStart prevented\n");
    return 0;
  }
#endif
  
  /*
   * If we were started by init (process 1) from the /etc/inittab file
   * there's no need to detach.
   * This test is unreliable due to an unavoidable ambiguity if the
   * process is started by some other process and orphaned (i.e. if
   * the parent process terminates before we are started.)
   */

  if (getppid () == 1)
    goto out;

  /* 
   * Ignore the terminal stop signals (BSD)
   */

#ifdef SIGTTOU
  signal (SIGTTOU, SIG_IGN);
#endif
#ifdef SIGTTIN
  signal (SIGTTIN, SIG_IGN);
#endif
#ifdef SIGTSTP
  signal (SIGTSTP, SIG_IGN);
#endif


  /* If we were not started in the backgroud, fork and let the parent exit.
   * This also guarantees the first child is not a process group leader.
   */

  if ((childpid = fork()) < 0)
    fprintf (stderr, "can't fork first child\n");
  else if (childpid > 0)
    exit (0); /* parent */

  /* 
   * First child process.
   *
   * Disassociate from controlling terminal and process group.
   * Ensure the process can't reacquire a new controlling terminal.
   */
  
#ifdef _USE_BSD
  if (setpgrp (0, getpid()) == -1)
    fprintf (stderr, "can't change process group\n");

  if ((fd = open("/dev/tty", O_RDWR)) >= 0) {
    ioctl (fd, TIOCNOTTY, (char *) NULL); /* lose controlling tty */
    close (fd);
  }


#else /* System V */
  if (setpgrp () == -1)
      fprintf (stderr, "can't change process group");
  
  signal (SIGHUP, SIG_IGN);   /* immune from pgrp leader death */

  if ((childpid = fork ()) < 0)
    fprintf (stderr, "can't fork second child\n");
  else if (childpid > 0)
    exit (0);  /* first child */

  /* second child */
#endif


out:
  /* 
   * Close any open file descriptors apart from stdout and stderror as they
   * will be redirected by the shell itself.
   */

  close (0);
  for (fd = 3; fd < NOFILE; fd++)
    close (fd);

  errno = 0;    /* Was probably set to EBADF from a close */

  /* Move the current directory to root, to make sure we aren't on a
   * mounted filesystem.
   */

  chdir ("/");

  /*
   * Clear any inherited file mode creation mask.
   */

  umask (0);

  /* See if the caller isn't interested in the exit status of its children,
   * and doesn't want to have them become zombies and clog up the system.
   * With System V all we need do is ignore the signal.
   * With BSD, however, we have to catch each signal and execute the wait3 () 
   * system call.
   */

  if (ignsigcld) {
#ifdef _USE_BSD
    int sig_child ();
    
    signal (SIGCLD, sig_child);  /* BSD */

#else
    signal (SIGCLD, SIG_IGN);    /* System V */
#endif
  }

  return 1;
}
