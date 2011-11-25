//*****************************************************************************
//
//! \file tc77read.c
//! \brief Get temperature from TC77.
//! \version 1.0
//! \date 9/11/2011
//! \author CooCox
//
//*****************************************************************************
#include "xhw_types.h"
#include "tc77read.h"
#include "tc77.h"
#include "xsysctl.h"

//*****************************************************************************
//
//! \brief TC77 Read Temparature
//!
//! \param None
//!
//! This function is to tell you how to use TC77
//!
//! \return none
//
//*****************************************************************************
void TC77TemperGet(void)
{   
    short sTemperInDec;

    //
    // Step 1, you should set system clock.
    // 
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Step 2, you should initialize TC77
    // 
    TC77Init(1000000);
    
    //
    // Step 3, you should check whether TC77 is existent and usable or not
    // 
    
    if(xtrue == TC77IDCheck())
    {
    //
    // Step 4, you should configure the mode of temperature convertion.
    //
        TC77Configure(TC77_MODE_CONTINUOUS);
        
    //
    // Step 5, you can get temperature value from TC77.
    //
        sTemperInDec = TC77TemperReadDec();
    }
}
