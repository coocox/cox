//*****************************************************************************
//
//! \file SmplAcmp.c
//! \brief example of ACMP.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************

#include "DrvGPIO.h"
#include "DrvSYS.h"
#include "MINI51.h"

static uint32_t acmpIntCnt = 0;

//*****************************************************************************
//
//!Define functions prototype  
//
//*****************************************************************************
void ACMP_IRQHandler(void);

//*****************************************************************************
//
//! \brief Example of ACMP.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void SmplAcmp(void)
{

    UNLOCKREG();
    
    //
    // P5.1 -> XTAL2, P5.0 -> XTAL1
    //
	GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03;
    CLK->PWRCON_BITS.XTLCLK_EN = 1;
    
    //
    // Waiting for 12M Xtal stable
    //
    while (DrvSYS_GetChipClockSourceStatus(XTL_CLK) != 1);

    DrvGPIO_InitFunction(FUNC_ACMP0);
    DrvGPIO_InitFunction(FUNC_ACMP1);

    //
    // Enable ACMP clock source
    //
    CLK->APBCLK_BITS.ACMP_EN = 1;

    //
    // Configure ACMP0
    //
    ACMP->CR0 = 0x13;

    //
    // Configure ACMP1
    //
    ACMP->CR1 = 0x13;

    NVIC_EnableIRQ(ACMP_IRQn);
}

//*****************************************************************************
//
//! \brief FMC interrupt callback function.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************

void ACMP_IRQHandler(void)
{
    acmpIntCnt++;
    if(ACMP->SR_BITS.CMPF0)
    {
        if(ACMP->SR_BITS.CO0 == 1)
        {
        }
        else
        {
        }

        ACMP->SR = 1;   // clear
    }

    if(ACMP->SR_BITS.CMPF1)
    {
        if(ACMP->SR_BITS.CO1 == 1)
        {
        }
        else
        {
        }
        ACMP->SR = 2;	// clear
    }
}
