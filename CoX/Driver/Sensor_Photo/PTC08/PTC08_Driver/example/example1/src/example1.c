//*****************************************************************************
//
//! \file Example1.c
//! \brief the STLM75 Example.
//! \version 1.0
//! \date 10/15/2011
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
#include "xi2c.h"
#include "hw_STLM75.h"
#include "STLM75.h"

//
//! STLM75 Init callback.
//
void Dev1GPIOInit(void);

//
//! STLM75 Device' OS/INT pin callback.
//
unsigned long UserCallback(void *pvCBData, unsigned long ulEvent, 
                           unsigned long ulMsgParam, void *pvMsgData);

//
//! Redefined the STLM75 Device's I2C pins.
//
#define STLM75_Dev1_SDA         PA8
#define STLM75_Dev1_SCK         PA9

//
//! STLM75 Device.
//
tSTLM75Dev Dev1={
    //
    // DQ is GPIO 
    //
    xGPIOSPinToPortPin(STLM75_Dev1_SCK),
    xGPIOSPinToPortPin(STLM75_Dev1_SDA),
    xGPIOSPinToPortPin(PA0),
    xI2C0_BASE,
    
    //
    // GPIO A.0 Init
    //
    Dev1GPIOInit,
    UserCallback,
    STLM75_ADDRESS_MASK,
};

unsigned char ucTemp1[]="Temperature Overlimit";
unsigned char ucTemp2[]="Temperature not Overlimit";

//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************
static 
void UartInit(void)
{
    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);

    xUARTConfigSet(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                        UART_CONFIG_STOP_ONE | 
                                        UART_CONFIG_PAR_NONE));
}

//*****************************************************************************
//
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
UartPrintfChar(char ch)
{
    unsigned char c;
    c = ch;
    while(!xUARTSpaceAvail(xUART0_BASE));
    
    //
    // Write this character to the transmit FIFO.
    //
    xUARTCharPut(xUART0_BASE, c);
}

//*****************************************************************************
//
//! \brief Prints a decimal unsigned number.
//!
//! \param n is the number to be printed
//!
//! \details Prints a decimal unsigned number.
//!
//! \return None.
//
//*****************************************************************************
static 
void UartPrintfNumber(unsigned long n)
{
    char buf[16], *p;

    if (n == 0)
    {
        UartPrintfChar('0');
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
            UartPrintfChar(*--p);
    }
}

//*****************************************************************************
//
//! \breif STLM75 Init callback.
//!
//! \return None
//
//*****************************************************************************
void Dev1GPIOInit(void)                                        
{
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C0SCL, STLM75_Dev1_SCK);
    xSPinTypeI2C(I2C0DATA, STLM75_Dev1_SDA); 
}
//*****************************************************************************
//! \breif GPIO External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long UserCallback(void *pvCBData, unsigned long ulEvent, 
                           unsigned long ulMsgParam, void *pvMsgData)                                        
{
    float fTemp,fTos,fThys;
    int i;
    fTemp = STLM75TempRead(&Dev1);
    fTos = STLM75LimitRead(&Dev1, 1);
    fThys = STLM75LimitRead(&Dev1, 0);

    if(fTemp > fTos)
    {
        for(i=0; ucTemp1[i]!=0; i++)
            UartPrintfChar(ucTemp1[i]);
    }
    else if(fTemp < fThys)
    {
        for(i=0; ucTemp2[i]!=0; i++)
            UartPrintfChar(ucTemp1[i]);
    } 
    
    return 0;
}

//*****************************************************************************
//
//! \brief 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void Example1(void)
{
    float fTemp;
    
    UartInit();
    STLM75Init(&Dev1, 100000);
    
    STLM75ConfigSet(&Dev1, STLM75_CFG_SHUTDOWN_OFF | STLM75_CFG_MODE_INT |
                           STLM75_CFG_POL_LOW | STLM75_CFG_FT1);
    
    fTemp = STLM75TempRead(&Dev1);
    UartPrintfNumber((unsigned long)fTemp);
    STLM75LimitSet(&Dev1, 25, 0);
    STLM75LimitSet(&Dev1, 27, 1);
    SysCtlDelay(100000);  
    while(1);

}
int main(void)
{
    Example1();
}

