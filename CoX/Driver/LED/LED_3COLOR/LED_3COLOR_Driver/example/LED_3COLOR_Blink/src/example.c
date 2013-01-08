#include "RGBLed.h"

int test(void)
{

	int i;
	rgbled_init();
	while(1)
	{
		for(i=0; i<100000; i++);
		rgbled_turnOn(RGBLED_R);
		for(i=0; i<100000; i++);
		rgbled_turnOn(RGBLED_G);
		for(i=0; i<100000; i++);
		rgbled_turnOn(RGBLED_B);
		for(i=0; i<100000; i++);
		rgbled_turnOff(RGBLED_R);
		for(i=0; i<100000; i++);
		rgbled_turnOff(RGBLED_G);
		for(i=0; i<100000; i++);
		rgbled_turnOff(RGBLED_B);
	}
}
