/*********************************************************************************************************//**
 * @file    ht32f125x_ckcu.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This library provides all the firmware functions about the Clock Control Unit.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_ckcu.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup CKCU CKCU
  * @brief CKCU driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Private_TypesDefinitions CKCU private types definitions
  * @{
  */

/**
  * @}
  */  /* End of CKCU_Private_TypesDefinitions group */

/* Private define ------------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Private_Define CKCU private definitions
  * @{
  */

/* GCFGR bit field define                                                                                   */
#define CKCU_POS_CKOUTSRC       0
#define CKCU_MASK_CKOUTSRC      0x7

#define CKCU_POS_URPRE          20
#define CKCU_MASK_URPRE         ((u32)0x3 << CKCU_POS_URPRE)

/* GCCR bit field define                                                                                    */
#define CKCU_POS_SW             0
#define CKCU_MASK_SW            0x3

/* PLLCFGR bit field define                                                                                 */
#define CKCU_POS_POTD           21
#define CKCU_POS_PFBD           23
#define CKCU_MASK_PLLOTDV       ((u32)0x0003 << CKCU_POS_POTD)
#define CKCU_MASK_PLLFBDV       ((u32)0x003F << CKCU_POS_PFBD)

/* APBCFGR bit field define                                                                                 */
#define CKCU_POS_ADCDIV         16
#define CKCU_MASK_ADCDIV        ((u32)0x0007 << CKCU_POS_ADCDIV)

/* CKST bit field define                                                                                    */
#define CKCU_POS_PLLST          8
#define CKCU_POS_HSEST          16
#define CKCU_POS_HSIST          24
#define CKCU_MASK_PLLST         ((u32)0x0003 << CKCU_POS_PLLST)
#define CKCU_MASK_HSEST         ((u32)0x0003 << CKCU_POS_HSEST)
#define CKCU_MASK_HSIST         ((u32)0x0007 << CKCU_POS_HSIST)

/* Register address define                                                                                  */
#define CKCU_ADDR_GCFGR         (u32)(CKCU_BASE + 0x00)
#define CKCU_ADDR_GCCR          (u32)(CKCU_BASE + 0x04)
#define CKCU_ADDR_GCIR          (u32)(CKCU_BASE + 0x0C)
#define CKCU_ADDR_PLLCR         (u32)(CKCU_BASE + 0x1C)
#define CKCU_ADDR_LPCR          (u32)(CKCU_BASE + 0x300)

/* Bit band alias define                                                                                    */

/* GCFGR Bit Band Alias                                                                                     */
#define CKCU_BB_WDTSRC          BitBand(CKCU_ADDR_GCFGR, 3)
#define CKCU_BB_PLLSRC          BitBand(CKCU_ADDR_GCFGR, 8)

/* GCCR Bit Band Alias                                                                                      */
#define CKCU_BB_PLLEN           BitBand(CKCU_ADDR_GCCR, 9)
#define CKCU_BB_HSEEN           BitBand(CKCU_ADDR_GCCR, 10)
#define CKCU_BB_HSIEN           BitBand(CKCU_ADDR_GCCR, 11)
#define CKCU_BB_CKMEN           BitBand(CKCU_ADDR_GCCR, 16)
#define CKCU_BB_PSRCEN          BitBand(CKCU_ADDR_GCCR, 17)

/* GCIR Bit Band Alias                                                                                      */
#define CKCU_BB_CKSF            BitBand(CKCU_ADDR_GCIR, 0)
#define CKCU_BB_CKSIE           BitBand(CKCU_ADDR_GCIR, 16)

/* PLLCR Bit Band Alias                                                                                     */
#define CKCU_BB_PLLBYPASS       BitBand(CKCU_ADDR_PLLCR, 31)

/* LPCR Bit Band Alias                                                                                      */
#define CKCU_BB_BKISO           BitBand(CKCU_ADDR_LPCR, 0)

/**
  * @}
  */  /* End of CKCU_Private_Define group */

/* Private macro -------------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Private_Macro CKCU private macros
  * @{
  */

/*********************************************************************************************************//**
 * @brief This macro is used to write the bit-field of the specific register.
 * @param Reg: Bit-field in what register.
 * @param Mask: Mask of this bit-field.
 * @param Pos: First bit position of this bit-field.
 * @param WriteValue: Write value.
 * @retval None
 ************************************************************************************************************/
#define CKCU_BF_WRITE(Reg, Mask, Pos, WriteValue)    (Reg = ((Reg & ~((u32)Mask)) | ((u32)WriteValue << Pos)) )

/*********************************************************************************************************//**
 * @brief This macro is used to read the bit-field of the specific register.
 * @param Reg: Bit-field in what register.
 * @param Mask: Mask of this bit-field.
 * @param Pos: First bit position of this bit-field.
 * @retval The specific bit-field value.
 ************************************************************************************************************/
#define CKCU_BF_READ(Reg, Mask, Pos)    ((Reg & (u32)Mask ) >> Pos )

/**
  * @}
  */  /* End of CKCU_Private_Macro group */

/* Private variables ---------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Private_Variable CKCU private variables
  * @{
  */

/**
  * @}
  */  /* End of CKCU_Private_Variable group */

/* Private function prototypes -----------------------------------------------------------------------------*/

/** @defgroup CKCU_Private_Function_Prototype CKCU private function prototypes
  * @{
  */

/**
  * @}
  */  /* End of CKCU_Private_Function_Prototype group */

/* Private functions ---------------------------------------------------------------------------------------*/

/** @defgroup CKCU_Private_Function CKCU private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief  Deinitialize the CKCU registers to the reset values.
 * @retval None
 ************************************************************************************************************/
void CKCU_DeInit(void)
{
  /* Reset system clock */
  CKCU_HSICmd(ENABLE);
  while (CKCU_GetClockReadyStatus(CKCU_FLAG_HSIRDY) == RESET);
  CKCU_SysClockConfig(CKCU_SW_HSI);

  CKCU->AHBCFGR = 0x0;                          /* Reset value of AHBCFGR                                   */
  CKCU->MCUDBGCR = 0x0;                         /* Reset value of MCUDBGCR                                  */
  CKCU->APBCCR0 = 0x0;                          /* Reset value of APBCCR0                                   */
  CKCU->APBCCR1 = 0x0;                          /* Reset value of APBCCR1                                   */
  CKCU->APBCFGR = 0x0;                          /* Reset value of APBCFGR                                   */
  CKCU->AHBCCR = 0x5;                           /* Reset value of AHBCCR                                    */
  CKCU->GCFGR = 0x00000102;                     /* Reset value of GCFGR                                     */
  CKCU->GCIR = 0x0000007D;                      /* Clear interrupt flags                                    */
  CKCU->GCCR = 0x00000803;                      /* Reset value of GCCR                                      */
  CKCU->PLLCFGR = 0x0;                          /* Reset value of PLLCFGR                                   */
  CKCU->PLLCR = 0x0;                            /* Reset value of PLLCR                                     */
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the external high speed oscillator (HSE).
 * @note  HSE can not be stopped if it is used by system clock or PLL.
 * @param Cmd: new status of the HSE.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_HSECmd(EventStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  CKCU_BB_HSEEN = Cmd;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the internal high speed oscillator (HSI).
 * @note  HSI can not be stopped if it is used by system clock or PLL.
 * @param Cmd: new status of the HSI.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_HSICmd(EventStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  CKCU_BB_HSIEN = Cmd;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the PLL clock.
 * @note  PLL can not be stopped if it is used by system clock or USART.
 * @param Cmd: new status of PLL.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_PLLCmd(EventStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  CKCU_BB_PLLEN = Cmd;
}

/*********************************************************************************************************//**
 * @brief  Wait for HSE ready to use.
 * @retval An ErrStatus value:
 *         SUCCESS: HSE clock ready
 *         ERROR: HSE clock not ready yet
 ************************************************************************************************************/
ErrStatus CKCU_WaitHSEReady(void)
{
  vu32 ReadyCnt = 0;

  /* Wait until HSE is ready or time-out occurred                                                           */
  while (1)
  {
    if (CKCU_GetClockReadyStatus(CKCU_FLAG_HSERDY) == SET)
        break;

    ReadyCnt++;
    if (ReadyCnt >= HSE_READY_TIME)
        break;
  }

  if (CKCU_GetClockReadyStatus(CKCU_FLAG_HSERDY) == SET)
  {
    return SUCCESS;
  }
  else
  {
    return ERROR;
  }
}

/*********************************************************************************************************//**
 * @brief Check if the specific clock ready flag is set.
 * @param CKCU_FLAG: Specify the clock ready flag.
 *        This parameter can be:
 *        @arg CKCU_FLAG_PLLRDY : PLL ready flag.
 *        @arg CKCU_FLAG_HSERDY : HSE ready flag.
 *        @arg CKCU_FLAG_HSIRDY : HSI ready flag.
 *        @arg CKCU_FLAG_LSERDY : LSE ready flag.
 *        @arg CKCU_FLAG_LSIRDY : LSI ready flag.
 * @retval The status of CKCU_FLAG, SET or RESET.
 ************************************************************************************************************/
FlagStatus CKCU_GetClockReadyStatus(u32 CKCU_FLAG)
{
  FlagStatus RetValue = RESET;
  
  /* Check the parameters */
  Assert_Param(IS_CKCU_FLAG(CKCU_FLAG));

  if ( (CKCU->GCSR & CKCU_FLAG) != RESET )
  {
    RetValue = SET;
  }
  else
  {
    RetValue = RESET;
  }

  return RetValue;
}

/*********************************************************************************************************//**
 * @brief Configure PLL.
 * @param PLLInit: pointer to CKCU_PLLInitTypeDef structure that contains the configuration information
 *                 for PLL.
 * @retval None
 ************************************************************************************************************/
void CKCU_PLLInit(CKCU_PLLInitTypeDef *PLLInit)
{
  CKCU_BB_PLLSRC = PLLInit->ClockSource;
  CKCU->PLLCFGR = ((u32)PLLInit->CFG) << 16;
  CKCU_BB_PLLBYPASS = PLLInit->BYPASSCmd;
}

/*********************************************************************************************************//**
 * @brief Configure the PLL clock source.
 * @param SRC: Specify the PLL clock source.
 *        This parameter can be:
 *        @arg CKCU_PLLSRC_HSE : HSE selected as PLL source.
 *        @arg CKCU_PLLSRC_HSI : HSI selected as PLL source.
 * @retval None
 ************************************************************************************************************/ 
void CKCU_PLLSourceConfig(CKCU_PLLSRC_TypeDef SRC)
{ 
  CKCU_BB_PLLSRC = SRC;
}

/*********************************************************************************************************//**
 * @brief Configure the system clock (SYS_CK).
 * @param CLKSRC: clock source which is used as system clock.
 *        This parameter can be:
 *        @arg CKCU_SW_PLL : PLL selected as system clock.
 *        @arg CKCU_SW_HSE : HSE selected as system clock.
 *        @arg CKCU_SW_HSI : HSI selected as system clock.
 * @retval ERROR or SUCCESS.
 ************************************************************************************************************/
ErrStatus CKCU_SysClockConfig(CKCU_SW_TypeDef CLKSRC)
{
  u32 cnt = 0xFF;
  
  CKCU_BF_WRITE(CKCU->GCCR, CKCU_MASK_SW, CKCU_POS_SW, CLKSRC);
  
  /* Wait until system clock takes effect or time-out occurred */
  while (cnt--)
  {
    if ( (CKCU->GCCR & CKCU_MASK_SW) == CLKSRC)
    {
      break;
    }  
  }
  
  if (cnt != 0)
  {
    return SUCCESS; 
  }
  else
  {
    return ERROR;
  }
}

/*********************************************************************************************************//**
 * @brief  Return the source clock which is used as system clock.
 * @retval The source clock used as system clock.
 *         0x01: PLL selected as system clock
 *         0x02: HSE selected as system clock
 *         0x03: HSI selected as system clock
 ************************************************************************************************************/
u8 CKCU_GetSysClockSource(void)
{
  return ( (u8) CKCU_BF_READ(CKCU->GCCR, CKCU_MASK_SW, CKCU_POS_SW) );
}

/*********************************************************************************************************//**
 * @brief Configure the AHB clock (HCLK).
 * @param DIV: HCLK is derived from the system clock.
 *        This parameter can be:
 *        @arg CKCU_SYSCLK_DIV1: HCLK = SYS_CK
 *        @arg CKCU_SYSCLK_DIV2: HCLK = SYS_CK / 2
 *        @arg CKCU_SYSCLK_DIV4: HCLK = SYS_CK / 4
 *        @arg CKCU_SYSCLK_DIV8: HCLK = SYS_CK / 8
 * @retval None
 ************************************************************************************************************/
void CKCU_SetHCLKPrescaler(CKCU_SYSCLKDIV_TypeDef DIV)
{
  CKCU->AHBCFGR = DIV;
}

/*********************************************************************************************************//**
 * @brief Configure the USART divider.
 * @param URPRE: Specify the value of divider.
 *        This parameter can be:
 *        @arg CKCU_URPRE_DIV1 : USART clock divided by 1.
 *        @arg CKCU_URPRE_DIV2 : USART clock divided by 2.
 * @retval None
 ************************************************************************************************************/
void CKCU_SetUSARTPrescaler(CKCU_URPRE_TypeDef URPRE)
{
  CKCU_BF_WRITE(CKCU->GCFGR, CKCU_MASK_URPRE, CKCU_POS_URPRE, URPRE);
}

/*********************************************************************************************************//**
 * @brief Configure the ADC clock divider.
 * @param PCLK_DIVX: ADC clock is derived from the PCLK.
 *        This parameter can be:
 *        @arg CKCU_PCLK_DIV1   : ADC_CK = PCLK.
 *        @arg CKCU_PCLK_DIV2   : ADC_CK = PCLK / 2.
 *        @arg CKCU_PCLK_DIV4   : ADC_CK = PCLK / 4.
 *        @arg CKCU_PCLK_DIV8   : ADC_CK = PCLK / 8.
 *        @arg CKCU_PCLK_DIV16  : ADC_CK = PCLK / 16.
 *        @arg CKCU_PCLK_DIV32  : ADC_CK = PCLK / 32.
 *        @arg CKCU_PCLK_DIV64  : ADC_CK = PCLK / 64.
 *        @arg CKCU_PCLK_DIV6   : ADC_CK = PCLK / 6.
 * @retval None
 ************************************************************************************************************/
void CKCU_SetADCDivide(CKCU_PCLKDIV_TypeDef PCLK_DIVX)
{
  CKCU_BF_WRITE(CKCU->APBCFGR, CKCU_MASK_ADCDIV, CKCU_POS_ADCDIV, PCLK_DIVX);
}

/*********************************************************************************************************//**
 * @brief Configure the WDT clock source (WDT_CK).
 * @param SRC: Specify the WDT clock source.
 *        This parameter can be:
 *        @arg CKCU_WDTSRC_LSI : LSI_CK selected as WDT clock
 *        @arg CKCU_WDTSRC_LSE : LSE_CK selected as WDT clock
 * @retval None
 ************************************************************************************************************/
void CKCU_WDTSourceConfig(CKCU_WDTSRC_TypeDef SRC)
{
  CKCU_BB_WDTSRC = SRC;
}

/*********************************************************************************************************//**
 * @brief Return the frequency of the different clocks.
 * @param CKCU_Clk: pointer to CKCU_ClocksTypeDef structure to get the clocks frequency.
 * @retval None
 ************************************************************************************************************/
void CKCU_GetClocksFrequency(CKCU_ClocksTypeDef* CKCU_Clk)
{
  u32 pllNO, pllNF;
  u32 sw, urpre, div;

  /* Get PLL frequency                                                                                      */
  if (CKCU_BB_PLLEN == DISABLE)
  {
    CKCU_Clk->PLL_Freq = 0;
  }
  else
  {
    if (CKCU_BB_PLLBYPASS != DISABLE)
    {
      if (CKCU_BB_PLLSRC == CKCU_PLLSRC_HSE)
      {
        CKCU_Clk->PLL_Freq = HSE_VALUE;
      }
      else
      {
        CKCU_Clk->PLL_Freq = HSI_VALUE;
      }
    }
    else
    {
      pllNF = CKCU_BF_READ(CKCU->PLLCFGR, CKCU_MASK_PLLFBDV, CKCU_POS_PFBD);
      if(pllNF == 0)
        pllNF=64;

      pllNO = CKCU_BF_READ(CKCU->PLLCFGR, CKCU_MASK_PLLOTDV, CKCU_POS_POTD);
      pllNO = (u8)0x1 << pllNO;

      if (CKCU_BB_PLLSRC == CKCU_PLLSRC_HSE)
      {
        CKCU_Clk->PLL_Freq = (HSE_VALUE / pllNO) * pllNF;
      }
      else
      {
        CKCU_Clk->PLL_Freq = (HSI_VALUE / pllNO) * pllNF;
      }
    }
  }

  /* Get system frequency                                                                                   */
  sw = CKCU_BF_READ(CKCU->GCCR, CKCU_MASK_SW, CKCU_POS_SW);
  switch (sw)
  {
    case CKCU_SW_PLL:
      CKCU_Clk->SYSCK_Freq = CKCU_Clk->PLL_Freq;
      break;
    case CKCU_SW_HSE:
      CKCU_Clk->SYSCK_Freq = HSE_VALUE;
      break;
    case CKCU_SW_HSI:
      CKCU_Clk->SYSCK_Freq = HSI_VALUE;
      break;
    default:
      CKCU_Clk->SYSCK_Freq = 0;
      break;
  }

  /* Get HCLK frequency                                                                                     */
  CKCU_Clk->HCLK_Freq = (CKCU_Clk->SYSCK_Freq) >> (CKCU->AHBCFGR);

  /* Get USART frequency                                                                                    */
  urpre = CKCU_BF_READ(CKCU->GCFGR, CKCU_MASK_URPRE, CKCU_POS_URPRE);
  CKCU_Clk->USART_Freq = (CKCU_Clk->HCLK_Freq) >> urpre;
  
  /* Get ADC frequency                                                                                      */
  div = CKCU_BF_READ(CKCU->APBCFGR, CKCU_MASK_ADCDIV, CKCU_POS_ADCDIV);
  if (div == 7)
  {
    CKCU_Clk->ADC_Freq = (CKCU_Clk->HCLK_Freq) / 6;
  }
  else
  {
    CKCU_Clk->ADC_Freq = (CKCU_Clk->HCLK_Freq) >> div;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the APB peripheral 0 clock.
 * @param CKCU_APBP: Specify the APB peripheral 0.
 *        This parameter can be:
 *        @arg CKCU_APBEN0_I2C , CKCU_APBEN0_SPI, CKCU_APBEN0_USART, CKCU_APBEN0_AFIO,
 *             CKCU_APBEN0_EXTI, CKCU_APBEN0_PA , CKCU_APBEN0_PB
 * @param Cmd: new status of the peripheral clock.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_APBPerip0ClockConfig(u32 CKCU_APBP, ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CKCU_APBEN0(CKCU_APBP));
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd == ENABLE)
  {
    CKCU->APBCCR0 |= CKCU_APBP;
  }
  else
  {
    CKCU->APBCCR0 &= ~CKCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the APB peripheral 1 clock.
 * @param CKCU_APBP: Specify the APB peripheral 1.
 *        This parameter can be:
 *        @arg CKCU_APBEN1_WDT,  CKCU_APBEN1_RTC,  CKCU_APBEN1_GPTM0, CKCU_APBEN1_GPTM1,
 *             CKCU_APBEN1_OPA0, CKCU_APBEN1_OPA1, CKCU_APBEN1_ADC
 * @param Cmd: new status of the peripheral clock.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_APBPerip1ClockConfig(u32 CKCU_APBP, ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CKCU_APBEN1(CKCU_APBP));
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd == ENABLE)
  {
    CKCU->APBCCR1 |= CKCU_APBP;
  }
  else
  {
    CKCU->APBCCR1 &= ~CKCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the HSE Clock Monitor function.
 * @param Cmd: new status of the Clock Monitor function.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_CKMCmd(ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  CKCU_BB_CKMEN = Cmd;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the power saving wakeup RC clock.
 * @param Cmd: new status of the power saving wakeup RC clock.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_PSRCWKUPCmd(ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  CKCU_BB_PSRCEN = Cmd;
}

/*********************************************************************************************************//**
 * @brief Select the output clock source through the CKOUT pin.
 * @param CKOUTInit: pointer to CKCU_CKOUTInitTypeDef structure that
 *                   contains the configuration information for the specific output clock source.
 * @retval None
 ************************************************************************************************************/
void CKCU_CKOUTConfig(CKCU_CKOUTInitTypeDef *CKOUTInit)
{
  CKCU_BF_WRITE(CKCU->GCFGR, CKCU_MASK_CKOUTSRC, CKCU_POS_CKOUTSRC, CKOUTInit->CKOUTSRC);
}

/*********************************************************************************************************//**
 * @brief Check if the specified CKCU interrupt has occurred.
 * @param CKCU_INT: Specify the CKCU interrupt source.
 *        This parameter can be:
 *        @arg CKCU_INT_CKS
 *        @arg CKCU_INT_PLLRDY
 *        @arg CKCU_INT_HSERDY
 *        @arg CKCU_INT_HSIRDY
 *        @arg CKCU_INT_LSERDY
 *        @arg CKCU_INT_LSIRDY
 * @retval The status of CKCU_INT, SET or RESET.
 ************************************************************************************************************/
FlagStatus CKCU_GetIntStatus(u8 CKCU_INT)
{
  FlagStatus RetValue;
  
  /* Check the parameters */
  Assert_Param(IS_CKCU_INT_FLAG(CKCU_INT));

  if ( (CKCU->GCIR & CKCU_INT) == RESET )
  {
    RetValue = RESET;
  }
  else
  {
    RetValue = SET;
  }

  return RetValue;
}

/*********************************************************************************************************//**
 * @brief Clear the CKCU interrupt flag.
 * @param CKCU_INT: Specify the CKCU interrupt flag to clear.
 *        This parameter can be:
 *        @arg CKCU_INT_CKS   : HSE clock failure interrupt (NMI) flag
 *        @arg CKCU_INT_PLLRDY: PLL ready interrupt flag
 *        @arg CKCU_INT_HSERDY: HSE ready interrupt flag
 *        @arg CKCU_INT_HSIRDY: HSI ready interrupt flag
 *        @arg CKCU_INT_LSERDY: LSE ready interrupt flag
 *        @arg CKCU_INT_LSIRDY: LSI ready interrupt flag
 * @retval None
 ************************************************************************************************************/
void CKCU_ClearIntFlag(u8 CKCU_INT)
{
  /* Check the parameters */
  Assert_Param(IS_CKCU_INT_FLAG(CKCU_INT));
   
  CKCU->GCIR |= CKCU_INT;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified CKCU interrupts.
 * @param CKCU_INT: Specify the CKCU interrupt source which is enabled or disabled.
 *        This parameter can be:
 *        @arg CKCU_INT_CKSIE    : HSE clock failure interrupt (NMI)
 *        @arg CKCU_INT_PLLRDYIE : PLL ready interrupt
 *        @arg CKCU_INT_HSERDYIE : HSE ready interrupt
 *        @arg CKCU_INT_HSIRDYIE : HSI ready interrupt
 *        @arg CKCU_INT_LSERDYIE : LSE ready interrupt
 *        @arg CKCU_INT_LSIRDYIE : LSI ready interrupt
 * @param Cmd: new status of the specific CKCU interrupts.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_IntConfig(u32 CKCU_INT, ControlStatus Cmd)
{
  u32 tmp1;
  
  /* Check the parameters */
  Assert_Param(IS_CKCU_INT(CKCU_INT));
  Assert_Param(IS_CONTROL_STATUS(Cmd));

  tmp1 = CKCU->GCIR;
  if (Cmd != DISABLE)
  {
    tmp1 |= CKCU_INT;
  }
  else
  {
    tmp1 &= ~CKCU_INT;
  }

  /* Note: CKCU interrupt flags will be cleared by writing "1". */
  tmp1 &= ~0x0000007D;
  CKCU->GCIR = tmp1;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable SRAM/FMC clock during Sleep mode.
 * @param CKCU_CLK: Specify the clock which is enabled or disabled.
 *        This parameter can be:
 *        @arg CKCU_AHBEN_SLEEP_FMC, CKCU_AHBEN_SLEEP_SRAM
 * @param Cmd: new status of the specific clocks.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_SleepClockConfig(u32 CKCU_CLK, ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CKCU_SLEEP_AHB(CKCU_CLK));
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd == ENABLE)
  {
    CKCU->AHBCCR |= CKCU_CLK;
  }
  else
  {
    CKCU->AHBCCR &= ~CKCU_CLK;
  }
}

/*********************************************************************************************************//**
 * @brief Check if PLL clock is being used by the specified target source.
 * @param Target: Specify the target clock.
 *        This parameter can be:
 *        @arg CKCU_PLLST_SYSCK : Is PLL used by system clock
 * @retval The status of target clock, TRUE or FALSE.
 ************************************************************************************************************/
bool CKCU_IS_PLL_USED(CKCU_PLLST_TypeDef Target)
{
  u32 temp;

  temp = (CKCU->CKST >> 8) & ((u32)Target);
  if (temp != FALSE)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*********************************************************************************************************//**
 * @brief Check if HSI clock is being used by the specified target source.
 * @param Target: Specify the target clock.
 *        This parameter can be:
 *        @arg CKCU_HSIST_SYSCK: Is HSI used by system clock
 *        @arg CKCU_HSIST_PLL  : Is HSI used by PLL
 *        @arg CKCU_HSIST_CKM  : Is HSI used by clock monitor
 * @retval The status of target clock, TRUE or FALSE.
 ************************************************************************************************************/
bool CKCU_IS_HSI_USED(CKCU_HSIST_TypeDef Target)
{
  u32 temp;

  temp = (CKCU->CKST >> 24) & ((u32)Target);
  if (temp != FALSE)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*********************************************************************************************************//**
 * @brief Check if HSE clock is being used by the specified target source.
 * @param Target: Specify the target clock.
 *        This parameter can be:
 *        @arg CKCU_HSEST_SYSCK : Is HSE used by system clock
 *        @arg CKCU_HSEST_PLL   : Is HSE used by PLL
 * @retval The status of target clock, TRUE or FALSE.
 ************************************************************************************************************/
bool CKCU_IS_HSE_USED(CKCU_HSEST_TypeDef Target)
{
  u32 temp;

  temp = (CKCU->CKST >> 16) & (u32)Target;
  if (temp != FALSE)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified debug function.
 * @param CKCU_DBGx: Specify the debug functions to be enabled or disabled.
 *        This parameter can be:
 *        @arg CKCU_DBG_SLEEP         , CKCU_DBG_DEEPSLEEP1
 *             CKCU_DBG_POWERDOWN     , CKCU_DBG_DEEPSLEEP2
 *             CKCU_DBG_WDT_HALT      , CKCU_DBG_GPTM0_HALT
 *             CKCU_DBG_GPTM1_HALT
 *             CKCU_DBG_USART_TIMEOUT , CKCU_DBG_SPI_TIMEOUT
 * @param Cmd: new status of the debug functions.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_MCUDBGConfig(u16 CKCU_DBGx, ControlStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CKCU_DBG(CKCU_DBGx));
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd != DISABLE)
  {
    CKCU->MCUDBGCR |= (u32)CKCU_DBGx;
  }
  else
  {
    CKCU->MCUDBGCR &= ~((u32)CKCU_DBGx);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Backup domain isolation control.
 * @param Cmd: new status of isolation control.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void CKCU_BKISOCmd(EventStatus Cmd)
{
  /* Check the parameters */
  Assert_Param(IS_CONTROL_STATUS(Cmd));
  
  if (Cmd == DISABLE)
  {
    CKCU_BB_BKISO = 1;  /* Backup domain is accessible by other power domain */
  }
  else
  {
    CKCU_BB_BKISO = 0;  /* Backup domain is isolated from other power domain */
  }
}

/**
  * @}
  */  /* End of CKCU_Private_Function group */

/**
  * @}
  */  /* End of CKCU peripheral group */

/**
  * @}
  */  /* End of HT32F125x_Peripheral_Driver group */
