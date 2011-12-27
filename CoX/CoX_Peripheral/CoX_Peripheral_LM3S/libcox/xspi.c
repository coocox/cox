//*****************************************************************************
//
// ssi.c - Driver for Synchronous Serial Interface.
//
// Copyright (c) 2005-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6852 of the Stellaris Peripheral Driver Library.
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
//! \brief Init the SPI Interrupt Callback function.
//!
//! \param ulBase is the base address of the UART.
//! \param pfnCallback is the callback function.
//!
//! When there is any UART intrrupt occrus, Interrupt Handler will 
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
SSIIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    
#if !xSPI_CONFIG_DMA_INT
    switch(ulBase)
    {
        case SSI0_BASE:
        {
            g_pfnSPIHandlerCallbacks[0] = pfnCallback;
            break;
        }
        case SSI1_BASE:
        {
            g_pfnSPIHandlerCallbacks[1] = pfnCallback;
            break;
        }        
            
    }
#endif
    
}

//*****************************************************************************
//
//! \brief SSI0 Interrupt Handler.
//!
//! If users want to user the SSI0 Callback feature, Users should promise 
//! that the SSI0 Handle in the vector table is SSI0IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void 
SSI0IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SSI0_BASE;

#if xSPI_CONFIG_DMA_INT
    xtEventCallback pfnCallback;
    unsigned long ulChannelID;
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
#endif

    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SSI_RIS);
    
    //
    // Clear Int flag
    //
    xHWREG(ulBase + SSI_ICR) = ulEventFlags;
    
#if !(xSPI_CONFIG_DMA_INT)
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[0])
    {
        g_pfnSPIHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    }    
#else
    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
            
    //
    // Check DMA RX flag
    //
    if(xHWREG(ulBase + SSI_DMACTL) & SSI_DMA_RX)
    {
        ulChannelID = xDMA_REQUEST_SPI0_RX & 0x1F;
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }

    //
    // Check DMA TX flag
    //
    if(xHWREG(ulBase + SSI_DMACTL) & SSI_DMA_TX)
    {
        ulChannelID = xDMA_REQUEST_SPI0_TX & 0x1F;
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }      
#endif
    
}


//*****************************************************************************
//
//! \brief SSI1 Interrupt Handler.
//!
//! If users want to user the SSI1 Callback feature, Users should promise 
//! that the SSI1 Handle in the vector table is SSI1IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void 
SSI1IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SSI1_BASE;

#if xSPI_CONFIG_DMA_INT
    xtEventCallback pfnCallback;
    unsigned long ulChannelID;
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
#endif

    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SSI_RIS);
    
    //
    // Clear Int flag
    //
    xHWREG(ulBase + SSI_ICR) = ulEventFlags;
    
#if !(xSPI_CONFIG_DMA_INT)
    //
    // Call Callback function
    //
    if(g_pfnSPIHandlerCallbacks[0])
    {
        g_pfnSPIHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    }    
#else
    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
            
    //
    // Check DMA RX flag
    //
    if(xHWREG(ulBase + SSI_DMACTL) & SSI_DMA_RX)
    {
        ulChannelID = xDMA_REQUEST_SPI1_RX & 0x1F;
        
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }

        ulChannelID = (xDMA_REQUEST_SPI1_RX >> 8) & 0x1F;
        
        //
        // Check channel assignment (Secondary)
        //
        if(xHWREG(UDMA_CHASGN) & (1 << ulChannelID))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }
        
    }

    //
    // Check DMA TX flag
    //
    if(xHWREG(ulBase + SSI_DMACTL) & SSI_DMA_TX)
    {
        ulChannelID = xDMA_REQUEST_SPI1_TX & 0x1F;
        
        //
        // Check channel assignment (primary)
        //
        if(!(xHWREG(UDMA_CHASGN) & (1 << ulChannelID)))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }

        ulChannelID = (xDMA_REQUEST_UART1_TX >> 8) & 0x1F;
        
        //
        // Check channel assignment (Secondary)
        //
        if(xHWREG(UDMA_CHASGN) & (1 << ulChannelID))
        {
            ulChannelStructIndex = ulChannelID;
            if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }

            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                            
                pfnCallback = xDMAChannelIntCallbackGet(ulChannelID);
                if(pfnCallback)
                {
                    //
                    // Call Callback function
                    //
                    pfnCallback(0, xDMA_INT_TC, 0, 0);
                }
            }
        }      
        
    }       
#endif
    
}

//*****************************************************************************
//
//! \brief Configures the synchronous serial interface.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulSSIClk is the rate of the clock supplied to the SSI module.
//! \param ulProtocol specifies the data transfer protocol.
//! \param ulMode specifies the mode of operation.
//! \param ulBitRate specifies the clock rate.
//! \param ulDataWidth specifies number of bits transferred per frame.
//!
//! This function configures the synchronous serial interface.  It sets
//! the SSI protocol, mode of operation, bit rate, and data width.
//!
//! The \e ulProtocol parameter defines the data frame format.  The
//! \e ulProtocol parameter can be one of the following values:
//! \b SSI_FRF_MOTO_MODE_0, \b SSI_FRF_MOTO_MODE_1, \b SSI_FRF_MOTO_MODE_2,
//! \b SSI_FRF_MOTO_MODE_3, \b SSI_FRF_TI, or \b SSI_FRF_NMW.  The Motorola
//! frame formats imply the following polarity and phase configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   SSI_FRF_MOTO_MODE_0
//!   0       1   SSI_FRF_MOTO_MODE_1
//!   1       0   SSI_FRF_MOTO_MODE_2
//!   1       1   SSI_FRF_MOTO_MODE_3
//! </pre>
//!
//! The \e ulMode parameter defines the operating mode of the SSI module.  The
//! SSI module can operate as a master or slave; if a slave, the SSI can be
//! configured to disable output on its serial output line.  The \e ulMode
//! parameter can be one of the following values: \b SSI_MODE_MASTER,
//! \b SSI_MODE_SLAVE, or \b SSI_MODE_SLAVE_OD.
//!
//! The \e ulBitRate parameter defines the bit rate for the SSI.  This bit rate
//! must satisfy the following clock ratio criteria:
//!
//! - FSSI >= 2 * bit rate (master mode)
//! - FSSI >= 12 * bit rate (slave modes)
//!
//! where FSSI is the frequency of the clock supplied to the SSI module.
//!
//! The \e ulDataWidth parameter defines the width of the data transfers, and
//! can be a value between 4 and 16, inclusive.
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original SSIConfig() API and performs the same
//! actions.  A macro is provided in <tt>ssi.h</tt> to map the original API to
//! this API.
//!
//! \return None.
//
//*****************************************************************************
void
SSIConfigSetExpClk(unsigned long ulBase, unsigned long ulSSIClk,
                   unsigned long ulProtocol, unsigned long ulMode,
                   unsigned long ulBitRate, unsigned long ulDataWidth)
{
    unsigned long ulMaxBitRate;
    unsigned long ulRegVal;
    unsigned long ulPreDiv;
    unsigned long ulSCR;
    unsigned long ulSPH_SPO;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    xASSERT((ulProtocol == SSI_FRF_MOTO_MODE_0) ||
           (ulProtocol == SSI_FRF_MOTO_MODE_1) ||
           (ulProtocol == SSI_FRF_MOTO_MODE_2) ||
           (ulProtocol == SSI_FRF_MOTO_MODE_3) ||
           (ulProtocol == SSI_FRF_TI) ||
           (ulProtocol == SSI_FRF_NMW));
    xASSERT((ulMode == SSI_MODE_MASTER) ||
           (ulMode == SSI_MODE_SLAVE) ||
           (ulMode == SSI_MODE_SLAVE_OD));
    xASSERT(((ulMode == SSI_MODE_MASTER) && (ulBitRate <= (ulSSIClk / 2))) ||
           ((ulMode != SSI_MODE_MASTER) && (ulBitRate <= (ulSSIClk / 12))));
    xASSERT((ulSSIClk / ulBitRate) <= (254 * 256));
    xASSERT((ulDataWidth >= 4) && (ulDataWidth <= 16));

    //
    // Set the mode.
    //
    ulRegVal = (ulMode == SSI_MODE_SLAVE_OD) ? SSI_CR1_SOD : 0;
    ulRegVal |= (ulMode == SSI_MODE_MASTER) ? 0 : SSI_CR1_MS;
    xHWREG(ulBase + SSI_CR1) = ulRegVal;

    //
    // Set the clock predivider.
    //
    ulMaxBitRate = ulSSIClk / ulBitRate;
    ulPreDiv = 0;
    do
    {
        ulPreDiv += 2;
        ulSCR = (ulMaxBitRate / ulPreDiv) - 1;
    }
    while(ulSCR > 255);
    xHWREG(ulBase + SSI_CPSR) = ulPreDiv;

    //
    // Set protocol and clock rate.
    //
    ulSPH_SPO = (ulProtocol & 3) << 6;
    ulProtocol &= SSI_CR0_FRF_M;
    ulRegVal = (ulSCR << 8) | ulSPH_SPO | ulProtocol | (ulDataWidth - 1);
    xHWREG(ulBase + SSI_CR0) = ulRegVal;
}

//*****************************************************************************
//
//! \brief Enables the synchronous serial interface.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function enables operation of the synchronous serial interface.  The
//! synchronous serial interface must be configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
void
SSIEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Read-modify-write the enable bit.
    //
    xHWREG(ulBase + SSI_CR1) |= SSI_CR1_SSE;
}

//*****************************************************************************
//
//! \brief Disables the synchronous serial interface.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function disables operation of the synchronous serial interface.
//!
//! \return None.
//
//*****************************************************************************
void
SSIDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Read-modify-write the enable bit.
    //
    xHWREG(ulBase + SSI_CR1) &= ~(SSI_CR1_SSE);
}

//*****************************************************************************
//
//! \brief Enables individual SSI interrupt sources.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulIntFlags is a bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated SSI interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.  The \e ulIntFlags parameter can be any of the
//! \b SSI_TXFF, \b SSI_RXFF, \b SSI_RXTO, or \b SSI_RXOR values.
//!
//! \return None.
//
//*****************************************************************************
void
SSIIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Enable the specified interrupts.
    //
    xHWREG(ulBase + SSI_IM) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Disables individual SSI interrupt sources.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulIntFlags is a bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated SSI interrupt sources.  The \e ulIntFlags parameter
//! can be any of the \b SSI_TXFF, \b SSI_RXFF, \b SSI_RXTO, or \b SSI_RXOR
//! values.
//!
//! \return None.
//
//*****************************************************************************
void
SSIIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Disable the specified interrupts.
    //
    xHWREG(ulBase + SSI_IM) &= ~(ulIntFlags);
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase specifies the SSI module base address.
//! \param bMasked is \b xfalse if the raw interrupt status is required or
//! \b xtrue if the masked interrupt status is required.
//!
//! This function returns the interrupt status for the SSI module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b SSI_TXFF, \b SSI_RXFF, \b SSI_RXTO, and \b SSI_RXOR.
//
//*****************************************************************************
unsigned long
SSIIntStatus(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(xHWREG(ulBase + SSI_MIS));
    }
    else
    {
        return(xHWREG(ulBase + SSI_RIS));
    }
}

//*****************************************************************************
//
//! \brief Clears SSI interrupt sources.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified SSI interrupt sources are cleared so that they no longer
//! assert.  This function must be called in the interrupt handler to keep the
//! interrupts from being recognized again immediately upon exit.  The
//! \e ulIntFlags parameter can consist of either or both the \b SSI_RXTO and
//! \b SSI_RXOR values.
//!
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
SSIIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Clear the requested interrupt sources.
    //
    xHWREG(ulBase + SSI_ICR) = ulIntFlags;
}

//*****************************************************************************
//
//! \brief Puts a data element into the SSI transmit FIFO.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulData is the data to be transmitted over the SSI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SSI module.
//!
//! \note The upper 32 - N bits of the \e ulData are discarded by the hardware,
//! where N is the data width as configured by SSIConfigSetExpClk().  For
//! example, if the interface is configured for 8-bit data width, the upper 24
//! bits of \e ulData are discarded.
//!
//! \return None.
//
//*****************************************************************************
void
SSIDataPut(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    xASSERT((ulData & (0xfffffffe << (xHWREG(ulBase + SSI_CR0) &
                                     SSI_CR0_DSS_M))) == 0);

    //
    // Wait until there is space.
    //
    while(!(xHWREG(ulBase + SSI_SR) & SSI_SR_TNF))
    {
    }

    //
    // Write the data to the SSI.
    //
    xHWREG(ulBase + SSI_DR) = ulData;
}

//*****************************************************************************
//
//! \brief Puts a data element into the SSI transmit FIFO.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulData is the data to be transmitted over the SSI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SSI module.  If there is no space in the FIFO, then this function
//! returns a zero.
//!
//! This function replaces the original SSIDataNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>ssi.h</tt> to map
//! the original API to this API.
//!
//! \note The upper 32 - N bits of the \e ulData are discarded by the hardware,
//! where N is the data width as configured by SSIConfigSetExpClk().  For
//! example, if the interface is configured for 8-bit data width, the upper 24
//! bits of \e ulData are discarded.
//!
//! \return Returns the number of elements written to the SSI transmit FIFO.
//
//*****************************************************************************
long
SSIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    xASSERT((ulData & (0xfffffffe << (xHWREG(ulBase + SSI_CR0) &
                                     SSI_CR0_DSS_M))) == 0);

    //
    // Check for space to write.
    //
    if(xHWREG(ulBase + SSI_SR) & SSI_SR_TNF)
    {
        xHWREG(ulBase + SSI_DR) = ulData;
        return(1);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
//! \brief Gets a data element from the SSI receive FIFO.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SSI interface.
//!
//! This function gets received data from the receive FIFO of the specified
//! SSI module and places that data into the location specified by the
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
SSIDataGet(unsigned long ulBase, unsigned long *pulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Wait until there is data to be read.
    //
    while(!(xHWREG(ulBase + SSI_SR) & SSI_SR_RNE))
    {
    }

    //
    // Read data from SSI.
    //
    *pulData = xHWREG(ulBase + SSI_DR);
}

//*****************************************************************************
//
//! \brief Gets a data element from the SSI receive FIFO.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SSI interface.
//!
//! This function gets received data from the receive FIFO of the specified SSI
//! module and places that data into the location specified by the \e ulData
//! parameter.  If there is no data in the FIFO, then this function  returns a
//! zero.
//!
//! This function replaces the original SSIDataNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>ssi.h</tt> to map
//! the original API to this API.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SSIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return Returns the number of elements read from the SSI receive FIFO.
//
//*****************************************************************************
long
SSIDataGetNonBlocking(unsigned long ulBase, unsigned long *pulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Check for data to read.
    //
    if(xHWREG(ulBase + SSI_SR) & SSI_SR_RNE)
    {
        *pulData = xHWREG(ulBase + SSI_DR);
        return(1);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
//! \brief Enable SSI DMA operation.
//!
//! \param ulBase is the base address of the SSI port.
//! \param ulDMAFlags is a bit mask of the DMA features to enable.
//!
//! The specified SSI DMA features are enabled.  The SSI can be
//! configured to use DMA for transmit and/or receive data transfers.
//! The \e ulDMAFlags parameter is the logical OR of any of the following
//! values:
//!
//! - SSI_DMA_RX - enable DMA for receive
//! - SSI_DMA_TX - enable DMA for transmit
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the SSI.
//!
//! \return None.
//
//*****************************************************************************
void
SSIDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Set the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + SSI_DMACTL) |= ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Disable SSI DMA operation.
//!
//! \param ulBase is the base address of the SSI port.
//! \param ulDMAFlags is a bit mask of the DMA features to disable.
//!
//! This function is used to disable SSI DMA features that were enabled
//! by SSIDMAEnable().  The specified SSI DMA features are disabled.  The
//! \e ulDMAFlags parameter is the logical OR of any of the following values:
//!
//! - SSI_DMA_RX - disable DMA for receive
//! - SSI_DMA_TX - disable DMA for transmit
//!
//! \return None.
//
//*****************************************************************************
void
SSIDMADisable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Clear the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + SSI_DMACTL) &= ~ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Determines whether the SSI transmitter is busy or not.
//!
//! \param ulBase is the base address of the SSI port.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware.  If \b xfalse is returned, then the transmit FIFO
//! is empty and all bits of the last transmitted word have left the hardware
//! shift register.
//!
//! \return Returns \b xtrue if the SSI is transmitting or \b xfalse if all
//! transmissions are complete.
//
//*****************************************************************************
xtBoolean
SSIBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Determine if the SSI is busy.
    //
    return((xHWREG(ulBase + SSI_SR) & SSI_SR_BSY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the Rx buffer of the specified SSI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! \return Returns \b xtrue if the SSI Rx buffer is empty or \b xfalse if the Rx
//! buffer is not empty.
//
//*****************************************************************************
xtBoolean
SSIIsRxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Determine if the SSI receive FIFO is empty.
    //
    return((xHWREG(ulBase + SSI_SR) & SSI_SR_RNE) ? xfalse : xtrue);     
}

//*****************************************************************************
//
//! \brief Check the status of the Tx buffer of the specified SSI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! \return Returns \b xtrue if the SSI Tx buffer is empty or \b xfalse if the Tx
//! buffer is not empty.
//
//*****************************************************************************
xtBoolean
SSIIsTxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Determine if the SSI transmit FIFO is empty.
    //
    return((xHWREG(ulBase + SSI_SR) & SSI_SR_TFE) ? xtrue : xfalse);        
}

//*****************************************************************************
//
//! \brief Check the status of the Rx buffer of the specified SSI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! \return Returns \b xtrue if the SSI Rx buffer is full or \b xfalse if the Rx
//! buffer is not full.
//
//*****************************************************************************
xtBoolean
SSIIsRxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Determine if the SSI receive FIFO is full
    //
    return((xHWREG(ulBase + SSI_SR) & SSI_SR_RFF) ? xtrue : xfalse);      
}

//*****************************************************************************
//
//! \brief Check the status of the Tx buffer of the specified SSI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! \return Returns \b xtrue if the SSI Tx buffer is full or \b xfalse if the Tx
//! buffer is not full.
//
//***************************************************************************** 
xtBoolean
SPIIsTxFull(unsigned long ulBase)
{
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    //
    // Determine if the SSI transmit FIFO is full
    //
    return((xHWREG(ulBase + SSI_SR) & SSI_SR_TNF) ? xfalse : xtrue);      
}

//*****************************************************************************
//
//! \brief Gets the number of bits transferred per frame.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function gets the number of bits transferred per frame:
//! - 0     - means frame data bit size is 32.
//! - 1     - means frame data bit size is 1.
//! - 2     - means frame data bit size is 2.
//! - 31    - means frame data bit size is 31.
//!
//! \return the number of bits transferred per frame.
//
//*****************************************************************************
unsigned char
SSIBitLengthGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));

    return ((xHWREG(ulBase + SSI_CR0) & SSI_CR0_DSS_M) + 1);
    
}

//*****************************************************************************
//
//! \brief Read and write a data element from and to the SSI interface.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulWData is the data that was transmitted over the SSI interface.
//!
//! This function send transmitted data to the SSI interface and gets received 
//! data from the SSI module then return that data.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SSIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the data that was received over the SSI interface.
//
//*****************************************************************************
unsigned long 
SSISingleDataReadWrite(unsigned long ulBase, unsigned long ulWData)
{
    unsigned long ulRData;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    xASSERT((ulWData & (0xfffffffe << (xHWREG(ulBase + SSI_CR0) &
                                      SSI_CR0_DSS_M))) == 0);

    //
    // Wait until there is space.
    //
    while(!(xHWREG(ulBase + SSI_SR) & SSI_SR_TNF))
    {
    }

    //
    // Write the data to the SSI.
    //
    xHWREG(ulBase + SSI_DR) = ulWData;
    
    //
    // Wait until there is data to be read.
    //
    while(!(xHWREG(ulBase + SSI_SR) & SSI_SR_RNE))
    {
    }

    //
    // Read data from SSI.
    //
    ulRData = xHWREG(ulBase + SSI_DR); 
    
    return ulRData;
}

//*****************************************************************************
//
//! \brief Gets a data element from the SSI interface.
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
SPIDataRead(unsigned long ulBase, unsigned long *pulRData, unsigned long ulLen)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    xASSERT(pulRData);
    
    for(i = 0; i < ulLen; i++)
    {
        pulRData[i] = xSPISingleDataReadWrite(ulBase, 0xFFFF);
    }
}

//*****************************************************************************
//
//! \brief Write datas element to the SSI interface.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulWData is a pointer to a storage location for data that was
//! transmitted over the SSI interface.
//! \param ulLen specifies the length of data will be write.
//!
//! This function transmitted data to the interface of the specified
//! SSI module .
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
SSIDataWrite(unsigned long ulBase, const unsigned long *pulWData, 
             unsigned long ulLen)
{
    unsigned long i;
    volatile unsigned long ulRDataDump;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SSI0_BASE) || (ulBase == SSI1_BASE));
    xASSERT(pulWData);
    
    for(i = 0; i < ulLen; i++)
    {
        ulRDataDump = xSPISingleDataReadWrite(ulBase, pulWData[i]);
    }    
}
