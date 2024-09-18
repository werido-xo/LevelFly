#ifndef __BOARD_H__
#define __BOARD_H__

#include "tinylib.h"


typedef unsigned int* iomem;

/* define base address of the aux componnet */
#define MINIUART_BASE_ADDR		0x7E215000
#define GPIO_BASE_ADDR			0x7E200000


/* define aux common control register addr */
#define AUX_IRQ_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x00)
#define AUX_ENA_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x04)
#define MIUART_IO_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x40)
#define MIUART_IER_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x44)
#define MIUART_IIR_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x48)
#define MIUART_LCR_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x4c)
#define MIUART_MCR_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x50)
#define MIUART_LSR_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x54)
#define MIUART_MSR_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x58)
#define MIUART_SCR_ADDR			(iomem) (MINIUART_BASE_ADDR + 0x5c)
#define MIUART_CNTL_ADDR		(iomem) (MINIUART_BASE_ADDR + 0x60)
#define MIUART_STAT_ADDR		(iomem) (MINIUART_BASE_ADDR + 0x68)
#define MIUART_BAUD_ADDR		(iomem) (MINIUART_BASE_ADDR + 0x6c)


/* define register address in the raspberrypi */
#define GPIO_FSEL0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x00)
#define GPIO_FSEL1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x04)
#define GPIO_FSEL2_ADDR			(iomem) (GPIO_BASE_ADDR + 0x08)
#define GPIO_FSEL3_ADDR			(iomem) (GPIO_BASE_ADDR + 0x0c)
#define GPIO_FSEL4_ADDR			(iomem) (GPIO_BASE_ADDR + 0x10)
#define GPIO_FSEL5_ADDR			(iomem) (GPIO_BASE_ADDR + 0x14)
#define GPIO_SET0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x1C)
#define GPIO_SET1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x20)
#define GPIO_CLR0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x28)
#define GPIO_CLR1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x2C)
#define GPIO_LEV0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x34)
#define GPIO_LEV1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x38)
#define GPIO_EDS0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x40)
#define GPIO_EDS1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x44)
#define GPIO_REN0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x4C)
#define GPIO_REN1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x50)
#define GPIO_FEN0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x58)
#define GPIO_FEN1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x5C)
#define GPIO_HEN0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x64)
#define GPIO_HEN1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x68)
#define GPIO_LEN0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x70)
#define GPIO_LEN1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x74)
#define GPIO_AREN0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x7C)
#define GPIO_AREN1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x80)
#define GPIO_AFEN0_ADDR			(iomem) (GPIO_BASE_ADDR + 0x88)
#define GPIO_AFEN1_ADDR			(iomem) (GPIO_BASE_ADDR + 0x8C)
#define GPIO_CNTL0_ADDR			(iomem) (GPIO_BASE_ADDR + 0xE4)
#define GPIO_CNTL1_ADDR			(iomem) (GPIO_BASE_ADDR + 0xE8)
#define GPIO_CNTL2_ADDR			(iomem) (GPIO_BASE_ADDR + 0xEC)
#define GPIO_CNTL3_ADDR			(iomem) (GPIO_BASE_ADDR + 0xf0)

/* define the mux-function for gpio */
#define GPIO_FUNCTION_IN		0x00
#define GPIO_FUNCTION_OUT		0x01
#define GPIO_FUNCTION_ALT0		0x04
#define GPIO_FUNCTION_ALT1		0x05
#define GPIO_FUNCTION_ALT2		0x06
#define GPIO_FUNCTION_ALT3		0x07
#define GPIO_FUNCTION_ALT4		0x03
#define GPIO_FUNCTION_ALT5		0x02	

/* define macro of gpio pull-up and pull-down */
#define GPIO_UPDOWN_NONE		0x00
#define GPIO_UPDOWN_UP			0x01
#define GPIO_UPDOWN_DOWN		0x02
#define GPIO_UPDOWN_RSV			0x03


/* define miniuart related funcs */
#define MINIUART_BAUDRATE		115200
#define SYSTEM_FREQ				250000000
#define MINIUART_BAUDVAL		SYSTEM_FREQ/(8*MINIUART_BAUDRATE) - 1

int miniuart_init(void);
int miniuart_putchar(unsigned char ch);


/* define gpio-related funcs */
void gpio_funcs_set(u32 pin, u32 alt);
void gpio_output_set(u32 pin, u32 level);
unsigned int gpio_level_read(u32 pin);
void gpio_pullud_set(u32 pin, u32 up_down);

void gpio_funcs_init(void);


#endif
