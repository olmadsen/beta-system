/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * lvra.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

ref(ValRep) LVRAAlloc(ref(ProtoType) proto, long range)
{
  ref(ValRep)    newRep;
  long           size;

  size = DispatchValRepSize(proto, range);
  newRep = (ref(ValRep)) AOAallocate(size);
  newRep->Proto      = proto;
  newRep->LowBorder  = 1;
  newRep->HighBorder = range; /* indexes */
  return newRep;
}


/* LVRACAlloc: allocate a Value repetition in the LVRA area 
 * and nullify the BODY of the repetition..
 */
ref(ValRep) LVRACAlloc(ref(ProtoType) proto, long range)     
{
  ref(ValRep) newRep = LVRAAlloc(proto, range);
  if (newRep){
    /* Clear the body of newRep */
    memset(newRep->Body, 0, DispatchValRepBodySize(proto, range));
  }
  return newRep;
}

/* LVRAXAlloc: allocate a Value repetition in the LVRA area 
 * and nullify extension part of the BODY of the repetition
 * (i.e. the elements from ]oldrange..newrange]
 */
ref(ValRep) LVRAXAlloc(ref(ProtoType) proto, long oldrange, long newrange)  
{
  ref(ValRep) newRep = LVRAAlloc(proto, newrange);
  if (newRep && (newrange>oldrange)){
    /* Clear the extension part of the body of newRep */
    long oldbodysize = DispatchValRepBodySize(proto, oldrange);
    long newbodysize = DispatchValRepBodySize(proto, newrange);
    memset((char*)(newRep->Body)+oldbodysize, 
	   0, 
	   newbodysize-oldbodysize);
  }
  return newRep;
}
