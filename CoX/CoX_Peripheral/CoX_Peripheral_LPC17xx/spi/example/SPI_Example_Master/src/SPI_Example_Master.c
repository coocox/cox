/******************************************************************************
 * \file    SPI_Example_Master.c
 * \brief   Show how to configure SPI master mode, how to transmit data via spi.
 * 
******************************************************************************/

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_spi.h"
#include "xspi.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)

#define BUF_SIZE                20

// SPI Transmit Data buffer
static unsigned long SPIRecv[BUF_SIZE];

// SPI Receive Data buffer
static unsigned long SPITran[BUF_SIZE];

void SPI_Example_Master(void);


void SPI_Example_Master(void)
{ 
    unsigned long i = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Map SPI Pin
    xSPinTypeSPI(SPI0CLK , PA15);
    xSPinTypeSPI(SPI0CS  , PA16);
    xSPinTypeSPI(SPI0MISO, PA17);
    xSPinTypeSPI(SPI0MOSI, PA18);

    // Enable SPI Power
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI);

    // Configure SPI
    SPICfg( SPI0_BASE, 1000000, SPI_DATA_LEN_8  | SPI_MODE_MASTER |
            SPI_CPHA_FIRST  | SPI_CPOL_LOW    | SPI_MSB_FIRST);

    // Initialize Buffer
    for(i = 0; i < BUF_SIZE; i++)
    {
        SPIRecv[i] = 0;
        SPITran[i] = i;
    }

    // Transmit data to SPI slave then receive data from spi slave.
    for(i = 0; i < BUF_SIZE; i++)
    {
        SPIRecv[i] = SPIDataReadWrite(SPI0_BASE, SPITran[i]);
    }

    // Infinite loop
    while (1)
    {
        ;  // DoNothing
    }
}

