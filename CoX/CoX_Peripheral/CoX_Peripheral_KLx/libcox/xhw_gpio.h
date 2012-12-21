//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.2.1.0
//! \date 7/31/2012
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
//! \addtogroup KLx_GPIO_Register KLx GPIO Register
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
//! \addtogroup KLx_GPIO_Register_Offsets GPIO Register Offset(Map)
//! \brief Here is the GPIO register offset, users can get the register address
//! through <b>GPIO_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Port Data Output Register
//
#define GPIO_PDOR               0x00000000  

//
//! Port Set Output Register 
//
#define GPIO_PSOR               0x00000004  

//
//! Port Clear Output Register
//
#define GPIO_PCOR               0x00000008  

//
//! Port Toggle Output Register 
//
#define GPIO_PTOR               0x0000000C 

//
//! Port Data Input Register
//
#define GPIO_PDIR               0x00000010

//
//! Port Data Direction Register 
//
#define GPIO_PDDR               0x00000014

//
//! Pin Control Register
//
#define PORT_PCR                0x00000000

//
//! Global Pin Control Low Register
//
#define PORT_GPCLR              0x00000080

//
//! Global Pin Control High Register
//
#define PORT_GPCHR              0x00000084

//
//! Interrupt Status Flag Register
//
#define PORT_ISFR               0x000000A0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Register_GPIO_PDOR GPIO_PDOR 
//! \brief Defines for the bit fields in the GPIO_PDOR register.
//! @{
//
//*****************************************************************************

//
//!  Port Data Output Mask
//
#define GPIO_PDOR_PD0_M         0x0000FFFF  

//
//!  Port Data Output Shift
//
#define GPIO_PDOR_PD0_S         0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Register_GPIO_PSOR GPIO_PSOR 
//! \brief Defines for the bit fields in the GPIO_PSOR register.
//! @{
//
//*****************************************************************************

//
//!  Port Set Output Mask
//
#define GPIO_PSOR_PTSO_M        0x0000FFFF

//
//!  Port Set Output Shift
//
#define GPIO_PSOR_PTSO_S        0   


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Register_GPIO_PCOR GPIO_PCOR 
//! \brief Defines for the bit fields in the GPIO_PCOR register.
//! @{
//
//*****************************************************************************

//
//!  Port Clear Output Mask
//
#define GPIO_PCOR_PTCO_M        0x0000FFFF  

//
//!  Port Clear Output Shift
//
#define GPIO_PCOR_PTCO_S        0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Register_GPIO_PTOR GPIO_PTOR 
//! \brief Defines for the bit fields in the GPIO_PTOR register.
//! @{
//
//*****************************************************************************

//
//!  Port Toggle Output mask
//
#define GPIO_PTOR_PTTO_M        0x0000FFFF  

//
//! Port Toggle Output shift
//
#define GPIO_PTOR_PTTO_S        0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Register_GPIO_PDIR GPIO_PDIR 
//! \brief Defines for the bit fields in the GPIO_PDIR register.
//! @{
//
//*****************************************************************************

//
//!  Port Data Input mask
//
#define GPIO_PDIR_PDI_M         0x0000FFFF  

//
//!  Port Data Input shift
//								
#define GPIO_PDIR_PDI_S         0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Register_GPIO_PDDR GPIO_PDDR 
//! \brief Defines for the bit fields in the GPIO_PDDR register.
//! @{
//
//*****************************************************************************

//
//! Port Data Direction
//
#define GPIO_PDDR_PDD_M         0x0000FFFF  

//
//!  Port Data Direction
//
#define GPIO_PDDR_PDD_S         0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Register_PORT_PCR PORT_PCR 
//! \brief Defines for the bit fields in the PORT_PCR register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Status Flag
//
#define PORT_PCR_ISF            0x01000000  

//
//! Interrupt Configuration mask
//
#define PORT_PCR_IRQC_M         0x00FF0000 

//
//! Interrupt/DMA request disabled
//
#define PORT_PCR_IRQC_DIS       0x00000000

//
//! DMA request on rising edge.
//
#define PORT_PCR_IRQC_DMAR      0x00010000

//
//! DMA request on falling edge.
//
#define PORT_PCR_IRQC_DMAF      0x00020000

//
//! DMA request on either edge.
//
#define PORT_PCR_IRQC_DMAE      0x00030000

//
//! Interrupt when logic zero.
//
#define PORT_PCR_IRQC_LOW       0x00080000

//
//! Interrupt on rising edge.
//
#define PORT_PCR_IRQC_RISING    0x00090000

//
//! Interrupt on falling edge.
//
#define PORT_PCR_IRQC_FALLING   0x000A0000

//
//! Interrupt on either .
//
#define PORT_PCR_IRQC_EBOTH     0x000B0000

//
//! Interrupt when logic one.
//
#define PORT_PCR_IRQC_HIGH      0x000C0000              

//
//! Interrupt Configuration shift
//
#define PORT_PCR_IRQC_S         16

//
//! Pin Mux Control	mask
//
#define PORT_PCR_PIN_MUX_M      0x00000700

//
//! Pin disabled (analog)
//
#define PORT_PCR_PIN_DIS        0x00000000

//
//! Alternative 0 (chip-specific)
//
#define PORT_PCR_PIN_ALT0       0x00000000

//
//! Pin disabled (analog)
//
#define PORT_PCR_PIN_GPIO       0x00000100

//
//! Alternative 2 (chip-specific)
//
#define PORT_PCR_PIN_ALT2       0x00000200

//
//! Alternative 3 (chip-specific)
//
#define PORT_PCR_PIN_ALT3       0x00000300

//
//! Alternative 4 (chip-specific)
//
#define PORT_PCR_PIN_ALT4       0x00000400

//
//! Alternative 5 (chip-specific)
//
#define PORT_PCR_PIN_ALT5       0x00000500

//
//! Alternative 6 (chip-specific)
//
#define PORT_PCR_PIN_ALT6       0x00000600

//
//! Alternative 7 (chip-specific)
//
#define PORT_PCR_PIN_ALT7       0x00000700

//
//! Pin Mux Control	shift
//
#define PORT_PCR_PIN_MUX_S      8

//
//! Drive Strength Enable
//
#define PORT_PCR_DSE_HIGH       0x00000040

//
//! Passive Filter Enable
//
#define PORT_PCR_PFE_ENABLE     0x00000010

//
//! Slew Rate Enable
//
#define PORT_PCR_SRE_ENABLE     0x00000004

//
//! Pull Enable
//
#define PORT_PCR_PE_ENABLE      0x00000002

//
//! Pull Select
//
#define PORT_PCR_PS_ENABLE      0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Register_PORT_GPCLR PORT_GPCLR
//! \brief Defines for the bit fields in the PORT_GPCLR register.
//! @{
//
//*****************************************************************************

//
//! Global Pin Write Enable mask
//
#define PORT_GPCLR_GPWE_M       0xFFFF0000

//
//! Global Pin Write Enable shift
//
#define PORT_GPCLR_GPWE_S       16    

//
//! Global Pin Write Data mask
//
#define PORT_GPCLR_GPWD_M       0x0000FFFF

//
//! Global Pin Write Data shift
//
#define PORT_GPCLR_GPWD_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Register_PORT_GPCLR PORT_GPCHR
//! \brief Defines for the bit fields in the PORT_GPCHR register.
//! @{
//
//*****************************************************************************

//
//! Global Pin Write Enable mask
//
#define PORT_GPCHR_GPWE_M       0xFFFF0000

//
//! Global Pin Write Enable shift
//
#define PORT_GPCHR_GPWE_S       16    

//
//! Global Pin Write Data mask
//
#define PORT_GPCHR_GPWD_M       0x0000FFFF

//
//! Global Pin Write Data shift
//
#define PORT_GPCHR_GPWD_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Register_PORT_ISFR PORT_ISFR
//! \brief Defines for the bit fields in the PORT_ISFR register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Status Flag 
//
#define PORT_ISFR_ISF_M         0xFFFFFFFF

//
//! Interrupt Status Flag
//
#define PORT_ISFR_ISF_S         0

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
