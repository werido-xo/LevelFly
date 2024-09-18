/*
 *
 */
#ifndef __ASM_ASSEMBLER_H
#define __ASM_ASSEMBLER_H

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6


#define SYM_L_GLOBAL(name)		.global name
#define SYM_L_WEAK(name)		.weak name
#define SYM_L_LOCAL(name)		/* nothing */

#define SYM_A_ALIGN				.align 4, 0x90	
#define SYM_A_NONE				/* nothing */

#define ASM_NL			;		/* next line com */
#define SYM_T_NONE				STT_NOTYPE


/* define symbol start in the begin fo code */
#define SYM_ENTRY(name, linkage, align...)	\
	linkage(name)	ASM_NL					\
	align	ASM_NL							\
	name:

#define SYM_START(name, linkage, align...)	\
	SYM_ENTRY(name, linkage, align)

#define SYM_CODE_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)

/* define symbol end in the end of the code */
#define SYM_END(name, sym_type)				\
	.type name sym_type ASM_NL				\
	.size name, .-name

#define SYM_CODE_END(name)					\
	SYM_END(name, SYM_T_NONE)


/* defien macro for exception entries for armv8 format */
	.macro ventry	label
	.align 7
	b	\label
	.endm

#endif
