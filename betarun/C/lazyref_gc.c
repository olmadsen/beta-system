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
 * sparc.
 *
 * On linux, nti and mac, most work is done in BetaError in exit.c
 * and in RefNone in Misc.run, Qua (Qua.run) and ChkRA 
 * (CheckReferenceAssignment.run).
 * Corresponding changes for the C runtime system are made in Misc.c, Qua.c
 * and CheckReferenceAssignment.c. */

#include "beta.h"

#ifdef RTLAZY
#include "data.h"

#ifdef sparc
#include "../CRUN/crun.h"
#endif /* sparc */

#ifdef INLINE
#undef INLINE
#endif
#ifdef __GNUC__
#define INLINE __inline__
#else
#define INLINE 
#endif

#ifdef AssignReference
#undef AssignReference
#endif
/* Use the function in betarun/GC/misc.c */
#define AssignReference assignRef

GLOBAL(static int negAOAmax) = 0; 
/* Max number of integers possible to put into the negAOArefs table. */

GLOBAL(static int negIOAsize) = 0; 
/* Current number of entries in the negIOArefs table. */

GLOBAL(static int negIOAmax) = 0; 
/* Max number of integers possible to put into the negIOArefs table. */

#define DEFAULTNEGTABLESIZE 32

void NegAOArefsRESET (void) { negAOAsize = 0; }
void negIOArefsFREE (void) { FREE (negIOArefs); negIOArefs = 0; }
   
void NegAOArefsINSERT(long fieldAdr)  
{     
  if (negAOAsize == negAOAmax) {
    if (negAOAmax == 0) {
      negAOAmax = DEFAULTNEGTABLESIZE;
      negAOArefs = (long *) MALLOC (negAOAmax*sizeof(long));
    } else {
      negAOAmax = 2*negAOAmax;
      negAOArefs = (long *) REALLOC (negAOArefs, negAOAmax*sizeof(long));
    }
  }

  DEBUG_LAZY(fprintf(output, "NegAOArefsINSERT(0x%x: %d) at index %d at address 0x%x\n", (int)fieldAdr, *((int *) fieldAdr), (int)negAOAsize, (int)&negAOArefs[negAOAsize] ));

  negAOArefs[negAOAsize++] = fieldAdr;
}


void NegIOArefsINSERT(long fieldAdr)
{
  if (negIOAsize == negIOAmax) {
    negIOAmax = 2*negIOAmax;
    negIOArefs = (long *) REALLOC (negIOArefs, negIOAmax*sizeof(int));
  }

  DEBUG_LAZY(fprintf (output, "NegIOArefsINSERT(0x%x: %d) at index %d\n", (int)fieldAdr, *((int *) fieldAdr), (int)negIOAsize));

  negIOArefs[negIOAsize++] = fieldAdr;
}


void preLazyGC ()
{
  DEBUG_LAZY(fprintf (output, "preLazyGC\n"));
  negIOAsize = 0; 
  negIOAmax = DEFAULTNEGTABLESIZE;
  negIOArefs = (long *) MALLOC (negIOAmax*sizeof(int));
  DEBUG_LAZY(fprintf (output, "preLazyGC done\n"));
}

static INLINE int danglerLookup (int* danglers, int low, int high, int dangler)
{ int mid;

  DEBUG_LAZY(fprintf (output, "danglerLookup(%d)\n", dangler)); 

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

void setupDanglers (int* danglers, long* objects, int count)
{ int i, dangler, inx;

  DEBUG_LAZY(fprintf (output, "setupDanglers\n"));

  DEBUG_LAZY(fprintf (output, "setupDanglers: processing negIOArefs\n"));
  for (i = 0; i < negIOAsize; i++) {
    DEBUG_LAZY(fprintf(output, "  trying index %d\n", i));
    dangler = (*((int *) negIOArefs[i]));
    if (isLazyRef(dangler))
      if ((inx = danglerLookup (danglers, 0, count - 1, dangler)) >= 0) {
	DEBUG_LAZY(fprintf (output, "setupDanglerIOA(%d)\n", dangler)); 
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
	  AssignReference ((long *) negIOArefs[i], (Item *) objects[inx]);
      }
  }
  
  negIOArefsFREE();

  DEBUG_LAZY(fprintf (output, "setupDanglers: processing negAOArefs\n"));
  if (negAOArefs) {
    i = 0;
    while (i < negAOAsize) {
      DEBUG_LAZY(fprintf(output, "  trying index %d\n", i));
      dangler = (*((int *) negAOArefs[i]));
      if (isLazyRef(dangler)) {
	if ((inx = danglerLookup (danglers, 0, count - 1, dangler)) >= 0) {
	  DEBUG_LAZY(fprintf (output, "setupDanglerAOA(%d)\n", dangler)); 
	  AssignReference ((long *) negAOArefs[i], (Item *) objects[inx]);
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

GLOBAL(static protoPtr *roots) = 0;

#define ROOTSIZE 5879

void addDanglingProto (int dangler, int proto)
/* proto is the prototype of the object referred by dangler.
 * dangler is _not_ in this table already. */
{ int inx;
  protoPtr new;

  DEBUG_LAZY(printf ("addDanglingProto(%d)\n", dangler));
  
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
  protoPtr this, next_in_list;
#ifdef RTDEBUG
  int num = 0;
#endif

  DEBUG_LAZY(printf ("removeDanglingProto(%d)\n",dangler));
  
  Claim(isLazyRef(dangler), "isLazyRef(dangler)");
  inx = (-dangler)%ROOTSIZE;
  Claim((0<=inx)&&(inx<ROOTSIZE), 
		   "removeDanglingProto: inx legal index");
  this = roots[inx];

  while (this) {
    Claim(++num<=ROOTSIZE, "At most ROOTSIZE protoPtr in roots");
    if (this->dangler == dangler) {
      if (this->next) 
	this->next->prev = this->prev;
      if (this->prev) {
	this->prev->next = this->next;
      } else {
	roots[inx] = this->next;
      }
      
      next_in_list = this->next;
      FREE (this);
      this = next_in_list;
    } else {
      this = this->next;
    }
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

unsigned long lazyTrapHandler(unsigned long dangler)
{  
  LazyDangler = dangler;

  /* call beta object handling the lazy fetch */
  /* A reference to this object is saved in 'LazyItem'. */
  /* sek: The lazyItem is an object receiving no arguments and exiting
     no results. How this can yield an absolute address to patch back
     into the register holding the lazy reference is completely
     unclear. The current author does not have enough knowledge about
     the implementation of the old persistent store in order to
     discover how the lazyItem can help to load the referred
     object. Callbacks to beta are implemented on all platforms, thus
     this is not the problem. The problem is that the code loading the
     lazyly referred object cannot be located anywhere in either
     'objectserver' or 'persistentstore'. */
  
  fprintf(output, 
	  "lazyTrapHandler: \n"
	  "             Lazy reference encountered. This is not implemented.\n"
	  "               Please disallow the use of lazy references by\n"
	  "             setting 'allowLazyFetch' in the persistentstore to\n"
	  "             false.\n"
	  "               If large amounts of data are scanned, the new\n"
	  "             persistent store can be used instead of the old.\n"
	  "             Include '~beta/persistentstore/virtualobjectstore'\n"
	  "             instead to use the new persistent store.\n"); 
  fflush(output);
  return 0;
} 

int getDangler ()
{ return LazyDangler; 
}

void clearDangler ()
{ LazyDangler = 0; }


/* initLazyTrapHandler:
 * called from objectserver/private/danglersbody, 
 * HandleDanglersInstall:descriptor
 * with the address of danglersprivate.onDanglerHit 
 * as argument.
 * HandleDanglersInstall is called from objectserver.init.
 * This means, that LazyItem (among others) will be set up
 * as soon as the objectserver is in function, regardless if
 * lazyfetch is enabled.
 */
void initLazyTrapHandler (Item * lazyHandler)
{ 
  /* Set up the LazyItem variable, which will be called
   * when a dangler is hit.
   */
  LazyItem = lazyHandler;
  
  /* save pointers for objects/functions in the
   * variables in the RTS, that are always present.
   * This allows for programs, that do not use lazyref_gc.o
   * to link anyway.
   */
  negAOArefsINSERT = NegAOArefsINSERT;
  negIOArefsINSERT = NegIOArefsINSERT;
  negAOArefsRESET = NegAOArefsRESET;
  findDanglingProto = FindDanglingProto;
}

/* Used by persistentstore to determine if the runtimesystem 
 * supports lazyFetch on the current platform.
 */
int lazyFetchImplemented(void)
{
#ifdef PERSIST
  return 0;
#else
#if defined (sun4s) || defined(hpux9pa) || defined(nti) || defined(linux)
  return 1;
#else
  return 0;
#endif
#endif /* PERSIST */
}

#endif /* RTLAZY */
