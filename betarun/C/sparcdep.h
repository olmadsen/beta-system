/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992 Mjolner Informatics Aps.
 * Mod: $RCSfile: sparcdep.h,v $, rel: %R%, date: $Date: 1992-06-15 20:50:36 $, SID: $Revision: 1.1 $
 * by Tommy Thorn
 */

/* SPARC Specifics, requires the use of GCC */

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


