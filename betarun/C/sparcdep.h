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

/* Heap:
   
   IOA:
      .
      .
      IOA+IOATopoff: First available byte
      .
      .
   IOALimit: First not available byte
*/

#ifdef sun4s
#define CPREF "C"
#define USCORE ""
#else
#define CPREF "_C"
#define USCORE "_"
#endif

register long *IOA asm("%g6");
register unsigned IOATopoff asm("%g7");

#define IOATop ((long *) ((char *)IOA+IOATopoff))

/* Refcheck: R[] -> S[];
    R[] in %l1 and S[] at %l2+Soff
    check for %l2+SOFF in [IOA, IOA+IOATopoff]
    notice that we can ignore the +Soff part

    sub	%l2, IOA, %g1
    cmp %g1, IOATopoff
    bltu 1f		! Branch if (unsigned)(%l2-IOA) < IOATopoff
    st  %l1, [%l2+Soff]

    ! We were storing in an old cell

    call CheckReferenceAssignment
    add  %l2, Soff, %o2  ! check that %o2 is the correct register

1:
*/
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

extern ref(Component) ActiveComponent;
extern ref(CallBackFrame) ActiveCallBackFrame;

register long * StackPointer asm("%sp");
register long * FramePointer asm("%fp");
register long   retAddress   asm("%i7");

#define setret(newret) (retAddress = (long) (newret))
#define getret(saved) (saved = retAddress)

/* Various machine instructions */
#define RETL 0x81c3e008
#define MOV_O7_G1 0x8210000f
#define MK_CALL(p,f) \
  (*(long *)p = 0x40000000| (((unsigned) ((char*)f-(char*)p)) >> 2))
#define NOP 0x1000000


/* Redefine inIOA as to make gcc generate optimal code */
#ifdef inIOA
#undef inIOA
#endif

/* Isn't life swell? This generates optimal code $^)*/
#define inIOA(x) (((unsigned) x - (unsigned) IOA) < (unsigned) IOATopoff)


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
#endif

#ifdef wasnotwas
# define DeclReference1(type, name) register type name asm("%o4")
# define DeclReference2(type, name) register type name asm("%o3")
#else
# define DeclReference1(type, name) type name
# define DeclReference2(type, name) type name
#endif

#define RETURN(v) return v

#define asmlabel(label, code) \
  __asm__(".text; .align 4; .global " #label ";" #label ": " code)

#define asmemptylabel(label) \
  __asm__(".text;.align 4;.global " #label ";" #label ":" )

#define asmcomment(text) \
  __asm__("! " #text)


#define return_in_i1(value)                             \
    __asm__ volatile("":: "r" (value));                 \
    __asm__("ret; restore %0, 0, %%i1"::"r" (value));   \
    return value /* keeps gcc happy */

/* C procs that gets origin and proto, and return an Object
   That mess of code just moves i1->o1 and jumps
   to Cname
*/

#define ParamOriginProto(type, name)			\
  asmlabel(name,					\
	   "clr %o1;"					\
	   "clr %o3;"					\
	   "clr %o4;"					\
	   "ba "CPREF#name";"				\
	   "mov %i1,%o2;"				\
	   );			                        \
  type C##name(struct Object *origin, int i1, \
               struct ProtoType *proto, int i3, int i4)

#define FetchOriginProto()

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

#define FetchThisComp()

/* C procs that gets this */
#define ParamThis(type, name)	\
  asmlabel(name, 		\
	   "clr %o1; " 		\
	   "clr %o3; "		\
	   "clr %o4; "		\
	   "ba "CPREF#name"; "	\
	   "mov %i0,%o0; ");	\
 type C##name(struct Object *this, int i1, int i2, int i3, int i4)

#define FetchThis()

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

#define FetchStruc()

/* C procs that gets object, offset and range */
#define ParamObjOffRange(type, name)			\
  asmlabel(name, 					\
	   "mov %i0, %o0; "				\
           "clr %o1; "					\
           "mov %l0, %o2; "				\
           "clr %o3; "					\
           "clr %o4; "					\
	   "ba "CPREF#name"; "				\
	   "mov %l1, %o5; ");				\
 type C##name(struct Object *theObj,			\
	      int i1,					\
	      unsigned offset, /* in bytes */		\
	      int i3,					\
	      int i4,					\
	      /*unsigned*/ int range)

/* On the SPARC we need to skip the first instruction */
#define CallBetaEntry(entry,item)			\
    (* (void (*)()) ((long*)entry+1) )(item);

/* The asm's tell GCC that 'var' is read and modified in 'code' */

#ifdef wasnotwas
#define Protect(var, code)				\
  { code; }			     			\
  __asm__ volatile("":: "r" (var));			\
  __asm__ volatile("": "=r" (var))

#define Protect2(v1, v2, code) \
  { code; }						\
  __asm__ volatile("":: "r" (v1), "r" (v2));		\
  __asm__ volatile("": "=r" (v1), "=r" (v2))
#endif

#define push(v) (StackPointer -= 2, StackPointer[16] = (long) v)
#define pop(v) (((long)v) = StackPointer[16], StackPointer += 2)

#define Protect(var, code)				\
  asmcomment( -- Protect-start);			\
  push(var);						\
  { code; }						\
  pop(var);						\
  asmcomment( -- Protect-end)

#define Protect2(v1, v2, code)				\
  asmcomment( -- Protect-start);			\
  push(v1); push(v2);					\
  { code; }						\
  pop(v2); pop(v1);					\
  asmcomment( -- Protect-end)

#define ClearCParams() \
  FramePointer[16] =   \
  FramePointer[17] =   \
  FramePointer[18] =   \
  FramePointer[19] =   \
  FramePointer[20] =   \
  FramePointer[21] =   \
  FramePointer[22] =   \
  FramePointer[23] =   \
  FramePointer[24] =   \
  FramePointer[25] =   \
  FramePointer[26] =   \
  FramePointer[27] = 0

#endif

static inline void USE()
{ int x;
  x=(int)IOA;
  x=(int)IOATopoff;
  x=(int)StackPointer;
  x=(int)FramePointer;
  x=(int)retAddress;
}

extern ref(RefRep) CAlloRR(struct Object *theObj,
			   int i1,
			   unsigned offset, /* in bytes */
			   int i3,
			   int i4,
			   /*unsigned*/ int range);
extern ref(ValRep) CAlloVR1(struct Object *theObj,
			    int i1,
			    unsigned offset, /* in bytes */
			    int i3,
			    int i4,
			    /*unsigned*/ int range);
extern ref(ValRep) CAlloVR2(struct Object *theObj,
			    int i1,
			    unsigned offset, /* in bytes */
			    int i3,
			    int i4,
			    /*unsigned*/ int range);
extern ref(ValRep) CAlloVR4(struct Object *theObj,
			    int i1,
			    unsigned offset, /* in bytes */
			    int i3,
			    int i4,
			    /*unsigned*/ int range);
extern ref(ValRep) CAlloVR8(struct Object *theObj,
			    int i1,
			    unsigned offset, /* in bytes */
			    int i3,
			    int i4,
			    /*unsigned*/ int range);
extern void CCopyT(int i0,
		   ref(Item) theItem,
		   unsigned offset, /* i ints */
		   int i3,
		   int i4,
		   char *asciz
		   );
