MOD-IO2
---------- 
firmware 3.02
----------

1. Description

MOD-IO2 is a stackable development board which adds RELAYs and GPIOs to 
any of our development boards with UEXT. MOD-IO2 uses the I2C interface 
of the UEXT (typically pins 3 and 4). If you work with any of our 
development boards with UEXT connector and you need more GPIOs and/or 
RELAY outputs you can add such using connecting MOD-IO2. This board 
allows easy way to interface up to 2 relays and 7 GPIOs (analog input,
analog output, PWM, etc). MOD-IO2 is stackable and addressable, what
does this means? These boards can stack together so you can add as
many input and outputs as you want! E.g. 2-4-6-8 etc.! MOD-IO2 has 
PIC16F1503 microcontroller and the firmware is available for 
modification.

It is important to notice that the PIC16F1503 used in MOD-IO2 is
a 14-pin microcontroller. There is a lot of multiplexing. For example, 
if you are reading analog input 0 (AN0) or analog input 1 (AN1) the 
values might be not correct if you have ICSP programmer connected to 
the board at the same time – the pins that have AN0 and AN1, also have 
ICSPDAT and ICSPCLK. Furthermore, not all analog inputs are lead to the 
GPIO connector. Only AN0, AN1, AN2, AN3, and AN7 are available on the 
GPIO connector. AN7 is also used for both AN7 and PWM2 in the firmware.

The firmware might be uploaded to your MOD-IO2 via a PIC programmer or
debugger. There is a prebuilt hex in the firmware archive for easier
upgrading.

Important! MOD-IO2 is compatible with the i2c-tools package and the 
commands i2cdetect, i2cset, i2cget, i2cdump. Visit the following two
web-sites for more info:

http://www.lm-sensors.org/wiki/I2CTools
http://www.lm-sensors.org/wiki/i2cToolsDocumentation

Consider the following:

	* This file describe operation with the version3 of the firmware.
	* MOD-IO2 works only at 100kHz (or lower) I2C speed.
	* Host must support clock stretching for proper work.
	* When reading, after sending command, STOP-START condition must be
	send, not RESTART.

Make sure to check the schematic for locations and possible multiplexing
of the analog input you have chosen for your tests.
	
2. I2C Commands:		
		
	* SET_TRIS(0x01):
		Define port direction of the gpio pins. Can be INPUT or OUTPUT. 
		Note that GPIO3  can be only input with pullup always turned on. 
		This is because the alternative function is #MCLR. To set gpio
		as INPUT write 1 to the coresponding bitmask, or 0 for output.
	Example:
	--------
		START | ADDRESS | W | ACK | SET_TRIS | ACK | VALUE | ACK | STOP
				
		where:
			ADDRESS = 0x21 (this is the default address)
			SET_TRIS = 0x01
			VALUE = 0b0ddddddd - the bitmask with the coresponding 
			directions. GPIO0 - bit0, GPIO1 - bit1, etc ... 
			0x7F - all input, 0x00 - all outputs)
					
	* SET_LAT(0x02):
		Set the output level of gpio. In the bitmask 1 corespond to logical
		"1", and 0 - logical "0". Again, GPIO3 can be only input, so the 
		coresponding bit in the mask will be igrored.
	Example:
	--------
		START | ADDRESS | W | ACK | SET_LAT | ACK | VALUE | ACK | STOP
		
		where:
			ADDRESS = 0x21
			SET_LAT = 0x02
			VALUE = 0b0dddxddd	the bitmask, where bit0 is the value for 
								GPIO0, bit1 - GPIO1, etc. bit3 is 
								x - doesn't care.

	
	* GET_PORT(0x03):
		Read current level of the GPIOs. The data will be valid if the 
		GPIO is configured as INPUT. 
	Example:
	--------
		START | ADDRESS | W | ACK | GET_PORT | ACK | STOP | START | ADDRESS | R | DATA | NACK | STOP
		
		where:
			ADDRESS = 0x21 (the default address)
			GET_PORT = 0x03
			DATA = 0x0ddddddd  - the bitmask containing the GPIOs status. bit0 - GPIO0, bit1 - GPIO1, etc.
			
			
	* SET_PU(0x04):
		Turn on or off weak pullup. GPIOs must be configured as INPUTS. Note that only GPIO0 to GPIO4 have pullups, and GPIO3 is with pullup always enabled.
	Example:
	--------
		START | ADDRESS | W | ACK | SET_PU | ACK | VALUE | ACK | STOP
		
		where:
			ADDRESS = 0x21  (the default address)
			SET_PU = 0x04
			VALUE = 0b000dxddd - bit0 coresponding to GPIO0, as "1" enables the pullup and "0" - disables it.
			
		
	* GET_AN0(0x10) on GPIO0:
	  GET_AN1(0x11) on GPIO1:
	  GET_AN2(0x12) on GPIO2:
	  GET_AN6(0x13) on GPIO3:
	  GET_AN7(0x15) on GPIO5:
		Read the voltage applied on any of the GPIOs mentioned above. If GPIO is configured as output, the execution the the command will set the GPIO as input. After the applied voltage is measured, the GPIO configuration will be as INPUT. After READ the master should read 2 bytes of data: HIGH and LOW byte.
	Example:
	--------
		START | ADDRESS | W | ACK | GET_ANx | ACK | STOP | START | ADDRESS | R | DATA_L | ACK | DATA_H | NACK | STOP
		
		where:
			ADDRESS = 0x21 (the default address)
			GET_ANx = 0x10, 0x11, 0x12, 0x13 or 0x15
			DATA_L = the byte that contains the low 8 bits of the adc value
			DATA_H = the byte that contains the high bits of the adc value
			
			
	* GET_ID(0x20):
		Read the ID of the MOD-IO2. By default it must be 0x23.
	Example:
	--------
	
		START | ADDRESS | W | ACK | GET_ID | ACK | STOP | START | ADDRESS | R | ACK | DATA | NACK | STOP
		
		where:
			ADDRESS = 0x21 (the default address)
			GET_ID = 0x20
			DATA = should be 0x23

		* SET_REL(0x40):
		Turn on or off the two relays. The data is the state of the relays. Bit0 is the state of RELAY1, and 
		bit1 - RELAY2. If 1 is writen the relays is turned on, 0 is off. For example to turn on both relays
		you must write 0x03.
		
	Example:
	--------
	
		START | ADDRESS | W | ACK | SET_REL | ACK | DATA | ACK | STOP

		where:
			ADDRESS = 0x21 (the default address)
			SET_REL = 0x40
			DATA = 0x01,0x02 or 0x03

NEW COMMANDS AFTER FV 3.02

	* GET_FV(0x21):
		Read the Firmware version of the MOD-IO2.
	Example:
	--------
	
		START | ADDRESS | W | ACK | GET_FV | ACK | STOP | START | ADDRESS | R | ACK | DATA | NACK | STOP
		
		where:
			ADDRESS = 0x21 (the default address)
			GET_FV = 0x21
			DATA = Firmware version



	* SET_RELON(0x41):
		Turn on the relays. The data is the mask of afected relays. Bit0 is for RELAY1, and 
		bit1 - RELAY2. If 1 is writen the relays is afected, 0 - is not. 
		
	Example:
	--------
	
		START | ADDRESS | W | ACK | SET_RELON | ACK | DATA | ACK | STOP

		where:
			ADDRESS = 0x21 (the default address)
			SET_RELON = 0x41
			DATA = 1,2 or 3


	* SET_RELOFF(0x42):
		Turn off the relays. The data is the mask of afected relays. Bit0 is for RELAY1, and 
		bit1 - RELAY2. If 1 is writen the relays is afected, 0 - is not. 
		
	Example:
	--------
	
		START | ADDRESS | W | ACK | SET_RELOFF | ACK | DATA | ACK | STOP

		where:
			ADDRESS = 0x21 (the default address)
			SET_RELOFF = 0x42
			DATA = 1,2 or 3

	* GET_RELAY(0x43):
		Read state of relays of the MOD-IO2. The readed data is the state of the relays. Bit0 is the state of RELAY1, and 
		bit1 - RELAY2. If 1 is readed the relays is turned on, 0 is off.
	Example:
	--------
	
		START | ADDRESS | W | ACK | GET_RELAY | ACK | STOP | START | ADDRESS | R | ACK | DATA | NACK | STOP
		
		where:
			ADDRESS = 0x21 (the default address)
			GET_ID = 0x43
			READED DATA = should be 0,1 or 3

	* OPEN_PWM1(0x51):
	
		Open PWM1 and set duty cicle.
	Example:
	--------
	
		START | ADDRESS | W | ACK | OPEN_PWM1 | ACK | DATA | ACK | STOP

		where:
			ADDRESS = 0x21 (the default address)
			OPEN_PWM1 = 0x51
			DATA = 0x00..0xFF

	* OPEN_PWM2(0x52):
	
		Open PWM2 and set duty cicle.
	Example:
	--------
	
		START | ADDRESS | W | ACK | OPEN_PWM2 | ACK | DATA | ACK | STOP

		where:
			ADDRESS = 0x21 (the default address)
			OPEN_PWM1 = 0x52
			DATA = 0x00..0xFF

	* CLOSE_PWM(0x50):
	
		Close PWMx and set GPIOx as input.
	Example:
	--------
	
		START | ADDRESS | W | ACK | CLOSE_PWM | ACK | DATA | ACK | STOP

		where:
			ADDRESS = 0x21 (the default address)
			CLOSE_PWM1 = 0x50
			DATA = 1 or 2


3.	Examples:

3.1 Turning on the relays:

3.1.1 Turning all relays on:
 
	i2cset –y 2 0x21 0x40 0x03,
 
	where
 
	i2cset – command for sending data;
	-y – to skip the y/n confirmation prompt;
	2 – I2C number (usually either 1 or 2);
	0x21 – board address (0x21 should be used for writing);
	0x40 – relay operations (as seen in the README.txt);
	0x03 – should be interpreted as binary 011 – turns on both relays (0x02 would turn only second relay, 0x01 only the first, 0x00 would turn both off – 0x03 again would turn them off also);
 
	Expected result: a specific sound would occur and relays' lights would turn on.

3.1.2 turning on only the first relay:

	i2set -y 2 0x21 0x41 0x01
	where
 
	i2cset – command for sending data;
	-y – to skip the y/n confirmation prompt;
	2 – I2C number (usually either 1 or 2);
	0x21 – board address (0x21 should be used for writing);
	0x41 – relay operations (as seen in the README.txt);
	0x01 – should be interpreted as binary 011 – turns on both relays (0x02 would turn only second relay, 0x03 both);
        
	Expected result: a specific sound would occur and first relay's LED would turn on.

3.1.3 turning off only the first relay:

	i2set -y 2 0x21 0x42 0x01
	where
 
	i2cset – command for sending data;
	-y – to skip the y/n confirmation prompt;
	2 – I2C number (usually either 1 or 2);
	0x21 – board address (0x21 should be used for writing);
	0x42 – relay operations (as seen in the README.txt);
	0x01 – should be interpreted as binary 011 – turns off both relays (0x02 would turn off only second relay, 0x03 - both);
	
	Expected result: a specific sound would occur and first relay's LED would turn off.


3.1.4 reading the state of the relays:
	
	i2cset –y 2 0x21 0x43,
	and then the read command
	i2cget –y 2 0x21,
 
	where

	i2cset – command for sending data;
	-y – to skip the y/n confirmation prompt;
	2 – I2C number (usually either 1 or 2);
	0x21 – board address (0x21 should be used for writing);
	0x43 – read relay operations;

	result:	0x03 – should be interpreted as binary 011, e.g. both relays are on; the same as the command for turning the relays on. 

3.2. Read analog inputs/outputs:
 
	i2cset –y 2 0x21 0x10,
	
	and then the read command
	i2cget –y 2 0x21,
 
	where
 
	0x10 is the first analog IO;
 
	The big thing here is that to read you actually have to write (“that you would read”). Read is a combination of i2cset and i2cget!
 
	Expected results: on the terminal you would receive random and changing number or 0x00 or 0x08 or 0xFF whether you have the GPIO floating or set to 0V or set to 3.3V.
 
3.3. To read the ID of MOD-IO2
 
	i2cset –y 2 0x21 0x20,
 
	i2cget –y 2 0x21,
 
	where
 
	0x20 is the ID according to chapter 2.
 
	Expected result: on the terminal you would receive 0x23.
 
3.4. Set all analog IOs in high level

	i2cset –y 2 0x21 0x01 0x01,
 
	where 
 
	0x01 according to chapter 2, SET_TRIS is used to define port directions;
	0x01 is the high level (for low level use 0x00).
 
3.5. Read all analog IOs

	i2cset –y 2 0x21 0x01
	i2cget –y 2 0x21	

3.6 Change I2C device address. Use with CAUTION!!!

	i2cset 2 0x21 0xHH where HH is new addres in hexadimal format

    To change device address JUMPER 1 must be closed. 
	
	If you forget the number of the address you can use the modio2tool to find the address, the command and parameter would be "modio2tool -l". You can also reset the default address (0x21) with the command and parameter "modio2tool -X".

4.	Release history:

	26 MAY 2015 - Released version 3.02 of the firmware - added new features, README revised.
	13 MAY 2015 - Released version 3.01 of the firmware - fixes a bug with the internal weak pull-ups
	24 JUL 2013	- Released version 3 of the firmware
	23 OCT 2013	- Revision 2 of the README
	
5. Support:
	https://www.olimex.com/
	support@olimex.com

