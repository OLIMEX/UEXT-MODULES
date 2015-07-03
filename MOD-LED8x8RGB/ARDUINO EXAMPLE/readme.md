Library with header files and three examples suitable for:

ARDUINO COMPATIBLE BOARD AND MOD-LED8x8RGB

In order to get the hardware working you have to:

Connect the MOD-LCD8x8RGB to your board according to the names of the signals. You might need to use wires for some boards. A typical connection between one and more than one MOD-LED8x8RGB might be seen in this blog post: https://olimex.wordpress.com/2013/06/21/new-product-mod-led8x8rgb-stackable-rgb-led-matrix/

You would need a source of 5V voltage and a GND to power the board. Connect those to EXT_IN.VCC and EXT_IN.GND. For the communications you would need the SCK and the MOSI line from the hardware SPI interface of your board. Locate and connect those to EXT_IN.DATA and EXT_IN.SCK. Finally, use a free digitial IO pin to connect to EXT_IN.LATCH (by default we have used pin 13). 

Note: the MOD-LED8x8RGB works at 5V of voltage. 3.3V will not be sufficient for powering!

In order to get the software working you have to:

1. Download the files (one by one or the whole folder containing this README.md) and keep the directory structure as in this repository.
1. Close Arduino IDE if it is running.
2. Copy the whole folder that you downloaded (both the headers and the examples folder in it) to the libraries folder of your Arduino IDE (ex. "..\arduino-x.x.x\libraries").
3. Start Arduino IDE.
4. Select the board and serial port (check this one in your Windows Device Manager --> Ports (COM & LPT) section).
5. Go to File -> Example -> name of the folder containing the headers and the examples -> select one of the examples.
6. If EXT_IN.LATCH is not connected to pin 13 of your ARDUINO board, then edit the header file "lcd8x8rgb.h" with a text editor. The text that needs editing is "const char chipSelectPin = 13;". Change 13 to the ARDUINO PIN that you have used instead. Save the header and close.
7. In Arduino IDE compile and upload

Note: if you are using more than one board you need to edit the header file "lcd8x8rgb.h". There are two variables called "bigX" and "bigY" that are used to define the shape of the connected boards. Edit this part:

define bigX 1                  // Number of MOD-LED8x8RGB in columns

define bigY 1                  // Number of MOD-LED8x8RGB in rows
