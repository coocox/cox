//*****************************************************************************
//
//! \file xhw_adc.h
//! \brief Macros used when accessing the ADC hardware.
//! \version V2.2.1.0
//! \date 5/31/2012
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

#ifndef __XHW_ADC_H__
#define __XHW_ADC_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register STM32F1xx ADC Register
//! \brief Here are the detailed info of ADC registers. 
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
//! \addtogroup STM32F1xx_ADC_Register_Offset ADC Register Offset(Map)
//! \brief Here is the ADC register offset, users can get the register address
//! through <b>ADC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! ADC Status Register
//
#define ADC_SR                  0x00000000

//
//! ADC Control Register 1
//
#define ADC_CR1                 0x00000004

//
//! ADC Control Register 2
//
#define ADC_CR2                 0x00000008

//
//! ADC Sample time Register 1
//
#define ADC_SMPR1               0x0000000C

//
//! ADC Sample time Register 2
//
#define ADC_SMPR2               0x00000010

//
//! ADC injected channel data offset register 1
//
#define ADC_JOFR1               0x00000014

//
//! ADC injected channel data offset register 2
//
#define ADC_JOFR2               0x00000018

//
//! ADC injected channel data offset register 3
//
#define ADC_JOFR3               0x0000001C

//
//! ADC injected channel data offset register 4
//
#define ADC_JOFR4               0x00000020

//
//! ADC Watchdog High Threshold Register
//
#define ADC_HTR                 0x00000024

//
//! ADC Watchdog low Threshold Register
//
#define ADC_LTR                 0x00000028

//
//! ADC regular sequence register 1 
//
#define ADC_SRQ1                0x0000002C

//
//! ADC regular sequence register 2 
//
#define ADC_SRQ2                0x00000030

//
//! ADC regular sequence register 3 
//
#define ADC_SRQ3                0x00000034

//
//! ADC injected sequence register 
//
#define ADC_JSQR                0x00000038

//
//! ADC injected data register 1
//
#define ADC_JDR1                0x0000003C

//
//! ADC injected data register 2
//
#define ADC_JDR2                0x00000040

//
//! ADC injected data register 3
//
#define ADC_JDR3                0x00000044

//
//! ADC injected data register 4
//
#define ADC_JDR4                0x00000048

//
//! ADC regular data register
//
#define ADC_DR                  0x0000004C
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_AD_SR A/D status Register 1(ADC_SR)
//! \brief Defines for the bit fields in the \ref ADC_SR register.
//! @{
//
//*****************************************************************************

//
//! Regular channel Start flag
//
#define ADC_SR_STRT_FLAG        0x00000010

//
//! Injected channel Start flag
//
#define ADC_SR_JSTRT_FLAG       0x00000008

//
//! Injected channel end of conversion flag
//
#define ADC_SR_JEOC_FLAG        0x00000004

//
//! End of conversion flag
//
#define ADC_SR_EOC_FLAG         0x00000002

//
//! Analog watchdog flag
//
#define ADC_SR_AWD_FLAG         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_AD_CR1 A/D Control Register 1(ADC_CR1)
//! \brief Defines for the bit fields in the \ref ADC_CR1 register.
//! @{
//
//*****************************************************************************

//
//! Analog watchdog enable on regular channels
//
#define ADC_CR1_AWDEN           0x00800000

//
//! Analog watchdog enable on injected channels
//
#define ADC_CR1_JAWDEN          0x00400000

//
//! A/D Dual mode selection Mask
//
#define ADC_CR1_DUALMOD_M       0x000F0000

//
//! A/D Dual mode selection Shift
//
#define ADC_CR1_DUALMOD_S       16

//
//! A/D Dual mode selection: Independent mode
//
#define ADC_CR1_DUALMOD_INDEPENDENT                                           \
                                0x00000000

//
//! A/D Dual mode selection: Combined regular simultaneous + injected simultaneous mode
//
#define ADC_CR1_DUALMOD_REG_INJEC_SIMULT                                      \
                                0x00010000
                                
//
//! A/D Dual mode selection: Combined regular simultaneous + alternate trigger mode
//
#define ADC_CR1_DUALMOD_REG_SIMULT_ALTER                                      \
                                0x00020000

//
//! A/D Dual mode selection: Combined injected simultaneous + fast interleaved mode
//
#define ADC_CR1_DUALMOD_INJEC_SIMULT_FAST                                     \
                                0x00030000
                                
//
//! A/D Dual mode selection: Combined injected simultaneous + slow interleaved mode
//
#define ADC_CR1_DUALMOD_INJEC_SIMULT_SLOW                                     \
                                0x00040000

//
//! A/D Dual mode selection: injected simultaneous mode only
//
#define ADC_CR1_DUALMOD_INJE_SIMULT                                           \
                                0x00050000

//
//! A/D Dual mode selection: Regular simultaneous mode only
//
#define ADC_CR1_DUALMOD_REGU_SIMULT                                           \
                                0x00060000

//
//! A/D Dual mode selection: Fast interleaved mode only
//
#define ADC_CR1_DUALMOD_FAST_INTERL                                           \
                                0x00070000

//
//! A/D Dual mode selection: Slow interleaved mode only
//
#define ADC_CR1_DUALMOD_SLOW_INTERL                                           \
                                0x00080000

//
//! A/D Dual mode selection: Alternate trigger mode only
//
#define ADC_CR1_DUALMOD_ALTER_TRIG                                            \
                                0x00090000
//
//! A/D Discontinuous mode channel count Mask
//
#define ADC_CR1_DISCNUM_M       0x0000E000

//
//! A/D Discontinuous mode channel count Shift
//
#define ADC_CR1_DISCNUM_S       13

//
//! A/D Discontinuous mode channel count:1
//
#define ADC_CR1_DISCNUM_1       0x00000000

//
//! A/D Discontinuous mode channel count:2
//
#define ADC_CR1_DISCNUM_2       0x00002000

//
//! A/D Discontinuous mode channel count:3
//
#define ADC_CR1_DISCNUM_3       0x00004000

//
//! A/D Discontinuous mode channel count:4
//
#define ADC_CR1_DISCNUM_4       0x00006000

//
//! A/D Discontinuous mode channel count:5
//
#define ADC_CR1_DISCNUM_5       0x00008000

//
//! A/D Discontinuous mode channel count:6
//
#define ADC_CR1_DISCNUM_6       0x0000A000

//
//! A/D Discontinuous mode channel count:7
//
#define ADC_CR1_DISCNUM_7       0x0000C000

//
//! A/D Discontinuous mode channel count:8
//
#define ADC_CR1_DISCNUM_8       0x0000E000

//
//! Discontinuous mode on injected channels
//
#define ADC_CR1_JDISCEN         0x00001000

//
//! Discontinuous mode on regular channels
//
#define ADC_CR1_DISCEN          0x00000800

//
//! Automatic Injected Group conversion
//
#define ADC_CR1_JAUTO           0x00000400

//
//! Enable the watchdog on a single channel in scan mode
//
#define ADC_CR1_AWDSGL          0x00000200

//
//! Scan mode
//
#define ADC_CR1_SCAN            0x00000100

//
//! Interrupt enable for injected channels
//
#define ADC_CR1_JEOCIE          0x00000080

//
//! Analog watchdog interrupt enable
//
#define ADC_CR1_AWDIE           0x00000040

//
//! Interrupt enable for EOC
//
#define ADC_CR1_EOCIE           0x00000020

//
//! A/D Analog watchdog channel select bits Mask
//
#define ADC_CR1_AWDCH_M         0x0000001F

//
//! A/D Analog watchdog channel select bits Shift
//
#define ADC_CR1_AWDCH_S         0

//
//! ADC_IN0 is monitored
//
#define ADC_CR1_AWDCH_IN0       0x00000000

//
//! ADC_IN1 is monitored
//
#define ADC_CR1_AWDCH_IN1       0x00000001

//
//! ADC_IN2 is monitored
//
#define ADC_CR1_AWDCH_IN2       0x00000002

//
//! ADC_IN3 is monitored
//
#define ADC_CR1_AWDCH_IN3       0x00000003

//
//! ADC_IN4 is monitored
//
#define ADC_CR1_AWDCH_IN4       0x00000004

//
//! ADC_IN5 is monitored
//
#define ADC_CR1_AWDCH_IN5       0x00000005

//
//! ADC_IN6 is monitored
//
#define ADC_CR1_AWDCH_IN6       0x00000006

//
//! ADC_IN7 is monitored
//
#define ADC_CR1_AWDCH_IN7       0x00000007

//
//! ADC_IN8 is monitored
//
#define ADC_CR1_AWDCH_IN8       0x00000008

//
//! ADC_IN9 is monitored
//
#define ADC_CR1_AWDCH_IN9       0x00000009

//
//! ADC_IN10 is monitored
//
#define ADC_CR1_AWDCH_IN10      0x0000000A

//
//! ADC_IN11 is monitored
//
#define ADC_CR1_AWDCH_IN11      0x0000000B

//
//! ADC_IN12 is monitored
//
#define ADC_CR1_AWDCH_IN12      0x0000000C

//
//! ADC_IN13 is monitored
//
#define ADC_CR1_AWDCH_IN13      0x0000000D

//
//! ADC_IN14 is monitored
//
#define ADC_CR1_AWDCH_IN14      0x0000000E

//
//! ADC_IN15 is monitored
//
#define ADC_CR1_AWDCH_IN15      0x0000000F

//
//! ADC_IN16 is monitored
//
#define ADC_CR1_AWDCH_IN16      0x00000010

//
//! ADC_IN17 is monitored
//
#define ADC_CR1_AWDCH_IN17      0x00000011
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_AD_CR2 A/D Control Register 2(ADC_CR2)
//! \brief Defines for the bit fields in the \ref ADC_CR2 register.
//! @{
//
//*****************************************************************************

//
//! Temperature sensor and VREFINT enable
//
#define ADC_CR2_TSVREFE         0x00800000

//
//! Start conversion of regular channels
//
#define ADC_CR2_SWSTART         0x00400000

//
//! Start conversion of injected channels
//
#define ADC_CR2_JSWSTART        0x00200000

//
//! External trigger conversion mode for regular channels
//
#define ADC_CR2_EXTTRIG         0x00100000

//
//! External event select for regular group Mask
//
#define ADC_CR2_EXTSEL_M        0x000E0000

//
//! A/D Dual mode selection Shift
//
#define ADC_CR2_EXTSEL_S        17

//
//! A/D External event selection: Timer 1 CC1 event
//
#define ADC_CR2_EXTSEL_TIME1_CC1                                              \
                                0x00000000

//
//! A/D External event selection: Timer 1 CC2 event
//
#define ADC_CR2_EXTSEL_TIME1_CC2                                              \
                                0x00020000

//
//! A/D External event selection: Timer 1 CC3 event
//
#define ADC_CR2_EXTSEL_TIME1_CC3                                              \
                                0x00040000

//
//! A/D External event selection: Timer 2 CC2 event
//
#define ADC_CR2_EXTSEL_TIME2_CC2                                              \
                                0x00060000

//
//! A/D External event selection: Timer 3 TRGO event
//
#define ADC_CR2_EXTSEL_TIME3_TRGO                                             \
                                0x00080000

//
//! A/D External event selection: Timer 4 CC4 event
//
#define ADC_CR2_EXTSEL_TIME4_CC4                                              \
                                0x000A0000

//
//! A/D External event selection: EXTI line 11/TIM8_TRGO event
//
#define ADC_CR2_EXTSEL_EXTI_TIM8TRGO                                          \
                                0x000C0000

//
//! External trigger conversion mode for injected channels
//
#define ADC_CR2_JEXTTRIG        0x00008000

//
//! External event select for injected group Mask
//
#define ADC_CR2_JEXTSEL_M       0x00007000

//
//! A/D Dual mode selection Shift
//
#define ADC_CR2_JEXTSEL_S       12

//
//! A/D External event selection for injected group: Timer 1 TRGO event
//
#define ADC_CR2_JEXTSEL_TIME1_TRGO                                            \
                                0x00000000

//
//! A/D External event selection for injected group: Timer 1 CC4 event
//
#define ADC_CR2_JEXTSEL_TIME1_CC4                                             \
                                0x00002000

//
//! A/D External event selection for injected group: Timer 2 TRGO event
//
#define ADC_CR2_JEXTSEL_TIME2_TRGO                                            \
                                0x00004000

//
//! A/D External event selection for injected group: Timer 2 CC1 event
//
#define ADC_CR2_JEXTSEL_TIME2_CC1                                             \
                                0x00006000

//
//! A/D External event selection for injected group: Timer 3 CC4 event
//
#define ADC_CR2_JEXTSEL_TIME3_CC4                                             \
                                0x00008000

//
//! A/D External event selection for injected group: Timer 4 TRGO event
//
#define ADC_CR2_JEXTSEL_TIME4_TRGO                                            \
                                0x0000A000

//
//! A/D External event selection for injected group: EXTI line 15/TIM8_CC4 event
//
#define ADC_CR2_JEXTSEL_EXTI_TIM8CC4                                          \
                                0x000C0000

//
//! Data alignment: Left Alignment
//
#define ADC_CR2_ALIGN_LEFT      0x00000800

//
//! Data alignment: Right Alignment
//
#define ADC_CR2_ALIGN_RIGHT     0x00000000

//
//! Direct memory access mode enable
//
#define ADC_CR2_DMA_EN          0x00000100

//
//! Initialize calibration register
//
#define ADC_CR2_RSTCAL          0x00000008

//
//!  A/D Calibration enable
//
#define ADC_CR2_CAL_EN          0x00000004

//
//! Continuous conversion
//
#define ADC_CR2_CONT            0x00000002

//
//!  A/D Calibration enable
//
#define ADC_CR2_ADON            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_SMPR1 A/D sample time Register 1 (ADC_SMPR1)
//! \brief Defines for the bit fields in the \ref ADC_SMPR1 register.
//! @{
//
//*****************************************************************************

//
//! Channel 17 Sample time selection Mask
//
#define ADC_SMPR1_SMP17_M       0x00E00000

//
//! Channel 17 Sample time selection Shift
//
#define ADC_SMPR1_SMP17_S       21

//
//! Channel 17 Sample time selection: 1.5 cycles
//
#define ADC_SMPR1_SMP17_1_5_CYCLE                                             \
                                0x00000000

//
//! Channel 17 Sample time selection: 7.5 cycles
//
#define ADC_SMPR1_SMP17_7_5_CYCLE                                             \
                                0x00200000

//
//! Channel 17 Sample time selection: 17.5 cycles
//
#define ADC_SMPR1_SMP17_13_5_CYCLE                                            \
                                0x00400000

//
//! Channel 17 Sample time selection: 28.5 cycles
//
#define ADC_SMPR1_SMP17_28_5_CYCLE                                            \
                                0x00600000

//
//! Channel 17 Sample time selection: 41.5 cycles
//
#define ADC_SMPR1_SMP17_41_5_CYCLE                                            \
                                0x00800000

//
//! Channel 17 Sample time selection: 55.5 cycles
//
#define ADC_SMPR1_SMP17_55_5_CYCLE                                            \
                                0x00A00000

//
//! Channel 17 Sample time selection: 71.5 cycles
//
#define ADC_SMPR1_SMP17_71_5_CYCLE                                            \
                                0x00C00000

//
//! Channel 17 Sample time selection: 239.5 cycles
//
#define ADC_SMPR1_SMP17_239_5_CYCLE                                           \
                                0x00E00000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_SMPR2 A/D sample time Register 2 (ADC_SMPR1)
//! \brief Defines for the bit fields in the \ref ADC_SMPR2 register.
//! @{
//
//*****************************************************************************

//
//! Channel 0 Sample time selection Mask
//
#define ADC_SMPR2_SMP0_M       0x00000007

//
//! Channel 0 Sample time selection Shift
//
#define ADC_SMPR2_SMP0_S       0

//
//! Channel 0 Sample time selection: 1.5 cycles
//
#define ADC_SMPR2_SMP0_1_5_CYCLE                                             \
                                0x00000000

//
//! Channel 0 Sample time selection: 7.5 cycles
//
#define ADC_SMPR2_SMP0_7_5_CYCLE                                             \
                                0x00000001

//
//! Channel 0 Sample time selection: 17.5 cycles
//
#define ADC_SMPR2_SMP0_13_5_CYCLE                                            \
                                0x00000002

//
//! Channel 0 Sample time selection: 28.5 cycles
//
#define ADC_SMPR2_SMP0_28_5_CYCLE                                            \
                                0x00000003

//
//! Channel 0 Sample time selection: 41.5 cycles
//
#define ADC_SMPR2_SMP0_41_5_CYCLE                                            \
                                0x00000004

//
//! Channel 0 Sample time selection: 55.5 cycles
//
#define ADC_SMPR2_SMP0_55_5_CYCLE                                            \
                                0x00000005

//
//! Channel 0 Sample time selection: 71.5 cycles
//
#define ADC_SMPR2_SMP0_71_5_CYCLE                                            \
                                0x00000006

//
//! Channel 0 Sample time selection: 239.5 cycles
//
#define ADC_SMPR2_SMP0_239_5_CYCLE                                           \
                                0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JOFR1 A/D injected channel data offset Register 1 (ADC_JOFR1)
//! \brief Defines for the bit fields in the \ref ADC_JOFR1 register.
//! @{
//
//*****************************************************************************

//
//!  Data offset for injected channel 1 Mask
//
#define ADC_JOFR1_M             0x00000FFF

//
//!  Data offset for injected channel 1 Shift
//
#define ADC_JOFR1_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JOFR2 A/D injected channel data offset Register 2 (ADC_JOFR2)
//! \brief Defines for the bit fields in the \ref ADC_JOFR2 register.
//! @{
//
//*****************************************************************************

//
//!  Data offset for injected channel 2 Mask
//
#define ADC_JOFR2_M             0x00000FFF

//
//!  Data offset for injected channel 2 Shift
//
#define ADC_JOFR2_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JOFR3 A/D injected channel data offset Register 3 (ADC_JOFR3)
//! \brief Defines for the bit fields in the \ref ADC_JOFR3 register.
//! @{
//
//*****************************************************************************

//
//!  Data offset for injected channel 3 Mask
//
#define ADC_JOFR3_M             0x00000FFF

//
//!  Data offset for injected channel 3 Shift
//
#define ADC_JOFR3_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JOFR4 A/D injected channel data offset Register 4 (ADC_JOFR4)
//! \brief Defines for the bit fields in the \ref ADC_JOFR4 register.
//! @{
//
//*****************************************************************************

//
//!  Data offset for injected channel 4 Mask
//
#define ADC_JOFR4_M             0x00000FFF

//
//!  Data offset for injected channel 4 Shift
//
#define ADC_JOFR4_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_HTR A/D watchdog high threshold Register (ADC_HTR)
//! \brief Defines for the bit fields in the \ref ADC_HTR register.
//! @{
//
//*****************************************************************************

//
//! Analog watchdog high threshold Mask
//
#define ADC_HTR_M               0x00000FFF

//
//! Analog watchdog high threshold Shift
//
#define ADC_HTR_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_LTR A/D watchdog high threshold Register (ADC_LTR)
//! \brief Defines for the bit fields in the \ref ADC_LTR register.
//! @{
//
//*****************************************************************************

//
//! Analog watchdog low threshold Mask
//
#define ADC_LTR_M               0x00000FFF

//
//! Analog watchdog low threshold Shift
//
#define ADC_LTR_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_SQR1 A/D  regular sequence Register 1 (ADC_SQR1)
//! \brief Defines for the bit fields in the \ref ADC_SQR1 register.
//! @{
//
//*****************************************************************************

//
//! A/D Regular channel sequence length Mask
//
#define ADC_SQR1_LEN_M          0x00F00000

//
//! A/D Regular channel sequence length Shift
//
#define ADC_SQR1_LEN_S          20

//
//! A/D Regular channel sequence length: 1 conversion
//
#define ADC_SQR1_LEN_1          0x00000000

//
//! A/D Regular channel sequence length: 2 conversions
//
#define ADC_SQR1_LEN_2          0x00100000

//
//! A/D Regular channel sequence length: 3 conversions
//
#define ADC_SQR1_LEN_3          0x00200000

//
//! A/D Regular channel sequence length: 4 conversions
//
#define ADC_SQR1_LEN_4          0x00300000

//
//! A/D Regular channel sequence length: 5 conversions
//
#define ADC_SQR1_LEN_5          0x00400000

//
//! A/D Regular channel sequence length: 6 conversions
//
#define ADC_SQR1_LEN_6          0x00500000

//
//! A/D Regular channel sequence length: 7 conversions
//
#define ADC_SQR1_LEN_7          0x00600000

//
//! A/D Regular channel sequence length: 8 conversions
//
#define ADC_SQR1_LEN_8          0x00700000

//
//! A/D Regular channel sequence length: 9 conversions
//
#define ADC_SQR1_LEN_9          0x00800000

//
//! A/D Regular channel sequence length: 10 conversions
//
#define ADC_SQR1_LEN_10         0x00900000

//
//! A/D Regular channel sequence length: 11 conversions
//
#define ADC_SQR1_LEN_11         0x00A00000

//
//! A/D Regular channel sequence length: 12 conversions
//
#define ADC_SQR1_LEN_12         0x00B00000

//
//! A/D Regular channel sequence length: 13 conversions
//
#define ADC_SQR1_LEN_13         0x00C00000

//
//! A/D Regular channel sequence length: 14 conversions
//
#define ADC_SQR1_LEN_14         0x00D00000

//
//! A/D Regular channel sequence length: 15 conversions
//
#define ADC_SQR1_LEN_15         0x00E00000

//
//! A/D Regular channel sequence length: 16 conversions
//
#define ADC_SQR1_LEN_16         0x00F00000

//
//! A/D Converter Regular Conversion Sequence No.13 Mask
//
#define ADC_SQR1_SQ13_M         0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.13 Shift
//
#define ADC_SQR1_SQ13_S         0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN0       0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN1       0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN2       0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN3       0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN4       0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN5       0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN6       0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN7       0x00000007

//
//! Input channel 8 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN8       0x00000008

//
//! Input channel 9 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN9       0x00000009

//
//! Input channel 10 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN10      0x0000000A

//
//! Input channel 11 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN11      0x0000000B

//
//! Input channel 12 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN12      0x0000000C

//
//! Input channel 13 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN13      0x0000000D

//
//! Input channel 14 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN14      0x0000000E

//
//! Input channel 15 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN15      0x0000000F

//
//! Input channel 16 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN16      0x00000010

//
//! Input channel 17 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_SQR1_SQ13_IN17      0x00000011

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_SQR2 A/D  regular sequence Register 2 (ADC_SQR2)
//! \brief Defines for the bit fields in the \ref ADC_SQR2 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Sequence No.7 Mask
//
#define ADC_SQR2_SQ7_M          0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.7 Shift
//
#define ADC_SQR2_SQ7_S          0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN0        0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN1        0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN2        0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN3        0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN4        0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN5        0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN6        0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN7        0x00000007

//
//! Input channel 8 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN8        0x00000008

//
//! Input channel 9 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN9        0x00000009

//
//! Input channel 10 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN10       0x0000000A

//
//! Input channel 11 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN11       0x0000000B

//
//! Input channel 12 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN12       0x0000000C

//
//! Input channel 13 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN13       0x0000000D

//
//! Input channel 14 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN14       0x0000000E

//
//! Input channel 15 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN15       0x0000000F

//
//! Input channel 16 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN16       0x00000010

//
//! Input channel 17 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_SQR2_SQ7_IN17       0x00000011

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_SQR3 A/D  regular sequence Register 3 (ADC_SQR3)
//! \brief Defines for the bit fields in the \ref ADC_SQR3 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Sequence No.1 Mask
//
#define ADC_SQR3_SQ1_M          0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.1 Shift
//
#define ADC_SQR3_SQ1_S          0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN0        0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN1        0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN2        0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN3        0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN4        0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN5        0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN6        0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN7        0x00000007

//
//! Input channel 8 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN8        0x00000008

//
//! Input channel 9 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN9        0x00000009

//
//! Input channel 10 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN10       0x0000000A

//
//! Input channel 11 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN11       0x0000000B

//
//! Input channel 12 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN12       0x0000000C

//
//! Input channel 13 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN13       0x0000000D

//
//! Input channel 14 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN14       0x0000000E

//
//! Input channel 15 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN15       0x0000000F

//
//! Input channel 16 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN16       0x00000010

//
//! Input channel 17 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_SQR3_SQ1_IN17       0x00000011

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JSQR A/D injected sequence Register (ADC_JSQR)
//! \brief Defines for the bit fields in the \ref ADC_JSQR register.
//! @{
//
//*****************************************************************************

//
//! A/D Injected channel sequence length Mask
//
#define ADC_JSQR_LEN_M          0x00300000

//
//! A/D Injected channel sequence length Shift
//
#define ADC_JSQR_LEN_S          20

//
//! A/D Regular channel sequence length: 1 conversion
//
#define ADC_JSQR_LEN_1          0x00000000

//
//! A/D Regular channel sequence length: 2 conversions
//
#define ADC_JSQR_LEN_2          0x00100000

//
//! A/D Regular channel sequence length: 3 conversions
//
#define ADC_JSQR_LEN_3          0x00200000

//
//! A/D Regular channel sequence length: 4 conversions
//
#define ADC_JSQR_LEN_4          0x00300000
//
//! A/D Converter Regular Conversion Sequence No.13 Mask
//
#define ADC_JSQR_JSQ1_M         0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.13 Shift
//
#define ADC_JSQR_JSQ1_S         0

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_JSQR_JSQ1_IN1       0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_JSQR_JSQ1_IN2       0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_JSQR_JSQ1_IN3       0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_JSQR_JSQ1_IN4       0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JDR1 ADC injected data Register 1(ADC_JDR1)
//! \brief Defines for the bit fields in the ADC_JDR1 register.
//! @{
//
//*****************************************************************************

//
//! ADC Injected data mask
//
#define ADC_JDR1_JDATA_M        0x0000FFFF

//
//! ADC Injected data shift
//
#define ADC_JDR1_JDATA_S        0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JDR2 ADC injected data Register 2(ADC_JDR2)
//! \brief Defines for the bit fields in the ADC_JDR2 register.
//! @{
//
//*****************************************************************************

//
//! ADC Injected data mask
//
#define ADC_JDR2_JDATA_M        0x0000FFFF

//
//! ADC Injected data shift
//
#define ADC_JDR2_JDATA_S        0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JDR1 ADC injected data Register 3(ADC_JDR3)
//! \brief Defines for the bit fields in the ADC_JDR3 register.
//! @{
//
//*****************************************************************************

//
//! ADC Injected data mask
//
#define ADC_JDR3_JDATA_M        0x0000FFFF

//
//! ADC Injected data shift
//
#define ADC_JDR3_JDATA_S        0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_JDR4 ADC injected data Register 4(ADC_JDR4)
//! \brief Defines for the bit fields in the ADC_JDR4 register.
//! @{
//
//*****************************************************************************

//
//! ADC Injected data mask
//
#define ADC_JDR4_JDATA_M        0x0000FFFF

//
//! ADC Injected data shift
//
#define ADC_JDR4_JDATA_S        0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Register_ADC_DR ADC regular data Register 4(ADC_DR)
//! \brief Defines for the bit fields in the ADC_JDR4 register.
//! @{
//
//*****************************************************************************

//
//! ADC Regular data mask
//
#define ADC_DR_DATA_M           0x0000FFFF

//
//! ADC Regular data shift
//
#define ADC_DR_DATA_S           0

//
//! ADC2 Regular data mask
//
#define ADC_DR_ADC2DATA_M       0xFFFF0000

//
//! ADC2 Regular data shift
//
#define ADC_DR_ADC2DATA_S       16
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

#endif // __XHW_ADC_H__ 
