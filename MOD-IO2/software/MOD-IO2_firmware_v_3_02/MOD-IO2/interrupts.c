/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>             /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"
#include "OLIMEX.h"


/******************************************************************************/
/* Interrupt Routines                                                         */

/******************************************************************************/
void interrupt
isr(void)
{
	if (SSP1IF) {
		unsigned char status;
		unsigned char foo;
		unsigned int adc;
		int i;

		if (SSPSTAT & STOP_C) {
			switch (DATA_BUFFER[0]) {
			case SET_TRIS:
				CommandSetTris(DATA_BUFFER[1]);
				break;
			case SET_LAT:
				CommandSetLat(DATA_BUFFER[1]);
				break;
			case SET_PU:
				CommandSetPullUps(DATA_BUFFER[1]);
				break;
			case SET_ADDRESS:
				CommandSetAddress(DATA_BUFFER[1]);
				break;
			case SET_REL:
				CommandSetRelay(DATA_BUFFER[1]);
				break;
            case SET_RELON:
                CommandSetOnX(DATA_BUFFER[1]);
                break;    
            case SET_RELOFF:
                CommandSetOffX(DATA_BUFFER[1]);
                break;    
        	case GET_PORT:
				DATA_OUT[0] = CommandGetPort();
				break;
            case GET_REL:    
                DATA_OUT[0] = REL2*2 + REL1;
                break;
			case GET_LAT:
				DATA_OUT[0] = CommandGetLat();
				break;
			case GET_TRIS:
				DATA_OUT[0] = CommandGetTris();
				break;
			case GET_AN_GPIO0:
				adc = CommandGetAnalog(0);
				DATA_OUT[0] = adc & 0xFF;
				DATA_OUT[1] = (adc >> 8) & 0xFF;
				break;
			case GET_AN_GPIO1:
				adc = CommandGetAnalog(1);
				DATA_OUT[0] = adc & 0xFF;
				DATA_OUT[1] = (adc >> 8) & 0xFF;
				break;
			case GET_AN_GPIO2:
				adc = CommandGetAnalog(2);
				DATA_OUT[0] = adc & 0xFF;
				DATA_OUT[1] = (adc >> 8) & 0xFF;
				break;
			case GET_AN_GPIO3:
				adc = CommandGetAnalog(3);
				DATA_OUT[0] = adc & 0xFF;
				DATA_OUT[1] = (adc >> 8) & 0xFF;
				break;
			case GET_AN_GPIO5:
				adc = CommandGetAnalog(7);
				DATA_OUT[0] = adc & 0xFF;
				DATA_OUT[1] = (adc >> 8) & 0xFF;
				break;
			case GET_ID:
				DATA_OUT[0] = IO2_ID;
				break;
            case GET_FV:
                DATA_OUT[0] = VERSION;
                break;
            case SET_PWM1:
                 SetPWM1(DATA_BUFFER[1]);
                 break;
            case SET_PWM2:
                 SetPWM2(DATA_BUFFER[1]);
                 break;        
            case PWM_OFF: 
                ClosePWM(DATA_BUFFER[1]);
                break;
  			default:
				break;
			}
		} else {
			status = SSPSTAT & 0x2D; //DA | P | S | R/W | x | BF
			switch (status) {
				//STATE 1
			case STATE1:
			{
				foo = SSPBUF;
				DATA_INDEX = 0;
				for (i = 0; i < MAX_BUFFER_SIZE; i++)
					DATA_BUFFER[i] = 0;
				if (SEN)
					CKP = 1;
			}
				break;
				//STATE 2
			case STATE2:
			{
				DATA_BUFFER[DATA_INDEX++] = SSPBUF;
				if (DATA_INDEX >= MAX_BUFFER_SIZE)
					DATA_INDEX = 0;
				if (SEN)
					CKP = 1;
			}
				break;
				//STATE 3
			case STATE3:
			{
				foo = SSPBUF;
				while (BF);
				SSPBUF = DATA_OUT[0];
				if (SEN)
					CKP = 1;
			}
				break;
				//STATE 4
			case STATE4:
			{
				foo = SSPBUF;
				while (BF);
				SSPBUF = DATA_OUT[1];
				if (SEN)
					CKP = 1;
			}
				break;
				//STATE 5
			case STATE5:
				break;
			default:
				break;
			}
		}
	}
	SSP1IF = 0;

} 