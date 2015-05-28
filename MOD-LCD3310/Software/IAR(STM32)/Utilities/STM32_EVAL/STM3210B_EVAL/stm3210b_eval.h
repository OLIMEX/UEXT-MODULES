/**
  ******************************************************************************
  * @file    stm3210b_eval.h
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   This file contains definitions for STM3210B_EVAL's Leds, push-buttons
  *          and COM ports hardware resources.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM3210B_EVAL_H
#define __STM3210B_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM3210B_EVAL
  * @{
  */ 


/** @defgroup STM3210B_EVAL_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 



/** @defgroup STM3210B_EVAL_Exported_Constants
  * @{
  */ 
/** @addtogroup STM3210B_EVAL_LED
  * @{
  */
#define LEDn                        1
#define LED1_GPIO_PORT              GPIOC
#define LED1_GPIO_CLK               RCC_APB2Periph_GPIOC  
#define LED1_GPIO_PIN               GPIO_Pin_12
/** @addtogroup STM3210B_EVAL_BUTTON
  * @{
  */  
#define BUTTONn                     1

/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PORT          GPIOA
#define WAKEUP_BUTTON_CLK           RCC_APB2Periph_GPIOA
#define WAKEUP_BUTTON_PIN           GPIO_Pin_0
#define WAKEUP_BUTTON_EXTI_LINE     EXTI_Line0
#define WAKEUP_BUTTON_PORT_SOURCE   GPIO_PortSourceGPIOA
#define WAKEUP_BUTTON_PIN_SOURCE    GPIO_PinSource0
#define WAKEUP_BUTTON_IRQn          EXTI0_IRQn 

// LCD3310
#define PIN_LOW(PORT, PIN)   PORT = PORT & (~(1<<PIN));
#define PIN_HIGH(PORT, PIN)  PORT = PORT | (1<<PIN);

// RB6
#define LCD3310_RST_PORT   GPIOB
#define LCD3310_RST_PIN    (6)
#define LCD3310_RST_MASK   (1<<LCD3310_RST_PIN)
#define LCD3310_RST_OUT    LCD3310_RST_PORT->ODR

// RA4
#define LCD3310_CS_PORT   GPIOA
#define LCD3310_CS_PIN    (4)
#define LCD3310_CS_MASK   (1<<LCD3310_CS_PIN)
#define LCD3310_CS_OUT    LCD3310_CS_PORT->ODR

// RB7
#define LCD3310_CD_PORT   GPIOB
#define LCD3310_CD_PIN    (7)
#define LCD3310_CD_MASK   (1<<LCD3310_CD_PIN)
#define LCD3310_CD_OUT    LCD3310_CD_PORT->ODR

// RA5
#define LCD3310_SCK_PORT   GPIOA
#define LCD3310_SCK_PIN    (5)
#define LCD3310_SCK_MASK   (1<<LCD3310_SCK_PIN)
#define LCD3310_SCK_OUT    LCD3310_SCK_PORT->ODR

// RA7
#define LCD3310_MOSI_PORT   GPIOA
#define LCD3310_MOSI_PIN    (7)
#define LCD3310_MOSI_MASK   (1<<LCD3310_MOSI_PIN)
#define LCD3310_MOSI_OUT    LCD3310_MOSI_PORT->ODR

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/** @defgroup STM3210B_EVAL_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM3210B_EVAL_Exported_Functions
  * @{
  */ 

/**
  * @}
  */ 
    
#ifdef __cplusplus
}
#endif
  
#endif /* __STM3210B_EVAL_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
