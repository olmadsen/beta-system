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
  extern void AlloVR1();

  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR1();
  setThisReg(popReference());
  return;
}

void DoAlloVR2 (struct Object *obj, int offset, int range)
{
  extern void AlloVR2();

  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR2();
  setThisReg(popReference());
  return;
}

void DoAlloVR4 (struct Object *obj, int offset, int range)
{
  extern void AlloVR4();

  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR4();
  setThisReg(popReference());
  return;
}

void DoAlloVR8 (struct Object *obj, int offset, int range)
{
  extern void AlloVR8();

  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloVR8();
  setThisReg(popReference());
  return;
}

void DoAlloRR (struct Object *obj, int offset, int range)
{
  extern void AlloRR();

  pushReference(getThisReg());
  setThisReg(obj);
  setD0Reg(offset);
  setD1Reg(range);
  AlloRR();
  setThisReg(popReference());
  return;
}

struct Structure *DoAlloS (struct Object *origin, struct ProtoType *proto)
{
  extern struct Item *AlloS();
  struct Structure *struc;

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
  extern struct Item *AlloH();
  struct Item *item;

  pushReference(getCallReg());
  pushReference(getOriginReg());
  setOriginReg(origin);
  setCallReg(proto);
  item = (struct Item *)AlloH();
  setOriginReg(popReference());
  setCallReg(popReference());
  return item;
}
