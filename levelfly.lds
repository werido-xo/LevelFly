/*
 * Copyright (C) 2016  Lin-Chen <weirdo-xo@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

SECTIONS
{
	. = 0x80000000;
	.start : {
		 __start_text = .; 
		 KEEP(*(.text.start));
		 . = ALIGN(8);
		 *(.text);
		 . = ALIGN(8);
		 *(.text.*);
		 . = ALIGN(8);
		 .gnu.linkonce.t*; 
	}

	.rodata : {
		*(.rodata .rodata.* .gnu.linkonce.r*);
	}
	PROVIDE(__data = .);

	.data : {
		*(.data .data.* .gnu.linkonce.d*);
	}

	.bss (NOLOAD) : {
		. = ALIGN(16);
		__bss_start = .;
		*(.bss .bss.*);
		*(COMMON);
		__bss_end = .;
	}
	
	_end = .;

	/* .text     : { *(.text) } */
	/DISCARD/ : { *(.dynstr*) }
	/DISCARD/ : { *(.common) }
	/DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.plt*) }
	/DISCARD/ : { *(.interp*) }
	/DISCARD/ : { *(.gnu*) }
	/DISCARD/ : { *(.note*) }
}

/* define the size of the .bss section */
__bss_size = (__bss_end - __bss_start) >> 3;
