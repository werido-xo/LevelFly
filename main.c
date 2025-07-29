#include "board.h"
#include "printf.h"
#include "gic-400.h"
#include "stdarg.h"

#define PER_MSECONDS			(CORE_FREQ / 50000)
#define PER_PERIODS				0x5D0000


int __attribute__((optimize("O0"))) loop_delay(int ms)
{
	int counter = 0;
	int times = PER_MSECONDS * ms;

	while (counter <= times)
		counter++;

	return times;
}


unsigned int get_currentEL()
{
	unsigned val;

	__asm__ __volatile__(
	"mrs	%0, currentel \n"
	: "=r" (val)
	:
	: "memory"
	);

	return val >> 2;
}

unsigned long get_sctlr()
{
	unsigned long val;

	__asm__ __volatile__(
	"mrs	%0, sctlr_el1 \n"
	: "=r" (val)
	:
	: "memory"
	);

	return val;
}

void system_timer_init(void)
{
	unsigned int val;
	unsigned int sec = PER_PERIODS;

	/* 1. clear timer compare register of channel 1*/
	val = readl(SYSTIMER_CLOW_ADDR);
	val += sec;
	writel(val, SYSTIMER_CC1_ADDR);

	/* 2. enable interrupt of the channel 1 */
	gic400_enable_irq(TIM1_IRQ);
}


unsigned int sum_funcs(int count, va_list va)
{
	int sum, index;
	sum = 0;



	return sum;
}

/* variable parameter functions
 * 1. get the base address of count
 * 2. based on the &count get the number of the variable
 */
unsigned int my_sum(int count, ...)
{
	int base = 0x30;
	va_list ap;			// it may be pointer in the implement
	int index;

	va_start(ap, count);
	for (index = 0; index < count; index++) {
		base += va_arg(ap, int);
	}
	// base += sum_funcs(count, ap);
	va_end(ap);

	return base;
}


void __attribute__((optimize("O0"))) __main_entry()
{
	int index;
	unsigned int val;
	int lines;
	unsigned char out;

	/* 1. set miniuart & led related pins  */
	gpio_funcs_init();

	/* 2. init the miniuart-related contorller */
	miniuart_putchar('h');
	miniuart_putchar('i');

	local_irq_disable();
	miniuart_putchar('i');

	unsigned int *addr = (unsigned int *)0x51000000;
	unsigned int data = 0x5A5A5A5A;

	*addr = data;
	if (*addr != data)
		miniuart_putchar('n');
	else
		miniuart_putchar('y');

//	val = readl((unsigned int *) (GICD_IIDR_ADDR));
//	printf("The distributor implemention: 0x%08x \n", val);

//	val = readl((unsigned int *) (GICC_IIDR_ADDR));
//	printf("The interface implemention: 0x%08x \n", val);

	/* 3. init the gic-400 controller */
	lines = gic400_init();
	miniuart_putchar('d');
	
	local_irq_enable();
	local_irq_barrier();

//	val = get_cpu_daif();
//	printf("DAIF: 0x%08x \n", val);

	/* verify the security level of the system */
//	val = readl((unsigned int *)(GICD_CTLR_ADDR));
//	printf("The value GICD.CTLR = 0x%08x \n", val);

//	val = readl((unsigned int *)(GICC_CTLR_ADDR));
//	printf("The value GICC.CTLR = 0x%08x \n", val);

//	val = get_currentEL();
//	printf("CurrentEL = %d \n", val);

//	val = get_sctlr();
//	printf("SCTLR = 0x%16x \n", val);
	
	/* 4. enable the system timer */
	system_timer_init();


	// printf("\n");
	debug_print("Hello\n");

	printf("weirdo\n");

	out = my_sum(3, 2, 3, 1);
	miniuart_putchar(out);

	miniuart_putchar('0');

//	unsigned int dat0, dat1, offs;
//
//	offs = 0;
//	for (index = 0; index < lines; index += 32) {
//		dat0 = readl((unsigned int *)(GICD_ISEN0_ADDR + offs));
//		// manage all interrupt to group 0
//		val = readl((unsigned int *)(GICD_IGRP0_ADDR + offs));
//		printf("OFFS: %d; ISEN: 0x%08x; IGRP: 0x%08x \n", offs, dat0, val);
//
//		offs += 4;
//	}

	/* 4. config all the priority of the interrupt 
	 *    config all the interrupt routing to processor 0 
	 */
//	offs = 0x20;
//	for (index = 32; index < lines; index += 4) {
//		dat0 = readl((unsigned int *)(GICD_IPRIO0_ADDR + offs));
//		dat1 = readl((unsigned int *)(GICD_ITARGET0_ADDR + offs));
//		printf("OFFS: %d; IPRI0: 0x%08x; ITARGET: 0x%08x \n", offs, dat0, dat1);
//		offs += 4;
//	}

//	val = readl((unsigned int *)(GICC_PMR_ADDR));
//	printf("GICC_PMR: 0x%08x \n", val);


	while (1) {
		index++;
		loop_delay(400);

		val = readl(SYSTIMER_CTLR_ADDR);
		if (val & 0x02) {
			// val = val & 0xF;
			// writel(val, SYSTIMER_CTLR_ADDR);

			// val = readl(SYSTIMER_CLOW_ADDR);
			// val += PER_PERIODS;
			// writel(val, SYSTIMER_CC1_ADDR);

			miniuart_putchar('y');
		} else	{
			miniuart_putchar('-');
		}
	}
}
