/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * exit.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

void BetaExit( number )
     long number;
{
  char buf[100];
  InfoS_End();
#ifdef RTDEBUG
  sprintf(buf, "NumIOAGc: %d, NumAOAGc: %d, NumLVRAGc: %d", 
	  NumIOAGc, NumAOAGc, NumLVRAGc);
  Notify(buf);
#endif /* RTDEBUG */
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
  long *thePC;

  do {
    if( errorNo < 0 ){
#ifdef sparc
      asm("ta 3");
      StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
      thePC = (long *) ((struct RegWin *)FramePointer)->i7;
#else
      StackEnd = (ptr(long)) &theObj; StackEnd++;
      /* Current object was pushed as the first thing, when
       * the error was detected. The "thing" just below
       * is the first real part of the Beta stack
       */
      thePC = 0;
#endif
      if (errorNo==QuaErr || errorNo==QuaOrigErr){
	if (QuaCont) {
	  fprintf(output, "\n*** OBS. ");
	  fprintf(output, ErrorMessage(QuaErr));
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
	  break; /* Don't BetaExit() */
	} 
#ifndef sparc
#if defined(linux) || defined(nti)
	(long *)StackEnd += 9;
	/* We have performed 'pushad', and also we have a return
	 * address from call Qua to ignore.; see Qua.run.
	 */
#else
	(long *)StackEnd += 14;
	/* We have saved a0-a4, d0-d7, and also we have a return
	 * address from jsr Qua to ignore.; see Qua.run.
	 */
#endif
#endif
      }
      if (DisplayBetaStack( errorNo, theObj, thePC, 0))
	break; /*  DisplayBetaStack <> 0 => continue execution */
    }    
    BetaExit(1);
  } while (FALSE);
  asmemptylabel(BetaErrorEnd);
}

