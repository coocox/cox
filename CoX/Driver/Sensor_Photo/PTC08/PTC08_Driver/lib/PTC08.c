//*****************************************************************************
//
//! \file PTC08.c
//! \brief Driver for digital thermometer PTC08.
//! \version V2.1.1.0
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
#include "xhw_ints.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "xcore.h"
#include "hw_PTC08.h"
#include "PTC08.h"


//*****************************************************************************
//
//! \brief Send a buffer to uart.
//!
//! \param ulBase is the base address of the UART port.
//! \param pucStr is the point of data will be sent.
//! \param ulLen is the lenth of data will be sent.
//!
//! Send a buffer to uart
//!
//! \return None
//
//*****************************************************************************
static void
UARTBufferPut(unsigned long ulBase, unsigned char *pucStr, unsigned long ulLen)
{
    unsigned long i;
    for(i=0; i<ulLen; i++)
    {
        xUARTCharPut(ulBase, *pucStr++);
    }	
}

//*****************************************************************************
//
//! \brief get data from UART.
//!
//! \param pucBuf is the point of data will be save.
//! \param ulLen is the lenth of data will be save.
//!
//! get data from UART.
//!
//! \return the lenth of data
//
//*****************************************************************************
static unsigned long 
UARTBufferGet(unsigned long ulBase, unsigned char *pucBuf, unsigned long  ulLen)
{
    unsigned long i = 0;
    for (i = 0; i < ulLen; i++)
    {
        pucBuf[i] = xUARTCharGet(ulBase);
    }	
    return ulLen;
}

//*****************************************************************************
//
//! \brief Initializes the PTC08 device.
//!
//! Initializes the PTC08 device,it will set the baud rate 115200,image size 
//! 320*240,ziprate 36 and non-save power.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean 
PTC08Init(void)
{
    //
    // Must wait for 2.5s before the camera can received Command
    //
    xSysCtlDelay(25000000); 
    
    if(!PTC08PhotoReset())
    {
        return xfalse;
    }
    if(!PTC08PhotoSizeSet(PTC08_SIZE_320_240))
    {
        return xfalse;
    }
    if(!PTC08ZipRateSet(0x36))
    {
        return xfalse;
    }
    xSysCtlDelay(10);
    
    if(!PTC08SavePowerSet(PTC08_SAVE_POWER_DIS))
    {
        return xfalse;
    } 
    if(!PTC08BaudRateSet(PTC08_BAUDRATE_115200))
    {
        return xfalse;
    } 
    xUARTConfigSet(PTC08_UART, 115200, (UART_CONFIG_WLEN_8 | 
                                        UART_CONFIG_STOP_ONE | 
                                        UART_CONFIG_PAR_NONE));
    return xtrue;
}

//*****************************************************************************
//
//! \brief Set the PTC08 save power or not.
//!
//! \param ucSavePower is save power or not save power.
//!
//! The \e ucSavePower parameter can be \b PTC08_SAVE_POWER_EN,  
//! \b PTC08_SAVE_POWER_DIS.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
PTC08SavePowerSet(unsigned char ucSavePower)
{
    unsigned long i;
    unsigned char ucTmp[5];
    
    //
    // Send Save Power Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucSavePowerCmd[0], 6);
    xUARTCharPut(PTC08_UART, ucSavePower);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 5)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (ucTmp[i] != ucSavePowerRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Set the photo's size.
//!
//! \param ucSize is the photo size.
//!
//! The \e ucSize parameter can be \b PTC08_SIZE_320_240,  
//! \b PTC08_SIZE_640_480.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
PTC08PhotoSizeSet(unsigned char ucSize)
{
    unsigned long i;
    unsigned char ucTmp[5];
    
    //
    // Send Save Power Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucPhotoSizeCmd[0], 8);
    xUARTCharPut(PTC08_UART, ucSize);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 5)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (ucTmp[i] != ucPhotoSizeRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Set the photo's zip rate.
//!
//! \param ucRate is the zip rate.
//!
//! The \e ucRate parameter can be : 0x00-0xFF.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
PTC08ZipRateSet(unsigned char ucRate)
{
    unsigned long i;
    unsigned char ucTmp[5];
    
    //
    // Send Save Power Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucSetZipRateCmd[0], 8);
    xUARTCharPut(PTC08_UART, ucRate &PTC08_ZIPRATE_MASK);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 5)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (ucTmp[i] != ucSetZipRateRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Set the PTC08's baud rate.
//!
//! \param pucBaudRate is the baudrate.
//!
//! The \e pucBaudRate parameter can be \b PTC08_BAUDRATE_9600,  
//! \b PTC08_BAUDRATE_19200,\b PTC08_BAUDRATE_38400,\b PTC08_BAUDRATE_57600 
//! and \b PTC08_BAUDRATE_115200.
//!
//! \return return xtrue if there is no error or return xfalse.
//
//*****************************************************************************
xtBoolean
PTC08BaudRateSet(unsigned char* pucBaudRate)
{
    unsigned long i;
    unsigned char ucTmp[5];
    
    //
    // Send Set baud rate Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucSetBaudRateCmd[0], 5);
    UARTBufferPut(PTC08_UART, pucBaudRate, 2);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 5)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (ucTmp[i] != ucSetBaudRateRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Start photo .
//!
//! Send Send start photo Command to PTC08 device.
//!
//! \return return xtrue if there is no error or return xfalse.
//
//*****************************************************************************
xtBoolean
PTC08PhotoStart(void)
{
    unsigned long i;
    unsigned char ucTmp[5];
    
    //
    // Send start photo Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucStartPhotoCmd[0], 5);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 5)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (ucTmp[i] != ucStartPhotoRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Stop photo of the PTC08 device.
//!
//! Send stop photo Command to PTC08 device,It used to clear buffer
//!
//! \return return xtrue if there is no error or return xfalse.
//
//*****************************************************************************
xtBoolean
PTC08PhotoStop(void)
{
    unsigned long i;
    unsigned char ucTmp[5];
    
    //
    // Send stop photo Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucStopPhotoCmd[0], 5);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 5)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (ucTmp[i] != ucStopPhotoRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Reset the PTC08 device.
//!
//! Send reset Command to the PTC08 device.
//!
//! \return return xtrue if there is no error or return xfalse.
//
//*****************************************************************************
xtBoolean
PTC08PhotoReset(void)
{
    unsigned long i;
    unsigned char ucTmp[4];
    
    //
    // Send Reset Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucResetCmd[0], 4);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 4)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 4; i++)
    {
        if (ucTmp[i] != ucResetRcv[i]) 
        {
            return xfalse;
        }
    }
    
    return xtrue;	
}

//*****************************************************************************
//
//! \brief Get the photo lenth of the PTC08.
//!
//! \param pucPhotoLen is the point that save the photo lenth.
//!
//! \return return xtrue if there is no error or return xfalse.
//
//*****************************************************************************
xtBoolean
PTC08PhotoLenGet(unsigned long* pucPhotoLen)
{
    unsigned long i;
    unsigned char ucTmp[9];
    
    //
    // Send Get the photo Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucReadLenCmd[0], 5);

    if (!UARTBufferGet(PTC08_UART, ucTmp, 9)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 7; i++)
    {
        if (ucTmp[i] != ucReadLenRcv[i]) 
        {
            return xfalse;
        }
    }
    *pucPhotoLen = (unsigned long)(ucTmp[7]) * 0x100 + ucTmp[8];
    
    return xtrue;
}

//*****************************************************************************
//
//! \brief Read the photo data from the PTC08 memory.
//!
//! \param pucBuffer is the point that data will be save.
//! \param ulAddr is the address of the PTC08 memory.
//! \param ulLen is the len of data will be read.
//!
//! \return return xtrue if there is no error or return xfalse.
//
//*****************************************************************************
xtBoolean 
PTC08PhotoDataGet(unsigned char* pucBuffer, unsigned long ulAddr,
                  unsigned long ulLen)
{
    unsigned long i;
    
    ucGetPhotoCmd[8] = ulAddr/256;
    ucGetPhotoCmd[9] = ulAddr%256;
    ucGetPhotoCmd[12] =ulLen/256;
    ucGetPhotoCmd[13] =ulLen%256;
    
    //
    // Send Read the photo data Command
    //
    UARTBufferPut(PTC08_UART, (unsigned char *)&ucGetPhotoCmd[0], 16);

    if (!UARTBufferGet(PTC08_UART, pucBuffer, 10+ulLen)) 
    {
        return xfalse;
    }
    
    //
    // verify data
    //
    for (i = 0; i < 5; i++)
    {
        if (pucBuffer[i] != ucGetPhotoRcv[i]) 
        {
            return xfalse;
        }
    }
    
    //
    // verify data
    //
    for (i = ulLen+5; i < ulLen+10; i++)
    {
        if (pucBuffer[i] != ucGetPhotoRcv[i]) 
        {
            return xfalse;
        }
    }

    return xtrue;
}