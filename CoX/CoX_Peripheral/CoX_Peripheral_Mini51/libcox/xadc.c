//*****************************************************************************
//
//! \file xadc.c
//! \brief Driver for the ADC Controller.
//! \version V2.1.1.0
//! \date 2/9/2012
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

#include "xhw_adc.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xadc.h"
#include "xdebug.h"
#include "xcore.h"

static xtEventCallback g_pfnADCHandlerCallbacks[1] = {0};

//*****************************************************************************
//
//! \brief Configure the mode and trigger source of a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulMode is the sequence operation mode. Refrence \ref xADC_Mode.
//! \param ulTrigger is the trigger source that initiates the sample sequence;
//! must be one of the \b xADC_TRIGGER_* values. Refrence 
//! \ref xADC_Trigger_Source.
//!
//! \return None.
//
//*****************************************************************************
void 
xADCConfigure(unsigned long ulBase, unsigned long ulMode, 
              unsigned long ulTrigger)
{
    unsigned long ulConfig;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == xADC0_BASE);

    xASSERT(ulMode == xADC_MODE_SCAN_SINGLE_CYCLE);
    xASSERT((ulTrigger == ADC_TRIGGER_PROCESSOR) || 
            (ulTrigger == (xADC_TRIGGER_EXT_PD2 | 
                           xADC_TRIGGER_EXT_FALLING_EDGE)) ||
            (ulTrigger == (xADC_TRIGGER_EXT_PD2 | 
                           xADC_TRIGGER_EXT_RISING_EDGE))                     
           );

    ulConfig = ulMode | ulTrigger;

    //
    // Save the config
    //
    xHWREG(ulBase + ADC_CR) &= ~(ADC_CR_TRGEN | ADC_CR_TRGCOND_FALLING);
    xHWREG(ulBase + ADC_CR) |= ulConfig;    
}

//*****************************************************************************
//
//! \brief Configure a step of the sample sequencer.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulStep is the step to be configured.
//! \param ulConfig is the configuration of this step; must be a logical OR of
//! \b xADC_CTL_END, and one of the input 
//! channel selects (\b xADC_CTL_CH0 through \b xADC_CTL_CH7).  For parts
//! with the digital comparator feature, the follow values may also be OR'd
//! into the \e ulConfig value to enable the digital comparater feature:
//! one of the comparater selects (\b xADC_CTL_CMP0 through xADC_CTL_CMP1). 
//! Refrence \ref xADC_Step_Config.
//!
//! This function will set the configuration of the ADC for one step of a
//! sample sequence.  The ADC can be configured for single-ended 
//! , the channel to be sampled can be chosen (the
//! \b xADC_CTL_CH0 through \b xADC_CTL_CH7 values), Additionally,
//! this step can be defined as the last in the sequence (the \b xADC_CTL_END
//! bit) . If the digital comparators are present
//! on the device, this step may also be configured send the ADC sample to
//! the selected comparator (the \b xADC_CTL_CMP0 through \b xADC_CTL_CMP1
//! values).  The configuration is used by the
//! ADC at the appropriate time when the trigger for this sequence occurs.
//!
//! \note It is the responsibility of the caller to ensure that a valid 
//! configuration is specified; this function does not check the validity of 
//! the specified configuration.
//!
//! \return None.
//
//*****************************************************************************
void 
xADCStepConfigure(unsigned long ulBase, unsigned long ulStep,
                  unsigned long ulConfig)
{
    unsigned long ulChannel;

    ulChannel = ulConfig & 0x0F;
    
    //
    // Check the arugments.
    //
    xASSERT(ulBase == xADC0_BASE);

    xASSERT(ulStep >= 0 && ulStep < 8);


    xASSERT(ulStep <= ulChannel);

    //
    // Save the Input mode config (set when the step is 0)
    //
    if(ulStep == 0)
    {
    }

    //
    // Configure the comp 0
    //
    if(ulConfig & 0x0800)
    {
       xHWREG( ulBase + ADC_CMPR0) &= ~(ADC_CMPRX_CMPCH_M);  
       xHWREG( ulBase + ADC_CMPR0) |= (ulChannel << ADC_CMPRX_CMPCH_S);
    }

    //
    // Configure the comp 1
    //
    if(ulConfig & 0x0900)
    {
       xHWREG( ulBase + ADC_CMPR1) &= ~(ADC_CMPRX_CMPCH_M);  
       xHWREG( ulBase + ADC_CMPR1) |= (ulChannel << ADC_CMPRX_CMPCH_S);
    }
    
    //
    // Clear the ADC_CHER first 
    //
    xHWREG(ulBase + ADC_CHER) |= 1 << ulChannel; 
}

//*****************************************************************************
//
//! \brief Configure an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the ID of the comparator to configure.
//! \param ulConfig is the configuration of the comparator.
//!
//! This function will configure a comparator.  The \e ulConfig parameter is
//! the result of xADC_COMP_INT_xxx value. Refrence 
//! \ref xADC_Comparator_Int_Condition.
//!
//! \return None.
//
//*****************************************************************************
void
xADCCompConditionConfig(unsigned long ulBase, unsigned long ulCompID, 
                        unsigned long ulConfig)
{
    unsigned long ulCompRegAddr;

    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Get the ADC_CMPRx register address
    //
    ulCompRegAddr = ulBase + ADC_CMPR0 + (4 * ulCompID);

    //
    // Write the config to the register
    //
    xHWREG(ulCompRegAddr) &= ~(ADC_CMPRX_CMPCOND);
    xHWREG(ulCompRegAddr) |= ulConfig;

}

//*****************************************************************************
//
//! \brief Init the ADC Interrupt Callback function.
//!
//! \param ulBase is the base address of the ADC.
//! \param pfnCallback is the callback function.
//!
//! When there is any ADC intrrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent is the interrupt event..
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xADCIntCallbackInit(unsigned long ulBase, 
                    xtEventCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == xADC0_BASE);

    g_pfnADCHandlerCallbacks[0] = pfnCallback;
}

//*****************************************************************************
//
//! \brief ADC0 Interrupt Handler.
//!
//! If users want to user the ADC0 Callback feature, Users should promise 
//! that the ADC0 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntHandler(void)
{
    unsigned long ulBase = ADC_BASE;
    unsigned long ulIntFlags;
    unsigned long ulEventFlags = 0;

    //
    // Get Int flags
    //
    ulIntFlags = xHWREG(ulBase + ADC_SR);

    //
    // Clear Int flags
    //
    xHWREG(ulBase + ADC_SR) = ulIntFlags;

    //
    // End conversion Interrupt on the sequence
    //
    if(ulIntFlags & ADC_SR_ADF)
    {
        ulEventFlags |= xADC_EVENT_END_CONVERSION;
    }

    //
    // Comp 0 Monitor Interrupt on the sequence
    //
    if(ulIntFlags & ADC_SR_CMPF0)
    {
        ulEventFlags |= xADC_EVENT_COMP0;
    }

    //
    // Comp 1 Monitor Interrupt on the sequence
    //
    if(ulIntFlags & ADC_SR_CMPF1)
    {
        ulEventFlags |= xADC_EVENT_COMP1;
    }

    if(ulEventFlags && g_pfnADCHandlerCallbacks[0])
    {
        g_pfnADCHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    } 

    //
    // ToDo: ulIntFlags is the interrupt flags
    //
    
}

//*****************************************************************************
//
//! \brief Get the captured data for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//! \param pulBuffer is the address where the data is stored.
//!
//! This function copies data from the specified sample sequence  FIFO to
//! a memory resident buffer.  The number of samples available in the 
//! FIFO are copied into the buffer, which is assumed to be large enough to
//! hold that many samples.  This will only return the samples that are
//! presently available, which may not be the entire sample sequence if it is
//! in the process of being executed.
//!
//! \return If some channel is converting ,return 0. 
//!         Else returns the number of samples copied to the buffer.
//
//*****************************************************************************
unsigned long
xADCDataGet(unsigned long ulBase, unsigned long *pulBuffer)
{
    unsigned long i;
    unsigned long ulEnableChannels;
    unsigned long ulValid;
    unsigned long ulWrite;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(pulBuffer != 0);

    //
    // Get the enable channels
    //
    ulEnableChannels = (xHWREG(ulBase + ADC_CHER) & ADC_CHER_CHEN_M) >> 
                       ADC_CHER_CHEN_S;

    //
    // Get the ADC status register data valid info
    //
    ulValid = (xHWREG(ulBase + ADC_SR) & ADC_SR_VALID) >> 8;

    //
    // Check if all enable channel data is valid
    //
    if(ulValid == 0)
    {
        //
        // some channel is converting, data is not ready
        //
        return 0;
    }

    //
    // Copy data to buffer
    //
    ulWrite = 0;
    for(i = 0; i < 8; i++)
    {
        if(ulEnableChannels & (1 << i))
        {
            pulBuffer[ulWrite++] = xHWREG(ulBase + ADC_DR0 + (4 * i));
            break;
            
        }
    }

    return ulWrite;
    
}

//*****************************************************************************
//
//! \brief Determine if the ADC sample sequence overflow occurred.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This determines if the ADC sample sequence overflow has occurred.  This will
//! happen if the captured samples are not read from the FIFO before the next
//! trigger occurs.
//!
//! \return Returns xfalse if there was not an overflow, and xtrue if there
//! was.
//
//*****************************************************************************
xtBoolean
xADCOverflow(unsigned long ulBase)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Get the ADC status register
    //
    ulStatus = xHWREG(ulBase + ADC_SR);

    return ((ulStatus & ADC_SR_OVERRUN) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clear the overflow condition on the ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This will clear an overflow condition on one of the sample sequences.  The
//! overflow condition must be cleared in order to detect a subsequent overflow
//! condition (it otherwise causes no harm).
//!
//! \return None.
//
//*****************************************************************************
void
xADCOverflowClear(unsigned long ulBase)  
{
    unsigned long i;
    unsigned long ulEnableChannels;
    volatile unsigned long ulDump;

    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Get the enable channels
    //
    ulEnableChannels = (xHWREG(ulBase + ADC_CHER) & ADC_CHER_CHEN_M) >> 
                       ADC_CHER_CHEN_S;
   
    //
    // Read the data register to clear the overflow flag
    //
    for(i = 0; i < 8; i++)
    {
        if(ulEnableChannels & (1 << i))
        {
            ulDump = xHWREG(ulBase + ADC_DR0 + (4 * i));    
        }
    }

}

//*****************************************************************************
//
//! \brief Configure the ADC.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulInputMode is the analog input mode.  
//! Refrence \ref MINI51_ADC_Input_Mode.
//! \param ulOpMode is the Operation mode. 
//! Refrence \ref MINI51_ADC_Operation_Mode.
//! \param ulTrigger is the trigger source that initiates the sample sequence;
//! must be one of the \b ADC_TRIGGER_* values. 
//! Refrence \ref MINI51_ADC_Tigger_Source.
//! 
//! This function configures the initiation criteria for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCConfigure(unsigned long ulBase, unsigned long ulInputMode,
             unsigned long ulOpMode, unsigned long ulTrigger)
{
    unsigned long ulConfig;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(ulInputMode == ADC_INPUT_SINGLE);
    xASSERT((ulTrigger == ADC_TRIGGER_PROCESSOR) || 
            (ulTrigger == (ADC_TRIGGER_EXT_PD2 | 
                           ADC_TRIGGER_EXT_FALLING_EDGE)) ||
            (ulTrigger == (ADC_TRIGGER_EXT_PD2 | 
                           ADC_TRIGGER_EXT_RISING_EDGE))                     
           );

    ulConfig = ulInputMode | ulOpMode | ulTrigger;

    //
    // Save the config
    //
    xHWREG(ulBase + ADC_CR) &= ~(ADC_CR_TRGEN | ADC_CR_TRGCOND_FALLING);
    xHWREG(ulBase + ADC_CR) |= ulConfig;
    
}
  
//*****************************************************************************
//
//! \brief Configure ADC channel 7.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulInputSrc  is the channe 7 input source. 
//! Refrence \ref MINI51_ADC_Channel7_Source.
//!
//! This function set the channel 7 input srouce.
//!
//! \return None.
//
//*****************************************************************************
void
ADCChannle7Configure(unsigned long ulBase, unsigned long ulInputSrc)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulInputSrc == ADC_CH7_EXT) || (ulInputSrc == ADC_CH7_INT_BV));

    //
    // Set channel 7 input source
    //
    xHWREG(ulBase + ADC_CHER) &= ~ADC_CHER_PRESEL_VBG;
    xHWREG(ulBase + ADC_CHER) |= ulInputSrc;
}

//*****************************************************************************
//
//! \brief Enable an ADC channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel  is the channel that to enable.
//!
//! This function enables an corresponding analog input channel.
//!
//! \return None.
//
//*****************************************************************************
void
ADCChannelEnable(unsigned long ulBase, unsigned long ulChannel)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(ulChannel >= 0 && ulChannel < 8);

    //
    // Enable the corresponding channle
    //
    xHWREG(ulBase + ADC_CHER) |= 1 << ulChannel;
}

//*****************************************************************************
//
//! \brief Disable an ADC channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel  is the channel that to enable.
//!
//! This function disables an corresponding analog input channel.
//!
//! \return None.
//
//*****************************************************************************
void
ADCChannelDisable(unsigned long ulBase, unsigned long ulChannel)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(ulChannel >= 0 && ulChannel < 8);

    //
    // Disable the corresponding channle
    //
    xHWREG(ulBase + ADC_CHER) &= ~(1 << ulChannel);
}

//*****************************************************************************
//
//! \brief Enable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//! Refrence \ref MINI51_ADC_Ints.
//!
//! Enables the indicated ADC interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | 
                             ADC_INT_COMP0 |
                             ADC_INT_COMP1))) == 0);

    //
    // Enable A/D Interrupt
    //
    if(ulIntFlags & ADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_CR) |= ADC_CR_ADIE;
    }

    //
    // Enable Compare 0 Interrupt
    //
    if(ulIntFlags & ADC_INT_COMP0)
    {
        xHWREG(ulBase + ADC_CMPR0) |= ADC_CMPRX_CMPIE;
    }

    //
    // Enable Compare 1 Interrupt
    //
    if(ulIntFlags & ADC_INT_COMP1)
    {
        xHWREG(ulBase + ADC_CMPR1) |= ADC_CMPRX_CMPIE;
    }

}

//*****************************************************************************
//
//! \brief Disable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//! Refrence \ref MINI51_ADC_Ints.
//!
//! Disables the indicated ADC interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | 
                             ADC_INT_COMP0 |
                             ADC_INT_COMP1))) == 0);

    //
    // Enable A/D Interrupt
    //
    if(ulIntFlags & ADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_CR) &= ~ADC_CR_ADIE;
    }

    //
    // Enable Compare 0 Interrupt
    //
    if(ulIntFlags & ADC_INT_COMP0)
    {
        xHWREG(ulBase + ADC_CMPR0) &= ~ADC_CMPRX_CMPIE;
    }

    //
    // Enable Compare 1 Interrupt
    //
    if(ulIntFlags & ADC_INT_COMP1)
    {
        xHWREG(ulBase + ADC_CMPR1) &= ~ADC_CMPRX_CMPIE;
    }

}

//*****************************************************************************
//
//! \brief Enable the ADC moudle.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Allows the specified sample sequence to be captured when its trigger is
//! detected. 
//!
//! \return None.
//
//*****************************************************************************
void
ADCEnable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // A/D Converter Enable
    //
    xHWREG(ulBase + ADC_CR) |= ADC_CR_ADEN;

}

//*****************************************************************************
//
//! \brief Get the current interrupt status.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This returns the interrupt status for the ADC module. 
//! Refrence \ref MINI51_ADC_Ints. This function is not
//! just for interrupt. When Users use ADC without enable the interrupt,
//! users can get the ADC status such as end conversion.
//!
//! \return The current raw or masked interrupt status.
//
//*****************************************************************************
unsigned long
ADCIntStatus(unsigned long ulBase)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Get the ADC_SR register content
    //
    ulStatus = xHWREG(ulBase + ADC_SR);

    //
    // mask interrupt flags
    //
    return (ulStatus & (ADC_INT_END_CONVERSION | 
                        ADC_INT_COMP0 |
                        ADC_INT_COMP1));   

}

//*****************************************************************************
//
//! \brief Clear the ADC interrupt source.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the bit mask of the interrupt sources to clear.
//! Refrence \ref MINI51_ADC_Ints.
//!
//! The specified sample sequence interrupt is cleared, so that it no longer
//! asserts.  This must be done in the interrupt handler to keep it from being
//! called again immediately upon exit.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntClear(unsigned long ulBase, unsigned long ulIntFlags)   
{   
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | 
                             ADC_INT_COMP0 |
                             ADC_INT_COMP1))) == 0);   

    //
    // Write 1 to clear the interrupt
    //
    xHWREG(ulBase + ADC_SR) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Disable the ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Prevents the sample sequence from being captured when its trigger
//! is detected.  The sample sequence should be disabled before it 
//! is configured.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDisable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // A/D Converter Enable
    //
    xHWREG(ulBase + ADC_CR) &= ~ADC_CR_ADEN;
}

//*****************************************************************************
//
//! \brief Cause a processor trigger for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a processor-initiated sample sequence if the sample
//! sequence trigger is configured to \b ADC_TRIGGER_PROCESSOR.  
//!
//! \return None.
//
//*****************************************************************************
void
ADCProcessorTrigger(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_CR) |= ADC_CR_ADST;
}

//*****************************************************************************
//
//! \brief Processor  stop the sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function stop the AD conversion and enter to idle.  
//!
//! \return None.
//
//*****************************************************************************
void
ADCConvertStop(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Stop Conversion
    //
    xHWREG(ulBase + ADC_CR) &= ~ADC_CR_ADST;
}

//*****************************************************************************
//
//! Determines whether the AD converter is busy or not.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Allows the caller to determine whether all conversions have been 
//! completed. 
//!
//! \return Returns \b xtrue if the ADC is busy at conversion or \b false 
//! if all conversions are complete.
//
//*****************************************************************************
xtBoolean
ADCBusy(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Determine if the ADC is busy.
    //
    return ((xHWREG(ulBase + ADC_SR) & ADC_SR_BUSY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get an channel conversion data status.
//!
//! \param ulBase is the base address of the ADC module.
//! \ulChannel is the channel index(0 - 7).
//!
//! Before Get the conversion data, user should get the data status.
//!
//! \return  a logical OR combination of the data status,
//! - \b  ADC_DATA_VALID indicate the conversion is completed.
//! - \b ADC_DATA_OVERRUN indicate an overun occurs.
//! .
//! Refrence \ref MINI51_ADC_Data_Status.
//
//*****************************************************************************
unsigned long
ADCDataStatus(unsigned long ulBase, unsigned long ulChannel)    
{
    unsigned long ulStatus;
    unsigned long ulResult = 0;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulChannel >= 0) && (ulChannel < 8));

    //
    // Get the ADC status register
    //
    ulStatus = xHWREG(ulBase + ADC_SR);

    //
    // Get Valid status
    //
    if((ulStatus >> ADC_SR_VALID_S) & 0x01)
    {
        ulResult |= ADC_DATA_VALID;
    }

    //
    // Get overrun status
    //
    if((ulStatus >> ADC_SR_OVERRUN_S) & 0x01)
    {
        ulResult |= ADC_DATA_OVERRUN;
    }

    return ulResult;
    
}

//*****************************************************************************
//
//! \brief Get the captured data for the ADC sample channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel is the input channel.
//!
//! This function get the ADC sample data of the input channel.
//!
//! \return Returns the sample data.
//
//*****************************************************************************
unsigned long
ADCDataGet(unsigned long ulBase, unsigned long ulChannel)    
{
    unsigned long ulData;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulChannel >= 0) && (ulChannel < 8));

    //
    // Get the ADC_DRx register content
    //
    ulData = xHWREG(ulBase + ADC_DR0 + (ulChannel * 4));
    
    //
    // Single-end analog input mode
    //
    return (ulData & 0xFFF);
}

//*****************************************************************************
//
//! \brief Configure an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the index of the comparator to configure.
//! \param ulCompChannel is the select input channel number of the comparator.
//! \param ulCondition is the compare condition of the comparator.
//! Refrence \ref MINI51_ADC_Comp_Conditions.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompConfigure(unsigned long ulBase, unsigned long ulComp, 
                 unsigned long ulCompChannel, unsigned long ulCondition) 
{
    unsigned long ulCompRegAddr;
    unsigned long ulConfig;
       
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));
    xASSERT((ulCompChannel >= 0) && (ulCompChannel < 8));

    //
    // Get the ADC_CMPRx register address
    //
    ulCompRegAddr = ulBase + ADC_CMPR0 + (4 * ulComp);
    
    //
    // Select the channel and  condition
    //
    ulConfig = (ulCompChannel << ADC_CMPRX_CMPCH_S) | ulCondition;

    //
    // Write the config to the register
    //
    xHWREG(ulCompRegAddr) &= ~(ADC_CMPRX_CMPCH_M | ADC_CMPRX_CMPCOND);
    xHWREG(ulCompRegAddr) |= ulConfig;
}

//*****************************************************************************
//
//! \brief Configure the compare data of an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the index of the comparator to configure.
//! \param usCompData is the compare data.
//! \param ucMatchCnt is the compare match count.
//!
//! This function will configure a comparator data.  When the compare
//! result meets the setting, compare match counter will increase 1, 
//! otherwise, the compare match counter will be clear to 0. When counter
//! value reach the setting of (ucMatchCnt)  then the ADC_INT_COMP0/1 status
//! will be set to 1, if the corresponding interrupt is enabled, and then 
//! interrupt is generated.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompDataSet(unsigned long ulBase, unsigned long ulComp,
               unsigned long ulCompData, unsigned long ulMatchCnt)
{
    unsigned long ulCompRegAddr;
    unsigned long ulConfig;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));
    xASSERT(ulCompData < 0x0400);
    xASSERT(ulMatchCnt < 16);

    //
    // Get the ADC_CMPRx register address
    //
    ulCompRegAddr = ulBase + ADC_CMPR0 + (4 * ulComp);
    
    //
    // Get the config
    //
    ulConfig = ((ulCompData << ADC_CMPRX_CMPD_S) | 
                (ulMatchCnt << ADC_CMPRX_CMPMATCNT_S));


    //
    // Write the config to the ADC_CMPRX register
    //
    xHWREG(ulCompRegAddr) &= ~(ADC_CMPRX_CMPD_M | ADC_CMPRX_CMPMATCNT_M);
    xHWREG(ulCompRegAddr) |= ulConfig;  

}

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the comparator index number(0, 1).
//!
//! Enables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompEnable(unsigned long ulBase, unsigned long ulComp)  
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Enables the corresponding comparator
    //
    xHWREG(ulBase + ADC_CMPR0 + (4 * ulComp)) |= ADC_CMPRX_CMPEN;
}

//*****************************************************************************
//
//! \brief Disable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the comparator index number.
//!
//! Disables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompDisable(unsigned long ulBase, unsigned long ulComp) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Disables the corresponding comparator
    //
    xHWREG(ulBase + ADC_CMPR0 + (4 * ulComp)) &= ~ADC_CMPRX_CMPEN;
}

