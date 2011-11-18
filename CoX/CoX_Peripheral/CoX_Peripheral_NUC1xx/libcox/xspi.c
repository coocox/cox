//*****************************************************************************
//
//! \file xspi.c
//! \brief Driver for the SPI
//! \version V2.1.1.1
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
SPI0IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI0_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_IF;

    ulEventFlags |= xHWREG(ulBase + SPI_CNTRL2) & SPI_CNTRL2_SLV_START_INTSTS;
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IF;
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SLV_START_INTSTS;
    
    
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
SPI1IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI1_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_IF;

    ulEventFlags |= xHWREG(ulBase + SPI_CNTRL2) & SPI_CNTRL2_SLV_START_INTSTS;
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IF;
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SLV_START_INTSTS;
    
    
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
SPI2IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI2_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_IF;

    ulEventFlags |= xHWREG(ulBase + SPI_CNTRL2) & SPI_CNTRL2_SLV_START_INTSTS;
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IF;
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SLV_START_INTSTS;
    
    
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
SPI3IntHandler(void)
{
    unsigned long ulEventFlags;
    unsigned long ulBase = SPI3_BASE;
    
    //
    // Gets interrupt status
    //
    ulEventFlags = xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_IF;

    ulEventFlags |= xHWREG(ulBase + SPI_CNTRL2) & SPI_CNTRL2_SLV_START_INTSTS;
    

    //
    // Clear Int flag
    //
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IF;
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SLV_START_INTSTS;
    
    
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
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
SPIConfig(unsigned long ulBase, unsigned long ulBitRate,
                    unsigned long ulConfig)
{
    unsigned long ulPCLK;
    unsigned long ulPreDiv;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
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
    ulPCLK = SysCtlHClockGet();
    ulPreDiv = (((ulPCLK / ulBitRate)+1) >> 1) -1 ;
    if (ulPreDiv > 65535)
    {
        ulPreDiv = 65535;
    }
    if (ulPreDiv < 1)
    {
        ulPreDiv = 1;
    }
    
    xHWREG(ulBase + SPI_DIVIDER) = ulPreDiv;
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
SPISingleDataReadWrite(unsigned long ulBase, unsigned long ulWData)
{
    unsigned long ulReadTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until SPI is not busy,data to be write.
    //
    while((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_GO_BUSY))
    {
    }
    xHWREG(ulBase + SPI_TX0) = ulWData;

    //
    // 
    //
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_GO_BUSY;
    
    //
    // Wait until there is data to be read.
    //
    
    while((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_GO_BUSY))
    {
    }
    
    //
    // write data to SPI.
    //
    ulReadTemp = xHWREG(ulBase + SPI_RX0);
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
SPIBitLengthGet(unsigned long ulBase)
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
SPIDataRead(unsigned long ulBase, void *pulRData, unsigned long ulLen)
{
    unsigned long i;
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
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
            SPISingleDataReadWrite(ulBase, 0xFF);
        }
        else if (ucBitLength >= 8 && ucBitLength <= 16)
        {
            ((unsigned short*)pulRData)[i] = 
            SPISingleDataReadWrite(ulBase, 0xFFFF);
        }   
        else
        {
            ((unsigned long*)pulRData)[i] = 
            SPISingleDataReadWrite(ulBase, 0xFFFFFF);
        }
    }
}


//*****************************************************************************
//
//! \brief Read two words of data from SPI Rx registers.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SSI interface.
//!
//! This function Read two words of data from SPI Rx registers of the specified
//! SSI module and places that data into the location specified by the
//! \e pulData parameter.and then trigger SPI for next transfer.
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
SPIBurstDataRead(unsigned long ulBase, unsigned long *pulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until there is data to be read.
    //
    while((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_GO_BUSY))
    {
    }

    //
    // Read data from SSI.
    //
    pulData[0] = xHWREG(ulBase + SPI_RX0);
    pulData[1] = xHWREG(ulBase + SPI_RX1);
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_GO_BUSY;
}


//*****************************************************************************
//
//! \brief Read data from Rx registers.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SSI interface.
//! \param ulCount specifies the number will read from Rx registers.
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
//! SSIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return Returns the number of elements read from the SPI Rx registers.
//
//*****************************************************************************
unsigned long
SPIRxRegisterGet(unsigned long ulBase, unsigned long *pulData, 
                 unsigned long ulCount)
{
    unsigned long i;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT(ulCount < 2);

    //
    // Wait until there is data to be read.
    //

    //
    // Read data from SPI Rx Register.
    //
    for (i=0; i<ulCount; i++)
    {
        pulData[i] = xHWREG(ulBase + SPI_RX0 + 4*i);
    }
    return ulCount;
    
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
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    for (i=0; i<ulLen; i++)
    {
        if (ucBitLength <= 8)
        {
            SPISingleDataReadWrite(ulBase, ((unsigned char*)pulWData)[i]);
        }
        else if (ucBitLength >= 8 && ucBitLength <= 16)
        {
            SPISingleDataReadWrite(ulBase, ((unsigned short*)pulWData)[i]);
        }   
        else
        {
            SPISingleDataReadWrite(ulBase, ((unsigned long*)pulWData)[i]);
        }
    }
}

//*****************************************************************************
//
//! \brief Write two datas element to the SPI interface.
//!
//! \param ulBase specifies the SSI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! transmitted over the SSI interface.
//!
//! This function  transmitted two data to the interface of the specified
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
SPIBurstDataWrite(unsigned long ulBase, unsigned long *pulData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until there is data to be Write.
    //
    while((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_GO_BUSY))
    {
    }

    //
    // Write data to SPI.
    //
    xHWREG(ulBase + SPI_TX0) = pulData[0];
    xHWREG(ulBase + SPI_TX1) = pulData[1];
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_GO_BUSY;
}

//*****************************************************************************
//
//! \brief Write data to Tx registers.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! write to the SPI interface.
//! \param ulCount specifies the number will write to Tx registers.
//!
//! This function write data to Tx registers of the specified SPI
//! module and This function will not trigger a SPI data transfer. 
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SSIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return Returns the number of elements write to the SPI Tx registers.
//
//*****************************************************************************
unsigned long
SPITxRegisterSet(unsigned long ulBase, unsigned long *pulData, 
                 unsigned long ulCount)
{
    unsigned long i;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    //
    // Wait until there is data to be read.
    //

    //
    // Read data from SPI Rx Register.
    //
    for (i=0; i<ulCount; i++)
    {
        xHWREG(ulBase + SPI_TX0 + 4*i) = pulData[i];
    }
    return ulCount;
    
}


//*****************************************************************************
//
//! \brief Set the GO_BUSY bit to trigger a SPI data transfer.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function is to set the GO_BUSY bit to trigger a SPI data transfer.
//!
//! \note all registers should be set before call this function.In FIFO mode,
//! GoBusy bit becomes a read only bit and will be controlled by hardware.
//!
//! \return None.
//
//*****************************************************************************
void
SPIBitGoBusySet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_GO_BUSY;
}

//*****************************************************************************
//
//! \brief Clear the GO_BUSY bit to stop a SPI data transfer.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function is to clear the GO_BUSY bit to stop a SPI data transfer.
//!
//! \note call this function will stop a data transfer.In FIFO mode,
//! GoBusy bit becomes a read only bit and will be controlled by hardware.
//!
//! \return None.
//
//*****************************************************************************
void
SPIBitGoBusyClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_GO_BUSY;
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
SPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IE;
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
SPIIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_IE;
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
SPIIntFlagGet(unsigned long ulBase, xtBoolean xbMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT(xbMasked == xfalse);
    return (xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_IF);
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_IF;
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
    xHWREG(ulBase + SPI_SSR) |= SPI_AUTOSS;
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

    xHWREG(ulBase + SPI_SSR) &= ~SPI_AUTOSS;
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT((ulSSTriggerMode == SPI_SS_EDGE_TRIGGER) || 
            (ulSSTriggerMode == SPI_SS_LEVEL_TRIGGER));
    xASSERT((ulSSActType == SPI_SS_ACTIVE_LOW_FALLING) || 
            (ulSSActType == SPI_SS_ACTIVE_HIGH_RISING));
    
    xHWREG(ulBase + SPI_SSR) |= ulSSTriggerMode | ulSSActType;
}


//*****************************************************************************
//
//! \brief Get the level-trigger transmission status of the specified SPI port.
//!
//! \param ulBase specifies the SSI module base address.
//!
//! This function is to get the level-trigger transmission status of the 
//! specified SPI port.
//!
//! \note this is Only for slave mode.
//!
//! \return the level-trigger transmission status.
//! \b xtrue The transaction number and the transferred bit length met the 
//! requirements which defines in TX_NUM and TX_BIT_LEN among one transfer.
//! or \b xfalse The transaction number or the transferred bit length of one 
//! transaction doesn't meet the requirements.
//
//*****************************************************************************
xtBoolean
SPILevelTriggerStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));

    return ((xHWREG(ulBase + SPI_SSR) & SPI_LTRIG_FLAG) ? xtrue : xfalse);
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    return ((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_GO_BUSY) ? xtrue : xfalse);
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    return ((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_RX_EMPTY)? xtrue : xfalse);
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    return ((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_RX_FULL)? xtrue : xfalse);
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    return ((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_TX_EMPTY)? xtrue : xfalse);
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
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    return ((xHWREG(ulBase + SPI_CNTRL) & SPI_CNTRL_TX_FULL)? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Check the status of the FIFO buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function Check the FIFO buffer status of the specified SPI module.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function..
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    return (xHWREG(ulBase + SPI_CNTRL) & (SPI_CNTRL_TX_FULL) || 
            (SPI_CNTRL_RX_FULL) || (SPI_CNTRL_TX_EMPTY) || (SPI_CNTRL_RX_EMPTY));
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
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
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
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT((ulInterval == 0) ||((ulInterval >= 2) && (ulInterval <= 15)));
    if (xtEnable)
    {
        xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_SP_CYCLE_M;
        xHWREG(ulBase + SPI_CNTRL) |= (ulInterval << SPI_CNTRL_SP_CYCLE_S);
        xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_FIFO;
    }
    else
    {
        xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_FIFO;
    }  
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
//! The \e ulByteReorder parameter can be one of the following values:
//! \b SPI_BYTE_REORDER_SUSPEND_DISABLE, \b SPI_BYTE_REORDER_SUSPEND,
//! \b SPI_BYTE_REORDER, or \b SPI_BYTE_SUSPEND
//! 
//! \note The Byte Reorder function is supported only in 16-, 24- and 
//! 32-bit transaction mode. The Byte Suspend function is only available 
//! in 32-bit transaction.
//!
//! \return None.
//
//*****************************************************************************
void
SPIByteReorderSet(unsigned long ulBase, unsigned long ulByteReorder)
{
    unsigned char ucBitLength = SPIBitLengthGet(ulBase);
#ifdef xDEBUG
    unsigned long ulTemp[4]={0, 3, 2, 1};
#endif
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT((ulByteReorder <= 3) || (ulByteReorder >= 0));
    xASSERT((ulTemp[ulByteReorder] & 1) && (ucBitLength == 0));
    xASSERT((ulTemp[ulByteReorder] & 2) && ((ucBitLength == 0) || 
            (ucBitLength == 16) || (ucBitLength == 24)));
    
   xHWREG(ulBase + SPI_CNTRL) |= (ulByteReorder << SPI_CNTRL_REORDER_S);
}

//*****************************************************************************
//
//! \brief Set the variable clock function. Only for master mode.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulPattern Specify the variable clock pattern.
//! \param xtEnable specifies enable the variable clock function or not.
//! \param ulClock1 specifies the clock rate 1.
//! \param ulClock2 specifies the clock rate 2.
//!
//! This function set the variable clock function of the specified 
//! SPI module.
//!
//! 
//! \note If the bit pattern of VARCLK is '0', the output frequency of SPICLK 
//! is according to the value of DIVIDER1,If the bit pattern of VARCLK is '1', 
//! the output frequency of SPICLK is according to the value of DIVIDER2.
//!
//! \return None.
//
//*****************************************************************************
void
SPIVariableClockSet(unsigned long ulBase, unsigned long ulPattern, 
                    xtBoolean xtEnable, unsigned long ulClock1, 
                    unsigned long ulClock2)
{
    unsigned long ulPCLK,ulPreDiv;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    xASSERT((ulClock1 != 0));
    xASSERT((ulClock2 != 0));
    xHWREG(ulBase + SPI_CNTRL) |= SPI_CNTRL_VARCLK_EN;
    
    //
    // Set the clock rate.
    //
    ulPCLK = SysCtlHClockGet();
    ulPreDiv = (((ulPCLK / ulClock1)+1) >> 1) -1 ;
    if (ulPreDiv > 65535)
    {
        ulPreDiv = 65535;
    }
    if (ulPreDiv < 1)
    {
        ulPreDiv = 1;
    }
    
    xHWREG(ulBase + SPI_DIVIDER) |= (ulPreDiv & SPI_DIVIDER_DIVIDER_M);
    
    ulPCLK = SysCtlHClockGet();
    ulPreDiv = (((ulPCLK / ulClock2)+1) >> 1) -1 ;
    if (ulPreDiv > 65535)
    {
        ulPreDiv = 65535;
    }
    if (ulPreDiv < 1)
    {
        ulPreDiv = 1;
    }
    
    xHWREG(ulBase + SPI_DIVIDER) |= ((ulPreDiv << SPI_DIVIDER_DIVIDER2_S) 
                                                & SPI_DIVIDER_DIVIDER2_M);
}

//*****************************************************************************
//
//! \brief Enable/disable the DIV_ONE feature of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param xtEnable enable this fuction or not.
//!
//! This function enable the DIV_ONE feature. The SPI clock rate will be equal
//! to system clock rate.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//! When this fuction is enabled, both the REORDER field and the VARCLK_EN
//! field must be configured as 0. In other words, the byte-reorder function,
//! byte suspend function and variable clock function must be disable.
//!
//! \return None.
//
//*****************************************************************************
void
SPIDivOneFunction(unsigned long ulBase, xtBoolean xtEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    if (xtEnable)
    {
        xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_DIV_ONE;
        xHWREG(ulBase + SPI_CNTRL) &= ~SPI_CNTRL_VARCLK_EN; 
        xHWREG(ulBase + SPI_CNTRL) &= (~SPI_CNTRL_REORDER_M);
    }
    else
    {
        xHWREG(ulBase + SPI_CNTRL2) &= ~SPI_CNTRL2_DIV_ONE;
    }
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
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//! In no slave select signal mode, the SS_LTRIG, SPI_SSR[4], shall be
//! set as 1.
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
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    if (xtEnable)
    {
        xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_NOSLVSEL;
        xHWREG(ulBase + SPI_SSR) |= SPI_SS_LTRIG;
    }
    else
    {
        xHWREG(ulBase + SPI_CNTRL2) &= ~SPI_CNTRL2_NOSLVSEL;
    }
}

//*****************************************************************************
//
//! \brief Abort transfer when using 3-wire SPI.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function abort transfer when using 3-wire SPI.If using 3-wire SPI as 
//! slave, when slave start interrupt status is set but transfer done flag  
//! doesn't be set over a reasonable time, use this function to abort this
//! transfer.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3WireAbort(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SLV_ABORT;
}

//*****************************************************************************
//
//! \brief Enable the 3-wire SPI start interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function enable the 3-wire SPI start interrupt of the specified 
//! SPI port and install the callback function.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3WireStartIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SSTA_INTEN;

}

//*****************************************************************************
//
//! \brief Disable the 3-wire SPI start interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function disable the 3-wire SPI start interrupt of the specified 
//! SPI port.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3WireStartIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    xHWREG(ulBase + SPI_CNTRL2) &= ~SPI_CNTRL2_SSTA_INTEN;
}

//*****************************************************************************
//
//! \brief Get the 3-wire SPI start interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function get the 3-wire SPI start interrupt flag of the specified 
//! SPI port.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//!
//! \return None.
//
//*****************************************************************************
unsigned long
SPI3WireStartIntFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    return (xHWREG(ulBase + SPI_CNTRL2) & SPI_CNTRL2_SLV_START_INTSTS);
}

//*****************************************************************************
//
//! \brief Clear the 3-wire SPI start interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function clear the 3-wire SPI start interrupt flag of the specified 
//! SPI port.
//!
//! \note Only the chips with the part number NUC1x0xxxCx, ex: NUC140VE3CN, 
//! can support this function.
//!
//! \return None.
//
//*****************************************************************************
void
SPI3WireStartIntFlagClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    xHWREG(ulBase + SPI_CNTRL2) |= SPI_CNTRL2_SLV_START_INTSTS;
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
SPI3PDMAEnable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
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
SPI3PDMADisable(unsigned long ulBase, unsigned long ulDmaMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == SPI0_BASE) || (ulBase == SPI1_BASE)||
            (ulBase == SPI2_BASE) || (ulBase == SPI3_BASE));
    
    xHWREG(ulBase + SPI_DMACTL) &= ~ulDmaMode;
}

