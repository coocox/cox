//*****************************************************************************
//
//! \file Example.c
//! \brief the AT45DB161 Example.
//! \version 1.0
//! \date 12/14/2012
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
#include "AT45DB161.h"
#include "xhw_types.h"
#include "xgpio.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xhw_uart.h"
#include "xsysctl.h"
#include "xuart.h"

#define MAXLEN      4096

//*****************************************************************************
//
//! \brief UART1 initialize.
//!
//! \param sulBaudRate is the BaudRate of UART1
//!
//! \details UART1 initialize.
//!
//! \return None.
//
//*****************************************************************************
void MyUartInit(unsigned long ulBaudRate)
{
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xUARTConfigSet(USART1_BASE, ulBaudRate, (UART_CONFIG_WLEN_8 |
                   UART_CONFIG_STOP_ONE |
                   UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART1TX, PA9);
}

//*****************************************************************************
//
//! \brief Prints string through UART1.
//!
//! \param str is the string to be printed
//!
//! \details Prints string through UART1.
//!
//! \return None.
//
//*****************************************************************************
static void xUARTPutString(char *str)
{
    char *s = str;
    while(*s != 0)
    {
        xUARTCharPut(USART1_BASE, *s++);
    }
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
    	xUARTCharPut(USART1_BASE, '0');
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
        	xUARTCharPut(USART1_BASE, *--p);
    }
}

unsigned char Buff1[MAXLEN] = {0};  //send buffer
unsigned char Buff2[MAXLEN] = {0};	//receive buffer

void SPIFlashTest(void)
{
    char num[5] = {0};
    unsigned long cnt;
    unsigned long tmp1;

    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(10000);
    AT45DB161_Init(16000000);
    MyUartInit(115200);		//UART1

    xUARTPutString("\r\nRead device information of AT45DB161>>\n\n\r");
    AT45DB161_GetChipID(Buff1);
    for(cnt = 0; cnt < 5; cnt++)
    {
    	UartPrintfNumber(Buff1[cnt]);
        xUARTPutString("\t");
    }

    xUARTPutString("\r\n\nRead state register of AT45DB161>>\n\r");
    Buff1[0] = AT45DB161_GetState();
    UartPrintfNumber(Buff1[0]);
loop:
    xUARTPutString("\n\n\r**************** AT45DB161 flash test program ***************\n\r");
    xUARTPutString("\r\n\n01.Erase page\n\r02.Erase block\n\r03.Erase sector\n\r"
                   "04.Erase chip\n\n\r05.Restore all data\n\n\r06.Read sector protection register\n\r"
                   "07.Program sector protection register\n\r08.Enable Software Sector Protection\n\r"
                   "09.Disable Software Sector Protection\n\n\r10.Test read internal buffer\n\r"
                   "11.Test Write internal buffer\n\r\nPress other key to view page data.\n\r");
    xUARTPutString("\r\n\nPlease input command with an enter>>");

    num[0] = UARTCharGet(USART1_BASE);
    xUARTCharPut(USART1_BASE, num[0]);
    num[1] = UARTCharGet(USART1_BASE);
    xUARTCharPut(USART1_BASE, num[1]);
    while((num[4] = UARTCharGet(USART1_BASE)) != 13);
    xUARTPutString("\r\n");
    tmp1 = (num[0] - '0') * 10 + (num[1] - '0');

    switch(tmp1)
    {
    case 1:		//Erase page
        xUARTPutString("\r\nPlease input the page you want to erase(0000~4095)\n\r>>");
        num[0] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[0]);
        num[1] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[1]);
        num[2] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[2]);
        num[3] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[3]);
        while((num[4] = UARTCharGet(USART1_BASE)) != 13);
        xUARTPutString("\r\n");

        tmp1 = (num[0] - '0') * 1000 + (num[1] - '0') * 100 + (num[2] - '0') * 10 + (num[3] - '0');
        if(tmp1 < 4096)
        {
            AT45DB161_ErasePage(tmp1);
            xUARTPutString("\r\nThe page has been erased\n\r");
        }
        goto loop;
        break;

    case 2:		//Erase block
        xUARTPutString("\r\nPlease input the block you want to erase(000~511)\n\r>>");
        num[0] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[0]);
        num[1] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[1]);
        num[2] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[2]);
        while((num[4] = UARTCharGet(USART1_BASE)) != 13);
        xUARTPutString("\r\n");

        tmp1 = (num[0] - '0') * 100 + (num[1] - '0') * 10 + (num[2] - '0');
        if(tmp1 < 512)
        {
            AT45DB161_EraseBlock(tmp1);
            xUARTPutString("\r\nThe block has been erased\n\r");
        }
        goto loop;
        break;

    case 3:		//Erase sector
        xUARTPutString("\r\nPlease input the sector you want to erase(00~15)\n\r>>");
        num[0] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[0]);
        num[1] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[1]);
        while((num[4] = UARTCharGet(USART1_BASE)) != 13);
        xUARTPutString("\r\n");

        tmp1 = (num[0] - '0') * 10 + (num[1] - '0');
        if(tmp1 < 16)
        {
            AT45DB161_EraseSector(tmp1);
            xUARTPutString("\r\nThe sector has been erased\n\r");
        }
        goto loop;
        break;

    case 4:		//Erase chip
        xUARTPutString("\r\nThe whole chip will be erased\n\r");
        AT45DB161_EraseChip();
        goto loop;
        break;

    case 5:		//Restore all data
        xUARTPutString("\r\nStart writing AT45DB161>>\n\n\r");
        //
        //! Write some data to Buff1
        //
        for(cnt = 0; cnt < MAXLEN; cnt++)
        {
            Buff1[cnt] = (unsigned char)cnt;
        }
        //
        //! Write data to flash
        //
        for(cnt = 10; cnt < 1000000; cnt += MAXLEN)
        {
            AT45DB161_Write(Buff1, cnt, MAXLEN);
            //
            //! display the rate of process
            //
            UartPrintfNumber(cnt / 10000);
            xUARTPutString("\r");
        }
        xUARTPutString("\r100\r\n\nWriting complete!!\n\n\r");
        goto loop;
        break;

    case 6:		//Read sector protection register
        xUARTPutString("\r\nThe sector protection register value are as follow:\n\r");
        AT45DB161_RdSecProtReg(Buff2);
        for(cnt = 0; cnt < 16;)
        {
        	UartPrintfNumber(Buff2[cnt]);
            xUARTPutString("\t");
            if(++cnt % 8 == 0)
                xUARTPutString("\n\r");
            xSysCtlDelay(10000);
        }
        xUARTPutString("\n\r");
        goto loop;
        break;

    case 7:		//Program sector protection register
        for(cnt = 0; cnt < 16; cnt++)
            Buff1[cnt] = 0x66;
        AT45DB161_ProgSecProtReg(Buff1);
        xUARTPutString("\r\nThe sector protection register has been programmed!\n\r");
        goto loop;
        break;

    case 8:		//Enable Software Sector Protection
        AT45DB161_SectorProtectionEn();
        xUARTPutString("\r\nSector Protection has been enabled!\n\r");
        goto loop;
        break;

    case 9:		//Disable Software Sector Protection
        AT45DB161_SectorProtectionDi();
        xUARTPutString("\r\nSector Protection has been disabled!\n\r");
        goto loop;
        break;

    case 10:	//Test read internal buffer
        xUARTPutString("\r\nThe contents of internal buffer1 are:\n\r");
        AT45DB161_ReadBuffer(1, Buff2, 0, MAXLEN);
        for(cnt = 0; cnt < MAXLEN;)
        {
        	UartPrintfNumber(Buff2[cnt]);
            xUARTPutString("\t");
            if(++cnt % 10 == 0)
                xUARTPutString("\n\r");
            xSysCtlDelay(10000);
        }
        goto loop;
        break;

    case 11:	//Test Write internal buffer
        for(cnt = 0; cnt < MAXLEN; cnt++)
        {
            Buff1[cnt] = 12;
        }
        AT45DB161_WriteBuffer(1, Buff1, 0, MAXLEN);
        xUARTPutString("\r\nInternal buffer1 write over!\n\r");
        goto loop;
        break;

    default :
        //xUARTPutString("\r\n invalid command!\n\r");
        break;
    }

    while(1)
    {
        xUARTPutString("\r\n\nInput a page address to show(0000~4095) \n\r>>");
        num[0] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[0]);
        num[1] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[1]);
        num[2] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[2]);
        num[3] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[3]);
        while((num[4] = UARTCharGet(USART1_BASE)) != 13);
        xUARTPutString("\r\n");

        tmp1 = (num[0] - '0') * 1000 + (num[1] - '0') * 100 + (num[2] - '0') * 10 + (num[3] - '0');
        if(tmp1 < 4096)
        {
            xUARTPutString("\r\n\nThe page data are >>\n\n\r");
            AT45DB161_Read(Buff2, tmp1 * 528, 528);
            for(cnt = 0; cnt < 528;)
            {
            	UartPrintfNumber(Buff2[cnt]);
                xUARTPutString("\t");
                if(++cnt % 10 == 0)
                    xUARTPutString("\n\r");
                xSysCtlDelay(10000);
            }
        }
        xUARTPutString("\r\nGoto main menu? y/n >>");
        num[0] = UARTCharGet(USART1_BASE);
        xUARTCharPut(USART1_BASE, num[0]);
        if(num[0] == 'y') goto loop;
    }
}
