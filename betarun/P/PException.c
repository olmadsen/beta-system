#include "beta.h"
#include "PException.h"
#include "unswizzle.h"

void pexp_dummy() {
  
#ifdef sparc
  USE();
#endif /* sparc */
  
}

#ifdef PERSIST

#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#include <signal.h>

/* sighandler.c */
extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);

/* block.c */
void mmapInitial(unsigned long numbytes);

/* LOCAL CONSTANTS */
#define MAXENTRIES 0x160000

/* LOCAL VARIABLES */
static long returnPC, returnSP, absAddr, sourcereg;
static u_long rd;
static u_long rs1;
static u_long rs2;

/* The indirection table */
static void *PIT, *PITTop, *PITLimit; 

/* LOCAL FUNCTION DECLARATIONS */
static void PITAlloc(void);
static void *getRegisterContents(u_long reg, ucontext_t *ucon);
static long sourceReg(u_long instruction, ucontext_t *ucon);
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon);

/* FUNCTIONS */
static void PITAlloc(void)
{
  /* The backpointer that will be placed in the persistent objects
     marking them as persistent is a pointer into a protected memory
     area. If the object has been assigned entry 'n' in the
     PObjectsTable, its corresponding backpointer will be n bytes into
     the protected memmory area.
  */
  
  /* Allocate mmapped proxy indirection table. */
  
  mmapInitial((unsigned long) MAXENTRIES);
  PIT = mmapHeapTop;
  PITTop = mmapHeapTop;
  PITLimit = mmapHeapLimit;
}

/* getRegisterContents: If register refers to G or O register the
   contents can be found in the ucon. Otherwise the contents is on the
   stack. The stack pointer is in the global variable 'returnSP'. Why
   this separation has been made between the O/G and I/L registers is
   unclear to me but it is imposed by the system. */
static void *getRegisterContents(u_long reg, ucontext_t *ucon) 
{
  if (reg == 0) {
    return 0;
  } else if ((reg > 0) && (reg < 0x10)) {
    /* Get the value from the context */
    return (void *)(ucon->uc_mcontext.gregs[reg + 3]);
  } else if ((reg >= 10) && (reg < 0x20)) {
    /* Get the value from the stack */
    return (void *)(((u_long *) returnSP)[reg - 16]);
  } else {
    fprintf(output, "getRegisterContents: "
	    "Unsupported register\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return (void *)-1;
}

/* sourceReg: Decodes the instruction and returns the register
   containing the proxy. */
static long sourceReg(u_long instruction, ucontext_t *ucon) 
{
  
  u_long op3;
  u_long simm13=-1;
  
  sourcereg = -1;
  rd = -1;
  rs1 = -1;
  rs2 = -1;
  
  /* Get the format bits (Bit 31 -> 30) of the instruction */
  switch (instruction >> 30){
  case 0:
    /* Bicc, FBfcc, CBccc, SETHI. These instructions does not access
       memory, but should they be able to cause a SIGBUS. */
    fprintf(output,"getSourceRegister: SIGBUS caused by optype = 0 ??\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
    break;
  case 1:
    /* CALL. Should these be able to cause a SIGBUS? */
    fprintf(output,"getSourceRegister: SIGBUS caused by optype = 1 ??\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
    break;
  case 2:
    /* Arithmetic, logical, shift and remaining. Should these be able
     * to cause a SIGBUS? */
    fprintf(output,"getSourceRegister: SIGBUS caused by optype = 3 (type 2) ??\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
    break;
  case 3: 
    {
      /* memory instructions. These we are looking for, but maybe also
       * some of the above ? */
      
      /* Bit 29 -> 25 (5 bits) is the register that supplies the data
       * for the store or receives the data from the load. */
      rd = (instruction >> 25) & 0x1F;
      
      /* bits 24 -> 19 (6 bits) is the format of these type of
       * instructions. */
      op3 = (instruction >> 19) & 0x3F;
      
      /* Bit 18 -> 14 (5 bits) contains the first register used to
	 calculate the memory address. */
      rs1 = (instruction >> 14) & 0x1F;
      
      /* Bit 13 determines whether we use another register to
       * calculate the memory address or we use an immediate value.  
       */
      if ((instruction >> 13) & 0x1) {
	/* Immediate value used. */
	simm13 = instruction & 0x1FFF;
	
      } else {
	/* Another register used */
	/* Bits 4 -> 0 contains the register */
	rs2 = instruction & 0x1F;
	
      }
      
      /* its assumed that only rs1 or sr2 can be the culprit, not both */
      if (simm13 != -1) {
	if (inPIT(getRegisterContents(rs1, ucon))) {
	  sourcereg = rs1;
	} 
      } else {
	if (inPIT(getRegisterContents(rs1, ucon))) {
	  sourcereg = rs1;
	  Claim(!inPIT(getRegisterContents(rs2, ucon)), "sourceReg: proxy in both rs1 and rs2\n");
	} else if (inPIT(getRegisterContents(rs2, ucon))) {
	  sourcereg = rs2;
	  Claim(!inPIT(getRegisterContents(rs1, ucon)), "sourceReg: proxy in both rs1 and rs2\n");
	}
      }
      /* Source reg is now set to the register containing the
	 proxy */
      return 1;
    }
  }
  return 0;
}

static u_long dummy;

/* proxyTrapHandler: Will decode the faulting instruction, lookup the
   object, and insert a reference to it in the register previously
   containing the proxy. */
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  u_long instruction;
  void *ip;
  
  /* Fetch the faulting instruction. */
  dummy = instruction = (* (long *) (ucon->uc_mcontext.gregs[REG_PC]));
  
  /* PC to jump to when fetch has completed: */
  returnPC = ucon->uc_mcontext.gregs[REG_PC]; 
  /* SP to restore when fetch has completed: */
  returnSP = ucon->uc_mcontext.gregs[REG_SP]; 
  
  if (sourceReg(instruction, ucon)) {
    
    if (sourcereg != -1) {
      
      /* Ok, so this is a genuine proxy reference. */
      ip = getRegisterContents(sourcereg, ucon);
      
      /* Calculate absolute address by looking in appropriate tables */
      absAddr = (long)unswizzleReference(ip);
      
      if (absAddr) {
	switch (sourcereg) {
	case 0x0: /* g0 */
	  fprintf(output, "proxyTrapHandler: "
		  "Code using %%g0 for proxy!!\n");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	  break;
	case 0x1: /* g1 */
	case 0x2: /* g2 */
	case 0x3: /* g3 */
	case 0x4: /* g4 */
	case 0x5: /* g5 */
	case 0x6: /* g6 */
	case 0x7: /* g7 */
	case 0x8: /* o0 */
	case 0x9: /* 01 */
	case 0xA: /* 02 */
	case 0xB: /* 03 */
	case 0xC: /* 04 */
	case 0xD: /* 05 */
	case 0xE: /* 06 */
	case 0xF: /* 07 */
	  ucon->uc_mcontext.gregs[sourcereg + 3] = absAddr;
	  break;
	case 0x10: /* l0 -> l7, i0 -> %i7 */
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1A:
	case 0x1B:
	case 0x1C:
	case 0x1D:
	case 0x1E:
	case 0x1F:
	  ((u_long *) returnSP)[sourcereg - 16] = absAddr;
	  break;
	default:
	  fprintf(output, "proxyTrapHandler: "
		  "Unsupported source register\n");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
	return;
      }
    }
  }
  
  /* Make sure signal handler is reinstalled. */
  signal (SIGSEGV, (void (*)(int)) proxyTrapHandler);
  signal (SIGBUS, (void (*)(int)) proxyTrapHandler);
  
  /* If we get here, it was an ordinary SIGBUS */
  BetaSignalHandler (sig, info, ucon);
  
}

/* GLOBAL FUNCTIONS */

Object *newPUID(u_long offset)
{
  Claim(offset < MAXENTRIES, "Illegal offset of puid");
  
  return (Object *)((u_long )PIT + offset);
}

u_long getPUID(void *ip)
{
  Claim(((ip >= PIT) && (ip < PITLimit)),"Illegal ip");
  
  return (u_long)ip - (u_long)PIT;
}

int inPIT(void *ip)
{
  return ((ip >= PIT) && (ip < PITLimit));
}

/* initProxyTrapHandler: */
void initProxyTrapHandler(void)
{ 
  struct sigaction sa;
  
  /* Specify that we want full info about the signal, and that
   * the handled signal should not be blocked while being handled: */
  sa.sa_flags = SA_SIGINFO | SA_NODEFER;
  
  /* No further signals should be blocked while handling the specified
   * signals. */
  sigemptyset(&sa.sa_mask); 
  
  /* Specify handler: */
  sa.sa_handler = proxyTrapHandler;
  
  sigaction (SIGBUS,&sa,0);
  sigaction (SIGSEGV,&sa,0);

  /* Allocate indirection table */
  PITAlloc();
}

#endif /* PERSIST */
