/* Created by Soren Brandt.
 * 
 * Necessary low level additions to the BETA RTS needed to handle
 * lazy references to persistent objects. In addition a number of 
 * changes has been made to other parts of the runtime system.
 * These changes are all enclosed in #ifdef RTLAZY to be able
 * to compile the RTS without them.
 *
 * Apart from generic tables containing different information on
 * dangling references, this file implements trap handling for
 * sparc and HP UX 8 with motorola 680x0.
 *
 * On linux, nti and mac, most work is done in BetaError in exit.c
 * and in RefNone in Misc.run, Qua (Qua.run) and ChkRA 
 * (CheckReferenceAssignment.run).
 * Corresponding changes for the C runtime system are made in Misc.c, Qua.c
 * and CheckReferenceAssignment.c. */

#if defined(macintosh) || defined(nti) || defined(MAC)
#include "beta.h"
#include "data.h"
#else
#include <C/beta.h>
#include <C/data.h>
#endif

#ifdef sparc
#include <CRUN/crun.h>
#endif

/* #define LAZYDEBUG 1 */

static int negAOAmax = 0; 
/* Max number of integers possible to put into the negAOArefs table. */

static int negIOAsize = 0; 
/* Current number of entries in the negIOArefs table. */

static int negIOAmax = 0; 
/* Max number of integers possible to put into the negIOArefs table. */

#define DEFAULTNEGTABLESIZE 25

void NegAOArefsRESET (void) { negAOAsize = 0; }
void negIOArefsFREE (void) { FREE (negIOArefs); negIOArefs = 0; }
   
void NegAOArefsINSERT(long fieldAdr)  
{     
  if (negAOAsize == negAOAmax)
    if (negAOAmax == 0) {
      negAOAmax = DEFAULTNEGTABLESIZE;
      negAOArefs = (long *) MALLOC (negAOAmax*sizeof(long));
    } else {
      negAOAmax = 2*negAOAmax;
      negAOArefs = (long *) REALLOC (negAOArefs, negAOAmax*sizeof(long));
    }

  /* fprintf (stderr, "NegAOArefsINSERT(%d)\n", *((int *) fieldAdr)); */

  negAOArefs[negAOAsize++] = fieldAdr;
}


void NegIOArefsINSERT(long fieldAdr)
{
  if (negIOAsize == negIOAmax) {
    negIOAmax = 2*negIOAmax;
    negIOArefs = (long *) REALLOC (negIOArefs, negIOAmax*sizeof(int));
  }

  /* fprintf (stderr, "NegIOArefsINSERT(%d)\n", *((int *) fieldAdr)); */

  negIOArefs[negIOAsize++] = fieldAdr;
}


void preLazyGC ()
{
  /* fprintf (stderr, "preLazyGC\n"); */
  negIOAsize = 0; 
  negIOAmax = DEFAULTNEGTABLESIZE;
  negIOArefs = (long *) MALLOC (negIOAmax*sizeof(int));
  /* fprintf (stderr, "preLazyGC done\n"); */
}

#if defined(macintosh) || defined(nti) || defined(MAC)
static int danglerLookup (int* danglers, int low, int high, int dangler)
#else
static inline int danglerLookup (int* danglers, int low, int high, int dangler)
#endif
{ int mid;

  /* fprintf (stderr, "danglerLookup(%d)\n", dangler); */

  while (low != high) {
    mid = (low+high)/2;

    if (danglers[mid] < dangler)
      low = mid + 1;
    else
      high = mid; 
  }

  if (danglers[low] == dangler)
    return low;
  else
    return -1;
} 

int getNextDangler ()
{
  lastDangler--;
  return lastDangler;
}

#ifndef sparc
#if defined(macintosh) || defined(nti) || defined(MAC)
   static void
#else
   static inline void
#endif

AssignReference(long *theCell, ref(Item) newObject)
/* If theCell is in AOA and will now reference an object in IOA, then insert in table */
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert((handle(Object))theCell);
}
#endif


void setupDanglers (int* danglers, long* objects, int count)
{ int i, dangler, inx;

  /* fprintf (stderr, "setupDanglers\n"); */

  for (i = 0; i < negIOAsize; i++) {
    dangler = (*((int *) negIOArefs[i]));
    if (isLazyRef(dangler))
      if ((inx = danglerLookup (danglers, 0, count - 1, dangler)) >= 0) {
	/* fprintf (stderr, "setupDanglerIOA(%d)\n", dangler); */
	/*if (!inIOA(negIOArefs[i]))*/
#ifdef UseRefStack
	if ( ((long)&ReferenceStack[0] <= negIOArefs[i]) &&
	     (negIOArefs[i]< (long)RefSP))
#else
	if (negIOArefs[i] >= (long) BetaStackTop)
#endif
	  /* Dangling reference on processor stack. AssignReference
           * would believe that negIOArefs[i] is in AOA and as a result
           * put it into AOAtoIOAtable if objects[inx] is in IOA. 
           * We surely do not want that. 
	   */
	  (*((long *) negIOArefs[i])) = objects[inx];
	else
	  AssignReference ((long *) negIOArefs[i], cast(Item) objects[inx]);
      }
  }
  
  negIOArefsFREE();

  if (negAOArefs) {
    i = 0;
    while (i < negAOAsize) {
      dangler = (*((int *) negAOArefs[i]));
      if (isLazyRef(dangler)) {
	if ((inx = danglerLookup (danglers, 0, count - 1, dangler)) >= 0) {
	  /* fprintf (stderr, "setupDanglerAOA(%d)\n", dangler); */
	  AssignReference ((long *) negAOArefs[i], cast(Item) objects[inx]);
	  negAOAsize--;
	  if (negAOAsize > 0) negAOArefs[i] = negAOArefs[negAOAsize];
	} else {
	  i++;
	}
      } else {
	negAOAsize--;
	if (negAOAsize > 0) negAOArefs[i] = negAOArefs[negAOAsize];
      }
    }
  }
}
                          

typedef struct pNode *protoPtr;

typedef struct pNode {
  int dangler, proto;
  protoPtr next, prev;
} protoElm;

static protoPtr *roots = 0;

#define ROOTSIZE 5879

void addDanglingProto (int dangler, int proto)
/* proto is the prototype of the object referred by dangler.
 * dangler is _not_ in this table already. */
{ int inx;
  protoPtr new;

  /* printf ("addDanglingProto(%d)\n", dangler); */
  
  if (!roots)
    roots = (protoPtr *) calloc (ROOTSIZE,sizeof(protoPtr));
  
  inx = (-dangler)%ROOTSIZE;

  new = (protoPtr) MALLOC (sizeof(protoElm));
  new->proto = proto;
  new->dangler = dangler;
  
  if (roots[inx]) {
    new->next = roots[inx];
    new->prev = NULL;
    roots[inx] = new->next->prev = new;
  }else{
    new->next = new->prev = NULL;
    roots[inx] = new;
  }
  
}

void removeDanglingProto (int dangler)
/* dangler has been fetched. Forget its prototype. */
{ int inx;
  protoPtr this;

  /* printf ("removeDanglingProto(%d)\n",dangler); */
  
  inx = (-dangler)%ROOTSIZE;
  this = roots[inx];

  while (this) {
    if (this->dangler == dangler) {
      if (this->next) this->next->prev = this->prev;
      if (this->prev) this->prev->next = this->next;
      else roots[inx] = this->next;
      
      FREE (this);
    }
    this = this->next;
  }
}

int FindDanglingProto (int dangler)
{ int inx;
  protoPtr this;
  
  inx = (-dangler)%ROOTSIZE;
  this = roots[inx];

  while (this) {
    if (this->dangler == dangler) {
      return this->proto;
    }
    this = this->next;
  }

  fprintf(output, "Fatal Error: Prototype of Dangling ref not found\n");
  return 0;
}

static volatile int returnPC;
static volatile int returnSP;

#include <signal.h>

/* Reference is NONE checks are handled as follows:
 *
 *
 * MC680xx:
 *      mov.l offset(%an), %dm
 *      tle
 *
 * The move instruction has the following format.
 * 
 * MC680xx:  15 14    13 12    11 10 9  8 7 6     5 4 3  2 1 0
 *                              Destination         Source
 *            0  0    size       reg    mode       mode   reg
 *  
 *           The format expected is  mov.l offset(%an), %dm giving
 *           rise to size = 2, destReg = m, destMode = 0, 
 *           sourceReg = n, sourceMode = 5
 *           and a 16 bit offset in the word following the instruction.
 *
 * 
 * 
 * 
 * SPARC: 
 *      tst %in         (pseudo instruction for orcc %g0, %in, %g0)
 *      tle 17
 * 
 * The tst (xorcc) instruction should thus have the following format.
 *
 * SPARC: 31 30  29 28 27 26 25  24 23 22 21 20 19   18 17 16 15 14
 *                  DestReg         orcc opcode         Source1    
 *         1  0   0  0  0  0  0   0  1  0  0  1  0    0  0  0  0  0
 * 
 *   13  12 11 10 9 8 7 6 5  4 3 2 1 0
 *          Dummys            Source2
 *    0                      ? ? ? ? ?
 *
 *
 * 
 * HP PA: ???
 *
 */


/* SPARC
 * ===== */

#ifdef sparc

#ifdef sun4s
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#else
#include <machine/trap.h>
#endif

#define KnownMask 0x80900000
#define instructionOk(instruction) ((instruction & KnownMask) == (KnownMask))
#define sourceReg(instruction) (instruction & 0x0000001F)

/* Temporary neccessary for trapHandler: */
static volatile int smask;

#ifdef sun4s
void trapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
#else
void trapHandler (int sig, int code, struct sigcontext *scp, char *addr)
#endif
{ int instruction;

#ifdef LAZYDEBUG
  fprintf (stderr, "trapHandler\n");
#endif

#ifdef sun4s  
  if (info->_data._fault._trapno - 0x80 == 17) {
#else
  if (code == ILL_TRAP_FAULT(17)) {
#endif

#ifdef LAZYDEBUG
    fprintf (stderr, "Caused by trap no 17\n");
#endif

    /* Ok, the signal was caused by a "tle 17" trap, meaning either
     * "reference is NONE" or dereference of a dangling reference */
    
    /* Fetch the 'tst %lm' instruction. */
#ifdef sun4s
    instruction = (* (long *) (ucon->uc_mcontext.gregs[REG_PC] - 4));
#else
    instruction = (* (long *) (scp->sc_pc - 4));
#endif

    if (instructionOk(instruction)) {

#ifdef LAZYDEBUG
      fprintf (stderr, "Instruction format ok\n");
#endif

      if (LazyDangler) 
	fprintf (stderr, "WARNING: Lazy trap handler reentered\n");

#ifdef sun4s 
      /* PC to jump to when fetch has completed: */
      returnPC = ucon->uc_mcontext.gregs[REG_PC] - 4; 
      /* SP to restore when fetch has completed: */
      returnSP = ucon->uc_mcontext.gregs[REG_SP]; 
#else      
      returnPC = scp->sc_pc-4; /* PC to jump to when fetch has completed. */
      returnSP = scp->sc_sp;   /* SP to restore when fetch has completed. */
#endif

      /* flush register windows to stack and fetch value of register causing
       * the trap. */
      asm volatile  ("ta 3");

      /* LazyDangler = ((int *) returnSP)[sourceReg(instruction) - 26]; */
      LazyDangler = ((int *) returnSP)[sourceReg(instruction) - 16];

#ifdef LAZYDEBUG
      fprintf (stderr, "returnPC = 0x%x, LazyDangler = %d, sourceReg = %d\n", 
	       returnPC, LazyDangler, sourceReg(instruction));
#endif
      
      if (isLazyRef(LazyDangler)) {

	/* Ok, so this is a genuine lazy reference, and not simply a NONE
	 * reference. */

#ifdef LAZYDEBUG
      fprintf (stderr, "It was actually a dangler\n");
#endif

	/* Return to trap window. */
	asm volatile ("restore; restore ! return to trap window");
      
	/* Now we are back in the register window where the trap occurred.
	 * Only global registers may be changed. Now reset correct sp. (UNIX 
	 * pushed some information on the stack). */
#ifdef sun4s 
	asm volatile ("sethi %hi(returnSP),%g1 ! reset sp to returnSP");
	asm volatile ("ld [%g1+%lo(returnSP)],%sp");
#else
	asm volatile ("sethi %hi(_returnSP),%g1 ! reset sp to returnSP");
	asm volatile ("ld [%g1+%lo(_returnSP)],%sp");
#endif    
	
	/* Allocate a new register window to avoid changing trap registers. */
	asm volatile ("save %sp,-64,%sp ! save trap window");
	
	/* Tell compiler to assume nothing about register contents: */
	asm volatile ("" : : : "i0", "i1", "i2", "i3", "i4", "i5", "fp", "i7",\
		      "o0", "o1", "o2", "o3", "o4", "o5", "sp", "o7", \
		      "l0", "l1", "l2", "l3", "l4", "l5", "l6", "l7");
      

#ifndef sun4s
	/* Unblock SIGILL signal: */
	smask = (~sigmask (SIGILL)) & sigsetmask (0);
	sigsetmask (smask);
	
	/* Make sure signal handler is reinstalled. */
	signal (SIGILL, (void (*)(int)) trapHandler);
#endif
	
        /* Save and then clear 'i' registers to avoid strange GC behaviour. 
	 * The i registers are the o registers of the trap frame. They may
	 * contain garbage that should not be interpreted as objects. */

	asm volatile ("mov %i0,%l0; set 0,%i0   ! Save and clear i registers");
	asm volatile ("mov %i1,%l1; set 0,%i1");
	asm volatile ("mov %i2,%l2; set 0,%i2");
	asm volatile ("mov %i3,%l3; set 0,%i3");
	asm volatile ("mov %i4,%l4; set 0,%i4");
	
	/* call beta object handling the lazy fetch */
#ifdef sun4s
	asm volatile ("sethi %hi(LazyItem),%i1  ! Call BETA lazy handler");
	asm volatile ("ld [%i1+%lo(LazyItem)],%i1 ! Object in %i1");
#else
	asm volatile ("sethi %hi(_LazyItem),%i1  ! Call BETA lazy handler");
	asm volatile ("ld [%i1+%lo(_LazyItem)],%i1 ! Object in %i1");
#endif
	asm volatile ("ld [%i1],%g1 ! Prototype in %g1");
	asm volatile ("ld [%g1+-4],%g1 ! Entry point in %g1");
	asm volatile ("call %g1; nop");

        /* Restore 'i' registers. */
	
	asm volatile ("mov %l0,%i0 ! Restore i registers");
	asm volatile ("mov %l1,%i1");
	asm volatile ("mov %l2,%i2");
	asm volatile ("mov %l3,%i3");
	asm volatile ("mov %l4,%i4");

	/* Get back to returnPC and continue from there. */
#ifdef sun4s
	asm volatile ("sethi %hi(returnPC),%g1  ! Jump back to before trap");
	asm volatile ("ld [%g1+%lo(returnPC)],%g1");
#else
	asm volatile ("sethi %hi(_returnPC),%g1  ! Jump back to before trap");
	asm volatile ("ld [%g1+%lo(_returnPC)],%g1");
#endif
	asm volatile ("restore");
	asm volatile ("jmp %g1; nop");
      } 
    } 
#ifdef LAZYDEBUG
    else {
      fprintf (stderr, "Unexpected instruction format\n");
    }
#endif
  }

  /* If we get here, it was not a lazy reference. Call the usual 
   * BetaSignalHandler. */
#ifdef sun4s
  BetaSignalHandler (sig, info, ucon);
#else
  BetaSignalHandler (sig, code, scp, addr);
#endif
  LazyDangler = 0; 
}

#endif




/* MC680?0 HP-UX 8
 * =============== */


#if defined(hpux) && !defined(hppa)

#include <machine/trap.h>

#define isMoveInstruction(instruction) ((0xC0000000 & instruction) == 0)
#define destReg(moveInstruction) ((0x0E000000 & moveInstruction) >> 25)
#define addressRegInx(n) 8+n
#define dataRegInx(n) n
#define movInstOffset 6
  
static int allregs[16];
static int returnSP;

void trapHandler (int sig, int code, struct sigcontext *scp, char *addr)
{   
  struct exception_stack* es;  /* From <machine/trap.h> */
  int i, movInst;
  long newObjectAddr;

  /* fprintf (stderr, "trapHandler\n"); */
  
  if (LazyDangler) 
    fprintf (stderr, "WARNING: Lazy trap handler reentered\n");
      
  es = (struct exception_stack*) (((long) &addr) + ((long) 32));
  
  /* if code == 7 it has been a tle instruction 
   *      => zero or negative reference.
   */
  
  if (code == 7) {

    /* Fetch the move instruction. */
    movInst = (* (int *) (scp->sc_pc - movInstOffset));

    if isMoveInstruction(movInst) {

      for (i=0; i < 16; i++) allregs[i] = es->e_regs[i];

      LazyDangler = allregs[dataRegInx(destReg(movInst))];

      if (isLazyRef (LazyDangler)) {
	
	returnPC = (scp->sc_pc - movInstOffset);
	returnSP = scp->sc_sp;

	/*
	 * Address registers may need to be updated by the garbage collector.
	 * This is ensured by putting a0 through a4 on the stack.
	 */

	/* Reset stackpointer to the one at traptime. */
	asm volatile ("lea _returnSP,%sp");
	asm volatile ("mov.l (%sp),%sp");

	/* Push return address on stack. */
	asm volatile ("mov.l _returnPC,-(%sp)");

	/* Push contents of address registers 0 through 4 on stack. */
	asm volatile ("lea _allregs, %a0 # Push saved a0 through a4 on stack");
	asm volatile ("mov.l 32(%a0),-(%sp)");
	asm volatile ("mov.l 36(%a0),-(%sp)");
	asm volatile ("mov.l 40(%a0),-(%sp)");
	asm volatile ("mov.l 44(%a0),-(%sp)");
	asm volatile ("mov.l 48(%a0),-(%sp)");

	/* Clear address registers to prevent strange GC behaviour. */
	asm volatile ("mov.l &0,%a2 # Clear address registers");
	asm volatile ("mov.l &0,%a3");
	asm volatile ("mov.l &0,%a4");
	
	/* call beta object handling the lazy fetch */
	asm volatile ("mov.l _LazyItem, %a1 # Call BETA lazy handler");
	asm volatile ("mov.l (%a1), %a0");
	asm volatile ("mov.l -4(%a0), %a0");
	asm volatile ("jsr (%a0)");

	/* Reset data registers. */
	asm volatile ("lea _allregs, %a0 # reset data registers");
	asm volatile ("mov.l (%a0),%d0");
	asm volatile ("mov.l 4(%a0),%d1");
	asm volatile ("mov.l 8(%a0),%d2");
	asm volatile ("mov.l 12(%a0),%d3");
	asm volatile ("mov.l 16(%a0),%d4");
	asm volatile ("mov.l 20(%a0),%d5");
	asm volatile ("mov.l 24(%a0),%d6");
	asm volatile ("mov.l 28(%a0),%d7");

	/* Reset address registers. */
	asm volatile ("mov.l (%sp)+,%a4 # reset address registers");
	asm volatile ("mov.l (%sp)+,%a3");
	asm volatile ("mov.l (%sp)+,%a2");
	asm volatile ("mov.l (%sp)+,%a1");
	asm volatile ("mov.l (%sp)+,%a0");
	
	asm volatile ("rts # return to address before trap");
      }
      
      
    } else
      printf ("Error. Not a move instruction: %d\n", movInst);
  } 

  /* If we get here, it was not a dangling reference that caused the 
   * SIGILL. Call usual BETA error handler.
   */

  BetaSignalHandler(sig,code,scp,addr);
};

#endif /* hpux && !hppa */

int getDangler ()
{ return LazyDangler; }

void clearDangler ()
{ LazyDangler = 0; }


void initLazyTrapHandler (ref(Item) lazyHandler)
{ 
#ifdef sun4s
  struct sigaction sa;

  /* Specify that we want full info about the signal, and that
   * the handled signal should not be blocked while being handled: */
  sa.sa_flags = SA_SIGINFO | SA_NODEFER;

  /* No further signals should be blocked while handling the specified
   * signals. */
  sigemptyset(&sa.sa_mask); 

  /* Specify handler: */
  sa.sa_handler = trapHandler;

  sigaction (SIGILL,&sa,0);
#endif

#if defined(sun4) || defined(hpux8)
  signal (SIGILL, (void (*)(int)) trapHandler);
#endif

  LazyItem = lazyHandler;
  negAOArefsINSERT = NegAOArefsINSERT;
  negIOArefsINSERT = NegIOArefsINSERT;
  negAOArefsRESET = NegAOArefsRESET;
  findDanglingProto = FindDanglingProto;
}
