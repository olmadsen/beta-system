/* C/initialize.c */
extern void Initialize(void);
#ifdef sun4
extern char *strerror(int err);
#endif
#if defined(MAC)
extern void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern long StandAlone;
extern void EnlargeMacHeap(char *buf);
#endif /* Mac */
#ifdef RTDEBUG
extern long GetBetaCodeStart(void);
extern long GetBetaCodeEnd(void);
#endif /* RTDEBUG */

/* C/floats.c */
void SetupFPU(void);

/* C/betaenv.c */
extern void GetBetaEnv(void);

/* C/property.c */
extern void SetupProperties(char *);

/* C/wordsort.c */
#ifdef USE_WORDSORT
extern void WordSort(unsigned long*, int);
#else /* USE_WORDSORT */
extern int intcompare(const void *, const void *);
#define WordSort(base, num) {                                     \
  /*fprintf(output, "wordsort(0x%x, 0x%x)\n", base, num); */      \
  qsort((char*)(base), (num), sizeof(unsigned long), intcompare); \
}
#endif /* USE_WORDSORT */

#ifdef RTDEBUG
/* C/dumper.c */
extern char *DumpItemName(void);
extern char *DumpItemFragment(void);
extern char *DumpValContents(void);
extern void DumpIOA(void);
#endif

/* C/outpattern.c */
extern char *ProtoTypeName(struct ProtoType *theProto);
extern long M_Part(ref(ProtoType) proto);
extern void  DisplayObject(ptr(FILE),ref(Object),long);
extern char *ErrorMessage(enum BetaErr);
extern int  DisplayBetaStack(enum BetaErr, ref(Object), long *, long);
#ifdef RTDEBUG
extern void DescribeObject(struct Object *);
#endif
#ifdef NEWRUN
extern unsigned long        CodeEntry(struct ProtoType *theProto, long PC);
#endif

/* C/group.c */
extern struct group_header* NextGroup (struct group_header*);
extern char *GroupName(long, int);
int IsBetaPrototype(group_header *gh, long data_addr);
int IsBetaCodeAddr(long addr);

/* C/exit.c */
extern void BetaExit(long);
#ifdef MT
extern void ThreadExit(void);
#endif
#ifdef NEWRUN
extern void BetaError(enum BetaErr err, struct Object *theObj, long *SP, long *thePC);
#else
extern void BetaError(enum BetaErr, ref(Object));
#endif

/* C/cbfa.c */
extern void CBFAalloc(void);
extern void CBFArelloc(void);
extern void freeCBF(unsigned long);
extern void freeCallbackCalled(void);
#ifdef RTDEBUG
extern void CBFACheck(void);
#endif

/* C/sighandler.c */
extern void SetupBetaSignalHandlers(void);
extern void InstallSigHandler(int sig);

#ifdef MT
/* C/multithread.c */
extern void destroy_TSD(void);
extern void initSynchVariables(void);
extern int numProcessors(int online);
extern thread_t attToProcessor(struct Component *comp);
extern void SetupVirtualTimerHandler(void);
extern void SetupVirtualTimer(unsigned usec);
extern void* MT_malloc(int size);
#endif /* MT */

/* C/valhallaComm.c */
extern void valhallaInit (int debug_valhalla);

/* GC/block.c */
extern ref(Block) newBlock(long);
extern void freeBlock(ref(Block));
extern long inArea(ref(Block), ref(Object));

/* GC/objectsize.c */
extern long ObjectSize(ref(Object));

/* GC/aoatoioa.c */
extern void AOAtoIOAInsert(handle(Object));
extern long AOAtoIOAalloc(void);
extern void AOAtoIOAClear(void);
#ifdef RTDEBUG
void AOAtoIOACheck(void);
void AOAtoIOAReport(void);
#endif

/* GC/aoa.c */
extern void tempAOArootsAlloc(void);
extern void tempAOArootsFree(void);
#ifdef NEWRUN
extern struct Object *AOAalloc(long numbytes, long *SP);
extern struct Object *AOAcalloc(long numbytes, long *SP);
#else
extern struct Object *AOAalloc(long numbytes);
extern struct Object *AOAcalloc(long numbytes);
#endif
#ifdef MT
extern struct Object *AOAalloc(long numbytes);
extern struct Object *AOAcalloc(long numbytes);
#endif
extern ref(Object) CopyObjectToAOA(ref(Object));
extern void AOAGc(void);
#ifdef RTDEBUG
extern void AOACheck(void);
extern void AOACheckObject(ref(Object));
extern void AOACheckReference(handle(Object));
extern void AOACheckObjectSpecial(ref(Object));
#endif

/* GC/copyobject.c */
extern ref(Object) NewCopyObject(ref(Object), handle(Object));

/* GC/stack.c */
extern void ProcessStack(void);
#ifdef NEWRUN
extern void ProcessStackFrames(long SP, long StackStart, long stopAtComp, long dynOnly, CellProcessFunc func);
extern void ProcessStackObj(struct StackObject *, CellProcessFunc func);
#else
extern void ProcessStackObj(struct StackObject *);
#endif

/* GC/ioa.c */
extern void IOAGc(void);
extern void ProcessReference(handle(Object));
extern void ProcessObject(ref(Object));
extern void ProcessAOAReference(handle(Object));
extern void ProcessAOAObject(ref(Object));
extern void CompleteScavenging(void);
#ifdef NEWRUN
extern void DoIOACell(struct Object **theCell,struct Object *theObj);
#endif
#ifdef RTDEBUG
extern void IOACheck(void);
extern void IOACheckObject(ref(Object));
extern void IOACheckReference(handle(Object));
#endif

/* GC/lvra.c */
extern ref(ValRep) LVRAAlloc(ref(ProtoType), long);
extern ref(ValRep) LVRACAlloc(ref(ProtoType), long);
extern long inLVRA(ref(Object));
extern void LVRAkill(struct ValRep *);
#ifdef CHECK_LVRA_IN_IOA
extern ref(Object) CopyObjectToLVRA(ref(ValRep)); 
#endif
#ifdef RTDEBUG
void LVRACheck(void);
long LVRAAlive(ref(ValRep));
#endif

/* GC/misc.c */
extern void assignRef(long *theCell, ref(Item) newObject);
#ifdef RTDEBUG
extern void Illegal(void);
#endif
extern long isObject(ref(Object));
extern long inBetaHeap(ref(Object));
#ifdef RTDEBUG
extern void Claim(long, char*);
#endif
#if defined(MAC)
extern void InitTheCursor(void);
extern void RotateTheCursor(void);
extern void RotateTheCursorBack(void);
#endif

#ifdef NEWRUN
/* Defined in betaenv */
extern void DoGC(long *SP); /* The one called directly from betaenv */
extern void doAtt(long SPx, struct Object *topObj, long spSize, long *stack, long entry);
extern long *GetSP(void);
extern void CallB(struct Object *caller,
		          struct Object *callee,
		          long address,
		          long SP);
extern void BETA_main(void);
#ifdef ppcmac
extern void FlushCodeCash(long start, long end);
#endif

extern struct Object * GetThis(long *SP);
#endif


#if defined(sun4)
/* Fucking header files on sun4 do not include function prototypes?? */

extern void *memalign(/*unsigned alignment, unsigned size*/);
extern int fprintf(FILE *, const char *, ...);
extern int fflush(FILE *);
extern int tolower(int);
extern int fclose(FILE *);
extern int pclose(FILE *);
extern int fscanf(FILE *stream, const char *format, ...);
extern int shutdown(int s, int how);
#include <sys/types.h>
#include <sys/socket.h>
extern int socket(int domain, int type, int protocol);
extern int connect(int s, struct sockaddr *name, int namelen);
extern int bind(int s, struct sockaddr *name, int namelen);
extern int getsockname(int s, struct sockaddr *name, int *namelen);
extern int accept(int s, struct sockaddr *name, int *namelen);
extern int getpeername(int s, struct sockaddr *name, int *namelen);
extern int listen(int s, int backlog);
extern int sigsetmask(int mask);
#endif
