//*****************************************************************************
//
//! \file CAT93Cx6.c
//! \brief Driver for EEPROM CAT93Cx6.
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
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "CAT93Cx6.h"

//*****************************************************************************
//
//! \brief Initialize the CAT93Cx6's pins and state.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
CAT93Cx6_Init(void)
{
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CAT93Cx6_CS));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CAT93Cx6_SCK));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CAT93Cx6_DI));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CAT93Cx6_DO));
	xGPIOSPinTypeGPIOOutput(CAT93Cx6_CS);
	xGPIOSPinTypeGPIOOutput(CAT93Cx6_SCK);
	xGPIOSPinTypeGPIOOutput(CAT93Cx6_DI);
	xGPIOSPinTypeGPIOInput(CAT93Cx6_DO);
	xGPIOSPinWrite(CAT93Cx6_CS, 0);
	xGPIOSPinWrite(CAT93Cx6_SCK, 0);
	xGPIOSPinWrite(CAT93Cx6_DI, 0);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
}

//*****************************************************************************
//
//! \brief Send a data to CAT93Cx6.
//!
//! \param dat is going to be the input data.
//! \param ucShift is the bits of the input data.
//!
//! \return None.
//
//*****************************************************************************
void 
CAT93Cx6_SendData(unsigned long dat, unsigned char ucShift)
{
    unsigned char ucTemp;
	dat = dat << (16 - ucShift);
	for(ucTemp = 0; ucTemp < ucShift; ucTemp++)
	{
        if(dat & 0x8000)
		{
            xGPIOSPinWrite(CAT93Cx6_DI, 1);
		}
		else
		{
            xGPIOSPinWrite(CAT93Cx6_DI, 0);
		}
        xGPIOSPinWrite(CAT93Cx6_SCK, 1);
		xGPIOSPinWrite(CAT93Cx6_SCK, 0);
		dat <<= 1;
	}
}

//*****************************************************************************
//
//! \brief Open CAT93Cx6 programming enable.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
CAT93Cx6_ProgrammOpen(void)
{
    unsigned char ucTemp;
    xGPIOSPinWrite(CAT93Cx6_CS, 0);
	CAT93Cx6_SendData(0x04, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(0x30, ucTemp);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
}

//*****************************************************************************
//
//! \brief Close CAT93Cx6 programming.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
CAT93Cx6_ProgrammClose(void)
{
    unsigned char ucTemp;
    xGPIOSPinWrite(CAT93Cx6_CS, 0);
	CAT93Cx6_SendData(0x04, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(0x00, ucTemp);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
}

//*****************************************************************************
//
//! \brief read a data form from its corresponding address.
//!
//! \param ulAddress is to be read address.
//!
//! \return Returns the reading data.
//
//*****************************************************************************
unsigned long 
CAT93Cx6_ReadFromAddress(unsigned long ulAddress)
{
    unsigned char ucTemp;
	unsigned long ulVal = 0;
	
	xGPIOSPinWrite(CAT93Cx6_CS, 0);
	
    CAT93Cx6_SendData(0x06, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(ulAddress, ucTemp);
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X16)	
	for(ucTemp = 0; ucTemp < 16; ucTemp++)
#elif (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    for(ucTemp = 0; ucTemp < 8; ucTemp++)
#endif
	{
	    ulVal <<= 1;
		xGPIOSPinWrite(CAT93Cx6_SCK, 1);
		xGPIOSPinWrite(CAT93Cx6_SCK, 0);
		if(xGPIOSPinRead(CAT93Cx6_DO))
		{
            ulVal |= 0x01;
		}	
	}
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
	
	return ulVal;
}

//*****************************************************************************
//
//! \brief Write a data to CAT93Cx6.
//!
//! \param ulAddress is going to write to a address.
//! \param dat is to want to write data.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char 
CAT93Cx6_WriteToAddress(unsigned long ulAddress, unsigned long dat)
{
    unsigned char ucTemp = 1;
	unsigned long ulDelay;
	
	CAT93Cx6_ProgrammOpen();
	xGPIOSPinWrite(CAT93Cx6_CS, 0);
	CAT93Cx6_SendData(0x05, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(ulAddress, ucTemp);
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X16)	
	CAT93Cx6_SendData(dat, 0x10);
#elif (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    CAT93Cx6_SendData(dat, 0x08);
#endif
    xGPIOSPinWrite(CAT93Cx6_CS, 0);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
	
	ulDelay = 50000;
	while(!xGPIOSPinRead(CAT93Cx6_DO))
	{
	    ulDelay -= 1;
		if(ulDelay == 0)
		{
            ucTemp = 0;
            break;			
		}
	}
	CAT93Cx6_ProgrammClose();
	
	return ucTemp;
}

//*****************************************************************************
//
//! \brief Erase CAT93Cx6.
//!
//! \param ulAddress is necessary to wipe out the address.
//!
//! \return Returns \b true if erase successful and \b false if it is not..
//
//*****************************************************************************
unsigned char 
CAT93Cx6_EraseToAddress(unsigned long ulAddress)
{
    unsigned char ucTemp = 1;
	unsigned long ulDelay;
	
	CAT93Cx6_ProgrammOpen();
	xGPIOSPinWrite(CAT93Cx6_CS, 0);
	CAT93Cx6_SendData(0x07, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(ulAddress, ucTemp);
    xGPIOSPinWrite(CAT93Cx6_CS, 0);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
	
	ulDelay = 50000;
	while(!xGPIOSPinRead(CAT93Cx6_DO))
	{
	    ulDelay -= 1;
		if(ulDelay == 0)
		{
            ucTemp = 0;
            break;			
		}
	}
	CAT93Cx6_ProgrammClose();
	
	return ucTemp;
}

//*****************************************************************************
//
//! \brief Erase all CAT93Cx6.
//!
//! \param None.
//!
//! \return Returns \b true if erase successful and \b false if it is not..
//
//*****************************************************************************
unsigned char 
CAT93Cx6_EraseToAll(void)
{
    unsigned char ucTemp;
	unsigned long ulDelay;
	
	CAT93Cx6_ProgrammOpen();
	xGPIOSPinWrite(CAT93Cx6_CS, 0);
	CAT93Cx6_SendData(0x04, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(0x20, ucTemp);
    xGPIOSPinWrite(CAT93Cx6_CS, 0);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
	
	ulDelay = 50000;
	ucTemp = 1;
	while(!xGPIOSPinRead(CAT93Cx6_DO))
	{
	    ulDelay -= 1;
		if(ulDelay == 0)
		{
            ucTemp = 0;
            break;			
		}
	}
	CAT93Cx6_ProgrammClose();
	
	return ucTemp;
}

//*****************************************************************************
//
//! \brief Write all CAT93Cx6.
//!
//! \param dat is to want to write data.
//!
//! \return Returns \b true if write successful and \b false if it is not.
//
//*****************************************************************************
unsigned char 
CAT93Cx6_WriteToAll(unsigned long dat)
{
    unsigned char ucTemp;
	unsigned long ulDelay;
	
	CAT93Cx6_ProgrammOpen();
	xGPIOSPinWrite(CAT93Cx6_CS, 0);
	CAT93Cx6_SendData(0x04, 0x03);
#if (CAT93Cx6_DEVICE == CAT93C46)
    ucTemp = 0x06;
#elif (CAT93Cx6_DEVICE == CAT93C56)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C66)
    ucTemp = 0x08;
#elif (CAT93Cx6_DEVICE == CAT93C57)
    ucTemp = 0x07;
#elif (CAT93Cx6_DEVICE == CAT93C86)
    ucTemp = 0x0A;
#endif
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    ucTemp += 1;
#endif
    CAT93Cx6_SendData(0x10, ucTemp);
#if (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X16)	
	CAT93Cx6_SendData(dat, 0x10);
#elif (CAT93Cx6_REGISTER_ORGANIZE == CAT93Cx6_REGISTER_X8)
    CAT93Cx6_SendData(dat, 0x08);
#endif	
    xGPIOSPinWrite(CAT93Cx6_CS, 0);
	xGPIOSPinWrite(CAT93Cx6_CS, 1);
	
	ulDelay = 50000;
	ucTemp = 1;
	while(!xGPIOSPinRead(CAT93Cx6_DO))
	{
	    ulDelay -= 1;
		if(ulDelay == 0)
		{
            ucTemp = 0;
            break;			
		}
	}
	CAT93Cx6_ProgrammClose();
	
	return ucTemp;
}
