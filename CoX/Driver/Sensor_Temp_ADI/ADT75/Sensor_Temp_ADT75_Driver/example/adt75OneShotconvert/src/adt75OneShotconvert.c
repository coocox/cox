//*****************************************************************************
//
//! \file main.c
//! \brief sleep mode test.
//! \version 1.0
//! \date 8/1/2011
//! \author CooCox
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xi2c.h"
#include "adt75.h"

//*****************************************************************************
//
//! The main function of the adt75 one-shot mode.
//
//! return none
//
//*****************************************************************************
void TemperatureGet(void)
{
    long lTemp;
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    ADT75Init(10000, ADT75_POWER_NORMAL); 
    
    //
    // OS Int mode configure
    //
    ADT75IntModeConfig(ADT75_OPEMODE_CMP);
    
    //
    // OS pin active level is low, a pull-up register should add on this pin.
    //
    ADT75OSActiveLevelConfig(ADT75_OSALERT_LEVEL_LOW);
    
    //
    // Set the Faultqueue is 1
    //
    ADT75FaultQueueConfig(ADT75_FAULTQUE_1);
    
    //
    // Enable the one-shot mode
    //
    ADT75OneShotEnable();
        
    //
    // Configure the setpoint register
    //
    ADT75LowLimitSetLong(25);
    ADT75UpLimitSetLong(28);    

    while(1)
    {
        ADT75OneShotConvst();
        lTemp = ADT75TempReadLDC();      
    }
    
}
