#include "beta.h"

ValRep *LVRAAlloc(ProtoType *proto, long range)
{
  ValRep *    newRep;
  long           size;

  Claim(isSpecialProtoType(proto), "isSpecialProtoType(proto)");

  size = DispatchValRepSize(proto, range);
  newRep = (ValRep *) AOAallocate(size);
  SETPROTO(newRep,proto);
  newRep->LowBorder  = 1;
  newRep->HighBorder = range; /* indexes */
  return newRep;
}


/* LVRACAlloc: allocate a Value repetition in the LVRA area 
 * and nullify the BODY of the repetition..
 */
ValRep * LVRACAlloc(ProtoType * proto, long range)     
{
  ValRep * newRep = LVRAAlloc(proto, range);
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
ValRep * LVRAXAlloc(ProtoType * proto, long oldrange, long newrange)  
{
  ValRep * newRep = LVRAAlloc(proto, newrange);
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
