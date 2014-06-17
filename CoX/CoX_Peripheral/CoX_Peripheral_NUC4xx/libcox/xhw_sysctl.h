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


#ifndef __XHW_SYSCTL_H__
#define __XHW_SYSCTL_H__

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
//! \addtogroup NUC4xx_SysCtl_Register NUC4xx SysCtl Register
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
//! \addtogroup NUC4xx_SysCtl_Register_Offsets NUC4xx SysCtl Register Offsets(Map)
//! \brief Defines for the system control register addresses.through 
//! <b>SysCtl_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Product ID register
//
#define GCR_PDID                0x40000000  

//
//! System Reset Source Register
//
#define GCR_RSTSRC              0x40000004  

//
//! IP Reset Control Register1
//
#define GCR_IPRSTC1             0x40000008  

//
//! IP Reset Control Register2
//
#define GCR_IPRSTC2             0x4000000C

//
//! IP Reset Control Register3
//
#define GCR_IPRSTC3             0x40000010

//
//! I/O self test mode for PWM and QEI test Register
//
#define GCR_ITESTCR             0x40000014

//
//! Brown-Out Detector Control Register
//
#define GCR_BODCR               0x40000018  

//
//! Temperature Sensor Control Register
//
#define GCR_TEMPCR              0x4000001C

//
//! Power-On-Reset Control Register
//
#define GCR_PORCR               0x40000024

//
//! ADC VREF control Register
//
#define GCR_VREFCR              0x40000028

//
//! USB PHY Control Register
//
#define GCR_USBPHYCR            0x4000002C

//
//! Multiple Function Pin GPIOA Low Byte Control Register
//
#define GCR_GPAMFPL             0x40000030  

//
//! Multiple Function Pin GPIOA High Byte Control Register
//
#define GCR_GPAMFPH             0x40000034

//
//! Multiple Function Pin GPIOB Low Byte Control Register
//
#define GCR_GPBMFPL             0x40000038  

//
//! Multiple Function Pin GPIOB High Byte Control Register
//
#define GCR_GPBMFPH             0x4000003C 

//
//! Multiple Function Pin GPIOC Low Byte Control Register
//
#define GCR_GPCMFPL             0x40000040  

//
//! Multiple Function Pin GPIOC High Byte Control Register
//
#define GCR_GPCMFPH             0x40000044 

//
//! Multiple Function Pin GPIOD Low Byte Control Register
//
#define GCR_GPDMFPL             0x40000048  

//
//! Multiple Function Pin GPIOD High Byte Control Register
//
#define GCR_GPDMFPH             0x4000004C

//
//! Multiple Function Pin GPIOE Low Byte Control Register
//
#define GCR_GPEMFPL             0x40000050

//
//! Multiple Function Pin GPIOE High Byte Control Register
//
#define GCR_GPEMFPH             0x40000054

//
//! Multiple Function Pin GPIOF Low Byte Control Register
//
#define GCR_GPFMFPL             0x40000058

//
//! Multiple Function Pin GPIOF High Byte Control Register
//
#define GCR_GPFMFPH             0x4000005C

//
//! Multiple Function Pin GPIOG Low Byte Control Register
//
#define GCR_GPGMFPL             0x40000060

//
//! Multiple Function Pin GPIOG High Byte Control Register
//
#define GCR_GPGMFPH             0x40000064

//
//! Multiple Function Pin GPIOH Low Byte Control Register
//
#define GCR_GPHMFPL             0x40000068

//
//! Multiple Function Pin GPIOH High Byte Control Register
//
#define GCR_GPHMFPH             0x4000006C

//
//! Multiple Function Pin GPIOI Low Byte Control Register
//
#define GCR_GPIMFPL             0x40000070

//
//! Multiple Function Pin GPIOI High Byte Control Register
//
#define GCR_GPIMFPH             0x40000074

//
//! SRAM Failed Interrupt Enable Control Register 
//
#define GCR_SRAMINTCTR          0x400000C0

//
//! SRAM Parity Check Error Flag
//
#define GCR_SRAMSTATUS          0x400000C4

//
//! SRAM Parity Check Error First Address1
//
#define GCR_SRAM0ERRADDR        0x400000C8

//
//! SRAM Parity Check Error First Address2
//
#define GCR_SRAM1ERRADDR        0x400000CC
//
//! IRC Trim Control Register
//
#define GCR_IRCTRIMCTL          0x400000F0

//
//! IRC Trim Interrupt Enable Register
//
#define GCR_IRCTRIMIEN          0x400000F4

//
//! IRC Trim Interrupt Status Register
//
#define GCR_IRCTRIMINT          0x400000F8

//
//! Register Lock Key Address Register
//
#define GCR_REGLOCK             0x40000100  

//
//! System Power Down Control Register
//
#define SYSCLK_PWRCON           0x40000200  

//
//! AHB Devices Clock Enable Control Register
//
#define SYSCLK_AHBCLK           0x40000204  

//
//! APB Devices Clock Enable Control Register
//
#define SYSCLK_APBCLK0          0x40000208

//
//! APB Devices Clock Enable Control Register1
//
#define SYSCLK_APBCLK1          0x4000020C

//
//! Clock Source Select Control Register 0
//
#define SYSCLK_CLKSEL0          0x40000210 

//
//! Clock Source Select Control Register 1
//
#define SYSCLK_CLKSEL1          0x40000214

//
//! Clock Source Select Control Register 2
//
#define SYSCLK_CLKSEL2          0x40000218

//
//! Clock Source Select Control Register 3
//
#define SYSCLK_CLKSEL3          0x4000021C

//
//! Clock Divider Number Register
//
#define SYSCLK_CLKDIV0          0x40000220  

//
//! Clock Divider Number Register1
//
#define SYSCLK_CLKDIV1          0x40000224

//
//! Clock Divider Number Register2
//
#define SYSCLK_CLKDIV2          0x40000228

//
//! Clock Divider Number Register3
//
#define SYSCLK_CLKDIV3          0x4000022C

//
//! PLL Control Register
//
#define SYSCLK_PLLCON           0x40000240  

//
//! PLL2 Control Register
//
#define SYSCLK_PLLCON2          0x40000244 

//
//! Clock Status Monitor Register
//
#define SYSCLK_CLKSTATUS        0x40000250

//
//! Frequency Divider Control Register
//
#define SYSCLK_FRQDIV           0x40000260

//
//! CClock Fail Detector Control Register 
//
#define SYSCLK_CLKDETCR         0x40000270

//
//! TRIM Control Register
//
#define SYSCLK_CLKTRIM          0x400002F0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_PDID SysCtl Register GCR PDID(SysCtl_GCR_PDID)
//! @{
//
//*****************************************************************************

//
//! Product ID
//
#define GCR_PDID_ID_M           0xFFFFFFFF  
#define GCR_PDID_ID_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_RSTSRC SysCtl Register GCR RSTSRC(SysCtl_GCR_RSTSRC)
//! @{
//
//*****************************************************************************

//
//! "reset signal" from Power-On Reset
//
#define GCR_RSTSRC_POR          BIT_32_0  

//
//! "reset signal" from the /RESET pin
//
#define GCR_RSTSRC_PAD          BIT_32_1  

//
//! "reset signal" from the Watch-Dog
//
#define GCR_RSTSRC_WDG          BIT_32_2  

//
//! "reset signal" from Low-Voltage-Reset
//
#define GCR_RSTSRC_LVR          BIT_32_3  

//
//! "reset signal" from Brown-Out-Detected
//
#define GCR_RSTSRC_BOD          BIT_32_4  

//
//! "reset signal" from MCU Cortex_M0 kernel
//
#define GCR_RSTSRC_SYS          BIT_32_5  

//
//! "reset signal" from CPU_RST (IPRSTCR1[1])
//
#define GCR_RSTSRC_CPU          BIT_32_7  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IPRSTC0 SysCtl GCR IPRSTC0 Register(SysCtl_GCR_IPRSTC0)
//! @{
//
//*****************************************************************************

//
//! CHIP one shot reset
//
#define GCR_IPRSTC1_CHIP        BIT_32_0  

//
//! CPU kernel one shot reset.
//
#define GCR_IPRSTC1_CPU         BIT_32_1

//
//! PDMA Controller Reset (Write-protection)
//
#define GCR_IPRSTC1_DMA         BIT_32_2

//
//! EBI Controller Reset
//
#define GCR_IPRSTC1_EBI         BIT_32_3

//
//! USBH Controller Reset
//
#define GCR_IPRSTC1_USBH        BIT_32_4

//
//! EMAC Controller Reset 
//
#define GCR_IPRSTC1_EMC         BIT_32_5

//
//! SD HOST Controller Reset
//
#define GCR_IPRSTC1_SDH         BIT_32_6

//
//! CRC Controller Reset
//
#define GCR_IPRSTC1_CRC         BIT_32_7

//
//! Image Capture Controller Reset 
//
#define GCR_IPRSTC1_CAP         BIT_32_8

//
//! CRYPTO Controller Reset
//
#define GCR_IPRSTC1_CRYPTO      BIT_32_12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IPRSTC1 SysCtl GCR IPRSTC1 Register(SysCtl_GCR_IPRSTC1)
//! @{
//
//*****************************************************************************

//
//! I2S Controller Reset
//
#define GCR_IPRSTC1_PS2         BIT_32_31

//
//! I2S1 Controller Reset
//
#define GCR_IPRSTC1_I2S1        BIT_32_30

//
//! I2S0 Controller Reset
//
#define GCR_IPRSTC1_I2S0        BIT_32_29

//
//! ADC Controller Reset
//
#define GCR_IPRSTC1_EADC        BIT_32_28

//
//! USB Device Controller Reset
//
#define GCR_IPRSTC1_USBD        BIT_32_27

//
//! USB OTG Controller Reset
//
#define GCR_IPRSTC1_OTG         BIT_32_26

//
//! CAN1 Controller Reset
//
#define GCR_IPRSTC1_CAN1        BIT_32_25

//
//! CAN0 Controller Reset
//
#define GCR_IPRSTC1_CAN0        BIT_32_24

//
//! UART5 controller Reset
//
#define GCR_IPRSTC1_UART5       BIT_32_21

//
//! UART4 controller Reset
//
#define GCR_IPRSTC1_UART4        BIT_32_20

//
//! UART3 Controller Reset
//
#define GCR_IPRSTC1_UART3        BIT_32_19

//
//! UART2 controller Reset
//
#define GCR_IPRSTC1_UART2       BIT_32_18

//
//! UART1 controller Reset
//
#define GCR_IPRSTC1_UART1       BIT_32_17

//
//! UART0 controller Reset
//
#define GCR_IPRSTC1_UART0       BIT_32_16

//
//! SPI3 controller Reset
//
#define GCR_IPRSTC1_SPI3        BIT_32_15

//
//! SPI2 controller Reset
//
#define GCR_IPRSTC1_SPI2        BIT_32_14

//
//! SPI1 controller Reset
//
#define GCR_IPRSTC1_SPI1        BIT_32_13

//
//! SPI0 controller Reset
//
#define GCR_IPRSTC1_SPI0        BIT_32_12

//
//! I2C3 controller Reset
//
#define GCR_IPRSTC1_I2C3        BIT_32_11

//
//! I2C2 controller Reset
//
#define GCR_IPRSTC1_I2C2        BIT_32_10

//
//! I2C1 controller Reset
//
#define GCR_IPRSTC1_I2C1        BIT_32_9

//
//! I2C0 controller Reset
//
#define GCR_IPRSTC1_I2C0        BIT_32_8

//
//! ACMP controller Reset
//
#define GCR_IPRSTC1_ACMP        BIT_32_7

//
//! Timer3 controller Reset
//
#define GCR_IPRSTC1_TME3        BIT_32_5

//
//! Timer2 controller Reset
//
#define GCR_IPRSTC1_TMR2        BIT_32_4

//
//! Timer1 controller Reset
//
#define GCR_IPRSTC1_TMR1        BIT_32_3

//
//! Timer0 controller Reset
//
#define GCR_IPRSTC1_TMR0        BIT_32_2

//
//! GPIO controller Reset
//
#define GCR_IPRSTC1_GPIO        BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IPRSTC3 SysCtl GCR IPRSTC3 Register(SysCtl_GCR_IPRSTC3)
//! @{
//
//*****************************************************************************

//
//! QEI1 Controller Reset
//
#define GCR_IPRSTC2_QEI1        BIT_32_23

//
//! QEI0 Controller Reset
//
#define GCR_IPRSTC2_QEI0         BIT_32_22

//
//! PWM1 Controller Reset
//
#define GCR_IPRSTC2_PWM1        BIT_32_17

//
//! PWM0 Controller Reset
//
#define GCR_IPRSTC2_PWM0        BIT_32_16

//
//! I2C4 Controller Reset
//
#define GCR_IPRSTC2_I2C4        BIT_32_8

//
//! SC5 Controller Reset
//
#define GCR_IPRSTC2_SC5         BIT_32_5

//
//! SC4 Controller Reset
//
#define GCR_IPRSTC2_SC4         BIT_32_4

//
//! SC3 Controller Reset
//
#define GCR_IPRSTC2_SC3         BIT_32_3

//
//! SC2 Controller Reset
//
#define GCR_IPRSTC2_SC2         BIT_32_2

//
//! SC1 Controller Reset
//
#define GCR_IPRSTC2_SC1         BIT_32_1

//
//! SC0 Controller Reset
//
#define GCR_IPRSTC2_SC0         BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_BODCR SysCtl GCR BODCR Register(SysCtl_GCR_BODCR)
//! @{
//
//*****************************************************************************

//
//! Brown Out Detector Enable
//
#define GCR_BODCR_BOD_EN        BIT_32_0  

//
//! Brown Out Detector Threshold Voltage Selection mask
//
#define GCR_BODCR_BOD_VL_M      0x00000006  
                                            
//
//! Brown Out Detector Threshold Voltage Selection shift
//
#define GCR_BODCR_BOD_VL_S      1

//
//! Brown Out Reset Enable
//
#define GCR_BODCR_BOD_RSTEN     BIT_32_3  

//
//! Brown Out Detector Interrupt Flag
//
#define GCR_BODCR_BOD_INTF      BIT_32_4  

//
//! Brown Out Detector Low power Mode
//
#define GCR_BODCR_BOD_LPM       BIT_32_5  

//
//! The status for Brown Out Detector output state
//
#define GCR_BODCR_BOD_OUT       BIT_32_6  
                                            
//
//! Low Voltage Reset Enable
//
#define GCR_BODCR_LVR_EN        BIT_32_7  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_TEMPCR SysCtl GCR Temperature Sensor Control Register(SysCtl_GCR_TEMPCR)
//! @{
//
//*****************************************************************************
#define GCR_TEMPCR_VTEMP_EN     BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_PORCR SysCtl GCR PORCR Register(SysCtl_GCR_PORCR)
//! @{
//
//*****************************************************************************

//
//! POR_DIS_CODE mask
//
#define GCR_PORCR_DIS_CODE_M    0x0000FFFF  

//
//! POR_DIS_CODE shift
//
#define GCR_PORCR_DIS_CODE_S    0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPAMFPL SysCtl GCR GPAMFPL Register(SysCtl_GCR_GPAMFPL)
//! @{
//
//*****************************************************************************

//
//! PA.0 Pin Function Selection
//
#define GCR_GPAMFPL_PA0MFP_M    0x0000000F
#define GCR_GPAMFPL_PA0MFP_S    0

//
//! PA.1 Pin Function Selection
//
#define GCR_GPAMFPL_PA1MFP_M    0x000000F0
#define GCR_GPAMFPL_PA1MFP_S    4

//
//! PA.2 Pin Function Selection
//
#define GCR_GPAMFPL_PA2MFP_M    0x00000F00
#define GCR_GPAMFPL_PA2MFP_S    8

//
//! PA.3 Pin Function Selection
//
#define GCR_GPAMFPL_PA3MFP_M    0x0000F000
#define GCR_GPAMFPL_PA3MFP_S    12

//
//! PA.4 Pin Function Selection
//
#define GCR_GPAMFPL_PA4MFP_M    0x000F0000
#define GCR_GPAMFPL_PA4MFP_S    16

//
//! PA.5 Pin Function Selection
//
#define GCR_GPAMFPL_PA5MFP_M    0x00F00000
#define GCR_GPAMFPL_PA5MFP_S    20

//
//! PA.6 Pin Function Selection
//
#define GCR_GPAMFPL_PA6MFP_M    0x0F000000
#define GCR_GPAMFPL_PA6MFP_S    24

//
//! PA.7 Pin Function Selection
//
#define GCR_GPAMFPL_PA7MFP_M    0xF000000
#define GCR_GPAMFPL_PA7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPAMFPH SysCtl GCR GPAMFPH Register(SysCtl_GCR_GPAMFPH)
//! @{
//
//*****************************************************************************

//
//! PA.8 Pin Function Selection
//
#define GCR_GPAMFPH_PA8MFP_M    0x0000000F
#define GCR_GPAMFPH_PA8MFP_S    0

//
//! PA.9 Pin Function Selection
//
#define GCR_GPAMFPH_PA9MFP_M    0x000000F0
#define GCR_GPAMFPH_PA9MFP_S    4

//
//! PA.10 Pin Function Selection
//
#define GCR_GPAMFPH_PA10MFP_M   0x00000F00
#define GCR_GPAMFPH_PA10MFP_S   8

//
//! PA.11 Pin Function Selection
//
#define GCR_GPAMFPH_PA11MFP_M   0x0000F000
#define GCR_GPAMFPH_PA11MFP_S   12

//
//! PA.12 Pin Function Selection
//
#define GCR_GPAMFPH_PA12MFP_M   0x000F0000
#define GCR_GPAMFPH_PA12MFP_S   16

//
//! PA.13 Pin Function Selection
//
#define GCR_GPAMFPH_PA13MFP_M   0x00F00000
#define GCR_GPAMFPH_PA13MFP_S   20

//
//! PA.14 Pin Function Selection
//
#define GCR_GPAMFPH_PA14MFP_M   0x0F000000
#define GCR_GPAMFPH_PA14MFP_S   24

//
//! PA.15 Pin Function Selection
//
#define GCR_GPAMFPH_PA15MFP_M   0xF000000
#define GCR_GPAMFPH_PA15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPBMFPL SysCtl GCR GPBMFPL Register(SysCtl_GCR_GPBMFPL)
//! @{
//
//*****************************************************************************

//
//! PB.0 Pin Function Selection
//
#define GCR_GPBMFPL_PB0MFP_M    0x0000000F
#define GCR_GPBMFPL_PB0MFP_S    0

//
//! PB.1 Pin Function Selection
//
#define GCR_GPBMFPL_PB1MFP_M    0x000000F0
#define GCR_GPBMFPL_PB1MFP_S    4

//
//! PB.2 Pin Function Selection
//
#define GCR_GPBMFPL_PB2MFP_M    0x00000F00
#define GCR_GPBMFPL_PB2MFP_S    8

//
//! PB.3 Pin Function Selection
//
#define GCR_GPBMFPL_PB3MFP_M    0x0000F000
#define GCR_GPBMFPL_PB3MFP_S    12

//
//! PB.4 Pin Function Selection
//
#define GCR_GPBMFPL_PB4MFP_M    0x000F0000
#define GCR_GPBMFPL_PB4MFP_S    16

//
//! PB.5 Pin Function Selection
//
#define GCR_GPBMFPL_PB5MFP_M    0x00F00000
#define GCR_GPBMFPL_PB5MFP_S    20

//
//! PB.6 Pin Function Selection
//
#define GCR_GPBMFPL_PB6MFP_M    0x0F000000
#define GCR_GPBMFPL_PB6MFP_S    24

//
//! PB.7 Pin Function Selection
//
#define GCR_GPBMFPL_PB7MFP_M    0xF000000
#define GCR_GPBMFPL_PB7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPBMFPH SysCtl GCR GPBMFPH Register(SysCtl_GCR_GPBMFPH)
//! @{
//
//*****************************************************************************

//
//! PB.8 Pin Function Selection
//
#define GCR_GPBMFPH_PB8MFP_M    0x0000000F
#define GCR_GPBMFPH_PB8MFP_S    0

//
//! PB.9 Pin Function Selection
//
#define GCR_GPBMFPH_PB9MFP_M    0x000000F0
#define GCR_GPBMFPH_PB9MFP_S    4

//
//! PB.10 Pin Function Selection
//
#define GCR_GPBMFPH_PB10MFP_M   0x00000F00
#define GCR_GPBMFPH_PB10MFP_S   8

//
//! PB.11 Pin Function Selection
//
#define GCR_GPBMFPH_PB11MFP_M   0x0000F000
#define GCR_GPBMFPH_PB11MFP_S   12

//
//! PB.12 Pin Function Selection
//
#define GCR_GPBMFPH_PB12MFP_M   0x000F0000
#define GCR_GPBMFPH_PB12MFP_S   16

//
//! PB.13 Pin Function Selection
//
#define GCR_GPBMFPH_PB13MFP_M   0x00F00000
#define GCR_GPBMFPH_PB13MFP_S   20

//
//! PB.14 Pin Function Selection
//
#define GCR_GPBMFPH_PB14MFP_M   0x0F000000
#define GCR_GPBMFPH_PB14MFP_S   24

//
//! PB.15 Pin Function Selection
//
#define GCR_GPBMFPH_PB15MFP_M   0xF000000
#define GCR_GPBMFPH_PB15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPCMFPL SysCtl GCR GPCMFPL Register(SysCtl_GCR_GPCMFPL)
//! @{
//
//*****************************************************************************

//
//! PC.0 Pin Function Selection
//
#define GCR_GPCMFPL_PC0MFP_M    0x0000000F
#define GCR_GPCMFPL_PC0MFP_S    0

//
//! PC.1 Pin Function Selection
//
#define GCR_GPCMFPL_PC1MFP_M    0x000000F0
#define GCR_GPCMFPL_PC1MFP_S    4

//
//! PC.2 Pin Function Selection
//
#define GCR_GPCMFPL_PC2MFP_M    0x00000F00
#define GCR_GPCMFPL_PC2MFP_S    8

//
//! PC.3 Pin Function Selection
//
#define GCR_GPCMFPL_PC3MFP_M    0x0000F000
#define GCR_GPCMFPL_PC3MFP_S    12

//
//! PC.4 Pin Function Selection
//
#define GCR_GPCMFPL_PC4MFP_M    0x000F0000
#define GCR_GPCMFPL_PC4MFP_S    16

//
//! PC.5 Pin Function Selection
//
#define GCR_GPCMFPL_PC5MFP_M    0x00F00000
#define GCR_GPCMFPL_PC5MFP_S    20

//
//! PC.6 Pin Function Selection
//
#define GCR_GPCMFPL_PC6MFP_M    0x0F000000
#define GCR_GPCMFPL_PC6MFP_S    24

//
//! PC.7 Pin Function Selection
//
#define GCR_GPCMFPL_PC7MFP_M    0xF000000
#define GCR_GPCMFPL_PC7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPCMFPH SysCtl GCR GPCMFPH Register(SysCtl_GCR_GPCMFPH)
//! @{
//
//*****************************************************************************

//
//! PC.8 Pin Function Selection
//
#define GCR_GPCMFPH_PC8MFP_M    0x0000000F
#define GCR_GPCMFPH_PC8MFP_S    0

//
//! PC.9 Pin Function Selection
//
#define GCR_GPCMFPH_PC9MFP_M    0x000000F0
#define GCR_GPCMFPH_PC9MFP_S    4

//
//! PC.10 Pin Function Selection
//
#define GCR_GPCMFPH_PC10MFP_M   0x00000F00
#define GCR_GPCMFPH_PC10MFP_S   8

//
//! PC.11 Pin Function Selection
//
#define GCR_GPCMFPH_PC11MFP_M   0x0000F000
#define GCR_GPCMFPH_PC11MFP_S   12

//
//! PC.12 Pin Function Selection
//
#define GCR_GPAMFPH_PC12MFP_M   0x000F0000
#define GCR_GPAMFPH_PC12MFP_S   16

//
//! PC.13 Pin Function Selection
//
#define GCR_GPCMFPH_PC13MFP_M   0x00F00000
#define GCR_GPCMFPH_PC13MFP_S   20

//
//! PC.14 Pin Function Selection
//
#define GCR_GPCMFPH_PC14MFP_M   0x0F000000
#define GCR_GPCMFPH_PC14MFP_S   24

//
//! PC.15 Pin Function Selection
//
#define GCR_GPCMFPH_PC15MFP_M   0xF000000
#define GCR_GPCMFPH_PC15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPDMFPL SysCtl GCR GPDMFPL Register(SysCtl_GCR_GPDMFPL)
//! @{
//
//*****************************************************************************

//
//! PD.0 Pin Function Selection
//
#define GCR_GPDMFPL_PD0MFP_M    0x0000000F
#define GCR_GPDMFPL_PD0MFP_S    0

//
//! PD.1 Pin Function Selection
//
#define GCR_GPDMFPL_PD1MFP_M    0x000000F0
#define GCR_GPDMFPL_PD1MFP_S    4

//
//! PD.2 Pin Function Selection
//
#define GCR_GPDMFPL_PD2MFP_M    0x00000F00
#define GCR_GPDMFPL_PD2MFP_S    8

//
//! PD.3 Pin Function Selection
//
#define GCR_GPDMFPL_PD3MFP_M    0x0000F000
#define GCR_GPDMFPL_PD3MFP_S    12

//
//! PD.4 Pin Function Selection
//
#define GCR_GPDMFPL_PD4MFP_M    0x000F0000
#define GCR_GPDMFPL_PD4MFP_S    16

//
//! PD.5 Pin Function Selection
//
#define GCR_GPDMFPL_PD5MFP_M    0x00F00000
#define GCR_GPDMFPL_PD5MFP_S    20

//
//! PD.6 Pin Function Selection
//
#define GCR_GPDMFPL_PD6MFP_M    0x0F000000
#define GCR_GPDMFPL_PD6MFP_S    24

//
//! PD.7 Pin Function Selection
//
#define GCR_GPDMFPL_PD7MFP_M    0xF000000
#define GCR_GPDMFPL_PD7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPDMFPH SysCtl GCR GPDMFPH Register(SysCtl_GCR_GPDMFPH)
//! @{
//
//*****************************************************************************

//
//! PD.8 Pin Function Selection
//
#define GCR_GPDMFPH_PD8MFP_M    0x0000000F
#define GCR_GPDMFPH_PD8MFP_S    0

//
//! PD.9 Pin Function Selection
//
#define GCR_GPDMFPH_PD9MFP_M    0x000000F0
#define GCR_GPDMFPH_PD9MFP_S    4

//
//! PD.10 Pin Function Selection
//
#define GCR_GPDMFPH_PD10MFP_M   0x00000F00
#define GCR_GPDMFPH_PD10MFP_S   8

//
//! PD.11 Pin Function Selection
//
#define GCR_GPDMFPH_PD11MFP_M   0x0000F000
#define GCR_GPDMFPH_PD11MFP_S   12

//
//! PD.12 Pin Function Selection
//
#define GCR_GPDMFPH_PD12MFP_M   0x000F0000
#define GCR_GPDMFPH_PD12MFP_S   16

//
//! PD.13 Pin Function Selection
//
#define GCR_GPDMFPH_PD13MFP_M   0x00F00000
#define GCR_GPDMFPH_PD13MFP_S   20

//
//! PD.14 Pin Function Selection
//
#define GCR_GPDMFPH_PD14MFP_M   0x0F000000
#define GCR_GPDMFPH_PD14MFP_S   24

//
//! PD.15 Pin Function Selection
//
#define GCR_GPDMFPH_PD15MFP_M   0xF000000
#define GCR_GPDMFPH_PD15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPEMFPL SysCtl GCR GPEMFPL Register(SysCtl_GCR_GPEMFPL)
//! @{
//
//*****************************************************************************

//
//! PE.0 Pin Function Selection
//
#define GCR_GPEMFPL_PE0MFP_M    0x0000000F
#define GCR_GPEMFPL_PE0MFP_S    0

//
//! PE.1 Pin Function Selection
//
#define GCR_GPEMFPL_PE1MFP_M    0x000000F0
#define GCR_GPEMFPL_PE1MFP_S    4

//
//! PE.2 Pin Function Selection
//
#define GCR_GPEMFPL_PE2MFP_M    0x00000F00
#define GCR_GPEMFPL_PE2MFP_S    8

//
//! PE.3 Pin Function Selection
//
#define GCR_GPEMFPL_PE3MFP_M    0x0000F000
#define GCR_GPEMFPL_PE3MFP_S    12

//
//! PE.4 Pin Function Selection
//
#define GCR_GPEMFPL_PE4MFP_M    0x000F0000
#define GCR_GPEMFPL_PE4MFP_S    16

//
//! PE.5 Pin Function Selection
//
#define GCR_GPEMFPL_PE5MFP_M    0x00F00000
#define GCR_GPEMFPL_PE5MFP_S    20

//
//! PE.6 Pin Function Selection
//
#define GCR_GPEMFPL_PE6MFP_M    0x0F000000
#define GCR_GPEMFPL_PE6MFP_S    24

//
//! PE.7 Pin Function Selection
//
#define GCR_GPEMFPL_PE7MFP_M    0xF000000
#define GCR_GPEMFPL_PE7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPEMFPH SysCtl GCR GPEMFPH Register(SysCtl_GCR_GPEMFPH)
//! @{
//
//*****************************************************************************

//
//! PE.8 Pin Function Selection
//
#define GCR_GPEMFPH_PE8MFP_M    0x0000000F
#define GCR_GPEMFPH_PE8MFP_S    0

//
//! PE.9 Pin Function Selection
//
#define GCR_GPEMFPH_PE9MFP_M    0x000000F0
#define GCR_GPEMFPH_PE9MFP_S    4

//
//! PE.10 Pin Function Selection
//
#define GCR_GPEMFPH_PE10MFP_M   0x00000F00
#define GCR_GPEMFPH_PE10MFP_S   8

//
//! PE.11 Pin Function Selection
//
#define GCR_GPEMFPH_PE11MFP_M   0x0000F000
#define GCR_GPEMFPH_PE11MFP_S   12

//
//! PE.12 Pin Function Selection
//
#define GCR_GPEMFPH_PE12MFP_M   0x000F0000
#define GCR_GPEMFPH_PE12MFP_S   16

//
//! PE.13 Pin Function Selection
//
#define GCR_GPEMFPH_PE13MFP_M   0x00F00000
#define GCR_GPEMFPH_PE13MFP_S   20

//
//! PE.14 Pin Function Selection
//
#define GCR_GPEMFPH_PE14MFP_M   0x0F000000
#define GCR_GPEMFPH_PE14MFP_S   24

//
//! PE.15 Pin Function Selection
//
#define GCR_GPEMFPH_PE15MFP_M   0xF000000
#define GCR_GPEMFPH_PE15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPFMFPL SysCtl GCR GPFMFPL Register(SysCtl_GCR_GPFMFPL)
//! @{
//
//*****************************************************************************

//
//! PF.0 Pin Function Selection
//
#define GCR_GPFMFPL_PF0MFP_M    0x0000000F
#define GCR_GPFMFPL_PF0MFP_S    0

//
//! PA.1 Pin Function Selection
//
#define GCR_GPFMFPL_PF1MFP_M    0x000000F0
#define GCR_GPFMFPL_PF1MFP_S    4

//
//! PF.2 Pin Function Selection
//
#define GCR_GPFMFPL_PF2MFP_M    0x00000F00
#define GCR_GPFMFPL_PF2MFP_S    8

//
//! PF.3 Pin Function Selection
//
#define GCR_GPFMFPL_PF3MFP_M    0x0000F000
#define GCR_GPFMFPL_PF3MFP_S    12

//
//! PF.4 Pin Function Selection
//
#define GCR_GPFMFPL_PF4MFP_M    0x000F0000
#define GCR_GPFMFPL_PF4MFP_S    16

//
//! PF.5 Pin Function Selection
//
#define GCR_GPFMFPL_PF5MFP_M    0x00F00000
#define GCR_GPFMFPL_PF5MFP_S    20

//
//! PF.6 Pin Function Selection
//
#define GCR_GPFMFPL_PF6MFP_M    0x0F000000
#define GCR_GPFMFPL_PF6MFP_S    24

//
//! PF.7 Pin Function Selection
//
#define GCR_GPFMFPL_PF7MFP_M    0xF000000
#define GCR_GPFMFPL_PF7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPFMFPH SysCtl GCR GPFMFPH Register(SysCtl_GCR_GPFMFPH)
//! @{
//
//*****************************************************************************

//
//! PF.8 Pin Function Selection
//
#define GCR_GPFMFPH_PF8MFP_M    0x0000000F
#define GCR_GPFMFPH_PF8MFP_S    0

//
//! PF.9 Pin Function Selection
//
#define GCR_GPFMFPH_PF9MFP_M    0x000000F0
#define GCR_GPFMFPH_PF9MFP_S    4

//
//! PF.10 Pin Function Selection
//
#define GCR_GPFMFPH_PF10MFP_M   0x00000F00
#define GCR_GPFMFPH_PF10MFP_S   8

//
//! PF.11 Pin Function Selection
//
#define GCR_GPFMFPH_PF11MFP_M   0x0000F000
#define GCR_GPFMFPH_PF11MFP_S   12

//
//! PF.12 Pin Function Selection
//
#define GCR_GPFMFPH_PF12MFP_M   0x000F0000
#define GCR_GPFMFPH_PF12MFP_S   16

//
//! PF.13 Pin Function Selection
//
#define GCR_GPFMFPH_PF13MFP_M   0x00F00000
#define GCR_GPFMFPH_PF13MFP_S   20

//
//! PF.14 Pin Function Selection
//
#define GCR_GPFMFPH_PF14MFP_M   0x0F000000
#define GCR_GPFMFPH_PF14MFP_S   24

//
//! PA.15 Pin Function Selection
//
#define GCR_GPFMFPH_PF15MFP_M   0xF000000
#define GCR_GPFMFPH_PF15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPGMFPL SysCtl GCR GPGMFPL Register(SysCtl_GCR_GPGMFPL)
//! @{
//
//*****************************************************************************

//
//! PG.0 Pin Function Selection
//
#define GCR_GPGMFPL_PG0MFP_M    0x0000000F
#define GCR_GPGMFPL_PG0MFP_S    0

//
//! PG.1 Pin Function Selection
//
#define GCR_GPGMFPL_PG1MFP_M    0x000000F0
#define GCR_GPGMFPL_PG1MFP_S    4

//
//! PG.2 Pin Function Selection
//
#define GCR_GPGMFPL_PG2MFP_M    0x00000F00
#define GCR_GPGMFPL_PG2MFP_S    8

//
//! PG.3 Pin Function Selection
//
#define GCR_GPGMFPL_PG3MFP_M    0x0000F000
#define GCR_GPGMFPL_PG3MFP_S    12

//
//! PG.4 Pin Function Selection
//
#define GCR_GPGMFPL_PG4MFP_M    0x000F0000
#define GCR_GPGMFPL_PG4MFP_S    16

//
//! PG.5 Pin Function Selection
//
#define GCR_GPGMFPL_PG5MFP_M    0x00F00000
#define GCR_GPGMFPL_PG5MFP_S    20

//
//! PG.6 Pin Function Selection
//
#define GCR_GPGMFPL_PG6MFP_M    0x0F000000
#define GCR_GPGMFPL_PG6MFP_S    24

//
//! PG.7 Pin Function Selection
//
#define GCR_GPGMFPL_PG7MFP_M    0xF000000
#define GCR_GPGMFPL_PG7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPGMFPH SysCtl GCR GPGMFPH Register(SysCtl_GCR_GPGMFPH)
//! @{
//
//*****************************************************************************

//
//! PG.8 Pin Function Selection
//
#define GCR_GPGMFPH_PG8MFP_M    0x0000000F
#define GCR_GPGMFPH_PG8MFP_S    0

//
//! PG.9 Pin Function Selection
//
#define GCR_GPGMFPH_PG9MFP_M    0x000000F0
#define GCR_GPGMFPH_PG9MFP_S    4

//
//! PG.10 Pin Function Selection
//
#define GCR_GPGMFPH_PG10MFP_M   0x00000F00
#define GCR_GPGMFPH_PG10MFP_S   8

//
//! PG.11 Pin Function Selection
//
#define GCR_GPGMFPH_PG11MFP_M   0x0000F000
#define GCR_GPGMFPH_PG11MFP_S   12

//
//! PG.12 Pin Function Selection
//
#define GCR_GPGMFPH_PG12MFP_M   0x000F0000
#define GCR_GPGMFPH_PG12MFP_S   16

//
//! PG.13 Pin Function Selection
//
#define GCR_GPGMFPH_PG13MFP_M   0x00F00000
#define GCR_GPGMFPH_PG13MFP_S   20

//
//! PG.14 Pin Function Selection
//
#define GCR_GPGMFPH_PG14MFP_M   0x0F000000
#define GCR_GPGMFPH_PG14MFP_S   24

//
//! PG.15 Pin Function Selection
//
#define GCR_GPGMFPH_PG15MFP_M   0xF000000
#define GCR_GPGMFPH_PG15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPHMFPL SysCtl GCR GPHMFPL Register(SysCtl_GCR_GPHMFPL)
//! @{
//
//*****************************************************************************

//
//! PH.0 Pin Function Selection
//
#define GCR_GPHMFPL_PH0MFP_M    0x0000000F
#define GCR_GPHMFPL_PH0MFP_S    0

//
//! PH.1 Pin Function Selection
//
#define GCR_GPHMFPL_PH1MFP_M    0x000000F0
#define GCR_GPHMFPL_PH1MFP_S    4

//
//! PH.2 Pin Function Selection
//
#define GCR_GPHMFPL_PH2MFP_M    0x00000F00
#define GCR_GPHMFPL_PH2MFP_S    8

//
//! PH.3 Pin Function Selection
//
#define GCR_GPHMFPL_PH3MFP_M    0x0000F000
#define GCR_GPHMFPL_PH3MFP_S    12

//
//! PH.4 Pin Function Selection
//
#define GCR_GPHMFPL_PH4MFP_M    0x000F0000
#define GCR_GPHMFPL_PH4MFP_S    16

//
//! PH.5 Pin Function Selection
//
#define GCR_GPHMFPL_PH5MFP_M    0x00F00000
#define GCR_GPHMFPL_PH5MFP_S    20

//
//! PH.6 Pin Function Selection
//
#define GCR_GPHMFPL_PH6MFP_M    0x0F000000
#define GCR_GPHMFPL_PH6MFP_S    24

//
//! PH.7 Pin Function Selection
//
#define GCR_GPHMFPL_PH7MFP_M    0xF000000
#define GCR_GPHMFPL_PH7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPAMFPH SysCtl GCR GPAMFPH Register(SysCtl_GCR_GPAMFPH)
//! @{
//
//*****************************************************************************

//
//! PH.8 Pin Function Selection
//
#define GCR_GPHMFPH_PH8MFP_M    0x0000000F
#define GCR_GPHMFPH_PH8MFP_S    0

//
//! PH.9 Pin Function Selection
//
#define GCR_GPHMFPH_PH9MFP_M    0x000000F0
#define GCR_GPHMFPH_PH9MFP_S    4

//
//! PH.10 Pin Function Selection
//
#define GCR_GPHMFPH_PH10MFP_M   0x00000F00
#define GCR_GPHMFPH_PH10MFP_S   8

//
//! PH.11 Pin Function Selection
//
#define GCR_GPHMFPH_PH11MFP_M   0x0000F000
#define GCR_GPHMFPH_PH11MFP_S   12

//
//! PH.12 Pin Function Selection
//
#define GCR_GPHMFPH_PH12MFP_M   0x000F0000
#define GCR_GPHMFPH_PH12MFP_S   16

//
//! PH.13 Pin Function Selection
//
#define GCR_GPHMFPH_PH13MFP_M   0x00F00000
#define GCR_GPHMFPH_PH13MFP_S   20

//
//! PH.14 Pin Function Selection
//
#define GCR_GPHMFPH_PH14MFP_M   0x0F000000
#define GCR_GPHMFPH_PH14MFP_S   24

//
//! PH.15 Pin Function Selection
//
#define GCR_GPHMFPH_PH15MFP_M   0xF000000
#define GCR_GPHMFPH_PH15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPIMFPL SysCtl GCR GPIMFPL Register(SysCtl_GCR_GPIMFPL)
//! @{
//
//*****************************************************************************

//
//! PI.0 Pin Function Selection
//
#define GCR_GPIMFPL_PI0MFP_M    0x0000000F
#define GCR_GPIMFPL_PI0MFP_S    0

//
//! PI.1 Pin Function Selection
//
#define GCR_GPIMFPL_PI1MFP_M    0x000000F0
#define GCR_GPIMFPL_PI1MFP_S    4

//
//! PI.2 Pin Function Selection
//
#define GCR_GPIMFPL_PI2MFP_M    0x00000F00
#define GCR_GPIMFPL_PI2MFP_S    8

//
//! PI.3 Pin Function Selection
//
#define GCR_GPIMFPL_PI3MFP_M    0x0000F000
#define GCR_GPIMFPL_PI3MFP_S    12

//
//! PI.4 Pin Function Selection
//
#define GCR_GPIMFPL_PI4MFP_M    0x000F0000
#define GCR_GPIMFPL_PI4MFP_S    16

//
//! PI.5 Pin Function Selection
//
#define GCR_GPIMFPL_PI5MFP_M    0x00F00000
#define GCR_GPIMFPL_PI5MFP_S    20

//
//! PI.6 Pin Function Selection
//
#define GCR_GPIMFPL_PI6MFP_M    0x0F000000
#define GCR_GPIMFPL_PI6MFP_S    24

//
//! PI.7 Pin Function Selection
//
#define GCR_GPIMFPL_PI7MFP_M    0xF000000
#define GCR_GPIMFPL_PI7MFP_S    28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_GPIMFPH SysCtl GCR GPIMFPH Register(SysCtl_GCR_GPIMFPH)
//! @{
//
//*****************************************************************************

//
//! PI.8 Pin Function Selection
//
#define GCR_GPIMFPH_PI8MFP_M    0x0000000F
#define GCR_GPIMFPH_PI8MFP_S    0

//
//! PI.9 Pin Function Selection
//
#define GCR_GPIMFPH_PI9MFP_M    0x000000F0
#define GCR_GPIMFPH_PI9MFP_S    4

//
//! PI.10 Pin Function Selection
//
#define GCR_GPIMFPH_PI10MFP_M   0x00000F00
#define GCR_GPIMFPH_PI10MFP_S   8

//
//! PI.11 Pin Function Selection
//
#define GCR_GPIMFPH_PI11MFP_M   0x0000F000
#define GCR_GPIMFPH_PI11MFP_S   12

//
//! PI.12 Pin Function Selection
//
#define GCR_GPIMFPH_PI12MFP_M   0x000F0000
#define GCR_GPIMFPH_PI12MFP_S   16

//
//! PI.13 Pin Function Selection
//
#define GCR_GPIMFPH_PI13MFP_M   0x00F00000
#define GCR_GPIMFPH_PI13MFP_S   20

//
//! PI.14 Pin Function Selection
//
#define GCR_GPIMFPH_PI14MFP_M   0x0F000000
#define GCR_GPIMFPH_PI14MFP_S   24

//
//! PI.15 Pin Function Selection
//
#define GCR_GPIMFPH_PI15MFP_M   0xF000000
#define GCR_GPIMFPH_PI15MFP_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IRCTRIMCTL SysCtl HIRC Trim Control Register(GCR_IRCTRIMCTL)
//! @{
//
//*****************************************************************************

#define GCR_SRAMINTCTR_PERRIEN  BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IRCTRIMCTL SysCtl HIRC Trim Control Register(GCR_IRCTRIMCTL)
//! @{
//
//*****************************************************************************

//
//! Clock Error Stop Enable
//
#define GCR_CLKERR_STOP_EN      BIT_32_8

#define GCR_TRIM_RETRY_CNT_M    BIT_MASK(32,7,6)
#define GCR_TRIM_RETRY_CNT_S    6

#define GCR_TRIM_LOOP_M         BIT_MASK(32,5,4)
#define GCR_TRIM_LOOP_S         4

#define GCR_TRIM_SEL_M          BIT_MASK(32,1,0)
#define GCR_TRIM_SEL_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IRCTRIMIEN SysCtl HIRC Trim Interrupt Register(GCR_IRCTRIMIEN)
//! @{
//
//*****************************************************************************

//
//! Clock Error Interrupt Enable
//
#define GCR_CLKERR_IEN          BIT_32_2
#define GCR_TRIM_FAIL_IEN       BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_IRCTRIMINT SysCtl HIRC Trim Interrupt Register(GCR_IRCTRIMINT)
//! @{
//
//*****************************************************************************

//
//! Clock Error Interrupt Status
//
#define GCR_CLKERR_INT          BIT_32_2
#define GCR_TRIM_FAIL_INT       BIT_32_1
#define GCR_FREQ_LOCK           BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_GCR_REGLOCK SysCtl GCR_REGLOCK Register(SysCtl_GCR_REGLOCK)
//! @{
//
//*****************************************************************************

//
//! Protected registers are lock FLAG
//
#define GCR_REGLOCK_REGUNLOCK   0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_PWRCON SysCtl PWRCON Register(SysCtl_SYSCLK_PWRCON)
//! @{
//
//*****************************************************************************

//
//! External 12 MHz Crystal Oscillator Control
//
#define SYSCLK_PWRCON_XTL12M_EN 0x00000001

//
//! External 32.768KHz Crystal Oscillator Control
//
#define SYSCLK_PWRCON_XTL32K_EN 0x00000002

//
//! Internal 22 MHz Oscillator Control
//
#define SYSCLK_PWRCON_OSC22M_EN 0x00000004  

//
//! Internal 10 kHz Oscillator Control
//
#define SYSCLK_PWRCON_OSC10K_EN 0x00000008  

//
//! Enable the wake up delay counter.
//
#define SYSCLK_PWRCON_WU_DLY    0x00000010  

//
//! Power down mode wake Up Interrupt Enable
//
#define SYSCLK_PWRCON_PD_INT_EN 0x00000020  

//
//! Chip power down wake up status flag
//
#define SYSCLK_PWRCON_PD_WU_STS 0x00000040  

//
//! System power down active or enable
//
#define SYSCLK_PWRCON_PWR_DO_EN 0x00000080 

//
//! control the power down entry condition
//
#define SYSCLK_PWRCON_PD_WAIT_CPU                                             \
                                0x00000100  
                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_AHBCLK SysCtl AHBCLK Register(SysCtl_SYSCLK_AHBCLK)
//! @{
//
//*****************************************************************************

//
//! Cryptographic Accelerator Clock Enable Control 
//
#define SYSCLK_AHBCLK_CRYPTO_EN BIT_32_12

//
//! USB 2.0 device Clock Enable Control
//
#define SYSCLK_AHBCLK_UDC20_EN  BIT_32_10

//
//! Sensor Clock Enable Control 
//
#define SYSCLK_AHBCLK_SENCLK_EN BIT_32_9

//
//! Image Capture Interface Controller Clock Enable Control 
//
#define SYSCLK_AHBCLK_ICAP_EN   BIT_32_8

//
//! CRC Generator Controller Clock Enable Control
//
#define SYSCLK_AHBCLK_CRC_EN    BIT_32_7

//
//! SDHOST Controller Clock Enable Control 
//
#define SYSCLK_AHBCLK_SDH_EN    BIT_32_6

//
//! Ethernet Controller Clock Enable Control (NUC472 only)
//
#define SYSCLK_AHBCLK_EMAC_EN   BIT_32_5

//
//! USB HOST Controller Clock Enable Control
//
#define SYSCLK_AHBCLK_UHC_EN    BIT_32_4

//
//! EBI Controller Clock Enable Control 
//
#define SYSCLK_AHBCLK_EBI_EN    BIT_32_3

//
//! Flash ISP Controller Clock Enable Control.
//
#define SYSCLK_AHBCLK_ISP_EN    BIT_32_2  

//
//! PDMA Controller Clock Enable Control
//
#define SYSCLK_AHBCLK_DMA_EN    BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_APBCLK SysCtl SYSCLK APBCLK Register(SysCtl_SYSCLK_APBCLK)
//! @{
//
//*****************************************************************************

//
//! Watch Dog Clock Enable.
//
#define SYSCLK_APBCLK0_WDCLK_EN BIT_32_0

//
//! Real-Time-Clock APB interface Clock Enable Control
//
#define SYSCLK_APBCLK0_RTC_EN   BIT_32_1

//
//! Timer0 Clock Enable Control
//
#define SYSCLK_APBCLK0_TMR0_EN  BIT_32_2  

//
//! Timer1 Clock Enable Control
//
#define SYSCLK_APBCLK0_TMR1_EN  BIT_32_3  

//
//! Timer2 Clock Enable Control
//
#define SYSCLK_APBCLK0_TMR2_EN  BIT_32_4  

//
//! Timer3 Clock Enable Control
//
#define SYSCLK_APBCLK0_TMR3_EN  BIT_32_5

//
//! Frequency Divider Output Clock Enable
//
#define SYSCLK_APBCLK0_FDIV_EN  BIT_32_6

//
//! ACMP Clock Enable Control.
//
#define SYSCLK_APBCLK0_ACMP_EN  BIT_32_7
//
//! I2C0 Clock Enable Control.
//
#define SYSCLK_APBCLK0_I2C0_EN  BIT_32_8

//
//! I2C1 Clock Enable Control.
//
#define SYSCLK_APBCLK0_I2C1_EN  BIT_32_9

//
//! I2C2 Clock Enable Control.
//
#define SYSCLK_APBCLK0_I2C2_EN  BIT_32_10

//
//! I2C3 Clock Enable Control.
//
#define SYSCLK_APBCLK0_I2C3_EN  BIT_32_11

//
//! SPI0 Clock Enable Control.
//
#define SYSCLK_APBCLK0_SPI0_EN  BIT_32_12  

//
//! SPI1 Clock Enable Control.
//
#define SYSCLK_APBCLK0_SPI1_EN  BIT_32_13

//
//! SPI2 Clock Enable Control.
//
#define SYSCLK_APBCLK0_SPI2_EN  BIT_32_14

//
//! SPI3 Clock Enable Control.
//
#define SYSCLK_APBCLK0_SPI3_EN  BIT_32_15

//
//! UART0 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART0_EN BIT_32_16  

//
//! UART1 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART1_EN BIT_32_17

//
//! UART2 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART2_EN BIT_32_18

//
//! UART3 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART3_EN BIT_32_19

//
//! UART4 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART4_EN BIT_32_20

//
//! UART5 Clock Enable Control.
//
#define SYSCLK_APBCLK0_UART5_EN BIT_32_21

//
//! CAN0 Clock Enable Control.
//
#define SYSCLK_APBCLK0_CAN0_EN  BIT_32_24

//
//! CAN1 Clock Enable Control.
//
#define SYSCLK_APBCLK0_CAN1_EN  BIT_32_25

//
//! OTG Clock Enable Control.
//
#define SYSCLK_APBCLK0_OTG_EN   BIT_32_26

//
//! ADC Clock Enable Control.
//
#define SYSCLK_APBCLK0_ADC_EN   BIT_32_28

//
//! I2S0 Clock Enable Control.
//
#define SYSCLK_APBCLK0_I2S0_EN  BIT_32_29

//
//! I2S1 Clock Enable Control.
//
#define SYSCLK_APBCLK0_I2S1_EN  BIT_32_30

//
//! PS2 Clock Enable Control.
//
#define SYSCLK_APBCLK0_PS2_EN   BIT_32_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKSEL1 SysCtl CLKSEL1(SysCtl_SYSCLK_CLKSEL1)
//! @{
//
//*****************************************************************************

//
//! SCx Clock Enable Control.
//
#define SYSCLK_APBCLK1_SC0_EN   BIT_32_0
#define SYSCLK_APBCLK1_SC1_EN   BIT_32_1
#define SYSCLK_APBCLK1_SC2_EN   BIT_32_2
#define SYSCLK_APBCLK1_SC3_EN   BIT_32_3
#define SYSCLK_APBCLK1_SC4_EN   BIT_32_4
#define SYSCLK_APBCLK1_SC5_EN   BIT_32_5

//
//! I2C4 Clock Enable Control.
//
#define SYSCLK_APBCLK1_I2C4_EN  BIT_32_8

//
//! PWMA Clock Enable Control.
//
#define SYSCLK_APBCLK1_PWMA01_EN BIT_32_16  
#define SYSCLK_APBCLK1_PWMA23_EN BIT_32_17
#define SYSCLK_APBCLK1_PWMA45_EN BIT_32_18

//
//! PWMB Clock Enable Control.
//
#define SYSCLK_APBCLK1_PWMB01_EN BIT_32_19  
#define SYSCLK_APBCLK1_PWMB23_EN BIT_32_20
#define SYSCLK_APBCLK1_PWMB45_EN BIT_32_21

//
//! Quadrature Encoder Interface Clock Enable Control.
//
#define SYSCLK_APBCLK1_QEI0_EN  BIT_32_22
#define SYSCLK_APBCLK1_QEI1_EN  BIT_32_23

//
//! Enhance CAP Clock Enable Control.
//
#define SYSCLK_APBCLK1_ECAP0_EN BIT_32_26
#define SYSCLK_APBCLK1_ECAP1_EN BIT_32_27

//
//! Enhance PWM Clock Enable Control.
//
#define SYSCLK_APBCLK1_EPWM0_EN BIT_32_28
#define SYSCLK_APBCLK1_EPWM1_EN BIT_32_29

//
//! OP amplifier Clock Enable Control.
//
#define SYSCLK_APBCLK1_OPA_EN   BIT_32_30

//
//! Enhance Analog-Digital-Converter Clock Enable Control.
//
#define SYSCLK_APBCLK1_EADC_EN  BIT_32_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKSTATUS SysCtl Status(SysCtl_SYSCLK_CLKSTATUS)
//! @{
//
//*****************************************************************************

//
//! SC0 Clock Enable Control.
//
#define SYSCLK_STATUS_SW_FAIL   BIT_32_7
#define SYSCLK_STATUS_PLL2_STB  BIT_32_5
#define SYSCLK_STATUS_OSC22_STB BIT_32_4
#define SYSCLK_STATUS_OSC10_STB BIT_32_3
#define SYSCLK_STATUS_PLL_STB   BIT_32_2
#define SYSCLK_STATUS_XTL32_STB BIT_32_1
#define SYSCLK_STATUS_XTL12_STB BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKSEL0 SysCtl CLKSEL0(SysCtl_SYSCLK_CLKSEL0)
//! @{
//
//*****************************************************************************

//
//! HCLK clock source select mask.
//
#define SYSCLK_CLKSEL0_HCLK_M   0x00000007  

//
//! HCLK clock source is external 12 MHz crystal clock
//
#define SYSCLK_CLKSEL0_HCLK12M  0x00000000  

//
//! HCLK clock source from PLL clock/2
//
#define SYSCLK_CLKSEL0_HCLK32K  0x00000001

//
//! HCLK clock source is PLL clock.
//
#define SYSCLK_CLKSEL0_HCLKPLL  0x00000002  

//
//! HCLK clock source is internal 10 kHz oscillator clock.
//
#define SYSCLK_CLKSEL0_HCLK10K  0x00000003  

//
//! HCLK clock source is USB PHY clock.
//
#define SYSCLK_CLKSEL0_HCLKPLL2 0x00000004

//
//! HCLK clock source is internal 22 MHz oscillator clock.
//
#define SYSCLK_CLKSEL0_HCLK22M  0x00000007  

//
//! HCLK clock source select shift.
//
#define SYSCLK_CLKSEL0_HCLK_S   0

//
//! MCU Cortex_M0 SysTick clock source select mask.
//
#define SYSCLK_CLKSEL0_STCLK_M  0x00000038 

//
//! MCU Cortex_M0 SysTick clock source is 12 MHz crystal clock .
//
#define SYSCLK_CLKSEL0_STCLK12M 0x00000000  
#define SYSCLK_CLKSEL0_STCLK32K 0x00000008

//
//! MCU Cortex_M0 SysTick clock source is 12 MHz crystal clock/2.
//
#define SYSCLK_CLKSEL0_STCLK12M_2                                             \
                                0x00000010  
                                
//
//! MCU Cortex_M0 SysTick clock source is HCLK/2.
//
#define SYSCLK_CLKSEL0_STCLKHCLK_2                                            \
                                0x00000018  
                                
//
//! MCU Cortex_M0 SysTick clock source is internal 22 MHz oscillator clock/2.
//
#define SYSCLK_CLKSEL0_STCLKiNT22M_2                                          \
                                0x00000038
 
//
//! MCU Cortex_M0 SysTick clock source select shift.
//   
#define SYSCLK_CLKSEL0_STCLK_S  3

//
//
//
#define SYSCLK_CLKSEL0_PCLK_S   BIT_32_6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKSEL1 SysCtl CLKSEL1 Register(SysCtl_SYSCLK_CLKSEL1)
//! @{
//
//*****************************************************************************
 
//
//! WDG CLK clock source select mask.
//  
#define SYSCLK_CLKSEL1_WDG_M    0x00000003
 
//
//! ADC Clock Source Selection.
//
#define SYSCLK_CLKSEL1_ADC_M    0x0000000C

//
//! SPI0 Clock Source Selection.
//
#define SYSCLK_CLKSEL1_SPI0     0x00000010

//
//! SPI1 Clock Source Selection.
//
#define SYSCLK_CLKSEL1_SPI1     0x00000020

//
//! SPI2 Clock Source Selection.
//
#define SYSCLK_CLKSEL1_SPI2     0x00000040
#define SYSCLK_CLKSEL1_SPI3     0x00000080

//
//! TIMER0 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR0_M   0x00000700  
 
//
//! TIMER1 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR1_M   0x00007000  
 
//
//! TIMER2 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR2_M   0x00070000  

//
//! TIMER3 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR3_M   0x00700000  
 
//
//! UART0 clock source select mask.
//
#define SYSCLK_CLKSEL1_UART_M   0x03000000
 
//
//! PWM0 and PWM1 clock source select mask.
//  
#define SYSCLK_CLKSEL1_PWM01_M  0x30000000  
 
//
//! PWM2 and PWM3 clock source select mask.
//  
#define SYSCLK_CLKSEL1_PWM23_M  0xC0000000  

 
//
//! WDG CLK clock source select shift.
// 
#define SYSCLK_CLKSEL1_WDG_S    0
 
//
//! TIMER0 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR0_S   8
 
//
//! TIMER1 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR1_S   12
 
//
//! TIMER2 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR2_S   16
 
//
//! TIMER3 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR3_S   20
 
//
//! UART clock source select shift.
// 
#define SYSCLK_CLKSEL1_UART_S   24
 
//
//! PWM0 and PWM1 clock source select shift.
//  
#define SYSCLK_CLKSEL1_PWM01_S  28
 
//
//! PWM2 and PWM3 clock source select shift.
//  
#define SYSCLK_CLKSEL1_PWM23_S  30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKSEL2 SysCtl CLKSEL2 Register(SysCtl_SYSCLK_CLKSEL2)
//! @{
//
//*****************************************************************************

//
//! Windowed-Watchdog Timer Clock Source Selection (Write-protection Bits).
//
#define SYSCLK_CLKSEL2_WWDT_M   BIT_MASK(32,17,16)

#define SYSCLK_CLKSEL2_WWDT_S   16

#define SYSCLK_CLKSEL2_PWM45_2 BIT_32_11
#define SYSCLK_CLKSEL2_PWM67_2 BIT_32_10
//
//! PWM2 and PWM3 Clock Source Select Bit [2].
//
#define SYSCLK_CLKSEL2_PWM23_2 BIT_32_9

//
//! WPWM0 and PWM1 Clock Source Select Bit [2].
//
#define SYSCLK_CLKSEL2_PWM01_2 BIT_32_8

#define SYSCLK_CLKSEL2_PWM45_M  BIT_MASK(32,5,4)

#define SYSCLK_CLKSEL2_PWM45_S  4

#define SYSCLK_CLKSEL2_PWM67_M  BIT_MASK(32,7,6)

#define SYSCLK_CLKSEL2_PWM67_S  4

//
//! Clock Divider Clock Source Selection.
//
#define SYSCLK_CLKSEL2_FDIV_M  BIT_MASK(32,3,2)

#define SYSCLK_CLKSEL2_FDIV_S  2

//
//! I2S Clock Source Selection.
//
#define SYSCLK_CLKSEL2_I2S_M   BIT_MASK(32,1,0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKSEL3 SysCtl CLKSEL3 Register(SysCtl_SYSCLK_CLKSEL3)
//! @{
//
//*****************************************************************************

//
//! SC2 Clock Source Selection
//
#define SYSCLK_CLKSEL3_SC2_M    BIT_MASK(32,5,4)
#define SYSCLK_CLKSEL3_SC2_S    4

#define SYSCLK_CLKSEL3_SC1_M    BIT_MASK(32,3,2)
#define SYSCLK_CLKSEL3_SC1_S    2

#define SYSCLK_CLKSEL3_SC0_M    BIT_MASK(32,1,0)
#define SYSCLK_CLKSEL3_SC0_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKDIV SysCtl CLKDIV Register(SysCtl_SYSCLK_CLKDIV)
//! @{
//
//*****************************************************************************
 
//
//! HCLK clock divide number mask.
//
#define SYSCLK_CLKDIV_HCLK_M    0x0000000F
 
//
//! USB clock divide number mask.
//
#define SYSCLK_CLKDIV_USB_M     0x000000F0
 
//
//! UART clock divide number mask.
//
#define SYSCLK_CLKDIV_UART_M    0x00000F00
 
//
//! ADC Clock Divide Number from ADC Clock Source mask.
//
#define SYSCLK_CLKDIV_ADC_M     BIT_MASK(32,23,16)

//
//! HCLK clock divide number shift.
//
#define SYSCLK_CLKDIV_HCLK_S    0
 
//
//! USB clock divide number shift.
//
#define SYSCLK_CLKDIV_USB_S     4
 
//
//! UART clock divide number shift.
//
#define SYSCLK_CLKDIV_UART_S    8

//
//! ADC Clock Divide Number from ADC Clock Source shift.
//
#define SYSCLK_CLKDIV_ADC_S     16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_CLKDIV1 SysCtl CLKDIV1 Register(SysCtl_SYSCLK_CLKDIV1)
//! @{
//
//*****************************************************************************

//
//! SC clock divide number mask.
//
#define SYSCLK_CLKDIV1_SC2_M    BIT_MASK(32,23,16)
#define SYSCLK_CLKDIV1_SC1_M    BIT_MASK(32,15,8)
#define SYSCLK_CLKDIV1_SC0_M    BIT_MASK(32,7,0)

#define SYSCLK_CLKDIV1_SC2_S    16
#define SYSCLK_CLKDIV1_SC1_S    8
#define SYSCLK_CLKDIV1_SC0_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_PLLCON SysCtl PLLCON Register(SysCtl_SYSCLK_PLLCON)
//! @{
//
//*****************************************************************************
 
//
//! PLL Feedback Divider Control Pins mask.
//
#define SYSCLK_PLLCON_FB_DV_M   0x000001FF  
 
//
//! PLL Input Divider Control Pins mask.
//
#define SYSCLK_PLLCON_IN_DV_M   0x00003E00  
 
//
//! PLL Output Divider Control Pins mask.
//
#define SYSCLK_PLLCON_OUT_DV_M  0x0000C000  
 
//
//! Power Down Mode.
//
#define SYSCLK_PLLCON_PD        0x00010000  
 
//
//! PLL Bypass Control.
//
#define SYSCLK_PLLCON_BP        0x00020000  
 
//
//! PLL OE (FOUT enable) pin Control.
//
#define SYSCLK_PLLCON_OE        0x00040000  
 
//
//! PLL Source Clock Select.
//
#define SYSCLK_PLLCON_PLL_SRC   0x00080000  
 
//
//! PLL Feedback Divider Control Pins shift.
//
#define SYSCLK_PLLCON_FB_DV_S   0
 
//
//! PLL Input Divider Control Pins shift.
//
#define SYSCLK_PLLCON_IN_DV_S   9
 
//
//! PLL Output Divider Control Pins shift.
//
#define SYSCLK_PLLCON_OUT_DV_S  14

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_FRQDIV SysCtl FRQDIV Register(SysCtl_SYSCLK_FRQDIV)
//! @{
//
//*****************************************************************************

//
//! Frequency Divider Enable Bit
//
#define SYSCLK_FRQDIV_EN        BIT_32_4

//
//! Divider Output Frequency Select Bits
//
#define SYSCLK_FRQDIV_FSEL_M    BIT_MASK(32,3,0)


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SysCtl_Register_SYSCLK_APBDIV SysCtl APBDIV Register(SysCtl_SYSCLK_APBDIV)
//! @{
//
//*****************************************************************************

//
//! Frequency Divider
//
//#define SYSCLK_APBDIV_DIV       BIT_32_0


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

