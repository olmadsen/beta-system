/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * outpattern.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#include "beta.h"

static ptr(char) ProtoTypeName(theProto)
     ref(ProtoType) theProto;
{
  ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
  ptr(short) dyn;
  
  while (*(short *) stat) stat++;	/* Step over static gc entries */ 
  dyn = ((short *) stat) + 1;		/* Step over the zero */
  while (*dyn++);			/* Step over dynamic gc entries */
  
  return (ptr(char)) dyn;
}

static ptr(char) theFormName(theItem)
     ref(Item) theItem;
{
  long  TabValue;
  
  TabValue  = (long) theItem->Proto;
  TabValue += (long)  theItem->Proto->FormOff;
  
  return (ptr(char)) TabValue;
}


void DisplayObject(output,aObj,retAddress)
     ptr(FILE)   output;       /* Where to dump object */
     ref(Object) aObj;         /* Object to display */
     ptr(long)   retAddress;   /* Address aObj was left from (jsr), i.e. when 
				* it was current object.
				*/
{ 
  ref(Item) aItem=0;
  ref(ProtoType) theProto=0;
  ref(ProtoType) activeProto=0;
  long           activeDist;
  ref(Object)    staticObj;
  
  if( isSpecialProtoType(aObj->Proto) ){
    switch ((long) aObj->Proto){
    case (long) ComponentPTValue:
      aItem = ComponentItem(aObj);
      if (aItem==BasicItem) {
	fprintf(output,"  basic component in %s\n", 
		theFormName(aItem));
      } else {
	theProto = aItem->Proto;
	if( retAddress ){
	  /* try finding active prefix */
	  activeProto = theProto;
	  activeDist  = retAddress - theProto->GenPart; 
	  while(theProto->Prefix &&
		theProto->Prefix->Prefix != theProto->Prefix){
	    theProto = theProto->Prefix;
	    if((retAddress - theProto->GenPart > 0) &&
	       (retAddress - theProto->GenPart < activeDist)){ 
	      activeProto = theProto;
	      activeDist  = retAddress - theProto->GenPart; 
	    }
	  }
	}
	theProto = aItem->Proto;
	if(theProto==activeProto || /* active prefix */
	   (!activeProto && 
	    theProto->Prefix &&
	    theProto->Prefix->Prefix==theProto->Prefix)) /* no prefix */
	  fprintf(output,"  comp <%s>", ProtoTypeName(theProto));
	else
	  fprintf(output,"  comp %s", ProtoTypeName(theProto));

	/* Print chain of prefixes */
	while(theProto->Prefix &&
	      theProto->Prefix->Prefix != theProto->Prefix){
	  theProto = theProto->Prefix;
	  if( theProto == activeProto )
	    fprintf(output,"<%s>", ProtoTypeName(theProto));
	  else
	    fprintf(output,"%s", ProtoTypeName(theProto));
	}
	fprintf(output," in %s\n", theFormName(aItem));
      }
      break;
    case (long) StackObjectPTValue:
      fprintf(output,"  stackobject\n");
      break;
    case (long) ByteRepPTValue:
      fprintf(output,"  ByteRep\n");
      break;
    case (long) WordRepPTValue:
      fprintf(output,"  WordRep\n");
      break;
    case (long) DoubleRepPTValue:
      fprintf(output,"  DoubleRep\n");
      break;
    case (long) ValRepPTValue:
      fprintf(output,"  ValRep\n");
      break;
    case (long) RefRepPTValue:
      fprintf(output,"  RefRep\n");
      break;
    } 
  }else{    
    theProto = aObj->Proto;
    /* Find the active prefix level based on the retAddress.
     * Here we use the fact, that the G-entry is placed just before
     * the M-entry. Thus the prefix we are in is the one, where
     * the distance from the G-entry of the corresponding prefix-level
     * to retAddress is smallest.
     */
    if( retAddress ){
      activeProto = theProto;
      activeDist  = retAddress - theProto->GenPart; 
      while(theProto->Prefix && 
	    theProto->Prefix->Prefix != theProto->Prefix){
	theProto = theProto->Prefix;
        if((retAddress - theProto->GenPart > 0) &&
	   (retAddress - theProto->GenPart < activeDist)){ 
	  activeProto = theProto;
	  activeDist  = retAddress - theProto->GenPart; 
	}
      }
    }
    fprintf(output,"  item ");
    /* Print chain of prefixes */
    theProto = aObj->Proto;
    if(theProto==activeProto || /* active prefix */
       (!activeProto && 
	theProto->Prefix &&
	theProto->Prefix->Prefix==theProto->Prefix)) /* no prefix */
      fprintf(output,"<%s>", ProtoTypeName(theProto));
    else
      fprintf(output,"%s", ProtoTypeName(theProto));
    while(theProto->Prefix &&
	  theProto->Prefix->Prefix != theProto->Prefix){
      theProto = theProto->Prefix;
      if( theProto == activeProto )
	fprintf(output,"<%s>", ProtoTypeName(theProto));
      else
	fprintf(output,"%s", ProtoTypeName(theProto));
    }
    fprintf(output, " in %s\n", theFormName(aObj));
    
    /* Print Static Environment Object. */
    { long addr;
      if (!activeProto) activeProto = theProto;
      if (!activeProto) return;
      addr=(long)aObj + (4*(long)activeProto->OriginOff);
      if (addr) 
	staticObj = *(handle(Object))addr;
      else
	staticObj = 0;
      if( staticObj )
	if( isObject( staticObj ) ){
	  fprintf(output,"    -- ");
	  theProto = staticObj->Proto;
	  fprintf(output,"%s", ProtoTypeName(theProto));
	  while(theProto->Prefix &&
		theProto->Prefix->Prefix != theProto->Prefix){
	    theProto = theProto->Prefix;
	    fprintf(output,"%s", ProtoTypeName(theProto));
	  }
	  fprintf(output, " in %s\n", theFormName(aObj));
	}
    }
  }
}

static struct errorEntry {
  long  errorNumber;
  char *errorMessage;
} errorTable[] = {
  RefNoneErr,        "Reference is none",
  CompTerminatedErr, "Executing terminated component",
  RepRangeErr,       "Repetition index out of range",
  ArithExceptErr,    "Arithmetic exception",
  RepSubRangeErr,    "Repetition subrange out of range",
  RepLowRangeErr,    "Repetition subrange out of range (low)",
  RepHighRangeErr,   "Repetition subrange out of range (high)",
  StopCalledErr,     "Stop is called",
  LVRAfullErr,       "LVRA is full",
  ZeroDivErr,        "Integer division by zero",
  CBFAfullErr,       "Call back function area (CBFA) is full",
  PascalCallBackErr, "Call back Pascal function has wrong return size",
  CompCallBackErr,   "Suspending component involving call backs",
  LeaveBasicCompErr, "Attempt to leave basic component",
  QuaErr,            "Qualification error in reference assignment",
  QuaOrigErr,        "Qualification error in reference assignment; origins differ",
  RecursiveAttErr,   "Attach of component that is already attached",
  EmulatorTrapErr,   "Emulator trap",
  IllegalInstErr,    "Illegal instruction",
  BusErr,            "Bus error",
  SegmentationErr,   "Segmentation fault",
  AOAtoIOAfullErr,   "AOAtoIOAtable is full",
  AOAtoLVRAfullErr,  "AOAtoLVRAtable is full",
  CTextPoolErr,      "Text parameter to C routine too big (max. 1000 bytes)",
  AOAtoIOAallocErr,  "Failed to allocate AOAtoIOAtable",
  UnknownSigErr,     "Unknown signal",
  0, 0
  };

static char UnknownError[25];

void ErrorMessage(output, errorNumber)
     ptr(FILE) output;
     long errorNumber;
{
  long  index = 0;
  
  while( errorTable[index].errorNumber != 0){
    if( errorNumber == errorTable[index].errorNumber){
      fprintf(output,"%s", errorTable[index].errorMessage);
      BetaErrorString = errorTable[index].errorMessage; /* For Valhalla */
      return;
    }
    index++;
  }
  sprintf(UnknownError, "Unknown error (%d)", errorNumber);
  BetaErrorString = UnknownError;
  fprintf(output, UnknownError);
}

#ifndef sparc

static NotInHeap( address)
     long address;
{
  if( inIOA(address) || inAOA(address) || inLVRA(address) ) return FALSE;
  else return TRUE;
}

/* Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
static DisplayStackPart( output, low, high, theComp)
     ptr(long) low;
     ptr(long) high;
     FILE *output;
     ref(Component) theComp;
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;
  long retAddr=0;
  
  while( current <= high ){
    retAddr=0;
    if( inBetaHeap( *current)){
      theCell = (handle(Object)) current;
      theObj  = *theCell;
      if( inIOA(theObj) || inAOA(theObj) ){
	if( isObject( theObj) && NotInHeap(*(current+1)))
	  if (theComp && cast(Object)theComp->Body==theObj){
	    retAddr=*(current+1); /* pc of theComp, when it was left */
	    break;
	  }
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
  if (theComp){
    DisplayObject( output, (ref(Object)) theComp, retAddr);
    /* Make an empty line after the component */
    fprintf( output, "\n");
  }
}
#endif

#ifdef sparc
void
  DisplayAR(FILE *output, struct RegWin *theAR, struct RegWin *nextAR)
{
  struct Object *theObj = (struct Object *) theAR->i0;
  
  if ((inIOA(theObj) || inAOA(theObj)) && isObject(theObj))
    DisplayObject(output, theObj, theAR->i7);
}
#endif

void DisplayBetaStack( errorNumber, theObj)
     long errorNumber;
     ref(Object) theObj;
{
  ptr(FILE) output;
#ifndef sparc
  ref(Component)      currentComponent;
#endif
  
  fprintf(stderr,"\n# Beta execution aborted: ");
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
  
  fprintf(output,"\nCall chain:\n\n");
  
#ifndef sparc
  /* If we are able to retrieve information about the current object
   * dump it.
   */
  if( theObj != 0 ){
    if( isObject(theObj)){
      if (theObj!=cast(Object)ActiveComponent->Body)
	/* retAddress is 0 because we have no way of knowing
	 * current address in current object (yet)
	 */
	DisplayObject(output, theObj, 0);
    }else{
      fprintf(output,"Current object is damaged!\n");
    }
  }else
    fprintf(output,"Current object is damaged!\n");
#endif

  if (StackStart == 0){
    fprintf(output,"\n  [initialization of basic component]\n");
    return;
  }
  
#ifdef hppa
  /*
   * The HP-PA (Snake) specific parts of tracing the Beta stack.
   */
  {
    struct Object **theCell = getRefSP();
    struct Object *theObj;
    
    while((void **)theCell > &ReferenceStack[0]) {
      if((unsigned)*theCell & 1) {
	theObj = (struct Object *)((unsigned)*theCell & ~1);
	if(theObj && isObject(theObj)) {
	  DisplayObject(output, theObj, 0);
	} else {
	  fprintf(output, "[Damaged object!: %x]\n", (long)theObj);
	}
      }
      theCell--;
    }
    
    fflush(output);
  }
#endif
  
#ifdef sparc
  /*
   * This is the SPARC specifics of DisplayBetaStack
   */
  {
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    
    /* Flush register windows to stack */
    asm("ta 3");
    
    for (theAR =  (struct RegWin *) StackEnd;
	 theAR != (struct RegWin *) 0;
	 theAR =  (struct RegWin *) theAR->fp) {
      if (theAR == nextCompBlock) {
	/* This is the AR of attach. Continue GC, but get
	 * new values for nextCompBlock and nextCBF. 
	 * Please read StackLayout.doc
	 */
	
	nextCBF = (struct RegWin *) theAR->l5;
	nextCompBlock = (struct RegWin *) theAR->l6;

	if (nextCompBlock == 0)
	  {
	    DisplayObject(output, (struct Object *)theAR->i1, 0); /* AttBC */
	    fprintf(output, "\n"); fflush(output);
	    break; /* we reached the bottom */
	  }

	DisplayObject(output, (struct Object *) theAR->i0, 0); /* Att */
	/* Make an empty line after the component */
	fprintf(output, "\n"); fflush(output);
	
	continue;
      }
      else if (theAR == nextCBF) {
	/* This is AR of HandleCB. Don't GC this, but
	 * skip to betaTop and update nextCBF */
	
	fprintf( output,"  [ C ACTIVATION PART ]\n");
	
	nextCBF = (struct RegWin *) theAR->l5;
	theAR = (struct RegWin *) theAR->l6;
      }
      if (theAR->fp != (long) nextCompBlock)
	DisplayAR(output, theAR, (struct RegWin *) theAR->fp);
    }
  }
#endif
  
#ifndef hppa
#ifndef sparc
  
  { 
    ptr(long)           theTop;
    ptr(long)           theBottom;
    
    ref(CallBackFrame)  theFrame;
    
    ref(ComponentBlock) currentBlock;
    ref(Object)         currentObject;
    long                retAddr=0;

    /*
     * First handle the topmost component block
     */
    currentComponent = ActiveComponent;
    theTop    = StackEnd;
    theBottom = (ptr(long)) lastCompBlock;
    theFrame  = ActiveCallBackFrame; 
    /* Follow the stack */
    while( theFrame){
      DisplayStackPart( output, theTop+1, (long *)theFrame-1, 0);
      fprintf( output,"  [ C ACTIVATION PART ]\n");
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
      if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
      theTop += 2;
    }

    DisplayStackPart(output, theTop, theBottom-1 -2, currentComponent);  
    /* -2 because:
     *  There will always be at least 2 longs, not needed above the
     *  ComponentBlock: the exitAddress (TerminateComponent) and
     *  the Saved previous object when the component starts executing.
     */
    
    fflush( output);
    
    /*
     * Then handle the remaining component blocks.
     */
    currentBlock     = lastCompBlock;
    currentObject    = currentComponent->CallerObj;
    retAddr          = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
    
    while( currentBlock->next ){
      theTop    = (long *) ((long) currentBlock + sizeof(struct ComponentBlock) );
      theBottom = (ptr(long)) currentBlock->next;
      theFrame  = currentBlock->callBackFrame;
      
      DisplayObject(output, currentObject, retAddr);
      while( theFrame){
	DisplayStackPart( output, theTop+1, (long *)theFrame-1, 0);
	fprintf( output,"  [ C ACTIVATION PART ]\n");
	theTop   = theFrame->betaTop;
	theFrame = theFrame->next;
	if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
	theTop += 2;
      }

      DisplayStackPart( output, theTop +1, theBottom-1 -2, currentComponent); 
      /* theTop +1 because the component to be attached is always
       * pushed before attach is called. We don't want to show
       * it here, since we have just shown it as separate component
       * block.
       */
      
      currentBlock = currentBlock->next;
      currentObject    = currentComponent->CallerObj;
      retAddr          = currentComponent->CallerLSC;
      currentComponent = currentComponent->CallerComp;
    }
  }
#endif
#endif
  
  fclose(output);
}



#ifdef RTDEBUG

char *DescribeObject(theObject)
  struct Object *theObject;
{
  ref(ProtoType) theProto = theObject->Proto;
  if (isSpecialProtoType(theProto)){
    char buffer[100];
    switch ((long) theProto){
    case (long) ComponentPTValue:
      strcpy(buffer, "Component: ");
      strncat(buffer, DescribeObject((cast(Component)theObject)->Body), 88);
      return buffer;
    case (long) StackObjectPTValue:
      return "StackObj";
    case (long) StructurePTValue:
      sprintf(buffer, 
	     "Struc: origin: 0x%x, proto: 0x%x", 
	     (cast(Structure)theObject)->iOrigin,
	     (cast(Structure)theObject)->iProto);
      return buffer;
    case (long) DopartObjectPTValue:
      sprintf(buffer, 
	     "Dopart: origin: 0x%x", 
	     (cast(DopartObject)theObject)->Origin);
      return buffer;
    case (long) RefRepPTValue:
      return "RefRep";	
    case (long) ValRepPTValue:
      return "IntegerRep";
    case (long) ByteRepPTValue:
      strcpy(buffer, "CharRep: '");
      if ( (((cast(ValRep)theObject)->HighBorder)-((cast(ValRep)theObject)->LowBorder)+1) > 10 ){
	strncat(buffer, (char *)(cast(ValRep)theObject)->Body, 10);
	strcat(buffer, "...'");
      } else {
	strcat(buffer, (char *)(cast(ValRep)theObject)->Body);
	strcat(buffer, "'");
      }
      return buffer;
    case (long) WordRepPTValue:
      return "ShortRep";
    case (long) DoubleRepPTValue:
      return "RealRep";
    }
  } else {
    ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
    ptr(short) dyn;
  
    while (*(short *) stat) stat++;	/* Step over static gc entries */ 
    dyn = ((short *) stat) + 1;		/* Step over the zero */
    while (*dyn++);			/* Step over dynamic gc entries */
    
    return (ptr(char)) dyn;
  }
}

#endif
