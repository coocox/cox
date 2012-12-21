//*****************************************************************************
//
//! \file xacmp.c
//! \brief Driver for the analog comparator.
//! \version V2.2.1.0
//! \date 8/23/2012
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
//! \note In KL25Z Series, the ulCompID must be 0.
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
ACMPIntHandler(void)    
{
    unsigned long ulBase = ACMP_BASE;   
    unsigned long ulIntFlags;

    //
    // Get the Interrupt flags
    //
    ulIntFlags = xHWREGB(ulBase + CMP0_SCR);

    //
    // Clear the Interrrupt flags
    //
    xHWREGB(ulBase + CMP0_SCR) = ulIntFlags;

    //
    // Call user event callback function
    //
    if((ulIntFlags & 0x06) && g_pfnACMPHandlerCallbacks[0])
    {
        g_pfnACMPHandlerCallbacks[0](0, 0, ulIntFlags, 0);
    }
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
//! \note In KL25Z Series, the ulCompID must be 0.
//!
//! \return None.
//
//*****************************************************************************

void ACMPConfigure(unsigned long ulBase, unsigned long ulCompID, unsigned long ulConfig)
{
    unsigned long ulCRAddr;
    unsigned long ulPlus;
    unsigned long ulMinus;
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + CMP0_MUXCR + (4 * ulCompID);

    if(((ulConfig & CMP0_MUXCR_PSEL_M) == CMP0_MUXCR_PSEL_M) || 
    	 ((ulConfig & CMP0_MUXCR_MSEL_M) == CMP0_MUXCR_MSEL_M));
    {
        xHWREGB(ulBase + CMP0_DACCR) |= CMP0_DACCR_DACEN;
    }
    //
    // Set the comp- input source
    //
    ulPlus = (ulConfig & CMP0_MUXCR_PSEL_M);
    xHWREGB(ulCRAddr) &= ~CMP0_MUXCR_PSEL_M;
    xHWREGB(ulCRAddr) |= ulPlus;
    
    ulMinus = (ulConfig & CMP0_MUXCR_MSEL_M);
    xHWREGB(ulCRAddr) &= ~CMP0_MUXCR_MSEL_M;
    xHWREGB(ulCRAddr) |= ulMinus;
}

//*****************************************************************************
//
//! \brief Enable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the index(0 - 1) of the comparator.
//!
//! This function enables comparator. 
//!
//! \note In KL25Z Series, the ulComp must be 0.
//!
//! \return None.
//
//*****************************************************************************    
void
ACMPEnable(unsigned long ulBase, unsigned long ulCompID)    
{
    unsigned long ulCRAddr;
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + CMP0_CR1+ (4 * ulCompID);

    //
    // Enable the comparator
    //
    xHWREGB(ulCRAddr) |= CMP0_CR1_EN;
}

//*****************************************************************************
//
//! \brief Disable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the index(0 - 1) of the comparator.
//!
//! This function disables comparator. 
//!
//! \note In KL25Z Series, the ulCompID must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPDisable(unsigned long ulBase, unsigned long ulCompID)    
{
    unsigned long ulCRAddr;
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + CMP0_CR1 + (4 * ulCompID);

    //
    // Disable the comparator
    //
    xHWREGB(ulCRAddr) &= ~CMP0_CR1_EN;
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
//! \note In KL25Z Series, the ulComp must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntEnable(unsigned long ulBase, unsigned long ulCompID)    
{
    unsigned long ulCRAddr;
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + CMP0_SCR + (4 * ulCompID);

    //
    // Enable the comparator interrupt
    //
    xHWREGB(ulCRAddr) |= CMP0_SCR_IEF;
    xHWREGB(ulCRAddr) |= CMP0_SCR_IER;

}

//*****************************************************************************
//
//! \brief Disable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the index(0 - 1) of the comparator.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \note In KL25Z Series, the ulCompID must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntDisable(unsigned long ulBase, unsigned long ulCompID)    
{
    unsigned long ulCRAddr;
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the corresponding CR register address
    //
    ulCRAddr = ulBase + CMP0_SCR + (4 * ulCompID);

    //
    // Disable the comparator interrupt
    //
    xHWREGB(ulCRAddr) &= ~CMP0_SCR_IEF;
    xHWREGB(ulCRAddr) &= ~CMP0_SCR_IER;
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
//! \note In KL25Z Series, the ulComp must be 0.
//!
//! \return \b xtrue if the comp flag is asserted and \b xfalse if it is not
//! asserted.
//
//*****************************************************************************
xtBoolean
ACMPIntStatus(unsigned long ulBase, unsigned long ulComp)
{
    unsigned long ulStatus;
    
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Get the comp flag
    //
    ulComp +=0;
    ulStatus = xHWREGB(ulBase + CMP0_SCR) & (CMP0_SCR_CFF | CMP0_SCR_CFR); 

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
//! \note In KL25Z Series, the ulComp must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntClear(unsigned long ulBase, unsigned long ulComp)
{
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Wirte 1 to clear the comp flag
    //
    ulComp +=0;
    xHWREGB(ulBase + CMP0_SCR) |= CMP0_SCR_CFF;
    xHWREGB(ulBase + CMP0_SCR) |= CMP0_SCR_CFR;
}

//*****************************************************************************
//
//! \brief Set CMP0 Filter Sample Count.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCount is the Filter Sample Count which you will set.
//!
//! This function is used to Set CMP0 Filter Sample Count.
//!
//! \note if ulCount is CMP_FILTER_SAMPLE_COUNT_0, then Filter is disabled. 
//! If SE = 1, then COUT is a logic 0. This is not a legal state, and is not
//! recommended. If SE = 0, COUT = COUTA.
//!
//! \return None.
//
//*****************************************************************************
void
CMPFilterSampleCountSet(unsigned long ulBase, unsigned long ulCount)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulCount == CMP_FILTER_SAMPLE_COUNT_0)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_1)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_2)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_3)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_4)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_5)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_6)||
            (ulCount == CMP_FILTER_SAMPLE_COUNT_7));

    //
    // Set Filter Sample Count
    //
    xHWREGB(ulBase + CMP0_CR0) &= ~CMP0_CR0_FILTER_CNT_M;
    xHWREGB(ulBase + CMP0_CR0) |= ulCount;
}

//*****************************************************************************
//
//! \brief Set CMP0 Comparator hard block hysteresis control.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulLevel is the the programmable hysteresis level.
//!
//! This function is used to Set Comparator hard block hysteresis control.
//!
//! \return None.
//
//*****************************************************************************
void
CMPHystersisLevelSet(unsigned long ulBase, unsigned long ulLevel)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulLevel == CMP_HYSTERESIS_LEVEL_0)||
            (ulLevel == CMP_HYSTERESIS_LEVEL_1)||
            (ulLevel == CMP_HYSTERESIS_LEVEL_2)||
            (ulLevel == CMP_HYSTERESIS_LEVEL_3));

    //
    // Set hysteresis level
    //
    xHWREGB(ulBase + CMP0_CR0) &= ~CMP0_CR0_HYSTCTR_M;
    xHWREGB(ulBase + CMP0_CR0) |= ulLevel;
}

//*****************************************************************************
//
//! \brief Enable the comparator Sample.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables sample function.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPSampleEnable(unsigned long ulBase)    
{ 
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the comparator sample function.
    //
    xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_SE;
}

//*****************************************************************************
//
//! \brief Disable the comparator Sample.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function disables sample function.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPSampleDisable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Disable the comparator sample function.
    //
    xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_SE;
}

//*****************************************************************************
//
//! \brief Enable the comparator Windowing.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables Windowing function.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPWindowingModeEnable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the comparator Windowing function.
    //
    xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_WE;
}

//*****************************************************************************
//
//! \brief Disable the comparator Windowing.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function Disables Windowing function.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPWindowingModeDisable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Disable the comparator Windowing function.
    //
    xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_WE;
}

//*****************************************************************************
//
//! \brief Enable the comparator Trigger Mode.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables Trigger Mode.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPTriggerModeEnable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the comparator Trigger function.
    //
    xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_TRIGM;
}

//*****************************************************************************
//
//! \brief Disable the comparator Trigger Mode.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function disables Trigger Mode.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPTriggerModeDisable(unsigned long ulBase)    
{   
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the comparator Trigger function.
    //
    xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_TRIGM;
}

//*****************************************************************************
//
//! \brief Enable the Comparator Output Pin.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables Comparator Output Pin.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPComparatorOutputPinEnable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the Comparator Output Pin.
    //
    xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_OPE;
}

//*****************************************************************************
//
//! \brief Disable the Comparator Output Pin.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function Disables Comparator Output Pin.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPComparatorOutputPinDisable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Disable the Comparator Output Pin.
    //
    xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_OPE;
}

//*****************************************************************************
//
//! \brief Enable the Comparator INVERT.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables INVERT.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPInvertEnable(unsigned long ulBase)    
{   
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the Comparator Output Pin.
    //
    xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_INV;
}

//*****************************************************************************
//
//! \brief Disable the Comparator INVERT.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function Disables INVERT.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPInvertDisable(unsigned long ulBase)    
{
    xASSERT(ulBase == ACMP_BASE);

    //
    // Disable the Comparator Output Pin.
    //
    xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_INV;
}

//*****************************************************************************
//
//! \brief Set Comparator Power Mode.
//!
//! \param ulBase is the base address of the CMP module.
//! \param ulPowerMode is Low-Power Configuration Mode that you will set. 
//! Refrence \ref KLx_CMP_Power_Mode.
//!
//! This function is to Select ADC Power Mode.
//!
//! \return None.
//
//*****************************************************************************
void
CMPPowerModeSet(unsigned long ulBase, unsigned long ulPowerMode)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulPowerMode == CMP_POWER_MODE_LS) ||
            (ulPowerMode == CMP_POWER_MODE_HS));

    //
    // Select CMP Power Mode
    //
    if(ulPowerMode == CMP_POWER_MODE_HS)
    {
        xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_PMODE;        
    }
    else
    {
        xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_PMODE;
    }
}

//*****************************************************************************
//
//! \brief Set Comparator Output.
//!
//! \param ulBase is the base address of the CMP module.
//! \param ulOutput is Output that you will set. 
//! Refrence \ref KLx_CMP_Output.
//!
//! This function is to Set Comparator Output.
//!
//! \return None.
//
//*****************************************************************************
void
CMPOutputSet(unsigned long ulBase, unsigned long ulOutput)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulOutput == CMP_OUTPUT_COUT) ||
            (ulOutput == CMP_OUTPUT_COUTA));

    //
    // Select CMP Output
    //
    if(ulOutput == CMP_OUTPUT_COUTA)
    {
        xHWREGB(ulBase + CMP0_CR1) |= CMP0_CR1_COS;        
    }
    else
    {
        xHWREGB(ulBase + CMP0_CR1) &= ~CMP0_CR1_COS;
    }
}

//*****************************************************************************
//
//! \brief Set CMP Filter Sample Period.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulPeriod is the CMP Filter Sample Period.
//!
//! This function to Set Filter Sample Period.
//!
//! \note This function has no effect when Sampling mode is selected(CR1[SE]=1). 
//! In that case, the external SAMPLE signal is used to determine the sampling
//! period.
//!
//! \return None.
//
//*****************************************************************************
void
CMPFilterSamplePeriodSet(unsigned long ulBase, unsigned long ulPeriod)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);

    //
    // Set CMP Filter Sample Period
    //
    xHWREGB(ulBase + CMP0_FPR) &= ~CMP0_FPR_FILT_PER_M;
    xHWREGB(ulBase + CMP0_FPR) |= ulPeriod;
}

//*****************************************************************************
//
//! \brief Enable CMP DMA.
//!
//! \param ulBase is the base address of the CMP port.
//!
//! \return None.
//
//*****************************************************************************
void
CMPDMAEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable DMA for CMP
    //
    xHWREGB(ulBase + CMP0_SCR) |= CMP0_SCR_DMAEN;
}

//*****************************************************************************
//
//! \brief Disable CMP DMA.
//!
//! \param ulBase is the base address of the CMP port.
//!
//! \return None.
//
//*****************************************************************************
void
CMPDMADisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ACMP_BASE);

    //
    // Disable DMA for CMP
    //
    xHWREGB(ulBase + CMP0_SCR) &= ~CMP0_SCR_DMAEN;
}

//*****************************************************************************
//
//! \brief Enable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulIntType is the Interrupt Type.
//!
//! This function enables generation of an interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntEnable2(unsigned long ulBase, unsigned long ulIntType)    
{
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulIntType == ACMP_INT_RISING) ||
            (ulIntType == ACMP_INT_FALLING) ||
            (ulIntType == (ACMP_INT_FALLING|ACMP_INT_RISING)));

    //
    // Enable the comparator interrupt
    //
    xHWREGB(ulBase + CMP0_SCR ) |= ulIntType;
}

//*****************************************************************************
//
//! \brief Disable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulIntType is the Interrupt Type.
//!
//! This function disables generation of an interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPIntDisable2(unsigned long ulBase, unsigned long ulIntType)    
{
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulIntType == ACMP_INT_RISING) ||
            (ulIntType == ACMP_INT_FALLING) ||
            (ulIntType == (ACMP_INT_FALLING|ACMP_INT_RISING)));

    //
    // Disable the comparator interrupt
    //
    xHWREGB(ulBase + CMP0_SCR) &= ~ulIntType;
}

//*****************************************************************************
//
//! \brief Enable Pass Through Mode.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables Pass Through Mode.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPPassThroughModeEnable(unsigned long ulBase)    
{   
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the comparator Pass Through Mode.
    //
    xHWREGB(ulBase + CMP0_MUXCR) |= CMP0_MUXCR_PSTM;
}

//*****************************************************************************
//
//! \brief Disable Pass Through Mode.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function disables Pass Through Mode.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPPassThroughModeDisable(unsigned long ulBase)    
{   
    xASSERT(ulBase == ACMP_BASE);

    //
    // Disable the comparator Pass Through Mode.
    //
    xHWREGB(ulBase + CMP0_MUXCR) &= ~CMP0_MUXCR_PSTM;
}

//*****************************************************************************
//
//! \brief Enable the DAC of ACMP.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function enables the DAC of ACMP.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPDACEnable(unsigned long ulBase)    
{   
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the DAC of ACMP.
    //
    xHWREGB(ulBase + CMP0_DACCR) |= CMP0_DACCR_DACEN;
}

//*****************************************************************************
//
//! \brief Disable the DAC of ACMP.
//!
//! \param ulBase is the base address of the comparator module.
//!
//! This function Disables the DAC of ACMP.
//!
//! \return None.
//
//*****************************************************************************
void
ACMPDACDisable(unsigned long ulBase)    
{  
    xASSERT(ulBase == ACMP_BASE);

    //
    // Enable the DAC of ACMP.
    //
    xHWREGB(ulBase + CMP0_DACCR) &= ~CMP0_DACCR_DACEN;
}

//*****************************************************************************
//
//! \brief Set DAC Output Voltage.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulVoltage is the DAC  Output Voltage that you will set.
//!
//! This function to Set DAC Output Voltage.
//!
//! \return None.
//
//*****************************************************************************
void
CMPDACOutputVoltageSet(unsigned long ulBase, unsigned long ulVoltage)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulVoltage >= 0) && (ulVoltage < 64));

    //
    // Set DAC Output Voltage
    //
    xHWREGB(ulBase + CMP0_DACCR) &= ~CMP0_DACCR_VOSEL_M;
    xHWREGB(ulBase + CMP0_DACCR) |= ulVoltage;
}

//*****************************************************************************
//
//! \brief Set CMP0 Plus and Minus Comparator Input Mux.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulPlus is the the Plus Input Mux.
//! \param ulMinus is the the Minus Input Mux.
//!
//! This function is used to Set Comparator Plus and Minus Comparator Input Mux.
//!
//! \note You must Enable DAC before you set the ulPlus or ulMinus is 7.
//!
//! \return None.
//
//*****************************************************************************
void
CMPInputMuxSet(unsigned long ulBase, unsigned long ulPlus, unsigned long ulMinus)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ACMP_BASE);
    xASSERT((ulPlus >= 0) && (ulPlus < 8));
    xASSERT((ulMinus >= 0) && (ulMinus < 8));

    //
    // Set CMP0 Plus and Minus Comparator Input Mux.
    //
    xHWREGB(ulBase + CMP0_MUXCR) &= ~CMP0_MUXCR_PSEL_M;
    xHWREGB(ulBase + CMP0_MUXCR) |= (ulPlus << CMP0_MUXCR_PSEL_S);
    
    xHWREGB(ulBase + CMP0_MUXCR) &= ~CMP0_MUXCR_MSEL_M;
    xHWREGB(ulBase + CMP0_MUXCR) |= (ulMinus << CMP0_MUXCR_MSEL_S);
}
