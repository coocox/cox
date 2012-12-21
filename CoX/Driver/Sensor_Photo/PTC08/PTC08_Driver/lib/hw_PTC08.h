//*****************************************************************************
// 
//! \file xhw_PTC08.h
//! \brief Macros used when accessing the PTC08 control hardware.
//! \version V2.1.1.0
//! \date 6. Nov. 2011
//! \author  CooCox
//!
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

#ifndef __XHW_PTC08_H__
#define __XHW_PTC08_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Sensor
//! @{
//
//*****************************************************************************
    
//*****************************************************************************
//
//! \addtogroup Photo_Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08_CMD  PTC08 Command
//! @{
//
//*****************************************************************************
//
//! PTC08 reset Command
//
unsigned char const ucResetCmd[] = 
{
    0x56,
    0x00,
    0x26,
    0x00
};

//
//! PTC08 reset received Command
//
unsigned char const ucResetRcv [] =
{ 
    0x76,
    0x00,
    0x26,
    0x00
};

//
//! PTC08 Start Photo Command
//
unsigned char const ucStartPhotoCmd [] =
{
    0x56,
    0x00,
    0x36,
    0x01,
    0x00
};

//
//! PTC08 Start Photo received Command
//
unsigned char const ucStartPhotoRcv [] =
{
    0x76,
    0x00,
    0x36,
    0x00,
    0x00
};

//
//! PTC08 read Photo lenth Command
//
unsigned char const ucReadLenCmd [] = 
{
    0x56,
    0x00,
    0x34,
    0x01,
    0x00
};

//
//! PTC08 read Photo lenth received Command
//! followed by one byte of data
//! last two byte is the Photo lenth
//
unsigned char const ucReadLenRcv [] =
{
    0x76,
    0x00,
    0x34,
    0x00,
    0x04
};

//
//! PTC08 read Photo data Command
//
unsigned char ucGetPhotoCmd [] =
{
    0x56,
    0x00,
    0x32, 
    0x0C, 
    0x00, 
    0x0A,
    
    0x00, 
    0x00, 
    0x00, 
    0x00,
    
    0x00, 
    0x00,
    0x00, 
    0x00,
    
    0x00,
    0x0A   
};

//
//! PTC08 read Photo data received Command
//
unsigned char const ucGetPhotoRcv [] =
{
    0x76,
    0x00,
    0x32,
    0x00,
    0x00
};

//
//! PTC08 set zip rate Command
//! followed by one byte of data
//! it can be 00 ----FF general 36
//
unsigned char const ucSetZipRateCmd [] =
{
    0x56,
    0x00, 
    0x31, 
    0x05,  
    0x01, 
    0x01, 
    0x12,
    0x04
};

//
//! PTC08 set zip rate received Command
//
unsigned char const ucSetZipRateRcv [] = 
{
    0x76,
    0x00,
    0x31,
    0x00,
    0x00
};

//
//! PTC08 stop taking photo Command
//
unsigned char const ucStopPhotoCmd [] =
{
    0x56,
    0x00,
    0x36,
    0x01,
    0x03
};

//
//! PTC08 stop taking photo received Command
//
unsigned char const ucStopPhotoRcv [] =
{
    0x76,
    0x00,
    0x36,
    0x00,
    0x00
};

//
//! PTC08 set photo size Command
//! followed by one byte of data
//! 11 320*240  00 640*480
//
unsigned char const ucPhotoSizeCmd [] =
{
    0x56,
    0x00, 
    0x31, 
    0x05,  
    0x04, 
    0x01, 
    0x00, 
    0x19
};

//
//! PTC08 set photo size received Command
//
unsigned char const ucPhotoSizeRcv [] =
{
    0x76, 
    0x00, 
    0x31, 
    0x00, 
    0x00
};

//
//! PTC08 set photo save power Command
//! followed by one byte of data
//! 01 save power  00 exit save power
//
unsigned char const ucSavePowerCmd [] =
{
    0x56, 
    0x00, 
    0x3E, 
    0x03, 
    0x00, 
    0x01
};

//
//! PTC08 set photo save power received Command
//
unsigned char const ucSavePowerRcv [] =
{
    0x76, 
    0x00, 
    0x3E, 
    0x00, 
    0x00
};

//
//! PTC08 set photo baud rate Command
//! followed by two byte of data
//!  AE C8 9600
//! 56 E4 19200
//! 2A F2 38400
//! 1C 4C 57600
//! 0D A6 115200
//! default is 38400
//
unsigned char const ucSetBaudRateCmd [] = 
{
    0x56,
    0x00, 
    0x24, 
    0x03, 
    0x01
};

//
//! PTC08 set photo baud rate received Command
//
unsigned char const ucSetBaudRateRcv [] = 
{
    0x76, 
    0x00, 
    0x24, 
    0x00, 
    0x00
};



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

#endif

















