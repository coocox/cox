//*****************************************************************************
//
//! \file xadc.h
//! \brief Defines and Macros for ADC API.
//! \version V2.2.1.0
//! \date 8/11/2012
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
//! \brief Values that show the ADC Interrupt source.
//!
//! They can be passed to xADCIntEnable(), 
//! xADCIntDisable() as the ulIntFlags parameter to enable/disable the 
//! corresponding interrupt.
//!
//! \section xADC_Ints_Sec_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+--------+
//! |xADC Interrupt Source   |       CoX      |   KLx  |
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
#define xADC_INT_COMP           ADC_INT_COMP0

//
//! Interrupt after single cycle conversion
//
#define xADC_INT_END_CONVERSION ADC_INT_END_CONVERSION

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
//! |xADC Event               |       CoX      |       KLx      |
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
#define xADC_EVENT_COMP0        ADC_INT_COMP0

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
//! +---------------------------+----------------+--------+
//! |xADC Mode                  |       CoX      |  KLx   |
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
                                ADC_OP_SINGLE

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
//! \b PB8.
//!
//! \section xADC_Trigger_Source_Port 2. CoX Port Details
//! \verbatim
//! +---------------------------+----------------+--------------------+
//! |xADC Trigger Source        |       CoX      |        KLx         |
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
#define xADC_TRIGGER_PROCESSOR  ADC_TRIGGER_PROCESSOR

//
//! External Pin Event (such as Rising, Falling...) on PB8
//
#define xADC_TRIGGER_EXT_PIN    0x00000000

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
//! |xADC Ext Trigger Mode        |       CoX      |  KLx   |
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
                                ADC_TRIGGER_EXT_LOW_LEVEL

//
//! EXT Tigger is highlevel.
//
#define xADC_TRIGGER_EXT_HIGH_LEVEL                                      \
                                ADC_TRIGGER_EXT_HIGH_LEVEL

//
//! EXT Tigger is rising edge.
//
#define xADC_TRIGGER_EXT_RISING_EDGE                                     \
                                ADC_TRIGGER_EXT_RISING_EDGE

//
//! EXT Tigger is falling edge.
//
#define xADC_TRIGGER_EXT_FALLING_EDGE                                    \
                                ADC_TRIGGER_EXT_FALLING_EDGE


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
//! |xADC Step Config|       CoX      |    KLx      |
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
#define xADC_CTL_TS             0x0000001A

//
//! Sequence end select 
//
#define xADC_CTL_END            0x40000000  

//
//! Differential select
//
#define xADC_CTL_D              0x20000000  

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
//! Select Comparator 0
//
#define xADC_CTL_CMP0           0x00000800  

//
//! Select Comparator 1
//
#define xADC_CTL_CMP1           0x00000900

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
//! |xADC Comp ID    |       CoX      |     KLx     |
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
#define xADC_COMP_0             ADC_COMP_0

//
// Comparator 1
//
#define xADC_COMP_1             ADC_COMP_1

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
//! |xADC Comp Int Condition  |       CoX      |   KLx   |
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
#define xADC_COMP_INT_LOW       ADC_COMP_LESS_THAN

//
//! Always generate ADC interrupt when ADC output is in the high-band.
//
#define xADC_COMP_INT_HIGH      ADC_COMP_GREATER_EQUAL

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
//! |xADC API                |       CoX      |   KLx  |
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
//! |xADCEnable              |  Non-Mandatory |    N   |
//! |------------------------|----------------|--------|
//! |xADCDisable             |  Non-Mandatory |    N   |
//! |------------------------|----------------|--------|
//! |xADCProcessorTrigger    |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCDataGet             |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xADCOverflow            |  Non-Mandatory |    N   |
//! |------------------------|----------------|--------|
//! |xADCOverflowClear       |  Non-Mandatory |    N   |
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
//! - \b xADC_INT_COMP - Comp0 and Comp1 interrupt
//! .
//!
//! \return None.
//
//*****************************************************************************
#define xADCIntEnable(ulBase, ulIntFlags)                                     \
        ADCIntEnable(ulBase, ulIntFlags)

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
#define xADCIntDisable(ulBase, ulIntFlags)                                    \
        ADCIntDisable(ulBase, ulIntFlags)

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
#define xADCDMAEnable(ulBase)                                                 \
        ADCPDMAEnable(ulBase)

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
#define xADCDMADisable(ulBase)                                                \
        ADCPDMADisable(ulBase)
        
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
//! Prevents the sample sequence from being captured when its trigger
//! is detected.  The sample sequence should be disabled before it 
//! is configured.
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

extern unsigned long xADCDataGet(unsigned long ulBase, 
                                 unsigned long *pulBuffer);

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
#define xADCCompRegionSet(ulBase, ulCompID, ulLowRef, ulHighRef)              \
        do                                                                    \
        {                                                                     \
            ADCCompDataSet(ulBase, 0, ulLowRef, ulHighRef);                   \
        }                                                                     \
        while(0)
        

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
#define xADCCompEnable(ulBase, ulCompID)                                      \
        ADCCompEnable(ulBase, ulCompID)

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
#define xADCCompDisable(ulBase, ulCompID)                                     \
        ADCCompDisable(ulBase, ulCompID)

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
//! \addtogroup KLx_ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Channel_IDs KLx ADC Channel ID
//! \brief ADC Channel ID/index
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
//!Analog Input Channel 10
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
//!Analog Input Channel 16
//
#define ADC_CHANNEL_16          16

//
//!Analog Input Channel 17
//
#define ADC_CHANNEL_17          17

//
//!Analog Input Channel 18
//
#define ADC_CHANNEL_18          18

//
//!Analog Input Channel 19
//
#define ADC_CHANNEL_19          19

//
//!Analog Input Channel 20
//
#define ADC_CHANNEL_20          20

//
//!Analog Input Channel 21
//
#define ADC_CHANNEL_21          21

//
//!Analog Input Channel 22
//
#define ADC_CHANNEL_22          22

//
//!Analog Input Channel 23
//
#define ADC_CHANNEL_23          23

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Comp_Function_Range KLx ADC Comparator Function Range
//! \brief ADC digital comparator Function Range
//! @{
//
//*****************************************************************************

//
//! Range function disabled. Only CV1 is compared
//
#define ADC_COMP_RANGE_CV1      0

//
//! Range function enabled. Both CV1 and CV2 are compared.
//
#define ADC_COMP_RANGE_CV1_CV2  1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Mux_Select KLx ADC Mux Select
//! \brief ADC Mux Select
//! The following are values that can be passed to the ADCMuxSelect()
//! API as the ulMux parameter. 
//! @{
//
//*****************************************************************************

//
//! ADxxa channels are selected
//
#define ADC_MUX_ADC0A           0x00000000

//
//! ADxxb channels are selected.
//
#define ADC_MUX_ADC0B           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Speed_Select KLx ADC conversion speed Select
//! \brief ADC conversion speed Select
//! The following are values that can be passed to the ADCConSpeedSelect()
//! API as the ulSpeed parameter. 
//! @{
//
//*****************************************************************************

//
//! Normal conversion sequence selected.
//
#define ADC_CONVERSION_SPEED_NORMAL                                           \
                                0x00000000

//
//! High-speed conversion sequence selected with 2 additional ADCK cycles to 
//! total conversion time.
//
#define ADC_CONVERSION_SPEED_HIGH                                             \
                                0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Comp_IDs KLx ADC Comparator ID
//! @{
//
//*****************************************************************************

//
// Analog Comparator 0
//
#define ADC_COMP_0              0

//
// Analog Comparator 1
//
#define ADC_COMP_1              1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Power_Mode KLx ADC Low-Power Configuration
//! \brief ADC Low-Power Configuration
//! The following are values that can be passed to the ADCPowerModeSet()
//! API as the ulPowerMode parameter. 
//! @{
//
//*****************************************************************************

//
//! Normal power configuration.
//
#define ADC_POWER_MODE_NORMAL   0x00000000

//
//! Low-power configuration.The power is reduced at the expense of maximum clock speed.
//
#define ADC_POWER_MODE_LOW      0x00000080

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Sample_Time KLx ADC Sample Time Set.
//! \brief ADC Sample Time Set.
//! The following are values that can be passed to the ADCSampleTimeSet()
//! API as the ulSampleTime parameter. 
//! @{
//
//*****************************************************************************

//
//! Short sample time.
//
#define ADC_SAMPLE_TIME_SHORT   0x00000000

//
//! Long sample time.
//
#define ADC_SAMPLE_TIME_LONG    0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Pretrigger_Mode KLx ADC Pretrigger Mode Set.
//! \brief ADC pretrigger select Set.
//! The following are values that can be passed to the ADCPretriggerSet()
//! API as the ulPretrigger parameter. 
//! @{
//
//*****************************************************************************

//
//! Pre-trigger A.
//
#define ADC_PRE_TRIGGER_A       0x00000000

//
//! Pre-trigger B.
//
#define ADC_PRE_TRIGGER_B       0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Long_Sample_Time_Select KLx ADC Long Sample Time Select
//! \brief ADC Long Sample Time Select.
//! The following are values that can be passed to the ADCLongSampleTimeSet()
//! API as the ulLongSamTime parameter. 
//! @{
//
//*****************************************************************************

//
//! Default longest sample time; 20 extra ADCK cycles; 24 ADCK cycles total.
//
#define ADC_LONG_SAMPLE_TIME_24 0x00000000

//
//! 12 extra ADCK cycles; 16 ADCK cycles total sample time.
//
#define ADC_LONG_SAMPLE_TIME_16 0x00000001

//
//! 6 extra ADCK cycles; 10 ADCK cycles total sample time.
//
#define ADC_LONG_SAMPLE_TIME_10 0x00000002

//
//! 2 extra ADCK cycles; 6 ADCK cycles total sample time.
//
#define ADC_LONG_SAMPLE_TIME_6  0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Single_Sample_resolution_Select KLx ADC single-ended resolution Select
//! \brief ADC single-ended resolution mode Select.
//! The following are values that can be passed to the ADCSingleResolutionSet()
//! API as the ulSingleRes parameter. 
//! @{
//
//*****************************************************************************

//
//! single-ended 8-bit conversion.
//
#define ADC_SINGLE_RESOLUTION_8 0x00000000

//
//! single-ended 12-bit conversion.
//
#define ADC_SINGLE_RESOLUTION_12                                              \
                                0x00000001

//
//! single-ended 10-bit conversion.
//
#define ADC_SINGLE_RESOLUTION_10                                              \
                                0x00000002

//
//! single-ended 16-bit conversion.
//
#define ADC_SINGLE_RESOLUTION_16                                              \
                                0x00000003                     
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Differential_Sample_resolution_Select KLx ADC Differential resolution Select
//! \brief ADC Differential resolution mode Select.
//! The following are values that can be passed to the ADCDifferentialResolutionSet()
//! API as the ulDiffRes parameter. 
//! @{
//
//*****************************************************************************

//
//! differential 9-bit conversion.
//
#define ADC_DIFF_RESOLUTION_9   0x00000000

//
//! differential 13-bit conversion.
//
#define ADC_DIFF_RESOLUTION_13  0x00000001

//
//! differential 11-bit conversion.
//
#define ADC_DIFF_RESOLUTION_11  0x00000002

//
//! differential 16-bit conversion.
//
#define ADC_DIFF_RESOLUTION_16  0x00000003                     
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Input_Mode KLx ADC Input Mode
//! \brief ADC analog input mode, single-end / difference.
//! @{
//
//*****************************************************************************

//
//! Single-end Input Mode
//
#define ADC_INPUT_SINGLE        0x00000000

//
//! Differential Input Mode
//
#define ADC_INPUT_DIFF          0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Operation_Mode KLx ADC Operation Mode
//! \brief ADC A/D Converter Operation Mode.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Operation Mode is Single conversion
// 
#define ADC_OP_SINGLE           0x00000000

//
//! A/D Converter Operation Mode is Continuous scan
// 
#define ADC_OP_CONTINUOUS       0x00000008


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Tigger_Source KLx ADC Tigger Source
//! \brief ADC trigger Source that can start the convertion.
//! @{
//
//*****************************************************************************
//
//! Processor event(Software)
//
#define ADC_TRIGGER_PROCESSOR   0x00000100

//
//! External trigger pin input(EXTRG_IN)
//
#define ADC_TRIGGER_EXT_PIN     0x00000000

//
//! HSCMP0 output
//
#define ADC_TRIGGER_HSCMP0      0x00000001

//
//! PIT trigger 0
//
#define ADC_TRIGGER_PIT0        0x00000004

//
//! PIT trigger 1
//
#define ADC_TRIGGER_PIT1        0x00000005

//
//! TPM0 overflow
//
#define ADC_TRIGGER_TPM0        0x00000008

//
//! TPM1 overflow
//
#define ADC_TRIGGER_TPM1        0x00000009

//
//! TPM2 overflow
//
#define ADC_TRIGGER_TPM2        0x0000000A

//
//! RTC alarm
//
#define ADC_TRIGGER_RTC_ALARM   0x0000000C

//
//! RTC second
//
#define ADC_TRIGGER_RTC_SECONDS 0x0000000D

//
//! LPTMR0 trigger
//
#define ADC_TRIGGER_LPTMR0      0x0000000E

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_EXT_Trigger_Mode KLx ADC External Tigger Mode
//! \brief ADC external trigger Mode when the trigger source is external 
//! pin.
//! @{
//
//*****************************************************************************

//
//! EXT Tigger is low level.
//
#define ADC_TRIGGER_EXT_LOW_LEVEL                                             \
                                0x00000000

//
//! EXT Tigger is high level.
//
#define ADC_TRIGGER_EXT_HIGH_LEVEL                                            \
                                0x00000040

//
//! EXT Tigger is falling edge.
//
#define ADC_TRIGGER_EXT_FALLING_EDGE                                          \
                                0x00000080


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
//! \addtogroup KLx_ADC_Channel7_Source KLx_ADC Channel 7 Source
//! \brief ADC channel 7 analog input source config.
//! @{
//
//*****************************************************************************

//
//! Analog Input Channel 7 source is External analog input
//
#define ADC_CH7_EXT             0x00000000

//
//! Analog Input Channel 7 source is Internal bandgap voltage
//

#define ADC_CH7_INT_BV          0x00000100

//
//! Analog Input Channel 7 source is Internal temperature sensor
//

#define ADC_CH7_INT_TS          0x00000200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Ints KLx ADC Interrupt
//! \brief Values that show the ADC Interrupt source.
//! @{
//
//*****************************************************************************

//
//! Interrupt after single cycle conversion
//
#define ADC_INT_END_CONVERSION  0x00000001

//
//!  Interrupt when the comparator 0 match
//
#define ADC_INT_COMP0           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Data_Status KLx ADC Data Status
//! \brief Check the convertion data if valid or overrun.
//! @{
//
//*****************************************************************************

//
//! Channel n Data is valid
//
#define ADC_DATA_VALID          0x00000001

//
//! Channel n Data is overrun
//
#define ADC_DATA_OVERRUN        0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Data_Resolution KLx ADC Data Resolution
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
//! \addtogroup KLx_ADC_Comp_Conditions KLx ADC Comparator Interrupt Condition
//! \brief Conditions when the digital comparator generate and interrupt.
//! @{
//
//*****************************************************************************

//
//! Compare condition is less than
//
#define ADC_COMP_LESS_THAN      0x00000000

//
//! Compare condition is greater or equal
//
#define ADC_COMP_GREATER_EQUAL  0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Comp_Ref_Voltage KLx ADC Comparator Reference Voltage
//! \brief ADC Comparator Reference Voltage.
//! @{
//
//*****************************************************************************

//
//! Default voltage reference pin pair, that is, external pins VREFH and VREFL
//
#define ADC_COMP_REF_VOL_DEFAULT                                              \
                                0x00000000

//
//! Alternate reference pair, that is, VALTH and VALTL.
//
#define ADC_COMP_REF_VOL_ALTERNATE                                              \
                                0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Hardware_Average_Select KLx ADC Hardware Average Select
//! \brief ADC Hardware Average Select.
//! The following are values that can be passed to the ADCHardwareAverageSet()
//! API as the ulAverage parameter. 
//! @{
//
//*****************************************************************************

//
//! 4 samples averaged.
//
#define ADC_HARDWARE_AVERAGE_4  0x00000000

//
//! 8 samples averaged.
//
#define ADC_HARDWARE_AVERAGE_8  0x00000001

//
//! 16 samples averaged.
//
#define ADC_HARDWARE_AVERAGE_16 0x00000002

//
//! 32 samples averaged.
//
#define ADC_HARDWARE_AVERAGE_32 0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ADC_Exported_APIs KLx ADC API
//! \brief KLx ADC API Reference
//! @{
//
//*****************************************************************************
extern void ADCConfigure(unsigned long ulBase, unsigned long ulInputMode,
                         unsigned long ulOpMode, unsigned long ulTrigger);
extern void ADCDiffChannelEnable(unsigned long ulBase, unsigned long ulChannel);
extern void ADCSingleEndedChannelEnable(unsigned long ulBase, unsigned long ulChannel);
extern void ADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCCalibrationEnable(unsigned long ulBase);
extern xtBoolean ADCCalibrationIsFailed(unsigned long ulBase);
extern void ADCCalibrationFailedFlagClear(unsigned long ulBase);
extern void ADCProcessorTrigger(unsigned long ulBase);
extern void ADCConvertStop(unsigned long ulBase);
extern unsigned long ADCDataGet(unsigned long ulBase);
extern unsigned long ADCOffsetDataGet(unsigned long ulBase);
extern void ADCCalibrationEnable(unsigned long ulBase);
extern void ADCCalibrationDisable(unsigned long ulBase);
extern void ADCAsynClkOutputEnable(unsigned long ulBase);
extern void ADCAsynClkOutputDisable(unsigned long ulBase);
extern xtBoolean ADCCalibrationDone(unsigned long ulBase);
extern void ADCRefVoltageSet(unsigned long ulBase, unsigned long ulRefVol);
extern void ADCHardwareAverageEnable(unsigned long ulBase);
extern void ADCHardwareAverageDisable(unsigned long ulBase);
extern void ADCHardwareAverageSet(unsigned long ulBase, unsigned long ulAverage);
extern void ADCCompDataSet(unsigned long ulBase, unsigned long ulComp,
                           unsigned long ulCompData, 
                           unsigned long ulMatchCnt);
extern void ADCCompEnable(unsigned long ulBase, unsigned long ulComp);
extern void ADCCompDisable(unsigned long ulBase, unsigned long ulComp);
extern void ADCCompFuncRangeSet(unsigned long ulBase, unsigned long ulRange);
extern void ADCDMAEnable(unsigned long ulBase);
extern void ADCDMADisable(unsigned long ulBase);
extern void ADCPowerModeSet(unsigned long ulBase, unsigned long ulPowerMode);
extern void ADCSampleTimeSet(unsigned long ulBase, unsigned long ulSampleTime);
extern void ADCGainSet(unsigned long ulBase, unsigned long ulMinusGain, 
                                 unsigned long ulPlusGain);
extern void ADCLongSampleTimeSet(unsigned long ulBase, 
                                 unsigned long ulLongSamTime);
extern void ADCSingleResolutionSet(unsigned long ulBase, 
                                   unsigned long ulSingleRes);
extern void ADCDifferentialResolutionSet(unsigned long ulBase, 
                                         unsigned long ulDiffRes);
extern void ADCConSpeedSelect(unsigned long ulBase, unsigned long ulSpeed);
extern void ADCMuxSelect(unsigned long ulBase, unsigned long ulMux);
extern void ADCBandgapConfigure(unsigned long ulBase, unsigned long ulInputMode);
extern void ADCTemperatureSensorConfigure(unsigned long ulBase, 
                                          unsigned long ulInputMode);
extern void ADCAlternateTriggerEnable(void);
extern void ADC0TPMTriggerEnable(void);
extern void ADC0PretriggerSet(unsigned long ulPretrigger);
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

