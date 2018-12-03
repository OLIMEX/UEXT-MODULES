/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>            /* HiTech General Includes */
#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
	OSCCONbits.IRCF = 0b1111;
	OSCCONbits.SCS  = 0b11;

	while(!OSCSTATbits.HFIOFR);
}
