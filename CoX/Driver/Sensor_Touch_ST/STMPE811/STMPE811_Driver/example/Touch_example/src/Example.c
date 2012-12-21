//*****************************************************************************
//
//! \file Example.c
//! \brief the STMPE811 Example.
//! \version 1.0
//! \date 7/13/2012
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
//*****************************************************************************
#include "STMPE811.h"
#include "hw_STMPE811.h"
#include "HX8347-G.h"
#include "hw_HX8347-G.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

extern xtBoolean TouchDetect;
extern unsigned long ulX, ulY, ulZ;
//*****************************************************************************
//
//! \brief The example of STMPE811.
//!
//! \param None
//!
//! \details The example of STMPE811.
//! \return None.
//
//*****************************************************************************
void STMPE811Example(void)
{
    unsigned long ulDeviceID;
    unsigned char pucBuffer[2];
    unsigned long ulPointX, ulPointY;
    
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ);
    
    HX8347Init(18000000);
    HX8347LCDClear(White);
    STMPE811Init();
    //
    // Get STMPE811 device ID.
    //
    STMPE811Read(STMPE811_CHIP_ID,2,pucBuffer);
    ulDeviceID = (unsigned long)((pucBuffer[0] << 8)| pucBuffer[1]);
    
    //
    // Display STMPE811 device ID.
    //
    HX8347LCDClear(White);
    HX8347DisplayString(0, 0, "STMPE811 ID is:");
    HX8347DisplayN(0, 15, ulDeviceID);   
    
    while(1)
    {
        if(TouchDetect == xtrue)
        {
            ulPointX = ulY;
            ulPointY = ulX;
            HX8347ClearLine(1);
            HX8347DisplayString(1, 0, "X:");
            HX8347DisplayN(1, 2, ulPointX);
            HX8347ClearLine(2);
            HX8347DisplayString(2, 0, "Y:");      
            HX8347DisplayN(2, 2, ulPointY);
            TouchDetect = xfalse;
        }
    }
}