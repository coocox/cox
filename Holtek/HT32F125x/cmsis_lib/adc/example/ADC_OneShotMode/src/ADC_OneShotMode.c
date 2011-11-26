#include "ht32f125x.h"
#include "ht32f125x_adc.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_usart.h"
#include "stdio.h"

void USART_Configuration(void);
void Delay(u32 cnt);

/*** the main example function **************************************/
void ADC_OneShorMode(void)
{
  int level=0;
  ADC_InitTypeDef ADC_InitStructure;

  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_USART, ENABLE);
  /* Config AFIO mode as USART_Rx and USART_Tx function. */
  AFIO_GPAConfig(AFIO_PIN_8 | AFIO_PIN_9, AFIO_MODE_2);

  /* Enable peripheral clock of ADC */
  CKCU_APBPerip1ClockConfig(CKCU_APBEN1_ADC, ENABLE);
  /* Config AFIO mode as ADC function. */
  AFIO_GPAConfig(AFIO_PIN_0 , AFIO_MODE_1);

  /* USART Related configuration */
  USART_Configuration();

  /* ADC configuration ------------------------------------------------------*/
  /* ADC configured as follow:
        - ConversionMode = ONE_SHOT_MODE
        - TriggerMode = SOFTWAER_TRIGGER
  */
  ADC_InitStructure.ADC_ConversionMode = ONE_SHOT_MODE ;
  ADC_InitStructure.ADC_HPCCMode = HP_ONE_SHOT_MODE;
  ADC_InitStructure.ADC_TriggerMode = SOFTWARE_TRIGGER;
  ADC_InitStructure.ADC_ExtiTriggerSource = ADC_EXTI1;
  ADC_InitStructure.ADC_ETPUTriggerChannel = ADC_GPTM0;
  ADC_InitStructure.ADC_TPTriggerChannel = ADC_CH3O;
  ADC_InitStructure.ADC_HPTriggerMode = SOFTWARE_TRIGGER;
  ADC_InitStructure.ADC_HPExtiTriggerSource = ADC_EXTI5;
  ADC_InitStructure.ADC_HPETPUTriggerChannel =ADC_GPTM0;
  ADC_InitStructure.ADC_HPTPTriggerChannel = ADC_CH3O ;
  ADC_Init(ADC, &ADC_InitStructure);
  /* Config ADC clock as ADC function. */
  CKCU_SetADCDivide(CKCU_PCLK_DIV64);

  ADC_RegularGroupConfig(ADC, ONE_SHOT_MODE, 0, 0);
  ADC_RegularChannelConfig(ADC, ADC_CH_0, 0, 0XFF);

  /* ADC transforms potentiometer level and send to USART.(Loop) */
  while (1)
  {
    ADC_SoftwareStartConvCmd(ADC, ENABLE);
    while (ADC_GetFlagStatus(ADC, ADC_FLAG_SINGLE_EOC|ADC_FLAG_CYCLE_EOC) == RESET);
    level = (((ADC->DR[0]&0x0FFF)*100)/4095);
    Delay(1000000);
  }
}


/*********************************************************************************************************//**
  * @brief  Configures USART.
  * @retval None
  * @details USART configuration as following:
  *   - Word Length = 8 Bits
  *   - One Stop Bit
  *   - No parity
  *   - BaudRate = 115200 baud
  *
  ***********************************************************************************************************/
void USART_Configuration(void)
{
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

void Delay(u32 cnt) { while(cnt--); }
