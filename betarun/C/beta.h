#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "define.h"

#include <stdio.h>

extern struct group_header *BETA_DATA; /* Defined in BETA */

#if defined (MAC)
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

#ifdef MT
#include <thread.h>
/* synchronization variables */
extern mutex_t lvra_lock;
extern mutex_t aoa_lock;
extern mutex_t cbfa_lock;
#endif

#include "betaerror.h"
#include "object.h"
#include "heap.h"
#include "constant.h"
#include "macro.h"
#include "function.h"
#include "data.h"
#include "registers.h"

#ifdef crts
#include "crtsdep.h"
#endif

#ifdef sparc
#include "sparcdep.h"
#endif

#ifdef hppa
#include "snakedep.h"
#endif

#endif
