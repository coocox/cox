//*****************************************************************************
//
//! \file xspi.c
//! \brief Driver for the SPI
//! \version V2.2.1.0
//! \date 11/14/2011
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
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_config.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_spi.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xspi.h"

//*****************************************************************************
//
// An array is SPI Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnSPIHandlerCallbacks[3]={0};

//*****************************************************************************
//
//! \brief SPI1 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI1 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI1IntHandler(void)
{
    unsigned long ulEventFlags, ulCR1;

    ulEventFlags =  xHWREG(SPI1_BASE + SPI_SR);

    if((ulEventFlags & SPI_SR_OVR) != 0)
    {
        xHWREG(SPI1_BASE + SPI_DR);
        xHWREG(SPI1_BASE + SPI_SR);
    }
    else if((ulEventFlags & SPI_SR_MODF) != 0)
    {
        (void)xHWREG(SPI1_BASE + SPI_SR);
        ulCR1 = xHWREG(SPI1_BASE + SPI_CR1);
        xHWREG(SPI1_BASE + SPI_CR1) = ulCR1;     
    }
    else if((ulEventFlags & SPI_SR_CRCERR) != 0)
    {
        xHWREG(SPI1_BASE + SPI_SR) &= ~SPI_SR_CRCERR; 
    }
        
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[0])
    {
        g_pfnSPIHandlerCallbacks[0](0, 0, ulEventFlags, 0);
    }
}

//*****************************************************************************
//
//! \brief SPI2 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI2 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI2IntHandler(void)
{
    unsigned long ulEventFlags, ulCR1;

    ulEventFlags =  xHWREG(SPI2_BASE + SPI_SR);

    if((ulEventFlags & SPI_SR_OVR) != 0)
    {
        xHWREG(SPI2_BASE + SPI_DR);
        xHWREG(SPI2_BASE + SPI_SR);
    }
    else if((ulEventFlags & SPI_SR_MODF) != 0)
    {
        ulCR1 = xHWREG(SPI2_BASE + SPI_CR1);
        xHWREG(SPI2_BASE + SPI_CR1) = ulCR1;     
    }
    else if((ulEventFlags & SPI_SR_CRCERR) != 0)
    {
        xHWREG(SPI2_BASE + SPI_SR) &= ~SPI_SR_CRCERR; 
    }
    
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[1])
    {
        g_pfnSPIHandlerCallbacks[1](0, 0, ulEventFlags, 0);
    }
}

//*****************************************************************************
//
//! \brief SPI3 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI3 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI3IntHandler(void)
{
    unsigned long ulEventFlags, ulCR1;

    ulEventFlags =  xHWREG(SPI3_BASE + SPI_SR);

    if((ulEventFlags & SPI_SR_OVR) != 0)
    {
        xHWREG(SPI3_BASE + SPI_DR);
        xHWREG(SPI3_BASE + SPI_SR);
    }
    else if((ulEventFlags & SPI_SR_MODF) != 0)
    {
        ulCR1 = xHWREG(SPI3_BASE + SPI_CR1);
        xHWREG(SPI3_BASE + SPI_CR1) = ulCR1;     
    }
    else if((ulEventFlags & SPI_SR_CRCERR) != 0)
    {
        xHWREG(SPI3_BASE + SPI_SR) &= ~SPI_SR_CRCERR; 
    }
    
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[2])
    {
        g_pfnSPIHandlerCallbacks[2](0, 0, ulEventFlags, 0);
    }
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSMode specifies the SS is hardware control or software control.
//! \param ulSlaveSel specifies the slave select pins which will be used.
//!
//! The \e ulSSMode can be one of the following values:
//! \b SPI_SS_HARDWARE, \b SPI_SS_SOFTWARE.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b xSPI_SS0.(only used in SPI_SS_HARDWARE mode)
//! \b xSPI_SS_NONE used in SPI_SS_SOFTWARE mode.
//!
//! \NOTE: xSPISSSet usage:
//! For SPI Master:
//!     1) Hardware mode: CS must configure into output mode, when SPI master is enable,
//!     CS is low, when SPI master is disable, CS is High.
//! 
//!     Configure example:
//! 
//!     xSPinTypeSPI(SPI1CS(3),   PA4);
//!     xSPinTypeSPI(SPI1CLK(3),  PA5);
//!     xSPinTypeSPI(SPI1MOSI(3), PA7);
//!     xSPinTypeSPI(SPI1MISO(1), PA6);
//! 
//!     xSPIConfigSet(xSPI2_BASE, 4000000, xSPI_MOTO_FORMAT_MODE_0 |
//!                                        xSPI_MODE_MASTER        |                                                
//!                                        xSPI_MSB_FIRST          |
//!                                        xSPI_DATA_WIDTH8);
//!     xSPISSSet(SPI2_BASE, SPI_SS_HARDWARE, xSPI_SS0);
//! 
//! 
//!     2) Software mode: CS pin is free for user.
//! 
//!     Configure example:
//! 
//!     xGPIOSPinTypeGPIOOutput(PA3);          //Free PA4, Use PA3 as SPI CS pin
//!     //xSPinTypeSPI(SPI1CS(3),   PA4);
//!     xSPinTypeSPI(SPI1CLK(3),  PA5);
//!     xSPinTypeSPI(SPI1MOSI(3), PA7);
//!     xSPinTypeSPI(SPI1MISO(1), PA6);
//! 
//!     xSPIConfigSet(xSPI2_BASE, 4000000, xSPI_MOTO_FORMAT_MODE_0 |
//!                                        xSPI_MODE_MASTER        |                                                
//!                                        xSPI_MSB_FIRST          |
//!                                        xSPI_DATA_WIDTH8);
//!     xSPISSSet(SPI1_BASE, SPI_SS_SOFTWARE, xSPI_SS_NONE);
//! 
//! 
//! 
//! -----------------------------------------------------------------------------
//! For SPI Slave :
//!     only need to set hardware mode. software mode is useless for Slave device.
//!     Configure example:
//! 
//!     xSPinTypeSPI(SPI2CS(1),   PB12);
//!     xSPinTypeSPI(SPI2CLK(1),  PB13);
//!     xSPinTypeSPI(SPI2MISO(3), PB14);
//!     xSPinTypeSPI(SPI2MOSI(1), PB15);
//!     xSPIConfigSet(xSPI2_BASE, 4000000, xSPI_MOTO_FORMAT_MODE_0 |
//!                                        xSPI_MODE_SLAVE         |                                                
//!                                        xSPI_MSB_FIRST          |
//!                                        xSPI_DATA_WIDTH8);
//!     xSPISSSet(SPI2_BASE, SPI_SS_HARDWARE, xSPI_SS0);
//! 
//! 
//! \return None.
//
//*****************************************************************************
void xSPISSSet(unsigned long ulBase, unsigned long ulSSMode, 
                      unsigned long ulSlaveSel)
{
    //unsigned long ulTemp; 
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    xASSERT((ulSSMode == SPI_SS_HARDWARE) || (ulSSMode == SPI_SS_SOFTWARE));
    xASSERT((ulSlaveSel == xSPI_SS0) || (ulSlaveSel == xSPI_SS_NONE));

    #if 0   //Commented by Cedar

    xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSM;
    ulTemp = xHWREG(ulBase + SPI_CR1) & SPI_CR1_MSTR;
    if(ulTemp == SPI_CR1_MSTR)
    {
        if(ulSSMode == SPI_SS_HARDWARE)
        {
            xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSM;
            //  xHWREG(ulBase + SPI_CR2) |= SPI_CR2_SSOE;
        }
        else if(ulSSMode == SPI_SS_SOFTWARE)
        {
            xHWREG(ulBase + SPI_CR1) |= SPI_CR1_SSM;
            xHWREG(ulBase + SPI_CR1) |= SPI_CR1_SSI;

        }
    }
    else if(ulTemp == 0)
    {
        if(ulSSMode == SPI_SS_HARDWARE)
        {
            xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSM;
        }
        else if(ulSSMode == SPI_SS_SOFTWARE)
        {
            xHWREG(ulBase + SPI_CR1) |= SPI_CR1_SSM ;
            xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSI;
        }
    }
    #endif

    (void) ulSlaveSel; //this parameter is useless
    if(ulSSMode == SPI_SS_SOFTWARE)
    {
        xHWREG(ulBase + SPI_CR1) |= SPI_CR1_SSM;
        xHWREG(ulBase + SPI_CR1) |= SPI_CR1_SSI;
    }
    else
    {
        xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSM;

        if(xHWREG(ulBase + SPI_CR1) & SPI_CR1_MSTR)    //Master Mode
        {
            xHWREG(ulBase + SPI_CR2) |= SPI_CR2_SSOE;
        }
        else                                           //Slave Mode
        {
            xHWREG(ulBase + SPI_CR2) &= ~SPI_CR2_SSOE;
        }
    }

}

//*****************************************************************************
//
//! \brief Configures the synchronous serial interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulBitRate specifies the clock rate.
//! \param ulConfig is the required configuration of the SPI.
//!
//! This function configures the synchronous serial interface.  It sets
//! the SSI protocol, mode of operation, bit rate, and data width and the first
//! bit.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The Protocol of SPI can be one of the following values:
//! \b SPI_FORMAT_MODE_0, \b SPI_FORMAT_MODE_1, \b SPI_FORMAT_MODE_2,
//! \b SPI_FORMAT_MODE_3. 
//! The Motorola frame formats imply the following polarity and phase 
//! configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   SPI_FORMAT_MODE_0
//!   0       1   SPI_FORMAT_MODE_1
//!   1       0   SPI_FORMAT_MODE_2
//!   1       1   SPI_FORMAT_MODE_3
//! </pre>
//!  
//! The SPI module can operate as a master or slave;  The Mode of SPI
//! can be one of the following values: \b SPI_MODE_MASTER, or
//! \b SPI_MODE_SLAVE.
//!
//! The \e ulBitRate parameter defines the bit rate for the SPI.  This bit rate
//! must satisfy the following clock ratio criteria:
//!
//! - 0 !=  bit rate (master mode)
//!
//! The width of the data transfers can be a value between 1 and 32, inclusive.
//! It can be one of the following values: \b SPI_DATA_WIDTH8, \b SPI_DATA_WIDTH16.
//! 
//! The first bit of the data transfers, can be one of the following values:
//! \b SPI_MSB_FIRST, or \b SPI_LSB_FIRST.
//! 
//! The bidirectional data mode, can be one of the following values:
//! \b SPI_2LINE_FULL, \b SPI_1LINE_RX, \b SPI_1LINE_TX, or \b SPI_2LINE_RX.
//!
//! \return None.
//
//*****************************************************************************
void
SPIConfig(unsigned long ulBase, unsigned long ulBitRate,
          unsigned long ulConfig)
{
    unsigned long ulPCLK;
    unsigned long ulPreDiv;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    xASSERT(((ulConfig & 0x00000003) == SPI_FORMAT_MODE_0) ||
            ((ulConfig & 0x00000003) == SPI_FORMAT_MODE_1) ||
            ((ulConfig & 0x00000003) == SPI_FORMAT_MODE_3) ||
            ((ulConfig & 0x00000003) == SPI_FORMAT_MODE_4));
    xASSERT(((ulConfig & 0x00000004) == SPI_MODE_MASTER) ||
            ((ulConfig & 0x00000004) == SPI_MODE_SLAVE));
    xASSERT(((ulConfig & 0x00000080) == SPI_MSB_FIRST) ||
            ((ulConfig & 0x00000080) == SPI_LSB_FIRST));
    xASSERT(((ulConfig & 0x00000800) == SPI_DATA_WIDTH8) ||
            ((ulConfig & 0x00000800) == SPI_DATA_WIDTH16));
    xASSERT(((ulConfig & 0x0000C400) == SPI_2LINE_FULL) ||
            ((ulConfig & 0x0000C400) == SPI_1LINE_RX) ||
            ((ulConfig & 0x0000C400) == SPI_1LINE_TX) ||
            ((ulConfig & 0x0000C400) == SPI_2LINE_RX));
    xASSERT((ulBitRate != 0));

    //
    // Set the mode.
    //
        xHWREG(ulBase + SPI_CR1) &= ~0x00000087;
    xHWREG(ulBase + SPI_CR1) |= ulConfig;

    //
    // Set the clock rate.
    //
    if(ulBase == SPI1_BASE)
    {
        ulPCLK = SysCtlAPB2ClockGet();
    }
    else
    {
        ulPCLK = SysCtlAPB1ClockGet();
    }
    ulPreDiv = (((ulPCLK / ulBitRate)+1) >> 1) -1 ;
    if (ulPreDiv <= 2)
    {
        ulPreDiv = 0;
    }
    else if(ulPreDiv <= 4)
    {
        ulPreDiv = 1;
    }
    else if(ulPreDiv <= 8)
    {
        ulPreDiv = 2;
    }
    else if(ulPreDiv <= 16)
    {
        ulPreDiv = 3;
    }
    else if(ulPreDiv <= 32)
    {
        ulPreDiv = 4;
    }
    else if(ulPreDiv <= 64)
    {
        ulPreDiv = 5;
    }
    else if(ulPreDiv <= 128)
    {
        ulPreDiv = 6;
    }
    else
    {
        ulPreDiv = 7;
    }
    xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_BR_M;
    xHWREG(ulBase + SPI_CR1) |= (ulPreDiv << SPI_CR1_BR_S);
}

//*****************************************************************************
//
//! \brief Read  and write a data element from and to the SPI interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulWData is the data that was transmitted over the SPI interface.
//!
//! This function send transmitted data to the SPI interface of the specified
//! SPI module and gets received data from the SPI interface of the specified
//! SPI module and return that data.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the data that was received over the SPI interface.
//
//*****************************************************************************
unsigned long
SPISingleDataReadWrite(unsigned long ulBase, unsigned long ulWData)
{
    unsigned long ulReadTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    //
    // Wait until there is space.
    //
    while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXE));
    xHWREG(ulBase + SPI_DR) = ulWData;

    //
    // Wait until there is data to be read.
    //
    while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_RXNE));
    ulReadTemp = xHWREG(ulBase + SPI_DR);

    return ulReadTemp;
}

//*****************************************************************************
//
//! \brief Gets a data element from the SPI interface.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SSI interface.
//! \param ulLen specifies the length of data will be read.
//!
//! This function gets received data from the interface of the specified
//! SPI module and places that data into the location specified by the
//! \e pulData parameter.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDataRead(unsigned long ulBase, void *pulRData, unsigned long ulLen)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    for (i=0; i<ulLen; i++)
    {
        if ((xHWREG(ulBase + SPI_CR1) & SPI_CR1_DFF) != SPI_CR1_DFF)
        {
            ((unsigned char*)pulRData)[i] = 
            SPISingleDataReadWrite(ulBase, 0xFF);
        }
        else
        {
            ((unsigned short*)pulRData)[i] = 
            SPISingleDataReadWrite(ulBase, 0xFFFF);
        }   
    }
}

//*****************************************************************************
//
//! \brief Write  datas element to the SPI interface.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulWData is a pointer to a storage location for data that was
//! transmitted over the SSI interface.
//! \param ulLen specifies the length of data will be write.
//!
//! This function transmitted data to the interface of the specified
//! SPI module .
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SSIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDataWrite(unsigned long ulBase, void *pulWData, unsigned long ulLen)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    for (i=0; i<ulLen; i++)
    {
        if ((xHWREG(ulBase + SPI_CR1) & SPI_CR1_DFF) != SPI_CR1_DFF)
        {
            SPISingleDataReadWrite(ulBase, ((unsigned char*)pulWData)[i]);
        }
        else
        {
            SPISingleDataReadWrite(ulBase, ((unsigned short*)pulWData)[i]);
        }   
    }
}

//*****************************************************************************
//
//! \brief Puts a data element into the SPI transmit FIFO.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulData is the data to be transmitted over the SPI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SPI module.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDataPut(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    //
    // Wait until there is space.
    //
    while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXE))
    {
    }

    //
    // Write the data to the SPI.
    //
    xHWREG(ulBase + SPI_DR) = ulData;
}

//*****************************************************************************
//
//! \brief Puts a data element into the SPI transmit FIFO.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulData is the data to be transmitted over the SSI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SSI module.  If there is no space in the FIFO, then this function
//! returns a zero.
//!
//! This function replaces the original SSIDataNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>SPI.h</tt> to map
//! the original API to this API.
//!
//! \return Returns the number of elements written to the SSI transmit FIFO.
//
//*****************************************************************************
long
SPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    //
    // Check for space to write.
    //
    if(xHWREG(ulBase + SPI_SR) & SPI_SR_TXE)
    {
        xHWREG(ulBase + SPI_DR) = ulData;
        return(1);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
//! \brief Gets a data element from the SPI receive FIFO.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SPI interface.
//!
//! This function gets received data from the receive FIFO of the specified
//! SPI module and places that data into the location specified by the
//! \e pulData parameter.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDataGet(unsigned long ulBase, unsigned long *pulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    //
    // Wait until there is data to be read.
    //
    while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_RXNE))
    {
    }

    //
    // Read data from SSI.
    //
    *pulData = xHWREG(ulBase + SPI_DR);
}

//*****************************************************************************
//
//! \brief Gets a data element from the SPI receive FIFO.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SPI interface.
//!
//! This function gets received data from the receive FIFO of the specified SPI
//! module and places that data into the location specified by the \e ulData
//! parameter.  If there is no data in the FIFO, then this function  returns a
//! zero.
//!
//! This function replaces the original SPIDataNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>ssi.h</tt> to map
//! the original API to this API.
//!
//! \return Returns the number of elements read from the SPI receive FIFO.
//
//*****************************************************************************
long
SPIDataGetNonBlocking(unsigned long ulBase, unsigned long *pulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    //
    // Check for data to read.
    //
    if(xHWREG(ulBase + SPI_SR) & SPI_SR_RXNE)
    {
        *pulData = xHWREG(ulBase + SPI_DR);
        return(1);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
//! \brief Enable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulIntFlags specifies the type of SPI interrupt.
//! 
//! The ulIntFlags parameter is the logical OR of several different values:
//! \b SPI_INT_RX, \b SPI_INT_TX, or \b SPI_INT_ERRE.
//!
//! This function is to enable the SPI interrupt of the specified SPI port 
//! and install the callback function.
//!
//! \return None.
//
//*****************************************************************************
void 
SPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    xHWREG(ulBase + SPI_CR2) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified SPI Port.
//!
//! \param ulPort is the base address of the SPI port.
//! \param xtI2CCallback is callback for the specified SPI Port.
//!
//! Init interrupts callback for the specified SPI Port.
//!
//! \return None.
//
//*****************************************************************************
void 
SPIIntCallbackInit(unsigned long ulBase, xtEventCallback xtSPICallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    switch(ulBase)
    {
        case SPI1_BASE:
        {
            g_pfnSPIHandlerCallbacks[0] = xtSPICallback;
            break;
        }
        case SPI2_BASE:
        {
            g_pfnSPIHandlerCallbacks[1] = xtSPICallback;
            break;
        }
        case SPI3_BASE:
        {
            g_pfnSPIHandlerCallbacks[2] = xtSPICallback;
            break;
        }
        default:
            break;
    }
}

//*****************************************************************************
//
//! \brief Disable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulIntFlags specifies the type of SPI interrupt.
//! 
//! The ulIntFlags parameter is the logical OR of several different values:
//! \b SPI_INT_RX, \b SPI_INT_TX, or \b SPI_INT_ERRE.
//!
//! This function is to disable the SPI interrupt of the specified SPI port 
//!
//! \return None.
//
//*****************************************************************************
void 
SPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    xHWREG(ulBase + SPI_CR2) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Get the SPI interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function is to get the SPI interrupt flag of the specified SPI port 
//!
//! \return the SPI interrupt flag.It can be the following values:
//! \b .
//
//*****************************************************************************
unsigned long 
SPIIntFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    return (xHWREG(ulBase + SPI_SR));
}

//*****************************************************************************
//
//! \brief Clear the SPI interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function is to clear the SPI interrupt flag of the specified SPI port 
//!
//! \return None.
//
//*****************************************************************************
void
SPIIntFlagClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    xHWREG(ulBase + SPI_SR) |= SPI_SR_CRCERR;
}

//*****************************************************************************
//
//! \brief Check the busy status of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the busy status of the specified SPI module.
//!
//! \return Returns the busy status of the specified SPI port.
//! \b xtrue The SPI port is in busy,or \b xfalse The SPI port is not in busy.
//
//*****************************************************************************
xtBoolean
SPIIsBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_BSY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Enable the DMA of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulDmaMode specifies the SPI module base address.
//!
//! This function enable the DMA of the specified SPI port.
//!
//! The \e ulDmaMode parameter can be one of the following values:
//! \b SPI_DMA_RX, \b SPI_DMA_TX ,or \b SPI_DMA_BOTH.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDMAEnable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    xHWREG(ulBase + SPI_CR2) &= ~(SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
    xHWREG(ulBase + SPI_CR2) |= ulDmaMode;
}

//*****************************************************************************
//
//! \brief Disable the DMA of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulDmaMode specifies the SPI module base address.
//!
//! This function disable the DMA of the specified SPI port.
//!
//! The \e ulDmaMode parameter can be one of the following values:
//! \b SPI_DMA_RX, \b SPI_DMA_TX ,or \b SPI_DMA_BOTH.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDMADisable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    xHWREG(ulBase + SPI_CR2) &= ~ulDmaMode;
}

//*****************************************************************************
//
//! \brief Enable the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function enable the specified SPI port.
//!
//!
//! \return None.
//
//***************************************************************************** 
void
SPIEnble(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    xHWREG(ulBase + SPI_CR1) |= SPI_CR1_SPE;
}

//*****************************************************************************
//
//! \brief Disable the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function disable the specified SPI port.
//!
//! \return None.
//
//***************************************************************************** 
void
SPIDisble(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SPE;
}

//*****************************************************************************
//
//! \brief Set or Clear the internal software SSI bit of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSI specifies the SSI bit value.
//!
//! The \e ulSSI can be one of the following values:
//! \b SPI_SSSET, \b SPI_SSRESET.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
SPISSIConfig(unsigned long ulBase, unsigned long ulSSI)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    xASSERT((ulSlaveSel == SPI_SS0));
    
    xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSI;
    xHWREG(ulBase + SPI_CR1) |= ulSSI;
}

//*****************************************************************************
//
//! \brief Enables or disables the SS output for the selected SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSOutPut new state of the SPIx SS output. 
//!
//! The \e ulSSI can be one of the following values:
//! \b SPI_SSOE_ENABLE, \b SPI_SSOE_DISABLE.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
SPISSOutputConfig(unsigned long ulBase, unsigned long ulSSOutPut)
{
      //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    xASSERT((ulSSOutPut == SPI_SSOE_ENABLE) ||
              (ulSSOutPut == SPI_SSOE_DISABLE)); 
    
    xHWREG(ulBase + SPI_CR2) &= ~SPI_CR2_SSOE;
    xHWREG(ulBase + SPI_CR2) |= ulSSOutPut;
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSMode specifies the SS is hardware control or software control.
//! \param ulSlaveSel specifies the slave select pins which will be used.
//!
//! The \e ulSSMode can be one of the following values:
//! \b SPI_SS_HARDWARE, \b SPI_SS_SOFTWARE.
//!
//! \return None.
//
//*****************************************************************************
void 
SPISSModeConfig(unsigned long ulBase, unsigned long ulSSMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_SSM;
    xHWREG(ulBase + SPI_CR1) |= ulSSMode;
}

//*****************************************************************************
//
//! \brief Check the status of the Tx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the Tx buffer status of the specified SPI module.
//!
//! \return Returns the Tx buffer status of the specified SPI port.
//! \b xtrue The Tx buffer is in empty,or \b xfalse The Tx buffer is not empty.
//
//*****************************************************************************
xtBoolean
SPIIsTxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_TXE) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the Rx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the Rx buffer status of the specified SPI module.
//!
//! \return Returns the Rx buffer status of the specified SPI port.
//! \b xtrue The Rx buffer is not empty,or \b xfalse The Rx buffer is empty.
//
//*****************************************************************************
xtBoolean
SPIIsRxNotEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_RXNE) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Set the CRC polynomial register of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulCRCPol specifies the the polynomial for the CRC calculation.
//!
//! This function set the CRC polynomial register of the specified SPI module.
//!
//! \return None
//
//*****************************************************************************
void
SPICRCPolSet(unsigned long ulBase, unsigned long ulCRCPol)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    xHWREG(ulBase + SPI_CRCPR) = ulCRCPol;
}

//*****************************************************************************
//
//! \brief Get the CRC polynomial register of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function get the CRC polynomial register of the specified SPI module.
//!
//! \return the the polynomial for the CRC calculation.
//
//*****************************************************************************
unsigned long
SPICRCPolGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    return xHWREG(ulBase + SPI_CRCPR);
}

//*****************************************************************************
//
//! \brief Get the computed CRC value of the subsequently transmitted bytes
//! of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function get the computed CRC value of the subsequently transmitted 
//! bytes of the specified SPI module.
//!
//! \return the computed CRC value of the subsequently transmitted bytes.
//
//*****************************************************************************
unsigned long
SPITXCRCGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    return xHWREG(ulBase + SPI_TXCRCR);
}

//*****************************************************************************
//
//! \brief Get the computed CRC value of the subsequently received
//!  bytes of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function get the computed CRC value of the subsequently received of
//! the specified SPI module.
//!
//! \return the computed CRC value of the subsequently received.
//
//*****************************************************************************
unsigned long
SPIRxCRCGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));
    
    return xHWREG(ulBase + SPI_RXCRCR);
}

//*****************************************************************************
//
//! \brief Enable the CRC of specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function enable the CRC of specified SPI port.
//!
//!
//! \return None.
//
//***************************************************************************** 
void
SPICRCEnble(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    xHWREG(ulBase + SPI_CR1) |= SPI_CR1_CRCEN;
}

//*****************************************************************************
//
//! \brief Disable the CRC of specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function disable the CRC of specified SPI port.
//!
//!
//! \return None.
//
//***************************************************************************** 
void
SPICRCDisble(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI3_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE));

    xHWREG(ulBase + SPI_CR1) &= ~SPI_CR1_CRCEN;
}
