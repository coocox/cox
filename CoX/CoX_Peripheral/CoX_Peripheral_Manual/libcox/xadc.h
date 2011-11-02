//*****************************************************************************
//
//! \file xadc.h
//! \brief Defines and Macros for ADC API.
//! \version 2.0.0.$Rev: 244 $
//! \date 9/30/2011
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

#ifndef __xADC_H__
#define __xADC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Data_Resolution xADC Data Resolution
//! \brief Values that show the ADC Data Resolution (Data Mask, Data Length)
//!
//! @{
//
//*****************************************************************************

//
//! Channel n Data Mask
//

#define xADC_DATA_MASK          0

//
//! Channel n Data Bit Length
//
#define xADC_DATA_BIT_SIZE      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Ints xADC Interrupt Source
//! \brief Values that show the ADC Interrupt source.
//!
//! They can be passed to xADCIntEnable(), 
//! xADCIntDisable() as the ulIntFlags parameter to enable/disable the 
//! corresponding interrupt.
//!
//! \section xADC_Ints_Sec_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+--------+
//! |xADC Interrupt Source   |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xADC_INT_COMP           |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADC_INT_END_CONVERSION |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! \endverbatim
//!    
//! @{
//
//*****************************************************************************

//
//! Interrupt when any of comparators match
//
#define xADC_INT_COMP           0 | 0

//
//! Interrupt after single cycle conversion
//
#define xADC_INT_END_CONVERSION 0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Events xADC Interrupt Event
//! \brief Values that show the interrupt event ID. 
//!
//! Users use the event ID in
//! the interrupt callback function(xtEventCallback) as \b ulEvent parameter to
//! determine what interrupt event occurs. 
//!
//! \section xADC_Events_Sec_Comp_Event 1. Comparators Events in CoX Standard
//! In CoX ADC standard, the macro like \b xADC_EVENT_$COMPx$ show the comparator
//! x interrupt event, x is 0, 1 and so on.
//! Users use the \ref xADC_INT_COMP with xADCIntEnable() to enable all the 
//! comparators interrupt. Then use \b xADC_EVENT_$COMPx$ in the interrupt
//! callback function to determine what comparator match.
//!
//! \section xADC_Events_Sec_Port 2. CoX Port Details
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xADC Event               |       CoX      |     NUC1xx     |
//! |-------------------------|----------------|----------------|
//! |xADC_EVENT_$COMPx$       |  Non-Mandatory |xADC_EVENT_COMP0|
//! |                         |                |xADC_EVENT_COMP1|
//! |-------------------------|----------------|----------------|
//! |xADC_EVENT_END_CONVERSION|    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The comparator match event
//
#define xADC_EVENT_COMP0        0

//
//! The comparator match event
//
#define xADC_EVENT_COMP1        0

//
//! The cycle conversion end event
//
#define xADC_EVENT_END_CONVERSION                                             \
                                0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Mode xADC Operation Mode
//! \brief Values that show the ADC Operation Mode.
//!
//! They can be passed to 
//! xADCConfigure() as the ulMode parameter to configure the ADC.
//!
//! \section xADC_Mode_Sec_Port CoX Port Details
//! \verbatim
//! +---------------------------+----------------+--------+
//! |xADC Mode                  |       CoX      | NUC1xx |
//! |---------------------------|----------------|--------|
//! |xADC_MODE_SCAN_SINGLE_CYCLE|    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xADC_MODE_SCAN_CONTINUOUS  |  Non-Mandatory |    Y   |
//! |---------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************
//
//! \brief Single cycle scan mode.
//!
//! A/D conversion will sample and convert the specified steps once in the
//! sequence, from the first step to the end. Then the A/D converter 
//! enters idle state.
//
#define xADC_MODE_SCAN_SINGLE_CYCLE                                           \
                                0

//
//! \brief Continuous scan mode.
//!
//! A/D conversion will sample and convert the
//! specified steps in the sequence, form the frist step to the end. and then 
//! The A/D converter repeat sample and convert from the first step, 
//! continuous.
//!
//! when the mode is set as continuous scan mode, the ADC will begin sample 
//! after enable the ADC.
//
#define xADC_MODE_SCAN_CONTINUOUS                                             \
                                0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Trigger_Source xADC Trigger Source
//! \brief values that show the ADC trigger source.
//!
//! Can be passed to 
//! xADCConfigure() as the ulTrigger parameter to configure the ADC.
//!
//! \section xADC_Trigger_Source_Sec_Ext 1. External Pin Event In CoX Standard
//! CoX defines macros like \b xADC_TRIGGER_EXT_$ShortPin$, show a trigger   
//! source on an external pin. \b $ShortPin$ is the GPIO short pin Name like 
//! \b PB8.
//!
//! \section xADC_Trigger_Source_Port 2. CoX Port Details
//! \verbatim
//! +---------------------------+----------------+--------------------+
//! |xADC Trigger Source        |       CoX      |       NUC1xx       |
//! |---------------------------|----------------|--------------------|
//! |xADC_TRIGGER_PROCESSOR     |    Mandatory   |          Y         |
//! |---------------------------|----------------|--------------------|
//! |xADC_TRIGGER_EXT_$ShortPin$|  Non-Mandatory |xADC_TRIGGER_EXT_PB8|
//! |---------------------------|----------------|--------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Processor trigger (Software)
//
#define xADC_TRIGGER_PROCESSOR  0

//
//! External Pin Event (such as Rising, Falling...) on PB8
//
#define xADC_TRIGGER_EXT_PB8    0

//
// Others add after these moudles finish
//

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_EXT_Trigger_Mode xADC External Tigger Source Mode
//! \brief Values that show the ADC external trigger source mode.
//!
//! Can be passed 
//! to the ADCConfigure() as the ulTrigger parameter, when the trigger source set
//! as xADC_TRIGGER_EXT_$ShortPin$. The ulTrigger parameter is an OR vaule 
//! with the \ref xADC_Trigger_Source. such as  
//! \ref xADC_TRIGGER_EXT_PB8 | \ref xADC_TRIGGER_EXT_RISING_EDGE.
//!
//! \section xADC_EXT_Trigger_Mode_Sec_Port CoX Port Details
//!
//! \verbatim
//! +-----------------------------+----------------+--------+
//! |xADC Ext Trigger Mode        |       CoX      | NUC1xx |
//! |-----------------------------|----------------|--------|
//! |xADC_TRIGGER_EXT_LOW_LEVEL   |  Non-Mandatory |    Y   |
//! |-----------------------------|----------------|--------|
//! |xADC_TRIGGER_EXT_HIGH_LEVEL  |  Non-Mandatory |    Y   |
//! |-----------------------------|----------------|--------|
//! |xADC_TRIGGER_EXT_RISING_EDGE |  Non-Mandatory |    Y   |
//! |-----------------------------|----------------|--------|
//! |xADC_TRIGGER_EXT_FALLING_EDGE|  Non-Mandatory |    Y   |
//! |-----------------------------|----------------|--------|
//! |xADC_TRIGGER_EXT_BOTH_EDGE   |  Non-Mandatory |    N   |
//! |-----------------------------|----------------|--------|
//! \endverbatim 
//! @{
//
//*****************************************************************************

//
//! EXT Tigger is low level.
//
#define xADC_TRIGGER_EXT_LOW_LEVEL                                       \
                                0

//
//! EXT Tigger is highlevel.
//
#define xADC_TRIGGER_EXT_HIGH_LEVEL                                      \
                                0

//
//! EXT Tigger is rising edge.
//
#define xADC_TRIGGER_EXT_RISING_EDGE                                     \
                                0

//
//! EXT Tigger is falling edge.
//
#define xADC_TRIGGER_EXT_FALLING_EDGE                                    \
                                0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Step_Config xADC Step Config
//! \brief ADC step config values, such as single-end / diffrence, channel source.
//!
//! They are can be passed to the xADCStepConfigure() as the ulConfig parameter.
//! 
//! \section xADC_Step_Config_Sec_Divide xADC Step Config Divide
//! The Step Config value is an logic OR type of the following config:
//! - Channel source select, like \b xADC_CTL_$CHx$, such as \ref xADC_CTL_CH0.  
//! Or \ref xADC_CTL_TS to select the temperature sensor.
//! - Comparator select to monitor the convertion value, like 
//! \b xADC_CTL_$CMPx$, such as \ref xADC_CTL_CMP0.
//! - single-end / diffrence input mode. xADC_CTL_D shows diffrence input mode,
//! and 0 shows single-end mode.
//! - \ref xADC_CTL_END shows this is the end step.
//! .
//! \section xADC_Step_Config_Sec_Port CoX Port Details
//! \verbatim
//! +----------------+----------------+-------------+
//! |xADC Step Config|       CoX      |   NUC1xx    |
//! |----------------|----------------|-------------|
//! |xADC_CTL_CH$x$  |  NonMandatory  |xADC_CTL_CH0 |
//! |                |                |xADC_CTL_CH1 |
//! |                |                |xADC_CTL_CH2 |
//! |                |                |xADC_CTL_CH3 |
//! |                |                |xADC_CTL_CH4 |
//! |                |                |xADC_CTL_CH5 |
//! |                |                |xADC_CTL_CH6 |
//! |                |                |xADC_CTL_CH7 |
//! |----------------|----------------|-------------|
//! |xADC_CTL_TS     |  Non-Mandatory |      Y      |
//! |----------------|----------------|-------------|
//! |xADC_CTL_CMP$x$ |  Non-Mandatory |xADC_CTL_CMP0|
//! |                |                |xADC_CTL_CMP1|
//! |----------------|----------------|-------------|
//! |xADC_CTL_D      |  Non-Mandatory |      Y      |
//! |----------------|----------------|-------------|
//! |xADC_CTL_END    |  Non-Mandatory |      Y      |
//! |----------------|----------------|-------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Temperature sensor select
//
#define xADC_CTL_TS             0

//
//! Sequence end select 
//
#define xADC_CTL_END            0  

//
//! Differential select
//
#define xADC_CTL_D              0  

//
//! Input channel 0
//
#define xADC_CTL_CH0            0  

//
//! Input channel 1
//
#define xADC_CTL_CH1            0  

//
//! Input channel 2
//
#define xADC_CTL_CH2            0 

//
//! Input channel 3
//
#define xADC_CTL_CH3            0

//
//! Input channel 4
//
#define xADC_CTL_CH4            0

//
//! Input channel 5
//
#define xADC_CTL_CH5            0

//
//! Input channel 6
//
#define xADC_CTL_CH6            0

//
//! Input channel 7
//
#define xADC_CTL_CH7            0

//
//! Select Comparator 0
//
#define xADC_CTL_CMP0           0  

//
//! Select Comparator 1
//
#define xADC_CTL_CMP1           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Comparator_IDs xADC Comparator ID
//! \brief IDs/index of the ADC digital comparator.
//!
//! They can be passed to the flowing function as ulComp parameter:
//! - xADCCompConditionConfig(), xADCCompRegionSet() to configure the comparator.
//! - xADCCompEnable(), xADCCompDisable() to enable/disable the comparator.
//! .
//! \section xADC_Comparator_IDs_Port CoX Port Details
//! \verbatim
//! +----------------+----------------+-------------+
//! |xADC Comp ID    |       CoX      |   NUC1xx    |
//! |----------------|----------------|-------------|
//! |xADC_COMP_$x$   |  Non-Mandatory | xADC_COMP_0 |
//! |                |                | xADC_COMP_1 |
//! |----------------|----------------|-------------| 
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Comparator 0
//
#define xADC_COMP_0             0

//
// Comparator 1
//
#define xADC_COMP_1             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Comparator_Int_Condition xADC Comp Interrupt Condition
//! \brief Conditions when the digital comparator generate and interrupt.
//!
//! They can be passed to xADCCompConditionConfig() as the ulConfig parameter to
//! configure the comparator interrupt condition.
//!
//! \section xADC_Comparator_Int_Condition_Port CoX Port Details
//! \verbatim
//! +-------------------------+----------------+---------+
//! |xADC Comp Int Condition  |       CoX      | NUC1xx  |
//! |-------------------------|----------------|---------|
//! |xADC_COMP_INT_LOW        |  Non-Mandatory |    Y    |
//! |-------------------------|----------------|---------| 
//! |xADC_COMP_INT_MID        |  Non-Mandatory |    N    |
//! |-------------------------|----------------|---------| 
//! |xADC_COMP_INT_HIGH       |  Non-Mandatory |    Y    |
//! +-------------------------+----------------+---------+ 
//! \endverbatim
//! 
//! @{
//
//*****************************************************************************

//
//! Always generate ADC interrupt when ADC output is in the low-band.
//
#define xADC_COMP_INT_LOW       0

//
//! Always generate ADC interrupt when ADC output is in the high-band.
//
#define xADC_COMP_INT_HIGH      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Exported_APIs xADC API
//! \brief xADC API Reference
//!
//! \section xADC_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+--------+
//! |xADC API                |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xADCConfigure           |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCStepConfigure       |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCIntCallbackInit     |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCIntEnable           |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCIntDisable          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCDMAEnable           |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xADCDMADisable          |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xADCEnable              |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCDisable             |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCProcessorTrigger    |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCDataGet             |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCOverflow            |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCOverflowClear       |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCCompConditionConfig |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xADCCompRegionSet       |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xADCCompEnable          |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xADCCompDisable         |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configures the mode and trigger source of a sample sequence.
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
extern void xADCConfigure(unsigned long ulBase, unsigned long ulMode, 
                          unsigned long ulTrigger);

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
//! \note If the Digitial Comparator is present and enabled, the ADC sample 
//! will NOT be written into the ADC sequence data register.
//!
//! The \e ulStep parameter determines the order in which the samples are
//! captured by the ADC when the trigger occurs.  It can range from zero to
//! seven for the first sample sequence, from zero to three for the second and
//! third sample sequence, and can only be zero for the fourth sample sequence.
//!
//! Differential mode only works with adjacent channel pairs (for example, 0
//! and 1).  The channel select must be the number of the channel pair to
//! sample (for example, \b ADC_CTL_CH0 for 0 and 1, or \b ADC_CTL_CH1 for 2
//! and 3) or undefined results will be returned by the ADC.  Additionally, if
//! differential mode is selected when the temperature sensor is being sampled,
//! undefined results will be returned by the ADC.
//!
//! It is the responsibility of the caller to ensure that a valid configuration
//! is specified; this function does not check the validity of the specified
//! configuration.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCStepConfigure(unsigned long ulBase, unsigned long ulStep,
                              unsigned long ulConfig);  

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
extern void xADCIntCallbackInit(unsigned long ulBase, 
                                xtEventCallback pfnCallback);

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
//! - \b xADC_INT_END_CONVERSION - AD conversion interrupt
//! - \b xADC_INT_COMP - Comp0 and Comp1 interrupt
//! .
//!
//! \return None.
//
//*****************************************************************************
extern void xADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief Disable ADC sample sequence interrupts.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the interrupt flags.
//!
//! This function disables the requested ADC interrupts.  
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief Enable ADC DMA operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! The specified ADC DMA features are enabled.  The ADC can be
//! configured to use DMA for transmit  AD conversion data.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCDMAEnable(unsigned long ulBase);

//*****************************************************************************
//
//! \brief Disable ADC DMA operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function is used to disable ADC DMA features that were enabled
//! by xADCDMAEnable().  The specified SSI DMA features are disabled. 
//!
//! \return None.
//
//*****************************************************************************
extern void xADCDMADisable(unsigned long ulBase);
        
//*****************************************************************************
//
//! \brief Enable ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Allows the specified sample sequence to be captured when its trigger is
//! detected.  A sample sequence must be configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCEnable(unsigned long ulBase);

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
extern void xADCDisable(unsigned long ulBase);

//*****************************************************************************
//
//! \brief Cause a processor trigger for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a processor-initiated sample sequence if the sample
//! sequence trigger is configured to \b xADC_TRIGGER_PROCESSOR. 
//!
//! \return None.
//
//*****************************************************************************
extern void xADCProcessorTrigger(unsigned long ulBase);

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
extern unsigned long xADCDataGet(unsigned long ulBase, 
                                 unsigned long *pulBuffer);

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
extern xtBoolean xADCOverflow(unsigned long ulBase);

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
extern void xADCOverflowClear(unsigned long ulBase);

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
extern void xADCCompConditionConfig(unsigned long ulBase, 
                                    unsigned long ulCompID, 
                                    unsigned long ulConfig);

//*****************************************************************************
//
//! \brief Define the ADC digital comparator regions.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the ID of the comparator to configure.
//! \param ulLowRef is the reference point for the low/mid band threshold.
//! \param ulHighRef is the reference point for the mid/high band threshold.
//!
//! The ADC digital comparator operation is based on three ADC value regions:
//! - \b low-band is defined as any ADC value less than or equal to the
//! \e ulLowRef value.
//! - \b mid-band is defined as any ADC value greater than the \e ulLowRef
//! value but less than or equal to the \e ulHighRef value.
//! - \b high-band is defined as any ADC value greater than the \e ulHighRef
//! value.
//!.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCCompRegionSet(unsigned long ulBase, unsigned long ulCompID, 
                              unsigned long ulLowRef, unsigned long ulHighRef);
        

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the comparator ID.
//!
//! Enables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCCompEnable(unsigned long ulBase, unsigned long ulCompID);

//*****************************************************************************
//
//! \brief Disable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the comparator ID.
//!
//! Disables the comparator to monitor the along input.
//!
//! \note In the Stellaris Implement, The comparators do note need to enable.
//! Users can switch to use other comparators or not use comparator function.
//!
//! \return None.
//
//*****************************************************************************
extern void xADCCompDisable(unsigned long ulBase, unsigned long ulCompID);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __xADC_H__

