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
/*=========================RCS info==================================*/
/* $Author: beta $ */
/* $Revision: 1.1.1.1 $ */
/* $Source: /a/home/alhambra02/beta/.CVSHOME/beta_project/basiclib/private/external/cbreak/sysdefs.h,v $ */
/* $Date: 1995-09-26 10:31:47 $ */
/* $State: Exp $ */
/* $Locker:  $ */
/*===================================================================*/
/*
 *   file :  sysdefs.h
 *   purpose: header file in which typical machine dependent definitions 
 *            are done
 *   author: R. Vankemmel
 *   date:   1/7/93
 *   revisions: 
 *      1) RVK: OSF 1.3 DEC Alpha support (14/9/1994)
 *      2) RVK: VMS 5.5 and OpenVMS 6.1 VAX / Dec Alpha support (8/11/1994)
 *
 */
#ifndef SYSDEFS_H_SEEN
#define SYSDEFS_H_SEEN

/* list of predefined constants on the currently supported platforms */
/*
	APOLLO DNxx00 and HP4xx series: 
		 apollo 
		 aegis 
		 unix 
		 mc68000 
	MAC:
		 MC68000 
		 mc68000 
		 m68k 
		 macintosh 
		 mc68881  	with the option -mc68881
		 applec         on MPW-c: Apples own C 
		 THINK_C        for Think-C 4 or Think-C 5
	HPUX: 1) in -Ac (Old K&R C) mode:
		 PWB            
		 hpux and __hpux
		 unix and __unix
		 hp9000s200 	on Series 200
		 hp9000s300 and __hp9000s300 on Series 300/400
		 hp9000s500 	on Series 500
		 __hp9000s700   on Series 700
		 hp9000s800 , __hp9000s800 and __hppa on Series 800
	      2) in -Aa mode (strict ANSI):  all __* macros from above
		 (e.g. __hp9000s700, __hpux) plus the 
		 ANSI-C def's as __STDC__.
	      3) in -Ae mode (extended ANSI): as previous plus:
		 _HPUX_SOURCE
	SUN3: SunOs
		 sun 
		 mc68000
		 unix 
	SUN4: Sparc 2 or Sparc 10; SunOs 4.X
		 sun 
		 sparc
		 unix 
        SUN5: Sparc 2 or Sparc 10; Solaris 2.3
		 sun sparc unix : not with -Xc mode
		 __sparc __unix __sun __BUILTIN_VA_ARG_INCR 
		 __SUNPRO_C=0x300 
		 __SVR4
		 __svr4__ (gcc)
	SONY:
		 sony
		 unix
	IBMPC:
		 MSDOS          on IBM compatibles under MS-DOS
        linux:
	         linux

        ultrix/DECstation:   DECRisc
                unix
                ultrix
                bsd4_2
                mips     : any RISC architecture
                MIPSEL   : little endian variant of MIPS architecture
		host_mips : native compilation environment (as opposed to
		            cross- compiler)


        ultrix/VAXstation:    
	    VAX-Ultrix using VAX-C :
                unix
                ultrix
                bsd4_2
		vax, VAX, vaxc, VAXC, vax11c, VAX11C
	    VAX-Ultrix using gcc -ansi :
		__unix__, __vax__
	    VAX-Ultrix using gcc :
		unix, vax

        DEC Alpha OSF V1.3: using dec cc:
		Flags always set independent of -std flag:
		__LANGUAGE_C__  
		__unix__
		__osf__
		__alpha
		_SYSTYPE_BSD

	VAX/VMS: VMS using VAX-C
		vms 
		VMS 
		vax, VAX, vaxc, VAXC, vax11c, VAX11C 

	IBM6000:
		_IBMR2

	MIPS:
		mips
		mips_host
		unix

	AMIGA PC:
		AMIGA

	Convex:
	        __convex__ : in all compatibility modes.
		convex     : only in backward compatibility mode.
		_CONVEX_SOURCE : only in extended mode.
		__convexc__ : always defined.
		__stdc__    : only in ANSI C mode. 
		__unix__    : in all compatibility modes.
*/
/* --------------------------------------------------- */

#ifdef apollo
#define APOLLO		            /* system type = 2 */
#define BSD
#define UNIX      

#else            /* else apollo  */
#if (defined(sun) || defined(__sun)) /* sun sparc machines  SunOs 4.* 
				      * or Solaris 2.3 */
#ifdef mc68000
# define SUN3			    /* system type = 8 */
# define BSD
# define UNIX      
#else            /* else mc68000 */
# if (defined(__sparc) && (defined(__SVR4)||defined(__svr4__)))/* sparc on Solaris */
#     define SUN5                   /* system type = 15 */
#     define SYSV
#     define UNIX
# else
#  ifdef sparc
#   define SUN4			    /* system type = 1 */
#   define BSD
#   define UNIX      
#  endif           /* end sparc    */
# endif
#endif           /* end mc68000  */

#else            /* else sun's   */
#ifdef sony      /* sony machine */
#define SONY   			    /* system type = 6 */
#define BSD
#define UNIX      

#else            /* else sony    */
#if (defined(hpux) || defined(_HPUX_SOURCE))
		 /* HP 9000/x00 machines */
#define HPUX   			    /* system type = 5 */
#define SYSV
#define UNIX      
#define POSIX

#else            /* else hpux    */
#ifdef _IBMR2    /* IBM Risc6000 machine */
#define IBM6000			    /* system type = 4 */
#define SYSV
#define UNIX      

#else            /* else _ibmr2 */
#if ( (defined(mips_host) || defined(mips) ) && ! defined(ultrix) ) 
		 /* mips machine */
#define MIPS			    /* system type = 7 */
#define UNIX      
#ifdef SYSTYPE_BSD43
#define BSD
#else            /* else SYSTYPE_BSD43   */
#define SYSV
#endif           /* end if SYSTYPE_BSD43 */

#else            /* else mips_host       */
#ifdef MSDOS     /* IBMPC under MSDOS    */
#define IBMPC  			    /* system type = 12 */ 

#else
#if ( defined(ultrix) || (defined(__unix__) && defined(__vax__)) )
#  define BSD   
#  define UNIX 
#  if (defined(vax) || defined(__vax__))
#    define VAXstation                  /* system type = 10 */
#  else
#    define DECRISC                     /* system type = 3 */
#  endif

#else            /* else ultrix */
#ifdef vms       /* VAX-VMS machine */
#ifndef VMS
#  define VMS                           /* system type = 9 */
#endif
#else            /* else vms    */
#ifdef macintosh
#define MAC    			    /* system type = 11 */

#else            /* else macintosh */
#ifdef AMIGA
#define amiga                       /* system type = 13 */

#else            /* else amiga  */
#ifdef __convex__
#define CONVEX                      /* system type = 14 */
#define UNIX
#define BSD
#else            /* else convex */
#if (defined(__alpha) && defined(__osf__))
#define DECALPHA                    /* system type = 16 */
#define OSF
#else            /* else dec alpha/osf */
#ifdef linux
#define UNIX                        /* system type = 17 */
#define SYSV
#else            /* else linux */

	>>> generate error, unknown porting platform <<<

#endif                          /* 14 */
#endif                          /* 13 */
#endif    			/* 11 */
#endif    			/* 9 */
#endif    			/* 3 & 10 */
#endif    			/* 12 */
#endif    			/* 7 */
#endif    			/* 4 */
#endif    			/* 5 */
#endif    			/* 6 */
#endif    			/* 1 & 8 & 15 */
#endif    			/* 2 */     
#endif                          /* 16 */
#endif                          /* 17 */


#ifdef UNIX
#define HAS_CTYPE		/* <ctype.h>, iswhite( ), etc.		*/
#define HAS_GETPID		/* getpid( ) to identify processes	*/
#define HAS_IOCTL               /* has ioctl call's                     */
#endif /* UNIX */

#ifdef BSD 
#define HAS_BSDDIRS		/* <sys/dir.h>				*/
#define HAS_STRINGS
#define HAS_CURSES              /* has a bad curses lib                 */
#define HAS_TERMCAP             /* has a libtermcap.a                   */
#define HAS_SGTTY               /* has sgtty.h instead of termios.h     */
#endif /* BSD */

#ifdef SYSV 
#define HAS_SYSVDIRS		/* <dirent.h>				*/
#define HAS_CURSES              /* sysV has a good curses lib           */
#define HAS_TERMCAP             /* has a libtermcap.a                   */
#define HAS_TERMIOS             /* has termios.h file                   */
#endif	/* SYSV */   

#ifdef OSF
#define HAS_IOCTL               /* has ioctl calls                      */
#define HAS_CTYPE		/* <ctype.h>, etc        .		*/
#define HAS_GETPID		/* getpid( ) to identify processes	*/
#define HAS_TERMIOS             /* has termios.h file                   */
#define HAS_SYSVDIRS            /* has <dirent.h>                       */
#define HAS_CURSES              /* has a sysV based curses lib          */
#endif

#ifdef POSIX                    /* a posix compliant system             */
#define HAS_POSIX
#endif

#ifdef IBMPC           
#define HAS_CTYPE		/* <ctype.h>, iswhite( ), etc.		*/
#define HAS_STDLIB
#include <malloc.h>
#define HAS_PERROR  	        /* has own definition of perror in stdio
				   not ansi's void                      */
#ifndef __WATCOMC__
typedef long time_t;
#endif
#endif /* IBMPC */

#ifdef VMS
#define HAS_SYSVTIME
#define HAS_CTYPE		/* <ctype.h>, iswhite( ), etc.		*/
#define HAS_SSR                 /* VAX-C has a bad curses lib ; use the */
#endif /* VMS */                /* system service routines (SSR)        */ 

#ifdef AMIGA
#define HAS_SGTTY               /* has sgtty.h, no termio.h             */
#endif
/*----------------------------------------------------------------------*/
#endif /* SYSDEFS_H_SEEN */
