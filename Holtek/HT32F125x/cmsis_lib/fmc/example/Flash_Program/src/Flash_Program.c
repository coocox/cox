#include "ht32f125x.h"
#include "ht32f125x_flash.h"
#include "ht32f125x_usart.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_ckcu.h"

/* Private typedef -----------------------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------------------------------------*/
#define StartAddress    ((u32) 0x00001000)
#define EndAddress      ((u32) 0x00002000)

void USART_Configuration(void);
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
void Flash_Program(void)
{
  u32 i, PageCnt = 0, Addr = 0;
  u32 Data = 0x12345678;
  vu32 err = 0;
  volatile FLASH_State FLASHState;

  USART_Configuration();

  /*
     Configures the system clock in startup file (startup_ht32f125x.s)
     by calling SystemInit function. Please refer to system_ht32f125x.c.
  */

  /* Clear Flash pending flags */
  FLASH_ClearIntFlag(FLASH_FLAG_ITADF | FLASH_FLAG_OBEF | FLASH_FLAG_IOCMF | FLASH_FLAG_OREF);

  /* Enable Flash interrupts */
  FLASH_IntConfig(FLASH_INT_ITADIE | FLASH_INT_OBEIE | FLASH_INT_IOCMIE | FLASH_INT_OREIE, ENABLE);

  /* Erase Flash pages before program data */
  PageCnt = (EndAddress - StartAddress) / FLASH_PAGE_SIZE;

  for (i = 0; i < PageCnt; i++)
  {
    FLASHState = FLASH_ErasePage(StartAddress + (i * FLASH_PAGE_SIZE));
  }

  /* Program Word data */
  for (Addr = StartAddress; Addr < EndAddress; Addr+=4)
  {
    FLASHState = FLASH_ProgramWordData(Addr, Data);

    if (FLASHState != FLASH_COMPLETE)
    {
      break;
    }
  }

  /* Check Flash data */
  for (Addr = StartAddress; Addr < EndAddress; Addr+=4)
  {
    if ( *((u32 volatile *) Addr) != Data )
    {
      err++;
    }
  }

  if(err == 0){
	  USART_SendData(USART, 'Y');
  }
  else{
	  USART_SendData(USART, 'N');
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
