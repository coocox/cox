//*****************************************************************************
//
//! \file xhw_acmp.h
//! \brief Macros used when accessing the comparator hardware.
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

#ifndef __XHW_ACMP_H__
#define __XHW_ACMP_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP_Register NUC1xx Analog Comparator Register
//! \brief Here are the detailed info of ACMP registers. 
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
//! \addtogroup NUC1xx_ACMP_Register_Offset ACMP Register Offset(Map)
//! \brief Here is the ACMP register offset, users can get the register address
//! through <b>ACMP_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Comparator0 Control Register
//
#define ACMP_CR0              0x00000000

//
//! Comparator1 Control Register
//
#define ACMP_CR1              0x00000004

//
//! Comparator Status Register
//
#define ACMP_SR               0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP_Register_CR Comparator Control Register(ACMP_CR0/1)
//! \brief Definition for the bit fields in the ACMP_O_CR0 or ACMP_O_CR1 register.
//! @{
//
//*****************************************************************************

//
//! Comparator0 negative input select
//
#define ACMP_CR_CN             0x00000010

//
//! Comparator0 Hysteresis Enable
//
#define ACMP_CR_HYSEN          0x00000004

//
//! Comparator0 Interrupt Enable
//
#define ACMP_CR_CMPIE          0x00000002

//
//! Comparator0 Enable
//
#define ACMP_CR_CMPEN          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP_Register_SR Comparator Status Register(ACMP_SR)
//! \brief Definition for the bit fields in the ACMP_O_SR register.
//! @{
//
//*****************************************************************************

//
//! Comparator1 Output
//
#define ACMP_SR_CO1             0x00000008

//
//! Comparator0 Output
//
#define ACMP_SR_CO0             0x00000004

//
//! Comparator1 Flag
//
#define ACMP_SR_CMPF1           0x00000002

//
//! Comparator0 Flag
//
#define ACMP_SR_CMPF0           0x00000001



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

#endif // __XHW_ACMP_H__

