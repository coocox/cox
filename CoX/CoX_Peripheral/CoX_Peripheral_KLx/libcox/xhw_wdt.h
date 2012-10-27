//*****************************************************************************
//
//! \file xhw_wdt.h
//! \brief Macros and defines used when accessing the WATCHDOG hardware.
//! \version V2.1.1.1
//! \date 11/14/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox 
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
//****************************************************************************
#ifndef __XHW_WDT_H__
#define __XHW_WDT_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_WDT_Register KLxx WDT Register
//! \brief Here are the detailed info of WDT registers. 
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
//! \addtogroup KLxx_WDT_Register_Address WDT Address Register(WDT_Address)
//! \brief Defines  the address of the WDT_Register_Address register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Control Register (SIM_COPC)
//
#define SIM_COPC                0x40048100


//
//! Watchdog Timer Service Register (SIM_SRVCOP)
//
#define SIM_SRVCOP              0x40048104

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLxx_WDT_Register_SIM_COPC WDT SIM_COPC Register(SIM_COPC)
//! \brief Defines for the bit fields in the WDT_Register_Address register
//! @{
//
//*****************************************************************************

//
//! Watchdog timeout
//
#define SIM_COPC_COPT_MASK      0x0000000C

//
//! Watchdog clock select
//
#define SIM_COPC_COPCLKS        0x00000002

//
//! Watchdog windowed mode
//
#define SIM_COPC_COPW           0x00000001


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

#endif // __XHW_WADT_H__

