//*****************************************************************************
//
//! \file xacmp.h
//! \brief Defines and Macros for the analog comparator API.
//! \version V2.2.1.0
//! \date 8/23/2011
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

#ifndef __xACMP_H__
#define __xACMP_H__

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
//! \addtogroup ACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Analog_Src_Positive xACMP Positive(ACMP+) Input Source
//! \brief Analog comparator negative input select.
//!
//! \section xACMP_Analog_Src_Positive_Sec_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+--------+
//! |xACMP ACMP+ Source      |       CoX      |   KLx  |
//! |------------------------|----------------|--------|
//! |xACMP_ASRCP_PIN         |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMP_ASRCP_REF         |  Non-Mandatory |    N   |
//! +------------------------+----------------+--------+
//! \endverbatim
//! @{
//
//*****************************************************************************
//
//! Dedicated Comp+ pin
//
#define xACMP_ASRCP_PIN_IN0     0x00000000
#define xACMP_ASRCP_PIN_IN1     0x00000008
#define xACMP_ASRCP_PIN_IN2     0x00000010
#define xACMP_ASRCP_PIN_IN3     0x00000018
#define xACMP_ASRCP_PIN_IN4     0x00000020
#define xACMP_ASRCP_PIN_IN5     0x00000028
#define xACMP_ASRCP_PIN_IN6     0x00000030
#define xACMP_ASRCP_PIN_IN7     0x00000038

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Analog_Src_Negative xACMP Negative(ACMP-) Input Source
//! \brief Analog comparator Negative input select.
//!
//! \section xACMP_Analog_Src_Negative_Sec_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+--------+
//! |xACMP ACMP- Source      |       CoX      |   KLx  |
//! |------------------------|----------------|--------|
//! |xACMP_ASRCN_PIN         |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMP_ASRCN_REF         |  Non-Mandatory |    Y   |
//! +------------------------+----------------+--------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Dedicated Comp- pin
//
#define xACMP_ASRCN_PIN_IN0     0x00000000  
#define xACMP_ASRCN_PIN_IN1     0x00000001
#define xACMP_ASRCN_PIN_IN2     0x00000002
#define xACMP_ASRCN_PIN_IN3     0x00000003
#define xACMP_ASRCN_PIN_IN4     0x00000004
#define xACMP_ASRCN_PIN_IN5     0x00000005
#define xACMP_ASRCN_PIN_IN6     0x00000006
#define xACMP_ASRCN_PIN_IN7     0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Int_Ref_Voltage xACMP Internal Refrence Voltage
//! \brief Analog Comparator Internal Refrence Voltage select.
//!
//! There may be servral configurations of the internal Vref. Here is a list
//!  of the Vref.Values of Vref like xACMP_REF_*V, can be:
//! - xACMP_REF_?V - Example 2V
//! - xACMP_REF_?_?V - Example 2.1V
//! - xACMP_REF_?_??V - Example 2.13V
//! - xACMP_REF_?_???V - Example 1.375V
//! - xACMP_REF_?_????V - Example 1.2375V
//! .
//! \section xACMP_Int_Ref_Voltage_Sec CoX Port Details
//! \verbatim
//! +------------------------+----------------+----------------------+
//! |xACMP Int Vref          |       CoX      |          KLx         |
//! |------------------------|----------------|----------------------|
//! |xACMP_REF_*V            |    Mandatory   |    xACMP_REF_1_2V    |
//! +------------------------+----------------+----------------------+
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//
//! Internal reference of 1.2V
//
#define xACMP_REF_1_2V          0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Comparator_IDs xACMP Analog Comparator ID
//! \brief Analog Comparator ID (index).
//!
//! The ID index is always like 0£¬ 1, and so on.
//!
//! \section xACMP_Comparator_IDs_Sec_Port CoX Port Details
//! \verbatim
//! +-------------------+----------------+---------+
//! |xACMP ACMP ID      |       CoX      |   KLx   |
//! |---------------- --|----------------|---------|
//! |xACMP_*            |    Mandatory   | xACMP_0 |
//! |                   |                | xACMP_1 |
//! +-------------------+----------------+---------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Comparator 0
//
#define xACMP_0             0x00000000

//
//! Comparator 1
//
#define xACMP_1             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Exported_APIs xACMP API
//! \brief Analog Comparator API Reference.
//!
//! \section xACMP_Exported_APIs_Port CoX Port Details
//!
//! \verbatim
//! +------------------------+----------------+--------+
//! |xACMP API               |       CoX      |   KLx  |
//! |------------------------|----------------|--------|
//! |xACMPConfigure          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMPEnable             |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMPDisable            |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMPIntCallbackInit    |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMPIntEnable          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xACMPIntDisable         |    Mandatory   |    Y   |
//! +------------------------+----------------+--------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configures a comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID(index) of the comparator to configure.
//! Refrence \ref xACMP_Comparator_IDs.
//! \param ulConfig is the configuration of the comparator.
//!
//! This function configures a comparator.  The \e ulConfig parameter is the
//! result of a logical OR operation between the \b ACMP_ASRCP_xxx, 
//! and \b ACMP_ASRCN_xxx values.
//!
//! The \b ACMP_ASRCP_xxx is determines the ACMP+ source, 
//! values refrence \ref xACMP_Analog_Src_Positive.
//!
//! The \b ACMP_ASRCP_xxx is determines the ACMP- source:
//! values refrence \ref xACMP_Analog_Src_Negative.
//! 
//! \return None.
//
//*****************************************************************************

#define xACMPConfigure(ulBase, ulCompID, ulConfig)                            \
        ACMPConfigure(ulBase, ulCompID, ulConfig);

//*****************************************************************************
//
//! \brief Enable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function enables a comparator. 
//!
//! \return None.
//
//*****************************************************************************
#define xACMPEnable(ulBase, ulCompID)                                         \
        ACMPEnable(ulBase, ulCompID)

//*****************************************************************************
//
//! \brief Disable the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function disables a comparator. 
//!
//! \return None.
//
//*****************************************************************************
#define xACMPDisable(ulBase, ulCompID)                                        \
        ACMPDisable(ulBase, ulCompID)

extern void xACMPIntCallbackInit(unsigned long ulBase, unsigned long ulCompID,
                                 xtEventCallback pfnCallback);

//*****************************************************************************
//
//! \brief Enable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID(index) of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function enables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPIntEnable(ulBase, ulCompID)                                      \
        ACMPIntEnable(ulBase, ulCompID)

//*****************************************************************************
//
//! \brief Disable the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulCompID is the ID(index) of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPIntDisable(ulBase, ulCompID)                                     \
        ACMPIntDisable(ulBase, ulCompID)

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
//! \addtogroup KLx_ACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Interrupt_Type KLx ACMP Interrupt Type
//! \brief Analog comparator Interrupt Type.
//! The following are values that can be passed to the ACMPIntEnable()
//! API as the ulIntType parameter. 
//! @{
//
//*****************************************************************************

//
//! Comparator Interrupt Enable Rising
//
#define ACMP_INT_RISING         0x10  

//
//! Comparator Interrupt Enable Falling
//
#define ACMP_INT_FALLING        0x08 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Filter_Sample_Count KLx Filter Sample Count
//! \brief Analog comparator Filter Sample Count.
//! The following are values that can be passed to the CMPFilterSampleCountSet()
//! API as the ulCount parameter. 
//! @{
//
//*****************************************************************************

//
//! Filter is disabled. If SE = 1, then COUT is a logic 0. This is not a legal 
//!state, and is not recommended. If SE = 0, COUT = COUTA.
//
#define CMP_FILTER_SAMPLE_COUNT_0                                             \
                                0x00 

//
//! One sample must agree. The comparator output is simply sampled.
//
#define CMP_FILTER_SAMPLE_COUNT_1                                             \
                                0x10

//
//! 2 consecutive samples must agree.
//
#define CMP_FILTER_SAMPLE_COUNT_2                                            \
                                0x20

//
//! 3 consecutive samples must agree.
//
#define CMP_FILTER_SAMPLE_COUNT_3                                            \
                                0x30

//
//! 4 consecutive samples must agree.
//
#define CMP_FILTER_SAMPLE_COUNT_4                                            \
                                0x40

//
//! 5 consecutive samples must agree.
//
#define CMP_FILTER_SAMPLE_COUNT_5                                            \
                                0x50

//
//! 6 consecutive samples must agree.
//
#define CMP_FILTER_SAMPLE_COUNT_6                                            \
                                0x60

//
//! 7 consecutive samples must agree.
//
#define CMP_FILTER_SAMPLE_COUNT_7                                            \
                                0x70
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Hysteresis_Level KLx Filter Hysteresis Level
//! \brief Analog comparator Hysteresis Level.
//! The following are values that can be passed to the CMPHystersisLevelSet()
//! API as the ulLevel parameter. 
//! @{
//
//*****************************************************************************

//
//! Level 0
//
#define CMP_HYSTERESIS_LEVEL_0  0x00 

//
//! Level 1
//
#define CMP_HYSTERESIS_LEVEL_1  0x01

//
//! Level 2
//
#define CMP_HYSTERESIS_LEVEL_2  0x02

//
//! Level 3
//
#define CMP_HYSTERESIS_LEVEL_3  0x03  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_CMP_Power_Mode KLx CMP Power Mode Select
//! \brief CMP Power Mode Select
//! The following are values that can be passed to the CMPPowerModeSet()
//! API as the ulPowerMode parameter. 
//! @{
//
//*****************************************************************************

//
//! Low-Speed (LS) Comparison mode selected.
//
#define CMP_POWER_MODE_LS       0x00

//
//! High-Speed (HS) Comparison mode selected.
//
#define CMP_POWER_MODE_HS       0x10

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_CMP_Output KLx CMP Output Select
//! \brief CMP Output Select
//! The following are values that can be passed to the CMPOutputSet()
//! API as the ulOutput parameter. 
//! @{
//
//*****************************************************************************

//
//! Set the filtered comparator output (CMPO) to equal COUT.
//
#define CMP_OUTPUT_COUT         0x00

//
//! et the unfiltered comparator output (CMPO) to equal COUTA.
//
#define CMP_OUTPUT_COUTA        0x04

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Exported_APIs KLx ACMP API
//! \brief KLx ACMP API Reference.
//! @{
//
//*****************************************************************************

extern void ACMPConfigure(unsigned long ulBase, unsigned long ulCompID, 
                          unsigned long ulConfig);
extern void ACMPEnable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPDisable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPIntEnable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPIntDisable(unsigned long ulBase, unsigned long ulComp);
extern xtBoolean ACMPIntStatus(unsigned long ulBase, unsigned long ulComp);
extern void ACMPIntClear(unsigned long ulBase, unsigned long ulComp);
extern void CMPFilterSampleCountSet(unsigned long ulBase, unsigned long ulCount);
extern void CMPHystersisLevelSet(unsigned long ulBase, unsigned long ulLevel);
extern void ACMPSampleEnable(unsigned long ulBase);
extern void ACMPSampleDisable(unsigned long ulBase);
extern void ACMPWindowingModeEnable(unsigned long ulBase);
extern void ACMPWindowingModeDisable(unsigned long ulBase);
extern void ACMPTriggerModeEnable(unsigned long ulBase);
extern void ACMPTriggerModeDisable(unsigned long ulBase);
extern void ACMPComparatorOutputPinEnable(unsigned long ulBase);
extern void ACMPComparatorOutputPinDisable(unsigned long ulBase);
extern void ACMPInvertEnable(unsigned long ulBase);
extern void ACMPInvertDisable(unsigned long ulBase);
extern void CMPPowerModeSet(unsigned long ulBase, unsigned long ulPowerMode);
extern void CMPOutputSet(unsigned long ulBase, unsigned long ulOutput);
extern void CMPFilterSamplePeriodSet(unsigned long ulBase, unsigned long ulPeriod);
extern void CMPDMAEnable(unsigned long ulBase);
extern void CMPDMADisable(unsigned long ulBase);
extern void ACMPIntEnable2(unsigned long ulBase, unsigned long ulIntType);
extern void ACMPIntDisable2(unsigned long ulBase, unsigned long ulIntType);
extern void ACMPPassThroughModeEnable(unsigned long ulBase);
extern void ACMPPassThroughModeDisable(unsigned long ulBase);
extern void ACMPDACEnable(unsigned long ulBase);
extern void ACMPDACDisable(unsigned long ulBase);
extern void CMPDACOutputVoltageSet(unsigned long ulBase, unsigned long ulVoltage);
extern void CMPInputMuxSet(unsigned long ulBase, unsigned long ulPlus,
                           unsigned long ulMinus);

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

#endif // __xACMP_H__


