//*****************************************************************************
//
//! \file adt7301read.c
//! \brief Get temperature from ADT7301.
//! \version 1.0
//! \date 10/25/2011
//! \author CooCox
//
//*****************************************************************************
#include "xhw_types.h"
#include "adt7301read.h"
#include "adt7301.h"
#include "xsysctl.h"

//*****************************************************************************
//
//! \brief Read Temparature from ADT7301.
//!
//! \param None
//!
//!  This function is to tell you how to use ADT7301.
//!
//! \return None
//
//*****************************************************************************
void ADT7301ReadTemper()
{   
    short sTemperInDec;
    
    //
    // Step 1, you should set system clock.
    // 
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Step 2, you should initialize ADT7301
    // 
    ADT7301Init(1000000);
 
    //
    // Step 3, you should configure the mode of temperature convertion.
    //
    ADT7301Configure(ADT7301_MODE_NORMAL);
        
    //
    // Step 4, you can get temperature value from ADT7301.
    //
    sTemperInDec = ADT7301TemperReadDec();
}
