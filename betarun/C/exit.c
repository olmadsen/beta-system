/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * exit.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann,
 *    S|ren Brandt and S|ren Pingel Dalsgaard
 */
#include "beta.h"
#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

#ifdef UNIX
#include <fcntl.h>
#endif /* UNIX */

#ifdef RTDEBUG
#ifdef UNIX
#include <unistd.h>
#endif /* UNIX */

#ifdef MAC
#define PrintMacNumVars()\
  fprintf(output, "PpkVT:    %-8d  ", (int)NumPpkVT);\
  fprintf(output, "PpkCT:    %-8d  ", (int)NumPpkCT);\
  fprintf(output, "PpkSVT:   %-8d\n", (int)NumPpkSVT);\
  fprintf(output, "CopyPPP:  %-8d\n", (int)NumCopyPPP)
#else
#define PrintMacNumVars()
#endif /* MAC */

static void PrintNumVars(void) 
{ 
  fprintf(output, "\n");
  fprintf(output, "AlloI:    %-8d  ", (int)NumAlloI);
  fprintf(output, "AlloC:    %-8d  ", (int)NumAlloC);
  fprintf(output, "AlloDO:   %-8d\n", (int)NumAlloDO);
  fprintf(output, "AlloCOM:  %-8d  ", (int)NumAlloCOM);
  fprintf(output, "AlloRR:   %-8d  ", (int)NumAlloRR);
  fprintf(output, "AlloVR1:  %-8d\n", (int)NumAlloVR1);
  fprintf(output, "AlloVR2:  %-8d  ", (int)NumAlloVR2);
  fprintf(output, "AlloVR4:  %-8d  ", (int)NumAlloVR4);
  fprintf(output, "AlloVR8:  %-8d\n", (int)NumAlloVR8);
  fprintf(output, "AlloVRI:  %-8d  ", (int)NumAlloVRI);
  fprintf(output, "AlloVRC:  %-8d  ", (int)NumAlloVRC);
  fprintf(output, "ExtRR:    %-8d\n", (int)NumExtRR);
  fprintf(output, "ExtVR1:   %-8d  ", (int)NumExtVR1);
  fprintf(output, "ExtVR2:   %-8d  ", (int)NumExtVR2);
  fprintf(output, "ExtVR4:   %-8d\n", (int)NumExtVR4);
  fprintf(output, "ExtVR8:   %-8d  ", (int)NumExtVR8);
  fprintf(output, "ExtVRI:   %-8d  ", (int)NumExtVRI);
  fprintf(output, "ExtVRC:   %-8d\n", (int)NumExtVRC);
  fprintf(output, "CopyCT:   %-8d  ", (int)NumCopyCT);
  fprintf(output, "CopyRR:   %-8d  ", (int)NumCopyRR);
  fprintf(output, "CopySRR:  %-8d\n", (int)NumCopySRR);
  fprintf(output, "CopySVR1: %-8d  ", (int)NumCopySVR1);
  fprintf(output, "CopySVR2: %-8d  ", (int)NumCopySVR2);
  fprintf(output, "CopySVR4: %-8d\n", (int)NumCopySVR4);
  fprintf(output, "CopySVR8: %-8d  ", (int)NumCopySVR8);
  fprintf(output, "CopySVRI: %-8d  ", (int)NumCopySVRI);
  fprintf(output, "CopySVRC: %-8d\n", (int)NumCopySVRC);
  fprintf(output, "CopyT:    %-8d  ", (int)NumCopyT);
  fprintf(output, "CopyVR1:  %-8d  ", (int)NumCopyVR1);
  fprintf(output, "CopyVR2:  %-8d\n", (int)NumCopyVR2);
  fprintf(output, "CopyVR4:  %-8d  ", (int)NumCopyVR4);
  fprintf(output, "CopyVR8:  %-8d  ", (int)NumCopyVR8);
  fprintf(output, "CopyVRI:  %-8d\n", (int)NumCopyVRI);
  fprintf(output, "CopyVRC:  %-8d  ", (int)NumCopyVRC);
  fprintf(output, "CopyCPP:  %-8d  ", (int)NumCopyCPP);
  fprintf(output, "NewRR:    %-8d\n", (int)NumNewRR);
  fprintf(output, "NewVR1:   %-8d  ", (int)NumNewVR1);
  fprintf(output, "NewVR2:   %-8d  ", (int)NumNewVR2);
  fprintf(output, "NewVR4:   %-8d\n", (int)NumNewVR4);
  fprintf(output, "NewVR8:   %-8d  ", (int)NumNewVR8);
  fprintf(output, "NewVRI:   %-8d  ", (int)NumNewVRI);
  fprintf(output, "NewVRC:   %-8d\n", (int)NumNewVRC);
  fprintf(output, "AlloS:    %-8d  ", (int)NumAlloS);
  fprintf(output, "AlloSI:   %-8d  ", (int)NumAlloSI);
  fprintf(output, "AlloSC:   %-8d\n", (int)NumAlloSC);
  fprintf(output, "AlloSICB: %-8d  ", (int)NumAlloSICB);
  fprintf(output, "AlloSO:   %-8d  ", (int)NumAlloSO);
  fprintf(output, "ThisS:    %-8d\n", (int)NumThisS);
  fprintf(output, "ObjS:     %-8d  ", (int)NumObjS);
  fprintf(output, "leS:      %-8d  ", (int)NumleS);
  fprintf(output, "geS:      %-8d\n", (int)NumgeS);
  fprintf(output, "gtS:      %-8d  ", (int)NumgtS);
  fprintf(output, "ltS:      %-8d  ", (int)NumltS);
  fprintf(output, "eqS:      %-8d\n", (int)NumeqS);
  fprintf(output, "neS:      %-8d  ", (int)NumneS);
  fprintf(output, "Qua:      %-8d  ", (int)NumQua);
  fprintf(output, "Return:   %-8d\n", (int)NumReturn);
  fprintf(output, "CinitT:   %-8d  ", (int)NumCinitT);
  fprintf(output, "CpkVT:    %-8d  ", (int)NumCpkVT);
  fprintf(output, "CpkSVT:   %-8d\n", (int)NumCpkSVT);
  fprintf(output, "ChkRA:    %-8d  ", (int)NumChkRA);
  fprintf(output, "ExO:      %-8d  ", (int)NumExO);
  fprintf(output, "Att:      %-8d\n", (int)NumAtt);
  fprintf(output, "Susp:     %-8d  ", (int)NumSusp);
  fprintf(output, "MkTO:     %-8d  ", (int)NumMkTO);
  fprintf(output, "TermComp: %-8d\n", (int)NumTermComp);
  PrintMacNumVars();
  fprintf(output, "\n");
  fprintf(output, "AOAAlloc: %-8d\n", (int)NumAOAAlloc);
  fprintf(output, "\n");
  fprintf(output, "IOAGc:    %-8d  ", (int)NumIOAGc);
  fprintf(output, "AOAGc:    %-8d  ", (int)NumAOAGc);
  fprintf(output, "\n");  
  fflush(output);
  
  fprintf(output, "\n");  
}
#endif /* RTDEBUG */

#ifdef PROTO_STATISTICS
static int indirectprotocmp(const void *a1, const void *a2)
{
  TRACE_PROTOSTATISTICS({
    ProtoValue **pv1 = (ProtoValue**)a1;
    ProtoValue **pv2 = (ProtoValue**)a2;
    
    if ((*pv1)->count > (*pv2)->count) 
      return 1;
    if ((*pv1)->count < (*pv2)->count) 
      return -1;
  });
  return 0;
}
#endif

void BetaExit(long number)
{
  TRACE_PROTOSTATISTICS({
    long i;
    /* Print out how many times each prototype has been created */
    if (proto_list) {
      qsort(proto_list, proto_num_elems, sizeof(ProtoValue *),
	    (int (*)(const void *, const void *))indirectprotocmp);
      for (i=0; i<proto_num_elems; i++) {
	fprintf(output, "count: %-8ld ", proto_list[proto_num_elems-i-1]->count);
	PrintProto((ProtoType*)proto_list[proto_num_elems-i-1]->proto);
	fprintf(output, "\n");
      }
    }
  });

#if (defined(RTVALHALLA) && !defined(nti_bor))
  if (valhallaID) {
    /* Tell valhalla that we are terminating: */
    ValhallaOnProcessStop (0,0,0,0,0);
#ifdef UNIX
    if (number){
      DEBUG_CODE(fprintf(output, "debuggee(PID=%d): sleeping for 10 minuttes before exiting...\n", (int)getpid()));
      DEBUG_CODE(sleep(10*60));
      DEBUG_CODE(fprintf(output, "debuggee: 10 minuttes past - goodbye...\n"));
    }
#endif
  }
#endif /* RTVALHALLA */

  InfoS_End();
  
  INFO_AOA(GCInfo());

#ifdef RTDEBUG
#if defined(UNIX) || defined(NEWRUN) || defined(nti)
#ifdef MT
  if (!TSDReg){
    fprintf(output, "TSDReg is zero!\n"); 
    fflush(output);
  } else
#endif
    INFO_VARS(PrintNumVars());
#endif /* UNIX */
#endif /* RTDEBUG */

  INFO_HEAP_USAGE(PrintHeapUsage("at exit"));

#ifdef MT
  DEBUG_MT(fprintf(output, "[thread 0x%x terminated]\n", (int)ThreadId);
	   fflush(output);
	   );
  destroy_TSD();

  fflush(stdout);
  fflush(stderr);
  fflush(output);
  if (NumTSD==0) {
    /* NumTSD was decremented to 0 by destroy_TSD so last thread is exiting */
    fclose(output);
    exit(number);
  } else {
    thr_exit(NULL);
  }
#else /* NOT MT */

  TIME_IOA(fprintf(output,"[Accumulated ioatime = %dms]\n", (int)ioatime));
  TIME_IOA(fprintf(output,"[IOAs = %d]\n", (int)NumIOAGc));
  TIME_AOA(fprintf(output,"[Accumulated aoatime = %dms]\n", (int)aoatime));
  TIME_IOA(fprintf(output,"[AOAs = %d]\n", (int)NumAOAGc));
  INFO_AOA(fprintf(output,"NumAOAtoIOAInsert=%d\n", (int)NumAOAtoIOAInsert));

  fflush(stdout);
  fflush(stderr);
  fflush(output);

  fclose(output);

#ifdef UNIX
  {
    /* Make STDIN blocking, in case this was a systemEnv program */
    int fd = fileno(stdin);
    fcntl(fd, F_SETFL, 0); 
  }
#endif /* UNIX */  

#ifdef RTDEBUG
  /* Clean up: Free all known allocations.
   * This will make detection of errors during purify runs easier.
   */
  CBFAfree();
  IOAfree();
  AOAfree();
  AOAtoIOAfree();
  LabelNameTableFree();
  /* persistence? */
#endif /* RTDEBUG */

  exit(number);

#endif /* MT */
}

