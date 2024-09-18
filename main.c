#include "board.h"
#include "printf.h"


#define GPIO_LED_PIN		18

void __main_entry()
{
	/* 1. set pin-18 to output */
	gpio_funcs_set(GPIO_LED_PIN, GPIO_FUNCTION_OUT);

	/* 2. set the gpio-pin push-up */
	gpio_pullud_set(GPIO_LED_PIN, GPIO_UPDOWN_UP);

	/* 3. output low to enable the led */
	gpio_output_set(GPIO_LED_PIN, 0);

	// gpio_funcs_init();
	// miniuart_base_init(baud);

	while (1) {

	}
}
