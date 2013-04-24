//*****************************************************************************
//
//! \file xadc.h
//! \brief Defines and Macros for ADC API.
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

#define xADC_DATA_MASK          0x00000FFF

//
//! Channel n Data Bit Length
//
#define xADC_DATA_BIT_SIZE      12

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
//! +------------------------+----------------+------------------+
//! |xADC Interrupt Source   |       CoX      |    STM32F1xx     |
//! |------------------------|----------------|------------------|
//! |xADC_INT_COMP           |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADC_INT_END_CONVERSION |  Non-Mandatory |         Y        |
//! |------------------------|----------------|------------------|
//! \endverbatim
//!    
//! @{
//
//*****************************************************************************

//
//! Interrupt when any of comparators match
//
#define xADC_INT_COMP           0

//
//! Interrupt after single cycle conversion
//
#define xADC_INT_END_CONVERSION 0x000000A0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Events xADC Interrupt Event
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
//! +-------------------------+----------------+--------------------------+
//! |xADC Event               |       CoX      |       STM32F1xx          |
//! |-------------------------|----------------|--------------------------|
//! |xADC_EVENT_$COMPx$       |  Non-Mandatory |            N             |
//! |-------------------------|----------------|--------------------------|
//! |xADC_EVENT_END_CONVERSION|    Mandatory   |            Y             |
//! |-------------------------|----------------|--------------------------|
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
                               xADC_INT_END_CONVERSION

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
//! +---------------------------+----------------+-------------------+
//! |xADC Mode                  |       CoX      |     STM32F1xx     |
//! |---------------------------|----------------|-------------------|
//! |xADC_MODE_SCAN_SINGLE_CYCLE|    Mandatory   |         Y         |
//! |---------------------------|----------------|-------------------|
//! |xADC_MODE_SCAN_CONTINUOUS  |  Non-Mandatory |         Y         |
//! |---------------------------|----------------|-------------------|
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
                                ADC_OP_SCAN

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
                                ADC_OP_CONTINUOUS
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
//! \b PB2.
//!
//! \section xADC_Trigger_Source_Port 2. CoX Port Details
//! \verbatim
//! +---------------------------+----------------+------------------------------+
//! |xADC Trigger Source        |       CoX      |          STM32F1xx           |
//! |---------------------------|----------------|------------------------------|
//! |xADC_TRIGGER_PROCESSOR     |    Mandatory   |               Y              |
//! |---------------------------|----------------|------------------------------|
//! |xADC_TRIGGER_EXT_$ShortPin$|  Non-Mandatory |     xADC_TRIGGER_EXT_n       |
//! |---------------------------|----------------|------------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Processor trigger (Software)
//
#define xADC_TRIGGER_PROCESSOR  ADC_TRIGGER_PROCESSOR

//
//! External Pin Event (such as Rising, Falling...) on EXTI11
//
#define xADC_TRIGGER_EXT_INT11   ADC_TRIGGER_EXT_INT11

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_EXT_Trigger_Mode xADC External Tigger Source Mode
//!
//! Can be passed 
//! to the ADCConfigure() as the ulTrigger parameter, when the trigger source set
//! as xADC_TRIGGER_EXT_$ShortPin$. The ulTrigger parameter is an OR vaule 
//! with the \ref xADC_Trigger_Source. such as  
//! \ref xADC_TRIGGER_EXT_PD2 | \ref xADC_TRIGGER_EXT_RISING_EDGE.
//!
//! \section xADC_EXT_Trigger_Mode_Sec_Port CoX Port Details
//!
//! \verbatim
//! +-----------------------------+----------------+------------------+
//! |xADC Ext Trigger Mode        |       CoX      |    STM32F1xx     |
//! |-----------------------------|----------------|------------------|
//! |xADC_TRIGGER_EXT_LOW_LEVEL   |  Non-Mandatory |         N        |
//! |-----------------------------|----------------|------------------|
//! |xADC_TRIGGER_EXT_HIGH_LEVEL  |  Non-Mandatory |         N        |
//! |-----------------------------|----------------|------------------|
//! |xADC_TRIGGER_EXT_RISING_EDGE |  Non-Mandatory |         Y        |
//! |-----------------------------|----------------|------------------|
//! |xADC_TRIGGER_EXT_FALLING_EDGE|  Non-Mandatory |         N        |
//! |-----------------------------|----------------|------------------|
//! |xADC_TRIGGER_EXT_BOTH_EDGE   |  Non-Mandatory |         N        |
//! |-----------------------------|----------------|------------------|
//! \endverbatim 
//! @{
//
//*****************************************************************************

//
//! EXT Tigger is low level.
//
#define xADC_TRIGGER_EXT_LOW_LEVEL                                           \
                                0
//
//! EXT Tigger is highlevel.
//
#define xADC_TRIGGER_EXT_HIGH_LEVEL                                          \
                                0

//
//! EXT Tigger is rising edge.
//
#define xADC_TRIGGER_EXT_RISING_EDGE                                         \
                                ADC_TRIGGER_EXT_RISING_EDGE

//
//! EXT Tigger is falling edge.
//
#define xADC_TRIGGER_EXT_FALLING_EDGE                                        \
                                0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xADC_Step_Config xADC Step Config
//! \brief ADC step config values, such as single-end / difference, channel source.
//!
//! They are can be passed to the xADCStepConfigure() as the ulConfig parameter.
//! 
//! \section xADC_Step_Config_Sec_Divide xADC Step Config Divide
//! The Step Config value is an logic OR type of the following config:
//! - Channel source select, like \b xADC_CTL_$CHx$, such as \ref xADC_CTL_CH0.  
//! Or \ref xADC_CTL_TS to select the temperature sensor.
//! - Comparator select to monitor the convertion value, like 
//! \b xADC_CTL_$CMPx$, such as \ref xADC_CTL_CMP0.
//! - single-end / difference input mode. xADC_CTL_D shows difference input mode,
//! and 0 shows single-end mode.
//! - \ref xADC_CTL_END shows this is the end step.
//! .
//! \section xADC_Step_Config_Sec_Port CoX Port Details.
//! \verbatim
//! +----------------+----------------+-----------------------+
//! |xADC Step Config|       CoX      |       STM32F1xx       |
//! |----------------|----------------|-----------------------|
//! |xADC_CTL_CH$x$  |  Non-Mandatory |     xADC_CTL_CH0      |
//! |                |                |     xADC_CTL_CH1      |
//! |                |                |     xADC_CTL_CH2      |
//! |                |                |     xADC_CTL_CH3      |
//! |                |                |     xADC_CTL_CH4      |
//! |                |                |     xADC_CTL_CH5      |
//! |                |                |     xADC_CTL_CH6      |
//! |                |                |     xADC_CTL_CH7      |
//! |----------------|----------------|-----------------------|
//! |xADC_CTL_TS     |  Non-Mandatory |           N           |
//! |----------------|----------------|-----------------------|
//! |xADC_CTL_CMP$x$ |  Non-Mandatory |           N           |
//! |----------------|----------------|-----------------------|
//! |xADC_CTL_D      |  Non-Mandatory |           N           |
//! |----------------|----------------|-----------------------|
//! |xADC_CTL_END    |  Non-Mandatory |           N           |
//! |----------------|----------------|-----------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

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
//! Internal temperature channel
//
#define xADC_CTL_TS             0x00000016

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
//! +----------------+----------------+------------------+
//! |xADC Comp ID    |       CoX      |    STM32F1xx     |
//! |----------------|----------------|------------------|
//! |xADC_COMP_$x$   |  Non-Mandatory |       N          |
//! |----------------|----------------|------------------| 
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
//! +-------------------------+----------------+--------------------+
//! |xADC Comp Int Condition  |       CoX      |     STM32F1xx      |
//! |-------------------------|----------------|--------------------|
//! |xADC_COMP_INT_LOW        |  Non-Mandatory |          N         |
//! |-------------------------|----------------|--------------------|
//! |xADC_COMP_INT_MID        |  Non-Mandatory |          N         |
//! |-------------------------|----------------|--------------------|
//! |xADC_COMP_INT_HIGH       |  Non-Mandatory |          N         |
//! +-------------------------+----------------+--------------------+ 
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
//! +------------------------+----------------+------------------+
//! |xADC API                |       CoX      |    STM32F1xx     |
//! |------------------------|----------------|------------------|
//! |xADCConfigure           |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCStepConfigure       |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCIntCallbackInit     |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCIntEnable           |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCIntDisable          |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCEnable              |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCDisable             |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCProcessorTrigger    |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCDataGet             |    Mandatory   |         Y        |
//! |------------------------|----------------|------------------|
//! |xADCOverflow            |  Non-Mandatory |         N        |
//! |------------------------|----------------|------------------|
//! |xADCOverflowClear       |  Non-Mandatory |         N        |
//! |------------------------|----------------|------------------|
//! |xADCCompConditionConfig |  Non-Mandatory |         N        |
//! |------------------------|----------------|------------------|
//! |xADCCompRegionSet       |  Non-Mandatory |         N        |
//! |------------------------|----------------|------------------|
//! |xADCCompEnable          |  Non-Mandatory |         N        |
//! |------------------------|----------------|------------------|
//! |xADCCompDisable         |  Non-Mandatory |         N        |
//! |------------------------|----------------|------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

extern void xADCConfigure(unsigned long ulBase, unsigned long ulMode, 
                          unsigned long ulTrigger);

extern void xADCStepConfigure(unsigned long ulBase, unsigned long ulStep,
                              unsigned long ulConfig);  

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
//! .
//!
//! \return None.
//
//*****************************************************************************
extern void  xADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);

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
extern void xADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);

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
#define xADCEnable(ulBase)                                                    \
        ADCEnable(ulBase)

//*****************************************************************************
//
//! \brief Disable the ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Prevents the sample sequence from being captured when its trigger is detected.
//! The sample sequence should be disabled before it is configured.
//!
//! \return None.
//
//*****************************************************************************
#define xADCDisable(ulBase)                                                   \
        ADCDisable(ulBase)

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
#define xADCProcessorTrigger(ulBase)                                          \
        ADCProcessorTrigger(ulBase)

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
#define xADCCompRegionSet(ulBase, ulCompID, ulLowRef, ulHighRef)              0
        

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
#define xADCCompEnable(ulBase, ulCompID)                                      0

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
#define xADCCompDisable(ulBase, ulCompID)                                     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

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
extern unsigned long xADCDataGet(unsigned long ulBase,
                                 unsigned long *pulBuffer);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Channel_IDs STM32F1xx ADC Channel ID
//! @{
//
//*****************************************************************************

//
//!Analog Input Channel 0
//
#define ADC_CHANNEL_0           0

//
//!Analog Input Channel 1
//
#define ADC_CHANNEL_1           1

//
//!Analog Input Channel 2
//
#define ADC_CHANNEL_2           2

//
//!Analog Input Channel 3
//
#define ADC_CHANNEL_3           3

//
//!Analog Input Channel 4
//
#define ADC_CHANNEL_4           4

//
//!Analog Input Channel 5
//
#define ADC_CHANNEL_5           5

//
//!Analog Input Channel 6
//
#define ADC_CHANNEL_6           6

//
//!Analog Input Channel 7
//
#define ADC_CHANNEL_7           7

//
//!Analog Input Channel 8
//
#define ADC_CHANNEL_8           8

//
//!Analog Input Channel 9
//
#define ADC_CHANNEL_9           9

//
//!Analog Input Channel 2
//
#define ADC_CHANNEL_10          10

//
//!Analog Input Channel 11
//
#define ADC_CHANNEL_11          11

//
//!Analog Input Channel 12
//
#define ADC_CHANNEL_12          12

//
//!Analog Input Channel 13
//
#define ADC_CHANNEL_13          13

//
//!Analog Input Channel 14
//
#define ADC_CHANNEL_14          14

//
//!Analog Input Channel 15
//
#define ADC_CHANNEL_15          15

//
//!Analog Input Channel 6
//
#define ADC_CHANNEL_16          16

//
//!Analog Input Channel 17
//
#define ADC_CHANNEL_17          17

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Operation_Mode STM32F1xx ADC Operation Mode
//! @{
//
//*****************************************************************************

//
//! A/D Converter Operation Mode is Single conversion
// 
#define ADC_OP_SINGLE           0x00000000

//
//! A/D Converter Operation Mode: Discontinuous conversion on injected channels
//
#define ADC_OP_INJECT_DISCONTINUOUS                                           \
                                0x00001000
//
//! A/D Converter Operation Mode: Discontinuous conversion on regular channels
//
#define ADC_OP_REGULAR_DISCONTINUOUS                                          \
                                0x00000800

//
//! A/D Converter Operation Mode: Continuous scan
// 
#define ADC_OP_CONTINUOUS       0x00000002

//
//! A/D Converter Operation Mode is Scan conversion
// 
#define ADC_OP_SCAN             0x00000100


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Sampling_Time STM32F1xx ADC Sampling Time Length
//! @{
//
//*****************************************************************************

//
//! Sample time selection: 1.5 cycles
// 
#define ADC_SAMPTIME_1_5_CYCLE  0x00000000

//
//! Sample time selection: 7.5 cycles
//
#define ADC_SAMPTIME_7_5_CYCLE  0x00000001

//
//! Sample time selection: 13.5 cycles
//
#define ADC_SAMPTIME_13_5_CYCLE 0x00000002

//
//! Sample time selection: 28.5 cycles
//
#define ADC_SAMPTIME_28_5_CYCLE 0x00000003

//
//! Sample time selection: 41.5 cycles
//
#define ADC_SAMPTIME_41_5_CYCLE 0x00000004

//
//! Sample time selection: 55.5 cycles
// 
#define ADC_SAMPTIME_55_5_CYCLE 0x00000005

//
//! Sample time selection: 71.5 cycles
// 
#define ADC_SAMPTIME_71_5_CYCLE 0x00000006

//
//! Sample time selection: 239.5 cycles
// 
#define ADC_SAMPTIME_239_5_CYCLE                                              \
                                0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Tigger_Source STM32F1xx ADC Tigger Source of regular Channel
//! @{
//
//*****************************************************************************

//
//! Processor event(Software)
//
#define ADC_TRIGGER_PROCESSOR   0x000E0000

//
//! External Pin event(EXTI line 11)
//
#define ADC_TRIGGER_EXT_INT11   0x000C0000

//
//! TIM1_CC1 event
//
#define ADC_TRIGGER_TIME1_CC1   0x00000000

//
//! TIM1_CC2 event
//
#define ADC_TRIGGER_TIME1_CC2   0x00020000

//
//! TIM1_CC3 event
//
#define ADC_TRIGGER_TIME1_CC3   0x00040000

//
//! TIM2_CC2 event
//
#define ADC_TRIGGER_TIME2_CC2   0x00060000

//
//! TIM3_TRGO event
//
#define ADC_TRIGGER_TIME3_TRGO  0x00080000

//
//! TIM4_CC4 event
//
#define ADC_TRIGGER_TIME4_CC4   0x000A0000

//
//! TIM8_TRGO event
//
#define ADC_TRIGGER_TIME8_TRGO  0x000C0000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Tigger_Source STM32F1xx ADC Tigger Source of Injected Channel
//! @{
//
//*****************************************************************************

//
//! Processor event(Software)
//
#define ADC_TRIGGER_PROCESSORIN 0x00007000

//
//! External Pin event(EXTI line 15)
//
#define ADC_TRIGGER_EXT_INT15   0x00006000

//
//! TIM1_TRGO event
//
#define ADC_TRIGGER_TIME1_TRGO  0x00000000

//
//! TIM1_CC4 event
//
#define ADC_TRIGGER_TIME1_CC4   0x00001000

//
//! TIM2TRGO event
//
#define ADC_TRIGGER_TIME2_TRGO  0x00002000

//
//! TIM2_CC1 event
//
#define ADC_TRIGGER_TIME2_CC1   0x00003000

//
//! TIM3_CC4 event
//
#define ADC_TRIGGER_TIME3_CC4   0x00004000

//
//! TIM4_TRGO event
//
#define ADC_TRIGGER_TIME4_TRGO  0x00005000

//
//! TIM8_CC4 event
//
#define ADC_TRIGGER_TIME8_CC4   0x00006000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_MONITOR_CHANNEL STM32F1xx ADC Monitor Channel
//! pin.
//! @{
//
//*****************************************************************************

#define ADC_MONITOR_ADWALL      0x00000100
#define ADC_MONITOR_ADSPEC      0x00000200

#define ADC_MONITOR_IN0         0x00000000
#define ADC_MONITOR_IN1         0x00000001
#define ADC_MONITOR_IN2         0x00000002
#define ADC_MONITOR_IN3         0x00000003
#define ADC_MONITOR_IN4         0x00000004
#define ADC_MONITOR_IN5         0x00000005
#define ADC_MONITOR_IN6         0x00000006
#define ADC_MONITOR_IN7         0x00000007
#define ADC_MONITOR_IN8         0x00000008
#define ADC_MONITOR_IN9         0x00000009
#define ADC_MONITOR_IN10        0x0000000A
#define ADC_MONITOR_IN11        0x0000000B
#define ADC_MONITOR_IN12        0x0000000C
#define ADC_MONITOR_IN13        0x0000000D
#define ADC_MONITOR_IN14        0x0000000E
#define ADC_MONITOR_IN15        0x0000000F
#define ADC_MONITOR_IN16        0x00000010
#define ADC_MONITOR_IN17        0x00000011

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_EXT_Trigger_Mode STM32F1xx ADC External Tigger Mode
//! pin.
//! @{
//
//*****************************************************************************

//
//! EXT Tigger is rising edge.
//
#define ADC_TRIGGER_EXT_RISING_EDGE                                           \
                                0x000000C0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Ints STM32F1xx ADC Interrupt
//! \brief Values that show the ADC Interrupt source.
//! @{
//
//*****************************************************************************

//
//! Interrupt of end conversion
//
#define ADC_INT_END_CONVERSION  0x00000002

//
//! Interrupt of Injected channel end of conversion
//
#define ADC_INT_END_JEOC        0x00000004

//
//! Interrupt of Analog watchdog
//
#define ADC_INT_AWD             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Data_Resolution STM32F1xx ADC Data Resolution
//! \brief Values that show the ADC Data Resolution (Data Mask, Data Length).
//! @{
//
//*****************************************************************************

//
//! Channel n Data mask
//

#define ADC_DATA_MASK           0x00000FFF

//
//! Channel n Data bit length
//
#define ADC_DATA_BIT_SIZE       12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Channel_Type STM32F1xx ADC Channel Type
//! \brief Values that show the ADC Channel Type.
//! @{
//
//*****************************************************************************

//
//! Regular Channel Type
//

#define ADC_TYPE_REGULAR        0x00000001

//
//! Injected Channel Type
//

#define ADC_TYPE_INJECTED       0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Mode_Type STM32F1xx ADC Mode Type
//! \brief Values that show the ADC Mode Type.
//! @{
//
//*****************************************************************************

//
//! Normal Mode
//

#define ADC_MODE_NORMAL         0x00000001

//
//! Dual Mode
//

#define ADC_MODE_DUAL           0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_DataAlign_Type STM32F1xx ADC Data Align Type
//! \brief Values that show the ADC Data Align Type.
//! @{
//
//*****************************************************************************

//
//! Right Align
//

#define ADC_ALIGN_RIGHT         0x00000000

//
//! Left Align
//

#define ADC_ALIGN_LEFT          0x00000800

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Dual_Type STM32F1xx Dual ADC Mode
//! \brief Values that show the Dual ADC Mode.
//! @{
//
//*****************************************************************************

//
//! Combined regular simultaneous + injected simultaneous mode
//

#define ADC_MODE_REGINJECSIMULT 0x00010000

//
//! Combined regular simultaneous + alternate trigger mode
//

#define ADC_MODE_REGSIMULT_ALTERTRIG                                          \
                                0x00020000

//
//! Combined injected simultaneous + fast interleaved mode
//
#define ADC_MODE_INJECSIMULT_FASTINTERL                                       \
                                0x00030000

//
//! Combined injected simultaneous + slow interleaved mode
//
#define ADC_MODE_INJECSIMULT_SLOWINTERL                                       \
                                0x00040000

//
//! injected simultaneous mode only
//
#define ADC_MODE_INJECSIMULT    0x00050000

//
//! Regular simultaneous mode only
//
#define ADC_MODE_REGSIMULT      0x00060000

//
//! Fast interleaved mode only
//
#define ADC_MODE_FASTINTERL     0x00070000

//
//! Slow interleaved mode only
//
#define ADC_MODE_SLOWINTERL     0x00080000

//
//! Alternate trigger mode only
//
#define ADC_MODE_ALTERTRIG      0x00090000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_ADC_Exported_APIs STM32F1xx ADC API
//! \brief STM32F1xx ADC API Reference
//! @{
//
//*****************************************************************************
extern void ADCRegularConfigure(unsigned long ulBase,  unsigned long ulOpMode,
                                 unsigned long ulTrigger);
extern void ADCInjectedConfigure(unsigned long ulBase,  unsigned long ulOpMode,
                                 unsigned long ulTrigger);
extern void ADCEnable(unsigned long ulBase);
extern void ADCDisable(unsigned long ulBase);
extern void ADCDualModeSet(unsigned long ulADCDualMode);

extern void ADCProcessorTrigger(unsigned long ulBase);
extern void ADCProcessorInjectedTrigger(unsigned long ulBase);
extern void ADCExtiEventReguTrigger(unsigned long ulBase);
extern void ADCExtiEventInjecTrigger(unsigned long ulBase);

extern unsigned long ADCDataRegularGet(unsigned long ulBase, unsigned long ulADCMode);
extern void ADCDataAlignModeSet(unsigned long ulBase, unsigned long ulAlignMode);
extern unsigned long ADCDataInjectedGet(unsigned long ulBase, unsigned long ulChannel);

extern void ADCMonitorSet(unsigned long ulBase, unsigned long ulHighThreshold,
                          unsigned long ulLowThreshold, unsigned long ulMoniChannel);

extern void ADCSampLenSet(unsigned long ulBase, unsigned long ulChannel, 
                          unsigned long ulSampTime) ;
extern void ADCMoniEnable(unsigned long ulBase, unsigned long ulComp);
extern void ADCMoniDisable(unsigned long ulBase, unsigned long ulComp);

extern void ADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long ADCIntStatus(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulIntFlags);

extern void ADCConverLenSet(unsigned long ulBase, unsigned long ulSeqRegLen, 
                            unsigned long ulSeqInjLen);
extern void ADCSequenceIndexSet(unsigned long ulBase, unsigned long *pulRegChanNo,
                        unsigned long *pulInjectChanNo);

extern void ADCMoniEnable(unsigned long ulBase, unsigned long ulChanType);
extern void ADCMoniDisable(unsigned long ulBase, unsigned long ulChanType);
extern void ADCAutoInjectedEnable(unsigned long ulBase);
extern void ADCAutoInjectedDisable(unsigned long ulBase);
extern unsigned long ADCInjectedOffsetDataGet(unsigned long ulBase, unsigned long ulChannel);
extern void ADCCalibrationReset(unsigned long ulBase);
extern xtBoolean ADCCalibrationResetStatusGet(unsigned long ulBase);
extern void ADCCalibrationStart(unsigned long ulBase);
extern xtBoolean ADCCalibrationStatusGet(unsigned long ulBase);
extern void ADCDMAEnable(unsigned long ulBase);
extern void ADCDMADisable(unsigned long ulBase);
extern void ADCTemperatureRefVolEnable(unsigned long ulBase);
extern void ADCTemperatureRefVolDisable(unsigned long ulBase);

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

