//*****************************************************************************
//
//! \file xcomp.h
//! \brief Defines and Macros for the analog comparator API.
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
//{
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
//! \addtogroup xACMP_Config xACMP User Configuration
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Config_Stellaris xACMP User Configuration Stellaris Part
//! @{
//
//*****************************************************************************

//
//! In Stellaris mcus, the comparator can tigger the ADC. Users can change
//! macro to other tigger sense.
//! - COMP_TRIG_NONE - No ADC trigger
//! - COMP_TRIG_HIGH  - Trigger when high
//! - COMP_TRIG_LOW - Trigger when low
//! - COMP_TRIG_FALL - Trigger on falling edge
//! - COMP_TRIG_RISE - Trigger on rising edge
//! - COMP_TRIG_BOTH - Trigger on both edges
//
#define xACMP_CONFIG_STELLARIS_TRIG_SENSE                                     \
        COMP_TRIG_BOTH

//
//! In cox standard provisions, comparator can be configured to cause an
//! interrupt when the comparator output value changes. Users can change it,
//! depending on the specific application.
//! - COMP_INT_HIGH - Interrupt when high
//! - COMP_INT_LOW - Interrupt when low
//! - COMP_INT_FALL - Interrupt on falling edge
//! - COMP_INT_RISE -Interrupt on rising edge
//! - COMP_INT_BOTH - Interrupt on both edges
//
#define xACMP_CONFIG_STELLARIS_INT_SENSE                                      \
        COMP_INT_BOTH

//
//! In Stellaris mcus, comparator output can be inverted or not, values can be:
//! - COMP_OUTPUT_NORMAL - Comparator output normal
//! - COMP_OUTPUT_INVERT - Comparator output inverted
//
#define xACMP_CONFIG_STELLARIS_OUTPUT_MODE                                    \
        COMP_OUTPUT_NORMAL
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
//! \addtogroup xACMP_Analog_Src_Positive xACMP Positive(ACMP+) Input Source
//!
//! \section xACMP_Analog_Src_Positive_Sec_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+---------+
//! |xACMP ACMP+ Source      |       CoX      |Stellaris|
//! |------------------------|----------------|---------|
//! |xACMP_ASRCP_PIN         |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMP_ASRCP_REF         |  Non-Mandatory |    Y    |
//! +------------------------+----------------+---------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Dedicated Comp+ pin
//
#define xACMP_ASRCP_PIN         COMP_ASRCP_PIN  

//
//! Internal voltage reference
//
#define xACMP_ASRCP_REF         COMP_ASRCP_REF 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Analog_Src_Negative xACMP Negative(ACMP-) Input Source
//!
//! \section xACMP_Analog_Src_Negative_Sec_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+---------+
//! |xACMP ACMP- Source      |       CoX      |Stellaris|
//! |------------------------|----------------|---------|
//! |xACMP_ASRCN_PIN         |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMP_ASRCN_REF         |  Non-Mandatory |    Y    |
//! +------------------------+----------------+---------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Dedicated Comp+ pin
//
#define xACMP_ASRCN_PIN         0x00000000

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
//! +------------------------+----------------+-------------------+
//! |xACMP Int Vref          |       CoX      |    Stellaris      |
//! |------------------------|----------------|-------------------|
//! |xACMP_REF_*V            |    Mandatory   |xACMP_REF_0V       |
//! |                        |                |xACMP_REF_0_1375V  |
//! |                        |                |xACMP_REF_0_275V   | 
//! |                        |                |xACMP_REF_0_4125V  |
//! |                        |                |xACMP_REF_0_55V    |
//! |                        |                |xACMP_REF_0_6875V  |
//! |                        |                |xACMP_REF_0_825V   |
//! |                        |                |xACMP_REF_0_928125V| 
//! |                        |                |xACMP_REF_0_9625V  |
//! |                        |                |xACMP_REF_1_03125V | 
//! |                        |                |xACMP_REF_1_134375V|
//! |                        |                |xACMP_REF_1_1V     |  
//! |                        |                |xACMP_REF_1_2375V  |  
//! |                        |                |xACMP_REF_1_340625V| 
//! |                        |                |xACMP_REF_1_375V   |
//! |                        |                |xACMP_REF_1_44375V |  
//! |                        |                |xACMP_REF_1_5125V  | 
//! |                        |                |xACMP_REF_1_546875V| 
//! |                        |                |xACMP_REF_1_65V    | 
//! |                        |                |xACMP_REF_1_753125V|
//! |                        |                |xACMP_REF_1_7875V  | 
//! |                        |                |xACMP_REF_1_85625V |  
//! |                        |                |xACMP_REF_1_925V   |  
//! |                        |                |xACMP_REF_1_959375V| 
//! |                        |                |xACMP_REF_2_0625V  |
//! |                        |                |xACMP_REF_2_165625V|
//! |                        |                |xACMP_REF_2_26875V |
//! |                        |                |xACMP_REF_2_371875V|
//! +------------------------+----------------+-------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Internal reference of 0V
//
#define xACMP_REF_0V            COMP_REF_0V  

//
//! Internal reference of 0.1375V
//
#define xACMP_REF_0_1375V       COMP_REF_0_1375V  

//
//! Internal reference of 0.275V
//
#define xACMP_REF_0_275V        COMP_REF_0_275V

//
//! Internal reference of 0.4125V
//
#define xACMP_REF_0_4125V       COMP_REF_0_4125V

//
//! Internal reference of 0.55V
//
#define xACMP_REF_0_55V         COMP_REF_0_55V

//
//! Internal reference of 0.6875V
//
#define xACMP_REF_0_6875V       COMP_REF_0_6875V

//
//! Internal reference of 0.825V
//
#define xACMP_REF_0_825V        COMP_REF_0_825V

//
//! Internal reference of 0.928125V
//
#define xACMP_REF_0_928125V     COMP_REF_0_928125V

//
//! Internal reference of 0.9625V
//
#define xACMP_REF_0_9625V       COMP_REF_0_9625V

//
//! Internal reference of 1.03125V
//
#define xACMP_REF_1_03125V      COMP_REF_1_03125V

//
//! Internal reference of 1.134375V
//
#define xACMP_REF_1_134375V     COMP_REF_1_134375V

//
//! Internal reference of 1.1V
//
#define xACMP_REF_1_1V          COMP_REF_1_1V

//
//! Internal reference of 1.2375V
//
#define xACMP_REF_1_2375V       COMP_REF_1_2375V

//
//! Internal reference of 1.340625V
//
#define xACMP_REF_1_340625V     COMP_REF_1_340625V

//
//! Internal reference of 1.375V
//
#define xACMP_REF_1_375V        COMP_REF_1_375V

//
//! Internal reference of 1.44375V
//
#define xACMP_REF_1_44375V      COMP_REF_1_44375V

//
//! Internal reference of 1.5125V
//
#define xACMP_REF_1_5125V       COMP_REF_1_5125V

//
//! Internal reference of 1.546875V
//
#define xACMP_REF_1_546875V     COMP_REF_1_546875V

//
//! Internal reference of 1.65V
//
#define xACMP_REF_1_65V         COMP_REF_1_65V

//
//! Internal reference of 1.753125V
//
#define xACMP_REF_1_753125V     COMP_REF_1_753125V

//
//! Internal reference of 1.7875V
//
#define xACMP_REF_1_7875V       COMP_REF_1_7875V

//
//! Internal reference of 1.85625V
//
#define xACMP_REF_1_85625V      COMP_REF_1_85625V

//
//! Internal reference of 1.925V
//
#define xACMP_REF_1_925V        COMP_REF_1_925V

//
//! Internal reference of 1.959375V
//
#define xACMP_REF_1_959375V     COMP_REF_1_959375V

//
//! Internal reference of 2.0625V
//
#define xACMP_REF_2_0625V       COMP_REF_2_0625V

//
//! Internal reference of 2.165625V
//
#define xACMP_REF_2_165625V     COMP_REF_2_165625V

//
//! Internal reference of 2.26875V
//
#define xACMP_REF_2_26875V      COMP_REF_2_26875V

//
//! Internal reference of 2.371875V
//
#define xACMP_REF_2_371875V     COMP_REF_2_371875V

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
//! |xACMP ACMP ID      |       CoX      |Stellaris|
//! |---------------- --|----------------|---------|
//! |xACMP_*            |    Mandatory   | xACMP_0 |
//! |                   |                | xACMP_1 |
//! |                   |                | xACMP_2 |
//! +-------------------+----------------+---------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Comparator 0
//
#define xACMP_0                 0x00000000

//
// Comparator 1
//
#define xACMP_1                 0x00000001

//
// Comparator 2
//
#define xACMP_2                 0x00000002


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xACMP_Exported_APIs xACMP API
//!
//! \section xACMP_Exported_APIs_Port CoX Port Details
//!
//! \verbatim
//! +------------------------+----------------+---------+
//! |xACMP API               |       CoX      |Stellaris|
//! |------------------------|----------------|---------|
//! |xACMPConfigure          |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMPEnable             |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMPDisable            |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMPIntCallbackInit    |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMPIntEnable          |    Mandatory   |    Y    |
//! |------------------------|----------------|---------|
//! |xACMPIntDisable         |    Mandatory   |    Y    |
//! +------------------------+----------------+---------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configures a comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator to configure.
//! \param ulConfig is the configuration of the comparator.
//!
//! This function configures a comparator.  The \e ulConfig parameter is the
//! result of a logical OR operation between the \b xACMP_ASRCP_xxx, 
//! and \b xACMP_ASRCN_xxx values.
//!
//! The \b ACMP_ASRCP_xxx term can take on the following values:
//!
//! - \b xACMP_ASRCP_PIN to use the dedicated Comp+ pin as the reference
//! voltage.
//! - \b xACMP_ASRCP_REF to use the internally generated voltage as the
//! reference voltage.
//! .
//!
//! The \b xACMP_ASRCN_xxx term can take on the following values:
//!
//! - \b xACMP_ASRCN_PIN to use the deidicated Comp- pins as the reference
//! voltage.
//! - \b xACMP_ASRCP_REF to use the internally generated voltage as the
//! reference voltage.( This is not exsit in the stellaris mcus).
//!.
//!
//!\note In the Stellaris implement, It set the tigger sense, interrupt 
//! sense, output mode through macros. more info, refrence 
//! \ref xACMP_Config_Stellaris.
//! 
//! \return None.
//
//*****************************************************************************

#define xACMPConfigure(ulBase, ulComp, ulConfig)                              \
        ComparatorConfigure(ulBase, ulComp,                                   \
                            ulConfig |                                        \
                            xACMP_CONFIG_STELLARIS_TRIG_SENSE |               \
                            xACMP_CONFIG_STELLARIS_INT_SENSE |                \
                            xACMP_CONFIG_STELLARIS_OUTPUT_MODE)


//*****************************************************************************
//
//! \brief Sets the internal reference voltage.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulRef is the desired reference voltage.
//!
//! This function sets the internal reference voltage value. such as 
//! \ref xACMP_REF_0V, more refrence \ref xACMP_Int_Ref_Voltage.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPRefSet(ulBase, ulRef)                                            \
        ComparatorRefSet(ulBase, ulRef)

//*****************************************************************************
//
//! \brief Enables the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the ID of the comparator.
//!
//! This function enables comparator. 
//!
//! \note In Stellaris implement, this function do nothing.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPEnable(ulBase, ulCompID)                                         \
        {}

//*****************************************************************************
//
//! \brief Disables the comparator.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the ID of the comparator.
//!
//! This function disables comparator. 
//!
//! \note In Stellaris implement, this function do nothing.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPDisable(ulBase, ulCompID)                                        \
        {}

extern void xACMPIntCallbackInit(unsigned long ulBase, unsigned long ulCompID,
                                 xtEventCallback pfnCallback);

//*****************************************************************************
//
//! \brief Enables the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//!
//! This function enables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPIntEnable(ulBase, ulCompID)                                      \
        ComparatorIntEnable(ulBase, ulCompID)

//*****************************************************************************
//
//! \brief Disables the comparator interrupt.
//!
//! \param ulBase is the base address of the comparator module.
//! \param ulComp is the index of the comparator.
//!
//! This function disables generation of an interrupt from the specified
//! comparator.  Only comparators whose interrupts are enabled can be reflected
//! to the processor.
//!
//! \return None.
//
//*****************************************************************************
#define xACMPIntDisable(ulBase, ulCompID)                                     \
        ComparatorIntDisable(ulBase, ulCompID)


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
//! \addtogroup Stellaris_COMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_COMP_Configure Comparator Configuration
//! 
// Values that can be passed to ComparatorConfigure() as the ulConfig
// parameter.  For each group (i.e. COMP_TRIG_xxx, COMP_INT_xxx, etc.), one of
// the values may be selected and combined together with values from the other
// groups via a logical OR.
//! @{
//
//*****************************************************************************

#define COMP_TRIG_NONE          0x00000000  // No ADC trigger
#define COMP_TRIG_HIGH          0x00000880  // Trigger when high
#define COMP_TRIG_LOW           0x00000800  // Trigger when low
#define COMP_TRIG_FALL          0x00000820  // Trigger on falling edge
#define COMP_TRIG_RISE          0x00000840  // Trigger on rising edge
#define COMP_TRIG_BOTH          0x00000860  // Trigger on both edges
#define COMP_INT_HIGH           0x00000010  // Interrupt when high
#define COMP_INT_LOW            0x00000000  // Interrupt when low
#define COMP_INT_FALL           0x00000004  // Interrupt on falling edge
#define COMP_INT_RISE           0x00000008  // Interrupt on rising edge
#define COMP_INT_BOTH           0x0000000C  // Interrupt on both edges
#define COMP_ASRCP_PIN          0x00000000  // Dedicated Comp+ pin
#define COMP_ASRCP_PIN0         0x00000200  // Comp0+ pin
#define COMP_ASRCP_REF          0x00000400  // Internal voltage reference

#define COMP_OUTPUT_NORMAL      0x00000000  // Comparator output normal
#define COMP_OUTPUT_INVERT      0x00000002  // Comparator output inverted

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_COMP_Ref_Set Comparator Reference voltage Set
//! 
//! Values that can be passed to ComparatorSetRef() as the ulRef parameter.
//! @{
//
//*****************************************************************************

//
//! Turn off the internal reference
//
#define COMP_REF_OFF            0x00000000
//
//! Internal reference of 0V
//
#define COMP_REF_0V             0x00000300  

//
//! Internal reference of 0.1375V
//
#define COMP_REF_0_1375V        0x00000301  

//
//! Internal reference of 0.275V
//
#define COMP_REF_0_275V         0x00000302

//
//! Internal reference of 0.4125V
//
#define COMP_REF_0_4125V        0x00000303

//
//! Internal reference of 0.55V
//
#define COMP_REF_0_55V          0x00000304

//
//! Internal reference of 0.6875V
//
#define COMP_REF_0_6875V        0x00000305

//
//! Internal reference of 0.825V
//
#define COMP_REF_0_825V         0x00000306

//
//! Internal reference of 0.928125V
//
#define COMP_REF_0_928125V      0x00000201

//
//! Internal reference of 0.9625V
//
#define COMP_REF_0_9625V        0x00000307

//
//! Internal reference of 1.03125V
//
#define COMP_REF_1_03125V       0x00000202

//
//! Internal reference of 1.134375V
//
#define COMP_REF_1_134375V      0x00000203

//
//! Internal reference of 1.1V
//
#define COMP_REF_1_1V           0x00000308

//
//! Internal reference of 1.2375V
//
#define COMP_REF_1_2375V        0x00000309

//
//! Internal reference of 1.340625V
//
#define COMP_REF_1_340625V      0x00000205

//
//! Internal reference of 1.375V
//
#define COMP_REF_1_375V         0x0000030A

//
//! Internal reference of 1.44375V
//
#define COMP_REF_1_44375V       0x00000206

//
//! Internal reference of 1.5125V
//
#define COMP_REF_1_5125V        0x0000030B

//
//! Internal reference of 1.546875V
//
#define COMP_REF_1_546875V      0x00000207

//
//! Internal reference of 1.65V
//
#define COMP_REF_1_65V          0x0000030C

//
//! Internal reference of 1.753125V
//
#define COMP_REF_1_753125V      0x00000209

//
//! Internal reference of 1.7875V
//
#define COMP_REF_1_7875V        0x0000030D

//
//! Internal reference of 1.85625V
//
#define COMP_REF_1_85625V       0x0000020A

//
//! Internal reference of 1.925V
//
#define COMP_REF_1_925V         0x0000030E

//
//! Internal reference of 1.959375V
//
#define COMP_REF_1_959375V      0x0000020B

//
//! Internal reference of 2.0625V
//
#define COMP_REF_2_0625V        0x0000030F

//
//! Internal reference of 2.165625V
//
#define COMP_REF_2_165625V      0x0000020D

//
//! Internal reference of 2.26875V
//
#define COMP_REF_2_26875V       0x0000020E

//
//! Internal reference of 2.371875V
//
#define COMP_REF_2_371875V      0x0000020F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_COMP_Exported_APIs
//! @{
//
//*****************************************************************************

extern void ComparatorConfigure(unsigned long ulBase, unsigned long ulComp,
                                unsigned long ulConfig);
extern void ComparatorRefSet(unsigned long ulBase, unsigned long ulRef);
extern xtBoolean ComparatorValueGet(unsigned long ulBase, unsigned long ulComp);
extern void ComparatorIntEnable(unsigned long ulBase, unsigned long ulComp);
extern void ComparatorIntDisable(unsigned long ulBase, unsigned long ulComp);
extern xtBoolean ComparatorIntStatus(unsigned long ulBase, unsigned long ulComp,
                                     xtBoolean bMasked);
extern void ComparatorIntClear(unsigned long ulBase, unsigned long ulComp);

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
//}
#endif

#endif // __xACMP_H__

