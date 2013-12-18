//*****************************************************************************
//
//! \file GetTouchPoint_Example.c
//! \brief Example for ADS7843 touch screen controller driver
//! \version V0.0.1
//! \date 4/28/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox
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
#include "xhw_memmap.h"
#include "xhw_uart.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "stdio.h"
#include "ADS7843.h"

//*****************************************************************************
//
//! \brief Touch example
//!
//! \param None.
//!
//! This function use UART1 of STM32 to print the x,y coordinate information.
//! You can use a hyper terminal to see the result.
//!
//! \return None.
//
//*****************************************************************************
void TouchExample(void)
{
    unsigned short adx, ady, posx, posy;
    unsigned char ucRes;

    //  System clock initialization
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(10000);

    // Configure the UART1 as debug print port
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xUARTConfigSet(xUART1_BASE, 115200, (xUART_CONFIG_WLEN_8 |
                                         xUART_CONFIG_STOP_1 |
                                         xUART_CONFIG_PAR_NONE));
    xUARTEnable(xUART1_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART1TX, PA9);

    //  ADS7843 initialization
    ADS7843Init();
    printf("---------Touch Screen Test----------\n\r");
    printf("Waiting for calibrating...\n\rLeave it alone if calibration is not needed.\n\r");
    ucRes = ADS7843Calibration();
    if(ucRes == 3)
    {
        printf("Calibration OK.\n\r");
    }
    else
    {
        if(ucRes == 2)
        {
            printf("Y axis calibration over.\n\r");
        }
        else if(ucRes == 1)
        {
            printf("X axis calibration over.\n\r");
        }
        printf("Calibration time out\n\r");
    }

    while(1)
    {
        // If pen down
#ifndef ADS7843_ENABLE_TOUCH_INT
        if(!ADS7843PenInq())
#else
        if(tTouchData.touch_status & TOUCH_STATUS_TOUCHING)
#endif
        {
            ADS7843ReadADXY(&adx, &ady);
            ADS7843ReadPiontXY(&posx, &posy);
            printf("The screen was touched!------------------>\n\r");
            printf("Current Touch Point AD Value of X: %d\n\r", adx);
            printf("Current Touch Point AD Value of Y: %d\n\r", ady);
            printf("Current Touch Point X Coordinate: %d\n\r", posx);
            printf("Current Touch Point Y Coordinate: %d\n\r", posy);
            xSysCtlDelay(1000000);
        }
    }
}
