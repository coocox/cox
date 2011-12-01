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
#include "hw_TCN75.h"

float  fTemp = 25;
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
	// config TCN75.
	//
	TCN75WakeUp();
	TCN75Config(TCN75_MODE_CMP | TCN75_POLARITY_HIGH | TCN75_FAULTQUE_6);
	TCN75LowLimitSet(fTemp);
	TCN75UpLimitSet(fTemp);
	
	
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_12, GPIO_DIR_MODE_OUT);
    
	TCN75IntConfig(test_Led);

    xIntEnable(xINT_GPIOB);
    xIntMasterEnable();
	
	uli = 0;

	while(!uli)
	{
	    fTemp = TCN75TempReadFDC();
		
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

