/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: outpattern.c,v $, rel: %R%, date: $Date: 1991-10-09 14:36:27 $, SID: $Revision: 1.7 $
 * by Lars Bak
 */

#include "beta.h"

static ptr(char) ProtoTypeName(theProto)
  ref(ProtoType) theProto;
{
  ptr(short) Tab;
  long  TabValue;
  int   index;

  TabValue  = (long) theProto->GCTabOff;
  TabValue += (long) theProto;
  Tab = (ptr(short)) TabValue;

  index = 0;
  while( Tab[index++] != 0 );
  while( Tab[index]   != 0 ) index += 4;
      
  return (ptr(char)) &Tab[index+1];
}

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


DisplayObject(output,aObj,retAddress)
  ptr(FILE)   output;
  ref(Object) aObj;
  ptr(long)   retAddress;
{ 
  ref(Item) aItem;

  if( isSpecialProtoType(aObj->Proto) ){
    switch ((long) aObj->Proto){
      case ComponentPTValue:
        aItem = ComponentItem(aObj);
        fprintf(output,"  comp %s in %s\n", 
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
  }else{
    ref(ProtoType) theProto;
    ref(ProtoType) activeProto;
    long           activeDist;
    ref(Object)    staticObj;
    handle(Object) theCell;

    theProto = aObj->Proto;
    if( retAddress ){
      activeProto = theProto;
      activeDist  = retAddress - theProto->GenPart; 
      while( theProto->Prefix->Prefix != theProto->Prefix){
	theProto = theProto->Prefix;
        if(    (retAddress - theProto->GenPart > 0)
            && (retAddress - theProto->GenPart < activeDist)){ 
	  activeProto = theProto;
	  activeDist  = retAddress - theProto->GenPart; 
	}
      }
    }else activeProto = theProto;

    fprintf(output,"  item ");
    theProto = aObj->Proto;
    if( theProto == activeProto )
      fprintf(output,"<%s>", ProtoTypeName(theProto));
    else
      fprintf(output,"%s", ProtoTypeName(theProto));
    while( theProto->Prefix->Prefix != theProto->Prefix){
      theProto = theProto->Prefix;
      if( theProto == activeProto )
	fprintf(output,"<%s>", ProtoTypeName(theProto));
      else
	fprintf(output,"%s", ProtoTypeName(theProto));
    }
    fprintf(output, " in %s\n", theFormName(aObj));

    /* Print Static Environment Object. */
    staticObj = *(handle(Object))((long)aObj + (4*(long)activeProto->OriginOff));
    if( staticObj )
      if( isObject( staticObj ) ){
	fprintf(output,"    -- ");
	theProto = staticObj->Proto;
	fprintf(output,"%s", ProtoTypeName(theProto));
	while( theProto->Prefix->Prefix != theProto->Prefix){
	  theProto = theProto->Prefix;
	  fprintf(output,"%s", ProtoTypeName(theProto));
	}
	fprintf(output, " in %s\n", theFormName(aObj));
      }
  }
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
  if( errorNumber == -12){
      fprintf(output,"Call back Pascal function has wrong return size"); return;
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
	  DisplayObject(output, theObj, *(current+1));
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
      DisplayObject(output, theObj, 0);
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
      DisplayStackPart( output, theTop, ((long) theFrame) - 16);
      fprintf( output,"  [ C ACTIVATION PART ]\n");
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
      if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
      theTop += 2;
    }
    DisplayStackPart( output, theTop, StackStart);  
  }else DisplayStackPart( output, StackEnd, StackStart);

  fclose(output);
}

