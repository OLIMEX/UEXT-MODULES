*** SUPPORT FILES FOR THE MOD-LCD3310 ***

These are generic support files with basic routines for interfacing the MOD-LCD3310 board. There are two versions provided:
	- Hardware SPI for processors that have such a module
	- Software SPI implemented by toggling SPI bus pins for processors that do not have such a module or the module is occupied by something else.
	
	The files provided are taken from the demo project for the LPC-P1227 board but can be easily configured to be used by any MCU and any C compiler by editing only the section marked with:
	
/* TO IMPLEMENT YOUR VERSION OF THE DRIVER YOU'LL HAVE TO EDIT THIS SECTION ONLY */

...

/* END OF SECTION */

In order to use you should include only one C file and one header file to your project, simple huh ;)

Last edit:
27 June 2011
