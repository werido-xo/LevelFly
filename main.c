#include "board.h"
#include "printf.h"


#define PER_MSECONDS			(CORE_FREQ / 50000)


int __attribute__((optimize("O1"))) loop_delay(int ms)
{
	int counter = 0;
	int times = PER_MSECONDS * ms;

	while (counter <= times)
		counter++;

	return times;
}


void __attribute__((optimize("O0"))) __main_entry()
{
	int index;
	unsigned int val;

	/* 1. set miniuart & led related pins  */
	gpio_funcs_init();

	/* 2. init the miniuart-related contorller */
	miniuart_putchar('h');
	miniuart_putchar('i');

	val = readl((unsigned int *) GPIO_FSEL1_ADDR);
	printf("The register value is 0x%08x \n", val);

	while (1) {
	}
}
