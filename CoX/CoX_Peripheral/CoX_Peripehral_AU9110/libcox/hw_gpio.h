//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.2.1.0
//! \date 6/15/2014
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


#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

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
//! \addtogroup AU9110_GPIO_Register AU9110 GPIO Register
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
//! \addtogroup AU9110_GPIO_Register_Offsets GPIO Register Offset(Map)
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
//! GPIO Port Bit input Disable
//
#define GPIO_INDIS              0x00000004

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
//! De-bounce Cycle Control
//
#define GPIO_DBNCECON           0x50004180

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_GPIO_Register_GPIO_PMD GPIO Mode Control(GPIO_PMD)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_INDIS GPIO Input Disable Register(GPIO_INDIS)
//! \brief Defines for the bit fields in the GPIO_OFFD register.
//! @{
//
//*****************************************************************************

//
//! Pin0 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_0      0x00010000

//
//! Pin1 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_1      0x00020000

//
//! Pin2 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_2      0x00040000

//
//! Pin3 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_3      0x00080000

//
//! Pin4 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_4      0x00100000

//
//! Pin5 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_5      0x00200000

//
//! Pin6 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_6      0x00400000

//
//! Pin7 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_7      0x00800000

//
//! Pin8 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_8      0x01000000

//
//! Pin9 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_9      0x02000000

//
//! Pin10 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_10     0x04000000

//
//! Pin11 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_11     0x08000000

//
//! Pin12 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_12     0x10000000

//
//! Pin13 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_13     0x20000000

//
//! Pin14 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_14     0x40000000

//
//! Pin15 Disable IO digital input path
//
#define GPIO_INDIS_INDIS_15     0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_GPIO_Register_GPIO_DOUT GPIO Data Output Value Register(GPIO_DOUT)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_DMASK GPIO Data Output Write Mask Register(GPIO_DMASK)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_PIN GPIO Pin Value Register(GPIO_PIN)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_DBEN GPIO De-bounce Enable Register(De-bounce Enable)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_IMD GPIO Interrupt Mode Control(GPIO_IMD)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_IEN GPIO Interrupt Enable Register(GPIO_IEN)
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
//! \addtogroup AU9110_GPIO_Register_GPIO_ISRC GPIO Interrupt Source Flag Register(GPIO_ISRC)
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
//! \addtogroup AU9110_GPIO_Register_DBNCECON GPIO De-bounce Cycle Control Register(GPIO_DBNCECON)
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
