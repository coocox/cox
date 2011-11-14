//*****************************************************************************
//
//! \file xwdt.c
//! \brief Driver for the WDT
//! \version V2.1.1.1
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_wdt.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xwdt.h"


//*****************************************************************************
//
// An array is WATCHDOG Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnWATCHDOGHandlerCallbacks[1]={0};


//*****************************************************************************
//
//! \brief The WatchDog Timer(WDT) default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default WatchDog Timer(WDT) IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
WDTIntHandler(void)
{
    //
    //! Clear the WDT INT Flag
    //
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTIF;

    if (g_pfnWATCHDOGHandlerCallbacks[0] != 0)
    {
        g_pfnWATCHDOGHandlerCallbacks[0](0, 0, 0, 0);
    }
}

//*****************************************************************************
//
//! \brief Configurate The WatchDog Timer(WDT)'s Timer Interval. 
//!
//! \param ulConfig is the Timer Interval Selection.
//!
//! This function is to Configurate The WatchDog Timer(WDT)'s Timer Interval.
//!
//! The \e ulConfig parameter is the one of any of the following:
//! \b WDT_INTERVAL_2_4T,\b WDT_INTERVAL_2_6T,\b WDT_INTERVAL_2_8T,
//! \b WDT_INTERVAL_2_10T,\b WDT_INTERVAL_2_12T,\b WDT_INTERVAL_2_14T,
//! \b WDT_INTERVAL_2_16T,\b WDT_INTERVAL_2_18T.
//!
//! \note When use watch dog WDTimerEnable() should be called after call 
//! WDTimerInit(ulConfig).
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerInit(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulConfig == WDT_INTERVAL_2_4T) || 
            (ulConfig == WDT_INTERVAL_2_6T) ||
            (ulConfig == WDT_INTERVAL_2_8T) ||
            (ulConfig == WDT_INTERVAL_2_10T) ||
            (ulConfig == WDT_INTERVAL_2_12T) ||
            (ulConfig == WDT_INTERVAL_2_14T) ||
            (ulConfig == WDT_INTERVAL_2_16T) ||
            (ulConfig == WDT_INTERVAL_2_18T));         

    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTE;
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTIS_M;
    xHWREG(WDT_WTCR) |= ulConfig;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Enable the Watchdog timer interrupt. 
//!
//! \param None.
//!
//! This function is to Enable the Watchdog timer interrupt.
//!
//! \note When use watch dog WDTimerEnable() should be called after call 
//! WDTimerInit(ulConfig).
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerEnable(void)
{   
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTE;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Disable the Watchdog timer interrupt. 
//!
//! \param None.
//!
//! This function is to disable the Watchdog timer interrupt.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerDisable(void)
{   
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTE;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Restart the Watchdog timer interrupt. 
//!
//! \param None.
//!
//! This function is to restart the Watchdog timer interrupt.
//!
//! \note this is use to feed the watch dog.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerRestart(void)
{   
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTR;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the Watchdog timer.
//!
//! \param xtPortCallback is callback for the Watchdog timer.
//!
//! Init interrupts callback for the Watchdog timer.
//!
//! \return None.
//
//*****************************************************************************
void
WDTimerIntCallbackInit(xtEventCallback xtWDTCallback)
{
    
    if (xtWDTCallback != 0)
    {
        g_pfnWATCHDOGHandlerCallbacks[0] = xtWDTCallback;
    }
}

//*****************************************************************************
//
//! \brief Enable the watch dog timer's function. 
//!
//! \param ulFunction is the watch dog timer's function.
//!
//! This function is to enable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b WDT_INT_FUNCTION,\b WDT_RESET_FUNCTION,\b WDT_WAKEUP_FUNCTION,
//! \b WDT_HOLD_IN_ICE.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerFunctionEnable(unsigned long ulFunction)
{   
    //
    // Check the arguments.
    //
    xASSERT(((ulFunction & WDT_INT_FUNCTION) == WDT_INT_FUNCTION) || 
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION) ||
            ((ulFunction & WDT_WAKEUP_FUNCTION) == WDT_WAKEUP_FUNCTION) ||
            ((ulFunction & WDT_HOLD_IN_ICE) == WDT_HOLD_IN_ICE));
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= ulFunction;
    SysCtlKeyAddrLock();
}


//*****************************************************************************
//
//! \brief Disable the watch dog timer's function. 
//!
//! \param ulFunction is the watch dog timer's function.
//!
//! This function is to disable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b WDT_INT_FUNCTION,\b WDT_RESET_FUNCTION,\b WDT_WAKEUP_FUNCTION,
//! \b WDT_HOLD_IN_ICE.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerFunctionDisable(unsigned long ulFunction)
{   
    //
    // Check the arguments.
    //
    xASSERT(((ulFunction & WDT_INT_FUNCTION) == WDT_INT_FUNCTION) || 
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION) ||
            ((ulFunction & WDT_WAKEUP_FUNCTION) == WDT_WAKEUP_FUNCTION) ||
            ((ulFunction & WDT_HOLD_IN_ICE) == WDT_HOLD_IN_ICE));
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~ulFunction;
    SysCtlKeyAddrLock();
}

