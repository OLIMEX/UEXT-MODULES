/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>             /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "i2c.h"
#include "OLIMEX.h"

/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/


void InitApp(void)
{
	InitGPIO();
	InitAddress();
	InitI2C();
	InitInterupts();
}

void InitI2C(void)
{
	SSPCON2 = 0x01; // Enable clock streching
	SSPCON3 = 0x40; // Enable interrupts on START and STOP
	SSPSTAT = 0x80; // Slew rate for 100kHz
	SSPADD = ADDRESS << 1;
	SSPCON1 = 0x3E;
}

void InitGPIO(void)
{
	ANSELC = 0x00;
	ANSELA = 0x00;

	/* Make all inputs */
	TRISA = 0xFF;
	TRISC = 0xFF;

	/* Clear LAT registers */
	LATA = 0x00;
	LATC = 0x00;

	SCL_TRIS = 1;
	SDA_TRIS = 1;
	SCL_LAT = 0;
	SDA_LAT = 0;

	REL1_TRIS = 0;
	REL2_TRIS = 0;
	REL1 = 0;
	REL2 = 0;

	OPTION_REGbits.nWPUEN = 0;
	WPUAbits.WPUA = 0x20;
	JMP_TRIS = 1;
	JMP_LAT = 0;
}

void InitInterupts(void)
{
	PIR1bits.SSP1IF = 0;
	PIE1bits.SSP1IE = 1;
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;

}

void InitAddress(void)
{
	unsigned int addr;
	addr = ReadFlash(MEMORY_ADDRESS);
	if ((addr & 0xFF) == 0xFF)
		ADDRESS = DEFAULT_ADDRESS;
	else
		ADDRESS = addr & 0xFF;
}

unsigned int ReadFlash(unsigned int address)
{
	unsigned int data = 0;
	PMADRL = address & 0x00FF;
	address >>= 8;
	PMADRH = address & 0x00FF;
	PMCON1bits.CFGS = 0;
	PMCON1bits.RD = 1;
	Nop();
	Nop();

	data = PMDATH;
	data <<= 8;
	data |= PMDATL;
	return data;
}

void EraseFlash(unsigned int address)
{
	PMADRL = address & 0x00FF;
	address >>= 8;
	PMADRH = address & 0x00FF;
	PMCON1bits.CFGS = 0;
	PMCON1bits.FREE = 1;
	PMCON1bits.WREN = 1;
	UnlockFlash();
	PMCON1bits.WREN = 0;
}

void UnlockFlash(void)
{
	PMCON2 = 0x55;
	PMCON2 = 0xAA;
	PMCON1bits.WR = 1;
	Nop();
	Nop();
}

void WriteFlash(unsigned int data, unsigned int address)
{
	PMCON1bits.CFGS = 0;
	PMADRL = address & 0x00FF;
	address >>= 8;
	PMADRH = address & 0x00FF;
	PMCON1bits.FREE = 0;
	PMCON1bits.LWLO = 1;
	PMCON1bits.WREN = 1;
	PMDATL = data & 0x00FF;
	data >>= 8;
	PMDATH = data & 0x00FF;
	PMCON1bits.LWLO = 0;
	UnlockFlash();
	PMCON1bits.WREN = 0;
}

void CommandSetTris(unsigned char data)
{
	GPIO0_TRIS = data & 0x01;
	data >>= 1;
	GPIO1_TRIS = data & 0x01;
	data >>= 1;
	GPIO2_TRIS = data & 0x01;
	data >>= 1;
	GPIO3_TRIS = 1;
	data >>= 1;
	GPIO4_TRIS = data & 0x01;
	data >>= 1;
	GPIO5_TRIS = data & 0x01;
	data >>= 1;
	GPIO6_TRIS = data & 0x01;

}

void CommandSetLat(unsigned char data)
{
	GPIO0_LAT = data & 0x01;
	data >>= 1;
	GPIO1_LAT = data & 0x01;
	data >>= 1;
	GPIO2_LAT = data & 0x01;
	data >>= 1;
	//	GPIO3_LAT = command & 0x01;	GPIO3 is ALWAYS INPUT!!!
	data >>= 1;
	GPIO4_LAT = data & 0x01;
	data >>= 1;
	GPIO5_LAT = data & 0x01;
	data >>= 1;
	GPIO6_LAT = data & 0x01;

}

unsigned char CommandGetPort()
{
	unsigned char data = 0;

	data = GPIO6_PORT & 0x01;
	data <<= 1;
	data |= GPIO5_PORT & 0x01;
	data <<= 1;
	data |= GPIO4_PORT & 0x01;
	data <<= 1;
	data |= GPIO3_PORT & 0x01;
	data <<= 1;
	data |= GPIO2_PORT & 0x01;
	data <<= 1;
	data |= GPIO1_PORT & 0x01;
	data <<= 1;
	data |= GPIO0_PORT & 0x01;

	return data;
}

void CommandSetRelay(unsigned char data)
{
	REL1 = data & 0x01;
	data >>= 1;
	REL2 = data & 0x01;
	data >>= 1;
}

void CommandSetOnX(unsigned char data)
{
	if (data & 0x01) REL1 = 1;
	if (data & 0x02) REL2 = 1;
}
void CommandSetOffX(unsigned char data)
{
	if (data & 0x01) REL1 = 0;
	if (data & 0x02) REL2 = 0;
}

void CommandSetAddress(unsigned char addr)
{
	if (!JMP_PORT) {
		EraseFlash(MEMORY_ADDRESS);
		WriteFlash(addr, MEMORY_ADDRESS);
		ADDRESS = addr;
		SSPCON1bits.SSPEN = 0;
		SSPCON2 = 0x01;
		SSPCON3 = 0x40;
		SSPSTAT = 0x00;
		SSPADD = ADDRESS << 1;
		SSPCON1 = 0x3E;
	}
}

void CommandSetPullUps(unsigned char data)
{
	WPUAbits.WPUA0 = data & 0x01;
	data >>= 1;
	WPUAbits.WPUA1 = data & 0x01;
	data >>= 1;
	WPUAbits.WPUA2 = data & 0x01;
	data >>= 1;
	WPUAbits.WPUA3 = data & 0x01;
	data >>= 1;
	WPUAbits.WPUA5 = data & 0x01;
	data >>= 1;

}

unsigned char CommandGetTris(void)
{
	unsigned char data = 0;
	data |= GPIO6_TRIS;
	data <<= 1;
	data |= GPIO5_TRIS;
	data <<= 1;
	data |= GPIO4_TRIS;
	data <<= 1;
	data |= GPIO3_TRIS;
	data <<= 1;
	data |= GPIO2_TRIS;
	data <<= 1;
	data |= GPIO1_TRIS;
	data <<= 1;
	data |= GPIO0_TRIS;

	return data;
}

unsigned char CommandGetLat(void)
{
	unsigned char data = 0;
	data |= GPIO6_LAT;
	data <<= 1;
	data |= GPIO5_LAT;
	data <<= 1;
	data |= 0; // Note: GPIO4 can't be output!
	data <<= 1;
	data |= GPIO3_LAT;
	data <<= 1;
	data |= GPIO2_LAT;
	data <<= 1;
	data |= GPIO1_LAT;
	data <<= 1;
	data |= GPIO0_LAT;

	return data;
}

unsigned int CommandGetAnalog(unsigned char channel)
{
	unsigned int data = 0;
	unsigned char count = 0;

	// Configure port
	switch (channel) {
	case 0:
		GPIO0_TRIS = 1;
		ANSELAbits.ANSA0 = 1;
		break;
	case 1:
		GPIO1_TRIS = 1;
		ANSELAbits.ANSA1 = 1;
		break;
	case 2:
		GPIO2_TRIS = 1;
		ANSELAbits.ANSA2 = 1;
		break;
	case 3:
		GPIO3_TRIS = 1;
		ANSELAbits.ANSA4 = 1;
		break;
	case 7:
		GPIO5_TRIS = 1;
		ANSELCbits.ANSC3 = 1;
		break;
	default:
		break;
	}

	// Configure the ADC modules
	ADCON1bits.ADCS = 0x00;		// Fosc/2
	ADCON1bits.ADPREF = 0x00;	// Vref+
	ADCON1bits.ADFM = 0x01;		// Right justify
	ADCON0bits.CHS = channel;	// Select input channel
	ADCON0bits.ADON = 0x01;		// Turn on the ADC module


	/* Wait aprox 20us aquisition time */
	for(count = 0; count < 5; count++)
		asm("NOP");
	ADCON0bits.GO_nDONE = 1;	// Start conversation
	while(ADCON0bits.GO_nDONE);	// Wait conversation to complete

	data = ADRESH;
	data <<= 8;
	data |= ADRESL;

	// Disable analog function for ports
	switch (channel) {
	case 0:
		ANSELAbits.ANSA0 = 0;
		break;
	case 1:
		ANSELAbits.ANSA1 = 0;
		break;
	case 2:
		ANSELAbits.ANSA2 = 0;
		break;
	case 3:
		ANSELAbits.ANSA4 = 0;
		break;
	case 7:
		ANSELCbits.ANSC3 = 0;
		break;
	default:
		break;
	}
	
	return data;
}
void SetPWM1(unsigned char value)
{
    T2CON=0x02;
    PWM1CON=0;
    PR2=255;
    PWM1DCH=value;
    PWM1DCL=0;
    PWM1CON=0xC0;
    T2CONbits.TMR2ON = 1;
    TRISCbits.TRISC5 = 0;
}
void SetPWM2(unsigned char value)
{
    T2CON=0x02;
    PWM2CON=0;
    PR2=255;
    PWM2DCH=value;
    PWM2DCL=0;
    PWM2CON=0xC0;
    T2CONbits.TMR2ON = 1;
    TRISCbits.TRISC3 = 0;
    
}
void ClosePWM(unsigned char value)
{
    switch(value)
    {
      case 1:
        PWM1CON=0;    
        TRISCbits.TRISC5 = 1;    
        break;
         
      case 2:
        PWM2CON=0;    
        TRISCbits.TRISC3 = 1;     
                   
        break;   
      default:
        break;
        
        
    }
            
}