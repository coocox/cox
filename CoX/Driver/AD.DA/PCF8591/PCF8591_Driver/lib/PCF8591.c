//*****************************************************************************
//
//! \file PCF8591.c
//! \brief source file of Driver for PCF8591
//! \version V2.1.1.0
//! \date 1/9/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "PCF8591.h"

//
// the reference voltage
//
const float ref_vol = 3.85;

//*****************************************************************************
//
//! \brief Initialize PCF8591.
//!
//! \return None.
//
//*****************************************************************************

void PCF8591_Init(unsigned long ulRate)
{
	//
	// Enable GPIO Clock
	//
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PCF8591_SDA_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PCF8591_SCL_PIN));

	xSPinTypeI2C(I2C_SDA, PA8);
	xSPinTypeI2C(I2C_SCK, PA9);

	//
	// Enable I2C peripheral Clock
	//
	xSysCtlPeripheralEnable2(PCF8591_I2C_PORT);

	xI2CMasterInit(PCF8591_I2C_PORT, ulRate);
}

//*****************************************************************************
//
//! \brief function for D/A conversion
//!
//! \param data specifies the data to convert, notice that the first value in
//! data is the control byte, for da conversion, is 0x40
//! \param data_len the length of data.
//!
//! \return status of conversion, true is successful, false is failed.
//
//*****************************************************************************
unsigned char  PCF8591_DA_OUT(unsigned char* data,
		unsigned long data_len)
{
	tI2CMasterTransferCfg Cfg;
	Cfg.ulSlave = PCF8591_ADDRESS;

	Cfg.pvWBuf = data;
	Cfg.ulWLen = data_len;
	Cfg.ulWCount = 0;
	Cfg.pvRBuf = 0;
	Cfg.ulRLen = 0;
	Cfg.ulRCount = 0;

	//Enable Analog Output
	data[0] |= 0x40;

	return I2CMasterTransfer(I2C0_BASE, &Cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief function forA/D conversion
//!
//! \param data the result of conversion
//! \param data_len the length of data.
//! \param mode set the control byte, it can be any combination of:
//! PCF8591_ANALOG_OUTPUT_ENABLE, PCF8591_ANALOG_OUTPUT_DISABLE,
//! PCF8591_INPUT_FOUR_SINGLE, PCF8591_INPUT_THREE_DIF,
//! PCF8591_INPUT_MIXED, PCF8591_INPUT_TWO_DIF
//! PCF8591__INPUT_INC_ENABLE	, PCF8591__INPUT_INC_DISABLE
//! PCF8591_CHANNEL_0, PCF8591_CHANNEL_1
//! PCF8591_CHANNEL_2, PCF8591_CHANNEL_3
//!
//! \return status of conversion, true is successful, false is failed.
//
//*****************************************************************************
void  PCF8591_AD_Trans(char* data, unsigned long data_len,
				unsigned char mode)
{

	tI2CMasterTransferCfg Cfg;

	//set the mode firstly
	unsigned char* ucpMode = &mode;

	Cfg.ulSlave = PCF8591_ADDRESS;

	Cfg.pvWBuf = ucpMode;
	Cfg.ulWLen = 1;
	Cfg.ulWCount = 0;
	Cfg.pvRBuf = 0;
	Cfg.ulRLen = 0;
	Cfg.ulRCount = 0;

	I2CMasterTransfer(I2C0_BASE, &Cfg, I2C_TRANSFER_POLLING);

	//get result of ad conversion
	Cfg.pvWBuf = 0;
	Cfg.ulWLen = 0;
	Cfg.pvRBuf = data;
	Cfg.ulRLen = data_len;

	I2CMasterTransfer(I2C0_BASE, &Cfg, I2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! \brief get the voltage of A/D conversion
//!
//! \param vol float type of the result of conversion
//! \param data char type of the result of conversion
//! \param data_len the length of data.
//!
//! \return none.
//
//*****************************************************************************
void  PCF8591_AD_Vol(float* vol, char* data, unsigned long data_len )
{
	int i;
	for(i=0;i<data_len;i++)
	{
		vol[i] = ref_vol*data[i]/256;
	}
}
