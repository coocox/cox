#include "ht32f125x.h"
#include "ht32f125x_misc.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

void SysTick_Handler(void);

/********************************************************************************//*
 * @brief: the main funtion of the example
 * @in:    none
 * @return none
 **********************************************************************************/
void SysClk_Tick()
{
	/***Enable the GPIOA clock **************************/
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA, ENABLE);
	/*** Set the GPIOA pin.5 as output pin***************/
    GPIO_DirectionConfig(GPIOA, GPIO_PIN_5, GPIO_DIR_OUT);
    /***Configures the SysTick clock source. ************/
    SYSTICK_ClockSourceConfig(SYSTICK_SRC_FCLK);
    /***Enable the SystemTick Interrupt******************/
    SYSTICK_IntConfig(ENABLE);
    /***Sets SysTick counter reload value****************/
    SYSTICK_SetReloadValue(0x3a2100);
    /***Enable the System Counter************************/
    SYSTICK_CounterCmd(ENABLE);
    while(1);
}

/*************************************************************//*
 * @brief SysTick interrupt handler
 * @in    none
 ***************************************************************/
void SysTick_Handler(void){
	uint32_t i;
	/***Clear System Tick counter flag******************/
    /*
     *
     */
	/***Flash the led which is connected to the pin.5***/
	GPIO_WriteOutData(GPIOA, 0xFFFF);
    for (i =0; i <100000; i++);
	GPIO_WriteOutData(GPIOA, 0);
	for (i =0; i <100000; i++);
}
