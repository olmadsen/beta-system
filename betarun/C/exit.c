/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * exit.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"

void BetaExit( number )
     long number;
{
  InfoS_End();
#ifdef RTDEBUG
  fprintf(output, "NumIOAGc: %d, NumAOAGc: %d, NumLVRAGc: %d\n", 
	  NumIOAGc, NumAOAGc, NumLVRAGc);
#endif
#ifdef apollo
  AsmExit( number );
#else
  exit( number );
#endif
}

void BetaError(errorNo, theObj)
  long errorNo;
  ref(Object) theObj;
{
  if( errorNo < 0 ){
#ifdef sparc
    asm("ta 3");
    StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
#else
    StackEnd = (ptr(long)) &theObj; StackEnd++;
    /* Current object was pushed as the first thing, when
     * the error was detected. The "thing" just below
     * is the first real part of the Beta stack
     */
#endif
    if (errorNo==QuaErr || errorNo==QuaOrigErr){
      if (QuaCont) {
	fprintf(output, "\n*** OBS. ");
	ErrorMessage(output, QuaErr);
	fprintf(output, ".\nCurrent object:\n");
	if( theObj != 0 ){
	  if( isObject(theObj)){
	    DisplayObject(output, theObj, 0);
	  }else{
	    fprintf(output,"Current object is damaged!\n");
	  }
	} else {
	  fprintf(output,"Current object is 0!\n");
	}
	fprintf(output, "(continuing)\n");
	fflush(output);
	return;
      } 
#ifndef sparc
      (long *)StackEnd+=13;
      /* We have saved a0-a4, d0-d7, and also we have a return
       * address from jsr Qua to ignore.; see Qua.run.
       */
#endif
    }
    DisplayBetaStack( errorNo, theObj);  
  }
  BetaExit(1);
}

