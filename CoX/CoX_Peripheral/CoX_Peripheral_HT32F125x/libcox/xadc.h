//*****************************************************************************
//
//! \file xadc.h
//! \brief Defines and Macros for ADC API.
//! \version V2.1.1.0
//! \date 3/21/2012
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
//! +------------------------+----------------+-------------+
//! |xADC Interrupt Source   |       CoX      |  HT32F125x  |
//! |------------------------|----------------|-------------|
//! |xADC_INT_COMP           |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADC_INT_END_CONVERSION |  Non-Mandatory |      N      |
//! |------------------------|----------------|-------------|
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
#define xADC_INT_END_CONVERSION (ADC_INT_END_CONVERSION | ADC_INT_END_CYCLE | ADC_INT_END_SUBGROUP)

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
//! +-------------------------+----------------+---------------------+
//! |xADC Event               |       CoX      |      HT32F125x      |
//! |-------------------------|----------------|---------------------|
//! |xADC_EVENT_$COMPx$       |  Non-Mandatory |          N          |
//! |-------------------------|----------------|---------------------|
//! |xADC_EVENT_END_CONVERSION|    Mandatory   |          Y          |
//! |-------------------------|----------------|---------------------|
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
//! +---------------------------+----------------+-------------+
//! |xADC Mode                  |       CoX      |  HT32F125x  |
//! |---------------------------|----------------|-------------|
//! |xADC_MODE_SCAN_SINGLE_CYCLE|    Mandatory   |      Y      |
//! |---------------------------|----------------|-------------|
//! |xADC_MODE_SCAN_CONTINUOUS  |  Non-Mandatory |      Y      |
//! |---------------------------|----------------|-------------|
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
//! \b PB2.
//!
//! \section xADC_Trigger_Source_Port 2. CoX Port Details
//! \verbatim
//! +---------------------------+----------------+-------------------------+
//! |xADC Trigger Source        |       CoX      |        HT32F125x        |
//! |---------------------------|----------------|-------------------------|
//! |xADC_TRIGGER_PROCESSOR     |    Mandatory   |            Y            |
//! |---------------------------|----------------|-------------------------|
//! |xADC_TRIGGER_EXT_$ShortPin$|  Non-Mandatory |   xADC_TRIGGER_EXT_PBn  |
//! |---------------------------|----------------|-------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Processor trigger (Software)
//
#define xADC_TRIGGER_PROCESSOR  ADC_TRIGGER_PROCESSOR

//
//! External Pin Event (such as Rising, Falling...) on PB0
//
#define xADC_TRIGGER_EXT_PB0    ADC_TRIGGER_EXT_PB0

//
//! External Pin Event (such as Rising, Falling...) on PB1
//
#define xADC_TRIGGER_EXT_PB1    ADC_TRIGGER_EXT_PB1

//
//! External Pin Event (such as Rising, Falling...) on PB2
//
#define xADC_TRIGGER_EXT_PB2    ADC_TRIGGER_EXT_PB2

//
//! External Pin Event (such as Rising, Falling...) on PB3
//
#define xADC_TRIGGER_EXT_PB3    ADC_TRIGGER_EXT_PB3

//
//! External Pin Event (such as Rising, Falling...) on PB4
//
#define xADC_TRIGGER_EXT_PB4    ADC_TRIGGER_EXT_PB4
//
//! External Pin Event (such as Rising, Falling...) on PB5
//
#define xADC_TRIGGER_EXT_PB5    ADC_TRIGGER_EXT_PB5

//
//! External Pin Event (such as Rising, Falling...) on PB6
//
#define xADC_TRIGGER_EXT_PB6    ADC_TRIGGER_EXT_PB6

//
//! External Pin Event (such as Rising, Falling...) on PB7
//
#define xADC_TRIGGER_EXT_PB7    ADC_TRIGGER_EXT_PB7

//
//! External Pin Event (such as Rising, Falling...) on PB8
//
#define xADC_TRIGGER_EXT_PB8    ADC_TRIGGER_EXT_PB8

//
//! External Pin Event (such as Rising, Falling...) on PB9
//
#define xADC_TRIGGER_EXT_PB9    ADC_TRIGGER_EXT_PB9

//
//! External Pin Event (such as Rising, Falling...) on PB10
//
#define xADC_TRIGGER_EXT_PB10   ADC_TRIGGER_EXT_PB10

//
//! External Pin Event (such as Rising, Falling...) on PB11
//
#define xADC_TRIGGER_EXT_PB11   ADC_TRIGGER_EXT_PB11

//
//! External Pin Event (such as Rising, Falling...) on PB12
//
#define xADC_TRIGGER_EXT_PB12   ADC_TRIGGER_EXT_PB12

//
//! External Pin Event (such as Rising, Falling...) on PB13
//
#define xADC_TRIGGER_EXT_PB13   ADC_TRIGGER_EXT_PB13

//
//! External Pin Event (such as Rising, Falling...) on PB14
//
#define xADC_TRIGGER_EXT_PB14   ADC_TRIGGER_EXT_PB14

//
//! External Pin Event (such as Rising, Falling...) on PB15
//
#define xADC_TRIGGER_EXT_PB15   ADC_TRIGGER_EXT_PB15

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
//! +-----------------------------+----------------+-------------+
//! |xADC Ext Trigger Mode        |       CoX      |  HT32F125x  |
//! |-----------------------------|----------------|-------------|
//! |xADC_TRIGGER_EXT_LOW_LEVEL   |  Non-Mandatory |      N      |
//! |-----------------------------|----------------|-------------|
//! |xADC_TRIGGER_EXT_HIGH_LEVEL  |  Non-Mandatory |      N      |
//! |-----------------------------|----------------|-------------|
//! |xADC_TRIGGER_EXT_RISING_EDGE |  Non-Mandatory |      Y      |
//! |-----------------------------|----------------|-------------|
//! |xADC_TRIGGER_EXT_FALLING_EDGE|  Non-Mandatory |      N      |
//! |-----------------------------|----------------|-------------|
//! |xADC_TRIGGER_EXT_BOTH_EDGE   |  Non-Mandatory |      N      |
//! |-----------------------------|----------------|-------------|
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
                                ADC_TRIGGER_EXT_RISING_EDGE

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
//! +----------------+----------------+------------------+
//! |xADC Step Config|       CoX      |    HT32F125x     |
//! |----------------|----------------|------------------|
//! |xADC_CTL_CH$x$  |  Non-Mandatory |   xADC_CTL_CH0   |
//! |                |                |   xADC_CTL_CH1   |
//! |                |                |   xADC_CTL_CH2   |
//! |                |                |   xADC_CTL_CH3   |
//! |                |                |   xADC_CTL_CH4   |
//! |                |                |   xADC_CTL_CH5   |
//! |                |                |   xADC_CTL_CH6   |
//! |                |                |   xADC_CTL_CH7   |
//! |----------------|----------------|------------------|
//! |xADC_CTL_TS     |  Non-Mandatory |        N         |
//! |----------------|----------------|------------------|
//! |xADC_CTL_CMP$x$ |  Non-Mandatory |        N         |
//! |----------------|----------------|------------------|
//! |xADC_CTL_D      |  Non-Mandatory |        N         |
//! |----------------|----------------|------------------|
//! |xADC_CTL_END    |  Non-Mandatory |        N         |
//! |----------------|----------------|------------------|
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
//! |xADC Comp ID    |       CoX      |    HT32F125x     |
//! |----------------|----------------|------------------|
//! |xADC_COMP_$x$   |  Non-Mandatory |         N        |
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
//! +-------------------------+----------------+---------------+
//! |xADC Comp Int Condition  |       CoX      |   HT32F125x   |
//! |-------------------------|----------------|---------------|
//! |xADC_COMP_INT_LOW        |  Non-Mandatory |       N       |
//! |-------------------------|----------------|---------------|
//! |xADC_COMP_INT_MID        |  Non-Mandatory |       N       |
//! |-------------------------|----------------|---------------|
//! |xADC_COMP_INT_HIGH       |  Non-Mandatory |       N       |
//! +-------------------------+----------------+---------------+ 
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
//! +------------------------+----------------+-------------+
//! |xADC API                |       CoX      |  HT32F125x  |
//! |------------------------|----------------|-------------|
//! |xADCConfigure           |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCStepConfigure       |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCIntCallbackInit     |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCIntEnable           |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCIntDisable          |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCEnable              |    Mandatory   |      N      |
//! |------------------------|----------------|-------------|
//! |xADCDisable             |    Mandatory   |      N      |
//! |------------------------|----------------|-------------|
//! |xADCProcessorTrigger    |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCDataGet             |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCOverflow            |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCOverflowClear       |    Mandatory   |      Y      |
//! |------------------------|----------------|-------------|
//! |xADCCompConditionConfig |  Non-Mandatory |      N      |
//! |------------------------|----------------|-------------|
//! |xADCCompRegionSet       |  Non-Mandatory |      N      |
//! |------------------------|----------------|-------------|
//! |xADCCompEnable          |  Non-Mandatory |      N      |
//! |------------------------|----------------|-------------|
//! |xADCCompDisable         |  Non-Mandatory |      N      |
//! |------------------------|----------------|-------------|
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
#define xADCEnable(ulBase)      0

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
#define xADCDisable(ulBase)     0

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

extern xtBoolean xADCOverflow(unsigned long ulBase);
extern void xADCOverflowClear(unsigned long ulBase);

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
            xASSERT(ulLowRef == ulHighRef);                                   \
            ADCCompDataSet(ulBase, ulCompID, ulLowRef, 1);                    \
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
#define xADCDataGet(ulBase, pulBuffer)                                       \
        ADCDataGet(ulBase, pulBuffer)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Channel_IDs HT32F125x ADC Channel ID
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Moni_IDs HT32F125x ADC Comparator ID
//! @{
//
//*****************************************************************************

//
// Watchdog lower threshold monitor.
//
#define ADC_MONI_L              0x00000001

//
// Watchdog upper threshold monitor.
//
#define ADC_MONI_U              0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Operation_Mode HT32F125x ADC Operation Mode
//! @{
//
//*****************************************************************************

//
//! A/D Converter Operation Mode is Single conversion
// 
#define ADC_OP_SINGLE           0x00000000

//
//! A/D Converter Operation Mode is Discontinuous conversion
//
#define ADC_OP_DISCONTINUOUS    0x00000003

//
//! A/D Converter Operation Mode is Continuous scan
// 
#define ADC_OP_CONTINUOUS       0x00000002


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Tigger_Source HT32F125x ADC Tigger Source
//! @{
//
//*****************************************************************************
//
//! Processor event(Software)
//
#define ADC_TRIGGER_PROCESSOR   0x00000001

//
//! External Pin event(external STADC pin PB0)
//
#define ADC_TRIGGER_EXT_PB0     0x00000000

//
//! External Pin event(external STADC pin PB1)
//
#define ADC_TRIGGER_EXT_PB1     0x00000100

//
//! External Pin event(external STADC pin PB2)
//
#define ADC_TRIGGER_EXT_PB2     0x00000200

//
//! External Pin event(external STADC pin PB3)
//
#define ADC_TRIGGER_EXT_PB3     0x00000300

//
//! External Pin event(external STADC pin PB4)
//
#define ADC_TRIGGER_EXT_PB4     0x00000400

//
//! External Pin event(external STADC pin PB5)
//
#define ADC_TRIGGER_EXT_PB5     0x00000500

//
//! External Pin event(external STADC pin PB6)
//
#define ADC_TRIGGER_EXT_PB6     0x00000600

//
//! External Pin event(external STADC pin PB7)
//
#define ADC_TRIGGER_EXT_PB7     0x00000700

//
//! External Pin event(external STADC pin PB8)
//
#define ADC_TRIGGER_EXT_PB8     0x00000800

//
//! External Pin event(external STADC pin PB9)
//
#define ADC_TRIGGER_EXT_PB9     0x00000900

//
//! External Pin event(external STADC pin PB10)
//
#define ADC_TRIGGER_EXT_PB10    0x00000A00

//
//! External Pin event(external STADC pin PB11)
//
#define ADC_TRIGGER_EXT_PB11    0x00000B00

//
//! External Pin event(external STADC pin PB12)
//
#define ADC_TRIGGER_EXT_PB12    0x00000C00

//
//! External Pin event(external STADC pin PB13)
//
#define ADC_TRIGGER_EXT_PB13    0x00000D00

//
//! External Pin event(external STADC pin PB14)
//
#define ADC_TRIGGER_EXT_PB14    0x00000E00

//
//! External Pin event(external STADC pin PB15)
//
#define ADC_TRIGGER_EXT_PB15    0x00000F00

//
//! GPTM0 Trigger
//
#define ADC_TRIGGER_GPTM0       0x00020000

//
//! GPTM1 Trigger
//
#define ADC_TRIGGER_GPTM1       0x00030000

//
//! GPTM MTO rising edge of GPTM Trigger
//
#define ADC_TRIGGER_GPTME_MT0   0x00000000

//
//! GPTM CH0 rising edge of GPTM Trigger
//
#define ADC_TRIGGER_GPTME_CH0   0x01000000

//
//! GPTM CH1 rising edge of GPTM Trigger
//
#define ADC_TRIGGER_GPTME_CH1   0x02000000

//
//! GPTM CH2 rising edge of GPTM Trigger
//
#define ADC_TRIGGER_GPTME_CH2   0x03000000

//
//! GPTM CH3 rising edge of GPTM Trigger
//
#define ADC_TRIGGER_GPTME_CH3   0x04000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_EXT_Trigger_Mode HT32F125x ADC External Tigger Mode
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
//! \addtogroup HT32F125x_ADC_Ints HT32F125x ADC Interrupt
//! \brief Values that show the ADC Interrupt source.
//! @{
//
//*****************************************************************************

//
//! Interrupt after single cycle conversion
//
#define ADC_INT_END_CONVERSION  0x00000001

//
//! Interrupt after subgroup conversion
//
#define ADC_INT_END_SUBGROUP    0x00000002

//
//! Interrupt after cycle conversion
//
#define ADC_INT_END_CYCLE       0x00000004

//
//!  Interrupt when the comparator lower
//
#define ADC_INT_MONIL           0x00010000

//
//! Interrupt when the comparator upper
//
#define ADC_INT_MONIU           0x00020000

//
//! Interrupt when data overwrite
//
#define ADC_INT_OVERW           0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Data_Status HT32F125x ADC Data Status
//! \brief Check the convertion data if valid or overrun.
//! @{
//
//*****************************************************************************

//
//! Channel n Data is valid
//
#define ADC_DATA_VALID          0x80000000

//
//! Channel n Data is invalid
//
#define ADC_DATA_INVALID        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Data_Resolution HT32F125x ADC Data Resolution
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
//! \addtogroup HT32F125x_ADC_Channel_Monitor HT32F125x ADC Channel Monitor
//! \brief Values that show the ADC Channel.
//! @{
//
//*****************************************************************************

//
//! A/D Converter all channels are monitored.
//
#define ADC_MONITOR_ADWALL      0x0000000A

//
//! A/D Converter Specific channel is monitored.
//
#define ADC_MONITOR_ADSPEC      0x00000000

//
//! ADC_IN0 is monitored
//
#define ADC_MONITOR_IN0         0x00000000

//
//! ADC_IN1 is monitored
//
#define ADC_MONITOR_IN1         0x00000100

//
//! ADC_IN2 is monitored
//
#define ADC_MONITOR_IN2         0x00000200

//
//! ADC_IN3 is monitored
//
#define ADC_MONITOR_IN3         0x00000300

//
//! ADC_IN4 is monitored
//
#define ADC_MONITOR_IN4         0x00000400

//
//! ADC_IN5 is monitored
//
#define ADC_MONITOR_IN5         0x00000500

//
//! ADC_IN6 is monitored
//
#define ADC_MONITOR_IN6         0x00000600

//
//! ADC_IN7 is monitored
//
#define ADC_MONITOR_IN7         0x00000700

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup HT32F125x_ADC_Exported_APIs HT32F125x ADC API
//! \brief HT32F125x ADC API Reference
//! @{
//
//*****************************************************************************
extern void ADCConfigure(unsigned long ulBase, unsigned long ulOpMode,
                         unsigned long ulTrigger);

extern void ADCProcessorTrigger(unsigned long ulBase);
extern void ADCExtiEventTrigger(unsigned long ulBase);
extern void ADCGptmEventTrigger(unsigned long ulBase);

extern unsigned long ADCDataStatus(unsigned long ulBase, unsigned long ulChannel);
extern unsigned long ADCDataGet(unsigned long ulBase, unsigned long *pulBuffer);

extern void ADCMonitorSet(unsigned long ulBase, unsigned long ulCompID,
                          unsigned long ulThreshold, unsigned long ulMonitor);

extern void ADCSampLenSet(unsigned long ulBase, unsigned long ulChannel,
                          unsigned long ulSampTime);
extern void ADCMoniEnable(unsigned long ulBase, unsigned long ulComp);
extern void ADCMoniDisable(unsigned long ulBase, unsigned long ulComp);

extern void ADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long ADCIntStatus(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCConverLenSet(unsigned long ulBase, unsigned long ulSeqLen, 
                            unsigned long ulSubLen);
extern void ADCSequenceIndexSet(unsigned long ulBase, unsigned long *ulChannel);
extern void ADCReset(unsigned long ulBase);
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

