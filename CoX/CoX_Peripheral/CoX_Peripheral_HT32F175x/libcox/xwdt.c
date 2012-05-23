//*****************************************************************************
//
//! \file xwdt.c
//! \brief Driver for the WDT
//! \version V2.1.1.0
//! \date 5/4/2011
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
//! \return None.
//
//*****************************************************************************
void 
WDTIntHandler(void)
{

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
//! \return None.
//
//*****************************************************************************
void 
WDTimerInit(unsigned long ulConfig)
{

    while(!SysCtlBackupReadyStateGet());

    SysCtlBackupDomainReset();
    //
    // Check the arguments.
    //
    xASSERT((ulConfig <= WDT_MR0_WDTV_M));         
    xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
    xHWREG(WDT_MR0) &= ~WDT_MR0_WDTV_M;
    xHWREG(WDT_MR0) |= ulConfig;
    xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
}

//*****************************************************************************
//
//! \brief Set The WatchDog Timer(WDT)'s Delta Value. 
//!
//! \param ulConfig is the Timer Delta Value Selection.
//!
//! This function is to set The WatchDog Timer(WDT)'s Delta Value.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerDeltaSet(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulConfig <= WDT_MR1_WDTD_M));         
    xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
    xHWREG(WDT_MR1) &= ~WDT_MR1_WDTD_M;
    xHWREG(WDT_MR1) |= ulConfig;
    xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
}

//*****************************************************************************
//
//! \brief Restart the Watchdog timer count value. 
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
    xHWREG(WDT_CR) |= (WDT_CR_RSKEY | WDT_CR_WDTRS);
}

//*****************************************************************************
//
//! \brief Get the Watchdog timer Status. 
//!
//! \param None.
//!
//! This function is to get the Watchdog timer Status.
//!
//! \return the Watchdog timer Status value.
//
//*****************************************************************************
unsigned long 
WDTimerStatusGet(void)
{   
    return xHWREG(WDT_SR);
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
//! \reset.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b WDT_INT_FUNCTION,\b WDT_RESET_FUNCTION.
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
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION));
    xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
    xHWREG(WDT_MR0) |= ulFunction;
    xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
}


//*****************************************************************************
//
//! \brief Disable the watch dog timer's function. 
//!
//! \param ulFunction is the watch dog timer's function.
//!
//! This function is to disable the watch dog timer's function such as Interrupt
//! \reset.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b WDT_INT_FUNCTION,\b WDT_RESET_FUNCTION.
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
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION));
    xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
    xHWREG(WDT_MR0) &= ~ulFunction;
    xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
}

//*****************************************************************************
//
//! \brief Set Watchdog Timer Prescaler. 
//!
//! \param ulDivide is the peripheral clock divide to be set.
//!
//! Set Watchdog Timer Prescaler.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerPrescalerSet(unsigned long ulDivide)
{   
    unsigned long ulTemp = 0;
    xASSERT((ulDivide <= 128) && (ulDivide >= 1));
    for(ulTemp=0; ulTemp<8; ulTemp++)
    {
        if(ulDivide == (1 << ulTemp))
        break;
    }
    xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_WDTSRC_M;
    xHWREG(SYSCLK_GCFGR) |= SYSCTL_PERIPH_WDG_S_EXTSL;
    xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
    xHWREG(WDT_MR1) &= ~WDT_MR1_WPSC_M;
    xHWREG(WDT_MR1) |= (ulTemp << WDT_MR1_WPSC_S);
    xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
}