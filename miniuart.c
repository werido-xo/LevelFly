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

int trans_avaliable()
{


}

int recv_avaliable()
{


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

int miniuart_base_init(int baud)
{
	unsigned int val;

	miniuart_disable();

	/* 1. configuration the baudrate of miniuart */
	writel(MINIUART_BAUDVAL, (unsigned int *) MIUART_BAUD_ADDR);

	/* 2. disable interupt and baud-rate */
	miniuart_interrupt_disable();

	/* 3. for miniuart */
	//clear trans & recv data fifo
	val = readl((unsigned int *) MIUART_IIR_ADDR);
	val |= 0x6;
	writel(val, (unsigned int *) MIUART_IIR_ADDR);

	// 4. set 8-bits data format and without break
	writel(0x1, (unsigned int *) MIUART_LCR_ADDR);


	/* 5. configuration the miniuart functions
	 *	5.1: enable trans & recv function  
 	 *  5.2: disable the flow-control: RTS & CTS
	 */
	val = 0xF;
	writel(val, (unsigned int *) MIUART_CNTL_ADDR);

	miniuart_enable();
}
