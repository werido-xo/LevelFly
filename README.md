# Raspberrpi 4B Bare Mental System
*author*: weirdo-xo
*data*: 2024/09/23
*description*: This project aim to design a simple bare metal system for raspberrypi 4b. Through this project, we can learing the exception level, system-call, and other system-related acknowledge.


## 1. How to access register on Raspberry-Pi
`Note`: The periheral controller base address is `0xFE20_0000`. 

The address stated in the BCM2711-datasheet is the legacy peripheral controller
address. It can not be read/write in the 64-bit mode ( we add `arm_64bit = 1` in the
file of config.txt).

> [!TIP}
> Take care of the GIC-400 distributor register offset is 0x1001, and the CPU interface register offset is 0x2000. Therefore, don't forgot to add this offset to the related register before access.


## 2. How to use uart-console on your board
If you want to used miniuart (UART1) or UART0, the `config.txt` shoud be modify
according follows:
+ using miniuart: add 'enable_uart = 1' as newline to the config file
+ using uart0: add "dtoverlay=disable-bt" as newline to the config file

## 3. Fix bug after update fireware of Rasspberry-pi
When I update fireware of raspberrypi on eeprom, i found that the function `prinf()` called abnormal. That is because the new fireware disable support for neon/fpu module, which need our enable it manually.

ARMv8 Website: [neon](https://developer.arm.com/documentation/ka006062/latest/)

**Add New Code to init.S**
```assemble

	MSR CPTR_EL2, XZR ; Instructions are not trapped below EL2

	MOV X0, #0x00300000 ; No trap to all NEON & FP instructions
	MSR CPACR_EL1, X0

```
