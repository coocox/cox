//*****************************************************************************
//
//! \file xbee.c
//! \brief the xbee Driver.
//! \version V2.1.1.0
//! \date 7/5/2012
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
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "xuart.h"
#include "xbee.h"
#include "cookie.h"

xBeeUART RxBuffer;

xtBoolean
BufferWrite(char cByte)
{
	RxBuffer.pcRxBuffer[RxBuffer.ulRxHead] = cByte;
	RxBuffer.ulRxHead = (RxBuffer.ulRxHead + 1) % MAX_RX_BUFFER;
	RxBuffer.ulRxCount++;
	if(RxBuffer.ulRxCount >= MAX_RX_BUFFER)
	{
		return xfalse;
		RxBuffer.ulError = 1;
	}
	return xtrue;
}
xtBoolean
BufferAllRead(char *pcByte, unsigned long ulReadFlag)//, unsigned long ulLen)
{
	int i;
	unsigned long ulReadF = ulReadFlag;
	unsigned long ulReadLen;
	ulReadLen = (ulReadF + MAX_RX_BUFFER -RxBuffer.ulRxTail)%MAX_RX_BUFFER;
	ulReadLen = RxBuffer.ulRxCount - ulReadLen;
	if (ulReadLen <= 0)
	{
		return xfalse;
	}
	for(i=0;i<ulReadLen;i++)
	{
		pcByte[i] = RxBuffer.pcRxBuffer[ulReadF];
		ulReadF = (ulReadF + 1) % MAX_RX_BUFFER;
		RxBuffer.ulRxCount--;
	}
	return xtrue;
}

void
BufferClear(void)
{
//	int i;
//	for(i=0;i<MAX_RX_BUFFER;i++)
//	{
//		RxBuffer.pcRxBuffer[i]=0;
//	}
	RxBuffer.ulRxCount = 0;
	RxBuffer.ulRxTail = RxBuffer.ulRxHead;
//	RxBuffer.ulRxHead = 0;
	RxBuffer.ulError = 0;
}
void
BufferErrorClear(void)
{
	RxBuffer.ulError = 0;
}

unsigned long
BufferLenGet(void)
{
	return RxBuffer.ulRxCount;
}

unsigned long
BufferStrFind(char * str, unsigned long len)
{
   unsigned long _ByteCnt   = RxBuffer.ulRxCount;
   unsigned long _ReadIndex = RxBuffer.ulRxTail;
   char * SubIndex   = str;

   if(_ByteCnt < len)
   {
	   return (-1);
   }

   while(_ByteCnt != 0)
   {
        while((0 != _ByteCnt) && (RxBuffer.pcRxBuffer[_ReadIndex] != *SubIndex))
        {
            _ByteCnt -= 1;
            _ReadIndex = (_ReadIndex + 1) % MAX_RX_BUFFER;
        }

        //Can not find the str in FIFO
        if(0 == _ByteCnt)
        {
        	return (-1);
        }
        else
        {
        	unsigned long IndexTmp = _ReadIndex;
        	unsigned long CntTmp   = _ByteCnt;
            do
            {
            	CntTmp -= 1;
            	IndexTmp = (IndexTmp + 1) % MAX_RX_BUFFER;
                SubIndex += 1;
            }
            while((0 != CntTmp) && (RxBuffer.pcRxBuffer[IndexTmp] == *SubIndex));

            //match it
            if((SubIndex - str) >= len)
            {
                return _ReadIndex;
            }
            else  //not match, restore string index
            {
                _ByteCnt -= 1;
                _ReadIndex = (_ReadIndex + 1) % MAX_RX_BUFFER;
                SubIndex = str;
            }
        }
   }

   //Find the String
   return 0;
}


//*****************************************************************************
//
//! Event callback function.
//!
//! \param pvCBData is the callback pointer associated with the instance
//!  generating the callback.  This is a value provided by the client during
//! initialization of the instance making the callback.
//! \param ulEvent is the identifier of the asynchronous event which is being
//! notified to the client.
//! \param ulMsgParam is an event-specific parameter.
//! \param pvMsgData is an event-specific data pointer.
//!
//! A function pointer provided to the CoX layer by the application
//! which will be called to notify it of all asynchronous events relating to
//! data transmission or reception.
//!
//! \return Returns 0.
//
//*****************************************************************************
unsigned long
xBeeUARTGet(void *pvCBData, unsigned long ulEvent,
            unsigned long ulMsgParam, void *pvMsgData)
{
	char cbyte;
	cbyte = xUARTCharGetNonBlocking(XBEE_UART);
#if (XBEE_LOOPBACK != 0)
	xUARTCharPut(XBEE_UART, cbyte);
#endif
	if(!RxBuffer.ulError)
	{
		BufferWrite(cbyte);
	}
	return 0;
}

//*****************************************************************************
//
//! \brief Initialize xbee UART.
//!
//! \param None
//! 
//! \return None.
//
//*****************************************************************************
void xBeeUartInit(void)
{
    xSysCtlPeripheralEnable2(XBEE_UART);

    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART1_MAIN, 1);

    sPinTypeUART(XBEE_UART);
    xUARTConfigSet(XBEE_UART, 9600, (xUART_CONFIG_WLEN_8 | xUART_CONFIG_STOP_1 | xUART_CONFIG_PAR_NONE));
    xIntEnable(xINT_UART1);
    xUARTIntEnable(XBEE_UART, xUART_INT_RX);
    xUARTIntCallbackInit(XBEE_UART, xBeeUARTGet);
    xUARTEnable(XBEE_UART, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
}


//*****************************************************************************
//
//! \brief Send a buffer to uart.
//!
//! \param pucBuf is the point of data will be sent.
//! \param ulLength is the length of data will be sent.
//!
//! Send a buffer to uart
//!
//! \return None
//
//*****************************************************************************
void
xBeeUartSendBuf(unsigned char *pucBuf, unsigned long ulLength)
{
    unsigned long i;
    for(i=0; i<ulLength && *pucBuf!=0; i++)
    {
        xUARTCharPut(XBEE_UART, *pucBuf++);
    }
}

//*****************************************************************************
//
//! \brief Enter AT Command Mode.
//!
//! \param None
//!
//! \return xtBoolean.
//
//*****************************************************************************
xtBoolean
xBeeEnterCmdMode(void)
{
	int i=1000;
	xUARTCharPut(XBEE_UART, '+');
	xUARTCharPut(XBEE_UART, '+');
	xUARTCharPut(XBEE_UART, '+');
	xSysCtlDelay(10000000);
	while((!(BufferStrFind("OK", 2)!=-1))&& (i--));

	if (i<=0)
	{
		BufferClear();
		return xfalse;
	}
	else
	{
		BufferClear();
		return xtrue;
	}
}

//*****************************************************************************
//
//! \brief The ND command
//! is used to discover and report all modules on its
//! current operating channel (CH parameter) and
//! PAN ID (ID parameter).
//!
//! \param None
//!
//! \return Number of node.
//
//*****************************************************************************
unsigned long
xBeeNodeGet(void)
{
	int i=0;
	BufferClear();
	xBeeUartSendBuf("ATND\r\n",6);
	xSysCtlDelay(30000000);
    while(BufferLenGet()>=i*48)
    {
    	i++;
    }

	return i;
}

//*****************************************************************************
//
//! \brief The DN command
//! is used to resolve a NI (Node Identifier) string to
//! a physical address.
//!
//! \param pucBuf is the point of data will be sent.
//!
//! \return xtrue or xfalse.
//
//*****************************************************************************
xtBoolean
xBeeNodeConnect(unsigned char *pucBuf)
{
	int i=1000;

//	xBeeUartSendBuf("ATDN",4);
//	xBeeUartSendBuf("R1",2);
	xUARTCharPut(XBEE_UART, 'a');
//	xSysCtlDelay(1000000);
	xUARTCharPut(XBEE_UART, 't');
//	xSysCtlDelay(1000000);
	xUARTCharPut(XBEE_UART, 'd');
//	xSysCtlDelay(1000000);
	xUARTCharPut(XBEE_UART, 'n');
//	xSysCtlDelay(1000000);
//	xUARTCharPut(XBEE_UART, 'r');
//	xUARTCharPut(XBEE_UART, '2');
	xBeeUartSendBuf(pucBuf,20);

	xUARTCharPut(XBEE_UART, '\r');
	xSysCtlDelay(300000);
	while((!(BufferStrFind("OK", 2)!=-1))&& (i--));

	if (i<=0)
	{
		BufferClear();
		return xfalse;
	}
	else
	{
		BufferClear();
		return xtrue;
	}
}
