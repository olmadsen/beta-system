/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamRepObjOff(CopyVR1)
{
    DeclReference1(ValRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();

    FetchRepObjOff();

    DEBUG_CODE(NumCopyVR1++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    size = ByteRepSize(range);
    
    if (range > LARGE_REP_SIZE){
        newRep = LVRAAlloc(ByteRepPTValue, range);
        
    } else {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOAalloc(size));
        newRep->Proto = ByteRepPTValue;
        
        if (IOAMinAge!=0) {
            newRep->GCAttr = IOAMinAge;
        }

        newRep->LowBorder = 1;
        newRep->HighBorder = range;
    }
    
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
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;
    
    size = ShortRepSize(range);
    
    if (range > LARGE_REP_SIZE){
        newRep = LVRAAlloc(ShortRepPTValue, range);
        
    } else {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOAalloc(size));
        newRep->Proto = ShortRepPTValue;

        if (IOAMinAge!=0) {
            newRep->GCAttr = IOAMinAge;
        }
        
        newRep->LowBorder = 1;
        newRep->HighBorder = range;
    }
    
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
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR4++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    size = LongRepSize(range);
    
    if (range > LARGE_REP_SIZE){
        newRep = LVRAAlloc(LongRepPTValue, range);
    } else {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOAalloc(size));
        newRep->Proto = LongRepPTValue;

        if (IOAMinAge!=0) {
            newRep->GCAttr = IOAMinAge;
        }
        
        newRep->LowBorder = 1;
        newRep->HighBorder = range;
    }
    
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
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR8++);
    
    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    size = DoubleRepSize(range);
    
    if (range > LARGE_REP_SIZE){
        newRep = LVRAAlloc(DoubleRepPTValue, range);
    } else {
        /* Allocate in IOA */
        Protect2(theObj, theRep, newRep = (ValRep *) IOAalloc(size));
        newRep->Proto = DoubleRepPTValue;

        if (IOAMinAge!=0) {
            newRep->GCAttr = IOAMinAge;
        }

        newRep->LowBorder = 1;
        newRep->HighBorder = range;
    }
    
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
    
    GCable_Entry();
    FetchORepObjOff();
    
    DEBUG_CODE(NumCopyVRI++);
    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;
    size = DynObjectRepSize(range);
    
    Protect2(theObj, theRep, newRep = (ObjectRep *) IOAalloc(size));
    
    newRep->Proto = DynItemRepPTValue;

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
    
    GCable_Entry();
    FetchORepObjOff();
    
    DEBUG_CODE(NumCopyVRC++);
    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;
    size = DynObjectRepSize(range);
    
    Protect2(theObj, theRep, newRep = (ObjectRep *) IOAalloc(size));
    
    newRep->Proto = DynCompRepPTValue;

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
