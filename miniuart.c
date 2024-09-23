#include "board.h"
#include "tinylib.h"


/* configuration of the miniuart for enable/disable
 * 
 */
void miniuart_enable()
{
	unsigned int value;
	value = readl((unsigned int *) AUX_ENA_ADDR);
	value |= 0x1;
	writel(value, (unsigned int *) AUX_ENA_ADDR);
}

void miniuart_disable()
{
	unsigned int value;
	value = readl((unsigned int *) AUX_ENA_ADDR);
	value &= ~0x1;
	writel(value, (unsigned int *) AUX_ENA_ADDR);
}


int miniuart_putchar(unsigned char ch)
{
	ch &= 0xFF;

	// 1. waiting for fifo having space
	while (!trans_avaliable());

	// 2. write data to the fifo space
	writel(ch, (unsigned int *) MIUART_IO_ADDR);

	// 2. backup for using uart0
	//writel(ch, (unsigned char *) 0xFE201000);

	return ch;
}

unsigned int miniuart_getchar(void)
{
	unsigned int val;

	val = readl((unsigned int *) MIUART_IO_ADDR);
	val &= 0xFF;
	
	return val;
}

void miniuart_interrupt_enable()
{
	unsigned int val;
	val = readl((unsigned int *) MIUART_IER_ADDR);
	val = 0x3;
	writel(val, (unsigned int *) MIUART_IER_ADDR);
}

void miniuart_interrupt_disable()
{
	unsigned int val;
	val = readl((unsigned int *) MIUART_IER_ADDR);
	val &= ~0x3;
	writel(val, (unsigned int *) MIUART_IER_ADDR);
}

void miniuart_base_init(int baud)
{
	/* 0. enable the miniuart-component, 
	 *  0.1 enable read/write to the register.
	 *  0.2 disable tx/rx on the miniuart-line
	 */
	//miniuart_enable();
	writel(0x01, (unsigned int *) AUX_ENA_ADDR);
	writel(0x00, (unsigned int *) MIUART_CNTL_ADDR);

	/* 1. configuration the baudrate of miniuart */
	writel(MINIUART_BAUDVAL, (unsigned int *) MIUART_BAUD_ADDR);

	/* 2. disable interupt and baud-rate */
	writel(0x00, (unsigned int *) MIUART_IER_ADDR);

	/* 3. for miniuart */
	//clear trans & recv data fifo
	writel(0xC6, (unsigned int *) MIUART_IIR_ADDR);

	// 4. set 8-bits data format and without break
	writel(0x03, (unsigned int *) MIUART_LCR_ADDR);

	/* 5. configuration the miniuart functions
	 *	5.1: enable trans & recv function  
 	 *  5.2: disable the flow-control: RTS & CTS
	 *  5.3: pull-down the RTS-line, without used 
	 */
	writel(0x00, (unsigned int *) MIUART_MCR_ADDR);
	writel(0x03, (unsigned int *) MIUART_CNTL_ADDR);
}
