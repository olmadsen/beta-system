#include "beta.h"

/* Not used currently !!!!!!!!!!!!!!!!!! */

#if 0



#if defined(LIN)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>

/* GLOBAL FUNCTIONS */
void initIndirTrapHandler (void);

/* LOCAL FUNCTIONS */
static void indirTrap(long sig, siginfo_t *info, ucontext_t *ucon);

/* LOCAL MACROS */
#define instructionOk(instruction) ((instruction & KnownMask) == (KnownMask))
#define KnownMask 0x80900000
#define sourceReg(instruction) (instruction & 0x0000001F)
/* Copied in liniarize.c, make sure to update if you change below */
#define MAPTOINDIRECT(id) ((id * -1) - 1)

/* LOCAL VARIABLES */
static long returnPC, returnSP, absAddr;
static indirRefsFollowed = 0;

/* sighandler.c */
extern void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon);

/* initIndirTrapHandler:
 */
void initIndirTrapHandler (void) { 
    struct sigaction sa;

    indirRefsFollowed = 0;
    
    /* Specify that we want full info about the signal, and that
     * the handled signal should not be blocked while being handled: */
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    
    /* No further signals should be blocked while handling the specified
     * signals. */
    sigemptyset(&sa.sa_mask); 
    
    /* Specify handler: */
    sa.sa_handler = indirTrap;
    
    sigaction (SIGILL,&sa,0);
}

/* indirTrap:
 */
static void indirTrap(long sig, siginfo_t *info, ucontext_t *ucon) {
    int instruction;
    long indirRef;
    long offset;
    
    
    if (info->si_trapno-0x80 == 17  /* solaris 2.3, 2.4, 2.5 */ || 
        info->si_trapno-0x100 == 17 /* solaris 2.5.1, 2.6? */
        ) {
        /* Ok, the signal was caused by a "tle 17" trap, meaning either
         * "reference is NONE" or dereference of an indirect reference */
        
        /* Fetch the 'tst %lm' instruction. */
        instruction = (* (long *) (ucon->uc_mcontext.gregs[REG_PC] - 4));
        
        if (instructionOk(instruction)) {
            /* PC to jump to when fetch has completed: */
            returnPC = ucon->uc_mcontext.gregs[REG_PC] - 4; 
            /* SP to restore when fetch has completed: */
            returnSP = ucon->uc_mcontext.gregs[REG_SP]; 
            
            /* flush register windows to stack and fetch value of register causing
             * the trap. */
            __asm__ volatile  ("ta 3");
            
            indirRef = ((int *) returnSP)[sourceReg(instruction) - 16];
            indirRefsFollowed++;
            
            if (isIndirRef(indirRef)) {
                
                /* Ok, so this is a genuine indirect reference, and
                 * not simply a NONE reference.
                 */

                /* Calculate absolute address by looking in the indirtable */
                
#if 0
                /* The following os correct, but not in use currently
                 * so infoTable does not exist...
                 */
                offset = l -> infoTable[MAPTOINDIRECT(indirRef)].byteOffset;
                absAddr = (long) (l -> liniarization + offset);
#endif
                
                /* Return to trap window. */
                __asm__ volatile ("restore; restore ! return to trap window");
                
                /* Now we are back in the register window where the trap occurred.
                 * Only global registers may be changed. Now reset correct sp. (UNIX 
                 * pushed some information on the stack). */
                __asm__ volatile ("sethi %hi(returnSP),%g1 ! reset sp to returnSP");
                __asm__ volatile ("ld [%g1+%lo(returnSP)],%sp");
                
                /* Allocate a new register window to avoid changing trap registers. */
                __asm__ volatile ("save %sp,-64,%sp ! save trap window");
                
                /* Tell compiler to assume nothing about register contents: */
                __asm__ volatile ("" : : : "i0", "i1", "i2", "i3", "i4", "i5", "fp", "i7",\
                                  "o0", "o1", "o2", "o3", "o4", "o5", "sp", "o7", \
                                  "l0", "l1", "l2", "l3", "l4", "l5", "l6", "l7");
                
                /* Get back to returnPC and continue from there. */
                __asm__ volatile ("sethi %hi(returnPC),%g1  ! Jump back to before trap");
                __asm__ volatile ("ld [%g1+%lo(returnPC)],%g1");
                __asm__ volatile ("restore");
                
                /* load the register containing the indirect reference with
                 * the absolute address.  
                 *
                 * sethi i1, %0
                 * ior i1, %0, i1
                 */
                
                __asm__ volatile ("sethi %hi(absAddr),%i2");
                __asm__ volatile ("ld [%i2+%lo(absAddr)],%i2");
                /* try again */
                __asm__ volatile ("jmp %g1; nop");
            }
        } 
    }
    
    /* If we get here, it was not a lazy reference. Call the usual 
     * BetaSignalHandler. */
    BetaSignalHandler (sig, info, ucon);
}

void printIndirStatistics(void) {
    printf("%20s: followed %lu\n", "indirTrapHandler", (long) indirRefsFollowed);
}
    
#endif /* LIN */
#endif /* 0 */
