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
register long _dummy1 asm("%r3");  /* really th */
register long _dummy2 asm("%r4");  /* really ca */
register long _dummy3 asm("%r5");  /* really or */
register long _dummy33 asm("%r6");  /* really tmp R1 */
register long _dummy37 asm("%r7");  /* really tmp R2 */
register long _dummy4 asm("%r17"); /* really IOAbot */
register long _dummy5 asm("%r18"); /* really IOAsize */
register long _dummy6 asm("%r9");  /* really D0 */
register long _dummy6 asm("%r10");  /* really D1 */
register long _dummy7 asm("%r14"); /* really RefSP */
#endif

/* Tell GCC that some called Beta code has potentially clobbered all these
   registers. */

#define BETA_CLOBBER \
   asm volatile ("" : : : /* "r3", "r4", "r5", "r6", "r7", */ "r8", "r9", \
		 "r10",	"r11", "r12", "r13","r14","r15","r16")

#define asmlabel(label, code) /*nothing*/

#define asmemptylabel(label) \
  /* asm(#label "\n	.EXPORT " #label ",CODE") */

#define asmcomment(text) \
  /* asm(";" #text) */

/*
 * Take care of the reference stack.
 * The reference stack may actually contain two types of pointers, namely
 * pointers to objects in the Beta heap, and pointers to pointers located
 * in the system stack, the pointer in the stack may be NULL or point to
 * an object in the Beta heap. All of this mess exists to make GC work.
 * References to object are not allowed on the system stack, unless they
 * are "registered" on the reference stack.
 */

#define REFSTACK

extern void *ReferenceStack[];
#if 0
extern long *savedRefSP;
#endif

#if 0
static inline void setRefSP(void *p)
{
  asm volatile ("COPY\t%0, %%r14" : /* no out */ : "r" (p)); 
  savedRefSP = (long *)p;
}
#endif

#if 0
static inline void *getRefSP()
{     
  void *res; 
  asm volatile ("COPY\t%%r14, %0" : "=r" (res)); 
  return res;
}
#endif

static inline void pushReference(void *p)
{
  /*fprintf(stdout, "push 0x%x at 0x%x\n", p, RefSP);*/
#if 0
  asm volatile ("STWS,MA\t%0,4(0,%%r14)" : /* no out */ : "r" (p): "%r14");
#else
   *RefSP=(long)p; 
  RefSP++; 
#endif
}

static inline void *popReference()
{
  void *p;
#if 0
  asm volatile ("LDWS,MB\t-4(0,%%r14),%0" : "=r" (p) : : "%r14");
#else
  RefSP--; 
  p=(void *)*RefSP; 
#endif
  /*fprintf(stdout, "pop 0x%x at 0x%x\n", p, RefSP);*/
  return p;
}

static inline void pushReg(void *r) 
{ /* This is how compiler pushes: strange big frame (64)? */
  asm volatile("STW\t%0,-36(0,%%r30)" : /* no out */ : "r" (r));
  asm volatile("LDO\t64(%r30),%r30");
}

static inline void *popReg() 
{ register void *r;
  asm volatile("LDO\t-64(%r30),%r30");
  asm volatile("LDW\t-36(0,%%r30),%0" : "=r" (r) : );
  return r;
}

extern ref(Component) ActiveComponent;
extern ref(CallBackFrame) ActiveCallBackFrame;

static inline long *getThisReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r3, %0" : "=r" (res)); 
  return res;
}

static inline void setThisReg(void *p)
{     
  asm volatile ("COPY\t%0, %%r3" : /* no out */ : "r" (p)); 
}

static inline long *getRetReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r28, %0" : "=r" (res)); 
  return res;
}

static inline long *getCallReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r4, %0" : "=r" (res)); 
  return res;
}

static inline void *setCallReg(void *p)
{     
  asm volatile ("COPY\t%0, %%r4" : /* no out */ : "r" (p));
  return p; /* 'cause it's used in the RETURN macro */
}

static inline long *getR8Reg()
{     
  long *res; 
  asm volatile ("COPY\t%%r8, %0" : "=r" (res)); 
  return res;
}

static inline void setR8Reg(long p)
{     
  asm volatile ("COPY\t%0, %%r8" : /* no out */ : "r" (p));
}

static inline long *getOriginReg()
{     
  /* This is probably a nop in most cases since r26 = first C param */
  long *res; 
  asm volatile ("COPY\t%%r26, %0" : "=r" (res));
  return res;
}

static inline void *setOriginReg(void *p)
{     
  asm volatile ("COPY\t%0, %%r26" : /* no out */ : "r" (p));
  return p;
}

static inline void setD0Reg(long v)
{     
  asm volatile ("COPY\t%0, %%r9" : /* no out */ : "r" (v)); 
}

static inline long getD0Reg()
{ 
  long v;
  asm volatile ("COPY\t%%r9, %0" : "=r" (v)); 
  return v;
}

static inline void setD1Reg(long v)
{     
  asm volatile ("COPY\t%0, %%r10" : /* no out */ : "r" (v) : "r10"); 
}

static inline long getD1Reg()
{ 
  long v;
  asm volatile ("COPY\t%%r10, %0" : "=r" (v)); 
  return v;
}

static inline long getR1Reg()
{ 
  long v;
  asm volatile ("COPY\t%%r15, %0" : "=r" (v)); 
  return v;
}

static inline long getR2Reg()
{ 
  long v;
  asm volatile ("COPY\t%%r16, %0" : "=r" (v)); 
  return v;
}

static inline long getSPReg()
{ 
  long v;
  asm volatile ("COPY\t%%r30, %0" : "=r" (v)); 
  return v;
}

static inline long getRPReg()
{ 
  long v;
  asm volatile ("COPY\t%%r2, %0" : "=r" (v)); 
  return v;
}

/* the typeof() is a GNU feature, it's used to produce fewer warnings */
#define RETURN(v) \
  return (typeof(v))(setCallReg((long *)(v)))

/* Defining this in the head of a module, together with a
   GCable_Entry and GCable_Exit in every routine in that module makes
   the activation record look like BETA, but *BEWARE*!:
   CHECK THAT THE ROUTINE DOESN'T USE ANY STACK, OR LOOSE!!
*/

#ifdef GCable_Module

#define GCable_Entry()
#define GCable_Exit(n) /* modifyRefSP(-n); */

#endif /* GCable_Module */

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

/* old DeclReference1  type * name##Ptr = (type *)newReference(); */

#define ParamOriginProto(t,name)			\
  t name(struct Object *origin, struct ProtoType *proto)

#define FetchOriginProto()			\
  origin = (struct Object *)getOriginReg();	\
  proto  = (struct ProtoType *)getCallReg();

/* C procs that gets this and component */
#define ParamThisComp(t,name)                       \
  t name(struct Item *this, struct Component *comp)

#define ParamObjOffRange(type, name)			\
 type C##name(struct Object *theObj,			\
	      unsigned offset, /* in bytes */		\
	      /*unsigned*/ int range			\
	      )

#define ParamStruc(t, name) \
  t name(struct Structure *struc)

#define FetchThisComp()			\
  this = (struct Item *)getThisReg();	\
  comp = (struct Component *)getCallReg();

#define FetchStruc() struc = cast(Structure) getCallReg();

extern struct Component *AlloC();
extern struct Item *AlloI();
extern struct Item *AlloSI();

static inline struct Item *CAlloI(struct Object *org, struct ProtoType *prot)
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

static inline struct Component *
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

static inline struct Item * CAlloSI(struct Structure *s)
{
    struct Item *i;

    pushReference(getCallReg());
    setCallReg(s);
    i = AlloSI();
    setCallReg(popReference());
    return i;
}

#define CallBetaEntry(entry,item) \
{                                 \
  /*pushReg(getRefSP()); */       \
  (setCallReg(item), (* (void (*)()) (entry))()); BETA_CLOBBER;  \
  /* setRefSP(popReg()); */       \
}

#define PushGCRegs()                                          \
    asm volatile ("\tLDIL\tLR'RefSP,%r1\n"                    \
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
    asm volatile ("\tLDIL\tLR'RefSP,%r1\n"                    \
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
  pushReference(var); { code; } var = (typeof(var))popReference();

#define Protect2(v1, v2, code) \
  pushReference(v1); pushReference(v2); \
  { code; } \
  v2 = (typeof(v2))popReference(); v1 = (typeof(v1))popReference();

extern struct RefRep *		AlloRR(struct Object* theObj, 
				       unsigned offset, 
				       int range);
extern struct ValRep *		AlloVR1(struct Object* theObj, 
					unsigned offset, 
					int range);
extern struct ValRep *		AlloVR2(struct Object* theObj, 
					unsigned offset, 
					int range);
extern struct ValRep *		AlloVR4(struct Object* theObj, 
					unsigned offset,
					int range);
extern struct ValRep *		AlloVR8(struct Object* theObj, 
					unsigned offset, 
					int range);
extern void 			CopyT(char *asciz, 
				      struct Item *theItem,
				      unsigned offset);
#endif /* ! _SNAKEDEP_H_ */
