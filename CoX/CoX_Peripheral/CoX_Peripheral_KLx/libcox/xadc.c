//*****************************************************************************
//
//! \file xadc.c
//! \brief Driver for the ADC Controller.
//! \version V2.2.1.0
//! \date 8/15/2011
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
#include "xhw_sysctl.h"
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
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == xADC0_BASE);

    xASSERT((ulMode == xADC_MODE_SCAN_SINGLE_CYCLE) ||
            (ulMode == xADC_MODE_SCAN_CONTINUOUS)
           );
    xASSERT((ulTrigger == xADC_TRIGGER_PROCESSOR) || 
            (ulTrigger == xADC_TRIGGER_EXT_PIN));

    //
    // Set Conversions Mode
    //
    xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC3_ADCO;  
    xHWREG(ulBase + ADC0_SC3) |= ulMode;

    //
    // Set Trigger Mode
    //
    if(ulTrigger == xADC_TRIGGER_EXT_PIN)
    {
        xHWREG(SIM_SOPT7) &= ~SIM_SOPT7_ADC0TRGSEL_M;   
    }
    else
    {
        xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC2_ADTRG_HARD; 
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
//! bit) .  If the digital comparators are present
//! on the device, this step may also be configured send the ADC sample to
//! the selected comparator (the \b xADC_CTL_CMP0 through \b xADC_CTL_CMP7
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

    xASSERT(((ulConfig & xADC_CTL_D) && (ulChannel < 4)) || 
            !(ulConfig & xADC_CTL_D));
    //
    // TS
    //
    xASSERT(ulConfig & xADC_CTL_TS);
    
    xASSERT(ulStep <= ulChannel);

    xASSERT(xHWREG(ulBase + ADC0_SC1A));
    xASSERT(((ulStep > 0) && 
             (xHWREG(ulBase + ADC_CR) & ADC_CR_DIFFEN)
              ) ||
              ((ulConfig & xADC_CTL_D) && 
               (
              (!(ulConfig & xADC_CTL_D) &&  
               !(xHWREG(ulBase + ADC0_SC1A) & ADC0_SC1A_DIFF)
              )
             )
            ) || (ulStep == 0)
           ); 

    //
    // Save the Input mode config (set when the step is 0)
    //
    if(ulStep == 0)
    {
        xHWREG(ulBase + ADC0_SC1A) &= ~ ADC0_SC1A_DIFF;
        if(ulConfig & xADC_CTL_D)
        {
            xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_DIFF;
        }   
    }

    //
    // Input is TS
    //
    if(ulConfig & xADC_CTL_TS)
    {
        xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_ADCH_M;
        xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_ADCH_TEMP_SENSOR;
    }

    //
    // Configure the comp 0
    //
    if(ulConfig & 0x0800)
    {
       xHWREG(ulBase + ADC0_CV1) &= ADC0_CV1_CV_M;  
       xHWREG( ulBase + ADC0_CV1) |= ulConfig;
    }
    
    //
    // Enable the corresponding channle pair in differential mode
    //
    if(ulConfig & xADC_CTL_D)
    {
        xHWREG(ulBase + ADC0_SC1A) |= 1 << (2 * ulChannel); 
    }
    //
    // Enable the corresponding channle pair in single-end mode
    //    
    else
    {
       xHWREG(ulBase + ADC0_SC1A) |= 1 << ulChannel; 
    }
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
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    //
    // Write the config to the register
    //
    xHWREG(ulBase + ADC0_SC2) &= ~(ADC0_SC2_ACREN|ADC0_SC2_ACFGT);
    xHWREG(ulBase + ADC0_SC2) |= ulConfig;

}

//*****************************************************************************
//
//! \brief Init the ADC  Interrupt Callback function.
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
    unsigned long ulEventFlags = 0;

    g_pfnADCHandlerCallbacks[0](0, ulEventFlags, 0, 0);
    
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
//! \return Returns the number of samples copied to the buffer.
//
//*****************************************************************************
unsigned long
xADCDataGet(unsigned long ulBase, unsigned long *pulBuffer)
{
    unsigned long ulValid = 0;
    unsigned long ulWrite;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(pulBuffer != 0);

    //
    // Check if ADC Conversion is complete.
    //
    ulValid = (xHWREG(ulBase + ADC0_SC1A) & ADC0_SC1A_COCO_FLAG) >> 7;

    while(!ulValid);

    //
    // Copy data to buffer
    //
    ulWrite = 0;
    pulBuffer[ulWrite++] = xHWREG(ulBase + ADC0_RA);

    return ulWrite;
}

//*****************************************************************************
//
//! \brief Configure the ADC.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulInputMode is the analog input mode.  
//! Refrence \ref KLx_ADC_Input_Mode.
//! \param ulOpMode is the Operation mode. 
//! Refrence \ref KLx_ADC_Operation_Mode.
//! \param ulTrigger is the trigger source that initiates the sample sequence;
//! must be one of the \b ADC_TRIGGER_* values. 
//! Refrence \ref KLx_ADC_Tigger_Source.
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
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulInputMode == ADC_INPUT_SINGLE) || 
            (ulInputMode == ADC_INPUT_DIFF));
    xASSERT((ulOpMode == ADC_OP_SINGLE) || 
            (ulOpMode == ADC_OP_CONTINUOUS)
           );
    xASSERT((ulTrigger == ADC_TRIGGER_PIT0) ||
            (ulTrigger == ADC_TRIGGER_PIT1) ||
            (ulTrigger == ADC_TRIGGER_TPM0) ||
            (ulTrigger == ADC_TRIGGER_TPM1) ||
            (ulTrigger == ADC_TRIGGER_TPM2) ||
            (ulTrigger == ADC_TRIGGER_LPTMR0) || 
            (ulTrigger == ADC_TRIGGER_HSCMP0) ||
            (ulTrigger == ADC_TRIGGER_EXT_PIN) ||
            (ulTrigger == ADC_TRIGGER_RTC_ALARM) ||
            (ulTrigger == ADC_TRIGGER_PROCESSOR) ||
            (ulTrigger == ADC_TRIGGER_RTC_SECONDS)
           );

    //
    // Set Input Mode
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_DIFF;  
    xHWREG(ulBase + ADC0_SC1A) |= ulInputMode;

    //
    // Set Conversions Mode
    //
    xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC3_ADCO;  
    xHWREG(ulBase + ADC0_SC3) |= ulOpMode;

    //
    // Set Trigger Mode
    //
    if(ulTrigger == ADC_TRIGGER_PROCESSOR)
    {
        xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC2_ADTRG_HARD;   
    }
    else
    {
        xHWREG(SIM_SOPT7) &= ~SIM_SOPT7_ADC0TRGSEL_M;
        xHWREG(SIM_SOPT7) |= ulTrigger;
    } 
    
}
  
//*****************************************************************************
//
//! \brief Configure ADC Temperature Sensor.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulInputMode is the analog input mode.  
//! Refrence \ref KLx_ADC_Input_Mode.
//!
//! This function is to set the ADC Temperature Sensor.
//!
//! \return None.
//
//*****************************************************************************
void
ADCTemperatureSensorConfigure(unsigned long ulBase, unsigned long ulInputMode)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulInputMode == ADC_INPUT_SINGLE) ||
            (ulInputMode == ADC_INPUT_DIFF));

    //
    // Set Input Mode
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_DIFF;  
    xHWREG(ulBase + ADC0_SC1A) |= ulInputMode;

    //
    // Select Temperature Sensor as input.
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_ADCH_M;  
    xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_ADCH_TEMP_SENSOR;
}

//*****************************************************************************
//
//! \brief Configure ADC Bandgap.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulInputMode is the analog input mode.  
//! Refrence \ref KLx_ADC_Input_Mode.
//!
//! This function is to set the ADC Bandgap.
//!
//! \return None.
//
//*****************************************************************************
void
ADCBandgapConfigure(unsigned long ulBase, unsigned long ulInputMode)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulInputMode == ADC_INPUT_SINGLE) ||
            (ulInputMode == ADC_INPUT_DIFF));

    //
    // Set Input Mode
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_DIFF;  
    xHWREG(ulBase + ADC0_SC1A) |= ulInputMode;

    //
    // Select Bandgap as input.
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_ADCH_M;  
    xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_ADCH_BANDGAP;
}

//*****************************************************************************
//
//! \brief ADC Mux Select.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulMux is the alternate sets of ADC channels. 
//! Refrence \ref KLx_ADC_Mux_Select.
//!
//! This function to Select ADC Mux.
//!
//! \return None.
//
//*****************************************************************************
void
ADCMuxSelect(unsigned long ulBase, unsigned long ulMux)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulMux == ADC_MUX_ADC0A) ||
            (ulMux == ADC_MUX_ADC0B));

    //
    // ADxxb channels are selected
    //
    if(ulMux == ADC_MUX_ADC0B)
    {
        xHWREG(ulBase + ADC0_CFG2) |= ADC0_CFG2_MUXSEL;        
    }
    else
    {
        xHWREG(ulBase + ADC0_CFG2) &= ~ADC0_CFG2_MUXSEL;
    }
}

//*****************************************************************************
//
//! \brief ADC conversion speed Select.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulSpeed is Speed Configuration. 
//! Refrence \ref KLx_ADC_Speed_Select.
//!
//! This function to Select ADC conversion speed.
//!
//! \return None.
//
//*****************************************************************************
void
ADCConSpeedSelect(unsigned long ulBase, unsigned long ulSpeed)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulSpeed == ADC_CONVERSION_SPEED_HIGH) ||
            (ulSpeed == ADC_CONVERSION_SPEED_NORMAL));

    //
    // High-speed conversion sequence is selected
    //
    if(ulSpeed == ADC_CONVERSION_SPEED_HIGH)
    {
        xHWREG(ulBase + ADC0_CFG2) |= ADC0_CFG2_ADHSC;        
    }
    else
    {
        xHWREG(ulBase + ADC0_CFG2) &= ~ADC0_CFG2_ADHSC;
    }
}

//*****************************************************************************
//
//! \brief Enable an ADC single-ended channel.
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
ADCSingleEndedChannelEnable(unsigned long ulBase, unsigned long ulChannel)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(ulChannel >= 0 && ulChannel < 24);

    //
    // Enable the corresponding channle
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_DIFF; 
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_ADCH_M;  
    xHWREG(ulBase + ADC0_SC1A) |= ulChannel;
}

//*****************************************************************************
//
//! \brief Enable an ADC differential channel.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel  is the channel that to enable.
//!
//! This function enables an differential analog input channel.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDiffChannelEnable(unsigned long ulBase, unsigned long ulChannel)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT(ulChannel >= 0 && ulChannel <4);

    //
    // Enable the corresponding channle
    //
    xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_DIFF; 
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_ADCH_M;  
    xHWREG(ulBase + ADC0_SC1A) |= ulChannel;
}

//*****************************************************************************
//
//! \brief Enable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//! Refrence \ref KLx_ADC_Ints.
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
    xASSERT((ulIntFlags == ADC_INT_END_CONVERSION)|| 
            (ulIntFlags == ADC_INT_COMP0));

    //
    // Enable AD conversion complete interrupts.
    //
    xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_AIEN;
}

//*****************************************************************************
//
//! \brief Disable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//! Refrence \ref KLx_ADC_Ints.
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
    xASSERT((ulIntFlags == ADC_INT_END_CONVERSION)|| 
            (ulIntFlags == ADC_INT_COMP0));

    //
    // Disable AD conversion complete interrupts.
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_AIEN;
}

//*****************************************************************************
//
//! \brief Get to know Calibration is Failed or completed normally.
//!
//! \param ulBase is the base address of the ADC.
//!
//! Get to know Calibration is Failed or completed normally..
//!
//! \return Returns the xtrue if Calibration is Failed or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
ADCCalibrationIsFailed(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Return Calibration is Failed or not.
    //
    return((xHWREG(ulBase + ADC0_SC3) & ADC0_SC3_CALF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clear the ADC Calibration Failed Flag.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Clear the ADC Calibration Failed Flag
//!
//! \return None.
//
//*****************************************************************************
void
ADCCalibrationFailedFlagClear(unsigned long ulBase)   
{   
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Write 1 to Calibration Failed Flag
    //
    xHWREG(ulBase + ADC0_SC3) |= ADC0_SC3_CALF;
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
    xHWREG(ulBase + ADC0_SC2) &= ~ADC0_SC2_ADTRG_HARD;
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
    xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_ADCH_M;
}

//*****************************************************************************
//
//! \brief Get the captured data for the ADC sample channel.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function get the ADC sample data of the input channel.
//!
//! \return Returns the sample data.
//
//*****************************************************************************
unsigned long
ADCDataGet(unsigned long ulBase)    
{
    unsigned long ulData = 0;
    unsigned long ulValid = 0;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Check if ADC Conversion is complete.
    //
    ulValid = (xHWREG(ulBase + ADC0_SC1A) & ADC0_SC1A_COCO_FLAG) >> 7;

    while(!ulValid);

    //
    // Get data from result register
    //
    ulData = xHWREG(ulBase + ADC0_RA);

    return ulData;
}

//*****************************************************************************
//
//! \brief Get the Offset data for the ADC sample channel.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function get the ADC sample  Offset data of the input channel.
//!
//! \return Returns the Offset data.
//
//*****************************************************************************
unsigned long
ADCOffsetDataGet(unsigned long ulBase)    
{
    unsigned long ulData = 0;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Get Offset data from result register
    //
    ulData = xHWREG(ulBase + ADC0_OFS) & ADC0_OFS_M;

    return ulData;
}

//*****************************************************************************
//
//! \brief Enable ADC Self Calibration.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function enables the self calibration. It needs 127 ADC clocks 
//! to complete the calibration. Users can call ADCCalibrationIsFailed()
//! to check the calibration done status. And the call ADCCalibrationDisable
//! to disable the self Calibration.
//! 
//! \return None.
//
//*****************************************************************************
void
ADCCalibrationEnable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Self Calibration Enable
    //
    xHWREG(ulBase + ADC0_SC3) |= ADC0_SC3_CAL;
}

//*****************************************************************************
//
//! \brief Disable ADC Self Calibration.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function disables  the self calibration. 
//! 
//! \return None.
//
//*****************************************************************************
void
ADCCalibrationDisable(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Self Calibration Disable
    //
    xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC3_CAL;
}

//*****************************************************************************
//
//! \brief Enable ADC Asynchronous Clock Output.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function enables ADC Asynchronous Clock Output.
//! 
//! \return None.
//
//*****************************************************************************
void
ADCAsynClkOutputEnable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // ADC Asynchronous Clock Output Enable
    //
    xHWREG(ulBase + ADC0_CFG2) |= ADC0_CFG2_ADACKEN;
}

//*****************************************************************************
//
//! \brief Disable ADC Asynchronous Clock Output.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function disables ADC Asynchronous Clock Output.
//! 
//! \return None.
//
//*****************************************************************************
void
ADCAsynClkOutputDisable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // ADC Asynchronous Clock Output Disable
    //
    xHWREG(ulBase + ADC0_CFG2) &= ~ADC0_CFG2_ADACKEN;
}

//*****************************************************************************
//
//! \brief Check ADC Self Calibration Done status.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulChannel  is the channel that to enable.
//!
//! It needs some ADC clocks to complete the calibration. Users call this 
//! function to check the self calibration status.
//! 
//! \return Returns \b xtrue if the ADC has completed the calibration or
//! \b xfalse if has not completed.
//
//*****************************************************************************
xtBoolean
ADCCalibrationDone(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Check self calibration status
    //
    return ((xHWREG(ulBase + ADC0_SC3) & ADC0_SC3_CALF) ? xfalse : xtrue);
}

//*****************************************************************************
//
//! \brief Set ADC Voltage Reference.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulRefVol is the Voltage Reference that you will set.
//!
//! Set ADC Voltage Reference.
//!
//! \return None.
//
//*****************************************************************************
void
ADCRefVoltageSet(unsigned long ulBase, unsigned long ulRefVol)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulRefVol == ADC_COMP_REF_VOL_DEFAULT) ||
            (ulRefVol == ADC_COMP_REF_VOL_ALTERNATE));

    //
    // Set ADC Voltage Reference.
    //
    xHWREG(ulBase + ADC0_SC2) &= ~ADC_SC2_REFSEL_M;
    xHWREG(ulBase + ADC0_SC2) |= ulRefVol; 
}


//*****************************************************************************
//
//! \brief Enable ADC Hardware Average operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function is used to enable ADC Hardware Average function.
//!
//! \return None.
//
//*****************************************************************************
void
ADCHardwareAverageEnable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Enable ADC Hardware Average function
    //
    xHWREG(ulBase + ADC0_SC3) |= ADC0_SC3_AVGE;
}

//*****************************************************************************
//
//! \brief Disable ADC Hardware Average operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function is used to Disable ADC Hardware Average function.
//!
//! \return None.
//
//*****************************************************************************
void
ADCHardwareAverageDisable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Disable ADC Hardware Average function
    //
    xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC3_AVGE;
}

//*****************************************************************************
//
//! \brief Set ADC Hardware Average operation.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulAverage is the Hardware Average which you will set.
//!
//! This function is used to Set ADC Hardware Average function.
//!
//! \return None.
//
//*****************************************************************************
void
ADCHardwareAverageSet(unsigned long ulBase, unsigned long ulAverage)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulAverage == ADC_HARDWARE_AVERAGE_4)||
            (ulAverage == ADC_HARDWARE_AVERAGE_8)||
            (ulAverage == ADC_HARDWARE_AVERAGE_16)||
            (ulAverage == ADC_HARDWARE_AVERAGE_32));

    //
    // Set ADC Hardware Average
    //
    xHWREG(ulBase + ADC0_SC3) &= ~ADC0_SC3_AVGS_M;
    xHWREG(ulBase + ADC0_SC3) |= ulAverage;
}

//*****************************************************************************
//
//! \brief Configure the compare data of an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the index of the comparator to configure.
//! \param ulLowRef is the reference point for the low/mid band threshold.
//! \param ulHighRef is the reference point for the mid/high band threshold.
//!
//! \note In KL25Z Series, the ulCompID must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompDataSet(unsigned long ulBase, unsigned long ulCompID,
               unsigned long ulLowRef, unsigned long ulHighRef)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));
    xASSERT(ulLowRef < 0xFFFF);
    xASSERT(ulHighRef < 0xFFFF);

    ulCompID += 0;

    xHWREG(ulBase + ADC0_SC2) |= ADC0_SC2_ACREN; 
    xHWREG(ulBase + ADC0_SC2) |= ADC0_SC2_ACFGT;

    //
    // Write the comparator to the compare register
    //
    xHWREG(ulBase + ADC0_CV1) &= ~ADC0_CV1_CV_M;
    xHWREG(ulBase + ADC0_CV1) |= ulLowRef;
    xHWREG(ulBase + ADC0_CV2) &= ~ADC0_CV2_CV_M;
    xHWREG(ulBase + ADC0_CV2) |= ulHighRef;  

}

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the ID of the comparator to enable.
//!
//! Enables the comparator to monitor the along input.
//!
//! \note In KL25Z Series, the ulCompID must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompEnable(unsigned long ulBase, unsigned long ulCompID)  
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));
    
    ulCompID += 0;
    //
    // Enables the corresponding comparator
    //
    xHWREG(ulBase + ADC0_SC2) |= ADC0_SC2_ACFE;
}

//*****************************************************************************
//
//! \brief Disable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the ID of the comparator to enable.
//!
//! Disables the comparator to monitor the along input.
//!
//! \note In KL25Z Series, the ulCompID must be 0.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompDisable(unsigned long ulBase, unsigned long ulCompID) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulCompID >= 0) && (ulCompID < 2));

    ulCompID += 0;
    //
    // Disables the corresponding comparator
    //
    xHWREG(ulBase + ADC0_SC2) &= ~ADC0_SC2_ACFE;
}

//*****************************************************************************
//
//! \brief Set Compare Function Range.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulRange is the range function
//!
//! Set Compare Function Range.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompFuncRangeSet(unsigned long ulBase, unsigned long ulRange) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulRange == ADC_COMP_RANGE_CV1) ||
            (ulRange == ADC_COMP_RANGE_CV1_CV2));

    //
    // Set Compare Function Range
    //
    xHWREG(ulBase + ADC0_SC2) &= ~ADC0_SC2_ACREN;
    xHWREG(ulBase + ADC0_SC2) |= ulRange;
}

//*****************************************************************************
//
//! \brief Enable ADC DMA.
//!
//! \param ulBase is the base address of the ADC port.
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
    xASSERT(ulBase == ADC_BASE);

    //
    // Enable DMA for ADC
    //
    xHWREG(ulBase + ADC0_SC2) |= ADC0_SC2_DMAEN;
}

//*****************************************************************************
//
//! \brief Disable ADC DMA.
//!
//! \param ulBase is the base address of the ADC port.
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
    xASSERT(ulBase == ADC_BASE);

    //
    // Disable DMA for ADC
    //
    xHWREG(ulBase + ADC0_SC2) &= ~ADC0_SC2_DMAEN;
}

//*****************************************************************************
//
//! \brief ADC Low-Power Configure.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulPowerMode is Low-Power Configuration Mode that you will set. 
//! Refrence \ref KLx_ADC_Power_Mode.
//!
//! This function is to Configure ADC Low-Power Mode.
//!
//! \return None.
//
//*****************************************************************************
void
ADCPowerModeSet(unsigned long ulBase, unsigned long ulPowerMode)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulPowerMode == ADC_POWER_MODE_LOW) ||
            (ulPowerMode == ADC_POWER_MODE_NORMAL));

    //
    // Low-power configuration is selected
    //
    if(ulPowerMode == ADC_POWER_MODE_LOW)
    {
        xHWREG(ulBase + ADC0_CFG1) |= ADC0_CFG1_ADLPC;        
    }
    else
    {
        xHWREG(ulBase + ADC0_CFG1) &= ~ADC0_CFG1_ADLPC;
    }
}

//*****************************************************************************
//
//! \brief ADC Low-Power Configure.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulSampleTime is sample time that you will set. 
//! Refrence \ref KLx_ADC_Sample_Time.
//!
//! This function to Set sample time.
//!
//! \return None.
//
//*****************************************************************************
void
ADCSampleTimeSet(unsigned long ulBase, unsigned long ulSampleTime)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulPowerMode == ADC_SAMPLE_TIME_LONG) ||
            (ulPowerMode == ADC_SAMPLE_TIME_SHORT));

    //
    // Long sample time is selected
    //
    if(ulSampleTime == ADC_SAMPLE_TIME_LONG)
    {
        xHWREG(ulBase + ADC0_CFG1) |= ADC0_CFG1_ADLSMP;        
    }
    else
    {
        xHWREG(ulBase + ADC0_CFG1) &= ~ADC0_CFG1_ADLSMP;
    }
}

//*****************************************************************************
//
//! \brief ADC Gain Set.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulBase is the ADC Minus-Side Gain Value.
//! \param ulBase is the ADC Plus-Side Gain Value.
//!
//! This function to Set ADC Gain.
//!
//! \return None.
//
//*****************************************************************************
void
ADCGainSet(unsigned long ulBase, unsigned long ulMinusGain, 
                                 unsigned long ulPlusGain)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulMinusGain > 0) && (ulMinusGain <= 65535));
    xASSERT((ulPlusGain > 0) && (ulPlusGain <= 65535));

    //
    // Set ADC Gain
    //
    xHWREG(ulBase + ADC0_MG) &= ~ADC0_MG_M;
    xHWREG(ulBase + ADC0_MG) |= ulMinusGain;
    xHWREG(ulBase + ADC0_PG) &= ~ADC0_PG_M;
    xHWREG(ulBase + ADC0_PG) |= ulPlusGain;
}

//*****************************************************************************
//
//! \brief Set ADC Long Sample Time.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulLongSamTime is Long Sample Time which you will set.
//!
//! This function is used to set ADC Long Sample Time.
//!
//! \return None.
//
//*****************************************************************************
void
ADCLongSampleTimeSet(unsigned long ulBase, unsigned long ulLongSamTime)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulLongSamTime == ADC_LONG_SAMPLE_TIME_24)||
            (ulLongSamTime == ADC_LONG_SAMPLE_TIME_16)||
            (ulLongSamTime == ADC_LONG_SAMPLE_TIME_10)||
            (ulLongSamTime == ADC_LONG_SAMPLE_TIME_6));

    //
    // Set ADC Long Sample Time
    //
    xHWREG(ulBase + ADC0_CFG2) &= ~ADC0_CFG2_ADLSTS_M;
    xHWREG(ulBase + ADC0_CFG2) |= ulLongSamTime;
}

//*****************************************************************************
//
//! \brief Set ADC single-ended resolution mode.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulSingleRes is the  single-ended resolution mode that you will set.
//!
//! This function is used to set single-ended resolution mode.
//!
//! \return None.
//
//*****************************************************************************
void
ADCSingleResolutionSet(unsigned long ulBase, unsigned long ulSingleRes)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulSingleRes == ADC_SINGLE_RESOLUTION_8)||
            (ulSingleRes == ADC_SINGLE_RESOLUTION_12)||
            (ulSingleRes == ADC_SINGLE_RESOLUTION_10)||
            (ulSingleRes == ADC_SINGLE_RESOLUTION_16));

    //
    // Set single-ended resolution mode
    //
    xHWREG(ulBase + ADC0_SC1A) &= ~ADC0_SC1A_DIFF; 
    xHWREG(ulBase + ADC0_CFG1) &= ~ADC0_CFG1_MODE_M;
    xHWREG(ulBase + ADC0_CFG1) |= ulSingleRes;
}

//*****************************************************************************
//
//! \brief Set ADC differential resolution mode.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulDiffRes is the  differentialresolution mode that you will set.
//!
//! This function is used to set differential resolution mode.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDifferentialResolutionSet(unsigned long ulBase, unsigned long ulDiffRes)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulDiffRes == ADC_DIFF_RESOLUTION_9)||
            (ulDiffRes == ADC_DIFF_RESOLUTION_13)||
            (ulDiffRes == ADC_DIFF_RESOLUTION_11)||
            (ulDiffRes == ADC_DIFF_RESOLUTION_16));

    //
    // Set differential resolution mode
    //
    xHWREG(ulBase + ADC0_SC1A) |= ADC0_SC1A_DIFF; 
    xHWREG(ulBase + ADC0_CFG1) &= ~ADC0_CFG1_MODE_M;
    xHWREG(ulBase + ADC0_CFG1) |= ulDiffRes;
}

//*****************************************************************************
//
//! \brief Enable ADC0 alternate trigger.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
ADCAlternateTriggerEnable(void)
{
    //
    // Enable ADC0 alternate trigger.
    //
    xHWREG(SIM_SOPT7) |= SIM_SOPT7_ADC0ALTTRGEN;
}

//*****************************************************************************
//
//! \brief Enable TPM1 channel 0(A) and channel 1(B) triggers selected for ADC0.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
ADC0TPMTriggerEnable(void)
{
    //
    // Enable ADC0 TPM1 channel 0(A) and channel 1(B) trigger.
    //
    xHWREG(SIM_SOPT7) &= ~SIM_SOPT7_ADC0ALTTRGEN;
}

//*****************************************************************************
//
//! \brief ADC0 pretrigger select.
//!
//! \param ulPretrigger is pretrigger select that you will set. 
//! Refrence \ref KLx_ADC_Pretrigger_Mode.
//!
//! This function to Set ADC0 pretrigger.
//!
//! \return None.
//
//*****************************************************************************
void
ADC0PretriggerSet(unsigned long ulPretrigger)
{
    //
    // Check the arguments
    //
    xASSERT((ulPretrigger == ADC_PRE_TRIGGER_A) ||
            (ulPretrigger == ADC_PRE_TRIGGER_B));

    //
    // Pretrigger is selected
    //
    if(ulPretrigger == ADC_PRE_TRIGGER_B)
    {
        xHWREG(SIM_SOPT7) |= SIM_SOPT7_ADC0PRETRGSEL;        
    }
    else
    {
        xHWREG(SIM_SOPT7) &= ~SIM_SOPT7_ADC0PRETRGSEL;
    }
}