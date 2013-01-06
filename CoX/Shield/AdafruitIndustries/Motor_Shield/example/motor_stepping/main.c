#include "xhw_types.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "coshining_cfg.h"
#include "coshining.h"
#include "MotorShield.h"

int main()
{
    unsigned long i, j;

    xSysCtlClockSet(12000000, (xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ));

/*
	xGPIOSPinTypeGPIOOutput(sD3);   
    //
	// MSDelay() test
	//
	while(1)
	{
	    xGPIOSPinWrite(sD3, 1);
		MSDelay(xTIMER0_BASE, xTIMER_CHANNEL0, 1);
	    xGPIOSPinWrite(sD3, 0);
	    MSDelay(xTIMER0_BASE, xTIMER_CHANNEL0, 1);
    }
*/

	MSStepMotorInit(MS_STEPPER_NUM2);
	MSStepsDelaySet(1);
	for(i = 0; i < 50; i++)
	{
		MSStepMotorRun(MS_RUN_FORWARD, 50);
		MSStepMotorStop();
	}


}			  	
