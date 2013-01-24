//*****************************************************************************
//
//! \file UC1701.h
//! \brief Prototypes for the uc1701 Driver.
//! \version V2.1.1.0
//! \date 1/15/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX 
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
#ifndef __UC1701_H__
#define __UC1701_H__
#include "hw_uc1701.h"
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
//! \addtogroup Displays
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup Text_Displays
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup UC1701
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup UC1701_Driver_Single UC1701 Single Driver
//! @{ 
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup UC1701_User_Config UC1701 User Config
//! @{
//
//*****************************************************************************
  
//
//! User write protect config,it can be UC1701_SPI_9BIT or UC1701_SPI_8BIT
//! UC1701_8080 UC1701_6800.
//
#define UC1701_INTERFACE        UC1701_SPI_8BIT

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup UC1701_Hardware_Config UC1701 Hardware Config
//! @{
//
//*****************************************************************************

//
//! Define SPIx as a port connecting uc1701 which can be configured
//
#define LCD_PIN_SPI_CLK         PD9
#define SPI_CLK                 SPI3CLK

#define LCD_PIN_SPI_MOSI        PD11
#define SPI_MOSI                SPI3MOSI
#define LCD_PIN_CD              PD10
#define LCD_PIN_RESET        PD12
#define LCD_PIN_SPI_PORT        SPI3_BASE
  
//
//! Configure GPIOD.8 as chip Select
//
#define LCD_PIN_SPI_CS          PD8
  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
// 
//! \addtogroup CoX_UC1701_Exported_APIs CoX UC1701 Exported APIs
//! @{
//
//*****************************************************************************
extern void UC1701Init(unsigned long ulSpiClock);
extern void UC1701DataWrite(unsigned char ucData);
extern void UC1701CmdWrite(unsigned char ucCmd);
extern void UC1701DoubleCmdWrite(unsigned char ucCmd, unsigned char ucData);
extern void UC1701AddressSet(unsigned char ucPA, unsigned char ucCA);
extern void UC1701Dispaly(unsigned char ucLine, unsigned char ucRow,
                          unsigned char ucAsciiWord);
extern void UC1701InverseDispaly(unsigned char ucLine, unsigned char ucRow,
                                 unsigned char ucAsciiWord);
extern void UC1701CharDispaly(unsigned char ucLine, unsigned char ucRow,
                              char *pcChar);
extern void UC1701ChineseDispaly(unsigned char ucLine, unsigned char ucRow,
                                 unsigned char ucLength, char *pcChar);
extern void UC1701DisplayN(unsigned char ucLine, unsigned char ucRow,
                            unsigned long n);
extern void UC1701Clear(void);
extern void UC1701InverseEnable(void);
extern void UC1701InverseDisable(void);
extern void UC1701AllPixelOnEnable(void);
extern void UC1701AllPixelOnDisable(void);
extern void UC1701DisplayOn(void);
extern void UC1701DisplayOff(void);
extern void UC1701ScrollLineSet(unsigned char ucLine);
extern void UC1701PMSet(unsigned char ucPM);
extern void UC1701BRSet(unsigned char ucBR);
extern void UC1701SegDirSet(unsigned char ucSegDir);
extern void UC1701ComDirSet(unsigned char ucComDir);

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

#endif //__UC1701_H__
