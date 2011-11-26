#include "ht32f125x.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

/*********************************************************************************************************
  * @brief  led program.
  * @retval None
  ********************************************************************************************************/
void led(void)
{
	int i;
	/*Enables the APB peripheral 0 clock*/
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA, ENABLE);
	/*Configure the corresponding pin*/
	GPIO_DirectionConfig(GPIOA, GPIO_PIN_5, GPIO_DIR_OUT);
	while(1)
	{
		for(i=0;i<100000;i++);
		/*Turn off LED3*/
		GPIO_SetOutBits(GPIOA, GPIO_PIN_5);
		for(i=0;i<100000;i++);
		/*Turn on LED3*/
		GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);
	}
}
