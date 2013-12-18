//*****************************************************************************
//
//! \file TEL0026.c
//! \brief TEL0026 Arduino Bluetooth Bee driver file.
//! \version V2.2.1.0
//! \date 3/3/2013
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
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xuart.h"
#include "xgpio.h"
#include "hw_TEL0026.h"
#include "TEL0026.h"

//
// UART receiving circle buffer size
//
#define UART_RXD_BUFFER_SIZE 64

//
// Command buffer size
//
#define UART_TXD_BUFFER_SIZE 30


// UART receiving circle buffer
static char s_cUartRecBuffer[UART_RXD_BUFFER_SIZE];
// command buffer
static char s_cCmdBuffer[UART_TXD_BUFFER_SIZE];

//
// receiving buffer overflow flag
//
static unsigned char s_ucRecBufOverFlow = 0;

//
// receiving buffer received lines count
//
static unsigned char s_ucLinesCnt = 0;



//*****************************************************************************
//
//! \brief The UART receiving interrupt service function
//!
//! \param pvCBData Not used.
//! \param ulEvent Not used.
//! \param ulMsgParam Not used.
//! \param pvMsgData Not used.
//!
//! This function is to deal with UART receive interrupt and save received
//! data to FIFO receiving buffer.
//!
//! \return Actually read out bytes count.
//
//*****************************************************************************
static unsigned char ucHead = 0;  // Point to the first of received data
static unsigned char ucTail = 0;  // Point to the next to the end of received data

unsigned long UartInterruptReceive(void *pvCBData,  unsigned long ulEvent,
        unsigned long ulMsgParam,
        void *pvMsgData)
{
	//
	// The receive function use ucUartRecBuffer as a circle buffer.
	// When the buffer is empty ucHead==ucTail. When the buffer is full
	// ucTail - ucHead == UART_RXD_BUFFER_SIZE-1 or ucHead-ucTail ==1.
	// If the buffer is full, the extra received data will be abandoned.
	//
	if(((ucTail - ucHead) > (UART_RXD_BUFFER_SIZE-1))||((ucHead-ucTail)==1))
	{
		s_ucRecBufOverFlow = 1;
		return 0;
	}
	else
	{
		s_ucRecBufOverFlow = 0;
	}


	//
	//! \note Since interrupt flags are cleared in system interrupt program before
	// invoking this interrupt function, we should only use register read, or
	// we will not get the right value!!! If you use this driver, the following
	// sentence(read data register of UART) may need to modify.
	//
	//ucUartRecBuffer[ucReceivedBytes++] = xUARTCharGetNonBlocking(TEL0026_UART_BASE);
	s_cUartRecBuffer[ucTail++] = xHWREG(TEL0026_UART_BASE + 0x00000004);//read DR

	if(s_cUartRecBuffer[ucTail-1] == '\n')
	{
		s_ucLinesCnt++;
	}

	if((ucTail > UART_RXD_BUFFER_SIZE-1) && (ucHead != 0))
	{
		ucTail = 0;
	}
	return 0;
}

//*****************************************************************************
//
//! \brief Read received data bytes from receiving buffer
//!
//! \param usLength The length of data.
//! \param pData The output buffer.
//!
//! This function is to Read UART received data from receive-buffer.
//!
//! \return Actually read out bytes count.
//
//*****************************************************************************
unsigned short RecBufReadBytes(unsigned short usLength, unsigned char *pData)
{
	unsigned short usReadCnt = 0;
	unsigned long ulWait = TEL0026_TIMEOUT_SHORT;

	while(usReadCnt < usLength)
	{
		ulWait = TEL0026_TIMEOUT_SHORT;
		while(ucTail == ucHead)
		{
			if(--ulWait < 1) return usReadCnt;
		}
		pData[usReadCnt++] = s_cUartRecBuffer[ucHead++];
		if(ucHead == UART_RXD_BUFFER_SIZE)
			ucHead = 0;
	}
	return usReadCnt;
}

//*****************************************************************************
//
//! \brief Read a line of string from receiving buffer
//!
//! \param pData The output buffer.
//!
//! This function is to Read UART received data from receive-buffer.
//!
//! \return Actually read out bytes count.
//
//*****************************************************************************
unsigned char BTReadLine(char *pData)
{
	unsigned char ucLineLen = 0;
	unsigned long ulTimeOut = TEL0026_TIMEOUT_LONG;

	while(ulTimeOut && (s_ucLinesCnt == 0))
	{
		if(--ulTimeOut == 0)
			return 0;
	}

	//if(s_ucLinesCnt)
		s_ucLinesCnt--;
	while(s_cUartRecBuffer[ucHead]!='\r')
	{
		*pData++ = s_cUartRecBuffer[ucHead++];
		if(ucHead == UART_RXD_BUFFER_SIZE)
			ucHead = 0;
		ucLineLen++;
	};
	*pData = 0;
	ucHead += 2;

	return ucLineLen;
}

//*****************************************************************************
//
//! \brief Clear the receiving buffer
//!
//! \param None.
//!
//! This function is to clear the receiving buffer.
//!
//! \return none.
//
//*****************************************************************************
void ClearRecBuf(void)
{
	ucHead = 0;
	ucTail = 0;
	s_ucLinesCnt = 0;
}

//*****************************************************************************
//
//! \brief MCU send an amount of data bytes to TEL0026.
//!
//! \param ulLength The length of data.
//! \param pData Data to be sent
//!
//! This function is simply to send a length of data.
//!
//! \return None.
//
//*****************************************************************************
void BTSendBytes(unsigned long ulLength, unsigned char *pData)
{
	while(ulLength > 0)
	{
		xUARTCharPut(TEL0026_UART_BASE, *pData++);
	}
}

//*****************************************************************************
//
//! \brief MCU send command string to TEL0026.
//!
//! \param pStr Command string.
//!
//! This function is to send command to TEL0026 and get response from it.
//! \note While TEL0026 is connected with other blue-tooth device and build a
//! wireless serial connection, all AT commands are invalid, they will be
//! regarded as common data.
//!
//! \return None.
//
//*****************************************************************************
void BTSendCmdString(const char *pStr)
{
    while(*pStr != 0)
    {
        xUARTCharPut(TEL0026_UART_BASE, *pStr++);
    }
    xUARTCharPut(TEL0026_UART_BASE, '\r');
    xUARTCharPut(TEL0026_UART_BASE, '\n');
}

//*****************************************************************************
//
//! \brief String compare function.
//!
//! \param pStr1 Point to first string.
//! \param pStr2 Point to second string.
//!
//! This function is to compare two string, if they are the same return 0,
//! else return 1.
//!
//! \return None.
//
//*****************************************************************************
//static
char StrCmp(const char *pStr1, const char *pStr2)
{
	while(*pStr1 && *pStr2 && (*pStr1 == *pStr2))
	{
		pStr1++;
		pStr2++;
	}
	if(*pStr1 == *pStr2)
		return 0;
	else
		return (*pStr1 - *pStr2);
}

//*****************************************************************************
//
//! \brief String connection function.
//!
//! \param pDest Point to destination string.
//! \param pSource Point to source string.
//!
//! This function is to connect two string. The destination string must have
//! enough size to hold source string.
//!
//! \return String length after connection.
//
//*****************************************************************************
//static
unsigned char StrCat(char *pDest, const char *pSource)
{
	unsigned char ucStrLen = 0;
	while(*pDest)
	{
		pDest++;
		ucStrLen++;
	}
	while(*pSource)
	{
		*pDest++ = *pSource++;
		ucStrLen++;
	}
	*pDest = *pSource;
	return ucStrLen;
}

//*****************************************************************************
//
//! \brief Convert number to string.
//!
//! \param ulNum The number to be converted
//! \param pDest Destination string
//! \param ucDigitType Specifies the digit type(2: binary, 8:octal, 10:decimal, 16:hex)
//!
//! This function is to convert number to string. The number type can be specified.
//!
//! \return Converted number string.
//
//*****************************************************************************
//static
char * Num2Str(unsigned long ulNum, char *pDest, unsigned char ucDigitType)
{
	unsigned char tmp = 0;
	char *p = pDest;
	char *s = pDest;

	if(ulNum == 0)
	{
		pDest[0] = '0';
		pDest[1] = 0;
	}
	else
	{
		while(ulNum)
		{
			tmp = ulNum % ucDigitType;
			if(ucDigitType > 10)
			{
				tmp = tmp - 10 + 'A';
			}
			else
			{
				tmp = tmp + '0';
			}
			*p++ = tmp;
			ulNum /= ucDigitType;
		}
		*p-- = 0;

		for( ; s<p ;s++, p--)
		{
			tmp = *s;
			*s = *p;
			*p = tmp;
		}
	}
	return pDest;
}

//*****************************************************************************
//
//! \brief Address convert.
//!
//! \param DevAddr Point to device address string get from TEL0026.
//!
//! This function is to convert address getting from TEL0026 in form like
//! "1234:56:A12B34" to form like "1234,56,A12B34" to get uniformed with input
//! address parameter of TEL0026.
//!
//! \return None.
//
//*****************************************************************************
void BTAddrConv(char *pDevAddr)
{
	while(*pDevAddr)
	{
		if(*pDevAddr == ':')
		{
			*pDevAddr = ',';
		}
		pDevAddr++;
	}
}

//*****************************************************************************
//
//! \brief Error code decode function.
//!
//! \param pErrStr Point to error string(do not contain "\r\n").
//!
//! This function is to get error state of returned string after send a command
//! to TEL0026.
//!
//! \return Error number refer to hw_TEL0026.h.
//
//*****************************************************************************
static tBtResult BTErrorDecode(char *pErrStr)
{
	unsigned char ucRes;
	char cRes = StrCmp(BtResOk, pErrStr);

	//
	// pErrStr is "+XXXX:xxxx"
	//
	if(*pErrStr == '+') return BT_ERR_OK;

	if(cRes == 0)
	{
		//
		// pErrStr is "OK"
		//
		return BT_ERR_OK;
	}
	else if(cRes < 0)
	{
		//
		// pErrStr is "SUCCESS"
		//
		return BT_ERR_SUCCESS;
	}
	else if(cRes <= 'O'-'F')
	{
		//
		// pErrStr is "FAIL"
		//
		return BT_ERR_FAIL;
	}
	else if(cRes <= 'O'-'E')
	{
		//
		// pErrStr is "ERROR:(n)"
		//
		while(*pErrStr++!='(');
		if(*(pErrStr+1)==')')
		{
			// n < 10
			ucRes = (*pErrStr <= '9') ? (*pErrStr - '0') : (*pErrStr - 'A');
			ucRes += BT_ERR_AT_CMD_ERR;
		}
		else
		{
			// n > 10
			ucRes = (*pErrStr <= '9') ? (*pErrStr - '0') : (*pErrStr - 'A');
			pErrStr++;
			ucRes *= 16;
			ucRes += (*(pErrStr) <= '9') ? (*(pErrStr) - '0') : (*(pErrStr) - 'A');
			ucRes += BT_ERR_AT_CMD_ERR;
		}
		return ucRes;
	}
	else
	{
		return BT_ERR_UNKNOW_ERROR;
	}
}

//*****************************************************************************
//
//! \brief Get response of TEL0026.
//!
//! \param None
//!
//! This function is to get response of TEL0026 after sending a command to it.
//!
//! \return Response error code.
//
//*****************************************************************************
tBtResult BTGetResponse(void)
{
	unsigned char ucRes = 0;
	while(!BTReadLine(s_cCmdBuffer))
	{
		ucRes++;
		if(ucRes>100)
			return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	return ucRes;
}

//*****************************************************************************
//
//! \brief MCU UART initialization.
//!
//! \param ulBaudRate Specify the baud rate of UART.
//! \param ucParity Specify the parity of UART.
//!
//! This function is to initialize mcu's UART port to communicate with TEL0026.
//!
//! \return None.
//
//*****************************************************************************
static void UartInit(unsigned long ulBaudRate, unsigned char ucParity, unsigned char ucStopBit)
{
	unsigned long ulUartConfig = 0;
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TEL0026_PIN_RXD));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TEL0026_PIN_TXD));
	xSysCtlPeripheralEnable2(TEL0026_UART_BASE);
	//xUARTDisable(TEL0026_UART_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));

	switch(ucParity)
	{
	case 0:
		ulUartConfig |= xUART_CONFIG_WLEN_8 | xUART_CONFIG_PAR_NONE;
		break;
	case 1:
		ulUartConfig |= xUART_CONFIG_WLEN_9 | xUART_CONFIG_PAR_ODD;
		break;
	case 2:
		ulUartConfig |= xUART_CONFIG_WLEN_9 | xUART_CONFIG_PAR_EVEN;
		break;
	default :
		ulUartConfig |= xUART_CONFIG_WLEN_8 | xUART_CONFIG_PAR_NONE;
		break;
	}
	if(ucStopBit == 2)
	{
		ulUartConfig |= xUART_CONFIG_STOP_2;
	}
	else
	{
		ulUartConfig |= xUART_CONFIG_STOP_1;
	}
	xUARTConfigSet(TEL0026_UART_BASE, ulBaudRate, ulUartConfig);

    //
    // Enable UART RX interrupt
    //
    xUARTIntEnable(TEL0026_UART_BASE, xUART_INT_RX);
    xUARTIntCallbackInit(TEL0026_UART_BASE, UartInterruptReceive);

    //
    // Enable UART interrupt
    //
    xIntEnable(TEL0026_UART_INT);
    xUARTEnable(TEL0026_UART_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(TEL0026_UART_TX, TEL0026_PIN_TXD);
}

//*****************************************************************************
//
//! \brief TEL0026 self test.
//!
//! \param None.
//!
//! This function is to send AT command to see if TEL0026 is ready.
//
//! \note While TEL0026 is connected with other blue-tooth device and build a
//! wireless serial connection, all AT commands are invalid, they will be
//! regarded as common data.
//!
//! \return Returns the status of operation.
//
//*****************************************************************************
tBtResult BTTestOK(void)
{
	ClearRecBuf();
	BTSendCmdString(BtCmdAt);
	return(BTGetResponse());
}

//*****************************************************************************
//
//! \brief Set TEL0026 module's baud rate.
//!
//! \param pName Specify the baud rate(bps) to use.
//!
//! This function is to set TEL0026 data baud rate. The default baud rate is 9600bps.
//! \Note This function is only effective in directly data transfer mode and does
//! not affect the baud rate when in AT mode which will always be 38400,0,0
//!
//!
//! \note While TEL0026 is linked with other blue-tooth device and build a
//! wireless serial connection, all AT commands are invalid, they will be
//! regarded as common data.
//! \note the settings are stored into TEL0026 and will not lose even power down.
//!
//! \return Returns the status of operation.
//
//*****************************************************************************
tBtResult BTUartParamSet(unsigned long ulBaudRate,
		unsigned char ucParity, unsigned char ucStopBit)
{
	char cTmp[20];

	ClearRecBuf();
	if(ulBaudRate <= 4800)
	{
		ulBaudRate = 4800;
	}
	else if(ulBaudRate <= 9600)
	{
		ulBaudRate = 9600;
	}
	else if(ulBaudRate <= 19200)
	{
		ulBaudRate = 19200;
	}
	else if(ulBaudRate <= 38400)
	{
		ulBaudRate = 38400;
	}
	else if(ulBaudRate <= 57600)
	{
		ulBaudRate = 57600;
	}
	else if(ulBaudRate <= 115200)
	{
		ulBaudRate = 115200;
	}
	else if(ulBaudRate <= 230400)
	{
		ulBaudRate = 230400;
	}
	else if(ulBaudRate <= 460800)
	{
		ulBaudRate = 460800;
	}
	else if(ulBaudRate <= 921600)
	{
		ulBaudRate = 921600;
	}
	else
	{
		ulBaudRate = 1382400;
	}
	if(ucParity >2)
	{
		ucParity = 2;
	}
	if(ucStopBit<=1)
	{
		ucStopBit = 1;
	}
	else
	{
		ucStopBit = 2;
	}

	s_cCmdBuffer[0] = 0; // Clear CmdBuffer

	//
	// Convert number and connect string
	//
	StrCat(s_cCmdBuffer, BtCmdUartParaSet);
	StrCat(s_cCmdBuffer, Num2Str(ulBaudRate, cTmp, 10));
	StrCat(s_cCmdBuffer, ",");
	StrCat(s_cCmdBuffer, Num2Str(ucParity, cTmp, 10));
	StrCat(s_cCmdBuffer, ",");
	StrCat(s_cCmdBuffer, Num2Str(ucStopBit, cTmp, 10));

	BTSendCmdString(s_cCmdBuffer);

	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Get UART parameters of TEL0026.
//!
//! \param pParam To store name string.
//!
//! This function is to set bluetooth pairing password of TEL0026.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTUartParamGet(char *pParam)
{
	pParam[0] = 0;
	ClearRecBuf();
	BTSendCmdString(BtCmdUartParaGet);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}

	//
	// Copy param string to pParam
	//
	StrCat(pParam, s_cCmdBuffer + 6);
	////////////////////////////
	BTReadLine(s_cCmdBuffer);

	return (BTErrorDecode(s_cCmdBuffer));
}

//*****************************************************************************
//
//! \brief Set password of TEL0026.
//!
//! \param pPswd To store name string.
//!
//! This function is to set bluetooth pairing password of TEL0026.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTPasswordSet(char *pPswd)
{
	ClearRecBuf();
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	StrCat(s_cCmdBuffer, BtCmdPassWordSet);
	StrCat(s_cCmdBuffer, pPswd);
	BTSendCmdString(s_cCmdBuffer);

	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Get password of TEL0026.
//!
//! \param pPswd To store name string.
//!
//! This function is to get bluetooth pairing password of TEL0026.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTPasswordGet(char *pPswd)
{
	*pPswd = 0;  //Clear password buffer
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	ClearRecBuf();

	BTSendCmdString(BtCmdPassWordGet);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}

	StrCat(pPswd, s_cCmdBuffer + 6);
////////////////////////////////////
	BTReadLine(s_cCmdBuffer);
	// Return error information
	return(BTErrorDecode(s_cCmdBuffer));
}

//*****************************************************************************
//
//! \brief Set bluetooth name of TEL0026.
//!
//! \param pName To store name string.
//!
//! This function is to set bluetooth name of TEL0026.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceNameSet(char *pName)
{
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	ClearRecBuf();

	StrCat(s_cCmdBuffer, BtCmdNameSet);
	StrCat(s_cCmdBuffer, pName);
	BTSendCmdString(s_cCmdBuffer);

	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Get bluetooth name of TEL0026.
//!
//! \param pName To store name string.
//!
//! This function is to get bluetooth name of TEL0026.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceNameGet(char *pName)
{
	unsigned char ucRes;

	pName[0] = 0;
	ClearRecBuf();
	BTSendCmdString(BtCmdNameGet);
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		// If no error copy device name to pName buffer
		// remove 6 bytes of the header
		StrCat(pName, s_cCmdBuffer + 6);
	}
	///////////////////////////////
	BTReadLine(s_cCmdBuffer);
	return ucRes;
}

//*****************************************************************************
//
//! \brief Restore the default setting.
//!
//! \param None.
//!
//! This function is to restore all settings to default value.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTRestore(void)
{
	ClearRecBuf();
	BTSendCmdString(BtCmdRestore);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Get software version of TEL0026.
//!
//! \param pBuf To store version information read from device.
//!
//! This function is to get software version of TEL0026 bluetooth module.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTVersionGet(char *pBuf)
{
	unsigned char ucRes;

	pBuf[0] = 0;
	ClearRecBuf();
	BTSendCmdString(BtCmdVersion);
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		// If no error copy version string to buffer
		// remove 9 bytes of the header
		StrCat(pBuf, s_cCmdBuffer + 9);
	}
	////////////////////////////////////
	BTReadLine(s_cCmdBuffer);
	return ucRes;
}

//*****************************************************************************
//
//! \brief TEL0026 role mode set.
//!
//! \param ucRoleMode Specify the working role mode of TRL0026 BT module.
//!
//! The parameter \e ucRoleMode is an enumerated data type that can be one of
//! the following values:
//!
//! - \b BT_ROLE_SLAVE
//! - \b BT_ROLE_MASTER
//! - \b BT_ROLE_SLAVE_LOOP
//!
//! This function is to set TEL0026 working role mode.
//! - In slave mode, the module can be connected by other device.
//! - In slave-loop mode, the module can  be connected by other
//!   device, receive and send back whatever received.
//! - In master mode, the module can actively poll the nearby device
//!   and initialize binding to other devices.
//!
//! \return Returns the status of operation.
//
//*****************************************************************************
tBtResult BTDeviceRoleSet(char cRoleMode)
{
	char cTmp[2];

	cTmp[0] = cRoleMode;
	cTmp[1] = 0;
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	ClearRecBuf();

	StrCat(s_cCmdBuffer, BtCmdRoleSet);
	StrCat(s_cCmdBuffer, cTmp);
	BTSendCmdString(s_cCmdBuffer);

	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief TEL0026 role mode get.
//!
//! \param None.
//!
//! This function is to get TEL0026 working role mode.
//!
//! \return Returns the role mode of TEL0026 or error information.
//
//*****************************************************************************
unsigned char BTDeviceRoleGet(void)
{
	unsigned char ucRes;

	ClearRecBuf();
	BTSendCmdString(BtCmdRoleGet);
	BTReadLine(s_cCmdBuffer);
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		// If no error return device role(0 or 1)
		return(*(s_cCmdBuffer + 9));
	}
	else
	{
		// Return error information
		return ucRes;
	}
}

//*****************************************************************************
//
//! \brief TEL0026 set device type.
//!
//! \param ulDevClass Specifies the bluetooth type.
//!
//! This function is to set device type of the bluetooth. The parameter is a
//! 32 bits number which specifies the Class of Device/Service(CoD).
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceTypeSet(unsigned long ulDevClass)
{
	char cTmp[10];

	ClearRecBuf();
	Num2Str(ulDevClass, cTmp, 16);
	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	StrCat(s_cCmdBuffer, BtCmdClassSet);
	StrCat(s_cCmdBuffer, cTmp);
	BTSendCmdString(s_cCmdBuffer);

	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief TEL0026 get bluetooth device type.
//!
//! \param pType Store the bluetooth type information.
//!
//! This function is to get device type of the bluetooth. The read out device
//! class value is a 32 bits number in character format and hex form.
//!
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceTypeGet(char *pType)
{
	unsigned char ucRes;

	pType[0] = 0; //clear buffer
	ClearRecBuf();
	BTSendCmdString(BtCmdClassGet);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}

	//
	// Copy data to pType buffer
	//
	StrCat(pType, s_cCmdBuffer + 7);
	ucRes = BTErrorDecode(s_cCmdBuffer);

	return ucRes;
}

//*****************************************************************************
//
//! \brief TEL0026 set inquiry mode.
//!
//! \param ucMode Specifies inquiry mode(0 - standard, 1 - RSSI).
//! \param ucMaxDevs Specifies max number of responded devices.
//! \param ucTimeOut Specifies how long for inquiry, can be 1~48(1.28s~61.44s)
//!
//! This function is to set inquiry mode of the bluetooth to get prepared for
//! inquiring nearby bluetooth devices.
//!
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTInqModeSet(unsigned char ucMode, unsigned char ucMaxDevs,
		unsigned char ucTimeOut)
{
	char cTmp[3];

	s_cCmdBuffer[0] = 0;  // Clear CmdBuffer
	ClearRecBuf();

	if(ucMode > 1) ucMode = 1;
	if(ucTimeOut > 48) ucTimeOut = 48;

	//
	// Parameters convert to string and connect to command
	//
	cTmp[0] = '0' + ucMode;
	cTmp[1] = ',';
	cTmp[2] = 0;
	StrCat(s_cCmdBuffer, BtCmdInqModeSet);
	StrCat(s_cCmdBuffer, cTmp);
	StrCat(s_cCmdBuffer, Num2Str(ucMaxDevs, cTmp, 10));
	StrCat(s_cCmdBuffer, ",");
	StrCat(s_cCmdBuffer, Num2Str(ucTimeOut, cTmp, 10));
	BTSendCmdString(s_cCmdBuffer);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Get inquiry mode of the TEL0026 bluetooth module.
//!
//! \param pBuf To store the inquiry mode information("n1,n2,n3").
//!
//! This function is to get inquiry mode of the bluetooth.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTInqModeGet(char *pBuf)
{
	unsigned char ucRes;

	*pBuf = 0;
	ClearRecBuf();
	s_cCmdBuffer[0] = 0;
	BTSendCmdString(BtCmdInqModeGet);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		// If no error, copy inquire string to buffer
		StrCat(pBuf, s_cCmdBuffer + 6);
	}
	return ucRes;
}

//*****************************************************************************
//
//! \brief Get current state of TEL0026.
//!
//! \param pBuf To store the inquiry mode information.
//!
//! This function is to get inquiry mode of the bluetooth.
//! Status can be following values:
//! - "INITIALIZED"
//! - "READY"
//! - "PAIRABLE"
//! - "PAIRED"
//! - "INQUIRING"
//! - "CONNECTING"
//! - "CONNECTED"
//! - "DISCONNECTED"
//! - "UNKNOW"
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTStatusGet(char *pBuf)
{
	unsigned char ucRes;

	*pBuf = 0;
	ClearRecBuf();
	BTSendCmdString(BtCmdStatusGet);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		//
		// If no error, return copy status string to pBuf
		//
		StrCat(pBuf, s_cCmdBuffer + 7);
	}
	return ucRes;
}

//*****************************************************************************
//
//! \brief Get the bluetooth address of TEL0026.
//!
//! \param pBuf To store the address information(format like: 1234:56:abcdef).
//!
//! This function is to get address of the bluetooth.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceAddrGet(char *pBuf)
{
	unsigned char ucRes;

	*pBuf = 0;
	ClearRecBuf();
	BTSendCmdString(BtCmdAddr);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		//
		// If no error, return copy address to pBuf
		//
		StrCat(pBuf, s_cCmdBuffer + 6);
	}
	//////////////////////////////
	BTReadLine(s_cCmdBuffer);
	return ucRes;
}

//*****************************************************************************
//
//! \brief Get remote bluetooth device name.
//!
//! \param pRemoDevAddr The address of remote device(format like: 1234,56,abcdef).
//! \param pRemoDevName The name of remote device
//!
//! This function is to get remote device's name by it's address.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTRemoteDeviceNameGet(char *pRemoDevAddr, char *pRemoDevName)
{
	unsigned char ucRes = 0;

	ClearRecBuf();
	pRemoDevName[0] = 0;
	s_cCmdBuffer[0] = 0;
	StrCat(s_cCmdBuffer, BtCmdRemoteDevNameGet);
	StrCat(s_cCmdBuffer, pRemoDevAddr);
	BTSendCmdString(s_cCmdBuffer);
	while(!BTReadLine(s_cCmdBuffer))
	{
		ucRes++;
		if(ucRes>100)
			return BT_ERR_NORESPONSE;
	}
	ucRes = BTErrorDecode(s_cCmdBuffer);
	if(!ucRes)
	{
		//
		// If no error, return copy address to pBuf
		//
		StrCat(pRemoDevName, s_cCmdBuffer + 7);
	}
	return ucRes;
}

//*****************************************************************************
//
//! \brief Scan nearby bluetooth devices
//!
//! \param ucMode Specifies inquiry mode(0 - standard, 1 - RSSI).
//! \param ucMaxDevs Specifies max number of responded devices.
//! \param ucTimeOut Specifies how long for inquiry, can be 1~48(1.28s~61.44s).
//! \param ucRemoteDevAddr A string array pointer to store device address.
//!
//! This function is to inquire nearby bluetooth devices and get their address,
//! device class and RSSI separated by commas in format like:
//! "1234:56:abcdef,1F1F,FFC1"(don't include "").
//! "1234:56:abcdef,1F1F,FFC0"
//! "2:72:D2224,3E0104,FFBC"
//!
//! \note This function is effective when set TEL0026 to master mode or it will
//! simply return OK.
//!
//! \return Returns the number of scanned devices.
//
//*****************************************************************************
unsigned char BTScanRemoteDevice(unsigned char ucInqMode, unsigned char ucMaxDevNum,
		unsigned char ucMaxTimeOut, char *pRemoteDevAddr)
{
	unsigned char ucRes = 0;
	unsigned char ucScannedDevice = 0;
	unsigned char ucTimeOut = 0;
	unsigned char i;
	unsigned char ucNotExist = 0;
	char cAddrTmp[15] = {0};


	BTDeviceRoleSet(BT_ROLE_MASTER);
	ClearRecBuf();
	//
	// Initialize SPP profile lib
	//
	BTSendCmdString(BtCmdInitSppLib);
	ucRes = BTGetResponse();
	if((ucRes != BT_ERR_OK)&&(ucRes != BT_ERR_SPP_REPEAT_INIT))
		return 0;

	s_cCmdBuffer[0] = 0;
	//
	// Inquire general inquire access code
	//
	StrCat(s_cCmdBuffer, BtCmdInqAccCodeSet);
	StrCat(s_cCmdBuffer, "9e8b33");
	BTSendCmdString(s_cCmdBuffer);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return 0;
	}
	s_cCmdBuffer[0] = 0;

	//
	// Inquire all devices types
	//
	StrCat(s_cCmdBuffer, BtCmdClassSet);
	StrCat(s_cCmdBuffer, "0");
	BTSendCmdString(s_cCmdBuffer);
	if(!BTReadLine(s_cCmdBuffer))
	{
		return 0;
	}

	ucRes = BTInqModeSet(ucInqMode, ucMaxDevNum, ucMaxTimeOut);
	if(ucRes != BT_ERR_OK) return 0;

	//
	// Inquire nearby devices
	//
	BTSendCmdString(BtCmdInqNearbyDev);

	while(ucMaxDevNum--)
	{
		while(BTReadLine(s_cCmdBuffer) == 0)
		{
			if(ucTimeOut++ > ucMaxTimeOut)
				return ucScannedDevice;
		}
		if(*s_cCmdBuffer == '+')
		{
			pRemoteDevAddr[ucScannedDevice*15] = 0;
			for(i=5; s_cCmdBuffer[i]!=','; i++)
				cAddrTmp[i-5] = s_cCmdBuffer[i];
			cAddrTmp[i-5] = 0;
			if(ucScannedDevice==0)
			{
				//
				// If scanned first device store it directly
				//
				StrCat(&pRemoteDevAddr[ucScannedDevice*15], cAddrTmp);
				ucScannedDevice++;
			}
			else if(ucScannedDevice < TEL0026_MAX_SCAN_DEVICES)
			{
				//
				// If is not first device, compared with last device,
				// if address is different store it.
				//
				for(i=0; i<ucScannedDevice; i++)
				{
					if(StrCmp(&pRemoteDevAddr[i*15], cAddrTmp) != 0)
					{
						ucNotExist++;
					}
				}
				if(ucNotExist==ucScannedDevice)
				{
					StrCat(&pRemoteDevAddr[ucScannedDevice*15], cAddrTmp);
					ucScannedDevice++;
				}
				ucNotExist = 0;
			}
		}
		else
		{
			return ucScannedDevice;
		}
	}
	return ucScannedDevice;
}

//*****************************************************************************
//
//! \brief Stop inquiring nearby bluetooth devices
//!
//! \param None
//!
//! This function is to stop inquiring nearby bluetooth devices.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTInqCancle(void)
{
	ClearRecBuf();
	BTSendCmdString(BtCmdInqCancel);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Pairing with nearby bluetooth devices
//!
//! \param pRemoteDevAddr Specifies the remote bluetooth device address
//! \param ucTimeOut Specifies the max waiting time for pairing.
//!
//! This function is to pairing with nearby bluetooth devices.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTPairing(char *pRemoteDevAddr, unsigned char ucTimeOut)
{
	char cTmp[5];

	ClearRecBuf();
	s_cCmdBuffer[0] = 0;
	StrCat(s_cCmdBuffer, BtCmdDevicePairing);
	StrCat(s_cCmdBuffer, pRemoteDevAddr);
	StrCat(s_cCmdBuffer, ",");
	StrCat(s_cCmdBuffer, Num2Str(ucTimeOut, cTmp, 10));

	BTSendCmdString(s_cCmdBuffer);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Check if the given bluetooth devices address is in the authenticated device list.
//!
//! \param pDevAddr Specifies the bluetooth device address(format like: 1234,56,abcdef)
//!
//! This function is to check if the given bluetooth devices address is
//! in the authenticated device list.
//!
//! \return Returns the result of operation(BT_ERR_OK:exist, BT_ERR_FIAL:not exist).
//
//*****************************************************************************
tBtResult BTLocateAuthDevice(char *pDevAddr)
{
	ClearRecBuf();
	s_cCmdBuffer[0] = 0;
	StrCat(s_cCmdBuffer, BtCmdLocSelDev);
	StrCat(s_cCmdBuffer, pDevAddr);
	BTSendCmdString(s_cCmdBuffer);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Connect to remote device
//!
//! \param pRemoteDevAddr The remote bluetooth device address(format like: 1234,56,abcdef)
//!
//! This function is to connect to remote bluetooth device. It's only valid in
//! master mode. If you want to connect successfully, the password of the two
//! bluetooth should be the same.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceConnect(char *pRemoteDevAddr)
{
	unsigned char ucRes;

	BTDeviceRoleSet(BT_ROLE_MASTER);
	ClearRecBuf();
	BTSendCmdString(BtCmdInitSppLib);
	ucRes = BTGetResponse();
	if((ucRes == BT_ERR_OK)||(ucRes == BT_ERR_SPP_REPEAT_INIT))
	{
		s_cCmdBuffer[0] = 0;
		StrCat(s_cCmdBuffer, BtCmdDevConnect);
		StrCat(s_cCmdBuffer, pRemoteDevAddr);
		BTSendCmdString(s_cCmdBuffer);
		return (BTGetResponse());
	}
	return ucRes;
}

//*****************************************************************************
//
//! \brief Auto connect to recently used remote bluetooth device
//!
//! \param None.
//!
//! This function is to Auto connect to recently used remote bluetooth device.
//! If the remote bluetooth device is power on and reachable and recently
//! connected, this function can automatically find and connect with the slave
//! device. It's only valid in master mode.
//!
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTAutoConnect()
{
	//
	// Address table which can store at most TEL0026_MAX_SCAN_DEVICES diferent
	// addresses.
	//
	char cDevAddrArray[TEL0026_MAX_SCAN_DEVICES*15]={""};
	unsigned char ucDevCnt = 0;
	unsigned char i;
	unsigned char ucRes;

	ucDevCnt = BTScanRemoteDevice(1, 12, 16, cDevAddrArray);

	for(i=0; i<ucDevCnt*15; i+=15)
	{
		//
		// Address convert
		//
		BTAddrConv(&cDevAddrArray[i]);

		//
		// Check if the address is in the authenticated device list.
		//
		ucRes = BTLocateAuthDevice(&cDevAddrArray[i]);
		if(ucRes == BT_ERR_OK)
		{
			ucRes = BTDeviceConnect(&cDevAddrArray[i]);
			if(ucRes == BT_ERR_OK)
				return BT_ERR_OK;
		}
	}
	return ucRes;
}
//*****************************************************************************
//
//! \brief Disconnect with remote device
//!
//! \param None
//!
//! This function is to cancel the connecting process with remote bluetooth device.
//! \note If two devices are already connected together, this function is invalid.
//! Since the commands are regarded as data after connected. The only way to
//! disconnect is one of the device power down or out of range.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTDeviceDisConnect(void)
{
	ClearRecBuf();
	BTSendCmdString(BtCmdDevDisConn);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Set PIO output level
//!
//! \param pPioBit Specifies the PIO bit(BT_PIO2 ~ BT_PIO7, BT_PIO10)
//! \param pLevel Specifies the PIO out put level(BT_PIO_LEVEL_HIGH, BT_PIO_LEVEL_LOW)
//!
//! This function is to Set PIO output level. Only PIO2~PIO7 and PIO10 are writable.
//!
//! \return Returns the result of operation.
//
//*****************************************************************************
tBtResult BTSingleIOControl(char *pPioBit, char *pLevel)
{
	ClearRecBuf();
	s_cCmdBuffer[0] = 0;
	StrCat(s_cCmdBuffer, BtCmdPIOOutSet);
	StrCat(s_cCmdBuffer, ",");
	StrCat(s_cCmdBuffer, pPioBit);
	StrCat(s_cCmdBuffer, ",");
	StrCat(s_cCmdBuffer, pLevel);
	BTSendCmdString(BtCmdDevDisConn);
	return (BTGetResponse());
}

//*****************************************************************************
//
//! \brief Waiting for bluetooth connect
//!
//! \param None.
//!
//! This function is to waiting for bluetooth connect(TEL0026 is in slave mode).
//!
//! \return none.
//
//*****************************************************************************
void BTWaitForConnect(void)
{
	unsigned char ucRes;

	ClearRecBuf();
	while(1)
	{
		ucRes = BTReadLine(s_cCmdBuffer);
		if(ucRes&&(!BTErrorDecode(s_cCmdBuffer)))
			break;
	}
}

//*****************************************************************************
//
//! \brief Initialization for TEL0026
//!
//! \param None.
//!
//! This function is to initialize TEL0026 bluetooth port.
//!
//! \return initialization result.
//
//*****************************************************************************
tBtResult BTInit(void)
{
	unsigned char ucRetry = 0;
	unsigned char ucRes = 1;
	UartInit( 38400, 0, 1);
	while(ucRes&&(ucRetry<10))
	{
		ucRes = BTTestOK();
		BTReadLine(s_cCmdBuffer);
		ucRetry++ ;
	}
	return ucRes;
}













