/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

static TerminateBasicComponent() { BetaExit(0); }

ParamThisComp(void, AttBC)
{
    register long *entrypoint;

#ifdef sparc
    register ref(CallBackFrame) callBackFrame asm("%l5");
    register ref(RegWin)	nextCompBlock asm("%l6");
    register long 		level 	      asm("%l7");
#endif

#ifdef hppa
    long			dummy;
    struct ComponentBlock       cb; /* don't move without changing SnakeAdditions.S */

    comp = cast(Component)getCallReg();
#endif

    GCable_Entry();

    /*
    printf("\nAttachBasicComponent: comp: 0x%08x\n", comp);
    printf("AttachBasicComponent: comp->CallerLSC: 0x%08x\n", comp->CallerLSC);
    fflush(stdout);
    */

    Ck(comp);

    /* Push the bottom component block. */
    /* Terminates the list of component blocks on the stack. */

#ifdef crts
    fprintf(output, "CRTS: AttBC: No ComponentBlock placed on stack (NYI)\n");
#endif

#ifdef sparc
    callBackFrame = cast(CallBackFrame) 0;
    nextCompBlock = cast(RegWin) 0;
    level = 0;

    lastCompBlock = cast(ComponentBlock) StackPointer;
    StackStart = (long)StackPointer;
    
    getret(comp->CallerLSC);
#endif
#ifdef hppa
    cb.callBackFrame = cast(CallBackFrame) 0;
    cb.next = cast(ComponentBlock) 0;
    cb.level = 0;
    cb.RefBlock = (void *)/*getRefSP()*/RefSP;
    lastCompBlock = (void *)/*getSPReg()*/RefSP;
    StackStart = (long)getSPReg();  /* Should be start of Ref Stack though */
    comp->CallerLSC = 1;
#endif

    BasicItem = cast(Item) &comp->Body;

    ActiveCallBackFrame = 0;
    ActiveComponent = comp;

#ifdef crts
 {
    extern void M1ENV();
    extern long T1ENV;
    /*extern long V3[2];*/
   /* fprintf(output, "AttBC: BasicItem: 0x%x\n", BasicItem);
    fprintf(output, "AttBC: M1ENV: 0x%x\n", M1ENV);
    fprintf(output, "AttBC: &T1ENV: 0x%x\n", &T1ENV);
    fprintf(output, "AttBC: Calling *((long *)&T1ENV-1): 0x%x\n", *((long *)&T1ENV-1));    

    /*fprintf(output, "AttBC: V3[0]: 0x%x\n", V3[0]);
    fprintf(output, "AttBC: V3[1]: 0x%x\n", V3[1]);
    fprintf(output, "AttBC: BasicItem->Proto: 0x%x\n", BasicItem->Proto);
    fprintf(output, "AttBC: &BasicItem->Proto: 0x%x\n", &BasicItem->Proto);
    fprintf(output, "AttBC: &V3[0]: 0x%x\n", &V3[0]);
    fprintf(output, "AttBC: Calling *((long *)BasicItem->Proto-1): 0x%x\n", *((long *)BasicItem->Proto-1));    
    fprintf(output, "AttBC: Calling *((long *)BasicItem->Proto-2): 0x%x\n", *((long *)BasicItem->Proto-2));
    fprintf(output, "AttBC: Calling *((long *)BasicItem->Proto-3): 0x%x\n", *((long *)BasicItem->Proto-3));
    
    fprintf(output, "AttBC: BasicItem->Proto->GCTabOff: 0x%x\n", BasicItem->Proto->GCTabOff);
    fprintf(output, "AttBC: BasicItem->Proto->OriginOff: 0x%x\n", BasicItem->Proto->OriginOff);
    fprintf(output, "AttBC: BasicItem->Proto->GenPart: 0x%x\n", BasicItem->Proto->GenPart);
    fprintf(output, "AttBC: BasicItem->Proto->Prefix: 0x%x\n", BasicItem->Proto->Prefix);
    fprintf(output, "AttBC: BasicItem->Proto->Size: 0x%x\n", BasicItem->Proto->Size);
    fprintf(output, "AttBC: BasicItem->Proto->FormOff: 0x%x\n", BasicItem->Proto->FormOff);
    fprintf(output, "AttBC: BasicItem->Proto->FormInx: 0x%x\n", BasicItem->Proto->FormInx);
    fprintf(output, "AttBC: BasicItem->Proto->AstRef: 0x%x\n", BasicItem->Proto->AstRef);
    fflush(output);*/
   }
#endif
    /*
    fprintf(output, "AttBC: CallBetaEntry(0x%x, 0x%x)\n", *((long *)BasicItem->Proto-1), &comp->Body);
    */

    /* ?? should set comp = 0 as done in Att.BasicComp.run */
    CallBetaEntry( *((long *)BasicItem->Proto-1), &comp->Body);

    /* TerminateBasicComponent: */
    BetaExit(0);

#ifdef sparc
    /* The following volapyk is to fool gcc into beliving that
     * callBackFrame, nextCompBlock and level is used in this function */

    asm(""::"r" (callBackFrame), "r" (nextCompBlock), "r" (level));
#endif
}

