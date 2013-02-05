#include "xhw_types.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "ArduinoMotorShield.h"

int main()
{

    xSysCtlClockSet(72000000, (xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ));


	AMSDCMotorPWMInit(AMS_MOTOR_B, 100000, 50);
	AMSDCMotorPWMInit(AMS_MOTOR_A, 100000, 50);

	AMSDCMotorRun(AMS_MOTOR_B, AMS_RUN_FORWARD);

//	AMSStepMotorInit();
//	AMSStepMotorRun(AMS_RUN_FORWARD, 100);

	while(1);
}			  	
