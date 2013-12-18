//*****************************************************************************
//
//! \file BluetoothBee.h
//! \brief prototype for TL0026 Arduino Bluetooth Bee driver.
//! \version V2.2.1.0
//! \date 3/5/2013
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
#ifndef __TEL0026_H__
#define __TEL0026_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//! \addtogroup Wireless
//! @{
//
//! \addtogroup Bluetooth
//! @{
//
//! \addtogroup TEL0026
//! @{
//
//! \addtogroup TEL0026_Driver_Single
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup TEL0026_User_Config
//! @{
//
//*****************************************************************************
#define TEL0026_PIN_RXD            PD6
#define TEL0026_PIN_TXD            PD5
#define TEL0026_UART_BASE          xUART2_BASE
#define TEL0026_UART_TX            UART2TX
#define TEL0026_UART_RX            UART2RX
#define TEL0026_UART_INT           INT_USART2

#define TEL0026_TIMEOUT_SHORT      100000
#define TEL0026_TIMEOUT_LONG       5000000
#define TEL0026_DEFAULT_BAUDRATE   38400

#define TEL0026_MAX_SCAN_DEVICES   4
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup TEL0026_Const_Values
//! @{
//
//*****************************************************************************
#define TEL0026_OK                 0
#define TEL0026_ERROR              1

#define TEL0026_PARITY_NONE        0
#define TEL0026_PARITY_ODD         1
#define TEL0026_PARITY_EVEN        2
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
typedef unsigned char tBtResult;
//*****************************************************************************
//! \addtogroup TEL0026_Export_APIs
//! \note All the functions start with BT are only valid when the bluetooth are
//! not connected. If TEL0026 is connected with other device, AT commands will be
//! invalid and related function invoking may always return error or time out.
//! all the settings are stored into TEL0026 and will not lose even power down.
//! @{
//
//*****************************************************************************
extern char StrCmp(const char *pStr1, const char *pStr2);
extern unsigned char StrCat(char *pDest, const char *pSource);
extern char * Num2Str(unsigned long ulNum, char *pDest, unsigned char ucDigitType);
extern unsigned short RecBufReadBytes(unsigned short usLength, unsigned char *pData);
extern unsigned char BTReadLine(char *pData);
extern void ClearRecBuf(void);
extern void BTSendBytes(unsigned long ulLength, unsigned char *pData);
extern void BTSendCmdString(const char *pStr);
extern tBtResult BTGetResponse(void);
extern tBtResult BTTestOK(void);
extern tBtResult BTUartParamSet(unsigned long ulBaudRate,
		unsigned char ucParity, unsigned char StopBit);
extern tBtResult BTUartParamGet(char *pParam);
extern tBtResult BTPasswordSet(char *pPswd);
extern tBtResult BTPasswordGet(char *pPswd);
extern tBtResult BTDeviceNameSet(char *pName);
extern tBtResult BTDeviceNameGet(char *pName);
extern tBtResult BTRestore(void);
extern tBtResult BTVersionGet(char *pBuf);
extern tBtResult BTDeviceRoleSet(char cRoleMode);
extern unsigned char BTDeviceRoleGet(void);
extern tBtResult BTDeviceTypeSet(unsigned long ulDevClass);
extern tBtResult BTDeviceTypeGet(char *pType);
extern tBtResult BTInqModeSet(unsigned char ucMode, unsigned char ucMaxDevs,
		unsigned char ucTimeOut);
extern tBtResult BTInqModeGet(char *pBuf);
extern tBtResult BTStatusGet(char *pBuf);
extern tBtResult BTDeviceAddrGet(char *pBuf);
extern tBtResult BTRemoteDeviceNameGet(char *pRemoDevAddr, char *pRemoDevName);
extern unsigned char BTScanRemoteDevice(unsigned char ucInqMode, unsigned char ucMaxDevNum,
		unsigned char ucMaxTimeOut, char *ucRemoteDevAddr);
extern tBtResult BTInqCancle(void);
extern tBtResult BTPairing(char *pRemoteDevAddr, unsigned char ucTimeOut);
extern tBtResult BTLocateAuthDevice(char *pDevAddr);
extern tBtResult BTDeviceConnect(char *pRemoteDevAddr);
extern tBtResult BTDeviceDisConnect(void);
extern tBtResult BTAutoConnect(void);
extern tBtResult BTSingleIOControl(char *pPioBit, char *pLevel);
extern void BTWaitForConnect(void);
extern tBtResult BTInit(void);
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
}
#endif

#endif
