#include "beta.h"

ValRep *LVRAAlloc(ProtoType *proto, long range)
{
  ValRep *    newRep;
  long           size;

  Claim(isSpecialProtoType(proto), "isSpecialProtoType(proto)");

  size = DispatchRepSize(proto, range);
  newRep = (ValRep *) AOAallocate(size, FALSE);
  if (newRep){
    /* The Copy and Extend routines always copy elements as longs.
     * If the element size is less than 4 bytes, this means that up to 3 bytes
     * more than actual data is copied. 
     * Furthermore, some allocation routines use ObjectAlign on the number 
     * of bytes to copy. That is they copy up to 7 bytes too much.
     * The bytes will be part of the object, but if allocatd in AOA they
     * may contain garbage. This is suspected to cause the String Table Corrupt
     * in the Windows code generator, since it may cause extra bytes after the
     * last "real" byts in the text encoding the string table.
     * To prevent this we clear the last two longs in the repetition.
     * Since the allocated area always include the repeptition header, 
     * there will always be at least 4 bytes (even for empty rep, which should
     * not be in LVRA anyway), so there's no need to test size.
     */
    *((long*)newRep + size/sizeof(long*) - 1) = 0;
    *((long*)newRep + size/sizeof(long*) - 2) = 0;

    SETPROTO(newRep,proto);
    newRep->LowBorder  = 1;
    newRep->HighBorder = range; /* indexes */
  }
  return newRep;
}


/* LVRACAlloc: allocate a repetition in the LVRA area 
 * and nullify the BODY of the repetition..
 */
ValRep * LVRACAlloc(ProtoType * proto, long range)     
{
  ValRep * newRep = LVRAAlloc(proto, range);
  long numbytes = DispatchRepBodySize(proto, range);
  if (newRep){
      /* Clear the body of newRep. Notice that since
       * RepSize<>RepBodySize+HeadSize due to alignment (see macro.h),
       * we cannot assume that the 8 bytes cleared by LVRAAlloc can be
       * skipped. We could, however, skip clearing of 4 bytes, but it
       * does not seem worth the effort. */
      memset(newRep->Body, 0, numbytes);
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
    /* Clear the extension part of the body of newRep. See comments in
       LVRACAlloc */
    long oldbodysize = DispatchRepBodySize(proto, oldrange);
    long newbodysize = DispatchRepBodySize(proto, newrange);
    long numbytes = newbodysize-oldbodysize;
    memset((char*)(newRep->Body)+oldbodysize, 
	   0, 
	   numbytes);
  }
  return newRep;
}
