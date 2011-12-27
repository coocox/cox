//*****************************************************************************
//
//! \file xspi.h
//! \brief Prototypes for the SPI Driver.
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
//! \addtogroup xSPI_User_Config xSPI User Config
//! @{
//
//*****************************************************************************

//
//! If the SPI Using the DMA feather and interrupt enable, please set the config
//! to 1, else 0
//
#define xSPI_CONFIG_DMA_INT     0

//*****************************************************************************
//
//! \addtogroup xSPI_User_Config_Stellaris xSPI User Config Stellaris Part
//! @{
//
//*****************************************************************************

//
//! Config the interrupt flag TXRIS mean:
//! - 1    - EOT(end of transmit), the transmit FIFO is empty, and the last bit
//!          has been transmitted out of the serializer.
//!          This will make there will be \ref xSPI_INT_EOT IN CoX SPI interrupt, 
//!          no \ref xSPI_INT_TX_FIFO.
//! - 0    - Transmit FIFO is half full or less.
//!          This will make there will be \ref xSPI_INT_TX_FIFO IN CoX SPI 
//!          interrupt, no \ref xSPI_INT_TX_FIFO.
//
#define xSPI_CONFIG_INT_TXRIS_AS_EOT                                          \
                                0
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

#if (defined(xSPI_CONFIG_INT_TXRIS_AS_EOT) && xSPI_CONFIG_INT_TXRIS_AS_EOT)
//
//! End of transfer
//
#define xSPI_INT_EOT            SSI_TXFF

#endif

#if (defined(xSPI_CONFIG_INT_TXRIS_AS_EOT) && !xSPI_CONFIG_INT_TXRIS_AS_EOT)

//
//! Transmit FIFO reduced to a level or less the level(in stellaris mcu, the
//! level is half of the FIFO), Notify users to write to the tx FIFO.
//
#define xSPI_INT_TX_FIFO        SSI_TXFF

#endif 

//
//! Receive FIFO accumulate to a level or bigger than the level(in stellaris mcu, 
//! the level is half of the FIFO), Notify users to read from the rx FIFO.
//
#define xSPI_INT_RX_FIFO        SSI_RXFF

//
//! Error
//
#define xSPI_INT_ERROR          (SSI_RXTO | SSI_RXOR)

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
//! |xSPI_EVENT_ERROR_RXTO   |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_ERROR_RXOR   |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer
//
#define xSPI_EVENT_EOT          SSI_TXFF

//
//! Transmit FIFO reduced to a level or less the level(in stellaris mcu, the
//! level is half of the FIFO), Notify users to write to the tx FIFO.
//
#define xSPI_EVENT_TXFF         SSI_TXFF

//
//! Receive FIFO accumulate to a level or bigger than the level(in stellaris mcu, 
//! the level is half of the FIFO), Notify users to read from the rx FIFO.
//
#define xSPI_EVNET_RXFF         SSI_RXFF

//
//! Receive Timeout
//
#define xSPI_EVENT_ERROR_RXTO   SSI_RXTO

//
//! Receive Overrun
//
#define xSPI_EVENT_ERROR_RXOR   SSI_RXOR

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Error xSPI Error Status
//! @{
//
//*****************************************************************************
//
//! Receive Timeout
//
#define xSPI_ERROR_RXTO         SSI_RXTO

//
//! Receive Overrun
//
#define xSPI_ERROR_RXOR         SSI_RXOR

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
//! |xSPI_TI_FORMAT_MODE     |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_NMW_FORMAT_MODE    |  Non-Mandatory |            Y           |
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
//! |xSPI_LSB_FIRST          |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |                        |                |                        |
//! |------------------------|----------------|------------------------|
//! |xSPI_DATA_WIDTHn        |  Non-Mandatory |    xSPI_DATA_WIDTH4    |
//! |                        |                |------------------------|
//! |                        |                |    xSPI_DATA_WIDTH5    |
//! |                        |                |------------------------|
//! |                        |                |    xSPI_DATA_WIDTH6    |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |    xSPI_DATA_WIDTH16   |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

// +----------+-----------------+--------------+-------------+
// | 31 - 24  |     23 - 16     |    15 - 8    |    7 - 0    |
// |---------------------------------------------------------|
// | reserved | Protocol Format | Master/Slave |  Data Width |
// +----------+-----------------+--------------+-------------+

//
//! Moto Format, polarity 0, phase 0
//
#define xSPI_MOTO_FORMAT_MODE_0 (SSI_FRF_MOTO_MODE_0 << 16)

//
//! Moto Format, polarity 0, phase 1
//  
#define xSPI_MOTO_FORMAT_MODE_1 (SSI_FRF_MOTO_MODE_1 << 16)
                                             
//
//! Moto Format, polarity 1, phase 0
//  
#define xSPI_MOTO_FORMAT_MODE_2 (SSI_FRF_MOTO_MODE_2 << 16)
                                           
//
//! Moto Format, polarity 1, phase 1
//
#define xSPI_MOTO_FORMAT_MODE_3 (SSI_FRF_MOTO_MODE_3 << 16)
                                            
//
//!  TI frame format
//                                            
#define xSPI_TI_FORMAT_MODE     (SSI_FRF_TI << 16)
  
//
//! National MicroWire frame format
//
#define xSPI_NMW_FORMAT_MODE    (SSI_FRF_NMW << 16)

#define xSPI_MODE_MASTER        (SSI_MODE_MASTER << 8)
#define xSPI_MODE_SLAVE         (SSI_MODE_SLAVE << 8)

#define xSPI_MSB_FIRST          0   

#define xSPI_DATA_WIDTH4        4 
#define xSPI_DATA_WIDTH5        5
#define xSPI_DATA_WIDTH6        6
#define xSPI_DATA_WIDTH7        7 
#define xSPI_DATA_WIDTH8        8 
#define xSPI_DATA_WIDTH9        9 
#define xSPI_DATA_WIDTH10       10 
#define xSPI_DATA_WIDTH11       11 
#define xSPI_DATA_WIDTH12       12 
#define xSPI_DATA_WIDTH13       13 
#define xSPI_DATA_WIDTH14       14 
#define xSPI_DATA_WIDTH15       15 
#define xSPI_DATA_WIDTH16       16 

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
#define xSPI_DMA_TX             SSI_DMA_TX
  
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
//! |xSPIBitLengthGet        |    Mandatory   |            Y           |
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
//! |xSPIErrorGet            |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIErrorClear          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsBusy              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsRxEmpty           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsTxEmpty           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsRxFull            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIsTxFull            |    Mandatory   |            Y           |
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
//! the SPI protocol, mode of operation, bit rate, and data width and the first
//! bit.
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
//! The width of the data transfers can be a value between 1 and 32, inclusive.
//! It can be one of the following values: \b xSPI_DATA_WIDTH4,
//! \b xSPI_DATA_WIDTH5,\b xSPI_DATA_WIDTH6,\b xSPI_DATA_WIDTH7,
//! \b xSPI_DATA_WIDTH8,\b xSPI_DATA_WIDTH9,\b xSPI_DATA_WIDTH10,
//! \b xSPI_DATA_WIDTH11,\b xSPI_DATA_WIDTH12,\b xSPI_DATA_WIDTH13,
//! \b xSPI_DATA_WIDTH11,\b xSPI_DATA_WIDTH15,\b xSPI_DATA_WIDTH16.
//! 
//! The first bit of the data transfers, can be one of the following values:
//! \b xSPI_MSB_FIRST(Stellaris MCU only support MSB only)
//! Details please refer to \ref xSPI_Config_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIConfigSet(ulBase, ulBitRate, ulConfig)                            \
        do                                                                    \
        {                                                                     \
         SSIConfigSetExpClk(ulBase,                                           \
                            xSysCtlClockGet(),                                \
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
        SSIBitLengthGet(ulBase)


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
        SSISingleDataReadWrite(ulBase, ulWData) 

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
        SSIDataRead(ulBase, pulRData, ulLen)

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
        SSIDataWrite(ulBase, pulWData, ulLen)

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
        SSIDataPut(ulBase, ulData)

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
        SSIDataPutNonBlocking(ulBase, ulData)

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
        SSIDataGet(ulBase, pulData)

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
        SSIDataGetNonBlocking(ulBase, pulData)


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
        SSIIntEnable(ulBase, ulIntFlags)

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
        SSIIntCallbackInit(ulBase, pfnCallback)

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
        SSIIntDisable(ulBase, ulIntFlags) 

//*****************************************************************************
//
//! \brief Get the SPI error status of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function returns the error status for the SPI module. usually is 
//! receive time-Out error, receive FIFo overrun error.
//!
//! \return the current SPI error status, enumerated as a bit field of:
//! - \ref xSPI_ERROR_RXTO
//! - \ref xSPI_ERROR_RXOR
//! - more refrence \ref xSPI_Error
//!
//
//*****************************************************************************        
#define xSPIErrorGet(ulBase)                                                 \
        (SSIIntStatus(ulBase, xfalse) & 0x03) 

//*****************************************************************************
//
//! \brief Clears SPI error flags.
//!
//! \param ulBase specifies the SSI module base address.
//! \param ulError is a bit mask of the error flags to be cleared. enumerated 
//! as a bit field of:
//! - \ref xSPI_ERROR_RXTO
//! - \ref xSPI_ERROR_RXOR
//! - more refrence \ref xSPI_Error
//!
//! \return None.
//
//*****************************************************************************
#define xSPIErrorClear(ulBase, ulError)                                      \
        SSIIntClear(ulBase, ulError)

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
        SSIBusy(ulBase)

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
        SSIIsRxEmpty(ulBase)  

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
        SSIIsTxEmpty(ulBase)

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
        SSIIsRxFull(ulBase)

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
        SSIIsTxFull(ulBase)   

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
        SSIDMAEnable(ulBase, ulDmaMode)

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
        SSIDMADisable(ulBase, ulDmaMode)

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
        SSIEnable(ulBase)

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
        SSIDisable(ulBase)


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
        {} 

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
//! \addtogroup Stellaris_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_SPI_Int SPI Interrupt 
//!
//! Values that can be passed to SSIIntEnable, SSIIntDisable, and SSIIntClear
//! as the ulIntFlags parameter, and returned by SSIIntStatus.
//! @{
//
//*****************************************************************************

#define SSI_TXFF                0x00000008  // TX FIFO half full or less
#define SSI_RXFF                0x00000004  // RX FIFO half full or more
#define SSI_RXTO                0x00000002  // RX timeout
#define SSI_RXOR                0x00000001  // RX overrun

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_SPI_Config SPI Frame & Bitrate & Mode Config
//!
//! Values that can be passed to SSIConfigSetExpClk.
//! @{
//
//*****************************************************************************

#define SSI_FRF_MOTO_MODE_0     0x00000000  // Moto fmt, polarity 0, phase 0
#define SSI_FRF_MOTO_MODE_1     0x00000002  // Moto fmt, polarity 0, phase 1
#define SSI_FRF_MOTO_MODE_2     0x00000001  // Moto fmt, polarity 1, phase 0
#define SSI_FRF_MOTO_MODE_3     0x00000003  // Moto fmt, polarity 1, phase 1
#define SSI_FRF_TI              0x00000010  // TI frame format
#define SSI_FRF_NMW             0x00000020  // National MicroWire frame format

#define SSI_MODE_MASTER         0x00000000  // SSI master
#define SSI_MODE_SLAVE          0x00000001  // SSI slave
#define SSI_MODE_SLAVE_OD       0x00000002  // SSI slave with output disabled

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_SPI_DMA SPI DMa
//!
//! Values that can be passed to SSIDMAEnable() and SSIDMADisable().
//! @{
//
//*****************************************************************************

#define SSI_DMA_TX              0x00000002  // Enable DMA for transmit
#define SSI_DMA_RX              0x00000001  // Enable DMA for receive

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_SPI_API Stellaris SSI API
//! @{
//
//*****************************************************************************

extern void SSIConfigSetExpClk(unsigned long ulBase, unsigned long ulSSIClk,
                               unsigned long ulProtocol, unsigned long ulMode,
                               unsigned long ulBitRate,
                               unsigned long ulDataWidth);
extern void SSIDataGet(unsigned long ulBase, unsigned long *pulData);
extern long SSIDataGetNonBlocking(unsigned long ulBase,
                                  unsigned long *pulData);
extern void SSIDataPut(unsigned long ulBase, unsigned long ulData);
extern long SSIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData);
extern void SSIDisable(unsigned long ulBase);
extern void SSIEnable(unsigned long ulBase);
extern void SSIIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void SSIIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern void SSIIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long SSIIntStatus(unsigned long ulBase, xtBoolean bMasked);
extern void SSIDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void SSIDMADisable(unsigned long ulBase, unsigned long ulDMAFlags);
extern xtBoolean SSIBusy(unsigned long ulBase);
extern xtBoolean SSIIsRxEmpty(unsigned long ulBase);
extern xtBoolean SSIIsTxEmpty(unsigned long ulBase);
extern xtBoolean SSIIsRxFull(unsigned long ulBase);
extern xtBoolean SPIIsTxFull(unsigned long ulBase);
extern unsigned char SSIBitLengthGet(unsigned long ulBase);
extern unsigned long SSISingleDataReadWrite(unsigned long ulBase, 
                                            unsigned long ulWData);
extern void SSIDataRead(unsigned long ulBase, 
                        unsigned long *pulRData, 
                        unsigned long ulLen);
extern void SSIDataWrite(unsigned long ulBase, 
                         const unsigned long *pulWData, 
                         unsigned long ulLen);
extern void SSIIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback pfnCallback);

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
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __xSPI_H__
