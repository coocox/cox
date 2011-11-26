#include "ht32f125x.h"
#include "ht32f125x_pwrcu.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_rtc.h"
#include "ht32f125x_ckcu.h"

/* Private typedef -----------------------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------------------------------------*/

extern vu32 wTimingDelay;

/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------------------------------------*/

void RTC_Configuration(void);
void LED_Configuration(void);
/*********************************************************************************************************//**
  * @brief  DeepSleepMode1 program,the example main funtion.
  * @retval None
  ***********************************************************************************************************/
void DeepSleepMode1(void)
{
  int i;  
  u32 wRtcCounterTmp=0;

  /* Initialize LED3 */
  LED_Configuration();

  /* Configure RTC clock source and prescaler */
  RTC_Configuration();
  /* Configure the SysTick to generate an interrupt each 1 millisecond */

  /* Turn on LED3 */
  GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);

  /* Configure SWCLK(PA14) pin in input mode (floating input trigger OFF) */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA, ENABLE);
  GPIO_PullResistorConfig(GPIOA, GPIO_PIN_14, GPIO_PR_DISABLE);
  
  /* Infinite loop */
  while (1)
  {
    /* Insert delay for LED3*/
	  for(i=0;i<50000;i++);

    /* Wait till RTC count occurs */
    wRtcCounterTmp = RTC_GetCounter();
    while(RTC_GetCounter() == wRtcCounterTmp);
    /* Compare Match in 3 second */
    RTC_SetCompare(RTC_GetCounter()+ 3);

    /* Turn off LED3 */
    GPIO_SetOutBits(GPIOA, GPIO_PIN_5);

    /* Request to enter Deep Sleep mode 1 (The LDO in low power mode) */
    PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_WFI);

    /* Turn on LED3 when the system has resumed from Deep Sleep mode 1 by RTC*/
    if(RTC_GetFlagStatus() & RTC_FLAG_CM)
    {
    	/* Toggle LED3 */
        GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);
    }
  }
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
  * @brief  Configures RTC clock source and prescaler.
  * @retval None
  ***********************************************************************************************************/
void RTC_Configuration(void)
{
  /* Check the backup domain(RTC & PWRCU) is ready for access */
  CKCU_APBPerip1ClockConfig(CKCU_APBEN1_RTC, ENABLE);
  if(PWRCU_CheckReadyAccessed() != PWRCU_OK)
  {
    while(1);
  }

  /* Reset Backup Domain */
  PWRCU_DeInit();

  RTC_ClockSourceConfig(RTC_SRC_LSI);
  /* Set the RTC time base to 1s */
  RTC_SetPrescaler(RTC_RPRE_32768);

  /* Set Compare value */
  RTC_SetCompare(0xFFFFFFFF);

  /* Enable the RTC */
  RTC_Cmd(ENABLE);

  /* Enable the RTC Compare Match wakeup event */
  RTC_WakeupConfig(RTC_WAKEUP_CM, ENABLE);
}

