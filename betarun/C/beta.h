#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991, 1992 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#include <stdio.h>
#include "define.h"
#include "betaerror.h"
#include "object.h"
#include "heap.h"
#include "constant.h"
#include "macro.h"
#include "function.h"
#include "data.h"

#ifdef macintosh
#include <Memory.h>
void Prompt(char *msg1, char *msg2, char *msg3, char *msg4);
#ifdef RTDEBUG
#include <Types.h>
#endif

#endif

#ifdef sparc
#include "sparcdep.h"
#endif

#ifdef hppa
#include "snakedep.h"
#endif

#ifdef __STDC__
#define P(A) A
#else
#define P(A) ()
#endif

#endif
