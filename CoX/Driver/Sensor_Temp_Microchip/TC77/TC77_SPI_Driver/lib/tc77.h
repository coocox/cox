//*****************************************************************************
//
//! \file tc77.h
//! \brief Prototypes for the TC77 Driver.
//! \version V2.1.1.0
//! \date 9/1/2011
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
#ifndef __TC77_H__
#define __TC77_H__

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
//! \addtogroup TC77
//! @{
//
//*****************************************************************************

  
//*****************************************************************************
//
//! \addtogroup TC77_SPI_Set TC77 Configuration 
//! \brief Values can be used in Tc77Init(),Define SPIx as a port connecting
//! TC77 which can be configured,when you use a different SPI port you should
//! configure them again.
//! @{
//
//*****************************************************************************

#define TC77_PIN_SPI_CLK        PC1
#define TC77_SPI_CLK            SPI0CLK 
#define TC77_PIN_SPI_MISO       PC2
#define TC77_SPI_MISO           SPI0MISO
#define TC77_PIN_SPI_MOSI       PC3  
#define TC77_SPI_MOSI           SPI0MOSI
  
#define TC77_PIN_SPI_PORT       SPI0_BASE

#define TC77_PIN_SPI_CS           PC0
 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TC77_Mode_Set TC77 Convertion Mode
//! \brief Values can be use to set and change TC77 temperature convertion mode, 
//! you can use TC77_MODE_SHUTDOWN if you want to enter power consumption condition.
//! And you can use TC77_MODE_CONTINUOUS to switch condition from low power mode
//! to start temperature conversion.
//! @{
//
//*****************************************************************************  
//
//! Continuous conversion mode, it is can be used in TC77Configure().
//
#define TC77_MODE_CONTINUOUS    0x0000
  
//
//! Shutdown mode, it is can be used in TC77Configure().
//
#define TC77_MODE_SHUTDOWN      0xFFFF

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup TC77_Exported_APIs  TC77 Driver APIs
//! \brief API Refrence of TC77 Driver.
//! @{
//
//*****************************************************************************

extern void TC77Init(unsigned long ulSpiClock);
extern void TC77Configure(unsigned short usMode);
extern short TC77TemperReadDec(void);
extern unsigned short TC77IDcodeGet(void);
extern short TC77TemperRead(void);
extern float TC77TemperReadFloat(void);
extern xtBoolean TC77Overflow(void);
extern xtBoolean TC77IDCheck(void);
extern void TC77DeInit(void);

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

#endif //__TC77_H__
