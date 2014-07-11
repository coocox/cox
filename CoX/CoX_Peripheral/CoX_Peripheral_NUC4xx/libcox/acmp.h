//*****************************************************************************
//
//! \file acmp.h
//! \brief Defines and Macros for the analog comparator API.
//! \version V2.1.1.0
//! \date 1/3/2012
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

#ifndef __ACMP_H__
#define __ACMP_H__

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
//! \addtogroup NUC4xx_ACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ACMP_Analog_Src_negative NUC4xx negative(ACMP-) Input Source
//! \brief Analog comparator negative input select.
//! @{
//
//*****************************************************************************

//
//! Comp-(Analog source negative input) is CPN pin
//
#define ACMP_ASRCN_PIN          0x00000000  

//
//! Comp-(Analog source negative input) is Internal voltage reference(1.2V)
//
#define ACMP_ASRCN_REF          0x00000010 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ACMP_Comparator_IDs NUC4xx_ACMP Analog Comparator ID
//! \brief Analog Comparator ID (index).
//!
//! The ID index is always like 0-1, and so on.
//!
//! @{
//
//*****************************************************************************

#define ACMP_0                  0
#define ACMP_1                  1


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ACMP_Exported_APIs NUC4xx ACMP API
//! \brief NUC4xx ACMP API Reference.
//! @{
//
//*****************************************************************************

extern void ACMPNegativeSrcSet(unsigned long ulBase, unsigned long ulComp,
                               unsigned long ulSource);

extern void ACMPHysEnable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPHysDisable(unsigned long ulBase, unsigned long ulComp);

extern void ACMPEnable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPDisable(unsigned long ulBase, unsigned long ulComp);

extern void ACMPIntEnable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPIntDisable(unsigned long ulBase, unsigned long ulComp);

extern xtBoolean ACMPIntStatus(unsigned long ulBase, unsigned long ulComp);
extern void ACMPIntClear(unsigned long ulBase, unsigned long ulComp);

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


