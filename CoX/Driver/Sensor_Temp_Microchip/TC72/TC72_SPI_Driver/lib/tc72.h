//*****************************************************************************
//
//! \file tc72.h
//! \brief Prototypes for the TC72 Driver.
//! \version V2.1.1.0
//! \date 10/20/2011
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
#ifndef __TC72_H__
#define __TC72_H__

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
//! \addtogroup Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Temperature_Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TC72
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TC72_SPI_Set TC72 SPI Connection
//! \brief Values that can be used in TC72Init(),Define SPIx as a port connecting
//! TC72 which can be configured,when you use a different SPI port you must
//! configure them again.
//! @{
//
//*****************************************************************************
//
//! Define SPIx as a port connecting TC72 which can be configured,when you use a
//! different SPI port you must them again.
//
#define TS_PIN_SPI_CLK          PC1
#define TS_PIN_SPI_MISO         PC2
#define TS_PIN_SPI_MOSI         PC3
#define TS_PIN_SPI_PORT         SPI0_BASE
  
//
//! Configure GPIOC.0 as chip Select
//
#define TS_PIN_SPI_CS           PC0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TC72_Mode_Set TC72 Convertion Mode
//! \brief TC72 Convertion Mode.
//! @{
//
//*****************************************************************************
  
//
//! Continuous mode,it can be used in TC72Configure().
//
#define TC72_MODE_CONTINUOUS    0x04
//
//! Shutdown mode,it can be used in TC72Configure().
//
#define TC72_MODE_SHUTDOWN      0x05
//
//! One-shot mode,it can be used in TC72Configure().
//    
#define TC72_MODE_ONESHOT       0x15

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TC72_Exported_APIs  TC72 Driver APIs
//! \brief API Refrence of TC72 Driver.
//! @{
//
//*****************************************************************************

extern void TC72Init(unsigned long ulSpiClock);
extern void TC72Configure(unsigned char ucMode);
extern short TC72TemperReadDec(void);
extern unsigned char TC72IDcodeGet(void);
extern short TC72TemperRead(void);
extern float TC72TemperReadFloat(void);
extern xtBoolean TC72IDCheck(void);
extern void TC72DeInit(void);
extern void TC72Disable(void);
extern unsigned char TC72ControlRegValGet(void);

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

#endif //__TC72_H__
