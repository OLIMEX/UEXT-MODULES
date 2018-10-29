/******************************************************************************/
/* OLIMEX COMMANDS	                                                      */
/******************************************************************************/
#ifndef _OLIMEX_H
#define _OLIMEX_H

#define	SET_TRIS	0x01
#define SET_LAT		0x02
#define	GET_PORT	0x03
#define SET_PU		0x04
#define GET_TRIS	0x05
#define GET_LAT		0x06

#define GET_AN_GPIO0	0x10
#define GET_AN_GPIO1	0x11
#define GET_AN_GPIO2	0x12
#define GET_AN_GPIO3	0x13
#define GET_AN_GPIO5	0x15

#define GET_ID		0x20
#define GET_FV      0x21        // get firmware version

#define IO2_ID		0x23
#define VERSION     0x3B      // current version 3.11

#define SET_REL		0x40
#define SET_RELON	0x41
#define SET_RELOFF	0x42
#define GET_REL		0x43

#define  PWM_OFF     0x50
#define  SET_PWM1    0x51
#define  SET_PWM2    0x52

#define SET_ADDRESS	0xF0

#endif