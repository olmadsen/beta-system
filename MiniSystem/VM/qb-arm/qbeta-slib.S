.section ".text.startup"

.global _start
.global _get_stack_pointer
.global init_mmu_s
_start:
	// Set it at 64MB which we know our application will not crash into
	// and we also know will be available to the ARM CPU. No matter what
	// settings we use to split the memory between the GPU and ARM CPU
	// ldr     sp, =0x8000
	ldr     sp, =(64 * 1024 * 1024)
	//bl init_mmu
	
	// Run the c startup function - should not return and will call kernel_main
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

