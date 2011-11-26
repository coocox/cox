#include "ht32f125x.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_wdt.h"
#include "ht32f125x_misc.h"
#include "ht32f125x_usart.h"

/* Private function declartion -----------------------------------------------------------------------------*/
void NVIC_Configuration(void);
void CKCU_Configuration(void);
void USART_Configuration(void);
void SYSTICK_Configuration(void);
void LED_Configuration(void);
void WDT_IRQHandler(void);
void SysTick_Handler(void);

extern signed int printf(const char *pFormat, ...);
/*********************************************************************************************************//**
  * @brief  Period_Reload program,the example main funtion.
  * @retval None
  ***********************************************************************************************************/
void Period_Reload(void)
{

  NVIC_Configuration();               /* NVIC configuration                                                 */
  CKCU_Configuration();               /* System Related configuration                                       */
  USART_Configuration();              /* USART Related configuration                                        */
  SYSTICK_Configuration();            /* SYSTICK Related configuration                                      */
  LED_Configuration();

  /* WatchDog configuration */
  WDT_IntConfig(ENABLE);              /* Enable WDT Interrupt */
  WDT_SetPrescaler(WDT_PRESCALER_8);  /* Set Prescaler Value as 2 */
  WDT_SetReloadValue(0xEFF);          /* Set Reload Value as 0xEFF  */
  WDT_Restart();                      /* Reload Counter as WDTV Value */
  WDT_SetDeltaValue(0xA00);           /* Set Delta Value as 0xA00 */
  WDT_ProtectCmd(ENABLE);             /* Enable Protection  */

  //printf("\n\rWDT Period Reload Starts...\n\r");
  //printf("The Program Is Still Working If LED3 Keep Flashing\n\r");

  /* Enable the SYSTICK Counter */
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);

  while(1);
}

/*********************************************************************************************************//**
  * @brief  Configures NVIC vector table.
  * @retval None
  ***********************************************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_EnableIRQ(WDT_IRQn);
}
/*********************************************************************************************************//**
  * @brief  Configures led.
  * @retval None
  ***********************************************************************************************************/
void LED_Configuration()
{
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA, ENABLE);
	GPIO_DirectionConfig(GPIOA, GPIO_PIN_5, GPIO_DIR_OUT);
}
/*********************************************************************************************************//**
  * @brief  Configures the system clocks.
  * @brief  None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  /*------------------------------------------------------------------------------------------------------*/
  /* APB Peripheral 1 Enable                                                                              */
  /* - CKCU_APBEN1_WDT,  CKCU_APBEN1_RTC,  CKCU_APBEN1_GPTM0, CKCU_APBEN1_GPTM1                           */
  /* - CKCU_APBEN1_OPA0, CKCU_APBEN1_OPA1, CKCU_APBEN1_ADC                                                */
  /*------------------------------------------------------------------------------------------------------*/
  CKCU_APBPerip1ClockConfig(CKCU_APBEN1_WDT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configures USART.
  * @retval None
  ***********************************************************************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure ;
  USART_InitStructure.USART_BaudRate = 115200 ;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B ;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO ;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

  /* Enable GPIO and AFIO clock */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA | CKCU_APBEN0_AFIO, ENABLE);

  /* Enable USART clock */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_USART, ENABLE);

  /* Configure USART Tx/Rx as alternate function */
   AFIO_GPAConfig(AFIO_PIN_8 | AFIO_PIN_9, AFIO_MODE_2);

  /* USART configuration */
   USART_Init(USART, &USART_InitStructure);
}

/*********************************************************************************************************//**
  * @brief  This function is used to configure SYSTICK.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_Configuration(void)
{
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK); /*  Default: 9MHz ON CHIP */
  SYSTICK_SetReloadValue(900000);               /*  (900K/9MHz) = 100ms ON CHIP */
  SYSTICK_IntConfig(ENABLE);                    /* Enable SysTick Interrupt */
}
/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
int led_on = 1;
void SysTick_Handler(void)
{
  /* Reload Counter as WDTV Value */
  WDT_Restart();
  if(led_on){
	  GPIO_SetOutBits(GPIOA, GPIO_PIN_5);
	  led_on = 0;
  }
  else{
	  GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);
	  led_on = 1;
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles WDT interrupt.
 * @retval  None
 ************************************************************************************************************/

void WDT_IRQHandler(void)
{
  /* Turn on LED3 */
  GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);

  if(WDT_GetFlagStatus(WDT_FLAG_UNDERFLOW) == SET)
	 // printf("\n\rWDT Underflow Happened...\n\r");

  if(WDT_GetFlagStatus(WDT_FLAG_ERROR) == SET)
  	 // printf("\n\rWDT Error Happened...\n\r");

  while(1);
}
