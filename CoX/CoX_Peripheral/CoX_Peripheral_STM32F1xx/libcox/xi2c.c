//*****************************************************************************
//
//! \file xspi.h
//! \brief Driver for Inter-IC (I2C) bus block.
//! \version V2.2.1.0
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
#include <stdint.h>

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_config.h"
#include "xhw_sysctl.h"
#include "xhw_i2c.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xi2c.h"
#include "xhw_dma.h"
#include "xdma.h"   

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
//! \return None.
//
//*****************************************************************************
void I2CStartSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C2_BASE) || (ulBase == I2C1_BASE));

    //
    // Send start
    //
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_START;
}

//*****************************************************************************
//
//! \brief Generate a stop condition on I2C bus.
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a stop condition on
//! specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C2_BASE, \b I2C1_BASE.
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
void
I2CStopSend (unsigned long ulBase)
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
//! \b I2C2_BASE, \b I2C1_BASE.
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
static void I2CByteSend (unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C2_BASE) || (ulBase == I2C1_BASE));

    //
    // Send i2c address and RW bit
    //
    xHWREG(ulBase + I2C_DR) = ucData;
}

//*****************************************************************************
//
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
xtBoolean
I2CEventCheck (unsigned long ulBase, unsigned long ulEvent)
{
    unsigned long ulLastEvent = 0;
    unsigned long ulSR1       = 0;
    unsigned long ulSR2       = 0;

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
    // Clear Interrupt flag
    //
    I2CFlagStatusClear(ulBase, I2C_EVENT_SMBALERT | I2C_EVENT_TIMEOUT |
                                  I2C_EVENT_PECERR | I2C_EVENT_OVR |
                                  I2C_EVENT_AF | I2C_EVENT_ARLO |
                                  I2C_EVENT_BERR);

    if((ulStatus == I2C_EVENT_SLAVE_BYTE_RECEIVED))
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
    // Clear interrupt flag
    //
    I2CFlagStatusClear(ulBase, I2C_EVENT_SMBALERT | I2C_EVENT_TIMEOUT |
                                  I2C_EVENT_PECERR | I2C_EVENT_OVR |
                                  I2C_EVENT_AF | I2C_EVENT_ARLO |
                                  I2C_EVENT_BERR);

    if((ulStatus == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_RECEIVED));
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) ||
       (ulStatus == I2C_EVENT_SLAVE_BYTE_TRANSMITTED));
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ||
       (ulStatus == I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) ||
       (ulStatus == I2C_EVENT_MASTER_BYTE_RECEIVED));
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_EVENT_SLAVE_STOP_DETECTED));
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
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
//! \b I2C2_BASE, \b I2C1_BASE.
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
    // Set the I2C mode.
    //
    //xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_SMBUS;

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
//! Enables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will enable operation of the I2C master block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Set the I2C mode.
    //
    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_SMBUS;
    //
    // Enable the master block.
    //
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_PE;
}

//*****************************************************************************
//
//! Disables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable operation of the I2C master block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Disable the master block.
    //
    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_PE;
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
    xASSERT((ulIntType & I2C_INT_ERR & I2C_INT_BUF & I2C_INT_EVT));

    //
    // Enable the master interrupt.
    //
    xHWREG(ulBase + I2C_CR2) |= ulIntType;
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
    xASSERT((ulIntType & I2C_INT_ERR & I2C_INT_BUF & I2C_INT_EVT));

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
    unsigned long ultmpreg = 0;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //
    // Enable the DMA of I2C block.
    //
    ultmpreg =   xHWREG(ulBase + I2C_CR2);
    ultmpreg |=  I2C_CR2_DMAEN;
    ultmpreg &= ~I2C_CR2_LAST;
    ultmpreg |=  ulDMALast;
    xHWREG(ulBase + I2C_CR2) = ultmpreg;
}

//*****************************************************************************
//
//! Disables the DMA of I2C block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable DMA operation of the I2C block.
//! at the same time, this function disable DMA_LAST bit
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
    xHWREG(ulBase + I2C_CR2) &= ~(I2C_CR2_DMAEN | I2C_CR2_LAST);
}

//*****************************************************************************
//
//! Configures the specified I2C own address2.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulDual is specifies enable dual address or not of the I2C module.
//! \param ucAddress is specifies the 7bit I2C own address2.
//!
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
    // This bit can be used in case the BUSY bit is set to 1 when no stop
    // condition has been detected on the bus.
    //
    //while ((xHWREG(ulBase + I2C_SR1) & I2C_SR1_STOPF));
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
    xASSERT((ulNACKPosition == I2C_NACKPOS_NEXT) ||
            (ulNACKPosition == I2C_NACKPOS_CURRENT));

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
    xASSERT((ulBase == I2C_PECPOS_NEXT) || (ulBase == I2C_PECPOS_CURRENT));

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

    //Modify By Cedar 2013-5-29
    //When Unset NOSTRETCH, I2C Stretch function is ENABLED
    //Literal meaning is confused
    //xHWREG(ulBase + I2C_CR1) |= I2C_CR1_NOSTRETCH;
    xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_NOSTRETCH;

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

    //Modify By Cedar 2013-5-29
    //When Set NOSTRETCH, I2C Stretch function is DISABLED
    //Literal meaning is confused
    //xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_NOSTRETCH;
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_NOSTRETCH;
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

    //Should wait for TXE = 1

    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_DR) = ucData;
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Master(Blocking).
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData data to be transmitted from the I2C Master
//!
//! This function will place the supplied data into I2C Master Data Register.
//! First wait for TxE, then send the data
//!
//! \return None.
//
//*****************************************************************************
void
I2CDataPutBlocking(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //Should wait for TXE = 1
    while((xHWREG(ulBase + I2C_SR1) & I2C_SR1_TXE) == 0);

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
//! Receives a byte that has been sent to the I2C Master(Blocking).
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//! function will wait for RxNE
//!
//! \return Returns the byte received from by the I2C Master, cast as an
//! unsigned long.
//
//*****************************************************************************
unsigned long
I2CDataGetBlocking(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));

    //Should wait for RxNE = 1
    while((xHWREG(ulBase + I2C_SR1) & I2C_SR1_RXNE) == 0);

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

    //Enable ACK function
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_ACK;

    //
    // Send start
    //
    I2CStartSend(ulBase);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT))
    {
        //Error occurs
        //if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        //    break;
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        {
            return;
        }
    }

    //
    // Send address
    //
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        //Error occurs
        //if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        //    break;
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        {
            return;
        }
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
            //Error occurs
            //if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            //    break;
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            {
                return;
            }
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
        //xHWREG(ulBase + I2C_CR1) &= ~I2C_CR1_ACK;
        //
        // Waiting the I2C controller to be transmited
        //
        do
        {
            ulStatus = I2CStatusGet(ulBase);
            //Error occurs
            //if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            //    break;
            if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
            {
                return;
            }
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
//! When the master have not obtained control of the bus, you can use this function
//! to receice a data from I2C slave, then this function will realse the I2C bus.
//! Note: 
//! 1: this function is only for I2C master.
//! 2: Parameter bEndTransmition is exist only for complatible.
//! 3: Function I2CMasterReadS1 and I2CMasterReadBufS1 is suit for the number-fixed
//!    situation.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
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

    //Here, we don't use parameter bEndTransmition
    //So we add (void) to avoid compiler warning
    (void) bEndTransmition;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(pucData);

    //
    // Send start
    //
    I2CStartSend(ulBase);
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT))
    {
        //Error occurs
        //if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        //    break;
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        {
            goto Error;
        }
    }

    //Clear SB Flag and send i2C slave address
    (void) xHWREG(ulBase + I2C_SR1);
    //Receive Mode, Set LSB    
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1);

    //wait for ADDR
    while((xHWREG(ulBase + I2C_SR1) & I2C_SR1_ADDR) == 0);

    //Disable ACK
    xHWREG(ulBase + I2C_CR1) &= ~(unsigned long) I2C_CR1_ACK;

    //Enter Cirtical section
    xIntMasterDisable();

    //Read SR2 to clear ADDR Flag
    (void) xHWREG(ulBase + I2C_SR2);

    //Program Stop bit
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_STOP;

    //Exit Cirtical section
    xIntMasterEnable();

    //Wait for RxNE bit
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
        //Error occurs
        //if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        //    break;
        if(xHWREG(ulBase + I2C_SR1) & 0x0F00)
        {
            goto Error;
        }
    }

    *pucData = xHWREG(ulBase + I2C_DR);

    //Enable ACK again
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_ACK;

    // Error part
    // Returns the error status, as one of I2C_MASTER_ERR_NONE,
    // I2C_MASTER_ERR_ADDR_ACK, I2C_MASTER_ERR_DATA_ACK or I2C_MASTER_ERR_ARB_LOST.
Error:
    return I2CMasterErr(ulBase);

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
//! note: This function is no need more in STM32 Cox lib
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long
I2CMasterReadS2(unsigned long ulBase,
                unsigned char *pucData,
                xtBoolean bEndTransmition)
{
    //Read input parameters but don't use them, only to avoid compiler warning
    (void) ulBase;
    (void) pucData;
    (void) bEndTransmition;
#if 0
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
#endif
    return (I2C_MASTER_ERR_NONE);
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
//! Note: This function is used to receive block of data from I2C slave, the release
//!       I2C bus.
//!       the parameter ulLen MUST be <= 65535
//
//! Users can then check the return value to see how many datas have been
//! successfully received. if the number != ulLen, user can call
//! I2CMasterErr() to see what error occurs.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
unsigned long
I2CMasterReadBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                   unsigned char* pucDataBuf, unsigned long ulLen,
                   xtBoolean bEndTransmition)
{
    unsigned long ulStatus = 0;    
    unsigned long ulDMACh  = 0;
    unsigned long ulDMACCR = 0;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    //xASSERT(!(ucSlaveAddr & 0x80));
    xASSERT(pucDataBuf);

    //Avoid Compiler warning
    (void) bEndTransmition;

    //previous code reserved
    //Comment by cedar
#if 0
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
#endif

    //New Code
    if(ulLen == 0 || ulLen > 65535)   //Error
    {
        return (0);
    }
    else if(ulLen == 1)
    {
        ulStatus = I2CMasterReadS1(ulBase, ucSlaveAddr,
                                   pucDataBuf, bEndTransmition);
        if (ulStatus == I2C_MASTER_ERR_NONE)
        {
            return (1);
        }
        else
        {
            return (0);
        }
    }

    /*------------------------ N >= 2 and N < 65535 -----------------------------*/

    //Configure DMA I2C Rx channel
    if(ulBase == I2C1_BASE)       // I2C1 --> DMA Rx Channel 7
    {
        ulDMACh  = DMA1_CHANNEL_7;
        ulDMACCR = DMA_CCR7;
    }
    else if(ulBase == I2C2_BASE)  // I2C1 --> DMA Rx Channel 5
    {
        ulDMACh  = DMA1_CHANNEL_5;
        ulDMACCR = DMA_CCR5;
    }
    else                          //Error, Return immediatly
    {
        return (0);
    }

    /*--------------------------------DMA Configure-------------------------------*/
    //Enable DMA1 Peripheral Clock
    //SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);

    //Configure DMA primity
    DMAChannelAttributeSet(ulDMACh, DMA_ATTR_PRIORITY_VHIGH);
    //Configure DMA Peripheral/Source Address
    DMAChannelTransferSet(ulDMACh, (void *)(ulBase + I2C_DR), pucDataBuf, ulLen);
    // MSIZE --> 8-bit
    // PSIZE --> 8-bit
    // MINC  --> Memory address increment mode
    // PINC  --> Peripheral address fixed mode
    // CIRC  --> Circular mode disabled     
    DMAChannelControlSet(ulDMACh, DMA_MEM_WIDTH_8BIT | DMA_PER_WIDTH_8BIT |
            DMA_MEM_DIR_INC | DMA_PER_DIR_FIXED | DMA_MODE_CIRC_DIS);

    //Configure DMA Direct: Read from peripheral
    xHWREG(DMA1_BASE + ulDMACCR) &= ~DMA_CCRx_DIR;

    //Enable DMA Channel
    DMAEnable(ulDMACh);

    /*------------------------------I2C Operate------------------------------------*/

    //Enable LastByte Operate
    xHWREG(ulBase + I2C_CR2) |= I2C_CR2_LAST;

    // Send start
    I2CStartSend(ulBase);
    //Clear SB Flag
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send I2C2 slave Address for write */    
    I2CByteSend(ulBase, (ucSlaveAddr << 1) | 0x01);    
    /* Test on I2C1 EV6 and clear it */
    while(!I2CEventCheck(ulBase, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    //Enable I2C DMA
    xHWREG(ulBase + I2C_CR2) |= I2C_CR2_DMAEN;

    //while((xHWREG(DMA1_BASE + DMA_ISR) & DMA_ISR_TCIF7) == 0);
    while(DMAChannelIntFlagGet(ulDMACh, DMA_INT_TC) == xfalse);

    //Clear DMA TC/HT/TE Flag and Reset DMA Configure to default value
    DMAChannelIntFlagClear(ulDMACh, DMA_INT_TG);
    I2CDMADisable(ulBase);
    DMADisable(ulDMACh);    

    //Send I2C Stop Signal    
    I2CStopSend(ulBase);
    
    return (0);

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
//! Note: this function is no avaible in STM32 Cox lib now
//!       Please use I2CMasterReadBufS1/I2CMasterReadS1  to read block of data
//!       from I2C Slave. when Number of data N >= 2, call I2CMasterReadBufS1,
//!       when N = 1, call I2CMasterReadS1 instead.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
unsigned long
I2CMasterReadBufS2(unsigned long ulBase, unsigned char *pucDataBuf,
                   unsigned long ulLen, xtBoolean bEndTransmition)
{

    //Here, we read input parameters simply, just to avoid compiler warning
    (void) ulBase;
    (void) pucDataBuf;
    (void) ulLen;
    (void) bEndTransmition;

    //Comment by cedar
#if 0  //Comment Begin
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
#endif   //End of Comment

    return (0);
}


//*****************************************************************************
//
//! \brief Initialize I2C Module
//! \param ulBase is the base address of the I2C Master module.
//! \param ulClk is the I2C Clock.
//!
//! \return None.
//
//*****************************************************************************
void I2CInit(unsigned long ulBase, unsigned long ulClk)
{
    unsigned long ultmpreg = 0;
    unsigned long ulAPBClk = 0;
    unsigned long result   = 0;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C1_BASE) || (ulBase == I2C2_BASE));
    xASSERT(ulClk <= 400000UL);

    /*-----------------Configure I2C Peripheral Frequency-------------*/
    ultmpreg = xHWREG(ulBase + I2C_CR2);
    ultmpreg &= ~(unsigned long)I2C_CR2_FREQ_M;
    ulAPBClk = SysCtlAPB1ClockGet()/1000000;
    //Peripheral input clock frequency is limit to 2~36 MHz
    if(ulAPBClk < 2 || ulAPBClk > 36)
    {
        //Error
        while(1);
    }
    ultmpreg |= ulAPBClk;
    xHWREG(ulBase + I2C_CR2) = ultmpreg;

    xHWREG(ulBase + I2C_OAR1) = 0x00004030;
    
    /*------------------Configure CCR register(Timing)---------------*/
    //Disable I2C module before configure CCR/TRISE register
    xHWREG(ulBase + I2C_CR1) &= ~(unsigned long)I2C_CR1_PE;
    //Reset CCR register to 0x0000
    ultmpreg = 0;

    ulAPBClk *= 1000000;
    //I2C clock < 100K, configure I2C into standard mode.
    if(ulClk <= 100000)
    {
        //Standard mode speed calculate
        result = ulAPBClk / (ulClk << 1);
        if(result < 0x04)
        {
            result = 0x04;
        }

        ultmpreg |= result;
        //Set maximum rise time for standard mode.
        xHWREG(ulBase + I2C_TRISE) = ulAPBClk/1000000 + 1;

    }
    else //I2C clock < 400K, configure I2C into fast mode.
    {
        //Here, we configure fast mode: Tlow/Thigh = 16:9
        //if this default configure is not suit for you
        //you can adjust by yourself

        //Tlow:Thigh = 2:1
        //result = ulAPBClk / (ulClk * 25);

        //Tlow:Thigh = 16:9
        result = ulAPBClk / (ulClk * 25);
        result |= I2C_CCR_DUTY;

        //CCR must >= 0x01
        if((result & I2C_CCR_CCR_M) == 0)
        {
            result |= 0x0001;
        }

        //Enable Fast mode
        ultmpreg |= I2C_CCR_F_S;

        //Set speed value
        ultmpreg |= result;

        //Set maximum rise time for fast mode
        ulAPBClk /= 1000000;
        xHWREG(ulBase + I2C_TRISE) = (ulAPBClk * 300)/1000 + 1;
    }

    //Write back to CCR register
    xHWREG(ulBase + I2C_CCR) = ultmpreg;

    //Enable I2C peripheral
    xHWREG(ulBase + I2C_CR1) |= I2C_CR1_PE;

    /*----------------Configure CR1 register---------------------*/
    //Here, we configure I2C parameter as below:
    //1:ACK Enable
    //2:I2C Mode
    //3:PE Enable
    //others keep reserved
    ultmpreg = (I2C_CR1_ACK | I2C_CR1_PE);
    xHWREG(ulBase + I2C_CR1) = ultmpreg;

}

