.globl init_mmu_x
init_mmu_x:
// Example 4.1. Setting up caches, MMU, and branch predictors
	// Disable MMU.
	MRC p15, 0, r1, c1, c0, 0 // Read Control Register configuration data.
	BIC r1, r1, #0x1
	MCR p15, 0, r1, c1, c0, 0 // Write Control Register configuration data.
		
	// Disable L1 Caches.
	MRC p15, 0, r1, c1, c0, 0 	// Read Control Register configuration data.
	BIC r1, r1, #(0x1 << 12) 	// Disable I Cache.
	BIC r1, r1, #(0x1 << 2) 	// Disable D Cache.
	MCR p15, 0, r1, c1, c0, 0 	// Write Control Register configuration data

	// Invalidate L1 Caches.
	// Invalidate Instruction cache.
	MOV r1, #0
	MCR p15, 0, r1, c7, c5, 0

	// Invalidate Data cache.
	// To make the code general purpose, calculate the
	// cache size first and loop through each set + way.

	MRC p15, 1, r0, c0, c0, 0 	// Read Cache Size ID.
	LDR r3, =#0x1ff
	AND r0, r3, r0, LSR #13 	// r0 = no. of sets - 1.
	
	B cp1
	.align 2
	.ltorg
cp1:
	MOV r1, #0 				// r1 = way counter way_loop.
way_loop:
	MOV r3, #0 				// r3 = set counter set_loop.
set_loop:
	MOV r2, r1, LSL #30
	ORR r2, r3, LSL #5 		// r2 = set/way cache operation format.
	MCR p15, 0, r2, c7, c6, 2	// Invalidate the line described by r2.
	ADD r3, r3, #1 			// Increment set counter.
	CMP r0, r3 			// Last set reached yet?
	BGT set_loop 			// If not, iterate set_loop, 
	ADD r1, r1, #1 			// else, next.
	CMP r1, #4 			// Last way reached yet?
	BNE way_loop 			// if not, iterate way_loop.

	// Invalidate TLB
	MCR p15, 0, r1, c8, c7, 0

	// Branch Prediction Enable.
	MOV r1, #0
	MRC p15, 0, r1, c1, c0, 0 	// Read Control Register configuration data.
	ORR r1, r1, #(0x1 << 11) 	// Global BP Enable bit.
	MCR p15, 0, r1, c1, c0, 0 	// Write Control Register configuration data.

// The following table shows the code you must use to create your translation 
// tables. Use the variable ttb_address to denote the address for the initial 
// translation table. This must be a 16KB area of memory whose start address is 
// aligned to a 16KB boundary, to which an L1 translation table can be written.
// Example 4.2. Create translation tables
	// Enable D-side Prefetch
	MRC p15, 0, r1, c1, c0, 1 		// Read Auxiliary Control Register.
	ORR r1, r1, #(0x1 <<2) 			// Enable D-side prefetch.
	MCR p15, 0, r1, c1, c0, 1;		// Write Auxiliary Control Register.
	DSB
	ISB
	// DSB causes completion of all cache maintenance operations appearing in program
	// order before the DSB instruction.
	// An ISB instruction causes the effect of all branch predictor maintenance
	// operations before the ISB instruction to be visible to all instructions
	// after the ISB instruction.
	// Initialize PageTable.

	// Create a basic L1 page table in RAM, with 1MB sections containing a flat
	// (VA=PA) mapping, all pages Full Access, Strongly Ordered.

	// It would be faster to create this in a read-only section in an assembly file.

	
	LDR r0, =#0b00000000000000000000110111100010 	// r0 is the non-address part of descriptor.
	        //0x   0   0   0   0   0   D   E   2
	//LDR r0, =0x0010DE6
	B cp2
	.align 2
	.ltorg
cp2:
 	
	LDR r1, =ttb_address
	LDR r3, = 4095				// loop counter.
write_pte:
	ORR r2, r0, r3, LSL #20			// OR together address & default PTE bits.
	STR r2, [r1, r3, LSL #2]		// Write PTE to TTB.
	SUBS r3, r3, #1				// Decrement loop counter.
	BNE write_pte
	//B cp3
	// For the first entry in the table, You can make it cacheable, normal,	write-back, write allocate.
	BIC r0, r0, #0b1100 			// Clear CB bits.
	ORR r0, r0, #0b0100 			// inner write-back, write allocate
	BIC r0, r0, #0b111000000000000 		// Clear TEX bits.
	ORR r0, r0, #0b101000000000000 		// set TEX as write-back, write allocate
	ORR r0, r0, #0b10000000000000000 	// shareable.
	STR r0, [r1]

	B cp3
	.align 2
	.ltorg
cp3:
 	// Initialize MMU.
	MOV r1,#0x0
	MCR p15, 0, r1, c2, c0, 2 // Write Translation Table Base Control Register.
	LDR r1, =ttb_address
	MCR p15, 0, r1, c2, c0, 0 // Write Translation Table Base Register 0.

	B cp4
	.align 2
	.ltorg
cp4:	
	// In this simple example, do not use TRE or Normal Memory Remap Register.
	// Set all Domains to Client.
	LDR r1, =0x55555555
	MCR p15, 0, r1, c3, c0, 0 		// Write Domain Access Control Register.
	
	B cp5
	.align 2
	.ltorg
cp5:
	// Enable MMU
	MRC p15, 0, r1, c1, c0, 0 		// Read Control Register configuration data.
	ORR r1, r1, #0x1 			// Bit 0 is the MMU enable.
	MCR p15, 0, r1, c1, c0, 0 		// Write Control Register configuration data.

	push {R0,R1,R2,R3,lr}
	ldr r0,=#68 // 'D'
	bl raw_putc
	pop {R0,R1,R2,R3,lr}
	bx lr
	
.align 14
ttb_address:
	.space 1024 * 4 * 4	


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
	//B QQQQ

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

way_loop_2:
	MOV R6, #0 // R6 = set loop counter.
set_loop_2:
	ORR R7, R0, R5, LSL R4 // Set way.
	ORR R7, R7, R6, LSL R1 // Set set.
	MCR P15, 0, R7, C7, C6, 2 // DCCISW R7.
	ADD R6, R6, #1 // Increment set counter.
	CMP R6, R2 // Last set reached yet?
	BLE set_loop_2 // If not, iterate set_loop,
	ADD R5, R5, #1 // else, next way.
	CMP R5, R3 // Last way reached yet?
	BLE way_loop_2 // if not, iterate way_loop.

	B xxx
	.align 2
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
	
QQQQ:	
	// Initialize TTBR0.
	LDR R0, =ttb0_base // ttb0_base must be a 16KB-aligned address.
	MOV R1, #0x2B // The translation table walk is normal, inner
	ORR R1, R0, R1 // and outer cacheable, WB WA, and inner
	MCR P15, 0, R1, C2, C0, 0 // shareable.
	// Set up translation table entries in memory
	LDR R4, =0x00100000 // Increase 1MB address each time.
	//LDR R2, =0x00000C02 // From HPD: ARM MMU tutorial: makes no difference
	//Full access, domain 0, no cache, page table entry
	// From bare metal boot doc
	//LDR R2, =0x00000C12 // just trying bit4=1
	//LDR R2, =0x00015C16 // just trying bit4=1
	//LDR R2, =0x40010C02
	//LDR R2, =0x00015C0E // Cacheable bit set
	//LDR R2, =0x00010C0A
	LDR R2, =0x00015C06 // Set up translation table descriptor with
	// Secure, global, full accessibility,
	// executable.
	// Domain 0, Shareable, Normal cacheable memory
	LDR R3, =4095
	//LDR R3, =1024 // executes the loop 1024 times to set up
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

//	mov r0, #0x3   // what is this? See init_mmu_s
//	mcr p15, 0, r0, c3, c0, 0
	
// Enable caches and the MMU.
	MRC P15, 0, R1, C1, C0, 0 // Read SCTLR.
	ORR R1, R1, #(0x1 << 2) // The C bit (data cache).
	ORR R1, R1, #(0x1 << 12) // The I bit (instruction cache).
	ORR R1, R1, #0x1 // The M bit (MMU).
	MCR P15, 0, R1, C1, C0, 0 // Write SCTLR.
	DSB
	ISB
	
	push {lr}
	ldr r0,=#71 // 'G'
	bl raw_putc
	pop {lr}

	bx lr

	B yyy
	.align 2
	.ltorg
yyy:

.align 14
ttb0_base:
	.space 1024 * 4 * 4
	
