//*****************************************************************************
//
//! \file Example.c
//! \brief the SSD1298 Example.
//! \version 1.0
//! \date 12/21/2012
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
//*****************************************************************************
#include "SSD1298.h"
#include "colors.h"
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"

//*****************************************************************************
//
//! \brief The example of the function of Dispaly.
//!
//! \param None
//!
//! \details The example of the function of Dispaly.
//! \return None.
//
//*****************************************************************************
void SSD1298DispalyExample(void)
{
    //
    // Set SysClk 72MHz using Extern 8M oscillator
    //
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    LCD_Init();
    LCD_Clear(COLOR_WHITE);
    g_usPointColor = COLOR_GREEN;
    LCD_Fill(150, 250, 230, 300, COLOR_BLUE);
    LCD_DrawLine(0, 60, 200, 60);
    LCD_DrawLine(0, 300, 230, 100);
    LCD_DrawCircle(150, 150, 30);
    LCD_DrawCircle(150, 150, 40);
    LCD_DrawCircle(150, 150, 50);
    LCD_DrawCircle(150, 150, 60);
    LCD_DrawCircle(150, 150, 70);
    g_usPointColor = COLOR_RED;
    LCD_ShowString(10, 0, "SSD1298 Display Example\n\r\t\tMerry Christmas!!", 16);
    LCD_ShowNumber(0, 16,2012,10,16);
    xSysCtlDelay(30000000);
}
