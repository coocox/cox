//*****************************************************************************
// 
//! \file PTC08.h
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

#ifndef __PTC08_H__
#define __PTC08_H__

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
//! \addtogroup PTC08_Config PTC08 Driver config
//! \brief Configurtions befor use PTC08 Driver.
//! 
//! @{
//
//*****************************************************************************

//
//! PTC08 config
//
#define PTC08_UART              xUART1_BASE
#define PTC08_PIN_UART_TX       PA0
#define PTC08_UART_TX           UART1TX
#define PTC08_PIN_UART_RX       PA1
#define PTC08_UART_RX           UART1RX
#define PTC08_UART_GPIO         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08_Config PTC08 Driver baud rate
//! \brief Configurtions baud rate when use PTC08BaudRateSet.
//! 
//! @{
//
//*****************************************************************************

//
//! PTC08 photo baud rate 9600
//
#define PTC08_BAUDRATE_9600     "0xAE,0xC8"

//
//! PTC08 photo baud rate 19200
//
#define PTC08_BAUDRATE_19200    "0x56,0xE4"

//
//! PTC08 photo baud rate 38400
//
#define PTC08_BAUDRATE_38400    "0x2A,0xF2"

//
//! PTC08 photo baud rate 57600
//
#define PTC08_BAUDRATE_57600    "0x1C,0x4C"

//
//! PTC08 photo baud rate 115200
//
#define PTC08_BAUDRATE_115200   "0x0D,0xA6"

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08_Config PTC08 Driver zip rate
//! \brief Configurtions zip rate when use PTC08ZipRateSet.
//! 
//! @{
//
//*****************************************************************************

//
//! PTC08 photo zip rate mask
//
#define PTC08_ZIPRATE_MASK      0xFF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08_Config PTC08 Driver photo size
//! \brief Configurtions photo size when use PTC08PhotoSizeSet.
//! 
//! @{
//
//*****************************************************************************

//
//! PTC08 photo size is 320*240
//
#define PTC08_SIZE_320_240      0x11

//
//! PTC08 photo size is 320*240
//
#define PTC08_SIZE_640_480      0x00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08_Config PTC08 Driver svae power
//! \brief Configurtions svae power when use PTC08SavePowerSet.
//! 
//! @{
//
//*****************************************************************************

//
//! PTC08 photo svae power enable
//
#define PTC08_SAVE_POWER_EN     0x01

//
//! PTC08 photo svae power disable
//
#define PTC08_SAVE_POWER_DIS    0x00

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
//! \addtogroup PTC08_Exported_CMDs  PTC08 Driver CMDs
//! \brief CMDs of PTC08 Driver.
//! @{
//
//*****************************************************************************
extern unsigned char const ucSetBaudRateRcv [];
extern unsigned char const ucSetBaudRateCmd [];
extern unsigned char const ucSavePowerRcv [];
extern unsigned char const ucSavePowerCmd [];
extern unsigned char const ucPhotoSizeRcv [];
extern unsigned char const ucPhotoSizeCmd [];
extern unsigned char const ucStopPhotoRcv [];
extern unsigned char const ucStopPhotoCmd [];
extern unsigned char const ucSetZipRateRcv [];
extern unsigned char const ucSetZipRateCmd [];
extern unsigned char const ucGetPhotoRcv [];
extern unsigned char ucGetPhotoCmd [];
extern unsigned char const ucReadLenRcv [];
extern unsigned char const ucReadLenCmd [];
extern unsigned char const ucStartPhotoRcv [];
extern unsigned char const ucStartPhotoCmd [];
extern unsigned char const ucResetRcv [];
extern unsigned char const ucResetCmd[];

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PTC08_Exported_APIs  PTC08 Driver APIs
//! \brief API Reference of PTC08 Driver.
//! @{
//
//*****************************************************************************
extern xtBoolean PTC08Init(void);
extern xtBoolean PTC08SavePowerSet(unsigned char ucSavePower);
extern xtBoolean PTC08PhotoSizeSet(unsigned char ucSize);
extern xtBoolean PTC08ZipRateSet(unsigned char ucRate);
extern xtBoolean PTC08BaudRateSet(unsigned char* pucBaudRate);
extern xtBoolean PTC08PhotoStart(void);
extern xtBoolean PTC08PhotoStop(void);
extern xtBoolean PTC08PhotoLenGet(unsigned long* pucPhotoLen);
extern xtBoolean PTC08PhotoReset(void);
extern xtBoolean PTC08PhotoDataGet(unsigned char* pucBuffer,
                                   unsigned long ulAddr,
                                   unsigned long ulLen);

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
















