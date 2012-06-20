#include "coshining.h"
#include "xgpio.h"
#include "xadc.h"
#include "xuart.h"
#include "xsysctl.h"
#include "LCDShield.h"

const char cKey[5][6] = {"right","up","dowm","left","select"};

int main()
{
    int key;
	
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    xSysCtlDelay(1000);
	
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);	
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD13));   
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);
	
    LCDShieldInit();
	
    //
    // Enable Peripheral SPI0
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
	  
    xSPinTypeADC(ADC0, sA0);
	  
    //
    // ADC Channel0 convert once, Software tirgger.
    //
    xADCConfigure(xADC0_BASE, xADC_MODE_SCAN_CONTINUOUS, ADC_TRIGGER_PROCESSOR);  
	  
    //
    // Enable the channel0
    //
    xADCStepConfigure(xADC0_BASE, 0, xADC_CTL_CH0); 
    
    //
    // Enable the adc
    //
    xADCEnable(xADC0_BASE);
		
    //
    // start ADC convert
    //
    xADCProcessorTrigger( xADC0_BASE );
		
    LCDShieldLocationSet(0, 0);
    LCDShieldDisplayString("Hello Nuvoton!");
    LCDShieldLocationSet(0, 1);
    LCDShieldDisplayString("Hello CooCox! ");
		
    xSysCtlDelay(1000000);

    while(1)
    {
        key = LCDShieldButtonGet();
        if(key != -1)
        {
            LCDShieldDisplayClear();
            LCDShieldLocationSet(0, 0);
            LCDShieldDisplayString("The key is: ");
            LCDShieldLocationSet(0, 1);
            LCDShieldDisplayString(&cKey[key][0]);
        }
    }
}
