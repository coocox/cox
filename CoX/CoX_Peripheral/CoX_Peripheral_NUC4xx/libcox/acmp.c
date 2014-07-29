//*****************************************************************************
//
//! \file acmp.c
//! \brief Driver for the analog comparator.
//! \version V2.1.1.0
//! \date 1/3/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "hw_acmp.h"
#include "CoX.h"


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
//! When there is any ADC interrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent not used, always 0.
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
	unsigned long  Base;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulCompID == xACMP_0) || (ulCompID == xACMP_1));
    Base = ((ulBase == ACMP_BASE) ? 0 : 2);

    switch(ulCompID)
    {
        case xACMP_0:
        {
            g_pfnACMPHandlerCallbacks[Base+0] = pfnCallback;
            break;
        }
        case xACMP_1:
        {
            g_pfnACMPHandlerCallbacks[Base+1] = pfnCallback;
            break;
        }        
    }
}

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \brief Comparator Interrupt Handler.
//!
//! If users want to user the ACMP Interrupt Callback feature, Users should 
//! promise that the ACMP Handle in the vector table is ACMPIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ACMP_IRQHandler(void)
{
    unsigned long ulBase = ACMP_BASE;
    unsigned long ulIntFlags;

    //
    // Get the Interrupt flags
    //
    ulIntFlags = xHWREG(ulBase + ACMP_SR);

    //
    // Clear the Interrrupt flags
    //
    xHWREG(ulBase + ACMP_SR) = ulIntFlags;

    //
    // Call user event callback function
    //
    if((ulIntFlags & ACMP_SR_CMPF0) && g_pfnACMPHandlerCallbacks[0])
    {
        g_pfnACMPHandlerCallbacks[0](0, 0, 0, 0);
    }
    
    if((ulIntFlags & ACMP_SR_CMPF1) && g_pfnACMPHandlerCallbacks[1])
    {
        g_pfnACMPHandlerCallbacks[1](0, 0, 0, 0);
    }
}
//
////*****************************************************************************
////
////! \brief Comparator Interrupt Handler.
////!
////! If users want to user the ACMP Interrupt Callback feature, Users should
////! promise that the ACMP Handle in the vector table is ACMPIntHandler.
////!
////! \return None.
////
////*****************************************************************************
//void
//ACMP23IntHandler(void)
//{
//    unsigned long ulBase = ACMP23_BASE;
//    unsigned long ulIntFlags;
//
//    //
//    // Get the Interrupt flags
//    //
//    ulIntFlags = xHWREG(ulBase + ACMP_SR);
//
//    //
//    // Clear the Interrrupt flags
//    //
//    xHWREG(ulBase + ACMP_SR) = ulIntFlags;
//
//    //
//    // Call user event callback function
//    //
//    if((ulIntFlags & ACMP_SR_CMPF0) && g_pfnACMPHandlerCallbacks[0])
//    {
//        g_pfnACMPHandlerCallbacks[3](0, 0, 0, 0);
//    }
//
//    if((ulIntFlags & ACMP_SR_CMPF1) && g_pfnACMPHandlerCallbacks[1])
//    {
//        g_pfnACMPHandlerCallbacks[4](0, 0, 0, 0);
//    }
//}
#ifdef __cplusplus
}
#endif
//*****************************************************************************
//
//! \brief Select the ACMP- input source of the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator to configure.
//! \param ulSource is the source of Comp- input. 
//! Refrence \ref M051_ACMP_Analog_Src_negative.
//!
//! This function configures the Comp- input source of a comparator.  
//!
//! \return None.
//
//*****************************************************************************
void
ACMPNegativeSrcSet(unsigned long ulBase, unsigned long ulComp,
                   unsigned long ulSource)
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));
    xASSERT((ulSource == ACMP_ASRCN_PIN) || (ulSource == ACMP_ASRCN_REF));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Set the comp- input source
    //
    xHWREG(ulCRAddr) &= ~ACMP_CR_CN;
    xHWREG(ulCRAddr) |= ulSource;
}

//*****************************************************************************
//
//! \brief Enable the comparator hysteresis function.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This function enables hysteresis function of the comparator. 
//!
//! \return None.
//
//*****************************************************************************  
void
ACMPHysEnable(unsigned long ulBase, unsigned long ulComp)    
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Enable hysteresis function. The typical range is 20mV. 
    //
    xHWREG(ulCRAddr) |= ACMP_CR_HYSEN;
}

//*****************************************************************************
//
//! \brief Disable the comparator hysteresis function.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This function disables hysteresis function of the comparator. 
//!
//! \return None.
//
//*****************************************************************************  
void
ACMPHysDisable(unsigned long ulBase, unsigned long ulComp)    
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Enable hysteresis function. The typical range is 20mV. 
    //
    xHWREG(ulCRAddr) &= ~ACMP_CR_HYSEN;

}

//*****************************************************************************
//
//! \brief Enable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This function enables comparator. 
//!
//! \return None.
//
//*****************************************************************************    
void
ACMPEnable(unsigned long ulBase, unsigned long ulComp)    
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Enable the comparator
    //
    xHWREG(ulCRAddr) |= ACMP_CR_CMPEN;
}

//*****************************************************************************
//
//! \brief Disable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This function disables comparator. 
//!
//! \return None.
//
//*****************************************************************************
void
ACMPDisable(unsigned long ulBase, unsigned long ulComp)    
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Disable the comparator
    //
    xHWREG(ulCRAddr) &= ~ACMP_CR_CMPEN;
}

//*****************************************************************************
//
//! \brief Enable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This function enables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntEnable(unsigned long ulBase, unsigned long ulComp)    
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Enable the comparator interrupt
    //
    xHWREG(ulCRAddr) |= ACMP_CR_CMPIE;

}

//*****************************************************************************
//
//! \brief Disable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntDisable(unsigned long ulBase, unsigned long ulComp)    
{
    unsigned long ulCRAddr;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + ACMP_CR0 + (4 * ulComp);

    //
    // Disable the comparator interrupt
    //
    xHWREG(ulCRAddr) &= ~ACMP_CR_CMPIE;
}

//*****************************************************************************
//
//! \brief Get the current interrupt status.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! This returns the interrupt status for the comparator.  
//!
//! \return \b xtrue if the comp flag is asserted and \b xfalse if it is not
//! asserted.
//
//*****************************************************************************
xtBoolean
ACMPIntStatus(unsigned long ulBase, unsigned long ulComp)
{
    unsigned long ulStatus;
    
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the comp flag
    //
    ulStatus = xHWREG(ulBase + ACMP_SR) & (1 << ulComp); 

    return (ulStatus ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clear a comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index(0 - 1) of the comparator.
//!
//! The comparator interrupt is cleared, so that it no longer asserts.  This
//! fucntion must be called in the interrupt handler to keep the handler from
//! being called again immediately upon exit. 
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntClear(unsigned long ulBase, unsigned long ulComp)
{
    xASSERT((ulBase == ACMP_BASE));
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Wirte 1 to clear the comp flag
    //
    xHWREG(ulBase + ACMP_SR) |= (1 << ulComp);
}


//*****************************************************************************
//
//! \brief Configures a comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID(index) of the comparator to configure.
//! Refrence \ref xACMP_Comparator_IDs.
//! \param ulConfig is the configuration of the comparator.
//!
//! This function configures a comparator.  The \e ulConfig parameter is the
//! result of a logical OR operation between the \b ACMP_ASRCP_xxx,
//! and \b ACMP_ASRCN_xxx values.
//!
//! The \b ACMP_ASRCP_xxx is determines the ACMP+ source,
//! values refrence \ref xACMP_Analog_Src_Positive.
//!
//! The \b ACMP_ASRCP_xxx is determines the ACMP- source:
//! values refrence \ref xACMP_Analog_Src_Negative.
//!
//! \return None.
//
//*****************************************************************************

void xACMPConfigure(unsigned long ulBase, unsigned long ulCompID,
                    unsigned long ulConfig)
{
	ACMPNegativeSrcSet(ulBase, ulCompID, ulConfig);
}

//*****************************************************************************
//
//! \brief Enable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function enables a comparator.
//!
//! \return None.
//
//*****************************************************************************
void xACMPEnable(unsigned long ulBase, unsigned long ulCompID)
{
	ACMPEnable(ulBase, ulCompID);
}

//*****************************************************************************
//
//! \brief Disable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function disables a comparator.
//!
//! \return None.
//
//*****************************************************************************
void xACMPDisable(unsigned long ulBase, unsigned long ulCompID)
{
	ACMPDisable(ulBase, ulCompID);
}

//*****************************************************************************
//
//! \brief Enable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID(index) of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function enables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void xACMPIntEnable(unsigned long ulBase, unsigned long ulCompID)
{
	ACMPIntEnable(ulBase, ulCompID);
}

//*****************************************************************************
//
//! \brief Disable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID(index) of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
void xACMPIntDisable(unsigned long ulBase, unsigned long ulCompID)
{
	ACMPIntDisable(ulBase, ulCompID);
}
