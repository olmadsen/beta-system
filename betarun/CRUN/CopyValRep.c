/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ParamRepObjOff(CopyVR1)
{
    DeclReference1(ValRep *, newRep);
    register unsigned range, i, size;
    
    FetchRepObjOff();

    DEBUG_CODE(NumCopyVR1++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    size = ByteRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE|| size>IOAMAXSIZE){
        newRep = LVRAAlloc(ByteRepPTValue, range);
      } 
      if (!newRep) {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
	if (newRep) {
	  SETPROTO(newRep,ByteRepPTValue);
	  
	  if (IOAMinAge!=0) {
	    newRep->GCAttr = IOAMinAge;
	  }
	  
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);
    
    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
        newRep->Body[i] = theRep->Body[i];
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);
    
    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOff(CopyVR2)
{
    DeclReference1(ValRep *, newRep);
    register unsigned range, i, size;
    
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;
    
    size = ShortRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE|| size>IOAMAXSIZE){
        newRep = LVRAAlloc(ShortRepPTValue, range);
      } 
      if (!newRep) {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
	if (newRep) {
	  SETPROTO(newRep,ShortRepPTValue);
	  
	  if (IOAMinAge!=0) {
	    newRep->GCAttr = IOAMinAge;
	  }
	  
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);
    
    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
        newRep->Body[i] = theRep->Body[i];
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);
    
    Ck(newRep); Ck(theRep); Ck(theObj);
}

ParamRepObjOff(CopyVR4)
{
    DeclReference1(ValRep *, newRep);
    register unsigned range, i, size;
    
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR4++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    size = LongRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE|| size>IOAMAXSIZE){
        newRep = LVRAAlloc(LongRepPTValue, range);
      } 
      if (!newRep) {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
	if (newRep) {
	  SETPROTO(newRep,LongRepPTValue);
	  
	  if (IOAMinAge!=0) {
            newRep->GCAttr = IOAMinAge;
	  }
	  
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);

    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
        newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (Item *) newRep);
    
    Ck(newRep); Ck(theRep); Ck(theObj);
    
}

ParamRepObjOff(CopyVR8)
{
    DeclReference1(ValRep *, newRep);
    register unsigned range, i, size;
    
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR8++);
    
    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    size = DoubleRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE|| size>IOAMAXSIZE){
        newRep = LVRAAlloc(DoubleRepPTValue, range);
      } 
      if (!newRep) {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
	if (newRep) {
	  SETPROTO(newRep,DoubleRepPTValue);
	  
	  if (IOAMinAge!=0) {
            newRep->GCAttr = IOAMinAge;
	  }
	  
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);

    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
        newRep->Body[i] = theRep->Body[i];
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);
    
    Ck(newRep); Ck(theRep); Ck(theObj);
    
}

ParamORepObjOff(CopyVRI)
{
    DeclReference1(ObjectRep *, newRep);
    register unsigned range, i, size;
    
    FetchORepObjOff();
    
    DEBUG_CODE(NumCopyVRI++);
    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;
    size = DynObjectRepSize(range);

    /*Protect2(theObj, theRep, newRep = (ObjectRep *) IOAalloc(size));*/
    newRep = 0;
    push(theObj);
    push(theRep); 
    do {
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVRI allocates in AOA\n"));
	newRep = (ObjectRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      } 
      if (!newRep) {
	newRep = (ObjectRep *)IOATryAlloc(size);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);

    SETPROTO(newRep,DynItemRepPTValue);

    if (IOAMinAge!=0) {
        newRep->GCAttr = IOAMinAge;
    }
    
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    newRep->iOrigin = theRep->iOrigin;
    newRep->iProto = theRep->iProto;
    
    size -= headsize(ObjectRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
        newRep->Body[i] = theRep->Body[i];
        /* No need to use AssignReference: newRep is in IOA */
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);
    
    Ck(newRep); Ck(theRep); Ck(theObj);
}

ParamORepObjOff(CopyVRC)
{
    DeclReference1(ObjectRep *, newRep);
    register unsigned range, i, size;
    
    FetchORepObjOff();
    
    DEBUG_CODE(NumCopyVRC++);
    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;
    size = DynObjectRepSize(range);
    
    /*Protect2(theObj, theRep, newRep = (ObjectRep *) IOAalloc(size));*/
    newRep = 0;
    push(theObj);
    push(theRep); 
    do {
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVRC allocates in AOA\n"));
	newRep = (ObjectRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      } 
      if (!newRep) {
	newRep = (ObjectRep *)IOATryAlloc(size);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);

    SETPROTO(newRep,DynCompRepPTValue);

    if (IOAMinAge!=0) {
        newRep->GCAttr = IOAMinAge;
    }
    
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    newRep->iOrigin = theRep->iOrigin;
    newRep->iProto = theRep->iProto;
    
    size -= headsize(ObjectRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
        newRep->Body[i] = theRep->Body[i];
        /* No need to use AssignReference: newRep is in IOA */
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);
    
    Ck(newRep); Ck(theRep); Ck(theObj);
}
