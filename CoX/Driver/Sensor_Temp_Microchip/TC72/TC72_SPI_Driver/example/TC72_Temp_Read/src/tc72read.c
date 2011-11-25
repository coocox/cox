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
#include "tc72read.h"
#include "tc72.h"
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
void TC72TemperGet(void)
{   
    short sTemperInDec;

    //
    // Step 1, you should set system clock.
    // 
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Step 2, you should initialize TC72
    // 
    TC72Init(1000000);
    
    //
    // Step 3, you should check whether TC72 is existent and usable or not
    // 
    if(xtrue == TC72IDCheck())
    {
    //
    // Step 4, you should configure the mode of temperature convertion.
    //
        TC72Configure(TC72_MODE_CONTINUOUS);
        
    //
    // Step 5, you can get temperature value from TC72.
    //
        sTemperInDec = TC72TemperReadDec();
    }
}
