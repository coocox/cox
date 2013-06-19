//*****************************************************************************
//
//! \file xadc.c
//! \brief Driver for the ADC Controller.
//! \version V2.2.1.0
//! \date 6/1/2012
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
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_config.h"
#include "xhw_types.h"
#include "xhw_adc.h"
#include "xadc.h"
#include "xdebug.h"
#include "xcore.h"

static xtEventCallback g_pfnADCHandlerCallbacks[3] = {0};

//*****************************************************************************
//
//! \brief ADC1 and ADC2 Interrupt Handler.
//!
//! If users want to user the ADC1 Callback feature, Users should promise 
//! that the ADC0 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ADC12IntHandler(void)
{
    unsigned long ulIntFlags = 0;

    //
    // Get Int flags of ADC1
    //
    ulIntFlags = xHWREG(ADC1_BASE + ADC_SR);

    if(ulIntFlags&(ADC_INT_END_CONVERSION|ADC_INT_AWD|ADC_INT_END_JEOC))
    {
    	//
    	// Clear Int flags
    	//
    	xHWREG(ADC1_BASE + ADC_SR) = ~ulIntFlags;
    	if(g_pfnADCHandlerCallbacks[0])
    	{
    	    g_pfnADCHandlerCallbacks[0](0, ulIntFlags, 0, 0);
    	    //return;
    	}
    }
    
    //
    // Get Int flags of ADC2
    //
    ulIntFlags = xHWREG(ADC2_BASE + ADC_SR);
    
    if(ulIntFlags&(ADC_INT_END_CONVERSION|ADC_INT_AWD|ADC_INT_END_JEOC))
    {
    	//
    	// Clear Int flags
    	//
    	xHWREG(ADC1_BASE + ADC_SR) = ~ulIntFlags;
    	if(g_pfnADCHandlerCallbacks[1])
    	{
    	    g_pfnADCHandlerCallbacks[1](0, ulIntFlags, 0, 0);
    	}
    }
}

//*****************************************************************************
//
//! \brief ADC3 Interrupt Handler.
//!
//! If users want to user the ADC3 Callback feature, Users should promise 
//! that the ADC3 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ADC3IntHandler(void)
{
    unsigned long ulBase = ADC2_BASE;
    unsigned long ulIntFlags;
    unsigned long ulEventFlags = 0;

    //
    // Get Int flags
    //
    ulIntFlags = xHWREG(ulBase + ADC_SR);

    //
    // Clear Int flags
    //
    xHWREG(ulBase + ADC_SR) = ~ulIntFlags;
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
    if(ulIntFlags & ADC_INT_AWD)
    {
        ulEventFlags |= ADC_INT_AWD;
    }
    //
    // Interrupt after Injected channel end of conversion
    //    
    if(ulIntFlags & ADC_INT_END_JEOC)
    {
        ulEventFlags |= ADC_INT_END_JEOC;
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
    xASSERT(ulBase == xADC1_BASE || ulBase == xADC2_BASE);

    if(ulBase == xADC1_BASE)
    {
        g_pfnADCHandlerCallbacks[0] = pfnCallback;
    }
    if(ulBase == xADC2_BASE)
    {
        g_pfnADCHandlerCallbacks[1] = pfnCallback;
    }
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
    xASSERT(ulBase == xADC1_BASE || ulBase == xADC2_BASE);

    xASSERT((ulMode == xADC_MODE_SCAN_SINGLE_CYCLE) ||
            (ulMode == xADC_MODE_SCAN_CONTINUOUS)
           );
    xASSERT((ulTrigger == xADC_TRIGGER_PROCESSOR) || 
            (ulTrigger == xADC_TRIGGER_EXT_INT11)             
           );

    //
    // Set the Mode
    //
    if(ulMode == xADC_MODE_SCAN_SINGLE_CYCLE)
    {
        xHWREG(ulBase + ADC_CR1) |= xADC_MODE_SCAN_SINGLE_CYCLE;
    }
    else
    {
        xHWREG(ulBase + ADC_CR2) &= ~xADC_MODE_SCAN_CONTINUOUS; 
        xHWREG(ulBase + ADC_CR2) |= xADC_MODE_SCAN_CONTINUOUS;        
    }
    //
    // Set the Trigger Source
    //
    xHWREG(ulBase + ADC_CR2) &= ~xADC_TRIGGER_PROCESSOR;
    xHWREG(ulBase + ADC_CR2) |= ulTrigger;
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
    xASSERT((ulBase == xADC1_BASE) || (ulBase == xADC2_BASE));
    xASSERT((ulIntFlags & (~xADC_INT_END_CONVERSION) == 0));

    //
    // Enable A/D Interrupt
    //
    if(ulIntFlags & xADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_CR1) |= xADC_INT_END_CONVERSION;
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
        xHWREG(ulBase + ADC_CR1) &= ~xADC_INT_END_CONVERSION;
    }
}

//*****************************************************************************
//
//! \brief Configure a step of the sample sequencer.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulStep is the step to be configured.
//! \param ulConfig is the channel(\b xADC_CTL_CH0 through \b xADC_CTL_CH15,
//! or \b xADC_CTL_TS the internal temperature channel(needs to be enabled in
//! initialize configuration)).
//! Reference \ref xADC_Step_Config.
//!
//! This function will set the configuration of the ADC for one step of a
//! sample sequence. At most, 4 injection group are used for one time ADC.
//!
//! \note It is the responsibility of the caller to ensure that a valid 
//! configuration is specified; this function does not check the validity of 
//! the specified configuration. The step of configure must start from 0
//! and should not jump over a step. The max step is 3.
//!
//! \return None.
//
//*****************************************************************************
void 
xADCStepConfigure(unsigned long ulBase, unsigned long ulStep,
                  unsigned long ulConfig)
{
	unsigned long ulJSQRChannels;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == xADC1_BASE) || (ulBase == xADC2_BASE));

    xASSERT((ulStep >= 0) && (ulStep < 4));

    //
    // make ulConfig a valid channel number
    //
    ulConfig &= 0x1F;
    
    //
    // Clear the length of A/D Converter Regular Conversion Sequence.
    //
    xHWREG(ulBase + ADC_JSQR) &= ~ADC_JSQR_LEN_M;

    //
    // Get Current injection channels
    //
    ulJSQRChannels = xHWREG(ulBase + ADC_JSQR);

    //
    // Clear the unused channel data
    //
    ulJSQRChannels &= (0xFFFFF << ((4-ulStep)*5));

    //
    // Left shift channel data to make room for new channel
    //
    ulJSQRChannels >>= 5;

    //
    // Write new channel data to the highest position
    //
    ulJSQRChannels |= ulConfig << 15;


    //
    // Clear JSQR register.
    //
    xHWREG(ulBase + ADC_JSQR) = 0;

    //
    // Set current JSQR channel data
    //
    xHWREG(ulBase + ADC_JSQR) = ulJSQRChannels;

    //
    // Set convert length
    //
    xHWREG(ulBase + ADC_JSQR) |= (0x03 & ulStep) << ADC_JSQR_LEN_S;

    //
    // Enable auto inject
    //
    xHWREG(ulBase + ADC_CR1) |= ADC_CR1_JAUTO;
}

//*****************************************************************************
//
//! \brief Enable ADC Block to wake up ADC from PowerDown.
//!
//! \param ulBase is the base address of the ADC port.
//!
//!  Enable ADC Block to wake up ADC from PowerDown.
//!
//! \return None.
//
//*****************************************************************************
void
ADCEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Enable ADC
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_ADON;
}

//*****************************************************************************
//
//! \brief Disable ADC Block to put it into PowerDown.
//!
//! \param ulBase is the base address of the ADC port.
//!
//!  Disable ADC Block to put it into PowerDown.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Disable ADC
    //
    xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_ADON;
}

//*****************************************************************************
//
//! \brief Set Dual ADC Mode.
//!
//! \param ulADCDualMode is the mode of the Dual ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDualModeSet(unsigned long ulADCDualMode)
{

    xASSERT((ulADCDualMode == ADC_MODE_REGINJECSIMULT) || 
            (ulADCDualMode == ADC_MODE_REGSIMULT_ALTERTRIG) ||
            (ulADCDualMode == ADC_MODE_INJECSIMULT_FASTINTERL) ||
            (ulADCDualMode == ADC_MODE_INJECSIMULT_SLOWINTERL) ||
            (ulADCDualMode == ADC_MODE_INJECSIMULT) ||
            (ulADCDualMode == ADC_MODE_REGSIMULT) ||
            (ulADCDualMode == ADC_MODE_FASTINTERL) ||
            (ulADCDualMode == ADC_MODE_SLOWINTERL) ||
            (ulADCDualMode == ADC_MODE_ALTERTRIG)
           );

    xHWREG(ADC1_BASE + ADC_CR1) &= ~0x000F0000;
    xHWREG(ADC1_BASE + ADC_CR1) |= ulADCDualMode;

}
//*****************************************************************************
//
//! \brief Get the current interrupt status.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the bit mask of the interrupt sources to clear.
//! Refrence \ref STM32F1xx_ADC_Ints.
//!
//! This returns the interrupt status for the ADC module. 
//! Refrence \ref STM32F1xx_ADC_Ints. This function is not
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
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_END_JEOC | 
                             ADC_INT_AWD))) == 0);
    //
    // Get the ADC_SR register content
    //
    ulStatus = xHWREG(ulBase + ADC_SR) & ulIntFlags;

    //
    // Interrupt flag which indicate the has occurred or not.
    //
    return ulStatus;
}
//*****************************************************************************
//
//! \brief Get the captured data from a sample sequence of regular channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulBase is the mode of the ADC module.
//!
//! \note The Data contains ADC2 conversion values when in dual mode in 16-31 bits
//! of ADC_DR.
//!
//! \return Data from ADC_DR register.
//
//*****************************************************************************
unsigned long
ADCDataRegularGet(unsigned long ulBase, unsigned long ulADCMode)
{
    unsigned long ulReturn = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulADCMode == ADC_MODE_NORMAL) || (ulADCMode == ADC_MODE_DUAL));

    if(ulADCMode == ADC_MODE_NORMAL)
    {
        //
        // Get Data from ADC_DR register
        //
        ulReturn = xHWREG(ulBase + ADC_DR) & ADC_DR_DATA_M;
    }
    else
    {
        //
        // Get Data from ADC_DR register of ADC1
        //
        ulReturn = xHWREG(ADC1_BASE + ADC_DR);
    }
    return ulReturn;
}

//*****************************************************************************
//
//! \brief Get the captured data from a sample sequence of injected channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel is the channel of the ADC module of injected channel.
//!
//! \return Data from ADC_JDRx register
//
//*****************************************************************************
unsigned long
ADCDataInjectedGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulReturn = 0;
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulChannel > 0) || (ulChannel < 5));

    //
    // Get Data from ADC_DR register
    //
    ulReturn = xHWREG(ulBase + ADC_JDR1 + (ulChannel-1)*4);

    return ulReturn;
}

//*****************************************************************************
//
//! \brief Set the mode of ADC data align.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulAlignMode is the mode of the ADC Data Align.
//!
//! \return None
//
//*****************************************************************************
void
ADCDataAlignModeSet(unsigned long ulBase, unsigned long ulAlignMode)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulAlignMode == ADC_ALIGN_RIGHT) || (ulAlignMode < ADC_ALIGN_LEFT));

    if(ulAlignMode == ADC_ALIGN_RIGHT)
    {
        xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_ALIGN_LEFT;
    }
    else
    {
        xHWREG(ulBase + ADC_CR2) |= ADC_CR2_ALIGN_LEFT;        
    }
}
//*****************************************************************************
//
//! Set the Length of ADC Converter Regular and Injected Conversion Sequence.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulSeqRegLen is A/D Converter Regular Conversion Sequence Length.
//! \param ulSeqInjLen is A/D Converter Injected Conversion Sequence Length.
//!
//! ADC Converter Regular Conversion Length set.
//!
//! \return None.
//
//*****************************************************************************
void
ADCConverLenSet(unsigned long ulBase, unsigned long ulSeqRegLen, 
                unsigned long ulSeqInjLen) 
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulSeqRegLen > 0) && (ulSeqRegLen < 17));
    xASSERT((ulSeqInjLen > 0) && (ulSeqInjLen < 5));

    //
    // Set the length of Regular Conversion Sequence Length
    //
    xHWREG(ulBase + ADC_SRQ1) &= ~ADC_SQR1_LEN_M;
    xHWREG(ulBase + ADC_SRQ1) |= ((ulSeqRegLen - 1)<<ADC_SQR1_LEN_S);

    //
    // Set the length of Injected Conversion Sequence Length
    //
    xHWREG(ulBase + ADC_JSQR) &= ~ADC_JSQR_LEN_M;
    xHWREG(ulBase + ADC_JSQR) |= ((ulSeqInjLen - 1)<<ADC_JSQR_LEN_S);
}

//*****************************************************************************
//
//! \brief Set A/D Converter Regular and Injected Conversion Sequence Number.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulpRegChanNo are Regular Sequence No.n which you will be Converter.
//! \param ulpInjectChanNo are Injected Sequence No.n which you will be Converter.
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
ADCSequenceIndexSet(unsigned long ulBase, unsigned long *pulRegChanNo,
                    unsigned long *pulInjectChanNo)
{
    unsigned long i, ulRegSeqLen, ulInjSeqLen;
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Get the Sequence Length
    //
    ulRegSeqLen = ((xHWREG(ulBase + ADC_SRQ1) & ADC_SQR1_LEN_M) >> ADC_SQR1_LEN_S) + 1;
    ulInjSeqLen = ((xHWREG(ulBase + ADC_JSQR) & ADC_JSQR_LEN_M) >> ADC_JSQR_LEN_S) + 1;

    //
    // Set Regular sequence
    //
    for(i = 0; i < ulRegSeqLen; i++)
    {
        xHWREG(ulBase + ADC_SRQ3 - (i/6)*4) |= (pulRegChanNo[i]<<((i%6)*5));
    }

    //
    // Set Injected sequence
    //
    for(i = 0; i < ulInjSeqLen; i++)
    {
        xHWREG(ulBase + ADC_JSQR) |= (pulInjectChanNo[i]<<((4-ulInjSeqLen+i)*5));
    }
}

//*****************************************************************************
//
//! \brief Configure the ADC of Regular channel.
//!
//! \param ulBase is the base address of the ADC module.
//! Refrence \ref STM32F1xx_ADC_Input_Mode.
//! \param ulOpMode is the Operation mode. 
//! Refrence \ref STM32F1xx_ADC_Operation_Mode.
//! \param ulTrigger is the trigger source that initiates the sample sequence;
//! must be one of the \b ADC_TRIGGER_* values. 
//! Refrence \ref STM32F1xx_ADC_Tigger_Source.
//! 
//! This function configures the initiation criteria for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCRegularConfigure(unsigned long ulBase, unsigned long ulOpMode,
                    unsigned long ulTrigger)
{
    
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    xASSERT((ulOpMode == ADC_OP_SCAN) || 
            (ulOpMode == ADC_OP_SINGLE) ||
            (ulOpMode == ADC_OP_CONTINUOUS) ||
            (ulOpMode == ADC_OP_REGULAR_DISCONTINUOUS)
           );
    xASSERT((ulTrigger == ADC_TRIGGER_PROCESSOR) ||
            (ulTrigger == ADC_TRIGGER_EXT_INT11) ||
            (ulTrigger == ADC_TRIGGER_TIME1_CC1) ||
            (ulTrigger == ADC_TRIGGER_TIME1_CC2) ||
            (ulTrigger == ADC_TRIGGER_TIME1_CC3) ||
            (ulTrigger == ADC_TRIGGER_TIME2_CC2) ||
            (ulTrigger == ADC_TRIGGER_TIME4_CC4) ||
            (ulTrigger == ADC_TRIGGER_TIME3_TRGO) ||
            (ulTrigger == ADC_TRIGGER_TIME8_TRGO)
           );

    //
    // Set the Mode
    //
    if((ulOpMode == ADC_OP_SCAN))
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_SCAN;
        xHWREG(ulBase + ADC_CR1) |= ulOpMode;
    }
    else if((ulOpMode == ADC_OP_REGULAR_DISCONTINUOUS))
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_DISCEN;
        xHWREG(ulBase + ADC_CR1) |= ulOpMode;
    }
    else if(ulOpMode == ADC_OP_CONTINUOUS)
    {
        xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_CONT;
        xHWREG(ulBase + ADC_CR2) |= ADC_CR2_CONT;
    }
    else
    {
        xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_CONT;
    }

    //
    // Set the Trigger Source
    //
    xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_EXTSEL_M;
    xHWREG(ulBase + ADC_CR2) |= ulTrigger;
}

//*****************************************************************************
//
//! \brief Configure the ADC of Injected channel.
//!
//! \param ulBase is the base address of the ADC module.
//! Refrence \ref STM32F1xx_ADC_Input_Mode.
//! \param ulOpMode is the Operation mode. 
//! Refrence \ref STM32F1xx_ADC_Operation_Mode.
//! \param ulTrigger is the trigger source that initiates the sample sequence;
//! must be one of the \b ADC_TRIGGER_* values. 
//! Refrence \ref STM32F1xx_ADC_Tigger_Source.
//! 
//! This function configures the initiation criteria for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCInjectedConfigure(unsigned long ulBase,  unsigned long ulOpMode,
                     unsigned long ulTrigger)
{
    
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    xASSERT((ulOpMode == ADC_OP_SCAN) || 
            (ulOpMode == ADC_OP_SINGLE) || 
            (ulOpMode == ADC_OP_CONTINUOUS) || 
            (ulOpMode == ADC_OP_INJECT_DISCONTINUOUS)
           );
    xASSERT((ulTrigger == ADC_TRIGGER_PROCESSORIN) ||
            (ulTrigger == ADC_TRIGGER_EXT_INT15) ||
            (ulTrigger == ADC_TRIGGER_TIME1_TRGO) ||
            (ulTrigger == ADC_TRIGGER_TIME1_CC4) ||
            (ulTrigger == ADC_TRIGGER_TIME2_TRGO) ||
            (ulTrigger == ADC_TRIGGER_TIME2_CC1) ||
            (ulTrigger == ADC_TRIGGER_TIME3_CC4) ||
            (ulTrigger == ADC_TRIGGER_TIME4_TRGO) ||
            (ulTrigger == ADC_TRIGGER_TIME8_TRGO)
           );

    //
    // Set the Mode
    //
    if((ulOpMode == ADC_OP_SCAN))
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_SCAN;
        xHWREG(ulBase + ADC_CR1) |= ulOpMode;
    }
    else if((ulOpMode == ADC_OP_INJECT_DISCONTINUOUS))
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_DISCEN;
        xHWREG(ulBase + ADC_CR1) |= ulOpMode;
    }
    else if(ulOpMode == ADC_OP_CONTINUOUS)
    {
        xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_CONT;
        xHWREG(ulBase + ADC_CR2) |= ADC_CR2_CONT;
    }
    else
    {
        xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_CONT;
    }

    //
    // Set the Trigger Source
    //
    xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_JEXTSEL_M;
    xHWREG(ulBase + ADC_CR2) |= ulTrigger;
}
//*****************************************************************************
//
//! \brief Clear the ADC interrupt source.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the bit mask of the interrupt sources to clear.
//! Refrence \ref STM32F1xx_ADC_Ints.
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
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_END_JEOC | 
                             ADC_INT_AWD))) == 0);

    //
    // Write 0 to clear the interrupt
    //
    xHWREG(ulBase + ADC_SR) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Cause a processor trigger for a sample sequence of Regular channel.
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
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_SWSTART;
}

//*****************************************************************************
//
//! \brief Cause a processor trigger for a sample sequence of Injected channel.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a processor-initiated sample sequence if the sample
//! sequence of Injected channel.
//!
//! \return None.
//
//*****************************************************************************
void
ADCProcessorInjectedTrigger(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_JSWSTART;
}

//*****************************************************************************
//
//! \brief Cause a EXTI Event trigger for a sample sequence of Regualr channel.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a EXTI Eventsample sequence of Regular channel.
//!
//! \return None.
//
//*****************************************************************************
void
ADCExtiEventReguTrigger(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_EXTTRIG;
}

//*****************************************************************************
//
//! \brief Cause a EXTI Event trigger for a sample sequence of Injected channel.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a EXTI Eventsample sequence of Injected channel.
//!
//! \return None.
//
//*****************************************************************************
void
ADCExtiEventInjecTrigger(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Start Conversion
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_JEXTTRIG;
}

//*****************************************************************************
//
//! \brief Configure the ADC Watchdog Monitor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulHighThreshold is the ADC analog watchdog High threshold value.
//! \param ulLowThreshold is ADC analog watchdog Low threshold value.
//! \param ulMoniChannel is the channel which will be monitored.
//!
//! The \e ulMoniChannel parameter is ADC_MONITOR_ADWALL and the logical OR of 
//! values:\b ADC_MONITOR_ADSPEC, \b ADC_MONITOR_IN0, \b ADC_MONITOR_IN1, 
//! \b ADC_MONITOR_IN2, ... ADC_MONITOR_IN17.
//!
//! \return None.
//
//*****************************************************************************
void
ADCMonitorSet(unsigned long ulBase, unsigned long ulHighThreshold,
              unsigned long ulLowThreshold, unsigned long ulMoniChannel)
{

    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT(ulHighThreshold < 0x1000);
    xASSERT(ulLowThreshold < 0x1000);

    //
    // Set ADC analog watchdog High and Low threshold value
    //
    xHWREG(ulBase + ADC_HTR) &= ~ ADC_HTR_M;
    xHWREG(ulBase + ADC_HTR) |= ulHighThreshold;
    xHWREG(ulBase + ADC_LTR) &= ~ ADC_LTR_M;
    xHWREG(ulBase + ADC_LTR) |= ulLowThreshold;
   
    if(ulMoniChannel == ADC_MONITOR_ADWALL)
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_MONITOR_ADSPEC;
    }
    else
    {
        //
        // select the channel which will be monitored. ADC_MONITOR_IN17
        //
        xHWREG(ulBase + ADC_CR1) |= ADC_MONITOR_ADSPEC;
        xHWREG(ulBase + ADC_CR1) &= ~0x0000001F;
        xHWREG(ulBase + ADC_CR1) |= ulMoniChannel;   
    }
}

//*****************************************************************************
//
//! \brief Enable the ADC Watchdog monitor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulBase is the type of the ADC Channel.
//!
//! The \e ulChanType parameter is \b ADC_TYPE_REGULAR, \b ADC_TYPE_INJECTED.
//!
//! Enables the comparator to monitor the analog input.
//!
//! \return None.
//
//*****************************************************************************

void
ADCMoniEnable(unsigned long ulBase, unsigned long ulChanType)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulChanType == ADC_TYPE_REGULAR) || (ulChanType == ADC_TYPE_INJECTED) || 
            (ulChanType == (ADC_TYPE_REGULAR|ADC_TYPE_INJECTED)));

    //
    // Enables the corresponding comparator
    //
    if(ulChanType == ADC_TYPE_REGULAR)
    {
        xHWREG(ulBase + ADC_CR1) |= ADC_TYPE_REGULAR;
    }
    else if(ulChanType == ADC_TYPE_INJECTED)
    {
        xHWREG(ulBase + ADC_CR1) |= ADC_TYPE_INJECTED;
    }
    else
    {
        xHWREG(ulBase + ADC_CR1) |= (ADC_TYPE_REGULAR|ADC_TYPE_INJECTED);
    }
}

//*****************************************************************************
//
//! \brief Disable the ADC Watchdog monitor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulBase is the type of the ADC Channel.
//!
//! The \e ulChanType parameter is \b ADC_TYPE_REGULAR, \b ADC_TYPE_INJECTED.
//!
//! Disables the comparator to monitor the analog input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCMoniDisable(unsigned long ulBase, unsigned long ulChanType) 
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulChanType == ADC_TYPE_REGULAR) || (ulChanType == ADC_TYPE_INJECTED) || 
            (ulChanType == (ADC_TYPE_REGULAR|ADC_TYPE_INJECTED)));

    //
    // Enables the corresponding comparator
    //
    if(ulChanType == ADC_TYPE_REGULAR)
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_TYPE_REGULAR;
    }
    else if(ulChanType == ADC_TYPE_INJECTED)
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_TYPE_INJECTED;
    }
    else
    {
        xHWREG(ulBase + ADC_CR1) &= ~(ADC_TYPE_REGULAR|ADC_TYPE_INJECTED);
    }
}

//*****************************************************************************
//
//! ADC Input Sampling Time Length Set.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel is A/D Channel(0~17).
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
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulChannel >= 0) && (ulChannel < 18));
    xASSERT((ulSampTime == ADC_SAMPTIME_1_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_7_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_13_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_28_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_41_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_55_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_71_5_CYCLE) ||
            (ulSampTime == ADC_SAMPTIME_239_5_CYCLE));

    //
    // Set Sampling Time Length
    //
    xHWREG(ulBase + ADC_SMPR2 - (ulChannel/10)*4) |= (ulSampTime << ((ulChannel%10)*3));
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
//! - \b ADC_INT_END_CONVERSION - Interrupt of end conversion
//! - \b ADC_INT_END_JEOC - Interrupt of Injected channel end of conversion
//! - \b ADC_INT_AWD - Interrupt of Analog watchdog
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
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_AWD | 
                             ADC_INT_END_JEOC))) == 0);
    //
    // Enable A/D Interrupt
    //
    if(ulIntFlags & ADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_CR1) |= ADC_CR1_EOCIE;
    }
    if(ulIntFlags & ADC_INT_END_JEOC)
    {
        xHWREG(ulBase + ADC_CR1) |= ADC_CR1_JEOCIE;
    }
    if(ulIntFlags & ADC_INT_AWD)
    {
        xHWREG(ulBase + ADC_CR1) |= ADC_CR1_AWDIE;
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
//! - \b ADC_INT_END_CONVERSION - Interrupt of end conversion
//! - \b ADC_INT_END_JEOC - Interrupt of Injected channel end of conversion
//! - \b ADC_INT_AWD - Interrupt of Analog watchdog
//!
//! \return None.
//
//*****************************************************************************
void ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulIntFlags & (~(ADC_INT_END_CONVERSION | ADC_INT_AWD | 
                             ADC_INT_END_JEOC))) == 0);

    //
    // Disable A/D Interrupt
    //
    if(ulIntFlags & ADC_INT_END_CONVERSION)
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_EOCIE;
    }
    if(ulIntFlags & ADC_INT_END_JEOC)
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_JEOCIE;
    }
    if(ulIntFlags & ADC_INT_AWD)
    {
        xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_AWDIE;
    }
}

//*****************************************************************************
//
//! \brief Enable ADC DMA.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Set DMA mode for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDMAEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Enable DMA mode for ADC
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_DMA_EN;
}

//*****************************************************************************
//
//! \brief Disable ADC DMA.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Disable DMA mode for the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDMADisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Disable DMA mode for ADC
    //
    xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_DMA_EN;
}

//*****************************************************************************
//
//! \brief Enable Automatic Injected conversion.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Enable Automatic Injected conversion.
//!
//! \return None.
//
//*****************************************************************************
void
ADCAutoInjectedEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Enable Automatic Injected conversion
    //
    xHWREG(ulBase + ADC_CR1) |= ADC_CR1_JAUTO;
}

//*****************************************************************************
//
//! \brief Disable Automatic Injected conversion.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Disable Automatic Injected conversion.
//!
//! \return None.
//
//*****************************************************************************
void
ADCAutoInjectedDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    //
    // Disable Automatic Injected conversion
    //
    xHWREG(ulBase + ADC_CR1) &= ~ADC_CR1_JAUTO;
}
//*****************************************************************************
//
//! \brief Get the offset value  from a sample sequence if Injected Channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel is the Injected channel number.
//!
//! \return the offset value of Injected channel
//
//*****************************************************************************
unsigned long
ADCInjectedOffsetDataGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulReturn;
    
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    xASSERT((ulChannel > 0) || (ulChannel < 5));

    //
    // Get the offset value of Injected channel
    //
    ulReturn = (xHWREG(ulBase + ADC_JOFR1 + (ulChannel-1)*4) & ADC_JOFR1_M);

    return ulReturn;
}

//*****************************************************************************
//
//! \brief Reset ADC Calibration.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Reset ADC Calibration.
//!
//! \return None.
//
//*****************************************************************************
void ADCCalibrationReset(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    
    //
    // Reset ADC Calibration
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_RSTCAL;
}

//*****************************************************************************
//
//! \brief Get ADC Calibration Reset completed status.
//!
//! \param ulBase is the base address of the ADC port.
//!
//!  Get ADC Calibration completed status.
//!
//! \return Returns the completed status of ADC Calibration Reset.
//! \b xtrue ADC Reset completed ,or \b xfalse ADC Reset not completed.
//
//*****************************************************************************
xtBoolean ADCCalibrationResetStatusGet(unsigned long ulBase)
{
    
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    
    return ((xHWREG(ulBase + ADC_CR2) & ADC_CR2_RSTCAL) ? xfalse : xtrue);
}

//*****************************************************************************
//
//! \brief Start ADC Calibration.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Start ADC Calibration.
//!
//! \return None.
//
//*****************************************************************************
void ADCCalibrationStart(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));
    
    //
    // Start ADC Calibration
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_CAL_EN;
}

//*****************************************************************************
//
//! \brief Get ADC Calibration Start completed status.
//!
//! \param ulBase is the base address of the ADC port.
//!
//!  Get ADC Calibration completed status.
//!
//! \return Returns the completed status of ADC Calibration Start.
//! \b xtrue ADC Start completed ,or \b xfalse ADC Start not completed.
//
//*****************************************************************************
xtBoolean ADCCalibrationStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE) || (ulBase == ADC3_BASE));

    return ((xHWREG(ulBase + ADC_CR2) & ADC_CR2_RSTCAL) ? xfalse : xtrue);
}

//*****************************************************************************
//
//! \brief Enable temperature sensor and Internal Voltage Reference.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Enable temperature sensor and  Internal Voltage Reference.
//!
//! \return None.
//
//*****************************************************************************
void
ADCTemperatureRefVolEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC1_BASE);

    //
    //  Enable temperature sensor and Internal Voltage Reference
    //
    xHWREG(ulBase + ADC_CR2) |= ADC_CR2_TSVREFE;
}

//*****************************************************************************
//
//! \brief Disable temperature sensor and Internal Voltage Reference.
//!
//! \param ulBase is the base address of the ADC port.
//!
//! Disable temperature sensor and  Internal Voltage Reference.
//!
//! \return None.
//
//*****************************************************************************
void
ADCTemperatureRefVolDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC1_BASE);

    //
    //  Enable temperature sensor and Internal Voltage Reference
    //
    xHWREG(ulBase + ADC_CR2) &= ~ADC_CR2_TSVREFE;
}

unsigned long xADCDataGet(unsigned long ulBase, unsigned long *pulBuffer)
{
	unsigned char ucChannels = 0;
	unsigned char ucValidInjectChannels = 1;

	xASSERT((ulBase == ADC1_BASE) || (ulBase == ADC2_BASE));

	ucValidInjectChannels = 1 + ((xHWREG(ulBase + ADC_JSQR) & ADC_JSQR_LEN_M) >> ADC_JSQR_LEN_S);

	while(ucChannels < ucValidInjectChannels)
	{
		pulBuffer[ucChannels] = xHWREG(ulBase + ADC_JDR1 + ucChannels*4);
		ucChannels++;
	}
	return ((unsigned long)ucValidInjectChannels);
}
