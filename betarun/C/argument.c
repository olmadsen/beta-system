/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * argument.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

  
/* Argc is an external described in "betaenvbody.bet"
 *   Argc: External
 *   (# noOfArgs: @integer;  
 *   exit noOfArgs
 *   #)
 */

long  Argc(){ return ArgCount; }

/* Argv is an external described in "betaenvbody.bet"
 *   Argv: External
 *  (# argNo: @integer;
 *     theArg: [1]@char;
 *  enter argNo
 *  do CallC
 *  exit theArg
 *  #) 
 */

char *Argv(n) long n; { return ArgVector[n-1]; }
