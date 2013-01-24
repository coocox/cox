#include "cookie.h"
#include "xpwm.h"
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "xhw_i2c.h"
#include "xi2c.h"
#include "xadc.h"
#include "t0006x.h"
#include "ArduinoMotorShield.h"
#include <stdio.h>

void LCD4884_example(void);
void MotorTest();
char buffer1[10];
char buffer2[10];
char buffer3[10];
unsigned long ulData;
int main(void)
{
//	embeddedpiTest();
//	MotorTest();
//	tLPR5150ALData g_XYAxisAngle;
//    //
//    // Initionalize system clock.
//    //
//    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
//
//    //automatically added by CoIDE
//	LCD4884_example();
//	LPR5150ALInit();
//
//	while(1)
//    {
//
//        LCD4884StringWrite(0,0,"ADC X:");
//		ulData = ADCDataInjectedGet(LPR5150AL_ADC_BASE, 3) & 0xFF0;
//		sprintf(buffer3, "%d", ulData);
//		LCD4884StringWrite(0,48,buffer3);
//
//		LCD4884StringWrite(3,0,"ADC Y:");
//		ulData = ADCDataInjectedGet(LPR5150AL_ADC_BASE, 4) & 0xFF0;
//		sprintf(buffer3, "%d", ulData);
//		LCD4884StringWrite(3,48,buffer3);
//
//        LCD4884StringWrite(1,0,"angular of X:");
//        LCD4884StringWrite(4,0,"angular of Y:");
//		g_XYAxisAngle = LPR5150ALXYAxisAngleGet();
//		sprintf(buffer1, "%f", g_XYAxisAngle.fXAxisData);
//		sprintf(buffer2, "%f", g_XYAxisAngle.fYAxisData);
//		LCD4884StringWrite(2,0,buffer1);
//		LCD4884StringWrite(5,0,buffer2);
//		xSysCtlDelay(1000000);
//    }


	xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
//	AMSDCMotorPWMInit(AMS_MOTOR_B, 10, 50);
//	AMSDCMotorPWMInit(AMS_MOTOR_A, 10, 50);
//
//	AMSDCMotorRun(AMS_MOTOR_B, AMS_RUN_FORWARD);
//	embeddedpiTest();

	AMSStepMotorInit();
	AMSStepMotorRun(AMS_RUN_FORWARD, 100);
	while(1);
}

