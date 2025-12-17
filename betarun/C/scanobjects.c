/*
 * Low level support for scanning BETA objects in the
 * different kinds of heaps. Used by ~beta/sysutils/scanobjects.bet.
 *
 * COPYRIGHT
 *       Copyright (C) Aarhus University
 *       All rights reserved.
 */

#include "beta.h"
#ifndef MT 

#define GC_PANIC_MSG "\n\n\tPANIC: object scan stopped because of GC!!\n\n"
#define UNKNOWN_PANIC_MSG "\n\n\tPANIC: object is neither live nor free!!\n\n"
#define MSG_DEST stdout


/**********************
 *                    *
 *   Implementation   *
 *                    *
 **********************/

static int
isPrefix(ProtoType * fst, ProtoType * snd)
{
  ProtoType * tmp=snd;

  if ((long)fst > 0 && (long)snd > 0) {

    /* Real object prototypes */
    while (1) {
      if (tmp==fst)
	return 1;
      if (0==tmp->Prefix || tmp->Prefix==tmp->Prefix->Prefix)
	return 0;
      tmp=tmp->Prefix;
    }
  }
  else {

    /* At least one of {fst,snd} is special or NULL */
    return 0;
  }
}


static void
printMessage(FILE *fp,
	     Object * theObj,
	     int printOrigin,
	     int printSize)
{
  ProtoType * proto=GETPROTO(theObj);
  char *name;

  if ((long)proto < 0)
    switch (SwitchProto(proto)) {
    case SwitchProto(ComponentPTValue): name = "[Component]"; break;
    case SwitchProto(StackObjectPTValue): name = "[Stack_Object]"; break;
    case SwitchProto(StructurePTValue): name = "[Struc_Object]"; break;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue): name = "[Object_Repetition]"; break;
    case SwitchProto(RefRepPTValue): name = "[Reference_Repetition]"; break;
    case SwitchProto(LongRepPTValue): name = "[Integer_Repetition]"; break;
    case SwitchProto(ByteRepPTValue): name = "[Char_Repetition]"; break;
    case SwitchProto(ShortRepPTValue): name = "[Int16_Repetition]"; break;
    case SwitchProto(DoubleRepPTValue): name = "[Real_Repetition]"; break;
    default: name = "[???]"; break;
    }
  else {
    name = ProtoTypeName(proto);
  }
  fprintf(fp, "%s", name);

  if ((long)proto >= 0) {	/* Real object */
    
    while (proto->Prefix && proto->Prefix->Prefix != proto->Prefix) {
      proto = proto->Prefix;
      fprintf(fp, "%s", ProtoTypeName(proto));
    }

    if (printOrigin) {
      fprintf(fp," ");
      printMessage(fp,
		   (Object *)(((long*)theObj)[OBJPROTOFIELD(theObj,OriginOff)]),
		   0,	/* don't print origins recursively */
		   0);	/* don't print size of origin */
    }
  }

  if (printSize) {
    fprintf(fp," %ld",4*ObjectSize(theObj));
  }
}


static void
noise_cb(Object * theObj, int printOrigin, int printSize)
{
  fprintf(MSG_DEST,"{scan} ");
  printMessage(MSG_DEST,theObj,printOrigin,printSize);
  fprintf(MSG_DEST,"\n");
}


static void
scanAOAliveObjects(int printVisited, int printOrigin, int printSize,
		   int docallback,
		   ProtoType * rootProto,
		   void (*cb)(Object *))
{
  Block * theBlock;
  Object * theObj;
  long objSize = 0;
  Block * savedLastBlock;
  long * savedLastTop;
  long * currentTop;
  long SavedNumAOAGc = NumAOAGc;

  /* If no AOA yet, stop */
  if (!AOABaseBlock)
    return;

  /* Ignore objects created during this scan: find limit */
  savedLastBlock = AOABaseBlock;
  while (savedLastBlock->next)
    savedLastBlock=savedLastBlock->next;
  savedLastTop=savedLastBlock->top;

  theBlock = AOABaseBlock;
  while (theBlock) {

    if (theBlock==savedLastBlock) {
      currentTop=savedLastTop;
    }
    else {
      currentTop=theBlock->top;
    }

    theObj = (Object *) BlockStart(theBlock);
    while ((long *) theObj < currentTop) {

      /* Check for AOA-GC */
      if (SavedNumAOAGc != NumAOAGc) {
	fprintf(MSG_DEST,GC_PANIC_MSG);
	return;
      }

      if (!AOAISFREE(theObj)) {
	/* Expose the object */
	if (((long) GETPROTO(theObj)) >= 0) {
	  
	  /* Real object: filter by root */
	  if ((0==rootProto) || isPrefix(rootProto,GETPROTO(theObj))) {
	    if (printVisited)
	      noise_cb(theObj,printOrigin,printSize);
	    if (docallback)
	      (*cb)(theObj);
	  }
	} else {
	  
	  /* Non-object: suppressed if there is a root */
	  if (printVisited && (0==rootProto))
	    noise_cb(theObj,printOrigin,printSize);
	}

	/* Go to next object */
	objSize = 4*ObjectSize(theObj);
      } else {
	objSize = ((AOAFreeChunk*)theObj)->size;
      }
      theObj = (Object *) ((long) theObj + objSize);
    }

    if (theBlock==savedLastBlock) {
      break;
    }
    else {
      theBlock = theBlock->next;
    }
  }
}


static void
scanIOAliveObjects(int printVisited,
		   int printOrigin,
		   int printSize,
		   int docallback,
		   ProtoType * rootProto,
		   void (*cb)(Object *))
{
  Object * theObj = (Object *)IOA;
  long objSize;
  long SavedNumIOAGc = NumIOAGc;

  /* If 'cb' creates new objects, ignore them */
  long *SavedIOATop = IOATop;

  while ((long*)theObj < SavedIOATop) {

    /* Check for IOA-GC */
    if (SavedNumIOAGc != NumIOAGc) {
      fprintf(MSG_DEST,GC_PANIC_MSG);
      return;
    }

    /* Expose the object */
    if (((long) GETPROTO(theObj)) >= 0) {

      /* Real object: filter by root */
      if ((0==rootProto) || isPrefix(rootProto,GETPROTO(theObj))) {
	if (printVisited)
	  noise_cb(theObj,printOrigin,printSize);
	if (docallback)
	  (*cb)(theObj);
      }
    }
    else {

      /* Non-object: suppressed if there is a root */
      if (printVisited && (0==rootProto))
	noise_cb(theObj,printOrigin,printSize);
    }

    /* Go to next object */
    objSize = 4*ObjectSize(theObj);
    theObj = (Object *) ((long)theObj + objSize);
  }
}




/*****************
 *               *
 *   Interface   *
 *               *
 *****************/


void
lowScanIOA(long printVisited, long printOrigin, long printSize,
	   long docallback,
	   ProtoType * rootProto,
	   void (*cb)(Object *))
{
  scanIOAliveObjects(printVisited,
		     printOrigin,
		     printSize,
		     docallback,
		     rootProto,
		     cb);
}


void
lowScanAOA(long printVisited, long printOrigin, long printSize,
	   long docallback,
	   ProtoType * rootProto,
	   void (*cb)(Object *))
{
  scanAOAliveObjects(printVisited,
		     printOrigin,
		     printSize,
		     docallback,
		     rootProto,
		     cb);
}


#define DEBUG_SCANREF 0
void scanIOAliveForRef(Object * target,
		  int printName,
		  void (*cb)(Object *))
{
  Object * theObj = (Object *)IOA;
  long objSize;
  long SavedNumIOAGc = NumIOAGc;
  GCEntry *gce;
  short *dynoffptr;
  long reftype;
  long* refptr;

  /* If 'cb' creates new objects, ignore them */
  long *SavedIOATop = IOATop;
#if DEBUG_SCANREF
  fprintf(output, "ScanRefs:Looking for target %08X\n", (long)target);
  fprintf(output, "ScanRefs:IOA=%08X, IOATop=%08X\n", (long)IOA, (long)IOATop);
#endif

  while ((long*)theObj < SavedIOATop) {
    /* Check for IOA-GC */
    if (SavedNumIOAGc != NumIOAGc) {
      fprintf(MSG_DEST,GC_PANIC_MSG);
      return;
    }

    /* Check the object */
    if (((long) GETPROTO(theObj)) >= 0) {
#if DEBUG_SCANREF
      fprintf(output, "ScanRefs:Looking at %08X %s\n", 
	      (long)theObj, ProtoTypeName(GETPROTO(theObj)));
#endif
      /* Real object: Scan refs or target */
      gce = (GCEntry*)((long)GETPROTO(theObj) + OBJPROTOFIELD(theObj,GCTabOff));
      while (gce->StaticOff) {
	/* Check static refs here. */
#if DEBUG_SCANREF
	if (((long)GETPROTO(gce)) >0)
	  fprintf(output, "ScanRefs:Looking at static part at %08X: %s\n",
		  (long)theObj+(gce->StaticOff*4),ProtoTypeName(GETPROTO(gce)));
#endif
	if ((long)theObj+(gce->StaticOff*4) == (long)target) {
	  /* Found a pointer at target */
	  if (printName) {
	    fprintf(output, "ScanRefs:Found target as static part of %s\n", 
		    ProtoTypeName(GETPROTO(theObj)));
	  }
	  if (cb) 
	    (*cb)(theObj);
	}
	gce++;
      }
      dynoffptr = (short*)gce;
      dynoffptr++; /* Skip terminating zero */
      while (*dynoffptr) {
	reftype = *dynoffptr;
	refptr = (long*)((reftype & ~3) + (long)theObj);
	reftype &= 3;
	if (*refptr == (long)target) {
	  /* Found a pointer at target */
	  if (printName) {
	    fprintf(output, "ScanRefs:Found pointer to target from %s\n", 
		    ProtoTypeName(GETPROTO(theObj)));
	  }
	  if (cb) 
	    (*cb)(theObj);
	}
	dynoffptr++;
      }
    }
    else {
      /* Non-object: most are ignored for now */
      switch ((long)(GETPROTO(theObj))) {
      case (long)ComponentPTValue:
#if DEBUG_SCANREF
	fprintf(output, "ScanRefs:Component, skipping header\n");
#endif
	theObj = (Object*)ComponentItem(theObj);
	continue;
      default:
	;
#if DEBUG_SCANREF
	fprintf(output, "ScanRefs:skipping at %08X proto %08X\n", 
		(long)theObj, (long)(GETPROTO(theObj)));
#endif
      }
    }
    
    /* Go to next object */
    objSize = 4*ObjectSize(theObj);
    theObj = (Object *) ((long)theObj + objSize);
  }
}

#endif /* !MT */
