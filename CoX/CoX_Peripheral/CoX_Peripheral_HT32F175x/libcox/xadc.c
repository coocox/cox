//*****************************************************************************
//
//! \file xadc.c
//! \brief Driver for the ADC Controller.
//! \version V2.2.1.0
//! \date 5/4/2012
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
    ulIntFlags = xHWREG(ulBase + ADC_IMASK);

    //
    // Clear Int flags
    //
    xHWREG(ulBase + ADC_ICLR) = ulIntFlags;

    //
    // End conversion Interrupt on the sequence
    //
    if(ulIntFlags & ADC_INT_END_CONVERSION)
    {
        ulEventFlags |= ADC_INT_END_CONVERSION;
    }

    //
    // Watchdog Monitor Interrupt on the sequence
    //
    if(ulIntFlags & ADC_INT_MONIU)
    {
        ulEventFlags |= ADC_INT_MONIU;
    }

    //
    // Watchdog Monitor Interrupt on the sequence
    //
    if(ulIntFlags & ADC_INT_MONIL)
    {
        ulEventFlags |= ADC_INT_MONIU;
    }

    if(ulIntFlags & ADC_INT_END_SUBGROUP)
    {
        ulEventFlags |= ADC_INT_END_SUBGROUP;
    }

    if(ulIntFlags & ADC_INT_END_CYCLE)
    {
        ulEventFlags |= ADC_INT_END_CYCLE;
    }

    if(ulIntFlags & ADC_INT_OVERW)
    {
        ulEventFlags |= ADC_INT_OVERW;
    }
    
    if(ulEventFlags && g_pfnADCHandlerCallbacks[0])
    {
        g_pfnADCHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    }
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
//! - ulEvent is the interrupt event.
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

    //
    // Check the arguments
    //
    xASSERT(ulBase == xADC0_BASE);

    xASSERT((ulMode == xADC_MODE_SCAN_SINGLE_CYCLE) ||
            (ulMode == xADC_MODE_SCAN_CONTINUOUS)
           );
    xASSERT((ulTrigger == xADC_TRIGGER_PROCESSOR) || 
            (ulTrigger == xADC_TRIGGER_EXT_PB2)
           );

    //
    // Reset the ADC
    //
    xHWREG(ulBase + ADC_RST) |= ADC_ADCRST_ADRST;
    //
    // Set the Mode
    //
    xHWREG(ulBase + ADC_CONV) &= ~ADC_CONV_MODE_M;
    xHWREG(ulBase + ADC_CONV) |= ulMode;
    //
    // Set the Trigger Source
    //
    xHWREG(ulBase + ADC_TSR) |= ulTrigger;
}

//*****************************************************************************
//
//! \brief Enable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated ADC interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the following:
//!
//! - \b xADC_INT_END_CONVERSION - AD conversion interrupt
//! .
//!
//! \return None.
//
//*****************************************************************************
void xADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == xADC0_BASE);
    xASSERT((ulIntFlags & (~xADC_INT_END_CONVERSION) == 0));

    //
    // Enable A/D Interrupt
    //
    if(ulIntFlags & xADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_IMR) |= xADC_INT_END_CONVERSION;
    }

}

//*****************************************************************************
//
//! \brief Disable ADC sample sequence interrupts.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the interrupt flags.
//!
//! This function disables the requested ADC interrupts.
//!
//! \return None.
//
//*****************************************************************************
void xADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == xADC0_BASE);
    xASSERT((ulIntFlags & (~xADC_INT_END_CONVERSION )) == 0);

    //
    // Disable A/D Interrupt
    //
    if(ulIntFlags & xADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_IMR) &= ~xADC_INT_END_CONVERSION;
    }
}

//*****************************************************************************
//
//! \brief Configure a step of the sample sequencer.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulStep is the step to be configured.
//! \param ulConfig is the configuration of this step; must be a logical OR of
//! \b xADC_CTL_TS,  \b xADC_CTL_END, \b xADC_CTL_D, and one of the input 
//! channel selects (\b xADC_CTL_CH0 through \b xADC_CTL_CH7).  For parts
//! with the digital comparator feature, the follow values may also be OR'd
//! into the \e ulConfig value to enable the digital comparater feature:
//! one of the comparater selects (\b xADC_CTL_CMP0 through xADC_CTL_CMP1). 
//! Refrence \ref xADC_Step_Config.
//!
//! This function will set the configuration of the ADC for one step of a
//! sample sequence.  The ADC can be configured for single-ended or
//! differential operation (the \b xADC_CTL_D bit selects differential
//! operation when set), the channel to be sampled can be chosen (the
//! \b xADC_CTL_CH0 through \b xADC_CTL_CH7 values), and the internal
//! temperature sensor can be selected (the \b xADC_CTL_TS bit).  Additionally,
//! this step can be defined as the last in the sequence (the \b xADC_CTL_END
//! bit) .If the digital comparators are present on the device, this step may
//! also be configured send the ADC sample to the selected comparator
//! (the \b xADC_CTL_CMP0 through \b xADC_CTL_CMP1 values).  The configuration
//! is used by the ADC at the appropriate time when the trigger for this 
//! sequence occurs.
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
    unsigned long ulSeqLen, ulSubLen, ulTrigger;
    //
    // Check the arugments.
    //
    xASSERT(ulBase == xADC0_BASE);

    xASSERT(ulStep >= 0 && ulStep < 8);
    
    //
    // Set the length of A/D Converter Regular Convevsion Sequence.
    //
    xHWREG(ulBase + ADC_CONV) &= ~ADC_CONV_SEQL_M;
    ulSeqLen = ADC_CONV_SEQL_M & ulConfig;
    xHWREG(ulBase + ADC_CONV) |= ((ulSeqLen - 1)<<ADC_CONV_SEQL_S);
    
    //
    // Set the length of Regular Conversion Seugroup Length
    //
    xHWREG(ulBase + ADC_CONV) &= ~ADC_CONV_SUBL_M;
    ulSubLen = ulConfig & ADC_CONV_SUBL_M;
    xHWREG(ulBase + ADC_CONV) |= ((ulSubLen - 1)<<ADC_CONV_SUBL_S);
    
    //
    // Set Trigger Source
    //
    ulTrigger = ulConfig & ADC_TRIGGER_PROCESSOR;
    xHWREG(ulBase + ADC_TSR) |= ulTrigger;
}

//*****************************************************************************
//
//! \brief Get the current interrupt status.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the bit mask of the interrupt sources to clear.
//! Refrence \ref HT32F125x_ADC_Ints.
//!
//! This returns the interrupt status for the ADC module. 
//! Refrence \ref HT32F125x_ADC_Ints. This function is not
//! just for interrupt. When Users use ADC without enable the interrupt,
//! users can get the ADC status such as end conversion.
//!
//! \return The current raw or masked interrupt status.
//
//*****************************************************************************
unsigned long
ADCIntStatus(unsigned long ulBase, unsigned long ulIntFlags)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_END_SUBGROUP | 
                             ADC_INT_END_CYCLE | ADC_INT_MONIU | ADC_INT_MONIL |
                             ADC_INT_OVERW))) == 0);
    //
    // Get the ADC_SR register content
    //
    ulStatus = xHWREG(ulBase + ADC_IRAW) & ulIntFlags;

    //
    // Interrupt flag which indicate the has occured or not.
    //
    return ulStatus;
}
//*****************************************************************************
//
//! \brief Get the captured data from a sample sequence.
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
ADCDataGet(unsigned long ulBase, unsigned long *pulBuffer)
{
    unsigned long i, j;
    unsigned long ulSeqLen,ulChannelNo[16];
    unsigned long ulWrite;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(pulBuffer != 0);

    //
    // Get the  Sequence Length
    //
    ulSeqLen = ((xHWREG(ulBase + ADC_CONV) & ADC_CONV_SEQL_M) >> ADC_CONV_SEQL_S) + 1;

    for(i = 0; i < ulSeqLen; i++)
    {

        ulChannelNo[i] = (xHWREG(ulBase + ADC_LST0 + (i/4)*4) & (0x07<<(8*(i%4))))
                                                                      >> (8*(i%4));
    }

    //
    // Copy data to buffer
    //
    ulWrite = 0;
    for(j = 0; j < ulSeqLen; j++)
    {
        while(!ADCIntStatus(ADC_BASE, ADC_INT_END_CYCLE));
        pulBuffer[ulWrite++] = xHWREG(ulBase + ADC_DR0 + ulChannelNo[j]*4) 
                                                                & ADC_DR0_ADD0_M;
    }
    return ulWrite;
}

//*****************************************************************************
//
//! \brief Set A/D Converter Regular Conversion Sequence Number.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel are Sequence No.n which you will be Converter.
//!
//! This function copies data from the specified sample sequence  FIFO to
//! a memory resident buffer.  The number of samples available in the 
//! FIFO are copied into the buffer, which is assumed to be large enough to
//! hold that many samples.  This will only return the samples that are
//! presently available, which may not be the entire sample sequence if it is
//! in the process of being executed.
//!
//! \return none.
//
//*****************************************************************************
void
ADCSequenceIndexSet(unsigned long ulBase, unsigned long *ulChannel)
{
    unsigned long i, ulSeqLen;
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Get the  Sequence Length
    //
    ulSeqLen = ((xHWREG(ulBase + ADC_CONV) & ADC_CONV_SEQL_M) >> ADC_CONV_SEQL_S) + 1;

    for(i = 0; i < ulSeqLen; i++)
    {
        xHWREG(ulBase + ADC_LST0 + (i/4)*4) |= (ulChannel[i]<<((i%4)*8));
    }

}

//*****************************************************************************
//
//! \brief Configure the ADC.
//!
//! \param ulBase is the base address of the ADC module.
//! Refrence \ref HT32F125x_ADC_Input_Mode.
//! \param ulOpMode is the Operation mode. 
//! Refrence \ref HT32F125x_ADC_Operation_Mode.
//! \param ulTrigger is the trigger source that initiates the sample sequence;
//! must be one of the \b ADC_TRIGGER_* values. 
//! Refrence \ref HT32F125x_ADC_Tigger_Source.
//! 
//! This function configures the initiation criteria for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCConfigure(unsigned long ulBase, unsigned long ulOpMode,
                                   unsigned long ulTrigger)
{
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    xASSERT((ulOpMode == ADC_OP_SINGLE) || 
            (ulOpMode == ADC_OP_CONTINUOUS) ||
            (ulOpMode == ADC_OP_DISCONTINUOUS)
           );
    xASSERT((ulTrigger == ADC_TRIGGER_GPTM0) ||
            (ulTrigger == ADC_TRIGGER_GPTM1) ||
            (ulTrigger == ADC_TRIGGER_MCTM) ||
            (ulTrigger == ADC_TRIGGER_BFTM0) ||
            (ulTrigger == ADC_TRIGGER_BFTM1) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB0) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB1) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB2) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB3) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB4) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB5) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB6) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB7) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB8) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB9) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB10) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB11) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB12) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB13) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB14) ||
            (ulTrigger == ADC_TRIGGER_EXT_PB15) ||
            (ulTrigger == ADC_TRIGGER_PROCESSOR) ||
            (ulTrigger == ADC_TRIGGER_GPTME_MT0) ||
            (ulTrigger == ADC_TRIGGER_GPTME_CH0) ||
            (ulTrigger == ADC_TRIGGER_GPTME_CH1) ||
            (ulTrigger == ADC_TRIGGER_GPTME_CH2) ||
            (ulTrigger == ADC_TRIGGER_GPTME_CH3) ||
           );

    //
    // Set the Mode
    //
    xHWREG(ulBase + ADC_CONV) &= ~ADC_CONV_MODE_M;
    xHWREG(ulBase + ADC_CONV) |= ulOpMode;
    //
    // Set the Trigger Source
    //
    xHWREG(ulBase + ADC_TSR) &= ~(0x01|0xF00|0xF0000|0xF000000);
    xHWREG(ulBase + ADC_TSR) |= ulTrigger;
}



//*****************************************************************************
//
//! \brief Clear the ADC interrupt source.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the bit mask of the interrupt sources to clear.
//! Refrence \ref HT32F125x_ADC_Ints.
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
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_END_SUBGROUP | 
                             ADC_INT_END_CYCLE | ADC_INT_MONIU | ADC_INT_MONIL |
                             ADC_INT_OVERW))) == 0);

    //
    // Write 1 to clear the interrupt
    //
    xHWREG(ulBase + ADC_ICLR) |= ulIntFlags;
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
    xHWREG(ulBase + ADC_TCR) |= ADC_TCR_ADSW_EN;
}

//*****************************************************************************
//
//! \brief Cause a EXTI Event trigger for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a EXTI Eventsample sequence.
//!
//! \return None.
//
//*****************************************************************************
void
ADCExtiEventTrigger(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_TCR) |= ADC_TCR_ADEXTI_EN;
}

//*****************************************************************************
//
//! \brief Cause a GPTM Event trigger for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a GPTM Event sample sequence.
//!
//! \return None.
//
//*****************************************************************************
void
ADCGptmEventTrigger(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_TCR) |= ADC_TCR_ADTM_EN;
}

//*****************************************************************************
//
//! \brief Cause a BFTM Event trigger for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a BFTM Event sample sequence.
//!
//! \return None.
//
//*****************************************************************************
void
ADCBftmEventTrigger(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_TCR) |= ADC_TCR_BFTM_EN;
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
//! - \b  1 indicate the data is  new data is valid.
//! - \b  0 indicate the data is invalid or has been read .
//! .
//
//*****************************************************************************
unsigned long
ADCDataStatus(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulChannel >= 0) && (ulChannel < 8));

    //
    // Get Valid status
    //
    ulStatus = xHWREG(ulBase + ADC_DR0 + ulChannel*4) & ADC_DR0_ADVLD;

    return ulStatus;
}

//*****************************************************************************
//
//! \brief Configure the ADC Watchdog Monitor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the index of the comparator to configure.
//! \param ulThreshold is the threshold value.
//! \param ucMonitor is the channel which will be monitored.
//!
//! \return None.
//
//*****************************************************************************
void
ADCMonitorSet(unsigned long ulBase, unsigned long ulMoniID,
               unsigned long ulThreshold, unsigned long ulMonitor)
{

    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulMoniID >= 0) && (ulMoniID < 2));
    xASSERT(ulThreshold < 0x1000);
    xASSERT((ulMonitor == ADC_MONITOR_ADWALL) ||
            (ulMonitor == ADC_MONITOR_IN0) ||
            (ulMonitor == ADC_MONITOR_IN1) ||
            (ulMonitor == ADC_MONITOR_IN2) ||
            (ulMonitor == ADC_MONITOR_IN3) ||
            (ulMonitor == ADC_MONITOR_IN4) ||
            (ulMonitor == ADC_MONITOR_IN5) ||
            (ulMonitor == ADC_MONITOR_IN6) ||
            (ulMonitor == ADC_MONITOR_IN7));

    if(ulMoniID == ADC_MONI_U)
    {
        xHWREG(ulBase + ADC_UTR) &= ~ ADC_ADCUTR_ADUT_M;
        xHWREG(ulBase + ADC_UTR) |= ulThreshold;
    }
    else
    {
        xHWREG(ulBase + ADC_LTR) &= ~ ADC_ADCLTR_ADLT_M;
        xHWREG(ulBase + ADC_LTR) |= ulThreshold;
    }
    if(ulMonitor == ADC_MONITOR_ADWALL)
    {
        xHWREG(ulBase + ADC_WCR) |= 0x00000004;
    }
    else
    {
        xHWREG(ulBase + ADC_WCR) &= ~ADC_MONITOR_ADWALL;
        xHWREG(ulBase + ADC_WCR) &= ~ADC_WCR_ADWCH_M;
        xHWREG(ulBase + ADC_WCR) |= (ulMonitor<<8);
    }
}

//*****************************************************************************
//
//! \brief Enable the ADC Watchdog monitor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the monitor index number(0, 1).
//!
//! Enables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCMoniEnable(unsigned long ulBase, unsigned long ulMoniID)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulMoniID >= 0) && (ulMoniID < 2));

    //
    // Enables the corresponding comparator
    //
    if(ulMoniID == ADC_MONI_U)
    {
        xHWREG(ulBase + ADC_WCR) |= ADC_WCR_ADWUE;
    }
    else
    {
        xHWREG(ulBase + ADC_WCR) |= ADC_WCR_ADWLE;
    }
}

//*****************************************************************************
//
//! \brief Disable the ADC Watchdog monitor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the monitor index number(0, 1).
//!
//! Disables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCMoniDisable(unsigned long ulBase, unsigned long ulMoniID) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulMoniID >= 0) && (ulMoniID < 2));

    //
    // Disables the corresponding comparator
    //
    if(ulMoniID == ADC_MONI_U)
    {
        xHWREG(ulBase + ADC_WCR) &= ~ADC_WCR_ADWUE;
    }
    else
    {
        xHWREG(ulBase + ADC_WCR) &= ~ADC_WCR_ADWLE;
    }
}

//*****************************************************************************
//
//! ADC Converter Regular Conversion Length set.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulSeqLen is A/D Converter Regular Conversion Sequence Length.
//! \param ulSubLen is A/D Converter Regular Conversion Subgroup Length.
//!
//! ADC Converter Regular Conversion Length set.
//!
//! \return None.
//
//*****************************************************************************
void
ADCConverLenSet(unsigned long ulBase, unsigned long ulSeqLen, unsigned long ulSubLen) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulSeqLen >= 0) && (ulSeqLen < 16));
    xASSERT((ulSubLen >= 0) && (ulSubLen < 16));

    //
    // Set the length of Regular Conversion Sequence Length
    //
    xHWREG(ulBase + ADC_CONV) &= ~ADC_CONV_SEQL_M;
    xHWREG(ulBase + ADC_CONV) |= ((ulSeqLen - 1)<<ADC_CONV_SEQL_S);

    //
    // Set the length of Regular Conversion Seugroup Length
    //
    xHWREG(ulBase + ADC_CONV) &= ~ADC_CONV_SUBL_M;
    xHWREG(ulBase + ADC_CONV) |= ((ulSubLen - 1)<<ADC_CONV_SUBL_S);
}

//*****************************************************************************
//
//! ADC Input Sampling Time Length Set.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel is A/D Channel(0~7).
//! \param ulSampTime is A/D Input Sampling Time Length.
//!
//! Input Sampling Time Length set.
//!
//! \return None.
//
//*****************************************************************************
void
ADCSampLenSet(unsigned long ulBase, unsigned long ulChannel, unsigned long ulSampTime) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulChannel >= 0) && (ulChannel < 7));
    xASSERT((ulSampTime >= 0) && (ulSampTime < 256));

    //
    // Set  Input Sampling Time Length
    //
    xHWREG(ulBase + ADC_STR0 + ulChannel*4) &= ~ADC_STR0_M;
    xHWREG(ulBase + ADC_STR0 + ulChannel*4) |= ulSampTime;
}

//*****************************************************************************
//
//! \brief Enable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated ADC interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b ADC_INT_END_CONVERSION - Interrupt after single cycle conversion
//! - \b ADC_INT_END_SUBGROUP - Interrupt after subgroup conversion
//! - \b ADC_INT_END_CYCLE - Interrupt after cycle conversion
//! - \b ADC_INT_MONIL - Interrupt when the comparator lower
//! - \b ADC_INT_MONIU - Interrupt when the comparator upper
//! - \b ADC_INT_OVERW - Interrupt when data overwrite
//! .
//!
//! \return None.
//
//*****************************************************************************
void ADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_END_SUBGROUP | 
                             ADC_INT_END_CYCLE | ADC_INT_MONIU | ADC_INT_MONIL |
                             ADC_INT_OVERW))) == 0);
    //
    // Enable A/D Interrupt
    //
    if(ulIntFlags & xADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_IMR) |= ADC_INT_END_CONVERSION;
    }
    if(ulIntFlags & ADC_INT_END_SUBGROUP)
    {
        xHWREG(ulBase + ADC_IMR) |= ADC_INT_END_SUBGROUP;
    }
    if(ulIntFlags & ADC_INT_END_CYCLE)
    {
        xHWREG(ulBase + ADC_IMR) |= ADC_INT_END_CYCLE;
    }
    if(ulIntFlags & ADC_INT_MONIU)
    {
        xHWREG(ulBase + ADC_IMR) |= ADC_INT_MONIU;
    }
    if(ulIntFlags & ADC_INT_MONIL)
    {
        xHWREG(ulBase + ADC_IMR) |= ADC_INT_MONIL;
    }
    if(ulIntFlags & ADC_INT_OVERW)
    {
        xHWREG(ulBase + ADC_IMR) |= ADC_INT_OVERW;
    }
}

//*****************************************************************************
//
//! \brief Disable ADC sample sequence interrupts.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the interrupt flags.
//!
//! This function disables the requested ADC interrupts.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b ADC_INT_END_CONVERSION - Interrupt after single cycle conversion
//! - \b ADC_INT_END_SUBGROUP - Interrupt after subgroup conversion
//! - \b ADC_INT_END_CYCLE - Interrupt after cycle conversion
//! - \b ADC_INT_MONIL - Interrupt when the comparator lower
//! - \b ADC_INT_MONIU - Interrupt when the comparator upper
//! - \b ADC_INT_OVERW - Interrupt when data overwrite
//!
//! \return None.
//
//*****************************************************************************
void ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_END_SUBGROUP | 
                             ADC_INT_END_CYCLE | ADC_INT_MONIU | ADC_INT_MONIL |
                             ADC_INT_OVERW))) == 0);

    //
    // Disable A/D Interrupt
    //
    if(ulIntFlags & ADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_IMR) &= ~ADC_INT_END_CONVERSION;
    }
    if(ulIntFlags & ADC_INT_END_SUBGROUP)
    {
        xHWREG(ulBase + ADC_IMR) &= ~ADC_INT_END_SUBGROUP;
    }
    if(ulIntFlags & ADC_INT_END_CYCLE)
    {
        xHWREG(ulBase + ADC_IMR) &= ~ADC_INT_END_CYCLE;
    }
    if(ulIntFlags & ADC_INT_MONIL)
    {
        xHWREG(ulBase + ADC_IMR) &= ~ADC_INT_MONIL;
    }
    if(ulIntFlags & ADC_INT_MONIU)
    {
        xHWREG(ulBase + ADC_IMR) &= ~ADC_INT_MONIU;
    }
    if(ulIntFlags & ADC_INT_OVERW)
    {
        xHWREG(ulBase + ADC_IMR) &= ~ADC_INT_OVERW;
    }
}

//*****************************************************************************
//
//! ADC Reset.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Reset ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCReset(unsigned long ulBase) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Reset ADC
    //
    xHWREG(ulBase + ADC_RST) |= ADC_ADCRST_ADRST;

}

//*****************************************************************************
//
//! \brief Enable ADC DMA.
//!
//! \param ulBase is the base address of the ADC port.
//! \param ulDMAMode is the mode of the ADC DMA.
//!
//! Set DMA mode for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDMAEnable(unsigned long ulBase, unsigned long ulDMAMode)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC_BASE);
    
    xASSERT((ulDMAMode == ADC_DMA_SINGAL) || (ulDMAMode == ADC_DMA_SUBGROUP) ||
            (ulDMAMode == ADC_DMA_CYCLE));

    //
    // Enable DMA mode for ADC
    //
    xHWREG(ulBase + ADC_DMAR) |= ulDMAMode;
}

//*****************************************************************************
//
//! \brief Disable ADC DMA.
//!
//! \param ulBase is the base address of the ADC port.
//! \param ulDMAMode is the mode of the ADC DMA.
//!
//! Disable DMA mode for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDMADisable(unsigned long ulBase, unsigned long ulDMAMode)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC_BASE);
    
    xASSERT((ulDMAMode == ADC_DMA_SINGAL) || (ulDMAMode == ADC_DMA_SUBGROUP) ||
            (ulDMAMode == ADC_DMA_CYCLE));

    //
    // Disable DMA mode for ADC
    //
    xHWREG(ulBase + ADC_DMAR) &= ~ulDMAMode;
}

//*****************************************************************************
//
//! \brief ADC Input Channel Offset Cancellation Enable.
//!
//! \param ulBase is the base address of the ADC port.
//! \param ulChannel is the channel of the ADC.
//!
//! ADC Input Channel Offset Cancellation Enable.
//!
//! \return None.
//
//*****************************************************************************
void
ADCInputOffsetCancEnable(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC_BASE);
    
    xASSERT((ulChannel >= 0) && (ulChannel <= 7));

    //
    // ADC Input Channel Offset Cancellation Enable
    //
    xHWREG(ulBase + ADC_OFR0 + ulChannel*4) |= ADC_ADOF0_EN;
}

//*****************************************************************************
//
//! \brief ADC Input Channel Offset Cancellation Disable.
//!
//! \param ulBase is the base address of the ADC port.
//! \param ulChannel is the channel of the ADC.
//!
//! ADC Input Channel Offset Cancellation Disable.
//!
//! \return None.
//
//*****************************************************************************
void
ADCInputOffsetCancDisable(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC_BASE);
    
    xASSERT((ulChannel >= 0) && (ulChannel <= 7));

    //
    // ADC Input Channel Offset Cancellation Enable
    //
    xHWREG(ulBase + ADC_OFR0 + ulChannel*4) &= ~ADC_ADOF0_EN;
}

//*****************************************************************************
//
//! \brief Get the offset value  from a sample sequence.
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
ADCOffsetDataGet(unsigned long ulBase, unsigned long *pulBuffer)
{
    unsigned long i, j;
    unsigned long ulSeqLen,ulChannelNo[16];
    unsigned long ulWrite;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(pulBuffer != 0);

    //
    // Get the  Sequence Length
    //
    ulSeqLen = ((xHWREG(ulBase + ADC_CONV) & ADC_CONV_SEQL_M) >> ADC_CONV_SEQL_S) + 1;

    for(i = 0; i < ulSeqLen; i++)
    {

        ulChannelNo[i] = (xHWREG(ulBase + ADC_LST0 + (i/4)*4) & (0x07<<(8*(i%4))))
                                                                      >> (8*(i%4));
    }

    //
    // Copy data to buffer
    //
    ulWrite = 0;
    for(j = 0; j < ulSeqLen; j++)
    {
        while(!ADCIntStatus(ADC_BASE, ADC_INT_END_CONVERSION));
        pulBuffer[ulWrite++] = xHWREG(ulBase + ADC_OFR0 + ulChannelNo[j]*4) 
                                                                & ADC_ADOF0_M;
    }
    return ulWrite;
}
