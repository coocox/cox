#include"Sensor_Shield.h"
#include "cookie.h"
#include "xsysctl.h"
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xcore.h"
#include "xgpio.h"
unsigned long key1;
unsigned long key2;
unsigned long tuch;
unsigned long Key1Callback(void *pvCBData,
						   unsigned long ulEvent,
						   unsigned long ulMsgParam,
						   void *pvMsgData)
{
	key1++;
	SensorShieldOutWrite(SENSOR_SHIELD_O0, key1%2);
	SensorShieldOutWrite(SENSOR_SHIELD_O1, (key1+1)%2);
    return 0;
}
unsigned long Key2Callback(void *pvCBData,
						   unsigned long ulEvent,
						   unsigned long ulMsgParam,
						   void *pvMsgData)
{
	key2++;
	//SensorShieldOutWrite(SENSOR_SHIELD_O1, key2%2);
    return 0;
}
unsigned long Key3Callback(void *pvCBData,
						   unsigned long ulEvent,
						   unsigned long ulMsgParam,
						   void *pvMsgData)
{
	tuch++;
	SensorShieldOutWrite(SENSOR_SHIELD_O2, tuch%2);
    return 0;
}

int main(void)
{
	unsigned char i;
	xSysCtlClockSet(16000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
//	xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);


	SensorShieldInit();
	SensorShieldIOInit();

    xGPIOSPinDirModeSet(SENSOR_SHIELD_I0, xGPIO_DIR_MODE_IN);
    xGPIOSPinDirModeSet(SENSOR_SHIELD_I1, xGPIO_DIR_MODE_IN);
    xGPIOSPinDirModeSet(SENSOR_SHIELD_I2, xGPIO_DIR_MODE_IN);
    xGPIOSPinIntEnable(SENSOR_SHIELD_I0, xGPIO_RISING_EDGE);
    xGPIOSPinIntEnable(SENSOR_SHIELD_I1, xGPIO_RISING_EDGE);
    xGPIOSPinIntEnable(SENSOR_SHIELD_I2, xGPIO_RISING_EDGE);
    xGPIOSPinIntCallbackInit(SENSOR_SHIELD_I0, Key1Callback);
    xGPIOSPinIntCallbackInit(SENSOR_SHIELD_I1, Key2Callback);
    xGPIOSPinIntCallbackInit(SENSOR_SHIELD_I2, Key3Callback);
    xIntEnable(xINT_GPIOB);
    xIntEnable(xINT_GPIOB);

	SensorShieldOutWrite(SENSOR_SHIELD_O0, 1);
	SensorShieldOutWrite(SENSOR_SHIELD_O1, 1);
	SensorShieldOutWrite(SENSOR_SHIELD_O2, 1);
	SensorShieldOutWrite(SENSOR_SHIELD_O3, 1);
	SensorShieldOutWrite(SENSOR_SHIELD_O4, 1);
	SensorShieldOutWrite(SENSOR_SHIELD_O5, 1);

    while(1)
    {
    	if(key2)
    	{
    		key2 = 0;
    		for(i=0;i<10;i++){
    		SensorShieldOutWrite(SENSOR_SHIELD_O0, 1);
    		SensorShieldOutWrite(SENSOR_SHIELD_O1, 1);
    		SensorShieldOutWrite(SENSOR_SHIELD_O2, 1);
    		SysCtlDelay(1000000);
    		SensorShieldOutWrite(SENSOR_SHIELD_O0, 0);
    		SensorShieldOutWrite(SENSOR_SHIELD_O1, 0);
    		SensorShieldOutWrite(SENSOR_SHIELD_O2, 0);
    		SysCtlDelay(1000000);
    		}
    	}
    }
}
