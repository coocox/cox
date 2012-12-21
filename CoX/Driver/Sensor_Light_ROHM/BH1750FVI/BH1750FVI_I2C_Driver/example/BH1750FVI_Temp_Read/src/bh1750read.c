//*****************************************************************************
//
//! \file tc72read.c
//! \brief Get temperature from TC72.
//! \version 1.0
//! \date 10/20/2011
//! \author CooCox
//
//*****************************************************************************

#include "xhw_types.h"
#include "hw_bh1750fvi.h"
#include "bh1750fvi.h"
#include "bh1750read.h"
#include "xsysctl.h"


//*****************************************************************************
//
//! \brief TC72 Read Temparature
//!
//! \param None
//!
//! This function is to tell you how to use TC72
//!
//! \return none
//
//*****************************************************************************
void BH1750LightGet(void)
{   
    short sTemperInDec;

    //
    // Step 1, you should set system clock.
    // 
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Step 2, you should initialize BH1750FVI
    // 
    BH1750Init(30000);
    
    //
    // Step 3, you should configure the mode of light convertion.
    //
    //
    BH1750Configure(BH1750_INS_CON_HR_MODE);
    SysCtlDelay(10000000);
    //
    // Step 4, you can get light value from BH1750FVI.
    //
    sTemperInDec = BH1750LightRead();
}
