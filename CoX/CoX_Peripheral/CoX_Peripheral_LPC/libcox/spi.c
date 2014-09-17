//*****************************************************************************
//
//! \file spi.c
//! \brief Driver for the SPI controller
//! \version V3.0.0.0
//! \date 8/15/2014
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
#include "spi.h"

//*****************************************************************************
//
// An array is Watchdog callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnSPIHandlerCallbacks[3] = {0};

//*****************************************************************************
//
//! \brief  SSP0 interrupt handler.
//!         This function is the SSP0 interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void SSP0IntHandler(void)
{
    if(g_pfnSPIHandlerCallbacks[0] != 0)
    {
        g_pfnSPIHandlerCallbacks[0](0, 0, 0, 0);
    }
}

//*****************************************************************************
//
//! \brief  SSP1 interrupt handler.
//!         This function is the SSP1 interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void SSP1IntHandler(void)
{
    if(g_pfnSPIHandlerCallbacks[1] != 0)
    {
        g_pfnSPIHandlerCallbacks[1](0, 0, 0, 0);
    }
}

#if defined(LPC_177x) && defined (LPC_178x)
//*****************************************************************************
//
//! \brief  SSP2 interrupt handler.
//!         This function is the SSP2 interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void SSP2IntHandler(void)
{
    if(g_pfnSPIHandlerCallbacks[2] != 0)
    {
        g_pfnSPIHandlerCallbacks[2](0, 0, 0, 0);
    }
}

#elif defined(LPC_175x) && defined (LPC_176x)
//*****************************************************************************
//
//! \brief  SPI interrupt handler.
//!         This function is the SPI interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void SPIIntHandler(void)
{
    if(g_pfnSPIHandlerCallbacks[2] != 0)
    {
        g_pfnSPIHandlerCallbacks[2](0, 0, 0, 0);
    }
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks a SPI base address.
//!
//! \param ulBase is the base address of the SPI port.
//!
//! This function determines if a SPI port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
SPIBaseValid(unsigned long ulBase)
{
    return((ulBase == SPI0_BASE) ||
           (ulBase == SPI1_BASE) ||
           (ulBase == SPI2_BASE));
}
#endif

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the SPI.
//!
//! \param  [in] xtPortCallback is user callback for the SPI.
//!
//! \return None.
//
//*****************************************************************************
unsigned long xSPIIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(pfnCallback != 0);
	
    switch (ulBase)
    {
        case SPI0_BASE: g_pfnSPIHandlerCallbacks[0] = pfnCallback; break;
        case SPI1_BASE: g_pfnSPIHandlerCallbacks[1] = pfnCallback; break;
        case SPI2_BASE: g_pfnSPIHandlerCallbacks[2] = pfnCallback; break;
        default: break;
    }

    return (0);
}

//*****************************************************************************
//
//! \brief  SPI single write and read data.
//!
//! \param  [in] ulBase specifies the SPI module base address.
//! \param  [in] ulVal is the data ready to send via spi bus.
//!
//! \return The receive data from spi slave.
//
//*****************************************************************************
unsigned long xSPISingleDataReadWrite(unsigned long ulBase, unsigned long ulVal)
{
#if (defined (LPC_175x) || defined (LPC_176x))
    // SPI (only for LPC175x_6x)
    if(ulBase == SPI2_BASE){
        while(0 == (xHWREG(ulBase + SPI_SR) & SPI_SR_SPIF));
        xHWREG(ulBase + SPI_DR) = ulVal & SPI_DR_DATA_M;
        return xHWREG(ulBase + SPI_DR);
	} 
    else
#endif
    // SSPn(LPC175x_6x: n = 0, 1; LPC177x_8x: n = 0, 1, 2)
    {
        while(0 == (xHWREG(ulBase + SSP_SR) & SSP_SR_TFE));
        xHWREG(ulBase + SSP_DR) = ulVal & SSP_DR_DATA_M;
        return xHWREG(ulBase + SSP_DR);
    }
}

//*****************************************************************************
//
//! \brief  Configure SPI Module.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \param  [in] ulClk is SPI bus clock frequency.
//!
//! \param  [in] ulConfig is SPI configure parameters.
//!              which can be OR of the following value:
//!              - \ref SPI_DATA_LEN_4
//!              - \ref SPI_DATA_LEN_5
//!              - \ref SPI_DATA_LEN_6
//!              - \ref SPI_DATA_LEN_7
//!              - \ref SPI_DATA_LEN_8
//!              - \ref SPI_DATA_LEN_9
//!              - \ref SPI_DATA_LEN_10
//!              - \ref SPI_DATA_LEN_11
//!              - \ref SPI_DATA_LEN_12
//!              - \ref SPI_DATA_LEN_13
//!              - \ref SPI_DATA_LEN_14
//!              - \ref SPI_DATA_LEN_15
//!              - \ref SPI_DATA_LEN_16
//!              - \ref SPI_MODE_MASTER
//!              - \ref SPI_MODE_SLAVE
//!              - \ref SPI_FORMAT_MODE_0
//!              - \ref SPI_FORMAT_MODE_1
//!              - \ref SPI_FORMAT_MODE_2
//!              - \ref SPI_FORMAT_MODE_3
//!              - \ref SPI_TI_FORMAT_MODE
//!              - \ref SPI_NMW_FORMAT_MODE
//!              - \ref SPI_LSB_FIRST
//!              - \ref SPI_MSB_FIRST
//!
//! \return None.
//
//*****************************************************************************
void xSPIConfigSet(unsigned long ulBase, unsigned long ulClk, unsigned long ulConfig)
{
    unsigned long ulTmpReg = 0;
    unsigned long ulActClk = 0;

    // Check the parameters.
    xASSERT(SPIBaseValid(ulBase));
    xASSERT((ulConfig & ~(  SPI_DATA_LEN_4      |
                            SPI_DATA_LEN_5      |
                            SPI_DATA_LEN_6      |
                            SPI_DATA_LEN_7      |
                            SPI_DATA_LEN_8      |
                            SPI_DATA_LEN_9      |
                            SPI_DATA_LEN_10     |
                            SPI_DATA_LEN_11     |
                            SPI_DATA_LEN_12     |
                            SPI_DATA_LEN_13     |
                            SPI_DATA_LEN_14     |
                            SPI_DATA_LEN_15     |
                            SPI_DATA_LEN_16     |
                            SPI_MODE_MASTER     |
                            SPI_MODE_SLAVE      |
                            SPI_FORMAT_MODE_0   |
                            SPI_FORMAT_MODE_1   |
                            SPI_FORMAT_MODE_2   |
                            SPI_FORMAT_MODE_3   |
                            SPI_TI_FORMAT_MODE  |
                            SPI_NMW_FORMAT_MODE |
                            SPI_LSB_FIRST       |
                            SPI_MSB_FIRST
                        )
              ) == 0);

    /********************* Configure SPI Clock frequency ***********************/
    ulActClk = SysCtlPeripheralClockGet(PCLKSEL_SPI);
    ulActClk /= ulClk;

    // ulActClk/ulClk must be an even number greater than or equal to 8.
    // Violations of this can result in unpredictable behavior.
    if( ((ulActClk/ulClk) < 8) || ((ulActClk/ulClk)%2 != 0))
    {
        while(1); //Error
    }
    xHWREG(ulBase + S0SPCCR) = ulActClk/ulClk;

    /********************* Configure SPI Mode, PHA, POL, DataLen ***************/
#if (defined (LPC_175x) || defined (LPC_176x))
    // SPI (only for LPC175x_6x)
    if(ulBase == SPI2_BASE){
        ulTmpReg = xHWREG(ulBase + SPI_CR);
        ulTmpReg &= ((~ulConfig) >> 16);
        ulTmpReg |= (ulConfig & 0xFFFF);
        xHWREG(ulBase + SPI_CR) = ulTmpReg;
	} 
    else
#endif
    // SSPn(LPC175x_6x: n = 0, 1; LPC177x_8x: n = 0, 1, 2)
    {
        xHWREG(ulBase + SSP_CR1) = 0x00;
        xHWREG(ulBase + SSP_CR0) |= ulConfig & 0xFF;
		xHWREG(ulBase + SSP_CR0) |= ((ulConfig >> 8) & 0xFF);
        xHWREG(ulBase + SSP_CR1) &= ~SSP_CR1_MS
        xHWREG(ulBase + SSP_CR1) |= (((ulConfig >> 16) & 0x1) << 2);		
    }
}

//*****************************************************************************
//
//! \brief  Enable SPI interrupt.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//! \param  [in] ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! \return None.
//
//*****************************************************************************
void xSPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT((ulFlags == SPI_INT_EOT) ||
            (ulFlags == SPI_INT_RX)  ||
            (ulFlags == SPI_INT_TX)  ||
            (ulFlags == SPI_INT_ERROR));

    // Clear interrupt flag.
#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        xHWREG(ulBase + SPI_CR) |= SPI_CR_SPIE;
    }
#endif
    xHWREG(ulBase + SSP_IMSC) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief  Disable SPI interrupt.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//! \param  [in] ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! \return None.
//
//*****************************************************************************
void xSPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT((ulFlags == SPI_INT_EOT) ||
            (ulFlags == SPI_INT_RX)  ||
            (ulFlags == SPI_INT_TX)  ||
            (ulFlags == SPI_INT_ERROR));

    // Clear interrupt flag.
#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        xHWREG(ulBase + SPI_CR) &= ~SPI_CR_SPIE;
    }
#endif
    xHWREG(ulBase + SSP_IMSC) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief  Get SPI Interrupt flag.
//!
//! \param  [in] ulBase specifies the SPI module base address.
//! \param  [in] xbMasked is \b false if the raw interrupt status is required or
//! \b true if the masked interrupt status is required.
//!
//! \return The interrupt status of SPI.
//
//*****************************************************************************
unsigned long xSPIStatusGet(unsigned long ulBase, xtBoolean xbMasked)
{
    unsigned long ulRegTmp;
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT((ulFlags == SPI_INT_EOT) ||
            (ulFlags == SPI_INT_RX)  ||
            (ulFlags == SPI_INT_TX)  ||
            (ulFlags == SPI_INT_ERROR));

    // Clear interrupt flag.
#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        return xHWREG(ulBase + SPI_INT);
    }
#endif
    if(xbMasked){
        ulRegTmp = xHWREG(ulBase + SSP_MIS);
    } else {
        ulRegTmp = xHWREG(ulBase + SSP_RIS);
    }
	return ulRegTmp;
}

//*****************************************************************************
//
//! \brief  Check interrupt status flag.
//!         This function is used to check whether special flag is set or not.
//!
//! \param  [in] ulBase specifies the SPI module base address.
//! \param  [in] ulFlags is the flag you want to check
//!
//! \return The status of special flag.
//!         - xtrue The check flag has been set.
//!         - xflase The check flag has not been set.
//
//*****************************************************************************
xtBoolean SPIIntFlagCheck(unsigned long ulBase, unsigned long ulFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT((ulFlags == SPI_INT_EOT) ||
            (ulFlags == SPI_INT_RX)  ||
            (ulFlags == SPI_INT_TX)  ||
            (ulFlags == SPI_INT_ERROR));

    // Clear interrupt flag.
#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        return (xHWREG(ulBase + SPI_INT) & SPI_INT_SPIF) ? xtrue : xfalse;
    }
#endif
    return (xHWREG(ulBase + SSP_RIS) & ulFlags) ? xtrue : xfalse;
}

//*****************************************************************************
//
//! \brief  Clear SPI interrupt status flag.
//!         This function can be used to clear special SPI interrupt status flag.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \param  [in] ulFlags is SPI interrupt status flag.
//!              This parameter can be OR of the following value:
//!              - \ref SPI_INT_SPIF
//!
//! \return None.
//
//*****************************************************************************
void SPIIntFlagClear(unsigned long ulBase, unsigned long ulFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT((ulFlags == SPI_INT_EOT) ||
            (ulFlags == SPI_INT_RX)  ||
            (ulFlags == SPI_INT_TX)  ||
            (ulFlags == SPI_INT_ERROR));

    // Clear interrupt flag.
#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        xHWREG(ulBase + SPI_INT) |= SPI_INT_SPIF;
    }
#endif
    xHWREG(ulBase + SPI_INT) |= ulFlags;
}

//*****************************************************************************
//
//! \brief  Gets the number of bits transferred per frame.
//!         This function gets the number of bits transferred per frame.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \return The number of bits transferred per frame.
//!         For LPC175x/6x, this value can be 8/9/../16.
//!         For LPC177x/8x, this value can be 4/5/../16.
//
//*****************************************************************************
unsigned long xSPIBitLengthGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));

#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        return ((xHWREG(ulBase + SPI_CR) & SPI_CR_BITS_M) >> SPI_CR_BITS_S);
    }
#endif
    return (xHWREG(ulBase + SSP_CR0) & SSP_CR0_DSS_M);
}

//*****************************************************************************
//
//! \brief  Gets a data element from the SPI interface.
//!         This function gets received data from the interface of the specified
//!         SPI module and places that data into the location specified by the
//!         pulData parameter.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \param  [out] pulData is a pointer to a storage location for data that was
//!               received over the SPI interface.
//! \param  [in]  ulLen specifies the length of data will be read.
//!
//! \return None.
//!
//! \note   Only the lower N bits of the value written to pulData contain
//!         valid data, where N is the data width as configured by xSPIConfigSet().
//!         For example, if the interface is configured for 8-bit data width,
//!         only the lower 8 bits of the value written to pulData contain valid
//!         data.
//
//*****************************************************************************
void xSPIDataRead(unsigned long ulBase, unsigned long *pulRData, unsigned long ulLen)
{
    unsigned long i = 0;

    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT(pulData != 0);

    for(i = 0; i < ulLen; i++)
    {
        *pulRData++ = xSPISingleDataReadWrite(ulBase, 0x00);
    }
}

//*****************************************************************************
//
//! \brief  Write datas element to the SPI interface.
//!         This function transmitted data to the interface of the specified
//!         SPI module .
//!
//! \param  [in] ulBase specifies the SPI module base address.
//! \param  [in] pulWData is a pointer to a storage location for data that was
//!              transmitted over the SPI interface.
//! \param  [in] ulLen specifies the length of data will be write.
//!
//! \return None.
//!
//! \note   Only the lower N bits of the value written to pulData contain
//!         valid data, where N is the data width as configured by xSPIConfigSet().
//!         For example, if the interface is configured for 8-bit data width,
//!         only the lower 8 bits of the value written to pulData contain valid
//!         data.
//
//*****************************************************************************
void xSPIDataWrite(unsigned long ulBase, unsigned long *pulWData,
                          unsigned long ulLen)
{
    unsigned long i = 0;

    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT(pulData != 0);

    for(i = 0; i < ulLen; i++)
    {
        xSPISingleDataReadWrite(ulBase, *pulWData++);
    }
}

//*****************************************************************************
//
//! \brief  Write data element to the SPI interface with block.
//!         This function transmitted data to the interface of the specified SPI
//!         module with block. when the TX and TX shift are both empty or in FIFO
//!         mode the TX FIFO depth is equal to or less than the trigger level,
//!         the data element can be transmitted, otherwise the data element will
//!         be blocked until can be transmitted.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \param  [in] ulData is data that was transmitted over the SPI interface.
//!
//! \return None.
//!
//! \note   Only the lower N bits of the value written to pulData contain
//!         valid data, where N is the data width as configured by xSPIConfigSet().
//!         For example, if the interface is configured for 8-bit data width,
//!         only the lower 8 bits of the value written to pulData contain valid
//!         data.
//
//*****************************************************************************
void xSPIDataPut(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));

#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
    // Wait last transmit done then write data to SPI data register.
        while(0 == (xHWREG(ulBase + SPI_SR) & SPI_SR_SPIF));
        xHWREG(ulBase + SPI_DR) = ulData & SPI_DR_DATA_M;
    }
#endif
    // Wait last transmit done then write data to SSPn data register.
    while(0 != (xHWREG(ulBase + SSP_SR) & SSP_SR_TFE));
    xHWREG(ulBase + SSP_DR) = ulData & SSP_DR_DATA_M;
}

//*****************************************************************************
//
//! \brief  Write data element to the SPI interface with Noblock.
//!         This function transmitted data to the interface of the specified
//!         SPI module with Noblock.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \param  [in] ulData is data that was transmitted over the SPI interface.
//!
//! \return The number of data that has been transfered..
//!
//! \note   Only the lower N bits of the value written to pulData contain
//!         valid data, where N is the data width as configured by xSPIConfigSet().
//!         For example, if the interface is configured for 8-bit data width,
//!         only the lower 8 bits of the value written to pulData contain valid
//!         data.
//!
//
//*****************************************************************************
void xSPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));

#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        // Write Data to SPI Data register.
        xHWREG(ulBase + SPI_DR) = ulData & SPI_DR_DATA_M;
    }
#endif
    // Write Data to SSPn Data register.
    xHWREG(ulBase + SSP_DR) = ulData & SSP_DR_DATA_M;
}

//*****************************************************************************
//
//! \brief  Gets a data element from the SPI interface with block.
//!         This function gets received data from the interface of the specified
//!         SPI module with block. when the RX not empty flag is set, the data
//!         element can be transmitted, otherwise the data element will be
//!         blocked until can be transmitted.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \param  [out] pulData is a pointer to a storage location for data that was
//!               received over the SPI interface.
//!
//! \note   Only the lower N bits of the value written to pulData contain
//!         valid data, where N is the data width as configured by xSPIConfigSet().
//!         For example, if the interface is configured for 8-bit data width,
//!         only the lower 8 bits of the value written to pulData contain valid
//!         data.
//!
//! \return None.
//
//*****************************************************************************
void xSPIDataGet(unsigned long ulBase, unsigned long * pulData)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT(pulData != 0);

#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        while(0 == (xHWREG(ulBase + SPI_SR) & SPI_SR_SPIF));
        *pulData = xHWREG(ulBase + SPI_DR) & SPI_DR_DATA_M;
    }
#endif
    // Wait until receive one byte, then read data from SPI Data register.
    while(0 != (xHWREG(ulBase + SSP_SR) & SSP_SR_RNE));
    *pulData = xHWREG(ulBase + SSP_DR) & SSP_DR_DATA_M;
}

//*****************************************************************************
//
//! \brief  Gets a data element from the SPI interface with Noblock.
//!         This function gets received data from the interface of the specified
//!         SPI module with Noblock.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!              - \ref xSPI1_BASE
//!              - \ref xSPI2_BASE
//!
//! \param  [out] pulData is a pointer to a storage location for data that was
//!               received over the SPI interface.
//!
//! \note   Only the lower N bits of the value written to pulData contain
//!         valid data, where N is the data width as configured by xSPIConfigSet().
//!         For example, if the interface is configured for 8-bit data width,
//!         only the lower 8 bits of the value written to pulData contain valid
//!         data.
//!
//! \return None.
//
//*****************************************************************************
void xSPIDataGetNonBlocking(unsigned long ulBase, unsigned long * pulData)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));
    xASSERT(pulData != 0);
	
#if defined(LPC_175x) || defined (LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        *pulData = xHWREG(ulBase + SPI_DR) & SPI_DR_DATA_M;
    }
#endif
    // Read data from SPI Data register.
    *pulData = xHWREG(ulBase + SSP_DR) & SSP_DR_DATA_M;
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
xtBoolean xSPIIsBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(SPIBaseValid(ulBase));

#if defined(LPC_175x) || defined(LPC_176x)
    if(ulBase == SPI2_BASE)
    {
        return (xHWREG(ulBase + SPI_SR) & SPI_SR_SPIF);
    }		
#endif
    return (xHWREG(ulBase + SSP_SR) & SSP_SR_BSY);
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
//! \b xtrue The Rx buffer is empty,or \b xfalse The Rx buffer is not empty.
//
//*****************************************************************************        
xtBoolean xSPIIsRxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    return (!(xHWREG(ulBase + SSP_SR) & SSP_SR_TFE));
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
xtBoolean xSPIIsTxEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    return (xHWREG(ulBase + SSP_SR) & SSP_SR_TFE);
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
//! \b xtrue The Rx buffer is full,or \b xfalse The Rx buffer is not full.
//
//*****************************************************************************        
xtBoolean xSPIIsRxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    return (xHWREG(ulBase + SSP_SR) & SSP_SR_RFF);
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
//! \b xtrue The Tx buffer is in full,or \b xfalse The Tx buffer is not full.
//
//*****************************************************************************        
xtBoolean xSPIIsTxFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    return (!(xHWREG(ulBase + SSP_SR) & SSP_SR_TNF));
}
 
//*****************************************************************************
//
//! \brief Enable the DMA of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulDmaMode specifies the SPI module base address.
//! Details please refer to \ref xSPI_DMA.
//!
//! This function enable the DMA of the specified SPI port.
//!
//! The \e ulDmaMode parameter can be one of the following values:
//! \b xSPI_DMA_RX, \b xSPI_DMA_TX ,or \b xSPI_DMA_BOTH.
//! Details please refer to \ref xSPI_DMA_CoX.
//!
//! \return None.
//
//*****************************************************************************        
void xSPIDMAEnable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    if(ulDmaMode & SPI_DMA_RX)
    {
        xHWREG(ulBase + SSP_DMACR) |= SSP_DMACR_RXDMAE;
    }
    if(ulDmaMode & SPI_DMA_TX)
    {
        xHWREG(ulBase + SSP_DMACR) |= SSP_DMACR_TXDMAE;
    }	
}

//*****************************************************************************
//
//! \brief Disable the DMA of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulDmaMode specifies the SPI module base address.
//! Details please refer to \ref xSPI_DMA.
//!
//! This function disable the DMA of the specified SPI port.
//!
//! The \e ulDmaMode parameter can be one of the following values:
//! \b SPI_DMA_RX, \b SPI_DMA_TX ,or \b SPI_DMA_BOTH.
//! Details please refer to \ref xSPI_DMA_CoX.
//!
//! \return None.
//
//*****************************************************************************        
void xSPIDMADisable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    if(ulDmaMode & SPI_DMA_RX)
    {
        xHWREG(ulBase + SSP_DMACR) &= ~SSP_DMACR_RXDMAE;
    }
    if(ulDmaMode & SPI_DMA_TX)
    {
        xHWREG(ulBase + SSP_DMACR) &= ~SSP_DMACR_TXDMAE;
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
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    xHWREG(ulBase + SSP_CR1) |= SSP_CR1_SSE;
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
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) ||
#if defined(LPC_177x) || defined(LPC_178x)
            (ulBase == SPI2_BASE) ||
#endif
            (ulBase == SPI1_BASE));

    xHWREG(ulBase + SSP_CR1) &= ~SSP_CR1_SSE;
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
//! \b xSPI_SS_HARDWARE.
//! Details please reference to \ref xSPI_SlaveSelMode_CoX.
//!
//! The \e ulSlaveSel can be one of the following values:
//! \b xSPI_SS0, Details please reference to \ref xSPI_SlaveSel_CoX.
//!
//! \note this is only for master.
//!
//! \return None.
//
//*****************************************************************************
void xSPISSSet(unsigned long ulBase, unsigned long ulSSMode, unsigned long ulSlaveSel)
{
    
}