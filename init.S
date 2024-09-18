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
	b		__processor_hang

// assume processor not used in low power mode
__processor_hang:
	wfe			
	b		__processor_hang


primary_entry:
	ldr		x1, =__stack
	sub		x1, x1, #stack_size
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
el1_sync_call:
el1_irq_call:
el1_fiq_call:
el1_err_call:
	b	el1_sync_call

el1x_sync_call:
el1x_irq_call:
el1x_fiq_call:
el1x_err_call:
	b	el1x_sync_call

el0_sync_call64:
el0_irq_call64:
el0_fiq_call64:
el0_err_call64:
	b	el0_sync_call64


el0_sync_call32:
el0_irq_call32:
el0_fiq_call32:
el0_err_call32:
	b	el0_sync_call32

/* interrupt functions vectors
 * This designed for el1 of armv8
 */	
	.pushsection	".entry.text", "ax"
	.align	11
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


.balign		16
__stack:
	.skip	stack_size		//alloc stack spece for call c

	.end					//end of the init.S
