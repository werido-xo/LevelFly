# Raspberrpi 4B Bare Mental System


`Note`: The periheral controller base address is `0xFE20_0000`. 

The address stated in the BCM2711-datasheet is the legacy peripheral controller
address. can not be read/write in the 64-bit mode ( we add `arm_64bit = 1` in the
file of config.txt).


If you want to used miniuart (UART1) or UART0, the `config.txt` shoud be modify
according follows:
+ using miniuart: add 'enable_uart = 1' as newline to the config file
+ using uart0: add "dtoverlay=disable-bt" as newline to the config file
