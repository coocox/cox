/**
  * COPYRIGHT 2011 Nuvoton Technology Corp.
  ******************************************************************************
  * @file    Smpl_WDT.c
  * @author  NuMicro MCU Software Team
  * @version  V1.06
  * @date     23. August 2011
  * @brief   This file provides all the WDT firmware functions.
  ******************************************************************************
  */

#include "MINI51.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "DrvTimer.h"

void WDT_Callback();

void SmplWDT(void)
{
    UNLOCKREG();
	GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03;  /* P5.1 -> XTAL2, P5.0 -> XTAL1 */
    CLK->PWRCON_BITS.XTLCLK_EN = 1;
    CLK->CLKSEL0_BITS.HCLK_S = 0;
    /* Waiting for 12M Xtal stalble */
    DrvSYS_Delay(5000);

    DrvSYS_SelectIPClockSource(WDT_CLK_SET, 3);
    LOCKREG();


    //[WDT Callback Function Test]
    //The sample code will set WDT interval is LEVEL6 and WDT clock source is 10K.
    //Wait about 6 senonds to exit WDT test function.
    b8WDTINT = FALSE;
    UNLOCKREG();
    DrvWDT_Open(E_WDT_LEVEL6);
    DrvWDT_InstallISR((WDT_CALLBACK)WDT_Callback);
    DrvWDT_Ioctl(E_WDT_IOC_ENABLE_INT, 0);
    DrvWDT_Ioctl(E_WDT_IOC_START_TIMER, 0);
    LOCKREG();

    while (1)
    {
        if (b8WDTINT)
        {
        	break;
        }
    }

}

/*---------------------------------------------------------------------------------------------------------*/
/*  Callback funtion                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/

volatile uint8_t b8WDTINT = FALSE;

void WDT_Callback()
{
    b8WDTINT = TRUE;

    DrvWDT_Ioctl(E_WDT_IOC_RESET_TIMER, 0);

    DrvWDT_Close();
}


/*** (C) COPYRIGHT 2011 Nuvoton Technology Corp. ***/
