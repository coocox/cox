//*****************************************************************************
//
//! \file xwdt.c
//! \brief Driver for the WDT
//! \version V2.2.1.0
//! \date 6/14/2011
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
#include "xhw_config.h"
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

    //
    // Check the arguments.
    //
    xASSERT((ulConfig >= 0x40) && (ulConfig <= WWDG_CR_CT_M));

    xHWREG(WWDG_CR) &= ~WWDG_CR_CT_M;
    xHWREG(WWDG_CR) |= ulConfig;
}

//*****************************************************************************
//
//! \brief Set The WatchDog Timer(WDT)'s Window Value. 
//!
//! \param ulConfig is the Timer Window Value Selection.
//!
//! This function is to set The WatchDog Timer(WDT)'s Wondow Value.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerWindowValueSet(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulConfig <= WWDG_CFR_W_M));
    
    xHWREG(WWDG_CFR) &= ~WWDG_CFR_W_M;
    xHWREG(WWDG_CFR) |= ulConfig;
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
    return xHWREG(WWDG_SR);
}


//*****************************************************************************
//
//! \brief Clear the Watchdog timer Status flag. 
//!
//! \param None.
//!
//! This function is to Clear the Watchdog timer Status flag.
//!
//! \return None.
//
//*****************************************************************************
void
WDTimerStatusClear(void)
{   
    xHWREG(WWDG_SR) = 0;
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
//! \brief Enable the watch dog timer's Interrupt. 
//!
//! This function is to enable the watch dog interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerIntEnable(void)
{   
    xHWREG(WWDG_CFR) |= WWDG_CFR_EWI_EN;
}

//*****************************************************************************
//
//! \brief Disable the watch dog timer's Interrupt. 
//!
//! This function is to Disable the watch dog interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerDisable(void)
{   
    xHWREG(WWDG_CFR) &= ~WWDG_CFR_EWI_EN;
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
    //
    // Check the arguments.
    //
    xASSERT((ulDivide == WDT_PRESCALER_1) ||
            (ulDivide == WDT_PRESCALER_2) ||
            (ulDivide == WDT_PRESCALER_4) ||
            (ulDivide == WDT_PRESCALER_8));
  

    xHWREG(WWDG_CFR) &= ~WWDG_CFR_WDGTB_M;
    xHWREG(WWDG_CFR) |= ulDivide;
}

//*****************************************************************************
//
//! \brief Enable Window watchdog. 
//!
//! \param ulBase specifies the Window watchdog base address.
//!
//! Enable Window watchdog.
//!
//! \return None.
//
//*****************************************************************************
void 
WWDGEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == WWDG_BASE));
    
    //
    // Enable Window watchdog
    //
    xHWREG(WWDG_CR) |= WWDG_CR_WDT_EN;
}

//*****************************************************************************
//
//! \brief Configurate The Independent WatchDog's Timer Interval. 
//!
//! \param ulConfig is the Timer Interval Selection.
//!
//! This function is to Configurate The Independent WatchDog's Timer Interval.
//!
//! \return None.
//
//*****************************************************************************
void 
IWDGTimerInit(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulConfig <= IWDG_RLR_RL_M));
        
    xHWREG(IWDG_KR) = IWDG_KR_PROTECT_DIS;
    xHWREG(IWDG_RLR) = ulConfig;
}

//*****************************************************************************
//
//! \brief Start the Independent Watchdog . 
//!
//! \param None.
//!
//! This function is to start the Independent Watchdog timer.
//!
//! \note this is use to start the Independent Watchdog.
//!
//! \return None.
//
//*****************************************************************************
void 
IWDGTimerStart(void)
{   
    xHWREG(IWDG_KR) = IWDG_KR_START;
}

//*****************************************************************************
//
//! \brief Restart the Independent Watchdog timer count value. 
//!
//! \param None.
//!
//! This function is to restart the Watchdog timer.
//!
//! \note this is use to feed the Independent watchdog.
//!
//! \return None.
//
//*****************************************************************************
void 
IWDGTimerRestart(void)
{   
    xHWREG(IWDG_KR) = IWDG_KR_RELOAD;
}

//*****************************************************************************
//
//! \brief Get the Independent Watchdog timer Status. 
//!
//! \param None.
//!
//! This function is to get the Watchdog timer Status.
//!
//! \return the Watchdog timer Status value.
//
//*****************************************************************************
unsigned long 
IWDGTimerStatusGet(void)
{   
    return xHWREG(IWDG_SR);
}

//*****************************************************************************
//
//! \brief Set Independent Watchdog Timer Prescaler. 
//!
//! \param ulDivide is the peripheral clock divide to be set.
//!
//! Set Independent Watchdog Timer Prescaler.
//!
//! \return None.
//
//*****************************************************************************
void 
IWDGTimerPrescalerSet(unsigned long ulDivide)
{   
    //
    // Check the arguments.
    //
    xASSERT((ulDivide == IWDT_PRESCALER_4) ||
            (ulDivide == IWDT_PRESCALER_8) ||
            (ulDivide == IWDT_PRESCALER_16) ||
            (ulDivide == IWDT_PRESCALER_32) ||
            (ulDivide == IWDT_PRESCALER_64) ||
            (ulDivide == IWDT_PRESCALER_128) ||
            (ulDivide == IWDT_PRESCALER_256));


    xHWREG(IWDG_KR) = IWDG_KR_PROTECT_DIS;
    xHWREG(IWDG_PR) = ulDivide;
}
