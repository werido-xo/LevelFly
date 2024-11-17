#ifndef __GIC400_H__
#define __GIC400_H__


#define GIC400_BASE_ADDR	0xFF840000

/* GIC-V2 Distributor Register Maps */
#define GICD_CTLR_OFFS		0x1000		// gic dispatch control register
#define GICD_TYPER_OFFS		0x1004		// gic interrupt control typer register
#define GICD_IIDR_OFFS		0x1008		// distributor implement identification
#define GICD_IGRP0_OFFS		0x1080		// interrupt group register
#define GICD_ISEN0_OFFS		0x1100		// interrupt enable register
#define GICD_ICEN0_OFFS		0x1180		// interrupt clear register
#define GICD_ISPEND0_OFFS	0x1200		// interrupt pending set register
#define GICD_ICPEND0_OFFS	0x1280		// interrupt pending clear register
#define GICD_ISACT0_OFFS	0x1300		// interrupt active set register
#define GICD_ICACT0_OFFS	0x1380		// interrupt active clear register
#define GICD_IPRIO0_OFFS	0x1400		// interrupt priority set register
#define GICD_ITARGET0_OFFS	0x1800		// interrupt processor target register
#define GICD_ICFGR0_OFFS	0x1C00		// interrupt configuration register
#define GICD_PPISR_OFFS		0x1D00		// private peripheral int status register
#define GICD_SPISR0_OFFS	0x1D04		// shared peripheral int status register
#define GICD_SGIR_OFFS		0x1F00		// software generated int register
#define GICD_SGICPEND0_OFFS	0x1F10		// SGI clear-pending register
#define GICD_SGISPEND0_OFFS	0x1F20		// SGI set-pending register
// #define GICD_PIDR4_OFFS		0x1FD0		// peripheral ID4 register
// #define GICD_PIDR5_OFFS		0x1FD4		// peripheral ID4 register
// #define GICD_PIDR6_OFFS		0x1FD8		// peripheral ID4 register
// #define GICD_PIDR7_OFFS		0x1FDC		// peripheral ID4 register
// #define GICD_PIDR0_OFFS		0x1FE0		// peripheral ID4 register
// #define GICD_PIDR1_OFFS		0x1FE4		// peripheral ID4 register
// #define GICD_PIDR2_OFFS		0x1FE8		// peripheral ID4 register
// #define GICD_PIDR3_OFFS		0x1FEC		// peripheral ID4 register
// #define GICD_CIDR0_OFFS		0x1FF0		// peripheral ID4 register
// #define GICD_CIDR1_OFFS		0x1FF4		// peripheral ID4 register
// #define GICD_CIDR2_OFFS		0x1FF8		// peripheral ID4 register
// #define GICD_CIDR3_OFFS		0x1FFC		// peripheral ID4 register



#define GICC_CTLR_OFFS		0x2000		// cpu interface control register
#define GICC_PMR_OFFS		0x2004		// interrupt priority mask register
#define GICC_BPR_OFFS		0x2008		// binary pointer register
#define GICC_IAR_OFFS		0x200c		// interrupt acknowlege register
#define GICC_EOIR_OFFS		0x2010		// end of interrupt register
#define GICC_RPR_OFFS		0x2014		// running priority register
#define GICC_HPPIR_OFFS		0x2018		// highest priority pending int register
#define GICC_ABPR_OFFS		0x201c		// aliased binary pointer register
#define GICC_AIAR_OFFS		0x2020		// aliased interrupt acknowledge register
#define GICC_AEOIR_OFFS		0x2024		// aliased end of interrupt register
#define GICC_AHPPIR_OFFS	0x2028		// aliased highest priority pendding int register

#define GICC_APR0_OFFS		0x20D0		// active priority register
#define GICC_NSAPR0_OFFS	0x20E0		// no-secure active priority register
#define GICC_IIDR_OFFS		0x20FC		// cpu interface identification register
#define GICC_DIR_OFFS		0x3000		// deactivate interrupt register


/* GIC-V2 Distributor Register Maps */
#define GICD_CTLR_ADDR			(GIC400_BASE_ADDR + GICD_CTLR_OFFS)		
#define GICD_TYPER_ADDR			(GIC400_BASE_ADDR + GICD_TYPER_OFFS)	
#define GICD_IIDR_ADDR			(GIC400_BASE_ADDR + GICD_IIDR_OFFS)		
#define GICD_IGRP0_ADDR			(GIC400_BASE_ADDR + GICD_IGRP0_OFFS)	
#define GICD_ISEN0_ADDR			(GIC400_BASE_ADDR + GICD_ISEN0_OFFS)		
#define GICD_ICEN0_ADDR			(GIC400_BASE_ADDR + GICD_ICEN0_OFFS)		
#define GICD_ISPEND0_ADDR		(GIC400_BASE_ADDR + GICD_ISPEND0_OFFS)	
#define GICD_ICPEND0_ADDR		(GIC400_BASE_ADDR + GICD_ICPEND0_OFFS)		
#define GICD_ISACT0_ADDR		(GIC400_BASE_ADDR + GICD_ISACT0_OFFS)		
#define GICD_ICACT0_ADDR		(GIC400_BASE_ADDR + GICD_ICACT0_OFFS)		
#define GICD_IPRIO0_ADDR		(GIC400_BASE_ADDR + GICD_IPRIO0_OFFS)	
#define GICD_ITARGET0_ADDR		(GIC400_BASE_ADDR + GICD_ITARGET0_OFFS)		
#define GICD_ICFGR0_ADDR		(GIC400_BASE_ADDR + GICD_ICFGR0_OFFS)	
#define GICD_PPISR_ADDR			(GIC400_BASE_ADDR + GICD_PPISR_OFFS)		
#define GICD_SPISR0_ADDR		(GIC400_BASE_ADDR + GICD_SPISR0_OFFS)	
#define GICD_SGIR_ADDR			(GIC400_BASE_ADDR + GICD_SGIR_OFFS)	
#define GICD_SGICPEND0_ADDR		(GIC400_BASE_ADDR + GICD_SGICPEND0_OFFS)
#define GICD_SGISPEND0_ADDR		(GIC400_BASE_ADDR + GICD_SGISPEND0_OFFS)		


#define GICC_CTLR_ADDR		(GIC400_BASE_ADDR + GICC_CTLR_OFFS)	
#define GICC_PMR_ADDR		(GIC400_BASE_ADDR + GICC_PMR_OFFS)
#define GICC_BPR_ADDR		(GIC400_BASE_ADDR + GICC_BPR_OFFS)
#define GICC_IAR_ADDR		(GIC400_BASE_ADDR + GICC_IAR_OFFS)
#define GICC_EOIR_ADDR		(GIC400_BASE_ADDR + GICC_EOIR_OFFS)
#define GICC_RPR_ADDR		(GIC400_BASE_ADDR + GICC_RPR_OFFS)
#define GICC_HPPIR_ADDR		(GIC400_BASE_ADDR + GICC_HPPIR_OFFS)
#define GICC_ABPR_ADDR		(GIC400_BASE_ADDR + GICC_ABPR_OFFS)
#define GICC_AIAR_ADDR		(GIC400_BASE_ADDR + GICC_AIAR_OFFS)
#define GICC_AEOIR_ADDR		(GIC400_BASE_ADDR + GICC_AEOIR_OFFS)	
#define GICC_AHPPIR_ADDR	(GIC400_BASE_ADDR + GICC_AHPPIR_OFFS)	

#define GICC_APR0_ADDR		(GIC400_BASE_ADDR + GICC_APR0_OFFS)
#define GICC_NSAPR0_ADDR	(GIC400_BASE_ADDR + GICC_NSAPR0_OFFS)
#define GICC_IIDR_ADDR		(GIC400_BASE_ADDR + GICC_IIDR_OFFS)
#define GICC_DIR_ADDR		(GIC400_BASE_ADDR + GICC_DIR_OFFS)



enum IRQ_TABLE {
	TIM0_IRQ = 96, 
	TIM1_IRQ, 
	TIM2_IRQ, 
	TIM3_IRQ,

	MCORE_SYNC0 = 108,
	MCORE_SYNC1,
	MCORE_SYNC2,
	MCOER_SYNC3,
	
	GPIO0_IRQ = 145,
	GPIO1_IRQ,
	GPIO2_IRQ, 
	GPIO3_IRQ,

	IIC_IRQ 	= 149,
	SPI_IRQ 	= 150,
	IIS_IRQ 	= 151,
	SDHOST_IRQ 	= 152,
	PL01_UART	= 153
};


struct gic400_property {	
	int line_num;
	int security_ext;
};

void local_irq_enable();
void local_irq_disable();
void local_irq_barrier();

unsigned int get_cpu_daif();
unsigned int get_cpu_mask();


int gic400_init(void);

void gic400_set_trigger_mode(unsigned int irq, int mode);
unsigned int gic400_get_pending(unsigned int irq);
void gic400_set_pending(unsigned int irq);
void gic400_clr_pending(unsigned int irq);

unsigned int gic400_get_active(unsigned int irq);
void gic400_set_active(unsigned int irq);
void gic400_clr_active(unsigned int irq);

void gic400_enable_irq(unsigned int irq);
void gic400_disable_irq(unsigned int irq);
unsigned int gic400_get_enable(unsigned int irq);
#endif
