/* runAlloc_snake.c
 *
 * Created by Peter Andersen
 *
 * Interface to BETA RTS allocation routines used by ObjectSerializer.
 *
 */

#include <beta.h>


void DoAlloVR1 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR1(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloVR2 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR2(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloVR4 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR4(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloVR8 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloVR8(offset, range, obj);
  setThisReg(popReference());
}

void DoAlloRR (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  AlloRR(offset, range, obj);
  setThisReg(popReference());
}

struct Structure *DoAlloS (struct Object *origin, struct ProtoType *proto)
{
  struct Structure *struc;
  extern struct Item *AlloS();

  pushReference(getCallReg());
  setCallReg(proto);
  struc = (struct Structure *)AlloS(origin, proto);
  setCallReg(popReference());
  return struc;
}

struct Item *DoAlloH(struct Object *origin, struct ProtoType *proto)
{
  struct Item *item;
  extern struct Item *AlloH();

  pushReference(getCallReg());
  setCallReg(proto);
  item = (struct Item *)AlloH(origin, proto);
  setCallReg(popReference());
  return item;
}


