#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include <stdio.h>

#include "define.h"

#ifndef NEWRUN
extern long *BETA_data1; /* Defined in BETA */
#endif /* NEWRUN */
extern long *BETA_end; /* C-variable */

#if defined(macintosh) || defined (MAC)
# include <Resources.h>
# include <Memory.h>
# include <StdLib.h>
# include <String.h>
# ifdef RTDEBUG
#  include <Types.h>
# endif
#else
# include <string.h>
# include <malloc.h>
# include <memory.h>
# include <stdlib.h>
#endif

#if defined(UNIX) || defined(nti)
#include <signal.h>
#endif /* UNIX || nti */

#ifdef sun4s
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#endif

#include "betaerror.h"
#include "object.h"
#include "heap.h"
#include "constant.h"
#include "macro.h"
#include "function.h"
#include "data.h"

#ifdef crts
#include "crtsdep.h"
#define CRUN
#endif

#ifdef sparc
#include "sparcdep.h"
#define CRUN
#endif

#ifdef hppa
#include "snakedep.h"
#define CRUN
#endif

#endif
