//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.2.1.0
//! \date 12/12/2011
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


#ifndef __XHW_GPIO_H__
#define __XHW_GPIO_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register STM32F1xx GPIO Register
//! \brief Here are the detailed info of GPIO registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_Offsets GPIO Register Offset(Map)
//! \brief Here is the GPIO register offset, users can get the register address
//! through <b>GPIO_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Port configuration register low
//
#define GPIO_CRL                0x00000000  

//
//! Port configuration register high
//
#define GPIO_CRH                0x00000004  

//
//! Port input data registe
//
#define GPIO_IDR                0x00000008 

//
//! Port output data register
//
#define GPIO_ODR                0x0000000C

//
//! Port bit set/reset register
//
#define GPIO_BSRR               0x00000010

//
//! Port bit reset register
//
#define GPIO_BRR                0x00000014

//
//! Port configuration lock register
//
#define GPIO_LCKR               0x00000018

//
//! Event control register 
//
#define AFIO_EVCR               0x40010000

//
//! AF remap and debug I/O configuration register
//
#define AFIO_MAPR               0x40010004

//
//! External interrupt configuration register 1 
//
#define AFIO_EXTICR1            0x40010008

//
//! External interrupt configuration register 2 
//
#define AFIO_EXTICR2            0x4001000C

//
//! External interrupt configuration register 3
//
#define AFIO_EXTICR3            0x40010010

//
//! External interrupt configuration register 4
//
#define AFIO_EXTICR4            0x40010014

//
//! AF remap and debug I/O configuration register2
//
#define AFIO_MAPR2              0x4001001C

//
//! AF remap and debug I/O configuration register2
//
#define AFIO_MAPR2              0x4001001C

//
//! Interrupt mask register (EXTI_IMR)
//
#define EXTI_IMR                0x40010400

//
//! Event mask register (EXTI_EMR)
//
#define EXTI_EMR                0x40010404

//
//! Rising trigger selection register (EXTI_RTSR)
//
#define EXTI_RTSR               0x40010408

//
//! Falling trigger selection register (EXTI_FTSR)
//
#define EXTI_FTSR               0x4001040C

//
//! Software interrupt event register (EXTI_SWIER)
//
#define EXTI_SWIER              0x40010410

//
//! Pending register (EXTI_PR)
//
#define EXTI_PR                 0x40010414

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_CRL GPIO_CRL 
//! \brief Defines for the bit fields in the GPIO_CRL register.
//! @{
//
//*****************************************************************************

//
//!  Port 0 mode bits mask
//
#define GPIO_CRL_MODE0_M        0x00000003  

//
//!  Port 0 mode bits shift
//
#define GPIO_CRL_MODE0_S        0 

//
//!  Port 0 configuration bits mask
//
#define GPIO_CRL_CNF0_M         0x0000000C  

//
//!  Port 0 configuration bits shift
//
#define GPIO_CRL_CNF0_S         2 

//
//!  Port 1 mode bits mask
//
#define GPIO_CRL_MODE1_M        0x00000030  

//
//!  Port 1 mode bits shift
//
#define GPIO_CRL_MODE1_S        4 

//
//!  Port 1 configuration bits mask
//
#define GPIO_CRL_CNF1_M         0x000000C0  

//
//!  Port 1 configuration bits shift
//
#define GPIO_CRL_CNF1_S         6 

//
//!  Port 2 mode bits mask
//
#define GPIO_CRL_MODE2_M        0x00000300  

//
//!  Port 2 mode bits shift
//
#define GPIO_CRL_MODE2_S        8 

//
//!  Port 2 configuration bits mask
//
#define GPIO_CRL_CNF2_M         0x00000C00  

//
//!  Port 2 configuration bits shift
//
#define GPIO_CRL_CNF2_S         10 

//
//!  Port 3 mode bits mask
//
#define GPIO_CRL_MODE3_M        0x00003000  

//
//!  Port 3 mode bits shift
//
#define GPIO_CRL_MODE3_S        12 

//
//!  Port 3 configuration bits mask
//
#define GPIO_CRL_CNF3_M         0x0000C000  

//
//!  Port 3 configuration bits shift
//
#define GPIO_CRL_CNF3_S         14 

//
//!  Port 4 mode bits mask
//
#define GPIO_CRL_MODE4_M        0x00030000  

//
//!  Port 4 mode bits shift
//
#define GPIO_CRL_MODE4_S        16 

//
//!  Port 4 configuration bits mask
//
#define GPIO_CRL_CNF4_M         0x000C0000  

//
//!  Port 4 configuration bits shift
//
#define GPIO_CRL_CNF4_S         18 

//
//!  Port 5 mode bits mask
//
#define GPIO_CRL_MODE5_M        0x00300000  

//
//!  Port 5 mode bits shift
//
#define GPIO_CRL_MODE5_S        20 

//
//!  Port 5 configuration bits mask
//
#define GPIO_CRL_CNF5_M         0x00C00000  

//
//!  Port 5 configuration bits shift
//
#define GPIO_CRL_CNF5_S         22 

//
//!  Port 6 mode bits mask
//
#define GPIO_CRL_MODE6_M        0x03000000  

//
//!  Port 6 mode bits shift
//
#define GPIO_CRL_MODE6_S        24 

//
//!  Port 6 configuration bits mask
//
#define GPIO_CRL_CNF6_M         0x0C000000  

//
//!  Port 6 configuration bits shift
//
#define GPIO_CRL_CNF6_S         26 

//
//!  Port 7 mode bits mask
//
#define GPIO_CRL_MODE7_M        0x30000000  

//
//!  Port 7 mode bits shift
//
#define GPIO_CRL_MODE7_S        28 

//
//!  Port 7 configuration bits mask
//
#define GPIO_CRL_CNF7_M         0xC0000000  

//
//!  Port 7 configuration bits shift
//
#define GPIO_CRL_CNF7_S         30 


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_CRH GPIO_CRH 
//! \brief Defines for the bit fields in the GPIO_CRH register.
//! @{
//
//*****************************************************************************

//
//!  Port 8 mode bits mask
//
#define GPIO_CRH_MODE8_M        0x00000003  

//
//!  Port 8 mode bits shift
//
#define GPIO_CRH_MODE8_S        0 

//
//!  Port 8 configuration bits mask
//
#define GPIO_CRH_CNF8_M         0x0000000C  

//
//!  Port 8 configuration bits shift
//
#define GPIO_CRH_CNF8_S         2 

//
//!  Port 9 mode bits mask
//
#define GPIO_CRH_MODE9_M        0x00000030  

//
//!  Port 9 mode bits shift
//
#define GPIO_CRH_MODE9_S        4 

//
//!  Port 9 configuration bits mask
//
#define GPIO_CRH_CNF9_M         0x000000C0  

//
//!  Port 9 configuration bits shift
//
#define GPIO_CRH_CNF9_S         6 

//
//!  Port 10 mode bits mask
//
#define GPIO_CRH_MODE10_M       0x00000300  

//
//!  Port 10 mode bits shift
//
#define GPIO_CRH_MODE10_S       8 

//
//!  Port 10 configuration bits mask
//
#define GPIO_CRH_CNF10_M        0x00000C00  

//
//!  Port 10 configuration bits shift
//
#define GPIO_CRH_CNF10_S        10 

//
//!  Port 11 mode bits mask
//
#define GPIO_CRH_MODE11_M       0x00003000  

//
//!  Port 11 mode bits shift
//
#define GPIO_CRH_MODE11_S       12 

//
//!  Port 11 configuration bits mask
//
#define GPIO_CRH_CNF11_M        0x0000C000  

//
//!  Port 11 configuration bits shift
//
#define GPIO_CRH_CNF11_S        14 

//
//!  Port 12 mode bits mask
//
#define GPIO_CRH_MODE12_M       0x00030000  

//
//!  Port 12 mode bits shift
//
#define GPIO_CRH_MODE12_S       16 

//
//!  Port 12 configuration bits mask
//
#define GPIO_CRH_CNF12_M        0x000C0000  

//
//!  Port 12 configuration bits shift
//
#define GPIO_CRH_CNF12_S        18 

//
//!  Port 13 mode bits mask
//
#define GPIO_CRH_MODE13_M       0x00300000  

//
//!  Port 13 mode bits shift
//
#define GPIO_CRH_MODE13_S       20 

//
//!  Port 13 configuration bits mask
//
#define GPIO_CRH_CNF13_M        0x00C00000  

//
//!  Port 13 configuration bits shift
//
#define GPIO_CRH_CNF13_S        22 

//
//!  Port 14 mode bits mask
//
#define GPIO_CRH_MODE14_M       0x03000000  

//
//!  Port 14 mode bits shift
//
#define GPIO_CRL_MODE14_S       24 

//
//!  Port 14 configuration bits mask
//
#define GPIO_CRL_CNF14_M        0x0C000000  

//
//!  Port 14 configuration bits shift
//
#define GPIO_CRH_CNF14_S        26 

//
//!  Port 15 mode bits mask
//
#define GPIO_CRH_MODE15_M       0x30000000  

//
//!  Port 15 mode bits shift
//
#define GPIO_CRH_MODE15_S       28 

//
//!  Port 15 configuration bits mask
//
#define GPIO_CRH_CNF15_M        0xC0000000  

//
//!  Port 15 configuration bits shift
//
#define GPIO_CRH_CNF15_S        30 


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_IDR GPIO_IDR 
//! \brief Defines for the bit fields in the GPIO_IDR register.
//! @{
//
//*****************************************************************************

//
//!  Port input data mask
//
#define GPIO_IDR_IDR_M          0x0000FFFF  

//
//!  Port input data shift
//
#define GPIO_IDR_IDR_S          0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_ODR GPIO_ODR 
//! \brief Defines for the bit fields in the GPIO_ODR register.
//! @{
//
//*****************************************************************************

//
//!  Port input data mask
//
#define GPIO_ODR_ODR_M          0x0000FFFF  

//
//!  Port input data shift
//
#define GPIO_ODR_ODR_S          0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_BSRR GPIO_BSRR 
//! \brief Defines for the bit fields in the GPIO_BSRR register.
//! @{
//
//*****************************************************************************

//
//!  Port x Reset bit mask
//
#define GPIO_BSRR_BS_M          0x0000FFFF  

//
//!  Port x Reset bit shift
//
#define GPIO_BSRR_BS_S          0 

//
//!  Port x Set bit mask
//
#define GPIO_BSRR_BR_M          0xFFFF0000  

//
//!  Port x Set bit shift
//
#define GPIO_BSRR_BR_S          16 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_BRR GPIO_BRR 
//! \brief Defines for the bit fields in the GPIO_BRR register.
//! @{
//
//*****************************************************************************

//
//!  Port x Reset bit mask
//
#define GPIO_BRR_BR_M           0x0000FFFF  

//
//!  Port x Reset bit shift
//
#define GPIO_BRR_BR_S           0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_GPIO_LCKR GPIO_LCKR 
//! \brief Defines for the bit fields in the GPIO_LCKR register.
//! @{
//
//*****************************************************************************

//
//!  Port x Lock key
//
#define GPIO_LCKR_KEY           0x00010000  

//
//!  Port x Lock bit mask
//
#define GPIO_LCKR_LCK_M         0x0000FFFF  

//
//!  Port x Lock bit shift
//
#define GPIO_LCKR_LCK_S         0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_EVCR AFIO_EVCR 
//! \brief Defines for the bit fields in the AFIO_EVCR register.
//! @{
//
//*****************************************************************************

//
//!  Event output enable
//
#define AFIO_EVCR_EVOE          0x00000080 

//
//!  Port selection mask
//
#define AFIO_EVCR_PORT_M        0x00000070  

//
//!  Port selection shift
//
#define AFIO_EVCR_PORT_S        4 

//
//!  Pin selection mask
//
#define AFIO_EVCR_PIN_M         0x0000000F  

//
//!  Pin selection shift
//
#define AFIO_EVCR_PIN_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_MAPR AFIO_MAPR 
//! \brief Defines for the bit fields in the AFIO_MAPR register.
//! @{
//
//*****************************************************************************

//
//!  Serial wire JTAG configuration mask
//
#define AFIO_MAPR_SWJCFG_M      0x07000000  

//
//!  Full SWJ (JTAG-DP + SW-DP): Reset State
//
#define AFIO_MAPR_SWJCFG_FULLR  0x00000000

//
//!  Full SWJ (JTAG-DP + SW-DP) but without NJTRST
//
#define AFIO_MAPR_SWJCFG_FULLN  0x01000000

//
//!  JTAG-DP Disabled and SW-DP Enabled
//
#define AFIO_MAPR_SWJCFG_SWDP   0x02000000

//
//!  JTAG-DP Disabled and SW-DP Enabled
//
#define AFIO_MAPR_SWJCFG_JTAG   0x04000000

//
//!  Serial wire JTAG configuration shift
//
#define AFIO_MAPR_SWJCFG_S      24 

//
//!  ADC 2 external trigger regular conversion remapping
//
#define AFIO_MAPR_ADC2_ETRGREG_REMAP                                          \
                                0x00100000

//
//!  ADC 2 external trigger injected conversion remapping
//
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP                                          \
                                0x00080000

//
//!  ADC 1 external trigger regular conversion remapping
//
#define AFIO_MAPR_ADC1_ETRGREG_REMAP                                          \
                                0x00040000

//
//!  ADC 1 external trigger injected conversion remapping
//
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP                                          \
                                0x00020000

//
//!  TIM5 channel4 internal remap
//
#define AFIO_MAPR_TIM5CH4_IREMAP                                              \
                                0x00010000

//
//!  Port D0/Port D1 mapping on OSC_IN/OSC_OUT
//
#define AFIO_MAPR_PD01_REMAP    0x00008000

//
//!  CAN alternate function remapping mask
//
#define AFIO_MAPR_CAN_REMAP_M   0x00006000

//
//!  CAN alternate function remapping shift
//
#define AFIO_MAPR_CAN_REMAP_S   13

//
//!  TIM4 remapping
//
#define AFIO_MAPR_TIM4_REMAP    0x00001000

//
//!  TIM3 remapping mask
//
#define AFIO_MAPR_TIM3_REMAP_M  0x00000C00

//
//!  TIM3 remapping shift
//
#define AFIO_MAPR_TIM3_REMAP_S  10

//
//!  TIM2 remapping mask
//
#define AFIO_MAPR_TIM2_REMAP_M  0x00000300

//
//!  TIM2 remapping shift
//
#define AFIO_MAPR_TIM2_REMAP_S  8

//
//!  TIM1 remapping mask
//
#define AFIO_MAPR_TIM1_REMAP_M  0x000000C0

//
//!  TIM1 remapping shift
//
#define AFIO_MAPR_TIM1_REMAP_S  6

//
//!  USART3 remapping mask
//
#define AFIO_MAPR_USART3_REMAP_M                                              \
                                0x00000030

//
//!  USART3 remapping shift
//
#define AFIO_MAPR_USART3_REMAP_S                                              \
                                4

//
//!  USART2 remapping 
//
#define AFIO_MAPR_USART2_REMAP  0x00000008

//
//!  USART1 remapping 
//
#define AFIO_MAPR_USART1_REMAP  0x00000004

//
//!  I2C1 remapping 
//
#define AFIO_MAPR_I2C1_REMAP    0x00000002

//
//!  SPI1 remapping 
//
#define AFIO_MAPR_SPI1_REMAP    0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_EXTICR1 AFIO_EXTICR1 
//! \brief Defines for the bit fields in the AFIO_EXTICR1 register.
//! @{
//
//*****************************************************************************

//
//!  EXTI 0 configuration mask
//
#define AFIO_EXTICR1_EXTI0_M    0x0000000F

//
//!  EXTI 0 configuration shift
//
#define AFIO_EXTICR1_EXTI0_S    0

//
//!  EXTI 1 configuration mask
//
#define AFIO_EXTICR1_EXTI1_M    0x000000F0

//
//!  EXTI 1 configuration shift
//
#define AFIO_EXTICR1_EXTI1_S    4

//
//!  EXTI 2 configuration mask
//
#define AFIO_EXTICR1_EXTI2_M    0x00000F00

//
//!  EXTI 2 configuration shift
//
#define AFIO_EXTICR1_EXTI2_S    8

//
//!  EXTI 3 configuration mask
//
#define AFIO_EXTICR1_EXTI3_M    0x0000F000

//
//!  EXTI 3 configuration shift
//
#define AFIO_EXTICR1_EXTI3_S    12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_EXTICR2 AFIO_EXTICR2 
//! \brief Defines for the bit fields in the AFIO_EXTICR2 register.
//! @{
//
//*****************************************************************************

//
//!  EXTI 4 configuration mask
//
#define AFIO_EXTICR2_EXTI4_M    0x0000000F

//
//!  EXTI 4 configuration shift
//
#define AFIO_EXTICR2_EXTI4_S    0

//
//!  EXTI 5 configuration mask
//
#define AFIO_EXTICR2_EXTI5_M    0x000000F0

//
//!  EXTI 5 configuration shift
//
#define AFIO_EXTICR2_EXTI5_S    4

//
//!  EXTI 6 configuration mask
//
#define AFIO_EXTICR2_EXTI6_M    0x00000F00

//
//!  EXTI 6 configuration shift
//
#define AFIO_EXTICR2_EXTI6_S    8

//
//!  EXTI 7 configuration mask
//
#define AFIO_EXTICR2_EXTI7_M    0x0000F000

//
//!  EXTI 7 configuration shift
//
#define AFIO_EXTICR2_EXTI7_S    12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_EXTICR3 AFIO_EXTICR3 
//! \brief Defines for the bit fields in the AFIO_EXTICR3 register.
//! @{
//
//*****************************************************************************

//
//!  EXTI 8 configuration mask
//
#define AFIO_EXTICR3_EXTI8_M    0x0000000F

//
//!  EXTI 8 configuration shift
//
#define AFIO_EXTICR3_EXTI8_S    0

//
//!  EXTI 9 configuration mask
//
#define AFIO_EXTICR3_EXTI9_M    0x000000F0

//
//!  EXTI 9 configuration shift
//
#define AFIO_EXTICR3_EXTI9_S    4

//
//!  EXTI 10 configuration mask
//
#define AFIO_EXTICR3_EXTI10_M   0x00000F00

//
//!  EXTI 10 configuration shift
//
#define AFIO_EXTICR3_EXTI10_S   8

//
//!  EXTI 11 configuration mask
//
#define AFIO_EXTICR3_EXTI11_M   0x0000F000

//
//!  EXTI 11 configuration shift
//
#define AFIO_EXTICR3_EXTI11_S   12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_EXTICR4 AFIO_EXTICR4 
//! \brief Defines for the bit fields in the AFIO_EXTICR4 register.
//! @{
//
//*****************************************************************************

//
//!  EXTI 12 configuration mask
//
#define AFIO_EXTICR4_EXTI12_M   0x0000000F

//
//!  EXTI 12 configuration shift
//
#define AFIO_EXTICR4_EXTI12_S   0

//
//!  EXTI 13 configuration mask
//
#define AFIO_EXTICR4_EXTI13_M   0x000000F0

//
//!  EXTI 13 configuration shift
//
#define AFIO_EXTICR4_EXTI13_S   4

//
//!  EXTI 14 configuration mask
//
#define AFIO_EXTICR4_EXTI14_M   0x00000F00

//
//!  EXTI 14 configuration shift
//
#define AFIO_EXTICR4_EXTI14_S   8

//
//!  EXTI 15 configuration mask
//
#define AFIO_EXTICR4_EXTI15_M   0x0000F000

//
//!  EXTI 15 configuration shift
//
#define AFIO_EXTICR4_EXTI15_S   12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_AFIO_MAPR2 AFIO_MAPR2 
//! \brief Defines for the bit fields in the AFIO_MAPR2 register.
//! @{
//
//*****************************************************************************

//
//!  NADV connect/disconnect
//
#define AFIO_MAPR2_FSMC_NADV    0x00000400

//
//!  TIM14 remapping
//
#define AFIO_MAPR2_TIM14_REMAP  0x00000200

//
//!  TIM13 remapping
//
#define AFIO_MAPR2_TIM13_REMAP  0x00000100

//
//!  TIM11 remapping
//
#define AFIO_MAPR2_TIM11_REMAP  0x00000080

//
//!  TIM10 remapping
//
#define AFIO_MAPR2_TIM10_REMAP  0x00000040

//
//!  TIM9 remapping
//
#define AFIO_MAPR2_TIM9_REMAP   0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_EXTI_IMR EXTI_IMR 
//! \brief Defines for the bit fields in the EXTI_IMR register.
//! @{
//
//*****************************************************************************

//
//!  Interrupt Mask on line all mask
//
#define EXTI_IMR_MRX_M          0x000FFFFF

//
//!  Interrupt Mask on line all shift
//
#define EXTI_IMR_MRX_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_EXTI_EMR EXTI_EMR 
//! \brief Defines for the bit fields in the EXTI_EMR register.
//! @{
//
//*****************************************************************************

//
//!  Event Mask on line all mask
//
#define EXTI_EMR_MRX_M          0x000FFFFF

//
//!  Event Mask on line all shift
//
#define EXTI_EMR_MRX_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_EXTI_RTSR EXTI_RTSR 
//! \brief Defines for the bit fields in the EXTI_RTSR register.
//! @{
//
//*****************************************************************************

//
//!  Rising trigger event configuration bit of line all mask
//
#define EXTI_RTSR_TRX_M         0x000FFFFF

//
//!  Rising trigger event configuration bit of line all shift
//
#define EXTI_RTSR_TRX_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_EXTI_FTSR EXTI_FTSR 
//! \brief Defines for the bit fields in the EXTI_FTSR register.
//! @{
//
//*****************************************************************************

//
//!  Falling trigger event configuration bit of line all mask
//
#define EXTI_FTSR_TRX_M         0x000FFFFF

//
//!  Falling trigger event configuration bit of line all shift
//
#define EXTI_FTSR_TRX_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_EXTI_SWIER EXTI_SWIER 
//! \brief Defines for the bit fields in the EXTI_SWIER register.
//! @{
//
//*****************************************************************************

//
//!  Software interrupt on line all mask
//
#define EXTI_SWIER_SWIERX_M     0x000FFFFF

//
//!  Software interrupt on line all shift
//
#define EXTI_SWIER_SWIERX_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Register_EXTI_PR EXTI_PR 
//! \brief Defines for the bit fields in the EXTI_PR register.
//! @{
//
//*****************************************************************************

//
//!  Software interrupt on line all mask
//
#define EXTI_PR_PRX_M           0x000FFFFF

//
//!  Software interrupt on line all shift
//
#define EXTI_PR_PRX_S           0

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
#endif // __XHW_GPIO_H__
