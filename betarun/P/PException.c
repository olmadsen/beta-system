#include "beta.h"
#include "PException.h"
#include "unswizzle.h"
#include "PStoreServer.h"

void pexp_dummy() {
  
#ifdef sparc
  USE();
#endif /* sparc */
  
}

#ifdef PERSIST

#ifdef UNIX
# include <signal.h>
# ifdef sun4s
#  include <siginfo.h>
#  include <sys/regset.h>
#  include <sys/ucontext.h>
# endif
# ifdef linux
#  include <asm/sigcontext.h> 
# endif
#endif

#ifdef nti
#ifdef nti_gnu
#include <excpt.h>
#define OUR_EXCEPTION_CONTINUE_SEARCH ExceptionContinueSearch
#define OUR_EXCEPTION_CONTINUE_EXECUTION ExceptionContinueExecution
#else /* !nti_gnu */
#define OUR_EXCEPTION_CONTINUE_SEARCH EXCEPTION_CONTINUE_SEARCH
#define OUR_EXCEPTION_CONTINUE_EXECUTION EXCEPTION_CONTINUE_EXECUTION
#endif /* nti_gnu */
#endif /* nti */

/* sighandler.c */
#ifdef UNIX
# ifdef linux
   void BetaSignalHandler(long sig, struct sigcontext_struct scp);
# else
   extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);
# endif
#endif

/* block.c */
void mmapInitial(unsigned long numbytes);

/* LOCAL CONSTANTS */
#define MAXENTRIES 0x160000

/* LOCAL VARIABLES */
static long sourcereg;
#ifdef sparc
static unsigned long rd;
static unsigned long rs1;
static unsigned long rs2;
#endif

/* The indirection table */
void *PIT, *PITTop, *PITLimit; 

/* LOCAL FUNCTION DECLARATIONS */
#ifdef sparc
static void *getRegisterContents(unsigned long reg, ucontext_t *ucon, long returnSP);
static long sourceReg(unsigned long instruction, ucontext_t *ucon, long returnSP);
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon);
#endif

/* FUNCTIONS */
void PITAlloc(void)
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
  PITLimit = mmapHeapLimit;

  Claim((unsigned long)PITLimit < 0x7fffffff,
	"PIT must be in positive adresses");
}

Object *newPUID(unsigned long offset)
{
  Claim(offset < MAXENTRIES, "Illegal offset of puid");
  
  return (Object *)((unsigned long )PIT + offset);
}

unsigned long getPUID(void *ip)
{
  Claim(((ip >= PIT) && (ip < PITLimit)),"Illegal ip");
  
  return (unsigned long)ip - (unsigned long)PIT;
}

/******************************* SPARC: ********************************/
#ifdef sparc
/* getRegisterContents: If register refers to G or O register the
   contents can be found in the ucon. Otherwise the contents is on the
   stack. The stack pointer is in the global variable 'returnSP'. Why
   this separation has been made between the O/G and I/L registers is
   unclear to me but it is imposed by the system. */
static void *getRegisterContents(unsigned long reg, ucontext_t *ucon, long returnSP) 
{
  if (reg == 0) {
    return 0;
  } else if ((reg > 0) && (reg < 0x10)) {
    /* Get the value from the context */
    return (void *)(ucon->uc_mcontext.gregs[reg + 3]);
  } else if ((reg >= 10) && (reg < 0x20)) {
    /* Get the value from the stack */
    return (void *)(((unsigned long *) returnSP)[reg - 16]);
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
static long sourceReg(unsigned long instruction, ucontext_t *ucon, long returnSP) 
{
  
  unsigned long op3;
  unsigned long simm13=-1;
  
  sourcereg = -1;
  rd = -1;
  rs1 = -1;
  rs2 = -1;
  
  /* Get the format bits (Bit 31 -> 30) of the instruction */
  switch (instruction >> 30){
  case 0:
    /* Bicc, FBfcc, CBccc, SETHI. These instructions does not access
       memory, but should they be able to cause a SIGBUS. */
    DEBUG_CODE(fprintf(output,"getSourceRegister: SIGBUS caused by optype = 0 ??\n"));
    DEBUG_CODE(Illegal());
    break;
  case 1:
    /* CALL. Should these be able to cause a SIGBUS? */
    DEBUG_CODE(fprintf(output,"getSourceRegister: SIGBUS caused by optype = 1 ??\n"));
    DEBUG_CODE(Illegal());
    break;
  case 2:
    /* Arithmetic, logical, shift and remaining. Should these be able
     * to cause a SIGBUS? */
    DEBUG_CODE(fprintf(output,"getSourceRegister: SIGBUS caused by optype = 3 (type 2) ??\n"));
    DEBUG_CODE(Illegal());
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
	if (inPIT(getRegisterContents(rs1, ucon, returnSP))) {
	  sourcereg = rs1;
	} 
      } else {
	if (inPIT(getRegisterContents(rs1, ucon, returnSP))) {
	  sourcereg = rs1;
	  Claim(!inPIT(getRegisterContents(rs2, ucon, returnSP)), "sourceReg: proxy in both rs1 and rs2\n");
	} else if (inPIT(getRegisterContents(rs2, ucon, returnSP))) {
	  sourcereg = rs2;
	  Claim(!inPIT(getRegisterContents(rs1, ucon, returnSP)), "sourceReg: proxy in both rs1 and rs2\n");
	}
      }
      /* Source reg is now set to the register containing the
	 proxy */
      return 1;
    }
  }
  return 0;
}

static unsigned long dummy;

/* proxyTrapHandler: Will decode the faulting instruction, lookup the
   object, and insert a reference to it in the register previously
   containing the proxy. */
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  unsigned long instruction, returnPC, returnSP, absAddr;
  void *ip;
  
  INFO_PERSISTENCE(numPF++);

  /* Fetch the faulting instruction. */
  dummy = instruction = (* (long *) (ucon->uc_mcontext.gregs[REG_PC]));
  
  /* PC to jump to when fetch has completed: */
  returnPC = ucon->uc_mcontext.gregs[REG_PC]; 
  /* SP to restore when fetch has completed: */
  returnSP = ucon->uc_mcontext.gregs[REG_SP]; 

  if (sourceReg(instruction, ucon, returnSP)) {
    
    if (sourcereg != -1) {
      
      /* Ok, so this is a genuine proxy reference. */
  
      Claim(isOpen(), 
	    "proxyTrapHandler: Lazy reference in memory eventhough store is closed");
      Claim(!BETAREENTERED, "Proxy met during rebinding!");
      
      ip = getRegisterContents(sourcereg, ucon, returnSP);
      
      /* Before calling unswizzleReference, which may call the callback entry 
       * 'callRebinderC' the C variable  BetaStackTop should be set to the value of the
       * stack pointer at the point where the process left BETA via the trap.
       */
      BetaStackTop = (long *)returnSP; /* Must be set in case og GC during callback */
#ifdef gcc_frame_size
      /* datpete 21/5/99: no need to push SP for GC anymore.
       * Thus could be saved in a local variable instead.
       */
#endif /* gcc_frame_size */
      pushSP(returnSP);

      /* Calculate absolute address by looking in appropriate tables */
      
      absAddr = (long)unswizzleReference(ip);
      
      popSP();
      
      /* We have fetched the object, and should continue execution.
       * With the introduction of dynamic compilation into debuggee, the 
       * debuggee may have allocated in IOA and even caused GC.
       * That is, the current value (right here in the signal handler)
       * of the two global sparc registers holding IOA and IOATopOff
       * MUST be written back into the ucontext to prevent the signal-
       * handler from restoring these registers to the old values.
       * Otherwise objects allocated during valhalla evaluators will
       * be forgotten!.
       * See register binding in registers.h.
       */
      
      ucon->uc_mcontext.gregs[REG_IOA] = (long)IOA;
      ucon->uc_mcontext.gregs[REG_IOATOPOFF] = (long)IOATopOff;
      
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
	  ((unsigned long *) returnSP)[sourcereg - 16] = absAddr;
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
/******************************* SPARC end ******************************/
#endif /* sparc */



#ifdef nti
/******************************* NTI: *********************************/
static long getRegisterContents(CONTEXT* pContextRecord, long reg)
{
#if 0
  DEBUG_CODE({
    fprintf(output, "Getting contents of reg=%0x\n", reg);
  });
#endif
  switch (reg) {
  case 0: return pContextRecord->Eax;
  case 1: return pContextRecord->Ecx;
  case 2: return pContextRecord->Edx;
  case 3: return pContextRecord->Ebx;
  case 4: return pContextRecord->Esp;
  case 5: return pContextRecord->Ebp;
  case 6: return pContextRecord->Esi;
  case 7: return pContextRecord->Edi;
  }
  return 0;
}

static long setRegisterContents(CONTEXT* pContextRecord, long reg, long value)
{
#if 0
  DEBUG_CODE({
    fprintf(output, "Setting reg=%0x to val=%0x\n", reg, value);
  });
#endif
  switch (reg) {
  case 0: pContextRecord->Eax = value; break;
  case 1: pContextRecord->Ecx = value; break;
  case 2: pContextRecord->Edx = value; break;
  case 3: pContextRecord->Ebx = value; break;
  case 4: pContextRecord->Esp = value; break;
  case 5: pContextRecord->Ebp = value; break;
  case 6: pContextRecord->Esi = value; break;
  case 7: pContextRecord->Edi = value; break;
  }
  return 0;
}

static long* decodeModRM(CONTEXT* pContextRecord, 
			 unsigned char modrm, 
			 unsigned char* modrmPC)
{
  /* if modrm==05, this is abs-adr, which really shouldn't trap. */
  sourcereg = modrm & 7;
  if (sourcereg != 4) {
    return (long*)getRegisterContents(pContextRecord, sourcereg);
  } else {
    unsigned char sib;
    long *adr;

    sib = modrmPC[2];
    /* FIXME: Do something about sib!
     * Needed: Check both regs to see which one is a proxy, 
     * then modify sourcereg accordingly. (Maybe it's always base?)
     * Assumption: Only one of them may point into the proxyspace.
     * This is true if the smallest address of proxyspace is larger
     * than the largest repetition.
     */
    sourcereg = sib & 7;
    adr = (long*)getRegisterContents(pContextRecord, sourcereg);
    if (inPIT(adr)) {
      return adr;
    } else {
      if (sib <= 0x3f) {
	sourcereg = sib/8;
	return (long*)getRegisterContents(pContextRecord, sourcereg);
      }
    }
  }  
  return 0;
}

int proxyTrapHandler(CONTEXT* pContextRecord)
{
  long *proxy, *absAddr = 0;
  unsigned char* PC;
  unsigned char modrm;

  PC = (unsigned char*)pContextRecord->Eip;

  Claim(!IOAActive, "!IOAActive");
  INFO_PERSISTENCE(numPF++);

  switch (PC[0]) {
  case 0x62:  /* BOUND R32, M32, M32 */
  case 0x80:  /* CMP R/M8, IMM8 */
  case 0x88:  /* MOV R/M8, R8 */
  case 0x89:  /* MOV R/M32, R32 */
  case 0x8a:  /* MOV R8, R/M8 */
  case 0x8b:  /* MOV R32, R/M32 */
  case 0xc6:  /* MOV R/M8, IMM8 */
  case 0xc7:  /* MOV R/M32, IMM32 */
    modrm = PC[1]; 
    proxy = decodeModRM(pContextRecord, modrm, PC+1);
    break;
  case 0x0f: /* Two-byte instruction. */
    switch (PC[1]) {
    case 0xb6: /* MOVZX R32, R/M8 */
    case 0xb7: /* MOVZX R32, R/M16 */
    case 0xbe: /* MOVSX R32, R/M8 */
    case 0xbf: /* MOVSX R32, R/M16 */
      modrm = PC[2]; 
      proxy = decodeModRM(pContextRecord, modrm, PC+2);
      break;
    default:
    DEBUG_CODE({
      fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
	      "%02x %02x %02x %02x %02x %02x\n", 
	      (int)PC, PC[0], PC[1], PC[2], PC[3], PC[4], PC[5]);
    });
    return 1;
    }
    break;
  default:
    DEBUG_CODE({
      fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
	      "%02x %02x %02x %02x %02x %02x\n", 
	      (int)PC, PC[0], PC[1], PC[2], PC[3], PC[4], PC[5]);
    });
    return 1;
  }
  
  if (inPIT(proxy)) {
    /* Calculate absolute address by looking in appropriate tables */
    absAddr = (long*)unswizzleReference(proxy);

    /* Now write the new value back into sourcereg: */
    setRegisterContents(pContextRecord, sourcereg, (long)absAddr);

    return 0;
  } else if (!proxy) {
    /* Normal refNone:  Handle as regular refNone. */
    return 2;
  }

  /* Exception not handled, let sighandler decide what to do. */
  return 1;
}
/******************************* NTI end ******************************/
#endif /* nti */

#ifdef linux
/******************************* LINUX: *********************************/
static long getRegisterContents(struct sigcontext_struct *scp, long reg)
{
#if 0
  DEBUG_CODE({
    fprintf(output, "Getting contents of reg=%0x\n", reg);
  });
#endif
  switch (reg) {
  case 0: return scp->eax;
  case 1: return scp->ecx;
  case 2: return scp->edx;
  case 3: return scp->ebx;
  case 4: return scp->esp;
  case 5: return scp->ebp;
  case 6: return scp->esi;
  case 7: return scp->edi;
  }
  return 0;
}

static long setRegisterContents(struct sigcontext_struct *scp, 
				long reg, long value)
{
#if 0
  DEBUG_CODE({
    fprintf(output, "Setting reg=%0x to val=%0x\n", reg, value);
  });
#endif
  switch (reg) {
  case 0: scp->eax = value; break;
  case 1: scp->ecx = value; break;
  case 2: scp->edx = value; break;
  case 3: scp->ebx = value; break;
  case 4: scp->esp = value; break;
  case 5: scp->ebp = value; break;
  case 6: scp->esi = value; break;
  case 7: scp->edi = value; break;
  }
  return 0;
}

static long* decodeModRM(struct sigcontext_struct *scp,
			 unsigned char modrm, 
			 unsigned char* modrmPC)
{
  /* if modrm==05, this is abs-adr, which really shouldn't trap. */
  sourcereg = modrm & 7;
  if (sourcereg != 4) {
    return (long*)getRegisterContents(scp, sourcereg);
  } else {
    unsigned char sib;
    long *adr;

    sib = modrmPC[2];
    /* FIXME: Do something about sib!
     * Needed: Check both regs to see which one is a proxy, 
     * then modify sourcereg accordingly. (Maybe it's always base?)
     * Assumption: Only one of them may point into the proxyspace.
     * This is true if the smallest address of proxyspace is larger
     * than the largest repetition.
     */
    sourcereg = sib & 7;
    adr = (long*)getRegisterContents(scp, sourcereg);
    if (inPIT(adr)) {
      return adr;
    } else {
      if (sib <= 0x3f) {
	sourcereg = sib/8;
	return (long*)getRegisterContents(scp, sourcereg);
      }
    }
  }  
  return 0;
}

void proxyTrapHandler(long sig, struct sigcontext_struct scp)
{
  long *proxy, *absAddr = 0;
  unsigned char* PC;
  unsigned char modrm;

  if (scp.trapno==5 || scp.trapno==12) {
    BetaSignalHandler(sig, scp);
    Illegal();
  }
  INFO_PERSISTENCE(numPF++);
  PC = (unsigned char*) scp.eip;
  
  Claim(!IOAActive, "!IOAActive");

  switch (PC[0]) {
  case 0x62:  /* BOUND R32, M32, M32 */
  case 0x80:  /* CMP R/M8, IMM8 */
  case 0x88:  /* MOV R/M8, R8 */
  case 0x89:  /* MOV R/M32, R32 */
  case 0x8a:  /* MOV R8, R/M8 */
  case 0x8b:  /* MOV R32, R/M32 */
  case 0xc6:  /* MOV R/M8, IMM8 */
  case 0xc7:  /* MOV R/M32, IMM32 */
    modrm = PC[1]; 
    proxy = decodeModRM(&scp, modrm, PC+1);
    break;
  case 0x0f: /* Two-byte instruction. */
    switch (PC[1]) {
    case 0xb6: /* MOVZX R32, R/M8 */
    case 0xb7: /* MOVZX R32, R/M16 */
    case 0xbe: /* MOVSX R32, R/M8 */
    case 0xbf: /* MOVSX R32, R/M16 */
      modrm = PC[2]; 
      proxy = decodeModRM(&scp, modrm, PC+2);
      break;
    default:
    DEBUG_CODE({
      fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
	      "%02x %02x %02x %02x %02x %02x\n", 
	      (int)PC, PC[0], PC[1], PC[2], PC[3], PC[4], PC[5]);
    });
    /* Exception not handled, let sighandler decide what to do. */
    BetaSignalHandler(sig, scp);
    }
    break;
  default:
    DEBUG_CODE({
      fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
	      "%02x %02x %02x %02x %02x %02x\n", 
	      (int)PC, PC[0], PC[1], PC[2], PC[3], PC[4], PC[5]);
    });
    /* Exception not handled, let sighandler decide what to do. */
    BetaSignalHandler(sig, scp);
  }
  
  if (inPIT(proxy)) {
    /* Calculate absolute address by looking in appropriate tables */
    absAddr = (long*)unswizzleReference(proxy);

    /* Now write the new value back into sourcereg: */
    setRegisterContents(&scp, sourcereg, (long)absAddr);
  } else if (!proxy) {
    Object *    theObj = 0;
    theObj = (Object *) scp.edx;
    if ( ! (inIOA(theObj) && isObject (theObj)))
      theObj  = 0;
    /* Normal refNone:  Handle as regular refNone. */
    if (!DisplayBetaStack(RefNoneErr, theObj, (long*)PC, sig)) {
      BetaExit(1);
    }
  } else {
    /* Exception not handled, let sighandler decide what to do. */
    BetaSignalHandler(sig, scp);
  }
}
/******************************* LINUX end ******************************/
#endif /* linux */

/******************************* UNIX: ********************************/
#ifdef UNIX
/* initProxyTrapHandler: */
void initProxyTrapHandler(void)
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
  sa.sa_handler = proxyTrapHandler;
  
  sigaction (SIGBUS,&sa,0);
  sigaction (SIGSEGV,&sa,0);

#else
  signal (SIGSEGV, (void (*)(int))proxyTrapHandler);
#endif
}
#endif



/* GLOBAL FUNCTIONS */
#ifdef RTINFO
void printProxyStatistics(void)
{
  ;
}
#else
void printProxyStatistics(void)
{
  ;
}
#endif /* RTINFO */

#endif /* PERSIST */
