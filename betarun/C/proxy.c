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

/* block.c */
extern void mmapInitial(unsigned long numbytes);

/* sighandler.c */
extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);

/* LOCAL MACROS */
#define MAXNUMPROXIES 0x160000 
#define INITIALPROXYLISTSIZE 0x100 /* Initial size of normalized proxy
				      lists local to an AOA block that
				      is to be exported. */

#define asLong(p) ((long) p)

#define PROXYALIVE             1
#define PROXYMOVED             2
#define PROXYDEAD              3
#define PROXYPOTENTIALLYDEAD   4

#define ISPROXYALIVE(x) ((x == PROXYALIVE) || (x == PROXYMOVED))

/* LOCAL TYPES */
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

/* LOCAL VARIABLES */

/* Proxy space */
static struct _Proxy *proxySpace;
static u_long length;

static void *PIT, *PITTop, *PITLimit; /* proxy indirection table */

static u_long nextFree;
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

/* asProxy: Given an indirect proxy-reference into the mmapped area a
   reference to the actual proxy object is returned. */
static Proxy *asProxy(long ip) 
{
  long offset;
  
  /* ip is the Indirect Proxy. */
  
  Claim((ip >= (long) PIT) && (ip < (long) PITLimit), "asProxy: Illegal proxy!\n");

  offset = ip - (long) PIT;
  
  Claim(offset >= 0 && offset < length, "asProxy: Illegal proxy!\n");
  
  return &proxySpace[offset];
}

/* addConstantToProxy: Given a proxy reference indirectly referring
   some object with some offset in some block, a proxy referring the
   an object at offset 'offset' further down in the same block is
   returned. This is mainly used to support proxies to part
   objects. */
long addConstantToProxy(long ip, long offset) 
{ 
  Proxy *p; 
  long newIp;
  
  findNextFree();
  
  /* findNextFree might reallocate proxySpace, thus findNextFree
     should come before asProxy, since asProxy returns pointer into
     proxySpace. */
  
  p = asProxy(ip);
  
  proxySpace[nextFree].dummy = p -> dummy;
  proxySpace[nextFree].id = p -> id;
  proxySpace[nextFree].offset =  p -> offset + offset;
  proxySpace[nextFree].GCAttr = PROXYALIVE;
  
  newIp = (long) PIT + nextFree;
  return newIp;
}

/* freeProxySpace: All proxies are marked as potentially dead. Will be
   called before a proxy GC, which is done in connection with normal
   AOAGC. */
void freeProxySpace(void) 
{
  long count;
  
  INFO_PROXY(numProxies=0);
  for(count = 0; count < length; count++) {
    if (ISPROXYALIVE(proxySpace[count].GCAttr)) {
      proxySpace[count].GCAttr = PROXYPOTENTIALLYDEAD;
    }
  }
}

/* removeProxyMovedMark: When blocks are exported and the proxies they
   contain are 'normalized' and exported with the block, the proxies
   are marked as visited so all proxy references to the same proxy
   object will be translated to the same 'normalized' proxy value. The
   function below removes this mark so that ensuing exports will
   work.*/
void removeProxyMovedMark(void) { long count;
 
  INFO_PROXY(fprintf(output,"[Proxy GC: Removing proxy moved marks "));
  for(count = 0; count < length; count++) {
    if (proxySpace[count].GCAttr == PROXYMOVED) {
      proxySpace[count].GCAttr = PROXYALIVE;
    }
  }
  INFO_PROXY(fprintf(output,"]\n"));
}

/* sweepAndCollectProxySpace: All proxies marked as
   PROXYPOTENTIALLYDEAD are reclaimed. */
void sweepAndCollectProxySpace(void) 
{
  long count;
  
  INFO_PROXY(fprintf(output,"[Proxy GC: "));
  for(count = 0; count < length; count++) {
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

/* initProxySpace: */
void initProxySpace(void) 
{
  static int isInitialized = 0;
  if (!isInitialized) {
    long count;
    
    isInitialized = 1;

    proxySpace = (struct _Proxy *)malloc(sizeof (struct _Proxy) * INITIALPROXYLISTSIZE);
    length = INITIALPROXYLISTSIZE;

    for(count = 0; count < length; count++) {
      proxySpace[count].GCAttr = PROXYDEAD;
    }
    nextFree = 0;
    
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

/* proxyAlive: Marks the proxy referred by 'theCell' as alive. */
long proxyAlive(Object **theCell) 
{
  Proxy *p;
  
  Claim(forceAOAGC == TRUE, "No proxy gc on going!");

  p = asProxy((long) *theCell);
  
  Claim(p -> GCAttr != PROXYDEAD,"proxyAlive: Proxy resurrected!\n");
  
  p -> GCAttr = PROXYALIVE;
  
  return 0;
}

/* proxyIsAlive: Returns whether the proxy referred by 'ip' is marked
   as alive. */
long proxyIsAlive(long ip) 
{
  Proxy *p;
  
  p = asProxy(ip);
  
  return (p -> GCAttr = PROXYALIVE);
}

/* findNextFree: Searches for the next free proxy and extends the
   proxy space if necessary. */
static void findNextFree(void) 
{
  long once=0;
  
  while ((nextFree < length) && (proxySpace[nextFree].GCAttr != PROXYDEAD)) {
    nextFree++;
  }
  
  if (nextFree < length) {
    return;
  }

  if (!once) {
    nextFree = 0;
    once = 1;
  } else {
    /* We should extend the proxy space */
    u_long newLength, count;
    struct _Proxy *newProxySpace;
    
    once = 0;

    newLength = length * 2 + 1;
    
    if (newLength > MAXNUMPROXIES) {
      newLength = MAXNUMPROXIES;
      if (newLength == length) {
	fprintf(output, "findNextFree: "
		"Out of proxy space\n");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
    }
    
    newProxySpace = (struct _Proxy *)malloc(sizeof (struct _Proxy) * newLength);
    
    if (length) {
      memcpy(newProxySpace, proxySpace, sizeof (struct _Proxy) * length);
      
      free(proxySpace);
      proxySpace = NULL;
    }
    
    proxySpace = newProxySpace;
    
    for(count = length; count < newLength; count++) {
      proxySpace[count].GCAttr = PROXYDEAD;
    }
    
    nextFree = length;
    length = newLength;
    
    /* Try again */
    findNextFree();
  }
}

/* newProxy: Return a proxy reference to theObj in theBlock. */
long newProxy(Block *theBlock, Object *theObj) 
{
  long newIp;
  
  /* new proxies are allocated alive */
  if (((long) BlockStart(theBlock) <= (long) theObj) && 
      ((long) theObj < (long) theBlock -> limit)) {
    if (!(unknownStore((char *)theBlock -> dummy))) {
      if (!(unknownId(theBlock -> id))) {

	findNextFree();
	
	proxySpace[nextFree].dummy = (void *)theBlock -> dummy;
	proxySpace[nextFree].id = theBlock -> id;
	proxySpace[nextFree].offset = (long) theObj - (long) BlockStart(theBlock);
	proxySpace[nextFree].GCAttr = PROXYALIVE;

	newIp = (long) PIT + nextFree;
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

/* getProxyAttributes: Get the proxy attributes of the proxy 'ip'. */
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

/* inProxy: Return whether 'ip' refers a proxy */
long inProxy(long ip)
{
  if ((ip >= (long) PIT) && (ip < (long) PITLimit)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/* initProxyTrapHandler: */
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

/* getRegisterContents: If register refers to G or O register the
   contents can be found in the ucon. Otherwise the contents is on the
   stack. The stack pointer is in the global variable 'returnSP'. Why
   this separation has been made between the O/G and I/L registers is
   unclear to me but it is imposed by the system. */
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

static u_long dummy;

/* proxyTrapHandler: Will decode the faulting instruction, lookup the
   object, and insert a reference to it in the register previously
   containing the proxy. */
static void proxyTrapHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  u_long instruction;
  long ip;
  
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
	void *dummy;
	u_long offset, id;
	
	p = asProxy(ip);
	dummy = p -> dummy;
	offset = p -> offset;
	id = p -> id;
	absAddr = (long)lookUpObject(dummy, id, offset);
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

/* initProxyList: Used when exporting blocks to initialize the list
   that holds the proxies used by the block. */
void *initProxyList(void) 
{
  ProxyList *pl = (ProxyList *)malloc(sizeof(struct _ProxyList));
  
  memset(&pl -> plist[0], 0, INITIALPROXYLISTSIZE * sizeof(struct _Proxy));
  pl -> top = 0;
  pl -> length = INITIALPROXYLISTSIZE;
  
  return (void *)pl;
}

/* appendProxyToList: Used when exporting blocks to append a proxy
   used by the block being exported. */
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

/* freeProxyList: Used when exporting blocks to clear list holding
   proxies used in the block. */
void freeProxyList(void *a) 
{  
  ProxyList *pl = (ProxyList *)a;
  
  memset(pl, 0, sizeOfProxyList(a));
  
  free(pl);
} 

/* sizeOfProxyList: Used when exporting blocks to return the size of
   the list holding proxies used in the block. */
u_long sizeOfProxyList(void *a)
{
  ProxyList *pl = (ProxyList *)a;
  
  return 
    sizeof(u_long) + 
    sizeof(u_long) + 
    sizeof(struct _Proxy) * pl -> top;
}

/* appendProxiesToProcess: Used when importing blocks to append the
   proxies used by the block to the local proxy space. */
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
    
    proxySpace[nextFree].dummy = pl -> plist[count].dummy;
    proxySpace[nextFree].id = pl -> plist[count].id;
    proxySpace[nextFree].offset = pl -> plist[count].offset;
    proxySpace[nextFree].GCAttr = PROXYALIVE;
    
    proxyMap[count + 1] = (long) PIT + nextFree;
  }
  
  return proxyMap;
  
}
#endif /* PERSIST */
