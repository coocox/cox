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
static xtEventCallback g_pfnSPIHandlerCallbacks[2]={0};

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
//! \return None.
//
//*****************************************************************************
void 
SPI0IntHandler(void)
{
    unsigned long ulFIFOFlags, ulFlags;
    unsigned long ulBase = SPI0_BASE;
    
    //
    // Gets interrupt status
    //
    ulFIFOFlags = xHWREG(ulBase + SPI_FSR);   
    ulFlags = xHWREG(ulBase + SPI_SR);
    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_FSR) &= ~ulFIFOFlags;
    xHWREG(ulBase + SPI_SR)	|= 0xff;
    
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[0])
    {
        g_pfnSPIHandlerCallbacks[0](0, 0, (ulFIFOFlags << 16) | ulFlags, 0);
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
//! \return None.
//
//*****************************************************************************
void 
SPI1IntHandler(void)
{
    unsigned long ulFIFOFlags, ulFlags;
    unsigned long ulBase = SPI1_BASE;
    
    //
    // Gets interrupt status
    //
    ulFIFOFlags = xHWREG(ulBase + SPI_FSR);   
    ulFlags = xHWREG(ulBase + SPI_SR);
    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_FSR) &= ~ulFIFOFlags;
    xHWREG(ulBase + SPI_SR)	|= 0x78;
    
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[1])
    {
        g_pfnSPIHandlerCallbacks[0](0, 0, (ulFIFOFlags << 16) | ulFlags, 0);
    }
}

//*****************************************************************************
//
//! \brief Eanble the SPI Module.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return None.
//
//*****************************************************************************
void 
SPIEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xHWREG(ulBase + SPI_CNTRL0) |= SPI_CNTRL0_EN;
}

//*****************************************************************************
//
//! \brief Disable the SPI Module.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return None.
//
//*****************************************************************************
void 
SPIDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xHWREG(ulBase + SPI_CNTRL0) &= ~SPI_CNTRL0_EN;
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSMode specifies the SS is hardware control or software control.
//! Details please reference to \ref xSPI_SlaveSelMode.
//! \param ulSlaveSel here is 0 to keep the number of parameters.
//!
//! The \e ulSSMode can be one of the following values:
//! \b xSPI_SS_HARDWARE, \b xSPI_SS_SOFTWARE.
//! Details please reference to \ref xSPI_SlaveSelMode_CoX.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    //
    //! Clear the bit first
    //! Select the SS Mode
    //
    xHWREG(ulBase + SPI_CNTRL1) &= ~SPI_CNTRL1_SELM;

    xHWREG(ulBase + SPI_CNTRL1) |= ulSSMode;
    
    //
    //! Set the SS pin
    //
    if(ulSSMode == xSPI_SS_SOFTWARE)
    {
        xHWREG(ulBase + SPI_CNTRL0) = SPI_CNTRL0_SELOEN;
        xHWREG(ulBase + SPI_CNTRL0) |= SPI_CNTRL0_SSELC;
    }
	else if(ulSSMode == xSPI_SS_HARDWARE)
	{
	    xHWREG(ulBase + SPI_CNTRL0) = SPI_CNTRL0_SELOEN;
	}

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
//! \b SPI_DATA_WIDTH11,\b SPI_DATA_WIDTH15,\b SPI_DATA_WIDTH16
//! 
//! The first bit of the data transfers, can be one of the following values:
//! \b SPI_MSB_FIRST, or \b SPI_LSB_FIRST.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(((ulConfig & 0x00000700) == SPI_FORMAT_MODE_1) ||
            ((ulConfig & 0x00000700) == SPI_FORMAT_MODE_2) ||
            ((ulConfig & 0x00000700) == SPI_FORMAT_MODE_5) ||
            ((ulConfig & 0x00000700) == SPI_FORMAT_MODE_6));
    xASSERT(((ulConfig & 0x00004000) == SPI_MODE_MASTER) ||
            ((ulConfig & 0x00004000) == SPI_MODE_SLAVE));
    xASSERT(((ulConfig & 0x0000000F) >= 0) && 
            ((ulConfig & 0x0000000F) <= 16));
    xASSERT((ulBitRate != 0));

	//
	// Clear the mode first
	//
    xHWREG(ulBase + SPI_CNTRL1) &= ~(SPI_CNTRL1_FORMAT_M | SPI_CNTRL1_MODE |
	                                 SPI_CNTRL1_FIRSTBIT);

    //
    // Set the mode.
    //
    xHWREG(ulBase + SPI_CNTRL1) |= ulConfig;

    //
    // Set the clock rate.
    //
    ulPCLK = SysCtlClockGet();
    ulPreDiv = (((ulPCLK / ulBitRate)+1) >> 1) -1 ;
    if (ulPreDiv > 65535)
    {
        ulPreDiv = 65535;
    }
    if (ulPreDiv < 1)
    {
        ulPreDiv = 1;
    }
    
    xHWREG(ulBase + SPI_CPR) = ulPreDiv;
}

//*****************************************************************************
//
//! \brief Read and write a data element from and to the SPI interface.
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
SPISingleDataReadWrite(unsigned long ulBase, unsigned long ulWData)
{
    unsigned long ulFlag, ulReadTemp;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    //
    // Wether in FIFO mode
    //
    ulFlag = xHWREG(ulBase + SPI_FCR) & SPI_FCR_FIFOEN;

    //
    // Wait Transmission Register or Transmit Buffer Empty flag is set.
    //
    if(ulFlag != SPI_FCR_FIFOEN)
    {
        while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXE))
        {
        }
    }
    else
    {
        while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXBE))
        {
        }
    }

    xHWREG(ulBase + SPI_DR) = ulWData;
    
    //
    // Wait until there is data to be read.
    // 
    while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_RXBNE))
    {
    }
    //
    // write data to SPI.
    //
    ulReadTemp = xHWREG(ulBase + SPI_DR);
    return ulReadTemp;
}

//*****************************************************************************
//
//! \brief Gets the number of bits transferred per frame.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function gets the number of bits transferred per frame.
//!
//! \note if return 0 that means number of bits is 32.
//!
//! \return the number of bits transferred per frame.
//
//*****************************************************************************
unsigned char
SPIBitLengthGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    return (xHWREG(ulBase + SPI_CNTRL1) & SPI_CNTRL1_DFL_M);
}

//*****************************************************************************
//
//! \brief Gets a data element from the SPI interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SPI interface.
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
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    for (i=0; i<ulLen; i++)
    {
        if (ucBitLength <= 8 && ucBitLength != 0)
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
//! \brief Read data from Rx registers.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Read data from Rx registers of the specified SPI
//! module and places that data into the location specified by the \e ulData
//! parameter.This function will not trigger a SPI data transfer. 
//!
//! This function replaces the original SSIDataNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>ssi.h</tt> to map
//! the original API to this API.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return Returns the number of elements read from the SPI Rx registers.
//
//*****************************************************************************
unsigned long
SPIRxRegisterGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Read data from SPI Rx Register.
    //
    return (xHWREG(ulBase + SPI_DR));
  
}

//*****************************************************************************
//
//! \brief Write datas element to the SPI interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulWData is a pointer to a storage location for data that was
//! transmitted over the SSI interface.
//! \param ulLen specifies the length of data will be write.
//!
//! This function transmitted data to the interface of the specified
//! SPI module .
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
SPIDataWrite(unsigned long ulBase, void *pulWData, unsigned long ulLen)
{
    unsigned long i;
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    for (i=0; i<ulLen; i++)
    {
        if (ucBitLength <= 8 && ucBitLength != 0)
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
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
    unsigned long ulFlag;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    //
    // Wether in FIFO mode
    //
    ulFlag = xHWREG(ulBase + SPI_FCR) & SPI_FCR_FIFOEN;

    //
    // Wait Transmission Register or Transmit Buffer Empty flag is set.
    //
    if(ulFlag != SPI_FCR_FIFOEN)
    {
        while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXE))
        {
        }
    }
    else
    {
        while(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXBE))
        {
        }
    }
    if(ucBitLength <= 8 && ucBitLength != 0)
    {
        xHWREG(ulBase + SPI_DR) = ulData & 0xFF;
    }
    else
    {
        xHWREG(ulBase + SPI_DR) = ulData & 0xFFFF;
    }
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
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
    unsigned long ulFlag;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Whether in FIFO mode
    //
    ulFlag = xHWREG(ulBase + SPI_FCR) & SPI_FCR_FIFOEN;

    //
    // Wait Transmission Register or Transmit Buffer Empty flag is set.
    //
    if(ulFlag != SPI_FCR_FIFOEN)
    {
        if(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXE))
        {
		        return 0;
        }
    }
    else
    {
        if(!(xHWREG(ulBase + SPI_SR) & SPI_SR_TXBE))
        {	
            return 0;
        }
    }  

    if(ucBitLength <= 8 && ucBitLength != 0)
    {
        xHWREG(ulBase + SPI_DR) = ulData & 0xFF;
    }
    else
    {
        xHWREG(ulBase + SPI_DR) = ulData & 0xFFFF;
    }

    return 1;
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
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Wait until there is data to be read.
    // 
    while(!((xHWREG(ulBase + SPI_SR) & SPI_SR_RXBNE)))
    {
    }

    //
    // write data to SPI.
    //
    if (ucBitLength <= 8 && ucBitLength != 0 )
    {
        *pulData = xHWREG(ulBase + SPI_DR) & 0xFF;
    }
    else
    {
        *pulData = xHWREG(ulBase + SPI_DR) & 0xFFFF;
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
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    ulTemp = xHWREG(ulBase + SPI_SR) & SPI_SR_RXBNE;
    if(!ulTemp)
    {
        return 0;
    }

    if(ucBitLength <= 8 && ucBitLength != 0)
    {
        *pulData = xHWREG(ulBase + SPI_DR);
    }
    else
    {
        *pulData = xHWREG(ulBase + SPI_DR);
    }

	return 1;
}

//*****************************************************************************
//
//! \brief Write data to Tx registers.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulData is a data that was write to the SPI interface.
//!
//! This function write data to Tx registers of the specified SPI
//! module and This function will not trigger a SPI data transfer. 
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return Returns the number of elements write to the SPI Tx registers.
//
//*****************************************************************************
void
SPITxRegisterSet(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Read data from SPI Rx Register.
    //
    xHWREG(ulBase + SPI_DR) = ulData;
}

//*****************************************************************************
//
//! \brief Enable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulIntFlags specifies the type of SPI interrupt.
//!
//! This function is to enable the SPI interrupt of the specified SPI port.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xHWREG(ulBase + SPI_IIER) |= ulIntFlags;
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    g_pfnSPIHandlerCallbacks[0] = xtSPICallback;
}
 

//*****************************************************************************
//
//! \brief Disable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulIntFlags specifies the type of SPI interrupt.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xHWREG(ulBase + SPI_IIER) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Get the SPI interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function is to get the SPI interrupt flag of the specified SPI port 
//!
//! \return the SPI interrupt flag.It can be the following values:
//! \b .
//
//*****************************************************************************
unsigned long 
SPIIntFlagGet(unsigned long ulBase, xtBoolean xbMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(xbMasked == xfalse);
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
SPIIntFlagClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xHWREG(ulBase + SPI_SR) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void
SPISSSet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    xHWREG(ulBase + SPI_CNTRL0) |= SPI_CNTRL0_SELOEN;
    xHWREG(ulBase + SPI_CNTRL0) |= SPI_CNTRL0_SSELC;
}


//*****************************************************************************
//
//! \brief Clear the slave select pins of the specified SPI port.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
void
SPISSClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xHWREG(ulBase + SPI_CNTRL0) &= ~SPI_CNTRL0_SSELC;
}

//*****************************************************************************
//
//! \brief Config the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSSActType specifies the active type of slave select pin.
//!
//! This function is to config the slave select pins of the 
//! specified SPI port.
//!
//! The \e ulSSActType can be one of the following values:
//! \b SPI_SS_ACTIVE_LOW, or \b SPI_SS_ACTIVE_HIGH.
//!
//! \note \e ulSSTriggerMode is only for slave mode
//!
//! \return None.
//
//*****************************************************************************
void
SPISSConfig(unsigned long ulBase, unsigned long ulSSActType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulSSActType == SPI_SS_ACTIVE_LOW) || 
            (ulSSActType == SPI_SS_ACTIVE_HIGH));
    
    //
    // Clear the corresponding bit first 
    //
    xHWREG(ulBase + SPI_CNTRL1) &= ~SPI_CNTRL1_SELAP;
    
    xHWREG(ulBase + SPI_CNTRL1) |= ulSSActType;
}
  
//*****************************************************************************
//
//! \brief Config the slave select Output function.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulEnable specifies the active type of slave select pin.
//!
//! The \e ulEnable can be one of the following values:
//! \b SPI_SS_OUTPUT_ENABLE, or \b SPI_SS_OUTPUT_DISABLE.
//!
//! \return None.
//
//***************************************************************************** 
void 
SPISSOutPutConfigure(unsigned long ulBase, unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulEnable == SPI_SS_OUTPUT_ENABLE) || 
            (ulEnable == SPI_SS_OUTPUT_DISABLE));
    
    if(ulEnable == SPI_SS_OUTPUT_ENABLE)
    {
        xHWREG(ulBase + SPI_CNTRL0) |= SPI_CNTRL0_SELOEN; 
    }
    else
    {
        xHWREG(ulBase + SPI_CNTRL0) &= ~SPI_CNTRL0_SELOEN; 
    }
    
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_BUSY) ? xtrue : xfalse);
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
SPIIsRxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_RXBNE)? xfalse : xtrue);
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
SPIIsRxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_RXBNE)? xtrue : xfalse);
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
SPIIsTxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_TXBE)? xfalse : xtrue);
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
SPIIsTxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    return ((xHWREG(ulBase + SPI_SR) & SPI_SR_TXBE)? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the FIFO buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulRxTx specifies the FIFO buffer is Rx buffer or Tx buffer.
//!
//! \return Returns the FIFO RX or TX buffer status of the specified SPI port.
//
//*****************************************************************************
unsigned long
SPIFIFOStatusGet(unsigned long ulBase, unsigned long ulRxTx)
{
    //
    // Check the arguments.
    //
    unsigned long ulDataNum;
   
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulRxTx == SPI_FSR_RX) || (ulRxTx == SPI_FSR_TX));
    
    if(ulRxTx == SPI_FSR_RX)
    {
        ulDataNum = (xHWREG(ulBase + SPI_FSR) & SPI_FSR_RXFS_M) >> SPI_FSR_RXFS_S;
    }
    else
    {
        ulDataNum = (xHWREG(ulBase + SPI_FSR) & SPI_FSR_TXFS_M) >> SPI_FSR_TXFS_S;
    }
    
    return ulDataNum;
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulRxTx == SPI_FSR_RX) || (ulRxTx == SPI_FSR_TX));
    
    if(ulRxTx == SPI_FSR_RX)
    {
        xHWREG(ulBase + SPI_FCR) |= SPI_FCR_RFPR;
    }
    else
    {
        xHWREG(ulBase + SPI_FCR) |= SPI_FCR_TFPR;
    }
}

//*****************************************************************************
//
//! \brief Enable/disable the FIFO mode of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulEnable enable the FIFO mode or not. It can be selected form
//! \b SPI_FIFO_ENABLE, 
//! \b SPI_FIFO_DISABLE
//!
//! This function enable/disable the FIFO mode of the specified SPI module.
//! If the caller enables FIFO mode.
//!
//! \return None.
//
//*****************************************************************************
void
SPIFIFOModeSet(unsigned long ulBase, unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulEnable == SPI_FIFO_ENABLE) || (ulEnable == SPI_FIFO_DISABLE));

    if (ulEnable == SPI_FIFO_ENABLE)
    {
        xHWREG(ulBase + SPI_FCR) |= SPI_FCR_FIFOEN;

    }
    else
    {
        xHWREG(ulBase + SPI_FCR) &= ~SPI_FCR_FIFOEN;
    }  
}

//*****************************************************************************
//
//! \brief Check the status of the FIFO buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulRxTx specifies the FIFO buffer is Rx buffer or Tx buffer.
//! \param ulLength is the level of the TX or RX FIFO.
//!
//! \return None
//
//*****************************************************************************             
void 
SPIFIFOLevelSet(unsigned long ulBase, unsigned long ulRxTx,
                unsigned long ulLength)
{
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulRxTx == SPI_FSR_RX) || (ulRxTx == SPI_FSR_TX));
    xASSERT((ulLength >= 0) || (ulLength <= 8));
    
    if(ulRxTx == SPI_FSR_RX)
    {
        xHWREG(ulBase + SPI_FCR) &= ~((ulLength << SPI_FCR_RXFTLS_S) & SPI_FCR_RXFTLS_M);
        xHWREG(ulBase + SPI_FCR) |= (ulLength << SPI_FCR_RXFTLS_S) & SPI_FCR_RXFTLS_M;
    }
    else
    {	
        xHWREG(ulBase + SPI_FCR) &= ~((ulLength << SPI_FCR_TXFTLS_S) & SPI_FCR_TXFTLS_M);
        xHWREG(ulBase + SPI_FCR) |= (ulLength << SPI_FCR_TXFTLS_S) & SPI_FCR_TXFTLS_M;
    } 
}

//*****************************************************************************
//
//! \brief Check the status of the FIFO buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulRxTx specifies the FIFO buffer is Rx buffer or Tx buffer.
//! \param ulLength is the level of the TX or RX FIFO.
//!
//! \return None
//
//*****************************************************************************
void 
SPITimeOutValSet(unsigned long ulBase, unsigned long ulTimeOutVal)
{
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xHWREG(ulBase + SPI_FTOCR) = ulTimeOutVal;
}

//*****************************************************************************
//
//! \brief Enable SPI DMA mode.
//!
//! \param ulBase is the base address of the SPI port.
//! \param ulDMAMode is the mode of the SPI DMA.
//!
//! Set DMA mode for the SPI.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDMAEnable(unsigned long ulBase, unsigned long ulDMAMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xASSERT((ulDMAMode == SPI_DMA_RX) || (ulDMAMode == SPI_DMA_TX));

    //
    // Set DMA mode for SPI
    //
    xHWREG(ulBase + SPI_CNTRL0) |= ulDMAMode;
}

//*****************************************************************************
//
//! \brief Disable SPI DMA mode.
//!
//! \param ulBase is the base address of the SPI port.
//! \param ulDMAMode is the mode of the SPI DMA mode.
//!
//! Disable DMA mode for the SPI.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDMADisable(unsigned long ulBase, unsigned long ulDMAMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xASSERT((ulDMAMode == SPI_DMA_RX) || (ulDMAMode == SPI_DMA_TX));

    //
    // Set DMA mode for SPI
    //
    xHWREG(ulBase + SPI_CNTRL0) &= ~ulDMAMode;
}

//*****************************************************************************
//
//! \brief Enable Loop Back Test Mode.
//!
//! \param ulBase is the base address of the SPI port.
//!
//! Enable Loop Back Test Mode for the SPI.
//!
//! \return None.
//
//*****************************************************************************
void
SPILoopBackEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Enable Loop Back Test Mode
    //
    xHWREG(ulBase + SPI_CNTRL0) |= SPI_CNTRL0_LOOPBACK_EN;
}

//*****************************************************************************
//
//! \brief Loop Back Test Mode.
//!
//! \param ulBase is the base address of the SPI port
//!
//! Disable Loop Back Test Mode for the SPI.
//!
//! \return None.
//
//*****************************************************************************
void
SPILoopBackDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Disable Loop Back Test Mode for SPI
    //
    xHWREG(ulBase + SPI_CNTRL0) &= ~SPI_CNTRL0_LOOPBACK_EN;
}
