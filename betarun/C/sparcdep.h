/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992 Mjolner Informatics Aps.
 * Mod: $RCSfile: sparcdep.h,v $, rel: %R%, date: $Date: 1992-08-22 02:06:55 $, SID: $Revision: 1.4 $
 * by Tommy Thorn
 */

/* SPARC Specifics, requires the use of GCC */

#ifndef _SPARC_H_
#define _SPARC_H_ 1

struct RegWin {
    int l0, l1, l2, l3, l4, l5, l6, l7;
    int i0, i1, i2, i3, i4, i5, fp, i7;
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
register volatile void *GCreg2 asm("%o3");
register volatile void *GCreg3 asm("%o4");

#define GCable_Entry \
  StackPointer = FramePointer-16; /* = 64 */ \
  GCreg0 = GCreg1 = GCreg2 = GCreg3 = 0;
#endif

#define DeclReferences1(r1)		\
  register r1 asm("%o4");

#define asmlabel(label, code) \
  asm(".text;.align 4;.global " #label ";" #label ":" code)

/* C procs that gets origin and proto, and return an Object
   That mess of code just moves (i2,i1)->(o0,o1) and jumps
   to Cname
*/

#define ParamOriginProto(name)		          \
  __asm__(".text;.align 4;.global "#name";"#name":\
          mov %i1,%o1;b _C"#name";mov %i2,%o0");\
 void *C##name(struct Object *origin, struct ProtoType *proto)

#define FetchOriginProto

/* C procs that gets this and component */
#define ParamThisComp(name)			  \
  __asm__(".text;.align 4;.global "#name";"#name":\
          mov %i0,%o0;b	_C"#name";mov %i1,%o1");   \
 void C##name(struct Item *this, struct Component *comp)

#define FetchThisComp

/* On the SPARC we need to skip the first instruction */
#define CallBetaEntry(entry,item)			\
  (* (void (*)()) ((long*)entry+1) )(item)

/* Returns value in both C return reg, %o0, and BETA return reg %i1
   so the routine call be called from both C and BETA ;^)
 */
#define ReturnDual(value)					\
  __asm__("mov %0, %%i0;ret;restore %%i0, 0, %%i1"::"r" (value)); \
  return (void *) 0 /* dummy */

#endif
