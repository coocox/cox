//*****************************************************************************
//
//! \file SPI_loop.c
//! \brief Test SPI.
//! \version 1.0
//! \date 8/2/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "SpiSlave.h"
#include "xhw_ints.h"
#include "xcore.h"

unsigned long SendData[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
unsigned long ReceData[64];
unsigned long i;

//*****************************************************************************
//
//! Ininite the SPI case which is needed
//!
//! \param None
//!
//! This function ininite the SPI including clock source and enable spi 
//!
//! \return none
//
//*****************************************************************************
void SpiReceiveTransferInit(void)
{
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(36000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_12MHZ);
    //
    // Enable Peripheral SPI0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
}
//*****************************************************************************
//
//! Spi Master Slave Mode Configure
//!
//! \param None
//!
//! This function configure the SPI as master and slave mode at the same time
//! transfer and receive data
//!
//! \return None
//
//*****************************************************************************
void SpiSlaveModeConfig(void)
{
    
    //
    // Configure Some GPIO pins as SPI Mode
    //
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_2);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_3);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_0);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_1);

    xHWREG(SPI0_BASE + SPI_CNTRL) = 0x00000000;
    xHWREG(SPI0_BASE + SPI_CNTRL) |= 0x00040844;
    //
    // Level Trig Slave at High Level
    //
    SPISSConfig(SPI0_BASE, SPI_SS_LEVEL_TRIGGER,SPI_SS_ACTIVE_HIGH_RISING);
    for(i=0;i<22;i++)
    {
        SPIDataWrite(SPI0_BASE,SendData,22);
        SPIDataRead(SPI0_BASE,ReceData,22);
        
    }
}
