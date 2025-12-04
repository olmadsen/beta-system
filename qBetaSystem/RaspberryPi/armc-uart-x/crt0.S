	.section	 .traps, "ax"
__start:
	b	__start_ram1

	.text
	.type __start_ram1, %function
__start_ram1:
	# Read preocessor nummber, move slave processors to an infinite loop
	mrs	r7, mpidr_el1
	and	r7, r7, #3
	cbz	r7, __start_master
0:	wfe				// Busy loop
	b	0b

__start_master:
	# Load stack pointer (on 32 bit)
	adrp	r2, __cpu0_stack_end
	add	r2, r2, #:lo12:__cpu0_stack_end
	mov 	sp, r2

	# Clear BSS
	ldr	w0, bss_segment + #0
	ldr	w1, bss_segment + #4
0:	cbz	r1, 1f
	str	xzr, [x0], #8
	sub	r1,r1,#1
	cbnz	r1, 0b
1:
	bl main /* Call main routine */
0:	b 0b	/* Wait foever in case of exit */
	.size __start_ram1, . - __start_ram1

.bss_segment:
	.word 	__bss_start
	.word	__bss_dwords

	
	