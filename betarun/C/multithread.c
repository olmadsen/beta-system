/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-96 Mjolner Informatics Aps.
 * multithread.c
 * by Peter Andersen, Morten Grouleff
 */

#include "beta.h"

#ifdef MT

#if defined(UNIX) || defined(nti)
#include <signal.h>
#endif /* UNIX || nti */

#ifdef sun4s
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#endif

#include <errno.h>
#include <unistd.h>

struct S_PreemptionLevel {
  unsigned long lock;
  unsigned long value;
  unsigned long inGC;
};

#ifdef RTDEBUG
static void AssertLock(mutex_t* lock)
{
  if (mutex_trylock(lock) != EBUSY) {
    fprintf(output, "Does not have required lock!\n");
    Illegal();
  }
}
#endif

void initSynchVariables(void)
{
  mutex_init(&tsd_lock, USYNC_THREAD, NULL);
  mutex_init(&lvra_lock, USYNC_THREAD, NULL);
  mutex_init(&aoa_lock,  USYNC_THREAD, NULL);
  mutex_init(&aoatoioa_lock,  USYNC_THREAD, NULL);
  mutex_init(&cbfa_lock, USYNC_THREAD, NULL);

#ifdef OURSEMAIMPL
  mutex_init(&cond_pause_lock, USYNC_THREAD, NULL);
  cond_init (&cond_pause, USYNC_THREAD, NULL);
#else
  mutex_init(&GC_lock, USYNC_THREAD, NULL);
  mutex_init(&ioa_lock, USYNC_THREAD, NULL);
  cond_init (&cond_startGC, USYNC_THREAD, NULL);
  mutex_init(&cond_startGC_lock, USYNC_THREAD, NULL);
  cond_init (&cond_GCdone, USYNC_THREAD, NULL);
  mutex_init(&cond_GCdone_lock, USYNC_THREAD, NULL);
#endif
}


TSD *create_TSD(void)
{
  TSD *tsd;
  int inx;

  mutex_lock(&tsd_lock);
  DEBUG_MT(TSDCheck());
  tsd = (TSD*)MALLOC(sizeof(TSD));
  tsd->_nums = MALLOC(sizeof(nums));

  /* insert newly created TSD into TSDlist */
  if (TSDlistlen <= NumTSD){
    int expand = numProcessors(TRUE); 
    DEBUG_MT(TSDCheck());
    DEBUG_MT(fprintf(output, "create_TSD: Expanding TSDlist:\n"));
    DEBUG_MT(fprintf(output,
		     "  TSDlist from: 0x%x, TSDlistlen from: %d\n", 
		     (int)TSDlist, (int)TSDlistlen));

    TSDlist = REALLOC(TSDlist, (TSDlistlen + expand)*sizeof(TSD*));
    memset(TSDlist + TSDlistlen, 0, expand * sizeof(TSD*));  
    TSDlistlen += expand;

    DEBUG_MT(fprintf(output,
		     "  TSDlist to:   0x%x, TSDlistlen to:   %d\n", 
		     (int)TSDlist, (int)TSDlistlen));
    DEBUG_MT(TSDCheck());
  }
  NumTSD++;
  
  /* Find free entry in TSDlist */
  for (inx = 0; TSDlist[inx]; inx++)
    ;
  tsd->_TSDinx = inx;
  TSDlist[inx] = tsd;
  
  DEBUG_MT(TSDCheck());

  mutex_unlock(&tsd_lock);

  /* Signal that the number of threads has changed */
  mutex_lock(&cond_pause_lock);
  cond_broadcast(&cond_pause);
  mutex_unlock(&cond_pause_lock);

  return tsd;
}

void CalculateSliceSize(void)
{
  DEBUG_MT(AssertLock(&tsd_lock));
  /* If more than one thread, make sure there are always spare slices.
   * Obtaining a new slice is cheap compared to the cost of 
   * syncronizing for GC.
   * When running only one thread, there is no need for slices.
   */
  NumIOASlices = (NumTSD > 1) ? 2 * NumTSD : 1;
  
  IOASliceSize = 
    ObjectAlignDown(((long)gIOALimit-(long)gIOATop) / NumIOASlices);

  /* However, we will not allow too small slice sizes (0 would be
   * foolish!).
   */
  if (IOASliceSize<2048){
    IOASliceSize=2048;
    /* NumIOASlices = (((long)gIOALimit-(long)gIOATop) / IOASliceSize); */
  }
  
  DEBUG_MT(fprintf(output, "CalculateSliceSize: Changed "
		   "NumIOASlices to: %d, IOASliceSize to: %d\n", 
		   (int)NumIOASlices, (int)IOASliceSize);
	   fflush(output));
}
  
void destroy_TSD(void)
{
  long inx = TSDinx;

  mutex_lock(&tsd_lock);
  DEBUG_MT(TSDCheck());
  free(Nums);
  free(TSDReg);
  TSDlist[inx] = NULL;
  TSDReg = NULL;
  NumTSD--;
  DEBUG_MT(TSDCheck());
  mutex_unlock(&tsd_lock);


  /* Some other thread may be initiating a GC.  
   * If we are the last to "join in", that thread wouldwait forever
   * without this...
   */
  mutex_lock(&cond_pause_lock);
  cond_broadcast(&cond_pause);
  mutex_unlock(&cond_pause_lock);
}

void ProcessTSD(void)
{
  int i;
  for (i = 0; i < TSDlistlen; i++) {
    if (TSDlist[i]) {
      DEBUG_MT(fprintf(output, 
		       "\nTSDlist[%d]: t@%d:\n", 
		       i, 
		       TSDlist[i]->_thread_id));

      DEBUG_MT(fprintf(output, 
		       "\tCurrentObject=0x%0x...", 
		       (int)TSDlist[i]->_CurrentObject));
      ProcessReference((handle(Object))(&TSDlist[i]->_CurrentObject));
      DEBUG_MT(fprintf(output, 
		       "CurrentObject=0x%0x\n", 
		       (int)TSDlist[i]->_CurrentObject));

      DEBUG_MT(fprintf(output, 
		       "\tOrigin=0x%0x...",
		       (int)TSDlist[i]->_Origin));
      ProcessReference((handle(Object))(&TSDlist[i]->_Origin));
      DEBUG_MT(fprintf(output, 
		       "Origin=0x%0x\n", (int)TSDlist[i]->_Origin));

      DEBUG_MT(fprintf(output, 
		       "\tSavedCallO=0x%0x...",
		       (int)TSDlist[i]->_SavedCallO));
      ProcessReference((handle(Object))(&TSDlist[i]->_SavedCallO));
      DEBUG_MT(fprintf(output, 
		       "SavedCallO=0x%0x\n", 
		       (int)TSDlist[i]->_SavedCallO));

      DEBUG_MT(fprintf(output, 
		       "\tActiveStack=0x%0x...",
		       (int)TSDlist[i]->_ActiveStack));
      ProcessReference((handle(Object))(&TSDlist[i]->_ActiveStack));
      DEBUG_MT(fprintf(output, 
		       "ActiveStack=0x%0x\n", 
		       (int)TSDlist[i]->_ActiveStack));

      DEBUG_MT(fprintf(output, 
		       "\tActiveComponent=0x%0x...",
		       (int)TSDlist[i]->_ActiveComponent));
      ProcessReference((handle(Object))(&TSDlist[i]->_ActiveComponent));
      DEBUG_MT(fprintf(output, 
		       "ActiveComponent=0x%0x\n", 
		       (int)TSDlist[i]->_ActiveComponent));
    }
#ifdef RTDEBUG
    else {
      DEBUG_MT(fprintf(output, "TSDlist[%d] is NULL\n", i));
    }
#endif
  }
  CompleteScavenging();
}

#ifdef RTDEBUG
static void TSDCheckReference(int i, struct Object *ref)
{
  if (ref && !(inBetaHeap(ref) && isObject(ref))) { 
    fprintf(output, "Illegal reference 0x%x in TSD[%d]\n", (int)ref, i); 
    Illegal();
  }
}

void TSDCheck(void)
{  
  int i;

  DEBUG_MT(AssertLock(&tsd_lock));
  for (i = 0; i < TSDlistlen; i++) {
    if (TSDlist[i]) {

      /* Check TSDinx */
      if (TSDlist[i]->_TSDinx != i){
	fprintf(output, 
		"Illegal TSDinx %d in TSD[%d]. NumTSD is %d.\n", 
		(int)TSDlist[i]->_TSDinx,
		i,
		(int)NumTSD);
	Illegal();
      }

      /* Check TSDFlags */
      if ( TSDlist[i]->_TSDFlags < 0 || TSDlist[i]->_TSDFlags>Flag_MAX ){
	fprintf(output, 
		"Illegal TSDFlags 0x%x in TSD[%d]. Flag_MAX is %d.\n", 
		(int)TSDlist[i]->_TSDFlags,
		i,
		(int)Flag_MAX);
	Illegal();
      }

      /* Check CTextPoolEnd */
      if ( TSDlist[i]->_CTextPoolEnd &&
	   (TSDlist[i]->_CTextPoolEnd<(char *)&TSDlist[i]->_CTextPool ||
	    TSDlist[i]->_CTextPoolEnd>(char *)&TSDlist[i]->_CTextPool[MAXCTEXTPOOL/4])){
	fprintf(output, 
		"Illegal CTextPoolEnd 0x%x in TSD[%d]. \n", 
		(int)TSDlist[i]->_CTextPoolEnd,
		i);
	fprintf(output, 
		"CTextPoolEnd lies in the interval [0x%x..0x%x[\n",
		(int)&TSDlist[i]->_CTextPool,
		(int)&TSDlist[i]->_CTextPool[MAXCTEXTPOOL/4]);
	Illegal();
      }

      /* Check thread_id. Cannot check against NumTSD, since several
       * threads may have been created and later destroyed by now,
       * in which case the thread id may be quite large 
       */
      if (TSDlist[i]->_thread_id > 100){
	fprintf(output, 
		"Suspicious thread id %d in TSD[%d]\n", 
		(int)TSDlist[i]->_thread_id,
		i);
	Illegal();
      }

      /* Check local IOA top and limit */
#if 0
      if (TSDlist[i]->_IOATop > TSDlist[i]->_IOALimit){
	fprintf(output, 
		"IOATop (0x%x) is above IOALimit (0x%x) in TSD[%d]\n", 
		(int)TSDlist[i]->_IOATop,
		(int)TSDlist[i]->_IOALimit,
		i);
	Illegal();
      }
      if (TSDlist[i]->_IOATop > gIOATop){
	fprintf(output, 
		"IOATop (0x%x) is above gIOATop (0x%x) in TSD[%d]\n", 
		(int)TSDlist[i]->_IOATop,
		(int)gIOATop,
		i);
	Illegal();
      }
      if (TSDlist[i]->_IOALimit > gIOALimit){
	fprintf(output, 
		"IOALimit (0x%x) is above gIOALimit (0x%x) in TSD[%d]\n", 
		(int)TSDlist[i]->_IOALimit,
		(int)gIOALimit,
		i);
	Illegal();
      }
#endif

      /* Check references */
      TSDCheckReference(i, (ref(Object))(TSDlist[i]->_CurrentObject));
      TSDCheckReference(i, (ref(Object))(TSDlist[i]->_Origin));
      TSDCheckReference(i, (ref(Object))(TSDlist[i]->_SavedCallO));
      TSDCheckReference(i, (ref(Object))(TSDlist[i]->_ActiveStack));
      TSDCheckReference(i, (ref(Object))(TSDlist[i]->_ActiveComponent));
    }
  }
}

#endif /* RTDEBUG */

void ProcessStackObj(struct StackObject *sObj)
{
  struct Object **handle = (struct Object **)&sObj->Body;
  struct Object **last   = (struct Object **)((long)&sObj->Proto + sObj->refTopOff);
  DEBUG_MT(fprintf(output, "ProcessStackObj: 0x%x\n",(int)sObj));
  while (handle<=last) {
    if (inBetaHeap(*handle) 
	&& isObject(*handle) 
	&& !inLVRA(*handle)){
      DEBUG_MT(fprintf(output, 
		       "ProcessStackObj: processing cell 0x%x (%s) in stackobject 0x%x\n",
		       (int)handle, ProtoTypeName((*handle)->Proto),
		       (int)sObj));
      ProcessReference(handle);
    } else {
      DEBUG_MT(fprintf(output, "ProcessStackObj: SKIPPED cell 0x%x in stackobject 0x%x\n",
		       (int)handle,
		       (int)sObj));
      DEBUG_MT(if(inLVRA(*handle)) fprintf(output, "ProcessStackObj: (in LVRA)\n"));
    }
    handle++;
  }
}
#ifdef RTDEBUG
void PrintStackObj(struct StackObject *sObj)
{
  struct Object **handle;
  struct Object **last;

  fprintf(output, "StackObj: 0x%x\n",(int)sObj);
  fprintf(output, "  BodySize:   0x%x\n",(int)sObj->BodySize);
  fprintf(output, "  refTopOff:  0x%x\n",(int)sObj->refTopOff);
  fprintf(output, "  dataTopOff: 0x%x\n",(int)sObj->dataTopOff);

  fprintf(output, "  References\n");
  handle = (struct Object **)&sObj->Body;
  last = (struct Object **)((long)sObj + sObj->refTopOff);
  while (handle<=last) {
    fprintf(output, 
	    "    0x%x: 0x%x (%s)\n",
	    (int)handle, 
	    (int)*handle, 
	    ProtoTypeName((*handle)->Proto));
    handle++;
  }

  fprintf(output, "  Data\n");
  handle = (struct Object **)((long)&sObj->Body + sObj->dataTopOff);
  last = (struct Object **)((long)sObj+headsize(StackObject)+sObj->BodySize);
  while (handle<=last) {
    fprintf(output, 
	    "    0x%x: 0x%x\n",
	    (int)handle, 
	    (int)*handle);
    handle++;
  }
}

#endif /*RTDEBUG*/

static struct Object *AllocObjectAndSlice(unsigned int numbytes, unsigned int reqsize)
{
  /* ASSUMPTION: that max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ */

  struct Object *newObj;

#ifdef RTDEBUG
  {
    int max = (numbytes>reqsize) ? numbytes : reqsize;
    Claim((int)gIOATop+max<=(int)gIOALimit, 
	  "AllocObjectAndSlice: gIOATop+max<=gIOALimit");
  }
#endif	     
  
  if (IOALimit == gIOATop){
    /* No other threads have been given a new slice since we got 
     * our last slice. So we can extend the current slice, and thus
     * utilize the remaining space in this slice, even though numbytes 
     * may be bigger.
     */
    newObj = (struct Object*)IOATop;
    IOATop = (long*)((long)IOATop + numbytes); /* size of object */
    gIOATop = (long*)((long)IOATop + reqsize-numbytes); /* size of slice */
  } else {
    newObj = (struct Object*)gIOATop;
    IOATop = (long*)((long)gIOATop + numbytes); /* size of object */
    gIOATop = (long*)((long)gIOATop + reqsize); /* size of slice */
  }
  savedIOALimit = IOALimit = gIOATop;

  return newObj;
}

/* Acquire cond_pause_lock and tsd_lock prior to calling */
static int CheckIfICanGC()
{ 
  int i;
  for (i = 0; i < TSDlistlen; i++)
    if (TSDlist[i] && (TSDlist[i]->_TSDFlags & Flag_DoingGC))
      return 0;
  return 1;
}

struct Object *doGC(unsigned long numbytes)
{
  /* Allocate an IOA slice. 
   * -Attempts to allocate max(numbytes,IOASliceSize) bytes.
   * -At least numbytes are allocated.
   *  A GC is triggered, if there is not room for max(numbytes,IOASliceSize).
   */

  static volatile int numReadyToGC;
  struct Object* newObj=0;
  unsigned long reqsize = numbytes;
  int i;
  
  do { /* do-while */
    mutex_lock(&cond_pause_lock);
    DEBUG_MT(fprintf(output,"t@%d: Got cond_pause_lock.\n", (int)ThreadId);
	     fflush(output);
	     );
    if (reqsize < IOASliceSize) reqsize = IOASliceSize;
  
    if (!IOATop) {
      /* IOATop is zero => this thread has not had a slice yet. */
      IOATop = gIOATop;
      DEBUG_MT(fprintf(output,"t@%d: Requesting initial slice.\n", (int)ThreadId);
	       fflush(output);
	       );
    } 
  
    if (do_unconditional_gc || gIOALimit < (long*)((long)gIOATop + reqsize)) {
      /* GC NEEDED */
      DEBUG_MT(fprintf(output,"t@%d: GC Needed.\n", (int)ThreadId);
	       fflush(output);
	       );
      if (ActiveStack) {
	ActiveStack->refTopOff = (long)RefTopOffReg;
	ActiveStack->dataTopOff = (long)DataTopOffReg;
      } else {
	DEBUG_MT(fprintf(output,"t@%d: doGC: No ActiveStack.\n", (int)ThreadId);
		 fflush(output);
		 );
      }

      mutex_lock(&tsd_lock);
      if (CheckIfICanGC()) {
	/* I'm the first thread that discovers the need to GC */
	/* Get Ready to GC now:
	 * 1) Only one threads will get in HERE for each GC.
	 * 2) Setup variables & locks so that only this thread will do the GC.
	 *    Also force all threads to run out of heap at next allocation, so
	 *    that they will not use the rest of their slice.
	 * 4) Then wait for the last of the other threads to signal start_gc.
	 * 5) Try IOAGc'ing at most three times, freeing room for slices
	 *    for all threads.
	 * 6) Allocate object and slice for this thread.
	 * 7) signal gc_done to all other threads.
	 */

	/* (2) */
	TSDFlags |= Flag_DoingGC;
	DEBUG_MT(fprintf(output,"t@%d: Set Flag_DoingGC\n", (int)ThreadId);
		 fflush(output);
		 );
	gIOATop = gIOALimit; /* No room for any more slices! */
	for (i = 0; i < TSDlistlen; i++) {
	  if (TSDlist[i]) {
	    if (gIOA <= TSDlist[i]->_IOALimit){
	      /* Make thread TSDlist[i]->_thread_id run out of mem */
	      TSDlist[i]->_IOALimit = gIOA; 
	    } else {
	      DEBUG_MT(fprintf(output,
			       "t@%d: not triggering GC for t@%d (no slice yet).\n", 
			       (int)ThreadId,
			       (int)TSDlist[i]->_thread_id);
		       fflush(output);
		       );
	    }
	  }
	}
	mutex_unlock(&tsd_lock);

	/* (4) */
	/* Scan TSD, counting blocked processes into numReadyToGC.
	 * Recount until NumTSD threads are blocked.
	 */

	while (1) {
	  numReadyToGC = 0;
	  mutex_lock(&tsd_lock);
	  for (i = 0; i < TSDlistlen; i++) {
	    if (TSDlist[i]) {
	      if (TSDlist[i]->_TSDFlags &
		  (Flag_Semablocked | Flag_GCblocked | Flag_DoingGC)) {
		numReadyToGC++;
		DEBUG_MT({
		  fprintf(output,
			  "t@%d: Detected t@%d ready for GC (%d ready, expecting %d)\n", 
			  (int)ThreadId,
			  TSDlist[i]->_thread_id,
			  (int)numReadyToGC,
			  (int)NumTSD
			  );
		  fflush(output);
		} );
	      } else {
		DEBUG_MT({
		  fprintf(output,
			  "t@%d: Detected t@%d NOT ready for GC (%d ready, expecting %d)\n", 
			  (int)ThreadId,
			  TSDlist[i]->_thread_id,
			  (int)numReadyToGC,
			  (int)NumTSD
			  );
		  fflush(output);
		});
	      }
	    }
	  }

	  if (numReadyToGC == NumTSD) {
	    mutex_unlock(&tsd_lock);
	    break;  /* all threads are blocked, go GC! */
	  } else {
	    mutex_unlock(&tsd_lock);
	    cond_wait(&cond_pause, &cond_pause_lock);
	  }
	}

	/* Now all other threads are sleeping */      
	/* (5) */
	DEBUG_MT(fprintf(output,"t@%d: Starting doGC.\n", (int)ThreadId);
		 fflush(output);
		 );
	ReqObjectSize = numbytes/4;
	mutex_lock(&tsd_lock); /* To allow CalculateSliceSize & TSDCheck */

	/* Try up to 3 IOAGcs to mature enough object to go into AOA */
	for (i=0; i<2; i++){
	  __asm__("stbar"); 
	  INFO_IOA(fprintf(output, "[%d]\n", i));
	  IOAGc();
	  reqsize = numbytes;
	  if (reqsize < IOASliceSize) reqsize = IOASliceSize;

	  if ((long*)((long)gIOATop + (reqsize + (NumTSD-1) * IOASliceSize)) <= gIOALimit) {
	    /* (6.0) */
	    IOATop = gIOATop; 
	    gIOATop = (long*)((long)gIOATop + reqsize); /* size of slice */
	    newObj = (struct Object *)IOATop;
	    IOATop = (long*)((long)IOATop + numbytes);
	    savedIOALimit = IOALimit = gIOATop;
	    break;
	  }

	  if (i==1){
	    /* Have now done two IOAGc's without freeing enough space.
	     * Make sure that all objects go to AOA in the next GC.
	     */
	    IOAtoAOAtreshold=IOAMinAge+1;
	    INFO_IOA(fprintf(output, "[%d]\n", i));
	    DEBUG_IOA(fprintf(output, "Forcing all objects in IOA to AOA\n"));
	    IOAGc();
	    reqsize = numbytes;
	    if (reqsize < IOASliceSize) reqsize = IOASliceSize;

	    if ((long*)((long)gIOATop + reqsize) <= gIOALimit) {
	      /* (6.1) */
	      IOATop = gIOATop; 
	      gIOATop = (long*)((long)gIOATop + reqsize); /* size of slice */
	      newObj = (struct Object *)IOATop;
	      IOATop = (long*)((long)IOATop + numbytes);
	      savedIOALimit = IOALimit = gIOATop;
	      break;
	    }

	    if ((long*)((long)gIOATop + numbytes) <= gIOALimit) {
	      /* (6.1) */
	      newObj = (struct Object *)gIOATop; 
	      gIOATop = (long*)((long)gIOATop + numbytes); /* size of object */
	      IOATop = savedIOALimit = IOALimit = gIOATop;
	      break;
	    }
	  
#if 0
	    /* Have now tried everything to get enough space in IOA */
	    /* Aber dann haben wir anderen metoden! */
	    /* (6.2) */
	    DEBUG_MT(fprintf(output,"t@%d: Allocated %d bytes in AOA, "
			     "as %d bytes would not fit in IOA\n", 
			     (int)ThreadId, (int)numbytes, (int)reqsize);
		     fflush(output);
		     );
	    newObj = AOAcalloc(numbytes);
	    savedIOALimit = IOALimit = IOATop = gIOATop;
#endif
	    break;
	  }
	}

	DEBUG_MT(Claim(newObj!=0, "doGC: newObj allocated"));

	DEBUG_MT(fprintf(output,"t@%d: GC completed.\n", (int)ThreadId);
		 fflush(output);
		 );
	/* (7) */
	for (i = 0; i < TSDlistlen; i++) {
	  if (TSDlist[i])
	    TSDlist[i]->_TSDFlags &= ~(Flag_GCblocked | Flag_DoingGC);
	}
	mutex_unlock(&tsd_lock);
	cond_broadcast(&cond_pause);
	mutex_unlock(&cond_pause_lock);
      } else {
	mutex_unlock(&tsd_lock);

	DEBUG_MT(fprintf(output,"t@%d: Flag and signal.\n", (int)ThreadId);
		 fflush(output);
		 );
	DEBUG_MT(fprintf(output,"t@%d: Wait for GC to complete.\n", (int)ThreadId);
		 fflush(output);
		 );
	TSDFlags |= Flag_GCblocked;
	cond_broadcast(&cond_pause);
	while (TSDFlags & Flag_GCblocked)
	  cond_wait(&cond_pause, &cond_pause_lock);
      
	DEBUG_MT(fprintf(output,"t@%d: Received GCdone.\n", (int)ThreadId);
		 fflush(output);
		 );
      
	
	reqsize = numbytes; /* IOASliceSize may have changed; recalc */
	if (reqsize < IOASliceSize) reqsize = IOASliceSize;
      
	if (gIOALimit <= (long*)((long)gIOATop + reqsize)) {
	  if (gIOALimit <= (long*)((long)gIOATop + numbytes)) {
#if 0
	    /* Not enough room in IOA. Allocate object in AOA, 
	       and return empty slice */
	    DEBUG_MT(fprintf(output,"t@%d: Allocated %d bytes in AOA, "
			     "as %d bytes would not fit in IOA\n", 
			     (int)ThreadId, (int)numbytes, (int)reqsize);
		     fflush(output);
		     );
	    newObj = AOAcalloc(numbytes);
	    IOATop = savedIOALimit = IOALimit = gIOATop;
#endif
	    mutex_unlock(&cond_pause_lock);
	    continue;
	  } else {
	    /* There is room for my object only, not a slice, as
	     * numbytes will fit into [gIOATop..gIOALimit[ 
	     */
	    newObj = AllocObjectAndSlice(numbytes, numbytes);	  
	  }
	} else {
	  /* There is room for my request, as
	 * max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ 
	 */
	  newObj = AllocObjectAndSlice(numbytes, reqsize);
	}
	DEBUG_MT(fprintf(output,"t@%d: Unlocking cond_pause_lock\n", (int)ThreadId);
		 fflush(output);
		 );
	mutex_unlock(&cond_pause_lock);
      }
    } else {
      /* No need to GC, as 
     * max(numbytes,IOASliceSize) will fit into [gIOATop..gIOALimit[ 
     */
      newObj = AllocObjectAndSlice(numbytes, reqsize);
      DEBUG_MT(fprintf(output,"t@%d: Got slice of at least %d\n", 
		       (int)ThreadId, (int)reqsize);
	       fflush(output);
	       );
      DEBUG_MT(fprintf(output,"t@%d: UNLock cond_pause_lock\n", 
		       (int)ThreadId);
	       fflush(output);
	       );
      mutex_unlock(&cond_pause_lock);
    }
  } while(!newObj); /* do-while */
  return newObj;
}

void DoGC() /* The one called directly from betaenv */
{
  doGC(0);
}


int numProcessors(int online)
{
  if (online){
    /* report #processors currently online */
    return sysconf(_SC_NPROCESSORS_ONLN);
  } else {
    /* report #processors configured */
    return sysconf(_SC_NPROCESSORS_CONF);
  }
}

extern void *AttTC(void *);

thread_t attToThread(struct Component *comp)
{ 
  TSD *tsd = create_TSD();
  tsd->_ActiveComponent = comp;
  if (thr_create(NULL                           /* stack base */,
		 0                              /* stack size */,
		 (void *(*)(void *))AttTC       /* func       */,
		 (void *)tsd                    /* arg        */,
		 THR_NEW_LWP|THR_DETACHED       /* flags      */,
		 &tsd->_thread_id               /* id         */)){
    fprintf(output, "Failed to create thread for component 0x%x\n", (int)comp);
    fflush(output);
    exit (1);
  }
  DEBUG_MT(fprintf(output, 
		   "[Created thread 0x%x for comp 0x%x]\n", 
		   (int)tsd->_thread_id, 
		   (int)comp);
	   fflush(output););
  return tsd->_thread_id;
}

int thisThreadInx(void)
{
  return TSDinx;
}

void BETA_MT_lock(void)
{
  DEBUG_MT(fprintf(output,"t@%d: Try BETA_MT_lock\n", (int)ThreadId);
	   fflush(output);
	   );
  __asm__("stbar"); 
  mutex_lock(&cond_pause_lock);
  DEBUG_MT(fprintf(output,"t@%d: Got BETA_MT_lock\n", (int)ThreadId);
	   fflush(output);
	   );
}
void BETA_MT_unlock(void)
{
  DEBUG_MT(fprintf(output,"t@%d: BETA_MT_unlock\n", (int)ThreadId);
	   fflush(output);
	   );
  __asm__("stbar"); 
  mutex_unlock(&cond_pause_lock); 
}


void BETA_MT_csuspend(void)
{
  DEBUG_MT(fprintf(output,"t@%d: BETA_MT_suspend\n", (int)ThreadId);
	   fflush(output);
	   );  
  DEBUG_MT(AssertLock(&cond_pause_lock));

  TSDFlags |= Flag_Semablocked; /* No need to lock; this is my own TSD */
  __asm__("stbar"); 
  cond_broadcast(&cond_pause);
  while (TSDFlags & Flag_Semablocked) {
    cond_wait(&cond_pause, &cond_pause_lock);
  }
  DEBUG_MT(fprintf(output,"t@%d: BETA_MT_suspend-continuing\n", (int)ThreadId);
	   fflush(output);
	   );
}
void BETA_MT_continue(int i)
{
  DEBUG_MT(fprintf(output,"t@%d: BETA_MT_continue\n", (int)ThreadId);
	   fflush(output);
	   );
  DEBUG_MT(AssertLock(&cond_pause_lock));

  __asm__("stbar"); 
  mutex_lock(&tsd_lock); /* Someone elses TSD; lock TSDlist first */
  if (TSDlist[i]) {
    TSDlist[i]->_TSDFlags &= ~Flag_Semablocked;
    __asm__("stbar"); 
    cond_broadcast(&cond_pause);
  } else {
    fprintf(output, "ERROR: continue on nonexisting thread!\n");
  }
  mutex_unlock(&tsd_lock);

}     


#ifdef RTDEBUG
void ReportMainStarted(void)
{
  DEBUG_MT(fprintf(output, 
		   "[MAIN thread 0x%x started]\n", 
		   (int)thr_self());
	   fflush(output));
}
#endif

static __inline__ int TryLock(unsigned long* l)
{ 
  register int v;
  __asm__ volatile ("ldstub\t[%1],%0" : "=r" (v) : "r" (l));
  return !v; 
}
static __inline__ void UnLock(unsigned long* l)
{ 
  __asm__ volatile ("stbar\n"
		    "stb\t%%g0,[%0]" : /* no outs */ : "r" (l));
}

struct S_PreemptionLevel PreemptionLevel;

void SetupVirtualTimer(unsigned usec);
void SetupRealTimeTimer(unsigned firstsec, unsigned firstusec, unsigned usecinterval);
GLOBAL(int AlarmOccured) = 0;
static int AlarmHandlerInitalized=0;

void AlarmHandler(int sig, siginfo_t *sip, void *uap)
{
  AlarmOccured++;
  
  if (TryLock(&PreemptionLevel.lock)){
    if (!PreemptionLevel.value) { 
      if (!PreemptionLevel.inGC) { /* We cannot reset IOALimit while GC'ing */
	IOALimit = 0;
	DEBUG_MT(fprintf(output, "AlarmOccured=0x%x\n", AlarmOccured));
      }
    }
    UnLock(&PreemptionLevel.lock);
  }
}

void SetupVirtualTimerHandler()
{
  struct sigaction act;

  if (!(AlarmHandlerInitalized & 1)) {
    PreemptionLevel.lock = 0;
    PreemptionLevel.value = 1;
    AlarmHandlerInitalized |= 1;
  }
  if (!(AlarmHandlerInitalized & 2)) {
    act.sa_handler = NULL;            /* Unused */
    act.sa_sigaction = &AlarmHandler; /* the handler */
    act.sa_flags = SA_SIGINFO;        /* Use sa_sigaction, not sa_handler */ 
    sigemptyset(&act.sa_mask);        /* Block no other signals in handler */
    
    if (sigaction(SIGVTALRM, &act, NULL)) {
      fprintf(output,"sigaction SIGVTALRM failed. Errno=%d (%s)\n", errno,strerror(errno));
      BetaExit(1);
    }
    AlarmHandlerInitalized |= 2;
  }
}

void SetupRealTimeTimerHandler()
{
  struct sigaction act;

  if (!(AlarmHandlerInitalized & 1)) {
    PreemptionLevel.lock = 0;
    PreemptionLevel.value = 1;
    AlarmHandlerInitalized |= 1;
  }
  
  if (!(AlarmHandlerInitalized & 4)) {
    act.sa_handler = NULL;            /* Unused */
    act.sa_sigaction = &AlarmHandler; /* the handler */
    act.sa_flags = SA_SIGINFO;        /* Use sa_sigaction, not sa_handler */ 
    sigemptyset(&act.sa_mask);        /* Block no other signals in handler */
    
    if (sigaction(SIGALRM, &act, NULL)) {
      fprintf(output,"sigaction SIGALRM failed. Errno=%d (%s)\n", errno,strerror(errno));
      BetaExit(1);
    }
    AlarmHandlerInitalized |= 4;
  }
}

void SetupVirtualTimer(unsigned usec)
{
  struct itimerval interval;
  if (!(AlarmHandlerInitalized & 2)) {
    fprintf(output,"SetupVirtualTimer called before SetupVirtualTimerHandler\n");
    BetaExit(1);
  }
  /* setup timer to trigger each usec microseconds */
  interval.it_value.tv_sec = 0;
  interval.it_value.tv_usec = usec;
  interval.it_interval.tv_sec = 0;
  interval.it_interval.tv_usec = usec;

  if (setitimer(ITIMER_VIRTUAL, &interval, NULL)) {
    fprintf(output,"setitimer ITIMER_VIRTUAL failed. Errno=%d (%s)\n", errno,strerror(errno));
    BetaExit(1);
  }  
}

void SetupRealTimeTimer(unsigned firstsec, 
			unsigned firstusec, 
			unsigned usecinterval)
{
  struct itimerval interval;

  if (!(AlarmHandlerInitalized & 4)) {
    fprintf(output,"SetupRealTimeTimer called before SetupRealTimeTimerHandler\n");
    BetaExit(1);
  }

  /* setup timer to trigger each usec microseconds, starting
   * firstsec:firstusec from now.
   */
  interval.it_value.tv_sec = firstsec;
  interval.it_value.tv_usec = firstusec;
  interval.it_interval.tv_sec = 0;
  interval.it_interval.tv_usec = usecinterval;

  if (setitimer(ITIMER_REAL, &interval, NULL)) {
    fprintf(output,"setitimer ITIMER_REAL failed. Errno=%d (%s)\n", errno,strerror(errno));
    BetaExit(1);
  }  
}

void* MT_malloc(int size) 
{ 
  void* p = memalign(8, (size));
  DEBUG_MT(fprintf(output,"[malloc at 0x%0x]\n", (int)p));
  memset(p, 0, (size));
  return p;
}

#endif /* MT */
