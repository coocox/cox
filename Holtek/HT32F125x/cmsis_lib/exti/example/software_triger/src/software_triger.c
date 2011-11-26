#include "ht32f125x.h"
#include "ht32f125x_exti.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_usart.h"
#include "stdio.h"

/***private functions declartion***********************************/
void USART_Configuration();
void EXTI11_IRQHandler(void);

/*** the example main funtion **************************/
void Software_Triger()
{
	/*** APB Peripheral 0 Enable ************************/
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_EXTI | CKCU_APBEN0_PB, ENABLE);

	/*** USART configuration *****************************/
	USART_Configuration();

	/* Enable PB Input Function */
	GPIO_InputConfig(GPIOB, GPIO_PIN_11, ENABLE);

    /* Select Port B as EXTI Trigger Source */
	AFIO_EXTISourceConfig(AFIO_EXTI_CH_11, AFIO_ESS_PB);

    /* Configure EXTI_CHANNEL_11 Interrupt Channel */
	NVIC_EnableIRQ(EXTI11_IRQn);

	/* Enable EXTI_CHANNEL_11 Interrupt */
	EXTI_IntConfig(EXTI_CHANNEL_11, ENABLE);

	/* use Software to trigger EXTI_CHANNEL_11 Interrupt */
	EXTI_SWIntCmd(EXTI_CHANNEL_11, ENABLE);
	while(1);
}

/*** USART Configutation function ****************************/
void USART_Configuration(){
    
	USART_InitTypeDef USART_InitStructure;
	/* Enable peripheral clock of AFIO, USART */
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_USART, ENABLE);
	/* Config AFIO mode as USART_Rx and USART_Tx function. */
	AFIO_GPAConfig(AFIO_PIN_8 | AFIO_PIN_9, AFIO_MODE_2) ;

    USART_InitStructure.USART_BaudRate = 115200 ;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B ;
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
	USART_InitStructure.USART_Parity = USART_PARITY_NO ;
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
	USART_Init(USART, &USART_InitStructure);
}

/*** This function handles EXTI11 interrupt. ****************/
void EXTI11_IRQHandler(void)
{
  /* Disable Software EXTI_CHANNEL_11 Interrupt */
  EXTI_SWIntCmd(EXTI_CHANNEL_11, DISABLE);

  /* Disable EXTI_CHANNEL_11 Interrupt */
  EXTI_IntConfig(EXTI_CHANNEL_11, DISABLE);
}

