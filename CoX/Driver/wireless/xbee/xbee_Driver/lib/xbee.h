//*****************************************************************************
//
//! \file xbee.h
//! \brief Prototypes for the xbee Driver.
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
//!
//*****************************************************************************
#ifndef __XBEE_H__
#define __XBEE_H__

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
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup wireless
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup wireless_zigbee
//! @{
//
//*****************************************************************************

//*****************************************************************************

//*****************************************************************************
//! \addtogroup wireless_xbee_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup xbee_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define UART as a port connecting xbee which can be configured
//
#define	XBEE_UART               sUART_BASE
#define	XBEE_LOOPBACK           0
#define MAX_RX_BUFFER           256
#define COMMAND_DELAY           10000


//*****************************************************************************
//
//! UART Rx Buffer Definition definitions
//
//*****************************************************************************
typedef struct
{
    //
    //! Buffer
    //
	volatile char pcRxBuffer[MAX_RX_BUFFER];

    //
    //! Count
    //
 	volatile unsigned long ulRxCount;

    //
    //! Head of buffer
    //
	volatile unsigned long ulRxHead;

    //
    //! Tail Head of buffer
    //
	volatile unsigned long ulRxTail;

    //
    //! error
    //
	volatile unsigned long ulError;
}xBeeUART;


//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup COX_xbee_Exported_APIs
//! @{
//
//*****************************************************************************
extern void xBeeUartInit(void);
extern void xBeeUartSendBuf(unsigned char *pucBuf, unsigned long ulLength);

extern xtBoolean xBeeEnterCmdMode(void);
extern unsigned long xBeeNodeGet(void);
extern xtBoolean xBeeNodeConnect(unsigned char *pucBuf);

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__AT25FS0X_H__
