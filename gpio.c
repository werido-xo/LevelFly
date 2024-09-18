#include "board.h"


void gpio_funcs_set(u32 pin, u32 alt)
{
	unsigned int offs, val, shift;

	offs = pin / 10;
	shift = pin % 10;

	val = readl((unsigned int *)(GPIO_BASE_ADDR + offs << 2));
	val &= ~(0x7 << (shift * 3));
	val |= alt;
	writel(val, (unsigned int *)(GPIO_BASE_ADDR + offs << 2));
}


void gpio_output_set(u32 pin, u32 level)
{
	unsigned int shift;
	unsigned int *addr;

	/* 1. get the base address base on the level */
	if (level) {
		addr = GPIO_SET0_ADDR;
	} else {
		addr = GPIO_CLR0_ADDR;
	}

	/* 2. get the offset of the pin in register */
	shift = pin >> 5;		
	if (shift) 
		addr += 0x4;
	else
		shift = pin;
		
	writel(0x1 << shift, addr);
}


unsigned int gpio_level_read(u32 pin)
{
	unsigned int shift, val;
	unsigned int *addr;

	addr = GPIO_LEV0_ADDR;
	shift = pin >> 5;		
	if (shift) 
		addr += 0x4;
	else
		shift = pin;

	val = readl(addr);
	val |= 0x1 << shift;

	return val ? 1 : 0;
}


void gpio_pullud_set(u32 pin, u32 up_down)
{
	unsigned int *addr;
	unsigned int offs, bits, val;

	
	offs = pin >> 4;
	bits = (pin & 0xF) << 1;
	addr = GPIO_CNTL0_ADDR + (offs << 2);

	val = readl((unsigned int *) addr);
	val &= ~(0x3 << bits);
	val |= (up_down << bits);
	writel(val, (unsigned int *) addr);
}



void gpio_funcs_init(void)
{
	unsigned int val;
	unsigned int mask = (0x7 << 15) | (0x7 << 12);
	unsigned int setting = (GPIO_FUNCTION_ALT5 << 15) \
							| (GPIO_FUNCTION_ALT5 << 12);

	val = readl(GPIO_FSEL1_ADDR);
	val = val & (~mask);
	val |= setting;
	writel(val, GPIO_FSEL1_ADDR);
}
