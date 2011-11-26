#include "ht32f125x.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

#define DELAY_TIME    0x2FFFF

void Delay(vu32 Cnt);


/*********************************************************************************************************//**
  * @brief  HSE_Clock program,the example main funtion.
  * @retval None
  ***********************************************************************************************************/
void HSE_Clock(void)
{

  /*Enables the external high speed oscillator (HSE).*/
  CKCU_HSECmd(ENABLE);
  if(CKCU_WaitHSEReady() == SUCCESS)
  {
  	/*HSE selected as system clock*/
	  if(CKCU_SysClockConfig(CKCU_SW_HSE) == ERROR)
	  {
		  while(1);
	  }
	  /* Initializes LED3 */
	  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA, ENABLE);
	  GPIO_DirectionConfig(GPIOA, GPIO_PIN_5, GPIO_DIR_OUT);

	  while (1)
	  {
		/* Toggle LED3 */
		GPIO_SetOutBits(GPIOA, GPIO_PIN_5);
		Delay(DELAY_TIME);
		GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);
		Delay(DELAY_TIME);
	  }
  }
  else
  {
	  while(1);
  }
}
/*********************************************************************************************************//**
  * @brief  Delay time.
  * @param  Cnt: delay time count.
  * @retval None
  ***********************************************************************************************************/
void Delay(vu32 Cnt)
{
  for(; Cnt > 0; Cnt--);
}
