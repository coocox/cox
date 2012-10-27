//*****************************************************************************
//
//! \file xwdt.c
//! \brief Driver for the WDT
//! \version V2.1.1.1
//! \date 11/14/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox 
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


//
// This vaiable is used to save watch dog configure information.
//
static unsigned long g_WatchDogStatue = 0;

//*****************************************************************************
//
//! \brief Configurate The WatchDog Timer(WDT)'s Timer Interval. 
//!
//! \param ulConfig is the Timer Interval Selection.
//!
//! This function is to Configurate The WatchDog Timer(WDT)'s Timer Interval.
//!
//! The \e ulConfig parameter is the one of any of the following:
//! \b WDT_INTERVAL_1K_32MS, \b WDT_INTERVAL_1K_256MS, \b WDT_INTERVAL_1K_1024MS,
//! \b WDT_INTERVAL_BUS_2_13T, \b WDT_INTERVAL_BUS_2_16T, \b WDT_INTERVAL_BUS_2_18T
//! OR one of the following \b WDT_MODE_NORMAL, \b WDT_MODE_WINDOWED
//! \note When use watch dog WDTimerEnable() should be called after call 
//! WDTimerInit(ulConfig).
//!
//! \return None.
//
//*****************************************************************************
void WDTimerInit(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(0 == (ulConfig & 0xFFFFFFF0));

    //
    // Configure Watch Dog
    //
    g_WatchDogStatue = ulConfig;    
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
void WDTimerEnable(void)
{   
    xHWREG(SIM_COPC) = g_WatchDogStatue;
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
void WDTimerDisable(void)
{   
    g_WatchDogStatue = xHWREG(SIM_COPC);
    xHWREG(SIM_COPC) &= ~SIM_COPC_COPT_MASK;
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
void WDTimerRestart(void)
{   
    xHWREG(SIM_SRVCOP) = 0x55UL;
    xHWREG(SIM_SRVCOP) = 0xAAUL;
}

