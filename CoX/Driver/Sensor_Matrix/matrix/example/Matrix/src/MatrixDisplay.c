#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_timer.h"
#include "xtimer.h"
#include "Dot_Matrix.h"

#define delay 0x1fffff

//*****************************************************************************
//
//! \brief This function is to test dot matrix.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void DotMatrixDisplay(void)
{
    int j;

    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(100000);

    DM163PinInit();
    DotMatrixSetGamma();
    DotMatrixOpenLine(9);
    DotMatrixScanTimerInit(12000000, 100);

    while(1)
    {
    	DotMatrixShowChar('A', 255, 0, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('B', 0, 255, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('C', 0, 0, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('D', 255, 255, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('E', 0, 255, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('F', 255, 255, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('G', 255, 0, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('H', 255, 127, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('I', 127, 255, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('J', 127, 0, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('K', 255, 127, 127,0);
        xSysCtlDelay(delay);

        //
        //! Move left
        //
        for(j = -7; j < 8; j++)
        {
            DotMatrixShowChar('S', 255, 0, 0, j);
            xSysCtlDelay(0x1ffff);
        }

        //
        //! Move right
        //
        for(j = 7; j > -8; j--)
        {
            DotMatrixShowChar('M', 0, 0, 255, j);
            xSysCtlDelay(0x1ffff);
        }
    }
}
