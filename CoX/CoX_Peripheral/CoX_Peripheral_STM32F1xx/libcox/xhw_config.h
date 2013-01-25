//*****************************************************************************
//
//! \file xhw_config.h
//! \brief Common configuratio.
//! \version V2.2.1.0
//! \date 07/04/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef __XHW_CONFIG_H__
#define __XHW_CONFIG_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer_Exported_Config xLowLayer Config
//! \brief Some Config.
//! @{
//
//*****************************************************************************

//
//! xRTC counter config.
//
#define xRTC_COUNTER_CONFIG     RTC_COUNTER_CONFIG

//
//! config your HSE external crystal value.
//
#define xHSE_VAL                STM32F1xx_HSE_VAL

//
//! xRTC auto Leap Year config. 
//
#define xRTC_AUTO_LEAPYEAR      RTC_AUTO_LEAPYEAR

//
//! xGPIO intrerrupt nimber config
//
#define xGPIO_INT_NUMBER        GPIO_INT_NUMBER

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_LowLayer_Exported_Config STM32F1xx Config
//! \brief Some Config.
//! @{
//
//*****************************************************************************

//
//! config your device series.It can be one of the following values: 
//! STM32F10X_LD_VL, STM32F10X_MD_VL, STM32F10X_HD_VL, STM32F10X_XL, STM32F10X_CL
//
#define STM32F1xx_DEVICE        STM32F10X_HD_VL

//
//! config your HSE external crystal value.It can be one of the following values: 
//! 4-16Mhz
//
#define STM32F1xx_HSE_VAL       8


//
//! STM32F1xx APB high-speed prescaler (APB2) division config.
//! It can be one of the following values: 
//! APBCLOCK_DIV_1, APBCLOCK_DIV_2, APBCLOCK_DIV_8, APBCLOCK_DIV_16
//
#define SYSCTL_APB2CLOCK_DIV    APBCLOCK_DIV_2

//
//! STM32F1xx APB low-speed prescaler (APB1) division config.
//! It can be one of the following values: 
//! APBCLOCK_DIV_1, APBCLOCK_DIV_2, APBCLOCK_DIV_8, APBCLOCK_DIV_16
//
#define SYSCTL_APB1CLOCK_DIV    APBCLOCK_DIV_1

//
//! STM32F1xx RTC counter config.
//! It can be one of the following values: 
//! 0 or 1.  0: can read hour minute second directly 
//!          1: can not read hour minute second directly 
//
#define RTC_COUNTER_CONFIG      1

//
//! STM32F1xx RTC auto Leap Year config.
//! It can be one of the following values: 
//! 0 or 1.  0: can read hour minute second directly 
//!          1: auto leap year 
//
#define RTC_AUTO_LEAPYEAR       1


//
//! STM32F1xx GPIO intrerrupt nimber config
//
#define GPIO_INT_NUMBER         8  

//
//! STM32F1xx Timer1 function select
//
#define TIM1_FUNCTION_SELECT    TIM_PWM

//
//! STM32F1xx Timer2 function select
//
#define TIM2_FUNCTION_SELECT    TIM_TIMER

//
//! STM32F1xx Timer3 function select
//
#define TIM3_FUNCTION_SELECT    TIM_TIMER

//
//! STM32F1xx Timer4 function select
//
#define TIM4_FUNCTION_SELECT    TIM_TIMER

//
//! STM32F1xx Timer5 function select
//
#define TIM5_FUNCTION_SELECT    TIM_TIMER

//
//! STM32F1xx Timer8 function select
//
#define TIM8_FUNCTION_SELECT    TIM_PWM

//
//! STM32F1xx Timer9 function select
//
#define TIM9_FUNCTION_SELECT    TIM_TIMER

//
//! STM32F1xx Timer10 function select
//
#define TIM10_FUNCTION_SELECT   TIM_TIMER

//
//! STM32F1xx Timer11 function select
//
#define TIM11_FUNCTION_SELECT   TIM_TIMER

//
//! STM32F1xx Timer12 function select
//
#define TIM12_FUNCTION_SELECT   TIM_TIMER

//
//! STM32F1xx Timer13 function select
//
#define TIM13_FUNCTION_SELECT   TIM_TIMER

//
//! STM32F1xx Timer14 function select
//
#define TIM14_FUNCTION_SELECT   TIM_TIMER

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_LowLayer_Series STM32F1xx series
//! \brief Some Config.
//! @{
//
//*****************************************************************************

//
//! Low-density devices are STM32F101xx, STM32F102xx and STM32F103xx 
//! microcontrollers where the Flash memory density ranges between 16 and 
//! 32 Kbytes.
//
#define STM32F10X_LD_VL         0

//
//! Medium-density devices are STM32F101xx, STM32F102xx and STM32F103xx
//! microcontrollers where the Flash memory density ranges between 64 and
//! 128 Kbytes.
//
#define STM32F10X_MD_VL         1

//
//! High-density devices are STM32F101xx and STM32F103xx microcontrollers
//! where the Flash memory density ranges between 256 and 512 Kbytes.
//
#define STM32F10X_HD_VL         2

//
//! XL-density devices are STM32F101xx and STM32F103xx microcontrollers
//! where the Flash memory density ranges between 768 Kbytes and 1 Mbyte.
//
#define STM32F10X_XL            3

//
//! Connectivity line devices are STM32F105xx and STM32F107xx microcontrollers.
//
#define STM32F10X_CL            4


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_LowLayer_APBDivide  STM32F1xx APB Divide
//! \brief APB clock divided.
//! @{
//
//*****************************************************************************

//
//! APB clock not divided.
//
#define APBCLOCK_DIV_1          0

//
//! APB clock divided by 2.
//
#define APBCLOCK_DIV_2          2

//
//! APB clock divided by 4.
//
#define APBCLOCK_DIV_4          4

//
//! APB clock divided by 8.
//
#define APBCLOCK_DIV_8          8

//
//! APB clock divided by 16.
//
#define APBCLOCK_DIV_16         16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_LowLayer_Tim_Function STM32F1xx timer Function 
//! \brief STM32F1xx timer Function .
//! @{
//
//*****************************************************************************

//
//! timer Function is used as a timer.
//
#define TIM_TIMER               0

//
//! timer Function is used as a PWM.
//
#define TIM_PWM                 1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif // __XHW_CONFIG_H__

