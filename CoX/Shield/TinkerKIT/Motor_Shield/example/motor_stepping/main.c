#include "xhw_types.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "MotorShield.h"

int main()
{
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(10000);
    
    MSStepMotorInit();
    
    MSStepsDelaySet(2);
    
    while(1)
    {
        MSStepMotorRun(MS_RUN_BACKWARD, 4);
        MSStepMotorStop();
    }
}			  	
