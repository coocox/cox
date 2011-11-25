//*****************************************************************************
//
// \file main.c
// \brief get ambient temperature.
// \version 1.0
// \date 8/1/2011
// \author CooCox
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xi2c.h"
#include "xuart.h"
#include "ad7417.h"
 
//*****************************************************************************
//
//! \brief callback function
//!
//! \return 0
//!
//
//*****************************************************************************
unsigned long SensorEvent (void *pvCBData, unsigned long ulEvent,
                            unsigned long ulMsgParam, void *pvMsgData)
{
    int i;
       
    //
    // Delay to see the led blink
    //
    for(i=0; i<100000; i++);
     
    //
    // Output the opposite bit value the blink the led 
    //
    xGPIOSPinWrite(PC12, !xGPIOSPinRead(PC12));
      
    AD7417TempReadLDC();
     
    return 0;
}

//*****************************************************************************
//
// \brief gpio init ,enble the GPB13 int ,low level triger
//
// \return none
//
//
//*****************************************************************************
void GPIOInit()
{
    //
    // PB12 used to driver led.
    //
    xGPIOSPinDirModeSet(PC12, xGPIO_DIR_MODE_OUT);
    xGPIOSPinWrite(PC12, 1);

}


//*****************************************************************************
//
// \brief  The main function of 
//
// \return none
//
//*****************************************************************************
void TemperatureGet(void)
{
    int i;  
    
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
     
    //
    // Init the gpio connected to led
    //     
    GPIOInit();
 
    //
    // AD7417Dev Init
    //
    AD7417Init(10000, AD7417_ShutDown_Disable | AD7417_Triger_Disable);
    
    
    //
    // Select temperature channel, OTI interrupt mode,
    // OTI active output low, fault queue is 1;
    //
    AD7417TempConfig(AD7417_OTI_INT | AD7417_OTI_ACTIVE_LOW |
                     AD7417_FAULTQUE_1 | AD7417_TEMP_CHANNEL);
    
    //
    // Enable OTI interrupt, install callback function
    //
    AD7417OTIntEnable();
    AD7417OTIntCallbackInit(SensorEvent);
 
    //
    // Set the up temperature(TOTI) to 35, when the Ambient temperature reach 
    // at 35, the OTI pin will active low, and the trigger the AD7417_OTI_PIN 
    // interrupt.
    //
    AD7417LowLimitSetLong(32);
    AD7417UpLimitSetLong(35);
    
   
    while(1)
    {        
        //
        // Get and print the temperature
        //
        AD7417TempReadLDC();
        for(i = 0; i < 1000000; i++);
     
    }
}
