/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $Id: exit.c,v 1.4 1992-09-04 17:13:04 tthorn Exp $
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"

BetaExit( number )
     int number;
{
  InfoS_End();
#ifdef apollo
  AsmExit( number );
#else
  exit( number );
#endif
}

BetaError(errorNo, theObj)
  int errorNo;
  ref(Object) theObj;
{
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

