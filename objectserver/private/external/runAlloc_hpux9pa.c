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
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR1(obj, offset, range);
  setThisReg(popReference());
  return;
}

void DoAlloVR2 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR2(obj, offset, range);
  setThisReg(popReference());
  return;
}

void DoAlloVR4 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR4(obj, offset, range);
  setThisReg(popReference());
  return;
}

void DoAlloVR8 (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR8(obj, offset, range);
  setThisReg(popReference());
  return;
}

void DoAlloRR (struct Object *obj, int offset, int range)
{
  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloRR(obj, offset, range);
  setThisReg(popReference());
  return;
}

struct Structure *DoAlloS (struct Object *origin, struct ProtoType *proto)
{
  struct Structure *struc;
  extern struct Item *AlloS();

  pushReference(getCallReg());
  pushReference(getOriginReg());
  setOriginReg(origin);
  setCallReg(proto);
  struc = (struct Structure *)AlloS();
  setOriginReg(popReference());
  setCallReg(popReference());
  return struc;
}

struct Item *DoAlloH(struct Object *origin, struct ProtoType *proto)
{
  struct Item *item;
  extern struct Item *AlloH();


  pushReference(getCallReg());
  pushReference(getOriginReg());
  setOriginReg(origin);
  setCallReg(proto);
  item = (struct Item *)AlloH();
  setOriginReg(popReference());
  setCallReg(popReference());
  return item;
}


