/************************ Solution NOT using doAtt *******************/


void Att(Object *this, Component *comp, pc_t RA, long SPx)
{
  Object *compObj;
  StackObject *sObj=0;
  long address, arg0, arg1;
  long SPy,SPz;
  int isFirst,i;

  DEBUG_CODE(NumAtt++);

#if 0
  fprintf(output, "Att(this=0x%x, comp=0x%x, RA=0x%x, SPx=0x%x\n",
	  this, comp, (int)RA, SPx);
  fprintf(output, "Att: comp= 0x%x, CallerLSC=0x%x\n", 
	  (int)comp, 
	  (int)comp->CallerLSC);
#endif

  if ((long)comp->CallerLSC == -2) {
    /* CallerLCS is set to -2 in ExitObjects.c when the component terminates.
     * So we are attempting to attach a component, that is terminated.
     */
    long SPoff;
    /* adjust SPx to be SP of previous frame. */
    GetSPoff(SPoff, CodeEntry(GETPROTO(this), RA)); 
    SPx = ((long)SPx+SPoff);
    BetaError(CompTerminatedErr, this, (long *)SPx, RA); 
  }

  if (((long)comp->CallerLSC != 0) && ((long)comp->StackObj==0)) {
    /* comp has a resume address but no stack object.
     * This means that is is active.
     */
    long SPoff;
    /* adjust SPx to be SP of previous frame. */
    GetSPoff(SPoff, CodeEntry(GETPROTO(this), RA)); 
    SPx = ((long)SPx+SPoff);
    BetaError(RecursiveAttErr, this, (long *)SPx, RA);
  }

  SPy = (long)GetSP();
  if (ActiveComponent) {
    ActiveComponent->CallerLSC = RA;
#if 0
    fprintf(output, 
	    "Susp: comp=0x%x, CallerLSC set to 0x%x\n",
	    (int)ActiveComponent,
	    (int)RA);
#endif
    comppush(SPy); /* fprintf(output, "comppush SPy: 0x%x\n", SPy); */
    comppush(SPx); /* fprintf(output, "comppush SPx: 0x%x\n", SPx); */
  } else { 
    DEBUG_CODE(fprintf(output, "ActiveComponent == 0\n"); ILLEGAL);
  };
   
  isFirst = (comp->CallerLSC == 0);
  if (isFirst) { 
    compObj = (Object *)comp->Body;
    address = (long)GETPROTO(compObj)->TopMpart;
    arg0    = (long)comp;
    arg1    = (long)compObj;
  } else {
    sObj = comp->StackObj;
    SPz = SPy - sObj->BodySize; 
    address = (long)comp->CallerLSC;
    arg0    = (long)SPz;
    arg1    = (long)comp->CallerObj; 
  }
  
  AssignReference(&comp->CallerComp, ActiveComponent); /* may call AOAtoIOAinsert */
  AssignReference(&comp->CallerObj, this); /* may call AOAtoIOAinsert */
  comp->StackObj   = 0;
  comp->CallerLSC = (pc_t)-1; /* indicate that comp is attached */

#if 0
  fprintf(output, "Att: comp=0x%x, CallerLSC set to -1\n", comp);
#endif

  ActiveComponent = comp;

  if (sObj){
    /* Unpack sObj on stack. Must be done as the last thing to prevent
     * calls to other functions to destroy the new stack part.
     */
#if 0
    fprintf(output, "Att: unpacking stack object:\n");
    for (i=0; i < sObj->BodySize/4; i++){
      fprintf(output, 
	      "  *0x%x=0x%x\n", 
	      (long)((long *)SPz+i), 
	      *((long *)sObj->Body+i));
    }
#endif
    for (i=0; i < sObj->BodySize/4; i++){
      *((long *)SPz+i) = *((long *)sObj->Body+i);
    }

  }
  /* Execute comp.
   * 1st call starts at M111FOO; arg0=comp, arg1=ca.
   * Subsequent attachments: arg0=SPz, arg1=ca;
   */
#ifdef RTVALHALLA
  if (valhallaIsStepping)
    ValhallaOnProcessStop ((long*)address,0,0,0,RTS_ATTACH);
#endif
  if (isFirst){
    CallB((Object *)arg0, (Object *)arg1, address, 0);
  } else {
    CallBetaEntry(address, arg0, arg1);
  }

  TerminateActiveComponent();
}
