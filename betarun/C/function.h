/* C/initialize.c */
extern void Initialize(void);
#if defined(macintosh) || defined(MAC)
extern void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern long StandAlone;
extern void EnlargeMacHeap(char *buf);
#endif /* Mac */
#ifdef RTDEBUG
extern long GetBetaCodeStart(void);
extern long GetBetaCodeEnd(void);
#endif /* RTDEBUG */

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
extern char *ErrorMessage(long);
extern int  DisplayBetaStack(long, ref(Object), long *, long);
extern struct group_header* NextGroup (struct group_header*);
extern char* NameOfGroup (struct group_header *);
extern char *GroupName(long, int);
#ifdef RTDEBUG
extern void DescribeObject(struct Object *);
#endif
#ifdef NEWRUN
extern unsigned long        CodeEntry(struct ProtoType *theProto, long PC);
#endif

/* C/exit.c */
extern void BetaExit(long);
#ifdef NEWRUN
extern void BetaError(long errorNo, struct Object *theObj, long *SP);
#else
extern void BetaError(long, ref(Object));
#endif

/* C/cbfa.c */
extern void CBFAAlloc(void);
extern void CBFArelloc(void);
extern void freeCBF(unsigned long);
extern void freeCallbackCalled(void);
#ifdef RTDEBUG
extern void CBFACheck(void);
#endif

/* C/sighandler.c */
#ifdef sun4s
extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);
#else
#ifdef crts
extern void BetaSignalHandler (long sig);
#else
#if defined(linux) || defined(nti)
extern voidvoid BetaSignalHandler(long sig, struct sigcontext scp);
#else
extern void BetaSignalHandler(long sig, long code, struct sigcontext * scp, char *addr);
#endif /* linux || nti */
#endif /* crts */
#endif /* sun4s */

/* C/valhallaComm.c */
extern void valhallaInit(void);

/* GC/block.c */
extern ref(Block) newBlock(long);
extern void freeBlock(ref(Block));
extern long inArea(ref(Block), ref(Object));

/* GC/objectsize.c */
extern long ObjectSize(ref(Object));

/* GC/aoatoioa.c */
extern void AOAtoIOAInsert(handle(Object));
extern long AOAtoIOAAlloc(void);
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
extern void ProcessStackObj(struct StackObject *, void (*func)(struct Object **,struct Object *));
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
extern long GetDistanceToEnclosingObject(ref(Object));
#ifdef NEWRUN
extern void DoIOACell(struct Object **theCell, struct Object *theObj);
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
extern long LVRARestInBlock(ref(LVRABlock));
extern void LVRAkill(struct ValRep *);
#ifdef CHECK_LVRA_IN_IOA
extern ref(Object) CopyObjectToLVRA(ref(ValRep)); 
#endif
#ifdef RTDEBUG
void LVRACheck(void);
long LVRAAlive(ref(ValRep));
#endif

/* GC/misc.c */
#ifdef RTDEBUG
extern void Illegal(void);
#endif
extern long isObject(ref(Object));
extern long inBetaHeap(ref(Object));
extern void Claim(long, char*);
#if defined(macintosh) || defined(MAC)
extern void InitTheCursor(void);
extern void RotateTheCursor(void);
extern void RotateTheCursorBack(void);
#endif

#ifdef NEWRUN
extern struct Object *      GetThis(long *SP);
extern long *               GetBetaData1(void);
extern long *               GetSP(void);
#endif


#if defined(sparc) || defined(crts)
/* Fucking header files on sun4 do not include function prototypes?? */
extern void *memalign(/*unsigned alignment, unsigned size*/);
extern int fprintf(FILE *, const char *, ...);
extern int fflush(FILE *);
extern int tolower(int);
extern int fclose(FILE *);
/*
#if defined(sun4s) || defined(SUN4S)
extern int pclose(FILE *);
#else
extern void pclose(FILE *);
#endif
*/
extern int fscanf(FILE *stream, const char *format, ...);
#endif
