//*****************************************************************************
//
//! \file xspi.h
//! \brief Prototypes for the UART Driver.
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
//! \brief Values that show xSPI interrupts
//! \n
//! \section xSPI_Ints_Section 1. Where to use this group
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned from SPIIntStatus. 
//! \n
//! \section xSPI_Ints_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Interrupts         |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_EOT            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_TX             |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_RX             |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_ERROR          |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer
//
#define xSPI_INT_EOT            SPI_INT_EOT

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Ints_Event xSPI Interrupt Event
//! \brief Values that show xSPI interrupt events.
//! \n
//! \section xSPI_Ints_Event_Section 1. Where to use this group
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned from SPIIntStatus. 
//! \n
//! \section xSPI_Ints_Event_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Interrupts         |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_EOT          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_TX           |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_RX           |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_ERROR        |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer
//
#define xSPI_EVENT_EOT          SPI_INT_EOT

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Config xSPI Configure
//! \brief Values that show xSPI Configure
//! \n
//! \section xSPI_Config_Section 1. Where to use this group
//! Values that can be passed to xSPIConfig()
//! as the ulConfig parameter. 
//! \n
//! \section xSPI_Config_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Configs            |       CoX      |         STM32F1xx      |
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
//! |xSPI_DATA_WIDTHn        |  Non-Mandatory |    xSPI_DATA_WIDTH1    |
//! |                        |                |------------------------|
//! |                        |                |    xSPI_DATA_WIDTH2    |
//! |                        |                |------------------------|
//! |                        |                |    xSPI_DATA_WIDTH3    |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |    xSPI_DATA_WIDTH32   |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Moto Format, polarity 0, phase 0
//
#define xSPI_MOTO_FORMAT_MODE_0 SPI_FORMAT_MODE_0

//
//! Moto Format, polarity 0, phase 1
//  
#define xSPI_MOTO_FORMAT_MODE_1 SPI_FORMAT_MODE_1
                                             
//
//! Moto Format, polarity 1, phase 0
//  
#define xSPI_MOTO_FORMAT_MODE_2 SPI_FORMAT_MODE_2
                                           
//
//! Moto Format, polarity 1, phase 1
//
#define xSPI_MOTO_FORMAT_MODE_3 SPI_FORMAT_MODE_3
                                            
//
//!  TI frame format
//                                            
#define xSPI_TI_FORMAT_MODE     0
  
//
//! National MicroWire frame format
//
#define xSPI_NMW_FORMAT_MODE    0

#define xSPI_MODE_MASTER        SPI_MODE_MASTER  
#define xSPI_MODE_SLAVE         SPI_MODE_SLAVE  

#define xSPI_MSB_FIRST          SPI_MSB_FIRST 
#define xSPI_LSB_FIRST          SPI_LSB_FIRST  

#define xSPI_DATA_WIDTH1        SPI_DATA_WIDTH8
#define xSPI_DATA_WIDTH2        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH3        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH4        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH5        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH6        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH7        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH8        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH9        SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH10       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH11       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH12       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH13       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH14       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH15       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH16       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH17       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH18       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH19       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH20       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH21       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH22       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH23       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH24       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH25       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH26       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH27       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH28       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH29       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH30       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH31       SPI_DATA_WIDTH16 
#define xSPI_DATA_WIDTH32       SPI_DATA_WIDTH16 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_DMA xSPI DMA
//! \brief Values that show xSPI DMA
//! \n
//! \section xSPI_DMA_Section 1. Where to use this group
//! Values that can be passed to xSPIDMAEnable() and xSPIDMADisable()
//! as the ulDmaMode parameter. 
//! \n
//! \section xSPI_DMA_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI DMA                |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xSPI_DMA_TX             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |SPI_DMA_RX              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |SPI_DMA_BOTH            |  Non-Mandatory |            Y           |
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
  
//
//! Enable DMA for transfer and receive
//
#define xSPI_DMA_BOTH           SPI_DMA_BOTH  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_SlaveSelMode xSPI Slave Select Mode
//! \brief Values show xSPI Slave Select Mode
//! \n
//! \section xSPI_SlaveSelMode_Section 1. Where to use this group
//! Values that can be passed to xSPISSSet()
//! as the ulSSMode parameter. 
//! \n
//! \section xSPI_SlaveSelMode_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xSPI Slave Select Mode  |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_HARDWARE        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_SOFTWARE        |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSPI_SS_HARDWARE        SPI_SS_HARDWARE  
#define xSPI_SS_SOFTWARE        SPI_SS_SOFTWARE  

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
//! |xSPI Slave Select       |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_NONE            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_SSn                |    Mandatory   |        xSPI_SS0        |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSPI_SS_NONE            SPI_SS_NONE   
#define xSPI_SS0                SPI_SS0  
//#define xSPI_SS1                SPI_SS1 
//#define xSPI_SS01               SPI_SS0_SS1

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
//! |xSPI API                |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xSPIConfigSet           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPISingleDataReadWrite |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIBitLengthGet        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataRead            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataWrite           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataPut             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataPutNonBlocking  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataGet             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIDataGetNonBlocking  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIntEnable           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIntCallbackInit     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIIntDisable          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPIStatusGet           |    Mandatory   |            Y           |
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
//! It can be one of the following values: \b xSPI_DATA_WIDTH1,
//! \b xSPI_DATA_WIDTH2,\b xSPI_DATA_WIDTH3,\b xSPI_DATA_WIDTH4,
//! \b xSPI_DATA_WIDTH5,\b xSPI_DATA_WIDTH6,\b xSPI_DATA_WIDTH7,
//! \b xSPI_DATA_WIDTH8,\b xSPI_DATA_WIDTH9,\b xSPI_DATA_WIDTH10,
//! \b xSPI_DATA_WIDTH11,\b xSPI_DATA_WIDTH12,\b xSPI_DATA_WIDTH13,
//! \b xSPI_DATA_WIDTH11,\b xSPI_DATA_WIDTH15,\b xSPI_DATA_WIDTH16,
//! \b xSPI_DATA_WIDTH17,\b xSPI_DATA_WIDTH18,\b xSPI_DATA_WIDTH19,
//! \b xSPI_DATA_WIDTH20,\b xSPI_DATA_WIDTH21,\b xSPI_DATA_WIDTH22,
//! \b xSPI_DATA_WIDTH23,\b xSPI_DATA_WIDTH24,\b xSPI_DATA_WIDTH25,
//! \b xSPI_DATA_WIDTH26,\b xSPI_DATA_WIDTH27,\b xSPI_DATA_WIDTH28,
//! \b xSPI_DATA_WIDTH29,\b xSPI_DATA_WIDTH30,\b xSPI_DATA_WIDTH31,
//! \b xSPI_DATA_WIDTH32,
//! 
//! The first bit of the data transfers, can be one of the following values:
//! \b xSPI_MSB_FIRST, or \b xSPI_LSB_FIRST.
//! Details please refer to \ref xSPI_Config_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIConfigSet(ulBase, ulBitRate, ulConfig)                            \
        do                                                                    \
        {                                                                     \
         SPIConfig(ulBase, ulBitRate, ulConfig);                              \
        }                                                                     \
        while(0)

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
#define xSPIBitLengthGet(ulBase)                                              \
        SPIBitLengthGet(ulBase)

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
//! SPIConfig().  For example, if the interface is configured for
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
//! SPIConfig(). For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIDataPut(ulBase, ulData)                                           \
        SPIDataPut(ulBase, ulData)

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
//! SPIConfig(). For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the number of data that has been transfered..
//
//*****************************************************************************
#define xSPIDataPutNonBlocking(ulBase, ulData)                                \
        SPIDataPutNonBlocking(ulBase, ulData)

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
//! SPIConfig(). For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIDataGet(ulBase, pulData)                                          \
         SPIDataGet(ulBase, pulData)

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
//! SPIConfig(). For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to \e pulData
//! contain valid data.
//!
//! \return the number of data that has been received.
//
//*****************************************************************************
#define xSPIDataGetNonBlocking(ulBase, pulData)	                              \
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
//! \param xtI2CCallback is callback for the specified SPI Port.
//!
//! Init interrupts callback for the specified SPI Port.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIIntCallbackInit(ulBase, xtSPICallback)                            \
        SPIIntCallbackInit(ulBase, xtSPICallback)

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
//! \brief Get the SPI interrupt flag of the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//! \param xbMasked is \b false if the raw interrupt status is required or
//! \b true if the masked interrupt status is required.
//!
//! This function returns the interrupt status for the SPI module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned. 
//!
//! \return the SPI interrupt flag.It can be the following values:
//! \b .
//
//*****************************************************************************        
#define xSPIStatusGet(ulBase, xbMasked)                                      \
        SPIIntFlagGet(ulBase, xbMasked) 

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
        SPIIsBusy(ulBase)

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
#define xSPIIsRxEmpty(ulBase)                                                 \
        SPIIsRxEmpty(ulBase)  

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
#define xSPIIsTxEmpty(ulBase)                                                 \
        SPIIsTxEmpty(ulBase)

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
#define xSPIIsRxFull(ulBase)                                                  \
        SPIIsRxFull(ulBase)

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
#define xSPIIsTxFull(ulBase)                                                  \
        SPIIsTxFull(ulBase)   

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
//! \b SPI_DMA_RX, \b SPI_DMA_TX ,or \b SPI_DMA_BOTH.
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
//! This function enable the specified SPI port.
//!
//! \note do nothing for STM32F1xx.
//!
//! \return None.
//
//*****************************************************************************
#define xSPIEnable(ulBase)                                                    \
        SPIEnble(ulBase)
  
//*****************************************************************************
//
//! \brief Disable the specified SPI port.
//!
//! \param ulBase specifies the SPI module base address.
//!
//! This function disable the specified SPI port.
//!
//! \note do nothing for STM32F1xx.
//!
//! \return None.
//
//***************************************************************************
#define xSPIDisable(ulBase)                                                 \
        SPIDisble(ulBase)

        
extern void xSPISSSet(unsigned long ulBase, unsigned long ulSSMode, 
                      unsigned long ulSlaveSel);

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
//! \addtogroup STM32F1xx_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_Ints STM32F1xx SPI Interrupts
//! \brief Values show that xSPI Interrupts
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned from SPIIntStatus.
//! @{
//
//*****************************************************************************

//
//! All Error Interrupt Mask
//
#define SPI_INT_EOT             0x00000000
#define SPI_INT_RX              0x00000040
#define SPI_INT_TX              0x00000080
#define SPI_INT_ERRE            0x00000020
 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Config STM32F1xx SPI Configure
//! \brief Values show that STM32F1xx SPI Configure
//! Values that can be passed to SPIConfig.
//! @{
//
//***************************************************************************** 

//
//! Moto Format, polarity 0, phase 0  M0
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_0       0x00000000  

//
//! Moto Format, polarity 0, phase 1  M1
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_1       0x00000001  

//
//! Moto Format, polarity 1, phase 1  M4
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_3       0x00000003

//
//! Moto Format, polarity 1, phase 0  M3
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_2       0x00000002

//
//£¡ SPI master
//
#define SPI_MODE_MASTER         0x00000004  

//
//! SPI slave
//
#define SPI_MODE_SLAVE          0x00000000

//
//! SPI MSB First
//
#define SPI_MSB_FIRST           0x00000000  

//
//! SPI LSB First
//
#define SPI_LSB_FIRST           0x00000080  

//
//! data width 8 bit
//
#define SPI_DATA_WIDTH8         0x00000000   

//
//! data width 16 bit
//
#define SPI_DATA_WIDTH16        0x00000800  

//
//! 2-line unidirectional data Full duplex (Transmit and receive)
//
#define SPI_2LINE_FULL          0x00000000 

//
//! 2-line unidirectional data Receive-only mode
//
#define SPI_2LINE_RX            0x00000400 

//
//! 1-line bidirectional data receive-only mode
//
#define SPI_1LINE_RX            0x00008000 

//
//! 1-line bidirectional data transmit-only mode
//
#define SPI_1LINE_TX            0x0000C000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_DMA STM32F1xx SPI DMA
//! \brief Values that show STM32F1xx SPI DMA
//! Values that can be passed to SPIDMAEnable() and SPIDMADisable().
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define SPI_DMA_TX              0x00000002

//
//! Enable DMA for receive
//
#define SPI_DMA_RX              0x00000001  

//
//! Enable DMA for receive and transmit
//
#define SPI_DMA_BOTH            0x00000003  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_SlaveSel_Config STM32F1xx SPI Slave Select Configure
//! \brief Values that show STM32F1xx SPI Slave Select Configure
//! Values that can be passed to SPISSIConfig(), SPISSModeConfig(), 
//! SPISSOutputConfig().
//! @{
//
//*****************************************************************************

#define SPI_SS_HARDWARE         0x00000000
#define SPI_SS_SOFTWARE         0x00000200 

//
//! SPISSx0
//
#define SPI_SS_NONE             0x00000000
#define SPI_SS0                 0x00000100 
#define SPI_SSSET               0x00000100
#define SPI_SSRESET             0x00000000
 
//
//! SS output enable
//
#define SPI_SSOE_ENABLE         0x00000004
#define SPI_SSOE_DISABLE        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_FIFOStatus STM32F1xx SPI FIFO Status
//! \brief Values that show STM32F1xx SPI FIFO Status
//! Values that can be passed to SPIFIFOStatusGet().
//! @{
//
//*****************************************************************************

//
//! Received FIFO_NOT_EMPTY STATUS
//
#define SPI_RX_NOT_EMPTY        0x00000001  

//
//! Transmitted FIFO_EMPTY STATUS
//
#define SPI_TX_EMPTY            0x00000002    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Error_flag STM32F1xx SPI Error flag
//! \brief Values that show STM32F1xx SPI Error flag
//! Values that can be passed to SPIErrorFlagGet().
//! @{
//
//*****************************************************************************

//
//! Overrun flag.
//
#define SPI_ERR_OVERRUN         0x00000040

//
//! Mode fault.
//
#define SPI_ERR_MODEFAULT       0x00000020

//
//! CRC error flag.
//
#define SPI_ERR_CRCE            0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Exported_APIs  STM32F1xx SPI API
//! \brief STM32F1xx SPI API Reference
//! @{
//
//*****************************************************************************

extern void SPIConfig(unsigned long ulBase, unsigned long ulBitRate,
                      unsigned long ulConfig);
extern unsigned long SPISingleDataReadWrite(unsigned long ulBase, 
                                            unsigned long ulWData);

extern void SPIDataRead(unsigned long ulBase, void *pulRData, 
                        unsigned long ulLen);
extern void SPIDataWrite(unsigned long ulBase, void *pulWData, 
                         unsigned long ulLen);
extern void SPIDataPut(unsigned long ulBase, unsigned long ulData);
extern long SPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData);
extern void SPIDataGet(unsigned long ulBase, unsigned long *pulData);
extern long SSIDataGetNonBlocking(unsigned long ulBase, unsigned long *pulData);
extern void SPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPIIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback xtSPICallback);
extern void SPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long SPIIntFlagGet(unsigned long ulBase);
extern void SPIIntFlagClear(unsigned long ulBase);

extern xtBoolean SPIIsBusy(unsigned long ulBase);
extern void SPIDMAEnable(unsigned long ulBase, unsigned long ulDmaMode);
extern void SPIDMADisable(unsigned long ulBase, unsigned long ulDmaMode);
extern void SPIEnble(unsigned long ulBase);
extern void SPIDisble(unsigned long ulBase);
extern void SPISSModeConfig(unsigned long ulBase, unsigned long ulSSValue);
extern void SPISSIConfig(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPISSOutputConfig(unsigned long ulBase, unsigned long ulSSOutPut);
extern xtBoolean SPIIsTxEmpty(unsigned long ulBase);
extern xtBoolean SPIIsRxNotEmpty(unsigned long ulBase);
extern void SPICRCPolSet(unsigned long ulBase, unsigned long ulCRCPol);
extern unsigned long SPICRCPolGet(unsigned long ulBase);
extern unsigned long SPIRxCRCGet(unsigned long ulBase);
extern unsigned long SPITXCRCGet(unsigned long ulBase);
extern void SPICRCEnble(unsigned long ulBase);
extern void SPICRCDisble(unsigned long ulBase);


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

