/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Main program body.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval.h"
#include "lcd3310.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  int Button_Released=1, Inverse=0;
  /* System Clocks Configuration **********************************************/
  RCC_Configuration();   

  /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC *************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, DISABLE);  

  /* Initialize Leds mounted on STM3210X-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_PBInit(Button_WAKEUP, Mode_GPIO);

  LCDInit();
  LCDContrast(0x70);
  LCDStr(0, (unsigned char *)"*** OLIMEX ***", Inverse);
  LCDStr(1, (unsigned char *)"  STM32-P103  ", !Inverse);
LCDStr(2, (unsigned char *)"  demo  for   ", Inverse);
  LCDStr(3, (unsigned char *)"  MOD-LCD3310 ", !Inverse);
#if defined  USE_SPI
  LCDStr(4, (unsigned char *)"  using SPI   ", Inverse);
#elif defined USE_GPIO
  LCDStr(4, (unsigned char *)"  using GPIO  ", Inverse);
#endif
  LCDStr(5, (unsigned char *)"  interface   ", !Inverse);
        
  while (1)
  {
     if (STM_EVAL_PBGetState (Button_WAKEUP))
     {
        if (Button_Released)
        {
          Button_Released = 0;
          Inverse = !Inverse;

          LCDStr(0, (unsigned char *)"*** OLIMEX ***", Inverse);
          LCDStr(1, (unsigned char *)"  STM32-P103  ", !Inverse);
          LCDStr(2, (unsigned char *)"  demo  for   ", Inverse);
          LCDStr(3, (unsigned char *)"  MOD-LCD3310 ", !Inverse);
#if defined  USE_SPI
          LCDStr(4, (unsigned char *)"  using SPI   ", Inverse);
#elif defined USE_GPIO
          LCDStr(4, (unsigned char *)"  using GPIO  ", Inverse);
#endif
          LCDStr(5, (unsigned char *)"  interface   ", !Inverse);
        }
     }
     else
        Button_Released = 1;

    /* Turn on LD1 */
    STM_EVAL_LEDToggle(LED1);
    /* Insert delay */
    Delay(0xFFFFF);
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{   
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
/*
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
*/

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
