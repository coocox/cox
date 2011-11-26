#include "ht32f125x.h"
#include "ht32f125x_rtc.h"
#include "ht32f125x_usart.h"
#include "ht32f125x_ckcu.h"
#include "ht32f125x_rstcu.h"
#include "ht32f125x_gpio.h"
#include "ht32f125x_pwrcu.h"

/* Private variables ---------------------------------------------------------------------------------------*/
vu32 gwTimeDisplay = 0;
int led_on = 1;

/* Private function declartion -----------------------------------------------------------------------------*/

void USART_Configuration(void);
void RTC_Configuration(void);
u32 Time_Regulate(void);
void Time_Display(u32 wTimeVar);
void LED_Configuration(void);
extern signed int printf(const char *pFormat, ...);


/* Private functions ---------------------------------------------------------------------------------------*/
void RTC_IRQHandler(void)
{
  u8 bFlags ;
  bFlags = RTC_GetFlagStatus();
  if((bFlags & 0x2) != 0x0) /* Match flag */
  {
    /* Reset RTC init time when Time is 23:59:59 */
    RTC_SetCompare(86400) ;
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_1, 0);
  }

  /* Toggle LED3 each 1s */
  if(led_on){
  	  GPIO_SetOutBits(GPIOA, GPIO_PIN_5);
  	  led_on = 0;
    }
    else{
  	  GPIO_ClearOutBits(GPIOA, GPIO_PIN_5);
  	  led_on = 1;
    }

  /* Enable time update */
  gwTimeDisplay = 1;
}
/*********************************************************************************************************
  * @brief  Calendar program.
  * @retval None
  ********************************************************************************************************/
void Calendar(void)
{
	CKCU_APBPerip1ClockConfig(CKCU_APBEN1_RTC, ENABLE);
	  if(PWRCU_CheckReadyAccessed() != PWRCU_OK)
	  {
	    while(1);
	  }

	  /* Init LED3 and USART */
	  LED_Configuration();
	  USART_Configuration();

	  /* Enable NVIC RTC interrupt */
	  NVIC_EnableIRQ(RTC_IRQn);

  /* Check if the Power On Reset flag is set */
  if(PWRCU_GetFlagStatus() == PWRCU_FLAG_BAKPOR)
  {
    printf("\r\n\n Power On Reset occurred....");
  }

  if(PWRCU_ReadBackupRegister(PWRCU_BAKREG_0) != 0x5A5A)
  {
    u32 wInitTime = 0;
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    printf("\r\n\n RTC not yet configured....");

    /* RTC Configuration */
    RTC_Configuration();

    printf("\r\n RTC configured....");

    /* Adjust time by values entred by the user on the hyperterminal,
       Then store the init time to PWRCU_BAKREG_1. */
    wInitTime = Time_Regulate() ;
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_1, wInitTime);

    /* Reset RTC Counter when Time is 23:59:59 */
    RTC_SetCompare(86400 - wInitTime) ;

    PWRCU_WriteBackupRegister(PWRCU_BAKREG_0, 0x5A5A);
    /* Enable RTC */
    RTC_Cmd(ENABLE) ;
  }
  else
  {
    printf("\r\n No need to configure RTC....");
  }

  /* Display current time in infinite loop */
  printf("\n\r");

  while (1)
  {
    /* If 1s has paased */
    if(gwTimeDisplay == 1)
    {
      /* Display current time.
         Current time is sum of the RTC counter value and the init time(stored in PWRCU_BAKREG_1 register).
         The init time (PWRCU_BAKREG_1 register) will be clear if the RTC Match flag(CMFLAG) is set.
         Refer to RTC_IRQHandler. */
      Time_Display(RTC_GetCounter() + PWRCU_ReadBackupRegister(PWRCU_BAKREG_1));
      gwTimeDisplay = 0;
    }
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
  *   - flow control: None
  *
  ***********************************************************************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  CKCU_SetUSARTPrescaler(CKCU_URPRE_DIV1);
  USART_InitStructure.USART_BaudRate = 115200 ;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B ;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO ;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;


  /* Enable GPIO and AFIO clock */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA | CKCU_APBEN0_AFIO, ENABLE);

  /* Enable USART clock */
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_USART, ENABLE);

  /* Configure USART Tx/Rx as alternate function */
   AFIO_GPAConfig(AFIO_PIN_8 | AFIO_PIN_9, AFIO_MODE_2);

  /* USART configuration */
   USART_Init(USART, &USART_InitStructure);
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
 * @brief Configures the RTC.
 * @retval None
 * @details RTC configuration as following:
 *  - S/W reset backup domain.
 *  - Configure RTC.
 *    - Select LSI as RTC Clock Source.
 *    - Enable the RTC Second interrupt.
 *    - RTC prescaler = 32768 to generate 1 second interrupt.
 *    - Enable clear RTC counter by match function.
 *
 ************************************************************************************************************/
void RTC_Configuration(void)
{
  /* Reset Backup Domain */
  PWRCU_DeInit();

  RTC_ClockSourceConfig(RTC_SRC_LSI);
  RTC_IntConfig(RTC_INT_CSEC, ENABLE);
  RTC_SetPrescaler(RTC_RPRE_32768);

  /* Restart counter when match event occured */
  RTC_CMPCLRCmd(ENABLE) ;
}

/*********************************************************************************************************//**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @return Enter time, unit is second within a day.
  ***********************************************************************************************************/
u32 Time_Regulate(void)
{
  u32 Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;

  do
  {
	 Tmp_HH = 11;
  } while(Tmp_HH > 23) ;
  printf(":  %u", (unsigned int)Tmp_HH);

  do
  {
	 Tmp_MM = 40;
  } while(Tmp_MM > 59) ;
  printf(":  %u", (unsigned int)Tmp_MM);

  do
  {
	Tmp_SS = 16;
  } while(Tmp_SS > 59) ;
  printf(":  %u", (unsigned int)Tmp_SS);

  return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}

/*********************************************************************************************************//**
  * @brief  Displays the input time.
  * @param  wTimeVar: Displays time.
  * @retval None
  ***********************************************************************************************************/
void Time_Display(u32 wTimeVar)
{
  u32 THH = 0, TMM = 0, TSS = 0;

  /* Compute  hours */
  THH = wTimeVar/3600;
  /* Compute minutes */
  TMM = (wTimeVar % 3600)/60;
  /* Compute seconds */
  TSS = (wTimeVar % 3600)% 60;

  printf("Time: %02u:%02u:%02u\r",(unsigned int)THH, (unsigned int)TMM, (unsigned int)TSS);
}
