#include "beta.h"

void pro_dummy() {

#ifdef sparc
  USE();
#endif /* sparc */
  
}

#ifdef PERSIST
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#include <signal.h>

#define INITIALPROXYLISTSIZE 0x100

/* block.c */
extern void mmapInitial(unsigned long numbytes);

/* sighandler.c */
extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);

typedef struct _Proxy {
  void *dummy;               /* ? */
  long GCAttr;
  long id;                   /* Id of block in store */
  long offset;               /* Offset of object in block */
} Proxy;

typedef struct _ProxyList {
  u_long length;
  u_long top;
  Proxy plist[INITIALPROXYLISTSIZE];
} ProxyList;

/* LOCAL MACROS */
#define MAXNUMPROXIES 0x160000
#define asLong(p) ((long) p)

#define PROXYALIVE             1
#define PROXYMOVED             2
#define PROXYDEAD              3
#define PROXYPOTENTIALLYDEAD   4

#define ISPROXYALIVE(x) ((x == PROXYALIVE) || (x == PROXYMOVED))

/* LOCAL VARIABLES */
/* Proxy space of 8192 Kb */
static struct _Proxy proxySpace[MAXNUMPROXIES];    /* */

static void *PIT, *PITTop, *PITLimit; /* proxy indirection table */

static struct _Proxy *nextFree;
static long returnPC, returnSP, absAddr, sourcereg;
static u_long rd;
static u_long rs1;
static u_long rs2;

/* LOCAL FUNCTIONS */
static void initProxyTrapHandler(void);
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon);
static void findNextFree(void);

/* Statistics */
#ifdef RTINFO
static u_long numProxies;
static u_long proxyHit;
#endif /* RTINFO */

/* */

#ifdef RTINFO
void showProxyStatistics(void) {
  fprintf(output,"[Proxy Hit: 0x%X times]\n", (int)proxyHit);
}
#endif /* RTINFO */

static Proxy *asProxy(long ip) 
{
  long offset;
  /* ip is the Indirect Proxy. */
  
  Claim((ip >= (long) PIT) && (ip < (long) PITLimit), "asProxy: Illegal proxy!\n");
  offset = ip - (long) PIT;
  
  return &proxySpace[offset];
}

long addConstantToProxy(long ip, long offset)
{
  Proxy *p;
  long newIp;

  p = asProxy(ip);
  
  findNextFree();
  
  nextFree -> dummy = p -> dummy;
  nextFree -> id = p -> id;
  nextFree -> offset =  p -> offset + offset;
  nextFree -> GCAttr = PROXYALIVE;

  newIp = (long) PIT + (((long) nextFree - (long) &proxySpace[0]) / sizeof(struct _Proxy));
  return newIp;
}

void freeProxySpace(void) 
{
  long count;
  
  INFO_PROXY(numProxies=0);
  for(count = 0; count < MAXNUMPROXIES; count++) {
    if (ISPROXYALIVE(proxySpace[count].GCAttr)) {
      proxySpace[count].GCAttr = PROXYPOTENTIALLYDEAD;
    }
  }
}

void removeProxyMovedMark(void)
{
  long count;
  
  INFO_PROXY(fprintf(output,"[Proxy GC: Removing proxy moved marks "));
  for(count = 0; count < MAXNUMPROXIES; count++) {
    if (proxySpace[count].GCAttr == PROXYMOVED) {
      proxySpace[count].GCAttr = PROXYALIVE;
    }
  }
  INFO_PROXY(fprintf(output,"]\n"));
}

void sweepAndCollectProxySpace(void) 
{
  long count;
  
  INFO_PROXY(fprintf(output,"[Proxy GC: "));
  for(count = 0; count < MAXNUMPROXIES; count++) {
    if (proxySpace[count].GCAttr == PROXYPOTENTIALLYDEAD) {
      proxySpace[count].GCAttr = PROXYDEAD;
    }
    INFO_PROXY
      (if (ISPROXYALIVE(proxySpace[count].GCAttr)) {
	numProxies++;
      });
  }
  INFO_PROXY(fprintf(output,"0x%X proxies used by process (%%%d)]\n", 
		     (int)numProxies, 
		     (int)(numProxies*100/MAXNUMPROXIES)));
}

void initProxySpace(void) 
{
  static int isInitialized = 0;
  if (!isInitialized) {
    long count;
    
    isInitialized = 1;
    
    for(count = 0; count < MAXNUMPROXIES; count++) {
      proxySpace[count].GCAttr = PROXYDEAD;
    }
    nextFree = &proxySpace[0];
    
    /* Allocate mmapped proxy indirection table. */
    mmapInitial((unsigned long) MAXNUMPROXIES * 4);
    PIT = mmapHeapTop;
    PITTop = mmapHeapTop;
    PITLimit = mmapHeapLimit;
    Claim(((long) PITLimit - (long) PITTop) == MAXNUMPROXIES * 4, 
	  "initProxySpace: Could not allocate PIT\n");
    INFO_PROXY(fprintf(output,"[ Proxy space: 0x%X -> 0x%X\n", (int)PIT, (int)PITLimit));
    initProxyTrapHandler();
  }
  /* Allocation is legal */
}

long proxyAlive(Object **theCell) 
{
  Proxy *p;
  
  Claim(forceAOAGC == TRUE, "No proxy gc on going!");

  p = asProxy((long) *theCell);
  
  Claim(p -> GCAttr != PROXYDEAD,"proxyAlive: Proxy resurrected!\n");
  
  p -> GCAttr = PROXYALIVE;
  
  return 0;
}

long proxyIsAlive(long ip) 
{
  Proxy *p;
  
  p = asProxy(ip);
  
  return (p -> GCAttr = PROXYALIVE);
}

static void findNextFree(void) 
{
  long once=0;
  
  while (nextFree -> GCAttr != PROXYDEAD) {
    if (nextFree < &proxySpace[MAXNUMPROXIES]) {
      nextFree++;
    } else {
      if (!once) {
	nextFree = &proxySpace[0];
	once = 1;
      } else {
	fprintf(output, "findNextFree: "
		"Out of proxy space\n");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
    }
  }
}

long newProxy(Block *theBlock, Object *theObj) 
{
  long newIp;
  
  /* new proxies are allocated alive */
  if (((long) BlockStart(theBlock) <= (long) theObj) && 
      ((long) theObj < (long) theBlock -> limit)) {
    if (!(unknownStore((char *)theBlock -> dummy))) {
      if (!(unknownId(theBlock -> id))) {

	findNextFree();
	
	nextFree -> dummy = (void *)theBlock -> dummy;
	nextFree -> id = theBlock -> id;
	nextFree -> offset = (long) theObj - (long) BlockStart(theBlock);
	nextFree -> GCAttr = PROXYALIVE;

	newIp = (long) PIT + (((long) nextFree - (long) &proxySpace[0]) / sizeof(struct _Proxy));
	return newIp;
      } else {
	fprintf(output, "createProxyObject: "
		"Unknown block id:%d\n",
		(int)(theBlock -> id));
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
    } else {
      fprintf(output, "createProxyObject: "
	      "Unknown block store:%s\n",
	      (char *)theBlock -> dummy);
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
  } else {
    fprintf(output, "createProxyObject: "
	    "Object not in block.\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return -1;
}

void getProxyAttributes(long ip,
			void **dummy,
			u_long *id,
			u_long *offset) 
{
  Proxy *p;
  
  p = asProxy(ip);
  
  *dummy = p -> dummy;
  *id = p -> id;
  *offset = p -> offset;
  
  return;
}

long inProxy(long ip)
{
  if ((ip >= (long) PIT) && (ip < (long) PITLimit)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

static void initProxyTrapHandler(void)
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

  INFO_PROXY(proxyHit = 0);
}

static u_long getRegisterContents(u_long reg, ucontext_t *ucon) 
{
  if (reg == 0) {
      return 0;
  } else if ((reg > 0) && (reg < 0x10)) {
    /* Get the value from the context */
    return ucon->uc_mcontext.gregs[reg + 3];
  } else if ((reg >= 10) && (reg < 0x20)) {
    /* Get the value from the stack */
    return (((u_long *) returnSP)[reg - 16]);
  } else {
    fprintf(output, "getRegisterContents: "
	    "Unsupported register\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return -1;
}

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
	if (inProxy(getRegisterContents(rs1, ucon))) {
	  sourcereg = rs1;
	}
      } else {
	if (inProxy(getRegisterContents(rs1, ucon))) {
	  sourcereg = rs1;
	  Claim(!inProxy(getRegisterContents(rs2, ucon)), "sourceReg: proxy in both rs1 and rs2\n");
	} else if (inProxy(getRegisterContents(rs2, ucon))) {
	  sourcereg = rs2;
	  Claim(!inProxy(getRegisterContents(rs1, ucon)), "sourceReg: proxy in both rs1 and rs2\n");
	}
      }
      /* Source reg is now set to the register containing the
	 proxy */
      return 1;
    }
  }
  return 0;
}

static int dummy;

static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  u_long instruction;
  long ip;

  /* Look below for info on 'ucontext_t' */
  
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
      { 
	Proxy *p;
	
	p = asProxy(ip);
	absAddr = (long)lookUpObject(p -> dummy, p -> id, p -> offset);
	/* INFO_PROXY(fprintf(output,"[Proxy lookup: 0x%X ]\n", (int)absAddr)); */
	Claim(inPersistentAOA(absAddr) != NULL, "Not in persistent AOA");

      } 	    
      
      if (absAddr) {
	INFO_PROXY(proxyHit++);
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

/* ucon is supplied to this handler by the system. The type
   'ucontext_t' is defined in ucontext.h,
   
   struct	ucontext {
   ulong_t		uc_flags;
   ucontext_t	*uc_link;
   sigset_t   	uc_sigmask;
   stack_t 	uc_stack;
   mcontext_t 	uc_mcontext;
   long		uc_filler[23];
   };
   
   the type 'mcontext_t' is defined in regset.h,
   
   typedef struct {
   gregset_t	gregs;	/ general register set /
   gwindows_t	*gwins;	/ POSSIBLE pointer to register windows /
   fpregset_t	fpregs;	/ floating point register set /
   xrs_t		xrs;	/ POSSIBLE extra register state association /
   long		filler[19];
   } mcontext_t;
   
   'gregs' is an array of the hardware state at the time the trap
   occured.
   
   #define	REG_PSR	(0)
   #define	REG_PC	(1)
   #define	REG_nPC	(2)
   #define	REG_Y	(3)
   #define	REG_G1	(4)
   #define	REG_G2	(5)
   #define	REG_G3	(6)
   #define	REG_G4	(7)
   #define	REG_G5	(8)
   #define	REG_G6	(9)
   #define	REG_G7	(10)
   #define	REG_O0	(11)
   #define	REG_O1	(12)
   #define	REG_O2	(13)
   #define	REG_O3	(14)
   #define	REG_O4	(15)
   #define	REG_O5	(16) 
   #define	REG_O6	(17) 
   #define	REG_O7	(18) 
   
   / the following defines are for portability /
   #define	REG_PS	REG_PSR
   #define	REG_SP	REG_O6
   #define	REG_R0	REG_O0
   #define	REG_R1	REG_O1
*/

void proxyStop(void)
{ 
  if (0) {
    USE();
  }
}

void *initProxyList(void) 
{
  ProxyList *pl = (ProxyList *)malloc(sizeof(struct _ProxyList));
  
  memset(&pl -> plist[0], 0, INITIALPROXYLISTSIZE * sizeof(struct _Proxy));
  pl -> top = 0;
  pl -> length = INITIALPROXYLISTSIZE;
  
  return (void *)pl;
}

u_long appendProxyToList(long ip, void **a) 
{
  Proxy *p;
  ProxyList **pl = (ProxyList **)a;
  
  while ((*pl) -> top >= (*pl) -> length) {
    u_long newLength = (*pl) -> length * 2 + 1;
    ProxyList *newPl = (ProxyList *)malloc(sizeof(u_long) +
					   sizeof(u_long) +
					   sizeof(struct _Proxy) * newLength);
    
    memcpy(newPl, *pl, sizeOfProxyList(*a));
    
    newPl -> top = (*pl) -> top;
    newPl -> length = newLength;
    
    memset(*pl, 0, sizeOfProxyList(*a));
    
    free(*pl);
    *pl = newPl;
  }
  
  /* */
  p = asProxy(ip);
  
  /* Check if this proxy has been moved to the list allready */
  if (p -> GCAttr == PROXYMOVED) {
    /* The index of the proxy has been saved in the dummy
       attribute. */
    return (u_long) (p -> dummy);
  } else {
    (*pl) -> plist[(*pl) -> top] = *p;
    (*pl) -> top++;
    p -> GCAttr = PROXYMOVED;
    p -> dummy = (void *)((*pl) -> top - 1);
    return (*pl) -> top - 1;
  }
  return -1;
}

void freeProxyList(void *a) 
{  
  ProxyList *pl = (ProxyList *)a;
  
  memset(pl, 0, sizeOfProxyList(a));
  
  free(pl);
} 

u_long sizeOfProxyList(void *a)
{
  ProxyList *pl = (ProxyList *)a;
  
  return 
    sizeof(u_long) + 
    sizeof(u_long) + 
    sizeof(struct _Proxy) * pl -> top;
}

u_long *appendProxiesToProcess(void *a)
{
  ProxyList *pl = (ProxyList *)a;
  u_long count;
  u_long *proxyMap;
  
  proxyMap = (u_long *)malloc(sizeof(u_long) * pl -> top + 1);

  /* First index is used to hold length */
  proxyMap[0] = pl -> top;

  for (count=0; count<pl -> top; count++) {
    findNextFree();
    
    nextFree -> dummy = pl -> plist[count].dummy;
    nextFree -> id = pl -> plist[count].id;
    nextFree -> offset = pl -> plist[count].offset;
    nextFree -> GCAttr = PROXYALIVE;
    
    proxyMap[count + 1] = (long) PIT + (((long) nextFree - 
					 (long) &proxySpace[0]) / sizeof(struct _Proxy));
  }
  
  return proxyMap;
  
}
#endif /* PERSIST */
