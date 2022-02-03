.globl init_mmu
init_mmu:
	
	/*ldr r0,=#65 // 'A'
	push {lr}	
	bl raw_putc	
	pop {lr}*/
	
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
	ORR R7, R0, R5, LSL R4    // Set way.
	ORR R7, R7, R6, LSL R1    // Set set.
	MCR P15, 0, R7, C7, C6, 2 // DCCISW R7.
	ADD R6, R6, #1            // Increment set counter.
	CMP R6, R2                // Last set reached yet?
	BLE set_loop 		  // If not, iterate set_loop,
	ADD R5, R5, #1 		  // else, next way.
	CMP R5, R3 		  // Last way reached yet?
	BLE way_loop 		  // if not, iterate way_loop.

		
	/*ldr r0,=#66 // 'B'
	push {lr}	
	bl raw_putc	
	pop {lr}*/

	
	// Initialize translation table control registers 
	LDR R1, =0xFF440400 // ATTR0 is Device-nGnRnE. ATTR1 is Device. 
	// ATTR2 is Normal Non-Cacheable. 
	// ATTR3 is Normal Cacheable. 
	MCR P15, 0, R1, C10, C2, 0 // Only use MAIR0. 
	LDR R0, =0xB0003500 // Use TTBR0 and long descriptor formant. 
	MCR P15, 0, R0, C2, C0, 2 // translation table walk is Inner-shareable 
	// Normal Inner and Outer cacheable. 
	LDR R0, =ttb0_base 
	MOV R1, #0 
	MCRR P15, 0, R0, R1, C2 // TTBR0 ASID=0. 
	// Set up translation table entries in memory with looped store instructions. 
	// Set a level 1 translation table. 
	// The first entry points to level2_pagetable. 
	LDR R1, =level2_pagetable // Must be a 4KB-aligned address. 
	LDR R2, =0xFFFFF000 
	AND R2, R1, R2 
	ORR R2, R2, #0x3 
	MOV R3, #0 // NSTable=0 APTable=0 XNTable=0 PXNTable=0. 
	STRD R2, R3, [R0], #8 
	// The second entry is 1GB block, 0x40000000 - 0x7FFFFFFF. 
	MOV R3, #0 // XN=0 PXN=0. 
	LDR R2, =0x40000741 // nG=0 AF=1 Inner and Outer Shareable. 
	STRD R2, R3, [R0], #8 // R/W at all ELs secure memory. 
	// The third entry is 1GB block, 0x80000000 - 0xBFFFFFFF. 
	LDR R2, =0x80000741 // AttrIdx=000 Device-nGnRnE. 
	STRD R2, R3, [R0], #8 
	// The fourth entry is 1GB block, 0xC0000000 - 0xFFFFFFFF. 
	LDR R2, =0xC0000741 // AttrIdx=000 Device-nGnRnE. 
	STRD R2, R3, [R0], #8 
	// Set level 2 translation table. 
	LDR R0, =level2_pagetable // R0 is the base address of level2_pagetable. 
	LDR R2, =0x0000074D // nG=0 AF=1 Inner and Outer Shareable. 
	// R/W at all ELs secure memory. 
	// AttrIdx=011 Normal Cacheable. 
	MOV R3, #0 // XN=0 PXN=0. 
	MOV R4, #512 // Set 512 level2 block entries. 
	LDR R5, =0x00200000 // Increase 2MB address each time. 
loop: 
	STRD R2, R3, [R0], #8 // Each entry occupies two words. 
	ADD R2, R2, R5 
	SUBS R4, #1 
	BNE loop

	/*push {lr}
	ldr r0,=#67 // 'c'
	bl raw_putc
	pop {lr}*/
	
	b EnableMMU_caches
	// constant pool
.align 2
	.ltorg
	.space	4000
	// Put a 64-bit value with little endianness. 
	.macro PUT_64B high, low 
	.word \low 
	.word \high 
	.endm 

	// Create an entry pointing to a next-level table. 
	.macro TABLE_ENTRY PA, ATTR 
	PUT_64B \ATTR, (\PA) + 0x3 
	.endm 

	// Create an entry for a 1GB block. 
	.macro BLOCK_1GB PA, ATTR_HI, ATTR_LO 
	PUT_64B \ATTR_HI, ((\PA) & 0xC0000000) | \ATTR_LO | 0x1 
	.endm 

	// Create an entry for a 2MB block. 
	.macro BLOCK_2MB PA, ATTR_HI, ATTR_LO 
	PUT_64B \ATTR_HI, ((\PA) & 0xFFE00000) | \ATTR_LO | 0x1 
	.endm
	
	.align 12
	.globl ttb0_base
	.globl ttb0_base_x
ttb0_base_x:
ttb0_base: 
	TABLE_ENTRY level2_pagetable, 0 
	BLOCK_1GB 0x40000000, 0, 0x740 
	BLOCK_1GB 0x80000000, 0, 0x740 
	BLOCK_1GB 0xC0000000, 0, 0x740 

	.align 12 
level2_pagetable: 
	.set ADDR, 0x000 // The current page address. 
	.rept 0x200 
	BLOCK_2MB (ADDR << 20), 0, 0x74C 
	.set ADDR, ADDR+2 
	.endr
	
EnableMMU_caches:
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

	/*push {lr}
	ldr r0,=#68 // 'D'
	bl raw_putc
	pop {lr}
	
	LDR R1, =mutex
	LDR R0,[R1]
	
	ldr r0,=#69 // 'E'
	push {lr}	
	bl raw_putc	
	pop {lr}
	
	LDR R1, =S0
	push {r0,r1,r2,r3,lr}
	mov r0,r1
	bl putstr
	pop {r0,r1,r2,r3,lr}

	MRC P15,0, R2, C0,C2,3
	push {r0,r1,r2,r3,lr}
	mov r0,r2
	bl puthex
	pop {r0,r1,r2,r3,lr}

	
	push {r0,r1,r2,r3,lr}
	bl putnl
	pop {r0,r1,r2,r3,lr}

	LDR R1, =S1
	push {r0,r1,r2,r3,lr}
	mov r0,r1
	bl putstr
	pop {r0,r1,r2,r3,lr}	
	
	MRRC P15, 1, R0, R1, C15 // Read CPUECTLR.
	push {r0,r1,r2,r3,lr}
	bl puthex
	pop {r0,r1,r2,r3,lr}	

	push {r0,r1,r2,r3,lr}
	bl putnl
	pop {r0,r1,r2,r3,lr}
	
	LDR R1, =S2
	push {r0,r1,r2,r3,lr}
	mov r0,r1
	bl putstr
	pop {r0,r1,r2,r3,lr}
	
	MRC P15, 0, R1, C1, C0, 0 // Read SCTLR.	
	push {r0,r1,r2,r3,lr}
	mov r0,r1
	bl puthex
	pop {r0,r1,r2,r3,lr}
	
	push {r0,r1,r2,r3,lr}
	//bl putnl
	pop {r0,r1,r2,r3,lr}
	
	push {lr}
	ldr r0,=#70 // 'F'
	bl raw_putc
	pop {lr}
	
	//LDR R1, =mutex
	//LDREX R0,[R1]
	
	push {lr}	
	bl raw_putc	
	pop {lr}*/
	
	bx lr

.align 2
mutex:
	.word 69 // 'E'

S0:	.asciz "\nID_ISAR3: "
S1:	.asciz "CPUECTLR: "	
S2:	.asciz "SCTLR   : "	
	
// constant pool
.align 2
	.ltorg
	
