/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * sparcdep.h
 * by Tommy Thorn
 */

/* SPARC Specifics, requires the use of GCC */

#ifndef _SPARC_H_
#define _SPARC_H_ 1

struct RegWin {
    long l0, l1, l2, l3, l4, l5, l6, l7;
    long i0, i1, i2, i3, i4, i5, fp, i7;
};

#ifdef sun4s
#define CPREF "C"
#define USCORE ""
#else
#define CPREF "_C"
#define USCORE "_"
#endif

/*
 * Stack manipulation - special for the SPARC
 *
 * Stack Layout:
 * 	sp	-> <space for l0 .. l7 registers>
 * 	sp+32	-> <space for i0 .. i7 registers>
 *	sp+64	-> <top of stack value>
 *
 * sp must be 8 byte aligned
 *
 * Instead of pushing a component block to the stack, it resides
 * in registers %l5 - %l7 of the coresponding reg.window
 */

#define setret(newret) (retAddress = (long) (newret))
#define getret(saved) (saved = retAddress)

/* Various machine instructions */
#define RETL 0x81c3e008
#define MOV_O7_G1 0x8210000f
#define MK_CALL(p,f) \
  (*(long *)p = 0x40000000| (((unsigned) ((char*)f-(char*)p)) >> 2))
#define NOP 0x1000000

/* Defining this in the head of a module, together with a
   GCable_Entry and GCable_Exit in every routine in that module makes
   the activation record look like BETA, but *BEWARE*!:
   CHECK THAT THE ROUTINE DOESN'T USE ANY STACK, OR LOOSE!!
*/

#ifdef GCable_Module
register volatile void *GCreg0 asm("%o0");
register volatile void *GCreg1 asm("%o1");
register volatile void *GCreg2 asm("%o2");
register volatile void *GCreg3 asm("%o3");
register volatile void *GCreg4 asm("%o4");

#define GCable_Entry() \
  StackPointer = FramePointer-16; /* = 64 */ \
  GCreg0 = GCreg1 = GCreg2 = GCreg3 = GCreg4 = 0

#define GCable_Exit(n) /* nothing on the sparc */
#endif /* GCable_Module */

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

#define asmlabel(label, code) \
  __asm__(".text; .align 4; .global " #label ";" #label ": " code)

#define asmcomment(text) \
  __asm__("! " #text)


#define RETURN(v) return v

#define return_in_i1(value)                             \
    __asm__ volatile("":: "r" (value));                 \
    __asm__("ret; restore %0, 0, %%i1"::"r" (value));   \
    return value /* keep gcc happy */

#define FetchOriginProto()
#define FetchThisComp()
#define FetchThis()
#define FetchStruc()

#define SaveVar(var) push(var)
#define RestoreVar(var) pop(var)

/* C procs that gets origin and proto, and return an Object */

#define ParamOriginProto(type, name)			\
  asmlabel(name,					\
	   "clr %o1;"					\
	   "clr %o3;"					\
	   "clr %o4;"					\
	   "ba "CPREF#name";"				\
	   "mov %i1,%o2;"				\
	   );			                        \
  type C##name(struct Object *origin,                   \
               int i1,                                  \
               struct ProtoType *proto,                 \
               int i3,                                  \
               int i4)


/* C procs that gets this and component */
#define ParamThisComp(type, name)			\
  asmlabel(name, 					\
	   "clr %o3; "					\
	   "clr %o4; "					\
	   "mov %i0,%o0; "				\
	   "ba "CPREF#name"; "				\
	   "mov %i1,%o1");				\
 type C##name(struct Object *this, struct Component *comp,\
              int i2, int i3, int i4)


/* C procs that gets this */
#define ParamThis(type, name)	\
  asmlabel(name, 		\
	   "clr %o1; " 		\
	   "clr %o3; "		\
	   "clr %o4; "		\
	   "ba "CPREF#name"; "	\
	   "mov %i0,%o0; ");	\
 type C##name(struct Object *this, int i1, int i2, int i3, int i4)

/* C procs that gets a Structure parameter, and returns in this */
#define ParamStruc(type, name)				\
  asmlabel(name,					\
	   "clr %o1;"					\
	   "clr %o3;"					\
	   "clr %o4;"					\
	   "ba "CPREF#name";"				\
	   "mov %i1,%o0;"				\
	   );			                        \
 type C##name(struct Structure *struc, int i1, int i2, int i3, int i4)

/* C procs that uses this, offset and range */
#define ParamThisOffRange(name)		        	\
  asmlabel(name, 					\
           "mov %o1, %o5; " /* range */			\
           "mov %o0, %o2; " /* offset */		\
	   "mov %i0, %o0; " /* this */			\
           "clr %o1; "					\
           "clr %o3; "					\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(struct Object *theObj,			\
	      int i1,					\
	      unsigned offset, /* in bytes */		\
	      int i3,					\
	      int i4,					\
	      /*unsigned*/ int range)

/* C procs that uses a specified object, offset and range */
#define ParamObjOffRange(name)			        \
  asmlabel(name, 					\
           "mov %o1, %o5; " /* offset */		\
           "clr %o1; "					\
           "clr %o3; "					\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(struct Object *theObj,			\
	      int i1,					\
	      /*unsigned*/ int range,                   \
	      int i3,					\
	      int i4,					\
	      unsigned offset /* in bytes */)

#define ParamRepObjOff(name)                            \
void name(struct ValRep *theRep,                        \
	   struct Object *theObj,                       \
	   unsigned offset /* in ints */)

#define ParamORepObjOff(name)                           \
void name(struct ObjectRep *theRep,                     \
	   struct Object *theObj,                       \
	   unsigned offset /* in ints */)

#define ParamRepObjOffLowHigh(name)                     \
void name(struct ValRep *theRep,                        \
	   struct Object *theObj,                       \
	   unsigned offset, /* in ints */               \
           unsigned low,                                \
	   long high)

#define ParamORepObjOffLowHigh(name)                    \
void name(struct ObjectRep *theRep,                     \
	   struct Object *theObj,                       \
	   unsigned offset, /* in ints */               \
           unsigned low,                                \
	   long high)

/* C procs that gets object, origin, prototype, offset, range,  */
#define ParamObjOriginProtoOffRange(name)		\
  asmlabel(name, 					\
           "mov %i1, %o5; " /* proto */			\
	   "mov %i0, %o1; " /* theObj */		\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(struct Object *origin,			\
	      struct Object *theObj,	                \
	      unsigned offset, /* in bytes */		\
	      int range,			        \
	      int i4,					\
	      struct ProtoType *proto)

/* On the SPARC we need to skip the first instruction */
#define CallBetaEntry(entry,item)			\
    (* (void (*)()) ((long*)entry+1) )(item);

#ifdef RTVALHALLA
#define ValhallaCallBetaEntry(entry,item,event)		\
    ValhallaOnProcessStop ((long*)entry+2,0,0,0,event); \
    (* (void (*)()) ((long*)entry+1) )(item);
#endif

#define push(v) (StackPointer -= 2, StackPointer[16] = (long) v)
#define pop(v) (((long)v) = StackPointer[16], StackPointer += 2)

#define Protect(var, code)				\
  push(var);						\
  { code; }						\
  pop(var);						\

#define Protect2(v1, v2, code)				\
  push(v1); push(v2);					\
  { code; }						\
  pop(v2); pop(v1);					\

static inline void USE()
{ int x;
  x=(int)IOA;
  x=(int)IOATopOff;
  x=(int)StackPointer;
  x=(int)FramePointer;
  x=(int)retAddress;
}

/* Routines called from others */
extern ref(Item) CCopyT  (int, ref(Item), unsigned, int, int, char *);
extern void      CAlloRR (ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR1(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR2(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR4(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR8(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVRI(ref(Object), ref(Object), unsigned, int, int, ref(ProtoType));
extern void      CAlloVRC(ref(Object), ref(Object), unsigned, int, int, ref(ProtoType));

#endif /* _SPARC_H_ */
