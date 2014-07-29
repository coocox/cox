//*****************************************************************************
//
//! \file spi.c
//! \brief Driver for the SPI
//! \version V2.2.1.0
//! \date 6/15/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox
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
#include "CoX.h"
#include "hw_sysctl.h"
#include "hw_spi.h"

//*****************************************************************************
//
// An array is SPI Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnSPIHandlerCallbacks[4]={0};

//*****************************************************************************
//
//! \brief SPI0 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI0 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One transaction done interrupt
//! and 3-wire SPI start interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI0_IRQHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI0_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_STATUS);

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_STATUS) |= ulEventFlags;
    
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
//! \brief SPI1 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI1 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One transaction done interrupt
//! and 3-wire SPI start interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI1_IRQHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI1_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_STATUS);
    
    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_STATUS) |= ulEventFlags;
    
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
//! \brief SPI2 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI2 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One transaction done interrupt
//! and 3-wire SPI start interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI2_IRQHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI2_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_STATUS);

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_STATUS) |= ulEventFlags;
    
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
//! \brief SPI3 interrupt handler. Clear the SPI interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the SPI3 interrupt handler,it will Clear the SPI 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One transaction done interrupt
//! and 3-wire SPI start interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3_IRQHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI3_BASE;

    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_STATUS);

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_STATUS) |= ulEventFlags;

    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[3])
    {
        g_pfnSPIHandlerCallbacks[3](0, 0, ulEventFlags, 0);
    }
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSMode specifies the SS is hardware control or software control.
//! Details please reference to \ref xSPI_SlaveSelMode.
//! \param ulSlaveSel specifies the slave select pins which will be used.
//! Details please reference to \ref xSPI_SlaveSel.
//!
//! This function is to Set the slave select pins of the 
//! specified SPI port.
//!
//! The \e ulSSMode can be one of the following values:
//! \b xSPI_SS_HARDWARE, \b xSPI_SS_SOFTWARE.
//! Details please reference to \ref xSPI_SlaveSelMode_CoX.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b xSPI_SS_NONE, \b xSPI_SS0,\b xSPI_SS1, or \b xSPI_SS0_SS1.
//! Details please reference to \ref xSPI_SlaveSel_CoX.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
xSPISSSet(unsigned long ulBase, unsigned long ulSSMode, 
          unsigned long ulSlaveSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE) );
    xASSERT((ulSlaveSel == SPI_SS_NONE) || (ulSlaveSel == SPI_SS0) ||
            (ulSlaveSel == SPI_SS1) || (ulSlaveSel == SPI_SS0_SS1));
    xHWREG(ulBase + SPI_SSR) |= ulSSMode;
    xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SSR_M;
    xHWREG(ulBase + SPI_SSR) |= ulSlaveSel;
}

//*****************************************************************************
//
//! \brief Configures the synchronous serial interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulMode specifies the mode of operation.
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
//! \b SPI_FORMAT_MODE_3, \b SPI_FORMAT_MODE_4, \b SPI_FORMAT_MODE_5. 
//! \b SPI_FORMAT_MODE_6, or \b SPI_FORMAT_MODE_7. 
//! The Motorola frame formats imply the following polarity and phase 
//! configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   SPI_FORMAT_MODE_1
//!   0       1   SPI_FORMAT_MODE_2
//!   1       0   SPI_FORMAT_MODE_6
//!   1       1   SPI_FORMAT_MODE_5
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
//! It can be one of the following values: \b SPI_DATA_WIDTH1,\b SPI_DATA_WIDTH2
//! \b SPI_DATA_WIDTH3,\b SPI_DATA_WIDTH4,\b SPI_DATA_WIDTH5,\b SPI_DATA_WIDTH6,
//! \b SPI_DATA_WIDTH7,\b SPI_DATA_WIDTH8,\b SPI_DATA_WIDTH9,\b SPI_DATA_WIDTH10,
//! \b SPI_DATA_WIDTH11,\b SPI_DATA_WIDTH12,\b SPI_DATA_WIDTH13,
//! \b SPI_DATA_WIDTH11,\b SPI_DATA_WIDTH15,\b SPI_DATA_WIDTH16,
//! \b SPI_DATA_WIDTH17,\b SPI_DATA_WIDTH18,\b SPI_DATA_WIDTH19,
//! \b SPI_DATA_WIDTH20,\b SPI_DATA_WIDTH21,\b SPI_DATA_WIDTH22,
//! \b SPI_DATA_WIDTH23,\b SPI_DATA_WIDTH24,\b SPI_DATA_WIDTH25,
//! \b SPI_DATA_WIDTH26,\b SPI_DATA_WIDTH27,\b SPI_DATA_WIDTH28,
//! \b SPI_DATA_WIDTH29,\b SPI_DATA_WIDTH30,\b SPI_DATA_WIDTH31,
//! \b SPI_DATA_WIDTH32,
//! 
//! The first bit of the data transfers, can be one of the following values:
//! \b SPI_MSB_FIRST, or \b SPI_LSB_FIRST.
//!
//! \return None.
//
//*****************************************************************************
void
xSPIConfigSet(unsigned long ulBase, unsigned long ulBitRate,
                    unsigned long ulConfig)
{
    unsigned long ulPCLK;
    unsigned long ulPreDiv;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    xASSERT(((ulConfig & 0x00000806) == SPI_FORMAT_MODE_0) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_1) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_2) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_3) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_4) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_5) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_6) ||
            ((ulConfig & 0x00000806) == SPI_FORMAT_MODE_7));
    xASSERT(((ulConfig & 0x00040000) == SPI_MODE_MASTER) ||
            ((ulConfig & 0x00040000) == SPI_MODE_SLAVE));
    xASSERT((((ulConfig & 0x000000F8) >> 3) >= 0) && 
            (((ulConfig & 0x000000F8) >> 3) <= 31));
    xASSERT((ulBitRate != 0));

    //
    // Set the mode.
    //
    xHWREG(ulBase + SPI_CNTRL) |= ulConfig;

    //
    // Set the clock rate.
    //
    ulPCLK = xSysCtlClockGet();
    ulPreDiv = (((ulPCLK / ulBitRate) + 1) >> 1) - 1 ;
    if (ulPreDiv > 65535)
    {
        ulPreDiv = 65535;
    }
    if (ulPreDiv < 1)
    {
        ulPreDiv = 1;
    }
    
    xHWREG(ulBase + SPI_DIVIDER) = ulPreDiv;

    // The slave select signal SPI_SS0/1 is active on low-level
    xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SS_LVL;
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
//! SSIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the data that was received over the SPI interface.
//
//*****************************************************************************
unsigned long
xSPISingleDataReadWrite(unsigned long ulBase, unsigned long ulWData)
{
    unsigned long ulReadTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until SPI is not busy, data to be write.
    //
    while((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY))
    {
    }
    xHWREG(ulBase + SPI_TX) = ulWData;

    //
    // 
    //
    //xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_SPIEN;
    
    //
    // Wait until there is data to be read.
    //
    while((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY))
    {
    }
    
    //
    // write data to SPI.
    //
    ulReadTemp = xHWREG(ulBase + SPI_RX);
    return ulReadTemp;
}

//*****************************************************************************
//
//! \brief Gets the number of bits transferred per frame.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function gets the number of bits transferred per frame.
//!
//! \note if return 0 that means number of bits is 32.
//!
//! \return the number of bits transferred per frame.
//
//*****************************************************************************
unsigned char
xSPIBitLengthGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    return ((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_TX_BIT_LEN_M)             
            >> SPI_CNTRL_TX_BIT_LEN_S);
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
//! SSIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************
void
xSPIDataRead(unsigned long ulBase, void *pulRData, unsigned long ulLen)
{
    unsigned long i;
    unsigned char ucBitLength = xSPIBitLengthGet(ulBase);
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    for (i=0; i<ulLen; i++)
    {
        if (ucBitLength <= 8)
        {
            ((unsigned char*)pulRData)[i] = 
            xSPISingleDataReadWrite(ulBase, 0xFF);
        }
        else if (ucBitLength >= 8 && ucBitLength <= 16)
        {
            ((unsigned short*)pulRData)[i] = 
            xSPISingleDataReadWrite(ulBase, 0xFFFF);
        }   
        else
        {
            ((unsigned long*)pulRData)[i] = 
            xSPISingleDataReadWrite(ulBase, 0xFFFFFF);
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
xSPIDataWrite(unsigned long ulBase, void *pulWData, unsigned long ulLen)
{
    unsigned long i;
    unsigned char ucBitLength = xSPIBitLengthGet(ulBase);
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    for (i=0; i<ulLen; i++)
    {
        if (ucBitLength <= 8)
        {
            xSPISingleDataReadWrite(ulBase, ((unsigned char*)pulWData)[i]);
        }
        else if (ucBitLength >= 8 && ucBitLength <= 16)
        {
            xSPISingleDataReadWrite(ulBase, ((unsigned short*)pulWData)[i]);
        }   
        else
        {
            xSPISingleDataReadWrite(ulBase, ((unsigned long*)pulWData)[i]);
        }
    }
}

//*****************************************************************************
//
//! \brief Write data element to the SPI interface with block.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulWData is data that was transmitted over the SPI interface.
//!
//! This function transmitted data to the interface of the specified
//! SPI module with block. when the TX and TX shift are both empty or in FIFO
//! mode the TX FIFO depth is equal to or less than the trigger level, the
//! data element can be transmitted, otherwise the data element will be blocked
//! until can be transmitted.
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
xSPIDataPut(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until there is space.
    //
    while((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY))
    {
    }

    //
    // Write the data to the SPI.
    //
    xHWREG(ulBase + SPI_TX) = ulData;
}

//*****************************************************************************
//
//! \brief Write data element to the SPI interface with Noblock.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulWData is data that was transmitted over the SPI interface.
//!
//! This function transmitted data to the interface of the specified
//! SPI module with Noblock.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the number of data that has been transfered.
//
//*****************************************************************************
long
xSPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Check for space to write.
    //
    if(!((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY)))
    {
        xHWREG(ulBase + SPI_TX) = ulData;
        return(1);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
//! \brief Gets a data element from the SPI interface with block.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SPI interface.
//!
//! This function gets received data from the interface of the specified
//! SPI module with block. when the RX not empty flag is set, the data element
//! can be transmitted, otherwise the data element will be blocked until can be
//! transmitted.
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
xSPIDataGet(unsigned long ulBase, unsigned long *pulData)
{
    unsigned char ucBitLength = xSPIBitLengthGet(ulBase);

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until there is data to be read.
    //
    while((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY))
    {
    }

    //
    // write data to SPI.
    //
    if (ucBitLength <= 8)
    {
        *pulData = xHWREG(ulBase + SPI_RX) & 0xFF;
    }
    else if(ucBitLength <= 16)
    {
        *pulData = xHWREG(ulBase + SPI_RX) & 0xFFFF;
    }
    else
    {
    	*pulData = xHWREG(ulBase + SPI_RX);
    }
}

//*****************************************************************************
//
//! \brief Gets a data element from the SPI interface with Noblock.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SPI interface.
//!
//! This function gets received data from the interface of the specified
//! SPI module with Noblock.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the number of data that has been received.
//
//*****************************************************************************
long
xSPIDataGetNonBlocking(unsigned long ulBase, unsigned long *pulData)
{
    unsigned long ulTemp;
    unsigned char ucBitLength = xSPIBitLengthGet(ulBase);

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    ulTemp = xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY;
    if(!ulTemp)
    {
        return 0;
    }

    if(ucBitLength <= 8 && ucBitLength != 0)
    {
        *pulData = xHWREG(ulBase + SPI_RX);
    }
    else
    {
        *pulData = xHWREG(ulBase + SPI_RX);
    }

    return 1;
}

//*****************************************************************************
//
//! \brief Enable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulIntFlags specifies the type of SPI interrupt.
//!
//! This function is to enable the SPI interrupt of the specified SPI port 
//! and install the callback function.
//!
//! \return None.
//
//*****************************************************************************
void 
xSPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    if(ulIntFlags & SPI_INT_EOT)
    {
    	xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IE;
    }
    if(ulIntFlags & SPI_INT_RX)
    {
    	xHWREG(ulBase + SPI_FIFOCTL) |= SPI_FIFOCTL_RX_INTEN;
    }
    if(ulIntFlags & SPI_INT_TX)
    {
        xHWREG(ulBase + SPI_FIFOCTL) |= SPI_FIFOCTL_TX_INTEN;
    }
    if(ulIntFlags & SPI_INT_ERROR)
    {
        xHWREG(ulBase + SPI_SSR) |= (SPI_SSR_SLVER0_INTEN | SPI_SSR_SLVER1_INTEN);
    }
    if(ulIntFlags & SPI_INT_RX_OVERRUN)
    {
    	xHWREG(ulBase + SPI_FIFOCTL) |= SPI_FIFOCTL_RXOV_INTEN;
    }
    if(ulIntFlags & SPI_INT_TIMEOUT)
    {
    	xHWREG(ulBase + SPI_SSR) |= SPI_SSR_SLVTO_INTEN;
    }
    if(ulIntFlags & SPI_INT_SLAVE_TIMEOUT)
    {
    	xHWREG(ulBase + SPI_SSR) |= SPI_SSR_SLVTO_INTEN;
    }
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
xSPIIntCallbackInit(unsigned long ulBase, xtEventCallback xtSPICallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    switch(ulBase)
    {
        case SPI0_BASE:
        {
            g_pfnSPIHandlerCallbacks[0] = xtSPICallback;
            break;
        }
        case SPI1_BASE:
        {
            g_pfnSPIHandlerCallbacks[1] = xtSPICallback;
            break;
        }
        case SPI2_BASE:
        {
            g_pfnSPIHandlerCallbacks[2] = xtSPICallback;
            break;
        }
        case SPI3_BASE:
        {
            g_pfnSPIHandlerCallbacks[3] = xtSPICallback;
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
//!
//! This function is to disable the SPI interrupt of the specified SPI port 
//!
//! \return None.
//
//*****************************************************************************
void 
xSPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    if(ulIntFlags & SPI_INT_EOT)
    {
    	xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_IE;
    }
    if(ulIntFlags & SPI_INT_RX)
    {
    	xHWREG(ulBase + SPI_FIFOCTL) &= ~SPI_FIFOCTL_RX_INTEN;
    }
    if(ulIntFlags & SPI_INT_TX)
    {
        xHWREG(ulBase + SPI_FIFOCTL) &= ~SPI_FIFOCTL_TX_INTEN;
    }
    if(ulIntFlags & SPI_INT_ERROR)
    {
        xHWREG(ulBase + SPI_SSR) &= ~(SPI_SSR_SLVER0_INTEN | SPI_SSR_SLVER1_INTEN);
    }
    if(ulIntFlags & SPI_INT_RX_OVERRUN)
    {
    	xHWREG(ulBase + SPI_FIFOCTL) &= ~SPI_FIFOCTL_RXOV_INTEN;
    }
    if(ulIntFlags & SPI_INT_TIMEOUT)
    {
    	xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SLVTO_INTEN;
    }
    if(ulIntFlags & SPI_INT_SLAVE_TIMEOUT)
    {
    	xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SLVTO_INTEN;
    }
}

//*****************************************************************************
//
//! \brief Get the SPI interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param xbMasked is \b false if the raw interrupt status is required or
//! \b true if the masked interrupt status is required.
//!
//! This function is to get the SPI interrupt flag of the specified SPI port 
//!
//! \return the SPI interrupt flag.It can be the following values:
//! \b .
//
//*****************************************************************************
unsigned long
xSPIStatusGet(unsigned long ulBase, xtBoolean xbMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT(bMasked == xfalse);

    return (xHWREG(ulBase + SPI_STATUS) & 0x000C14EE);
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
SPIIntFlagClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xHWREG(ulBase + SPI_STATUS) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Enable the automatic slave select function of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulSlaveSel specifies the slave select pins which will be used.
//!
//! This function is to enable the automatic slave select function of the 
//! specified SPI port.And set the specified slave select pin.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b SPI_SS_NONE, \b SPI_SS0,\b SPI_SS1, or \b SPI_SS0_SS1.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void
SPIAutoSSEnable(unsigned long ulBase, unsigned long ulSlaveSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT((ulSlaveSel == SPI_SS_NONE) || (ulSlaveSel == SPI_SS0) ||
            (ulSlaveSel == SPI_SS1) || (ulSlaveSel == SPI_SS0_SS1));
    xHWREG(ulBase + SPI_SSR) |= SPI_SSR_AUTOSS;
    xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SSR_M;
    xHWREG(ulBase + SPI_SSR) |= ulSlaveSel;
}

//*****************************************************************************
//
//! \brief Disable the automatic slave select function of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function is to enable the automatic slave select function of the 
//! specified SPI port.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void
SPIAutoSSDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_AUTOSS;
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulSlaveSel specifies the slave select pins which will be used.
//!
//! This function is to Set the slave select pins of the 
//! specified SPI port.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b SPI_SS_NONE, \b SPI_SS0,\b SPI_SS1, or \b SPI_SS0_SS1.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void
SPISSSet(unsigned long ulBase, unsigned long ulSlaveSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) ||(ulBase == SPI3_BASE));
    xASSERT((ulSlaveSel == SPI_SS_NONE) || (ulSlaveSel == SPI_SS0) ||
            (ulSlaveSel == SPI_SS1) || (ulSlaveSel == SPI_SS0_SS1));
    xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SSR_M;
    xHWREG(ulBase + SPI_SSR) |= ulSlaveSel;
}

//*****************************************************************************
//
//! \brief Clear the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulSlaveSel specifies the slave select pins which will be used.
//!
//! This function is to Clear the slave select pins of the 
//! specified SPI port.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b SPI_SS_NONE, \b SPI_SS0,\b SPI_SS1, or \b SPI_SS0_SS1.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void
SPISSClear(unsigned long ulBase, unsigned long ulSlaveSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    xASSERT((ulSlaveSel == SPI_SS_NONE) || (ulSlaveSel == SPI_SS0) ||
            (ulSlaveSel == SPI_SS1) || (ulSlaveSel == SPI_SS0_SS1));
    
    xHWREG(ulBase + SPI_SSR) &= ~ulSlaveSel;
}

//*****************************************************************************
//
//! \brief Config the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulSSTriggerMode specifies the trigger mode of slave select pin.
//! \param ulSSActType specifies the active type of slave select pin.
//!
//! This function is to config the slave select pins of the 
//! specified SPI port.
//!
//! The \e ulSSTriggerMode can be one of the following values:
//! \b SPI_SS_EDGE_TRIGGER, or \b SPI_SS_LEVEL_TRIGGER.
//!
//! The \e ulSSActType can be one of the following values:
//! \b SPI_SS_ACTIVE_LOW_FALLING, or \b SPI_SS_ACTIVE_HIGH_RISING.
//!
//! \note \e ulSSTriggerMode is only for slave mode
//!
//! \return None.
//
//*****************************************************************************
void
SPISSConfig(unsigned long ulBase, unsigned long ulSSTriggerMode,
            unsigned long ulSSActType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    xASSERT((ulSSTriggerMode == SPI_SS_EDGE_TRIGGER) || 
            (ulSSTriggerMode == SPI_SS_LEVEL_TRIGGER));
    xASSERT((ulSSActType == SPI_SS_ACTIVE_LOW_FALLING) || 
            (ulSSActType == SPI_SS_ACTIVE_HIGH_RISING));
    
    xHWREG(ulBase + SPI_SSR) |= ulSSTriggerMode | ulSSActType;
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
xSPIIsBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    
    return ((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_BUSY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the Rx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the Rx buffer status of the specified SPI module.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function..
//!
//! \return Returns the Rx buffer status of the specified SPI port.
//! \b xtrue The Rx buffer is empty,or \b xfalse The Rx buffer is not empty.
//
//*****************************************************************************
xtBoolean
xSPIIsRxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    return ((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_RX_EMPTY)? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the Rx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the Rx buffer status of the specified SPI module.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function..
//!
//! \return Returns the Rx buffer status of the specified SPI port.
//! \b xtrue The Rx buffer is full,or \b xfalse The Rx buffer is not full.
//
//*****************************************************************************
xtBoolean
xSPIIsRxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    return ((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_RX_FULL)? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the Tx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the Tx buffer status of the specified SPI module.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function..
//!
//! \return Returns the Tx buffer status of the specified SPI port.
//! \b xtrue The Tx buffer is in empty,or \b xfalse The Tx buffer is not empty.
//
//*****************************************************************************
xtBoolean
xSPIIsTxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    return ((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_TX_EMPTY)? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the Tx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the Tx buffer status of the specified SPI module.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function..
//!
//! \return Returns the Tx buffer status of the specified SPI port.
//! \b xtrue The Tx buffer is in full,or \b xfalse The Tx buffer is not full.
//
//*****************************************************************************
xtBoolean
xSPIIsTxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    return ((xHWREG(ulBase + SPI_STATUS) & SPI_STATUS_TX_FULL)? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the FIFO buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the FIFO buffer status of the specified SPI module.
//!
//! \return Returns the FIFO buffer status of the specified SPI port.
//! the return can be the OR of the following values:
//! \b SPI_CNTRL_TX_FULL, \b SPI_CNTRL_RX_FULL, \b SPI_CNTRL_TX_EMPTY, or
//! \b SPI_CNTRL_RX_EMPTY.
//
//*****************************************************************************
unsigned long
SPIFIFOStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    return (xHWREG(ulBase + SPI_STATUS) & (SPI_STATUS_TX_FULL) ||
            (SPI_STATUS_RX_FULL) || (SPI_STATUS_TX_EMPTY) || (SPI_STATUS_RX_EMPTY));
}

//*****************************************************************************
//
//! \brief Clear the FIFO buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulRxTx specifies the FIFO buffer is Rx buffer or Tx buffer.
//!
//! This function Clear the FIFO buffer of the specified SPI module.
//!
//! \return None.
//
//*****************************************************************************
void
SPIFIFOClear(unsigned long ulBase, unsigned long ulRxTx)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    xHWREG(ulBase + SPI_FIFOCTL) |= ulRxTx;
}

//*****************************************************************************
//
//! \brief Enable/disable the FIFO mode of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param xtEnable enable the FIFO mode or not.
//! \param ulInterval specifies the suspend interval.
//!
//! This function enable/disable the FIFO mode of the specified SPI module.
//! If the caller enables FIFO mode,configure the setting of suspend cycle.
//!
//! The \e ulInterval can be 2~15 and 0.
//! 0 indicates the maximum suspend interval;
//! 2 indicates the minimum suspend interval.
//!
//! \return None.
//
//*****************************************************************************
void
SPIFIFOModeSet(unsigned long ulBase, xtBoolean xtEnable, 
               unsigned long ulInterval)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    xASSERT((ulInterval == 0) ||((ulInterval >= 2) && (ulInterval <= 15)));
    if (xtEnable)
    {
        xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_SP_CYCLE_M;
        xHWREG(ulBase + SPI_CNTRL) |= (ulInterval << SPI_CNTRL_SP_CYCLE_S);
        //xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_FIFO;
    }
    else
    {
        //xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_FIFO;
    }  
}

void
SPIFIFOTxThresholdSet(unsigned long ulBase, unsigned long ulThreshold)
{
    xHWREG(ulBase + SPI_FIFOCTL) &= ~SPI_FIFOCTL_TX_THRESHOLD_M;
    xHWREG(ulBase + SPI_FIFOCTL) |= (ulThreshold << SPI_FIFOCTL_TX_THRESHOLD_S);
}

void
SPIFIFORxThresholdSet(unsigned long ulBase, unsigned long ulThreshold)
{
    xHWREG(ulBase + SPI_FIFOCTL) &= ~SPI_FIFOCTL_RX_THRESHOLD_M;
    xHWREG(ulBase + SPI_FIFOCTL) |= (ulThreshold << SPI_FIFOCTL_RX_THRESHOLD_S);
}

//*****************************************************************************
//
//! \brief Enable/disable Byte Reorder function.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulByteReorder the options of Byte Reorder function and Byte Suspend
//! function.
//!
//! This function Enable/disable Byte Reorder function of the specified
//! SPI module.
//!
//! \note The Byte Reorder function is supported only in 16-, 24- and
//! 32-bit transaction mode. The Byte Suspend function is only available
//! in 32-bit transaction.
//!
//! \return None.
//
//*****************************************************************************
void
SPIByteReorderSet(unsigned long ulBase, xtBoolean xtEnable)
{
#ifdef xDEBUG
    unsigned char ucBitLength = xSPIBitLengthGet(ulBase);
#endif
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT((ucBitLength == 32) || (ucBitLength == 16) || (ucBitLength == 24));

    if(xtEnable)
        xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_REORDER;
    else
	   xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_REORDER;
}

//*****************************************************************************
//
//! \brief Enable/disable the 3 wire feature of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param xtEnable enable this fuction or not.
//!
//! This function enable the 3 wire feature. the controller start to transmit/
//!receive data after the GO_BUSY bit active and the serial clock input.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3WireFunction(unsigned long ulBase, xtBoolean xtEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    if (xtEnable)
    {
        xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_SLVSEL;
        xHWREG(ulBase + SPI_SSR) |= SPI_SSR_SLV3WIRE;
    }
    else
    {
        xHWREG(ulBase + SPI_SSR) &= ~SPI_SSR_SLV3WIRE;
        xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_SLVSEL;
    }
}

//*****************************************************************************
//
//! \brief Enable the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function enable the specified SPI port.
//!
//! \return None.
//
//*****************************************************************************
void xSPIEnable(unsigned long ulBase)
{
	xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_SPIEN;
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
void xSPIDisable(unsigned long ulBase)
{
	xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_SPIEN;
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
xSPIDMAEnable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    
    xHWREG(ulBase + SPI_DMACTL) |= ulDmaMode;
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
xSPIDMADisable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE)||(ulBase == SPI3_BASE) );
    
    xHWREG(ulBase + SPI_DMACTL) &= ~ulDmaMode;
}

void
SPIPDMAReset(unsigned long ulBase)
{
	xHWREG(ulBase + SPI_DMACTL) |= SPI_DMACTL_PDMA_RST;
}

void
SPIPDualIOEnable(unsigned long ulBase, unsigned long ulDir)
{
	xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_QUAL_IO_EN;
	if(ulDir & SPI_CNTRL_QD_IO_DIR)
	{
		xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_QD_IO_DIR;
	}
	else {
		xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_QD_IO_DIR;
	}
}

void
SPIPDualIODisable(unsigned long ulBase)
{
	xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_QUAL_IO_EN;
}

void
SPIPDuadIOEnable(unsigned long ulBase, unsigned long ulDir)
{
	xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_QUAD_IO_EN;
	if(ulDir & SPI_CNTRL_QD_IO_DIR)
	{
		xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_QD_IO_DIR;
	}
	else {
		xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_QD_IO_DIR;
	}
}

void
SPIPDuadIODisable(unsigned long ulBase)
{
	xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_QUAD_IO_EN;
}
