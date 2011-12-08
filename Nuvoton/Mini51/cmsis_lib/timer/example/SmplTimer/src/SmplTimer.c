//*****************************************************************************
//
//! \file SmplTimer.c
//! \brief Driver Sample Code for timer.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.    
//
//*****************************************************************************

//*****************************************************************************
//
//! Include related header files  
//
//*****************************************************************************
#include "MINI51.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "DrvTimer.h"

//*****************************************************************************
//
//! Define global variables and constants
//
//*****************************************************************************
uint32_t uTimerEventNo[2];;
volatile uint32_t u32Timer0Cnt = 0;
void TMR0_Callback();

//*****************************************************************************
//
//! \brief Example of Timer.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void SmplTimer(void)
{
    UNLOCKREG();
    //
    // P5.1 -> XTAL2, P5.0 -> XTAL1
    //
	  GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03;
    CLK->PWRCON_BITS.XTLCLK_EN = 1;
    CLK->CLKSEL0_BITS.HCLK_S = 0;
    
    //
    // Waiting for 12M Xtal stalble
    //
    DrvSYS_Delay(5000);
    
    //
    // Set all the TIMER clock source are from 12MHz
    //
    DrvSYS_SelectIPClockSource(TMR0_CLK_SET, 0);
    LOCKREG();

    DrvTIMER_Init();

    //
    // Using TIMER0 in PERIODIC_MODE, 2 ticks
    //
    DrvTIMER_Open(E_TMR0, 2, E_PERIODIC_MODE);

    //
    // Install callback "TMR0_Callback" and trigger callback when Interrupt happen twice
    //
    uTimerEventNo[0] = DrvTIMER_SetTimerEvent(E_TMR0, 2, (TIMER_CALLBACK)TMR0_Callback, 0);

    //
    // Enable TIMER0 Intettupt
    //
    DrvTIMER_EnableInt(E_TMR0);

    //
    // Start counting 
    //
    u32Timer0Cnt = 0;
    DrvTIMER_Start(E_TMR0);

    while (u32Timer0Cnt < 10);
     
    //
    // Clear the Timer event
    //
    DrvTIMER_ClearTimerEvent(E_TMR0, uTimerEventNo[0]);

    //
    // Close TIMER0 
    //
    DrvTIMER_Close(E_TMR0);

}


//*****************************************************************************
//
//! \brief Timer interrupt callback function.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void TMR0_Callback()
{
    ++u32Timer0Cnt;
    TIMER0->ISR_BITS.TIF = 1;
}

