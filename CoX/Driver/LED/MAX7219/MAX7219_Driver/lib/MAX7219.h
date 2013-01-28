//*****************************************************************************
//
//! \file MAX7219.h
//! \brief Prototypes for the MAX7219 Driver.
//! \version V2.1.1.0
//! \date 6/1/2012
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
#ifndef __MAX7219_H__
#define __MAX7219_H__

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
//! \addtogroup LED
//! @{
//! \addtogroup SPI_Seven_Segment
//! @{
//! \addtogroup MAX7219
//! @{
//! \addtogroup MAX7219_Driver
//! @{
//
//*****************************************************************************


//*****************************************************************************
//! \addtogroup MAX7219_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define SPI as a port connecting MAX7219 which can be configured
//
#define	MAX7219_PIN_SPI_SCK         PC1
#define	MAX7219_SPI_SCK                 SPI0CLK
#define	MAX7219_PIN_SPI_DIN          PC3
#define	MAX7219_SPI_DIN       			SPI0MOSI
#define	MAX7219_PIN_SPI_CS            PC0
#define	MAX7219_SPI_CS      			    SPI0CS
#define MAX7219_SPI_PORT    		    SPI0_BASE
#define MAX7219_SPI_GPIO     		    GPIO_PORTC_BASE

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup MAX7219_Control_Address
//! @{
//
//*****************************************************************************
#define MAX7219_DECODE_MODE_ADDR        0x09
#define MAX7219_INTENSITY_ADDR                 0x0A
#define MAX7219_SCAN_LIMIT_ADDR              0x0B
#define MAX7219_SHUTDOWN_ADDR              0x0C
#define MAX7219_TEST_ADDR                            0x0F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup COX_MAX7219_Exported_APIs
//! @{
//
//*****************************************************************************
extern void MAX7219_Init(void);
extern void MAX7219_Write(unsigned char ctlByte,
										unsigned char ucdata);
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
//! @}
//! @}
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

#endif //__MAX7219_H__
