//*****************************************************************************
//
//! \file xdebug.h
//! \brief Macros for assisting debug of the peripheral library.
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

#ifndef __xDEBUG_H__
#define __xDEBUG_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDebug xDebug
//! \brief Provided some assert macros to help debug.
//!
//! This module provides a macro called \ref xASSERT, Used to assert 
//! some conditions if is correct.
//!
//! \section xDebug_When When User the Debug feature?
//! - Verify the legitimacy of the parameters
//! - Judge execution of the accuracy of the results
//! - where you want to determine if actual == expected ?
//! .
//!
//! \section xDebug_How How to use the Debug Feature?
//! -# Enable the debug feature by doing a \b xDEBUG build.
//! -# add the \ref xASSERT where you want.
//! . 
//!
//! We strongly recommend you to open the debug characteristics in your 
//! development  process. This way can find out the questions as soon 
//! as possible.
//!
//! When release the code, you should shut down the debug characteristics,  
//! because they also take up CPU time, and you have ensured the condition 
//! is ok in the debug process.
//! 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDebug_Exported_APIs xDebug API
//! \brief xDebug API Reference.
//! @{
//
//*****************************************************************************

extern void __xerror__(char *pcFilename, unsigned long ulLine);

//*****************************************************************************
//
//! \brief The ASSERT macro.
//!
//! \param expr is the expression to be check.
//!
//! It does the actual assertion checking. Typically, this will be for 
//! procedure arguments.
//!
//! \return None.
//
//*****************************************************************************
#ifdef xDEBUG
#define xASSERT(expr) {                                                       \
                         if(!(expr))                                          \
                         {                                                    \
                             __xerror__(__FILE__, __LINE__);                  \
                         }                                                    \
                     }
#else
#define xASSERT(expr)
#endif

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

#endif // __xDEBUG_H__


