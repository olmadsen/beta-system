/* runAlloc_snake.c
 *
 * Created by Peter Andersen
 *
 * Interface to BETA RTS allocation routines used by ObjectSerializer.
 *
 */

#include <beta.h>


void DoAlloVR1 (Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR1(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloVR2 (Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR2(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloVR4 (Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR4(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloVR8 (Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR8(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloRR (Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloRR(offset, range, obj);
  setThisReg(popReference());
}

Structure *DoAlloS (Object *origin, ProtoType *proto)
{
  Structure *struc;
  extern Item *AlloS();

  pushReference(getCallReg());
  setCallReg(proto);
  struc = (Structure *)AlloS(origin, proto);
  setCallReg(popReference());
  return struc;
}

Item *DoAlloH(Object *origin, ProtoType *proto)
{
  Item *item;
  extern Item *AlloH();

  pushReference(getCallReg());
  setCallReg(proto);
  item = (Item *)AlloH(origin, proto);
  setCallReg(popReference());
  return item;
}


