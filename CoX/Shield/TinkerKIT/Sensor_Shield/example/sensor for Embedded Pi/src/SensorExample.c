//*****************************************************************************
//
//! \file SensorExample.c
//! \brief Get ADC value from sensor shield and
//!        then print the ad value through UART.
//! \date 9/20/2011
//! \author CooCox
//!
//! \copy
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "xhw_adc.h"
#include "xadc.h"
#include "xhw_i2c.h"
#include "xi2c.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "Sensor_Shield.h"


//*****************************************************************************
//
//! \biref The main example function
//!
//! \return  none
//
//*****************************************************************************

void SensorExample(void)
{
	int ADValue;
	char buf[4];
	//
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(100000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable2(sUART_BASE);
    xUARTConfigSet(sUART_BASE, 115200, (xUART_CONFIG_WLEN_8 |
									     xUART_CONFIG_STOP_1 |
									     xUART_CONFIG_PAR_NONE));
    xUARTEnable(sUART_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    sPinTypeUART(sUART_BASE);

	SensorShieldInit();

    while(1){
        ADValue = ADCValueGet(SENSOR_SHIELD_AI2);
        buf[0] = ADValue/1000 + 0x30;
        buf[1] = ADValue/100%10 + 0x30;
        buf[2] = ADValue/10%10 + 0x30;
        buf[3] = ADValue%10 + 0x30;
	    SensorShieldUARTBufferPut(sUART_BASE, buf, 4);
    }
}
