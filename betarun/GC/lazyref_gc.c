#ifdef RTLAZY


/* Created by Soren Brandt.
 * 
 * Necessary low level additions to the BETA RTS needed to handle
 * lazy references to persistent objects. In addition a number of 
 * changes has been made to other parts of the runtime system.
 * These changes are all enclosed in #ifdef RTLAZY to be able
 * to compile the RTS without them. */

#include "../C/beta.h"


static int negAOAmax = 0; 
/* Max number of integers possible to put into the negAOArefs table. */

static int negIOAsize = 0; 
/* Current number of entries in the negIOArefs table. */

static int negIOAmax = 0; 
/* Max number of integers possible to put into the negIOArefs table. */



#define DEFAULTNEGTABLESIZE 25

void negAOArefsRESET () { negAOAsize = 0; }
void negIOArefsFREE () { free (negIOArefs); negIOArefs = 0; }
   
void negAOArefsINSERT(long fieldAdr)  
{     
  if (negAOAsize == negAOAmax)
    if (negAOAmax == 0) {
      negAOAmax = DEFAULTNEGTABLESIZE;
      negAOArefs = (long *) malloc (negAOAmax*sizeof(long));
    } else {
      negAOAmax = 2*negAOAmax;
      negAOArefs = (long *) realloc (negAOArefs, negAOAmax*sizeof(long));
    }

  negAOArefs[negAOAsize++] = fieldAdr;
}


void negIOArefsINSERT(long fieldAdr)
{
  if (negIOAsize == negIOAmax) {
    negIOAmax = 2*negIOAmax;
    negIOArefs = (long *) realloc (negIOArefs, negIOAmax*sizeof(int));
  }

  negIOArefs[negIOAsize++] = fieldAdr;
}


void preLazyGC ()
{
  negIOAsize = 0; 
  negIOAmax = DEFAULTNEGTABLESIZE;
  negIOArefs = (long *) malloc (negIOAmax*sizeof(int));
}

static inline int danglerLookup (int* danglers, int low, int high, int dangler)
{ int mid;

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

#ifdef sparc
#include "../CRUN/crun.h"
#else
static inline void
AssignReference(long *theCell, ref(Item) newObject)
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(theCell);
}
#endif


void setupDanglers (int* danglers, long* objects, int count)
{ int i, dangler, inx;

  for (i = 0; i < negIOAsize; i++)
    if isLazyRef(dangler = (*((int *) negIOArefs[i])))
      if ((inx = danglerLookup (danglers, 0, count - 1, dangler)) >= 0)
	if (negIOArefs[i] >= (long) BetaStackTop)
	  /* Dangling reference on processor stack. AssignReference
           * would believe that negIOArefs[i] is in AOA and as a result
           * put it into AOAtoIOAtable if objects[inx] is in IOA. 
           * We surely do not want that. 
	   */
	  (*((long *) negIOArefs[i])) = objects[inx];
	else
	  AssignReference ((long *) negIOArefs[i], cast(Item) objects[inx]);
  
  negIOArefsFREE();

  if (negAOArefs) {
    i = 0;
    while (i < negAOAsize) {
      if isLazyRef(dangler = (*((int *) negAOArefs[i]))) {
	if ((inx = danglerLookup (danglers, 0, count - 1, dangler)) >= 0) {
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

  /* printf ("addDanglingProto\n"); */
  
  if (!roots)
    roots = (protoPtr *) calloc (ROOTSIZE,sizeof(protoPtr));
  
  inx = (-dangler)%ROOTSIZE;

  new = (protoPtr) malloc (sizeof(protoElm));
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

  /* printf ("removeDanglingProto\n"); */
  
  inx = (-dangler)%ROOTSIZE;
  this = roots[inx];

  while (this) {
    if (this->dangler == dangler) {
      if (this->next) this->next->prev = this->prev;
      if (this->prev) this->prev->next = this->next;
      else roots[inx] = this->next;
      
      free (this);
    }
    this = this->next;
  }
}

int findDanglingProto (int dangler)
{ int inx;
  protoPtr this;
  
  /* printf ("findDanglingProto\n"); */

  inx = (-dangler)%ROOTSIZE;
  this = roots[inx];

  while (this) {
    if (this->dangler == dangler) {
      return this->proto;
    }
    this = this->next;
  }

  fprintf (stderr, "Fatal Error: Prototype of Dangling ref not found\n");
  return 0;
}



#include <signal.h>
#include <machine/trap.h>

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
 *      tst %ln         (pseudo instruction for orcc %ln, %g0, %g0)
 *      tle 17
 * 
 * The tst (xorcc) instruction should thus have the following format.
 *
 * SPARC: 31 30  29 28 27 26 25  24 23 22 21 20 19   18 17 16 15 14  13  12 11 10 9 8 7 6 5  4 3 2 1 0
 *                  DestReg         orcc opcode         Source1             Dummys            Source2
 *         1  0   0  0  0  0  0   0  1  0  0  1  0    ?  ?  ?  ?  ?   0                      0 0 0 0 0
 *                                                                                           ^
 *                                                                                   Viser sig at v{re 1?????
 * 
 *
 * 
 * 
 * 
 * 
 * HP PA: ???
 *
 */


int (*fetchFromDisc)(int); /* BETA callback function. */



/* SPARC
 * ===== */

#ifdef sparc

#include "../CRUN/crun.h"

/* #define FilterUnknown 0xFFF8201F */
#define FilterUnknown 0xFFF8200F  /* ???????? */
#define KnownMask 0x80900000
#define instructionOk(instruction) ((instruction & FilterUnknown) == KnownMask)

#define sourceReg(instruction) ((instruction >> 14) & 0x0000001F)

struct RegWin* lazyTrapAR = 0;

void DoLazyFetchGC()
{ 
  /* This wrapper adds an activation record around doGC, which skips two AR's */
  preLazyGC();
  doGC();
}

void trapHandler (int sig, int code, struct sigcontext *scp, char *addr)
{
  int instruction, sreg, dangler;

  /* fprintf (stderr, "trapHandler\n"); */

  if (code == ILL_TRAP_FAULT(17)) {
    /* Ok, this has been a "tle 17" instruction meaning either 
     *"reference is NONE" or a dangling reference. */
    
    /* Set up BetaStackTop. It is normally set up by the compiler on
     * external calls.
     * Furthermore lazyTrapAR is used to avoid skipping the stack references
     * during GC as is usually done for compiler generated external calls. */
    BetaStackTop = (long *) lazyTrapAR = (struct RegWin*) (scp->sc_sp);
    
    /* Fetch the 'tst %lm' instruction. */
    instruction = (* (long *) (scp->sc_pc - 4));

    if (instructionOk(instruction)) {
      sreg = sourceReg(instruction);
      dangler = ((int *) scp->sc_sp)[sreg];

      if (isLazyRef(dangler)) {
	((int *) scp->sc_sp)[sreg] = fetchFromDisc (dangler);

	/* IOA GC has changed contents of register %g6 (IOA) and %g7 (IOATopoff). 
         * The corresponding saved registers from before the trap
         * needs to be updated to avoid loosing the change made by GC.
         * AS FAR AS I KNOW THE LOCATION OF THE SAVED GLOBAL REGISTERS IS NOT 
         * DOCUMENTED AND MIGHT CHANGE. THE LOCATION USED BELOW IS
         * FOUND SIMPLY BY DUMPING THE STATE SAVED ON STACK BY SunOs 
         * TRAPHANDLER!!!!!!!! */

	BetaStackTop[-557] = IOATopoff;
	BetaStackTop[-558] = IOA;


      } else
	SignalHandler (sig, code, scp, addr);

      lazyTrapAR = 0;

      scp->sc_pc -= 4;  /* Perform tst and tle again. */
      scp->sc_npc -= 4;  
      
    } else
      SignalHandler (sig, code, scp, addr);
    
  } else
    SignalHandler (sig, code, scp, addr);

  /* fprintf (stderr, "trapHandler returning\n"); */
}

#endif




/* MC680?0 HP-UX 8
 * =============== */


#if defined(hpux) && !defined(hppa)
/* The macros below are specifically for HP-UX  series 300/400 */

#define isMoveInstruction(instruction) ((0xC0000000 & instruction) == 0)
#define size(moveInstruction) (moveInstruction >> 28)
#define destReg(moveInstruction) ((0x0E000000 & moveInstruction) >> 25)
#define destMode(moveInstruction) ((0x01C00000 & moveInstruction) >> 22)
#define sourceMode(moveInstruction) ((0x00380000 & moveInstruction) >> 19)
#define sourceReg(moveInstruction) ((0x00070000 & moveInstruction) >> 16)

#define destModeOk(moveInstruction) (destMode(moveInstruction) == 0)
#define sourceModeOk(moveInstruction) (sourceMode(moveInstruction) == 5)

#define addressReg(n) (es->e_regs[8+n])
#define dataReg(n)  (es->e_regs[n])

#define newBetaStackTop ((long *) ((long) scp->sc_sp - (long) 4*5))

#define whereToPut_a0 (* (long *) ((long) newBetaStackTop + (long) 16))
#define whereToPut_a1 (* (long *) ((long) newBetaStackTop + (long) 12))
#define whereToPut_a2 (* (long *) ((long) newBetaStackTop + (long) 8))
#define whereToPut_a3 (* (long *) ((long) newBetaStackTop + (long) 4))
#define whereToPut_a4 (*newBetaStackTop)

#define updateReferencedRegister(newObjectAddr,moveInstruction) dataReg(destReg(moveInstruction)) = newObjectAddr
  
#define movInstOffset 6




void trapHandler (int sig, int code, struct sigcontext *scp, char *addr)
{   
  struct exception_stack* es;  /* From <machine/trap.h> */
  int movInst;
  int saveStack[5];
  
  long newObjectAddr;
  
  es = (struct exception_stack*) (((long) &addr) + ((long) 32));
  
  /* if code == 7 then it has been a tle instruction => zero or negative reference. */
  if (code == 7) {
    
    /* Fetch the move instruction. */
    movInst = (* (int *) (scp->sc_pc - movInstOffset));
    
    if isMoveInstruction(movInst) {
      
      if (dataReg(destReg(movInst)) == 0)
	/* An ordinary NONE reference. Call usual BETA error handler. */
	SignalHandler (sig, code, scp, addr);
      
      /*
       * Address registers may need to be updated by the garbage collector.
       * This is ensured by putting a0 through a4 in the part of the stack
       * seen by the garbage collector. (below BetaStackTop)
       */
      
      BetaStackTop = newBetaStackTop;
      
      saveStack[0] = whereToPut_a0; whereToPut_a0 = addressReg(0);
      saveStack[1] = whereToPut_a1; whereToPut_a1 = addressReg(1);
      saveStack[2] = whereToPut_a2; whereToPut_a2 = addressReg(2);
      saveStack[3] = whereToPut_a3; whereToPut_a3 = addressReg(3);
      saveStack[4] = whereToPut_a4; whereToPut_a4 = addressReg(4);
      
      /* Now do callback into beta-code taking care of fetching the object. 
       * It should return the address of the newly created object. */
      
      /* printf ("Dangler: %d\n", dataReg(destReg(movInst))); */

      newObjectAddr = fetchFromDisc (dataReg(destReg(movInst)));
      
      /* Restore address registers */
      addressReg(0) = whereToPut_a0; whereToPut_a0 = saveStack[0];
      addressReg(1) = whereToPut_a1; whereToPut_a1 = saveStack[1];
      addressReg(2) = whereToPut_a2; whereToPut_a2 = saveStack[2];
      addressReg(3) = whereToPut_a3; whereToPut_a3 = saveStack[3];
      addressReg(4) = whereToPut_a4; whereToPut_a4 = saveStack[4];
      
      /* Update the dataregister that contained the NONE reference */
      updateReferencedRegister(newObjectAddr,movInst);
      
      
    } else {
      printf ("Error. Not a move instruction: %d\n", movInst);
    } 
  } else {
    /* SIGILL Not caused by dangling  instruction. */
    SignalHandler(sig,code,scp,addr);
  }
};
#endif /* hpux && !hppa */

void initLazyTrapHandler (int (*cb)(int))
{ 
  fetchFromDisc = cb;
  signal (SIGILL, (void (*)(int)) trapHandler); 
};




#endif /* RTLAZY */
