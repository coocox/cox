//*****************************************************************************
//
//! \file xacmp.h
//! \brief Defines and Macros for the analog comparator API.
//! \version V2.2.1.0
//! \date 11/20/2011
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
//! |xACMP ACMP+ Source      |       CoX      | NUC1xx |
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
#define xACMP_ASRCP_PIN         0

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
//! |xACMP ACMP- Source      |       CoX      | NUC1xx |
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
#define xACMP_ASRCN_PIN         0  

//
//!  Comp-(Analog source negative input) is Internal voltage reference
//
#define xACMP_ASRCN_REF         0 

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
//! |xACMP Int Vref          |       CoX      |        NUC1xx        |
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
#define xACMP_REF_1_2V          0

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
//! The ID index is always like 0-1, and so on.
//!
//! \section xACMP_Comparator_IDs_Sec_Port CoX Port Details
//! \verbatim
//! +-------------------+----------------+---------+
//! |xACMP ACMP ID      |       CoX      | NUC1xx  |
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
#define xACMP_0             0

//
//! Comparator 1
//
#define xACMP_1             0

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
//! |xACMP API               |       CoX      | NUC1xx |
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

extern void xACMPConfigure(unsigned long ulBase, unsigned long ulCompID, 
                           unsigned long ulConfig);

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
extern void xACMPEnable(unsigned long ulBase, unsigned long ulCompID);

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
extern void xACMPDisable(unsigned long ulBase, unsigned long ulCompID);

//*****************************************************************************
//
//! \brief Init the Comp n Interrupt Callback function.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulCompID is the ID(index) of the comparator.
//! Refrence \ref xACMP_Comparator_IDs.
//! \param pfnCallback is the callback function.
//!
//! When there is any ADC intrrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent not used, always 0..
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
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
extern void xACMPIntEnable(unsigned long ulBase, unsigned long ulCompID);

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
extern void xACMPIntDisable(unsigned long ulBase, unsigned long ulCompID);

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


