#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include <stdio.h>

#include "define.h"

extern long *BETA_data1; /* C-variable */
extern long *BETA_end; /* C-variable */

#if !defined(macintosh) && !defined(MAC)
# include <string.h>
# include <malloc.h>
# include <memory.h>
#endif

#if defined(macintosh) || defined (MAC)
# include <Memory.h>
# include <StdLib.h>
# include <String.h>
# ifdef RTDEBUG
#  include <Types.h>
# endif
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
#endif

#ifdef sparc
#include "sparcdep.h"
#endif

#ifdef hppa
#include "snakedep.h"
#endif

#if 0
#ifdef __STDC__
#define P(A) A
#else
#define P(A) ()
#endif
#endif

#endif
