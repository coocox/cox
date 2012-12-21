//*****************************************************************************
//
//! \file xspi.h
//! \brief Prototypes for the UART Driver.
//! \version V2.1.1.0
//! \date 3/6/2012
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
//! |xSPI Interrupts         |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_EOT            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_TX             |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_RX             |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_INT_ERROR          |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer (TX | RX Register Empty Interrupt)
//
#define xSPI_INT_EOT            SPI_INT_TXE
  
//
//! TX Buffer Empty Interrupt
//  
#define xSPI_INT_TX             SPI_INT_TXBE

//
//! RX Buffer Not Empty Interrupt
//  
#define xSPI_INT_RX             SPI_INT_RXBNE
  
//
//! All ERROR Interrupt
// 
#define xSPI_INT_ERROR          SPI_INT_WC | SPI_INT_RO | SPI_INT_MF |        \
                                SPI_INT_SAIEN

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
//! |xSPI Interrupts         |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_EOT          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_TX           |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_RX           |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xSPI_EVENT_ERROR        |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! End of transfer (TX | RX Register Empty Event)
//
#define xSPI_EVENT_EOT          SPI_INT_TXEIEN
  
//
//! TX Buffer Empty Event
//  
#define xSPI_EVENT_TX           SPI_INT_TXBEIEN

//
//! RX Buffer Not Empty Event
//  
#define xSPI_EVENT_RX           SPI_INT_RXBNEIEN
  
//
//! All ERROR Event
// 
#define xSPI_EVENT_ERROR        SPI_INT_WCIEN | SPI_INT_ROIEN | SPI_INT_MFIEN |\
                                SPI_INT_SAIEN

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
//! |xSPI Configs            |       CoX      |         HT32F125x      |
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
//! |                        |                |    xSPI_DATA_WIDTH16   |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Moto Format, polarity 0, phase 0
//
#define xSPI_MOTO_FORMAT_MODE_0 SPI_FORMAT_MODE_1

//
//! Moto Format, polarity 0, phase 1
//  
#define xSPI_MOTO_FORMAT_MODE_1 SPI_FORMAT_MODE_2  
                                             
//
//! Moto Format, polarity 1, phase 0
//  
#define xSPI_MOTO_FORMAT_MODE_2 SPI_FORMAT_MODE_6  
                                           
//
//! Moto Format, polarity 1, phase 1
//
#define xSPI_MOTO_FORMAT_MODE_3 SPI_FORMAT_MODE_5

#define xSPI_MODE_MASTER        SPI_MODE_MASTER  
#define xSPI_MODE_SLAVE         SPI_MODE_SLAVE  

#define xSPI_MSB_FIRST          SPI_MSB_FIRST 
#define xSPI_LSB_FIRST          SPI_LSB_FIRST  

#define xSPI_DATA_WIDTH1        SPI_DATA_WIDTH1
#define xSPI_DATA_WIDTH2        SPI_DATA_WIDTH2 
#define xSPI_DATA_WIDTH3        SPI_DATA_WIDTH3 
#define xSPI_DATA_WIDTH4        SPI_DATA_WIDTH4 
#define xSPI_DATA_WIDTH5        SPI_DATA_WIDTH5 
#define xSPI_DATA_WIDTH6        SPI_DATA_WIDTH6 
#define xSPI_DATA_WIDTH7        SPI_DATA_WIDTH7 
#define xSPI_DATA_WIDTH8        SPI_DATA_WIDTH8 
#define xSPI_DATA_WIDTH9        SPI_DATA_WIDTH9 
#define xSPI_DATA_WIDTH10       SPI_DATA_WIDTH10 
#define xSPI_DATA_WIDTH11       SPI_DATA_WIDTH11 
#define xSPI_DATA_WIDTH12       SPI_DATA_WIDTH12 
#define xSPI_DATA_WIDTH13       SPI_DATA_WIDTH13 
#define xSPI_DATA_WIDTH14       SPI_DATA_WIDTH14 
#define xSPI_DATA_WIDTH15       SPI_DATA_WIDTH15 
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
//! |xSPI DMA                |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xSPI_DMA_TX             |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |SPI_DMA_RX              |    Mandatory   |            N           |
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
#define xSPI_DMA_TX             0
  
//
//! Enable DMA for receive
//
#define xSPI_DMA_RX             0
  
//
//! Enable DMA for transfer and receive
//
#define xSPI_DMA_BOTH           0 

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
//! |xSPI Slave Select Mode  |       CoX      |         HT32F125x      |
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
//! |xSPI Slave Select       |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xSPI_SS_NONE            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xSPI_SSn                |    Mandatory   |        xSPI_SS0        |
//! |                        |                |------------------------|
//! |                        |                |        xSPI_SS1        |
//! |                        |                |------------------------|
//! |                        |                |        xSPI_SS01       |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSPI_SS_NONE            0   
#define xSPI_SS0                0  
#define xSPI_SS1                0 
#define xSPI_SS01               0

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
//! |xSPI API                |       CoX      |         HT32F125x      |
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
         SPISSConfig(ulBase, SPI_SS_ACTIVE_LOW);                              \
        }                                                                     \
        while(0)

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
//! \note if return 0 that means number of bits is 16.
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
extern void xSPIDataPut(unsigned long ulBase, unsigned long ulData);

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
//! \return the number of data that has been transfered..
//
//*****************************************************************************
extern long xSPIDataPutNonBlocking(unsigned long ulBase, unsigned long ulData);

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
extern void xSPIDataGet(unsigned long ulBase, unsigned long *pulData);

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
extern long xSPIDataGetNonBlocking(unsigned long ulBase, unsigned long *pulData);

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
#define xSPIStatusGet(ulBase, xbMasked)                                       \
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
#define xSPIDMAEnable(ulBase, ulDmaMode)

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
#define xSPIDMADisable(ulBase, ulDmaMode)

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
#define xSPIEnable(ulBase)      SPIEnable(ulBase)

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
#define xSPIDisable(ulBase)     SPIDisable(ulBase)

        
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
//! \addtogroup HT32F125x_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Ints xSPI Interrupts
//! \brief Values show that xSPI Interrupts
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntFlagClear
//! as the ulIntFlags parameter, and returned from SPIIntFlagGet.
//! @{
//
//*****************************************************************************

//
//! TX Buffer Empty Interrupt
//
#define SPI_INT_TXBE            0x00000001

//
//! TX Register Empty Interrupt
//
#define SPI_INT_TXE             0x00000002

//
//! RX Buffer Not Empty Interrupt
//
#define SPI_INT_RXBNE           0x00000004

//
//! Write Collision Interrupt
//
#define SPI_INT_WC              0x00000008

//
//! Read Overrun Interrupt
//
#define SPI_INT_RO              0x00000010

//
//! Mode Fault Interrupt
//
#define SPI_INT_MF              0x00000020

//
//! Slave Abort Interrupt
//
#define SPI_INT_SA              0x00000040

//
//! Time Out Interrupt
//
#define SPI_INT_TO              0x00000080

//
//! SPI Busy flag (only by SPIIntFlagClear and SPIIntFlagGet)
//
#define SPI_BUSY_FLAG           0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Config HT32F125x SPI Configure
//! \brief Values show that HT32F125x SPI Configure
//! Values that can be passed to SPIConfig.
//! @{
//
//*****************************************************************************

//
//! Moto Format, polarity 0, phase 0  M0
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_1       0x00000100  

//
//! Moto Format, polarity 0, phase 1  M1
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_2       0x00000200

//
//! Moto Format, polarity 1, phase 1  M4
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_5       0x00000500

//
//! Moto Format, polarity 1, phase 0  M3
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_6       0x00000600

//
//£¡ SPI master
//
#define SPI_MODE_MASTER         0x00004000  

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
#define SPI_LSB_FIRST           0x00001000  

//
//! data width 1 bit
//
#define SPI_DATA_WIDTH1         0x00000001

//
//! data width 2 bit
//
#define SPI_DATA_WIDTH2         0x00000002  

//
//! data width 3 bit
//
#define SPI_DATA_WIDTH3         0x00000003  

//
//! data width 4 bit
//
#define SPI_DATA_WIDTH4         0x00000004  

//
//! data width 5 bit
//
#define SPI_DATA_WIDTH5         0x00000005  

//
//! data width 6 bit
//
#define SPI_DATA_WIDTH6         0x00000006 

//
//! data width 7 bit
//
#define SPI_DATA_WIDTH7         0x00000007 

//
//! data width 8 bit
//
#define SPI_DATA_WIDTH8         0x00000008  

//
//! data width 9 bit
//
#define SPI_DATA_WIDTH9         0x00000009  

//
//! data width 10 bit
//
#define SPI_DATA_WIDTH10        0x0000000A  

//
//! data width 11 bit
//
#define SPI_DATA_WIDTH11        0x0000000B  

//
//! data width 12 bit
//
#define SPI_DATA_WIDTH12        0x0000000C 

//
//! data width 13 bit
//
#define SPI_DATA_WIDTH13        0x0000000D  

//
//! data width 14 bit
//
#define SPI_DATA_WIDTH14        0x0000000E  

//
//! data width 15 bit
//
#define SPI_DATA_WIDTH15        0x0000000F 

//
//! data width 16 bit
//
#define SPI_DATA_WIDTH16        0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_SlaveSel_Config HT32F125x SPI Slave Select Configure
//! \brief Values that show HT32F125x SPI Slave Select Configure Values that can
//! be passed to SPISSSet().
//! SPISSConfig().
//! @{
//
//*****************************************************************************

#define SPI_SS_HARDWARE         0x00002000
#define SPI_SS_SOFTWARE         0x00000000

//
//! SPISSx0/1 is active at low-level
//
#define SPI_SS_ACTIVE_LOW       0x00000000  

//
//! SPISSx0/1 is active at high-level
//
#define SPI_SS_ACTIVE_HIGH      0x00000800 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_SlaveSel_Output_Config HT32F125x SPI Slave Select 
//! Output Configure
//! \brief Values that can be passed to SPISSOutPutConfigure() as the ulEnable 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! Slave Select Output Enable
//
#define SPI_SS_OUTPUT_ENABLE    0x00000001

//
//! Slave Select Output Disable
//
#define SPI_SS_OUTPUT_DISABLE   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_FIFO_ENABLE HT32F125x SPI FIFO Enable
//! Values that can be passed to SPIFIFOModeSet().
//! @{
//
//*****************************************************************************

//
//! Received FIFO
//
#define SPI_FIFO_ENABLE              0x00000001

//
//! Received FIFO_FULL STATUS
//
#define SPI_FIFO_DISABLE             0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_FIFOStatus HT32F125x SPI FIFO Status
//! Values that can be passed to SPIFIFOStatusGet() and SPIFIFOClear().
//! @{
//
//*****************************************************************************

//
//! Received FIFO
//
#define SPI_FSR_RX              0x00000000

//
//! Received FIFO_FULL STATUS
//
#define SPI_FSR_TX              0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Exported_APIs  HT32F125x SPI API
//! \brief HT32F125x SPI API Reference
//! @{
//
//*****************************************************************************
extern void SPIEnable(unsigned long ulBase);
extern void SPIDisable(unsigned long ulBase);
extern void SPIConfig(unsigned long ulBase, unsigned long ulBitRate,                      
                      unsigned long ulConfig);
extern unsigned long SPISingleDataReadWrite(unsigned long ulBase, 
                                            unsigned long ulWData);
extern unsigned char SPIBitLengthGet(unsigned long ulBase);
extern void SPIDataRead(unsigned long ulBase, void *pulRData, 
                        unsigned long ulLen);
extern unsigned long SPIRxRegisterGet(unsigned long ulBase);
extern void SPIDataWrite(unsigned long ulBase, void *pulWData, 
                         unsigned long ulLen);
extern void SPITxRegisterSet(unsigned long ulBase, unsigned long ulData);
extern void SPIIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPIIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback xtSPICallback);
extern void SPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long SPIIntFlagGet(unsigned long ulBase, xtBoolean xbMasked);
extern void SPIIntFlagClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPISSSet(unsigned long ulBase);
extern void SPISSClear(unsigned long ulBase);
extern void SPISSConfig(unsigned long ulBase, unsigned long ulSSActType);
extern void SPISSOutPutConfigure(unsigned long ulBase, unsigned long ulEnable);
extern xtBoolean SPIIsBusy(unsigned long ulBase);
extern xtBoolean SPIIsRxEmpty(unsigned long ulBase);
extern xtBoolean SPIIsRxFull(unsigned long ulBase);
extern xtBoolean SPIIsTxEmpty(unsigned long ulBase);
extern xtBoolean SPIIsTxFull(unsigned long ulBase);

extern unsigned long SPIFIFOStatusGet(unsigned long ulBase, unsigned long ulSelect);
extern void SPIFIFOClear(unsigned long ulBase, unsigned long ulRxTx);
extern void SPIFIFOModeSet(unsigned long ulBase, unsigned long ulEnable);
extern void SPIFIFOLevelSet(unsigned long ulBase, unsigned long ulRxTx,
                            unsigned long ulLength);
extern void SPITimeOutValSet(unsigned long ulBase, unsigned long ulTimeOutVal);

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


