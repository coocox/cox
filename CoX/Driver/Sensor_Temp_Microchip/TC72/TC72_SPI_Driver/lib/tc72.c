//*****************************************************************************
//
//! \file tc72.c
//! \brief Driver for temperature sensor TC72.
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xgpio.h"
#include "hw_tc72.h"
#include "tc72.h"


//*****************************************************************************
//
//! \brief Initialize TC72 
//!
//! \param ulClock specifies the SPI Clock Rate
//!
//! This function is to initialize the MCU as master and specified SPI port.Set
//! TS_PIN_SPI_CS as CS, TS_PIN_SPI_CLK as CLK, TS_PIN_SPI_MISO ->MISO and 
//! TS_PIN_SPI_MOSI->MOSI.
//! 
//! \return None.
//
//*****************************************************************************
void
TC72Init(unsigned long ulSpiClock)
{

    //
    // The max clock rate of TC72 is 7M Hz acoording to Datasheet, Otherwise
    // it will generate  bigger error
    //

    xASSERT((ulSpiClock > 0) && (ulSpiClock < 7000000));

    //
    // Enable the GPIOx port which is connected with TC72 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_CS));
    
    //
    // Enable the SPIx which is connected with TC72
    //
    xSysCtlPeripheralEnable2(TS_PIN_SPI_PORT);

    //
    // Set TS_PIN_SPI_CS as a chip select pin and set it as OUT_MODE
    //
    xGPIOSPinDirModeSet(TS_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);

    //
    // Set TS_PIN_SPI_CLK as TS_PIN_SPI_CLK 
    //
    xSPinTypeSPI(SPI0CLK, TS_PIN_SPI_CLK);

    //
    // Set TS_PIN_SPI_MISO as SPI0.MISO
    //
    xSPinTypeSPI(SPI0MISO, TS_PIN_SPI_MISO);

    //
    // Set TS_PIN_SPI_MOSI as SPI0.MOSI
    //
    xSPinTypeSPI(SPI0MOSI, TS_PIN_SPI_MOSI);  
    
    //
    // Configure MCU as a master device , 8 bits data width ,MSB first,Mode_1
    //
    xSPIConfigSet(TS_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_1 |
                                                      xSPI_MODE_MASTER | 
                                                        xSPI_MSB_FIRST |
                                                        xSPI_DATA_WIDTH8);
    //
    // Disable TC72 when Power up
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
}

//*****************************************************************************
//
//! \brief Configure TC72 temperature convertion mode 
//!
//! \param ucMode specifies the TC72 convertion mode.
//!
//! The parameter of ucMode can be:
//! - TC72_MODE_CONTINUOUS - enter Continuous Temperature Conversion Mode
//! - TC72_MODE_SHUTDOWN - enter ShutDown Mode
//! - TC72_MODE_ONESHOT - enter one shot Conversion Mode.
//!
//! This function is to set and change TC72 temperature convertion mode,you can 
//! use TC72_MODE_SHUTDOWN if you want to enter low power consumption condition.
//! And you can use TC72_MODE_CONTINUOUS or TC72_MODE_ONESHOT to switch condition 
//! from shutdown mode.
//! 
//! \return None
//
//*****************************************************************************
void
TC72Configure(unsigned char ucMode)
{
    unsigned char ucWrite = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ucMode == TC72_MODE_CONTINUOUS) || (ucMode == TC72_MODE_SHUTDOWN)
                                             || (ucMode == TC72_MODE_ONESHOT)); 
    //
    // Step 0, Set CS,Start communication
    // 
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    //
    // Step 1, Write address of control register
    //
    ucWrite = TC72_CONTROL_WRITE_REG;
    xSPIDataWrite(TS_PIN_SPI_PORT, &ucWrite, 1);
    
    //
    // Step 2, Write the mode of convertion
    //  
    if(ucMode == TC72_MODE_CONTINUOUS)
    {
        ucWrite = TC72_MODE_CONTINUOUS;
    }       
    else if(ucMode == TC72_MODE_SHUTDOWN)
    {
    	ucWrite = TC72_MODE_SHUTDOWN;	
    }
    else
    {
    	ucWrite = TC72_MODE_ONESHOT;    	
    }
    
    xSPIDataWrite(TS_PIN_SPI_PORT, &ucWrite, 1);
    
    //
    // Step 3, Set CS => 0 Stop Communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
}

//*****************************************************************************
//
//! \brief Read TC72 ID
//! 
//! \param None
//!
//! This function is to Read ID
//! 
//! \return TC72 ID in Hexadecimal(0x54)
//
//*****************************************************************************
unsigned char
TC72IDcodeGet(void)
{
    unsigned char ucReadVal,ucWriteVal;
    
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    //
    //  Step 0, Set CS,Start communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    //
    //  Step 1, Write address of ID register
    //
    ucWriteVal = TC72_ID_REG;
    xSPIDataWrite(TS_PIN_SPI_PORT, &ucWriteVal, 1);
    
    //
    //  Step 2, Read IDcode
    //   
    xSPIDataRead(TS_PIN_SPI_PORT, &ucReadVal, 1);
    
    //
    // Step 3, Set CS => 0 Stop Communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    return ucReadVal;
}


//*****************************************************************************
//
//! \brief Read TC72 temperature value from TEMP register
//! 
//! \param None
//!
//! This function is to Read Temperature
//! 
//! \return the original temperature value of valid bits from TEMP register
//
//*****************************************************************************
short
TC72TemperRead(void)
{
    short sTemperature;
    unsigned short usReadMSB;
    unsigned char ucWriteAddr,ucReadLSB,ucControlByte;
    
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);

    //
    //  Step 0, Set CS,Start communication
    //   
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    //
    // Step 1,  Write address of TC72_MSB_REG
    //
    ucWriteAddr = TC72_MSB_REG;
    xSPIDataWrite(TS_PIN_SPI_PORT, &ucWriteAddr, 1);
    
    //
    // Step 2, Read MSB and LSB
    //    
    xSPIDataRead(TS_PIN_SPI_PORT, &usReadMSB, 1);
    xSPIDataRead(TS_PIN_SPI_PORT, &ucReadLSB, 1);
    xSPIDataRead(TS_PIN_SPI_PORT, &ucControlByte, 1);
    
    //
    // Step 3, Set CS => 0 Stop Communication
    //        
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    //
    // Get temperature value of valid bits from TEMP register
    //
    usReadMSB = usReadMSB << 8;

    sTemperature = usReadMSB | ucReadLSB;

    sTemperature = sTemperature >> 6;

    return sTemperature;
}

//*****************************************************************************
//
//! \brief Read TC72 temperature value and handle data in decimal
//! 
//! \param None
//!
//! This function is to Read Temperature
//! 
//! \return temperature value which is in decimal
//
//*****************************************************************************
short
TC72TemperReadDec(void)
{
    short sTempValue;
    
    //
    // Get the temperature value 
    //    
    sTempValue = TC72TemperRead();
    sTempValue = sTempValue * 0.25;

    return sTempValue;
}

//*****************************************************************************
//
//! \brief Check the ID whether it is equal 0x54 or not
//! 
//! \param None
//!
//! This function is to check TC72 ID,you should check it is existent and usable
//! or not before you start getting temperaturwert.
//! 
//! \return Returns \b true if the TC72 is existent and usable and \b false 
//! if it is not.
//
//*****************************************************************************
xtBoolean
TC72IDCheck(void)
{
    unsigned char ucIDValue;
    
    //
    // Get the TC72 ID value 
    //    
    ucIDValue = TC72IDcodeGet();
    
    //
    // check the ID 
    //
    return (ucIDValue == 0x54) ? xtrue : xfalse;
    
}

//*****************************************************************************
//
//! \brief Read TC72 temperature value and handle data in float
//! 
//! \param None
//!
//! This function is to Read Temperature
//! 
//! \return temperature value which is in float
//
//*****************************************************************************
float
TC72TemperReadFloat(void)
{
    float fTem;
    short sTempValue;
    
    //
    // Get the temperature value 
    //
    sTempValue = TC72TemperRead();
    fTem = (float)sTempValue * 0.25;

    return fTem;
}

//*****************************************************************************
//
//! \brief conversely initialize TC72
//! 
//! \param None
//!
//! This function is to conversely initialize TC72,you can use it when you do not
//! want to get temperaturwert.
//! 
//! \return None
//
//*****************************************************************************
void
TC72DeInit(void)
{
    //
    // conversely initialize TC72
    //
    xSysCtlPeripheralDisable2(TS_PIN_SPI_PORT);
}

//*****************************************************************************
//
//! \brief Read values of control register
//! 
//! \param None
//!
//! This function is to get values of control register
//! 
//! \return values of control register
//
//*****************************************************************************
unsigned char
TC72ControlRegValGet(void)
{
    unsigned char ucReadVal, ucWriteVal;
    
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    //
    //  Step 0, Set CS,Start communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    //
    //  Step 1, Write address of control register
    //
    ucWriteVal = TC72_CONTROL_READ_REG;
    xSPIDataWrite(TS_PIN_SPI_PORT, &ucWriteVal, 1);
    
    //
    //  Step 2, Read the value of mode
    //   
    xSPIDataRead(TS_PIN_SPI_PORT, &ucReadVal, 1);
    
    //
    // Step 3, Set CS => 0 Stop Communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    return ucReadVal;
}
