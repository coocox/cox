//*****************************************************************************
//
//! \file xadc.h
//! \brief Defines and Macros for ADC API.
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
//! \addtogroup COX_Peripheral_Lib
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
//! \addtogroup xADC_Config xADC Config
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Ints xADC Interrupt Source
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
//! Interrupt when the comparator match
//
#define xADC_INT_COMP           0x00000001

//
//! Interrupt after single cycle conversion
//
#define xADC_INT_END_CONVERSION 0x00000100

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
#define xADC_EVENT_COMP0        0x00000001

//
//! The comparator match event
//
#define xADC_EVENT_COMP1        0x00000002

//
//! The comparator match event
//
#define xADC_EVENT_COMP2        0x00000004

//
//! The comparator match event
//
#define xADC_EVENT_COMP3        0x00000008

//
//! The comparator match event
//
#define xADC_EVENT_COMP4        0x00000010

//
//! The comparator match event
//
#define xADC_EVENT_COMP5        0x00000020

//
//! The comparator match event
//
#define xADC_EVENT_COMP6        0x00000040

//
//! The comparator match event
//
#define xADC_EVENT_COMP7        0x00000080

//
//! The single cycle conversion end event
//
#define xADC_EVENT_END_CONVERSION                                             \
                                xADC_INT_END_CONVERSION

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Mode xADC Operation Mode
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
//! Single cycle scan mode, A/D conversion will sample and convert the 
//! specified steps once in the sequence, from the first step to the end. 
//! Then the A/D converter enters idle state.
//
#define xADC_MODE_SCAN_SINGLE_CYCLE                                           \
                                0x00000000

//
//! Continuous scan mode, A/D conversion will sample and convert the
//! specified steps in the sequence, form the frist step to the end. and then 
//! The A/D converter repeat sample and convert from the first step, 
//! continuous.
//!
//! when the mode is set as continuous scan mode, the ADC will begin sample 
//! after enable the ADC.
//
#define xADC_MODE_SCAN_CONTINUOUS                                             \
                                0x0000000F
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Trigger_Source xADC Trigger Source
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
//! Processor event(Software)
//
#define xADC_TRIGGER_PROCESSOR  0x00000000

//
//! External event
//
#define xADC_TRIGGER_EXT_PB4    0x00000004

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
//!
//! Can be passed to the ADCConfigure() as the ulTrigger parameter, 
//! when the trigger source set
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
#define xADC_TRIGGER_EXT_MODE_LOW_LEVEL                                       \
                                0x00000000

//
//! EXT Tigger is high level.
//
#define xADC_TRIGGER_EXT_MODE_HIGH_LEVEL                                      \
                                0x00000000

//
//! EXT Tigger is rising edge.
//
#define xADC_TRIGGER_EXT_MODE_RISING_EDGE                                     \
                                0x00000000

//
//! EXT Tigger is falling edge.
//
#define xADC_TRIGGER_EXT_MODE_FALLING_EDGE                                    \
                                0x00000000


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
#define xADC_CTL_TS             0x00000080

//
//! Sequence end select 
//
#define xADC_CTL_END            0x00000020  

//
//! Differential select
//
#define xADC_CTL_D              0x00000010  


//
//! Input channel 0
//
#define xADC_CTL_CH0            0x00000000  

//
//! Input channel 1
//
#define xADC_CTL_CH1            0x00000001  

//
//! Input channel 2
//
#define xADC_CTL_CH2            0x00000002 

//
//! Input channel 3
//
#define xADC_CTL_CH3            0x00000003

//
//! Input channel 4
//
#define xADC_CTL_CH4            0x00000004

//
//! Input channel 5
//
#define xADC_CTL_CH5            0x00000005

//
//! Input channel 6
//
#define xADC_CTL_CH6            0x00000006

//
//! Input channel 7
//
#define xADC_CTL_CH7            0x00000007

//
//! Input channel 8
//
#define xADC_CTL_CH8            0x00000008

//
//! Input channel 9
//
#define xADC_CTL_CH9            0x00000009

//
//! Input channel 10
//
#define xADC_CTL_CH10           0x0000000A

//
//! Input channel 11
//
#define xADC_CTL_CH11           0x0000000B

//
//! Input channel 12
//
#define xADC_CTL_CH12           0x0000000C

//
//! Input channel 13
//
#define xADC_CTL_CH13           0x0000000D

//
//! Input channel 14
//
#define xADC_CTL_CH14           0x0000000E

//
//! Input channel 15
//
#define xADC_CTL_CH15           0x0000000F

//
//! Select Comparator 0
//
#define xADC_CTL_CMP0           0x00080000  

//
//! Select Comparator 1
//
#define xADC_CTL_CMP1           0x00090000

//
//! Select Comparator 2
//
#define xADC_CTL_CMP2           0x000A0000

//
//! Select Comparator 3
//
#define xADC_CTL_CMP3           0x000B0000

//
//! Select Comparator 4
//
#define xADC_CTL_CMP4           0x000C0000

//
//! Select Comparator 5
//
#define xADC_CTL_CMP5           0x000D0000

//
//! Select Comparator 6
//
#define xADC_CTL_CMP6           0x000E0000

//
//! Select Comparator 7
//
#define xADC_CTL_CMP7           0x000F0000

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
#define xADC_COMP_0             0x00000000

//
// Comparator 1
//
#define xADC_COMP_1             0x00000001

//
// Comparator 2
//
#define xADC_COMP_2             0x00000002

//
// Comparator 3
//
#define xADC_COMP_3             0x00000003

//
// Comparator 4
//
#define xADC_COMP_4             0x00000004

//
// Comparator 5
//
#define xADC_COMP_5             0x00000005

//
// Comparator 6
//
#define xADC_COMP_6             0x00000006

//
// Comparator 7
//
#define xADC_COMP_7             0x00000007

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
//! @{
//
//*****************************************************************************

//
//! Never generate ADC interrupt.
//
#define xADC_COMP_INT_NONE      ADC_COMP_INT_NONE

//
//! Always generate ADC interrupt when ADC output is in the low-band.
//
#define xADC_COMP_INT_LOW       ADC_COMP_INT_LOW_ALWAYS

//
//! Always generate ADC interrupt when ADC output is in the mid-band.
//
#define xADC_COMP_INT_MID       ADC_COMP_INT_MID_ALWAYS

//
//! Always generate ADC interrupt when ADC output is in the high-band.
//
#define xADC_COMP_INT_HIGH      ADC_COMP_INT_HIGH_ALWAYS

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Reference_Source
//! @{
//
//*****************************************************************************

//
//! Internal reference
//
#define xADC_REF_INT_3V          ADC_REF_INT  

//
//! External 3V reference(EXT_##V)
//
#define xADC_REF_EXT_3V         ADC_REF_EXT_3V

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Exported_APIs
//! @{
//
//*****************************************************************************
extern void xADCConfigure(unsigned long ulBase, unsigned long ulMode, 
                          unsigned long ulTrigger);

extern void xADCStepConfigure(unsigned long ulBase, unsigned long ulStep,
                              unsigned long ulConfig);

extern void xADCIntCallbackInit(unsigned long ulBase, 
                                xtEventCallback pfnCallback);
extern void xADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void xADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief Enables ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Allows the specified sample sequence to be captured when its trigger is
//! detected.  A sample sequence must be configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
#define xADCEnable(ulBase)                                                    \
        ADCSequenceEnable(ulBase, xADC_CONFIG_STELLARIS_SEQUENCE_USE)

//*****************************************************************************
//
//! \brief Disables the ADC sample sequence.
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
#define xADCDisable(ulBase)                                                   \
        ADCSequenceDisable(ulBase, xADC_CONFIG_STELLARIS_SEQUENCE_USE)

//*****************************************************************************
//
//! \brief Causes a processor trigger for a sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function triggers a processor-initiated sample sequence if the sample
//! sequence trigger is configured to \b xADC_TRIGGER_PROCESSOR. 
//!
//! \return None.
//
//*****************************************************************************
#define xADCProcessorTrigger(ulBase)                                          \
        ADCProcessorTrigger(ulBase, xADC_CONFIG_STELLARIS_SEQUENCE_USE)

//*****************************************************************************
//
//! \brief Determines if the ADC sample sequence overflow occurred.
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
#define xADCOverflow(ulBase)                                                  \
        ADCSequenceOverflow(ulBase, xADC_CONFIG_STELLARIS_SEQUENCE_USE)

//*****************************************************************************
//
//! \brief Clears the overflow condition on the ADC sample sequence.
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
#define xADCOverflowClear(ulBase)                                             \
        ADCSequenceOverflowClear(ulBase, xADC_CONFIG_STELLARIS_SEQUENCE_USE)

//*****************************************************************************
//
//! \brief Gets the captured data for the ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//! \param pulBuffer is the address where the data is stored.
//!
//! This function copies data from the specified sample sequence output FIFO to
//! a memory resident buffer.  The number of samples available in the hardware
//! FIFO are copied into the buffer, which is assumed to be large enough to
//! hold that many samples.  This will only return the samples that are
//! presently available, which may not be the entire sample sequence if it is
//! in the process of being executed.
//!
//! \return Returns the number of samples copied to the buffer(long type).
//
//*****************************************************************************
#define xADCDataGet(ulBase, pulBuffer)                                        \
        ADCSequenceDataGet(ulBase, xADC_CONFIG_STELLARIS_SEQUENCE_USE,        \
                           pulBuffer)
                           
//*****************************************************************************
//
//! \brief Configures an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the ID of the comparator to configure.
//! \param ulConfig is the configuration of the comparator.
//!
//! This function will configure a comparator.  The \e ulConfig parameter is
//! the result of xADC_COMP_INT_xxx value.
//!
//! The \b xADC_COMP_INT_xxx term can take on the following values:
//!
//! - \b xADC_COMP_INT_NONE to never generate ADC interrupt.
//! - \b xADC_COMP_INT_LOW_ALWAYS to always generate ADC interrupt when ADC
//! output is in the low-band.
//! - \b xADC_COMP_INT_MID_ALWAYS to always generate ADC interrupt when ADC
//! output is in the mid-band.
//! - \b xADC_COMP_INT_HIGH_ALWAYS to always generate ADC interrupt when ADC
//! output is in the high-band.
//!.
//!
//! \return None.
//
//*****************************************************************************
#define xADCCompConditionConfig(ulBase, ulCompID, ulConfig)                   \
        ADCComparatorConfigure(ulBase, ulCompID, ulConfig) 

//*****************************************************************************
//
//! \brief Defines the ADC digital comparator regions.
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
#define xADCCompRegionSet(ulBase, ulCompID, ulLowRef, ulHighRef)              \
        ADCComparatorRegionSet(ulBase, ulCompID, ulLowRef, ulHighRef)

//*****************************************************************************
//
//! \brief Enables the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the comparator ID.
//!
//! Enables the comparator to monitor the along input.
//!
//! \note In the Stellaris Implement, this function just reset the comparator interrupt
//! flags. The comparators do note need to enable.
//!
//! \return None.
//
//*****************************************************************************
#define xADCCompEnable(ulBase, ulCompID)                                      \
        ADCComparatorReset(ulBase, ulCompID, xtrue, xtrue)

//*****************************************************************************
//
//! \brief Disables the ADC digital comparator .
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
#define xADCCompDisable(ulBase, ulCompID)

//*****************************************************************************
//
//! \brief Selects the ADC reference.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulRef is the reference to use.
//!
//! The ADC reference is set as specified by \e ulRef.  The value can be 
//! xADC_REF_INT_xV or xADC_REF_EXT_xV. such as:
//! - \b xADC_REF_INT_3V - an internal 3V reference is used.
//! - \b xADC_REF_EXT_3V -a 3V reference must be supplied to the AVREF pin.
//! .
//!
//! \note The ADC reference can only be selected on parts that have an external
//! reference.  Consult the data sheet for your part to determine if there is
//! an external reference.
//!
//! \return None.
//
//*****************************************************************************
#define xADCReferenceSet(ulBase, ulRef)                                       \
        ADCReferenceSet(ulBase, ulRef)

//*****************************************************************************
//
//! \brief Returns the current setting of the ADC reference.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Returns the value of the ADC reference setting.  The returned value will be
//! one of \b ADC_REF_INT_xV or \b ADC_REF_EXT_xV. refrence 
//! \ref xADC_Reference_Source.
//!
//! \note The value returned by this function is only meaningful if used on a
//! part that is capable of using an external reference.  Consult the data
//! sheet for your part to determine if it has an external reference input.
//!
//! \return The current setting of the ADC reference.
//
//*****************************************************************************
#define xADCReferenceGet(ulBase)                                              \
        ADCReferenceGet(ulBase)
    
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
//! \addtogroup Stellaris_ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Values that can be passed to ADCSequenceConfigure as the ulTrigger
// parameter.
//
//*****************************************************************************
#define ADC_TRIGGER_PROCESSOR   0x00000000  // Processor event
#define ADC_TRIGGER_COMP0       0x00000001  // Analog comparator 0 event
#define ADC_TRIGGER_COMP1       0x00000002  // Analog comparator 1 event
#define ADC_TRIGGER_COMP2       0x00000003  // Analog comparator 2 event
#define ADC_TRIGGER_EXTERNAL    0x00000004  // External event
#define ADC_TRIGGER_TIMER       0x00000005  // Timer event
#define ADC_TRIGGER_PWM0        0x00000006  // PWM0 event
#define ADC_TRIGGER_PWM1        0x00000007  // PWM1 event
#define ADC_TRIGGER_PWM2        0x00000008  // PWM2 event
#define ADC_TRIGGER_PWM3        0x00000009  // PWM3 event
#define ADC_TRIGGER_ALWAYS      0x0000000F  // Always event

//*****************************************************************************
//
// Values that can be passed to ADCSequenceStepConfigure as the ulConfig
// parameter.
//
//*****************************************************************************
#define ADC_CTL_TS              0x00000080  // Temperature sensor select
#define ADC_CTL_IE              0x00000040  // Interrupt enable
#define ADC_CTL_END             0x00000020  // Sequence end select
#define ADC_CTL_D               0x00000010  // Differential select
#define ADC_CTL_CH0             0x00000000  // Input channel 0
#define ADC_CTL_CH1             0x00000001  // Input channel 1
#define ADC_CTL_CH2             0x00000002  // Input channel 2
#define ADC_CTL_CH3             0x00000003  // Input channel 3
#define ADC_CTL_CH4             0x00000004  // Input channel 4
#define ADC_CTL_CH5             0x00000005  // Input channel 5
#define ADC_CTL_CH6             0x00000006  // Input channel 6
#define ADC_CTL_CH7             0x00000007  // Input channel 7
#define ADC_CTL_CH8             0x00000008  // Input channel 8
#define ADC_CTL_CH9             0x00000009  // Input channel 9
#define ADC_CTL_CH10            0x0000000A  // Input channel 10
#define ADC_CTL_CH11            0x0000000B  // Input channel 11
#define ADC_CTL_CH12            0x0000000C  // Input channel 12
#define ADC_CTL_CH13            0x0000000D  // Input channel 13
#define ADC_CTL_CH14            0x0000000E  // Input channel 14
#define ADC_CTL_CH15            0x0000000F  // Input channel 15
#define ADC_CTL_CMP0            0x00080000  // Select Comparator 0
#define ADC_CTL_CMP1            0x00090000  // Select Comparator 1
#define ADC_CTL_CMP2            0x000A0000  // Select Comparator 2
#define ADC_CTL_CMP3            0x000B0000  // Select Comparator 3
#define ADC_CTL_CMP4            0x000C0000  // Select Comparator 4
#define ADC_CTL_CMP5            0x000D0000  // Select Comparator 5
#define ADC_CTL_CMP6            0x000E0000  // Select Comparator 6
#define ADC_CTL_CMP7            0x000F0000  // Select Comparator 7

//*****************************************************************************
//
// Values that can be passed to ADCComparatorConfigure as part of the
// ulConfig parameter.
//
//*****************************************************************************
#define ADC_COMP_TRIG_NONE      0x00000000  // Trigger Disabled
#define ADC_COMP_TRIG_LOW_ALWAYS \
                                0x00001000  // Trigger Low Always
#define ADC_COMP_TRIG_LOW_ONCE  0x00001100  // Trigger Low Once
#define ADC_COMP_TRIG_LOW_HALWAYS \
                                0x00001200  // Trigger Low Always (Hysteresis)
#define ADC_COMP_TRIG_LOW_HONCE 0x00001300  // Trigger Low Once (Hysteresis)
#define ADC_COMP_TRIG_MID_ALWAYS \
                                0x00001400  // Trigger Mid Always
#define ADC_COMP_TRIG_MID_ONCE  0x00001500  // Trigger Mid Once
#define ADC_COMP_TRIG_HIGH_ALWAYS \
                                0x00001C00  // Trigger High Always
#define ADC_COMP_TRIG_HIGH_ONCE 0x00001D00  // Trigger High Once
#define ADC_COMP_TRIG_HIGH_HALWAYS \
                                0x00001E00  // Trigger High Always (Hysteresis)
#define ADC_COMP_TRIG_HIGH_HONCE \
                                0x00001F00  // Trigger High Once (Hysteresis)

#define ADC_COMP_INT_NONE       0x00000000  // Interrupt Disabled
#define ADC_COMP_INT_LOW_ALWAYS \
                                0x00000010  // Interrupt Low Always
#define ADC_COMP_INT_LOW_ONCE   0x00000011  // Interrupt Low Once
#define ADC_COMP_INT_LOW_HALWAYS \
                                0x00000012  // Interrupt Low Always
                                            // (Hysteresis)
#define ADC_COMP_INT_LOW_HONCE  0x00000013  // Interrupt Low Once (Hysteresis)
#define ADC_COMP_INT_MID_ALWAYS \
                                0x00000014  // Interrupt Mid Always
#define ADC_COMP_INT_MID_ONCE   0x00000015  // Interrupt Mid Once
#define ADC_COMP_INT_HIGH_ALWAYS \
                                0x0000001C  // Interrupt High Always
#define ADC_COMP_INT_HIGH_ONCE  0x0000001D  // Interrupt High Once
#define ADC_COMP_INT_HIGH_HALWAYS \
                                0x0000001E  // Interrupt High Always
                                            // (Hysteresis)
#define ADC_COMP_INT_HIGH_HONCE \
                                0x0000001F  // Interrupt High Once (Hysteresis)

//*****************************************************************************
//
// Values that can be used to modify the sequence number passed to
// ADCProcessorTrigger in order to get cross-module synchronous processor
// triggers.
//
//*****************************************************************************
#define ADC_TRIGGER_WAIT        0x08000000  // Wait for the synchronous trigger
#define ADC_TRIGGER_SIGNAL      0x80000000  // Signal the synchronous trigger

//*****************************************************************************
//
// Values that can be passed to ADCPhaseDelaySet as the ulPhase parameter and
// returned from ADCPhaseDelayGet.
//
//*****************************************************************************
#define ADC_PHASE_0             0x00000000  // 0 degrees
#define ADC_PHASE_22_5          0x00000001  // 22.5 degrees
#define ADC_PHASE_45            0x00000002  // 45 degrees
#define ADC_PHASE_67_5          0x00000003  // 67.5 degrees
#define ADC_PHASE_90            0x00000004  // 90 degrees
#define ADC_PHASE_112_5         0x00000005  // 112.5 degrees
#define ADC_PHASE_135           0x00000006  // 135 degrees
#define ADC_PHASE_157_5         0x00000007  // 157.5 degrees
#define ADC_PHASE_180           0x00000008  // 180 degrees
#define ADC_PHASE_202_5         0x00000009  // 202.5 degrees
#define ADC_PHASE_225           0x0000000A  // 225 degrees
#define ADC_PHASE_247_5         0x0000000B  // 247.5 degrees
#define ADC_PHASE_270           0x0000000C  // 270 degrees
#define ADC_PHASE_292_5         0x0000000D  // 292.5 degrees
#define ADC_PHASE_315           0x0000000E  // 315 degrees
#define ADC_PHASE_337_5         0x0000000F  // 337.5 degrees

//*****************************************************************************
//
// Values that can be passed to ADCReferenceSet as the ulRef parameter.
//
//*****************************************************************************
#define ADC_REF_INT             0x00000000  // Internal reference
#define ADC_REF_EXT_3V          0x00000001  // External 3V reference


//*****************************************************************************
//
//! \addtogroup Stellaris_ADC_Exported_APIs
//! @{
//
//*****************************************************************************

extern void ADCIntDisable(unsigned long ulBase, unsigned long ulSequenceNum);
extern void ADCIntEnable(unsigned long ulBase, unsigned long ulSequenceNum);
extern unsigned long ADCIntStatus(unsigned long ulBase,
                                  unsigned long ulSequenceNum,
                                  xtBoolean bMasked);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulSequenceNum);
extern void ADCSequenceEnable(unsigned long ulBase,
                              unsigned long ulSequenceNum);
extern void ADCSequenceDisable(unsigned long ulBase,
                               unsigned long ulSequenceNum);
extern void ADCSequenceConfigure(unsigned long ulBase,
                                 unsigned long ulSequenceNum,
                                 unsigned long ulTrigger,
                                 unsigned long ulPriority);
extern void ADCSequenceStepConfigure(unsigned long ulBase,
                                     unsigned long ulSequenceNum,
                                     unsigned long ulStep,
                                     unsigned long ulConfig);
extern xtBoolean ADCSequenceOverflow(unsigned long ulBase,
                                     unsigned long ulSequenceNum);
extern void ADCSequenceOverflowClear(unsigned long ulBase,
                                     unsigned long ulSequenceNum);
extern xtBoolean ADCSequenceUnderflow(unsigned long ulBase,
                                      unsigned long ulSequenceNum);
extern void ADCSequenceUnderflowClear(unsigned long ulBase,
                                      unsigned long ulSequenceNum);
extern long ADCSequenceDataGet(unsigned long ulBase,
                               unsigned long ulSequenceNum,
                               unsigned long *pulBuffer);
extern void ADCProcessorTrigger(unsigned long ulBase,
                                unsigned long ulSequenceNum);
extern void ADCSoftwareOversampleConfigure(unsigned long ulBase,
                                           unsigned long ulSequenceNum,
                                           unsigned long ulFactor);
extern void ADCSoftwareOversampleStepConfigure(unsigned long ulBase,
                                               unsigned long ulSequenceNum,
                                               unsigned long ulStep,
                                               unsigned long ulConfig);
extern void ADCSoftwareOversampleDataGet(unsigned long ulBase,
                                         unsigned long ulSequenceNum,
                                         unsigned long *pulBuffer,
                                         unsigned long ulCount);
extern void ADCHardwareOversampleConfigure(unsigned long ulBase,
                                           unsigned long ulFactor);
extern void ADCComparatorConfigure(unsigned long ulBase, unsigned long ulComp,
                                   unsigned long ulConfig);
extern void ADCComparatorRegionSet(unsigned long ulBase, unsigned long ulComp,
                                   unsigned long ulLowRef,
                                   unsigned long ulHighRef);
extern void ADCComparatorReset(unsigned long ulBase, unsigned long ulComp,
                               xtBoolean bTrigger, xtBoolean bInterrupt);
extern void ADCComparatorIntDisable(unsigned long ulBase,
                                    unsigned long ulSequenceNum);
extern void ADCComparatorIntEnable(unsigned long ulBase,
                                   unsigned long ulSequenceNum);
extern unsigned long ADCComparatorIntStatus(unsigned long ulBase);
extern void ADCComparatorIntClear(unsigned long ulBase,
                                  unsigned long ulStatus);
extern void ADCReferenceSet(unsigned long ulBase, unsigned long ulRef);
extern unsigned long ADCReferenceGet(unsigned long ulBase);
extern void ADCPhaseDelaySet(unsigned long ulBase, unsigned long ulPhase);
extern unsigned long ADCPhaseDelayGet(unsigned long ulBase);

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

