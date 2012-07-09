//*****************************************************************************
//
//! \file xspi.h
//! \brief Driver for Inter-IC (I2C) bus block.
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
//! Initializes the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulI2CClk is the rate of the clock supplied to the I2C module.
//! \param bFast set up for fast data transfers
//!
//! This function initializes operation of the I2C Master block.  Upon
//! successful initialization of the I2C block, this function will have set the
//! bus speed for the master, and will have enabled the I2C Master block.
//!
//! If the parameter \e bFast is \b xtrue, then the master block will be set up
//! to transfer data at 400 kbps; otherwise, it will be set up to transfer data
//! at 100 kbps.
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original I2CMasterInit() API and performs the
//! same actions.  A macro is provided in <tt>i2c.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterInitExpClk(unsigned long ulBase, unsigned long ulI2CClk,
                    xtBoolean bFast)
{
    unsigned long ulSCLFreq;
    unsigned long ulTPR;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Must enable the device before doing anything else.
    //
    I2CMasterEnable(ulBase);

    //
    // Get the desired SCL speed.
    //
    if(bFast == xtrue)
    {
        ulSCLFreq = 400000;
    }
    else
    {
        ulSCLFreq = 100000;
    }

    //
    // Compute the clock divider that achieves the fastest speed less than or
    // equal to the desired speed.  The numerator is biased to favor a larger
    // clock divider so that the resulting clock is always less than or equal
    // to the desired clock, never greater.
    //
    ulTPR = ((ulI2CClk + (2 * 10 * ulSCLFreq) - 1) / (2 * 10 * ulSCLFreq)) - 1;
    xHWREG(ulBase + I2C_MTPR) = ulTPR;
}

//*****************************************************************************
//
//! Initializes the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ucSlaveAddr 7-bit slave address
//!
//! This function initializes operation of the I2C Slave block.  Upon
//! successful initialization of the I2C blocks, this function will have set
//! the slave address and have enabled the I2C Slave block.
//!
//! The parameter \e ucSlaveAddr is the value that will be compared against the
//! slave address sent by an I2C master.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveInit(unsigned long ulBase, unsigned char ucSlaveAddr)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));

    //
    // Must enable the device before doing anything else.
    //
    I2CSlaveEnable(ulBase);

    //
    // Set up the slave address.
    //
    xHWREG(ulBase + I2C_SOAR) = ucSlaveAddr;
}

//*****************************************************************************
//
//! Enables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This will enable operation of the I2C Master block.
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Enable the master block.
    //
    xHWREG(ulBase + I2C_MCR) |= I2C_MCR_MFE;
}

//*****************************************************************************
//
//! Enables the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This will enable operation of the I2C Slave block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Enable the clock to the slave block.
    //
    xHWREG(ulBase - I2C0_SLAVE_BASE + I2C0_MASTER_BASE + I2C_MCR) |=
        I2C_MCR_SFE;

    //
    // Enable the slave.
    //
    xHWREG(ulBase + I2C_SCSR) = I2C_SCSR_DA;
}

//*****************************************************************************
//
//! Disables the I2C master block.
//!
//! \param ulBase is the base address of the I2C Master module.
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Disable the master block.
    //
    xHWREG(ulBase + I2C_MCR) &= ~(I2C_MCR_MFE);
}

//*****************************************************************************
//
//! Disables the I2C slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This will disable operation of the I2C slave block.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Disable the slave.
    //
    xHWREG(ulBase + I2C_SCSR) = 0;

    //
    // Disable the clock to the slave block.
    //
    xHWREG(ulBase - I2C0_SLAVE_BASE + I2C0_MASTER_BASE + I2C_MCR) &=
        ~(I2C_MCR_SFE);
}

//*****************************************************************************
//
//! Enables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! Enables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Enable the master interrupt.
    //
    xHWREG(ulBase + I2C_MIMR) = 1;
}

//*****************************************************************************
//
//! Enables the I2C Slave interrupt.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! Enables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Enable the slave interrupt.
    //
    xHWREG(ulBase + I2C_SIMR) |= I2C_SLAVE_INT_DATA;
}

//*****************************************************************************
//
//! Enables individual I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated I2C Slave interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b I2C_SLAVE_INT_STOP - Stop condition detected interrupt
//! - \b I2C_SLAVE_INT_START - Start condition detected interrupt
//! - \b I2C_SLAVE_INT_DATA - Data interrupt
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntEnableEx(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Enable the slave interrupt.
    //
    xHWREG(ulBase + I2C_SIMR) |= ulIntFlags;
}

//*****************************************************************************
//
//! Disables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! Disables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Disable the master interrupt.
    //
    xHWREG(ulBase + I2C_MIMR) = 0;
}

//*****************************************************************************
//
//! Disables the I2C Slave interrupt.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! Disables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Disable the slave interrupt.
    //
    xHWREG(ulBase + I2C_SIMR) &= ~I2C_SLAVE_INT_DATA;
}

//*****************************************************************************
//
//! Disables individual I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated I2C Slave interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to I2CSlaveIntEnableEx().
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntDisableEx(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Disable the slave interrupt.
    //
    xHWREG(ulBase + I2C_SIMR) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! Gets the current I2C Master interrupt status.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param bMasked is xfalse if the raw interrupt status is requested and
//! xtrue if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Master module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, returned as \b xtrue if active
//! or \b xfalse if not active.
//
//*****************************************************************************
xtBoolean
I2CMasterIntStatus(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return((xHWREG(ulBase + I2C_MMIS)) ? xtrue : xfalse);
    }
    else
    {
        return((xHWREG(ulBase + I2C_MRIS)) ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! Gets the current I2C Slave interrupt status.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param bMasked is xfalse if the raw interrupt status is requested and
//! xtrue if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Slave module.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return The current interrupt status, returned as \b xtrue if active
//! or \b xfalse if not active.
//
//*****************************************************************************
xtBoolean
I2CSlaveIntStatus(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return((xHWREG(ulBase + I2C_SMIS)) ? xtrue : xfalse);
    }
    else
    {
        return((xHWREG(ulBase + I2C_SRIS)) ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! Gets the current I2C Slave interrupt status.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param bMasked is xfalse if the raw interrupt status is requested and
//! xtrue if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Slave module.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in I2CSlaveIntEnableEx().
//
//*****************************************************************************
unsigned long
I2CSlaveIntStatusEx(unsigned long ulBase, xtBoolean bMasked)
{
    unsigned long ulValue;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        //
        // Workaround for I2C slave masked interrupt status register errata
        // (7.1) for Dustdevil Rev A0 devices.
        //
        if(CLASS_IS_DUSTDEVIL && REVISION_IS_A0)
        {
            ulValue = xHWREG(ulBase + I2C_SRIS);
            return(ulValue & xHWREG(ulBase + I2C_SIMR));
        }
        else
        {
            return(xHWREG(ulBase + I2C_SMIS));
        }
    }
    else
    {
        return(xHWREG(ulBase + I2C_SRIS));
    }
}

//*****************************************************************************
//
//! Clears I2C Master interrupt sources.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! The I2C Master interrupt source is cleared, so that it no longer asserts.
//! This must be done in the interrupt handler to keep it from being called
//! again immediately upon exit.
//!
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterIntClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Clear the I2C master interrupt source.
    //
    xHWREG(ulBase + I2C_MICR) = I2C_MICR_IC;

    //
    // Workaround for I2C master interrupt clear errata for rev B Stellaris
    // devices.  For later devices, this write is ignored and therefore
    // harmless (other than the slight performance hit).
    //
    xHWREG(ulBase + I2C_MMIS) = I2C_MICR_IC;
}

//*****************************************************************************
//
//! Clears I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! The I2C Slave interrupt source is cleared, so that it no longer asserts.
//! This must be done in the interrupt handler to keep it from being called
//! again immediately upon exit.
//!
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Clear the I2C slave interrupt source.
    //
    xHWREG(ulBase + I2C_SICR) = I2C_SICR_DATAIC;
}

//*****************************************************************************
//
//! Clears I2C Slave interrupt sources.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified I2C Slave interrupt sources are cleared, so that they no
//! longer assert.  This must be done in the interrupt handler to keep it from
//! being called again immediately upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to I2CSlaveIntEnableEx().
//!
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveIntClearEx(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Clear the I2C slave interrupt source.
    //
    xHWREG(ulBase + I2C_SICR) = ulIntFlags;
}

//*****************************************************************************
//
//! Sets the address that the I2C Master will place on the bus.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr 7-bit slave address
//! \param bReceive flag indicating the type of communication with the slave
//!
//! This function will set the address that the I2C Master will place on the
//! bus when initiating a transaction.  When the \e bReceive parameter is set
//! to \b xtrue, the address will indicate that the I2C Master is initiating a
//! read from the slave; otherwise the address will indicate that the I2C
//! Master is initiating a write to the slave.
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterSlaveAddrSet(unsigned long ulBase, unsigned char ucSlaveAddr,
                      xtBoolean bReceive)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));

    //
    // Set the address of the slave with which the master will communicate.
    //
    xHWREG(ulBase + I2C_MSA) = (ucSlaveAddr << 1) | bReceive;
}

//*****************************************************************************
//
//! Indicates whether or not the I2C Master is busy.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function returns an indication of whether or not the I2C Master is
//! busy transmitting or receiving data.
//!
//! \return Returns \b xtrue if the I2C Master is busy; otherwise, returns
//! \b xfalse.
//
//*****************************************************************************
xtBoolean
I2CMasterBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Return the busy status.
    //
    if(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY)
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
I2CMasterBusBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Return the bus busy status.
    //
    if(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSBSY)
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
//! Controls the state of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulCmd command to be issued to the I2C Master module
//!
//! This function is used to control the state of the Master module send and
//! receive operations.  The \e ucCmd parameter can be one of the following
//! values:
//!
//! - \b I2C_MASTER_CMD_SINGLE_SEND
//! - \b I2C_MASTER_CMD_SINGLE_RECEIVE
//! - \b I2C_MASTER_CMD_BURST_SEND_START
//! - \b I2C_MASTER_CMD_BURST_SEND_CONT
//! - \b I2C_MASTER_CMD_BURST_SEND_FINISH
//! - \b I2C_MASTER_CMD_BURST_SEND_ERROR_STOP
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_START
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_CONT
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_FINISH
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP
//!
//! \return None.
//
//*****************************************************************************
void
I2CMasterControl(unsigned long ulBase, unsigned long ulCmd)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT((ulCmd == I2C_MASTER_CMD_SINGLE_SEND) ||
           (ulCmd == I2C_MASTER_CMD_SINGLE_RECEIVE) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_START) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_CONT) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_FINISH) ||
           (ulCmd == I2C_MASTER_CMD_BURST_SEND_ERROR_STOP) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_START) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_CONT) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_FINISH) ||
           (ulCmd == I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP));

    //
    // Send the command.
    //
    xHWREG(ulBase + I2C_MCS) = ulCmd;
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Get the raw error state
    //
    ulErr = xHWREG(ulBase + I2C_MCS);

    //
    // If the I2C master is busy, then all the other bit are invalid, and
    // don't have an error to report.
    //
    if(ulErr & I2C_MCS_BUSY)
    {
        return(I2C_MASTER_ERR_NONE);
    }

    //
    // Check for errors.
    //
    if(ulErr & (I2C_MCS_ERROR | I2C_MCS_ARBLST))
    {
        return(ulErr & (I2C_MCS_ARBLST | I2C_MCS_DATACK | I2C_MCS_ADRACK));
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
I2CMasterDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_MDR) = ucData;
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
I2CMasterDataGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    //
    // Read a byte.
    //
    return(xHWREG(ulBase + I2C_MDR));
}

//*****************************************************************************
//
//! Gets the I2C Slave module status
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This function will return the action requested from a master, if any.
//! Possible values are:
//!
//! - \b I2C_SLAVE_ACT_NONE
//! - \b I2C_SLAVE_ACT_RREQ
//! - \b I2C_SLAVE_ACT_TREQ
//! - \b I2C_SLAVE_ACT_RREQ_FBR
//!
//! \return Returns \b I2C_SLAVE_ACT_NONE to indicate that no action has been
//! requested of the I2C Slave module, \b I2C_SLAVE_ACT_RREQ to indicate that
//! an I2C master has sent data to the I2C Slave module, \b I2C_SLAVE_ACT_TREQ
//! to indicate that an I2C master has requested that the I2C Slave module send
//! data, and \b I2C_SLAVE_ACT_RREQ_FBR to indicate that an I2C master has sent
//! data to the I2C slave and the first byte following the slave's own address
//! has been received.
//
//*****************************************************************************
unsigned long
I2CSlaveStatus(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Return the slave status.
    //
    return(xHWREG(ulBase + I2C_SCSR));
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Slave.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ucData data to be transmitted from the I2C Slave
//!
//! This function will place the supplied data into I2C Slave Data Register.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSlaveDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_SDR) = ucData;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Slave.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This function reads a byte of data from the I2C Slave Data Register.
//!
//! \return Returns the byte received from by the I2C Slave, cast as an
//! unsigned long.
//
//*****************************************************************************
unsigned long
I2CSlaveDataGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_SLAVE_BASE) || (ulBase == I2C1_SLAVE_BASE));

    //
    // Read a byte.
    //
    return(xHWREG(ulBase + I2C_SDR));
}

//*****************************************************************************
//
//! \brief Transmite the STOP condition, master goes to idle state.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function free the I2C bus. When the master no longer need send or 
//! receive any more data, or need to terminate this transmition after getting
//! some errors, call this function.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CMasterStop(unsigned long ulBase)
{
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    
    while(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY);
    
    xHWREG(ulBase + I2C_MCS) = I2C_MASTER_CMD_BURST_SEND_ERROR_STOP;
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
    unsigned long ulCmd;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));

    //
    // Waitting the I2C Control & I2C bus to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while((ulStatus & I2C_MCS_BUSY) || (!(ulStatus & I2C_MCS_BUSY) && 
                                         (ulStatus & I2C_MCS_BUSBSY)));
    
    //
    // Set the address of the slave with which the master will communicate.
    // R/S is transmit(0)
    //    
    xHWREG(ulBase + I2C_MSA) = (ucSlaveAddr << 1) | 0;
    
    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_MDR) = ucData;
    
    //
    // Send the command.
    //
    ulCmd = bEndTransmition ? I2C_MASTER_CMD_SINGLE_SEND :
                              I2C_MASTER_CMD_BURST_SEND_START;
                                            
    xHWREG(ulBase + I2C_MCS) = ulCmd;
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
    unsigned long ulCmd;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    
    //
    // Waiting the I2C controller to idle
    //
    while(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY);
    
    //
    // Write the byte.
    //
    xHWREG(ulBase + I2C_MDR) = ucData;
    
    //
    // Send the command.
    //
    ulCmd = bEndTransmition ? I2C_MASTER_CMD_BURST_SEND_FINISH :
                              I2C_MASTER_CMD_BURST_SEND_CONT;
                                            
    xHWREG(ulBase + I2C_MCS) = ulCmd;    
       
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    
    //
    // Send write request
    //
    I2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, bEndTransmition);
    
    //
    // Waiting the I2C controller to idle
    //
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);    
    }
    while(ulStatus & I2C_MCS_BUSY);
    
    //
    // return the error status
    //
    return (ulStatus & (I2C_MCS_ARBLST | I2C_MCS_DATACK | I2C_MCS_ADRACK));
    
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    
    //
    // Send write request
    //
    I2CMasterWriteRequestS2(ulBase, ucData, bEndTransmition);
    
    //
    // Waiting the I2C controller to idle
    //
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);    
    }
    while(ulStatus & I2C_MCS_BUSY);
        
    //
    // return the error status
    //
    return (ulStatus & (I2C_MCS_ARBLST | I2C_MCS_DATACK | I2C_MCS_ADRACK));    
    
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
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
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while((ulStatus & I2C_MCS_BUSY) || (!(ulStatus & I2C_MCS_BUSY) && 
                                         (ulStatus & I2C_MCS_BUSBSY)));

    //
    // Set the address of the slave with which the master will communicate.
    // R/S is transmit(0)
    //    
    xHWREG(ulBase + I2C_MSA) = (ucSlaveAddr << 1) | 0;
    
    //
    // Write the first byte.
    //
    xHWREG(ulBase + I2C_MDR) = pucDataBuf[0];                                     
    xHWREG(ulBase + I2C_MCS) = I2C_MASTER_CMD_BURST_SEND_START;
    
    //
    // Waiting the I2C controller to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while(ulStatus & I2C_MCS_BUSY);
    
    //
    // Check if any error occurs
    //
    if(ulStatus & (I2C_MCS_ERROR | I2C_MCS_ARBLST))
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
    unsigned long ulCmd;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(pucDataBuf);
    
    //
    // Waiting the I2C controller to idle
    //
    while(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY);

    
    for(i = 0; i < ulLen - 1; i++)                              
    {        
        //
        // Write the first byte.
        //
        xHWREG(ulBase + I2C_MDR) = pucDataBuf[i];                                     
        xHWREG(ulBase + I2C_MCS) = I2C_MASTER_CMD_BURST_SEND_CONT;
        //
        // Waiting the I2C controller to idle
        //    
        do
        {
            ulStatus = xHWREG(ulBase + I2C_MCS);
        }while(ulStatus & I2C_MCS_BUSY);
        
        //
        // Check if any error occurs
        //
        if(ulStatus & I2C_MCS_ERROR)
        {
            return i;   
        }        
    }   
    
    xHWREG(ulBase + I2C_MDR) = pucDataBuf[i]; 
    ulCmd = bEndTransmition ? I2C_MASTER_CMD_BURST_SEND_FINISH :
                              I2C_MASTER_CMD_BURST_SEND_CONT;
    xHWREG(ulBase + I2C_MCS) = ulCmd;                          

    //
    // Waiting the I2C controller to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while(ulStatus & I2C_MCS_BUSY);
    
    //
    // Check if any error occurs
    //
    if(ulStatus & I2C_MCS_ERROR)
    {
        return ulLen - 1;   
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
    unsigned long ulCmd;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    
    //
    // Waitting the I2C Control & I2C bus to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while((ulStatus & I2C_MCS_BUSY) || (!(ulStatus & I2C_MCS_BUSY) && 
                                         (ulStatus & I2C_MCS_BUSBSY)));
    
    //
    // Set the address of the slave with which the master will communicate.
    // R/S is transmit(0)
    //    
    xHWREG(ulBase + I2C_MSA) = (ucSlaveAddr << 1) | I2C_MSA_RS;
    
    
    //
    // Send the command.
    //
    ulCmd = bEndTransmition ? I2C_MASTER_CMD_SINGLE_RECEIVE :
                              I2C_MASTER_CMD_BURST_RECEIVE_START;
                                            
    xHWREG(ulBase + I2C_MCS) = ulCmd;
       
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
    unsigned long ulCmd;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    
    //
    // Waitting the I2C Control & I2C bus to idle
    //
    while(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY);

    //
    // Send the command.
    //
    ulCmd = bEndTransmition ? I2C_MASTER_CMD_BURST_RECEIVE_FINISH :
                              I2C_MASTER_CMD_BURST_RECEIVE_CONT;
                                            
    xHWREG(ulBase + I2C_MCS) = ulCmd;    
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE)); 
    
    //
    // Waitting the I2C Control & I2C bus to idle
    //
    while(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY);

    
    //
    // RECEIVE operation with negative ACK(no stop)
    //
    xHWREG(ulBase + I2C_MCS) = 0x00000001;    
    
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    xASSERT(pucData);
    
    I2CMasterReadRequestS1(ulBase, ucSlaveAddr, bEndTransmition);
    
    //
    // Waiting the I2C controller to idle
    //
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);    
    }
    while(ulStatus & I2C_MCS_BUSY);
  
    //
    // Get the error code
    //
    ulStatus &= (I2C_MCS_ARBLST | I2C_MCS_DATACK | I2C_MCS_ADRACK);
            
    if(!ulStatus)
    {
        *pucData = xHWREG(ulBase + I2C_MDR);
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));

    I2CMasterReadRequestS2(ulBase, bEndTransmition);
    
    //
    // Waiting the I2C controller to idle
    //
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);    
    }
    while(ulStatus & I2C_MCS_BUSY);
        
    //
    // Get the error code
    //
    ulStatus &= (I2C_MCS_ARBLST | I2C_MCS_DATACK | I2C_MCS_ADRACK);
            
    if(!ulStatus)
    {
        *pucData = xHWREG(ulBase + I2C_MDR);
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
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
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
            pucDataBuf[0] = xHWREG(ulBase + I2C_MDR);
            
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
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while((ulStatus & I2C_MCS_BUSY) || (!(ulStatus & I2C_MCS_BUSY) && 
                                         (ulStatus & I2C_MCS_BUSBSY)));

    //
    // Set the address of the slave with which the master will communicate.
    // R/S is receive(1)
    //    
    xHWREG(ulBase + I2C_MSA) = (ucSlaveAddr << 1) | I2C_MSA_RS;
    
    //
    // First receive request
    //
    xHWREG(ulBase + I2C_MCS) = I2C_MASTER_CMD_BURST_RECEIVE_START;
    
    //
    // Waiting the I2C controller to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while(ulStatus & I2C_MCS_BUSY);
    
    //
    // Check if any error occurs
    //
    if(ulStatus & (I2C_MCS_ERROR | I2C_MCS_ARBLST))
    {
        return 0;   
    }
    
    pucDataBuf[0] = xHWREG(ulBase + I2C_MDR);
    
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
    unsigned long ulCmd;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_MASTER_BASE) || (ulBase == I2C1_MASTER_BASE));
    xASSERT(pucDataBuf);

    if(ulLen == 0) 
    {
        return 0;
    }
    
    //
    // Waiting the I2C controller to idle
    //
    while(xHWREG(ulBase + I2C_MCS) & I2C_MCS_BUSY);

    for(i = 0; i < ulLen - 1; i++)                              
    {                           
        xHWREG(ulBase + I2C_MCS) = I2C_MASTER_CMD_BURST_RECEIVE_CONT;
        
        //
        // Waiting the I2C controller to idle
        //    
        do
        {
            ulStatus = xHWREG(ulBase + I2C_MCS);
        }while(ulStatus & I2C_MCS_BUSY);
        
        //
        // Check if any error occurs
        //
        if(ulStatus & I2C_MCS_ERROR)
        {
            return i;   
        }
        
        pucDataBuf[i] = xHWREG(ulBase + I2C_MDR);
    }   
    
    ulCmd = bEndTransmition ? I2C_MASTER_CMD_BURST_RECEIVE_FINISH :
                              I2C_MASTER_CMD_BURST_RECEIVE_CONT;
    xHWREG(ulBase + I2C_MCS) = ulCmd;                          

    //
    // Waiting the I2C controller to idle
    //    
    do
    {
        ulStatus = xHWREG(ulBase + I2C_MCS);
    }while(ulStatus & I2C_MCS_BUSY);
    
    //
    // Check if any error occurs
    //
    if(ulStatus & I2C_MCS_ERROR)
    {
        return ulLen - 1;   
    }
    
    pucDataBuf[i] = xHWREG(ulBase + I2C_MDR);
    
    return ulLen; 
    
}
