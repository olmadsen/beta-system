#ifndef _SNAKEDEP_H_
#define _SNAKEDEP_H_

/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992 Mjolner Informatics Aps.
 * Mod: $Id: snakedep.h,v 1.5 1992-09-03 12:54:33 beta Exp $
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
   and allow GCC to use the register */

register int _dummy1 asm("%r3");  /* really th */
register int _dummy2 asm("%r4");  /* really ca */
register int _dummy3 asm("%r5");  /* really or */
register int _dummy33 asm("%r6");  /* really tmp R1 */
register int _dummy37 asm("%r7");  /* really tmp R2 */
register int _dummy4 asm("%r17"); /* really IOAbot */
register int _dummy5 asm("%r18"); /* really IOAsize */
register int _dummy6 asm("%r9");  /* really D0 */
register int _dummy6 asm("%r10");  /* really D1 */
register int _dummy7 asm("%r14"); /* really RefSP */

/* Tell GCC that some called Beta code has potentially clobbered all these
   registers. */

#define BETA_CLOBBER \
   asm volatile ("" : : : /* "r3", "r4", "r5", "r6", "r7", */ "r8", "r9", \
		 "r10",	"r11", "r12", "r13","r14","r15","r16")

#define asmlabel(label, code) /*nothing*/

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
/* extern void *lastRefBlock; */

static inline void setRefSP(void *p)
{
  asm volatile ("COPY\t%0, %%r14" : /* no out */ : "r" (p)); 
}

static inline void *getRefSP()
{     
  void *res; 
  asm volatile ("COPY\t%%r14, %0" : "=r" (res)); 
  return res;
}

static inline void *newReference(void)
{
  void *res;
  asm volatile ("STWS,MB\t%%r0,4(0,%%r14)\n\tCOPY\t%%r14,%0" : "=r" (res));
  return res;
}

static inline void pushReference(void *p)
{
  asm volatile ("STWS,MB\t%0,4(0,%%r14)" : /* no out */ : "r" (p));
}

static inline void *popReference()
{
  void *p;
  asm volatile ("LDWS,MA\t-4(0,%%r14),%0" : "=r" (p) : );
  return p;
}

static inline void modifyRefSP(const int n)
{
  asm volatile ("LDO\t%0(%%r14),%%r14" : /* no out */ : "i" (n<<2));
}

/*
 * get and set IOA registers.
 */

static inline long *getIOAReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r17, %0" : "=r" (res)); 
  return res;
}


static inline void setIOAReg(long *p)
{     
  asm volatile ("COPY\t%0, %%r17" : /* no out */ : "r" (p)); 
}

static inline unsigned getIOATopoffReg()
{     
  unsigned res; 
  asm volatile ("COPY\t%%r18, %0" : "=r" (res)); 
  return res;
}

static inline void setIOATopoffReg(unsigned v)
{     
  asm volatile ("COPY\t%0, %%r18" : /* no out */ : "r" (v)); 
}

#define IOA    getIOAReg()
#define IOATop ((long *) ((char *)getIOAReg()+getIOATopoffReg()))

extern ref(Component) ActiveComponent;
extern ref(CallBackFrame) ActiveCallBackFrame;

static inline long *getThisReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r3, %0" : "=r" (res)); 
  return res;
}

static inline void setThisReg(long *p)
{     
  asm volatile ("COPY\t%0, %%r3" : /* no out */ : "r" (p)); 
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

static inline long *getOriginReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r5, %0" : "=r" (res)); 
  return res;
}

static inline void *setOriginReg(void *p)
{     
  asm volatile ("COPY\t%0, %%r5" : /* no out */ : "r" (p));
  return p;
}

static inline void setD0Reg(int v)
{     
  asm volatile ("COPY\t%0, %%r9" : /* no out */ : "r" (v)); 
}

static inline long getD0Reg()
{ 
  long v;
  asm volatile ("COPY\t%%r9, %0" : "=r" (v)); 
  return v;
}

static inline void setD1Reg(int v)
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

/* Redefine inIOA as to make gcc generate optimal code */
#ifdef inIOA
#undef inIOA
#endif

/* Isn't life swell? */
#define inIOA(x) (((unsigned) x - (unsigned) getIOAReg()) < (unsigned) getIOATopoffReg())


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

#define FetchOriginProto			\
  origin = (struct Object *)getOriginReg();	\
  proto  = (struct ProtoType *)getCallReg();

/* C procs that gets this and component */
#define ParamThisComp(t,name)                       \
  t name(struct Item *this, struct Component *comp)

#define ParamStruc(t, name) \
  t name(struct Structure *struc)

#define FetchThisComp			\
  this = (struct Item *)getThisReg();	\
  comp = (struct Component *)getCallReg();

#define FetchStruc struc = cast(Structure) getCallReg();

extern struct Component *AlloC();
extern struct Item *AlloI();

static inline struct Item *CAlloI(struct Object *org, struct ProtoType *prot)
{
  setOriginReg(org);
  setCallReg(prot);
  return((struct Item *)AlloI());
}

static inline struct Component *
  CAlloC(struct Object *org, struct ProtoType *prot)
{
  setOriginReg(org);
  setCallReg(prot);
  return((struct Component *)AlloC());
}

#define CallBetaEntry(entry,item)       \
  (setCallReg(item), (* (void (*)()) (entry))()); BETA_CLOBBER

#define Protect(var, code) \
  pushReference(var); { code; } var = (typeof(var))popReference();

#define Protect2(v1, v2, code) \
  pushReference(v1); pushReference(v2); \
  { code; } \
  v2 = (typeof(v2))popReference(); v1 = (typeof(v1))popReference();

#endif /* ! _SNAKEDEP_H_ */
