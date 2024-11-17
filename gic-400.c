#include "gic-400.h"
#include "printf.h"
#include "tinylib.h"
#include "board.h"

unsigned int intnum;
struct gic400_property gic400; 


void local_irq_enable()
{
	asm volatile ("msr daifclr, #3;");
}

void local_irq_disable()
{
	asm volatile ("msr daifset, #3;");
}

void local_irq_barrier()
{
	asm volatile ("dsb sy;");
}


unsigned int get_cpu_daif() 
{
	unsigned int val;
	
	__asm__ __volatile__(
	"mrs	%0, daif \n"
	: "=r" (val)
	:
	: "memory"
	);

	return val;
}

unsigned int get_cpu_mask(void)
{
	unsigned int cpuid;
	__asm__ __volatile__(
	"mrs	%0, mpidr_el1 \n"
	: "=r" (cpuid)
	:
	: "memory"
	);
	
	return cpuid;
}


/* gic400_set_trigger_mode (irq, mode)
 * @irq: the number of irq connected to gic400
 * @mode: 0x0--level sensitive, 0x1--edge sensitive
 *
 * @funcs: set the trigger mode of the irq
 */
void gic400_set_trigger_mode(unsigned int irq, int mode)
{
	unsigned int val, shift = 4;
	unsigned int regs = irq >> (shift - 2);

	val = readl((unsigned int *) (GICD_ICFGR0_ADDR + regs));
	shift = (irq & 0xF) << 1;
	val &= ~(0x3 << shift);			//clear the data in the register
	if (mode) 
		val |= 0x2 << shift;
	
	writel(val, (unsigned int *)(GICD_ICFGR0_ADDR + regs));
}


/* gic400_enable_irq (irq)
 * @irq: the number of irq need to be enabled
 *
 * @funcs: enalbe the irq in the dispachor. the sequence of init
 *  specific irq line according to the follows:
 *   * 1. init the specific device controller
 *   * 2. find the controller related irq line: passed by parameter
 *   * 3. enable the irq in GIC distributor: GICD_EN
 *   * 4. enable the device controller irq function
 *   * 5. set the bit if PSTAE of the CPU
 */
void gic400_enable_irq(unsigned int irq) 
{
	unsigned int val = 0x1 << (irq & 0x1F);
	unsigned int regs = irq >> 5;

	writel(val, (unsigned int *)(GICD_ISEN0_ADDR + 4 * regs));
}

/* gic400_disable_irq (irq)
 * @irq: the number of irq to be disabled
 *
 * @funcs: disable the irq in the dispatchor
 */
void gic400_disable_irq(unsigned int irq)
{
	unsigned int val = 0x1 << (irq & 0x1F);
	unsigned int regs = irq >> 5;

	writel(val, (unsigned int *)(GICD_ICEN0_ADDR + 4 * regs));
}

unsigned int gic400_get_enable(unsigned int irq)
{
	unsigned int val;
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	val = readl((unsigned int *)(GICD_ISEN0_ADDR + offs));
	val &= bits;

	return val;
}



/* get, set, clear the state of pending interrupt
 *
 */
unsigned int gic400_get_pending(unsigned int irq)
{
	unsigned int val;
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	val = readl((unsigned int *) (GICD_ISPEND0_ADDR + offs));

	return val & bits;
}

void gic400_set_pending(unsigned int irq)
{
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	writel(bits, (unsigned int *) (GICD_ISPEND0_ADDR + offs));
}

void gic400_clr_pending(unsigned int irq)
{
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	writel(bits, (unsigned int *) (GICD_ICPEND0_ADDR + offs));
}



/* get, set, clear the state of the active interrupt
 *
 */
unsigned int gic400_get_active(unsigned int irq)
{
	unsigned int val;
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	val = readl((unsigned int *) (GICD_ISACT0_ADDR + offs));

	return val & bits;
}

void gic400_set_active(unsigned int irq)
{
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	writel(bits, (unsigned int *) (GICD_ISACT0_ADDR + offs));
}

void gic400_clr_active(unsigned int irq)
{
	unsigned int bits = 0x1 << (irq & 0x1F);
	unsigned int offs = irq >> 3;

	writel(bits, (unsigned int *) (GICD_ICACT0_ADDR + offs));
}



/* How to init the GIC-400?
 * 1. init the distributor
 * 1.1 get the Distributor and CPU interface base address
 * 1.2 read GICD_TYPER register, get the number of int source
 * 1.3 init the distributor according to follow steps:
 *     * 1.3.1 disable the distributor
 *     * 1.3.2 setting the SPI routing target
 *     * 1.3.3 setting the SPI trigger typers
 *     * 1.3.4 disactive and disable all interrupt source
 *     * 1.3.5 enable the distributor
 *
 * 2. init the cpu interface
 * 2.1 set the GICC_PRIMASK, setting the priority of the interrupt
 * 2.2 enable the CPU interface
 *
 */

void gic400_distributor_init(int lines) 
{
	int index;
	unsigned int val, base, offs;

	/* 1. disable the distributor send interrupt to the cpu interface */
	writel(0x00, (unsigned int *)(GIC400_BASE_ADDR + GICD_CTLR_OFFS));

	/* 2. clear the state of the gic controller
	 *   2.1 disable all avaliable interrupt in the soc
	 *   2.2 clear the active state of the interrupt
	 *   2.3 clear all the pending state interrupt
	 */
	offs = 0;
	for (index = 0; index < lines; index += 32) {
		writel(0xFFFFFFFF, (unsigned int *)(GIC400_BASE_ADDR + GICD_ICEN0_OFFS + offs));
		writel(0xFFFFFFFF, (unsigned int *)(GIC400_BASE_ADDR + GICD_ICACT0_OFFS + offs));
		writel(0xFFFFFFFF, (unsigned int *)(GIC400_BASE_ADDR + GICD_ICPEND0_OFFS + offs));
		// manage all interrupt to group 0
		writel(0x00000000, (unsigned int *)(GICD_IGRP0_ADDR + offs));

		offs += 4;
	}

	/* 3. config the property of all detect mode of interrupt */
	offs = 0x8;
	val = 0x00;			// level-sensitive
	base = GIC400_BASE_ADDR + GICD_ICFGR0_OFFS;
	for (index = 32; index < lines; index += 16) {
		writel(val, (unsigned int *) (base + offs));
		offs += 4;
	}

	/* 4. config all the priority of the interrupt 
	 *    config all the interrupt routing to processor 0 
	 */
	offs = 0x20;
	for (index = 32; index < lines; index += 4) {
		writel(0xA0A0A0A0, (unsigned int *)(GICD_IPRIO0_ADDR + offs));
		writel(0x01010101, (unsigned int *)(GICD_ITARGET0_ADDR + offs));
		offs += 4;
	}
}


void gic400_interface_init(int lines) 
{
	int pending;

	/* 1. disable CPU interface before regs configuration */
	writel(0x00, (unsigned int *)(GICC_CTLR_ADDR));

	/* 2. set the cpu interface priority filter: lowest */
	writel(0xF0, (unsigned int *)(GICC_PMR_ADDR));

	// writel(0x0, (unsigned int *)(GICC_BPR_ADDR));

	/* 4. clean all of the active interrupts */
	pending = readl((unsigned int *) (GICC_IAR_ADDR));
	pending &= 0x3FF;
	while (pending != 0x3FF) {
		writel(pending, (unsigned int *) (GICC_EOIR_ADDR));

		pending = readl((unsigned int *) (GICC_IAR_ADDR));
		pending &= 0x3FF;
	}
}


int gic400_init(void) {
	unsigned int val, lines;

	/* 1. get the number of the irq that soc supported */
	val = readl((unsigned int *)(GIC400_BASE_ADDR + GICD_TYPER_OFFS));
	lines = ((val & 0x1F) + 1) << 5;
	if (lines > 1020)
		lines = 1020;

	intnum = lines;
//	printf("The number of irq = %d, val = 0x%08x \n", lines, val);

	/* enalbe the functon of the dispator and interface */
	gic400_interface_init(lines);

	gic400_distributor_init(lines);

	/* enable group-0 forwarding from distributor to interface */
	writel(0x01, (unsigned int *)(GICD_CTLR_ADDR));		

 	/* enable forwarding from interface to cpu */
	writel(0x01, (unsigned int *)(GICC_CTLR_ADDR));

	return lines;
}


/* gic400_int_dispatch()
 *
 * @intro: when there are interrupt be triggerd, goto the interrupt
 *   vector entry and call in to this function. the sequence of this
 *   function as follows:
 *    * 1. read CPU interface register: GICC_IAR, to get the irq number
 *    * 2. call interrupt related callback functions
 *    * 3. write the irq number back to the CPU interface: GICC_EOI
 *
 * @funcs: dispatch target irq to the process function
 */
void gic400_int_dispatch() {
	unsigned int spi_num;
	unsigned int spi_id;

	local_irq_disable();

	while (1) {
		spi_num = readl((unsigned int *) (GIC400_BASE_ADDR + GICC_IAR_OFFS));
		spi_id = spi_num & 0x3FF;

		//printf("Dispatch Triggered!\n");
		miniuart_putchar('k');
		// un-except interrupt happened
		if (spi_id >= intnum) {			
			//printf("Spurious interrupt received: %d", spi_id);
			__asm__("msr daifclr, #3\n\t"
					"wfi\n\t");
			continue;
		}

		if (spi_id == TIM1_IRQ) {
			int val = readl(SYSTIMER_CTLR_ADDR);
			writel(val, SYSTIMER_CTLR_ADDR);

			val = readl(SYSTIMER_CC1_ADDR);	
			val += 0x5D0000;
			writel(val, SYSTIMER_CC1_ADDR);
			miniuart_putchar('t');
			//printf("Timer interrupt received!\n");
		}

		//printf("Unknown interrupt received!\n");
		writel(spi_num, (unsigned int *) (GIC400_BASE_ADDR + GICC_EOIR_OFFS));
		break;
	}

	local_irq_enable();
}
