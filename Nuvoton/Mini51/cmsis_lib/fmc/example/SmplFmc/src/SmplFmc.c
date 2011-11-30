//*****************************************************************************
//
//! \file SmplFmc.c
//! \brief example of Fmc.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//***************************************************************************** 
#include "DrvFMC.h"

//*****************************************************************************
//
//! Define global variables and constants
//
//*****************************************************************************
//
// The location of signature 
//
#define KEY_ADDR    0x200003FC
//
// The signature word is used by AP code to check if simple LD is finished
//
#define SIGNATURE   0x21557899

#define CONFIG0_TEST_CODE   0x0F9000FF

#define CONFIG_BASE     0x00300000
#define LDROM_BASE      0x00100000
#define PAGE_SIZE       512

//*****************************************************************************
//
//! \brief Mini51 FMC Driver Sample Code for LDROM.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void SmplFmc(void)
{
    int32_t  i32Err;
    uint32_t u32Data, i;
    uint32_t apBase, apLimit;

    UNLOCKREG();
    CLK->PWRCON_BITS.XTLCLK_EN = 1;
    //
	// Waiting for 12M Xtal stalble
	// 
    while (CLK->CLKSTATUS_BITS.XTL_STB != 1);
    //
    //Enable ISP function
    //
    DrvFMC_EnableISP();
    //
    //Read BS
    //
    if (DrvFMC_GetBootSelect() == E_FMC_APROM)
    {
     //
     // Not boot from LDROM!!
     //
        while(1);
    }

    apBase = 0x3800;
    apLimit= 0x4000;
    
    //
	// Page Erase LDROM
	//
    for (i=apBase;i<apLimit;i+=PAGE_SIZE)
        DrvFMC_Erase(i);
    //
	// Erase Verify 
    //
    i32Err = 0;
    for(i = apBase; i < apLimit; i += 4)
    {
        DrvFMC_Read(i, &u32Data);

        if (u32Data != 0xFFFFFFFF)
        {
            i32Err = 1;
        }
    }
    if (i32Err)
    {
     //
     // Erase Fail
     //
    }
    else
    {
     //
     // Erase OK
     //
    }
    //
    // Program AP ROM and read out data to compare it
    //
    for(i = apBase; i < apLimit; i += 4)
    {
        DrvFMC_Write(i, i);
    }

    i32Err = 0;
    for(i = apBase; i < apLimit; i += 4)
    {
		DrvFMC_Read(i, &u32Data);
        if(u32Data != i)
        {
           i32Err = 1;
        }
    }
    if (i32Err)
    {
     //
     // Program Fail
     //
    }
    else
    {
      //
      // Program OK
      //
    }
    //
    // Write the signature to tell AP code that LD code has finished.
    //
    outpw(KEY_ADDR, SIGNATURE);
    //
    //FMC Simple LD Code Completed.Reset to back to AP mode
    //

    //
    // Make sure message has printed out
    //
    while (UART0->FSR_BITS.TE_FLAG == 0);

    DrvFMC_BootSelect(E_FMC_APROM);

    UNLOCKREG();
    GCR->IPRST_CTL1_BITS.CPU_RST = 1;
    LOCKREG();
}
