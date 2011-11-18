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
#include "xuart.h"
#include "ad7415.h"

//*****************************************************************************
//
//! The main function of the adi7417 Get Temperature
//
//! return none
//
//*****************************************************************************
void TemperatureGet(void)
{
    unsigned long  ulTemp;
    int i;    

    //
    // Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // AD7415 device init
    //
    AD7415Init(10000, AD7415_PowerDown_Enter); 
    
    while(1)
    {               
        for(i = 0; i < 10; i++)
        {
            if(i == 3)
            {
                AD7415PowerDownConvert();
            }
            ulTemp = AD7415TempReadLDC();
            ulTemp = ulTemp + 1;
            for(ulTemp = 0; ulTemp < 1000; ulTemp++);
        }
     
    }
}
