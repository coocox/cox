//*****************************************************************************
//
//! \file xhw_sysctl.h
//! \brief Macros used when accessing the system control hardware.
//! \version V2.2.1.0
//! \date 6/15/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox
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


#ifndef __HW_SYSCTL_H__
#define __HW_SYSCTL_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register AU9110 SysCtl Register
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
//! \addtogroup AU9110_SysCtl_Register_Offsets AU9110 SysCtl Register Offsets(Map)
//! \brief Defines for the system control register addresses.through 
//! <b>AHB_BA + offset</b>.
//! @{
//
//*****************************************************************************

//
//! System Reset Source Register
//
#define GCR_RSTSRC              0x50000004

//
//! IP Reset Control Register1
//
#define GCR_IPRSTC1             0x50000008

//
//! IP Reset Control Register2
//
#define GCR_IPRSTC2             0x5000000C

//
//! GPIOA input type control register
//
#define GCR_GPAINP              0x50000030

//
//! GPIOB input type control register
//
#define GCR_GPBINP              0x50000034

//
//! GPIOA multiple function control register
//
#define GCR_GPAALT              0x50000038

//
//! GPIOB multiple function control register
//
#define GCR_GPBALT              0x5000003C

//
//! WAKEUP pad control register
//
#define GCR_WAKECR              0x50000054

//
//! Register Lock Key address
//
#define GCR_REGLOCK             0x50000100

//
//! Internal oscillator trim register
//
#define GCR_OSCTRIM             0x50000110

//
//! 16K Oscillator trim register
//
#define GCR_OSC16K              0x50000114

//
//! System Power Control Register
//
#define SYSCLK_PWRCON           0x50000200

//
//! AHB Devices Clock Enable Control Register
//
#define SYSCLK_AHBCLK           0x50000204

//
//! APB Devices Clock Enable Control Register
//
#define SYSCLK_APBCLK           0x50000208

//
//! DPD State Register
//
#define SYSCLK_DPDSTATE         0x5000020C

//
//! Clock Source Select Control Register 0
//
#define SYSCLK_CLKSEL0          0x50000210

//
//! Clock Source Select Control Register 1
//
#define SYSCLK_CLKSEL1          0x50000214

//
//! Clock Divider Register
//
#define SYSCLK_CLKDIV           0x50000218

//
//! Clock Source Select Control Register 2
//
#define SYSCLK_CLKSEL2          0x5000021C

//
//! Sleep Clock Source Select Register
//
#define SYSCLK_CLKSLEEP         0x50000220

//
//! Power Down Flag Register
//
#define SYSCLK_PDFLAG           0x50000224

//
//! Debug Port Power Down Disable Register
//
#define SYSCLK_DBGPD            0x50000228


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_RSTSRC SysCtl Register GCR RSTSRC(GCR_RSTSRC)
//! @{
//
//*****************************************************************************

//
//! RSTS CPU flag
//
#define GCR_RSTSRC_CPU_F        0x00000080

//
//! RSTS PMU flag
//
#define GCR_RSTSRC_PMU_F        0x00000040
//
//! RSTS SYS flag
//
#define GCR_RSTSRC_SYS_F        0x00000020
//
//! RSTS WDG flag
//
#define GCR_RSTSRC_WDG_F        0x00000002

//
//! RSTS CORE flag
//
#define GCR_RSTSRC_CORE_F       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_IPRSTC1 SysCtl Register GCR IPRSTC1(GCR_IPRSTC1)
//! @{
//
//*****************************************************************************

//
//! PDMA Controller Reset
//
#define GCR_IPRSTC1_PDMA        BIT_32_2

//
//! CPU kernel one shot reset
//
#define GCR_IPRSTC1_CPU         BIT_32_1

//
//! CHIP one shot reset
//
#define GCR_IPRSTC1_CHIP        BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_IPRSTC1 SysCtl Register GCR IPRSTC1(GCR_IPRSTC1)
//! @{
//
//*****************************************************************************

//
//! PDMA Controller Reset
//
#define GCR_IPRSTC1_PDMA        BIT_32_2

//
//! CPU kernel one shot reset
//
#define GCR_IPRSTC1_CPU         BIT_32_1

//
//! CHIP one shot reset
//
#define GCR_IPRSTC1_CHIP        BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_IPRSTC2 SysCtl GCR IPRSTC2 Register(SysCtl_GCR_IPRSTC2)
//! @{
//
//*****************************************************************************

//
//! Analog block Controller Reset
//
#define GCR_IPRSTC2_ANA         BIT_32_30

//
//! I2S1 Controller Reset
//
#define GCR_IPRSTC2_I2S         BIT_32_29

//
//! ADC Controller Reset
//
#define GCR_IPRSTC2_ADC         BIT_32_28

//
//! Analog Comparator Reset
//
#define GCR_IPRSTC2_ACMP        BIT_32_22

//
//! PWM10 controller reset
//
#define GCR_IPRSTC2_PWM10       BIT_32_20

//
//! CRC Generation block reset
//
#define GCR_IPRSTC2_CRC         BIT_32_19

//
//! Biquad Filter block reset
//
#define GCR_IPRSTC2_BIQ         BIT_32_18

//
//! UART0 controller Reset
//
#define GCR_IPRSTC2_UART0       BIT_32_16

//
//! DPWM Speaker driver reset
//
#define GCR_IPRSTC2_DPWM        BIT_32_13

//
//! SPI0 controller reset
//
#define GCR_IPRSTC2_SPI0        BIT_32_12

//
//! I2C0 controller Reset
//
#define GCR_IPRSTC2_I2C0        BIT_32_8

//
//! Timer1 controller Reset
//
#define GCR_IPRSTC2_TMR1        BIT_32_7

//
//! Timer0 controller Reset
//
#define GCR_IPRSTC2_TMR0        BIT_32_6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_GAPINP SysCtl GCR GAP_INP Register(SysCtl_GCR_GAPINP)
//! @{
//
//*****************************************************************************

//
//! GPIOA bit0 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT0 0x00010000

//
//! GPIOA bit1 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT1 0x00020000

//
//! GPIOA bit2 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT2 0x00040000

//
//! GPIOA bit3 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT3 0x00080000

//
//! GPIOA bit4 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT4 0x00100000

//
//! GPIOA bit5 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT5 0x00200000

//
//! GPIOA bit6 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT6 0x00400000

//
//! GPIOA bit7 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT7 0x00800000

//
//! GPIOA bit8 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT8 0x01000000

//
//! GPIOA bit9 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT9 0x02000000

//
//! GPIOA bit10 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT10                                              \
	                            0x04000000

//
//! GPIOA bit11 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT11                                              \
	                            0x08000000

//
//! GPIOA bit12 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT12                                              \
	                            0x10000000

//
//! GPIOA bit13 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT13                                              \
	                            0x20000000

//
//! GPIOA bit14 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT14                                              \
	                            0x40000000

//
//! GPIOA bit15 schmitt trigger
//
#define GCR_GAPINP_SCHMITT_BIT15                                              \
	                            0x80000000


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_GBPINP SysCtl GCR GBP_INP Register(SysCtl_GCR_GBPINP)
//! @{
//
//*****************************************************************************

//
//! GPIOB bit0 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT0 0x00010000

//
//! GPIOB bit1 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT1 0x00020000

//
//! GPIOB bit2 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT2 0x00040000

//
//! GPIOB bit3 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT3 0x00080000

//
//! GPIOB bit4 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT4 0x00100000

//
//! GPIOB bit5 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT5 0x00200000

//
//! GPIOB bit6 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT6 0x00400000

//
//! GPIOB bit7 schmitt trigger
//
#define GCR_GBPINP_SCHMITT_BIT7 0x00800000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_GPAALT SysCtl GCR GPA ALT Register(GCR_GPAALT)
//! @{
//
//*****************************************************************************

//
//! PA.0 Pin Function Selection
//
#define GCR_GPAALT_PA0MFP_M     0x00000003
#define GCR_GPAALT_PA0MFP_S     0

#define GCR_GPAALT_PA0MFP_SPIMOSI0                                            \
	                            0x00000001
#define GCR_GPAALT_PA0MFP_SPIMCLK                                             \
	                            0x00000002

//
//! PA.1 Pin Function Selection
//
#define GCR_GPAALT_PA1MFP_M    0x0000000C
#define GCR_GPAALT_PA1MFP_S    2
#define GCR_GPAALT_PA1MFP_SPISCLK                                            \
	                            0x00000004
#define GCR_GPAALT_PA1MFP_I2CSCL                                             \
	                            0x00000008

//
//! PA.2 Pin Function Selection
//
#define GCR_GPAALT_PA2MFP_M    0x00000030
#define GCR_GPAALT_PA2MFP_S    4
#define GCR_GPAALT_PA2MFP_SPISSB0                                            \
	                            0x00000010

//
//! PA.3 Pin Function Selection
//
#define GCR_GPAALT_PA3MFP_M    0x000000C0
#define GCR_GPAALT_PA3MFP_S    6
#define GCR_GPAALT_PA3MFP_SPIMISO0                                           \
	                            0x00000040
#define GCR_GPAALT_PA3MFP_I2CSDA                                             \
	                            0x00000080

//
//! PA.4 Pin Function Selection
//
#define GCR_GPAALT_PA4MFP_M    0x00000300
#define GCR_GPAALT_PA4MFP_S    8
#define GCR_GPAALT_PA4MFP_I2SFS                                              \
	                            0x00000100

//
//! PA.5 Pin Function Selection
//
#define GCR_GPAALT_PA5MFP_M    0x00000C00
#define GCR_GPAALT_PA5MFP_S    10
#define GCR_GPAALT_PA4MFP_I2SBCLK                                            \
	                            0x00000400

//
//! PA.6 Pin Function Selection
//
#define GCR_GPAALT_PA6MFP_M    0x00003000
#define GCR_GPAALT_PA6MFP_S    12
#define GCR_GPAALT_PA4MFP_I2SSDI                                            \
	                            0x00001000

//
//! PA.7 Pin Function Selection
//
#define GCR_GPAALT_PA7MFP_M    0x0000C000
#define GCR_GPAALT_PA7MFP_S    14
#define GCR_GPAALT_PA7MFP_I2SSDO                                            \
	                            0x00004000

//
//! PA.8 Pin Function Selection
//
#define GCR_GPAALT_PA8MFP_M    0x00030000
#define GCR_GPAALT_PA8MFP_S    16
#define GCR_GPAALT_PA8MFP_UARTTX                                            \
	                            0x00010000
#define GCR_GPAALT_PA8MFP_I2SFS                                             \
	                            0x00020000

//
//! PA.9 Pin Function Selection
//
#define GCR_GPAALT_PA9MFP_M    0x000C0000
#define GCR_GPAALT_PA9MFP_S    18
#define GCR_GPAALT_PA9MFP_UARTRX                                            \
	                            0x00040000
#define GCR_GPAALT_PA9MFP_I2SBCLK                                           \
	                            0x00080000

//
//! PA.10 Pin Function Selection
//
#define GCR_GPAALT_PA10MFP_M   0x00300000
#define GCR_GPAALT_PA10MFP_S   20
#define GCR_GPAALT_PA10MFP_I2CSDA                                           \
	                            0x00100000
#define GCR_GPAALT_PA10MFP_I2SSDI                                           \
	                            0x00200000
#define GCR_GPAALT_PA10MFP_UARTRTSn                                         \
	                            0x00200000

//
//! PA.11 Pin Function Selection
//
#define GCR_GPAALT_PA11MFP_M   0x00C00000
#define GCR_GPAALT_PA11MFP_S   22
#define GCR_GPAALT_PA11MFP_I2CSCL                                           \
	                            0x00400000
#define GCR_GPAALT_PA11MFP_I2SSDO                                           \
	                            0x00800000
#define GCR_GPAALT_PA11MFP_UARTCTSn                                         \
	                            0x00C00000

//
//! PA.12 Pin Function Selection
//
#define GCR_GPAALT_PA12MFP_M   0x03000000
#define GCR_GPAALT_PA12MFP_S   24
#define GCR_GPAALT_PA12MFP_PWM0                                             \
	                            0x01000000
#define GCR_GPAALT_PA12MFP_SPKP                                             \
	                            0x02000000
#define GCR_GPAALT_PA12MFP_I2SFS                                            \
	                            0x03000000

//
//! PA.13 Pin Function Selection
//
#define GCR_GPAALT_PA13MFP_M   0x0C000000
#define GCR_GPAALT_PA13MFP_S   26
#define GCR_GPAALT_PA13MFP_PWM1                                             \
	                            0x04000000
#define GCR_GPAALT_PA13MFP_SPKM                                             \
	                            0x08000000
#define GCR_GPAALT_PA13MFP_BCLK                                             \
	                            0x0C000000

//
//! PA.14 Pin Function Selection
//
#define GCR_GPAALT_PA14MFP_M   0x30000000
#define GCR_GPAALT_PA14MFP_S   28
#define GCR_GPAALT_PA14MFP_TM0                                             \
	                            0x10000000
#define GCR_GPAALT_PA14MFP_SDCLK                                           \
	                            0x20000000
#define GCR_GPAALT_PA14MFP_SDCLKn                                          \
	                            0x30000000

//
//! PA.15 Pin Function Selection
//
#define GCR_GPAALT_PA15MFP_M   0xC0000000
#define GCR_GPAALT_PA15MFP_S   30
#define GCR_GPAALT_PA15MFP_TM1                                             \
	                            0x40000000
#define GCR_GPAALT_PA15MFP_SDIN                                            \
	                            0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_GPBALT SysCtl GCR GPB ALT Register(GCR_GPBALT)
//! @{
//
//*****************************************************************************

//
//! PB.0 Pin Function Selection
//
#define GCR_GPBALT_PB0MFP_M     0x00000003
#define GCR_GPBALT_PB0MFP_S     0

#define GCR_GPBALT_PB0MFP_SPISSB1                                            \
	                            0x00000001
#define GCR_GPBALT_PB0MFP_CMP0                                               \
	                            0x00000002
#define GCR_GPBALT_PB0MFP_SPISSB0                                            \
	                            0x00000003

//
//! PB.1 Pin Function Selection
//
#define GCR_GPBALT_PB1MFP_M     0x0000000C
#define GCR_GPBALT_PB1MFP_S     2
#define GCR_GPBALT_PB1MFP_MCLK                                               \
	                            0x00000004
#define GCR_GPBALT_PB1MFP_CMP1                                               \
	                            0x00000008
#define GCR_GPBALT_PB1MFP_SPISSB1                                            \
	                            0x0000000C

//
//! PB.2 Pin Function Selection
//
#define GCR_GPBALT_PB2MFP_M     0x00000030
#define GCR_GPBALT_PB2MFP_S     4
#define GCR_GPBALT_PB2MFP_I2CSCL                                             \
	                            0x00000010
#define GCR_GPBALT_PB2MFP_CMP2                                               \
	                            0x00000020
#define GCR_GPBALT_PB2MFP_SPISCLK                                            \
	                            0x00000030

//
//! PB.3 Pin Function Selection
//
#define GCR_GPBALT_PB3MFP_M     0x000000C0
#define GCR_GPBALT_PB3MFP_S     6
#define GCR_GPBALT_PB3MFP_I2CSDA                                             \
	                            0x00000040
#define GCR_GPBALT_PB3MFP_CMP3                                               \
	                            0x00000080
#define GCR_GPBALT_PB3MFP_SPIMISO0                                           \
	                            0x000000C0

//
//! PB.4 Pin Function Selection
//
#define GCR_GPBALT_PB4MFP_M     0x00000300
#define GCR_GPBALT_PB4MFP_S     8
#define GCR_GPBALT_PB4MFP_PWM0B                                              \
	                            0x00000100
#define GCR_GPBALT_PB4MFP_CMP4                                               \
	                            0x00000200
#define GCR_GPBALT_PB4MFP_SPIMOSI0                                           \
	                            0x00000300

//
//! PB.5 Pin Function Selection
//
#define GCR_GPBALT_PB5MFP_M     0x00000C00
#define GCR_GPBALT_PB5MFP_S     10
#define GCR_GPBALT_PB5MFP_PWM1B                                              \
	                            0x00000400
#define GCR_GPBALT_PB5MFP_CMP5                                               \
	                            0x00000800
#define GCR_GPBALT_PB5MFP_SPIMISO1                                           \
	                            0x00000C00

//
//! PB.6 Pin Function Selection
//
#define GCR_GPBALT_PB6MFP_M     0x00003000
#define GCR_GPBALT_PB6MFP_S     12
#define GCR_GPBALT_PB6MFP_I2SSDI                                             \
	                            0x00001000
#define GCR_GPBALT_PB6MFP_CMP6                                               \
	                            0x00002000
#define GCR_GPBALT_PB6MFP_SPIMISO1                                           \
	                            0x00003000

//
//! PB.7 Pin Function Selection
//
#define GCR_GPBALT_PB7MFP_M     0x0000C000
#define GCR_GPBALT_PB7MFP_S     14
#define GCR_GPBALT_PB7MFP_I2SSDO                                             \
	                            0x00004000
#define GCR_GPBALT_PB7MFP_CMP7                                               \
	                            0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_WAKECR SysCtl GCR WAKECR Register(SysCtl_GCR_WAKECR)
//! @{
//
//*****************************************************************************

//
//! State of WAKEUP pin. Read only
//
#define GCR_WAKECR_WAKEDOUT     BIT_32_3

//
//! Pin output enable bar. 1 = tristate(default), 0 = drive WAKE_DOUT to pin
//
#define GCR_WAKECR_WAKEOENB     BIT_32_2

//
//! Pin pull-up control. 1 = tristate(default). 0 = pull-up enable. This signal is latched in deep powerdown and preserved.
//
#define GCR_WAKECR_WAKETRI      BIT_32_1

//
//! State of WAKEUP pin. Read only
//
#define GCR_WAKECR_WAKEDIN      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_GCR_OSCTRIM SysCtl GCR OSCTRIM Register(GCR_OSCTRIM)
//! @{
//
//*****************************************************************************

//
//! OSCTRIM[0].TRIM
//
#define GCR_OSCTRIM_OSCTRIM0TRIM_M                                          \
	                            0x000000FF
#define GCR_OSCTRIM_OSCTRIM0TRIM_S                                          \
	                            0
//
//! OSCTRIM[0].RANGE
//
#define GCR_OSCTRIM_OSCTRIM0RANGE                                           \
	                            0x00000100

//
//! OSCTRIM[1].TRIM
//
#define GCR_OSCTRIM_OSCTRIM1TRIM_M                                          \
	                            0x00FF0000
#define GCR_OSCTRIM_OSCTRIM1TRIM_S                                          \
	                            16

//
//! OSCTRIM[1].RANGE
//
#define GCR_OSCTRIM_OSCTRIM1RANGE                                           \
	                            0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_PWRCON SysCtl PWRCON Register(SysCtl_SYSCLK_PWRCON)
//! @{
//
//*****************************************************************************

//
//! External 32.768 kHz Crystal Enable bit
//
#define SYSCLK_PWRCON_XTL12M_EN 0x00000002

//
//! OSC49M Oscillator enable bit
//
#define SYSCLK_PWRCON_OSC49M_EN 0x00000004

//
//! OSC16K Oscillator enable bit
//
#define SYSCLK_PWRCON_OSC22M_EN 0x00000008

//
//! Reserved - do not set to '1'
//
#define SYSCLK_PWRCON_STOP      0x00000200

//
//! Standby Power Down bit.
//
#define SYSCLK_PWRCON_STANDBY_PD                                              \
	                            0x00000400

//
//! Deep Power Down bit.
//
#define SYSCLK_PWRCON_DEEP_PD   0x00000800

//
//! Determines whether WAKEUP pin is enabled in DPD mode.
//
#define SYSCLK_PWRCON_PIN_ENB   0x00010000

//
//! Determines whether OSC16K pin is enabled in DPD mode.
//
#define SYSCLK_PWRCON_OSC16K_ENB                                             \
	                            0x00010000

//
//! Select WAKEUP Timer mask
//
#define SYSCLK_PWRCON_TIMER_SEL_M                                            \
	                            0x00F00000

//
//! Select WAKEUP Timer shift
//
#define SYSCLK_PWRCON_TIMER_SEL_S                                            \
	                            20

//
//! Wakeup after 128 OSC16K clocks(12.8ms)
//
#define SYSCLK_PWRCON_TIMER_SEL0                                             \
	                            0x00100000

//
//! Wakeup after 256 OSC16K clocks(25.6ms)
//
#define SYSCLK_PWRCON_TIMER_SEL1                                             \
	                            0x00200000

//
//! Wakeup after 512 OSC16K clocks(51.2ms)
//
#define SYSCLK_PWRCON_TIMER_SEL2                                             \
	                            0x00400000

//
//! Wakeup after 1024 OSC16K clocks(102.4ms)
//
#define SYSCLK_PWRCON_TIMER_SEL3                                             \
	                            0x00800000

//
//! Pin wake flag(high to low transition on the WAKEUP pin), flag is cleared when DPD mode is entered
//
#define SYSCLK_PWRCON_PIN_WAKE                                               \
	                            0x01000000

//
//! TIMER count flag(requested with TIMER count 16 Khz oscillator), flag is cleared when DPD mode is entered
//
#define SYSCLK_PWRCON_TIMER_WAKE                                             \
	                            0x02000000

//
//! TIMER count flag(requested with TIMER count 16 Khz oscillator), flag is cleared when DPD mode is entered
//
#define SYSCLK_PWRCON_POI_WAKE                                               \
	                            0x04000000

//
//! Read bask of the current WAKEUP timer setting, this value is updated when DPD mode is entered
//
#define SYSCLK_PWRCON_TIMER_SEL_RD_M                                         \
	                            0xF0000000


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_AHBCLK SysCtl AHBCLK Register(SysCtl_SYSCLK_AHBCLK)
//! @{
//
//*****************************************************************************

//
//! CPU Clock Enable(HCLK) must be left as'1' for normal operation
//
#define SYSCLK_AHBCLK_CPU_EN    BIT_32_0

//
//! PDMA Controller Clock Enable Control
//
#define SYSCLK_AHBCLK_PDMA_EN   BIT_32_1

//
//! Flash ISP Controller Clock Enable Control
//
#define SYSCLK_AHBCLK_ISP_EN    BIT_32_2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_APBCLK SysCtl SYSCLK APBCLK Register(SysCtl_SYSCLK_APBCLK)
//! @{
//
//*****************************************************************************

//
//! Watch Dog Clock Enable.
//
#define SYSCLK_APBCLK_WDG_EN    BIT_32_4

//
//! Real-Time-Clock APB interface Clock Enable Control
//
#define SYSCLK_APBCLK_RTC_EN    BIT_32_5

//
//! Timer0 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR0_EN   BIT_32_6

//
//! Timer1 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR1_EN   BIT_32_7

//
//! I2C0 Clock Enable Control.
//
#define SYSCLK_APBCLK_I2C0_EN   BIT_32_8

//
//! SPI0 Clock Enable Control.
//
#define SYSCLK_APBCLK_SPI0_EN   BIT_32_12

//
//! DPWM Clock Enable Control.
//
#define SYSCLK_APBCLK_DPWM_EN   BIT_32_13

//
//! UART0 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART0_EN BIT_32_16  

//
//! BIQALC Clock Enable Control.
//
#define SYSCLK_APBCLK0_BIQALC_EN                                              \
	                            BIT_32_18

//
//! CRC Clock Enable Control.
//
#define SYSCLK_APBCLK_CRC_EN    BIT_32_19

//
//! PWM01 Block Clock Enable Control.
//
#define SYSCLK_APBCLK_PWM01_EN  BIT_32_20

//
//! ACMP Clock Enable Control.
//
#define SYSCLK_APBCLK_ACMP_EN   BIT_32_22

//
//! SBRAM Clock Enable Control.
//
#define SYSCLK_APBCLK_SBRAM_EN  BIT_32_26

//
//! ADC Clock Enable Control.
//
#define SYSCLK_APBCLK_ADC_EN    BIT_32_28

//
//! I2S Clock Enable Control.
//
#define SYSCLK_APBCLK_I2S_EN    BIT_32_29

//
//! ANA Clock Enable Control.
//
#define SYSCLK_APBCLK_ANA_EN    BIT_32_30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_DPDSTATE SysCtl DPDSTATE(SysCtl_SYSCLK_DPDSTATE)
//! @{
//
//*****************************************************************************

//
//! Write value to this register, data is latched on the next DPD event
//
#define SYSCLK_DPD_STATE_WR_M  0x000000FF
#define SYSCLK_DPD_STATE_WR_S  0

//
//! Read value form this register, this reigster was preserved from last DPD event.
//
#define SYSCLK_DPD_STATE_RD_M  0x0000FF00
#define SYSCLK_DPD_STATE_RD_S  0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_CLKSEL0 SysCtl CLKSEL0(SysCtl_SYSCLK_CLKSEL0)
//! @{
//
//*****************************************************************************

//
//! HCLK clock source slect
//
#define SYSCLK_CLKSEL0_HCLK_S_M 0x00000007
#define SYSCLK_CLKSEL0_HCLK_S_S 0

//
//! clock source form internal OSC48M oscillator
//
#define SYSCLK_CLKSEL0_HCLK_S_OSC48M                                          \
	                            0x00000000
//
//! clock source form external 32k Hz crystal clock
//
#define SYSCLK_CLKSEL0_HCLK_S_32KHZ                                           \
	                            0x00000001
//
//! clock source form internal 16kHZ oscillator
//
#define SYSCLK_CLKSEL0_HCLK_S_16KHZ                                           \
	                            0x00000002

//
//! STCLK_S clock source slect
//
#define SYSCLK_CLKSEL0_STCLK_S_M                                              \
	                            0x00000038
#define SYSCLK_CLKSEL0_STCLK_S_S                                              \
	                            3

//
//! system tick clock source form 16 khz internal clock
//
#define SYSCLK_CLKSEL0_STCLK_S_16KHZ                                          \
	                            0x00000000

//
//! system tick clock source form external 32 khz crystal clock
//
#define SYSCLK_CLKSEL0_STCLK_S_32KHZ                                          \
	                            0x00000008

//
//! system tick clock source form 16 khz internal clock divided by 2
//
#define SYSCLK_CLKSEL0_STCLK_S_16KHZ_2                                        \
	                            0x00000010

//
//! system tick clock source form OSC 49M internal clock divided by 2
//
#define SYSCLK_CLKSEL0_STCLK_S_OSC49M_2                                       \
	                            0x00000018

//
//! system tick clock source form HCLK divided by 2
//
#define SYSCLK_CLKSEL0_STCLK_S_HCLK_2                                         \
	                            0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_CLKSEL1 SysCtl Status(SysCtl_SYSCLK_CLKSEL1)
//! @{
//
//*****************************************************************************

//
//! WDG CLK clock source select
//
#define SYSCLK_CLKSEL1_WDG_S_M  0x00000003
#define SYSCLK_CLKSEL1_WDG_S_S  0

//
//! clock source from internal OSC48M oscillator clock
//
#define SYSCLK_CLKSEL1_WDG_S_OSC48M                                          \
	                            0x00000000

//
//! clock source from external crystal clock
//
#define SYSCLK_CLKSEL1_WDG_S_32KHZ                                           \
	                            0x00000001

//
//! clock source from HCLK/2048 clock
//
#define SYSCLK_CLKSEL1_WDG_S_HCLK_2048                                       \
	                            0x00000002

//
//! clock source from internal 16 kHz oscillator clock
//
#define SYSCLK_CLKSEL1_WDG_S_16KHZ                                           \
	                            0x00000003

//
//! DPWM clock source select
//
#define SYSCLK_CLKSEL1_DPWM_S_OSC48M                                         \
	                            0x00000000

//
//! DPWM clock source select
//
#define SYSCLK_CLKSEL1_DPWM_S_2OSC48M                                        \
	                            0x00000010

//
//! TMR0 clock source select
//
#define SYSCLK_CLKSEL1_TMR0_S_M                                              \
	                            0x00000700

//
//! TMR0 clock source select
//
#define SYSCLK_CLKSEL1_TMR0_S_S                                              \
	                            7

//
//! TIMER0 clock source select from internal 16 khz oscillator
//
#define SYSCLK_CLKSEL1_TMR0_S_16KHZ                                          \
	                            0x00000000

//
//! TIMER0 clock source select from external 32 kHz crystal
//
#define SYSCLK_CLKSEL1_TMR0_S_32KHZ                                          \
	                            0x00000100

//
//! TIMER0 clock source select from HCLK
//
#define SYSCLK_CLKSEL1_TMR0_S_HCLK                                           \
	                            0x00000200

//
//! TIMER0 clock source select from external pin(GPIOA[14])
//
#define SYSCLK_CLKSEL1_TMR0_S_EXT                                            \
	                            0x00000300

//
//! TIMER0 clock source select from OSC48M oscillator clock
//
#define SYSCLK_CLKSEL1_TMR0_S_OSC48M                                         \
	                            0x00000700

//
//! TMR1 clock source select
//
#define SYSCLK_CLKSEL1_TMR1_S_M                                              \
	                            0x00007000

//
//! TMR1 clock source select
//
#define SYSCLK_CLKSEL1_TMR1_S_S                                              \
	                            12

//
//! TIMER1 clock source select from internal 16 khz oscillator
//
#define SYSCLK_CLKSEL1_TMR1_S_16KHZ                                          \
	                            0x00000000

//
//! TIMER1 clock source select from external 32 kHz crystal
//
#define SYSCLK_CLKSEL1_TMR1_S_32KHZ                                          \
	                            0x00001000

//
//! TIMER1 clock source select from HCLK
//
#define SYSCLK_CLKSEL1_TMR1_S_HCLK                                           \
	                            0x00002000

//
//! TIMER1 clock source select from external pin(GPIOA[14])
//
#define SYSCLK_CLKSEL1_TMR1_S_EXT                                            \
	                            0x00003000

//
//! TIMER1 clock source select from OSC48M oscillator clock
//
#define SYSCLK_CLKSEL1_TMR1_S_OSC48M                                         \
	                            0x00007000

//
//! PWM01 clock source select
//
#define SYSCLK_CLKSEL1_PWM01_S_M                                              \
	                            0x30000000

//
//! PWM01 clock source select
//
#define SYSCLK_CLKSEL1_PWM01_S_S                                              \
	                            28

//
//! PWM01 clock source select from internal 16 khz oscillator
//
#define SYSCLK_CLKSEL1_PWM01_S_16KHZ                                          \
	                            0x00000000

//
//! PWM01 clock source select from external 32 kHz crystal
//
#define SYSCLK_CLKSEL1_PWM01_S_32KHZ                                          \
	                            0x10000000

//
//! PWM01 clock source select from HCLK
//
#define SYSCLK_CLKSEL1_PWM01_S_HCLK                                           \
	                            0x20000000

//
//! PWM01 clock source select from external pin(GPIOA[14])
//
#define SYSCLK_CLKSEL1_PWM01_S_EXT                                            \
	                            0x30000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_CLKDIV SysCtl CLKDIV(SysCtl_SYSCLK_CLKDIV)
//! @{
//
//*****************************************************************************

//
//! HCLK clock divide number from HCLK clock source.
//
#define SYSCLK_CLKDIV_HCLK_N_M  0x00000007
#define SYSCLK_CLKDIV_HCLK_N_S  0

//
//! UART clock divide number from UART clock source.
//
#define SYSCLK_CLKDIV_UART_N_M  0x00000F00
#define SYSCLK_CLKDIV_UART_N_S  8

//
//! ADC clock divide number from ADC clock source.
//
#define SYSCLK_CLKDIV_ADC_N_M   0x00FF0000
#define SYSCLK_CLKDIV_ADC_N_S   16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_CLKSEL2 SysCtl Status(SysCtl_SYSCLK_CLKSEL2)
//! @{
//
//*****************************************************************************

//
//! I2S CLK clock source select
//
#define SYSCLK_CLKSEL2_I2S_S_M  0x00000003
#define SYSCLK_CLKSEL2_I2S_S_S  0

//
//! clock source from internal OSC48M oscillator clock
//
#define SYSCLK_CLKSEL2_I2S_S_OSC48M                                          \
	                            0x00000003

//
//! clock source from external crystal clock
//
#define SYSCLK_CLKSEL2_I2S_S_32KHZ                                           \
	                            0x00000001

//
//! clock source from HCLK clock
//
#define SYSCLK_CLKSEL2_I2S_S_HCLK                                            \
	                            0x00000002

//
//! clock source from internal 16 kHz oscillator clock
//
#define SYSCLK_CLKSEL2_I2S_S_16KHZ                                           \
	                            0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_CLKSLEEP SysCtl CLKSLEEP Register(SysCtl_SYSCLK_CLKSLEEP)
//! @{
//
//*****************************************************************************
 
//
//! CPU Clock Sleep Enable (HCLK) must be left as '1' for normal operation
//
#define SYSCLK_CLKSLEEP_CPU_EN  BIT_32_0

//
//! PDMA Controller sleep clock enable control
//
#define SYSCLK_CLKSLEEP_PDMA_EN BIT_32_1

//
//! Flash ISP Controller Sleep Clock Enable Control
//
#define SYSCLK_CLKSLEEP_ISP_EN  BIT_32_2

//
//! Watchdog sleep Clock Enable Control
//
#define SYSCLK_CLKSLEEP_WDG_EN  BIT_32_4

//
//! Real-time-sleep Clock APB interface clcok
//
#define SYSCLK_CLKSLEEP_RTC_EN  BIT_32_5
 
//
//! Timer0 sleep clock enable control
//
#define SYSCLK_CLKSLEEP_TMR0_EN BIT_32_6

//
//! Timer1 sleep clock enable control
//
#define SYSCLK_CLKSLEEP_TMR1_EN BIT_32_7

//
//! I2C0 sleep clock enable control
//
#define SYSCLK_CLKSLEEP_I2C0_EN BIT_32_8

//
//! SPI0 sleep clock enable control
//
#define SYSCLK_CLKSLEEP_SPI0_EN BIT_32_12

//
//! DPWM sleep clock enable control
//
#define SYSCLK_CLKSLEEP_DPWM_EN BIT_32_13

//
//! UART0 sleep clock enable control
//
#define SYSCLK_CLKSLEEP_UART0_EN                                             \
	                            BIT_32_16

//
//! BIQALC sleep clock enable control
//
#define SYSCLK_CLKSLEEP_BIQALC_EN                                            \
	                            BIT_32_18

//
//! CRC sleep clock enable control
//
#define SYSCLK_CLKSLEEP_CRC_EN                                               \
	                            BIT_32_19

//
//! PWM01 sleep clock enable control
//
#define SYSCLK_CLKSLEEP_PWM01_EN                                             \
	                            BIT_32_20

//
//! ACMP sleep clock enable control
//
#define SYSCLK_CLKSLEEP_ACMP_EN                                              \
	                            BIT_32_22

//
//! SBRAM sleep clock enable control
//
#define SYSCLK_CLKSLEEP_SBRAM_EN                                             \
	                            BIT_32_26

//
//! ADC sleep clock enable control
//
#define SYSCLK_CLKSLEEP_ADC_EN                                               \
	                            BIT_32_28

//
//! I2S sleep clock enable control
//
#define SYSCLK_CLKSLEEP_I2S_EN                                               \
	                            BIT_32_29

//
//! ANA sleep clock enable control
//
#define SYSCLK_CLKSLEEP_ANA_EN                                               \
	                            BIT_32_30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SysCtl_Register_SYSCLK_DBGPD SysCtl DBGPD Register(SysCtl_SYSCLK_DBGPD)
//! @{
//
//*****************************************************************************

//
//! Power down request
//
#define SYSCLK_DBGPD_DISABLE_PD BIT_32_0

//
//! Current state of ICE_CLK pin
//
#define SYSCLK_DBGPD_ICE_CLK    BIT_32_6

//
//! Current state of ICE_DAT pin
//
#define SYSCLK_DBGPD_ICE_DAT    BIT_32_7


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

#endif // __XHW_SYSCTL_H__

