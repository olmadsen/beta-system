        .section ".text.startup"

        .global _start
        .balign 0x20
_start:
el2_vector_table:
        b el2_start
        b el2_undefined_instruction_vector
        b el2_software_interrupt_vector
        b el2_prefetch_abort_vector
        b el2_data_abort_vector
        b el2_hyp_trap_vector
        b el2_interrupt_vector
        b el2_fast_interrupt_vector

        .balign 0x20
el1_vector_table:
        nop
        b el1_undefined_instruction_vector
        b el1_software_interrupt_vector
        b el1_prefetch_abort_vector
        b el1_data_abort_vector
        nop
        b el1_interrupt_vector
        b el1_fast_interrupt_vector


el2_start:
        // Read core number - only 0 is allowed here,
        // and other cores should never pass by here
        mrc p15, 0, r3, c0, c0, 5
        ands r3, r3, #3
        beq 0f
        // Sanity check: if the core number is NOT 0
        // we will sleep forever
sleep:  wfe
        b sleep

0:      bl init_core
        
        mov r0, r2     // First argument is the device tree
        bl _cstartup   // Should never return!
unexpected_return:
        bl print_core
	ldr r0, =unexpected_return_txt
        bl putstr
        b sleep        // Sleep forever
        



init_core:
        // Initialize core.
        // The core number is in r3. We cannot clobber r1-r2

        // Drop from HYP (EL2) to SVC (EL1) mode
        mov r4, lr
        bl hypervisor_dropout
        mov lr, r4

        // Initialize stack pointer
        // Each core gets a 1kB stack from the range 0x03fff000 - 0x04000000
        ldr sp, =0x04000000
        lsl r0, r3, #10
        sub sp, sp, r0

        // Save r1-r2 as we are not allowed to clobber these registers
        push {r1, r2, lr}

        // Initialize EL1 vectors
        ldr r1, =el1_vector_table
        mcr p15, 0, r1, c12, c0, 0 // VBAR

        // Initialize memory - caches and MMU
        bl init_memory
 
        // TODO:
        // Enable NEON and VFP coprocessors
        
        pop {r1, r2, lr}
        
        bx lr

        



hypervisor_dropout:
        // Drop from HYP to SVC mode
        // This function clobbers: {r0}

        ldr r0, =el2_vector_table
        mcr p15, 4, r0, c12, c0, 0 // Initialize HVBAR.
        mov r0, #0x73              // Grant access to all controls from EL1
        mcr p15, 4, r0, c1, c0, 1  // Write HACTLR
        mrs r0, cpsr
        bic r0, r0, #0x1F
        orr r0, r0, #0x13
        msr spsr_cxsf, r0
        add r0, pc, #12
        msr elr_hyp, r0
        mov r0, lr
        isb
        eret
        mov lr, r0
        bx lr

        



init_memory:
        // Initialize the memory system - set up caches and MMU
        // Core number is in r3

	// Initialize TTBCR.
	mov r0, #0 		  // Use short descriptor.
	mcr p15, 0, r0, c2, c0, 2 // Base address is 16KB aligned.
				  // Perform translation table walk for TTBR0.

	// Initialize DACR.
	ldr r1, =0x55555555 	  // Set all domains as clients.
	mcr p15, 0, r1, c3, c0, 0 // Accesses are checked against the
				  // permission bits in the translation tables.

	// Initialize SCTLR.AFE.
	mrc p15, 0, r1, c1, c0, 0 // Read SCTLR.
	bic r1, r1, #(0x1 <<29)   // Set AFE to 0 and disable Access Flag.
	mcr p15, 0, r1, c1, c0, 0 // Write SCTLR.
		
	// Initialize TTBR0.
	ldr r0, =ttb0_base	  // ttb0_base must be a 16KB-aligned address.
	mov r1, #0x2b  		  // The translation table walk is normal, inner
	orr r1, r0, r1 		  // and outer cacheable, WB WA, and inner
	mcr p15, 0, r1, c2, c0, 0 // shareable.

        // Core 0 will set up a translation table, which will be shared among all.
        cmp r3, #0
        bne 3f
        
	// Set up translation table entries in memory
	ldr r4, =0x00100000       // Increase 1MB address each time.

        // Normal memory: 0x00000000-0x3effffff
	ldr r2, =0x00015c06       // Set up translation table descriptor with
	                          // Secure, global, full accessibility,
	                          // executable.
	                          // Domain 0, Shareable, Normal cacheable memory
	ldr r3, =1008             // executes the loop 1008 times to set up
	                          // descriptors to cover up to 0x3effffff.
0:	str r2, [r0], #4          // Build a page table section entry.
	add r2, r2, r4            // Update address part for next descriptor.
	subs r3, #1
	bne 0b

        // Memory-mapped peripherals: 0x3f000000-0x400fffff
        ldr r2, =0x3f010c02       // Set up translation table descriptors with
                                  // secure, global, full accessibility,
                                  // Domain=0 Shareable Device-nGnRnE Memory.
        ldr r3, =17               // Executes loop 17 times to cover descriptors
                                  // for 0x3f000000-0x400fffff
1:      str r2, [r0], #4          // Build a translation table section entry.
        add r2, r2, r4            // Update address part for next descriptor.
        subs r3, #1
        bne 1b

        // Invalid memory locations: 0x4010000-0xffffffff
        ldr r2, =0x40100000       // Invalid address
        ldr r3, =3071             // Executes loop 3071 times to cover the
                                  // remaining address space up to 4GB.
2:      str r2, [r0], #4          // Build a translation table section entry.
        add r2, r2, r4            // Update address part for next descriptor.
        subs r3, #1
        bne 2b


        // SMP is implemented in the CPUECTLR register.
3:      mrrc p15, 1, r0, r1, c15  // Read CPUECTLR.
	orr r0, r0, #(0x1 << 6)   // Set SMPEN.
	mcrr p15, 1, r0, r1, c15  // Write CPUECTLR.
	
        // Enable caches and the MMU.
	mrc p15, 0, r1, c1, c0, 0 // Read SCTLR.
	orr r1, r1, #(0x1 << 2)   // The C bit (data cache).
	orr r1, r1, #(0x1 << 11)  // The Z bit (branch prediction).
	orr r1, r1, #(0x1 << 12)  // The I bit (instruction cache).
	orr r1, r1, #0x1          // The M bit (MMU).
	mcr p15, 0, r1, c1, c0, 0 // Write SCTLR.
	dsb
	isb

        bx lr
        



        
        // *******
        //
        //    EXCEPTION HANDLERS (WILL PRINT ERROR MESSAGES)
        // 
        // *******

                      
        // For the time being, we keep a HYP vector table
        // here just to catch any unexpected exceptions.
        // The goal is to avoid this table altogether and
        // catch all exceptions at EL1, so if anything is
        // ever found stuck here, it is an error!
        // Unfortunately, it is not possible to disable the
        // HVC instruction unless we disable or override
        // the armstub7.S code provided by the Raspberry Pi
        // bootloader. Hence, the hyp_trap_vector remains "alive".

el2_undefined_instruction_vector:
0:      wfe
        b 0b
el2_software_interrupt_vector:
0:      wfe
        b 0b
el2_prefetch_abort_vector:  
0:      wfe
        b 0b
el2_data_abort_vector:      
0:      wfe
        b 0b
el2_hyp_trap_vector:
        // Print error message
        mov sp, #0x100
        bl print_core
	ldr r0, =hyp_trap_txt
        bl putstr
        mrs r0, elr_hyp
        sub r0, r0, #4
        bl puthex
        mov r0, #'\n'
        bl putch
        mrc p15, 4, r0, c5, c2, 0
        bl puthex
        mov r0, #'\n'
        bl putch
        b sleep
el2_interrupt_vector:       
0:      wfe
        b 0b
el2_fast_interrupt_vector:  
0:      wfe
        b 0b
        
el1_undefined_instruction_vector:
	ldr r8, =undefined_instruction_txt
1:      mov r9, lr
        mov sp, #0x100
        bl print_core
        mov r0, r8
        bl putstr
        sub r0, r9, #4
        bl puthex
        mov r0, #'\n'
        bl putch
        b sleep

el1_software_interrupt_vector:
	ldr r8, =software_interrupt_txt
        b 1b

el1_prefetch_abort_vector:  
	ldr r8, =software_interrupt_txt
2:      mov sp, #0x100
        bl print_core
        mov r0, r8
        bl putstr
        b sleep

el1_data_abort_vector:
	ldr r8, =data_abort_txt
        b 2b

el1_interrupt_vector:
        ldr r8, =interrupt_txt
        b 2b

el1_fast_interrupt_vector:
        ldr r8, =fast_interrupt_txt
        b 2b

print_core:
        push {lr}
        ldr r0, =stopped_txt
        bl putstr
        mrc p15, 0, r0, c0, c0, 5
        ands r0, r0, #3
        add r0, #'0'
        bl putch
        mov r0, #']'
        bl putch
        mov r0, #' '
        bl putch
        pop {lr}
        bx lr





        // *******
        //
        //    START CORE 1-3
        // 
        // *******       

#define ARM_LOCAL_PERI_BASE  0x40000000
#define ARML_MBOX_SET03	     0x8c
#define ARML_MBOX_READ_CLR03 0xcc
        
        .global start_core
start_core:
        push {r4, r5, r6}
        // We must be on core 0 to allow this
        mrc p15, 0, r3, c0, c0, 5
        ands r3, r3, #3
        bne start_core_failed
        // The child core must be in the range 1..3
        cmp r2, #0
        beq start_core_failed
        ands r3, r2, #0xfffffffc
        bne start_core_failed
        // And the function pointer cannot be NULL
        cmp r0, #0
        beq start_core_failed

        ldr r6, =ARM_LOCAL_PERI_BASE
        // Offset to mailbox register
        // e.g. ARML_MBOX_SETx3 = ARML_MBOX_SET03 + c * 0x10)
	lsl r2, r2, #4
        
	add r4, r2, #ARML_MBOX_READ_CLR03 // r4: READ_CLRx3 offset
	add r5, r2, #ARML_MBOX_SET03      // r5: SETx3 offset

        ldr r2, [r6, r4] // READ mailbox 3
        cmp r2, #0
        bne start_core_failed // Already started

        ldr r2, =child_core_entry
        str r2, [r6, r5] // WRITE mailbox 3: address of child_core_entry
        dsb
        sev

0:      ldr r2, [r6, r4] // READ mailbox 3 - wait for clear
        cmp r2, #0
        wfene
        bne 0b

        sub r4, r5, #4   // r4: SETx2 offset
        str r1, [r6, r4] // WRITE mailbox 2: argument
        str r0, [r6, r5] // WRITE mailbox 3: address of function
        dsb
        sev

        mov r0, #0
1:      pop {r4, r5, r6}
        bx lr
start_core_failed:
        mov r0, #-1
        b 1b

child_core_entry:
        dsb
        sev              // Wake core 0
        mrc p15, 0, r3, c0, c0, 5
        and r3, r3, #3
	lsl r0, r3, #4
	add r0, r0, #ARML_MBOX_READ_CLR03 // r0: READ_CLRx3 offset

        ldr r1, =ARM_LOCAL_PERI_BASE

0:      ldr r6, [r1, r0] // READ mailbox 3: - address of function
        cmp r6, #0
        wfeeq
        beq 0b
        // Do not clear mailbox 3 - it indicates to core 0 that  core is started

        sub r0, r0, #4   // Go to mailbox 2
        ldr r7, [r1, r0] // READ mailbox 2: - argument of function
        str r7, [r1, r0] // CLEAR mailbox 2

        bl init_core

        // Start the function
        mov r0, r7           // First argument
        blx r6               // Should never return!
        b unexpected_return  // Print error message and sleep forever

	/* added by OLM */
	
.globl put32
put32:
	str r1,[r0]
	bx lr

.globl GET32
GET32:
	ldr r0,[r0]
	bx lr

	.globl raw_putc
	
	.globl putNL
putNL:
	push {r0,r1,r2,r3,lr}
	ldr r0,=#13
	bl putch
	pop {r0,r1,r2,r3,lr}
	push {r0,r1,r2,r3,lr}
	ldr r0,=#10
	bl putch
	pop {r0,r1,r2,r3,lr}
	bx lr
		
.globl cmpAndSwap
cmpAndSwap:	
	// r0 = adr of mem loc
	// r1 = old value
	// r2 = new value
	
	push {r0,r1,r2,r3,lr}
	bl puthex
	pop {r0,r1,r2,r3,lr}

	push {r0,r1,r2,r3,lr}	
	bl putNL
	pop {r0,r1,r2,r3,lr}
	
	ldr r3,[r0]

	push {r0,r1,r2,r3,lr}
	mov r0,r3
	bl puthex
	pop {r0,r1,r2,r3,lr}
	bl putNL
	
	//mcr P15, 0, r0, C7, C10, 5
	ldrex r4,[r0]

	/*push {r0,r1,r2,r3,lr}
	mov r0,r3
	bl puthex
	pop {r0,r1,r2,r3,lr}*/
	
	/*push {r0,r1,r2,r3,lr}
	ldr r0,=#98
	bl raw_putc
	pop {r0,r1,r2,r3,lr}*/
	
	cmpne r1,r4
	beq fail
	strexne r3,r2,[r0]
	cmpne r3,#1
	beq fail
	ldr r0, =#1
	bx lr
fail:
	ldr r0, =#0
	bx lr
	
	/* end added by OLM */
	
        // *******
        //
        //    MUTEX
        // 
        // *******
        
#define locked 1
#define unlocked 0

        // lock_mutex
        // Declare for use from C as extern void lock_mutex(int8_t *mutex);
        .global lock_mutex
lock_mutex:
	ldr r1, =locked
0:      ldrexb r2, [r0]
	cmp r2, r1            // Test if mutex is locked or unlocked
	beq 1f                // If locked - wait for it to be released
	strexb r2, r1, [r0]   // Not locked, attempt to lock it
	cmpne r2, #1          // Check if Store-Exclusive failed
	beq 0b                // Still not locked: retry from '0'
	dmb                   // Memory barrier before accessing protected resource
	bx lr
        
1:      dsb                   // Commit any outstanding memory writes before going to sleep
        wfe                   // Sleep while waiting for mutex to become unlocked
        b 0b                  // Retry lock


        // unlock_mutex
        // Declare for use from C as extern void unlock_mutex(int8_t *mutex)//
        .global unlock_mutex
unlock_mutex:	
        ldr r1, =unlocked
        dmb                   // Memory barrier before releasing protected resource
        strb r1, [r0]         // Unlock mutex
        dsb                   // Wait for the store to take effect before the notification
	sev                   // Wake/notify all sleeping cores
        bx lr






        

        
        .data

        .p2align 14
ttb0_base:
	.space 16 * 1024

        



        // *******
        //
        //    ERROR MESSAGES TO PRINT ON EXCEPTIONS
        // 
        // *******
        
stopped_txt:
        .asciz "[STOPPED CORE "
unexpected_return_txt:
        .asciz "The core's main function returned unexpectedly\n"
hyp_trap_txt:
        .asciz "Hypervisor trap at address: "
undefined_instruction_txt:
        .asciz "Undefined instruction at address: "
software_interrupt_txt:
        .asciz "SVC called at address: "
prefetch_abort_txt:
        .asciz "Prefetch abort\n"
data_abort_txt:
        .asciz "Data abort\n"
interrupt_txt:
        .asciz "Interrupt\n"
fast_interrupt_txt:     
        .asciz "Fast interrupt\n"
