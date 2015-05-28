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

// RB10
#define LCD3310_RST_PORT   GPIOB
#define LCD3310_RST_PIN    (10)
#define LCD3310_RST_MASK   (1<<LCD3310_RST_PIN)
#define	LCD3310_RST_DNUM   29

#ifdef JUMPER_TO_D10	// chip select jumper closed to D10 --> RA4
	// RA4
	#define LCD3310_CS_PORT   GPIOA
	#define LCD3310_CS_PIN    (4)
	#define LCD3310_CS_MASK   (1<<LCD3310_CS_PIN)
	#define LCD3310_CS_DNUM   10
#else	// chip select jumper closed to D4 --> RB5
	// RB5
	#define LCD3310_CS_PORT   GPIOB
	#define LCD3310_CS_PIN    (5)
	#define LCD3310_CS_MASK   (1<<LCD3310_CS_PIN)
	#define LCD3310_CS_DNUM   4
#endif

// RB11
#define LCD3310_CD_PORT   GPIOB
#define LCD3310_CD_PIN    (11)
#define LCD3310_CD_MASK   (1<<LCD3310_CD_PIN)
#define LCD3310_CD_DNUM   30

// RA5
#define LCD3310_SCK_PORT   GPIOA
#define LCD3310_SCK_PIN    (5)
#define LCD3310_SCK_MASK   (1<<LCD3310_SCK_PIN)
#define LCD3310_SCK_DNUM   13

// RA7
#define LCD3310_MOSI_PORT   GPIOA
#define LCD3310_MOSI_PIN    (7)
#define LCD3310_MOSI_MASK   (1<<LCD3310_MOSI_PIN)
#define LCD3310_MOSI_DNUM   11
    
#ifdef __cplusplus
}
#endif
  
#endif /* __OLIMEXINO_STM32_H */
