/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define REL1	LATCbits.LATC4
#define REL2	LATCbits.LATC2
#define REL1_TRIS TRISCbits.TRISC4
#define REL2_TRIS TRISCbits.TRISC2


#define GPIO0_TRIS TRISAbits.TRISA0
#define GPIO0_LAT LATAbits.LATA0
#define GPIO0_PORT PORTAbits.RA0

#define GPIO1_TRIS TRISAbits.TRISA1
#define GPIO1_LAT LATAbits.LATA1
#define GPIO1_PORT PORTAbits.RA1

#define GPIO2_TRIS TRISAbits.TRISA2
#define GPIO2_LAT LATAbits.LATA2
#define GPIO2_PORT PORTAbits.RA2

#define GPIO3_TRIS TRISAbits.TRISA4
#define GPIO3_LAT LATAbits.LATA4
#define GPIO3_PORT PORTAbits.RA4

#define GPIO4_TRIS TRISAbits.TRISA5
#define GPIO4_LAT LATAbits.LATA5
#define GPIO4_PORT PORTAbits.RA5

#define GPIO5_TRIS TRISCbits.TRISC3
#define GPIO5_LAT LATCbits.LATC3
#define GPIO5_PORT PORTCbits.RC3

#define GPIO6_TRIS TRISCbits.TRISC5
#define GPIO6_LAT LATCbits.LATC5
#define GPIO6_PORT PORTCbits.RC5


#define JMP_TRIS	TRISAbits.TRISA5
#define JMP_LAT		LATAbits.LATA5
#define JMP_PORT	PORTAbits.RA5

/*--------------------------------I2C PINS--------------------------------*/
#define SCL_TRIS		TRISCbits.TRISC0
#define SCL_LAT			LATCbits.LATC0
#define SCL_PORT		PORTCbits.RC0
#define SDA_TRIS		TRISCbits.TRISC1
#define SDA_LAT			LATCbits.LATC1
#define SDA_PORT		PORTCbits.RC1

#define DEFAULT_ADDRESS		0x21
#define MEMORY_ADDRESS		0x7FF

#define START_C	0b00001000	//START CONDITION MASK
#define STOP_C	0b00010000	//STOP CONDITION MASK
#define STATE1	0b00001001	// MASTER WRITE LAST WAS ADDRESS
#define STATE2	0b00101001	// MASTER WRITE LAST WAS DATA
#define STATE3	0b00001101	// MASTER READ LAST WAS ADDRESS
#define STATE4	0b00101100	// MASTER READ LAST WAS DATA
#define STATE5	0b00101000	// MASTER NACK

#define MAX_BUFFER_SIZE		10


#define Nop() asm("NOP")


/******************************************************************************/
/* Local Variables							      */
/******************************************************************************/

extern unsigned char ADDRESS;
extern unsigned char DATA_BUFFER[6];
extern unsigned int DATA_INDEX;
extern unsigned char DATA_OUT[2];



/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/



/**
 * Initialize all the periphere
 * @param none
 */
void InitApp(void);
/**
 * Read stored address from the program memmory 0x7FF. If the cell if empty
 * the board load the default address - 0x21.
 * @param none
 */
void InitAddress(void);
/**
 * Initialize all the gpio ports. By default:
 * @LAT registers - All "0" - low level
 * @TRIS registers - All "1" - inputs
 * @WPUA registers - All pullups on PORTA are on, PORTC doesn't have such.
 * @param none
 */
void InitGPIO(void);
/**
 * Initialize interrupts. Only interrupts from I2C are processed.
 * @param none
 */
void InitInterupts(void);
/**
 * Initialize I2C module. It is configured for 100kHz, 7-bit address, with
 * enabled clock streching and enabled STOP and START interrupts.
 * @param none
 */
void InitI2C(void);
/**
 * Write procedure for writing in the program memory.
 * @param data Data to be stored, the range is from 0x0000 to 0x3FFF.
 * @param address The address of the cell in the programm memory.
 */
void WriteFlash(unsigned int data, unsigned int address);
/**
 * Read procedure for reading from the program memory.
 * @return The data in the selected cell
 * @param address The address of the cell in the program memory.
 */
unsigned int ReadFlash(unsigned int address);
/**
 * Erase the stored data in specific cell int the program memory.
 * @param address The address of the cell
 */
void EraseFlash(unsigned int address);
/**
 * By unlocking the cell becomes available for writing and erasing.
 * @param none
 */
void UnlockFlash(void);
/*
 * Defines the function of the gpio.
 * @param data - The states of all gpios bit0 - GPIO0, bit1 - GPIO1 ...
 */
void CommandSetTris(unsigned char data);
/**
 * Set output level of the gpios
 * @param data - Defines all parameters - bit0 - GPIO0, bit1 - GPIO1 ...
 */
void CommandSetLat(unsigned char data);
/**
 * Return the current state of the PORT registers.
 * @param none
 */
unsigned char CommandGetPort(void);
/**
 * Set or clear pullups. Note that not all GPIO have internal pullups.
 * @param data - bitmasked state of the all GPIOs pullups
 */
void CommandSetPullUps(unsigned char data);
/* Set state of the two relays.
 * @param data - bitmasked state of the relays - bit0 -REL1, bit1 - REL2.
 */
void CommandSetRelay(unsigned char data);
/**
 * Set new address for this device. PROG jumper must closed to set new address.
 * @param addr - The new address.
 */
void CommandSetOnX(unsigned char data);
/* Switch Relay ON 1 - relay1, 2 - relay2, 3 - both*/
void CommandSetOffX(unsigned char data);
/* Switch Relay OFF 1 - relay1, 2 - relay2, 3 - both*/
void CommandSetAddress(unsigned char data);
/**
 * Change i2c address! Jumper 1 must be closed.
 * @param none
 */
unsigned char CommandGetTris(void);
/**
 * Return the current stsate of the LAT registers.
 * @param none
 */
unsigned char CommandGetLat(void);
/**
 * Return the readings from Analog input
 * @param channel The analog channel to select.
 */
unsigned int CommandGetAnalog(unsigned char channel);


void SetPWM1(unsigned char value);
/*
 *   value = pwm duty  
 */
void SetPWM2(unsigned char value);
/*
 * value = pwm duty 
 */
void ClosePWM(unsigned char value);
/*
 * value = pwm# to be closed
 */
