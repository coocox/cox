#include "ht32f125x.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_gpio.h"

void power_reset(void)
{
	uint32_t tem;
	uint32_t i;
	/*** Enable the GPIOA clock and config the pin.5 as output***/
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA, ENABLE);
    GPIO_DirectionConfig(GPIOA, GPIO_PIN_5|GPIO_PIN_6, GPIO_DIR_OUT);
    GPIO_WriteOutData(GPIOA, 0);
	/*** Get the reset flag**************************************/
	tem = RSTCU_GetResetFlagStatus(RSTCU_FLAG_PORST);
	/***If it is power reset*************************************/
	if(tem == SET){
	    while(1){
	    	  GPIO_WriteOutData(GPIOA, 0x20);
	    	  for (i =0; i <100000; i++);
	    	  GPIO_WriteOutData(GPIOA, 0);
	    	  for (i =0; i <100000; i++);
	    }

	}
	else{       /***Other reset***********************************/
		while(1){
			  GPIO_WriteOutData(GPIOA, 0x40);
			  for (i =0; i <100000; i++);
			  GPIO_WriteOutData(GPIOA, 0);
			  for (i =0; i <100000; i++);
		}

	}
}
