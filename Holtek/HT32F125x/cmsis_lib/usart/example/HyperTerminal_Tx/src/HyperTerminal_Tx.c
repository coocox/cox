#include "ht32f125x.h"
#include "ht32f125x_usart.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

extern signed int printf(const char *pFormat, ...);
/*********************************************************************************************************//**
  * @brief  HyperTerminal_Tx program.
  * @retval None
  * @details HyperTerminal_Tx program as following
  *  - Enable peripheral clock of AFIO, USART.
  *  - Config AFIO mode as USART_Rx and USART_Tx function.
  *  - USART configuration:
  *     - BaudRate = 115200 baud
  *     - Word Length = 8 Bits
  *     - One Stop Bit
  *     - None parity bit
  *  - USART Tx "Hello World!" string 10 times.
  *
  ***********************************************************************************************************/
void HyperTerminal_Tx(void)
{
  USART_InitTypeDef USART_InitStructure;
  int input;


  /* Enable peripheral clock of AFIO, USART */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_USART, ENABLE);

  /* Config AFIO mode as USART_Rx and USART_Tx function. */
  AFIO_GPAConfig(AFIO_PIN_8 | AFIO_PIN_9, AFIO_MODE_2) ;

  /* USART configuration ------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 115200 ;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B ;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO ;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
  USART_Init(USART, &USART_InitStructure);

  /* USART Tx "Hello World!" string 10 times. */
  for(input = 0; input < 10; input++)
  {
    //printf("Hello World! %d\n\r", (int)input);
  }
}

