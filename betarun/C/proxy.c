#include "beta.h"

extern void mmapInitial(unsigned long numbytes);

typedef struct _Proxy {
  void *dummy;               /* ? */
  long GCAttr;
  long id;                   /* Id of block in store */
  long offset;               /* Offset of object in block */
} Proxy;

/* LOCAL MACROS */
#define MAXNUMPROXIES 0x10000
#define asLong(p) ((long) p)

#define PROXYALIVE             1
#define PROXYDEAD              2
#define PROXYPOTENTIALLYDEAD   3


/* LOCAL VARIABLES */
/* Proxy space of 768 Kb */
static struct _Proxy proxySpace[MAXNUMPROXIES];    /* */

static void *PIT, *PITTop, *PITLimit; /* proxy indirection table */

static struct _Proxy *nextFree;

/* LOCAL FUNCTIONS */

/* */

static Proxy *asProxy(long ip) 
{
  long offset;
  /* ip is the Indirect Proxy. */

  Claim((ip >= (long) PIT) && (ip < (long) PITLimit), "asProxy: Illegal proxy!\n");
  offset = ip - (long) PIT;
  
  return &proxySpace[offset];
}

void freeProxySpace(void) 
{
  long count;
  
  for(count = 0; count < MAXNUMPROXIES; count++) {
    if (proxySpace[count].GCAttr == PROXYALIVE) {
      proxySpace[count].GCAttr = PROXYPOTENTIALLYDEAD;
    }
  }
}

void sweepAndCollectProxySpace(void) 
{
  long count;
  
  for(count = 0; count < MAXNUMPROXIES; count++) {
    if (proxySpace[count].GCAttr == PROXYPOTENTIALLYDEAD) {
      proxySpace[count].GCAttr = PROXYDEAD;
    }
  }
}

void initProxySpace(void) 
{
  static isInitialized = 0;
  USE(); /* This has no meaning. So don't worry about it. */
  if (!isInitialized) {
    long count;

    isInitialized = 1;
    
    for(count = 0; count < MAXNUMPROXIES; count++) {
      proxySpace[count].GCAttr = PROXYDEAD;
    }
    nextFree = &proxySpace[0];
    
    /* Allocate mmapped proxy indirection table. */
    mmapInitial((u_long) MAXNUMPROXIES * 4);
    PIT = mmapHeapTop;
    PITTop = mmapHeapTop;
    PITLimit = mmapHeapLimit;
    Claim(((long) PITLimit - (long) PITTop) == MAXNUMPROXIES * 4, "initProxySpace: Could not allocate PIT\n");
    
  }
}

long proxyAlive(Object **theCell) 
{
  Proxy *p;
  
  p = asProxy((long) *theCell);
  
  Claim(p -> GCAttr != PROXYDEAD,"proxyAlive: Proxy resurrected!\n");
  
  p -> GCAttr = PROXYALIVE;

  return 0;
}

static void findNextFree() 
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
	
	return (long) PIT + (((long) nextFree - (long) &proxySpace[0]) / sizeof(struct _Proxy));
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

long inProxy(long ip)
{
#ifdef sparc
  if ((ip >= (long) PIT) && (ip < (long) PITLimit)) {
    return TRUE;
  } else {
    return FALSE;
  }
#endif /* sparc */
  return FALSE;
}
