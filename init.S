/* The file "init.S" designed for boot linux-platform
 *
 *	author: weirdo-xo
 *	date: 2024/09/04
 *
 */


#include "assembler.h"


#define _STACK			0x51000000
#define _EXCSTACK		0x52000000

	.section ".text.start"
	.global _start

	.equ	stack_size, 8192


_start:
	mrs		x1, mpidr_el1
	and		x1, x1, #3 
	cbz		x1, level_change

// assume processor not used in low power mode
__processor_hang:
	wfe			
	b		__processor_hang


light_led:
	/* light the led by asm code
	 * w5: the gpio-controller base address
	 * w2: the target register
	 * w3: target register value
	 * w4: the fields of the gpio-pin
	 */
	// 1. set the gpio output
	mov		w5, #0x0000
	movk	w5, #0xfe20, lsl #16

	add 	w2, w5, #4
	ldr		w3, [x2]
	mov		w4, #0x7
	lsl		w4, w4, #24
	bic		w3, w3, w4
	mov		w4, #0x1
	lsl		w4, w4, #24
	orr		w3, w3, w4
	str		w3, [x2]

	// 2. set the gpio-pin output high
	add		w2, w5, #0x1c
	mov		w3, #0x1		//output-high
	lsl		w3, w3, #18
	str		w3, [x2]

	ret

level_change:
    // config EL1 before leaving inital(!) EL2, exc. handler run in EL1h
    ldr     x1, =_EXCSTACK
    msr     sp_el1, x1
   
	// MSR		CPTR_EL3, XZR
	// nop

	MSR		CPTR_EL2, XZR
	nop

	MOV		x0, #0x00300000
	MSR		CPACR_EL1, x0
	nop
 
    // enable AArch64 in EL1
    mov     x2, #(1 << 31)          // AArch64
    msr     hcr_el2, x2
    
    // Setup System Control register access
    mov     x2, #0x0800             // = more details!
    movk    x2, #0x30d0, lsl #16    // last bit is 0 = MMU disabled (Cache?)
    msr     sctlr_el1, x2
    
    // change execution level to EL1
    mov     x2, #0x3c4
    msr     spsr_el2, x2            // EL1_SP0 | D | A | I | F
    adr     x2, primary_entry
    msr     elr_el2, x2
    eret


primary_entry:
 	ldr		x1, =_STACK
	// sub		x1, x1, #stack_size
	// ldr		x1, = __stack_el0
	mov		sp, x1

	// clear section .bss to zero
	ldr		x1, = __bss_start
	ldr 	w2, = __bss_size
	cbz		w2, __jump_to_main


__clean_bss:
	str		xzr, [x1], #8
	sub		w2, w2, #1
	cbnz	w2, __clean_bss


__jump_to_main:
	// set the vector base address for EL1
	adr		x1, vectors
	msr		vbar_el1, x1		// vector table address

	// test  qregister
	// fadd	d0, d1, d2

	// goto c functions
	b		__main_entry 



#include "entry.S"

/* define exception operations: goto exception ops
 * kernel_entry be defined as a macro, without effect
 * previous process state
 */
el1x_irq_call:
	kernel_entry
	bl		gic400_int_dispatch
	kernel_exit


invalid_gic400_entry:
	eret 		



/* gic-400 interrupt functions vectors, the init
 * of this controller implemented in the file gic-400.c
 *
 * This designed for el1 of armv8
 */	
	.pushsection	".entry.text", "ax"
	.align	11
SYM_CODE_START(vectors)
	ventry		invalid_gic400_entry
	ventry		el1x_irq_call
	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry

	ventry		invalid_gic400_entry
	ventry		el1x_irq_call
	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry

	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry

	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry
	ventry		invalid_gic400_entry
SYM_CODE_END(vectors)

	
	.balign		16
	.data
__stack_el0:	.word	0x01000000
				.skip	4, 0

__stack_el1:	.word	0x02000000
				.skip	4, 0

// __stack:
//	.skip	stack_size		//alloc stack spece for call c

	.end					//end of the init.S
