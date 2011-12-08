//*****************************************************************************
//
//! \file ADC_OneShotMode.c
//! \brief example of ADC.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************  

//*****************************************************************************
//
//! Include related header files  
//
//*****************************************************************************
#include "MINI51.h"
#include "DrvADC.h"
#include "DrvGPIO.h"
#include "DrvSYS.h"

//*****************************************************************************
//
//! Define Function Prototypes
//
//*****************************************************************************
void AdcSingleModeTest(void);
void AdcIntCallback_SingleMode(uint32_t);

//*****************************************************************************
//
//! Define global variables and constants
//
//*****************************************************************************
volatile uint8_t gu8AdcIntFlag;

//*****************************************************************************
//
//! \brief ADCSingleMode
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void ADCSingleMode(void)
{
    UNLOCKREG();

    GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03;  /* P5.1 -> XTAL2, P5.0 -> XTAL1 */
    CLK->PWRCON_BITS.XTLCLK_EN = 1;

    /* Waiting for 12M Xtal stalble */
    while (DrvSYS_GetChipClockSourceStatus(XTL_CLK) != 1);
    /*                           ADC sample code                                       */

    /* default setting: single end input, single operation mode, all channel disable, ADC clock frequency = 12MHz/(3+1) */
    DrvADC_Open(0, EXTERNAL_CLOCK, 3);
    AdcSingleModeTest();

    DrvADC_Close();
}
//*****************************************************************************
//
//! \brief ADC single mode test.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void AdcSingleModeTest()
{
    int32_t i32ConversionData;


    /* Set the ADC channel */
    DrvADC_SetADCChannel(2);

    gu8AdcIntFlag = 0;
    DrvADC_EnableADCInt(AdcIntCallback_SingleMode, 0);

    /* Start A/D conversion */
    DrvADC_StartConvert();
    /* Wait ADC interrupt */
    while(gu8AdcIntFlag==0);

    DrvADC_DisableADCInt();

    i32ConversionData = DrvADC_GetConversionData();

}

//*****************************************************************************
//
//! \brief ADC interrupt callback function.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void AdcIntCallback_SingleMode(uint32_t u32UserData)
{
    gu8AdcIntFlag = 1;
}
