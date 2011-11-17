//*****************************************************************************
//
//! \file tc77.c
//! \brief Driver for temperature sensor TC77.
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xgpio.h"
#include "tc77.h"


//*****************************************************************************
//
//! \brief Initialize TC77 
//!
//! \param ulClock specifies the SPI Clock Rate
//!
//! This function is to initialize the MCU as master and specified SPI port.Set
//! TS_PIN_SPI_CS as CS, TS_PIN_SPI_CLK as CLK, TS_PIN_SPI_MISO ->MISO and 
//! TS_PIN_SPI_MOSI->MOSI,most of all it check the first conversion is finished 
//! or not in order to execute the following operation.
//! 
//! \return None.
//
//*****************************************************************************
void
TC77Init(unsigned long ulSpiClock)
{
    short sReadValue = 0;
    
    //
    // The max clock rate of TC77 is 7M Hz acoording to Datasheet, Otherwise
    // it will generate  bigger error
    //
    xASSERT((ulSpiClock > 0) && (ulSpiClock < 7000000));
    
    //
    // Enable the GPIOx port which is connected with tc77 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_MISO));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(TS_PIN_SPI_CS));
    
    //
    // Enable the SPIx which is connected with tc77
    //
    xSysCtlPeripheralEnable2(TS_PIN_SPI_PORT);
    
    //
    // Set TS_PIN_SPI_CS as a chip select pin and set it as OUT_MODE
    //
    xGPIOSPinDirModeSet(TS_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    
    //
    // Set TS_PIN_SPI_CLK as SPI0.CLK
    //
    xSPinTypeSPI(SPI0CLK, TS_PIN_SPI_CLK);
    
    //
    // Set PC2 as SPI0.MISO
    //
    xSPinTypeSPI(SPI0MISO, TS_PIN_SPI_MISO);
    
    //
    // Configure MCU as a master device , 16 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(TS_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_0 |
                                                     xSPI_DATA_WIDTH16 |
                                                      xSPI_MODE_MASTER |
                                                        xSPI_MSB_FIRST);
    //
    // Disable TC77 when Power up
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);

    //
    // Wait for the first conversion completed
    //
    while(!(0x0004 & sReadValue))
    {
        sReadValue = TC77TemperRead();
    }
}


//*****************************************************************************
//
//! \brief Configure TC77 temperature convertion mode 
//!
//! \param ulMode determines if TC77_CONTINUOUS_MODE or TC77_SHUTDOWN_MODE to select.
//!
//! The parameter of usMode can be:
//! - TC77_CONTINUOUS_MODE - enter Continuous Temperature Conversion Mode
//! - TC77_SHUTDOWN_MODE.  - enter ShutDown Mode
//!
//! This function is to set and change TC77 temperature convertion mode,you can 
//! use TC77_SHUTDOWN_MODE if you want to enter low power consumption condition.
//! And you can use TC77_CONTINUOUS_MODE to switch condition from shutdown mode.
//! 
//! \return None
//
//*****************************************************************************
void
TC77Configure(unsigned short usMode)
{
    unsigned short usRead,usWrite;
    
    //
    // Check the arguments.
    //
    xASSERT((usMode == TC77_MODE_CONTINUOUS) || (usMode == TC77_MODE_SHUTDOWN));
    
    //
    //  Step 0, Set CS,Start communication
    // 
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    xGPIOSPinTypeGPIOInput(TS_PIN_SPI_MOSI);
    
    //
    // Step 1, Read temperature
    //
    xSPIDataRead(TS_PIN_SPI_PORT, &usRead, 1);  

    xSPinTypeSPI(SPI0MOSI, TS_PIN_SPI_MOSI);
    
    //
    // Continous conversion mode 
    //
    if(usMode == TC77_MODE_CONTINUOUS)
    {
        usWrite = TC77_MODE_CONTINUOUS;
    }
    
    //
    // ShutDown conversion mode 
    //    
    else
    {
        usWrite = TC77_MODE_SHUTDOWN;
    }
    
    //
    // Step 2, Enter corresponding mode
    //
    xSPIDataWrite(TS_PIN_SPI_PORT, &usWrite, 1);
    
    //
    // Step 3, Set CS => 1 Stop Communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
}


//*****************************************************************************
//
//! \brief Read TC77 temperature value from TEMP register
//! 
//! \param None
//!
//! This function is to Read Temperature
//! 
//! \return the original temperature value from TEMP register
//
//*****************************************************************************
short
TC77TemperRead(void)
{
    short sTemperature;
    
    xGPIOSPinTypeGPIOInput(TS_PIN_SPI_MOSI);
    
    //
    //  Step 0, Set CS,Start communication
    //   
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    //
    // Step 1, Read 16(temperature value)
    //       
    xSPIDataRead(TS_PIN_SPI_PORT, &sTemperature, 1);
    
    //
    // Step 2, Set CS => 1 Stop Communication
    //        
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
        
    return sTemperature;
}


//*****************************************************************************
//
//! \brief Get TC77 temperature value and handle data in float
//! 
//! \param None
//!
//! This function is to Read Temperature
//! 
//! \return temperature value which is in float
//
//*****************************************************************************
float
TC77TemperReadFloat(void)
{
    float fTemReturn;
    short sTempValue;
    
    //
    // Get the temperature value 
    //
    sTempValue = TC77TemperRead();
    
    //
    // Get temperature value of valid bits from TEMP register
    // 
    sTempValue = sTempValue >> 3;
    
    fTemReturn = (float)sTempValue * 0.0625;

    return fTemReturn;
}


//*****************************************************************************
//
//! \brief  TC77 over temperature check
//!
//! \param None
//!
//! This function checks the tc77 whether it is over the highest temperature
//! 
//! \return status (status == xture indicate the TC77 not over the highest) 
//
//*****************************************************************************
xtBoolean
TC77Overflow(void)
{   
    short sTemperature;
    
    sTemperature = TC77TemperRead();
    
//
// Check the sign according to the Most Significant Bit
//
    if(sTemperature & 0x8000)
    {
        //
        // Negative value handle
        //  
        return (!(sTemperature & 0x2000)) ? xtrue : xfalse;
    }
    else
    {
        //
        // Positive value handle
        //
        return (sTemperature & 0x4000) ? xtrue : xfalse;
    }
}


//*****************************************************************************
//
//! \brief Read TC77 ID
//! 
//! \param None
//!
//! This function is to get ID
//! 
//! \return TC77 ID
//
//*****************************************************************************
unsigned short
TC77IDcodeGet(void)
{
    unsigned short usReadVal,usWriteVal,usIDcode;

    //
    //  Step 0, Set CS,Start communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 0);
    
    xGPIOSPinTypeGPIOInput(TS_PIN_SPI_MOSI);
    
    //
    //  Step 1, Read 16
    //
    xSPIDataRead(TS_PIN_SPI_PORT, &usReadVal, 1);
    
    //
    //  Step 2, Enter Shutdown mode : Write 0XFFFF
    //
    xSPinTypeSPI(SPI0MOSI, TS_PIN_SPI_MOSI);
    
    usWriteVal = TC77_MODE_SHUTDOWN;
    
    xSPIDataWrite(TS_PIN_SPI_PORT, &usWriteVal, 1);
    
    //
    // Step 3, Read IDcode
    //
    xGPIOSPinTypeGPIOInput(TS_PIN_SPI_MOSI);
    
    usReadVal = 0;
    xSPIDataRead(TS_PIN_SPI_PORT, &usReadVal, 1);
    
    //
    //  Step 4, Enter Continus Mode : Wirte 0x0000
    //
    xSPinTypeSPI(SPI0MOSI, TS_PIN_SPI_MOSI);
    
    usWriteVal = TC77_MODE_CONTINUOUS;
    
    xSPIDataWrite(TS_PIN_SPI_PORT, &usWriteVal, 1);
    
    //
    // Step 5, Set CS => 1 Stop Communication
    //
    xGPIOSPinWrite(TS_PIN_SPI_CS, 1);
    
    usIDcode = usReadVal >> 8;
    
    return usIDcode;
}


//*****************************************************************************
//
//! \brief Read TC77 temperature value and handle data in decimal
//! 
//! \param None
//!
//! This function is to Read Temperature
//! 
//! \return temperature value which is in decimal
//
//*****************************************************************************
short
TC77TemperReadDec(void)
{
    short sTempValue;
    
    //
    // Get the temperature value 
    //    
    sTempValue = TC77TemperRead();
    
    //
    // Get temperature value of valid bits from TEMP register
    // 
    sTempValue = sTempValue >> 3;    
    
    sTempValue = sTempValue * 0.0625;

    return sTempValue;
}


//*****************************************************************************
//
//! \brief Check the ID whether it is equal 0x54
//! 
//! \param None
//!
//! This function is to check TC77 ID,you should check it is existent and usable
//! before you start getting temperaturwert.
//! 
//! \return Returns \b true if the TC77 is existent and usable and \b false 
//! if it is not.
//
//*****************************************************************************
xtBoolean
TC77IDCheck(void)
{
    short sIDValue;
    
    //
    // Get the tc77 ID value 
    //    
    sIDValue = TC77IDcodeGet();
    
    //
    // check the ID 
    //
    return (sIDValue == 0x54) ? xtrue : xfalse;
}


//*****************************************************************************
//
//! \brief conversely initialize TC77
//! 
//! \param None
//!
//! This function is to conversely initialize TC77,you can use it when you do not
//! want to get temperaturwert.
//! 
//! \return None
//
//*****************************************************************************
void 
TC77DeInit(void)
{
    //
    // Conversely initialize TC77
    //
    xSysCtlPeripheralDisable2(TS_PIN_SPI_PORT);
}
