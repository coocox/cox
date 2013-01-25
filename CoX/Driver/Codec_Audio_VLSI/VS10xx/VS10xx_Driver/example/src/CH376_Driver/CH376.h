//*****************************************************************************
//
//! \file CH376.h
//! \brief header file of hardware layer driver for CH376
//!        Configure this file to apply this driver to your application
//! \version V2.1.1.0
//! \date 1/5/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX All rights reserved.
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

#ifndef	__CH376_H__
#define __CH376_H__

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
//! \addtogroup USB
//! @{
//! \addtogroup USB File Management Controller
//! @{
//! \addtogroup CH376
//! @{
//! \addtogroup CH376_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_User_Config
//! CH376 Interface Configure
//! @{
//
//*****************************************************************************

//
//! Select device CH376S or CH376T(Only CH376S supports parallel communication port)
//
//#define CH376X_DEVICE CH376T
#define CH376X_DEVICE CH376S

//
//! Select communication interface according to your hardware
//! When CH376 powered up, it will sample WR, RD, PCS, A0, RXD, TXD pins.
//! CH376 will work in different mode according to these pins combination.
//! The combinations and working mode are defined as follow(x represents
//! don't care electric level)
//! WR	RD	PCS	 A0	 RXD  TXD  interface type
//! 0	0	1	 1	 1	  1    SPI
//! 1	1	1	 1	 1	  1    UART
//! 1	1/x 1/x	 x	 1	  0    PARALLEL
//! others                     CH376 do not work
//!
//! This driver implements SPI and parallel communication interface driver
//

#define CH376_USE_HARDWARE_SPI
//#define CH376_USE_SOFTWARE_SPI
//#define CH376_USE_PARALLEL

//
//! Define CH376_INT_WIRE to get interrupt signal.
//! CH376_INT_WIRE and CH376_SPI_SDO_INT are only used in SPI mode,
//! and only one of them need to be defined.
//! If use hardware SPI, it's suggested to use CH376_INT_WIRE rather than CH376_SPI_SDO_INT.
//! If use CH376_SPI_SDO_INT, CH376 can set SPI's SDO(MISO) pin as interrupt out put line,
//! so CH376_INT_WIRE is not needed and by this way it can reduce one pin,
//! this is a good choice when your board doesn't have enough GPIOs
//!
//! ATTENTION: although the wire is called INT WIRE, the MCU do not respond to interrupt.
//! Instead,MCU will querying related pin's level to get status of CH376
//
#define CH376_INT_WIRE
//#define CH376_SPI_SDO_INT


//
//! specify interrupt input pin of MCU
//
#ifdef CH376_INT_WIRE
#define CH376_INT_PORT     xGPIO_PORTC_BASE
#define CH376_INT_PIN      PC0
#endif

//
//! specify hardware spi interface and pins
//
#ifdef CH376_USE_HARDWARE_SPI

//
//! CH376 support up to 24MHz clock rate in spi mode
//
#define CH376_CLK_FREQ	       4500000
#define CH376_SPI_PORT         SPI1_BASE
#define CH376_SCK              PA5
#define CH376_MISO             PA6
#define CH376_MOSI             PA7
#define CH376SPI_CLK           SPI1CLK(APP)
#define CH376SPI_MOSI          SPI1MOSI(APP)
#define CH376SPI_MISO          SPI1MISO(FIN)
#define CH376_SPI_CS_PORT      xGPIO_PORTA_BASE
#define CH376_SPI_CS_PIN       PA1

#endif

//
//! specify software spi interface and pins
//
#ifdef CH376_USE_SOFTWARE_SPI
#define CH376_SPI_INT
//#define CH376_SCK_PORT		    xGPIO_PORTA_BASE
#define CH376_SCK_PIN           PA5
//#define CH376_MISO_PORT         xGPIO_PORTA_BASE
#define CH376_MISO_PIN		    PA6
//#define CH376_MOSI_PORT         xGPIO_PORTA_BASE
#define CH376_MOSI_PIN		    PA7
//#define CH376_SPI_CS_PORT       GPIOA_BASE
#define CH376_SPI_CS_PIN        PA1
#endif

//
//! Only CH376S has parallel interface, specify parallel interface and pins
//
#if(CH376X_DEVICE == CH376S)
#ifdef CH376_USE_PARALLEL
#define CH376_WR_PORT	    xGPIO_PORTC_BASE
#define CH376_WR_PIN	    PC8
#define CH376_RD_PORT	    xGPIO_PORTC_BASE
#define CH376_RD_PIN	    PC9
#define CH376_A0_PORT	    xGPIO_PORTC_BASE
#define CH376_A0_PIN	    PC10
#define CH376_PCS_PORT      xGPIO_PORTC_BASE
#define CH376_PCS_PIN       PC11
#define CH376_DATA_PORT	    xGPIO_PORTE_BASE
#endif
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup CH376_Hardware_Layer_Driver_API
//! @{
//
//*****************************************************************************

//
//! delay specified us, need to be modified according MCU system clock, not exactly
//
extern void mDelayuS(unsigned int n);

//
//!delay specified ms, need to be modified according MCU system clock, not exactly
//
extern void mDelaymS(unsigned int n);

//
//! The below two function are intended for debugging use
//
extern void    mStopIfError( UINT8 ucError );

//
//! The debug function will use UART and printf to send debugging information.
//! This is to initialize UART1 for debugging
//
extern void    mInitSTDIO( void );

//
//! this function is to end a command only used in spi interface mode
//
extern void	xEndCH376Cmd( void );

//
//! Write command to CH376
//
extern void	xWriteCH376Cmd( UINT8 mCmd );

//
//! Write data to CH376
//
extern void	xWriteCH376Data( UINT8 mData );

//
//! Read data from CH376
//
extern UINT8	xReadCH376Data( void );

//
//! Query interrupt(low level of INT#)
//
extern UINT8	Query376Interrupt( void );

//
//! Initialize CH376
//
extern UINT8	mInitCH376Host( void );

//*****************************************************************************
//
//! @}
//!
//! @}
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif
#endif
