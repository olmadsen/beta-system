#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "valhallaFIFOS.h"
#include "valhallaComm.h"
#include "valhallaFindComp.h"
#include "dot.h"

/* Opcodes for communication between valhalla and debugged process.
 *
 * VOP_* constants are replicated in
 *
 *    ~debugger/processCommCodes.bet
 * 
 * A protocol description including parameters and return value is
 * found in processCommCodes.bet as well.
 */

#define VOP_SCANGROUPS          1 
#define VOP_KILL                2 
#define VOP_GETDATAMEM          3 
#define VOP_GETINSTRUCTIONMEM   4 
#define VOP_SETDATAMEM          5 
#define VOP_GETDATAWORDS        6 
#define VOP_CONTINUE            7
#define VOP_DOTINSERT           9
#define VOP_GETPROTOINFO       10
#define VOP_DOTDELETE          11
#define VOP_SCANSTACK          12
#define VOP_OBJADRCANONIFY     13

#define VOP_STOPPED            50

/* DOTgarbageOnDelete
 * ==================
 * 
 * Dummy function used as parameter to DOT operations demanding a callback
 * function. Deleted indices are not saved explicitly since DOT is scanned
 * each time the process stops to keep valhalla up to date with its part
 * of the DOT contents. */

static void DOTgarbageOnDelete (index)
     int index;
{ ;
}


#ifdef RTDEBUG
void printOpCode (int opcode)
{
  switch (opcode) {
  case VOP_SCANGROUPS:  
    fprintf (output,"VOP_SCANGROUPS"); break;
  case VOP_KILL:  
    fprintf (output,"VOP_KILL"); break;
  case VOP_GETDATAMEM: 
    fprintf (output,"VOP_GETDATAMEM"); break;
  case VOP_GETINSTRUCTIONMEM: 
    fprintf (output,"VOP_GETINSTRUCTIONMEM"); break;
  case VOP_SETDATAMEM: 
    fprintf (output,"VOP_SETDATAMEM"); break;
  case VOP_GETDATAWORDS:  
    fprintf (output,"VOP_GETDATAWORDS"); break;
  case VOP_CONTINUE:  
    fprintf (output,"VOP_CONTINUE"); break;
  case VOP_DOTINSERT: 
    fprintf (output,"VOP_DOTINSERT"); break;
  case VOP_GETPROTOINFO: 
    fprintf (output,"VOP_GETPROTOINFO"); break;
  case VOP_DOTDELETE:
    fprintf (output,"VOP_DOTDELETE"); break;
  case VOP_OBJADRCANONIFY:
    fprintf (output,"VOP_OBJADRCANONIFY"); break;
  case VOP_SCANSTACK:
    fprintf (output,"VOP_SCANSTACK"); break;
  default:
    fprintf (output,"UNKNOWN OPCODE"); break;
  }
}
#endif

int valhallaCommunicate (int curPC);

/* FIFOS FOR VALHALLA COMMUNICATION
 * ================================ */

static FILE *fifoFrom, *fifoTo;

extern char *Argv (int);

void InstallHandler (int sig)
{
#ifndef sun4s
#ifdef UNIX
     signal (sig, BetaSignalHandler);
#endif
#else /* sun4s */
  { struct sigaction sa;
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigemptyset(&sa.sa_mask); 
    sa.sa_handler = BetaSignalHandler;
    sigaction(sig,&sa,0);
  }
#endif /* sun4s */
}

/* VALHALLAINIT
 * ============
 * 
 * Called when connection to valhalla should be setup. If valhalla is already
 * running, valhallaID is expected to contain the PID of the valhalla process 
 * is textual form. */

void valhallaInit ()
{ char tmp[20];
  int valhallaPID, pid;
  
  if (valhallaID) {

    /* Valhalla is already running. */
    valhallaPID = atoi (valhallaID);
    openFIFOS (valhallaPID,&fifoFrom,&fifoTo);

  } else {
    
    /* Valhalla is not running. */
    
    pid = getpid (); 
    createFIFOS (pid); 
    valhallaPID = vfork ();
    
    if (valhallaPID) {

      if (valhallaPID!=-1) {
	sprintf (tmp,"%d",valhallaPID); valhallaID = strdup (tmp);
	openFIFOS (pid,&fifoFrom,&fifoTo);
      } else
	fprintf (output, "Could not fork\n");

    } else {
      char valhallaname[200];
      char* betalib;

      betalib = getenv ("BETALIB");
      if (!betalib) {
	betalib="/usr/local/lib/beta";
	DEBUG_VALHALLA(fprintf(output,"BETALIB not found\n"));
      }
      sprintf (valhallaname,"%s/%s",betalib,"bin/valhalla2.0");
      sprintf (tmp,"%d",pid);
      
      execl (valhallaname,valhallaname,"-PID",tmp,"-EXECNAME",Argv(1),(char *) 0);
      fprintf (output, "Could not exec\n");
      exit (0);
      
    }
  }

  /* Make BetaSignalHandler handle the SIGINT signal.
   * Since SIGINT is not handled specially by the runtime system,
   * it will be sent to DisplayBetaStack, and from there to
   * valhallaOnProcessStop that will recognize it as a breakpoint hit. */
  
  InstallHandler(SIGINT);

  /* Initialize DOT */

  DOTinit ();

  /* Do initial communication with valhalla. ValhallaCommunicate returns
   * what to do next. */

  { int todo;
    switch (todo=valhallaCommunicate (0)) {
    case CONTINUE: break;
    case TERMINATE: exit (99);
    default:
      fprintf (output, "Unexpected return from valhallaCommunicate: %d \n",
	       todo);
      exit (99);
    }
  }
    

} /* End ValhallaInit */



/* FIFO OPERATIONS
 * =============== */

int fifoBinGetBytes (FILE *f, char* buf, int bytes)
{
  return fread (buf,1,bytes,f);
}

int fifoBinPutBytes (FILE *f, char* buf, int bytes)
{
  return fwrite(buf,1,bytes,f);
}

int fifoBinGetInt (FILE *f)
{ int val;
  if (fifoBinGetBytes (f, (char *)&val, sizeof(val)) != sizeof(val))
    fprintf (output, "WARNING -- fifoBinGetInt failed\n");
  return val;
}

void fifoBinPutInt (FILE *f, int val)
{ 
  if (fifoBinPutBytes (f, (char *)&val, sizeof(val)) != sizeof(val))
    fprintf (output, "WARNING -- fifoBinPutInt failed\n");
}

int fifoGetText (FILE *f, char* buf, int buflen)
{ int len;
  len = fifoBinGetInt (f);
  if (len < buflen) {
    return fifoBinGetBytes (f,buf,len+1);
  } else {
    return -1;
  }
}

void fifoPutText (FILE *f, char* txt)
{ int len = strlen (txt);
  fifoBinPutInt (f,len);
  fifoBinPutBytes (f,txt,len+1);
}




/* int valhallaCommunicate (int curPC)
 * ==========================
 *
 * Serves requests from valhalla regarding the state of this process.
 * curPC is needed to serve VOP_SCANSTACK requests.
 *
 * Possible return values:
 *    0: CONTINUE.
 *    1: TERMINATE. */

void forEachStackEntry (int returnAdr, int returnObj)
/* Used by VOP_SCANSTACK */
{
  fifoBinPutInt (fifoFrom, returnAdr);
  fifoBinPutInt (fifoFrom, returnObj);
}

extern void Return ();
static inline int findMentry (struct ProtoType *proto)
     /* 
      * Used to locate the Mentry point corresponding to a T entry. This is
      * done by scanning backwards in the INNER table of the prototype until
      * the address of Return is seen. The previous address seen is then the 
      * Mentry.
      *
      * However, if a prototype does not have an M entry point of its own
      * (no dopart), this method may return the Mentry point of one of its
      * prefixes. To ensure that this does not happen, the INNER table of
      * the immediate prefix prototype is scanned to ensure that the Mentry
      * found is not in that table too. If it is anyway, the current prototype 
      * has no Mentry of its own, and an Mentry of 0 is used. */
{ long tmp,Mentry=0;
  long* INNERtab = ((long *) proto)-1;
  struct ProtoType *prefix;
  
  while (TRUE) {
    tmp = *(INNERtab--);
    if (tmp==(long)Return) break;
    Mentry=tmp;
  }
  if (!Mentry) return 0; /* Empty INNER table. */
  
  /* Now check that the Mentry found cannot be found in the
   * prefix INNER table. */
  
  prefix = proto->Prefix;
  
  if ((prefix) && (prefix!=proto)) {
    INNERtab = ((long *) prefix)-1;
    while (TRUE) {
      tmp = *(INNERtab--);
      if (tmp==(long)Return) break;
      if (tmp==Mentry) return 0;
    }
  }
  
  return Mentry;
}

int valhallaCommunicate (int curPC)
{ int opcode;

  while (TRUE) {
    opcode = fifoBinGetInt (fifoTo);
    
    DEBUG_VALHALLA(fprintf (output, "valhallaCommunicate: opcode is "));
    DEBUG_VALHALLA(printOpCode(opcode); fprintf (output,"\n"));

    switch (opcode) {

    case VOP_SCANGROUPS:
      
      { group_header *current = 0;

	fifoBinPutInt (fifoFrom,opcode);
	while ((current = NextGroup (current))) {
	  fifoPutText (fifoFrom,NameOfGroup(current));         /* groupName */
	  fifoBinPutInt (fifoFrom, (int) current->self);       /* dataStart */ 
	  fifoBinPutInt (fifoFrom, (int) current->next);       /* dataEnd   */
	  fifoBinPutInt (fifoFrom, (int) current->code_start); /* codeStart */
	  fifoBinPutInt (fifoFrom, (int) current->code_end);   /* codeEnd   */
	}
	fifoPutText (fifoFrom,"");
	fflush (fifoFrom);
      }
      break;

    case VOP_KILL:

      fclose (fifoFrom); fclose (fifoTo);
      return TERMINATE;

    case VOP_CONTINUE:

      fifoBinPutInt (fifoFrom, opcode);
      fflush (fifoFrom);
      return CONTINUE;
      
    case VOP_GETDATAMEM:
    case VOP_GETINSTRUCTIONMEM:
      { 
	int address = fifoBinGetInt (fifoTo);
	int bytelen = fifoBinGetInt (fifoTo);
	DEBUG_VALHALLA(fprintf (output, "VOP_GET*MEM: %d bytes from address 0x%x\n",bytelen, address));
	   
	fifoBinPutInt (fifoFrom, opcode);
	if (fifoBinPutBytes (fifoFrom, (char *) address, bytelen) != bytelen)
	  fprintf (output, "VOP_GETDATAMEM: fifoBinPutBytes failed\n");
	fflush (fifoFrom);
      }
      break;

    case VOP_SETDATAMEM:
      {
	int address = fifoBinGetInt (fifoTo);
	int bytelen = fifoBinGetInt (fifoTo);
	if (fifoBinGetBytes (fifoTo, (char *) address, bytelen) != bytelen)
	  fprintf (output, "VOP_SETDATAMEM: fifoBinGetBytes failed\n");
	fifoBinPutInt (fifoFrom, opcode);
	fflush (fifoFrom);
      }
      break;

    case VOP_GETDATAWORDS:
      { 
	int address;
	
	fifoBinPutInt (fifoFrom, opcode);
	while ((address = fifoBinGetInt (fifoTo)))
	  fifoBinPutInt (fifoFrom, (* (int *) address));
	fflush (fifoFrom);
      }
      break;

    case VOP_OBJADRCANONIFY:
      { int address;
	struct Object *obj = (struct Object *) fifoBinGetInt (fifoTo);

	DEBUG_VALHALLA(fprintf(output,"Got object %d\n",(int) obj));
	
	if (obj) {
	  address = (int) obj;
	  if (obj->Proto != ComponentPTValue) {
	    DEBUG_VALHALLA(fprintf(output,"Not ComponentPTValue\n"));
	    if (obj->GCAttr == -6) {
	      struct Component *comp = (struct Component *) (address - 24);
	      DEBUG_VALHALLA(fprintf(output,"GCAttr was -6\n"));
	      if (comp->Proto == ComponentPTValue)
		address = address - 24;
	    }
	  }
	} else {
	  address=0;
	}
	fifoBinPutInt (fifoFrom, opcode);
	fifoBinPutInt (fifoFrom, address);
	fflush (fifoFrom);
      }
      break;

    case VOP_DOTINSERT:
      { int address, index;

	address = fifoBinGetInt (fifoTo);
	index = DOThandleInsert (address, DOTgarbageOnDelete, FALSE);

	fifoBinPutInt (fifoFrom, opcode);
	fifoBinPutInt (fifoFrom, index);
	fifoBinPutInt (fifoFrom, ObjectSize((ref(Object)) address));
	fflush (fifoFrom);
      }
      break;

    case VOP_DOTDELETE:
      {
	int handle = fifoBinGetInt (fifoTo);
	DOThandleDelete (handle);
	fifoBinPutInt (fifoFrom, opcode);
	fflush (fifoFrom);
      }
      break;

    case VOP_GETPROTOINFO:
      {
	struct group_header* header; int tableSize;
	long** protoTable; int i;

	header = (struct group_header*) fifoBinGetInt (fifoTo);
	protoTable = (long **) header->protoTable;
	
	tableSize= (int) protoTable[0];

	for (i=1; i<=tableSize; i++) {
	  /* M entry point: */
	  fifoBinPutInt (fifoFrom,
			 findMentry ((struct ProtoType *) protoTable[i]));
	  
	  fifoBinPutInt (fifoFrom,protoTable[i][1]); /* G entry point. */
	  fifoBinPutInt (fifoFrom,protoTable[i][4]); /* (formIndex,AstIndex) */
	};
	fifoBinPutInt (fifoFrom, opcode);
	
	fflush (fifoFrom);
      }
      break;

    case VOP_SCANSTACK:
      { struct ComponentStack cs;

	cs.comp = (struct Component *) fifoBinGetInt (fifoTo);

	DEBUG_VALHALLA(fprintf (output,"Received component: %d, pt = %d\n",(int)cs.comp, (int) cs.comp->Proto));

	findComponentStack (&cs,curPC);

	DEBUG_VALHALLA(fprintf (output,"FindComponentStack done. stacktype = %d. \n",cs.stacktype));
	  
	fifoBinPutInt (fifoFrom,cs.stacktype);
	
	DEBUG_VALHALLA(fprintf (output,"Scanning ComponentStack.\n"));
	
	scanComponentStack (&cs,forEachStackEntry);
	
	DEBUG_VALHALLA(fprintf (output,"ScanComponentStack done.\n"));
	
	fifoBinPutInt (fifoFrom,-1);
	fifoBinPutInt (fifoFrom, opcode);
	fflush (fifoFrom);
      }
      break;
      
    default:
      
      fprintf (output, "Unexpected valhalla opcode: %d\n", opcode);
      break;
      
    }

    DEBUG_VALHALLA(fprintf (output, "valhallaCommunicate: opcode "));
    DEBUG_VALHALLA(printOpCode(opcode); fprintf (output," done\n"));

  }
}


/* forEachAlive
 * ============
 *
 * Callback function used by ValhallaOnProcessStop during DOTscan. */

void forEachAlive (int handle, int address, DOTonDelete onDelete)
{
  DEBUG_VALHALLA(fprintf (output,"forEachAlive: handle=%d, address=%d \n", handle, address));
  if (onDelete==DOTgarbageOnDelete) {
    fifoBinPutInt (fifoFrom,handle);
    fifoBinPutInt (fifoFrom,address);
  }
}



/* 
 * int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
 *                            long sig, long errorNumber)
 * ====================================================================
 *
 * Calls back to valhalla to inform that this process has stopped and
 * is ready to serve requests. */

static int invops = 0; /* TRUE iff ValhallaOnProcessStop is active. Used to check
			* for reentrance of ValhallaOnProcessStop. This could happen
			* in case of bus-errors or the like during communication with
			* valhalla . */


int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
			   long sig, long errorNumber)
{ char *txt; int res;

  if (invops) {
    fprintf (output,"FATAL: ValhallaOnProcessStop re-entered\n");
    exit (99);
  } else
    invops=TRUE;

  fifoBinPutInt (fifoFrom, VOP_STOPPED);
  fifoBinPutInt (fifoFrom, (int) PC);

  if (PC==0) { /* Process about to stop. */
    fflush (fifoFrom);
    invops=FALSE;
    return TERMINATE;
  };

  fifoBinPutInt (fifoFrom, (int) curObj);
  fifoBinPutInt (fifoFrom, (int) ActiveComponent);
  
  fifoBinPutInt (fifoFrom, (int) SP);

  fifoBinPutInt (fifoFrom, sig);
  switch (sig) {
  case SIGILL:  txt = "SIGILL"; break;
  case SIGFPE:  txt = "SIGFPE"; break;
  case SIGBUS:  txt = "SIGBUS"; break;
  case SIGSEGV: txt = "SIGSEGV"; break;
  case SIGINT:  txt = "SIGINT"; break;
  case SIGQUIT: txt = "SIGQUIT"; break;
#ifndef linux
  case SIGEMT:  txt = "SIGEMT"; break;
#endif
  default: txt = "UNKNOWN"; break;
  }
  fifoPutText (fifoFrom, txt);

  fifoBinPutInt (fifoFrom, errorNumber);
  if (errorNumber) {
    txt = ErrorMessage (errorNumber);
    fifoPutText (fifoFrom, txt);
  }

  /* Locate objects known by valhalla that have become garbage: */
  DOThandlePerformCompaction (DOTgarbageOnDelete);
    
  /* Scan and send info on all alive objects known by valhalla: */
  DOTscan (forEachAlive);
  fifoBinPutInt (fifoFrom,-1);

  fflush (fifoFrom);

  if (fifoBinGetInt (fifoTo) != VOP_STOPPED)
    fprintf (output, "Warning! Wrong answer from Valhalla on VOP_STOPPED\n"); 

  res=valhallaCommunicate ((int) PC);
  invops=FALSE;

  /* If we came here through BetaSignalHandler, signals have been redirected to
   * ExitHandler. Reinstall BetaSignalHandler: */

  InstallHandler(SIGFPE);
  InstallHandler(SIGILL);
  InstallHandler(SIGBUS);
  InstallHandler(SIGSEGV);
  InstallHandler(SIGEMT);
  InstallHandler(SIGINT);

  return res;
}

int connected_to_valhalla ()
{
  return (valhallaID!=0);
}
