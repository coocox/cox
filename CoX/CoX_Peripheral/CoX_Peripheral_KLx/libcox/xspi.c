//*****************************************************************************
//
//! \file xspi.c
//! \brief Driver for the SPI
//! \version V2.2.1.0
//! \date 12/27/2011
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
#include "xhw_spi.h"
#include "xdebug.h"
#include "xcore.h"
#include "xspi.h"
#if xSPI_CONFIG_DMA_INT
#include "xhw_dma.h"
#include "xdma.h"
#endif

#if !xSPI_CONFIG_DMA_INT
static xtEventCallback g_pfnSPIHandlerCallbacks[2] = {0};
#endif

//*****************************************************************************
//
//! \brief SPI0 Interrupt Handler.
//!
//! If users want to user the SPI0 Callback feature, Users should promise 
//! that the SPI0 Handle in the vector table is SPI0IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI0IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI0_BASE;

    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREGB(ulBase + SPI_S); 
    
    //
    // Clear Int flag
    //
    xHWREGB(ulBase + SPI_S) |= (unsigned char)ulEventFlags & 0x40;
    
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
//! \brief SPI1 Interrupt Handler.
//!
//! If users want to user the SPI1 Callback feature, Users should promise 
//! that the SPI1 Handle in the vector table is SPI1IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI1IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI1_BASE;
	
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREGB(ulBase + SPI_S); 
	
    //
    // Clear Int flag
    //
    xHWREGB(ulBase + SPI_S) |= (unsigned char)ulEventFlags & 0x40;
    
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
//! \brief Configures the synchronous serial interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSPIClk is the rate of the clock supplied to the SPI module.
//! \param ulProtocol specifies the data transfer protocol.
//! \param ulMode specifies the mode of operation.
//! \param ulBitRate specifies the clock rate.
//! \param ulShiftDirection specifies direction of bits transferred per frame.
//!
//! This function configures the synchronous serial interface.  It sets
//! the SPI protocol, mode of operation, bit rate, and data shift direction.
//!
//! The \e ulProtocol parameter defines the data frame format.  The
//! \e ulProtocol parameter can be one of the following values:
//! \b SPI_FRF_MOTO_MODE_0, \b SPI_FRF_MOTO_MODE_1, \b SPI_FRF_MOTO_MODE_2, 
//! \b SPI_FRF_MOTO_MODE_3.
//! The Motorola frame formats imply the following polarity and phase
//! configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   SPI_FRF_MOTO_MODE_0
//!   0       1   SPI_FRF_MOTO_MODE_1
//!   1       0   SPI_FRF_MOTO_MODE_2
//!   1       1   SPI_FRF_MOTO_MODE_3
//! </pre>
//!
//! The \e ulMode parameter defines the operating mode of the SPI module.  The
//! SPI module can operate as a master or slave; if a slave, the SPI can be
//! configured to disable output on its serial output line.  The \e ulMode
//! parameter can be one of the following values: \b SPI_MODE_MASTER,
//! \b SPI_MODE_SLAVE, or \b SPI_MODE_SLAVE_OD.
//!
//! The \e ulBitRate parameter defines the bit rate for the SPI.  This bit rate
//! must satisfy the following clock ratio criteria:
//!
//! - FSPI >= 2 * bit rate (master mode)
//! - FSPI >= 12 * bit rate (slave modes)
//!
//! where FSPI is the frequency of the clock supplied to the SPI module.
//!
//! The \e ulShiftDirection parameter defines the direction of the data 
//! transfers. 
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original SPIConfig() API and performs the same
//! actions.  A macro is provided in <tt>spi.h</tt> to map the original API to
//! this API.
//!
//! \return None.
//
//*****************************************************************************
void
SPIConfigSetExpClk(unsigned long ulBase, unsigned long ulSPIClk,
                   unsigned long ulProtocol, unsigned long ulMode,
                   unsigned long ulBitRate, unsigned long ulShiftDirection)
{
    unsigned long ulMaxBitRate;
    unsigned long ulRegVal;
    unsigned long ulPreDiv;
    unsigned long ulSCR;
    unsigned long ulCnt;
	
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT((ulProtocol == SPI_FRF_MOTO_MODE_0) ||
           (ulProtocol == SPI_FRF_MOTO_MODE_1) ||
           (ulProtocol == SPI_FRF_MOTO_MODE_2) ||
           (ulProtocol == SPI_FRF_MOTO_MODE_3));
    xASSERT((ulMode == SPI_MODE_MASTER) || (ulMode == SPI_MODE_SLAVE));
    xASSERT(((ulMode == SPI_MODE_MASTER) && (ulBitRate <= (ulSPIClk / 2))) ||
           ((ulMode == SPI_MODE_SLAVE) && (ulBitRate <= (ulSPIClk / 4))));
    xASSERT((ulSPIClk / ulBitRate) <= (512 * 8));	
	
    //
    // Set the clock predivider.
    //
    ulMaxBitRate = ulSPIClk / ulBitRate;
    ulPreDiv = 1;
    ulCnt = 0;
    do
    {
        ulCnt ++;
        ulPreDiv *= 2;
        ulSCR = ulMaxBitRate / ulPreDiv;
    }
    while(ulSCR > 8);
	
    xHWREGB(ulBase + SPI_BR) = (unsigned char)(ulCnt - 1);
    xHWREGB(ulBase + SPI_BR) |= (unsigned char)((ulSCR - 1) << SPI_BR_SPPR_S);
	
    //
    // Set protocol 
    //
    ulRegVal = (ulShiftDirection | ulMode | ulProtocol);
    xHWREGB(ulBase + SPI_C1) = (unsigned char)ulRegVal;
}

//*****************************************************************************
//
//! \brief Enables the synchronous peripheral interface.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function enables operation of the synchronous peripheral interface.The
//! synchronous peripheral interface must be configured before it is enabled.
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

    //
    // Read-modify-write the enable bit.
    //
    xHWREGB(ulBase + SPI_C1) |= (unsigned char)SPI_C1_SPE;
}

//*****************************************************************************
//
//! \brief Disables the synchronous peripheral interface.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function disables operation of the synchronous peripheral interface.
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

    //
    // Read-modify-write the enable bit.
    //
    xHWREGB(ulBase + SPI_C1) &= ~((unsigned char)SPI_C1_SPE);
}

//*****************************************************************************
//
//! \brief Enables individual SPI interrupt sources.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulIntFlags is a bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated SPI interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.  The \e ulIntFlags parameter can be any of the
//! \b SPI_SPRF, \b SPI_MODF, \b SPI_SPTEF, \b SPI_SPMF or \b SPI_SPLPF values.
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
	
    //
    // Enable the specified interrupts.
    //
    if(ulIntFlags & 0xF0)
    {
        xHWREGB(ulBase + SPI_C2) |= (unsigned char)(ulIntFlags << 4);
    }
    else
    {
        xHWREGB(ulBase + SPI_C1) |= (unsigned char)(ulIntFlags << 4);
    }
}

//*****************************************************************************
//
//! \brief Disables individual SPI interrupt sources.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulIntFlags is a bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated SPI interrupt sources.  The \e ulIntFlags parameter
//! can be any of the \b SPI_SPRF, \b SPI_MODF, \b SPI_SPTEF, or \b SPI_SPMF
//! or \b SPI_SPLPF values.
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

    //
    // Disable the specified interrupts.
    //
    if(ulIntFlags & 0xF0)
    {
        xHWREGB(ulBase + SPI_C2) &= ~((unsigned char)(ulIntFlags << 4));
    }
    else
    {
        xHWREGB(ulBase + SPI_C1) &= ~((unsigned char)(ulIntFlags << 4));
    }
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase specifies the SPI module base address.
//! \param bMasked is \b xfalse if the raw interrupt status is required or
//! \b xtrue if the masked interrupt status is required.
//!
//! This function returns the interrupt status for the SPI module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b SPI_SPRF, \b SPI_MODF, \b SPI_SPTEF, and \b SPI_SPMF.
//
//*****************************************************************************
unsigned long
SPIIntStatus(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(bMasked == xfalse);
	
    //
    // Return  the interrupt status as requested.
    // 
    return (xHWREGB(ulBase + SPI_S) & SPI_S_M) ;
}

//*****************************************************************************
//
//! \brief Init the SPI Interrupt Callback function.
//!
//! \param ulBase is the base address of the SPI.
//! \param pfnCallback is the callback function.
//!
//! When there is any SPI intrrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent is the interrupt event.
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void
SPIIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
#if !xSPI_CONFIG_DMA_INT
    switch(ulBase)
    {
        case SPI0_BASE:
        {
            g_pfnSPIHandlerCallbacks[0] = pfnCallback;
            break;
        }
        case SPI1_BASE:
        {
            g_pfnSPIHandlerCallbacks[1] = pfnCallback;
            break;
        }                   
    }
#endif   
}

//*****************************************************************************
//
//! \brief Puts a data element into the SPI transmit .
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulData is the data to be transmitted over the SPI interface.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module.
//!
//! \note The data width is always 8-bit.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(ulData < 256);

    //
    // Wait until SPRF is set.
    //
    while(!(xHWREGB(ulBase + SPI_S) & SPI_S_SPTEF))
    {
    }

    //
    // Write the data to the SPI.
    //
    xHWREGB(ulBase + SPI_D) = (unsigned char)ulData;
}

//*****************************************************************************
//
//! \brief Puts a data element into the SPI transmit FIFO.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulData is the data to be transmitted over the SPI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SPI module.  If there is no space in the FIFO, then this function
//! returns a zero.
//!
//! This function replaces the original SPIDataNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>spi.h</tt> to map
//! the original API to this API.
//!
//! \note The data width is always 8-bit.
//!
//! \return Returns the number of elements written to the SPI transmit FIFO.
//
//*****************************************************************************
long
SPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(ulData < 256);

    //
    // Check for space to write.
    //
    if(xHWREGB(ulBase + SPI_S) & SPI_S_SPTEF)
    {
        xHWREGB(ulBase + SPI_D) = (unsigned char)ulData;
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
//! \note The data width is always 8-bit.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Wait until there is data to be read.
    //
    while(!(xHWREGB(ulBase + SPI_S) & SPI_S_SPRF))
    {
    }

    //
    // Read data from SPI.
    //
    *pulData = xHWREGB(ulBase + SPI_D);
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
//! performs the same actions.  A macro is provided in <tt>spi.h</tt> to map
//! the original API to this API.
//!
//! \note The data width is always 8-bit.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Check for data to read.
    //
    if(xHWREGB(ulBase + SPI_S) & SPI_S_SPRF)
    {
        *pulData = xHWREGB(ulBase + SPI_D);
        return(1);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
//! \brief Enable SPI DMA operation.
//!
//! \param ulBase is the base address of the SPI port.
//! \param ulDMAFlags is a bit mask of the DMA features to enable.
//!
//! The specified SPI DMA features are enabled.  The SPI can be
//! configured to use DMA for transmit and/or receive data transfers.
//! The \e ulDMAFlags parameter is the logical OR of any of the following
//! values:
//!
//! - SPI_DMA_RX - enable DMA for receive
//! - SPI_DMA_TX - enable DMA for transmit
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the SPI.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Set the requested bits in the SPI DMA control register.
    //
    xHWREGB(ulBase + SPI_C2) |= (unsigned char)ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Disable SPI DMA operation.
//!
//! \param ulBase is the base address of the SPI port.
//! \param ulDMAFlags is a bit mask of the DMA features to disable.
//!
//! This function is used to disable SPI DMA features that were enabled
//! by SPIDMAEnable().  The specified SPI DMA features are disabled.  The
//! \e ulDMAFlags parameter is the logical OR of any of the following values:
//!
//! - SPI_DMA_RX - disable DMA for receive
//! - SPI_DMA_TX - disable DMA for transmit
//!
//! \return None.
//
//*****************************************************************************
void
SPIDMADisable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Clear the requested bits in the SPI DMA control register.
    //
    xHWREGB(ulBase + SPI_C2) &= ~((unsigned char)ulDMAFlags);
}

//*****************************************************************************
//
//! \brief Read and write a data element from and to the SPI interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulWData is the data that was transmitted over the SPI interface.
//!
//! This function send transmitted data to the SPI interface and gets received 
//! data from the SPI module then return that data.
//!
//! \note The data width is always 8-bit.
//!
//! \return the data that was received over the SPI interface.
//
//*****************************************************************************
unsigned long 
SPISingleDataReadWrite(unsigned long ulBase, unsigned long ulWData)
{
    unsigned long ulRData;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));

    //
    // Wait until there is space.
    //
    while(!(xHWREGB(ulBase + SPI_S) & SPI_S_SPTEF))
    {
    }

    //
    // Write the data to the SPI.
    //
    xHWREGB(ulBase + SPI_D) = (unsigned char)ulWData;
    
    //
    // Wait until there is data to be read.
    //
    while(!(xHWREGB(ulBase + SPI_S) & SPI_S_SPRF))
    {
    }

    //
    // Read data from SPI.
    //
    ulRData = xHWREGB(ulBase + SPI_D); 
    
    return ulRData;
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
//! \note The data width is always 8-bit.
//!
//! \return None.
//
//*****************************************************************************        
void 
SPIDataRead(unsigned long ulBase, unsigned long *pulRData, unsigned long ulLen)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(pulRData);
    
    for(i = 0; i < ulLen; i++)
    {
        pulRData[i] = xSPISingleDataReadWrite(ulBase, 0xFFFF);
    }
}

//*****************************************************************************
//
//! \brief Write datas element to the SPI interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulWData is a pointer to a storage location for data that was
//! transmitted over the SPI interface.
//! \param ulLen specifies the length of data will be write.
//!
//! This function transmitted data to the interface of the specified
//! SPI module .
//!
//! \note The data width is always 8-bit.
//!
//! \return None.
//
//*****************************************************************************        
void
SPIDataWrite(unsigned long ulBase, const unsigned long *pulWData, 
             unsigned long ulLen)
{
    unsigned long i;
    volatile unsigned long ulRDataDump;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    xASSERT(pulWData);
    
    for(i = 0; i < ulLen; i++)
    {
        ulRDataDump = xSPISingleDataReadWrite(ulBase, pulWData[i]);
    }    
}

//*****************************************************************************
//
//! \brief Enable/disable the 3 wire feature of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulMode specifies the SPI is configured as a master or a slave, 
//!        it uses the MOSI (MOMI) or MISO (SISO) pin.
//!
//! This function enable the 3 wire feature. the controller start to transmit/
//!receive data after the GO_BUSY bit active and the serial clock input.
//!
//! In no slave select signal mode, the BIDIROE, SPI_C2[3], shuld be
//! set as 1.
//!
//! \return None.
//
//*****************************************************************************
void 
SPI3WireEnable(unsigned long ulBase, unsigned long ulMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
	xASSERT((ulMode == SPI_MODE_MASTER) || (ulMode == SPI_MODE_SLAVE));
	
    xHWREGB(ulBase + SPI_C2) |= SPI_C2_SPC0;
	
    xHWREGB(ulBase + SPI_C2) &= ~SPI_C2_BIDIROE;
    if(ulMode == SPI_MODE_MASTER) 
    {
        xHWREGB(ulBase + SPI_C2) |= SPI_C2_BIDIROE;
    }
}

//*****************************************************************************
//
//! \brief Abort transfer when using 3-wire SPI.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function abort transfer when using 3-wire SPI. If using 3-wire SPI as 
//! slave, when slave start interrupt status is set but transfer done flag  
//! doesn't be set over a reasonable time, use this function to abort this
//! transfer.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3WireDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xHWREGB(ulBase + SPI_C2) &= ~SPI_C2_SPC0;
}

//*****************************************************************************
//
//! \brief Set the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulSlaveSel specifies the slave select output enable.
//!
//! This function is to Set the slave select pins of the 
//! specified SPI port.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b SPI_SS_MODEFAULT or \b SPI_SS_OUTPUT.
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xHWREGB(ulBase + SPI_C2) |= SPI_C2_MODFEN;
	
    xHWREGB(ulBase + SPI_C1) &= ~SPI_C1_SSOE;
    if(ulSlaveSel == SPI_SS_OUTPUT)
    {
	xHWREGB(ulBase + SPI_C1) |= SPI_C1_SSOE;
    }
}

//*****************************************************************************
//
//! \brief Clear the slave select pins of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function is to Clear the slave select pins of the 
//! specified SPI port.
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
    
    xHWREGB(ulBase + SPI_C2) &= ~SPI_C2_MODFEN;
}

//*****************************************************************************
//
//! \brief set the SPI clock status when the MCU enters wait mode.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulMode specifies the SPI clock status in wait mode.
//!
//! This function is to set the SPI clock continue when the MCU enters wait mode.
//!
//! The \e ulMode can be one of the following values:
//! \b SPI_CLK_STOP or \b SPI_CLK_CONTINUE.
//!
//! \note This bit is used for power conservation while the device is in 
//!       wait mode.
//!
//! \return None.
//
//*****************************************************************************
void
SPIClkStatusForWaitMode(unsigned long ulBase, unsigned long ulMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE));
    
    xHWREGB(ulBase + SPI_C2) &= ~SPI_C2_SPISWAI;
    if(ulMode == SPI_CLK_STOP)
    {
        xHWREGB(ulBase + SPI_C2) |= SPI_C2_SPISWAI;
    }
}