//*****************************************************************************
//
//! \file bh1750fvi.c
//! \brief Driver for light sensor BH1750FVI.
//! \version V2.2.1.0
//! \date 7/17/2012
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
#include "xhw_i2c.h"
#include "xi2c.h"
#include "xgpio.h"
#include "hw_bh1750fvi.h"
#include "bh1750fvi.h"


//*****************************************************************************
//
//! \brief Initialize BH1750FVI 
//!
//! \param ulClock specifies the I2C Clock Rate
//!
//! This function is to initialize the MCU as master and specified I2C port.Set
//! BH1750_PIN_DVI as DVI, BH1750_PIN_I2C_CLK as SCK, BH1750_PIN_I2C_SDA ->SDA 
//! BH1750_PIN_ADDR ->ADDR.
//! 
//! \return None.
//
//*****************************************************************************
void
BH1750Init(unsigned long ulI2cClock)
{

    //
    // The max clock rate of BH1750 is 400k Hz acoording to Datasheet, Otherwise
    // it will generate  bigger error
    //

    xASSERT((ulI2cClock > 0) && (ulSpiClock < ulI2cClock));

    //
    // Enable the GPIOx port which is connected with BH1750FVI 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(BH1750_PIN_I2C_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(BH1750_PIN_I2C_SDA));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(BH1750_PIN_ADDR));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(BH1750_PIN_DVI));
    
    //
    // Enable the I2Cx which is connected with BH1750FVI
    //
    xSysCtlPeripheralEnable2(BH1750_PIN_I2C_PORT);

    //
    // Set BH1750_PIN_DVI as OUT_MODE
    //
    xGPIOSPinDirModeSet(BH1750_PIN_DVI, xGPIO_DIR_MODE_IN);
    
    //
    // Set BH1750_PIN_ADDR as OUT_IN
    //
    xGPIOSPinDirModeSet(BH1750_PIN_ADDR, xGPIO_DIR_MODE_IN);

    //
    // Set BH1750_PIN_I2C_CLK as CLK 
    //
    xSPinTypeI2C(BH1750_I2C_CLK, BH1750_PIN_I2C_CLK);

    //
    // Set BH1750_PIN_I2C_SDA as SDA 
    //
    xSPinTypeI2C(BH1750_I2C_SDA, BH1750_PIN_I2C_SDA);

    //
    // Configure MCU as a master device and Set Clcok Rates
    //
    xI2CMasterInit(BH1750_PIN_I2C_PORT, ulI2cClock);
    xI2CMasterEnable(BH1750_PIN_I2C_PORT);
}

//*****************************************************************************
//
//! \brief Configure BH1750FVI light convertion mode 
//!
//! \param ucMode specifies the BH1750FVI convertion mode.
//!
//! The parameter of ucMode can be:
//! - BH1750_INS_CON_HR_MODE - enter Continuously H-Resolution Mode.
//! - BH1750_INS_CON_HR_MODE_2 - enter Continuously H-Resolution Mode 2.
//! - BH1750_INS_CON_LR_MODE - enter Continuously L-Resolution Mode.
//! - BH1750_INS_ONE_HR_MODE - enter One Time H-Resolution Mode.
//! - BH1750_INS_ONE_HR_MODE_2 - enter One Time H-Resolution Mode 2.
//! - BH1750_INS_ONE_LR_MODE - enter One Time L-Resolution Mode.
//!
//! This function is to set and change BH1750FVI light convertion mode.
//!
//! \note After Configuring the BH1750FVI,You should delay sometime(the length of
//! time refer datasheet) before you want to get light value.
//! 
//! \return None
//
//*****************************************************************************
void
BH1750Configure(unsigned char ucMode)
{
    
    //
    // Check the arguments.
    //
    xASSERT((ucMode == BH1750_INS_CON_HR_MODE) || 
            (ucMode == BH1750_INS_CON_LR_MODE) ||
            (ucMode == BH1750_INS_ONE_HR_MODE) || 
            (ucMode == BH1750_INS_ONE_LR_MODE) ||
            (ucMode == BH1750_INS_CON_HR_MODE_2) || 
            (ucMode == BH1750_INS_ONE_HR_MODE_2));
    //
    // Step 0,Send POWER_ON and Reset Instruction.
    // 
    xI2CMasterWriteS1(BH1750_PIN_I2C_PORT, 0x23, BH1750_INS_POWER_ON, xtrue);
    xI2CMasterWriteS1(BH1750_PIN_I2C_PORT, 0x23, BH1750_INS_RESET, xtrue);
    
    //
    // Step 1, Send light convertion mode
    //
    xI2CMasterWriteS1(BH1750_PIN_I2C_PORT, 0x23, ucMode, xtrue);
}

//*****************************************************************************
//
//! \brief Read light value from BH1750FVI.
//! 
//! \param None
//!
//! This function is to Read light value
//! 
//! \return the original light value of valid bits from BH1750FVI.
//
//*****************************************************************************
short
BH1750LightRead(void)
{
    unsigned char ucLowBits = 0;
    unsigned char ucHighBits = 0;
    unsigned short usLight = 0;


    //
    //  Step 0, Get the low bits of light value
    //   
    xI2CMasterReadS1(BH1750_PIN_I2C_PORT, 0x23, &ucLowBits, xfalse);
    
    //
    // Step 1,  Get the high bits of light value
    //
    xI2CMasterReadS2(BH1750_PIN_I2C_PORT, &ucHighBits, xtrue);
    
    usLight = (ucHighBits << 8) | ucLowBits;

    //
    // Return Light value
    //
    return usLight;
}

//*****************************************************************************
//
//! \brief Adjust the sensor sensitivity of BH1750FVI.
//! 
//! \param ucMeasurementTime specifies BH1750FVI Measurement time
//!
//! This function is to Adjust the sensor sensitivity of BH1750FVI.
//!
//! \note If you want to Adjust the sensor sensitivity of BH1750FVI, You should
//! use it before you call BH1750Configure() to Set Mode.
//! 
//! \return None
//
//*****************************************************************************
void
BH1750SensitivityAdjust(unsigned char ucMeasurementTime)
{
    unsigned char ucLowBits = 0;
    unsigned char ucHighBits = 0;


    ucLowBits = ((ucMeasurementTime >> 5) & 0x40) | 0x40;
    ucHighBits = (ucMeasurementTime | 0x60) & 0x7f;

    //
    // Step 0, Set the high bits of light value
    //   
    xI2CMasterWriteS1(BH1750_PIN_I2C_PORT, 0x23, ucHighBits, xtrue);
    
    //
    // Step 1, Set the low bits of light value
    //
    xI2CMasterWriteS1(BH1750_PIN_I2C_PORT, 0x23, ucLowBits, xtrue);
}

//*****************************************************************************
//
//! \brief conversely initialize BH1750FVI
//! 
//! \param None
//!
//! This function is to conversely initialize BH1750FVI,you can use it when you 
//! do not want to get light value.
//! 
//! \return None
//
//*****************************************************************************
void
BH1750DeInit(void)
{
    //
    // conversely initialize BH1750FVI
    //
    xSysCtlPeripheralDisable2(BH1750_PIN_I2C_PORT);
}
