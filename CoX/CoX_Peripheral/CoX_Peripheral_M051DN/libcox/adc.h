//*****************************************************************************
//
//! \file adc.h
//! \brief Defines and Macros for ADC API.
//! \version V2.1.1.0
//! \date 12/29/2011
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

#ifndef __ADC_H__
#define __ADC_H__

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
//! \addtogroup M051_ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_ADC_Channel_IDs M051 ADC Channel ID
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
//! \addtogroup M051_ADC_Comp_IDs M051 ADC Comparator ID
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
//! \addtogroup M051_ADC_Input_Mode M051 ADC Input Mode
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
#define ADC_INPUT_DIFF          0x00000400

//
//! A/D differential input Mode Output Format is unsigned format.
//
#define ADC_DIFF_UNSIGNED       0x00000000

//
//! A/D differential input Mode Output Format is 2'complement format
//
#define ADC_DIFF_2C             0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_ADC_Operation_Mode M051 ADC Operation Mode
//! @{
//
//*****************************************************************************

//
//! A/D Converter Operation Mode is Single conversion
// 
#define ADC_OP_SINGLE           0x00000000

//
//! A/D Converter Operation Mode is Burst conversion
//
#define ADC_OP_BURST            0x00000004

//
//! A/D Converter Operation Mode is Single-cycle scan
// 
#define ADC_OP_SINGLE_CYCLE     0x00000008

//
//! A/D Converter Operation Mode is Continuous scan
// 
#define ADC_OP_CONTINUOUS       0x0000000C


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_ADC_Tigger_Source M051 ADC Tigger Source
//! @{
//
//*****************************************************************************
//
//! Processor event(Software)
//
#define ADC_TRIGGER_PROCESSOR   0x00000000

//
//! External Pin event(external STADC pin PD2)
//
#define ADC_TRIGGER_EXT_PD2     0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_ADC_EXT_Trigger_Mode M051 ADC External Tigger Mode
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
//! \addtogroup M051_ADC_Channel7_Source M051_ADC Channel 7 Source
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
//! \addtogroup M051_ADC_Ints M051 ADC Interrupt
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
#define ADC_INT_COMP0           0x00000002

//
//! Interrupt when the comparator 1 match
//
#define ADC_INT_COMP1           0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_ADC_Data_Status M051 ADC Data Status
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
//! \addtogroup M051_ADC_Data_Resolution M051 ADC Data Resolution
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
//! \addtogroup M051_ADC_Comp_Conditions M051 ADC Comparator Interrupt Condition
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
#define ADC_COMP_GREATER_EQUAL  0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_ADC_Exported_APIs M051 ADC API
//! \brief M051 ADC API Reference
//! @{
//
//*****************************************************************************
extern void ADCConfigure(unsigned long ulBase, unsigned long ulInputMode,
                         unsigned long ulOpMode, unsigned long ulTrigger);

extern void ADCChannelEnable(unsigned long ulBase, unsigned long ulChannel);
extern void ADCChannelDisable(unsigned long ulBase, unsigned long ulChannel);
extern void ADCChannle7Configure(unsigned long ulBase, 
                                 unsigned long ulInputSrc);

extern void ADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long ADCIntStatus(unsigned long ulBase);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulIntFlags);

extern void ADCEnable(unsigned long ulBase);
extern void ADCDisable(unsigned long ulBase);

extern void ADCProcessorTrigger(unsigned long ulBase);
extern void ADCConvertStop(unsigned long ulBase);
extern xtBoolean ADCBusy(unsigned long ulBase);

extern unsigned long ADCDataStatus(unsigned long ulBase, 
                                   unsigned long ulChannel);
extern unsigned long ADCDataGet(unsigned long ulBase, unsigned long ulChannel);

extern void ADCCompConfigure(unsigned long ulBase, unsigned long ulComp, 
                             unsigned long ulCompChannel, 
                             unsigned long ulCondition);
extern void ADCCompDataSet(unsigned long ulBase, unsigned long ulComp,
                           unsigned long ulCompData, 
                           unsigned long ulMatchCnt);
extern void ADCCompEnable(unsigned long ulBase, unsigned long ulComp);

extern void ADCCompDisable(unsigned long ulBase, unsigned long ulComp);

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

