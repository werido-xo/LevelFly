/* The file "init.S" designed for boot linux-platform
 *
 *	author: weirdo-xo
 *	data: 2024/09/04
 *
 */


#include "assembler.h"


	.section ".text.start"
	.global _start

	.equ	stack_size, 8192


_start:
	mrs		x1, mpidr_el1
	and		x1, x1, #3 
	cbz		x1, primary_entry

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


primary_entry:
	// ldr		x1, =__stack
	// sub		x1, x1, #stack_size
	ldr		x1, = _start
	mov		sp, x1

	// clear section .bss to zero
	ldr		x1, = __bss_start
	ldr 	w2, = __bss_size
	cbz		w2, __jump_to_main


__clean_bss:
	str		xzr, [x1], #8
	sub		w2, w2, #1
	cbnz	w2, __clean_bss


end_clean_bss:
__jump_to_main:
	// goto c functions
	b	__main_entry 



/* define exception operations */
// el1_sync_call:
// el1_irq_call:
// el1_fiq_call:
// el1_err_call:
//	b	el1_sync_call

// el1x_sync_call:
// el1x_irq_call:
// el1x_fiq_call:
// el1x_err_call:
//	b	el1x_sync_call

// el0_sync_call64:
// el0_irq_call64:
// el0_fiq_call64:
// el0_err_call64:
//	b	el0_sync_call64


// el0_sync_call32:
// el0_irq_call32:
// el0_fiq_call32:
// el0_err_call32:
//	b	el0_sync_call32

/* interrupt functions vectors
 * This designed for el1 of armv8
 */	
//	.pushsection	".entry.text", "ax"
//	.align	11
/*
SYM_CODE_START(vectors)
	ventry		el1_sync_call
	ventry		el1_irq_call
	ventry		el1_fiq_call
	ventry		el1_err_call

	ventry		el1x_sync_call
	ventry		el1x_irq_call
	ventry		el1x_fiq_call
	ventry		el1x_err_call

	ventry		el0_sync_call64
	ventry		el0_irq_call64
	ventry		el0_fiq_call64
	ventry		el0_err_call64

	ventry		el0_sync_call32
	ventry		el0_irq_call32
	ventry		el0_fiq_call32
	ventry		el0_err_call32
SYM_CODE_END(vectors)
*/

//.balign		16
//__stack:
//	.skip	stack_size		//alloc stack spece for call c

	.end					//end of the init.S
