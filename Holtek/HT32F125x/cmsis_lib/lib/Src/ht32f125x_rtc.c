/*********************************************************************************************************//**
 * @file    ht32f125x_rtc.c
 * @version V1.0
 * @date    04/11/2011
 * @brief   This file provides all the firmware functions about RTC.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f125x_rtc.h"

/** @addtogroup HT32F125x_Peripheral_Driver HT32F125x Peripheral Driver
  * @{
  */

/** @defgroup RTC RTC
  * @brief RTC driver modules
  * @{
  */

/** @defgroup RTC_Private_TypesDefinitions RTC private types definitions
  * @{
  */
/**
  * @} End of RTC_Private_TypesDefinitions group
  */

/** @defgroup RTC_Private_Define RTC private definitions
  * @{
  */

#define RTC_CR_ADDR   (RTC_BASE + 0x008)
#define BB_RTCEN    BitBand(RTC_CR_ADDR, 0)
#define BB_RTCSRC   BitBand(RTC_CR_ADDR, 1)
#define BB_LSI_EN   BitBand(RTC_CR_ADDR, 2)
#define BB_LSE_EN   BitBand(RTC_CR_ADDR, 3)
#define BB_CMPCLR   BitBand(RTC_CR_ADDR, 4)
#define BB_SOP      BitBand(RTC_CR_ADDR, 5)
#define BB_ROEN     BitBand(RTC_CR_ADDR, 16)
#define BB_ROES     BitBand(RTC_CR_ADDR, 17)
#define BB_ROWM     BitBand(RTC_CR_ADDR, 18)
#define BB_ROAP     BitBand(RTC_CR_ADDR, 19)
#define BB_ROLF     BitBand(RTC_CR_ADDR, 20)
#define RPRE_MASK   0xF0FF

/**
  * @} End of RTC_Private_Define group
  */

/** @defgroup RTC_Private_Macro RTC private macros
  * @{
  */
/**
  * @} End of RTC_Private_Macro group
  */

/** @defgroup RTC_Private_Variable RTC private variables
  * @{
  */
/**
  * @} End of RTC_Private_Variable group
  */

/** @defgroup RTC_Private_Function_Prototype RTC private function prototypes
  * @{
  */
/**
  * @} End of RTC_Private_Function_Prototype group
  */

/** @defgroup RTC_Private_Function RTC private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitialize the RTC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void RTC_DeInit(void)
{
  vu32 tmp = 0;

  RTC->CR = 0x00000004;
  RTC->CMP = 0x0;
  RTC->IWEN = 0x0;
  RTC->CR |= 0x00000005;
  while(RTC->CNT);
  RTC->CR = 0x00000F04;
  tmp = RTC->SR;
}

/*********************************************************************************************************//**
 * @brief Select RTC timer clock source.
 * @param Source: Specify the clock source of RTC and backup domain.
 *   @arg RTC_SRC_LSI : Low speed internal clock.
 *   @arg RTC_SRC_LSE : Low speed external clock.
 * @retval None
 ************************************************************************************************************/
void RTC_ClockSourceConfig(RTC_SRC_Enum Source)
{
  Assert_Param(IS_RTC_SRC(Source));

  BB_RTCSRC = Source ;
}

/*********************************************************************************************************//**
 * @brief Load the LSI trim data.
 * @retval None
 ************************************************************************************************************/
void RTC_LSILoadTrimData(void)
{
  u32 i = 7200;
  BB_LSI_EN = 0 ;

  /* Insert a delay must > 1 CK_RTC */
  while(i--);
  BB_LSI_EN = 1 ;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LSI clock.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_LSICmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState == DISABLE)
  {
    BB_LSI_EN = 0;
  }
  else
  {
    BB_LSI_EN = 1;
  }
}

/*********************************************************************************************************//**
 * @brief Select LSE startup mode.
 * @param Mode: Specify the LSE startup mode.
 *   @arg RTC_LSESM_NORMAL : Less power consumption but longer startup time.
 *   @arg RTC_LSESM_FAST : Shorter startup time but higher power consumption.
 * @retval None
 ************************************************************************************************************/
void RTC_LSESMConfig(RTC_LSESM_Enum Mode)
{
  Assert_Param(IS_RTC_LSESM(Mode));

  BB_SOP = Mode;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LSE clock.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_LSECmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState == DISABLE)
  {
    BB_LSE_EN = 0;
  }
  else
  {
    BB_LSE_EN = 1;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable RTC counter cleared by compare match function.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_CMPCLRCmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  BB_CMPCLR = NewState ;
}

/*********************************************************************************************************//**
 * @brief Configure RTC prescaler to a specified value.
 * @param Psc: Value of RTC prescaler.
 *   This parameter can be one of following values:
 *   @arg RTC_RPRE_1
 *   @arg RTC_RPRE_2
 *   @arg RTC_RPRE_4
 *   @arg RTC_RPRE_8
 *   @arg RTC_RPRE_16
 *   @arg RTC_RPRE_32
 *   @arg RTC_RPRE_64
 *   @arg RTC_RPRE_128
 *   @arg RTC_RPRE_256
 *   @arg RTC_RPRE_512
 *   @arg RTC_RPRE_1024
 *   @arg RTC_RPRE_2048
 *   @arg RTC_RPRE_4096
 *   @arg RTC_RPRE_8192
 *   @arg RTC_RPRE_16384
 *   @arg RTC_RPRE_32768
 * @retval None
 ************************************************************************************************************/
void RTC_SetPrescaler(RTC_RPRE_Enum Psc)
{
  Assert_Param(IS_RTC_PSC(Psc));

  RTC->CR = (RTC->CR & RPRE_MASK) | Psc ;
}

/*********************************************************************************************************//**
 * @brief Return the value of divider.
 * @return The prescaler value. It is powered by 2 and max.is 32768.
 ************************************************************************************************************/
u16 RTC_GetPrescaler(void)
{
  u32 prescaler ;

  prescaler = RTC->CR >> 8 ;

  return ((u16)0x1 << prescaler) ;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable RTC timer.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_Cmd(ControlStatus NewState)
{
  BB_RTCEN = NewState ;
}

/*********************************************************************************************************//**
 * @brief Return the counter value of RTC timer.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 RTC_GetCounter(void)
{
  return RTC->CNT ;
}

/*********************************************************************************************************//**
 * @brief Configure the compare match value.
 * @param Compare: Between 0x0 ~ 0xFFFFFFFF
 * @retval None
 ************************************************************************************************************/
void RTC_SetCompare(u32 Compare)
{
  RTC->CMP = Compare ;
}

/*********************************************************************************************************//**
 * @brief Return the compare match value of RTC timer.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 RTC_GetCompare(void)
{
  return RTC->CMP ;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified wakeup source.
 * @param RTC_WAKEUP Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *   @arg RTC_WAKEUP_CSEC : Waken up by counter counting.
 *   @arg RTC_WAKEUP_CM   : Waken up by counter compare match with CMP register.
 *   @arg RTC_WAKEUP_OV   : Waken up by conuter overflow.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
 void RTC_WakeupConfig(u32 RTC_WAKEUP, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_RTC_WAKEUP(RTC_WAKEUP)) ;

  if(NewState != DISABLE)
  {
    RTC->IWEN |= RTC_WAKEUP ;
  }
  else
  {
    RTC->IWEN &= ~RTC_WAKEUP ;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified interrupt source.
 * @param RTC_INT: Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *   @arg RTC_INT_CSEC  : Assert interrupt at counter counting.
 *   @arg RTC_INT_CM    : Assert interrupt at conuter compare match with CMP register.
 *   @arg RTC_INT_OV    : Assert interrupt at conuter overflow.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_IntConfig(u32 RTC_INT, ControlStatus NewState)
{
  /* Check the parameters */
  Assert_Param(IS_RTC_INT(RTC_INT)) ;

  if(NewState != DISABLE)
  {
    RTC->IWEN |= RTC_INT ;
  }
  else
  {
    RTC->IWEN &= ~RTC_INT ;
  }
}

/*********************************************************************************************************//**
 * @brief Return the RTC flags.
 * @return RTC_STS register value. The value can be any combination of the following.
 *   - 0x0 : No flag set
 *   - 0x1 : Count flag
 *   - 0x2 : Match flag
 *   - 0x4 : Overflow flag
 * @note RTC_SR is cleared by read action.
 ************************************************************************************************************/
u8 RTC_GetFlagStatus(void)
{
  return (u8)RTC->SR ;
}

/*********************************************************************************************************//**
 * @brief Configure the RTC output function.
 * @param WMode: Specify the RTC output waveform mode
 *    @arg RTC_ROWM_PULSE: Pulse mode
 *    @arg RTC_ROWM_LEVEL: Level mode
 * @param EventSel: Specify the RTC output event selection
 *    @arg RTC_ROES_MATCH: Compare match selected
 *    @arg RTC_ROES_SECOND: Second clock selected
 * @param Pol: Specify the RTC output active polarity
 *    @arg RTC_ROAP_HIGH: Active level is high
 *    @arg RTC_ROAP_LOW: Active level is low
 * @note This function will disable RTC output first.
 ************************************************************************************************************/
void RTC_OutConfig(RTC_ROWM_Enum WMode, RTC_ROES_Enum EventSel, RTC_ROAP_Enum Pol)
{
  Assert_Param(IS_RTC_ROWM(WMode));
  Assert_Param(IS_RTC_ROES(EventSel));
  Assert_Param(IS_RTC_ROAP(Pol));

  BB_ROEN = 0;
  BB_ROWM = WMode;
  BB_ROES = EventSel;
  BB_ROAP = Pol;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable RTC output.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_OutCmd(ControlStatus NewState)
{
  Assert_Param(IS_CONTROL_STATUS(NewState));

  BB_ROEN = NewState;
}

/*********************************************************************************************************//**
 * @brief Return the RTCOUT level mode flag.
 * @retval SET or RESET
 * @note Reading RTC_CR action will clear ROLF flag.
 ************************************************************************************************************/
FlagStatus RTC_GetOutStatus(void)
{
  return (FlagStatus)BB_ROLF;
}

/**
  * @} End of RTC_Private_Function group
  */

/**
  * @} End of RTC group
  */

/**
  * @} End of HT32F125x_Peripheral_Driver group
  */
