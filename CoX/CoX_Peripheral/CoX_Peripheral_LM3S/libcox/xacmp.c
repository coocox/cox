//*****************************************************************************
//
//! \file xcomp.c
//! \brief Driver for the analog comparator.
//! \version V2.1.1.0
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
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_acmp.h"
#include "xacmp.h"

//*****************************************************************************
//
// The Interrupt Callback functions
//
//*****************************************************************************
static xtEventCallback g_pfnCOMPHandlerCallbacks[3] = {0};

//*****************************************************************************
//
//! \brief Configures a comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator to configure.
//! \param ulConfig is the configuration of the comparator.
//!
//! This function configures a comparator.  The \e ulConfig parameter is the
//! result of a logical OR operation between the \b COMP_TRIG_xxx,
//! \b COMP_INT_xxx, \b COMP_ASRCP_xxx, and \b COMP_OUTPUT_xxx values.
//!
//! The \b COMP_TRIG_xxx term can take on the following values:
//!
//! - \b COMP_TRIG_NONE to have no trigger to the ADC.
//! - \b COMP_TRIG_HIGH to trigger the ADC when the comparator output is high.
//! - \b COMP_TRIG_LOW to trigger the ADC when the comparator output is low.
//! - \b COMP_TRIG_FALL to trigger the ADC when the comparator output goes low.
//! - \b COMP_TRIG_RISE to trigger the ADC when the comparator output goes
//! high.
//! - \b COMP_TRIG_BOTH to trigger the ADC when the comparator output goes low
//! or high.
//!
//! The \b COMP_INT_xxx term can take on the following values:
//!
//! - \b COMP_INT_HIGH to generate an interrupt when the comparator output is
//! high.
//! - \b COMP_INT_LOW to generate an interrupt when the comparator output is
//! low.
//! - \b COMP_INT_FALL to generate an interrupt when the comparator output goes
//! low.
//! - \b COMP_INT_RISE to generate an interrupt when the comparator output goes
//! high.
//! - \b COMP_INT_BOTH to generate an interrupt when the comparator output goes
//! low or high.
//!
//! The \b COMP_ASRCP_xxx term can take on the following values:
//!
//! - \b COMP_ASRCP_PIN to use the dedicated Comp+ pin as the reference
//! voltage.
//! - \b COMP_ASRCP_PIN0 to use the Comp0+ pin as the reference voltage (this
//! the same as \b COMP_ASRCP_PIN for the comparator 0).
//! - \b COMP_ASRCP_REF to use the internally generated voltage as the
//! reference voltage.
//!
//! The \b COMP_OUTPUT_xxx term can take on the following values:
//!
//! - \b COMP_OUTPUT_NORMAL to enable a non-inverted output from the comparator
//! to a device pin.
//! - \b COMP_OUTPUT_INVERT to enable an inverted output from the comparator to
//! a device pin.
//! - \b COMP_OUTPUT_NONE is deprecated and behaves the same as
//! \b COMP_OUTPUT_NORMAL.
//!
//! \return None.
//
//*****************************************************************************
void
ComparatorConfigure(unsigned long ulBase, unsigned long ulComp,
                    unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT(ulComp < 3);

    //
    // Configure this comparator.
    //
    xHWREG(ulBase + (ulComp * 0x20) + COMP_ACCTL0) = ulConfig;
}

//*****************************************************************************
//
//! \brief Sets the internal reference voltage.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulRef is the desired reference voltage.
//!
//! This function sets the internal reference voltage value.  The voltage is
//! specified as one of the following values:
//!
//! - \b COMP_REF_OFF to turn off the reference voltage
//! - \b COMP_REF_0V to set the reference voltage to 0 V
//! - \b COMP_REF_0_1375V to set the reference voltage to 0.1375 V
//! - \b COMP_REF_0_275V to set the reference voltage to 0.275 V
//! - \b COMP_REF_0_4125V to set the reference voltage to 0.4125 V
//! - \b COMP_REF_0_55V to set the reference voltage to 0.55 V
//! - \b COMP_REF_0_6875V to set the reference voltage to 0.6875 V
//! - \b COMP_REF_0_825V to set the reference voltage to 0.825 V
//! - \b COMP_REF_0_928125V to set the reference voltage to 0.928125 V
//! - \b COMP_REF_0_9625V to set the reference voltage to 0.9625 V
//! - \b COMP_REF_1_03125V to set the reference voltage to 1.03125 V
//! - \b COMP_REF_1_134375V to set the reference voltage to 1.134375 V
//! - \b COMP_REF_1_1V to set the reference voltage to 1.1 V
//! - \b COMP_REF_1_2375V to set the reference voltage to 1.2375 V
//! - \b COMP_REF_1_340625V to set the reference voltage to 1.340625 V
//! - \b COMP_REF_1_375V to set the reference voltage to 1.375 V
//! - \b COMP_REF_1_44375V to set the reference voltage to 1.44375 V
//! - \b COMP_REF_1_5125V to set the reference voltage to 1.5125 V
//! - \b COMP_REF_1_546875V to set the reference voltage to 1.546875 V
//! - \b COMP_REF_1_65V to set the reference voltage to 1.65 V
//! - \b COMP_REF_1_753125V to set the reference voltage to 1.753125 V
//! - \b COMP_REF_1_7875V to set the reference voltage to 1.7875 V
//! - \b COMP_REF_1_85625V to set the reference voltage to 1.85625 V
//! - \b COMP_REF_1_925V to set the reference voltage to 1.925 V
//! - \b COMP_REF_1_959375V to set the reference voltage to 1.959375 V
//! - \b COMP_REF_2_0625V to set the reference voltage to 2.0625 V
//! - \b COMP_REF_2_165625V to set the reference voltage to 2.165625 V
//! - \b COMP_REF_2_26875V to set the reference voltage to 2.26875 V
//! - \b COMP_REF_2_371875V to set the reference voltage to 2.371875 V
//!
//! \return None.
//
//*****************************************************************************
void
ComparatorRefSet(unsigned long ulBase, unsigned long ulRef)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);

    //
    // Set the voltage reference voltage as requested.
    //
    xHWREG(ulBase + COMP_ACREFCTL) = ulRef;
}

//*****************************************************************************
//
//! \brief Gets the current comparator output value.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//!
//! This function retrieves the current value of the comparator output.
//!
//! \return Returns \b xtrue if the comparator output is high and \b xfalse if
//! the comparator output is low.
//
//*****************************************************************************
xtBoolean
ComparatorValueGet(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT(ulComp < 3);

    //
    // Return the appropriate value based on the comparator's present output
    // value.
    //
    if(xHWREG(ulBase + (ulComp * 0x20) + COMP_ACSTAT0) & COMP_ACSTAT0_OVAL)
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
//! \brief Init the Comp n Interrupt Callback function.
//!
//! \param ulBase is the base address of the ADC.
//! \param pfnCallback is the callback function.
//!
//! When there is any ADC intrrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent not used, always 0..
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xACMPIntCallbackInit(unsigned long ulBase, unsigned long ulCompID,
                     xtEventCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT((ulCompID == xACMP_0) || (ulCompID == xACMP_1) ||
            (ulCompID == xACMP_2));

    switch(ulCompID)
    {
        case xACMP_0:
        {
            g_pfnCOMPHandlerCallbacks[0] = pfnCallback;
            break;
        }
        case xACMP_1:
        {
            g_pfnCOMPHandlerCallbacks[1] = pfnCallback;
            break;
        } 
        case xACMP_2:
        {
            g_pfnCOMPHandlerCallbacks[2] = pfnCallback;
            break;
        }        
    }
}

//*****************************************************************************
//
//! \brief Enables the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//!
//! This function enables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ComparatorIntEnable(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT(ulComp < 3);

    //
    // Enable the comparator interrupt.
    //
    xHWREG(ulBase + COMP_ACINTEN) |= 1 << ulComp;
}

//*****************************************************************************
//
//! \brief Disables the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ComparatorIntDisable(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT(ulComp < 3);

    //
    // Disable the comparator interrupt.
    //
    xHWREG(ulBase + COMP_ACINTEN) &= ~(1 << ulComp);
}

//*****************************************************************************
//
//! \brief Comparator 0 Interrupt Handler.
//!
//! If users want to user the COMP0 Interrupt Callback feature, Users should 
//! promise that the COMP0 Handle in the vector table is ACMP1IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ACMP0IntHandler(void)    
{
    unsigned long ulBase = COMP_BASE;
    unsigned long ulComp = 0;
    
    unsigned long ulIntFlags;

    //
    // Get the Interrupt flags
    //
    ulIntFlags = (xHWREG(ulBase + COMP_ACMIS) >> ulComp);

    //
    // Clear the Interrrupt flags
    //
    xHWREG(ulBase + COMP_ACMIS) = ulIntFlags;

    //
    // Call user event callback function
    //
    if(ulIntFlags && g_pfnCOMPHandlerCallbacks[ulComp])
    {
        g_pfnCOMPHandlerCallbacks[ulComp](0, 0, 0, 0);
    }    
}

//*****************************************************************************
//
//! \brief Comparator 1 Interrupt Handler.
//!
//! If users want to user the COMP1 Interrupt Callback feature, Users should 
//! promise that the COMP1 Handle in the vector table is ACMP1IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ACMP1IntHandler(void)    
{
    unsigned long ulBase = COMP_BASE;
    unsigned long ulComp = 1;
    
    unsigned long ulIntFlags;

    //
    // Get the Interrupt flags
    //
    ulIntFlags = (xHWREG(ulBase + COMP_ACMIS) >> ulComp);

    //
    // Clear the Interrrupt flags
    //
    xHWREG(ulBase + COMP_ACMIS) = ulIntFlags;

    //
    // Call user event callback function
    //
    if(ulIntFlags && g_pfnCOMPHandlerCallbacks[ulComp])
    {
        g_pfnCOMPHandlerCallbacks[ulComp](0, 0, 0, 0);
    }    
}

//*****************************************************************************
//
//! \brief Comparator 2 Interrupt Handler.
//!
//! If users want to user the COMP2 Interrupt Callback feature, Users should 
//! promise that the COMP2 Handle in the vector table is ACMP2IntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ACMP2IntHandler(void)    
{
    unsigned long ulBase = COMP_BASE;
    unsigned long ulComp = 2;
    
    unsigned long ulIntFlags;

    //
    // Get the Interrupt flags
    //
    ulIntFlags = (xHWREG(ulBase + COMP_ACMIS) >> ulComp);

    //
    // Clear the Interrrupt flags
    //
    xHWREG(ulBase + COMP_ACMIS) = ulIntFlags;

    //
    // Call user event callback function
    //
    if(ulIntFlags && g_pfnCOMPHandlerCallbacks[ulComp])
    {
        g_pfnCOMPHandlerCallbacks[ulComp](0, 0, 0, 0);
    }    
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//! \param bMasked is \b xfalse if the raw interrupt status is required and
//! \b xtrue if the masked interrupt status is required.
//!
//! This returns the interrupt status for the comparator.  Either the raw or
//! the masked interrupt status can be returned.
//!
//! \return \b xtrue if the interrupt is asserted and \b xfalse if it is not
//! asserted.
//
//*****************************************************************************
xtBoolean
ComparatorIntStatus(unsigned long ulBase, unsigned long ulComp,
                    xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT(ulComp < 3);

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(((xHWREG(ulBase + COMP_ACMIS) >> ulComp) & 1) ? xtrue : xfalse);
    }
    else
    {
        return(((xHWREG(ulBase + COMP_ACRIS) >> ulComp) & 1) ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! \brief Clears a comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//!
//! The comparator interrupt is cleared, so that it no longer asserts.  This
//! fucntion must be called in the interrupt handler to keep the handler from
//! being called again immediately upon exit.  Note that for a level-triggered
//! interrupt, the interrupt cannot be cleared until it stops asserting.
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
ComparatorIntClear(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == COMP_BASE);
    xASSERT(ulComp < 3);

    //
    // Clear the interrupt.
    //
    xHWREG(ulBase + COMP_ACMIS) = 1 << ulComp;
}


