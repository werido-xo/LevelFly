#ifndef __TINYLIB_H__
#define __TINYLIB_H__

/* define the pointer don't refers to data */
#ifdef __CHECKER__
#define __force __attribute__((force))
#define __iomem __attribute__((noderef, address_space(2)))
#else
#define __force
#define __iomem
#endif

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;


/* u32 readl(ptr)
 * @ptr: the address of the register
 *
 * @ret: the value stored in the register
 */
static inline u32 readl(const volatile void __iomem *ptr)
{
	return *(const volatile u32 __force *) ptr;
}

/* void writel(value, ptr)
 * @ptr: the address of the register
 * @val: the value need to be write to the register
 *
 */
static inline void writel(unsigned int value, volatile void __iomem *ptr)
{
	*(volatile u32 __force *) ptr = value;
}

#endif
