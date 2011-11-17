//*****************************************************************************
//
//! \file adt7301.c
//! \brief Driver for temperature sensor adt7301.
//! \version V2.1.1.0
//! \date 10/26/2011
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
#include "adt7301.h"

//*****************************************************************************
//
//! \brief Initialize ADT7301  
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
ADT7301Init(unsigned long ulSpiClock)
{
    //
    // Enable the GPIOx port which is connected with ADT7301 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_CS));
    
    //
    // Enable the SPIx which is connected with ADT7301
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
    // Configure MCU as a master device , 16 bits data width ,MSB first,Mode_3
    //
    xSPIConfigSet(TS_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_3 |
                                                      xSPI_MODE_MASTER | 
                                                        xSPI_MSB_FIRST |
                                                      xSPI_DATA_WIDTH16);
    //
    // Disable ADT7301 when Power up
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief Configure ADT7301 temperature convertion mode 
//!
//! \param usMode specifies the ADT7301 convert mode.
//!
//! The parameter of usMode can be:
//! - ADT7301_NORMAL_MODE - enter Normal Temperature Conversion Mode
//! - ADT7301_SHUTDOWN_MODE - enter ShutDown Mode
//! 
//! This function is to set and change ADT7301 temperature convertion mode,you  
//! can use ADT7301_SHUTDOWN_MODE if you want to enter low power consumption 
//! And you can use ADT7301_NORMAL_MODE to switch condition from shutdown mode.
//! 
//! \return None
//
//*****************************************************************************
void
ADT7301Configure(unsigned short usMode)
{
    unsigned short usWrite;
    
    //
    // Check the arguments.
    //
    xASSERT((usMode == ADT7301_MODE_NORMAL) || (usMode == ADT7301_MODE_SHUTDOWN));
    
    //
    // Step 0, Set CS,Start communication
    // 
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    //
    // Step 1, Write the mode of convertion
    //  
    if(usMode == ADT7301_MODE_NORMAL)
    {
        usWrite =ADT7301_MODE_NORMAL;
    }
    else
    {
    	usWrite = ADT7301_MODE_SHUTDOWN;
    }
    
    xSPISingleDataReadWrite(TS_PIN_SPI_PORT, usWrite);
    
    //
    // Step 2, Set CS => 1 Stop Communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
}

//*****************************************************************************
//
//! \brief Read ADT7301 temperature value from TEMP register
//! 
//! \param None
//!
//! This function is to get temperature value
//! 
//! \return the original temperature value of valid bits from TEMP register
//
//*****************************************************************************
short
ADT7301TemperRead(void)
{
    short sReadVal;
    unsigned long ulSysClk;
    
    //
    // Allow time for conversions
    //    
    ulSysClk = xSysCtlClockGet();
    xSysCtlDelay(ulSysClk/10);
    
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    //
    // Step 0, Set CS,Start communication
    //   
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    //
    // Step 1,  Read temperature value
    //
    sReadVal = xSPISingleDataReadWrite(TS_PIN_SPI_PORT, 0x0000);
    
    //
    // Step 2, Set CS => 1 Stop Communication
    //        
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    //
    // Temperature value stored in sReadVal
    //
    return sReadVal;
}

//*****************************************************************************
//
//! \brief Read ADT7301 temperature value and handle data in decimal
//! 
//! \param None
//!
//! This function is to Get temperature value from ADT7301 and the value is in
//! decimal format
//! 
//! \return temperature value which is in decimal
//
//*****************************************************************************
short
ADT7301TemperReadDec(void)
{
    short sTempValue;
    
    //
    // Get the temperature value 
    //    
    sTempValue = ADT7301TemperRead();
    
    //
    // Check sign bit for negative value.
    //      
    if ((0x2000 & sTempValue) == 0x2000)        
    {
    //
    // Conversion formula if negative temperature
    //
        sTempValue = (sTempValue - 16384)/32;  
    } 
    else 
    {
    //
    // Conversion formula if positive temperature
    //
        sTempValue = sTempValue/32;           
    }
    
    //
    // Temperature value stored in sTempValue
    //
    return sTempValue;
}

//*****************************************************************************
//
//! \brief Read ADT7301 temperature value and handle data in float
//! 
//! \param None
//!
//! This function is to Get temperature value from ADT7301 and the value is in
//! float format
//! 
//! \return temperature value which is in float
//
//*****************************************************************************
float
ADT7301TemperReadFloat(void)
{
    float fTem;
    short sTempValue;
    
    //
    // Get the temperature value 
    //
    sTempValue = ADT7301TemperRead();

    //
    // Check sign bit for negative value.
    //    
    if ((0x2000 & sTempValue) == 0x2000)
    { 
    //
    // Conversion formula if negative temperature
    //
        fTem = (float)(sTempValue - 16384) * 0.03125;  
    } 
    else
    { 
    //
    // Conversion formula if positive temperature
    //
        fTem = (float)(sTempValue * 0.03125);           
    }
    
    //
    // Temperature value stored in fTem
    //
    return fTem;
}

//*****************************************************************************
//
//! \brief conversely initialize ADT7301
//! 
//! \param None
//!
//! This function is to conversely initialize ADT7301,you can use it when you do 
//! not want to get temperaturwert.
//! 
//! \return None
//
//*****************************************************************************
void
ADT7301DeInit(void)
{
    //
    // conversely initialize ADT7301
    //
    xSysCtlPeripheralDisable2(TS_PIN_SPI_PORT);
}
