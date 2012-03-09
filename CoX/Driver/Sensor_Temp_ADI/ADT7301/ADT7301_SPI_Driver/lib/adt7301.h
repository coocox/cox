//*****************************************************************************
//
//! \file adt7301.h
//! \brief Prototypes for the ADT7301 Driver.
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
#ifndef __ADT7301_H__
#define __ADT7301_H__

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
//! \addtogroup ADT7301
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup ADC7301_SPI_Set ADT7301 Configuration
//! \brief Values can be used in ADT7301Init(),Define SPIx as a port connecting
//! with ADC7301 which can be configured,when you use a different SPI port you 
//! must configure them again.
//! @{
//
//*****************************************************************************

#define ADT7301_PIN_SPI_CLK     PC1
#define ADT7301_SPI_CLK         SPI0CLK 
#define ADT7301_PIN_SPI_MISO    PC2
#define ADT7301_SPI_MISO        SPI0MISO
#define ADT7301_PIN_SPI_MOSI    PC3
#define ADT7301_SPI_MOSI        SPI0MOSI
  
#define ADT7301_PIN_SPI_PORT    SPI0_BASE

#define ADT7301_PIN_SPI_CS      PC0
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADT7301_Mode_Set ADT7301 Convertion Mode
//! \brief Values can be use to set and change ADT7301 temperature convertion mode, 
//! you can use ADT7301_MODE_SHUTDOWN if you want to enter power consumption condition.
//! And you can use ADT7301_MODE_NORMAL to switch condition from low power mode
//! to start temperature conversion.
//! @{
//
//*****************************************************************************
//
//! normal mode,it can be passed to ADT7301Configure().
//
#define ADT7301_MODE_NORMAL     0x0000
  
//
//! shutdown mode,it can be passed to ADT7301Configure().
//
#define ADT7301_MODE_SHUTDOWN   0x2000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup ADT7301_Exported_APIs  ADT7301 Driver APIs
//! \brief API Refrence of ADT7301 Driver.
//! @{
//
//*****************************************************************************
  
extern void ADT7301Init(unsigned long ulSpiClock);
extern void ADT7301Configure(unsigned short usMode);
extern short ADT7301TemperReadDec(void);
extern short ADT7301TemperRead(void);
extern float ADT7301TemperReadFloat(void);
extern void ADT7301DeInit(void);

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

#endif //__ADT7301_H__
