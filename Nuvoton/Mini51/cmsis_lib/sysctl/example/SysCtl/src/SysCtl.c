//*****************************************************************************
//
//! \file SysCtl.c
//! \brief example of SysCtl.
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
#include "DrvSYS.h"

//*****************************************************************************
//
//! Define global variables and constants
//
//*****************************************************************************
#define SIGNATURE       0x125ab234
#define FLAG_ADDR       0x200007FC

void BOD_CallbackFn(void);

//*****************************************************************************
//
//! \brief SysCtl Example.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void SysCtlTest(void)
{
    int32_t  i32ret;
    uint32_t u32data;

    //
	// Enable high external clock and use it as system clock (HCLK) */
	//
    DrvSYS_Open(XTL_CLK);

    //
    // Waiting for 12M Xtal stable 
    //
    while (DrvSYS_GetChipClockSourceStatus(XTL_CLK) != 1);

    if(M32(FLAG_ADDR) == SIGNATURE)
    {
    //
    // CPU Reset success!
    //
    }
    
    //
    // Read Product ID
    //
    u32data = DrvSYS_ReadProductID();

    //
    // Get reset source from last operation
    //
    u32data = DrvSYS_GetResetSource();

    //
    // Clear reset source
    //
    DrvSYS_ClearResetSource(u32data);

    //
    //Reset IP (I2C)
    //
    DrvSYS_ResetIP(E_SYS_I2C_RST);

    //
    // Unlock protected address register before reset CPU
    //
    i32ret = DrvSYS_UnlockProtectedReg();
    if (i32ret == 0)
    {
    //
    // Protected Address is Unlocked
    //
    }

    //
    //Enable Brown Our Detector , select Brown Out Interrupt function and install its callback function 
    //
    DrvSYS_SetBODFunction(1, 0, BOD_CallbackFn);
    
    //
    // Set Brown Our Detector voltage 2.2V
    //
    DrvSYS_SelectBODVolt(0);

    //
    // Select internal OSC22M as system clock, and disable internal OS10K
    //
    DrvSYS_Open(OSC22M_CLK);
    DrvSYS_SetOscCtrl(OSC10K_CLK, 0);

    //
    // Set IP clock source(ADC clock source from 12M)
    //
    DrvSYS_SelectIPClockSource(ADC_CLK_SET, 0x00);

    //
    // Enable IP clock(I2C)
    //
    DrvSYS_SetIPClock(E_SYS_I2C_CLK, 1);

    //
    // Write a signature work to SRAM to check if it is reset by software
    //
    M32(FLAG_ADDR) = SIGNATURE;
    //
    // Reset CPU
    //
    DrvSYS_ResetCPU();
}

//*****************************************************************************
//
//! \brief Brown out Callback Function.
//!
//! \param None  
//!
//! \return None  
//
//*****************************************************************************
void BOD_CallbackFn(void)
{
//
// Brown Out Detect
//
}

