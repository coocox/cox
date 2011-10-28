//*****************************************************************************
//
//! \file xwatchdog.h
//! \brief Prototypes for the WDT Driver.
//! \version 2.0.0.$Rev: 243 $
//! \date 9/30/2011
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

#ifndef __xWDT_H__
#define __xWDT_H__

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
//! \addtogroup WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Function_Type xWDT Function Type
//! \brief Values that show xWDT Function Type
//! \n
//! \section xWDT_Function_Type_Section 1. Where to use this group
//! Values that can be passed to xWDTFunctionEnable(), 
//! xWDTFunctionDisable() as the ulFunction parameter. 
//! \n
//! \section xWDT_Function_Type_COX 2. COX Port Details 
//! \verbatim
//! +------------------------ +----------------+------------------------+
//! |xWDT Function Type       |       COX      |         NUC1xx         |
//! |------------------------ |----------------|------------------------|
//! |xWDT_INT_FUNCTION        |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_RESET_FUNCTION      |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_WAKEUP_FUNCTION     |  Non-Mandatory |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_HOLD_IN_ICE         |  Non-Mandatory |            Y           |
//! +------------------------ +----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define xWDT_INT_FUNCTION       0

//
//! Reset CPU when watch dog time out
//
#define xWDT_RESET_FUNCTION     0

//
//! Watchdog timer timeout can wake-up chip from power down mode.
//
#define xWDT_WAKEUP_FUNCTION    0

//
//! Watchdog Timer counter will keep going no matter ICE debug mode
//! acknowledged or not.
//
#define xWDT_HOLD_IN_ICE        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Clock_Config xWDT Clock Configuration
//! \brief Values that show xWDT Clock Configuration
//! \n
//! \section xWDT_Clock_Config_Section 1. Where to use this group
//! Watch dog clock Configs. Such as clock source, Prescaler divider.
//! Values that can be passed to xWDTInit as the ulConfig parameter 
//! \n
//! \section xWDT_Clock_Config_COX 2.COX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Clock Configuration     |       COX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_INTSL            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_EXTSL            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_HCLK_DIV         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The watch dog source is int. 10 KHz
//
#define xWDT_S_INTSL            0     

//
//! The watch dog source is ext. 32 KHz
//
#define xWDT_S_EXTSL            0

//
//! The watch dog source is the HCLK/2048
//
#define xWDT_S_HCLK_DIV         0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Time_Reload_Config xWDT Time Reload Configuration
//! \brief Values that show xWDT Time Reload Configuration
//! \n
//! \section xWDT_Time_Reload_Config_Section 1. Where to use this group
//! Values that can be passed to xWDTimerInit() as the ulConfig parameter 
//! \n
//! \section xWDT_Time_Reload_Config_COX 2.COX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Time Reload Config      |       COX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |Time Reload Value       |  Non-Mandatory |   xWDT_INTERVAL_2_4T   |
//! |                        |                |------------------------|
//! |unsigned value          |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |   xWDT_INTERVAL_2_18T  |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Timeout Interval Selection is 2 4 * TWDT
//
#define xWDT_INTERVAL_2_4T      0

//
//! Timeout Interval Selection is 2 6 * TWDT
//
#define xWDT_INTERVAL_2_6T      0

//
//! Timeout Interval Selection is 2 8 * TWDT
//
#define xWDT_INTERVAL_2_8T      0

//
//! Timeout Interval Selection is 2 10 * TWDT
//
#define xWDT_INTERVAL_2_10T     0

//
//! Timeout Interval Selection is 2 12 * TWDT
//
#define xWDT_INTERVAL_2_12T     0

//
//! Timeout Interval Selection is 2 14 * TWDT
//
#define xWDT_INTERVAL_2_14T     0

//
//! Timeout Interval Selection is 2 16 * TWDT
//
#define xWDT_INTERVAL_2_16T     0

//
//! Timeout Interval Selection is 2 18 * TWDT
//
#define xWDT_INTERVAL_2_18T     0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Exported_APIs xWDT API
//! \brief xWDT API Refrence.
//!
//! \section xWDT_Exported_APIs_Port COX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xWDT API                |       COX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xWDTInit                |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTEnable              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTIntCallbackInit     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTDisable             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTRestart             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionEnable      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionDisable     |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configurate The WatchDog Timer(WDT)'s Timer Interval. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulConfig is the Timer's Prescaler divider and clock source 
//! Selection.
//! Details please reference to \ref xWDT_Clock_Config and
//! xWDT_Time_Reload_Config.
//! \param ulReload is the Timer's reload value.
//!
//! This function is to Configurate The WatchDog Timer(WDT)'s Timer Interval.
//! There are three factors to determine the Timer Interval,they are :
//! - clock source
//! - Prescaler divider
//! - reload value
//!
//! The \e ulConfig parameter contains clock source and Prescaler divider;
//! When use,this parameter is the logical OR of the two values.
//! For NUC1xx,there are no Prescaler divider.And the clock source can be:
//! \b xWDT_S_INTSL,\b xWDT_S_EXTSL,
//! \b xWDT_S_HCLK_DIV.
//! Details please reference to \ref xWDT_Clock_Config_COX.
//!
//! The \e ulReload parameter is value which will reload the counter when feed
//! the watch dog.The value range dDepends on the number of bits of 
//! corresponding counter.
//! For NUC1xx,the reload value can only be one of the following:
//! \b xWDT_INTERVAL_2_4T,\b xWDT_INTERVAL_2_6T,\b xWDT_INTERVAL_2_8T,
//! \b xWDT_INTERVAL_2_10T,\b xWDT_INTERVAL_2_12T,\b xWDT_INTERVAL_2_14T,
//! \b xWDT_INTERVAL_2_16T,\b xWDT_INTERVAL_2_18T.
//! Details please reference to \ref xWDT_Time_Reload_Config_COX.
//! 
//! \note When use watch dog xWDTEnable() should be called after call 
//! xWDTInit(ulBase, ulConfig, ulReload).
//!
//! \return None.
//
//*****************************************************************************

extern void xWDTInit(unsigned long ulBase, unsigned long ulConfig, 
                     unsigned long ulReload);

//*****************************************************************************
//
//! \brief Enable the Watchdog timer interrupt. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to Enable the Watchdog timer interrupt.
//!
//! \note When use watch dog xWDTimerEnable() should be called after call 
//! xWDTInit(ulBase, ulConfig, ulReload).
//!
//! \return None.
//
//*****************************************************************************       
extern void xWDTEnable(unsigned long ulBase); 


//*****************************************************************************
//
//! \brief Init interrupts callback for the Watchdog timer.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param xtPortCallback is callback for the Watchdog timer.
//!
//! Init interrupts callback for the Watchdog timer.
//!
//! \return None.
//
//*****************************************************************************     
extern void xWDTIntCallbackInit(unsigned long ulBase, 
                                xtEventCallback xtWDTCallback); 
        
//*****************************************************************************
//
//! \brief Disable the Watchdog timer interrupt. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to disable the Watchdog timer interrupt.
//!
//! \return None.
//
//*****************************************************************************
extern void xWDTDisable(unsigned long ulBase);
        
//*****************************************************************************
//
//! \brief Restart the Watchdog timer interrupt. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to restart the Watchdog timer interrupt.
//!
//! \note this is use to feed the watch dog.
//!
//! \return None.
//
//*****************************************************************************       
extern void xWDTRestart(unsigned long ulBase);

//*****************************************************************************
//
//! \brief Enable the watch dog timer's function. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulFunction is the watch dog timer's function.
//! Details please reference to \ref xWDT_Function_Type.
//!
//! This function is to enable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! \b xWDT_WAKEUP_FUNCTION,\b xWDT_HOLD_IN_ICE.
//! Details please reference to \ref xWDT_Function_Type_COX.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xWDTFunctionEnable(unsigned long ulBase, unsigned long ulFunction);
        
//*****************************************************************************
//
//! \brief Disable the watch dog timer's function. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulFunction is the watch dog timer's function.
//! Details please reference to \ref xWDT_Function_Type.
//!
//! This function is to disable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! \b xWDT_WAKEUP_FUNCTION,\b xWDT_HOLD_IN_ICE.
//! Details please reference to \ref xWDT_Function_Type_COX.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************      
extern void xWDTFunctionDisable(unsigned long ulBase, unsigned long ulFunction);

        
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

#endif // __xWDT_H__


