/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: exit.c,v $, rel: %R%, date: $Date: 1992-05-04 14:46:39 $, SID: $Revision: 1.1 $
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
    StackEnd = (ptr(long)) &theObj; StackEnd++;     
    DisplayBetaStack( errorNo, theObj);  
  }
  BetaExit(-1);
}

