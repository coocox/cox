//*****************************************************************************
//
//! \file uc1601.h
//! \brief Prototypes for the uc1601 Driver.
//! \version V2.1.1.0
//! \date 9/22/2011
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
#ifndef __UC1601_H__
#define __UC1601_H__
#include "hw_uc1601.h"
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
//! \addtogroup COX_Driver_Lib
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
//! \addtogroup UC1601
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup UC1601_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup UC1601_User_Config
//! @{
//
//*****************************************************************************
  
//
//! User write protect config,it can be UC1601_SPI_9BIT or UC1601_SPI_8BIT 
//! UC1601_8080 UC1601_6800.
//
#define UC1601_INTERFACE        UC1601_SPI_9BIT 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup UC1601_Hardware_Config
//! @{
//
//*****************************************************************************

#if (UC1601_INTERFACE == UC1601_SPI_9BIT)

//
//! Define SPIx as a port connecting uc1601 which can be configured
//
#define LCD_PIN_SPI_CLK         PD9
#define SPI_CLK                 SPI3CLK  

#define LCD_PIN_SPI_MOSI        PD11
#define SPI_MOSI                SPI3MOSI
#define LCD_PIN_SPI_PORT        SPI3_BASE
  
//
//! Configure GPIOD.8 as chip Select
//
#define LCD_PIN_SPI_CS          PD8
  
//
//! Configure GPIOD.10 as chip reset
//
#define LCD_PIN_RST             PD10
  
#elif (UC1601_INTERFACE == UC1601_SPI_8BIT)

//
//! Define SPIx as a port connecting uc1601 which can be configured
//
#define LCD_PIN_SPI_CLK         PD9
#define SPI_CLK                 SPI3CLK  

#define LCD_PIN_SPI_MOSI        PD11
#define SPI_MOSI                SPI3MOSI
#define LCD_PIN_CD              PD10
#define LCD_PIN_SPI_PORT        SPI3_BASE
  
//
//! Configure GPIOD.8 as chip Select
//
#define LCD_PIN_SPI_CS          PD8
  

#elif (UC1601_INTERFACE == UC1601_I2C)

//
//! Define I2Cx as a port connecting uc1601 which can be configured
//
#define LCD_PIN_I2C_SCK         PA9
#define I2C_SCK                 I2C0SCK  

#define LCD_PIN_I2C_SDA         PA8
#define I2C_SDA                 I2C0SDA

#define LCD_PIN_I2C_PORT        I2C0_BASE
  
#elif (UC1601_INTERFACE == UC1601_8080)

//
//! Define GPIO as a port connecting uc1601 which can be configured
//
#define LCD_PIN_DATA0           PA0
#define LCD_PIN_DATA1           PA1 
#define LCD_PIN_DATA2           PA2
#define LCD_PIN_DATA3           PA3
#define LCD_PIN_DATA4           PA4
#define LCD_PIN_DATA5           PA5
#define LCD_PIN_DATA6           PA6
#define LCD_PIN_DATA7           PA7

#define LCD_PIN_CD              PA8
#define LCD_PIN_WR              PA9
#define LCD_PIN_RD              PA10
  
#define LCD_PIN_CS              PA11

#define LCD_PIN_DATA_OUT                                                      \
        do                                                                    \
        {                                                                     \
          xGPIOSPinDirModeSet(LCD_PIN_DATA0, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA1, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA2, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA3, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA4, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA5, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA6, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA7, xGPIO_DIR_MODE_OUT);             \
        }while(0)
#define LCD_PIN_DATA_IN                                                       \
        do                                                                    \
        {                                                                     \
          xGPIOSPinDirModeSet(LCD_PIN_DATA0, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA1, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA2, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA3, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA4, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA5, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA6, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA7, xGPIO_DIR_MODE_IN);              \
        }while(0)

#define LCD_DATA_OUT(Data)                                                    \
        do                                                                    \
        {                                                                     \
          xGPIOSPinWrite(LCD_PIN_DATA0, 1&Data);                              \
          xGPIOSPinWrite(LCD_PIN_DATA1, (Data&2)>>1);                         \
          xGPIOSPinWrite(LCD_PIN_DATA2, (Data&4)>>2);                         \
          xGPIOSPinWrite(LCD_PIN_DATA3, (Data&8)>>3);                         \
          xGPIOSPinWrite(LCD_PIN_DATA4, (Data&16)>>4);                        \
          xGPIOSPinWrite(LCD_PIN_DATA5, (Data&32)>>5);                        \
          xGPIOSPinWrite(LCD_PIN_DATA6, (Data&64)>>6);                        \
          xGPIOSPinWrite(LCD_PIN_DATA7, (Data&128)>>7);                       \
        }while(0)
        
#elif (UC1601_INTERFACE == UC1601_6800)

//
//! Define GPIO as a port connecting uc1601 which can be configured
//
#define LCD_PIN_DATA0           PA0
#define LCD_PIN_DATA1           PA1 
#define LCD_PIN_DATA2           PA2
#define LCD_PIN_DATA3           PA3
#define LCD_PIN_DATA4           PA4
#define LCD_PIN_DATA5           PA5
#define LCD_PIN_DATA6           PA6
#define LCD_PIN_DATA7           PA7

#define LCD_PIN_CD              PA8
#define LCD_PIN_RW              PA9
#define LCD_PIN_E               PA10
  
#define LCD_PIN_CS              PA11 
  
#define LCD_PIN_DATA_OUT                                                      \
        do                                                                    \
        {                                                                     \
          xGPIOSPinDirModeSet(LCD_PIN_DATA0, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA1, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA2, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA3, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA4, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA5, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA6, xGPIO_DIR_MODE_OUT);             \
          xGPIOSPinDirModeSet(LCD_PIN_DATA7, xGPIO_DIR_MODE_OUT);             \
        }while(0)
#define LCD_PIN_DATA_IN                                                       \
        do                                                                    \
        {                                                                     \
          xGPIOSPinDirModeSet(LCD_PIN_DATA0, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA1, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA2, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA3, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA4, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA5, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA6, xGPIO_DIR_MODE_IN);              \
          xGPIOSPinDirModeSet(LCD_PIN_DATA7, xGPIO_DIR_MODE_IN);              \
        }while(0)
  
#define LCD_DATA_OUT(Data)                                                    \
        do                                                                    \
        {                                                                     \
          xGPIOSPinWrite(LCD_PIN_DATA0, 1&Data);                              \
          xGPIOSPinWrite(LCD_PIN_DATA1, (Data&2)>>1);                         \
          xGPIOSPinWrite(LCD_PIN_DATA2, (Data&4)>>2);                         \
          xGPIOSPinWrite(LCD_PIN_DATA3, (Data&8)>>3);                         \
          xGPIOSPinWrite(LCD_PIN_DATA4, (Data&16)>>4);                        \
          xGPIOSPinWrite(LCD_PIN_DATA5, (Data&32)>>5);                        \
          xGPIOSPinWrite(LCD_PIN_DATA6, (Data&64)>>6);                        \
          xGPIOSPinWrite(LCD_PIN_DATA7, (Data&128)>>7);                       \
        }while(0)
#endif

  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup COX_UC1601_Exported_APIs
//! @{
//
//*****************************************************************************
extern void UC1601Init(unsigned long ulSpiClock);
extern void UC1601DataWrite(unsigned char ucData);
extern void UC1601CmdWrite(unsigned char ucCmd);
extern void UC1601DoubleCmdWrite(unsigned char ucCmd, unsigned char ucData);
extern void UC1601AddressSet(unsigned char ucPA, unsigned char ucCA);
extern void UC1601Dispaly(unsigned char ucLine, unsigned char ucRow, 
                          unsigned char ucAsciiWord);
extern void UC1601InverseDispaly(unsigned char ucLine, unsigned char ucRow, 
                                 unsigned char ucAsciiWord);
extern void UC1601CharDispaly(unsigned char ucLine, unsigned char ucRow, 
                              char *pcChar);
extern void UC1601ChineseDispaly(unsigned char ucLine, unsigned char ucRow, 
                                 unsigned char ucLength, char *pcChar);
extern void HD44780DisplayN(unsigned char ucLine, unsigned char ucRow, 
                            unsigned long n);
extern void UC1601Clear(void);
extern void UC1601InverseEnable(void);
extern void UC1601InverseDisable(void);
extern void UC1601AllPixelOnEnable(void);
extern void UC1601AllPixelOnDisable(void);
extern void UC1601DisplayOn(void);
extern void UC1601DisplayOff(void);
extern void UC1601ScrollLineSet(unsigned char ucLine);
extern void UC1601PMSet(unsigned char ucPM);
extern void UC1601CENSet(unsigned char ucCEN);
extern void UC1601DSTSet(unsigned char ucDST);
extern void UC1601DENSet(unsigned char ucDEN);





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

#endif //__UC1601_H__