/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: exit.c,v $, rel: %R%, date: $Date: 1992-06-11 17:21:54 $, SID: $Revision: 1.2 $
 * by Lars Bak.
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
    StackEnd = FramePointer;
#else
    StackEnd = (ptr(long)) &theObj; StackEnd++;
#endif
    DisplayBetaStack( errorNo, theObj);  
  }
  BetaExit(-1);
}

