
//  Part of the Raspberry-Pi Bare Metal Tutorials
//  Copyright (c) 2013, Brian Sidebotham
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.


.section ".text.startup"

.global _start
.global _get_stack_pointer

_start:
    // Set it at 64MB which we know our application will not crash into
    // and we also know will be available to the ARM CPU. No matter what
    // settings we use to split the memory between the GPU and ARM CPU
    // ldr     sp, =0x8000
    ldr     sp, =(64 * 1024 * 1024)

// Run the c startup function - should not return and will call kernel_main
    b       _cstartup

_inf_loop:
    b       _inf_loop

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

