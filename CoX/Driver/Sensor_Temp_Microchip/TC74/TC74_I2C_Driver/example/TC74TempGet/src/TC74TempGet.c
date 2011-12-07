#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "TC74.h"
#include "hw_TC74.h"
unsigned char ucMode, ucStatus, ucTemp;
void TemperatureGet()
{   
    //
	//Initalizes I2C.
	//
    TC74Init(50000);

    //
    //Sets TC74 as standby mode.
    //
    TC74ModeSet(TC74_MODE_STANDBY);
    
    //
    //Gets the mode of TC74.
    //
    ucMode = TC74ModeGet();

    //
    //Sets TC74 as normal mode.
    //
    TC74ModeSet(TC74_MODE_NORMAL);

    //
    //Gets the mode of TC74.
    //
    ucMode = TC74ModeGet();

    ucTemp = TC74TempGet();
	//
	// Disable I2C0, set TC74 as standby mode.
	//
	TC74DeInit();	
}


