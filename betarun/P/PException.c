#include "beta.h"
#include "function.h"
#include "PException.h"
#include "rtsighandler.h"

#ifdef PERSIST
#include "unswizzle.h"

/* block.c */
void mmapInitial(unsigned long numbytes);

/* LOCAL CONSTANTS */
#define MAXENTRIES PERSIST_MAXENTRIES

/* LOCAL VARIABLES */
#ifndef macosx
static long sourcereg;
#endif

#ifdef sparc
static unsigned long rd;
static unsigned long rs1;
static unsigned long rs2;
#endif

#ifdef UNIX
static void InstallProxyHandler(void);
#endif

/* LOCAL FUNCTION DECLARATIONS */
#ifdef sparc
static void *getRegisterContents(unsigned long reg, ucontext_t *ucon, long returnSP);
static long sourceReg(unsigned long instruction, ucontext_t *ucon, long returnSP);
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon);
#endif

/* FUNCTIONS */
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
    DEBUG_CODE(ILLEGAL);
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
    DEBUG_CODE(ILLEGAL);
    break;
  case 1:
    /* CALL. Should these be able to cause a SIGBUS? */
    DEBUG_CODE(fprintf(output,"getSourceRegister: SIGBUS caused by optype = 1 ??\n"));
    DEBUG_CODE(ILLEGAL);
    break;
  case 2:
    /* Arithmetic, logical, shift and remaining. Should these be able
     * to cause a SIGBUS? */
    DEBUG_CODE(fprintf(output,"getSourceRegister: SIGBUS caused by optype = 3 (type 2) ??\n"));
    DEBUG_CODE(ILLEGAL);
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
      {
	
	if (simm13 != -1) {
	  sourcereg = rs1;
	} else {
	  void *reg_contents1;
	  void *reg_contents2;
	  reg_contents1 = getRegisterContents(rs1, ucon, returnSP);
	  reg_contents2 = getRegisterContents(rs2, ucon, returnSP);
	  
	  if (inPIT(reg_contents1)) {
	    sourcereg = rs1;
	    Claim(!inPIT(reg_contents2), 
		  "sourceReg: proxy in both rs1 and rs2\n");
	  } else if (inPIT(reg_contents2)) {
	    sourcereg = rs2;
	    Claim(!inPIT(reg_contents1), 
		  "sourceReg: proxy in both rs1 and rs2\n");
	  }
	}
	/* Source reg is now set to the register containing the
	   proxy */
	return 1;
      }
    }
  }
  return 0;
}

static unsigned long dummy;

/* SPARC:
   proxyTrapHandler: Will decode the faulting instruction, lookup the
   object, and insert a reference to it in the register previously
   containing the proxy. */
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  unsigned long instruction, returnPC, returnSP, absAddr = 0;
  
  void *ip;
  
  static int reentered = 0;

  INFO_PERSISTENCE(numPF++);

  if (!reentered) {
     reentered = 1;
     /* Fetch the faulting instruction. */
    if ((dummy = instruction = (* (long *) (ucon->uc_mcontext.gregs[REG_PC])))) {
       
       /* PC to jump to when fetch has completed: */
       returnPC = ucon->uc_mcontext.gregs[REG_PC]; 
       /* SP to restore when fetch has completed: */
       returnSP = ucon->uc_mcontext.gregs[REG_SP]; 
       
       if (sourceReg(instruction, ucon, returnSP)) {
          if (sourcereg != -1) {
             /* Ok, so this is a genuine refNone or proxy reference. */
             ip = getRegisterContents(sourcereg, ucon, returnSP);
             
             if (inPIT(ip)) {
                /* Calculate absolute address by looking in appropriate tables */
                
                /* 'unswizzleReference' *might* call back into beta code to
                   rebind special references. Thus the call is protected using
                   the 'BetaCallback' abstraction. */
                BetaCallback(ucon, 
                             returnSP, 
                             absAddr = (long)unswizzleReference(ip));
             } else {
                DEBUG_CODE({fprintf(output, ", proxy not in PIT 0x%X)\n", (int)ip);};);
             }
             
             if (absAddr) {
                /* We have fetched the object, and should continue execution. */
                switch (sourcereg) {
                  case 0x0: /* g0 */
                     fprintf(output, "proxyTrapHandler: "
                             "Code using %%g0 for proxy!!\n");
                     DEBUG_CODE(ILLEGAL);
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
                     DEBUG_CODE(ILLEGAL);
                     BetaExit(1);
                }
                reentered = 0;
                return;
             }
          } else {
             DEBUG_CODE({fprintf(output, ", could not retreive source reg)\n");};);
          }
       } else {
          DEBUG_CODE({fprintf(output, 
                              ", could not decode instruction = 0x%X)\n",
                              (int)instruction);};);
       }
    } else {
       DEBUG_CODE({fprintf(output, 
                           ", instruction is NULL)\n");};);
    }
  } else {
     DEBUG_CODE({fprintf(output, ", reentered)\n");};);     
  }
  /* If we get here, it was an ordinary SIGBUS, SIGSEGV or object
     could not be loaded */
  BetaSignalHandler(sig, info, ucon);
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

/* WIN32:
   NTI:
   proxyTrapHandler:
*/
int proxyTrapHandler(CONTEXT* pContextRecord)
{
   long *proxy, *absAddr = 0;
   unsigned char* PC;
   unsigned char modrm;
   static unsigned char reentered = 0;
   
   if (reentered) {
      return 1;
   }
   reentered = 1;
   
   PC = (unsigned char*)pContextRecord->Eip;
   StackEnd = (long *)pContextRecord->Esp;
   
   Claim(!IOAActive, "!IOAActive");
   INFO_PERSISTENCE(numPF++);
   INFO_PERSISTENCE({
      fprintf(output, "proxyTrapHandler:%d:0x%08lx\n", numPF, (long)PC);
   });

#  ifdef BOUND_BASED_AOA_TO_IOA
#      error Not coded for Windows yet
#  endif
   
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
             reentered = 0;
             return 1;
        }
        break;
     default:
        DEBUG_CODE({
           fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
                   "%02x %02x %02x %02x %02x %02x\n", 
                   (int)PC, PC[0], PC[1], PC[2], PC[3], PC[4], PC[5]);
        });
        reentered = 0;
        return 1;
   }
   if (inPIT(proxy)) {
      /* Calculate absolute address by looking in appropriate tables */
      absAddr = (long*)unswizzleReference(proxy);

      /* Now write the new value back into sourcereg: */
      setRegisterContents(pContextRecord, sourcereg, (long)absAddr);
      reentered = 0;
      
      return 0;
   } else if (!proxy) {
      /* Normal refNone:  Handle as regular refNone. */
      reentered = 0;
      return 2;
   }
   
   /* Exception not handled, let sighandler decide what to do. */
   reentered = 0;
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

/* LINUX:
   proxyTrapHandler:
*/
void proxyTrapHandler(long sig, struct sigcontext_struct scp)
{
   long *proxy = 0, *absAddr = 0;
   unsigned char* PC;
   unsigned char modrm;
   int isBeta;

#if 0   
   DEBUG_CODE({
     fprintf(output, "(proxyTrapHandler:PC=0x%08x, sig=%d)", (int)PC, (int)sig);
     fflush(output);
   });
#endif

#  if defined(__i386__) && defined(BOUND_BASED_AOA_TO_IOA)
       if (scp.trapno==5) {
	  BoundSignalHandler(sig, &scp);
	  return;
       }
#  endif

   if (scp.trapno==5 /* boundl=>index error */|| 
       scp.trapno==12 /* stack fault */) {
      BetaSignalHandler(sig, scp);
      return;
   }
   INFO_PERSISTENCE(numPF++);
   PC = (unsigned char*) scp.eip;
   
   
   isBeta = IsBetaCodeAddrOfProcess(PC);
   if (!isBeta){
      DEBUG_CODE({
         fprintf(output, "(proxyTrapHandler:PC=0x%08x, ", (int)PC);
         fflush(output);
      });
      DEBUG_CODE({
         fprintf(output, "(outside BETA code))\n");
         fflush(output);
      });
   } else {
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
         
         return;
      } else if (!proxy) {
         Object *    theObj = 0;
         theObj = (Object *) scp.edx;
         if (!((inIOA(theObj) || inAOA(theObj)) && isObject (theObj))) {
            theObj  = 0;
         }
         /* Normal refNone:  Handle as regular refNone. */
         /* PC = (long *) scp.eip; */
         StackEnd = (long *) scp.esp_at_signal;
         if (!DisplayBetaStack(RefNoneErr, theObj, PC, sig)) {
            BetaExit(1);
         }
         return;
      } 
   }
   /* Exception not handled, let sighandler decide what to do. */
   BetaSignalHandler(sig, scp);
}
/******************************* LINUX end ******************************/
#endif /* linux */

#ifdef x86sol
/******************************* X86SOL: *********************************/
static void *getRegisterContents(ucontext_t *ucon,
				 unsigned long reg) 
{
  return (void *)ucon->uc_mcontext.gregs[(long)reg];
}

static void setRegisterContents(ucontext_t *ucon, 
				long reg, 
				long value)
{
   ucon->uc_mcontext.gregs[(long)reg] = (long)value;
}

static long* decodeModRM(ucontext_t *ucon,
			 unsigned char modrm, 
			 unsigned char* modrmPC)
{
   /* if modrm==05, this is abs-adr, which really shouldn't trap. */
   sourcereg = modrm & 7;
   if (sourcereg != 4) {
      return (long*)getRegisterContents(ucon, sourcereg);
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
      adr = (long*)getRegisterContents(ucon, sourcereg);
      if (inPIT(adr)) {
         return adr;
      } else {
         if (sib <= 0x3f) {
            sourcereg = sib/8;
            return (long*)getRegisterContents(ucon, sourcereg);
         }
      }
   }  
   return 0;
}

/* X86SOL:
   proxyTrapHandler:
*/
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
   long *proxy = 0, *absAddr = 0;
   unsigned char* pc;
   unsigned char modrm;
   int isBeta;
   
   DEBUG_CODE({
     fprintf(output, "(proxyTrapHandler:PC=0x%08x, sig=%d)", (int)pc, (int)sig);
     fflush(output);
   });

   if (ucon->uc_mcontext.gregs[TRAPNO]==5 /* boundl => index error */||
       ucon->uc_mcontext.gregs[TRAPNO]==12 /* stack fault */) {
     BetaSignalHandler(sig, info, ucon);
   }

   INFO_PERSISTENCE(numPF++);
   pc = (unsigned char*) getRegisterContents(ucon, EIP);
   
   isBeta = IsBetaCodeAddrOfProcess((pc_t)pc);
   if (!isBeta){
      DEBUG_CODE({
         fprintf(output, "(proxyTrapHandler:PC=0x%08x, ", (int)pc);
         fflush(output);
      });
      DEBUG_CODE({
         fprintf(output, "(outside BETA code))\n");
         fflush(output);
      });
   } else {
      Claim(!IOAActive, "!IOAActive");
      
      switch (pc[0]) {
        case 0x62:  /* BOUND R32, M32, M32 */
        case 0x80:  /* CMP R/M8, IMM8 */
        case 0x88:  /* MOV R/M8, R8 */
        case 0x89:  /* MOV R/M32, R32 */
        case 0x8a:  /* MOV R8, R/M8 */
        case 0x8b:  /* MOV R32, R/M32 */
        case 0xc6:  /* MOV R/M8, IMM8 */
        case 0xc7:  /* MOV R/M32, IMM32 */
           modrm = pc[1]; 
           proxy = decodeModRM(ucon, modrm, pc+1);
           break;
        case 0x0f: /* Two-byte instruction. */
           switch (pc[1]) {
             case 0xb6: /* MOVZX R32, R/M8 */
             case 0xb7: /* MOVZX R32, R/M16 */
             case 0xbe: /* MOVSX R32, R/M8 */
             case 0xbf: /* MOVSX R32, R/M16 */
                modrm = pc[2]; 
                proxy = decodeModRM(ucon, modrm, pc+2);
                break;
             default:
                DEBUG_CODE({
                   fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
                           "%02x %02x %02x %02x %02x %02x\n", 
                           (int)pc, pc[0], pc[1], pc[2], pc[3], pc[4], pc[5]);
                });
                /* Exception not handled, let sighandler decide what to do. */
                BetaSignalHandler(sig, info, ucon);
           }
           break;
        default:
           DEBUG_CODE({
              fprintf(output, "proxyTrapHandler: Unknown code at %8x: "
                      "%02x %02x %02x %02x %02x %02x\n", 
                      (int)pc, pc[0], pc[1], pc[2], pc[3], pc[4], pc[5]);
           });
           /* Exception not handled, let sighandler decide what to do. */
           BetaSignalHandler(sig, info, ucon);
      }
    
      if (inPIT(proxy)) {
         /* Calculate absolute address by looking in appropriate tables */
         absAddr = (long*)unswizzleReference(proxy);
         
         /* Now write the new value back into sourcereg: */
         setRegisterContents(ucon, sourcereg, (long)absAddr);
         
         return;
      } else if (!proxy) {
         Object *    theObj = 0;
         theObj = (Object *) getRegisterContents(ucon, EDX);
         if (!((inIOA(theObj) || inAOA(theObj)) && isObject (theObj))) {
            theObj  = 0;
         }
         /* Normal refNone:  Handle as regular refNone. */
	 
         StackEnd = (long *) ucon->uc_mcontext.gregs[UESP]; /* not SP */
         if (!DisplayBetaStack(RefNoneErr, theObj, (pc_t)pc, sig)) {
            BetaExit(1);
         }
         return;
      } 
   }
   /* Exception not handled, let sighandler decide what to do. */
   BetaSignalHandler(sig, info, ucon);
}
/******************************* X86SOL end ******************************/
#endif /* x86sol */

/******************************* SGI: ********************************/
#ifdef sgi
static unsigned long regToSet = 0;
static unsigned long getRegisterContents(struct sigcontext *scp,
					 unsigned long reg)
{
   Claim(reg<32, "reg<32");
   return (unsigned long)(scp->sc_regs[reg]);
}

static void setRegisterContents(struct sigcontext *scp,
				unsigned long reg,
				unsigned long value)
{
   Claim(reg<32, "reg<32");
   scp->sc_regs[reg] = value;
   scp->sc_regmask |= (1 << reg);
}

static unsigned long DecodeFormatI(struct sigcontext *scp,
				   unsigned long instruction)
{
   unsigned long rt,rs;
   unsigned long proxy;

   DEBUG_CODE({
      fprintf(output, ", DecodeFormatI: instruction=0x%08x",instruction);
   });
   
   rs = (instruction >> 21) & 0x1f;
   /* rt = (instruction >> 16) & 0x1f; */
   
   proxy = getRegisterContents(scp, rs);
   DEBUG_CODE({
      fprintf(output, ", DecodeFormatI: reg=%d, value=0x%08x", 
              (int)rs, (int)proxy);
   });
   if (!proxy) { /* RefNone */
    return 1;
   }
   if (inPIT(proxy)) {
      regToSet = rs;
      return proxy;
   }
   return 0;
}

static unsigned long dummy;

extern void BetaSignalHandler(long sig, long code, 
			      struct sigcontext * scp, char *addr);

/* SGI:
   proxyTrapHandler: Will decode the faulting instruction, lookup the
   object, and insert a reference to it in the register previously
   containing the proxy. */
/* See /usr/include/sys/signal.h, man siginfo */
static void proxyTrapHandler(long sig, long code, struct sigcontext * scp, char *addr)
{
   unsigned long instruction, opcode;
   unsigned long proxy = 0;
   long *PC;
   
   static int reentered = 0;
  
   /* Make sure signal handler is reinstalled. */
   InstallProxyHandler();
   
   PC = (long *) scp->sc_pc;
   
   INFO_PERSISTENCE(numPF++);
   DEBUG_CODE({
      fprintf(output, "(proxyTrapHandler:PC=0x%08x", (int)PC);
      fflush(output);
   });

   /* Fetch the faulting instruction. */
   if (!reentered) {
      reentered = 1;
      
      if ((dummy = (instruction = *PC))) {
         opcode = (instruction & 0xfc000000);
         if (opcode == /* LW   */ 0x8c000000) {
            proxy = DecodeFormatI(scp, instruction);
            if (proxy >= (unsigned long)PIT) {
               if (proxy <= (unsigned long)PITLimit) {
                  proxy = (unsigned long)unswizzleReference((long*)proxy);
                  DEBUG_CODE({
                     fprintf(output, ", reg=%d set to value=0x%08x)\n", 
                             (int)regToSet, (int)proxy);
                  });
                  setRegisterContents(scp, regToSet, proxy);
                  reentered = 0;
                  return;
               } else {
                  DEBUG_CODE({fprintf(output, ", proxy = 0x%X > limit)\n", (int)proxy);};);
               }
            } else {
               DEBUG_CODE({fprintf(output, ", proxy = 0x%X < limit)\n", (int)proxy);};);
            }
         } else {
            DEBUG_CODE({fprintf(output, ", opcode = 0x%X != LW)\n", (int)opcode);};);
         }
      } else {
         DEBUG_CODE({fprintf(output, ", opcode == 0x0)\n");};);      
      }
   } else {
      DEBUG_CODE({fprintf(output, ", reentered)\n");};);     
   }
   
   /* Exception not handled, let sighandler decide what to do.  */
   BetaSignalHandler(sig, code, scp, addr);
}
/******************************* SGI end ******************************/
#endif /* sgi */

/******************************* HPUX9PA: ********************************/
#ifdef hpux9pa
static void *getRegisterContents(unsigned long reg, ucontext_t *ucon, long returnSP);
static long sourceReg(unsigned long instruction, ucontext_t *ucon, long returnSP);
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon);

static void *getRegisterContents(unsigned long reg, ucontext_t *ucon, long returnSP)
{

}

static long sourceReg(unsigned long instruction, ucontext_t *ucon, long returnSP)
{

}


/* HPUX9PA:
   proxyTrapHandler: Will decode the faulting instruction, lookup the
   object, and insert a reference to it in the register previously
   containing the proxy. */
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  unsigned long instruction, returnPC, returnSP, absAddr = 0;
  
  void *ip;
  
  static int reentered = 0;

  INFO_PERSISTENCE(numPF++);

  if (!reentered) {
     reentered = 1;
     /* Fetch the faulting instruction. */
     instruction = (* (long *) (ucon->uc_mcontext.ss_narrow.ss_pcoq_head));
    if (instruction) {
       /* PC to jump to when fetch has completed: */
      returnPC = ucon->uc_mcontext.ss_narrow.ss_pcoq_head;
       /* SP to restore when fetch has completed: */
      returnSP = ucon->uc_mcontext.ss_narrow.ss_pcoq_head;
       
       if (sourceReg(instruction, ucon, returnSP)) {
          if (sourcereg != -1) {
             /* Ok, so this is a genuine refNone or proxy reference. */
             ip = getRegisterContents(sourcereg, ucon, returnSP);
             
             if (inPIT(ip)) {
                /* Calculate absolute address by looking in appropriate tables */
                
                /* 'unswizzleReference' *might* call back into beta code to
                   rebind special references. Thus the call is protected using
                   the 'BetaCallback' abstraction. */
                BetaCallback(ucon, 
                             returnSP, 
                             absAddr = (long)unswizzleReference(ip));
             } else {
                DEBUG_CODE({fprintf(output, ", proxy not in PIT 0x%X)\n", (int)ip);};);
             }
             
             if (absAddr) {
                /* We have fetched the object, and should continue execution. */
                switch (sourcereg) {
                  case 0x0: /* g0 */
                     fprintf(output, "proxyTrapHandler: "
                             "Code using %%g0 for proxy!!\n");
                     DEBUG_CODE(ILLEGAL);
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
                     DEBUG_CODE(ILLEGAL);
                     BetaExit(1);
                }
                reentered = 0;
                return;
             }
          } else {
             DEBUG_CODE({fprintf(output, ", could not retreive source reg)\n");};);
          }
       } else {
          DEBUG_CODE({fprintf(output, 
                              ", could not decode instruction = 0x%X)\n",
                              (int)instruction);};);
       }
    } else {
       DEBUG_CODE({fprintf(output, 
                           ", instruction is NULL)\n");};);
    }
  } else {
     DEBUG_CODE({fprintf(output, ", reentered)\n");};);     
  }
  /* If we get here, it was an ordinary SIGBUS, SIGSEGV or object
     could not be loaded */
  BetaSignalHandler(sig, info, ucon);
}

/******************************* HPUX9PA end ******************************/
#endif /* hpux9pa */

/******************************* UNIX: ********************************/
#ifdef UNIX
static void InstallProxyHandler(void)
{
#ifndef macosx
  InstallSigHandler(SIGBUS,  (void*)proxyTrapHandler);
  InstallSigHandler(SIGSEGV, (void*)proxyTrapHandler);
#endif /* macosx */
}

void initProxyTrapHandler(void)
{ 
  InstallProxyHandler();
}
#endif /* UNIX */

/* GLOBAL FUNCTIONS */
void printProxyStatistics(void)
{
   ;
}

#ifdef RTDEBUG
void chrashSIGSEGV(void)
{
  long *addr, cont;
  
  fprintf(stderr, "chrashSIGSEGV (0x%X):\n", (int)chrashSIGSEGV);
  
  addr = (long *)0x0;
  cont = *addr;
  
  fprintf(stderr, "Contents of 0x%X = 0x%X\n", (int)addr, (int)cont);
}

void chrashSIGBUS(void)
{
  long *addr, cont;
   
  fprintf(stderr, "chrashSIGBUS (0x%X):\n", (int)chrashSIGBUS);

  addr = (long *)0x1;
  cont = *addr;
   
  fprintf(stderr, "Contents of 0x%X = 0x%X\n", (int)addr, (int)cont);
}

void chrashFuncNULL(void)
{
  long (*func)(void) = NULL;
  
  /* fprintf(stderr, "chrashFuncNULL (0x%X):\n", (int)chrashFuncNULL); */

  fprintf(stderr, "Func val = %X\n", (int)func());
}
#endif /* DEBUG */
#endif /* PERSIST */
