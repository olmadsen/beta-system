/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * exit.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"

BetaExit( number )
     long number;
{
  InfoS_End();
#ifdef apollo
  AsmExit( number );
#else
  exit( number );
#endif
}

BetaError(errorNo, theObj)
  long errorNo;
  ref(Object) theObj;
{
  if (QuaCont && errorNo==QuaErr){
    fprintf(output, "\n*** OBS. ");
    ErrorMessage(output, QuaErr);
    fprintf(output, " (continuing)\n");
  } else {
    if( errorNo < 0 ){
#ifdef sparc
      asm("ta 3");
      StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
#else
      StackEnd = (ptr(long)) &theObj; StackEnd++;
#endif
      DisplayBetaStack( errorNo, theObj);  
    }
    BetaExit(-1);
  }
}

