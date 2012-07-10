#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_i2c.h"
#include "xi2c.h"

unsigned long ulMaster = I2C1_BASE;
unsigned char ucTempData[5] = "abcd";
unsigned char ucTemp[5];
unsigned char ucTempCount = 0;
unsigned char ucTempCount1 = 0;


//*****************************************************************************
//
//! \brief xi2c Configure main body.
//!
//! \return None.
//
//*****************************************************************************
void xI2CConfig(void)
{
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);
    xSysCtlPeripheralEnable2(ulMaster);

    xSysCtlPeripheralEnable2(xGPIO_PORTD_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C1SCK, PB6);
    xSPinTypeI2C(I2C1SDA, PB7);

    I2CMasterInit(ulMaster, 400000, xfalse, xfalse);
    I2CEnable(ulMaster);
    
    I2CMasterWriteS1(ulMaster, 0x12, 'a', xfalse);
    I2CMasterWriteS2(ulMaster, 'b', xfalse);
    I2CMasterWriteS2(ulMaster, 'c', xfalse);
    I2CMasterWriteS2(ulMaster, 'd', xfalse);
    
    I2CMasterReadBufS1(ulMaster, 0x12, ucTemp, 5, xtrue);
}