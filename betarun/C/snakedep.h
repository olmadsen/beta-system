#ifndef _SNAKEDEP_H_
#define _SNAKEDEP_H_

/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * snakedep.h
 * by Peter Orbaek
 */

/* Heap:
   
   IOA:
      .
      .
      IOA+IOATopoff: First available byte
      .
      .
   IOALimit: First not available byte
*/

typedef unsigned long ulong;

/* The layout of a 64 byte stackframe. arg0 may hold ThisReg */

struct SnakeSF {
  ulong		arg7,arg6,arg5,arg4,arg3,arg2,arg1,arg0;
  ulong		lpt,lpt1,rp1,rp,sl,cleanup,rp2,psp;
};

/* assignments to global register vars doesn't really work with
   gcc 2.2.2 on the snake, but we must prevent the compiler from
   restoring old values into these registers as they may be used
   as return values from RT routines, hack hack...

   The actual assignment is done via the set.. and get... routines
   below. They are inlined, and thus just induce the overhead of
   one register-to-register copy

   If you are sure that one or more of these are never used as a
   returnvalue from (or set in) a RT routine, then please remove it, 
   and allow GCC to use the register.
 */

#ifndef NO_GLOB_REGS
register long _dummy1 __asm__("%r3");  /* really th */
register long _dummy2 __asm__("%r4");  /* really ca */
register long _dummy3 __asm__("%r5");  /* really or */
register long _dummy33 __asm__("%r6");  /* really tmp R1 */
register long _dummy37 __asm__("%r7");  /* really tmp R2 */
register long _dummy4 __asm__("%r17"); /* really IOAbot */
register long _dummy5 __asm__("%r18"); /* really IOAsize */
register long _dummy6 __asm__("%r9");  /* really D0 */
register long _dummy6 __asm__("%r10");  /* really D1 */
register long _dummy7 __asm__("%r14"); /* really RefSP */
#endif

/* Tell GCC that some called Beta code has potentially clobbered all these
 * registers. 
 */

#define BETA_CLOBBER() \
__asm__ volatile ("" : : : /* "r3", "r4", "r5", "r6", "r7", */ "r8", "r9", \
		  "r10",	"r11", "r12", "r13","r14","r15","r16");
#define asmlabel(label, code)
#define asmcomment(text) 

/*
 * Take care of the reference stack.
 * The reference stack may actually contain two types of pointers, namely
 * pointers to objects in the Beta heap, and pointers to pointers located
 * in the system stack, the pointer in the stack may be NULL or point to
 * an object in the Beta heap. All of this mess exists to make GC work.
 * References to object are not allowed on the system stack, unless they
 * are "registered" on the reference stack.
 */

extern void *ReferenceStack[];

static __inline__ void pushReference(void *p)
{
  /*fprintf(stdout, "push 0x%x at 0x%x\n", p, RefSP);*/
   *RefSP=(long)p; 
   RefSP++; 
}

static __inline__ void *popReference()
{
  void *p;
  RefSP--; 
  p=(void *)*RefSP; 
  /*fprintf(stdout, "pop 0x%x at 0x%x\n", p, RefSP);*/
  return p;
}

static __inline__ void pushReg(void *r) 
{ /* This is how compiler pushes: strange big frame (64)? */
  __asm__ volatile("STW\t%0,-36(0,%%r30)" : /* no out */ : "r" (r));
  __asm__ volatile("LDO\t64(%r30),%r30");
}

static __inline__ void *popReg() 
{ register void *r;
  __asm__ volatile("LDO\t-64(%r30),%r30");
  __asm__ volatile("LDW\t-36(0,%%r30),%0" : "=r" (r) : );
  return r;
}

extern ref(Component) ActiveComponent;
extern ref(CallBackFrame) ActiveCallBackFrame;

static __inline__ long *getThisReg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r3, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setThisReg(void *p)
{     
  __asm__ volatile ("COPY\t%0, %%r3" : /* no out */ : "r" (p)); 
}

static __inline__ long *getRetReg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r28, %0" : "=r" (res)); 
  return res;
}

static __inline__ long *getCallReg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r4, %0" : "=r" (res)); 
  return res;
}

static __inline__ void *setCallReg(void *p)
{     
  __asm__ volatile ("COPY\t%0, %%r4" : /* no out */ : "r" (p));
  return p; /* 'cause it's used in the RETURN macro */
}

static __inline__ long *getR8Reg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r8, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setR8Reg(long p)
{     
  __asm__ volatile ("COPY\t%0, %%r8" : /* no out */ : "r" (p));
}

static __inline__ long *getD0Reg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r9, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setD0Reg(long p)
{     
  __asm__ volatile ("COPY\t%0, %%r9" : /* no out */ : "r" (p));
}

static __inline__ long *getD1Reg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r10, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setD1Reg(long p)
{     
  __asm__ volatile ("COPY\t%0, %%r10" : /* no out */ : "r" (p));
}

static __inline__ long *getD2Reg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r11, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setD2Reg(long p)
{     
  __asm__ volatile ("COPY\t%0, %%r11" : /* no out */ : "r" (p));
}

static __inline__ long *getD3Reg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r12, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setD3Reg(long p)
{     
  __asm__ volatile ("COPY\t%0, %%r12" : /* no out */ : "r" (p));
}

static __inline__ long *getD4Reg()
{     
  long *res; 
  __asm__ volatile ("COPY\t%%r13, %0" : "=r" (res)); 
  return res;
}

static __inline__ void setD4Reg(long p)
{     
  __asm__ volatile ("COPY\t%0, %%r13" : /* no out */ : "r" (p));
}

static __inline__ long *getOriginReg()
{     
  /* This is probably a nop in most cases since r26 = first C param */
  long *res; 
  __asm__ volatile ("COPY\t%%r26, %0" : "=r" (res));
  return res;
}

static __inline__ void *setOriginReg(void *p)
{     
  __asm__ volatile ("COPY\t%0, %%r26" : /* no out */ : "r" (p));
  return p;
}

static __inline__ void setPrimReg1(long v)
{     
  __asm__ volatile ("COPY\t%0, %%r26" : /* no out */ : "r" (v)); 
}

static __inline__ long getPrimReg1()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r26, %0" : "=r" (v)); 
  return v;
}

static __inline__ void setPrimReg2(long v)
{     
  __asm__ volatile ("COPY\t%0, %%r25" : /* no out */ : "r" (v) : "r10"); 
}

static __inline__ long getPrimReg2()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r25, %0" : "=r" (v)); 
  return v;
}

static __inline__ void setPrimReg3(long v)
{     
  __asm__ volatile ("COPY\t%0, %%r24" : /* no out */ : "r" (v) : "r10"); 
}

static __inline__ long getPrimReg3()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r24, %0" : "=r" (v)); 
  return v;
}

static __inline__ void setPrimReg4(long v)
{     
  __asm__ volatile ("COPY\t%0, %%r23" : /* no out */ : "r" (v) : "r10"); 
}

static __inline__ long getPrimReg4()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r23, %0" : "=r" (v)); 
  return v;
}

static __inline__ void setPrimReg5(long v)
{     
  __asm__ volatile ("COPY\t%0, %%r22" : /* no out */ : "r" (v) : "r10"); 
}

static __inline__ long getPrimReg5()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r22, %0" : "=r" (v)); 
  return v;
}

static __inline__ long getR1Reg()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r15, %0" : "=r" (v)); 
  return v;
}

static __inline__ long getR2Reg()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r16, %0" : "=r" (v)); 
  return v;
}

static __inline__ long getSPReg()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r30, %0" : "=r" (v)); 
  return v;
}

static __inline__ long getRPReg()
{ 
  long v;
  __asm__ volatile ("COPY\t%%r2, %0" : "=r" (v)); 
  return v;
}

/* the __typeof__ is a GNU feature, it is used to produce fewer warnings */
#define RETURN(v) return (__typeof__(v))(setCallReg((long *)(v)))

/* Defining this in the head of a module, together with a
   GCable_Entry and GCable_Exit in every routine in that module makes
   the activation record look like BETA, but *BEWARE*!:
   CHECK THAT THE ROUTINE DOESN'T USE ANY STACK, OR LOOSE!!
*/

#ifdef GCable_Module
     
#define GCable_Entry()
#define GCable_Exit(n)

#endif /* GCable_Module */

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

/* AlloC, AlloI, AlloH, AlloS */
#define ParamOriginProto(type, name)		        \
  type name(struct Object *origin,                      \
	    struct ProtoType *proto)
#define FetchOriginProto()				\
  /* origin is in correct register */                   \
  proto  = (struct ProtoType *)getCallReg()


/* Att, AttBC, HandleIndexErr */
#define ParamThisComp(type, name)			\
 type name(struct Object *this, struct Component *comp)
#define FetchThisComp()			                \
  this = (struct Object *)getThisReg();	                \
  comp = (struct Component *)getCallReg()


/* Susp */
#define ParamThis(type, name)                         	\
 type name(struct Object *this)
#define FetchThis()					\
  this = (struct Object *) getThisReg();                \


/* AlloSI, AlloSC */
#define ParamStruc(type, name)				\
 type name(struct Structure *struc)
#define FetchStruc()                                    \
  struc = cast(Structure) getCallReg();


/* AlloRR, AlloVR1, AlloVR2, AlloVR4, AlloVR8 */
#define ParamThisOffRange(name)		        	\
 void name(unsigned offset, /* in bytes */		\
	   /*unsigned*/ int range,                      \
	   struct Object *theObj)
#define FetchThisOffRange()				\
  /* offset and range are in correct registers */       \
  theObj = (struct Object *) getThisReg();              \


/* ExtRR, ExtVRx, NewRR, NewVRx */
#define ParamObjOffRange(name)			        \
 void name(struct Object *theObj,			\
	   unsigned offset, /* in bytes */              \
	   /*unsigned*/ int range)
#define FetchObjOffRange()				\
  /* all are in correct registers */


/* Copy(S)RR, Copy(S)VR1, Copy(S)VR2, Copy(S)VR4, Copy(S)VR8 */
#define ParamRepObjOff(name)                            \
void name(struct ValRep *theRep,                        \
	  struct Object *theObj,                        \
	  unsigned offset /* in ints */)
#define FetchRepObjOff()				\
  /* all are in correct registers */


/* CopySVRI, CopySVRC, CopyVRI, CopyVRC */
#define ParamORepObjOff(name)                           \
void name(struct ObjectRep *theRep,                     \
	  struct Object *theObj,                        \
	  unsigned offset /* in ints */)
#define FetchORepObjOff()				\
  /* all are in correct registers */


/* CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamRepObjOffLowHigh(name)                     \
void name(struct ValRep *theRep,                        \
	  struct Object *theObj,                        \
	  unsigned offset, /* in ints */                \
	  unsigned low,                                 \
	  long high)
#define FetchRepObjOffLowHigh()				\
  /* all but high are in correct registers */           \
  high = (long) getPrimReg5()


/* CopySVRI, CopySVRC */
#define ParamORepObjOffLowHigh(name)                    \
void name(struct ObjectRep *theRep,                     \
	  struct Object *theObj,                        \
	  unsigned offset, /* in ints */                \
	  unsigned low,                                 \
	  long high)
#define FetchORepObjOffLowHigh()			\
  /* all but high are in correct registers */           \
  high = (long) getPrimReg5()


/* AlloVRI, AlloVRC */
#define ParamObjOriginProtoOffRange(name)		\
 void name(struct Object *origin,			\
	   struct Object *theObj,	                \
	   unsigned offset, /* in bytes */		\
	   int range,			                \
	   struct ProtoType *proto)
#define FetchObjOriginProtoOffRange()			\
  /* origin is in correct register */                   \
  theObj = (struct Object *) getThisReg();              \
  /* offset and range are in correct registers */       \
  proto  = (struct ProtoType *) getCallReg()

/* Wrappers for functions called directly from RTS */
extern struct Component *AlloC();
extern struct Item *AlloI();
extern struct Item *AlloSI();
extern void   AlloRR(unsigned offset, int range, struct Object *theObj);
extern void   AlloVR1(unsigned offset, int range, struct Object *theObj);
extern void   AlloVR2(unsigned offset, int range, struct Object *theObj);
extern void   AlloVR4(unsigned offset, int range, struct Object *theObj);
extern void   AlloVR8(unsigned offset, int range, struct Object *theObj);
extern void   AlloVRI(struct Object *origin,
		      struct Object *theObj,
		      unsigned offset,
		      int range,
		      struct ProtoType *proto);
extern void   AlloVRC(struct Object *origin,
		      struct Object *theObj,
		      unsigned offset,
		      int range,
		      struct ProtoType *proto);

static __inline__ struct Item *CAlloI(struct Object *org, struct ProtoType *prot)
{
  struct Item *item;
  
  pushReference(getCallReg());
  pushReference(getOriginReg());
  setOriginReg(org);
  setCallReg(prot);
  item = (struct Item *)AlloI();
  setOriginReg(popReference());
  setCallReg(popReference());
  return item;
}

static __inline__ struct Component *
  CAlloC(struct Object *org, struct ProtoType *prot)
{
  struct Component *comp;
  
  pushReference(getCallReg());
  pushReference(getOriginReg());
  setOriginReg(org);
  setCallReg(prot);
  comp = AlloC();
  setOriginReg(popReference());
  setCallReg(popReference());
  return comp;
}

static __inline__ struct Item * CAlloSI(struct Structure *s)
{
  struct Item *i;
  
  pushReference(getCallReg());
  setCallReg(s);
  i = AlloSI();
  setCallReg(popReference());
  return i;
}

static __inline__ void 
CAlloRR(unsigned offset, int range, struct Object *theObj)
{
  pushReference(getThisReg());
  setThisReg(theObj);
  AlloRR(offset, range, 0);
  setThisReg(popReference());
}

static __inline__ void 
CAlloVR1(unsigned offset, int range, struct Object *theObj)
{
  pushReference(getThisReg());
  setThisReg(theObj);
  AlloVR1(offset, range, 0);
  setThisReg(popReference());
}

static __inline__ void 
CAlloVR2(unsigned offset, int range, struct Object *theObj)
{
  pushReference(getThisReg());
  setThisReg(theObj);
  AlloVR2(offset, range, 0);
  setThisReg(popReference());
}

static __inline__ void 
CAlloVR4(unsigned offset, int range, struct Object *theObj)
{
  pushReference(getThisReg());
  setThisReg(theObj);
  AlloVR4(offset, range, 0);
  setThisReg(popReference());
}

static __inline__ void 
CAlloVR8(unsigned offset, int range, struct Object *theObj)
{
  pushReference(getThisReg());
  setThisReg(theObj);
  AlloVR8(offset, range, 0);
  setThisReg(popReference());
}

static __inline__ void 
CAlloVRI(struct Object *origin,	
	 struct Object *theObj,	
	 unsigned offset,
	 int range,
	 struct ProtoType *proto)
{
  pushReference(getThisReg());
  pushReference(getCallReg());
  setThisReg(theObj);
  setCallReg(proto);
  AlloVRI(origin, 0, offset, range, 0);
  setCallReg(popReference());
  setThisReg(popReference());
}

static __inline__ void 
CAlloVRC(struct Object *origin,	
	 struct Object *theObj,	
	 unsigned offset,
	 int range,
	 struct ProtoType *proto)
{
  pushReference(getThisReg());
  pushReference(getCallReg());
  setThisReg(theObj);
  setCallReg(proto);
  AlloVRC(origin, 0, offset, range, 0);
  setCallReg(popReference());
  setThisReg(popReference());
}


#define CallBetaEntry(entry,item) \
{                                 \
  /*pushReg(getRefSP()); */       \
  (setCallReg(item), (* (void (*)()) (entry))()); BETA_CLOBBER();  \
  /* setRefSP(popReg()); */       \
}

#define PushGCRegs()                                          \
    __asm__ volatile ("\tLDIL\tLR'RefSP,%r1\n"                    \
		  "\tLDW\tRR'RefSP(%r1),%r14\n"               \
		  "\tSTWS,MA\t%r3,4(0,%r14)\n"  /* r3 (th) */ \
		  "\tSTWS,MA\t%r4,4(0,%r14)\n"  /* r4 (ca) */ \
		  "\tSTWS,MA\t%r5,4(0,%r14)\n"  /* r5 */      \
		  "\tSTWS,MA\t%r6,4(0,%r14)\n"  /* r6 */      \
		  "\tSTWS,MA\t%r7,4(0,%r14)\n"  /* r7 */      \
		  /* r8 is NOT to be GC'ed */                 \
		  "\tSTW\t%r14,RR'RefSP(0,%r1)\n"             \
		  )

#define PopGCRegs()                                           \
    __asm__ volatile ("\tLDIL\tLR'RefSP,%r1\n"                    \
		  "\tLDW\tRR'RefSP(%r1),%r14\n"               \
		  "\tLDWS,MB\t-4(0,%r14),%r7\n"               \
		  "\tLDWS,MB\t-4(0,%r14),%r6\n"               \
		  "\tLDWS,MB\t-4(0,%r14),%r5\n"               \
		  "\tLDWS,MB\t-4(0,%r14),%r4\n"               \
		  "\tLDWS,MB\t-4(0,%r14),%r3\n"               \
		  "\tSTW\t%r14,RR'RefSP(0,%r1)\n"             \
		  )

#define SaveVar(var) pushReference(var)
#define RestoreVar(var) popReference(var)

#define Protect(var, code) \
  pushReference(var); { code; } var = (__typeof__(var))popReference();

#define Protect2(v1, v2, code) \
  pushReference(v1); pushReference(v2); \
  { code; } \
  v2 = (__typeof__(v2))popReference(); v1 = (__typeof__(v1))popReference();

#endif /* ! _SNAKEDEP_H_ */
