/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: outpattern.c,v $, rel: %R%, date: $Date: 1991-04-09 08:48:20 $, SID: $Revision: 1.5 $
 * by Lars Bak
 */

#include "beta.h"

static ptr(char) theItemName(theItem)
  ref(Item) theItem;
{
  ptr(short) Tab;
  long  TabValue;
  int   index;

  TabValue  = (long) theItem->Proto->GCTabOff;
  TabValue += (long) theItem->Proto;
  Tab = (ptr(short)) TabValue;

  index = 0;
  while( Tab[index++] != 0 );
  while( Tab[index]   != 0 ) index += 4;
      
  return (ptr(char)) &Tab[index+1];
}

static ptr(char) theFormName(theItem)
  ref(Item) theItem;
{
  long  TabValue;

  TabValue  = (long) theItem->Proto;
  TabValue += (int)  theItem->Proto->FormOff;

  return (ptr(char)) TabValue;
}


DisplayObject(output,aObj)
  ptr(FILE)   output;
  ref(Object) aObj;
{ 
  ref(Item) aItem;

  if( isSpecialProtoType(aObj->Proto) ){
    switch ((long) aObj->Proto){
      case ComponentPTValue:
        aItem = ComponentItem(aObj);
        fprintf(output,"  comp '%s' in '%s'\n", 
		theItemName(aItem), theFormName(aItem));
        break;
      case StackObjectPTValue:
        fprintf(output,"  stackobject\n");
        break;
      case ValRepPTValue:
        fprintf(output,"  ValRep\n");
        break;
      case RefRepPTValue:
        fprintf(output,"  RefRep\n");
        break;
    } 
  }else
    fprintf(output,"  item '%s' in '%s'\n", 
	   theItemName(aObj), theFormName(aObj));
}


ErrorMessage(output, errorNumber)
  ptr(FILE) output;
  int errorNumber;
{
  if( errorNumber == -1){
      fprintf(output,"Reference is none"); return;
    }
  if( errorNumber == -2){
      fprintf(output,"Executing terminated component"); return;
    }
  if( errorNumber == -3){
      fprintf(output,"Repetition index out of range"); return;
    }
  if( errorNumber == -4){
      fprintf(output,"Arithmetic exception"); return;
    }
  if( errorNumber == -5){
      fprintf(output,"Repetition subrange out of range"); return;
    }
  if( errorNumber == -6){
      fprintf(output,"Repetition subrange out of range"); return;
    }
  if( errorNumber == -7){
      fprintf(output,"Repetition subrange out of range"); return;
    }
  if( errorNumber == -8){
      fprintf(output,"Stop is called"); return;
    }
  if( errorNumber == -9){
      fprintf(output,"LVRA is full, please implement next step!"); return;
    }
  if( errorNumber == -10){
      fprintf(output,"Integer division by zero"); return;
    }
  if( errorNumber == -11){
      fprintf(output,"Call back function area is full"); return;
    }
  if( errorNumber == -30){
      fprintf(output,"Illegal instruction"); return;
    }
  if( errorNumber == -31){
      fprintf(output,"Bus error"); return;
    }
  if( errorNumber == -32){
      fprintf(output,"Segmentation fault"); return;
    }
  if( errorNumber == -33){
      fprintf(output,"AOAtoIOAtable is full (temporary)"); return;
  }
  if( errorNumber == -34){
      fprintf(output,"AOAtoLVRAtable is full (temporary)"); return;
  }
  if( errorNumber == -100){
      fprintf(output,"Unknown signal"); return;
    }
  fprintf(output,"Unknown error (%d)", errorNumber);
}

NotInHeap( address)
  int address;
{
  if( inIOA(address) || inAOA(address) || inLVRA(address) ) return FALSE;
  else return TRUE;
}

/* Traverse the StackArea [low..high] and Process all references within it. */
static DisplayStackPart( output, low, high)
  ptr(long) low;
  ptr(long) high;
  FILE *output;
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;

  while( current <= high ){
    if( inBetaHeap( *current)){
      theCell = (handle(Object)) current;
      theObj  = *theCell;
      if( inIOA(theObj) || inAOA(theObj) ){
	if( isObject( theObj) && NotInHeap(*(current+1)))
	  DisplayObject(output, theObj);
      }
    }else{
      switch( *current){
      case -8: current++;
      case -7: current++;
      case -6: current++;
      case -5: current++;
	break;
      }
    }
    current++;
  }
}

DisplayBetaStack( errorNumber, theObj)
  int errorNumber;
  ref(Object) theObj;
{
  ptr(long) stackptr;
  ptr(FILE) output;

  fprintf(stderr,"# Beta execution aborted: ");
  ErrorMessage(stderr, errorNumber);

  if( (output = fopen("beta.dump","w")) == NULL){
    output = stderr;
    fprintf( output, ".\n");
  }else{
    fprintf(stderr,", look at 'beta.dump'.\n");
    fprintf(output,"Beta execution aborted: ");
    ErrorMessage(output, errorNumber);
    fprintf( output, ".\n");
  }

  if( theObj != 0 ){
    if( isObject(theObj)){
      fprintf(output,"Current Object:\n");
      DisplayObject(output, theObj);
    }else{
      fprintf(output,"Current Object can't be retrieved!\n");
    }
  }else
    fprintf(output,"Current Object is 0!\n");

  fprintf(output,"Dump of stack:\n");

  if( ActiveCallBackFrame ){
    ptr(long)          theTop   = StackEnd;
    ref(CallBackFrame) theFrame = ActiveCallBackFrame;
    while( theFrame){
      DisplayStackPart( output, theTop, (long) theFrame - 4);
      fprintf( output,"  [ C activation part involving beta Call Back ]\n");
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
    }
    DisplayStackPart( output, theTop, StackStart);  
  }else DisplayStackPart( output, StackEnd, StackStart);

  fclose(output);
}

