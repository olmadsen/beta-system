.section ".text.startup"

.global _start
.global _get_stack_pointer
.global init_mmu_s
_start:
	//CPS 0x1F

	// Processors are in Secure SVC mode after reset. 
	MOV    R0, #0 
	MOV    R1, #0 
	MOV    R2, #0 
	MOV    R3, #0 
	MOV    R4, #0 
	MOV    R5, #0 
	MOV    R6, #0 
	MOV    R7, #0 
	MOV    R8, #0 
	MOV    R9, #0 
	MOV    R10, #0 
	MOV    R11, #0 
	MOV    R12, #0 
	MOV    R13, #0 
	MOV    R14, #0 
	
 	B LLL
 
	CPS    #0x11                  // Change to FIQ mode. 
	MOV    R8, #0 
	MOV    R9, #0 
	MOV    R10, #0 
	MOV    R11, #0 
	MOV    R12, #0
	MOV    R13, #0 
	MOV    R14, #0 
	
// if B LLL is placed here, the code fails, nothing happens	
	
	CPS    #0x12                  // Change to IRQ mode. 
	MOV    R13, #0 	
	MOV    R14, #0 
 
	CPS    #0x1F                  // Change to System mode.  
	MOV    R13, #0         // System and User modes reuse the same banking
	MOV    R14, #0                // of r13 and r14. 
 
	CPS    #0x17                  // Change to Abort mode. 
	MOV    R13, #0 
	MOV    R14, #0 
 
	CPS    #0x1B                  // Change to Undef mode. 
	MOV    R13, #0 
	MOV    R14, #0 
	
// if LLL is placed here, the code fails - nothing happens	
	CPS    #0x16                  // Change to Monitor mode. 
	MOV    R13, #0 
	MOV    R14, #0 
	
 LLL:	 
	MOV    R0, #0                 // Use MSR in Monitor Mode. 
	//MSR    SP_hyp, R0             // Initialize Hyp mode R13.
	// The above instruction is in the RAM boot doc,
	// but it makes no difference if it is executed or not!?
	
	//CPS	#0x13		// made by OLM: dont work
	
	//bl init_mmu
	//LDR R1, =secure_vector_table_base_address
	//MCR P15, 0, R1, C12, C0, 0 // Initialize VBAR (Secure).
	//LDR R1, =monitor_vector_table_base_address
	//MCR P15, 0, R1, C12, C0, 1 // Initialize MVBAR.

	LDR R1, =Vectors
	MCR P15, 4, R1, C12, C0, 0 // Initialize HVBAR.

	// Enable asynchronous aborts, interrupts, and fast interrupts.
	//CPSIE aif
	

	// Enable access to FP registers.
	MOV R1, #(0xF << 20)
	MCR P15, 0, R1, C1, C0, 2 // CPACR full access to cp11 and cp10.
	MOV R1, #(0x1 << 30)

	// Enable Floating point and Neon unit.
	VMSR	FPEXC, R1	// Set FPEXC.EN.
	ISB	// Ensure the enable operation takes effect.

		
	// Set SP at 64MB which we know our application will not crash into
	// and we also know will be available to the ARM CPU. No matter what
	// settings we use to split the memory between the GPU and ARM CPU
	// ldr     sp, =0x8000
	// ldr     sp, =(64 * 1024 * 1024) // OLM: the simple way

	// Initialize the stack pointer. From ARM bare metal doc
	.EQU stack_top, 0x8000
	.EQU CPU_STACK_SIZE, 0x1000
	LDR R13, =stack_top
	ADD R13, R13, #4
	MRC P15, 0, R0, C0, C0, 5 	// Read MPIDR.
	AND R0, R0, #0xFF 		// R0 == core number
	MOV R2, #CPU_STACK_SIZE
	MUL R1, R0, R2 			// Create separate stack spaces
	SUB R13, R13, R1		// for each processor.


	// Note! push and pop bewlow, use SP


	// Initialize SPSR in all modes.
	MOV    R0, #0
	MSR    SPSR, R0
	MSR    SPSR_svc, R0
	MSR    SPSR_und, R0
	MSR    SPSR_hyp, R0
	MSR    SPSR_abt, R0
	MSR    SPSR_irq, R0
	MSR    SPSR_fiq, R0

	// Initialize ELR_hyp.
	MOV R0, #0
	MSR ELR_hyp, R0
	
	push {r0,r1,r2,r3,lr}
	bl init_mmu
	pop {r0,r1,r2,r3,lr}	

	/*
	//push {r0,r1,r2,r3,lr}
	//bl init_uart	
	//pop {r0,r1,r2,r3,lr}
	
	LDR R1, =S0
	push {r0,r1,r2,r3,lr}
	mov r0,r1
	bl putstr
	pop {r0,r1,r2,r3,lr}

	//LDR R1, =mutex
	//LDREX R0,[R1]
	
	push {lr}	
	bl raw_putc	
	pop {lr}
	
	push {lr}
	ldr r0,=#68 // 'D'
	bl raw_putc
	pop {lr}*/

	// Run the c startup function
	// should not return and will call kernel_main
	b       _cstartup

_inf_loop:
	b       _inf_loop


	
	.globl putNL
putNL:
	push {r0,r1,r2,r3,lr}
	ldr r0,=#13
	bl raw_putc
	pop {r0,r1,r2,r3,lr}
	push {r0,r1,r2,r3,lr}
	ldr r0,=#10
	bl raw_putc
	pop {r0,r1,r2,r3,lr}
	bx lr
	
	.globl putSP
putSP:
	push {r0,r1,r2,r3,lr}
	ldr r0,=#83
	bl raw_putc
	pop {r0,r1,r2,r3,lr}
	
	push {r0,r1,r2,r3,lr}
	ldr r0,=#80
	bl raw_putc
	pop {r0,r1,r2,r3,lr}
	
	push {r0,r1,r2,r3,lr}
	ldr r0,=#58
	bl raw_putc
	pop {r0,r1,r2,r3,lr}
	
	push {r0,r1,r2,r3,lr}
	mov r0,sp
	bl puthex
	pop {r0,r1,r2,r3,lr}
	
	push {r0,r1,r2,r3,lr}
	bl putNL
	pop {r0,r1,r2,r3,lr}
	
	bx lr
	
.globl cmpAndSwap
cmpAndSwap:	
	// r0 = adr of mem loc
	// r1 = old value
	// r2 = new value
	bl putSP
	//bl putNL
	
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
	
	push {r0,r1,r2,r3,lr}
	ldr r0,=#98
	bl raw_putc
	pop {r0,r1,r2,r3,lr}
	
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
	
#define locked 1
#define unlocked 0

// lock_mutex
// Declare for use from C as extern void lock_mutex(void * mutex);
.globl lock_mutex
lock_mutex:
	LDR     r1, =locked
_b1:
	LDREX   r2, [r0]
	CMP     r2, r1        // Test if mutex is locked or unlocked
	BEQ     _b2           // If locked - wait for it to be released, from 2
	STREXNE r2, r1, [r0]  // Not locked, attempt to lock it
	CMPNE   r2, #1        // Check if Store-Exclusive failed
	BEQ     _b1           // Failed - retry from 1
			      // we should just return failure
	// Lock acquired
	DMB                   // Required before accessing protected resource
	BX      lr

_b2:
	// Take appropriate action while waiting for mutex to become unlocked
WAIT_FOR_UPDATE:
	// Here we just return failure 
    B       _b1           // Retry from 1


// unlock_mutex
// Declare for use from C as extern void unlock_mutex(void * mutex)//
.globl unlock_mutex
unlock_mutex:	
    LDR     r1, =unlocked
    DMB                   // Required before releasing protected resource
    STR     r1, [r0]      // Unlock mutex
SIGNAL_UPDATE:	
    BX      lr

.globl put32
put32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr
	
.globl startCore
startCore:
	ldr r2,=start_cpu
	mov r1,#0x40000000
	str r2,[r1,r0]
	bx lr

start_cpu:
	//ldr sp, =(128 * 1024 * 1024)
	mov r2,#0x60  // SP start
	ldr sp,[r2]
	push {lr}
	ldr r0,=#97
	bl raw_putc
	pop {lr}
	mov r2,#0x40 // adr of B
	ldr r0,[r2]
	mov r2,#0x50 // adr of interpreter
	ldr r1,[r2]
	blx r1 
	bx lr
	
.globl  qbeta_fork
qbeta_fork:
	// r0 = B, r1 = interpreter, r2 = coreNo
	// check coreNo
	mov r3,#0x40
	str r0,[r3]
	mov r3,#0x50
	str r1,[r3]
	ldr r0,=start_cpu
	mov r1,#0x40000000
	str r0,[r1,#0x9C]
	bx lr

.globl start1
start1:
    ldr r0,=start_cpu1
    mov r1,#0x40000000
    str r0,[r1,#0x9C]
    bx lr
	
start_cpu1:
    mrc p15, 0, r0, c0, c0, 5
    mov r1,#0x40
    str r0,[r1]
	ldr sp, =(128 * 1024 * 1024)
	push {lr}
	ldr r0,=#97
	bl raw_putc
	pop {lr}
	
    bl beta_fork	
    b start_cpu1

.globl start2
start2:
    ldr r0,=start_cpu2
    mov r1,#0x40000000
    str r0,[r1,#0xAC]
    bx lr

start_cpu2:
    mrc p15, 0, r0, c0, c0, 5
    mov r1,#0x40
    str r0,[r1]
    b start_cpu2

.globl start3
start3:
    ldr r0,=start_cpu3
    mov r1,#0x40000000
    str r0,[r1,#0xBC]
    bx lr

start_cpu3:
    mrc p15, 0, r0, c0, c0, 5
    mov r1,#0x40
    str r0,[r1]
    b start_cpu3
	
.align 2
S0:	.asciz "\ninit_mmu and init_uart done!\n"
.align 2
mutex:
	.word 69 // 'E'

/*
.globl reset_handler
.globl undefined_handler
.globl svc_handler
.globl prefetch_handler
.globl data_handler
	
.balign 0x20
secure_vector_table_base_address:
	B reset_handler
	B undefined_handler
	B svc_handler
	B prefetch_handler
	B data_handler
	NOP
	B IRQ_handler
monitor_vector_table_base_address:	
	B reset_handler
	B undefined_handler
	B svc_handler
	B prefetch_handler
	B data_handler
	NOP
	B IRQ_handler
*/
// You can place the FIQ handler code here.
    .global Vectors

//----------------------------------------------------------------
// Exception Vector Table
//----------------------------------------------------------------
// Note: LDR PC instructions are used here, though branch (B) instructions
// could also be used, unless the exception handlers are >32MB away.

Vectors:
    LDR PC, Reset_Addr
    LDR PC, Undefined_Addr
    LDR PC, SVC_Addr
    LDR PC, Prefetch_Addr
    LDR PC, Abort_Addr
    LDR PC, Hypervisor_Addr
    LDR PC, IRQ_Addr
    LDR PC, FIQ_Addr


    .balign 4
Reset_Addr:
    .word Reset_Handler
Undefined_Addr:
    .word Undefined_Handler
SVC_Addr:
    .word SVC_Handler
Prefetch_Addr:
    .word Prefetch_Handler
Abort_Addr:
    .word Abort_Handler
Hypervisor_Addr:
    .word Hypervisor_Handler
IRQ_Addr:
    .word IRQ_Handler
FIQ_Addr:
    .word FIQ_Handler

	
//----------------------------------------------------------------
// Exception Handlers
//----------------------------------------------------------------

/*Undefined_Handler:
	B Undefined_Handler
SVC_Handler:
	B SVC_Handler
Prefetch_Handler:
	B Prefetch_Handler
Abort_Handler:
	B Abort_Handler
Hypervisor_Handler:
	B Hypervisor_Handler
IRQ_Handler:
	B IRQ_Handler
FIQ_Handler:
	B FIQ_Handler
	*/
Reset_Handler:
	LDR R0, =Err7
	bl putstr
L7:	
	B   L7
Undefined_Handler:
	LDR R0, =Err0
	bl putstr
L0:	
	B   L0
SVC_Handler:
	LDR R0, =Err1
	bl putstr
L1:	
	B   L1
Prefetch_Handler:
 	LDR R0, =Err2
	bl putstr
L2:	
	B   L2
Abort_Handler:
	LDR R0, =Err3
	bl putstr
L3:	
	B   L3
Hypervisor_Handler:
	LDR R0, =Err4
	bl putstr
L4:	
	B   L4
IRQ_Handler:
	LDR R0, =Err5
	bl putstr
L5:	
	B   L5
FIQ_Handler:
	LDR R0, =Err6
	bl putstr
L6:	
	B   L6
.align 2
Err0:	 .asciz "\nUndefined\n"
Err1:	 .asciz "\nSVC\n"		
Err2:	 .asciz "\nPrefetch\n"
Err3:	 .asciz "\nAbort\n"
Err4:	 .asciz "\nHypervisor\n"			
Err5:	 .asciz "\nIRQ\n"			
Err6:	 .asciz "\nFIQ\n"
Err7:	.asciz "\nReset_handler\n"
