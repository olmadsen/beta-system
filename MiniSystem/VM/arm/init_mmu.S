.global init_mmu_s
init_mmu_s:
	ldr r0, tlb_l1_base
	mcr p15, 0, r0, c2, c0, 0


	ldr r0, entry0000
	ldr r1, val0000
	str r1, [r0]

	ldr r0, entry0408
	ldr r1, val0408
	str r1, [r0]
	
	ldr r0, entry00fc
	ldr r1, val00fc
	str r1, [r0]

	ldr r0, entry1020
	ldr r1, val1020
	str r1, [r0]

	mov r0, #0x3
	mcr p15, 0, r0, c3, c0, 0

	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x1
	mcr p15, 0, r0, c1, c0, 0
	bx lr
	

tlb_l1_base:
	.word 0x10200000

entry0000:
	.word 0x10200000
val0000:
	.word 0x00080c02
entry00fc:
	.word 0x102000fc
val00fc:
	.word 0x03f80c02
entry0408:
	.word 0x10200408
val0408:
	.word 0x10280c02
	
entry1020:
	.word 0x10201008
val1020:
	.word 0x10280c02


.globl init_mmu
init_mmu:
	push {lr}
	ldr r0,=#65 // 'A'
	bl raw_putc
	pop {lr}

clean_cache:
	// Disable L1 Caches.	
	MRC P15, 0, R1, C1, C0, 0 // Read SCTLR.
	BIC R1, R1, #(0x1 << 2) // Disable D Cache.
	MCR P15, 0, R1, C1, C0, 0 // Write SCTLR.
	// Invalidate Data cache to create general-purpose code. Calculate the
	// cache size first and loop through each set + way.
	MOV R0, #0x0 // R0 = 0x0 for L1 dcache 0x2 for L2 dcache.
	MCR P15, 2, R0, C0, C0, 0 // CSSELR Cache Size Selection Register.
	MRC P15, 1, R4, C0, C0, 0 // CCSIDR read Cache Size.
	AND R1, R4, #0x7
	ADD R1, R1, #0x4 // R1 = Cache Line Size.
	LDR R3, =0x7FFF
	AND R2, R3, R4, LSR #13 // R2 = Cache Set Number – 1.
	LDR R3, =0x3FF
	AND R3, R3, R4, LSR #3 // R3 = Cache Associativity Number – 1.
	CLZ R4, R3 // R4 = way position in CISW instruction.
	MOV R5, #0 // R5 = way loop counter.

way_loop:
	MOV R6, #0 // R6 = set loop counter.
set_loop:
	ORR R7, R0, R5, LSL R4 // Set way.
	ORR R7, R7, R6, LSL R1 // Set set.
	MCR P15, 0, R7, C7, C6, 2 // DCCISW R7.
	ADD R6, R6, #1 // Increment set counter.
	CMP R6, R2 // Last set reached yet?
	BLE set_loop // If not, iterate set_loop,
	ADD R5, R5, #1 // else, next way.
	CMP R5, R3 // Last way reached yet?
	BLE way_loop // if not, iterate way_loop.

	B xxx
	.align 12
	.ltorg
xxx:
	push {lr}
	ldr r0,=#66  // 'B'
	bl raw_putc
	pop {lr}

init_TTBCR:	
	// Initialize TTBCR.
	MOV R0, #0 // Use short descriptor.
	MCR P15, 0, R0, C2, C0, 2 // Base address is 16KB aligned.
	// Perform translation table walk for TTBR0.

	// Initialize DACR.
	LDR R1, =0x55555555 // Set all domains as clients.
	MCR P15, 0, R1, C3, C0, 0 // Accesses are checked against the
	// permission bits in the translation tables.

	// Initialize SCTLR.AFE.
	MRC P15, 0, R1, C1, C0, 0 // Read SCTLR.
	BIC R1, R1, #(0x1 <<29) // Set AFE to 0 and disable Access Flag.
	MCR P15, 0, R1, C1, C0, 0 // Write SCTLR.

	push {lr}
	ldr r0,=#67 // 'C'
	bl raw_putc
	pop {lr}
	
	
	// Initialize TTBR0.
	LDR R0, =ttb0_base // ttb0_base must be a 16KB-aligned address.
	MOV R1, #0x2B // The translation table walk is normal, inner
	ORR R1, R0, R1 // and outer cacheable, WB WA, and inner
	MCR P15, 0, R1, C2, C0, 0 // shareable.
	// Set up translation table entries in memory
	LDR R4, =0x00100000 // Increase 1MB address each time.
	LDR R2, =0x00015C06 // Set up translation table descriptor with
	// Secure, global, full accessibility,
	// executable.
	// Domain 0, Shareable, Normal cacheable memory
	LDR R3, =1024 // executes the loop 1024 times to set up
	// 1024 descriptors to cover 0-1GB memory.

	push {R0,R1,R2,R3,lr}
	ldr r0,=#68 // 'D'
	bl raw_putc
	pop {R0,R1,R2,R3,lr}

	push {R0,R1,R2,R3,lr}	
	mov R0, R3
	bl puthex
	pop {R0,R1,R2,R3,lr}
	
loop:
	STR R2, [R0], #4 // Build a page table section entry.
	ADD R2, R2, R4 // Update address part for next descriptor.

	push {R0,R2,R3,lr}
	mov r0,R2
	bl puthex
	pop {R0,R2,R3,lr}
	push {R0,R2,R3,lr}	
	mov R0, R3
	bl puthex
	pop {R0,R2,R3,lr}

	SUBS R3, #1	
	BNE loop

	push {lr}
	ldr r0,=#69 // 'E'
	bl raw_putc
	pop {lr}

	b final
	
	LDR R2, =0x40010C02 // Set up translation table descriptors with
			// secure, global, full accessibility,
			// Domain=0 Shareable Device-nGnRnE Memory.
	LDR R3, =3072 	// Executes loop 3072 times to set up 2096	
			// descriptors to cover 1-4GB memory.
loop2:
	STR R2, [R0], #4 // Build a translation table section entry.
	ADD R2, R2, R4 // Update address part for next descriptor.
	SUBS R3, #1
	BNE loop2

	push {lr}
	ldr r0,=#70 // 'F'
	bl raw_putc
	pop {lr}
	
final:	
// SMP is implemented in the CPUECTLR register.
	MRRC P15, 1, R0, R1, C15 // Read CPUECTLR.
	ORR R0, R0, #(0x1 << 6) // Set SMPEN.
	MCRR P15, 1, R0, R1, C15 // Write CPUECTLR.

// Enable caches and the MMU.
	MRC P15, 0, R1, C1, C0, 0 // Read SCTLR.
	ORR R1, R1, #(0x1 << 2) // The C bit (data cache).
	ORR R1, R1, #(0x1 << 12) // The I bit (instruction cache).
	ORR R1, R1, #0x1 // The M bit (MMU).
	MCR P15, 0, R1, C1, C0, 0 // Write SCTLR.
	DSB
	ISB
	
	push {lr}
	ldr r0,=#68 // 'D'
	bl raw_putc
	pop {lr}

	bx lr

	B yyy
	.align 12
	.ltorg
yyy:

.align 12
ttb0_base:
	.space 1024 * 4
	
