//*****************************************************************************
//
//! \file xacmp.c
//! \brief Driver for the analog comparator.
//! \version V2.1.1.1
//! \date 11/14/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "xhw_acmp.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xacmp.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xcore.h"

//*****************************************************************************
//
// The Interrupt Callback functions
//
//*****************************************************************************
static xtEventCallback g_pfnACMPHandlerCallbacks[2] = {0};

//*****************************************************************************
//
//! \brief Init the Comp n Interrupt Callback function.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulCompID is the ID(index) of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
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
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID == xACMP_0) || (ulCompID == xACMP_1));

    switch(ulCompID)
    {
        case xACMP_0:
        {
            g_pfnACMPHandlerCallbacks[0] = pfnCallback;
            break;
        }
        case xACMP_1:
        {
            g_pfnACMPHandlerCallbacks[1] = pfnCallback;
            break;
        }        
    }
}

//*****************************************************************************
//
//! \brief Comparator 0 Interrupt Handler.
//!
//! If users want to user the ACMP Interrupt Callback feature, Users should 
//! promise that the ACMP Handle in the vector table is ACMPIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
COMPIntHandler(void)    
{
    unsigned long ulBase = ACMP_BASE;   
    unsigned long ulIntFlags1, ulIntFlags2;

    //
    // Get the Interrupt flags
    //
    ulIntFlags1 = xHWREG(ulBase + ACMP_ISR);
    ulIntFlags2 = xHWREG(ulBase + ACMP_ISR + 0x100);

    //
    // Clear the Interrrupt flags
    //
    xHWREG(ulBase + ACMP_ICLR) = ulIntFlags1;
    xHWREG(ulBase + ACMP_ICLR+ 0x100) = ulIntFlags2;

    //
    // Call user event callback function
    //
    if((ulIntFlags1) && g_pfnACMPHandlerCallbacks[0])
    {
        g_pfnACMPHandlerCallbacks[0](0, 0, 0, 0);
    }
    
    if((ulIntFlags2) && g_pfnACMPHandlerCallbacks[1])
    {
        g_pfnACMPHandlerCallbacks[1](0, 0, 0, 0);
    }
}

//*****************************************************************************
//
//! \brief Select the ACMP- input source of the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulSource is the source of Comp- input. 
//! Refrence \ref NUC1xx_ACMP_Analog_Src_negative.
//!
//! This function configures the Comp- input source of a comparator.  
//!
//! \return None.
//
//*****************************************************************************
void
ACMPConfigure(unsigned long ulBase, unsigned long ulCompID, 
              unsigned long ulConfig)
{   
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));
    xASSERT((((ulConfig & ACMP_POSITIVE_INPUT) == ACMP_POSITIVE_INPUT) || 
            ((ulConfig & ACMP_POSITIVE_INPUT) == ACMP_NEGATIVE_INPUT)) &&
            (((ulConfig & ACMP_MODE_CMP) == ACMP_MODE_CMP) || 
            ((ulConfig & ACMP_MODE_CMP) == ACMP_MODE_OP)));

    //
    // Set Configure
    //
    xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100) &= ~ACMP_CONFIG_MASK;
    xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100) |= ulConfig;
}

//*****************************************************************************
//
//! \brief Cancellation of ACMP peripheral that will decrease the offset 
//! between CP and CN.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulInputRef Specify the CMP_OP reference input for cancellation. 
//!
//! This function Cancellation of ACMP peripheral that will decrease the offset 
//! between CP and CN.  
//!
//! \return None.
//
//*****************************************************************************
void
ACMPCancellation(unsigned long ulBase,  unsigned long ulCompID,
                 unsigned long ulInputRef)
{
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));
    unsigned long i=0,ulTemp=0,ulTemp1=0;
    ulTemp1 = xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100);
    xHWREG(ulBase + ACMP_IER + ulCompID*0x100) = 0;
    xHWREG(ulBase + ACMP_ICLR + ulCompID*0x100) = 3;
    xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100) = ACMP_OPACR_EN | 
                                                   ACMP_OPACR_AOFM | 
                                                   ulInputRef;

    xHWREG(ulBase + ACMP_OFVCR + ulCompID*0x100) = 0;
    while (ulTemp ==0)
    {
        xHWREG(ulBase + ACMP_OFVCR + ulCompID*0x100) = i;
        SysCtlDelay(20000);
        ulTemp = (xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100)
                  & ACMP_OPACR_CMPS);
        i++;
    if(i >64){ulTemp = 1;} 
    }

    xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100) = ulTemp1;
    
    return ;
}

//*****************************************************************************
//
//! \brief Enable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables comparator. 
//!
//! \return None.
//
//*****************************************************************************    
void
ACMPEnable(unsigned long ulBase,  unsigned long ulCompID)    
{
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Enable the comparator
    //
    xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100) |= ACMP_OPACR_EN;
}

//*****************************************************************************
//
//! \brief Disable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function disables comparator. 
//!
//! \return None.
//
//*****************************************************************************
void
ACMPDisable(unsigned long ulBase,  unsigned long ulCompID)    
{
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Disable the comparator
    //
    xHWREG(ulBase + ACMP_OPACR + ulCompID*0x100) &= ~ACMP_OPACR_EN;
}

//*****************************************************************************
//
//! \brief Enable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulIntType is the base address of the comparator module.
//!
//! This function enables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntEnable(unsigned long ulBase, unsigned long ulCompID,
              unsigned long ulIntType)    
{
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Enable the comparator interrupt
    //
    xHWREG(ulBase + ACMP_IER + ulCompID*0x100) |= ulIntType;

}

//*****************************************************************************
//
//! \brief Disable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulIntType is the index(0 - 1) of the comparator.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntDisable(unsigned long ulBase, unsigned long ulCompID,
               unsigned long ulIntType)    
{
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Disable the comparator interrupt
    //
    xHWREG(ulBase + ACMP_IER + ulCompID*0x100) &= ~ulIntType;
}

//*****************************************************************************
//
//! \brief Get the current interrupt status.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This returns the interrupt status for the comparator.  
//!
//! \return interrupt status.
//
//*****************************************************************************
unsigned long
ACMPIntStatus(unsigned long ulBase, unsigned long ulCompID)
{    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the comp flag
    //
    return xHWREG(ulBase + ACMP_ISR + ulCompID*0x100);
}

//*****************************************************************************
//
//! \brief Get the current flag status.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This returns the flag status for the comparator.  
//!
//! \return flag status.
//
//*****************************************************************************
unsigned long
ACMPFlagStatus(unsigned long ulBase, unsigned long ulCompID)
{    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the comp flag
    //
    return xHWREG(ulBase + ACMP_RSR + ulCompID*0x100);
}

//*****************************************************************************
//
//! \brief Clear a comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulIntType is the index(0 - 1) of the comparator.
//!
//! The comparator interrupt is cleared, so that it no longer asserts.  This
//! fucntion must be called in the interrupt handler to keep the handler from
//! being called again immediately upon exit. 
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntClear(unsigned long ulBase, unsigned long ulCompID,
             unsigned long ulIntType)
{
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Wirte 1 to clear the comp flag
    //
    xHWREG(ulBase + ACMP_ICLR + ulCompID*0x100) |= ulIntType;
}

