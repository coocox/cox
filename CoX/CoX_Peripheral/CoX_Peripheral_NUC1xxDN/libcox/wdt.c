//*****************************************************************************
//
//! \file wdt.c
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
#include "CoX.h"
#include "hw_sysctl.h"
#include "hw_wdt.h"


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
//! \brief  Configurate The WatchDog Timer(WDT)'s Timer Interval.
//!         This function is to configure The WatchDog Timer(WDT)'s Timer Interval.
//!         There are three factors to determine the Timer Interval, they are:
//!             - clock source
//!             - Prescaler divider
//!             - reload value
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulConfig is the WDT clock source Selection.
//!              - \ref xWDT_S_INTSL
//!              - \ref xWDT_S_EXTSL
//!
//! \param  [in] ulReload is the WDT's reload value.
//!              0xFF <= ulReload <= 0xFFFFFFFF
//!
//! \return None.
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         - \ref xWDTEnable and - \ref xWDTFunctionEnable.
//!
//
//*****************************************************************************
void 
xWDTInit(unsigned long ulBase, unsigned long ulConfig, unsigned long ulReload)
{
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);
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
    xHWREG(WDT_WTCR) |= ulReload;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief  Enable the Watchdog timer module.
//!         This function is to Enable the Watchdog timer and start counter.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \return None.
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         - \ref xWDTEnable and - \ref xWDTFunctionEnable.
//
//*****************************************************************************
void 
xWDTEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);

    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTE;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief  Disable the Watchdog timer.
//!         This function is to Disable the Watchdog timer module and stop
//!         the counter.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \return None.
//!
//
//*****************************************************************************
void 
xWDTDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);

    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTE;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief  Restart the Watchdog timer counter.
//!         This function is to restart the Watchdog timer by feed watchdog.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \return None.
//!
//! \note   User can use this function to feed the watch dog interval.
//
//*****************************************************************************
void 
xWDTRestart(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);

    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTR;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief  Select the Watchdog timer reset delay period.
//!         This function is to select the Watchdog timer reset delay period.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//! \param  [in] ulPeriod is the reset delay period.
//!              This value must be \ref WDT_WTCRALT_WTRDSEL_1024,
//!                                 \ref WDT_WTCRALT_WTRDSEL_128,
//!                                 \ref WDT_WTCRALT_WTRDSEL_16,
//!                                 \ref WDT_WTCRALT_WTRDSEL_1,
//!
//! \return None.
//!
//! \note   User can use this function to select the watch dog reset time interval.
//
//*****************************************************************************
void
WDTRestartDelayPeriod(unsigned long ulBase, unsigned long ulPeriod)
{
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);

    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCRALT) &= ~WDT_WTCRALT_WTRDSEL_M;
    xHWREG(WDT_WTCRALT) |= ulPeriod;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief  Register user interrupt callback function for the Watchdog timer.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] xtPortCallback is user's callback function for the Watchdog
//!              timer.
//!
//! \return None.
//
//*****************************************************************************
void
xWDTimerIntCallbackInit(unsigned long ulBase, xtEventCallback xtWDTCallback)
{
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);

    if (xtWDTCallback != 0)
    {
        g_pfnWATCHDOGHandlerCallbacks[0] = xtWDTCallback;
    }
}

//*****************************************************************************
//
//! \brief  Enable the watch dog timer's function.
//!         This function is to Enable the watch dog timer's function such as
//!         Interrupt reset.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulFunction is the watch dog timer's function.
//!              This parameter is the OR value of any of the following:
//!              - \ref xWDT_INT_FUNCTION
//!              - \ref xWDT_RESET_FUNCTION
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         \ref xWDTEnable and \ref xWDTFunctionEnable.
//
//*****************************************************************************
void 
xWDTFunctionEnable(unsigned long ulBase, unsigned long ulFunction)
{   
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);
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
//! \brief  Disable the watch dog timer's function.
//!         This function is to disable the watch dog timer's function such as
//!         Interrupt reset.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulFunction is the watch dog timer's function.
//!              This parameter is the OR value of any of the following:
//!              - \ref xWDT_INT_FUNCTION
//!              - \ref xWDT_RESET_FUNCTION
//!
//! \return None.
//!
//! \note   None.
//
//*****************************************************************************
void 
xWDTFunctionDisable(unsigned long ulBase, unsigned long ulFunction)
{   
    //
    // Check the arguments.
    //
	xASSERT(ulBase == xWDT_BASE);
    xASSERT(((ulFunction & WDT_INT_FUNCTION) == WDT_INT_FUNCTION) || 
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION) ||
            ((ulFunction & WDT_WAKEUP_FUNCTION) == WDT_WAKEUP_FUNCTION) ||
            ((ulFunction & WDT_HOLD_IN_ICE) == WDT_HOLD_IN_ICE));
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~ulFunction;
    SysCtlKeyAddrLock();
}
