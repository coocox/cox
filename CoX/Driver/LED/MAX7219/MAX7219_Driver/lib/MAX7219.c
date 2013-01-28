//*****************************************************************************
//
//! \file MAX7219.c
//! \brief the MAX7219 Driver.
//! \version V2.1.1.0
//! \date 1/10/2013
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xgpio.h"
#include "MAX7219.h"

#define     SPI_Speed           200000

//*****************************************************************************
//
//! \brief Write one byte to MAX7219.
//!
//! \param addr specifies the address to write.
//! \param ucdata specifies the data to write.
//!
//! \return None.
//
//*****************************************************************************
void MAX7219_Write(unsigned char addr, unsigned char ucdata)
{
	unsigned short data = (addr<<8) | ucdata;

	SPISSSet(MAX7219_SPI_PORT, SPI_SS0);
	SPIDataWrite(MAX7219_SPI_PORT, &data, 1);
	SPISSClear(MAX7219_SPI_PORT, SPI_SS0);
}

//*****************************************************************************
//
//! \brief Initialize  MAX7219 and SPI
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void MAX7219_Init(void)
{

    //
	// Enable Peripheral SPI0
	//
    xSysCtlPeripheralEnable2(MAX7219_SPI_PORT);
    xSysCtlPeripheralEnable2(MAX7219_SPI_GPIO);

    xSPinTypeSPI(MAX7219_SPI_SCK, MAX7219_PIN_SPI_SCK);
    xSPinTypeSPI(MAX7219_SPI_DIN, MAX7219_PIN_SPI_DIN);
    xSPinTypeSPI(MAX7219_SPI_CS, MAX7219_PIN_SPI_CS);

    //
	// Configure SPI
	//
	SPIConfig(MAX7219_SPI_PORT, SPI_Speed, SPI_FORMAT_MODE_1 | SPI_DATA_WIDTH16 |
											   SPI_MSB_FIRST | SPI_MODE_MASTER);

	SPISSConfig(MAX7219_SPI_PORT, SPI_SS_LEVEL_TRIGGER,
			SPI_SS_ACTIVE_LOW_FALLING);

	//
	// decode for all number, d0~d7
	//
	MAX7219_Write(MAX7219_DECODE_MODE_ADDR, 0xff);

	//
	// set intensity
	//
	MAX7219_Write(MAX7219_INTENSITY_ADDR, 0x03);

	//
	// set scan limit, scan all number, d0~d7
	//
	MAX7219_Write(MAX7219_SCAN_LIMIT_ADDR, 0x07);

	//
	// set to normal mode
	//
	MAX7219_Write(MAX7219_SHUTDOWN_ADDR, 0x01);

	//
	// not test
	//
	MAX7219_Write(MAX7219_TEST_ADDR, 0x00);
}
