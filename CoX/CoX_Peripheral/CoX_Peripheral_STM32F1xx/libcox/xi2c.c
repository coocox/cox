//*****************************************************************************
//
//! \file xspi.h
//! \brief Driver for Inter-IC (I2C) bus block.
//! \version V2.1.1.1
//! \date 02/08/2011
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

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xhw_i2c.h"
#include "xdebug.h"
#include "xcore.h"
#include "xi2c.h"


//*****************************************************************************
//
// An array is I2C callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnI2CHandlerCallbacks[2]={0};

//*****************************************************************************
//
//! \internal
//! \brief Generate a start condition on I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a start condition on 
//! specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C1_BASE, \b I2C2_BASE.
//!
//! \note This is only for master
//!
//! \return value of I2C status register after generate a start condition.
//
//*****************************************************************************
static unsigned long I2CStartSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C2_BASE) || (ulBase == I2C1_BASE));

    //
    // Send start
    //
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_START;
	
    return 0;
}

//*****************************************************************************
//
//! \internal
//! \brief Generate a stop condition on I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a stop condition on 
//! specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
static void I2CStopSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C2_BASE) || (ulBase == I2C1_BASE));
    
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_STOP;
}

//*****************************************************************************
//
//! \internal
//! \brief Send a byte to I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucData specifies the data which will send to I2C BUS.
//!
//! This function is to send a byte on specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note This is only for master
//!
//! \return value of I2C status register after send a byte.
//
//*****************************************************************************
static unsigned long I2CByteSend (unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C2_BASE) || (ulBase == I2C1_BASE));
            
    //
    // Send i2c address and RW bit 
    //
    xHWREG(ulBase + I2C_DR) = ucData;
        
    //
    // Return the i2c status
    //
    return 0;
}

//*****************************************************************************
//
//! \internal
//! \brief Get a byte to I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucpData specifies the data point which will save the data get from 
//! I2C BUS.
//!
//! This function is to get a byte on specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note This is only for master
//!
//! \return value of I2C status register after send a byte.
//
//*****************************************************************************
static unsigned long I2CByteGet (unsigned long ulBase, unsigned char *ucpData, 
                                 unsigned char ucAck)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C1_BASE));
    
    //
    // Make sure start bit is not active 
    //
    if (ucAck == 1)
    {
        xHWREG(ulBase + I2C_CR1) |= I2C_CR1_ACK;
    }
    else
    {
        xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
    }
    
	while (!(xHWREG(ulBase + I2C_SR1) & I2C_SR1_RXNE));
    *ucpData = (unsigned char)xHWREG(ulBase + I2C_DR);
    return (xHWREG(ulBase + I2C_SR1) | (xHWREG(ulBase + I2C_SR2) << 16));
}

//*****************************************************************************
//
//! \internal
//! \brief Checks whether the last I2Cx Event is equal to the one passed
//! as parameter.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulEvent is the specifies the event to be checked.
//!
//! This function is to checks whether the last I2Cx Event is equal to the one 
//! passed as parameter.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C1_BASE, \b I2C2_BASE.
//!
//! \return An Error Status enumeration value: 
//! xtrue :Last event is equal to the I2C_EVENT
//! xfalse :Last event is different from the I2C_EVENT
//
//*****************************************************************************
static xtBoolean 
I2CEventCheck (unsigned long ulBase, unsigned long ulEvent)
{
    unsigned long ulLastEvent;
    unsigned long ulSR1,ulSR2;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C2_BASE) || (ulBase == I2C1_BASE));
    xASSERT((ulEvent == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) || 
            (ulEvent == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) ||
            (ulEvent == I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED) ||
            (ulEvent == I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED) ||
            (ulEvent == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED) ||
            (ulEvent == I2C_EVENT_SLAVE_BYTE_RECEIVED) ||
            (ulEvent == I2C_EVENT_SLAVE_BYTE_RECEIVED) ||
            (ulEvent == I2C_EVENT_SLAVE_BYTE_TRANSMITTED) ||
            (ulEvent == I2C_EVENT_SLAVE_ACK_FAILURE) ||
            (ulEvent == I2C_EVENT_SLAVE_STOP_DETECTED) ||
            (ulEvent == I2C_EVENT_MASTER_MODE_SELECT) ||
            (ulEvent == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ||
            (ulEvent == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) ||
            (ulEvent == I2C_EVENT_MASTER_BYTE_RECEIVED) ||
            (ulEvent == I2C_EVENT_MASTER_BYTE_TRANSMITTING) ||
            (ulEvent == I2C_EVENT_MASTER_BYTE_TRANSMITTED) ||
            (ulEvent == I2C_EVENT_MASTER_MODE_ADDRESS10));

    //
    // get statues
    //
    ulSR1 = xHWREG(ulBase + I2C_SR1);
    ulSR2 = (xHWREG(ulBase + I2C_SR2) << 16);
    ulLastEvent = (ulSR1 | ulSR2) & 0x00FFFFFF;
	
    if((ulLastEvent & ulEvent) == ulEvent)
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief I2C1 interrupt handler. Clear the I2C1 interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C1 interrupt handler,it will Clear the I2C1 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are many source of this interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
I2C1EVIntHandler(void)
{
    unsigned long ulBase = I2C1_BASE;
    unsigned long ulStatus;
    unsigned long ulSR1,ulSR2;

    ulSR1 = xHWREG(ulBase + I2C_SR1);
    ulSR2 = (xHWREG(ulBase + I2C_SR2) << 16);
    ulStatus = (ulSR1 | ulSR2) & 0x00FFFFFF;
    //
    // 0
    //
    I2CFlagStatusClear(ulBase, I2C_EVENT_SMBALERT | I2C_EVENT_TIMEOUT |
                                  I2C_EVENT_PECERR | I2C_EVENT_OVR |
                                  I2C_EVENT_AF | I2C_EVENT_ARLO | 
                                  I2C_EVENT_BERR);
    
    if((ulStatus == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_RECEIVED))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_TRANSMITTING) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_TRANSMITTED))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ||
       (ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) ||
       (ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_EVENT_SLAVE_STOP_DETECTED))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
    }
}

//*****************************************************************************
//
//! \brief I2C2 interrupt handler. Clear the I2C2 interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C1 interrupt handler,it will Clear the I2C2 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are many source of this interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
I2C2EVIntHandler(void)
{
    unsigned long ulBase = I2C2_BASE;
    unsigned long ulStatus;
    unsigned long ulSR1,ulSR2;

    ulSR1 = xHWREG(ulBase + I2C_SR1);
    ulSR2 = (xHWREG(ulBase + I2C_SR2) << 16);
    ulStatus = (ulSR1 | ulSR2) & 0x00FFFFFF;
    //
    // 
    //
    I2CFlagStatusClear(ulBase, I2C_EVENT_SMBALERT | I2C_EVENT_TIMEOUT |
                                  I2C_EVENT_PECERR | I2C_EVENT_OVR |
                                  I2C_EVENT_AF | I2C_EVENT_ARLO | 
                                  I2C_EVENT_BERR);
    
    if((ulStatus == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_RECEIVED));
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_TRANSMITTED));
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ||
       (ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) ||
       (ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_EVENT_SLAVE_STOP_DETECTED));
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
    }
}

//*****************************************************************************
//
//! Initializes the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulI2CClk is the rate of the clock supplied to the I2C module.
//! \param bFast set up for fast data transfers
//! \param bDutyCycle set up the Duty Cycle for fast mode.
//!
//! This function initializes operation of the I2C Master block.  Upon
//! successful initialization of the I2C block, this function will have set the
//! bus speed for the master, and will have enabled the I2C Master block.
//!
//! If the parameter \e bFast is \b xtrue, then the master block will be set up
//! to transfer data at 400 kbps; otherwise, it will be set up to transfer data
//! at 100 kbps.
//!
//! If the parameter \e bDutyCycle is \b xtrue, then Fast mode speed calculate:
//! Tlow/Thigh = 2; otherwise, Fast mode speed calculate: Tlow/Thigh = 16/9.
//!
//! The peripheral clock will be the same as the PCLK1 clock.  This will be
//! the value returned by SysCtlAPB1ClockGet(), or it can be explicitly hard 
//! coded if it is constant and known (to save the code/execution overhead of 
//! a call to SysCtlAPB1ClockGet()).
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk,
              xtBoolean bFast, xtBoolean bDutyCycle)
{
    unsigned long ulSCLFreq;
    unsigned long ulCCR;
    unsigned long ulTRISE;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    xHWREG(ulBase + I2C_CR2) &= ~I2C_CR2_FREQ_M;
    
    xHWREG(ulBase + I2C_CR2) |= (ulI2CClk/1000000);
    ulTRISE = (ulI2CClk/1000000);

    //
    // Must disable the device before configure TRISE.
    //
    I2CDisable(ulBase);

    //
    // Get the desired SCL speed.
    //
    if(bFast == xtrue)
    {
        ulSCLFreq = 400000;
        if(bDutyCycle)
        {
            //
            // Fast mode speed calculate: Tlow/Thigh = 2
            //
            ulCCR = ulI2CClk / (ulSCLFreq * 3);
        }
        else
        {
            //
            // Fast mode speed calculate: Tlow/Thigh = 16/9
            //
            ulCCR = ulI2CClk / (ulSCLFreq * 25);
            ulCCR |= I2C_CCR_DUTY;
            
        }
        ulCCR |= I2C_CCR_F_S;
        xHWREG(ulBase + I2C_CCR) = ulCCR;
        xHWREG(ulBase + I2C_TRISE) = (((ulTRISE * 300) / 1000) + 1);
    }
    else
    {
        ulSCLFreq = 100000;

        //
        // Standard mode speed calculate
        //
        ulCCR = (ulI2CClk / (ulSCLFreq << 1));
        if (ulCCR < 4)
        {
            ulCCR =4;
        }
        xHWREG(ulBase + I2C_CCR) = ulCCR;
        xHWREG(ulBase + I2C_TRISE) = ulTRISE + 1;
    }
    I2CEnable(ulBase);
}

//*****************************************************************************
//
//! \brief Set the clock rate of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulAddrConfig specifies the slave address type.
//! \param ucSlaveAddr specifies the slave address.
//! \param ulGeneralCall specifies enable General Call function or not.
//!
//! This function is to Set 4 7-bit slave addresses and enable General Call 
//! function of specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! The \e ulAddrConfig is the I2C slave address type,There are 2 type.
//! The ulAddrConfig can be I2C_ADDR_7BIT, I2C_ADDR_10BIT.
//!
//! The \e ucSlaveAddr is the I2C slave address,There are 4 slave addrss.
//! The ucSlaveAddr can be a 7-bit value.
//!
//! The \e ulGeneralCall is to enable the General Call function or not.
//! The ulGeneralCall can be one of the following values:
//! \b I2C_GENERAL_CALL_EN,\b I2C_GENERAL_CALL_DIS.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveInit(unsigned long ulBase, unsigned long ulAddrConfig, 
             unsigned char ucSlaveAddr, unsigned long ulGeneralCall)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));

    //
    // Must enable the device before doing anything else.
    //
    I2CEnable(ulBase);

    //
    // Set up the slave address.
    //
    xHWREG(ulBase + I2C_OAR1) = ulAddrConfig | (ucSlaveAddr << 1);

    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ENGC;
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_ACK;
    xHWREG(ulBase + I2C_CR1) |= ulGeneralCall;
}

//*****************************************************************************
//
//! Enables the I2C block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will enable operation of the I2C block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Enable the master block.
    //
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_PE;
}

//*****************************************************************************
//
//! Disables the I2C block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable operation of the I2C block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Disable the master block.
    //
    xHWREG(ulBase + I2C_CR1) &= ~(I2C_CR1_PE);
}

//*****************************************************************************
//
//! Enables the I2C interrupt.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulIntType is the interrupt type of the I2C module.
//!
//! The \e ulIntType is the interrupt type of the I2C module.
//! The ulIntType can be "OR" value of \b I2C_INT_BUF, \b I2C_INT_EVT, 
//! \b I2C_INT_ERR.
//!
//! Enables the I2C interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CIntEnable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Enable the master interrupt.
    //
    xHWREG(ulBase + I2C_CR2) = ulIntType;
}

//*****************************************************************************
//
//! Disables the I2C interrupt.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulIntType is the interrupt type of the I2C module.
//!
//! The \e ulIntType is the interrupt type of the I2C module.
//! The ulIntType can be "OR" value of \b I2C_INT_BUF, \b I2C_INT_EVT, 
//! \b I2C_INT_ERR.
//!
//! Disables the I2C interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CIntDisable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Disable the master interrupt.
    //
    xHWREG(ulBase + I2C_CR2) &= ~ulIntType;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified I2C Port.
//!
//! \param ulPort is the base address of the UART port.
//! \param xtUARTCallback is callback for the specified I2C Port.
//!
//! Init interrupts callback for the specified I2C Port.
//!
//! \return None.
//
//*****************************************************************************
void
I2CIntCallbackInit(unsigned long ulBase, 
                   xtEventCallback xtI2CCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    switch(ulBase)
    {
        case I2C1_BASE:
        {
            g_pfnI2CHandlerCallbacks[0] = xtI2CCallback;
            break;
        }
        case I2C2_BASE:
        {
            g_pfnI2CHandlerCallbacks[1] = xtI2CCallback;
            break;
        }
        default:
            break;
    }
}

//*****************************************************************************
//
//! Enables the DMA of I2C block.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulDMALast is the DMA last transfer of the I2C module.
//!
//! The \e ulDMALast is the DMA last transfer.
//! The ulDMALast can be \b I2C_DMA_LAST_EN, \b I2C_DMA_LAST_DIS.
//!
//! This will enable DMA operation of the I2C block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CDMAEnable(unsigned long ulBase, unsigned long ulDMALast)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Enable the DMA of I2C block.
    //
    xHWREG(ulBase + I2C_CR2) |= I2C_CR2_DMAEN;
    xHWREG(ulBase + I2C_CR2) &= ~I2C_CR2_LAST;
    xHWREG(ulBase + I2C_CR2) |= ulDMALast;
}

//*****************************************************************************
//
//! Disables the DMA of I2C block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable DMA operation of the I2C block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CDMADisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Enable the DMA of I2C block.
    //
    xHWREG(ulBase + I2C_CR2) &= ~I2C_CR2_DMAEN;
    xHWREG(ulBase + I2C_CR2) &= ~I2C_CR2_LAST;
}

//*****************************************************************************
//
//! Configures the specified I2C own address2.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulDual is specifies enable dual address or not of the I2C module.
//! \param ucAddress is specifies the 7bit I2C own address2.
//!
//! The \e ulDual is the DMA last transfer.
//! The ulDual can be \b I2C_DUAL_ADD_EN, \b I2C_DUAL_ADD_DIS.
//!
//! This will configures the specified I2C own address2.
//!
//! \return None.
//
//*****************************************************************************
void
I2COwnAddress2Config(unsigned long ulBase, unsigned long ulDual, 
                     unsigned char ucAddress)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Configures the specified I2C own address2.
    //
    xHWREG(ulBase + I2C_OAR2) = ulDual | (ucAddress << 1);
}

//*****************************************************************************
//
//! Enables the specified I2C software reset.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will enables the specified I2C software reset.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSoftwareResetEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // This bit can be used in case the BUSY bit is set to бо1 when no stop 
    // condition has been detected on the bus.
    //
    while ((xHWREG(ulBase + I2C_SR1) & I2C_SR1_STOPF));
    while (!(xHWREG(ulBase + I2C_SR2) & I2C_SR2_BUSY));

    //
    // Enable the software reset.
    //
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_SWRST;
}

//*****************************************************************************
//
//! Disables the specified I2C software reset.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disables the specified I2C software reset.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSoftwareResetDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Enable the software reset.
    //
    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_SWRST;
}

//*****************************************************************************
//
//! Selects the specified I2C NACK position.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulNACKPosition specifies the NACK position.
//!
//! The \e ulNACKPosition can be one of the following values:
//! \b I2C_NACKPOS_NEXT, \b I2C_NACKPOS_CURRENT.
//!
//! Selects the specified I2C NACK position in master receiver mode.
//! This function is useful in I2C Master Receiver mode when the number
//! of data to be received is equal to 2. In this case, this function 
//! should be called (with parameter I2C_NACKPosition_Next) before data 
//! reception starts,as described in the 2-byte reception procedure 
//! recommended in Reference Manual in Section: Master receiver.
//!
//! \note This function configures the same bit (POS) as I2CPECPositionConfig() 
//! but is intended to be used in I2C mode while I2CPECPositionConfig() 
//! is intended to used in SMBUS mode.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CNACKPositionConfig(unsigned long ulBase, unsigned long ulNACKPosition)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_POS;
    xHWREG(ulBase + I2C_CR1) |= ulNACKPosition;
}

//*****************************************************************************
//
//! Selects the specified I2C PEC position.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulPECPosition specifies the NACK position.
//!
//! The \e ulPECPosition can be one of the following values:
//! \b I2C_PECPOS_NEXT, \b I2C_PECPOS_CURRENT.
//!
//! Selects the specified I2C PEC position in SMBUS mode.
//!
//! \note  This function configures the same bit (POS) as 
//! I2CNACKPositionConfig() but is intended to be used in SMBUS mode while
//! I2CNACKPositionConfig() is intended to used in I2C mode.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CPECPositionConfig(unsigned long ulBase, unsigned long ulPECPosition)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_POS;
    xHWREG(ulBase + I2C_CR1) |= ulPECPosition;
}

//*****************************************************************************
//
//! Selects the specified I2C PEC position.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulConfig specifies the configration of PEC.
//!
//! The \e ulConfig is the "OR" values of the following three values:
//! The PEC transfer,The PEC Position,The PEC enable
//! The PEC transfer can be \b I2C_PEC_TRANSFER_EN, \b I2C_PEC_TRANSFER_NO.
//! The PEC Position can be \b I2C_PECPOS_NEXT, \b I2C_PECPOS_CURRENT.
//! The PEC enable can be \b I2C_PEC_EN, \b I2C_PEC_DIS.
//!
//! Selects the specified I2C PEC position in SMBUS mode.
//!
//! \note  This function configures the same bit (POS) as 
//! I2CNACKPositionConfig() but is intended to be used in SMBUS mode while
//! I2CNACKPositionConfig() is intended to used in I2C mode.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CPECConfig(unsigned long ulBase, unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    xHWREG(ulBase + I2C_CR1) &= ~(I2C_CR1_POS | I2C_CR1_PEC | I2C_CR1_ENPEC);
    xHWREG(ulBase + I2C_CR1) |= ulConfig;
}

//*****************************************************************************
//
//! Gets the PEC value for the specified I2C
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This returns the PEC value for the specified I2C.
//!
//! \return The PEC value.
//
//*****************************************************************************
unsigned char
I2CPECGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    return ((xHWREG(ulBase + I2C_SR2) & I2C_SR2_PEC_M) >> 8);
}

//*****************************************************************************
//
//! Enables the specified I2C Clock stretching.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This enables the specified I2C Clock stretching.
//!
//! \note This is only use in slave mode.
//!
//! \return None.
//
//*****************************************************************************
void
I2CStretchClockEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_NOSTRETCH;
}

//*****************************************************************************
//
//! Disables the specified I2C Clock stretching.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This disables the specified I2C Clock stretching.
//!
//! \note This is only use in slave mode.
//!
//! \return None.
//
//*****************************************************************************
void
I2CStretchClockDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_NOSTRETCH;
}

//*****************************************************************************
//
//! Gets the current I2C status.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This returns the status for the I2C module. 
//!
//! \return The current status vaules.
//
//*****************************************************************************
unsigned long
I2CStatusGet(unsigned long ulBase)
{
    unsigned long ulStatus;
    unsigned long ulSR1,ulSR2;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Return the status 
    //
    ulSR1 = xHWREG(ulBase + I2C_SR1);
    ulSR2 = (xHWREG(ulBase + I2C_SR2) << 16);
    ulStatus = (ulSR1 | ulSR2) & 0x00FFFFFF;
    
    return ulStatus;
}

//*****************************************************************************
//
//! Clears the specified I2C'S flag status.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulFlag is the specifies the flag to clear.
//!
//! The ulFlag parameter can be any combination of the following values:
//! \b I2C_EVENT_SMBALERT: SMBus Alert flag
//! \b I2C_EVENT_TIMEOUT: Timeout or Tlow error flag
//! \b I2C_EVENT_PECERR: PEC error in reception flag
//! \b I2C_EVENT_OVR: Overrun/Underrun flag (Slave mode)
//! \b I2C_EVENT_AF: Acknowledge failure flag
//! \b I2C_EVENT_ARLO: Arbitration lost flag (Master mode)
//! \b I2C_EVENT_BERR: Bus error flag
//!
//! \note 
//! - STOPF (STOP detection) is cleared by software sequence: a read operation 
//!   to I2C_SR1 register followed by a write operation 
//!   to I2C_CR1 register to re-enable the I2C peripheral).
//! - ADD10 (10-bit header sent) is cleared by software sequence: a read 
//!   operation to I2C_SR1 followed by writing the 
//!   second byte of the address in DR register.
//! - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
//!   operation to I2C_SR1 register followed by a 
//!   read/write to I2C_DR register .
//! - ADDR (Address sent) is cleared by software sequence: a read operation to 
//!   I2C_SR1 register  followed by a read operation to 
//!   I2C_SR2 register .
//! - SB (Start Bit) is cleared software sequence: a read operation to I2C_SR1
//!   register followed by a write operation to I2C_DR
//!   register.
//!
//! \return None.
//
//*****************************************************************************
void
I2CFlagStatusClear(unsigned long ulBase, unsigned long ulFlag)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Clear the I2C flag status.
    //
    xHWREG(ulBase + I2C_SR1) &= ~(ulFlag);
}

//*****************************************************************************
//
//! Indicates whether or not the I2C bus is busy.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function returns an indication of whether or not the I2C bus is busy.
//! This function can be used in a multi-master environment to determine if
//! another master is currently using the bus.
//!
//! \return Returns \b xtrue if the I2C bus is busy; otherwise, returns
//! \b xfalse.
//
//*****************************************************************************
xtBoolean
I2CBusBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Return the bus busy status.
    //
    if(xHWREG(ulBase + I2C_SR2) & I2C_SR2_BUSY)
    {
        return(xtrue);
    }
    else
    {
        return(xfalse);
    }
}

//*****************************************************************************
//
//! Gets the error status of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function is used to obtain the error status of the Master module send
//! and receive operations.
//!
//! \return Returns the error status, as one of \b I2C_MASTER_ERR_NONE,
//! \b I2C_MASTER_ERR_ADDR_ACK, \b I2C_MASTER_ERR_DATA_ACK, or
//! \b I2C_MASTER_ERR_ARB_LOST.
//
//*****************************************************************************
unsigned long
I2CMasterErr(unsigned long ulBase)
{
    unsigned long ulErr;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Get the raw error state
    //
    ulErr = xHWREG(ulBase + I2C_SR1);

    //
    // Check for errors.
    //
    if(ulErr & (I2C_SR1_ARLO | I2C_SR1_AF | I2C_SR1_BERR))
    {
        return(ulErr & (I2C_SR1_ARLO | I2C_SR1_AF | I2C_SR1_BERR));
    }
    else
    {
        return(I2C_MASTER_ERR_NONE);
    }
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData data to be transmitted from the I2C Master
//!
//! This function will place the supplied data into I2C Master Data Register.
//!
//! \return None.
//
//*****************************************************************************
void
I2CDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_DR) = ucData;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//!
//! \return Returns the byte received from by the I2C Master, cast as an
//! unsigned long.
//
//*****************************************************************************
unsigned long
I2CDataGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Read a byte.
    //
    return(xHWREG(ulBase + I2C_DR));
}

//*****************************************************************************
//
//! \brief Send a master transmit request when the bus is idle.(Write Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new write transmition. When the master have not obtained
//! control of the bus, This function send request to transmit the START 
//! condition, the slave address and the data, Then it returns immediately, no 
//! waiting any bus transmition to complete. 
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, the call I2CMasterErr() to check if any error occurs. 
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterWriteRequestS2() to continue transmit data to slave.
//! Users can also call I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CMasterWriteRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                        unsigned char ucData, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));

    //
    // Waitting the I2C Control & I2C bus to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_SR2);
    }while((ulStatus & I2C_SR2_BUSY));
    
    //
    // Send start
    //    
    I2CStartSend(ulBase);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }

    //
    // Send address
    //    
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 0);
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    //
    // Send data
    //    
    I2CByteSend(ulBase, ucData);

    if(bEndTransmition)
    {
        do
        {
            ulStatus = I2CStatusGet(ulBase);  
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
                break;
        }
        while(!(ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
        I2CStopSend(ulBase);
    }
}

//*****************************************************************************
//
//! \brief Send a master data transmit request when the master have obtained 
//! control of the bus.(Write Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! I2CMasterWriteRequestS1() without any error), and haven't release it, users 
//! can call this function to continue transmit data to slave.
//!
//! This function just send request to transmit the data, and it returns 
//! immediately, no waiting any bus transmition to complete. 
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, the call I2CMasterErr() to check if any error occurs. Users call
//! also can I2CMasterStop() to terminate this transmition and release the 
//! I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterWriteRequestS2(unsigned long ulBase, unsigned char ucData,
                        xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    
    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_DR) = ucData;
    
    //
    // Send the stop if End Transmition.
    //
    if(bEndTransmition)
    {
        do
        {
            ulStatus = I2CStatusGet(ulBase);  
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
                break;
        }
        while(!(ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
        I2CStopSend(ulBase);
    }    
}

//*****************************************************************************
//
//! \brief Write a data to the slave when the bus is idle, and waiting for all 
//! bus transmiton complete.(Write Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new write transmition. When the master have not obtained
//! control of the bus, This function transmit the START condition, the slave 
//! address and the data, then waiting for all bus transmition complete.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterWriteS2() to continue transmit data to slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long 
I2CMasterWriteS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                 unsigned char ucData, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    
    //
    // Send write request
    //
    I2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, xfalse);
    
    //
    // Waiting the I2C controller to be transmited
    //
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
    
    //
    // return the error status
    //
    return (ulStatus & (I2C_SR1_ARLO | I2C_SR1_AF));
    
}

//*****************************************************************************
//
//! \brief Write a data to the slave, when the master have obtained control of 
//! the bus, and waiting for all bus transmiton complete.(Write Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! I2CMasterWriteS1() without any error), and haven't release it, users 
//! can call this function to continue transmit data to slave.
//!
//! This function transmit the data to the slave, and waiting for all bus 
//! transmition complete.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! Then users can call this function to continue transmit data to slave.
//! Users call also call I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long 
I2CMasterWriteS2(unsigned long ulBase, unsigned char ucData,
                 xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    
    //
    // Send write request
    //
    I2CMasterWriteRequestS2(ulBase, ucData, xfalse);
    
    //
    // Waiting the I2C controller to br transmited
    //
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
        
    //
    // return the error status
    //
    return (ulStatus & (I2C_SR1_ARLO | I2C_SR1_AF));    
    
}

//*****************************************************************************
//
//! \brief Write a data buffer to the slave when the bus is idle, and waiting   
//! for all bus transmiton complete.(Write Buffer Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucDataBuf is the data buffer to transmit.
//! \param ulLen is the data buffer byte size.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition.
//!
//! This function init a new data buffer write transmition. When the master have 
//! not obtained control of the bus, This function transmit the START condition,  
//! the slave address and the data, then waiting for the data transmition 
//! complete, and continue next data transmition, until all complete. If there 
//! is any error occurs, the remain data will be canceled.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully transmited. if the number != ulLen, user can call 
//! I2CMasterErr() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterWriteS2() / I2CMasterWriteBufS2() to continue transmit data 
//! to slave. Users call also call I2CMasterStop() to terminate this transmition 
//! and release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the data number that have been successully tranmited.
//
//*****************************************************************************
unsigned long
I2CMasterWriteBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                    const unsigned char *pucDataBuf, unsigned long ulLen, 
                    xtBoolean bEndTransmition)
{
    
    unsigned long ulStatus;
    unsigned long ulWritten;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    xASSERT(pucDataBuf);
    
    if(ulLen == 1)
    {
        ulStatus = I2CMasterWriteS1(ulBase, ucSlaveAddr, 
                                    pucDataBuf[0], bEndTransmition);
        
        return (ulStatus == I2C_MASTER_ERR_NONE) ? 1 : 0;
    }

    //
    // Waitting the I2C Control & I2C bus to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_SR2);
    }while((ulStatus & I2C_SR2_BUSY));

    //
    // Send start
    //    
    I2CStartSend(ulBase);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            return 0;
    }

    //
    // Send address
    //    
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 0);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            return 0;
    }

    //
    // Send data
    //    
    I2CByteSend(ulBase, pucDataBuf[0]);
    
    //
    // Check if any error occurs
    //
    if(ulStatus & (I2C_SR1_ARLO | I2C_SR1_AF | I2C_SR1_BERR))
    {
        return 0;   
    }
    
    ulWritten = 1;
    
    ulWritten += I2CMasterWriteBufS2(ulBase, 
                                     &pucDataBuf[1], 
                                     ulLen - 1, 
                                     bEndTransmition);
    
    return ulWritten;

}

//*****************************************************************************
//
//! \brief Write a data buffer to the slave, when the master have obtained  
//! control of the bus, and waiting for all bus transmiton complete.(Write
//! Buffer Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param pucDataBuf is the data buffer to transmit.
//! \param ulLen is the data buffer byte size.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition.
//!
//! After the master obtained control of the bus(have called  
//! I2CMasterWriteS1() or I2CMasterWriteBufS1() without any error), and haven't 
//! release it, users can call this function to continue transmit data to slave.
//!
//! This function transmit the data one by one to the slave, waiting for every  
//! data transmition complete, and continue next data transmition, until all  
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully transmited. if the number != ulLen, user can call 
//! I2CMasterErr() to see what error occurs.
//!
//! Then users can call I2CMasterWriteS2() or this function to continue  
//! transmit data to slave. Users call also call I2CMasterStop() to terminate  
//! this transmition and release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the data number that have been successully tranmited.
//
//*****************************************************************************
unsigned long 
I2CMasterWriteBufS2(unsigned long ulBase, const unsigned char *pucDataBuf,
                    unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(pucDataBuf);
    
    for(i = 0; i < ulLen - 1; i++)                              
    {        
        //
        // Write the first byte.
        //
        xHWREG(ulBase + I2C_DR) = pucDataBuf[i];                                     

        //
        // Waiting the I2C controller to idle
        //    
        do
        {
            ulStatus = I2CStatusGet(ulBase);  
            //
            // Check if any error occurs
            //
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
                return i;
        }
        while(!(ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
               
    }   
    
    xHWREG(ulBase + I2C_DR) = pucDataBuf[i];                        

    //
    // Waiting the I2C controller to idle
    //    
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        //
        // Check if any error occurs
        //
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            return ulLen - 1;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }    
    
    return ulLen;
    
}

//*****************************************************************************
//
//! \brief Send a master receive request when the bus is idle.(Read Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new receive transmition. When the master have not obtained
//! control of the bus, This function send request to transmit the START 
//! condition, the slave address and the data request, Then it returns  
//! immediately, no waiting any bus transmition to complete. 
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, then call I2CMasterErr() to check if any error occurs. Then user 
//! can get the data by calling I2CMasterDataGet() if there is no error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadRequestS2() to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterReadRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                       xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
        
    //
    // Waitting the I2C Control & I2C bus to idle
    //    
    //do
    //{
    //    ulStatus = xHWREG(ulBase + I2C_SR2);
    //}while((ulStatus & I2C_SR2_BUSY));
    
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_ACK;
    
    //
    // Send start
    //    
    I2CStartSend(ulBase);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }

    //
    // Send address
    //    
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
        //
        // Waiting the I2C controller to be transmited
        //
        do
        {
            ulStatus = I2CStatusGet(ulBase);  
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
                break;
        }
        while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
        I2CStopSend(ulBase);
    }
}

//*****************************************************************************
//
//! \brief Send a master data receive request when the master have obtained 
//! control of the bus.(Write Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! I2CMasterReadRequestS1() without any error), and haven't release it, users 
//! can call this function to continue receive data from slave.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, then call I2CMasterErr() to check if any error occurs. Then user 
//! can get the data by calling I2CMasterDataGet() if there is no error occurs.
//!
//! Then users can call this function to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterReadRequestS2(unsigned long ulBase, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    
    //
    // Send the stop if End Transmition.
    //
    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
        //
        // Waiting the I2C controller to be transmited
        //
        do
        {
            ulStatus = I2CStatusGet(ulBase);  
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
                break;
        }
        while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
        I2CStopSend(ulBase);
    }     
}

//*****************************************************************************
//
//! \brief Send a master data receive request with an NACK when the master have  
//! obtained control of the bus(Write Step2).
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function is used to request the last data to receive, and signal the 
//! end of the transfer to the slave transmitter. Then the master can repeat
//! START condition, switch to transmit or other slaves without lost control
//! of the bus.
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, then call I2CMasterErr() to check if any error occurs. Then user 
//! can get the data by calling I2CMasterDataGet() if there is no error occurs.
//!
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterReadLastRequestS2(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    
    //
    // RECEIVE operation with negative ACK(no stop)
    //
    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;    
    
}

//*****************************************************************************
//
//! \brief Read a data from a slave when the bus is idle, and waiting for all 
//! bus transmiton complete.(Read Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucData is the buffer where to save the data.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new receive transmition. When the master have not obtained
//! control of the bus, This function send request to transmit the START 
//! condition, the slave address and the data request, then waiting for all bus
//! transmition complete.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadS2() to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long 
I2CMasterReadS1(unsigned long ulBase, 
                unsigned char ucSlaveAddr,
                unsigned char *pucData,
                xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    xASSERT(pucData);
    
    I2CMasterReadRequestS1(ulBase, ucSlaveAddr, xfalse);

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
    } 
    
    //
    // Waiting the I2C controller to be transmited
    //
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
    
  
    //
    // Get the error code
    //
    ulStatus &= (I2C_SR1_ARLO | I2C_SR1_AF);
            
    if(!ulStatus)
    {
        *pucData = xHWREG(ulBase + I2C_DR);
    }

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }  
    
    //
    // return the error status
    //
    return ulStatus;       
      
}

//*****************************************************************************
//
//! \brief Read a data from a slave when the master have obtained control of 
//! the bus, and waiting for all bus transmiton complete.(Read Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param pucData is the buffer where to save the data.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! I2CMasterReadS1() without any error), and haven't release it, users can 
//! call this function to continue receive data from the slave.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! It will be waiting for all bus transmition complete before return.
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! Then useres can call this function to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long
I2CMasterReadS2(unsigned long ulBase,
                unsigned char *pucData,
                xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    I2CMasterReadRequestS2(ulBase, xfalse);

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
    } 
    
    //
    // Waiting the I2C controller to be transmited
    //
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
        
    //
    // Get the error code
    //
    ulStatus &= (I2C_SR1_ARLO | I2C_SR1_AF);
            
    if(!ulStatus)
    {
        *pucData = xHWREG(ulBase + I2C_DR);
    }

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    } 
    
    //
    // return the error status
    //
    return ulStatus;    
}

//*****************************************************************************
//
//! \brief Read some data from a slave when the bus is idle, and waiting for all 
//! bus transmiton complete.(Read Buffer Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucDataBuf is the buffer where to save the data.
//! \param ulLen is the data number to receive.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new data buffer receive transmition. When the master 
//! have not obtained control of the bus, This function send request to transmit 
//! the START condition, the slave address and the data request, then waiting for 
//! the data transmition complete, and continue next data transmition, until all 
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully received. if the number != ulLen, user can call 
//! I2CMasterErr() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadS2() or I2CMasterReadBufS2() to continue receive data .
//! from slave .Users call also can I2CMasterStop() to terminate this transmition
//! and release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
unsigned long 
I2CMasterReadBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                   unsigned char* pucDataBuf, unsigned long ulLen,
                   xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    unsigned long ulRead;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    xASSERT(pucDataBuf);
    
    if(ulLen == 0)
    {
        return 0;   
    }
    
    else if(ulLen == 1)
    {
        ulStatus = I2CMasterReadS1(ulBase, ucSlaveAddr, 
                                   pucDataBuf, bEndTransmition); 

        if (ulStatus == I2C_MASTER_ERR_NONE)
        {
            pucDataBuf[0] = xHWREG(ulBase + I2C_DR);
            
            return 1;
        }
        else
        {
            return 0;   
        }
    }
    
    //
    // Waitting the I2C Control & I2C bus to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_SR2);
    }while((ulStatus & I2C_SR2_BUSY));

    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_ACK;

    //
    // Send start
    //    
    I2CStartSend(ulBase);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            return 0;
    }

    //
    // Send address
    //    
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            return 0;
    }

    //
    // Waiting the I2C controller to be transmited
    //
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            break;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
    
    //
    // Check if any error occurs
    //
    if(ulStatus & (I2C_SR1_ARLO | I2C_SR1_AF | I2C_SR1_BERR))
    {
        return 0;   
    }
    
    pucDataBuf[0] = xHWREG(ulBase + I2C_DR);
    
    ulRead = 1;
    
    ulRead += I2CMasterReadBufS2(ulBase, 
                                 &pucDataBuf[1], 
                                 ulLen - 1, 
                                 bEndTransmition);    
    
    
    return ulRead;
    
}

//*****************************************************************************
//
//! \brief Read some data from a slave when the master have obtained control of
//! the bus, and waiting for all bus transmiton complete.(Write Buffer Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucDataBuf is the buffer where to save the data.
//! \param ulLen is the data number to receive.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! I2CMasterReadS1() or I2CMasterReadBufS1() without any error), and haven't 
//! release it, users can call this function to continue receive data from slave.
//!
//! This function receive data one by one from the slave, waiting for every  
//! data transmition complete, and continue next data transmition, until all  
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully received. if the number != ulLen, user can call 
//! I2CMasterErr() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadS2() or I2CMasterReadBufS2() to continue receive data
//! from slave. Users call also can I2CMasterStop() to terminate this transmition
//! and release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
unsigned long
I2CMasterReadBufS2(unsigned long ulBase, unsigned char *pucDataBuf,
                   unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(pucDataBuf);

    if(ulLen == 0) 
    {
        return 0;
    }
    

    for(i = 0; i < ulLen - 1; i++)                              
    {                           
        //
        // Waiting the I2C controller to idle
        //    
        do
        {
            ulStatus = I2CStatusGet(ulBase);  
            //
            // Check if any error occurs
            //
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
                return i;
        }
        while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
        
        pucDataBuf[i] = xHWREG(ulBase + I2C_DR);
    }  

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
    }

    //
    // Waiting the I2C controller to idle
    //    
    do
    {
        ulStatus = I2CStatusGet(ulBase);  
        //
        // Check if any error occurs
        //
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            return ulLen - 1;
    }
    while(!(ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
    
    pucDataBuf[i] = xHWREG(ulBase + I2C_DR);

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
    
    return ulLen; 
    
}

