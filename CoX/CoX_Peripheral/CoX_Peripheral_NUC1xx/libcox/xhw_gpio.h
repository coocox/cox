//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.1.1.1
//! \date 11/14/2011
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
//! \addtogroup NUC1xx_GPIO_Register NUC1xx GPIO Register
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
//! \addtogroup NUC1xx_GPIO_Register_Offsets GPIO Register Offset(Map)
//! \brief Here is the GPIO register offset, users can get the register address
//! through <b>GPIO_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! GPIO Port  I/O Mode Control
//
#define GPIO_PMD                0x00000000  

//
//! GPIO Port Pin OFF Digital Enable
//
#define GPIO_OFFD               0x00000004  

//
//! GPIO Port Data Output Value
//
#define GPIO_DOUT               0x00000008  

//
//! GPIO Port Data Output Write Mask
//
#define GPIO_DMASK              0x0000000C   

//
//! GPIO Port Pin Value
//
#define GPIO_PIN                0x00000010  

//
//! GPIO Port De-bounce Enable
//
#define GPIO_DBEN               0x00000014  

//
//! GPIO Port Interrupt Mode Control
//
#define GPIO_IMD                0x00000018  

//
//! GPIO Port Interrupt Enable
//
#define GPIO_IEN                0x0000001C  

//
//! GPIO Port Interrupt Trigger Source Indicator
//
#define GPIO_ISRC               0x00000020  

//
//! GPIO Port External Interrupt De-bounce Control
//
#define GPIO_DBNCECON           0x50004180  

//
//! GPIO PA.0 Bit Output/Input Control
//
#define GPIOA0_DOUT             0x00000200  

//
//! GPIO PA.1 Bit Output/Input Control
//
#define GPIOA1_DOUT             0x00000204

//
//! GPIO PA.2 Bit Output/Input Control
//
#define GPIOA2_DOUT             0x00000208

//
//! GPIO PA.3 Bit Output/Input Control
//
#define GPIOA3_DOUT             0x0000020C

//
//! GPIO PA.4 Bit Output/Input Control
//
#define GPIOA4_DOUT             0x00000210

//
//! GPIO PA.5 Bit Output/Input Control
//
#define GPIOA5_DOUT             0x00000214

//
//! GPIO PA.6 Bit Output/Input Control
//
#define GPIOA6_DOUT             0x00000218

//
//! GPIO PA.7 Bit Output/Input Control
//
#define GPIOA7_DOUT             0x0000021C

//
//! GPIO PA.8 Bit Output/Input Control
//
#define GPIOA8_DOUT             0x00000220

//
//! GPIO PA.9 Bit Output/Input Control
//
#define GPIOA9_DOUT             0x00000224

//
//! GPIO PA.10 Bit Output/Input Control
//
#define GPIOA10_DOUT            0x00000228

//
//! GPIO PA.11 Bit Output/Input Control
//
#define GPIOA11_DOUT            0x0000022C

//
//! GPIO PA.12 Bit Output/Input Control
//
#define GPIOA12_DOUT            0x00000230

//
//! GPIO PA.13 Bit Output/Input Control
//
#define GPIOA13_DOUT            0x00000234

//
//! GPIO PA.14 Bit Output/Input Control
//
#define GPIOA14_DOUT            0x00000238

//
//! GPIO PA.15 Bit Output/Input Control
//
#define GPIOA15_DOUT            0x0000023C

//
//! GPIO PB.0 Bit Output/Input Control
//
#define GPIOB0_DOUT             0x00000240  

//
//! GPIO PB.1 Bit Output/Input Control
//
#define GPIOB1_DOUT             0x00000244

//
//! GPIO PB.2 Bit Output/Input Control
//
#define GPIOB2_DOUT             0x00000248

//
//! GPIO PB.3 Bit Output/Input Control
//
#define GPIOB3_DOUT             0x0000024C

//
//! GPIO PB.4 Bit Output/Input Control
//
#define GPIOB4_DOUT             0x00000250

//
//! GPIO PB.5 Bit Output/Input Control
//
#define GPIOB5_DOUT             0x00000254

//
//! GPIO PB.6 Bit Output/Input Control
//
#define GPIOB6_DOUT             0x00000258

//
//! GPIO PB.7 Bit Output/Input Control
//
#define GPIOB7_DOUT             0x0000025C

//
//! GPIO PB.8 Bit Output/Input Control
//
#define GPIOB8_DOUT             0x00000260

//
//! GPIO PB.9 Bit Output/Input Control
//
#define GPIOB9_DOUT             0x00000264

//
//! GPIO PB.10 Bit Output/Input Control
//
#define GPIOB10_DOUT            0x00000268

//
//! GPIO PB.11 Bit Output/Input Control
//
#define GPIOB11_DOUT            0x0000026C

//
//! GPIO PB.12 Bit Output/Input Control
//
#define GPIOB12_DOUT            0x00000270

//
//! GPIO PB.13 Bit Output/Input Control
//
#define GPIOB13_DOUT            0x00000274

//
//! GPIO PB.14 Bit Output/Input Control
//
#define GPIOB14_DOUT            0x00000278

//
//! GPIO PB.15 Bit Output/Input Control
//
#define GPIOB15_DOUT            0x0000027C

//
//! GPIO PC.0 Bit Output/Input Control
//
#define GPIOC0_DOUT             0x00000280

//
//! GPIO PC.1 Bit Output/Input Control
//
#define GPIOC1_DOUT             0x00000284

//
//! GPIO PC.2 Bit Output/Input Control
//
#define GPIOC2_DOUT             0x00000288

//
//! GPIO PC.3 Bit Output/Input Control
//
#define GPIOC3_DOUT             0x0000028C

//
//! GPIO PC.4 Bit Output/Input Control
//
#define GPIOC4_DOUT             0x00000290

//
//! GPIO PC.5 Bit Output/Input Control
//
#define GPIOC5_DOUT             0x00000294

//
//! GPIO PC.6 Bit Output/Input Control
//
#define GPIOC6_DOUT             0x00000298

//
//! GPIO PC.7 Bit Output/Input Control
//
#define GPIOC7_DOUT             0x0000029C

//
//! GPIO PC.8 Bit Output/Input Control
//
#define GPIOC8_DOUT             0x000002A0

//
//! GPIO PC.9 Bit Output/Input Control
//
#define GPIOC9_DOUT             0x000002A4

//
//! GPIO PC.10 Bit Output/Input Control
//
#define GPIOC10_DOUT            0x000002A8

//
//! GPIO PC.11 Bit Output/Input Control
//
#define GPIOC11_DOUT            0x000002AC

//
//! GPIO PC.12 Bit Output/Input Control
//
#define GPIOC12_DOUT            0x000002B0

//
//! GPIO PC.13 Bit Output/Input Control
//
#define GPIOC13_DOUT            0x000002B4

//
//! GPIO PC.14 Bit Output/Input Control
//
#define GPIOC14_DOUT            0x000002B8

//
//! GPIO PC.15 Bit Output/Input Control
//
#define GPIOC15_DOUT            0x000002BC

//
//! GPIO PD.0 Bit Output/Input Control
//
#define GPIOD0_DOUT             0x000002C0

//
//! GPIO PD.1 Bit Output/Input Control
//
#define GPIOD1_DOUT             0x000002C4

//
//! GPIO PD.2 Bit Output/Input Control
//
#define GPIOD2_DOUT             0x000002C8

//
//! GPIO PD.3 Bit Output/Input Control
//
#define GPIOD3_DOUT             0x000002CC

//
//! GPIO PD.4 Bit Output/Input Control
//
#define GPIOD4_DOUT             0x000002D0

//
//! GPIO PD.5 Bit Output/Input Control
//
#define GPIOD5_DOUT             0x000002D4

//
//! GPIO PD.6 Bit Output/Input Control
//
#define GPIOD6_DOUT             0x000002D8

//
//! GPIO PD.7 Bit Output/Input Control
//
#define GPIOD7_DOUT             0x000002DC

//
//! GPIO PD.8 Bit Output/Input Control
//
#define GPIOD8_DOUT             0x000002E0

//
//! GPIO PD.9 Bit Output/Input Control
//
#define GPIOD9_DOUT             0x000002E4

//
//! GPIO PD.10 Bit Output/Input Control
//
#define GPIOD10_DOUT            0x000002E8

//
//! GPIO PD.11 Bit Output/Input Control
//
#define GPIOD11_DOUT            0x000002EC

//
//! GPIO PD.12 Bit Output/Input Control
//
#define GPIOD12_DOUT            0x000002F0

//
//! GPIO PD.13 Bit Output/Input Control
//
#define GPIOD13_DOUT            0x000002F4

//
//! GPIO PD.14 Bit Output/Input Control
//
#define GPIOD14_DOUT            0x000002F8

//
//! GPIO PD.15 Bit Output/Input Control
//
#define GPIOD15_DOUT            0x000002FC

//
//! GPIO PE.0 Bit Output/Input Control
//
#define GPIOE0_DOUT             0x00000300

//
//! GPIO PE.1 Bit Output/Input Control
//
#define GPIOE1_DOUT             0x00000304

//
//! GPIO PE.2 Bit Output/Input Control
//
#define GPIOE2_DOUT             0x00000308

//
//! GPIO PE.3 Bit Output/Input Control
//
#define GPIOE3_DOUT             0x0000030C

//
//! GPIO PE.4 Bit Output/Input Control
//
#define GPIOE4_DOUT             0x00000310

//
//! GPIO PE.5 Bit Output/Input Control
//
#define GPIOE5_DOUT             0x00000314

//
//! GPIO PE.6 Bit Output/Input Control
//
#define GPIOE6_DOUT             0x00000318

//
//! GPIO PE.7 Bit Output/Input Control
//
#define GPIOE7_DOUT             0x0000031C

//
//! GPIO PE.8 Bit Output/Input Control
//
#define GPIOE8_DOUT             0x00000320

//
//! GPIO PE.9 Bit Output/Input Control
//
#define GPIOE9_DOUT             0x00000324

//
//! GPIO PE.10 Bit Output/Input Control
//
#define GPIOE10_DOUT            0x00000328

//
//! GPIO PE.11 Bit Output/Input Control
//
#define GPIOE11_DOUT            0x0000032C

//
//! GPIO PE.12 Bit Output/Input Control
//
#define GPIOE12_DOUT            0x00000330

//
//! GPIO PE.13 Bit Output/Input Control
//
#define GPIOE13_DOUT            0x00000334

//
//! GPIO PE.14 Bit Output/Input Control
//
#define GPIOE14_DOUT            0x00000338

//
//! GPIO PE.15 Bit Output/Input Control
//
#define GPIOE15_DOUT            0x0000033C

//
//! Multiple Function Pin GPIOA Control Register
//                                         
#define GCR_GPAMFP              0x50000030  

//
//! Multiple Function Pin GPIOB Control Register
//
#define GCR_GPBMFP              0x50000034  

//
//! Multiple Function Pin GPIOC Control Register
//
#define GCR_GPCMFP              0x50000038  

//
//! Multiple Function Pin GPIOD Control Register
//
#define GCR_GPDMFP              0x5000003C  

//
//! Multiple Function Pin GPIOE Control Register
//
#define GCR_GPEMFP              0x50000040  

//
//! Alternative Multiple Function
//
#define GCR_ALTMFP              0x50000050  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_PMD GPIO Mode Control(GPIO_PMD) 
//! \brief Defines for the bit fields in the GPIO_PMD register.
//! @{
//
//*****************************************************************************
//
//! Pin[0] Mode Control
//
#define GPIO_PMD_PMD0_M         0x00000003  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD0_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD0_OUT       0x00000001

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD0_OD        0x00000002

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD0_QB        0x00000003

//
//! Pin[1] Mode Control
//
#define GPIO_PMD_PMD1_M         0x0000000C  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD1_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD1_OUT       0x00000004

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD1_OD        0x00000008

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD1_QB        0x0000000C

//
//! Pin[2] Mode Control
//
#define GPIO_PMD_PMD2_M         0x00000030  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD2_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD2_OUT       0x00000010

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD2_OD        0x00000020

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD2_QB        0x00000030

//
//! Pin[3] Mode Control
//
#define GPIO_PMD_PMD3_M         0x000000C0  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD3_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD3_OUT       0x00000040

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD3_OD        0x00000080

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD3_QB        0x000000C0

//
//! Pin[4] Mode Control
//
#define GPIO_PMD_PMD4_M         0x00000300  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD4_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD4_OUT       0x00000100

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD4_OD        0x00000200

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD4_QB        0x00000300

//
//! Pin[5] Mode Control
//
#define GPIO_PMD_PMD5_M         0x00000C00  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD5_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD5_OUT       0x00000400

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD5_OD        0x00000800

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD5_QB        0x00000C00

//
//! Pin[6] Mode Control
//
#define GPIO_PMD_PMD6_M         0x00003000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD6_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD6_OUT       0x00001000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD6_OD        0x00002000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD6_QB        0x00003000

//
//! Pin[7] Mode Control
//
#define GPIO_PMD_PMD7_M         0x0000C000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD7_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD7_OUT       0x00004000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD7_OD        0x00008000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD7_QB        0x0000C000

//
//! Pin[8] Mode Control
//
#define GPIO_PMD_PMD8_M         0x00030000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD8_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD8_OUT       0x00010000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD8_OD        0x00020000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD8_QB        0x00030000

//
//! Pin[9] Mode Control
//
#define GPIO_PMD_PMD9_M         0x000C0000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD9_IN        0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD9_OUT       0x00040000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD9_OD        0x00080000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD9_QB        0x000C0000

//
//! Pin[10] Mode Control
//
#define GPIO_PMD_PMD10_M        0x00300000 

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD10_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD10_OUT      0x00100000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD10_OD       0x00200000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD10_QB       0x00300000

//
//! Pin[11] Mode Control
//
#define GPIO_PMD_PMD11_M        0x00C00000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD11_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD11_OUT      0x00400000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD11_OD       0x00800000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD11_QB       0x00C00000

//
//! Pin[12] Mode Control
//
#define GPIO_PMD_PMD12_M        0x03000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD12_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD12_OUT      0x01000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD12_OD       0x02000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD12_QB       0x03000000

//
//! Pin[13] Mode Control
//
#define GPIO_PMD_PMD13_M        0x0C000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD13_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD13_OUT      0x04000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD13_OD       0x08000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD13_QB       0x0C000000

//
//! Pin[14] Mode Control
//
#define GPIO_PMD_PMD14_M        0x30000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD14_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD14_OUT      0x10000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD14_OD       0x20000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD14_QB       0x30000000

//
//! Pin[15] Mode Control
//
#define GPIO_PMD_PMD15_M        0xC0000000  

//
//! This Pin is in Control input mode
//
#define GPIO_PMD_PMD15_IN       0x00000000

//
//! This Pin is in Control output mode
//
#define GPIO_PMD_PMD15_OUT      0x40000000

//
//! This Pin is in Control Open-Drain mode
//
#define GPIO_PMD_PMD15_OD       0x80000000

//
//! This Pin is in Control Quasi-bidirectional mode
//
#define GPIO_PMD_PMD15_QB       0xC0000000


#define GPIO_PMD_PMD0_S         0
#define GPIO_PMD_PMD1_S         2
#define GPIO_PMD_PMD2_S         4
#define GPIO_PMD_PMD3_S         6
#define GPIO_PMD_PMD4_S         8
#define GPIO_PMD_PMD5_S         10
#define GPIO_PMD_PMD6_S         12
#define GPIO_PMD_PMD7_S         14
#define GPIO_PMD_PMD8_S         16
#define GPIO_PMD_PMD9_S         18
#define GPIO_PMD_PMD10_S        20
#define GPIO_PMD_PMD11_S        22
#define GPIO_PMD_PMD12_S        24
#define GPIO_PMD_PMD13_S        26
#define GPIO_PMD_PMD14_S        28
#define GPIO_PMD_PMD15_S        30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_OFFD GPIO OFF Digital Enable Register(GPIO_OFFD)
//! \brief Defines for the bit fields in the GPIO_OFFD register.
//! @{
//
//*****************************************************************************

//
//! Pin[n] OFF digital input path Enable mask
//
#define GPIO_OFFD_OFFD_M        0xFFFF0000  

//
//! Pin[n] OFF digital input path Enable shift
//
#define GPIO_OFFD_OFFD_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_DOUT GPIO Data Output Value Register(GPIO_DOUT)
//! \brief Defines for the bit fields in the GPIO_DOUT register.
//! @{
//
//*****************************************************************************

//
//! Pin[n] Output Value mask
//
#define GPIO_DOUT_DOUT_M        0x0000FFFF  

//
//! Pin[n] Output Value shift
//
#define GPIO_DOUT_DOUT_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_DMASK GPIO Data Output Write Mask Register(GPIO_DMASK)
//! \brief Defines for the bit fields in the GPIO_DMASK register.
//! @{
//
//*****************************************************************************

//
//! Data Output Write Mask
//
#define GPIO_DMASK_DMASK_M      0x0000FFFF  

//
//! Data Output Write shift
//
#define GPIO_DMASK_DMASK_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_PIN GPIO Pin Value Register(GPIO_PIN)
//! \brief Defines for the bit fields in the GPIO_PIN register.
//! @{
//
//*****************************************************************************

//
//! Port in Values mask
//
#define GPIO_PIN_PIN_M          0x0000FFFF 

//
//! Port in Values shift
//
#define GPIO_PIN_PIN_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_DBEN GPIO De-bounce Enable Register(De-bounce Enable)
//! \brief Defines for the bit fields in the GPIO_DBEN register.
//! @{
//
//*****************************************************************************

//
//! Input Signal De-bounce Enable mask
//
#define GPIO_DBEN_DBEN_M        0x0000FFFF  // Input Signal De-bounce Enable

//
//! Input Signal De-bounce Enable shift
//
#define GPIO_DBEN_DBEN_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_IMD GPIO Interrupt Mode Control(GPIO_IMD)
//! \brief Defines for the bit fields in the GPIO_IMD register.
//! @{
//
//*****************************************************************************

//
//! Port [A/B/C/D/E] Edge or Level Detection Interrupt Control mask
//
#define GPIO_IMD_IMD_M          0x0000FFFF  

//
//! Port [A/B/C/D/E] Edge or Level Detection Interrupt Control shift
//
#define GPIO_IMD_IMD_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_IEN GPIO Interrupt Enable Register(GPIO_IEN)
//! \brief Defines for the bit fields in the GPIO_IEN register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask
//
#define GPIO_IEN_IR_EN_M        0xFFFF0000  

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask shift
//                                            
#define GPIO_IEN_IR_EN_S        16

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask
//
#define GPIO_IEN_IF_EN_M        0x0000FFFF  

//
//! Interrupt Enable by Input Rising Edge or Input Level High shift
//                                          
#define GPIO_IEN_IF_EN_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIO_ISRC GPIO Interrupt Source Flag Register(GPIO_ISRC)
//! \brief Defines for the bit fields in the GPIO_ISRC register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Trigger Source Indicator mask
//
#define GPIO_ISRC_ISRC_M        0x0000FFFF  

//
//! Interrupt Trigger Source Indicator shift
//
#define GPIO_ISRC_ISRC_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_DBNCECON GPIO De-bounce Cycle Control Register(GPIO_DBNCECON)
//! \brief Defines for the bit fields in the GPIO_DBNCECON register.
//! @{
//
//*****************************************************************************

//
//! Interrupt clock On mode
//
#define GPIO_DBNCECON_ICLK_ON   0x00000020  

//
//! De-bounce counter clock source select
//
#define GPIO_DBNCECON_DBCLKSRC  0x00000010  

//
//! De-bounce sampling cycle selection mask
//
#define GPIO_DBNCECON_DBCLKSEL_M                                               \
                                0x0000000F  
                                
//
//! De-bounce sampling cycle selection shift
//
#define GPIO_DBNCECON_DBCLKSEL_S                                               \
                                0
                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA0_DOUT GPIOA0 DOUT Register(GPIOA0_DOUT)
//! \brief Defines for the bit fields in the GPIOA0_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA0_DOUT_PA0         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA1_DOUT GPIOA1 DOUT Register(GPIOA1_DOUT)
//! \brief Defines for the bit fields in the GPIOA1_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA1_DOUT_PA1         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA2_DOUT GPIOA2 DOUT Register(GPIOA2_DOUT)
//! \brief Defines for the bit fields in the GPIOA2_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA2_DOUT_PA2         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA3_DOUT GPIOA3 DOUT Register(GPIOA3_DOUT)
//! \brief Defines for the bit fields in the GPIOA3_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA3_DOUT_PA3         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA4_DOUT GPIOA4 DOUT Register(GPIOA4_DOUT)
//! \brief Defines for the bit fields in the GPIOA4_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA4_DOUT_PA4         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA5_DOUT GPIOA5 DOUT Register(GPIOA5_DOUT)
//! \brief Defines for the bit fields in the GPIOA5_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA5_DOUT_PA5         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA6_DOUT GPIOA6 DOUT Register(GPIOA6_DOUT)
//! \brief Defines for the bit fields in the GPIOA6_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA6_DOUT_PA6         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA7_DOUT GPIOA7 DOUT Register(GPIOA7_DOUT)
//! \brief Defines for the bit fields in the GPIOA7_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA7_DOUT_PA7         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA8_DOUT GPIOA8 DOUT Register(GPIOA8_DOUT)
//! \brief Defines for the bit fields in the GPIOA8_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA8_DOUT_PA8         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA9_DOUT GPIOA9 DOUT Register(GPIOA9_DOUT)
//! \brief Defines for the bit fields in the GPIOA9_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA9_DOUT_PA9         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA10_DOUT GPIOA10 DOUT Register(GPIOA10_DOUT)
//! \brief Defines for the bit fields in the GPIOA10_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA10_DOUT_PA10       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA11_DOUT GPIOA11 DOUT Register(GPIOA11_DOUT)
//! \brief Defines for the bit fields in the GPIOA11_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA11_DOUT_PA11       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA12_DOUT GPIOA12 DOUT Register(GPIOA12_DOUT)
//! \brief Defines for the bit fields in the GPIOA12_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA12_DOUT_PA12       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA13_DOUT GPIOA13 DOUT Register(GPIOA13_DOUT)
//! \brief Defines for the bit fields in the GPIOA13_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA13_DOUT_PA13       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA14_DOUT GPIOA14 DOUT Register(GPIOA14_DOUT)
//! \brief Defines for the bit fields in the GPIOA14_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA14_DOUT_PA14       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOA15_DOUT GPIOA15 DOUT Register(GPIOA15_DOUT)
//! \brief Defines for the bit fields in the GPIOA15_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOA15_DOUT_PA15       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB0_DOUT GPIOB0 DOUT Register(GPIOB0_DOUT)
//! \brief Defines for the bit fields in the GPIOB0_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB0_DOUT_PB0         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB1_DOUT GPIOB1 DOUT Register(GPIOB1_DOUT)
//! \brief Defines for the bit fields in the GPIOB1_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB1_DOUT_PB1         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB2_DOUT GPIOB2 DOUT Register(GPIOB2_DOUT)
//! \brief Defines for the bit fields in the GPIOB2_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB2_DOUT_PB2         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB3_DOUT GPIOB3 DOUT Register(GPIOB3_DOUT)
//! \brief Defines for the bit fields in the GPIOB3_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB3_DOUT_PB3         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB4_DOUT GPIOB4 DOUT Register(GPIOB4_DOUT)
//! \brief Defines for the bit fields in the GPIOB4_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB4_DOUT_PB4         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB5_DOUT GPIOB5 DOUT Register(GPIOB5_DOUT)
//! \brief Defines for the bit fields in the GPIOB5_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB5_DOUT_PB5         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB6_DOUT GPIOB6 DOUT Register(GPIOB6_DOUT)
//! \brief Defines for the bit fields in the GPIOB6_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB6_DOUT_PB6         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB7_DOUT GPIOB7 DOUT Register(GPIOB7_DOUT)
//! \brief Defines for the bit fields in the GPIOB7_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB7_DOUT_PB7         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB8_DOUT GPIOB8 DOUT Register(GPIOB8_DOUT)
//! \brief Defines for the bit fields in the GPIOB8_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB8_DOUT_PB8         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB9_DOUT GPIOB9 DOUT Register(GPIOB9_DOUT)
//! \brief Defines for the bit fields in the GPIOB9_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB9_DOUT_PB9         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB10_DOUT GPIOB10 DOUT Register(GPIOB10_DOUT)
//! \brief Defines for the bit fields in the GPIOB10_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB10_DOUT_PB10       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB11_DOUT GPIOB11 DOUT Register(GPIOB11_DOUT)
//! \brief Defines for the bit fields in the GPIOB11_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB11_DOUT_PB11       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB12_DOUT GPIOB12 DOUT Register(GPIOB12_DOUT)
//! \brief Defines for the bit fields in the GPIOB12_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB12_DOUT_PB12       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB13_DOUT GPIOB13 DOUT Register(GPIOB13_DOUT)
//! \brief Defines for the bit fields in the GPIOB13_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB13_DOUT_PB13       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB14_DOUT GPIOB14 DOUT Register(GPIOB14_DOUT)
//! \brief Defines for the bit fields in the GPIOB14_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB14_DOUT_PB14       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOB15_DOUT GPIOB15 DOUT Register(GPIOB15_DOUT)
//! \brief Defines for the bit fields in the GPIOB15_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOB15_DOUT_PB15       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC0_DOUT GPIOC0 DOUT Register(GPIOC0_DOUT)
//! \brief Defines for the bit fields in the GPIOC0_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC0_DOUT_PC0         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC1_DOUT GPIOC1 DOUT Register(GPIOC1_DOUT)
//! \brief Defines for the bit fields in the GPIOC1_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC1_DOUT_PC1         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC2_DOUT GPIOC2 DOUT Register(GPIOC2_DOUT)
//! \brief Defines for the bit fields in the GPIOC2_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC2_DOUT_PC2         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC3_DOUT GPIOC3 DOUT Register(GPIOC3_DOUT)
//! \brief Defines for the bit fields in the GPIOC3_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC3_DOUT_PC3         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC4_DOUT GPIOC4 DOUT Register(GPIOC4_DOUT)
//! \brief Defines for the bit fields in the GPIOC4_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC4_DOUT_PC4         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC5_DOUT GPIOC5 DOUT Register(GPIOC5_DOUT)
//! \brief Defines for the bit fields in the GPIOC5_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC5_DOUT_PC5         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC6_DOUT GPIOC6 DOUT Register(GPIOC6_DOUT)
//! \brief Defines for the bit fields in the GPIOC6_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC6_DOUT_PC6         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC7_DOUT GPIOC7 DOUT Register(GPIOC7_DOUT)
//! \brief Defines for the bit fields in the GPIOC7_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC7_DOUT_PC7         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC8_DOUT GPIOC8 DOUT Register(GPIOC8_DOUT)
//! \brief Defines for the bit fields in the GPIOC8_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC8_DOUT_PC8         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC9_DOUT GPIOC9 DOUT Register(GPIOC9_DOUT)
//! \brief Defines for the bit fields in the GPIOC9_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC9_DOUT_PC9         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC10_DOUT GPIOC10 DOUT Register(GPIOC10_DOUT)
//! \brief Defines for the bit fields in the GPIOC10_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC10_DOUT_PC10       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC11_DOUT GPIOC11 DOUT Register(GPIOC11_DOUT)
//! \brief Defines for the bit fields in the GPIOC11_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC11_DOUT_PC11       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC12_DOUT GPIOC12 DOUT Register(GPIOC12_DOUT)
//! \brief Defines for the bit fields in the GPIOC12_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC12_DOUT_PC12       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC13_DOUT GPIOC13 DOUT Register(GPIOC13_DOUT)
//! \brief Defines for the bit fields in the GPIOC13_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC13_DOUT_PC13       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC14_DOUT GPIOC14 DOUT Register(GPIOC14_DOUT)
//! \brief Defines for the bit fields in the GPIOC14_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC14_DOUT_PC14       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOC15_DOUT GPIOC15 DOUT Register(GPIOC15_DOUT)
//! \brief Defines for the bit fields in the GPIOC15_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOC15_DOUT_PC15       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD0_DOUT GPIOD0 DOUT Register(GPIOD0_DOUT)
//! \brief Defines for the bit fields in the GPIOD0_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD0_DOUT_PD0         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD1_DOUT GPIOD1 DOUT Register(GPIOD1_DOUT)
//! \brief Defines for the bit fields in the GPIOD1_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD1_DOUT_PD1         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD2_DOUT GPIOD2 DOUT Register(GPIOD2_DOUT)
//! \brief Defines for the bit fields in the GPIOD2_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD2_DOUT_PD2         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD3_DOUT GPIOD3 DOUT Register(GPIOD3_DOUT)
//! \brief Defines for the bit fields in the GPIOD3_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD3_DOUT_PD3         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD4_DOUT GPIOD4 DOUT Register(GPIOD4_DOUT)
//! \brief Defines for the bit fields in the GPIOD4_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD4_DOUT_PD4         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD5_DOUT GPIOD5 DOUT Register(GPIOD5_DOUT)
//! \brief Defines for the bit fields in the GPIOD5_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD5_DOUT_PD5         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD6_DOUT GPIOD6 DOUT Register(GPIOD6_DOUT)
//! \brief Defines for the bit fields in the GPIOD6_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD6_DOUT_PD6         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD7_DOUT GPIOD7 DOUT Register(GPIOD7_DOUT)
//! \brief Defines for the bit fields in the GPIOD7_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD7_DOUT_PD7         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD8_DOUT GPIOD8 DOUT Register(GPIOD8_DOUT)
//! \brief Defines for the bit fields in the GPIOD8_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD8_DOUT_PD8         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD9_DOUT GPIOD9 DOUT Register(GPIOD9_DOUT)
//! \brief Defines for the bit fields in the GPIOD9_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD9_DOUT_PD9         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD10_DOUT GPIOD10 DOUT Register(GPIOD10_DOUT)
//! \brief Defines for the bit fields in the GPIOD10_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD10_DOUT_PD10       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
// 
//! \addtogroup NUC1xx_GPIO_Register_GPIOD11_DOUT GPIOD11 DOUT Register(GPIOD11_DOUT)
//! \brief Defines for the bit fields in the GPIOD11_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD11_DOUT_PD11       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD12_DOUT GPIOD12 DOUT Register(GPIOD12_DOUT)
//! \brief Defines for the bit fields in the GPIOD12_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD12_DOUT_PD12       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD13_DOUT GPIOD13 DOUT Register(GPIOD13_DOUT)
//! \brief Defines for the bit fields in the GPIOD13_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD13_DOUT_PD13       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD14_DOUT GPIOD14 DOUT Register(GPIOD14_DOUT)
//! \brief Defines for the bit fields in the GPIOD14_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD14_DOUT_PD14       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOD15_DOUT GPIOD15 DOUT Register(GPIOD15_DOUT)
//! \brief Defines for the bit fields in the GPIOD15_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOD15_DOUT_PD15       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE0_DOUT GPIOE0 DOUT Register(GPIOE0_DOUT)
//! \brief Defines for the bit fields in the GPIOE0_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE0_DOUT_PE0         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE1_DOUT GPIOE1 DOUT Register(GPIOE1_DOUT)
//! \brief Defines for the bit fields in the GPIOE1_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE1_DOUT_PE1         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE2_DOUT GPIOE2 DOUT Register(GPIOE2_DOUT)
//! \brief Defines for the bit fields in the GPIOE2_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE2_DOUT_PE2         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE3_DOUT GPIOE3 DOUT Register(GPIOE3_DOUT)
//! \brief Defines for the bit fields in the GPIOE3_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE3_DOUT_PE3         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE4_DOUT GPIOE4 DOUT Register(GPIOE4_DOUT)
//! \brief Defines for the bit fields in the GPIOE4_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE4_DOUT_PE4         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE5_DOUT GPIOE5 DOUT Register(GPIOE5_DOUT)
//! \brief Defines for the bit fields in the GPIOE5_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE5_DOUT_PE5         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE6_DOUT GPIOE6 DOUT Register(GPIOE6_DOUT)
//! \brief Defines for the bit fields in the GPIOE6_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE6_DOUT_PE6         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE7_DOUT GPIOE7 DOUT Register(GPIOE7_DOUT)
//! \brief Defines for the bit fields in the GPIOE7_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE7_DOUT_PE7         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE8_DOUT GPIOE8 DOUT Register(GPIOE8_DOUT)
//! \brief Defines for the bit fields in the GPIOE8_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE8_DOUT_PE8         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE9_DOUT GPIOE9 DOUT Register(GPIOE9_DOUT)
//! \brief Defines for the bit fields in the GPIOE9_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE9_DOUT_PE9         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE10_DOUT GPIOE10 DOUT Register(GPIOE10_DOUT)
//! \brief Defines for the bit fields in the GPIOE10_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE10_DOUT_PE10       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE11_DOUT GPIOE11 DOUT Register(GPIOE11_DOUT)
//! \brief Defines for the bit fields in the GPIOE11_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE11_DOUT_PE11       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE12_DOUT GPIOE12 DOUT Register(GPIOE12_DOUT)
//! \brief Defines for the bit fields in the GPIOE12_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE12_DOUT_PE12       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE13_DOUT GPIOE13 DOUT Register(GPIOE13_DOUT)
//! \brief Defines for the bit fields in the GPIOE13_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE13_DOUT_PE13       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE14_DOUT GPIOE14 DOUT Register(GPIOE14_DOUT)
//! \brief Defines for the bit fields in the GPIOE14_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE14_DOUT_PE14       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Register_GPIOE15_DOUT GPIOE15 DOUT Register(GPIOE15_DOUT)
//! \brief Defines for the bit fields in the GPIOE15_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOE15_DOUT_PE15       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPAMFP SysCtl GCR GPAMFP Register(GCR_GPAMFP)
//! \brief Defines for the bit fields in the GCR_GPAMFP register.
//! @{
//
//*****************************************************************************

//
//! PA.0 Pin Function Selection
//
#define GCR_GPAMFP_MFP0         0x00000001  

//
//! PA.1 Pin Function Selection
//
#define GCR_GPAMFP_MFP1         0x00000002  

//
//! PA.2 Pin Function Selection
//
#define GCR_GPAMFP_MFP2         0x00000004  

//
//! PA.3 Pin Function Selection
//
#define GCR_GPAMFP_MFP3         0x00000008  

//
//! PA.4 Pin Function Selection
//
#define GCR_GPAMFP_MFP4         0x00000010  

//
//! PA.5 Pin Function Selection
//
#define GCR_GPAMFP_MFP5         0x00000020  

//
//! PA.6 Pin Function Selection
//
#define GCR_GPAMFP_MFP6         0x00000040  

//
//! PA.7 Pin Function Selection
//
#define GCR_GPAMFP_MFP7         0x00000080  

//
//! PA.8 Pin Function Selection
//
#define GCR_GPAMFP_MFP8         0x00000100  

//
//! PA.9 Pin Function Selection
//
#define GCR_GPAMFP_MFP9         0x00000200  

//
//! PA.10 Pin Function Selection
//
#define GCR_GPAMFP_MFP10        0x00000400  

//
//! PA.11 Pin Function Selection
//
#define GCR_GPAMFP_MFP11        0x00000800  

//
//! PA.12 Pin Function Selection
//
#define GCR_GPAMFP_MFP12        0x00001000  

//
//! PA.13 Pin Function Selection
//
#define GCR_GPAMFP_MFP13        0x00002000  

//
//! PA.14 Pin Function Selection
//
#define GCR_GPAMFP_MFP14        0x00004000  

//
//! PA.15 Pin Function Selection
//
#define GCR_GPAMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPBMFP SysCtl GCR GPBMFP Register(GCR_GPBMFP)
//! \brief Defines for the bit fields in the GCR_GPBMFP register.
//! @{
//
//*****************************************************************************

//
//! PB.0 Pin Function Selection
//
#define GCR_GPBMFP_MFP0         0x00000001  

//
//! PB.1 Pin Function Selection
//
#define GCR_GPBMFP_MFP1         0x00000002  

//
//! PB.2 Pin Function Selection
//
#define GCR_GPBMFP_MFP2         0x00000004  

//
//! PB.3 Pin Function Selection
//
#define GCR_GPBMFP_MFP3         0x00000008  

//
//! PB.4 Pin Function Selection
//
#define GCR_GPBMFP_MFP4         0x00000010  

//
//! PB.5 Pin Function Selection
//
#define GCR_GPBMFP_MFP5         0x00000020  

//
//! PB.6 Pin Function Selection
//
#define GCR_GPBMFP_MFP6         0x00000040  

//
//! PB.7 Pin Function Selection
//
#define GCR_GPBMFP_MFP7         0x00000080  

//
//! PB.8 Pin Function Selection
//
#define GCR_GPBMFP_MFP8         0x00000100  

//
//! PB.9 Pin Function Selection
//
#define GCR_GPBMFP_MFP9         0x00000200  

//
//! PB.10 Pin Function Selection
//
#define GCR_GPBMFP_MFP10        0x00000400  

//
//! PB.11 Pin Function Selection
//
#define GCR_GPBMFP_MFP11        0x00000800  

//
//! PB.12 Pin Function Selection
//
#define GCR_GPBMFP_MFP12        0x00001000  

//
//! PB.13 Pin Function Selection
//
#define GCR_GPBMFP_MFP13        0x00002000  

//
//! PB.14 Pin Function Selection
//
#define GCR_GPBMFP_MFP14        0x00004000  

//
//! PB.15 Pin Function Selection
//
#define GCR_GPBMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPCMFP SysCtl GCR GPCMFP Register(GCR_GPCMFP)
//! \brief Defines for the bit fields in the GCR_GPCMFP register.
//! @{
//
//*****************************************************************************

//
//! PC.0 Pin Function Selection
//
#define GCR_GPCMFP_MFP0         0x00000001  

//
//! PC.1 Pin Function Selection
//
#define GCR_GPCMFP_MFP1         0x00000002  

//
//! PC.2 Pin Function Selection
//
#define GCR_GPCMFP_MFP2         0x00000004  

//
//! PC.3 Pin Function Selection
//
#define GCR_GPCMFP_MFP3         0x00000008  

//
//! PC.4 Pin Function Selection
//
#define GCR_GPCMFP_MFP4         0x00000010  

//
//! PC.5 Pin Function Selection
//
#define GCR_GPCMFP_MFP5         0x00000020  

//
//! PC.6 Pin Function Selection
//
#define GCR_GPCMFP_MFP6         0x00000040  

//
//! PC.7 Pin Function Selection
//
#define GCR_GPCMFP_MFP7         0x00000080  

//
//! PC.8 Pin Function Selection
//
#define GCR_GPCMFP_MFP8         0x00000100  

//
//! PC.9 Pin Function Selection
//
#define GCR_GPCMFP_MFP9         0x00000200  

//
//! PC.10 Pin Function Selection
//
#define GCR_GPCMFP_MFP10        0x00000400  

//
//! PC.11 Pin Function Selection
//
#define GCR_GPCMFP_MFP11        0x00000800  

//
//! PC.12 Pin Function Selection
//
#define GCR_GPCMFP_MFP12        0x00001000  

//
//! PC.13 Pin Function Selection
//
#define GCR_GPCMFP_MFP13        0x00002000  

//
//! PC.14 Pin Function Selection
//
#define GCR_GPCMFP_MFP14        0x00004000  

//
//! PC.15 Pin Function Selection
//
#define GCR_GPCMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPDMFP SysCtl GCR GPDMFP Register(GCR_GPDMFP)
//! \brief Defines for the bit fields in the GCR_GPDMFP register.
//! @{
//
//*****************************************************************************

//
//! PD.0 Pin Function Selection
//
#define GCR_GPDMFP_MFP0         0x00000001  

//
//! PD.1 Pin Function Selection
//
#define GCR_GPDMFP_MFP1         0x00000002  

//
//! PD.2 Pin Function Selection
//
#define GCR_GPDMFP_MFP2         0x00000004  

//
//! PD.3 Pin Function Selection
//
#define GCR_GPDMFP_MFP3         0x00000008  

//
//! PD.4 Pin Function Selection
//
#define GCR_GPDMFP_MFP4         0x00000010  

//
//! PD.5 Pin Function Selection
//
#define GCR_GPDMFP_MFP5         0x00000020  

//
//! PD.6 Pin Function Selection
//
#define GCR_GPDMFP_MFP6         0x00000040  

//
//! PD.7 Pin Function Selection
//
#define GCR_GPDMFP_MFP7         0x00000080  

//
//! PD.8 Pin Function Selection
//
#define GCR_GPDMFP_MFP8         0x00000100  

//
//! PD.9 Pin Function Selection
//
#define GCR_GPDMFP_MFP9         0x00000200  

//
//! PD.10 Pin Function Selection
//
#define GCR_GPDMFP_MFP10        0x00000400  

//
//! PD.11 Pin Function Selection
//
#define GCR_GPDMFP_MFP11        0x00000800  

//
//! PD.12 Pin Function Selection
//
#define GCR_GPDMFP_MFP12        0x00001000  

//
//! PD.13 Pin Function Selection
//
#define GCR_GPDMFP_MFP13        0x00002000  

//
//! PD.14 Pin Function Selection
//
#define GCR_GPDMFP_MFP14        0x00004000  

//
//! PD.15 Pin Function Selection
//
#define GCR_GPDMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPEMFP SysCtl GCR GPEMFP Register(GCR_GPEMFP)
//! \brief Defines for the bit fields in the GCR_GPEMFP register.
//! @{
//
//*****************************************************************************

//
//! PE.0 Pin Function Selection
//
#define GCR_GPEMFP_MFP0         0x00000001  

//
//! PE.1 Pin Function Selection
//
#define GCR_GPEMFP_MFP1         0x00000002  

//
//! PE.2 Pin Function Selection
//
#define GCR_GPEMFP_MFP2         0x00000004  

//
//! PE.3 Pin Function Selection
//
#define GCR_GPEMFP_MFP3         0x00000008  

//
//! PE.4 Pin Function Selection
//
#define GCR_GPEMFP_MFP4         0x00000010  

//
//! PE.5 Pin Function Selection
//
#define GCR_GPEMFP_MFP5         0x00000020  

//
//! PE.6 Pin Function Selection
//
#define GCR_GPEMFP_MFP6         0x00000040  

//
//! PE.7 Pin Function Selection
//
#define GCR_GPEMFP_MFP7         0x00000080  

//
//! PE.8 Pin Function Selection
//
#define GCR_GPEMFP_MFP8         0x00000100  

//
//! PE.9 Pin Function Selection
//
#define GCR_GPEMFP_MFP9         0x00000200  

//
//! PE.10 Pin Function Selection
//
#define GCR_GPEMFP_MFP10        0x00000400  

//
//! PE.11 Pin Function Selection
//
#define GCR_GPEMFP_MFP11        0x00000800  

//
//! PE.12 Pin Function Selection
//
#define GCR_GPEMFP_MFP12        0x00001000  

//
//! PE.13 Pin Function Selection
//
#define GCR_GPEMFP_MFP13        0x00002000  

//
//! PE.`4 Pin Function Selection
//
#define GCR_GPEMFP_MFP14        0x00004000  

//
//! PE.15 Pin Function Selection
//
#define GCR_GPEMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_ALTMFP SysCtl GCR ALTMFP Register(GCR_ALTMFP)
//! \brief Defines for the bit fields in the GCR_ALTMFP register.
//! @{
//
//*****************************************************************************

//
//! PB.10 Pin Function Selection
//
#define GCR_ALTMFP_PB10_S01     0x00000001  

//
//! PB.9 Pin Function Selection
//
#define GCR_ALTMFP_PB9_S11      0x00000002  

//
//! PA.7 Pin Function Selection
//
#define GCR_ALTMFP_PA7_S21      0x00000004  

//
//! PB.14 Pin Function Selection
//
#define GCR_ALTMFP_PB14_S31     0x00000008  

//
//! PB.11 Pin Function Selection
//
#define GCR_ALTMFP_PB11_PWM4    0x00000010  

//
//! PC.0 Pin Function Selection
//
#define GCR_ALTMFP_PC0_I2SLRCLK 0x00000020  

//
//! PC.1 Pin Function Selection
//
#define GCR_ALTMFP_PC1_I2SBCLK  0x00000040  

//
//! PC.2 Pin Function Selection
//
#define GCR_ALTMFP_PC2_I2SDI    0x00000080  

//
//! PC.3 Pin Function Selection
//
#define GCR_ALTMFP_PC3_I2SDO    0x00000100  

//
//! PA.15 Pin Function Selection
//
#define GCR_ALTMFP_PA15_I2SMCLK 0x00000200  

//
//! PB.12 Pin Function Selection
//
#define GCR_ALTMFP_PB12_CLKO    0x00000400

//
//! EBI_EN is use to switch GPIO function to EBI function (AD[15:0], ALE, RE,
//! WE, CS,MCLK), it need additional registers EBI_EN[7:0] and EBI_MCLK_EN for
//! some GPIO to switch to EBI function(AD[15:8], MCLK)
//
#define GCR_ALTMFP_EBI_EN       0x00000800 

//
//! Bits EBI_MCLK_EN, EBI_EN and GPC_MFP[8] determine the PC.8 function.
//
#define GCR_ALTMFP_EBI_MCLK_EN  0x00001000

//
//! Bits EBI_nWRL_EN, EBI_EN and GPB_MFP[2] determine the PB.2 function.
//
#define GCR_ALTMFP_EBI_nWRL_EN  0x00002000

//
//! Bits EBI_nWRH_EN, EBI_EN and GPB_MFP[3] determine the PB.3 function.
//
#define GCR_ALTMFP_EBI_nWRH_EN  0x00004000

//
//! Bits EBI_HB_EN[0], EBI_EN and GPA_MFP[5] determine the PA.5 function.
//
#define GCR_ALTMFP_EBI_HB_EN_0 0x00010000

//
//! Bits EBI_HB_EN[1], EBI_EN and GPA_MFP[4] determine the PA.4 function.
//
#define GCR_ALTMFP_EBI_HB_EN_1 0x00020000

//
//! Bits EBI_HB_EN[2], EBI_EN and GPA_MFP[3] determine the PA.3 function.
//
#define GCR_ALTMFP_EBI_HB_EN_2 0x00040000

//
//! Bits EBI_HB_EN[3], EBI_EN and GPA_MFP[2] determine the PA.2 function.
//
#define GCR_ALTMFP_EBI_HB_EN_3 0x00080000

//
//! Bits EBI_HB_EN[4], EBI_EN and GPA_MFP[1] determine the PA.1 function.
//
#define GCR_ALTMFP_EBI_HB_EN_4 0x00100000

//
//! Bits EBI_HB_EN[5], EBI_EN and GPA_MFP[12] determine the PA.12 function.
//
#define GCR_ALTMFP_EBI_HB_EN_5 0x00200000

//
//! Bits EBI_HB_EN[6], EBI_EN and GPA_MFP[13] determine the PA.13 function.
//
#define GCR_ALTMFP_EBI_HB_EN_6 0x00400000

//
//! Bits EBI_HB_EN[7], EBI_EN and GPA_MFP[14] determine the PA.14 function.
//
#define GCR_ALTMFP_EBI_HB_EN_7 0x00800000

//
//! Bits GPB_MFP15 and PB15_T0EX (ALT_MFP[24]) determine the PB.15 function.
//
#define GCR_ALTMFP_PB15_T0EX    0x01000000

//
//! Bits GPE_MFP5 and PE5_T1EX (ALT_MFP[25]) determine the PE.5 function.
//
#define GCR_ALTMFP_PE5_T1EX     0x02000000

//
//! Bits GPB_MFP2 and EBI_nWRL_EN (ALT_MFP[13]) and EBI_EN (ALT_MFP[11]) and
//! PB2_T2EX (ALT_MFP[26]) determine the PB.2 function.
//
#define GCR_ALTMFP_PB2_T2EX     0x04000000

//
//! Bits GPB_MFP3 and EBI_nWRH_EN (ALT_MFP[14]) and EBI_EN (ALT_MFP[11]) and
//! PB3_T3EX (ALT_MFP[27]) determine the PB.3 function.
//
#define GCR_ALTMFP_PB3_T3EX     0x08000000


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
