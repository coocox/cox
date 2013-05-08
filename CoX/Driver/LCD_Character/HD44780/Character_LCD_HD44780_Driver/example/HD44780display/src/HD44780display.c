//*****************************************************************************
//
//! \file HD44780display.c
//! \brief HD44780 & ad key test.
//! \version 1.0
//! \date 01/11/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_spi.h"
#include "xspi.h"
#include "hw_hd44780.h"
#include "hd44780.h"

//*****************************************************************************
//
//! \brief This function is to test LCD44780.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void hd44780display(void)
{
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(100000);

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    HD44780Init();

	//
    // Location Set & Display string, number Test
    //
    HD44780LocationSet(0, 0);
    HD44780DisplayString("Hello HD44780!");
    HD44780LocationSet(0, 1);
    HD44780DisplayString("Number:");
    HD44780DisplayN(10086);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780LocationSet(0,1);
    HD44780DisplayString("Display off/on");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780DisplayOff();
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    HD44780DisplayOn();
    xSysCtlDelay(xSysCtlClockGet() / 4);
}
	
