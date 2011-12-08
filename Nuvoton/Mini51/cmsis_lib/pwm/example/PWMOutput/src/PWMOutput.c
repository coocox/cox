//*****************************************************************************
//
//! \file PWMOutput.c
//! \brief example of PWM.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************
#include "DrvGPIO.h"
#include "DrvPWM.h"
#include "DrvSYS.h"

//*****************************************************************************
//
//! Define global variables and constants
//
//*****************************************************************************
int32_t g_bCapInt = 0;
uint8_t volatile g_u8PWMCount = 0;
uint16_t g_u16Frequency;
static uint32_t s_u32Pulse = 0;
void PWMA_IRQHandler(void);

//*****************************************************************************
//
//! \brief PWM Output.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void PWMOutput(void)
{
    S_DRVPWM_TIME_DATA_T sPt;
    int32_t i32Loop = 1;

    UNLOCKREG();
    //
    // P5.1 -> XTAL2, P5.0 -> XTAL1
    //
    GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03;
    CLK->PWRCON_BITS.XTLCLK_EN = 1;

    //
    // Waiting for 12M Xtal stalble
    //
    DrvSYS_Delay(5000);
     
    //
    //Enable PWM clock
    //
    DrvPWM_Open();
	  CLK->CLKSEL1_BITS.PWM23_S = 2;
    
    //
    // Set PWM pin
    //
    DrvGPIO_InitFunction(FUNC_PWM3);

    UNLOCKREG();
    DrvSYS_SelectHCLKSource(0);
    LOCKREG();

    while(i32Loop)
    {

        uint8_t u8ItemOK;

        u8ItemOK = 1;
        g_u16Frequency = 256;


        if (u8ItemOK && g_u8PWMCount == 0)
        {
            s_u32Pulse = 0;
            g_u8PWMCount = 1;
            //
            // PWM Timer property
            //
            sPt.u8Mode = DRVPWM_AUTO_RELOAD_MODE;
            sPt.u32Frequency = g_u16Frequency;
            //
            // High Pulse peroid : Total Pulse peroid = 10 : 90
            //
            sPt.u8HighPulseRatio = 90;
            sPt.i32Inverter = 0;
            
            //
            // Set PWM Timer Configuration 
            //
            DrvPWM_SetTimerClk(DRVPWM_TIMER3, &sPt);

            //
            // Enable Output for PWM Timer */
            //
            DrvPWM_SetTimerIO(DRVPWM_TIMER3, 1);
            
            //
            // Enable Interrupt Sources of PWM Timer and install call back function
            //
            DrvPWM_EnableInt(DRVPWM_TIMER3, PWM_INT_PERIOD, PWMA_IRQHandler, 0);
            
            //
            //Enable the PWM Timer
            //
            DrvPWM_Enable(DRVPWM_TIMER3);

            while (g_u8PWMCount);
            DrvPWM_Disable(DRVPWM_TIMER3);
          }
    }
    DrvPWM_Close();
}

//*****************************************************************************
//
//! PWM Timer Callback function
//
//*****************************************************************************
void PWMA_IRQHandler(void)
{
    if (s_u32Pulse == g_u16Frequency)
    {
     //
     // Stop PWM Timer 3
     // Set PWM Timer counter as 0, When interrupt request happen, disable PWM Timer
     // 
        DrvPWM_SetTimerCounter(DRVPWM_TIMER3, 0);
		DrvPWM_SetTimerComparator(DRVPWM_TIMER3, 0);
    }

    if (s_u32Pulse == g_u16Frequency + 1)
        g_u8PWMCount = 0;
    s_u32Pulse++;
}

