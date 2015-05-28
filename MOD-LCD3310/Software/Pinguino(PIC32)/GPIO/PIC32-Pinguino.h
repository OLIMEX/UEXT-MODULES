/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OLIMEXINO_STM32_H
#define __OLIMEXINO_STM32_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#define	JUMPER_TO_D10	// uncomment this macro if you close chip select pin to D10 --> RA4

// LCD3310
#define PIN_LOW(PIN)   digitalWrite (PIN, 1)
#define PIN_HIGH(PIN)  digitalWrite (PIN, 0)

// RD10
#define LCD3310_RES_PORT   LATD
#define LCD3310_RES_PIN    (10)
#define LCD3310_RES_MASK   (1<<LCD3310_RES_PIN)
#define	LCD3310_RES_DNUM   A5

#ifdef JUMPER_TO_D10	// chip select jumper closed to D10 --> RG9
	// RG9
	#define LCD3310_CS_PORT   LATG
	#define LCD3310_CS_PIN    (9)
	#define LCD3310_CS_MASK   (1<<LCD3310_CS_PIN)
	#define LCD3310_CS_DNUM   10
#else	// chip select jumper closed to RF0
	// RF0
	#define LCD3310_CS_PORT   LATF
	#define LCD3310_CS_PIN    (0)
	#define LCD3310_CS_MASK   (1<<LCD3310_CS_PIN)
	#define LCD3310_CS_DNUM   0	// TODO
#endif

// RD9
#define LCD3310_CD_PORT   LATD
#define LCD3310_CD_PIN    (9)
#define LCD3310_CD_MASK   (1<<LCD3310_CD_PIN)
#define LCD3310_CD_DNUM   A4

// RG6
#define LCD3310_SCK_PORT   LATG
#define LCD3310_SCK_PIN    (6)
#define LCD3310_SCK_MASK   (1<<LCD3310_SCK_PIN)
#define LCD3310_SCK_DNUM   13

// RG8
#define LCD3310_MOSI_PORT   LATG
#define LCD3310_MOSI_PIN    (8)
#define LCD3310_MOSI_MASK   (1<<LCD3310_MOSI_PIN)
#define LCD3310_MOSI_DNUM   11
    
#ifdef __cplusplus
}
#endif
  
#endif /* __OLIMEXINO_STM32_H */
