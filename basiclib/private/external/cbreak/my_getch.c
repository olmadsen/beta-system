/*
 * Copyright 1993 by R. Vankemmel
 * 
 * Permission to use, copy, modify and distribute this software and the
 * supporting documentation without fee is hereby granted, provided that :
 * 
 * 1 : Both the above copyright notice and this permission notice
 *     appear in all copies of both the software and the supporting
 *     documentation.
 * 2 : You don't make a profit out of it.
 * 3 : You properly credit the author of this software when it is 
 *     included in any other package.
 * 
 * THE AUTHORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL THEY BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 */
/* =========================RCS info================================== */
/* $Author: beta $ */
/* $Revision: 1.1.1.1 $ */
/* $Source: /a/home/alhambra02/beta/.CVSHOME/beta_project/basiclib/private/external/cbreak/my_getch.c,v $ */
/* $Date: 1995-09-26 10:31:47 $ */
/* $State: Exp $ */
/* $Locker:  $ */
/* =================================================================== */
/* 
 * file:   my_getch.c 
 *
 * routine: my_raw() 
 * purpose: the routine raw() allows to put a terminal into a
 *  raw state so that we are able to do unbuffered input from the keyboard.
 *  Hence we can read one char without the trailing CR/LF. 
 *
 * routine: my_getch() 
 * purpose: this routine reads one character from the
 *  keyboard while being in raw mode. This enables to read a char without
 *  needing a CR/LF. The routine performs detection of control characters
 *  (especially EOF, [^D]) and prevents stdin to be closed. The returned
 *  status is the same as for getc(). In case no raw mode is available, the
 *  character is read by using the my_gets() routine needing however a CR ! 
 *
 *
 * author: R. Vankemmel date  : 8/7/93 
 *
 * Note : I experimented first with raw() modes which are not doing signal
 * processing. So, we must do it by ourself. However, raw() has the
 * disadvantage that it also stops any i/o processing hence any data in the
 * output buffer (e.g. the question to answer with y/n) is being flushed to
 * /dev/null !! Therefore I switched to cbreak modes with signal catching
 * with signal(). for doing a controlled exit from this modes. 
 *
 * syntax: 
 *    void my_raw(int set) 
 *    Input:  set = TRUE (1) : set terminal into raw state; 
 *            set = FALSE (0): reset terminal into no raw state; 
 *    Output: ---- 
 *
 *    int my_getch() 
 *    Input:  ----- 
 *    Output: -) int value of input character. 
 *            -) EOF on ^D or error. 
 *
 */
/* ===================================================================== */
#include <stdio.h>		/* IO functions    */
#include <string.h>             /* strlen functions*/
#include <errno.h>		/* file errors     */
#include <signal.h>		/* emulate signals */
#include <setjmp.h>		/* apply a jump after suspends */
#include "sysdefs.h"		/* general library header */

#ifdef HAS_POSIX                /* try first the POSIX style (easy) */
#  include <termios.h>
#elif defined(HAS_IOCTL)
#  define  FD_IN   0		/* file descriptor of stdin (see stdio.h) */
#  ifdef HAS_SGTTY		/* BSD systems, AMIGA, MINIX */
#    include <sgtty.h>		/* general terminal interface */
#  elif defined(HAS_TERMIOS)	/* SYSV (and some BSD) systems */
#    include <sys/termio.h>	/* terminal interface          */
#  else				/* generate an error           */
#    include "PROBLEM: no termios.h nor sgtty.h file ?????"
#  endif
#elif defined(HAS_CURSES)	/* uses curses lib */
#   include <curses.h>
#elif THINK_C			/* Think-C 4 or -5 on MAC        */
#   include <console.h>
#elif defined(HAS_SSR)          /* VAX-VMS SSR library          */
#   include "vms_getkey.h"
#else				/* no ioctl() or curses lib      */
#  define USE_MY_GETS		/* use my_gets for reading          */
extern char    *my_gets();
#endif

/* this might be defined already */
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

/* =================================================================== */
#if !(defined(USE_MY_GETS) || defined(HAS_SSR))	 
/* compile only when ioctl / curses available */
void            set_signals();
void            reset_signals();
void            signal_handler();

static int      is_in_noraw = TRUE;	/* assumption at first call !!! */
jmp_buf         return_env;	        /* jump environment for signals */

/* ANSI C , CONVEX C-source  or DEC ucode C compiler are more or less ANSI */
#if(defined(__STDC__)||defined(CONVEX)||defined(DECRISC)||defined(DECALPHA))
# define _ASSUME_STDC_
#endif

/* keep previous signals if called from */
/* a program with other signal settings */
/* Note: ANSI C (strict) does not allow for typedef signaltyp void 
 * hence you cannot us signaltyp here. */
#ifdef _ASSUME_STDC_
 void (*Intr) (), (*Quit) (), (*Term) (), (*Tstp) (), (*Cont) ();
#else
 int  (*Intr) (), (*Quit) (), (*Term) (), (*Tstp) (), (*Cont) ();
#endif


#ifdef HAS_POSIX
struct termios  old_term, new_term;     /* struct's must be global:     */
#elif defined(HAS_IOCTL)
#  ifdef HAS_TERMIOS
struct termio   old_term, new_term;	/* struct's must be global:     */
#  elif defined(HAS_SGTTY)	        /* we must be able to pick up   */
struct sgttyb   old_term, new_term;	/* the settings after signal-   */
#    ifdef CONVEX		/* convex defines them as       */
#      undef  TCGETA		/* TIOCGETA and TIOCSETAW       */
#      undef  TCSETAW		/* therefore undef needed !!!   */
#    endif
#    ifdef DECRISC              /* DEC Risc ucode C comp. set both     */
#      undef  TCGETA            /* SYSV and BSD definitions in ioctl.h */
#      undef  TCSETAW           /* so undef them too.                  */
#    endif
#    define TCGETA  TIOCGETP	/* handling (scope of struct's) */
#    define TCSETAW TIOCSETP	/* define TC* to be BSD functions */
#  endif
#endif

void 
my_raw(int set)
{
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifdef HAS_POSIX   /* try first with POSIX routines */
        if (set && is_in_noraw) {
		/* get the original settings and save them */
		tcgetattr(fileno(stdin), &old_term);
		new_term = old_term;

		/* change terminal settings */
		new_term.c_lflag &= ~(ICANON | ECHO); /* in raw mode */
		new_term.c_cc[VMIN] = '\01';	/* read one char a time */
		new_term.c_cc[VTIME] = '\00';	/* wait time for reading */

		/* set terminal in new state */
		tcsetattr(fileno(stdin), TCSANOW, &new_term);
		is_in_noraw = FALSE;
	} else if (!(set || is_in_noraw)) {
		/* restore old terminal setting again */
		tcsetattr(fileno(stdin), TCSANOW, &old_term);
		is_in_noraw = TRUE;
	}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#elif defined(HAS_IOCTL)
	if (set && is_in_noraw) {
		/* get the original settings first, save */
		ioctl(FD_IN, TCGETA, &old_term);	/* get old settings   */
		ioctl(FD_IN, TCGETA, &new_term);	/* again for changing */

		/* now change the new terminal settings */
#  ifdef HAS_SGTTY
		new_term.sg_flags &= ~(CRMOD | ECHO); /* switch of echo and */
		                                      /* CR --> CR-LF mapping */
		new_term.sg_flags |= CBREAK;	      /* set in cbreak mode */
#  elif defined(HAS_TERMIOS)
		new_term.c_lflag &= ~(ICANON | ECHO); /* in raw mode        */
		new_term.c_cc[VMIN] = '\01';	/* read one char a time */
		new_term.c_cc[VTIME] = '\00';	/* wait time for reading */
#  endif

		/* set the new terminal mode */
		ioctl(FD_IN, TCSETAW, &new_term);
		is_in_noraw = FALSE;
	} else if (!(set || is_in_noraw)) {
		/* restore old terminal setting again */
		ioctl(FD_IN, TCSETAW, &old_term);
		is_in_noraw = TRUE;
	}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#elif defined(HAS_CURSES)
	if (set && is_in_noraw) {
		/* terminal to be putted in raw state */
		initscr();	/* curses needs this ; call's also 
				 * def_shell_mode() */
		savetty();	/* save current tty flags */
		cbreak();
		noecho();
		is_in_noraw = FALSE;
	} else if (!(set || is_in_noraw)) {
		/* terminal to be set in noraw state  */
		nocbreak();
		echo();
		resetty();	/* restore old tty flags */
#ifdef SYSV
		reset_shell_mode();	/* now here's a trick; endwin() does
					 * a clear of the window which we 
					 * don't want therefore restore 
					 * shell mode terminal settings 
					 * without clearing.              */
#endif
		is_in_noraw = TRUE;
	}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#elif defined(THINK_C)		/* don't HAS_CURSES but has csetmode
				 * (Think-C) */
	if (set && is_in_noraw) {
		csetmode(C_BREAK, stdin);
		is_in_noraw = FALSE;
	} else if (!(set || is_in_noraw)) {
		csetmode(C_ECHO, stdin);
		is_in_noraw = TRUE;
	}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#endif				/* HAS_IOCTL - THINK_C - HAS_CURSES */

}
#endif				/* end if ! (USE_MY_GETS || HAS_SSR) */

/* ================================================================ */
int 
my_getch()
{
	/* read a char in raw mode                               */
	/* read one char from the screen, trap any eof entered ! */
	/* If the user enters EOF then reopen stdin              */

	int input;

#ifdef USE_MY_GETS		/* no  raw mode available */
	char            buffer[256];
	char           *bufptr;
	int             begin;

	bufptr = my_gets(buffer, begin);
	if (bufptr != (char *) NULL) {
		/* take only one char */
		input = (int) buffer[begin];
	} else if (begin == -1)
		input = EOF;
	else
		input = atoi('\0');	/* on CR/LF */

#elif defined(HAS_SSR)          /* VAX_VMS SSR routines */
        char  buffer[10];

        /* call the external routine form McCracken */
	input = (int) getkey();
        
#else
	/* we have a raw mode available from ioctl() or curses */

	/* we cannot allow to exit while in raw mode: signal catching */
	set_signals();

	/* first get the char in the selected mode */
	if (setjmp(return_env)) {
		/* we return here after resuming a suspended session */
		printf("You had to enter something here: <y,n> ");
		fflush(stdout);
		my_raw(1);
		input = getchar();
		my_raw(0);
	} else {
		/* normal case */
		my_raw(1);
		input = getchar();
		my_raw(0);
	}

	/* reset signals */
	reset_signals();

#endif

#ifndef HAS_SSR      /* System service routines do not know about stdin.. ; */
		     /* it is sys level */

	/* NOTE !! : getc() return EOF (-1) on ^D          */
	if (input == EOF) {
		/* 1) the user entered EOF (^D) in no_raw mode or */
		/* 2) an error on stdin occured                   */

		if (feof(stdin)) {	/* reopen stdin on EOF input (stdin
					 * closed) */
			freopen("/dev/tty", "r", stdin);
		} else if (ferror(stdin)) {
			clearerr(stdin);
		}
	}
#endif

	return (input);
}

/* ================================================================ */
#if !(defined(USE_MY_GETS) || defined(HAS_SSR))	 
/* compile only when ioctl / curses available */

void 
set_signals()
{
	/* set local signal handler but keep previous settings     */
	/* of the signal: important if called from another program */
	/* doing signal handling on its own                        */
	/* Note that a SIGKILL cannot be caught or blocked !!!!    */
	/* Therefore terminal may be left into undefined state when */
	/* killing this proces, except when using csh who is        */
	/* resetting the tty settings explicitely (tcsh)             */
	/* Also SIGSTOP cannot be blocked so the same problem occurs */
	Intr = signal(SIGINT, signal_handler);	/* ctrl-C */
	Quit = signal(SIGQUIT, signal_handler);	/* ctrl-\ */
	Term = signal(SIGTERM, signal_handler);	/* kill -15 */
#ifdef SIGTSTP
	Tstp = signal(SIGTSTP, signal_handler);	/* ctrl-Z, kill -18 */
#endif
#ifdef SIGCONT
	/*
	 * now this is something special: if we load SIGCONT handling here
	 * then it will be executed first when SIGTERM arives !!. In order to
	 * circumvent this, I ignore the action here (set to default because
	 * you can't ignore SIGCONT), keep the previous action and load
	 * SIGCONT handling when a SIGTSTP arives. 
	 */
	Cont = signal(SIGCONT, SIG_DFL);	/* fg after ^Z, kill -19 */
#endif
}

/* ================================================================ */
void 
signal_handler(int sig)
{
	int             send_sig;	/* signal to be sent */
#ifdef _ASSUME_STDC_
	void (*Restore) ();	/* default signals to be restored */
#else
	int  (*Restore) ();	/* default signals to be restored */
#endif

	switch (sig) {
	case SIGINT:
	case SIGQUIT:
	case SIGTERM:
		/* reset raw mode of terminal */
		my_raw(0);
		send_sig = SIGTERM;	/* send a terminate signal */
		signal(sig, SIG_DFL);	/* restore default setting */
		signal(send_sig, SIG_DFL); /* prevent again getting here */
		                           /* after sending send_sig !   */
		break;
#ifdef SIGTSTP
	case SIGTSTP:
		/* reset raw mode of terminal */
		my_raw(0);
		send_sig = SIGSTOP;	/* send a suspend signal    */
		signal(sig, SIG_DFL);	/* load default signal mode */
		/* now we will install the SIGCONT handler */
		signal(SIGCONT, signal_handler);

		break;
#endif
#ifdef SIGCONT
	case SIGCONT:
		/* this is resumed after a suspend: */
		printf(" Continuing ..... (my_raw.c)\n");
		fflush(stdout);
		signal(sig, signal_handler);	/* keep same signal mode */
		longjmp(return_env, 1);	        /* return to question    */
		break;
#endif
	default:
		Restore = signal(sig, SIG_IGN);
		send_sig = sig;
		signal(sig, Restore);	/* restore previous signal */
		/* note : restore with SIG_DFL could reset user      */
		/* defined settings; therefore catch it in Restore() */
		break;
	}

	/* now generate the signals */
#if (defined(sun) || defined(VMS)) /* no raise in lib  on sun and VMS !! */
	kill(getpid(), send_sig);	/* use UNIX sys library */
#else
	raise(send_sig);	        /* this is ansi C       */
#endif

#ifndef SIGCONT			
	/* SIGCONT might not be defined: take
	 * appropriate  action when returning from kill() */
	/* if this is resumed after a suspend: */
	longjmp(return_env, 1);
#endif

}

/* ================================================================= */
void 
reset_signals()
{
	/* now restore the old signals , previously was SIG_DFL */
	signal(SIGINT, Intr);	/* ctrl-C */
	signal(SIGQUIT, Quit);	/* ctrl-\ */
	signal(SIGTERM, Term);	/* kill -15 */
#ifdef SIGTSTP
	signal(SIGTSTP, Tstp);	/* ctrl-Z */
#endif
#ifdef SIGCONT
	signal(SIGCONT, Cont);	/* fg after ^Z */
#endif
}
/* ================================================================= */
#endif           /* if ! (USE_MY_GETS || HAS_SSR)  */
