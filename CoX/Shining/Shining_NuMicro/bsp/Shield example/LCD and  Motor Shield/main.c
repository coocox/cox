#include "coshining.h"
#include "coshining_cfg.h"
#include "hd44780.h"
#include "sdcard.h"

#include "xhw_pwm.h"
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

static unsigned char pucBuf[1024] = {"CooCox"};


//*****************************************************************************
//
//! \brief ADC callback interrupt
//!
//! \param None
//!
//! \return none
//
//*****************************************************************************
unsigned long ADCCallback(void *pvCBData,  unsigned long ulEvent,
                          unsigned long ulMsgParam,void *pvMsgData)
{
    unsigned long ulValueLength;
    unsigned long ulData[10];
    //
    // Read the convert value
    //
    ulValueLength = xADCDataGet(xADC0_BASE, ulData);
    return 0;
}

void SendData74HC595(unsigned char ucData)
{
    unsigned long i = 0;
    unsigned long ulBit = 0;
    xGPIOSPinTypeGPIOOutput(sD4);
    xGPIOSPinTypeGPIOOutput(sD8);
    xGPIOSPinTypeGPIOOutput(sD7);
	
    // 
    // 74HC595 operation
    // Output Enable
    //
    xGPIOSPinWrite(sD7, 1);
    xGPIOSPinWrite(sD7, 0);

    //
    // Send Data 0xF7 to 74HC595
    //
    xGPIOSPinWrite(sD4, 0);
    for(i=0; i<8; i++)
    {
        if((ucData & (1<<i)))
        {
            xGPIOSPinWrite(sD8, 1);
        }
        else
        {
            xGPIOSPinWrite(sD8, 0);	
        }
        xGPIOSPinWrite(sD4, 1);
        xSysCtlDelay(1);
        xGPIOSPinWrite(sD4, 0);
    }
    //
    // Latch Data to 74HC595
    //
    xGPIOSPinWrite(sD12, 0);
    xSysCtlDelay(1);
    xGPIOSPinWrite(sD12, 1);
    xSysCtlDelay(1);
    xGPIOSPinWrite(sD12, 0);
}
//*****************************************************************************
//
//! \brief System and PWM Initialize.
//!
//! \param None
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void xSysCtlAndPwmInit(void)
{
    unsigned long i = 0;
    unsigned long ulBit = 0;
    //
    // Set System clock is 48M
    //
    xSysCtlClockSet(48000000, (xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ));

    //
    // Enable GPIO and PWM
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOE);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOE);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_PWMB);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMB);


    //
    // Set PE2(DIR_CLK), PD3(DIR_SER), and PA6(DIR_LATCH) PD2(DIR_EN) as output
    //
    xGPIOSPinTypeGPIOOutput(sD4);
    xGPIOSPinTypeGPIOOutput(sD8);
    xGPIOSPinTypeGPIOOutput(sD12);
    xGPIOSPinTypeGPIOOutput(sD7);

    //
    // Set PWM Clock Source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_MAIN, 4);
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMB_MAIN, 4);

    //
    // Congigure the PWM pin(PWM7, sD11))
    //
    sD11PinTypePWM();
    //xGPIOSPinTypeGPIOOutput(sD11);
    //xGPIOSPinWrite(sD11, 1);

    // 
    // 74HC595 operation
    // Output Enable
    //
    SendData74HC595(0x60);
}
//*****************************************************************************
//
//! \brief Using PWM to Driver Motor.
//!
//! \param None
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void xPWMotorControl(void)
{
    
    xSysCtlAndPwmInit();

    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure(xPWMB_BASE, xPWM_CHANNEL7, xPWM_TOGGLE_MODE |
                                                 xPWM_OUTPUT_INVERTER_DIS | 
                                                 xPWM_DEAD_ZONE_DIS);

    //
    // Set CNR, Prescale and Divider
    //
    xPWMFrequencyConfig(xPWMB_BASE, xPWM_CHANNEL7, xPWM_FREQ_CONFIG(16,150,5000));

	
    //    
    // Set CMR
    //
    xPWMDutySet(xPWMB_BASE, xPWM_CHANNEL7, 50);
	
    //    
    // Set output enable
    //
    xPWMOutputEnable(xPWMB_BASE, xPWM_CHANNEL7); 
	
	
    //    
    // start PWM
    //
    xPWMStart(xPWMB_BASE, xPWM_CHANNEL7);
}
unsigned long ulDuty = 50;
int main()
{
    unsigned long i;
    unsigned char ucRet = 0;
    unsigned long ulValueLength;
    unsigned long ulData[10];
    
	  
    xPWMotorControl();

    HD44780Init();
	
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
    // Enable the ADC end of conversion interrupt
    //  
    //xADCIntEnable(xADC0_BASE, xADC_INT_END_CONVERSION);  
    
    //
    // install the call back interrupt
    //
    //xADCIntCallbackInit(xADC0_BASE, ADCCallback);
    
    //
    // Enable the NVIC ADC interrupt
    //
    //xIntEnable(xINT_ADC0);
    
    //
    // Enable the adc
    //
    xADCEnable(xADC0_BASE);
		
    //
    // start ADC convert
    //
    xADCProcessorTrigger( xADC0_BASE );
		
    HD44780LocationSet(0, 0);
    HD44780DisplayString("Hello Nuvoton!");
    HD44780LocationSet(0, 1);
    HD44780DisplayString("Hello CooCox! ");
		
    SysCtlDelay(10000000);
		
    while(1)
    {
        SysCtlDelay(1000000);
        //
        // Read the convert value
        //
        ulValueLength = xADCDataGet(xADC0_BASE, ulData);
			
	
        if (ulData[0] < 0x30100)
        {
            HD44780DisplayClear();
            HD44780LocationSet(0, 0);
            HD44780DisplayString("right");
            SendData74HC595(0x60);
            sD11PinTypePWM();
            xPWMStart(xPWMB_BASE, xPWM_CHANNEL7);
            xGPIOSPinWrite(sD3, 1);
        }
        else if(ulData[0] < 0x30300)
        {
            HD44780DisplayClear();
            HD44780LocationSet(0, 0);
            HD44780DisplayString("up");
            ulDuty++;
            xPWMDutySet(xPWMB_BASE, xPWM_CHANNEL7, ulDuty);
            sD11PinTypePWM();
            xPWMStart(xPWMB_BASE, xPWM_CHANNEL7);
            xGPIOSPinWrite(sD3, 1);
            SysCtlDelay(100000);
        }
        else if(ulData[0] < 0x30500)
        {
            HD44780DisplayClear();
            HD44780LocationSet(0, 0);
            HD44780DisplayString("dowm");
            ulDuty--;
            xPWMDutySet(xPWMB_BASE, xPWM_CHANNEL7, ulDuty);
            sD11PinTypePWM();
            xPWMStart(xPWMB_BASE, xPWM_CHANNEL7);
            xGPIOSPinWrite(sD3, 1);
            SysCtlDelay(100000);
			  
        }
        else if(ulData[0] < 0x30800)
        {
            HD44780DisplayClear();
            HD44780LocationSet(0, 0);
            HD44780DisplayString("left");
            SendData74HC595(0x18);
            sD11PinTypePWM();
            xPWMStart(xPWMB_BASE, xPWM_CHANNEL7);
            xGPIOSPinWrite(sD3, 1);
        }
        else if(ulData[0] < 0x30B00)
        {
            HD44780DisplayClear();
            HD44780LocationSet(0, 0);
            HD44780DisplayString("select");
            SendData74HC595(0x60);
            sD11PinTypePWM();
            xPWMStart(xPWMB_BASE, xPWM_CHANNEL7);
            xGPIOSPinWrite(sD3, 1);
        }
        else 
        {
            HD44780DisplayClear();
            HD44780LocationSet(0, 0);
            HD44780DisplayString("Nothing");
            xPWMStop(xPWMB_BASE, xPWM_CHANNEL7);
            xGPIOSPinTypeGPIOOutput(sD11);
            xGPIOSPinTypeGPIOOutput(sD3);
            xGPIOSPinWrite(sD11, 0);
            xGPIOSPinWrite(sD3, 0);
        }
        if(ulDuty >= 99)
        {
            ulDuty = 99;
        }
        if(ulDuty <= 1)
        {
            ulDuty = 1;
        }      
    }
    
    //
    // SD Card Init
    //
    ucRet = SDInit();
    
    //
    // write a block to the card 
    //
    ucRet = SDBlockWrite(pucBuf, 0);
	
    //
    // Re-init the test buffer to 0
    //
    for(i = 0; i < 512; i++)
    {
        pucBuf[i] = 0;
    }
	  
    //
    // Read 1 block from the card
    //    
    ucRet = SDBlockRead(pucBuf, 0);
			
    while(1);
}
