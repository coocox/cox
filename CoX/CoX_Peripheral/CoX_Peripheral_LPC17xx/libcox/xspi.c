#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_spi.h"
#include "xspi.h"

//*****************************************************************************
//
// An array is Watchdog callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnSPIHandlerCallbacks = 0;

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
    if(g_pfnSPIHandlerCallbacks != 0)
    {
        g_pfnSPIHandlerCallbacks(0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the SPI.
//!
//! \param  [in] xtPortCallback is user callback for the SPI.
//!
//! \return None.
//
//*****************************************************************************
unsigned long SPIIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    // Avoid Compiler warning
    (void) ulBase;

    // Check the parameters.
    xASSERT(pfnCallback != 0);

    g_pfnSPIHandlerCallbacks = pfnCallback;

    return (0);
}

//*****************************************************************************
//
//! \brief  Check SPI status.
//!         This function check whether the spi status flag has been set.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \param  [in] ulFlags is the SPI status flag, this value can be OR of the
//!              following value:
//!              - \ref SPI_ABRT Slave abort
//!              - \ref SPI_MODF Mode Fault
//!              - \ref SPI_ROVR Read overrun
//!              - \ref SPI_WCOL write collision
//!              - \ref SPI_SPIF SPI transfer finish
//!
//! \return The status of checked flag.
//!         - \ref xtrue status flag has been set.
//!         - \ref xflase status flag has not been set.
//!
//
//*****************************************************************************
xtBoolean SPIStatCheck(unsigned long ulBase, unsigned long ulFlags)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT( (ulCfg & ~(
                           SPI_ABRT |
                           SPI_MODF |
                           SPI_ROVR |
                           SPI_WCOL |
                           SPI_SPIF
                        )
              ) == 0);

    // Check Status Bit.
    if(xHWREG(ulBase + S0SPSR) & ulFlags)        // Set
    {
        return (xtrue);
    }
    else                                         // Unset
    {
        return (xfalse);
    }
}

//*****************************************************************************
//
//! \brief  Get SPI bus status.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \return The status of SPI, which is the OR of the following value:
//!              - \ref SPI_ABRT Slave abort
//!              - \ref SPI_MODF Mode Fault
//!              - \ref SPI_ROVR Read overrun
//!              - \ref SPI_WCOL write collision
//!              - \ref SPI_SPIF SPI transfer finish
//!
//
//*****************************************************************************
unsigned long SPIStatGet(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    return xHWREG(ulBase + S0SPSR);
}

//*****************************************************************************
//
//! \brief  Clear SPI status flag.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \param  [in] ulFlags is the flag ready to be clear.
//!              can be one of the following value:
//!              - \ref SPI_ABRT    Slave abort
//!              - \ref SPI_MODF    Mode fault
//!              - \ref SPI_ROVR    Read overrun
//
//*****************************************************************************
void SPIStatFlagClear(unsigned long ulBase, unsigned long ulFlags)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT( (ulCfg & ~(
                           SPI_ABRT |
                           SPI_MODF |
                           SPI_ROVR
                        )
              ) == 0);

    // Check Status Bit.
    (void) xHWREG(ulBase + S0SPSR);

    // Clear WCOL Write collision by reading SPI status register(S0SPSR),
    // then accessing the SPI control register(S0SPCR).
    if(ulFlags & SPI_MODF)
    {
        unsigned long ulTmpReg = 0;

        ulTmpReg = xHWREG(ulBase + S0SPCR);
        xHWREG(ulBase + S0SPCR) = ulTmpReg;
    }
}


//*****************************************************************************
//
//! \brief  SPI single write read data.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \param  [in] ulVal is the data ready to send via spi bus.
//!
//! \return The receive data from spi slave.
//
//*****************************************************************************
unsigned long SPIDataReadWrite(unsigned long ulBase, unsigned long ulVal)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    while(0 == (xHWREG(ulBase + S0SPSR) & S0SPSR_SPIF));
    xHWREG(ulBase + S0SPDR) = ulVal & S0SPDR_DATA_M;
    return xHWREG(ulBase + S0SPDR);
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
//! \param  [in] ulCfgs is SPI configure parameters.
//!              which can be OR of the following value:
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
//!              - \ref SPI_CPHA_FIRST
//!              - \ref SPI_CPHA_SECOND
//!              - \ref SPI_CPOL_HIGH
//!              - \ref SPI_CPOL_LOW
//!              - \ref SPI_LSB_FIRST
//!              - \ref SPI_MSB_FIRST
//!
//! \return None.
//
//*****************************************************************************
void SPICfg(unsigned long ulBase, unsigned long ulClk, unsigned long ulCfgs)
{
    unsigned long ulTmpReg = 0;
    unsigned long ulActClk = 0;

    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT( (ulCfg & ~(
                            SPI_DATA_LEN_8  |
                            SPI_DATA_LEN_9  |
                            SPI_DATA_LEN_10 |
                            SPI_DATA_LEN_11 |
                            SPI_DATA_LEN_12 |
                            SPI_DATA_LEN_13 |
                            SPI_DATA_LEN_14 |
                            SPI_DATA_LEN_15 |
                            SPI_DATA_LEN_16 |
                            SPI_MODE_MASTER |
                            SPI_MODE_SLAVE  |
                            SPI_CPHA_FIRST  |
                            SPI_CPHA_SECOND |
                            SPI_CPOL_HIGH   |
                            SPI_CPOL_LOW    |
                            SPI_LSB_FIRST   |
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
    ulTmpReg = xHWREG(ulBase + S0SPCR);
    ulTmpReg &= ((~ulCfgs) >> 16);
    ulTmpReg |= (ulCfgs & 0xFFFF);
    xHWREG(ulBase + S0SPCR) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief  Enable SPI interrupt.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \return None.
//
//*****************************************************************************
void SPIIntEnable(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    // Avoid Compiler warning.
    (void) ulBase;

    xHWREG(ulBase + S0SPCR) |= S0SPCR_SPIE;
}

//*****************************************************************************
//
//! \brief  Disable SPI interrupt.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \return None.
//
//*****************************************************************************
void SPIIntDisable(unsigned long ulBase)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    // Avoid Compiler warning.
    (void) ulBase;

    xHWREG(ulBase + S0SPCR) &= ~S0SPCR_SPIE;
}

//*****************************************************************************
//
//! \brief  Get SPI Interrupt flag.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \return The interrupt status of SPI, this value can be
//!         - \ref SPI_INT_SPIF SPI event has been occurs.
//!         0.
//
//*****************************************************************************
unsigned long SPIIntFlagGet(unsigned long ulBase)
{
    // Avoid Compiler warning.
    (void) ulBase;

    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    return xHWREG(ulBase + S0SPINT);
}

//*****************************************************************************
//
//! \brief  Check ADC status flag.
//!         This function is used to check whether special flag is set or not.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
//!
//! \param  [in] ulFlags is the flag you want to check
//!         This value is the one of the following value:
//!              - \ref SPI_INT_SPIF
//!
//! \return The status of special flag.
//!         - xtrue The check flag has been set.
//!         - xflase The check flag has not been set.
//
//*****************************************************************************
xtBoolean SPIIntFlagCheck(unsigned long ulBase, unsigned long ulFlags)
{
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT(ulFlags == SPI_INT_SPIF);

    if(xHWREG(ulBase + S0SPINT) & ulFlags) // Interrupt has occures.
    {
        return (xtrue);
    }
    else                                   // Interrupt has not occures.
    {
        return (xfalse);
    }
}

//*****************************************************************************
//
//! \brief  Clear SPI interrupt status flag.
//!         This function can be used to clear special SPI interrupt status flag.
//!
//! \param  [in] ulBase specifies the SPI module base address. which can be one
//!              of the following value:
//!              - \ref SPI0_BASE
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
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT(ulFlags == SPI_INT_SPIF);

    // Clear interrupt flag.
    xHWREG(ulBase + S0SPINT) |= S0SPINT_SPIF;
}

//*****************************************************************************
//
//! \brief  Gets the number of bits transferred per frame.
//!         This function gets the number of bits transferred per frame.
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!
//! \return The number of bits transferred per frame.
//!         For LPC17xx, this value can be 8/9/../16.
//
//*****************************************************************************
unsigned long xSPIBitLengthGet(unsigned long ulBase)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    ulTmpReg = xHWREG(ulBase + S0SPCR);

    if(ulTmpReg & S0SPCR_BIT_EN)      // 8-16 bit
    {
        if(ulTmpReg & S0SPCR_BITS_M)  // 8-15 bit
        {
            return ((ulTmpReg &  S0SPCR_BITS_M) >> S0SPCR_BITS_S);
        }
        else                          // 16-bit
        {
            return (16);
        }
    }
    else                              // Fixed 8-bit
    {
        return (8);
    }
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
void xSPIDataRead(unsigned long ulBase,
                         unsigned long *pulRData, unsigned long ulLen)
{
    unsigned long i = 0;

    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT(pulData != 0);

    for(i = 0; i < ulLen; i++)
    {
        *pulRData++ = SPIDataReadWrite(ulBase, 0x00);
    }
}

//*****************************************************************************
//
//! \brief  Write datas element to the SPI interface.
//!         This function transmitted data to the interface of the specified
//!         SPI module .
//!
//! \param  [in] ulBase specifies the SPI module base address. This value can
//!              be one of the following value:
//!              - \ref xSPI0_BASE
//!
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

    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT(pulData != 0);

    for(i = 0; i < ulLen; i++)
    {
        SPIDataReadWrite(ulBase, *pulWData++);
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
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    // Wait last transmit done then write data to SPI data register.
    while(0 == (xHWREG(ulBase + S0SPSR) & S0SPSR_SPIF));
    xHWREG(ulBase + S0SPDR) = ulData & S0SPDR_DATA_M;
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
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);

    // Write Data to SPI Data register.
    xHWREG(ulBase + S0SPDR) = ulData & S0SPDR_DATA_M;
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
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT(pulData != 0);

    // Wait until receive one byte, then read data from SPI Data register.
    while(0 == (xHWREG(ulBase + S0SPSR) & S0SPSR_SPIF));
    *pulData = xHWREG(ulBase + S0SPDR) & S0SPDR_DATA_M;
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
    // Check the parameters.
    xASSERT(ulBase == SPI0_BASE);
    xASSERT(pulData != 0);

    // Read data from SPI Data register.
    *pulData = xHWREG(ulBase + S0SPDR) & S0SPDR_DATA_M;
}

