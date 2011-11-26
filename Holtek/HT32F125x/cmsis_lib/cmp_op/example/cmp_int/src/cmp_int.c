#include "ht32f125x.h"
#include "ht32f125x_cmp_op.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_misc.h"
#include "ht32f125x_gpio.h"

void COMP_IRQHandler(void);
/**************************************************************************************************************//*
 *@ brief:    the main example function,see the file brief.
 *@ in:       none
 *@ return:   none
 ****************************************************************************************************************/
void cmp_int(void)
{
    CMP_OP_InitTypeDef CMP_OP_InitStruct;
	/*** Enable the GPIOA clock and config the pin.5 as output***/
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO, ENABLE);
    CKCU_APBPerip1ClockConfig(CKCU_APBEN1_OPA0, ENABLE);

    AFIO_GPBConfig(AFIO_PIN_2|AFIO_PIN_3, AFIO_MODE_1);

	CMP_OP_InitStruct.CMP_OP_Enable = CMP_OP_ENABLE;
	CMP_OP_InitStruct.CMP_OP_CMPOPMode = CMP_MODE;
	CMP_OP_InitStruct.CMP_OP_CancellOPAMode = NORMAL_MODE;
	CMP_OP_InitStruct.CMP_OP_RefSelect = NEGATIVE_INPUT;
	CMP_OP_InitStruct.CMP_OP_Cancellation =  CENTER;
	CMP_OP_InitStruct.CMP_OP_RisingInterruptMask = FALL_INTERRUPT_MASK ;
	CMP_OP_InitStruct.CMP_OP_FallingInterruptMask = RISING_INTERRUPT_MASK ;

	/*** Init the ******************************/
	CMP_OP_Init(CMP_OP0, &CMP_OP_InitStruct);
	/*** Enable the ADC interrupt **************/
	CMP_OP_IntConfig(CMP_OP0, CMP_OP_INT_FALLING, ENABLE);
}

