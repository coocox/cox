//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.1.1.0
//! \date 2/5/2012
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
//! \addtogroup MINI51_GPIO_Register MINI51 GPIO Register
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
//! \addtogroup MINI51_GPIO_Register_Offsets GPIO Register Offset(Map)
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
//! GPIO PB.0 Bit Output/Input Control
//
#define GPIOB0_DOUT             0x00000220  

//
//! GPIO PB.2 Bit Output/Input Control
//
#define GPIOB2_DOUT             0x00000228

//
//! GPIO PB.3 Bit Output/Input Control
//
#define GPIOB3_DOUT             0x0000022C

//
//! GPIO PB.4 Bit Output/Input Control
//
#define GPIOB4_DOUT             0x00000230

//
//! GPIO PB.5 Bit Output/Input Control
//
#define GPIOB5_DOUT             0x00000234

//
//! GPIO PC.2 Bit Output/Input Control
//
#define GPIOC2_DOUT             0x00000248

//
//! GPIO PC.3 Bit Output/Input Control
//
#define GPIOC3_DOUT             0x0000024C

//
//! GPIO PC.4 Bit Output/Input Control
//
#define GPIOC4_DOUT             0x00000250

//
//! GPIO PC.5 Bit Output/Input Control
//
#define GPIOC5_DOUT             0x00000254

//
//! GPIO PC.6 Bit Output/Input Control
//
#define GPIOC6_DOUT             0x00000258

//
//! GPIO PD.0 Bit Output/Input Control
//
#define GPIOD0_DOUT             0x00000260

//
//! GPIO PD.1 Bit Output/Input Control
//
#define GPIOD1_DOUT             0x00000264

//
//! GPIO PD.2 Bit Output/Input Control
//
#define GPIOD2_DOUT             0x00000268

//
//! GPIO PD.4 Bit Output/Input Control
//
#define GPIOD4_DOUT             0x00000270

//
//! GPIO PD.5 Bit Output/Input Control
//
#define GPIOD5_DOUT             0x00000274

//
//! GPIO PD.6 Bit Output/Input Control
//
#define GPIOD6_DOUT             0x00000278

//
//! GPIO PE.6 Bit Output/Input Control
//
#define GPIOE6_DOUT             0x00000298

//
//! GPIO PE.7 Bit Output/Input Control
//
#define GPIOE7_DOUT             0x0000029C

//
//! GPIO PF.0 Bit Output/Input Control
//
#define GPIOF0_DOUT             0x000002A0

//
//! GPIO PF.1 Bit Output/Input Control
//
#define GPIOF1_DOUT             0x000002A4

//
//! GPIO PF.2 Bit Output/Input Control
//
#define GPIOF2_DOUT             0x000002A8

//
//! GPIO PF.3 Bit Output/Input Control
//
#define GPIOF3_DOUT             0x000002AC

//
//! GPIO PF.4 Bit Output/Input Control
//
#define GPIOF4_DOUT             0x000002B0

//
//! GPIO PF.5 Bit Output/Input Control
//
#define GPIOF5_DOUT             0x000002B4

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
//! Multiple Function Pin GPIOF Control Register
//
#define GCR_GPFMFP              0x50000044 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIO_PMD GPIO Mode Control(GPIO_PMD) 
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

#define GPIO_PMD_PMD0_S         0
#define GPIO_PMD_PMD1_S         2
#define GPIO_PMD_PMD2_S         4
#define GPIO_PMD_PMD3_S         6
#define GPIO_PMD_PMD4_S         8
#define GPIO_PMD_PMD5_S         10
#define GPIO_PMD_PMD6_S         12
#define GPIO_PMD_PMD7_S         14

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIO_OFFD GPIO OFF Digital Enable Register(GPIO_OFFD)
//! \brief Defines for the bit fields in the GPIO_OFFD register.
//! @{
//
//*****************************************************************************

//
//! Pin[n] OFF digital input path Enable mask
//
#define GPIO_OFFD_OFFD_M        0x00FF0000  

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
//! \addtogroup MINI51_GPIO_Register_GPIO_DOUT GPIO Data Output Value Register(GPIO_DOUT)
//! \brief Defines for the bit fields in the GPIO_DOUT register.
//! @{
//
//*****************************************************************************

//
//! Pin[n] Output Value mask
//
#define GPIO_DOUT_DOUT_M        0x000000FF  

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
//! \addtogroup MINI51_GPIO_Register_GPIO_DMASK GPIO Data Output Write Mask Register(GPIO_DMASK)
//! \brief Defines for the bit fields in the GPIO_DMASK register.
//! @{
//
//*****************************************************************************

//
//! Data Output Write Mask
//
#define GPIO_DMASK_DMASK_M      0x000000FF  

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
//! \addtogroup MINI51_GPIO_Register_GPIO_PIN GPIO Pin Value Register(GPIO_PIN)
//! \brief Defines for the bit fields in the GPIO_PIN register.
//! @{
//
//*****************************************************************************

//
//! Port in Values mask
//
#define GPIO_PIN_PIN_M          0x000000FF 

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
//! \addtogroup MINI51_GPIO_Register_GPIO_DBEN GPIO De-bounce Enable Register(De-bounce Enable)
//! \brief Defines for the bit fields in the GPIO_DBEN register.
//! @{
//
//*****************************************************************************

//
//! Input Signal De-bounce Enable mask
//
#define GPIO_DBEN_DBEN_M        0x000000FF  // Input Signal De-bounce Enable

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
//! \addtogroup MINI51_GPIO_Register_GPIO_IMD GPIO Interrupt Mode Control(GPIO_IMD)
//! \brief Defines for the bit fields in the GPIO_IMD register.
//! @{
//
//*****************************************************************************

//
//! Port [A/B/C/D/E/F] Edge or Level Detection Interrupt Control mask
//
#define GPIO_IMD_IMD_M          0x000000FF  

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
//! \addtogroup MINI51_GPIO_Register_GPIO_IEN GPIO Interrupt Enable Register(GPIO_IEN)
//! \brief Defines for the bit fields in the GPIO_IEN register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask
//
#define GPIO_IEN_IR_EN_M        0x00FF0000  

//
//! Interrupt Enable by Input Rising Edge or Input Level High mask shift
//                                            
#define GPIO_IEN_IR_EN_S        16

//
//! Interrupt Enable by Input Falling Edge or Input Level Low mask
//
#define GPIO_IEN_IF_EN_M        0x000000FF  

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
//! \addtogroup MINI51_GPIO_Register_GPIO_ISRC GPIO Interrupt Source Flag Register(GPIO_ISRC)
//! \brief Defines for the bit fields in the GPIO_ISRC register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Trigger Source Indicator mask
//
#define GPIO_ISRC_ISRC_M        0x000000FF  

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
//! \addtogroup MINI51_GPIO_Register_DBNCECON GPIO De-bounce Cycle Control Register(GPIO_DBNCECON)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA0_DOUT GPIOA0 DOUT Register(GPIOA0_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA1_DOUT GPIOA1 DOUT Register(GPIOA1_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA2_DOUT GPIOA2 DOUT Register(GPIOA2_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA3_DOUT GPIOA3 DOUT Register(GPIOA3_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA4_DOUT GPIOA4 DOUT Register(GPIOA4_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA5_DOUT GPIOA5 DOUT Register(GPIOA5_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA6_DOUT GPIOA6 DOUT Register(GPIOA6_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOA7_DOUT GPIOA7 DOUT Register(GPIOA7_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB0_DOUT GPIOB0 DOUT Register(GPIOB0_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB1_DOUT GPIOB1 DOUT Register(GPIOB1_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB2_DOUT GPIOB2 DOUT Register(GPIOB2_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB3_DOUT GPIOB3 DOUT Register(GPIOB3_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB4_DOUT GPIOB4 DOUT Register(GPIOB4_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB5_DOUT GPIOB5 DOUT Register(GPIOB5_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB6_DOUT GPIOB6 DOUT Register(GPIOB6_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOB7_DOUT GPIOB7 DOUT Register(GPIOB7_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC0_DOUT GPIOC0 DOUT Register(GPIOC0_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC1_DOUT GPIOC1 DOUT Register(GPIOC1_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC2_DOUT GPIOC2 DOUT Register(GPIOC2_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC3_DOUT GPIOC3 DOUT Register(GPIOC3_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC4_DOUT GPIOC4 DOUT Register(GPIOC4_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC5_DOUT GPIOC5 DOUT Register(GPIOC5_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC6_DOUT GPIOC6 DOUT Register(GPIOC6_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOC7_DOUT GPIOC7 DOUT Register(GPIOC7_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD0_DOUT GPIOD0 DOUT Register(GPIOD0_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD1_DOUT GPIOD1 DOUT Register(GPIOD1_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD2_DOUT GPIOD2 DOUT Register(GPIOD2_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD3_DOUT GPIOD3 DOUT Register(GPIOD3_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD4_DOUT GPIOD4 DOUT Register(GPIOD4_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD5_DOUT GPIOD5 DOUT Register(GPIOD5_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD6_DOUT GPIOD6 DOUT Register(GPIOD6_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOD7_DOUT GPIOD7 DOUT Register(GPIOD7_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE0_DOUT GPIOE0 DOUT Register(GPIOE0_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE1_DOUT GPIOE1 DOUT Register(GPIOE1_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE2_DOUT GPIOE2 DOUT Register(GPIOE2_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE3_DOUT GPIOE3 DOUT Register(GPIOE3_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE4_DOUT GPIOE4 DOUT Register(GPIOE4_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE5_DOUT GPIOE5 DOUT Register(GPIOE5_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE6_DOUT GPIOE6 DOUT Register(GPIOE6_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOE7_DOUT GPIOE7 DOUT Register(GPIOE7_DOUT)
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
//! \addtogroup MINI51_GPIO_Register_GPIOF0_DOUT GPIOF0 DOUT Register(GPIOF0_DOUT)
//! \brief Defines for the bit fields in the GPIOF0_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF0_DOUT_PF0         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF1_DOUT GPIOF1 DOUT Register(GPIOF1_DOUT)
//! \brief Defines for the bit fields in the GPIOF1_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF1_DOUT_PF1         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF2_DOUT GPIOF2 DOUT Register(GPIOF2_DOUT)
//! \brief Defines for the bit fields in the GPIOF2_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF2_DOUT_PF2         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF3_DOUT GPIOF3 DOUT Register(GPIOF3_DOUT)
//! \brief Defines for the bit fields in the GPIOF3_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF3_DOUT_PF3         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF4_DOUT GPIOF4 DOUT Register(GPIOF4_DOUT)
//! \brief Defines for the bit fields in the GPIOF4_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF4_DOUT_PF4         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF5_DOUT GPIOF5 DOUT Register(GPIOF5_DOUT)
//! \brief Defines for the bit fields in the GPIOF5_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF5_DOUT_PF5         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF6_DOUT GPIOF6 DOUT Register(GPIOF6_DOUT)
//! \brief Defines for the bit fields in the GPIOF6_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF6_DOUT_PF6         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Register_GPIOF7_DOUT GPIOF7 DOUT Register(GPIOF7_DOUT)
//! \brief Defines for the bit fields in the GPIOF7_DOUT register.
//! @{
//
//*****************************************************************************
//
//! Write this bit can control one GPIO pin output value,Read this register to 
//! get IO pin status.
//
#define GPIOF7_DOUT_PF7         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_GPAMFP SysCtl GCR GPAMFP Register(GCR_GPAMFP)
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
//! PA.0 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT0         0x00000100

//
//! PA.1 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT1         0x00000200

//
//! PA.2 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT2         0x00000400

//
//! PA.3 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT3         0x00000800

//
//! PA.4 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT4         0x00001000

//
//! PA.5 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT5         0x00002000

//
//! PA.6 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT6         0x00004000

//
//! PA.7 Pin Alternate Function Selection
//
#define GCR_GPAMFP_ALT7         0x00008000

//
//! PA input Schmitt Trigger function Enable Mask
//
#define GCR_GPAMFP_TYPE_M       0x00ff0000

//
//! PA input Schmitt Trigger function Enable Offset
//
#define GCR_GPAMFP_TYPE_O       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_GPBMFP SysCtl GCR GPBMFP Register(GCR_GPBMFP)
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
//! PB.0 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT0         0x00000100

//
//! PB.1 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT1         0x00000200

//
//! PB.2 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT2         0x00000400

//
//! PB.3 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT3         0x00000800

//
//! PB.4 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT4         0x00001000

//
//! PB.5 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT5         0x00002000

//
//! PB.6 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT6         0x00004000

//
//! PB.7 Pin Alternate Function Selection
//
#define GCR_GPBMFP_ALT7         0x00008000

//
//! PB input Schmitt Trigger function Enable Mask
//
#define GCR_GPBMFP_TYPE_M       0x00ff0000

//
//! PB input Schmitt Trigger function Enable Offset
//
#define GCR_GPBMFP_TYPE_O       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_GPCMFP SysCtl GCR GPCMFP Register(GCR_GPCMFP)
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
//! PC.0 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT0         0x00000100

//
//! PC.1 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT1         0x00000200

//
//! PC.2 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT2         0x00000400

//
//! PC.3 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT3         0x00000800

//
//! PC.4 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT4         0x00001000

//
//! PC.5 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT5         0x00002000

//
//! PC.6 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT6         0x00004000

//
//! PC.7 Pin Alternate Function Selection
//
#define GCR_GPCMFP_ALT7         0x00008000

//
//! PC input Schmitt Trigger function Enable Mask
//
#define GCR_GPCMFP_TYPE_M       0x00ff0000

//
//! PC input Schmitt Trigger function Enable Offset
//
#define GCR_GPCMFP_TYPE_O       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_GPDMFP SysCtl GCR GPDMFP Register(GCR_GPDMFP)
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
//! PD.0 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT0         0x00000100

//
//! PD.1 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT1         0x00000200

//
//! PD.2 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT2         0x00000400

//
//! PD.3 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT3         0x00000800

//
//! PD.4 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT4         0x00001000

//
//! PD.5 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT5         0x00002000

//
//! PD.6 Pin Alternate Function Selection
//
#define GCR_GPDMFP_ALT6         0x00004000

//
//! PD input Schmitt Trigger function Enable Mask
//
#define GCR_GPDMFP_TYPE_M       0x00ff0000

//
//! PD input Schmitt Trigger function Enable Offset
//
#define GCR_GPDMFP_TYPE_O       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_GPEMFP SysCtl GCR GPEMFP Register(GCR_GPEMFP)
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
//! PE.0 Pin Alternate Function Selection
//
#define GCR_GPEMFP_ALT0         0x00000100

//
//! PE.1 Pin Alternate Function Selection
//
#define GCR_GPEMFP_ALT1         0x00000200

//
//! PE input Schmitt Trigger function Enable Mask
//
#define GCR_GPDMFP_TYPE_M       0x00ff0000

//
//! PE input Schmitt Trigger function Enable Offset
//
#define GCR_GPDMFP_TYPE_O       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_GPFMFP SysCtl GCR GPFMFP Register(GCR_GPFMFP)
//! \brief Defines for the bit fields in the GCR_GPFMFP register.
//! @{
//
//*****************************************************************************

//
//! PF.0 Pin Function Selection
//
#define GCR_GPFMFP_MFP0         0x00000001  

//
//! PF.1 Pin Function Selection
//
#define GCR_GPFMFP_MFP1         0x00000002  

//
//! PF.2 Pin Function Selection
//
#define GCR_GPFMFP_MFP2         0x00000004  

//
//! PF.3 Pin Function Selection
//
#define GCR_GPFMFP_MFP3         0x00000008  

//
//! PF.4 Pin Function Selection
//
#define GCR_GPFMFP_MFP4         0x00000010  

//
//! PF.5 Pin Function Selection
//
#define GCR_GPFMFP_MFP5         0x00000020  

//
//! PF.6 Pin Function Selection
//
#define GCR_GPFMFP_MFP6         0x00000040  

//
//! PF.7 Pin Function Selection
//
#define GCR_GPFMFP_MFP7         0x00000080   

//
//! PF.0 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT0         0x00000100

//
//! PF.1 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT1         0x00000200

//
//! PF.2 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT2         0x00000400

//
//! PF.3 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT3         0x00000800

//
//! PF.4 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT4         0x00001000

//
//! PF.5 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT5         0x00002000

//
//! PF.6 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT6         0x00004000

//
//! PF.7 Pin Alternate Function Selection
//
#define GCR_GPFMFP_ALT7         0x00008000

//
//! PF input Schmitt Trigger function Enable Mask
//
#define GCR_GPDMFP_TYPF_M       0x00ff0000

//
//! PF input Schmitt Trigger function Enable Offset
//
#define GCR_GPDMFP_TYPF_O       16

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
