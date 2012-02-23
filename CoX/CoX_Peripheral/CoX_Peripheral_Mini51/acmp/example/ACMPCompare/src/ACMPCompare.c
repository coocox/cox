//*****************************************************************************
//
//! \file SPI_loop.c
//! \brief Test SPI.
//! \version 1.0
//! \date 2/17/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"
#include "xacmp.h"

unsigned long AcmpCallback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,void *pvMsgData);

//*****************************************************************************
//
//! Ininite the ACMP 
//!
//! \param None
//!
//! This function ininite the ACMP including clock source and enable ACMP 
//!
//! \return none
//
//*****************************************************************************
void ACMPCompare(void)
{
    //
    // Set SysClk 12MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Enable Peripheral ACMP
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_ACMP0);
    
    //
    // Configure the ACMP pin
    //
    xSPinTypeACMP(CMP0P, PB5);
    xSPinTypeACMP(CMP0N, PB4);
    xSPinTypeACMP(CMP0O, PD6);
    
    //
    // Congigure Comp-(Analog source negative input) is CPN pin
    //
    xACMPConfigure(xACMP0_BASE, 0, xACMP_ASRCN_PIN);
    
    //
    // Configure the INT 
    //
    xACMPIntCallbackInit(xACMP0_BASE, 0, AcmpCallback);
    xACMPIntEnable(xACMP0_BASE, 0);	
    xIntEnable(xINT_ACMP0);

    //
    // Enable ACMP
    //
    xACMPEnable(xACMP0_BASE, 0);    
}


//*****************************************************************************
//
//! \brief ACMP callback interrupt
//!
//! \param None
//!
//! \return none
//
//*****************************************************************************
unsigned long AcmpCallback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,void *pvMsgData)
{
    //
    // add your own code
    //
    //...
  
    return 0;
}