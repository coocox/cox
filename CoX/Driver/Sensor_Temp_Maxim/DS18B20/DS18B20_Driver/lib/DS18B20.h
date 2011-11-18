//*****************************************************************************
// 
//! \file DS18B20.h
//! \brief Macros used when accessing the DS18B20 control hardware.
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

#ifndef __DS18B20_H__
#define __DS18B20_H__

//*****************************************************************************
//
//! \addtogroup COX_Driver_Lib
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
//! \addtogroup Sensor_Temp
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DS18B20
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DS18B20_Config DS18B20 Driver Config
//! \brief Configurtions something before using this driver.
//! 
//! @{
//
//*****************************************************************************

#define DS18B20_SEARCH_ROM_EN   1


//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup DS18B20_Device DS18B20 Driver Device
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//! @{
//
//*****************************************************************************

//#define DS18B20_PIN_DIO         PA0
typedef struct 
{
    //
    //! DS18B20 DIO port
    // 
    unsigned long ulPort;     
    //
    //! DS18B20 DIO pin
    // 
    unsigned long ulPin;
    
    //
    //! Init the DS18B20 pin function
    //! Enable the pin corresponding peripheral
    //
    void (*PinSet)(void);
    
    //
    //! DS18B20 ROM
    // 
    unsigned char ucROM[8]; 
} 
tDS18B20Dev;


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DS18B20_Bit_Config DS18B20 Thermometer Resolution Configuration
//! @{
//
//*****************************************************************************
//
//! DS18B20 9 Bits MAX CONVERSION TIME is 93.75ms (tCONV/8)
// 
#define DS18B20_9BIT            0x1F
//
//! DS18B20 10 Bits MAX CONVERSION TIME is 187.5ms (tCONV/4)
// 
#define DS18B20_10BIT           0x3F
//
//! DS18B20 11 Bits MAX CONVERSION TIME is 375ms (tCONV/2)
// 
#define DS18B20_11BIT           0x5F
//
//! DS18B20 12 Bits MAX CONVERSION TIME is 750ms (tCONV)
// 
#define DS18B20_12BIT           0x7F


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DS18B20_Exported_APIs  DS18B20 Driver APIs
//! \brief API Reference of DS18B20 Driver.
//! @{
//
//*****************************************************************************
extern void DS18B20Init(tDS18B20Dev *psDev);
extern xtBoolean DS18B20Reset(tDS18B20Dev *psDev);
extern void DS18B20ROMRead(tDS18B20Dev *psDev);
extern void DS18B20ROMMatch(tDS18B20Dev *psDev);
extern void DS18B20ROMSkip(tDS18B20Dev *psDev);
extern void DS18B20AlarmSearch(tDS18B20Dev *psDev);
#if (DS18B20_SEARCH_ROM_EN > 0)
extern xtBoolean DS18B20ROMSearch(tDS18B20Dev *psDev);
extern xtBoolean DS18B20Verify(tDS18B20Dev *psDev);
extern void DS18B20TargetSetup(tDS18B20Dev *psDev, unsigned char ucFamily);
extern void DS18B20FamilySkipSetup(tDS18B20Dev *psDev, unsigned char ucFamily);
#endif
extern void DS18B20TempConvert(tDS18B20Dev *psDev);
extern void DS18B20ScratchpadCopy(tDS18B20Dev *psDev);
extern void DS18B20ScratchpadSet(tDS18B20Dev *psDev, char cHigh, char cLow,
                                 unsigned char ucBitConfig);
extern void DS18B20TempRead(tDS18B20Dev *psDev, float *pfTemp);
extern void DS18B20ScratchpadRead(tDS18B20Dev *psDev, unsigned char *pucTemp);
extern void DS18B20EEROMRecall(tDS18B20Dev *psDev);
extern xtBoolean DS18B20PowerSupplyRead(tDS18B20Dev *psDev);


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

#endif

















