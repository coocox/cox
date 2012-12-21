//*****************************************************************************
//
//! \file SSD2119.c
//! \brief Driver for Character LCD SSD2119.
//! \version 2.1.1.0
//! \date 10/18/2011
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

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_spi.h"
#include "xspi.h"
#include "hw_ssd2119.h"
#include "ssd2119.h"

#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8) |               \
                                 (((c) & 0x0000fc00) >> 5) |               \
                                 (((c) & 0x000000f8) >> 3))

//*****************************************************************************
//
//! \brief Write data or command to the ssd2119.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - SSD2119_DC_COMMAND - select the IR.
//! - SSD2119_DC_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119Write(unsigned char ucDC, unsigned long ulInstruction, unsigned char ucRegType)
{
    //
    // Check Arguments.
    //
    xASSERT((ucDC == SSD2119_DC_COMMAND) || (ucDC == SSD2119_DC_DATA));
    xASSERT((ucRegType == SSD2119_NORMAL_REG) || (ucRegType == SSD2119_GRAM_REG));
    
#if (defined SSD2119_INTERFACE_LEN_8BIT)
    //
    // DC:Command, CS:Select
    //
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
#ifdef  SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_WRITE);
#endif
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);

    if(ucRegType == SSD2119_NORMAL_REG)
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 8) & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 	
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, ulInstruction & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800 
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
    }
    else
    {
#if (SSD2119_COLOR_MODE == SSD2119_COLOR_MODE_65K)
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 8) & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 	
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, ulInstruction & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800 
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 
#endif
#if (SSD2119_COLOR_MODE == SSD2119_COLOR_MODE_262K)
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 17) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 16) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 12) & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 6) & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, ulInstruction & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
#endif
    }
    
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE);

#elif (defined SSD2119_INTERFACE_LEN_9BIT)
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
#ifdef  SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_WRITE);
#endif
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
    
    if(ucRegType == SSD2119_NORMAL_REG)
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 8) & 0x01);
    }
    else
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 17) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 16) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D9, (ulInstruction >> 9) & 0x01);
    }
#ifdef SSD2119_INTERFACE_CTL_8080
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 
    
    if(ucRegType == SSD2119_NORMAL_REG)
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, ulInstruction & 0x01);
    }
    else
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D9, ulInstruction & 0x01);
    }
#ifdef SSD2119_INTERFACE_CTL_8080
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800 
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
 
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE);
   
#elif (defined SSD2119_INTERFACE_LEN_16BIT)   
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
#ifdef SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_WRITE);
#endif
    if(ucRegType == SSD2119_NORMAL_REG)
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 15) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D8, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D7, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D6, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D5, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D4, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D3, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D2, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D1, ulInstruction & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 
    }
    else
    {
#if (SSD2119_COLOR_MODE == SSD2119_COLOR_MODE_65K)
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 15) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D8, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D7, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D6, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D5, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D4, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D3, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D2, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D1, ulInstruction & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 
#endif
#if (SSD2119_COLOR_MODE == SSD2119_COLOR_MODE_262K)
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 17) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 16) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 12) & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
        xGPIOSPinWrite(SSD2119_PIN_D8, (ulInstruction >> 11) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D7, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D6, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D5, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D4, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D3, (ulInstruction >> 6) & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 5) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, ulInstruction & 0x01);
#ifdef SSD2119_INTERFACE_CTL_8080
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
        xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
        xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif
#endif
    }
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE); 

#elif (defined SSD2119_INTERFACE_LEN_18BIT)  
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
#ifdef SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_WRITE);
#endif
    if(ucRegType == SSD2119_NORMAL_REG)
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 15) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D8, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D7, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D6, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D5, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D4, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D3, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D2, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D1, ulInstruction & 0x01);
    }
    else
    {
        xGPIOSPinWrite(SSD2119_PIN_D17, (ulInstruction >> 17) & 0x01); 
        xGPIOSPinWrite(SSD2119_PIN_D16, (ulInstruction >> 16) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D15, (ulInstruction >> 15) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D14, (ulInstruction >> 14) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D13, (ulInstruction >> 13) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D12, (ulInstruction >> 12) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D11, (ulInstruction >> 11) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D10, (ulInstruction >> 10) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D9, (ulInstruction >> 9) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D8, (ulInstruction >> 8) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D7, (ulInstruction >> 7) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D6, (ulInstruction >> 6) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D5, (ulInstruction >> 5) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D4, (ulInstruction >> 4) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D3, (ulInstruction >> 3) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D2, (ulInstruction >> 2) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D1, (ulInstruction >> 1) & 0x01);
        xGPIOSPinWrite(SSD2119_PIN_D0, ulInstruction & 0x01);
    }
#ifdef SSD2119_INTERFACE_CTL_8080
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);
#endif 
   
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE); 
 
#elif (defined SSD2119_INTERFACE_18RGB)


#elif (defined SSD2119_INTERFACE_3_SPI)
    if(ucDC)
    {
        if(ucRegType == SSD2119_NORMAL_REG)
        {
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ((ulInstruction >> 8) & 0xFF) | 0x100);
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, (ulInstruction & 0xFF) | 0x100);
        }
        else
        {
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ((ulInstruction >> 12) & 0xFC) | 0x100);
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ((ulInstruction >> 6) & 0xFC) | 0x100);
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, (ulInstruction & 0xFC) | 0x100);
        }
    }
    else
    {
        xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ulInstruction & 0xFF);
    }
#elif (defined SSD2119_INTERFACE_4_SPI)
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
    if(ucDC)
    {
        if(ucRegType == SSD2119_NORMAL_REG)
        {
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, (ulInstruction >> 8) & 0xFF);
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ulInstruction & 0xFF);
        }
        else
        {
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, (ulInstruction >> 12) & 0xFC);
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, (ulInstruction >> 6) & 0xFC);
            xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ulInstruction & 0xFC);
        }
    }    
    xSPIDataBufferWriteNonBlocking(SSD2119_SPIBase, ulInstruction & 0xFF);
#endif  
}

//*****************************************************************************
//
//! \brief Read the state or data from the SSD2119.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucDC can be:
//! - SSD2119_DC_COMMAND - select the IR.
//! - SSD2119_DC_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
SSD2119Read(unsigned char ucDC)
{
    unsigned long ulData = 0;

    //
    // Set D17 - D0 direction to GPIO Input
    //
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT))       
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D17);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D16);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D15);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D14);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D13);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D12);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D11);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D10);       
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFACE_LEN_18BIT))   
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D17);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D16);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D15);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D14);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D13);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D12);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D11);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D10);        
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D8);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D7);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D6);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D5);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D4);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D3);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D2);
    xGPIOSPinTypeGPIOInput(SSD2119_PIN_D1);   
#endif
    
#ifdef SSD2119_INTERFACE_CTL_6800
    //
    // DC:Command, RD:Write, CS:Enable
    //
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_READ); 
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);    
#endif
#ifdef SSD2119_INTERFACE_CTL_8080
    //
    // DC:Command, RD:Write, CS:Enable
    //
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
    xGPIOSPinWrite(SSD2119_PIN_RD, SSD2119_8080_RD_ENABLE); 
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
#endif
    xSysCtlDelay(200);
    
    //
    // Read the Data
    //
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT))
    ulData |= xGPIOSPinRead(SSD2119_PIN_D17) << 7;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D16) << 6;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D15) << 5;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D14) << 4;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D13) << 3;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D12) << 2;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D11) << 1;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D10) << 0;
#ifdef SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_ENABLE);  
    xSysCtlDelay(100); 
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);   
#endif
#ifdef SSD2119_INTERFACE_CTL_8080
    xGPIOSPinWrite(SSD2119_PIN_RD, SSD2119_8080_RD_DISABLE);
    xSysCtlDelay(100);
    xGPIOSPinWrite(SSD2119_PIN_RD, SSD2119_8080_RD_ENABLE);
#endif
    
    xSysCtlDelay(200);
    ulData |= xGPIOSPinRead(SSD2119_PIN_D17) << 15;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D16) << 14;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D15) << 13;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D14) << 12;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D13) << 11;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D12) << 10;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D11) << 9;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D10) << 8;
    
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE);
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFACE_LEN_18BIT))
    ulData |= xGPIOSPinRead(SSD2119_PIN_D17) << 15;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D16) << 14;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D15) << 13;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D14) << 12;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D13) << 11;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D12) << 10;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D11) << 9;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D10) << 8;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D8) << 7;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D7) << 6;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D6) << 5;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D5) << 4;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D4) << 3;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D3) << 2;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D2) << 1;
    ulData |= xGPIOSPinRead(SSD2119_PIN_D1) << 0;
    
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE);
#elif (defined SSD2119_INTERFACE_18RGB)

#elif (defined SSD2119_INTERFACE_3_SPI)
    xSPIDataBufferReadNonBlocking(SSD2119_SPIBase, &ulData);
#elif (defined SSD2119_INTERFACE_4_SPI)
    //
    // DC  0 : Command, 1 : Data
    //
    xGPIOSPinWrite(SSD2119_PIN_DC, ucDC);
    xSPIDataBufferReadNonBlocking(SSD2119_SPIBase, &ulData);
#endif    

    //
    // At the End, set D17 - D0 direction to GPIO OutPut
    //
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT))     
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D17);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D16);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D15);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D14);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D13);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D12);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D11);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D10);
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFACE_LEN_18BIT))      
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D17);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D16);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D15);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D14);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D13);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D12);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D11);  
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D10);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D8);       
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D7);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D6);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D5);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D4);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D3);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D2);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D1);   
#endif    
    
    return ulData;
}

void 
SSD2119WriteCmd(unsigned char ucCmd)
{
    SSD2119Write(SSD2119_DC_COMMAND, ucCmd, SSD2119_NORMAL_REG);
}

void 
SSD2119WriteData(unsigned long ulData)
{
    SSD2119Write(SSD2119_DC_DATA, ulData, SSD2119_NORMAL_REG);
}

//*****************************************************************************
//
//! \brief Write data to the SSD2119 GRAM.
//!
//! \param None.
//!
//! \return data that have been read.
//
//*****************************************************************************
void 
SSD2119WritePixelData(unsigned long ulData)
{
    SSD2119Write(SSD2119_DC_DATA, ulData, SSD2119_GRAM_REG);
}

//*****************************************************************************
//
//! \brief Set the cursor location.
//!
//! \param ulStartX is the character index.
//! \param ulEndX is the line number.
//!
//! The default location is (0,0). After set the location, the strings will
//! display at the (ulCol, ulRow).
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119SetCurPos(unsigned long ulStartX, unsigned long ulEndX, 
                  unsigned long ulStartY, unsigned long ulEndY)
{
    //
    // Check Arguments.
    //
    xASSERT((ulEndX < 320) || (ulEndY < 240));

    //
    // Write the Y extents of the rectangle.
    //
    SSD2119WriteCmd(SSD2119_ENTRY_MODE_REG);
    SSD2119WriteData(SSD2119_ENTRY_MODE_SET(HORIZ_DIRECTION));

    //
    // Write the X extents of the rectangle.
    //
    SSD2119WriteCmd(SSD2119_H_RAM_START_REG);
#if (defined PORTRAIT) || (defined LANDSCAPE)
    SSD2119WriteData(MAPPED_X(ulEndX, ulEndY));
#else
    SSD2119WriteData(MAPPED_X(ulStartX, ulStartY));
#endif
    
    SSD2119WriteCmd(SSD2119_H_RAM_END_REG);
#if (defined PORTRAIT) || (defined LANDSCAPE)
    SSD2119WriteData(MAPPED_X(ulStartX, ulStartY));
#else
    SSD2119WriteData(MAPPED_X(ulEndX, ulEndY));
#endif
    
    //
    // Write the Y extents of the rectangle
    //
    SSD2119WriteCmd(SSD2119_V_RAM_POS_REG);
#if (defined LANDSCAPE_FLIP) || (defined PORTRAIT)
    SSD2119WriteData(MAPPED_Y(ulStartX, ulStartY) | (MAPPED_Y(ulEndX, ulEndY) << 8));
#else
    SSD2119WriteData(MAPPED_Y(ulEndX, ulEndY) | (MAPPED_Y(ulStartX, ulStartY) << 8));
#endif   
    //
    // Set the display cursor to the upper left of the rectangle (in application
    // coordinate space).
    //
    SSD2119WriteCmd(SSD2119_X_RAM_ADDR_REG);
    SSD2119WriteData(MAPPED_X(ulStartX, ulStartY));

    SSD2119WriteCmd(SSD2119_Y_RAM_ADDR_REG);
    SSD2119WriteData(MAPPED_Y(ulStartX, ulStartY));

    //
    // Tell the controller we are about to write data into its RAM.
    //
    SSD2119WriteCmd(SSD2119_RAM_DATA_REG);
}

//*****************************************************************************
//
//! \brief Init the SSD2119 LCD Device.
//!
//! \param None.
//!
//! This function is used to Init the SSD2119 Device. It must be call before 
//! any other LCD function use.
//!
//! It Open the pins's GPIO peripheral port, and config the pins type to GPIO 
//! output. Then config the LCD into the default state, clear the LCD and 
//! Open the display. Default A Blink cursor is set on. The LCD cursor move 
//! direction is config as increment default.
//!
//! The SSD2119 Initial state can be determined by the \ref SSD2119_Config.
//! - Pins that used is determined by \ref SSD2119_Config_Pins.
//! - The inteface data length is determined by \ref SSD2119_INTERFACE_IDATA_LEN.
//! - The LCD display line is determined by \ref SSD2119_DISPLAY_LINE.
//! - The LCD character font is determined by \ref SSD2119_CHARACTER_FONT.
//! .
//! 
//! \return None.
//
//*****************************************************************************
void 
SSD2119Init(void)
{
    unsigned long ulCount;
    
    //
    // Enable GPIO Port that used
    //
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT))    
#ifdef SSD2119_INTERFACE_CTL_6800
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_E));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_RW));
#endif
#ifdef SSD2119_INTERFACE_CTL_8080
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_RD));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_WR));
#endif
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_DC));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D17));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D16));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D15));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D14));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D13));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D12));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D11));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D10)); 
#ifdef SSD2119_INTERFACE_LEN_9BIT
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D9)); 
#endif
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFACE_LEN_18BIT))  
#ifdef SSD2119_INTERFACE_CTL_8080
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_RD));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_WR)); 
#endif
#ifdef SSD2119_INTERFACE_CTL_6800    
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_E));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_RW));
#endif
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_CS)); 
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_DC));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D17));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D16));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D15));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D14));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D13));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D12));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D11));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D10));  
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D8));    
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D7));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D6));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D5));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D4));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D3));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D2));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D1)); 
#ifdef SSD2119_INTERFACE_LEN_18BIT
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D9));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_D0)); 
#endif
#elif (defined SSD2119_INTERFACE_18RGB)

#elif (defined SSD2119_INTERFACE_3_SPI)
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_SPICLK));
    xSysCtlPeripheralEnable2(SSD2119_SPIBase);

#elif (defined SSD2119_INTERFACE_4_SPI)
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_DC));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_SPICLK));
    xSysCtlPeripheralEnable2(SSD2119_SPIBase);   
#endif    
    
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_RST));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(SSD2119_PIN_BACKLIGHT)); 
    //
    // Set Pins Type to GPIO Output
    //
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT))   
#ifdef SSD2119_INTERFACE_CTL_8080
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_RD);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_WR);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_E);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_RW);
#endif
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_CS);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_DC);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D17);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D16);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D15);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D14);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D13);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D12);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D11);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D10);
#ifdef SSD2119_INTERFACE_LEN_9BIT
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D9);
#endif
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFAC_LEN_18BIT))
#ifdef SSD2119_INTERFACE_CTL_8080 
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_RD);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_WR);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800   
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_E);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_RW);
#endif   
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_CS);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_DC);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D17);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D16);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D15);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D14);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D13);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D12);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D11);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D10); 
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D8);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D7);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D6);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D5);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D4);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D3);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D2);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D1); 
#ifdef SSD2119_INTERFACE_LEN_18BIT
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D9);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_D0);
#endif 
#elif (defined SSD2119_INTERFACE_18RGB)

#elif (defined SSD2119_INTERFACE_3_SPI)
#if (SSD2119_SPIBase == xSPI0_BASE)
    xSPinTypeSPI(SPI0CLK, SSD2119_SPICLK);
    xSPinTypeSPI(SPI0CS, SSD2119_SPICS);
    xSPinTypeSPI(SPI0RX, SSD2119_SPIRX);
    xSPinTypeSPI(SPI0TX, SSD2119_SPITX);
#endif
#if (SSD2119_SPIBase == xSPI1_BASE)
    xSPinTypeSPI(SPI1CLK, SSD2119_SPICLK);
    xSPinTypeSPI(SPI1CS, SSD2119_SPICS);
    xSPinTypeSPI(SPI1RX, SSD2119_SPIRX);
    xSPinTypeSPI(SPI1TX, SSD2119_SPITX);
#endif
    ulCount = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_MASTER | xSPI_DATA_WIDTH9);
    xSPIConfigSet(SSD2119_SPIBase, 200000, ulCount);
#elif (defined SSD2119_INTERFACE_4_SPI)
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_DC);
#if (SSD2119_SPIBase == xSPI0_BASE)
    xSPinTypeSPI(SPI0CLK, SSD2119_SPICLK);
    xSPinTypeSPI(SPI0CS, SSD2119_SPICS);
    xSPinTypeSPI(SPI0RX, SSD2119_SPIRX);
    xSPinTypeSPI(SPI0TX, SSD2119_SPITX);
#endif
#if (SSD2119_SPIBase == xSPI1_BASE)
    xSPinTypeSPI(SPI1CLK, SSD2119_SPICLK);
    xSPinTypeSPI(SPI1CS, SSD2119_SPICS);
    xSPinTypeSPI(SPI1RX, SSD2119_SPIRX);
    xSPinTypeSPI(SPI1TX, SSD2119_SPITX);
#endif 
    ulCount = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_MASTER | xSPI_DATA_WIDTH8);
    xSPIConfigSet(SSD2119_SPIBase, 200000, ulCount);
#endif      
    
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_RST);
    xGPIOSPinTypeGPIOOutput(SSD2119_PIN_BACKLIGHT);   
    //
    // Turn on the backlight.
    //
    xGPIOSPinWrite(SSD2119_PIN_BACKLIGHT, SSD2119_BACKLIGHT_ON);
    
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT))        
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_DC, SSD2119_DC_COMMAND);
#ifdef SSD2119_INTERFACE_CTL_8080 
    xGPIOSPinWrite(SSD2119_PIN_RD, SSD2119_8080_RD_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_WRITE);
#endif
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFACE_LEN_18BIT))        
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_CS, SSD2119_CS_ENABLE);
    xGPIOSPinWrite(SSD2119_PIN_DC, SSD2119_DC_COMMAND);
#ifdef SSD2119_INTERFACE_CTL_8080
    xGPIOSPinWrite(SSD2119_PIN_RD, SSD2119_8080_RD_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_WR, SSD2119_8080_WR_DISABLE);
#endif
#ifdef SSD2119_INTERFACE_CTL_6800
    xGPIOSPinWrite(SSD2119_PIN_E, SSD2119_6800_E_DISABLE);
    xGPIOSPinWrite(SSD2119_PIN_RW, SSD2119_6800_RW_WRITE);
#endif
#elif (defined SSD2119_INTERFACE_18RGB)

#elif (defined SSD2119_INTERFACE_3_SPI)
    xSPIEnable(SSD2119_SPIBase);
#elif (defined SSD2119_INTERFACE_4_SPI)
    xGPIOSPinWrite(SSD2119_PIN_DC, SSD2119_DC_COMMAND);
    xSPIEnable(SSD2119_SPIBase);
#endif

    xGPIOSPinWrite(SSD2119_PIN_RST, SSD2119_RST_ENABLE);
    xSysCtlDelay(10000);
    xGPIOSPinWrite(SSD2119_PIN_RST, SSD2119_RST_DISABLE);
    xSysCtlDelay(10000);
    
    //
    // Enter sleep mode (if we are not already there).
    //
    SSD2119WriteCmd(SSD2119_SLEEP_MODE_1_REG);
    SSD2119WriteData(SSD2119_SLEEP_MODE_ENTER);
    
    //
    // Set initial power parameters.
    //
    SSD2119WriteCmd(SSD2119_PWR_CTRL_5_REG);
    SSD2119WriteData(SSD2119_VCOMH_SET(SSD2119_VLCD_TIMES_0_86));
    SSD2119WriteCmd(SSD2119_VCOM_OTP_1_REG);
    SSD2119WriteData(0x0006);
    
    //
    // Start the oscillator.
    //
    SSD2119WriteCmd(SSD2119_OSC_START_REG);
    SSD2119WriteData(0x0001);
    
    //
    // Set pixel format and basic display orientation (scanning direction).
    //
    SSD2119WriteCmd(SSD2119_OUTPUT_CTRL_REG);
    SSD2119WriteData(SSD2119_OUTPUTCTL_SET(SSD2119_OUTPUT_ORIGIN_DOWNRIGHT));
    SSD2119WriteCmd(SSD2119_LCD_DRIVE_AC_CTRL_REG);
    SSD2119WriteData(0x0600);
    
    //
    // Exit sleep mode.
    //
    SSD2119WriteCmd(SSD2119_SLEEP_MODE_1_REG);
    SSD2119WriteData(SSD2119_SLEEP_MODE_EXIT);
    
    //
    // Delay 30mS
    //
    xSysCtlDelay(100);
    
    //
    // Configure pixel color format and MCU interface parameters.
    //
    SSD2119WriteCmd(SSD2119_ENTRY_MODE_REG);
#if (SSD2119_COLOR_MODE == SSD2119_COLOR_MODE_65K)
    SSD2119WriteData(SSD2119_ENTRY_MODE_DEFAULT);
#endif
#if (SSD2119_COLOR_MODE == SSD2119_COLOR_MODE_262K)
    SSD2119WriteData(0x48B0);
#endif
    
    //
    // Enable the display.
    //
    SSD2119WriteCmd(SSD2119_DISPLAY_CTRL_REG);
    SSD2119WriteData(0x0033);
    
    //
    // Set VCIX2 voltage to 6.1V.
    //
    SSD2119WriteCmd(SSD2119_PWR_CTRL_2_REG);
    SSD2119WriteData(SSD2119_OUTPUT_VOLTAGE_SET(SSD2119_OUTPUT_VOLTAGE_6_1V));
    
    //
    // Configure gamma correction.
    //
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_1_REG);
    SSD2119WriteData(0x0000);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_2_REG);
    SSD2119WriteData(0x0303);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_3_REG);
    SSD2119WriteData(0x0407);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_4_REG);
    SSD2119WriteData(0x0301);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_5_REG);
    SSD2119WriteData(0x0301);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_6_REG);
    SSD2119WriteData(0x0403);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_7_REG);
    SSD2119WriteData(0x0707);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_8_REG);
    SSD2119WriteData(0x0400);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_9_REG);
    SSD2119WriteData(0x0a00);
    SSD2119WriteCmd(SSD2119_GAMMA_CTRL_10_REG);
    SSD2119WriteData(0x1000);
    
    //
    // Configure Vlcd63 and VCOMl.
    //
    SSD2119WriteCmd(SSD2119_PWR_CTRL_3_REG);
    SSD2119WriteData(SSD2119_VLCD63_SET(SSD2119_VREF_TIMES_2_335));
    SSD2119WriteCmd(SSD2119_PWR_CTRL_4_REG);
    SSD2119WriteData(SSD2119_VCOM_SET(SSD2119_VLCD63_TIMES_1_02));
    
    //
    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    //
    SSD2119WriteCmd(SSD2119_V_RAM_POS_REG);
    SSD2119WriteData((LCD_VERTICAL_MAX-1) << 8);
    SSD2119WriteCmd(SSD2119_H_RAM_START_REG);
    SSD2119WriteData(0x0000);
    SSD2119WriteCmd(SSD2119_H_RAM_END_REG);
    SSD2119WriteData(LCD_HORIZONTAL_MAX-1);
    SSD2119WriteCmd(SSD2119_X_RAM_ADDR_REG);
    SSD2119WriteData(0x00);
    SSD2119WriteCmd(SSD2119_Y_RAM_ADDR_REG);
    SSD2119WriteData(0x00);
    
    SSD2119WriteCmd(SSD2119_RAM_DATA_REG);
    
    //
    // Clear the contents of the display buffer.
    //
    for(ulCount = 0; ulCount < (LCD_HORIZONTAL_MAX * LCD_VERTICAL_MAX); ulCount++)
    {
        SSD2119WritePixelData(0xFFFF);
    } 
}

//*****************************************************************************
//
//! \brief Enter the the LCD sleep mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119EnterSleepMode(void)
{
    //
    // Sleep set
    //
    SSD2119WriteCmd(SSD2119_SLEEP_MODE_1_REG);		
    SSD2119WriteData(0x0001);
    //
    // Display Control
    //
    SSD2119WriteCmd(SSD2119_DISPLAY_CTRL_REG);		
    SSD2119WriteData(0x0000);
}

//*****************************************************************************
//
//! \brief Exit the the LCD sleep mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119ExitSleepMode(void)
{
    SSD2119WriteCmd(SSD2119_SLEEP_MODE_1_REG);		
    SSD2119WriteData(0x0000);
    SSD2119WriteCmd(SSD2119_DISPLAY_CTRL_REG);		
    SSD2119WriteData(0x0033);
}

//*****************************************************************************
//
//! \brief Fills a rectangle (direct LCD access mode).
//!
//! \param ulStartX is the starting address of X.
//! \param ulStartY is the starting address of Y.
//! \param ulEndX is the ending address of X.
//! \param ulEndY is the ending address of Y.
//! \param ulColor is the color.
//!
//! This function fills a rectangle on the display.  The coordinates of the
//! rectangle are assumed to be within the extents of the display, and the
//! rectangle specification is fully inclusive (in other words, both ulStartX and
//! ulEndX are drawn, along with ulStartY and ulEndY).
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119DisplayRectFill(unsigned short usStartX, unsigned short usEndX, 
                        unsigned short usStartY, unsigned short usEndY, unsigned long ulColor)
{
    unsigned short usTemp;
	
    //
    // Check Arguments.
    //
    xASSERT((usStartX <= ulEndX)                &&
            (usStartY <= ulEndY)                &&
            ((usStartX >= 0) || (usEndX < 320)) &&
            ((usStartY >= 0) || (usEndY < 240)));            
	
    //
    // Clear LCD
    //
    SSD2119SetCurPos(usStartX, usEndX, usStartY, usEndY); 
    
    for(usTemp = 0; usTemp <= (usEndX - usStartX + 1) * (usEndY - usStartY + 1); usTemp++)
    {
        SSD2119WriteData(ulColor);
    }
}

//*****************************************************************************
//
//! \brief Clears all the LCD display with the specified colour.
//!
//! \param ulColor is the specified colour.
//!
//! It clears all the LCD display with the specified colour.
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119DisplayClear(unsigned long ulColor)
{
    SSD2119DisplayRectFill(0, 319, 0, 239, ulColor);
}

//*****************************************************************************
//
//! \brief Turn on the entire LCD backlight display.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119BackLightOn(void)
{
    xGPIOSPinWrite(SSD2119_PIN_BACKLIGHT, SSD2119_BACKLIGHT_ON);   
}

//*****************************************************************************
//
//! \brief Turn off the entire LCD backlight display.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119DisplayOff(void)
{
    xGPIOSPinWrite(SSD2119_PIN_BACKLIGHT, SSD2119_BACKLIGHT_OFF);    
}

//*****************************************************************************
//
//! \brief Draws a pixel on the screen.
//!
//! \param ulX is the X coordinate of the pixel.
//! \param ulY is the Y coordinate of the pixel.
//! \param ulValue is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119DrawOnePixel(unsigned short usX, unsigned short usY, unsigned long ulColor)                                 
{
    //
    // Set the X address of the display cursor.
    //
    SSD2119WriteCmd(SSD2119_X_RAM_ADDR_REG);
    SSD2119WriteData(MAPPED_X(usX, usY));

    //
    // Set the Y address of the display cursor.
    //
    SSD2119WriteCmd(SSD2119_Y_RAM_ADDR_REG);
    SSD2119WriteData(MAPPED_Y(usX, usY));

    //
    // Write the pixel value.
    //
    SSD2119WriteCmd(SSD2119_RAM_DATA_REG);
    SSD2119WritePixelData(ulColor);
}

//*****************************************************************************
//
//! \brief Draws a horizontal sequence of pixels on the screen.
//!
//! \param lX is the X coordinate of the first pixel.
//! \param lY is the Y coordinate of the first pixel.
//! \param lX0 is sub-pixel offset within the pixel data, which is valid for 1
//! or 4 bit per pixel formats.
//! \param lCount is the number of pixels to draw.
//! \param lBPP is the number of bits per pixel; must be 1, 4, or 8.
//! \param pucData is a pointer to the pixel data.  For 1 and 4 bit per pixel
//! formats, the most significant bit(s) represent the left-most pixel.
//! \param pucPalette is a pointer to the palette used to draw the pixels.
//!
//! This function draws a horizontal sequence of pixels on the screen, using
//! the supplied palette.  For 1 bit per pixel format, the palette contains
//! pre-translated colors; for 4 and 8 bit per pixel formats, the palette
//! contains 24-bit RGB values that must be translated before being written to
//! the display.
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119PixelDrawMultiple(unsigned long lX, unsigned long lY, 
                         unsigned long lX0, unsigned long lCount,
                         unsigned long lBPP,
                         const unsigned char *pucData,
                         const unsigned char *pucPalette)
{
    unsigned long ulByte;

    //
    // Set the cursor increment to left to right, followed by top to bottom.
    //
    SSD2119WriteCmd(SSD2119_ENTRY_MODE_REG);
    SSD2119WriteData(SSD2119_ENTRY_MODE_SET(HORIZ_DIRECTION));

    //
    // Set the starting X address of the display cursor.
    //
    SSD2119WriteCmd(SSD2119_X_RAM_ADDR_REG);
    SSD2119WriteData(MAPPED_X(lX, lY));

    //
    // Set the Y address of the display cursor.
    //
    SSD2119WriteCmd(SSD2119_Y_RAM_ADDR_REG);
    SSD2119WriteData(MAPPED_Y(lX, lY));

    //
    // Write the data RAM write command.
    //
    SSD2119WriteCmd(SSD2119_RAM_DATA_REG);

    //
    // Determine how to interpret the pixel data based on the number of bits
    // per pixel.
    //
    switch(lBPP)
    {
        //
        // The pixel data is in 1 bit per pixel format.
        //
        case 1:
        {
            //
            // Loop while there are more pixels to draw.
            //
            while(lCount)
            {
                //
                // Get the next byte of image data.
                //
                ulByte = *pucData++;

                //
                // Loop through the pixels in this byte of image data.
                //
                for(; (lX0 < 8) && lCount; lX0++, lCount--)
                {
                    //
                    // Draw this pixel in the appropriate color.
                    //
                    SSD2119WriteData(((unsigned long *)pucPalette)[(ulByte >>
                                                             (7 - lX0)) & 1]);
                }

                //
                // Start at the beginning of the next byte of image data.
                //
                lX0 = 0;
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // The pixel data is in 4 bit per pixel format.
        //
        case 4:
        {
            //
            // Loop while there are more pixels to draw.  "Duff's device" is
            // used to jump into the middle of the loop if the first nibble of
            // the pixel data should not be used.  Duff's device makes use of
            // the fact that a case statement is legal anywhere within a
            // sub-block of a switch statement.  See
            // http://en.wikipedia.org/wiki/Duff's_device for detailed
            // information about Duff's device.
            //
            switch(lX0 & 1)
            {
                case 0:
                    while(lCount)
                    {
                        //
                        // Get the upper nibble of the next byte of pixel data
                        // and extract the corresponding entry from the
                        // palette.
                        //
                        ulByte = (*pucData >> 4) * 3;
                        ulByte = (*(unsigned long *)(pucPalette + ulByte) &
                                  0x00ffffff);

                        //
                        // Translate this palette entry and write it to the
                        // screen.
                        //
                        SSD2119WriteData(DPYCOLORTRANSLATE(ulByte));

                        //
                        // Decrement the count of pixels to draw.
                        //
                        lCount--;

                        //
                        // See if there is another pixel to draw.
                        //
                        if(lCount)
                        {
                case 1:
                            //
                            // Get the lower nibble of the next byte of pixel
                            // data and extract the corresponding entry from
                            // the palette.
                            //
                            ulByte = (*pucData++ & 15) * 3;
                            ulByte = (*(unsigned long *)(pucPalette + ulByte) &
                                      0x00ffffff);

                            //
                            // Translate this palette entry and write it to the
                            // screen.
                            //
                            SSD2119WriteData(DPYCOLORTRANSLATE(ulByte));

                            //
                            // Decrement the count of pixels to draw.
                            //
                            lCount--;
                        }
                    }
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // The pixel data is in 8 bit per pixel format.
        //
        case 8:
        {
            //
            // Loop while there are more pixels to draw.
            //
            while(lCount--)
            {
                //
                // Get the next byte of pixel data and extract the
                // corresponding entry from the palette.
                //
                ulByte = *pucData++ * 3;
                ulByte = *(unsigned long *)(pucPalette + ulByte) & 0x00ffffff;

                //
                // Translate this palette entry and write it to the screen.
                //
                SSD2119WriteData(DPYCOLORTRANSLATE(ulByte));
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // We are being passed data in the display's native format.  Merely
        // write it directly to the display.  This is a special case which is
        // not used by the graphics library but which is helpful to
        // applications which may want to handle, for example, JPEG images.
        //
        case 16:
        {
            unsigned short usByte;

            //
            // Loop while there are more pixels to draw.
            //
            while(lCount--)
            {
                //
                // Get the next byte of pixel data and extract the
                // corresponding entry from the palette.
                //
                usByte = *((unsigned short *)pucData);
                pucData += 2;

                //
                // Translate this palette entry and write it to the screen.
                //
                SSD2119WriteData(usByte);
            }
        }
    }
}

//*****************************************************************************
//
//! \brief Draws a horizontal line.
//!
//! \param usStartX is the X coordinate of the start of the line.
//! \param usEndX is the X coordinate of the end of the line.
//! \param usY is the Y coordinate of the line.
//! \param usColor is the color of the line.
//!
//! This function draws a horizontal line on the display.  The coordinates of
//! the line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119DrawHorizontalLine(unsigned short usStartX, unsigned short usEndX,
                          unsigned short usY, unsigned long ulColor)
{
    xASSERT((usStartX <= usEndX) && (usEndX <= LCD_HORIZONTAL_MAX) && (usStartX >= 0));
    
    while(usStartX++ <= usEndX)
    {
        SSD2119DrawOnePixel(usStartX, usY, ulColor);
    }
}

//*****************************************************************************
//
//! \brief Draws a vertical line.
//!
//! \param ulX is the X coordinate of the line.
//! \param ulStartY is the Y coordinate of the start of the line.
//! \param ulEndY is the Y coordinate of the end of the line.
//! \param ulColor is the color of the line.
//!
//! This function draws a vertical line on the display.  The coordinates of the
//! line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void
SSD2119DrawVerticalLine(unsigned short usX, unsigned short usStartY,
                        unsigned short usEndY, unsigned long ulColor)
{
    xASSERT((usStartY <= usEndY) && (usEndY <= LCD_VERTICAL_MAX) && (usStartY >= 0));
    
    while(usStartY++ <= usEndY)
    {
        SSD2119DrawOnePixel(usX, usStartY, ulColor);
    }
}

//*****************************************************************************
//
//! \brief Display a char on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a string on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#ifdef SSD2119_CHARACTER_FONT_8X16
#include "8X16.h"
void SSD2119PutChar8x16(unsigned short usX, unsigned short usY, char c, 
                         unsigned long fColor, unsigned long bColor)
{
    unsigned int i, j;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    SSD2119SetCurPos(usX, usX + 8 - 1, usY, usY + 16 - 1);
    for(i = 0; i < 16; i++) 
    {
        unsigned char m = Font8x16[(c - 0x20) * 16 + i];
	for(j = 0; j < 8; j++) 
        {
            if((m & 0x80) == 0x80) 
            {
                SSD2119WritePixelData(fColor);
            }
            else 
            {
                SSD2119WritePixelData(bColor);
            }
            m <<= 1;
        }
    }
}
#endif

//*****************************************************************************
//
//! \brief Display a 16*16 chinese on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a chinese on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#ifdef SSD2119_CHINESE_FONT_16X16
#include "GB1616.h"
void SSD2119PutGB1616(unsigned short usX, unsigned short usY, unsigned char ucChinese[2], 
                       unsigned long fColor,unsigned long bColor)
{
    unsigned char i,j,k;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    SSD2119SetCurPos(usX,  usX + 16 - 1, usY, usY + 16 - 1);

    for (k = 0; k < 64; k++) 
    { 
        if ((codeGB_16[k].Index[0] == ucChinese[0])&&(codeGB_16[k].Index[1] == ucChinese[1]))
        { 
            for(i = 0; i < 32; i++) 
            {
                unsigned short m = codeGB_16[k].Msk[i];
                for(j = 0; j < 8; j++) 
                {
                    if((m & 0x80) == 0x80) 
                    {
                        SSD2119WritePixelData(fColor);
                    }
                    else 
                    {
                        SSD2119WritePixelData(bColor);
                    }
                    m <<= 1;
                } 
            }
        }  
    }	
}
#endif

//*****************************************************************************
//
//! \brief Display a 32*32 chinese on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a chinese on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#ifdef SSD2119_CHINESE_FONT_32X32
#include "GB3232.h"	
void SSD2119PutGB3232(unsigned short usX, unsigned short  usY, unsigned char ucChinese[2], 
                       unsigned long fColor,unsigned long bColor)
{
    unsigned char i, j, k;

    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    SSD2119SetCurPos(usX,  usX + 32 - 1, usY, usY + 32 - 1);

    for (k = 0; k < 5; k++) 
    { 
        if ((codeGB_32[k].Index[0] == ucChinese[0])&&(codeGB_32[k].Index[1] == ucChinese[1]))
        { 
            for(i = 0; i < 128; i++) 
            {
                unsigned short m = codeGB_32[k].Msk[i];
                for(j = 0; j < 8; j++) 
                {
                    if((m & 0x80) == 0x80) 
                    {
                        SSD2119WriteData(fColor);
                    }
                    else 
                    {
                        SSD2119WriteData(bColor);
                    }
                    m <<= 1;
                } 
            }
        }  
    }	
}
#endif

//*****************************************************************************
//
//! \brief Display a string on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a string on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#if ((defined SSD2119_CHARACTER_FONT_8X16)||(defined SSD2119_CHINESE_FONT_16X16))
void 
SSD2119DisplayString(unsigned short usX, unsigned short usY, const char* pcString,
                     unsigned long fColor, unsigned long bColor)
{
    unsigned char ucl = 0;
    
    xASSERT(pcString != 0);
    
    while(*pcString) 
    {
        if( *pcString < 0x80) 
        {
            SSD2119PutChar8x16(usX + ucl * 8, usY, *pcString, fColor, bColor);
            pcString++; ucl++;
        }
        else
        {
            SSD2119PutGB1616(usX + ucl * 8, usY, (unsigned char*)pcString, fColor, bColor);
            pcString += 2; ucl += 2;
        }
    }
}
#endif

//*****************************************************************************
//
//! \brief Display a decimal number on the LCD.
//!
//! \param n is the number that to display.
//!
//! Display a decimal number on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119DisplayNum(unsigned short usX, unsigned short usY, unsigned long ulNum,
                   unsigned long fColor, unsigned long bColor)
{
    unsigned char ucFigures = 0;
    unsigned long ulTemp = ulNum;  
    
    if(ulNum)
    {
        while (ulTemp)
        {
            ulTemp /= 10;
            ucFigures++;
        }
    
        while (ulNum)
        {
            SSD2119PutChar8x16(usX + (ucFigures--) * 8 - 8, usY, ulNum%10 + '0', fColor, bColor);
            ulNum /= 10;
        }
    }
    else
    {
        SSD2119PutChar8x16(usX, usY, '0', fColor, bColor);
    }
}

//*****************************************************************************
//
//! \brief Display a bmp picture on the LCD.
//!
//! \param n is the number that to display.
//!
//! Display a decimal number on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
void 
SSD2119DisplayBmp(unsigned short usX, unsigned short usY, unsigned short usSizeX, 
                   unsigned short usSizeY, unsigned char const *Bmp)
{
    unsigned short i,j;
    unsigned long ulBmpData;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    SSD2119SetCurPos(usX, usX + usSizeX, usY, usY + usSizeY);  
    for( i = usY; i <= usY + usSizeY; i++ ) 
    {
        for( j = usX ; j <= usX + usSizeX; j++)
        {
            ulBmpData = *Bmp++;
            ulBmpData |= (*Bmp++) << 8;
            SSD2119WriteData(ulBmpData);  
        }
    }
}
