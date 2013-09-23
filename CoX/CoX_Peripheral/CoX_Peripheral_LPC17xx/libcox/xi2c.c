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
#include "xhw_i2c.h"
#include "xi2c.h"

//*****************************************************************************
//
// An array is I2C callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnI2CHandlerCallbacks[3] = {0};

//*****************************************************************************
//
//! \brief  I2C 0 interrupt handler.
//!         This function is the I2C interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void I2C0IntHandler(void)
{
    if(g_pfnI2CHandlerCallbacks[0] != 0)
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  I2C 1 interrupt handler.
//!         This function is the I2C interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void I2C1IntHandler(void)
{
    if(g_pfnI2CHandlerCallbacks[1] != 0)
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  I2C 2 interrupt handler.
//!         This function is the I2C interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void I2C2IntHandler(void)
{
    if(g_pfnI2CHandlerCallbacks[2] != 0)
    {
        g_pfnI2CHandlerCallbacks[2](0, 0, 0, 0);
    }
    else                               // Infinite loop
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the I2C.
//!
//! \param  [in] xtPortCallback is user callback for the I2C.
//!
//! \return None.
//
//*****************************************************************************
unsigned long I2CIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{

    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );
    // Function pointer must be a valid pointer!
    xASSERT(pfnCallback != 0);

    if(pfnCallback == 0)
    {
        while(1);
    }

    switch(ulBase)
    {
        case I2C0_BASE:
            {
                g_pfnI2CHandlerCallbacks[0] = pfnCallback;
                break;
            }
        case I2C1_BASE:
            {
                g_pfnI2CHandlerCallbacks[1] = pfnCallback;
                break;
            }
        case I2C2_BASE:
            {
                g_pfnI2CHandlerCallbacks[2] = pfnCallback;
                break;
            }
        default:                        // Error
            {
                while(1);
            }
    }

    return (0);

}

//*****************************************************************************
//
//! \brief  Initialize the I2C controller.
//!         This function initializes operation of the I2C Master block.
//!         Upon successful initialization of the I2C block, this function will
//!         have set the bus speed for the master, and will have enabled the I2C
//!         Master block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] TargetClk is the I2C clock bit rate.
//!              0 < ulI2CClk <= 400000
//!
//! \return None.
//
//*****************************************************************************
void I2CMasterInit(unsigned long ulBase, unsigned long TargetClk)
{
    unsigned long clk = 0;

    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Get PCLK of I2C controller
    if (ulBase == I2C0_BASE)
    {
        clk = SysCtlPeripheralClockGet(PCLKSEL_I2C0)/TargetClk;
    }
    else if (ulBase == I2C1_BASE)
    {
        clk = SysCtlPeripheralClockGet(PCLKSEL_I2C1)/TargetClk;
    }
    else if (ulBase == I2C2_BASE)
    {
        clk = SysCtlPeripheralClockGet(PCLKSEL_I2C2)/TargetClk;
    }

    // Set the I2C clock value to register
    xHWREG(ulBase + I2C_SCLH) = (unsigned long)(clk / 2);
    xHWREG(ulBase + I2C_SCLL) = (unsigned long)(clk - xHWREG(ulBase + I2C_SCLH));

    // Set I2C operation to default
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC | CONCLR_SIC | CONCLR_STAC | CONCLR_I2CENC;
}

//*****************************************************************************
//
//! \brief  Initialize I2C slave function.
//!         This function is to 7-bit slave addresses and enable General Call
//!         function of specified I2C port.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucSlaveAddr specifies the slave address.
//!              The ucSlaveAddr can be a 7-bit value.
//!
//! \param  [in] ulGeneralCall specifies enable General Call function or not.
//!              The ulGeneralCall can be one of the following values:
//!                  - \ref I2C_GENERAL_CALL_EN
//!                  - \ref I2C_GENERAL_CALL_DIS.
//!
//! \return None.
//!
//! \note   This function is only suit for I2C slave mode.
//
//*****************************************************************************
void I2CSlaveInit(unsigned long ulBase, unsigned long ulSlaveAddr,
                         unsigned long ulGeneralCall)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Configure I2C Address
    if(ulGeneralCall == I2C_GENERAL_CALL_EN)
    {
        ulSlaveAddr |= ADR_GC;
        xHWREG(ulBase + I2C_ADR0) = ulSlaveAddr;
    }
    else if(ulGeneralCall == I2C_GENERAL_CALL_DIS)
    {
        ulSlaveAddr &= ~ADR_GC;
        xHWREG(ulBase + I2C_ADR0) = ulSlaveAddr;
    }
    else
    {
        while(1); // Error
    }

    // Enable I2C Auto AckKnowledge
    xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC | CONCLR_STAC | CONCLR_I2CENC;
}

//*****************************************************************************
//
//! \brief  Enable I2C Module.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CEnable(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Enable I2C Module.
    xHWREG(ulBase + I2C_CONSET) = CONSET_I2CEN;
}

//*****************************************************************************
//
//! \brief  Disable I2C Module.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CDisable(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Disable I2C Module.
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_I2CENC;
}

//*****************************************************************************
//
//! \brief  Release Start signal on i2c bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CStartSend(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Reset STA, STO, SI
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC | CONCLR_STAC;

    // Enter to Master Transmitter mode
    xHWREG(ulBase + I2C_CONSET) = CONSET_STA;

    // Wait for complete
    while (!(xHWREG(ulBase + I2C_CONSET) & CONSET_SI));
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_STAC;
}

//*****************************************************************************
//
//! \brief  Release Stop signal on i2c bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CStopSend(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Make sure start bit is not active
    if(xHWREG(ulBase + I2C_CONSET) & CONSET_STA)
    {
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_STAC;
    }

    xHWREG(ulBase + I2C_CONSET) = CONSET_AA | CONSET_STO;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
}

//*****************************************************************************
//
//! \brief  Enable I2C general call function.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CGeneralCallEnable(unsigned long ulBase, unsigned long ulID)
{
    switch(ulID)
    {
        case I2C_SLAVE_ADD0:
            {
                xHWREG(ulBase + I2C_ADR0) |= ADR_GC;
                break;
            }
        case I2C_SLAVE_ADD1:
            {
                xHWREG(ulBase + I2C_ADR1) |= ADR_GC;
                break;
            }
        case I2C_SLAVE_ADD2:
            {
                xHWREG(ulBase + I2C_ADR2) |= ADR_GC;
                break;
            }
        case I2C_SLAVE_ADD3:
            {
                xHWREG(ulBase + I2C_ADR3) |= ADR_GC;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Disable I2C general call function.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CGeneralCallDisable(unsigned long ulBase, unsigned long ulID)
{
    switch(ulID)
    {
        case I2C_SLAVE_ADD0:
            {
                xHWREG(ulBase + I2C_ADR0) &= ~ADR_GC;
                break;
            }
        case I2C_SLAVE_ADD1:
            {
                xHWREG(ulBase + I2C_ADR1) &= ~ADR_GC;
                break;
            }
        case I2C_SLAVE_ADD2:
            {
                xHWREG(ulBase + I2C_ADR2) &= ~ADR_GC;
                break;
            }
        case I2C_SLAVE_ADD3:
            {
                xHWREG(ulBase + I2C_ADR3) &= ~ADR_GC;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Configure I2C slave address.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ulID is Slave addree channel
//!              This parameter can be one of the following value.
//!              - \ref I2C_SLAVE_ADD0
//!              - \ref I2C_SLAVE_ADD1
//!              - \ref I2C_SLAVE_ADD2
//!              - \ref I2C_SLAVE_ADD3
//!
//! \param  [in] ulVal is the slave address.
//!              bit7-->bit1
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CSlaveAddrSet(unsigned long ulBase, unsigned long ulID, unsigned long ulVal)
{
    unsigned long ulTmpReg = 0;

    ulVal &= (unsigned long)0xFE;

    switch(ulID)
    {
        case I2C_SLAVE_ADD0:
            {
                ulTmpReg = xHWREG(ulBase + I2C_ADR0);
                ulTmpReg &= ~ADR_ADDR_M;
                ulTmpReg |= ulVal;
                xHWREG(ulBase + I2C_ADR0)  = ulTmpReg;
                xHWREG(ulBase + I2C_MASK0) = (unsigned long)0xFE;

                break;
            }
        case I2C_SLAVE_ADD1:
            {
                ulTmpReg = xHWREG(ulBase + I2C_ADR1);
                ulTmpReg &= ~ADR_ADDR_M;
                ulTmpReg |= ulVal;
                xHWREG(ulBase + I2C_ADR1)  = ulTmpReg;
                xHWREG(ulBase + I2C_MASK1) = (unsigned long)0xFE;

                break;
            }
        case I2C_SLAVE_ADD2:
            {
                ulTmpReg = xHWREG(ulBase + I2C_ADR2);
                ulTmpReg &= ~ADR_ADDR_M;
                ulTmpReg |= ulVal;
                xHWREG(ulBase + I2C_ADR2)  = ulTmpReg;
                xHWREG(ulBase + I2C_MASK2) = (unsigned long)0xFE;
                break;
            }
        case I2C_SLAVE_ADD3:
            {
                ulTmpReg = xHWREG(ulBase + I2C_ADR3);
                ulTmpReg &= ~ADR_ADDR_M;
                ulTmpReg |= ulVal;
                xHWREG(ulBase + I2C_ADR3)  = ulTmpReg;
                xHWREG(ulBase + I2C_MASK3) = (unsigned long)0xFE;
                break;
            }
        default:
            {
                while(1);                  // Error
            }
    }
}

//*****************************************************************************
//
//! \brief  Read an byte from I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//
//*****************************************************************************
unsigned long I2CDataRead(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Read Data Register
    return xHWREG(ulBase + I2C_DAT);
}

//*****************************************************************************
//
//! \brief  Write an byte to I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ulValue is the byte ready to write.
//!
//! \return None.
//!
//
//*****************************************************************************
void I2CDataWrite(unsigned long ulBase, unsigned long ulValue)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Read Data Register
    xHWREG(ulBase + I2C_DAT) = ulValue;
}

//*****************************************************************************
//
//! \brief  Get I2C bus status.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return The status code of I2C bus, which can be one of the following value:
//!         - \ref I2C_STAT_NO_INF
//!         - \ref I2C_STAT_BUS_ERROR
//!         - \ref I2C_STAT_M_TX_START
//!         - \ref I2C_STAT_M_TX_RESTART
//!         - \ref I2C_STAT_M_TX_SLAW_ACK
//!         - \ref I2C_STAT_M_TX_SLAW_NACK
//!         - \ref I2C_STAT_M_TX_DAT_ACK
//!         - \ref I2C_STAT_M_TX_DAT_NACK
//!         - \ref I2C_STAT_M_TX_ARB_LOST
//!         - \ref I2C_STAT_M_RX_START
//!         - \ref I2C_STAT_M_RX_RESTART
//!         - \ref I2C_STAT_M_RX_ARB_LOST
//!         - \ref I2C_STAT_M_RX_SLAR_ACK
//!         - \ref I2C_STAT_M_RX_SLAR_NACK
//!         - \ref I2C_STAT_M_RX_DAT_ACK
//!         - \ref I2C_STAT_M_RX_DAT_NACK
//!         - \ref I2C_STAT_S_RX_SLAW_ACK
//!         - \ref I2C_STAT_S_RX_ARB_LOST_M_SLA
//!         - \ref I2C_STAT_S_RX_GENCALL_ACK
//!         - \ref I2C_STAT_S_RX_ARB_LOST_M_GENCALL
//!         - \ref I2C_STAT_S_RX_PRE_SLA_DAT_ACK
//!         - \ref I2C_STAT_S_RX_PRE_SLA_DAT_NACK
//!         - \ref I2C_STAT_S_RX_PRE_GENCALL_DAT_ACK
//!         - \ref I2C_STAT_S_RX_PRE_GENCALL_DAT_NACK
//!         - \ref I2C_STAT_S_RX_STA_STO_SLVREC_SLVTRX
//!         - \ref I2C_STAT_S_TX_SLAR_ACK
//!         - \ref I2C_STAT_S_TX_ARB_LOST_M_SLA
//!         - \ref I2C_STAT_S_TX_DAT_ACK
//!         - \ref I2C_STAT_S_TX_DAT_NACK
//!         - \ref I2C_STAT_S_TX_LAST_DAT_ACK
//
//*****************************************************************************
unsigned long I2CStatusGet(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(
            (ulBase == I2C0_BASE) ||
            (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE)
            );

    // Get I2C status.
    return xHWREG(ulBase + I2C_STAT);
}

//*****************************************************************************
//
//! \brief  Enable I2C Function Interrupt.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//
//*****************************************************************************
void I2CIntEnable(unsigned long ulBase)
{
    switch(ulBase)
    {
        case I2C0_BASE:
            {
                xIntEnable(xINT_I2C0);
                break;
            }
        case I2C1_BASE:
            {
                xIntEnable(xINT_I2C1);
                break;
            }
        case I2C2_BASE:
            {
                xIntEnable(xINT_I2C2);
                break;
            }
        default:                        // Error
            {
                while(1);
            }
    }

}

//*****************************************************************************
//
//! \brief  Disable I2C Function Interrupt.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//
//*****************************************************************************
void I2CIntDisable(unsigned long ulBase)
{
    switch(ulBase)
    {
        case I2C0_BASE:
            {
                xIntDisable(xINT_I2C0);
                break;
            }
        case I2C1_BASE:
            {
                xIntDisable(xINT_I2C1);
                break;
            }
        case I2C2_BASE:
            {
                xIntDisable(xINT_I2C2);
                break;
            }
        default:                        // Error
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Send a master transmit request when the bus is idle.(Write Step1)
//!
//!         This function init a new write transmition. When the master have
//!         not obtained control of the bus, This function send request to
//!         transmit the START condition, the slave address and the data, Then
//!         it returns immediately, no waiting any bus transmition to complete.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus transmition
//!         complete, the call xI2CMasterError() to check if any error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterWriteRequestS2() to continue transmit data
//!         to slave.  Users can also call xI2CMasterStop() to terminate this
//!         transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return None.
//!
//! \nore   For this function returns immediately, it is always using in the
//!         interrupt handler.
//
//*****************************************************************************
void I2CMasterWriteRequestS1(unsigned long ulBase, unsigned long ucSlaveAddr,
                              unsigned long ucData, xtBoolean bEndTransmition)
{
    unsigned long ulTmpReg = 0;

    // Send start signal
    xHWREG(ulBase + I2C_CONSET) = CONSET_STA;
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_TX_START) || (ulTmpReg == I2C_STAT_M_TX_RESTART) )
        {
            break;
        }
    }

    // Send slave address + W
    ucSlaveAddr &= ~BIT_32_0;
    xHWREG(ulBase + I2C_DAT) = ucSlaveAddr;

    // Enable Autuo Ackknowledge
    xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC | CONCLR_STAC;

    // Address+W Transfer OK ?
    while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_TX_SLAW_ACK);
    xHWREG(ulBase + I2C_DAT) = ucData;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

    // First Data Transfer OK ?
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_TX_DAT_ACK) || (ulTmpReg == I2C_STAT_M_TX_DAT_NACK) )
        {
            break;
        }
    }

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)
    {
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO | CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
}

//*****************************************************************************
//
//! \brief  Send a master data transmit request when the master have obtained
//!         control of the bus.(Write Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterWriteRequestS1() without any error), and haven't release it,
//!         users can call this function to continue transmit data to slave.
//!
//!         This function just send request to transmit the data, and it returns
//!         immediately, no waiting any bus transmition to complete.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus transmition
//!         complete, the call xI2CMasterError() to check if any error occurs.
//!         Users call also can xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return None.
//! \note   For this function returns immediately, it is always using in the interrupt
//!         handler.
//
//*****************************************************************************
void I2CMasterWriteRequestS2(unsigned long ulBase, unsigned long ucData,
        xtBoolean bEndTransmition)
{
    unsigned long ulTmpReg = 0;

    // Previous Data Transfer OK ?
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_TX_DAT_ACK) || (ulTmpReg == I2C_STAT_M_TX_DAT_NACK) )
        {
            break;
        }
    }

    // Feed New Data
    xHWREG(ulBase + I2C_DAT) = ucData;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

    // Previous Data Transfer OK ?
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_TX_DAT_ACK) || (ulTmpReg == I2C_STAT_M_TX_DAT_NACK) )
        {
            break;
        }
    }

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)
    {
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO | CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
}

//*****************************************************************************
//
//! \brief  Write a data to the slave when the bus is idle, and waiting for all
//!         bus transmiton complete.(Write Step1)
//!
//!         This function init a new write transmition. When the master have not
//!         obtained control of the bus, This function transmit the START condition,
//!         the slave address and the data, then waiting for all bus transmition
//!         complete.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterWriteS2() to continue transmit data to slave.
//!         Users call also can xI2CMasterStop() to terminate this transmition and
//!         release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the master error status.
//!
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
void I2CMasterWriteS1(unsigned long ulBase, unsigned long ulSlaveAddr,
                       unsigned long ulData, xtBoolean bEndTransmition)
{
    I2CMasterWriteRequestS1(ulBase, ulSlaveAddr, ulData, bEndTransmition);
}

//*****************************************************************************
//
//! \brief  Write a data to the slave, when the master have obtained control of
//!         the bus, and waiting for all bus transmiton complete.(Write Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterWriteS1() without any error), and haven't release it,
//!         users can call this function to continue transmit data to slave.
//!
//!         This function transmit the data to the slave, and waiting for all bus
//!         transmition complete.
//!
//!         Then users can call this function to continue transmit data to slave.
//!         Users call also call xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//!
//!
//! \return Returns the master error status.
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
void I2CMasterWriteS2(unsigned long ulBase, unsigned long ulData, xtBoolean bEndTransmition)
{
    I2CMasterWriteRequestS2(ulBase, ulData, bEndTransmition);
}

//*****************************************************************************
//
//! \brief  Write a data buffer to the slave when the bus is idle, and waiting
//!         for all bus transmiton complete.(Write Buffer Step1)
//!
//!         This function init a new data buffer write transmition. When the
//!         master have not obtained control of the bus, This function transmit
//!         the START condition, the slave address and the data, then waiting for
//!         the data transmition complete, and continue next data transmition,
//!         until all complete. If there is any error occurs, the remain data
//!         will be canceled.
//!
//!         Users can then check the return value to see how many datas have
//!         been successfully transmited. if the number != ulLen, user can call
//!         xI2CMasterError() to see what error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterWriteS2()/xI2CMasterWriteBufS2() to continue
//!         transmit data to slave. Users call also call xI2CMasterStop() to
//!         terminate this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] pucDataBuf is the data buffer to transmit.
//! \param  [in] ulLen is the data buffer byte size.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the data number that have been successully tranmited.
//!
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
void I2CMasterWriteBufS1(unsigned long ulBase, unsigned long ucSlaveAddr,
        unsigned char *pucDataBuf, unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i        = 0;
    unsigned long ulTmpReg = 0;

    // Send start signal
    xHWREG(ulBase + I2C_CONSET) = CONSET_STA;
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_TX_START) || (ulTmpReg == I2C_STAT_M_TX_RESTART) )
        {
            break;
        }
    }

    // Send slave address + W
    ucSlaveAddr &= ~BIT_32_0;
    xHWREG(ulBase + I2C_DAT) = ucSlaveAddr;

    // Enable Autuo Ackknowledge
    xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_STAC | CONCLR_SIC;

    // Address+W Transfer OK ?
    while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_TX_SLAW_ACK);

    // Transfer Data to I2C Bus
    for(i = 0; i < ulLen; i++)
    {
        xHWREG(ulBase + I2C_DAT) = pucDataBuf[i];
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // First Data Transfer OK ?
        while(1)
        {
            ulTmpReg = xHWREG(ulBase + I2C_STAT);
            // A Start/Restart signal has been transmitted.
            if( (ulTmpReg == I2C_STAT_M_TX_DAT_ACK) || (ulTmpReg == I2C_STAT_M_TX_DAT_NACK) )
            {
                break;
            }
        }
    }

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)
    {
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO | CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
}

//*****************************************************************************
//
//! \brief  Write a data buffer to the slave, when the master have obtained
//!         control of the bus, and waiting for all bus transmiton complete.
//!         (Write Buffer Step2)
//!
//!         After the master obtained control of the bus(have called xI2CMasterWriteS1()
//!         or xI2CMasterWriteBufS1() without any error), and haven't release it,
//!         users can call this function to continue transmit data to slave.
//!
//!         This function transmit the data one by one to the slave, waiting for
//!         every data transmition complete, and continue next data transmition,
//!         until all complete. If there is any error occurs, the remain data will
//!         be canceled.
//!
//!         Users can then check the return value to see how many datas have been
//!         successfully transmited. if the number != ulLen, user can call
//!         xI2CMasterError() to see what error occurs.
//!
//!         Then users can call xI2CMasterWriteS2() or this function to continue
//!         transmit data to slave. Users call also call xI2CMasterStop() to terminate
//!         this transmition and release the I2C bus.!
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] pucDataBuf is the data buffer to transmit.
//! \param  [in] ulLen is the data buffer byte size.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the data number that have been successully tranmited.
//!
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
void I2CMasterWriteBufS2(unsigned long ulBase, unsigned char *pucDataBuf,
                          unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long ulTmpReg = 0;
    unsigned long i = 0;

    // Previous Data Transfer OK ?
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_TX_DAT_ACK) || (ulTmpReg == I2C_STAT_M_TX_DAT_NACK) )
        {
            break;
        }
    }

    // Transfer Data to I2C Bus
    for(i = 0; i < ulLen; i++)
    {
        // Feed New Data
        xHWREG(ulBase + I2C_DAT) = pucDataBuf[i];
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Previous Data Transfer OK ?
        while(1)
        {
            ulTmpReg = xHWREG(ulBase + I2C_STAT);
            // A Start/Restart signal has been transmitted.
            if( (ulTmpReg == I2C_STAT_M_TX_DAT_ACK) || (ulTmpReg == I2C_STAT_M_TX_DAT_NACK) )
            {
                break;
            }
        }
    }

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)
    {
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO | CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
}

//*****************************************************************************
//
//! \brief  Send a master receive request when the bus is idle.(Read Step1)
//!
//!         This function init a new receive transmition. When the master have
//!         not obtained control of the bus, This function send request to
//!         transmit the START condition, the slave address and the data request,
//!         Then it returns immediately, no waiting any bus transmition to complete.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed by
//!         an negative ACK and STOP condition.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus transmition
//!         complete, then call xI2CMasterError() to check if any error occurs.
//!         Then user can get the data by calling xI2CMasterDataGet() if there
//!         is no error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterReadRequestS2() to continue receive data from
//!         slave.  Users call also can xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP
//!              condition and terminate this transmition.
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in the
//!         interrupt hander.
//
//*****************************************************************************
unsigned long I2CMasterReadRequestS1(unsigned long ulBase,
        unsigned long ucSlaveAddr, xtBoolean bEndTransmition)
{
    unsigned long ulTmpReg = 0;
    unsigned long ulTmp    = 0;

    // Send start signal
    xHWREG(ulBase + I2C_CONSET) = CONSET_STA;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_RX_START) || (ulTmpReg == I2C_STAT_M_RX_RESTART) )
        {
            break;
        }
    }

    // Send slave address + W
    ucSlaveAddr |= BIT_32_0;
    xHWREG(ulBase + I2C_DAT) = ucSlaveAddr;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC | CONCLR_STAC;
    while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_SLAR_ACK);

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)                                     // Yes
    {
        // Disable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        ulTmp = xHWREG(ulBase + I2C_DAT);

        // Release Stop Signal
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
    else                                                             // No
    {
        // Enable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        ulTmp = xHWREG(ulBase + I2C_DAT);
    }

    return (ulTmp);
}

//*****************************************************************************
//
//! \brief  Send a master data receive request when the master have obtained
//!         control of the bus.(Write Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterReadRequestS1() without any error), and haven't release it,
//!         users can call this function to continue receive data from slave.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed
//!         by an negative ACK and STOP condition.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus
//!         transmition complete, then call xI2CMasterError() to check if any
//!         error occurs. Then user can get the data by calling xI2CMasterDataGet()
//!         if there is no error occurs.
//!
//!         Then users can call this function to continue receive data
//!         from slave. Users call also can xI2CMasterStop() to terminate
//!         this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition and
//!              terminate this transmition.
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in the
//!         interrupt hander.
//
//*****************************************************************************
unsigned long I2CMasterReadRequestS2(unsigned long ulBase, xtBoolean bEndTransmition)
{
    unsigned long ulTmp    = 0;

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)                                     // Yes
    {
        // Disable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        ulTmp = xHWREG(ulBase + I2C_DAT);

        // Release Stop Signal
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
    else                                                             // No
    {
        // Enable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        ulTmp = xHWREG(ulBase + I2C_DAT);
    }

    return (ulTmp);
}

//*****************************************************************************
//
//! \brief  Send a master data receive request with an NACK when the master have
//!         obtained control of the bus(Write Step2).
//!
//!         This function is used to request the last data to receive, and
//!         signal the end of the transfer to the slave transmitter. Then
//!         the master can repeat START condition, switch to transmit or
//!         other slaves without lost control of the bus.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus
//!         transmition complete, then call xI2CMasterError() to check
//!         if any error occurs. Then user can get the data by calling
//!         xI2CMasterDataGet() if there is no error occurs.
//!
//!         Users call also can xI2CMasterStop() to terminate this
//!         transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in
//!         the interrupt handler.
//
//*****************************************************************************
unsigned long I2CMasterReadLastRequestS2(unsigned long ulBase)
{
    // Disable Auto Ackknowledge
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

    // Wait Receive Data
    while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
    return ( xHWREG(ulBase + I2C_DAT) );
}

//*****************************************************************************
//
//! \brief  Read a data from a slave when the bus is idle, and waiting for all
//!         bus transmiton complete.(Read Step1)
//!
//!         This function init a new receive transmition. When the master have
//!         not obtained control of the bus, This function send request to
//!         transmit the START condition, the slave address and the data
//!         request, then waiting for all bus transmition complete.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed
//!         by an negative ACK and STOP condition.
//!
//!         After the master obtained control of the bus, and haven't release
//!         it, users can call xI2CMasterReadS2() to continue receive data
//!         from slave.  Users call also can xI2CMasterStop() to terminate
//!         this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] pucData is the buffer where to save the data.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP
//!              condition and terminate this transmition.
//!
//! \return Returns the master error status.
//!
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
unsigned long I2CMasterReadS1(unsigned long ulBase,
        unsigned long ucSlaveAddr,
        unsigned char *pucData, xtBoolean bEndTransmition)
{
    *pucData = I2CMasterReadRequestS1(ulBase, ucSlaveAddr, bEndTransmition);
    return (0);
}

//*****************************************************************************
//
//! \brief  Read a data from a slave when the master have obtained control of
//!         the bus, and waiting for all bus transmiton complete.(Read Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterReadS1() without any error), and haven't release
//!         it, users can call this function to continue receive data
//!         from the slave.
//!
//!         If bEndTransmition is xtrue, the receive operation will
//!         followed by an negative ACK and STOP condition.
//!
//!         Then useres can call this function to continue receive
//!         data from slave.  Users call also can xI2CMasterStop()
//!         to terminate this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [in] pucData is the buffer where to save the data.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP
//!              condition and terminate this transmition.
//!
//!
//! \return Returns the master error status.
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
unsigned long I2CMasterReadS2(unsigned long ulBase, unsigned char *pucData,
        xtBoolean bEndTransmition)
{
    *pucData = I2CMasterReadRequestS2(ulBase, bEndTransmition);
    return (0);
}

//*****************************************************************************
//
//! \brief Read some data from a slave when the bus is idle, and waiting for all
//!        bus transmiton complete.(Read Buffer Step1)
//!
//!        This function init a new data buffer receive transmition. When the
//!        master have not obtained control of the bus, This function send request
//!        to transmit the START condition, the slave address and the data request,
//!        then waiting for the data transmition complete, and continue next data
//!        transmition, until all complete. If there is any error occurs, the remain
//!        data will be canceled.
//!
//!        If bEndTransmition is xtrue, the receive operation will followed by an
//!        negative ACK and STOP condition.
//!
//!        Users can then check the return value to see how many datas have been
//!        successfully received. if the number != ulLen, user can call
//!        xI2CMasterError() to see what error occurs.
//!
//!        After the master obtained control of the bus, and haven't release it,
//!        users can call xI2CMasterReadS2() or xI2CMasterReadBufS2() to continue
//!        receive data .  from slave .Users call also can xI2CMasterStop() to
//!        terminate this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [out] ucSlaveAddr is the 7-bit slave address.
//!
//! \param  [in]  pucDataBuf is the buffer where to save the data.
//!
//! \param  [in]  ulLen is the data number to receive.
//!
//! \param  [in]  bEndTransmition is flag to control if transmit the STOP condition
//!               and terminate this transmition. this value can be one fo the following
//!               value: \ref xtrue, \ref xflase.
//!
//! \return Returns the data number that have been successully received.
//!
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
unsigned long  I2CMasterReadBufS1(unsigned long ulBase,
        unsigned long ucSlaveAddr,
        unsigned char *pucDataBuf,
        unsigned long ulLen,
        xtBoolean bEndTransmition)
{
    unsigned long ulTmpReg = 0;
    unsigned long i        = 0;

    // Send start signal
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC;
    xHWREG(ulBase + I2C_CONSET) = CONSET_STA;
    while(1)
    {
        ulTmpReg = xHWREG(ulBase + I2C_STAT);
        // A Start/Restart signal has been transmitted.
        if( (ulTmpReg == I2C_STAT_M_RX_START) || (ulTmpReg == I2C_STAT_M_RX_RESTART) )
        {
            break;
        }
    }

    // Send slave address + W
    ucSlaveAddr |= BIT_32_0;
    xHWREG(ulBase + I2C_DAT) = ucSlaveAddr;
    xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC | CONCLR_STAC;
    while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_SLAR_ACK);

    for(i = 0; i < ulLen; i++)
    {
        // Disable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        pucDataBuf[i] = xHWREG(ulBase + I2C_DAT);
    }

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)                                     // Yes
    {
        // Disable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        pucDataBuf[i] = xHWREG(ulBase + I2C_DAT);

        // Release Stop Signal
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
    else                                                             // No
    {
        // Enable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        pucDataBuf[i] = xHWREG(ulBase + I2C_DAT);
    }

    return (ulLen);
}

//*****************************************************************************
//
//! \brief  Read some data from a slave when the master have obtained control of
//!         the bus,and waiting for all bus transmiton complete.(Write Buffer Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterReadS1() or xI2CMasterReadBufS1() without any error), and haven't
//!         release it, users can call this function to continue receive data from slave.
//!
//!         This function receive data one by one from the slave, waiting for every
//!         data transmition complete, and continue next data transmition, until all
//!         complete. If there is any error occurs, the remain data will be canceled.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed by an
//!         negative ACK and STOP condition.
//!
//!         Users can then check the return value to see how many datas have been
//!         successfully received. if the number != ulLen, user can call
//!         xI2CMasterError() to see what error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it, users
//!         can call xI2CMasterReadS2() or xI2CMasterReadBufS2() to continue receive data
//!         from slave. Users call also can xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \param  [out] pucDataBuf is the buffer where to save the data.
//!
//! \param  [in]  ulLen is the data number to receive.
//!
//! \param  [in]  bEndTransmition is flag to control if transmit the STOP condition
//!               and terminate this transmition. this value can be one fo the following
//!               value: \ref xtrue, \ref xflase.
//!
//! \return Returns the data number that have been successully received.
//!
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
unsigned long I2CMasterReadBufS2(unsigned long ulBase,
        unsigned char *pucDataBuf,
        unsigned long ulLen,
        xtBoolean bEndTransmition)
{
    unsigned long i        = 0;

    for(i = 0; i < ulLen; i++)
    {
        // Disable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        pucDataBuf[i] = xHWREG(ulBase + I2C_DAT);
    }

    // Need to Send Stop signal ?
    if(bEndTransmition == xtrue)                                     // Yes
    {
        // Disable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_AAC;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        pucDataBuf[i] = xHWREG(ulBase + I2C_DAT);

        // Release Stop Signal
        xHWREG(ulBase + I2C_CONSET) = CONSET_STO;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;
    }
    else                                                             // No
    {
        // Enable Auto Ackknowledge
        xHWREG(ulBase + I2C_CONSET) = CONSET_AA;
        xHWREG(ulBase + I2C_CONCLR) = CONCLR_SIC;

        // Wait Receive Data
        while(xHWREG(ulBase + I2C_STAT) != I2C_STAT_M_RX_DAT_ACK);
        pucDataBuf[i] = xHWREG(ulBase + I2C_DAT);
    }

    return (ulLen);
}

//*****************************************************************************
//
//! \brief  Check I2C bus busy status.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref I2C0_BASE
//!              - \ref I2C1_BASE
//!              - \ref I2C2_BASE
//!
//! \return Return the I2C bus busy status.
//!         - \ref xtrue   I2C bus is busy.
//!         - \ref xflase  I2C bus is not busy.
//!
//
//*****************************************************************************
xtBoolean I2CBusBusyStatus(unsigned long ulBase)
{
    if(xHWREG(ulBase + I2C_STAT) != I2C_STAT_NO_INF)           // I2C Bus is busy ?
    {
        return (xtrue);                                        // Yes
    }
    else
    {
        return (xfalse);                                       // No
    }
}

