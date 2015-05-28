Sample demo for OLIMEXINO-STM32 revision E with MOD-LCD3310 revision A connected on the UEXT.
This version of the demo gives you an option to control the pins of LCD as hardware SPI function.

The example is build and tested with IDE - Maple 0.0.12.
In order to work you have to copy the directory "LCD3310_SPI" in the library directory of Maple (for example <install directory>\Maple 0.0.12\libraries\LCD3310_SPI").
After that open the project located in: "<extract directory>\Olimexino-STM32_MOD_LCD3310_SPI\Olimexino_STM32_Demo\Olimexino_STM32_Demo.pde"
If you are using another hardware and your SPI pins are on different position or you want to use another SPI you need to edit the file "Olimexino-STM32.h" in the BoardHardware directory.

It should initialize the hardware SPI and the LCD display and visualize the following text:
*** OLIMEX ***
   OLIMEXINO
    STM32 +
  MOD-LCD3310
  using SPI
  interface

Rows 0,2 and 4 are with light background and dark symbols, and the rows 1,3 and 5 are inverted: dark background with light symbols.

Last update: 2013.09.30
