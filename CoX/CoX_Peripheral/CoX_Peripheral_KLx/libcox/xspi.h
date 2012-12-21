//*****************************************************************************
//
//! \file xspi.h
//! \brief Prototypes for the SPI Driver.
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
//! THE POSPIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef __xSPI_H__
#define __xSPI_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Ints xSPI Interrupts
//! 
//! \section xSPI_Ints_Section 1. Where to use this group
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned from SPIIntStatus. 
//! 
//! \section xSPI_Ints_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Interrupts         |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_EOT            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_TX_FIFO        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_RX_FIFO        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_ERROR          |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer
//
#define xSPI_INT_EOT            SPI_SPTEF

//
//! Transmit FIFO reduced to a level or less the level(in KLx mcu, the level 
//! is full of the FIFO(1 Byte)), Notify users to write to the tx FIFO.
//
#define xSPI_INT_TX_FIFO        SPI_SPTEF

//
//! Receive FIFO accumulate to a level or bigger than the level(in KLx mcu, the 
//! level is full of the FIFO(1 Byte)), Notify users to read from the rx FIFO.
//
#define xSPI_INT_RX_FIFO        SPI_SPRF

//
//! Error
//
#define xSPI_INT_ERROR          SPI_MODF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Ints_Event xSPI Interrupt Event
//! 
//! \section xSPI_Ints_Event_Section 1. Where to use this group
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned from SPIIntStatus. 
//! \n
//! \section xSPI_Ints_Event_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Interrupts         |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_EOT          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_TXFF         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVNET_RXFF         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_ERROR_RXTO   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_ERROR_RXOR   |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer
//
#define xSPI_EVENT_EOT          SPI_SPTEF

//
//! Transmit FIFO reduced to a level or less the level(in KLx mcu, the level 
//! is full of the FIFO(1 Byte)), Notify users to write to the tx FIFO.
//
#define xSPI_EVENT_TXFF         SPI_SPTEF

//
//! Receive FIFO accumulate to a level or bigger than the level(in KLx mcu, 
//! the level is full of the FIFO(1 Byte)), Notify users to read from the rx FIFO.
//
#define xSPI_EVNET_RXFF         SPI_SPRF

//
//! Receive Timeout
//
#define xSPI_EVENT_ERROR_RXTO   0

//
//! Receive Overrun
//
#define xSPI_EVENT_ERROR_RXOR   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Config xSPI Configure
//! 
//! \section xSPI_Config_Section 1. Where to use this group
//! Values that can be passed to xSPIConfig()
//! as the ulConfig parameter. 
//! \n
//! \section xSPI_Config_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Configs            |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPI_MOTO_FORMAT_MODE_0 |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_MOTO_FORMAT_MODE_1 |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_MOTO_FORMAT_MODE_2 |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_MOTO_FORMAT_MODE_3 |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_TI_FORMAT_MODE     |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_NMW_FORMAT_MODE    |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |                        |                |                        |
//! |------------------------|----------------|------------------------|
//! |xSPI_MODE_MASTER        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_MODE_SLAVE         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |                        |                |                        |
//! |------------------------|----------------|------------------------|
//! |xSPI_MSB_FIRST          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_LSB_FIRST          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |                        |                |                        |
//! |------------------------|----------------|------------------------|
//! |xSPI_DATA_WIDTHn        |  Non-Mandatory |    		   N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

// +----------+-----------------+--------------+--------------------+
// | 31 - 24  |     23 - 16     |    15 - 8    |        7 - 0       |
// |----------------------------------------------------------------|
// | reserved | Protocol Format | Master/Slave |  Shifter Direction |
// +----------+-----------------+--------------+--------------------+

//
//! Moto Format, polarity 0, phase 0
//
#define xSPI_MOTO_FORMAT_MODE_0 (SPI_FRF_MOTO_MODE_0 << 16)

//
//! Moto Format, polarity 0, phase 1
//  
#define xSPI_MOTO_FORMAT_MODE_1 (SPI_FRF_MOTO_MODE_1 << 16)
                                             
//
//! Moto Format, polarity 1, phase 0
//  
#define xSPI_MOTO_FORMAT_MODE_2 (SPI_FRF_MOTO_MODE_2 << 16)
                                           
//
//! Moto Format, polarity 1, phase 1
//
#define xSPI_MOTO_FORMAT_MODE_3 (SPI_FRF_MOTO_MODE_3 << 16)                                         

#define xSPI_MODE_MASTER        (SPI_MODE_MASTER << 8)
#define xSPI_MODE_SLAVE         (SPI_MODE_SLAVE << 8)

#define xSPI_MSB_FIRST          SPI_MSB_FIRST   
#define xSPI_LSB_FIRST          SPI_LSB_FIRST
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_DMA xSPI DMA
//! 
//! \section xSPI_DMA_Section 1. Where to use this group
//! Values that can be passed to xSPIDMAEnable() and xSPIDMADisable()
//! as the ulDmaMode parameter. 
//! 
//! \section xSPI_DMA_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI DMA                |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPI_DMA_TX             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |SPI_DMA_RX              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |SPI_DMA_BOTH            |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define xSPI_DMA_TX             SPI_DMA_TX
  
//
//! Enable DMA for receive
//
#define xSPI_DMA_RX             SPI_DMA_RX

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_SlaveSelMode xSPI Slave Select(FSS) Mode
//! 
//! \section xSPI_SlaveSelMode_Section 1. Where to use this group
//! Values that can be passed to xSPISSSet()
//! as the ulSSMode parameter. 
//! \n
//! \section xSPI_SlaveSelMode_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Slave Select Mode  |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_HARDWARE        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_SOFTWARE        |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSPI_SS_HARDWARE        0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_SlaveSel xSPI Slave Select
//! \brief Values that show xSPI Slave Select
//! \n
//! \section xSPI_SlaveSel_Section 1. Where to use this group
//! Values that can be passed to xSPISSSet()
//! as the ulSlaveSel parameter. 
//! \n
//! \section xSPI_SlaveSel_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Slave Select       |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_NONE            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_SSn                |    Mandatory   |        xSPI_SS0        |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSPI_SS_NONE            0  
 
#define xSPI_SS0                0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Exported_APIs xSPI API
//! \brief xSPI API Reference.
//!
//! \section xSPI_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI API                |       CoX      |       Stellaris        |
//! |------------------------|----------------|------------------------|
//! |xSPIConfigSet           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIBitLengthGet        |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPISingleDataReadWrite |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataRead            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataWrite           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataBufferRead      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataBufferReadNonBlocking  Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataBufferWrite     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataBufferWriteNonBlocking Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIntEnable           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIntCallbackInit     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIntDisable          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIStatusGet           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsBusy              |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsRxEmpty           |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsTxEmpty           |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsRxFull            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsTxFull            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPIDMAEnable           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDMADisable          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIEnable              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDisable             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPISSSet               |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Configures the synchronous serial interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulBitRate specifies the clock rate.
//! \param ulConfig is the required configuration of the SPI.
//! Details please refer to \ref xSPI_Config.
//!
//! This function configures the synchronous serial interface.  It sets
//! the SPI protocol, mode of operation, bit rate, and the first bit
//! shift direction.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The Protocol of SPI can be one of the following values:
//! \b xSPI_MOTO_FORMAT_MODE_0, \b xSPI_MOTO_FORMAT_MODE_1,
//! \b xSPI_MOTO_FORMAT_MODE_2, \b xSPI_MOTO_FORMAT_MODE_3. 
//! The Motorola frame formats imply the following polarity and phase 
//! configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   xSPI_MOTO_FORMAT_MODE_0
//!   0       1   xSPI_MOTO_FORMAT_MODE_1
//!   1       0   xSPI_MOTO_FORMAT_MODE_2
//!   1       1   xSPI_MOTO_FORMAT_MODE_3
//! </pre>
//!  
//! The SPI module can operate as a master or slave;  The Mode of SPI
//! can be one of the following values: \b xSPI_MODE_MASTER, or
//! \b xSPI_MODE_SLAVE.
//!
//! The \e ulBitRate parameter defines the bit rate for the SPI.  This bit rate
//! must satisfy the following clock ratio criteria:
//!
//! - 0 !=  bit rate (master mode)
//!
//! The first bit shift direction of the data transfers can be one of the 
//! following values: \b xSPI_MSB_FIRST or \b xSPI_LSB_FIRST.
//! 
//! Details please refer to \ref xSPI_Config_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIConfigSet(ulBase, ulBitRate, ulConfig)                            \
        do                                                                    \
        {                                                                     \
                 SPIConfigSetExpClk(ulBase,                                   \
                            xSysCtlClockGet()/2,                                \
                            (ulConfig >> 16) & 0xFF,                          \
                            (ulConfig >> 8) & 0xFF,                           \
                            ulBitRate,                                        \
                            ulConfig & 0xFF);                                 \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Gets the number of bits transferred per frame.
//!
//! \param ulBase specifies the SPI module base address.
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
#define xSPIBitLengthGet(ulBase)                                              \
        0


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
#define xSPISingleDataReadWrite(ulBase, ulWData)                              \
        SPISingleDataReadWrite(ulBase, ulWData) 

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
//! SPIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************        
#define xSPIDataRead(ulBase, pulRData, ulLen)                                 \
        SPIDataRead(ulBase, pulRData, ulLen)

//*****************************************************************************
//
//! \brief Write  datas element to the SPI interface.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulWData is a pointer to a storage location for data that was
//! transmitted over the SPI interface.
//! \param ulLen specifies the length of data will be write.
//!
//! This function transmitted data to the interface of the specified
//! SPI module .
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! SPIConfigSetExpClk().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************        
#define xSPIDataWrite(ulBase, pulWData, ulLen)                                \
        SPIDataWrite(ulBase, pulWData, ulLen)

//*****************************************************************************
//
//! \brief Puts a data element into the SPI transmit FIFO.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulData is the data to be transmitted over the SPI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SPI module.
//!
//! \note The upper 32 - N bits of the \e ulData are discarded by the hardware,
//! where N is the data width as configured by xSPIConfigSet().  For
//! example, if the interface is configured for 8-bit data width, the upper 24
//! bits of \e ulData are discarded.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIDataBufferWrite(ulBase, ulData)                                   \
        SPIDataPut(ulBase, ulData)

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
//! \note The upper 32 - N bits of the \e ulData are discarded by the hardware,
//! where N is the data width as configured by xSPIConfigSet().  For
//! example, if the interface is configured for 8-bit data width, the upper 24
//! bits of \e ulData are discarded.
//!
//! \return Returns the number of elements written to the SPI transmit FIFO.
//
//*****************************************************************************
#define xSPIDataBufferWriteNonBlocking(ulBase, ulData)                        \
        SPIDataPutNonBlocking(ulBase, ulData)

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
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! xSPIConfigSet().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIDataBufferRead(ulBase, pulData)                                   \
        SPIDataGet(ulBase, pulData)

//*****************************************************************************
//
//! \brief Gets a data element from the SPI receive FIFO/buffer.
//!
//! \param ulBase specifies the SPI module base address.
//! \param pulData is a pointer to a storage location for data that was
//! received over the SPI interface.
//!
//! This function gets a received data from the receive FIFO of the specified SPI
//! module and places that data into the location specified by the \e pulData
//! parameter.  If there is no data in the FIFO, then this function  returns a
//! zero.
//!
//! \note Only the lower N bits of the value written to \e pulData contain
//! valid data, where N is the data width as configured by
//! xSPIConfigSet().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return Returns 0 if there is no data in the FIFO, or 1 if succssful get a 
//! data element.
//
//*****************************************************************************
#define xSPIDataBufferReadNonBlocking(ulBase, pulData)                        \
        SPIDataGetNonBlocking(ulBase, pulData)


//*****************************************************************************
//
//! \brief Enable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param ulIntFlags specifies the type of SPI interrupt.
//! Details please refer to \ref xSPI_Ints.
//!
//! This function is to enable the SPI interrupt of the specified SPI port.
//!
//! \return None.
//
//*****************************************************************************        
#define xSPIIntEnable(ulBase, ulIntFlags)                                     \
        SPIIntEnable(ulBase, ulIntFlags)

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified SPI Port.
//!
//! \param ulPort is the base address of the SPI port.
//! \param pfnCallback is callback for the specified SPI Port.
//!
//! Init interrupts callback for the specified SPI Port.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIIntCallbackInit(ulBase, pfnCallback)                            \
        SPIIntCallbackInit(ulBase, pfnCallback)

//*****************************************************************************
//
//! \brief Disable the SPI interrupt of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function is to disable the SPI interrupt of the specified SPI port 
//!
//! \return None.
//
//*****************************************************************************        
#define xSPIIntDisable(ulBase, ulIntFlags)                                    \
        SPIIntDisable(ulBase, ulIntFlags) 

//*****************************************************************************
//
//! \brief Get the SPI interrupt status of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function returns the interrupt status for the SPI module. 
//!
//! \return the current SPI interrupt status, enumerated as a bit field of:
//! - \ref xSPI_ERROR_RXTO
//! - \ref xSPI_ERROR_RXOR
//! - more refrence \ref xSPI_Error
//!
//
//*****************************************************************************        
#define xSPIStatusGet(ulBase, xbMasked)                                      \
        SPIIntStatus(ulBase, xbMasked) 

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
#define xSPIIsBusy(ulBase)                                                    \
        0

//*****************************************************************************
//
//! \brief Check the empty status of the Rx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return Returns \b xtrue if the SPI Rx buffer is empty or \b xfalse if the Rx
//! buffer is not empty.
//
//*****************************************************************************        
#define xSPIIsRxEmpty(ulBase)                                                 \
        0

//*****************************************************************************
//
//! \brief Check the empty status of the Tx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return Returns \b xtrue if the Tx buffer is empty or \b xfalse if the Tx
//! buffer is not empty.
//
//*****************************************************************************        
#define xSPIIsTxEmpty(ulBase)                                                 \
        0

//*****************************************************************************
//
//! \brief Check the full status of the Rx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return Returns \b xtrue if the Rx buffer is full or \b xfalse if the Rx
//! buffer is not full.
//
//*****************************************************************************       
#define xSPIIsRxFull(ulBase)                                                  \
        0

//*****************************************************************************
//
//! \brief Check the full status of the Tx buffer of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return Returns \b xtrue if the Tx buffer is full or \b xfalse if the Tx
//! buffer is not full.
//
//*****************************************************************************        
#define xSPIIsTxFull(ulBase)                                                  \
        0 

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
//! \b xSPI_DMA_RX, \b xSPI_DMA_TX.
//! Details please refer to \ref xSPI_DMA_CoX.
//!
//! \return None.
//
//*****************************************************************************        
#define xSPIDMAEnable(ulBase, ulDmaMode)                                      \
        SPIDMAEnable(ulBase, ulDmaMode)

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
//! \b SPI_DMA_RX, \b SPI_DMA_TX.
//! Details please refer to \ref xSPI_DMA_CoX.
//!
//! \return None.
//
//*****************************************************************************        
#define xSPIDMADisable(ulBase, ulDmaMode)                                     \
        SPIDMADisable(ulBase, ulDmaMode)

//*****************************************************************************
//
//! \brief Enable the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return None.
//
//*****************************************************************************         
#define xSPIEnable(ulBase)                                                    \
        SPIEnable(ulBase)

//*****************************************************************************
//
//! \brief Disable the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIDisable(ulBase)                                                   \
        SPIDisable(ulBase)


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
#define xSPISSSet(ulBase, ulSSMode, ulSlaveSel)                               \
        SPISSSet(ulBase, ulSlaveSel)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_Int SPI Interrupt 
//!
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned by SPIIntStatus.
//! @{
//
//*****************************************************************************

//
//! SPI RX buffer full
//
#define SPI_SPRF                0x08  

//
//! SPI mode fault
//
#define SPI_MODF                0x08  

//
//! SPI TX buffer empty
//
#define SPI_SPTEF               0x02 

//
//! SPI match interrupt
//
#define SPI_SPMF                0x18  

//
//! SPI low power interrupt
//
#define SPI_SPLPF               0x14  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_Config SPI Frame & Bitrate & Mode Config
//!
//! Values that can be passed to SPIConfigSetExpClk.
//! @{
//
//*****************************************************************************

//
//! Moto fmt, polarity 0, phase 0
//
#define SPI_FRF_MOTO_MODE_0     0x00  

//
//! Moto fmt, polarity 0, phase 1
//
#define SPI_FRF_MOTO_MODE_1     0x04  

//
//! Moto fmt, polarity 1, phase 0
//
#define SPI_FRF_MOTO_MODE_2     0x08 

//
//! Moto fmt, polarity 1, phase 1
// 
#define SPI_FRF_MOTO_MODE_3     0x0C  

//
//! SPI master
//
#define SPI_MODE_MASTER         0x10 

//
//! SPI slave
// 
#define SPI_MODE_SLAVE          0x00  

//
//! SPI MSB first
//
#define SPI_MSB_FIRST         	0x00  

//
//! SPI LSB first
//
#define SPI_LSB_FIRST         	0x01  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_DMA SPI DMa
//!
//! Values that can be passed to SPIDMAEnable() and SPIDMADisable().
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define SPI_DMA_TX              0x20  

//
//! Enable DMA for receive
//
#define SPI_DMA_RX              0x04  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_SlaveSelectOutput SPI Slave select output
//!
//! Values that can be passed to SPISSSet() and SPISSClear().
//! @{
//
//*****************************************************************************

//
//! SPI Slave select output modefault
//
#define SPI_SS_MODEFAULT        0x00 

//
//! SPI Slave select output
//
#define SPI_SS_OUTPUT	        0x02 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_ClkWaitMode SPI ClkWaitMode
//!
//! Values that can be passed to SPIClkStatusForWaitMode().
//! @{
//
//*****************************************************************************

//
//! SPI clocks continue to operate in wait mode
//
#define SPI_CLK_STOP            0x02 
									 
//
//! SPI clocks stop when the MCU enters wait mode
//									 
#define SPI_CLK_CONTINUE        0x00 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_API KLx SPI API
//! @{
//
//*****************************************************************************

extern void SPIConfigSetExpClk(unsigned long ulBase, unsigned long ulSPIClk,
                               unsigned long ulProtocol, unsigned long ulMode,
                               unsigned long ulBitRate,
                               unsigned long ulShiftDirection);
extern void SPIDataGet(unsigned long ulBase, unsigned long *pulData);
extern long SPIDataGetNonBlocking(unsigned long ulBase,
                                  unsigned long *pulData);
extern void SPIDataPut(unsigned long ulBase, unsigned long ulData);
extern long SPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData);
extern void SPIDisable(unsigned long ulBase);
extern void SPIEnable(unsigned long ulBase);
extern void SPIIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long SPIIntStatus(unsigned long ulBase, xtBoolean bMasked);
extern void SPIDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void SPIDMADisable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void SPI3WireEnable(unsigned long ulBase, unsigned long ulMode);
extern void SPI3WireDisable(unsigned long ulBase);
extern void SPISSSet(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPISSClear(unsigned long ulBase);
extern void SPIClkStatusForWaitMode(unsigned long ulBase, unsigned long ulMode);
extern unsigned long SPISingleDataReadWrite(unsigned long ulBase, 
                                            unsigned long ulWData);
extern void SPIDataRead(unsigned long ulBase, 
                        unsigned long *pulRData, 
                        unsigned long ulLen);
extern void SPIDataWrite(unsigned long ulBase, 
                         const unsigned long *pulWData, 
                         unsigned long ulLen);
extern void SPIIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback pfnCallback);

#endif
