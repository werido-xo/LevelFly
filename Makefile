
# 1. define the toolchains for the target
TOOLCHAIN_PATH ?= /opt/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin
# TOOLCHAIN_PATH ?= /opt/gcc-linaro-11.3.1-2022.06-x86_64_aarch64-linux-gnu/bin
CROSS_COMPILE := $(TOOLCHAIN_PATH)/aarch64-none-linux-gnu
#CROSS_COMPILE := $(TOOLCHAIN_PATH)/aarch64-linux-gnu


# 2. compile parameters
SRC_FLAGS := -Wall -O2 -fno-builtin -ffreestanding -nostdlib -Iinclude
ASM_FLAGS := -Iinclude


# 3. define the dependency files of the target
BUILD_DIRS := $(shell pwd)
# SRC_FILES := $(wildcard $(BUILD_DIRS)/*.c)
SRC_FILES := main.c gpio.c miniuart.c printf.c gic-400.c
# ASM_FILES := $(wildcard $(BUILD_DIRS)/*.S) 
ASM_FILES := init.S 

SRC_OBJS = $(patsubst %.c, %.o, $(SRC_FILES))
ASM_OBJS = $(patsubst %.S, %.o, $(ASM_FILES))

LINK_FILE = $(BUILD_DIRS)/levelfly.lds



levelfly: $(ASM_OBJS) $(SRC_OBJS) 
	$(CROSS_COMPILE)-ld -T $(LINK_FILE) -o levelfly.elf $^
	$(CROSS_COMPILE)-objcopy -O binary levelfly.elf levelfly.bin
	$(CROSS_COMPILE)-objdump -D levelfly.elf > levelfly.dis

%.o : %.S
	$(CROSS_COMPILE)-gcc $(ASM_FLAGS) -MMD -c -o $@ $<

%.o : %.c
	$(CROSS_COMPILE)-gcc $(SRC_FLAGS) -MMD -c  -o $@ $< 

clean:
	rm -f *.o *.d *.elf *.bin *.dis 
