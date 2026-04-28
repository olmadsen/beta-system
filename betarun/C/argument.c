/*
 * BETA RUNTIME SYSTEM, Copyright (C) Aarhus University
 * argument.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

  
/* Argc is an external described in "betaenvbody.bet"
 *   Argc: External
 *   (# noOfArgs: @integer;  
 *   exit noOfArgs
 *   #)
 */

long  Argc(void){ return ArgCount; }

/* Argv is an external described in "betaenvbody.bet"
 *   Argv: External
 *  (# argNo: @integer;
 *     theArg: [1]@char;
 *  enter argNo
 *  do CallC
 *  exit theArg
 *  #) 
 */

char  *Argv(long n){ return ArgVector[n-1]; }

char **Argvector(void){ return ArgVector; }

#include <stdarg.h>
void TraceXcall(long arg1, ...)
{
  va_list ap;
  fprintf(output, "External call: %s(", XcallName);
  if (XcallNum--){
    /* At least 1 arg */
    fprintf(output, "0x%x", (int)arg1);
    if (XcallNum) {
      /* At least 2 args */
      fprintf(output, ", ");
      va_start(ap, arg1);
      while (XcallNum--){
	fprintf(output, "0x%x", (int)(va_arg(ap, long)));
	if (XcallNum) fprintf(output, ", ");
      }
      va_end(ap);
    }
  }
  fprintf(output, ")\n"); fflush(output);
}

void TraceXres(unsigned int res)
{
  fprintf(output, "returns 0x%x\n", res);
  fflush(output);
}
