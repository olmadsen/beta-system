/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * outpattern.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "rtsighandler.h"
#ifdef ppcmac
#include <Files.h>
#endif

#if 0
/* comment in if you want tracing of dump for non-debug betarun */
#undef TRACE_DUMP
#define PrintCodeAddress(x) {}
#define TRACE_DUMP(code) { code; }
#endif /* 0 */

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

static char NotifyMessage[500] = { 0 /* rest is uninitialized */};

GLOBAL(static int basic_dumped)=0;

/******************************* System Exceptions *******************/

typedef int (*SYSTEMEXCEPTIONHANDLER)(BetaErr, Object *, long *, long *);
SYSTEMEXCEPTIONHANDLER systemexceptionhandler = NULL;

/* InstallSystemExceptionHandler: To be called from beta. */
void InstallSystemExceptionHandler(SYSTEMEXCEPTIONHANDLER sex){
  fprintf(output, "InstallSystemExceptionHandler: Warning: Not yet tested!!\n");
  systemexceptionhandler = sex;
}

/******************************* M_Part: *****************************/

long M_Part(ProtoType * proto)
     /* Return the address of the M-entry for the prototype proto.
      *
      * If the pattern has NO do-part and NO explicit prefix,
      * the routine returns MAXINT.
      * 
      * If the pattern has NO do-part but has a prefix, the routine will 
      * return the entry part of the last prefix.
      */
{
  if (!proto) return MAXINT;
  while ((!proto->MpartOff) && (proto!=proto->Prefix)){
    proto=proto->Prefix;
  }
  
  if (proto->MpartOff){
#ifdef macppc
    return **(long **)((long)proto+proto->MpartOff);
#else
    return *(long *)((long)proto+proto->MpartOff);
#endif
  } else {
    return MAXINT;
  }

}

/***************************** machine_type: **************************/

char *machine_type(void)
{
#undef MACHINE_TYPE

  /* Sun variants */
#ifdef sun4s
#define MACHINE_TYPE "sun4s"
#endif
 
  /* HP variants */
#ifdef hpux9pa
#define MACHINE_TYPE "hpux9pa"
#endif
  
  /* SGI */
#ifdef sgi
#define MACHINE_TYPE "sgi"
#endif

  /* Macintosh */
#ifdef macppc
#define MACHINE_TYPE "ppcmac"
#endif

  /* Linux */
#ifdef linux
#define MACHINE_TYPE "linux"
#endif
  
  /* NTI */
#ifdef nti_ms
#define MACHINE_TYPE "nti_ms"
#endif
#ifdef nti_gnu
#define MACHINE_TYPE "nti_gnu"
#endif
  
#ifndef MACHINE_TYPE
#error MACHINE_TYPE should be defined
#endif

return MACHINE_TYPE;

#undef MACHINE_TYPE

}

static void print_setenv(char *var, char *val)
{
#ifdef UNIX
  fprintf(output, "  setenv %s %s", var, val);
#endif /* UNIX */
#ifdef nti
  fprintf(output, "  set %s=%s", var, val);
#endif /* nti */
#ifdef MAC
  fprintf(output, "  set -e %s %s", var, val);
#endif /* MAC */
  fflush(output);
}

static void PrintLegend(void)
{
#undef P
#define P(text) fprintf(output, "%s\n", text)
  P("");
  P("Legend:");
  P("");
  if (SimpleDump){
    P("The above dump shows the dynamic call stack of invoked objects.");
    P("The dump starts at the object that was the current object when");
    P("the error occurred and continues down towards the basic component.");
    P("The descriptions have the following meaning:");
    P("1. Items are shown like this:");
    P("      item <name#>pname1#pname2#pname3 in ifile");
    P("   meaning that the item is an instance of the pattern \"name\" which");
    P("   has prefix \"pname1\" which has prefix \"pname2\", etc. ");
    P("   This item is defined in the file \"ifile\". ");
    P("   The part of the prefix chain enclosed in \"<\" and \">\" indicates");
    P("   where in the action sequence the error occurred.");
  } else {
    /* Including low level dump */
    P("The above dumps show the dynamic call stack of invoked objects.");
    P("Each dump starts at the object that was the current object when");
    P("the error occurred and continues down towards the basic component.");
    P("The descriptions have the following meaning:");
    P("1. Items are shown in two lines, like this:");
    P("      item <name#>pname1#pname2#pname3 in ifile");
    P("        -- sname#spname1#spname2 in sfile");
    P("   meaning that the item is an instance of the pattern \"name\" which");
    P("   has prefix \"pname1\" which has prefix \"pname2\", etc. ");
    P("   This item is defined in the file \"ifile\". ");
    P("   The part of the prefix chain enclosed in \"<\" and \">\" indicates");
    P("   where in the action sequence the error occurred.");
    P("   The line beginning with \"--\" shows the textually surrounding");
    P("   pattern using the same notation.");
  }
  P("2. The descriptor names used in the above description will normally");
  P("   have one or more \"meta characters\" appended. These mean:");
  P("      #  The descriptor belongs to a pattern, e.g. P: (# ... #)");
  P("      ~  Singular named descriptor, e.g. X: @(# ... #)");
  P("      *  Singular unnamed descriptor, e.g. ... ; (# ... #) ; ...");
  P("      -  Descriptor SLOT.");
  P("3. Components are shown using a notation similar to that of items:");
  P("      comp <name#>pname1#pname2#pname3 in cfile");
  P("4. The bottommost component corresponding to the basic environment is");
  P("   shown like an ordinary component, but indicated with");
  P("      basic component <name#>pname1#pname2#pname3 in cfile");
  P("5. In case the error occurred in some external code called from BETA,");
  P("   the top of the call stack is shown as");
  P("      [ EXTERNAL ACTIVATION PART ]");
  P("6. In case the BETA code has called some external code which has in");
  P("   turn called back into the BETA code, and the callback is still");
  P("   active at the point of the error, the intermediate call stack part");
  P("   is shown as");
  P("      [ EXTERNAL ACTIVATION PART ]");
  if (SimpleDump) return;
  P("7. The section labeled \"Low level information\" can be avoided by");
  fprintf(output, "    ");
  print_setenv("BETART", "SimpleDump");
  fprintf(output, "\n");
  P("   before subsequent executions of the program.");
#undef P
}


/********************** DisplayCell: ********************/

static void DisplayCell(long PC, Object *theObj)
{
  DisplayObject(output, theObj, PC);
}

/************************* ProtoTypeName **********************/

char *ProtoTypeName(ProtoType *theProto)
{
  GCEntry * stat;
  short *dyn;

#ifdef RTDEBUG
  if (isSpecialProtoType(theProto)){
    /* ProtoTypeName is used for some debug output, where
     * the prototype may be a special one
     */
    switch (SwitchProto(theProto)){
    case SwitchProto(ComponentPTValue):    return "[Component]";
    case SwitchProto(StackObjectPTValue):  return "[StackObj]";
    case SwitchProto(StructurePTValue):    return "[StrucObject]";
    case SwitchProto(DopartObjectPTValue): return "[DopartObject]";
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):   return "[ObjectRep]";
    case SwitchProto(RefRepPTValue):       return "[RefRep]";
    case SwitchProto(LongRepPTValue):       return "[IntegerRep]";
    case SwitchProto(ByteRepPTValue):      return "[CharRep]";
    case SwitchProto(ShortRepPTValue):      return "[ShortRep]";
    case SwitchProto(DoubleRepPTValue):    return "[RealRep]";
    }
  }
#endif /* RTDEBUG */
  
  stat = (GCEntry *) ((long) theProto + theProto->GCTabOff);
  while (*(short *) stat) stat++;	/* Step over static gc entries */ 
  dyn = ((short *) stat) + 1;		/* Step over the zero */
  while (*dyn++)
     ;			/* Step over dynamic gc entries */

#if defined(linux) || defined(nti)
  /* Step over little endian long/short/real position information */
  { 
    int skiplists=0; /* number of entries for int16s and reals */

    if((*(char*)dyn) & 0x80) skiplists++;
    if((*(char*)dyn) & 0x40) skiplists++;
    
    /* step over 'integer' bit vector (short-aligned) */
    dyn += (theProto->Size+15)>>4; 
 
    while (skiplists--){
      while (*dyn++);                /* step over int16/real info */
    }
  }
#endif

  return (char *) dyn;
}

/* Error-pc is used to remember original PC when the error happened */
GLOBAL(static unsigned long error_pc);

/*************************** ObjectDescription: **********************/

static void ObjectSurrounderDescription(Object *obj, 
					ProtoType *activeProto);

static void ObjectDescription(Object *obj, 
			      long PC, 
			      char *type, 
			      int print_origin)
{
  signed long  gDist=MAXINT, mDist, activeDist=0;
  ProtoType   *proto=GETPROTO(obj);
  ProtoType   *activeProto=proto;
  char        *groupname;
  long         mPart = M_Part(proto);
  long         gPart = G_Part(proto);

  if (isMakingDump && (obj==(Object *)BasicItem)){
    /* BasicItem will be shown as component */
    TRACE_DUMP(fprintf(output, "(BasicItem ignored - will be shown as comp)\n"));
    return;
  }

  TRACE_CODEENTRY(fprintf(output, "ObjectDescription: initial: proto=0x%x (%s), addr=0x%x\n", (int)proto, ProtoTypeName(proto), (int)PC)); 

  if (PC) {
    /* Find the active prefix level based on the PC.
     * Here we use both the G-entry and the M-entry. 
     * The prefix we are in is the one, where the distance from the 
     * G-entry or M-entry of the corresponding prefix-level
     * to PC is smallest (and positive).
     */
    
    gDist  = PC - gPart; 
    TRACE_CODEENTRY(fprintf(output, "initial gPart: 0x%x, gDist: 0x%x\n", (int)gPart, (int)gDist));
    mDist  = PC - mPart;
    TRACE_CODEENTRY(fprintf(output, "initial mPart: 0x%x, mDist: 0x%x\n", (int)mPart, (int)mDist));
    if (gDist < 0) gDist = MAXINT;
    if (mDist < 0) mDist = MAXINT;
    activeDist = (gDist<mDist) ? gDist : mDist;
    
    while(proto && (proto->Prefix != proto)/* stop at Object# */){
      proto = proto->Prefix;
      mPart = M_Part(proto);
      gPart = G_Part(proto);
      TRACE_CODEENTRY(fprintf(output, "ObjectDescription: proto=0x%x (%s), mPart=0x%x, gPart=0x%x\n", (int)proto, ProtoTypeName(proto), (int)mPart, (int)gPart)); 
      if((PC - gPart > 0) &&
	 (PC - gPart <= activeDist)){ 
	/* Use <= to get the LAST level, that has the entry point */ 
	activeProto = proto;
	activeDist  = gDist = PC - gPart; 
	TRACE_CODEENTRY(fprintf(output, "gDist: 0x%x\n", (int)gDist));
      }
      if((PC - mPart > 0) &&
	 (PC - mPart <= (long) activeDist)){ 
	/* Use <= to get the LAST level, that has the entry point */ 
	activeProto = proto;
	activeDist  = mDist = PC - mPart; 
	TRACE_CODEENTRY(fprintf(output, "mDist: 0x%x\n", (int)mDist));
      }
    }
    if (activeDist == MAXINT) return;
#ifdef MAC
    /* can't determine if an address is in a given
     * object file on MAC, so we use the prototype instead. 
     */
    TRACE_GROUP(fprintf(output, "Calling GroupName with activeProto\n"));
    groupname = GroupName((long)activeProto,0);
#else
    TRACE_GROUP(fprintf(output, "Calling GroupName with return address\n"));
    groupname = GroupName(PC,1);
#endif
  } else {
#ifdef MAC
    /* PC not known. can't determine if an address is in a given
     * object file on MAC, so we use the prototype instead. 
     */
    TRACE_GROUP(fprintf(output, "Calling GroupName with default activeProto\n"));
    groupname = GroupName((long)activeProto,0);
#else
   /* PC not known. Use the groupname of obj's mPart */
    TRACE_GROUP(fprintf(output, "Calling GroupName with default mPart\n"));
    groupname = GroupName(mPart,1);
#endif
  }

  proto = GETPROTO(obj);

  if (groupname==NULL){
    /* GroupName failed */
    TRACE_DUMP(fprintf(output, ">>>TraceDump: GroupName failed for object 0x%x, addr 0x%x\n", (int)obj, (int)PC));
    return;
  }  

  if (activeDist == gDist)
    fprintf(output,"  allocating %s ", type);
  else
    fprintf(output,"  %s ", type);
  
  if(proto==activeProto || /* active prefix */
     (!activeProto && 
      proto->Prefix &&
      proto->Prefix->Prefix==proto->Prefix)) /* no prefix */
    fprintf(output,"<%s>", ProtoTypeName(proto));
  else
    fprintf(output,"%s", ProtoTypeName(proto));
  
  /* Print chain of prefixes */
  while(proto->Prefix &&
	proto->Prefix->Prefix != proto->Prefix){
    proto = proto->Prefix;
    if( proto == activeProto )
      fprintf(output,"<%s>", ProtoTypeName(proto));
    else
      fprintf(output,"%s", ProtoTypeName(proto));
  }
  fprintf(output," in %s\n", groupname);
  if (!SimpleDump){
    /* Print lowlevel info after standard info */
    proto=GETPROTO(obj);
    fprintf(output, "  { PC  0x%x", (int)PC);
    if (!SimpleDump) PrintCodeAddress(PC);
    fprintf(output, 
	    ", object 0x%x, proto 0x%x ",
	    (int)obj, 
	    (int)proto);
    PrintProto(proto); fprintf(output, " ");
    fprintf(output, "}\n");
    if (print_origin){
      /* Print Static Environment Object. */
      ObjectSurrounderDescription(obj, activeProto);
    }
  }
}

static void ObjectSurrounderDescription(Object *obj, 
					ProtoType *activeProto)
{
  long addr;
  Object      *staticObj;
  ProtoType   *proto=GETPROTO(obj);
  char        *groupname;
  
  if (!activeProto) activeProto = proto;
  if (!activeProto) return;
  addr=(long)obj + (4*(long)activeProto->OriginOff);
  if (addr) 
    staticObj = *(Object **)addr;
  else
    staticObj = 0;
  TRACE_DUMP(fprintf(output, ">>>TraceDump: staticObj=0x%x\n", (int)staticObj));
  if( isSpecialProtoType(GETPROTO(staticObj)) ){
    switch (SwitchProto(GETPROTO(staticObj))){
    case SwitchProto(ComponentPTValue):
      staticObj = (Object *) ComponentItem(obj);
      break;
    case SwitchProto(DopartObjectPTValue):
      staticObj = ((DopartObject *)staticObj)->Origin;
      break;
      
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
    case SwitchProto(StackObjectPTValue):
    case SwitchProto(ByteRepPTValue):
    case SwitchProto(ShortRepPTValue):
    case SwitchProto(DoubleRepPTValue):
    case SwitchProto(LongRepPTValue):
    case SwitchProto(RefRepPTValue):
      /* This is an error */
      fprintf(output,
	      "    -- Illegal surrounding object (0x%x) %s!\n",
	      (int)staticObj,
	      ProtoTypeName(GETPROTO(staticObj)));
      return;
    } 
  }
  if( staticObj && isObject( staticObj ) ){
    groupname = GroupName((long)GETPROTO(staticObj),0);
    if (groupname==NULL){
      fprintf(output,
	      "    -- Surrounding object (0x%x) damaged!\n",
	      (int)staticObj
	      );
      return;
    }
    proto = GETPROTO(staticObj);
    
    fprintf(output,"    -- ");
    fprintf(output,"%s", ProtoTypeName(proto));
    while(proto->Prefix &&
	  proto->Prefix->Prefix != proto->Prefix){
      proto = proto->Prefix;
      fprintf(output,"%s", ProtoTypeName(proto));
    }
    fprintf(output, " in %s\n", groupname);
    if (!SimpleDump) {
      /* Print lowlevel info after standard info */
      proto=GETPROTO(staticObj);
      fprintf(output, "    { Surrounding object 0x%x, proto 0x%x ", 
	      (int)staticObj, 
	      (int)proto);
      PrintProto(proto); fprintf(output, " ");
      fprintf(output, "}\n");
    }
  } else {
    if (staticObj){
      fprintf(output,
	      "    -- Surrounding object (0x%x) damaged!\n",
	      (int)staticObj
	      );
    } else {
      fprintf(output,
	      "    -- Surrounding object is zero!\n"
	      );
    }
  }
}

/********************** DisplayObject: ********************
 * Called by DisplayBetaStack and BetaError (in case of QuaCont)
 */

GLOBAL(static Object *lastDisplayedObject)=0;

void DisplayObject(FILE   *output, /* Where to dump object */
		   Object *obj,    /* Object to display */
		   long    PC      /* Address obj was left from (jsr), 
				    * i.e. when it was current object.
				    */
		   )
{ 
  Object * theItem;

  if (isMakingDump){
    /* Make an empty line after the last line of a component 
     * in dump file.
     */
    if (lastDisplayedObject &&
	((GETPROTO(lastDisplayedObject))==(ComponentPTValue)) 
	&& (lastDisplayedObject != obj)){
      fprintf(output, "\n"); fflush(output);
    }
  }

  if (!obj){
    fprintf(output, "  [NONE]\n");
    fflush(output);
    return;
  }
  if( isSpecialProtoType(GETPROTO(obj)) ){
    switch (SwitchProto(GETPROTO(obj))){
    case SwitchProto(ComponentPTValue):
      theItem = (Object *) ComponentItem(obj);
      if (theItem == (Object *) BasicItem) {
	if (!basic_dumped){
	  fprintf(output,
		  "  basic component in %s\n", 
		  GroupName((long)GETPROTO(theItem),0) );
	  if (isMakingDump) {
	    /* only dump basicitem once in dump file */
	    basic_dumped=1;
	  }
	}
      } else {
	ObjectDescription(theItem, PC, "comp", 1);
      }
      break;
    case SwitchProto(DopartObjectPTValue):
      theItem = ((DopartObject *)obj)->Origin;
      /* Check whether theItem is actually an item or is the
       * body part of a component.
       */
      if (!isComponent(theItem) 
	  && IsComponentItem(theItem)) {
	DisplayObject(output, 
		      (Object *)EnclosingComponent(theItem),
		      PC);
	return;
      } else {
	ObjectDescription(theItem, PC, "item", 1);
      }
      break;
    case SwitchProto(StructurePTValue):
      fprintf(output, "  strucobject\n");
    case SwitchProto(StackObjectPTValue):
      fprintf(output,"  stackobject\n");
      break;
    case SwitchProto(ByteRepPTValue):
      fprintf(output,"  ByteRep\n");
      break;
    case SwitchProto(ShortRepPTValue):
      fprintf(output,"  ShortRep\n");
      break;
    case SwitchProto(DoubleRepPTValue):
      fprintf(output,"  DoubleRep\n");
      break;
    case SwitchProto(LongRepPTValue):
      fprintf(output,"  ValRep\n");
      break;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      fprintf(output, "  ObjectRep\n"); 
      break;
    case SwitchProto(RefRepPTValue):
      fprintf(output,"  RefRep\n");
      break;
    } 
  }else{    
    ObjectDescription(obj, PC, "item", 1);
  }

  if (isMakingDump) lastDisplayedObject=obj;
}


/************************* Begin HPPA ****************************/
#ifdef hppa

void DisplayHPPAStack(long *thePC) 
{
  /* FIXME: Could possibly use ProcessHPPAStack with appropriate func */

#ifdef UseRefStack
  /*
   * The ReferenceStack way of tracing the Beta stack.
   */
  Object **theCell = /*getRefSP()*/ (Object **)(RefSP-1);
  Object *theObj;
  long   *PC=thePC;
  
  while((void **)theCell > &ReferenceStack[0]) {
    if ((*theCell)==(Object *)ExternalMarker){
      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
    } else if ((unsigned)*theCell & 1) {
      /* The reference is tagged: Should appear in beta.dump */
      theObj = (Object *)((unsigned)*theCell & ~1);
      PC = 0; /* No way to tell the PC ?? */
#if 0 /* not yet */
#ifdef RTVALHALLA
      theCell--;
      PC = (long *)*theCell
#endif
#endif
	if(theObj && isObject(theObj)) {
	  /* Check if theObj is inlined in a component */
	  if (!isComponent(theObj) && IsComponentItem(theObj)) {
	    DisplayObject(output, 
			  (Object *)EnclosingComponent(theObj), 
			  (long)PC);
	    if (theObj==(Object *)BasicItem) break;
	  } else {
	    DisplayObject(output, theObj, (long)PC);
	  }
	} else {
	  if (theObj) fprintf(output, "  [Damaged object!: %x]\n", (int)theObj);
	}
    }
    theCell--;
  }
  fflush(output);
#else
#error DisplayHPPAStack not implemented
#endif /* UseRefStack */
}

#endif /* hppa */
/*************************** End HPPA ****************************/

/*************************** Begin NEWRUN ***************************/
#ifdef NEWRUN
/*
 * This is the NEWRUN specifics of DisplayBetaStack
 */
static void DumpCell(Object **theCell, Object *theObj)
{ 
  register long PC=-1;
  long *SP;

  /* theObj is dyn in a frame. This is the current object in the 
   * previous frame. 
   */

  TRACE_DUMP({
    fprintf(output, 
	    ">>>TraceDump: theCell=0x%x, theObj=0x%x",
	    (int)theCell, 
	    (int)theObj);
  });

  /* First check if theObj is CALLBACKMARK */
  if ((theObj==CALLBACKMARK)||(theObj==GENMARK)){
    SP = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
    PC = *((long *)SP+PC_OFF);
    if (theObj==CALLBACKMARK){
      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf(output, 
	      "  [ EXTERNAL ACTIVATION PART (address 0x%x", 
	      (int)PC);
      if (!SimpleDump) PrintCodeAddress((long)PC);
      fprintf(output, ") ]\n");
    } else {
      TRACE_DUMP(fprintf(output, "  allo: "));
    }
    /* Since ProcessStackFrames now skips to previous frame before
     * BETA called C, we will not see the current object in the
     * frame before C as a dyn-pointer in any frame (it is hidden
     * by this CALLBACKMARK).
     * So we have to go to this previous frame ourselves and
     * find the current object for that frame and dump it.
     * See figure in stack.c.
     */
    SP = (long*)GetSPbeta(SP);	 /* SP-beta */
    if (SP==0){
      /* We passed the main+CallB frames */
      return;
    }
    theObj = GetThis(SP);
    PC = 0;			 /* not known - is somewhere in the C frames */
  }
    
  /* Check if theObj IS a component */
  if (theObj && (GETPROTO(theObj)==ComponentPTValue)){
    TRACE_DUMP(fprintf(output, " is comp - getting real dyn"));
    /* Passing a component frame. The real dyn is found 
     * as theComp->CallerObj - see stack.c for details.
     */
    PC = ((Component *)theObj)->CallerComp->CallerLSC;
    theObj = ((Component *)theObj)->CallerObj;
  } 
    
  /* Check if theObj is inlined in a component */
  if (!isComponent(theObj) && IsComponentItem(theObj)) {
    TRACE_DUMP(fprintf(output, " dump as comp"));
    theObj = (Object *)EnclosingComponent(theObj);
  } 
    
  if (PC==-1){
    SP = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
    PC = *((long *)SP+PC_OFF);
  }

  TRACE_DUMP(fprintf(output, ", PC=0x%x *\n", (int)PC));
  DisplayObject(output, theObj, PC);
}

void DisplayNEWRUNStack(long *PC, Object *theObj, int signal)
{ 

  /* First check for errors occured outside BETA */
  if (!IsBetaCodeAddrOfProcess((long)PC)){
    long *betatop = BetaStackTop[0];
    fprintf(output, 
	    "  [ EXTERNAL ACTIVATION PART (address 0x%x", 
	    (int)PC);
    if (!SimpleDump) PrintCodeAddress((long)error_pc);
    fprintf(output, ") ]\n");
    
    /* 
     * Adjust StackEnd to BETA part of stack, if possible.
     */
#ifdef ppcmac
    /* FIXME: could wind down through frame pointers */
#endif /* ppcmac */
#ifdef sgi
    if ((StackEnd<betatop) && (betatop<StackStart)){
      /* BetaStackTop is in the active stack. Try continuing from there.
       * This will work if BETA called a C routine, but not if the error
       * occurred in a runtime routine - BetaStackTop is not set, when
       * runtime routines are called.
       */
      TRACE_DUMP(fprintf(output, "  Adjusting StackEnd to BetaStackTop\n"));
      StackEnd = betatop;
      /* Unfortunately the BetaStackTop points to the next-to-top-entry on 
       * the stack (for other reasons). The topmost BETA object can be found
       * as the saved THIS in the frame just above SP but we cannot figure
       * out the PC, at this is saved somewhere in the C frames.
       */
      DisplayObject(output, GetThis(StackEnd), 0);
    } else {
       /* In low level dump StackEnd will be equal to betatop since the
	* above code has just been performed for the simple dump.
	*/ 
      if (StackEnd==betatop){
	/* Low level dump - dump topmost object here too */
	DisplayObject(output, GetThis(StackEnd), 0);
      } else {
	fprintf(output, "\n");
	fprintf(output, "  (Unable to find start of BETA stack - sorry)\n");
	BetaExit(1);
      }
    }
#endif /* sgi */
  }

  /* Dump the stack */
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, DumpCell);
}

#endif /* NEWRUN */
/************************* End NEWRUN ***************************/

/************************* Begin INTEL ****************************/
#ifdef intel

static Object *prevObj=0;
static CellDisplayFunc displayFunc=0;

static void objectMet(Object **theCell, Object *theObj)
{
  if ((!inBetaHeap(*(theCell+1))) && IsBetaCodeAddrOfProcess((long)*(theCell+1))){
    /* Found an object with a PC just below it on stack */
    prevObj = theObj;
    TRACE_DUMP(fprintf(output,"new prevObj: "); DescribeObject(prevObj));
    if (!isComponent(prevObj) && IsComponentItem(prevObj)){
      prevObj = (Object*)EnclosingComponent(prevObj);
      TRACE_DUMP({
	fprintf(output, 
		" is item of component 0x%x\n", 
		(int)prevObj);
      });
    }
    TRACE_DUMP(fprintf(output, "\n"));
  } else {
    /* Probably a pushed register */
    TRACE_DUMP(fprintf(output, "(object with no PC below)\n"));
  }
}

static void nonObjectMet(Object **theCell, Object *theObj)
{
  if (IsBetaCodeAddrOfProcess((long)theObj)){
    /* Found a BETA PC */
    long PC=(long)theObj;
    TRACE_DUMP(PrintCodeAddress(PC));
    if (prevObj){
      TRACE_DUMP(fprintf(output, "\n"));
      displayFunc(PC, prevObj);
    } else {
      TRACE_DUMP(fprintf(output, " (no prevObj)"));
    }
  }
}

/* DisplayStackPart:
 * Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
void DisplayStackPart(long *low, 
		      long *high,
		      Object *currentObject,
		      CellDisplayFunc func)
{
  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackPart [0x%x..0x%x]\n", (int)low, (int)high));
  prevObj = currentObject;
  TRACE_DUMP({
    fprintf(output, ">>>TraceDump: Initial prevObj: "); 
    DescribeObject(prevObj); fprintf(output, "\n");
  });
  if (prevObj && !isComponent(prevObj) && IsComponentItem(prevObj)){
    prevObj = (Object*)EnclosingComponent(prevObj);
    TRACE_DUMP(fprintf(output, " is item of component 0x%x\n", (int)prevObj));
  }  
  displayFunc = func;
  ProcessStackPart(low, high, objectMet, nonObjectMet);
  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackPart done.\n"));
}

long *DisplayCallbackFrames(CallBackFrame *cbFrame,
			    long *low,
			    Object *currentObject,
			    CellDisplayFunc func)
{
  TRACE_DUMP({
    fprintf(output, 
	    ">>>DisplayCallbackFrames: cbFrame: 0x%x, low: 0x%x\n", 
	    (int)cbFrame,
	    (int)low);
  });
  while (cbFrame) {
    DisplayStackPart(low, (long *)cbFrame-2, currentObject, func);
    /* -2 because 2 longs are not shown:
     *    1. The last of the three pushed words in the callback frame
     *    2. The address of the call back stub.
     */
    TRACE_DUMP(fprintf(output, "  cb: "));
    if (isMakingDump){
      /* beta.dump */
      fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n"); 
    } else {
      /* valhalla? */
    }
    low = cbFrame->betaTop;
    low += 3;
    /* low+3 because the compiler pushes %edx, %edi, %ebp, %esi
     * before setting BetaStackTop.
     * Of these we only want to see %edx (current object).
     */
    cbFrame = cbFrame->next;
    if (isObject((Object *)(*low))) {
      Object *obj = (Object*)(*low);
      TRACE_DUMP({
	fprintf(output, 
		">>>DisplayCallbackFrames: low: 0x%x: 0x%x ", (int)low, (int)obj);
	DescribeObject(obj);
	fprintf(output, "\n"); 
      });
      if (!isComponent(obj) && IsComponentItem(obj)){
	  obj = (Object*)EnclosingComponent(obj);
	  TRACE_DUMP({
	    fprintf(output, " is item of component 0x%x\n", (int)obj);
	  });
      }
      TRACE_DUMP({ fprintf(output, ">>>DisplayCallbackFrames: func(0, obj)\n");});
      func(0, obj); /* PC=0 since we cannot easily determine where the PC is
		     * saved when the external was called: BetaStackTop was set before 
		     * arguments to the external were pushed. So if we were to
		     * figure out where the PC was saved, we need to know how many 
		     * arguments the external has.
		     */
    }
    low += 1; /* Skip the object */
    TRACE_DUMP({
      fprintf(output, 
	      ">>>DisplayCallbackFrames: cbFrame: 0x%x, low: 0x%x\n", 
	      (int)cbFrame,
	      (int)low);
    });
  }
  TRACE_DUMP({
    fprintf(output, 
	    ">>>DisplayCallbackFrames: returning low: 0x%x\n",
	    (int)low);
  });
  return low;
}

void DisplayINTELStack(BetaErr errorNumber, 
		       Object *currentObject, 
		       long PC, 
		       long theSignal /* theSignal is zero if not applicable. */
		       )
{ 

  /* FIXME: Could possibly use ProcessINTELStack with appropriate func */
  Component       *currentComponent = ActiveComponent;
  long            *low              = (long *) StackEnd;
  long            *high             = (long *) lastCompBlock;
  CallBackFrame   *cbFrame          = ActiveCallBackFrame; 
  ComponentBlock  *currentBlock;

  /*
   * Handle the topmost component block, designated by 
   * StackEnd, ActiveCallbackFrame and lastCompBlock.
   */

  /* First check for errors occured outside BETA */
  if (!IsBetaCodeAddrOfProcess(PC)){
    fprintf(output, 
	    "  [ EXTERNAL ACTIVATION PART (address 0x%x",
	    (int)error_pc
	    );
    if (!SimpleDump) PrintCodeAddress((long)PC);
    fprintf(output, ") ]\n");
    if ((StackEnd<BetaStackTop) && (BetaStackTop<(long*)StackStart)){
      /* BetaStackTop is in the active stack. Try continuing from there.
       * This will work if BETA called a C routine, but not if the error
       * occurred in a runtime routine - BetaStackTop is not set, when
       * runtime routines are called.
       * This might also fail if we are returning from a callback chain,
       * since BetaStackTop is not adjusted as we pop off callback frames.
       * Should be handled, though, by the requirement that BetaStackTop 
       * must be between StackStart and StackEnd.
       */
      low = BetaStackTop;
      TRACE_DUMP({
	fprintf(output, 
		">>>DisplayINTELStack: adjusting low to BetaStackTop: 0x%x\n",
		(int)BetaStackTop);
      });
    }
    /* The PC corresponding to the BETA object that called C is just 
     * above BetaStackTop.
     * NO: First comes the arguments for the external.
     * Here we cannot determine how many of these there are.
     */
    /* PC = *(BetaStackTop-1); */

    /* Adjust low to low+3 because the compiler pushes %edx, %edi, %ebp, %esi
     * before setting BetaStackTop.
     * Of these we only want to see %edx (current object).
     */
    low += 3;

    /* Since a new prevObj will be met by DisplayStackPart before 
     * any other PC corresponding to currentObject, the current object that
     * called C will not be displayed by DisplayStackPart.
     * So we display it here.
     */
    TRACE_DUMP(fprintf(output, "Displaying current object\n"));
    DisplayObject(output, currentObject, 0 /*PC*/);

  }

  if (cbFrame){
    /* Display callbackframes in the component */
    low = DisplayCallbackFrames(cbFrame, low, currentObject, DisplayCell);
  }

  /* Displays the objects from where the last callback was initiated
   * (if any) and onwards to the ComponentBlock.
   */
  DisplayStackPart(low, high-3, currentObject, DisplayCell);  
  /* -3 because 3 longs are not shown: 
   *    1. The last of the three pushed words in the comp block
   *    2. The address of the M-part for the component.
   *    3. The current object saved by the M-part.
   */
  
  /*
   * Then handle the remaining component blocks designated by the linked
   * list of ComponentBlocks from lastCompBlock and onwards.
   */
  currentBlock     = lastCompBlock;
  currentObject    = currentComponent->CallerObj;
  PC               = currentComponent->CallerLSC;
  currentComponent = currentComponent->CallerComp;
  
  while (currentBlock->next){
    low  = (long *)((long)currentBlock+sizeof(ComponentBlock))+1
      /* +1 because the compiler always pushes the component before calling
       * attach.
       */;
    high = (long *) currentBlock->next;
    cbFrame  = currentBlock->callBackFrame;
    
    /* Display current object in ComponentBlock */
    if (cbFrame){
      /* Current object will be shown along with the first CB frame */
      TRACE_DUMP(fprintf(output, ">>>TraceDump: current: 0x%x\n", (int)currentObject));
    } else {
      if (!isComponent(currentObject) && IsComponentItem(currentObject)){
	DisplayObject(output, (Object*)EnclosingComponent(currentObject), PC);
      } else {
	DisplayObject(output, currentObject, PC);
      }
    }

    if (cbFrame){
      /* Display callbackframes in the component */
      low = DisplayCallbackFrames(cbFrame, low, currentObject, DisplayCell);
    }
    
    /* Displays the objects from where the last callback was initiated
     * (if any) and onwards to the ComponentBlock.
     */
    DisplayStackPart(low, high-3, currentObject, DisplayCell); 
    /* -3 because:
     *  3 longs are not shown: 
     *    1. The last of the three pushed words in the comp block
     *    2. The address of the M-part for the component.
     *    3. The current object saved by the M-part.
     */

    currentBlock     = currentBlock->next;
    currentObject    = currentComponent->CallerObj;
    PC               = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
  }
}
#endif /* intel */
/***************************** End INTEL **********************************/

/*************************** Begin SPARC ******************************/
#ifdef sparc

/*
 * This is the SPARC specifics of DisplayBetaStack
 */

void DisplayAR(RegWin *theAR, long PC, CellDisplayFunc func)
{
  Object *prevObj /* used for last successfully identified object */;

  TRACE_DUMP({
    fprintf(output, 
	    "\n\n>>>TraceDump: DisplayAR: [%%sp=0x%x..%%fp=0x%x[, %%i0: 0x%x, PC: 0x%x", 
	    (int)theAR, 
	    (int)theAR->fp, 
	    (int)theAR->i0, 
	    (int)PC);
    if (!SimpleDump) PrintCodeAddress(PC);
    fprintf(output, "\n");
  });

  /* Handle current object in this frame */
  prevObj  = (Object *) theAR->i0;
  if (inBetaHeap(prevObj) && isObject(prevObj)){
    if (!isComponent(prevObj) && IsComponentItem(prevObj)){
      prevObj = (Object*)EnclosingComponent(prevObj);
      TRACE_DUMP({
	fprintf(output, 
		">>>TraceDump: DisplayAR: Current object is item of component 0x%x\n", 
		(int)prevObj);
      });
    } 
    func(PC, prevObj);
  }

  TraverseSparcStackPart(theAR, prevObj, func);
  
}

void TraverseSparcStackPart(RegWin *theAR, Object* prevObj, CellDisplayFunc func)
{

  long* this, *end;
  long PC;

  /* handle possible pushed PCs (%o7s) in the
   * stackpart (INNER call chains).
   * In case of INNER P, the previous current object has been
   * pushed before the code address.
   */
  this = (long *) (((long)theAR)+sizeof(RegWin));
  end  = (long *) (((long)theAR->fp));
  TRACE_DUMP({
    if (this<end){
      fprintf(output, 
	      ">>>TraceDump: DisplayAR: stackpart is [0x%x..0x%x[\n", 
	      (int)this, 
	      (int)end);
    } else {
      fprintf(output, 
	      ">>>TraceDump: DisplayAR: no stackpart (this=0x%x, end=0x%x)\n",
	      (int)this,
	      (int)end);
    }
  });
  while (this<end) {
    TRACE_DUMP({
      fprintf(output, 
	      ">>>TraceDump: DisplayAR: stackpart 0x%08x: 0x%08x\n", 
	      (int)this, 
	      (int)this[0]);
    });

    /* Test for floating point regs on stack. See comment in ProcessAR */
    {
      int tag = (int)*this;
      if ( (-(2*16+4)<=tag) && (tag<=-4) ){
	DEBUG_CODE({
	  fprintf(output, 
		  "Skipping %d saved floating points regs.\n", 
		  (-tag-4)/2);
	});
	if ( (int)(this+(-tag-4)) >= (int)(theAR->fp) ){
	  /* Skip would be out of frame */
	  DEBUG_CODE({
	    fprintf(output, 
		    "NO: not skipping anyway: skip would be out of frame!.\n");
	  });
	} else {
	  this += -tag-4;
	}
      }
    }

    PC = this[0];
    if (isCode(PC)) {
      /* isCode is a real macro on sparc. So now we know that
       * a code address has been pushes in the stack part.
       * Add 8 to get the real SPARC return address.
       */
      PC+=8;
      TRACE_DUMP({
	fprintf(output, 
		">>>TraceDump: DisplayAR: PC 0x%x\n",
		(int)PC);
      });
      if ((this+2<end) && inBetaHeap((Object*)this[2]) && isObject((Object*)this[2])) {
	/* There was an object, assumed to be from an INNER P */
	prevObj = (Object*)this[2];
	TRACE_DUMP({
	  fprintf(output, 
		  ">>>TraceDump: DisplayAR: stackpart 0x%08x: 0x%08x INNER P object\n", 
		  (int)(this+2), 
		  (int)prevObj);
	});
	if (!isComponent(prevObj) && IsComponentItem(prevObj)){
	  prevObj = (Object*)EnclosingComponent(prevObj);
	  TRACE_DUMP({
	    fprintf(output,
		    ">>>TraceDump: DisplayAR: object is item of component 0x%x\n",
		    (int)prevObj);
	  });
	} 
	func(PC, prevObj);
	this+=2; /* Skip the object */
      } else {
	/* No Object below the code. Display with the previous
	 * found object.
	 */
	func(PC, prevObj);
      }
    }
    this+=2;
  }
}

void DisplaySPARCStack(BetaErr errorNumber, 
		       Object *theObj, 
		       long *thePC, 
		       long theSignal)
{
  /* FIXME: Could possibly use ProcessSPARCStack with suitable CellProcessFunc */
  RegWin *theAR;
  RegWin *nextCBF = (RegWin *) ActiveCallBackFrame;
  RegWin *nextCompBlock = (RegWin *) lastCompBlock;
  long   *PC=thePC;
  
  /* Flush register windows to stack */
  __asm__("ta 3");

  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackEnd:   0x%x\n", (int)StackEnd));
  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackStart: 0x%x\n", (int)StackStart));

  theAR = (RegWin *) StackEnd;

  /* First check for errors occured outside BETA and wind down
   * to BETA part of stack, if possible.
   */
  if (!IsBetaCodeAddrOfProcess((long)PC)){
    fprintf(output, 
	    "  [ EXTERNAL ACTIVATION PART (address 0x%x", 
	    (int)PC);
    if (!SimpleDump) PrintCodeAddress((long)error_pc);
    fprintf(output, ") ]\n");

    TRACE_DUMP(fprintf(output, "  Winding back through C frames on top\n"));
    for (PC = (long *)theAR->i7, theAR = (RegWin *) theAR->fp;
	 !IsBetaCodeAddrOfProcess((long)PC);
	 PC = (long *)theAR->i7, theAR = (RegWin *) theAR->fp){
      if (!SimpleDump) {
	fprintf(output, "  { PC  0x%x", (int)PC);
	if (!SimpleDump) PrintCodeAddress((int)PC);
	fprintf(output, " }\n");
      }
      if ((theAR->fp==0) || (theAR->fp==StackStart) || (PC = 0)){
	TRACE_DUMP({
	  fprintf(output, 
		  "Wierd: Did not find any BETA frames... At theAR=0x%x\n",
		  (int)theAR);
	});
	return;
      }
    }
    TRACE_DUMP(fprintf(output, "  Winding through frames on top done."));
  }

  for (;
       theAR != (RegWin *) 0;
       PC = (long*)theAR->i7, theAR =  (RegWin *) theAR->fp) {
    /* PC is execution point in THIS frame. The update of PC
     * in the for-loop is not done until it is restarted.
     */
    TRACE_DUMP(fprintf(output, ">>>TraceDump: DisplaySPARCStack: theAR->fp: 0x%x\n", (int)theAR->fp));
    if (theAR->fp == (long)nextCBF) {
      /* This is AR of the code stub (e.g. <foo>) called from HandleCB. 
       * Don't display objects in this, but skip to betaTop and update 
       * nextCBF 
       */
      RegWin *cAR;

      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
      /* Wind down the stack until betaTop is reached.
       * This is only done to update PC in order to get the PC
       * for the first frame before the callback.
       */
      TRACE_DUMP(fprintf(output, 
			 "  Winding back to 0x%x", 
			 (int)((RegWin *)theAR->fp)->l6
			 ));
      for (cAR = theAR;
	   cAR != (RegWin *)((RegWin *)theAR->fp)->l6;
	   PC = (long *)cAR->i7, cAR = (RegWin *) cAR->fp){
	if (!SimpleDump) {
	  fprintf(output, "  { PC  0x%x", (int)PC);
	  PrintCodeAddress((int)PC);
	  fprintf(output, " }\n");
	}
      }
      nextCBF = (RegWin*) ((RegWin*)(theAR->fp))->l5;
      theAR   = (RegWin*) ((RegWin*)(theAR->fp))->l6;
      TRACE_DUMP(fprintf(output, "  Winding done."));
    }
    if (theAR == nextCompBlock) {
      /* This is the AR of attach. Continue, but get
       * new values for nextCompBlock and nextCBF. 
       * Please read StackLayout.doc
       */
      nextCBF = (RegWin *) theAR->l5;
      nextCompBlock = (RegWin *) theAR->l6;
      
      if (nextCompBlock == 0){ 
	/* We reached the bottom */
	TRACE_DUMP({
	  fprintf(output, 
		  ">>>TraceDump: reached frame of AttBC at SP=0x%x\n", 
		  (int)theAR);
	});
	break;
      }
      
      TRACE_DUMP({
	fprintf(output, 
		">>>TraceDump: reached frame of Att at SP=0x%x\n", 
		(int)theAR);
      });
      continue;
    } 
    /* Normal frame */
    DisplayAR(theAR, (long)PC, DisplayCell);
  }
  return;
}

#endif /* sparc */
/*************************** End SPARC ******************************/

/********************** DisplayCurrentObject ************/

#ifndef sparc
void DisplayCurrentObject(Object *theObj, long *thePC)
{
  TRACE_DUMP(fprintf(output, ">>>TraceDump: Current object 0x%x\n", (int)theObj));
  if( theObj != 0 ){
    if( isObject(theObj)){
      if (theObj==(Object *)ActiveComponent->Body){
	DisplayObject(output, (Object *)ActiveComponent, (long)thePC);
      } else {
	DisplayObject(output, theObj, (long)thePC);
      }
    } else {
      fprintf(output,
	      "  Current object (0x%x) is damaged",
	      (int)theObj
	      );
      DEBUG_CODE(PrintWhichHeap(theObj));
      fprintf(output, "\n");
      fflush(output);
#if 1
      DEBUG_CODE({
	extern int isObjectState;
	if (inBetaHeap(theObj)){
	  fprintf(output, "    proto: 0x%x\n", (int)GETPROTO(theObj));
	  fflush(output);
	  fprintf(output, "    gc:    0x%x\n", (int)theObj->GCAttr);
	  fflush(output);
	}
	fprintf(output, "  isObjectState: %d\n", isObjectState);
	fflush(output);
      });
#endif
      
    }
  } else {
    fprintf(output,"Current object is zero!\n");
  }
}
#endif /* sparc */

/********************** OpenDumpFile: ********************/

#ifdef UNIX
static int OpenDumpFile(long errorNumber)
{
  char dumpname[500];
  char dirCh;
  char *execname, *localname;

  dirCh = '/';
  execname = ArgVector[0];
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;
  strcpy(dumpname, localname);
  strcat(dumpname, ".dump");
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened - use stderr */
    output = stderr;
    fprintf(output, "\n# Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
    fprintf(output, "# Generating dump.  This may take a little while - please be patient\n");
    fflush(output);
  } else {
    /* beta.dump opened successfully */
    fprintf(stderr, "\n# Beta execution aborted: ");
    fprintf(stderr, ErrorMessage(errorNumber));
    fprintf(stderr, ".\n# Look at '%s'\n", dumpname);
    fprintf(stderr, "# Generating dump file.  This may take a little while - please be patient\n");
    fflush(stderr);
    /* Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
    fflush(output);
  }
  return 1;
}
#endif /* UNIX */

#if defined(MAC)
GLOBAL(static char dumpname[33]); /* max filename length is 32 */
static int OpenDumpFile(long errorNumber)
{
  char dirCh;
  char *execname, *localname;
  char lookat[100];
  int locallen;

  dirCh = ':';
  execname = ArgVector[0]; /* Always right ??? */
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;

  locallen = strlen(localname);
  if (locallen>27){
    strncpy(dumpname, localname, 27); /* allow for ".dump" */
    dumpname[27] = 0;
  } else {
    strcpy(dumpname, localname);
  }
  strcat(dumpname, ".dump");
  
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened */
    if (StandAlone){
      /* macintosh, failed to open dump file: running as standalone appl */
      int i=2;
      char extension[10];
      do {
	/* Construct xxxxx.dumpNNN name taking max filename 
	 * length into account.
	 */
	if (i<10){
	  if (locallen>26){
	    strncpy(dumpname, localname, 26); /* allow for ".dumpN" */
	    dumpname[26] = 0;
	  } else {
	    strcpy(dumpname, localname);
	  }
	} else if (i<100) {
	  if (locallen>25){
	    strncpy(dumpname, localname, 25); /* allow for ".dumpNN" */
	    dumpname[25]=0;
	  } else {
	    strcpy(dumpname, localname);
	  }
	} else {
	  if (locallen>24){
	    strncpy(dumpname, localname, 24); /* allow for ".dumpNNN" */
	    dumpname[24]=0;
	  } else {
	    strcpy(dumpname, localname);
	  }
	}
	sprintf(extension, "dump%d", i++);
	strcat(dumpname, extension);
      } while (((output = fopen(dumpname,"w")) == NULL) && (i<1000));
      if (i==1000){
	/* Failed to open dump1, dump2, ... dump999 */
	strncpy(dumpname, localname, 27); /* allow for ".dump" */
	strcat(dumpname, ".dump");
	sprintf(lookat, "\n\nFailed to open '%s'", dumpname);
	CPrompt("Beta execution aborted:\n\n", 
		ErrorMessage(errorNumber), 
		lookat, 
		"");
	return 0;
      } else {
	sprintf(lookat, "\n\nLook at '%s'", dumpname);
	CPrompt("Beta execution aborted:\n\n", 
		ErrorMessage(errorNumber), 
		lookat, 
		"");
      }
    } else {
      /* macintosh, failed to open dump file: running as tool under MPW */
      output = stderr;
      fprintf(output, "\n# Beta execution aborted: ");
      fprintf(output, ErrorMessage(errorNumber));
      fprintf(output, ".\n");
    }
  } else {
    /* beta.dump opened successfully */
    if (StandAlone){
      /* macintosh, dump file opened OK: running as stand alone application */
      char *lookat;
      lookat = MALLOC(strlen(dumpname)+12);
      sprintf(lookat, "\n\nLook at '%s'", dumpname);
      CPrompt("Beta execution aborted:\n\n", 
	      ErrorMessage(errorNumber), 
	      lookat, 
	      "");
    } else {
      /* macintosh, dump file opened OK: running as tool under MPW */
      fprintf(stderr, "\n# Beta execution aborted: ");
      fprintf(stderr, ErrorMessage(errorNumber));
      fprintf(stderr, ".\nFile \"%s\"; Line 1\n", dumpname);
    }
    /* Dump file opened OK: Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
  }
  return 1;
}
#endif /* mac */

#ifdef nti
static char *OpenDumpFile(long errorNumber)
{
  GLOBAL(static char dumpname[500]);
  char dirCh;
  char *execname, *localname;

  dirCh = '\\';
  execname = ArgVector[0];
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;
  strcpy(dumpname, localname);
  { /* If a '.' is present overwrite it and what follows */
    char *exetype = strrchr(dumpname, '.');
    char *pathsep = strrchr(dumpname, dirCh);
    /* If local name is 1 or 2 overwrite extension. Case 3 appends extension.
     * 1. D:\USERS\BETA\TEST.EXE   => D:\USERS\BETA\TEST.DUMP
     * 2. BETA.EXE                 => BETA.DUMP
     * 3. D:\USERS\BETA\V1.0\TEST  => not D:\USERS\BETA\V1.DUMP
     *                             => but D:\USERS\BETA\V1.0\TEST.DUMP
     * FIXME: this means that foo.bar.exe run as "foo.bar" yields
     * a dump file named foo.dump.
     * Use function EqualNCS as in initLabels in misc.c instead.
     */
    if (exetype && (!pathsep || pathsep < exetype))
      strcpy(exetype, ".dump");
    else
      strcat(dumpname, ".dump");
  }
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened */
    { sprintf(NotifyMessage,
	      "\nBeta execution aborted: %s.\nFailed to open '%s'",
              ErrorMessage(errorNumber),
	      dumpname);
      return 0;
    }
  } else {
    /* beta.dump opened successfully */
    { sprintf(NotifyMessage,
	      "\nBeta execution aborted: %s.\nLook at '%s'",
              ErrorMessage(errorNumber), dumpname);
    }
    /* Dump file opened OK: Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
  }
  return dumpname;
}
#endif /* nti */

static void DisplayCurrentObjectAndStack(BetaErr errorNumber, 
					 Object *theObj, 
					 long *thePC, 
					 long theSignal /* theSignal is zero if not applicable. */
					 )
{
#ifndef sparc
  /* If we are able to retrieve information about the current object
   * dump it.
   * On the sparc, it resides in the top register window, and 
   * nothing should be done.
   */
  DisplayCurrentObject(theObj, thePC);
#endif /* sparc */

#ifdef MT
  fprintf(output, "DisplayCurrentObjectAndStack: NYI for MT\n"); 
  fflush(output);
  return
#endif

  if (StackStart == 0){
    fprintf(output,"\n  [initialization of basic component]\n");
    return;
  }
 
#ifdef hppa
  DisplayHPPAStack(thePC);
#endif
#ifdef NEWRUN
  DisplayNEWRUNStack(thePC, theObj, theSignal);
#endif
#ifdef sparc
  DisplaySPARCStack(errorNumber, theObj, thePC, theSignal);
#endif
#ifdef intel
  DisplayINTELStack(errorNumber, theObj, (long)thePC, theSignal);
#endif
}

static void AuxInfo(Object *theObj, BetaErr errorNumber)
{
  /******** Additional info for some error types **************/
  switch (errorNumber){
  case IOAFullErr:
    if (4*(long)ReqObjectSize>(long)IOASize){
      char buf[100];
      fprintf(output, 
	      "\nRequested object size (%d bytes) is larger than\n", 
	      4*(int)ReqObjectSize);
      fprintf(output, "IOA heap size (%d Kb).\n", (int)IOASize/1024);
      fprintf(output, "Try increasing IOA size using BETART:\n");
      if (4*(long)ReqObjectSize>2*(long)IOASize){
	sprintf(buf, "IOA=%d", (4*(int)ReqObjectSize+1023)/1024);
      } else {
	sprintf(buf, "IOA=%d", 2*(int)IOASize/1024);
      }
      print_setenv("BETART", buf);
      fprintf(output, "\n");
    }
    break;
  case QuaErr:
    fprintf(output, "\nReference being assigned:\n");
    DisplayObject(output, QuaSrc, 0);
    fprintf(output, "\n");
    fprintf(output, "Required qualification:\n  ");
    PrintProto(QuaDstProto);
    fprintf(output, "\n");
    break;
  case RepHighRangeErr:
  case RepLowRangeErr:
    fprintf(output, "\nSubRange: [%d:%d]; range: [1:%d]\n", SubRangeErrLow, SubRangeErrHigh, RangeMax);
    break;
  case StopCalledErr:
    if (theObj){
      /* Stop object has integer and then text reference */
      TextObject *msg = *(TextObject **)((long *)theObj+4);
      if (msg && GETPROTO(msg) == TextProto){
	fprintf(output, 
		"\nStop message:\n  \"%s\"\n",
		(char*)(msg->T->Body));
	fflush(output);
      }
    }
  default:
    break;
  }
}

/**************** DisplayBetaStack: *******************/

/* If DisplayBetaStack returns non-zero, the debugger was invoked, and
 * the process should continue execution. */

int DisplayBetaStack(BetaErr errorNumber, 
		     Object *theObj, 
		     long *thePC, 
		     long theSignal /* theSignal is zero if not applicable. */
		     )
{
  FILE *old_output=0;

  DEBUG_CODE({
    fprintf(output, "\n");
    fprintf(output, "DisplayBetaStack(errorNumber=%d", errorNumber);
    PrintBetaError(errorNumber); fprintf(output, ",\n");
    fprintf(output, "                 theObj=0x%x ", (int)theObj);
    DescribeObject(theObj);
    fprintf(output, ",\n");
    fprintf(output, "                 thePC=0x%x", (int)thePC);
    PrintCodeAddress((int)thePC); fprintf(output, ",\n");
    fprintf(output, "                 theSignal=%d", (int)theSignal);
    PrintSignal((int)theSignal);
    fprintf(output, ")\n");
    fflush(output);
  });

#ifdef UseRefStack
#define STACKEND RefSP
#else
#define STACKEND StackEnd
#endif

#ifndef MT
  TRACE_DUMP(fprintf(output, "StackEnd=0x%x, StackStart=0x%x\n", 
		     (int)STACKEND, 
		     (int)StackStart
		     ));

  if (isMakingDump){
    /* Something went wrong during the dump. Stop here! */
    if (((BetaErr)isMakingDump == errorNumber) && theSignal){
      errorNumber = SignalErr;
    };
    NotifyErrorDuringDump((BetaErr)isMakingDump, errorNumber);
    BetaExit(1);
  } else {
    isMakingDump=(int)errorNumber;
  }
  
#ifdef NEWRUN
  /* If a signal was the reason program stopped, the NEWRUN
   * stack pointer should be adjusted to point to second topmost frame.
   */
  if (theSignal){
    if (IsBetaCodeAddrOfProcess((long)thePC)){ 
      DEBUG_CODE(fprintf(output, "DisplayBetaStack: Adjusting StackEnd\n"));
      StackEnd = (long*)WindBackSP((long)StackEndAtSignal, theObj, (long)thePC);
      DEBUG_CODE({
	fprintf(output, 
		"DisplayBetaStack: "
		"Adjusted StackEnd from 0x%08x to 0x%08x\n", 
		(int)StackEndAtSignal,
		(int)StackEnd);
      });
    } else {
      DEBUG_CODE({
	fprintf(output, "DisplayBetaStack: Signal in external code: Not adjusting StackEnd.\n");
	fflush(output);
      });
    }
  }
#endif /* NEWRUN */

#ifdef RTVALHALLA
  if (valhallaID){
    DEBUG_VALHALLA({
      fprintf(output, 
	      "DisplayBetaStack: "
	      "calling ValhallaOnProcessStop"
	      "(PC=0x%x, SP=0x%x, Object=0x%x, signal=0x%x, err=%d\n",
	      (int)thePC,
	      (int)STACKEND,
	      (int)theObj,
	      (int)theSignal,
	      (int)errorNumber
	      );
    });
    switch(ValhallaOnProcessStop(thePC,STACKEND,theObj,theSignal,errorNumber)){
    case CONTINUE: 
      /* Do not create dump file and terminate */
      DEBUG_VALHALLA(fprintf(output, "DisplayBetaStack: returning after ValhallaOnProcessStop\n"));
      isMakingDump = 0;
      return 1;
    case TERMINATE: 
      /* Go through with the dump and eventually terminate */
      DEBUG_VALHALLA(fprintf(output, "DisplayBetaStack: breaking out of switch after ValhallaOnProcessStop\n"));
      break;
    }
  } else {
    /*DEBUG_CODE(fprintf(output, "DisplayBetaStack: valhallaID is 0\n"));*/
  }
#else
  if (theSignal) theSignal = 0; 
  /* Just to avoid a compiler warning if RTVALHALLA is not defined. */ 
#endif /* RTVALHALLA */
#endif /* MT */
  
  /* Handle systemexceptions: see TST/tstprogram.bet */
  if (systemexceptionhandler){
    if (errorNumber==StopCalledErr){
      DEBUG_CODE(fprintf(output, "RTS: ignoring systemexceptionhandler for StopCalled\n"));
    } else {
      int skip_dump;
      int old_isMakingDump = isMakingDump;
      DEBUG_CODE(fprintf(output, "DisplayBetaStack: calling systemexceptionhandler\n"));
      /* FIXME: Save registers etc. as described in
       * http://www.daimi.au.dk/~beta/doc/betarun/internal/trapcallbacks.html
       * Cannot use BetaCallBack (rtsignalhandler.h) since we do not
       * have a signal context here!!! Not always? Index Errors, for instance.
       * Is now partly fixed: For (some) errors coming from signals, the valhalla
       * solution is now used.
       */
      set_BetaStackTop(StackEnd);
      isMakingDump = 0; /* In case the user leaves the handler */
      skip_dump = systemexceptionhandler(errorNumber, theObj, thePC, StackEnd);
      isMakingDump = old_isMakingDump;
      /* FIXME: Restore registers */
      if (skip_dump) {
	isMakingDump = 0;
	return 0;
      }
    }
  }

  error_pc = (unsigned long)thePC;
#ifdef RISC
  /* Correct PC in case of unalignment */
  thePC = (long *)((long)thePC & ~3);
#endif

  NotifyMessage[0]=0;

  if ((errorNumber==IllegalInstErr) && 
      IsBetaCodeAddrOfProcess((long)thePC) &&
      IS_BREAK_INST(*(long*)thePC)){
    /* Hit breakpoint instruction in BETA code - must be a %break */
    errorNumber = EmulatorTrapErr;
  }

  old_output = output;

  if (errorNumber==DumpStackErr) {
    SimpleDump = 1;
    output = stderr; 
  } else {
    if (!OpenDumpFile(errorNumber)) return 0;
  }
  
  DEBUG_CODE({
    fprintf(output,
	    "\nIOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
	    (int)GLOBAL_IOA, 
	    (int)GLOBAL_IOATop, 
	    (int)GLOBAL_IOALimit);
    fprintf(output,
	    "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	    (int)ToSpace, 
	    (int)ToSpaceTop, 
	    (int)ToSpaceLimit);
  });

  /******** And now for the actual trace of the stack: ********/
  {
    int UserWantsSimpleDump = SimpleDump;
    
    SimpleDump=1;

    AuxInfo(theObj, errorNumber);
    fflush(output);
    fprintf(output,"\nCall chain: (%s)\n\n", machine_type());
    fflush(output);
    DisplayCurrentObjectAndStack(errorNumber, theObj, thePC, theSignal);
    fflush(output);

    if (!UserWantsSimpleDump){
      SimpleDump=0;
      basic_dumped=0;
      lastDisplayedObject=0;
      fprintf(output,"\n\nLow level information:\n");
      AuxInfo(theObj, errorNumber);
      fflush(output);
      fprintf(output,"\nCall chain: (%s)\n\n", machine_type());
      fflush(output);
      DisplayCurrentObjectAndStack(errorNumber, theObj, thePC, theSignal);
    }
  }
  
  if (errorNumber!=DumpStackErr) {
    PrintLegend();
    fflush(output);
    fclose(output);
  } else {
    isMakingDump = 0;
    fflush(output);
  }

  if (old_output) output = old_output; 

#if defined(MAC)
  MakeMPWFile(dumpname);
#endif /* MAC */

  if (NotifyMessage[0]) Notify(NotifyMessage);

  isMakingDump = 0;
  return 0;
} /* DisplayBetaStack */

void NotifyErrorDuringDump(BetaErr errorNumber, BetaErr errorNumber2)
{
  fprintf(output, "\n# Beta execution aborted: ");
  fprintf(output, ErrorMessage(errorNumber));
  fprintf(output, "\n# Error during dump: ");
  fprintf(output, ErrorMessage(errorNumber2));
  fprintf(output, ". Aborting.\n\n");
  fflush(output);
  fflush(stdout);
#ifdef MT
  isMakingDump=0; /* allow other threads to make dump */
#endif
  if (NotifyMessage[0]) Notify(NotifyMessage);
  return;
}

#ifdef NEWRUN

/*************************** CodeEntry: ***************************/

/* Return the M or G part obtained from theProto, that PC is in */
unsigned long CodeEntry(ProtoType *theProto, long PC)
{
  /* Find the active prefix level based on the PC.
   * Here we use both the G-entry and the M-entry. 
   * The prefix we are in is the one, where the distance from the 
   * G-entry or M-entry of the corresponding prefix-level
   * to PC is smallest.
   */
  long gPart, gDist, mPart, mDist, minDist;
  ProtoType *activeProto;
  ProtoType *protoArg=theProto;

  TRACE_CODEENTRY({
    fprintf(output, "CodeEntry(theProto=0x%x", (int)theProto);
    PrintProto(theProto);
    fprintf(output, " PC=0x%x", PC); 
    PrintCodeAddress(PC);
    fprintf(output, ")\n");
    fflush(output);
  });
  mPart = M_Part(theProto);
  gPart = G_Part(theProto);
  gDist  = PC - gPart; 
  mDist  = PC - mPart;
  activeProto = theProto;
  if (gDist < 0) gDist = MAXINT;
  if (mDist < 0) mDist = MAXINT;
  TRACE_CODEENTRY(fprintf(output, "CodeEntry(initial gDist: 0x%x, proto=0x%x)\n", gDist, theProto));
  TRACE_CODEENTRY(fprintf(output, "CodeEntry(initial mDist: 0x%x, proto=0x%x)\n", mDist, theProto));
  minDist = (gDist<mDist) ? gDist : mDist;
    
  while(theProto && theProto->Prefix != theProto){
    theProto = theProto->Prefix;
    TRACE_CODEENTRY(fprintf(output, "CodeEntry: new candidate: theProto=0x%x (%s)\n", theProto, ProtoTypeName(theProto))); 
    mPart = M_Part(theProto);
    gPart = G_Part(theProto);
    if((PC-gPart > 0) && (PC-gPart <= minDist)){ 
      /* Use <= to get the LAST level, that has the entry point */ 
      minDist = gDist = PC-gPart;
      activeProto = theProto; 
      TRACE_CODEENTRY(fprintf(output, "CodeEntry(gDist: 0x%x, proto=0x%x)\n", gDist, theProto));
    }
    if((PC-mPart > 0) && (PC-mPart <= minDist)){ 
      /* Use <= to get the LAST level, that has the entry point */ 
      minDist = mDist = PC-mPart; 
      activeProto = theProto;
      TRACE_CODEENTRY(fprintf(output, "CodeEntry(mDist: 0x%x, proto=0x%x)\n", mDist, theProto));
    }
  }
  if (minDist == MAXINT) {
    fprintf(output, 
	    "RTS: Fatal Error: CodeEntry(proto=0x%x, PC=0x%x): minDist == MAXINT\n",
	    protoArg,
	    PC);
    if (isMakingDump){
      NotifyErrorDuringDump((BetaErr)isMakingDump, InternalErr);
    }
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }
  if (minDist == PC) {
    fprintf(output, 
	    "RTS: Fatal Error: CodeEntry(proto=0x%x, PC=0x%x) returns 0.\n",
	    protoArg,
	    PC);
    if (isMakingDump){
      NotifyErrorDuringDump((BetaErr)isMakingDump, InternalErr);
    }
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }
  if (minDist == gDist) {
    TRACE_CODEENTRY(fprintf(output, "CodeEntry returns G_part(0x%x): 0x%x\n", (int)activeProto, G_Part(activeProto)));
    return (unsigned long)G_Part(activeProto);
  } else {
    TRACE_CODEENTRY(fprintf(output, "CodeEntry returns M_part(0x%x): 0x%x\n", (int)activeProto, M_Part(activeProto)));
    return (unsigned long)M_Part(activeProto);
  }
}

#endif /* NEWRUN */
