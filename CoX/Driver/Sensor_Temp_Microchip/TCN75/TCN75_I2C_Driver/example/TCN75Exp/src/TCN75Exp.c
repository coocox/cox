#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"
#include "xi2c.h"
#include "TCN75.h"
#include "xhw_TCN75.h"

float  fTemp = 30;
unsigned long uli = 0, ulj;

unsigned long test_Led (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData);

void TCN75Exp()
{   
    //
	// Initalizes I2C.
	//
    TCN75Init(5000);

	//
	// Sets fault queue number.
	//
	TCN75FaultQueSet(TCN75_FAULTQUE_6);

	//
	// Sets temperature in THYS and TSET registers.
	//
    TCN75RegWrite(TCN75_THYS, &fTemp);
	TCN75RegWrite(TCN75_TSET, &fTemp);

	xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_12, GPIO_DIR_MODE_OUT);
    
	//
	// Sets TCN75 as compare mode and low level alert.
	//
	TCN75IntConfig(test_Led, ALERTPOL_LOW, TCN75_MODE_CMP);

    xIntEnable(xINT_GPIOB);
    xIntMasterEnable();
	
	while(!uli)
	{
	    //
		// Gets current temperature.
		//
	    fTemp = TCN75TempReadFDC(TCN75_TEMP);

	    for(ulj = 0; ulj < 0xfff ;ulj++);
	}
	xIntDisable(xINT_GPIOB);
	xIntMasterDisable(); 
  
	//
	// Disables I2C0, set TCN75 as shutdown mode.
	//
	TCN75DeInit();	
}

unsigned long test_Led (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
	xGPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 0);

	uli = 1;

    return 0;
}

