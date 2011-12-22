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
#include "xhw_ints.h"
#include "xcore.h"
#include "xspi.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "SpiMaster.h"

unsigned long SendData[] = {145,4,2,5,3,9,8,4,1,214,36,14,25,387,15,25,36,1,2};
unsigned long IntMessage[] = {145,4,2,5,3,9,8,4,1,214,25,387,15,25,36,1,2};
unsigned long ReceData[64];
unsigned long i;
unsigned long TransferOver(void *pvCBData, 
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
  
}

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
    // Enable Peripheral SPI0,SPI1
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    xIntEnable(INT_SPI0);
    xIntPrioritySet(INT_SPI0, 1);
    xSPIIntEnable(SPI0_BASE, xSPI_INT_EOT);
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
void SpiMasterModeConfig(void)
{
    
    //
    // Configure Some GPIO pins as SPI Mode
    //
    xSPinTypeSPI(SPI0CLK, PC1);
    xSPinTypeSPI(SPI0MOSI, PC3);
    xSPinTypeSPI(SPI0MISO, PC2);
    xSPinTypeSPI(SPI0CS, PC0);
    
    //
    // Master Mode  polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 2000000Hz 8Bits Data windth  SPI MSB First
    //
    xSPIConfigSet(SPI0_BASE,2000000,SPI_FORMAT_MODE_5 | 
                                SPI_DATA_WIDTH8 | 
                                SPI_MSB_FIRST | SPI_MODE_MASTER);
    //
    // Software Control Transfer Select SS0 and SS1
    //
    xSPISSSet(SPI0_BASE, xSPI_SS_HARDWARE, SPI_SS0);   
    xSPIIntEnable(SPI0_BASE, xSPI_INT_EOT);
   
    for(i=0;i<22;i++)
    {
        xSPIDataWrite(SPI0_BASE,SendData,21);
        xSPIDataRead(SPI0_BASE,ReceData, 22);
        ReceData[i] = xSPISingleDataReadWrite(SPI0_BASE, SendData[i]);
    }
}
