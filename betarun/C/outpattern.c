/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: outpattern.c,v $, rel: %R%, date: $Date: 1992-03-04 10:18:08 $, SID: $Revision: 1.13 $
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
  while( Tab[index]   != 0 ) index += 4;
  while( Tab[index++] != 0 );
      
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
  while( Tab[index]   != 0 ) index += 4;
  while( Tab[index++] != 0 );
      
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

struct errorEntry {
  int  errorNumber;
  char *errorMessage;
} errorTable[] = {
    -1, "Reference is none",
    -2, "Executing terminated component",
    -3, "Repetition index out of range",
    -4, "Arithmetic exception",
    -5, "Repetition subrange out of range",
    -6, "Repetition subrange out of range",
    -7, "Repetition subrange out of range",
    -8, "Stop is called",
    -9, "LVRA is full, please implement next step!",
   -10, "Integer division by zero",
   -11, "Call back function area is full",
   -12, "Call back Pascal function has wrong return size",
   -13, "Suspending component involving call backs",
   -30, "Illegal instruction",
   -31, "Bus error",
   -32, "Segmentation fault",
   -33, "AOAtoIOAtable is full (temporary)",
   -34, "AOAtoLVRAtable is full (temporary)",
   -35, "Text param. to C routine to big (max. 1000 bytes)",
  -100, "Unknown signal",
     0, 0
};

ErrorMessage(output, errorNumber)
  ptr(FILE) output;
  int errorNumber;
{
  int  index = 0;

  while( errorTable[index].errorNumber != 0){
    if( errorNumber == errorTable[index].errorNumber){
      fprintf(output,"%s", errorTable[index].errorMessage);
      return;
    }
    index++;
  }
  fprintf(output,"Unknown error (%d)", errorNumber);
}

NotInHeap( address)
  int address;
{
  if( inIOA(address) || inAOA(address) || inLVRA(address) ) return FALSE;
  else return TRUE;
}

/* Traverse the StackArea [low..high-4] and Process all references within it. */
static DisplayStackPart( output, low, high)
  ptr(long) low;
  ptr(long) high;
  FILE *output;
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;

  while( current < high ){
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
  ptr(FILE) output;

  ptr(long)          theTop;
  ptr(long)          theBottom;
  
  ref(CallBackFrame)  theFrame;
  ref(ComponentBlock) currentBlock;

  ref(Component)      currentComponent;
  ref(Object)         currentObject;

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

  fprintf(output,"\nCall chain:\n");

  /* If we are able to retrieve information about the current object
   * dump it.
   */
  if( theObj != 0 ){
    if( isObject(theObj)){
      DisplayObject(output, theObj, 0);
    }else{
      fprintf(output,"Current object is damaged!\n");
    }
  }else
    fprintf(output,"Current object is 0!\n");

   /*
   * First handle the topmost component block
   */
  currentComponent = ActiveComponent;
  theTop    = StackEnd;
  theBottom = (ptr(long)) lastCompBlock;
  theFrame  = ActiveCallBackFrame;
  /* Follow the stack */
  while( theFrame){
    DisplayStackPart( output, theTop+1, theFrame-1);
    fprintf( output,"  [ C ACTIVATION PART ]\n");
    theTop   = theFrame->betaTop;
    theFrame = theFrame->next;
    if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
    theTop += 2;
  }
  DisplayStackPart(output, theTop, theBottom - 4);

  DisplayObject( output, (ref(Object)) currentComponent, 0);
  /* Make an empty line after the component */
  fprintf( output, "\n");
 
  fflush( output);

  /*
   * Then handle the remaining component blocks.
   */
  currentBlock = lastCompBlock;
  currentObject    = currentComponent->CallerObj;
  currentComponent = currentComponent->CallerComp;

  while( currentBlock->next ){
    theTop    = (ptr(long)) ((long) currentBlock + 12);
    theBottom = (ptr(long)) currentBlock->next;
    theFrame  = currentBlock->callBackFrame;

    DisplayObject(output, currentObject, 0);
    while( theFrame){
      DisplayStackPart( output, theTop+1, theFrame-1);
      fprintf( output,"  [ C ACTIVATION PART ]\n");
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
      if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
      theTop += 2;
    }
    DisplayStackPart( output, theTop, theBottom-4); 

    DisplayObject( output, (ref(Object)) currentComponent, 0);
    /* Make an empty line after the component */
    fprintf( output, "\n");
   
    currentBlock = currentBlock->next;
    currentObject    = currentComponent->CallerObj;
    currentComponent = currentComponent->CallerComp;
  }

  fclose(output);
}

