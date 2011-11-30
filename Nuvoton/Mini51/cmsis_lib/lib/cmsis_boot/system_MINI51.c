//*****************************************************************************
//
//! \file system_MINI51.c
//! \brief CMSIS ARM Cortex-M0 Device Peripheral Access Layer Source File
//! \version V1.01
//! \date 20. April 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************  
#include <stdint.h>
#include "MINI51.h"


//*****************************************************************************
//
//! Clock Variable definitions
//
//*****************************************************************************
uint32_t SystemCoreClock  = __HSI;   /*!< System Clock Frequency (Core Clock) */
uint32_t CyclesPerUs      = (__HSI / 1000000); /* Cycles per micro second */


//*****************************************************************************
//
//! \brief This function is used to update the variable SystemCoreClock
//!  and must be called whenever the core clock is changed.
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
    uint32_t u32CoreFreq, u32ClkSrc;
 
    u32ClkSrc = CLK->CLKSEL0_BITS.HCLK_S;
        
    if (u32ClkSrc == 0)
	u32CoreFreq = __XTAL;		/* External  crystal clock */
    else if (u32ClkSrc == 3)
        u32CoreFreq = __IRC10K;	/* Interanl 10K  crystyl clock */
    else if (u32ClkSrc ==  7)
        u32CoreFreq = __IRC22M;	 /* Internal 22M */
    else
	u32CoreFreq = __IRC22M;	 /* unknown value, use default Internal 22M */
 
    SystemCoreClock = (u32CoreFreq/(CLK->CLKDIV_BITS.HCLK_N + 1));
    CyclesPerUs = (SystemCoreClock + 500000) / 1000000;
}

//*****************************************************************************
//
//! \brief The necessary initializaiton of systerm.
//!
//! \param  None   
//!
//! \return None  
//
//*****************************************************************************
void SystemInit (void)
{

}


