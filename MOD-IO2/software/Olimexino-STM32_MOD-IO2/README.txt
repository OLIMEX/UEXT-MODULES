This is example demo for Olimex board Olimexino-STM32 rev.E connected via UEXT cable to MOD-IO2 rev.B.

The project is compiled and tested with Maple 0.0.12

In order to work you have to copy the MOD_IO2_Library located in the root directory to the "libraries" directory of your Maple IDE.


When you compile and program the board it should initialize I2C communication between Olimexino-STM32 and the slave module.
The address of the slave is selected in the source code of the example line 18:
--------------------------------------------------
		#define  MOD_IO2_ADDRESS  0x21
--------------------------------------------------
This address depends on the firmware of the MOD-IO2. So take care of it if you decide to change the firmware of MOD-IO2 since the address might be different.

The same way you can change SCL and SDA pins of I2C interface (line 19-20):
--------------------------------------------------
				#define  SCL 29
				#define  SDA 30
--------------------------------------------------
The effect of the program is that when you click the USER button of the host board new value of the relays' state should be sent to the MOD and so the relays on the slave will be toggled.

The procedure of sending data is this:
Start --> Address --> Command code --> Data --> Stop
Sending of each of them is included in the library method WriteSingleIadr (you can see the code in the MOD-IO2.cpp file).
Start and Stop bits are standard for the I2C protocol.
Address value is defined in the top of your source code (as it was described above) and it is initialized in the constructor when the object of the class is defined.
Command codes are predefined values for the firmware (macros are defined in the header file MOD-IO2.h) with specific actions.
Data is a value that the user wants to send to the slave.
For more details you can check "MOD-IO2 README.txt" where you can find the specific for the MOD-IO2 command codes and examples of the sending data via I2C protocol.

2013.10.28