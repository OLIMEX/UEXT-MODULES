Sample demo (1.1) for STM32-P103 revision C with MOD-LCD3310 revision A connected on the UEXT.
This version of the demo gives you an option to control the pins of LCD as both GPIO and SPI.

The example is build and tested with IDE - IAR for ARM 6.30.7v.
The workspace you need to open is located: "<extract directory>\STM32-P103_UEXT_Demo\Project\STM32-P103_MOD-3310_Demo.eww".
To select your communication interface (GPIO/SPI) choose your configuration from the drop-down menu: MOD-LCD3310_GPIO or MOD-LCD3310_SPI.

In order to work for YOUR OWN BOARD you have to edit files:
0) lcd3310_GPIO.c or lcd3310_SPI.c
This is in case you are using different processor so many of the registers for GPIO or SPI may be different. According to the README.txt in the MOD-LCD3310 library directory you have to edit only the part marked with the comments:
/* TO IMPLEMENT YOUR VERSION OF THE DRIVER YOU'LL HAVE TO EDIT THIS SECTION ONLY */
/* END OF SECTION */

1) stm3210b_eval.h
This is specific for any board. Here it is described where are placed each of the five controller pins: (RST, CD, CS, MOSI, SCK).
You can check for the comment LCD3310 to see where is the description of the pins.

If everything is fine as a result of execution on the LCD should be displayed the following message and the STAT LED blinking:
*** OLIMEX ***
  STM32-P103
  demo  for
  MOD-LCD3310
  using <selected configuration>
  interface

At first rows 0,2 and 4 are with light background and dark symbols, and the rows 1,3 and 5 are inverted: dark background with light symbols.
To switch the inversion (rows 0, 2, 4 -> inverted; rows 1, 3, 5 normal) press the button.
