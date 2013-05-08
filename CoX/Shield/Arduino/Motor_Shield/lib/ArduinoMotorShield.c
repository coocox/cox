//*****************************************************************************
//
//! \file ArduinoMotorShield.c
//! \brief Driver for the Motor controller
//! \version V2.1.1.0
//! \date 6/7/2012
//! \author CooCox
//! \copy
//!
//
//*****************************************************************************

#include "xhw_types.h"
#include "xcore.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xpwm.h"
#include "xhw_timer.h"
#include "xtimer.h"
#include "xadc.h"
#include "cookie.h"
#include "cookie_cfg.h"
#include "ArduinoMotorShield.h"

//
//! Step Motor 42BYGH403AA run forward pulse data in 8 pat
//
static unsigned long g_ul42BYGHForward[8] = {0x09, 0x0D, 0x01, 0x02, 0x06, 0x07, 0x04, 0x08};


//
//! Step motor steps delay
//
static unsigned long g_ulStepsDelay = 10;

//*****************************************************************************
//
//! \brief Init the PWM corresponding pins, and enable the corresponding port.
//!
//! \param ulBase is the selected PWM.
//! \param ulMotor is the selected pwm channel.
//!
//! The \e ulBase parameter can be one of the values:
//! \b sPWMA_BASE, \b sPWMB_BASE.
//!
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSDCMotorPWMInit(unsigned long ulMotor, unsigned long ulFrequency,
		          unsigned long ulDuty)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == AMS_MOTOR_A) ||
	        (ulBase == AMS_MOTOR_B));

    //
	// Enable the corresponding	port
	//
	switch(ulMotor)
	{
    	case AMS_MOTOR_A:
     	{
	        //
	    	// Enable the corresponding port and configure function pin
	    	//
     		xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD3));
     		xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD12));
     		xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD9));
     		xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
     		xSysCtlPeripheralEnable2(sPWMB_BASE);

     		xGPIOSPinDirModeSet(sD12,xGPIO_DIR_MODE_OUT);
     		xGPIOSPinDirModeSet(sD9,xGPIO_DIR_MODE_OUT);

     		xGPIOSPinWrite(sD9,1);

     		sD3PinTypePWM();
     		xGPIOSPinDirModeSet(sD3,GPIO_DIR_MODE_HWSTD);


     		//
     	    // Set invert, dead zone and mode
     	    //
     	    xPWMInitConfigure(sPWMB_BASE, xPWM_CHANNEL0, xPWM_TOGGLE_MODE |
     	                                                 xPWM_OUTPUT_INVERTER_DIS |
     	                                                 xPWM_DEAD_ZONE_DIS);

     	    //
     	    // Set CNR, Prescale and Divider
     	    //
     	    xPWMFrequencySet(sPWMB_BASE, xPWM_CHANNEL0, ulFrequency);

     	    //
     	    // Set CMR
     	    //
     	    xPWMDutySet(sPWMB_BASE, xPWM_CHANNEL0, ulDuty);

     	    //
     	    // Set output enable
     	    //
     	    xPWMOutputEnable(sPWMB_BASE, xPWM_CHANNEL0);

     	    //
     	    // start PWM
     	    //
     	    xPWMStart(sPWMB_BASE, xPWM_CHANNEL0);

		    break;
	    }
    	case AMS_MOTOR_B:
	    {
	        //
		    // Enable the corresponding port and configure function pin
		    //
     		xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD8));
     		xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD11));
     		xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD13));
     		xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
     		xSysCtlPeripheralEnable2(sPWMA_BASE);

     		xGPIOSPinDirModeSet(sD13,xGPIO_DIR_MODE_OUT);
     		sD8PinTypeOUT();

     		xGPIOSPinWrite(sD8,1);

     		sD11PinTypePWM();
     		xGPIOSPinDirModeSet(sD11,GPIO_DIR_MODE_HWSTD);

     		//
     	    // Set invert, dead zone and mode
     	    //
     	    xPWMInitConfigure(sPWMA_BASE, xPWM_CHANNEL2, xPWM_TOGGLE_MODE |
     	                                                 xPWM_OUTPUT_INVERTER_DIS |
     	                                                 xPWM_DEAD_ZONE_DIS);

     	    //
     	    // Set CNR, Prescale and Divider
     	    //
     	   xPWMFrequencySet(sPWMA_BASE, xPWM_CHANNEL2, ulFrequency);

     	    //
     	    // Set CMR
     	    //
     	    xPWMDutySet(sPWMA_BASE, xPWM_CHANNEL2, ulDuty);

     	    //
     	    // Set output enable
     	    //
     	    xPWMOutputEnable(sPWMA_BASE, xPWM_CHANNEL2);

     	    //
     	    // start PWM
     	    //
     	    xPWMStart(sPWMA_BASE, xPWM_CHANNEL2);
		    break;
	    }
	    default:
	    break;
	}

}

//*****************************************************************************
//
//! \brief Configure the PWM frecqurecy and output duty cycle.
//!
//! \param ulMotor is the selected pwm channel.
//! \param ulDir is the selection of Motor rev direction.
//!
//! The \e ulMotor parameter can be one of the values:
//! \b AMS_MOTOR_A, \b AMS_MOTOR_B,
//!
//! The \e ulDir parameter can be one of the values:
//! \b AAMS_RUN_FORWARD, \b AMS_RUN_BACKWARD.
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSDCMotorRun(unsigned long ulMotor, unsigned long ulDir)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == AMS_MOTOR_A) ||
	        (ulBase == AMS_MOTOR_B));
    xASSERT((ulDir == AAMS_RUN_FORWARD) ||
			(ulDir == AMS_RUN_BACKWARD));

    if(ulMotor == AMS_MOTOR_A)
	{
    	xGPIOSPinWrite(sD12,ulDir);
    	xGPIOSPinWrite(sD9,0);
    	xPWMStart(sPWMB_BASE, xPWM_CHANNEL0);

	}
	else if(ulMotor == AMS_MOTOR_B)
	{
    	xGPIOSPinWrite(sD13,ulDir);
    	xGPIOSPinWrite(sD8,0);
    	xPWMStart(sPWMA_BASE, xPWM_CHANNEL2);
	}

}

//*****************************************************************************
//
//! \brief Set the DC motor speed.
//!
//! \param ulMotor is the selected pwm channel.
//! \param ulDir is the selection of Motor rev direction.
//!
//! The \e ulMotor parameter can be one of the values:
//! \b AMS_MOTOR_A, \b AMS_MOTOR_B,
//!
//! The \e ulSpeed parameter can be values: Any values ,ulSpeed > 0 &&
//! ulSpeed < PWM module input clock.
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void
AMSDCMotorSpeedSet( unsigned long ulMotor, unsigned long ulSpeed)
{
    //
    // Check the arguments.
    //
    xASSERT((ulMotor == AMS_MOTOR_A) ||
	        (ulMotor == AMS_MOTOR_B));

    if(ulMotor == AMS_MOTOR_A)
    {
		//
		// Disable the pwm channel
		//
		xPWMStop(sPWMB_BASE, xPWM_CHANNEL0);

		//
		// Set the pwm frequency.
		//
		xPWMFrequencySet(sPWMB_BASE, xPWM_CHANNEL0, ulSpeed);

		//
		// Set the pwm duty as 50% .
		//
		xPWMDutySet(sPWMB_BASE, xPWM_CHANNEL0, 50);

		//
		// Enable the pwm channel
		//
		xPWMStart(sPWMB_BASE, xPWM_CHANNEL0);
    }
    else if(ulMotor == AMS_MOTOR_B)
    {
		//
		// Disable the pwm channel
		//
		xPWMStop(sPWMA_BASE, xPWM_CHANNEL2);

		//
		// Set the pwm frequency.
		//
		xPWMFrequencySet(sPWMA_BASE, xPWM_CHANNEL2, ulSpeed);

		//
		// Set the pwm duty as 50% .
		//
		xPWMDutySet(sPWMA_BASE, xPWM_CHANNEL2, 50);

		//
		// Enable the pwm channel
		//
		xPWMStart(sPWMA_BASE, xPWM_CHANNEL2);
    }

}

//*****************************************************************************
//
//! \brief Disable the corresponding pwm output channel to stop the DC motor.
//!
//! \param ulMotor is the selected pwm channel.
//!
//! The \e ulMotor parameter can be one of the values:
//! \b AMS_MOTOR_A, \b AMS_MOTOR_B,
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSDCMotorStop(unsigned long ulMotor)
{
    //
    // Check the arguments.
    //
    xASSERT((ulMotor == AMS_MOTOR_A) ||
	        (ulMotor == AMS_MOTOR_B));

	//
    // Set both motor pin to 0 to disable the motor
    //
    if(ulMotor == AMS_MOTOR_A)
	{
        //
		// Set both motor pin M4A to 0, M4B to 0;
		//
    	xPWMStop(sPWMB_BASE, xPWM_CHANNEL0);
    	xGPIOSPinWrite(sD9,1);

	}
	else if(ulMotor == AMS_MOTOR_B)
	{
		//
		// Set both motor pin M1A to 0, M1B to 0;
		//
		xPWMStop(sPWMA_BASE, xPWM_CHANNEL2);
		xGPIOSPinWrite(sD8,1);
	}
}

//*****************************************************************************
//
//! \brief Init the selected stepper number.
//!
//! \param ulStepperNum is the selection of Stepper number.
//!
//! The \e ulDir parameter can be one of the values:
//! \b MS_STEPPER_NUM1, \b MS_STEPPER_NUM2.
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSStepMotorInit(void)
{


	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD3));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD12));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD9));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD8));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD11));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(sD13));

	//
	// Set PC7(PWM2A), PE1(PWM2B) as output
	//
	xGPIOSPinTypeGPIOOutput(sD11);
	xGPIOSPinTypeGPIOOutput(sD3);
	xGPIOSPinTypeGPIOOutput(sD9);
	sD8PinTypeOUT();
	xGPIOSPinTypeGPIOOutput(sD12);
	xGPIOSPinTypeGPIOOutput(sD13);

}

//*****************************************************************************
//
//! \brief Set the step motor steps delay
//!
//! \param ulDelay is the steps delay ms.
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSStepsDelaySet(unsigned long ulDelay)
{
    g_ulStepsDelay = ulDelay;
}

//*****************************************************************************
//
//! \brief Control the 42BYGH step motor roll direction and speed. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulMotor is the channel of the Timer port.
//! \param ulDir is the selection of Step Motor running direction.
//! \param ulSteps is the motor rev step number.
//!
//! The \e ulDir parameter can be one of the values:
//! \b AMS_RUN_FORWARD, \b MS_RUN_BACKWARD.
//! 
//! \note The 42BYGH step motor is drivered by ladyada mshield IC1. The red wire
//!       connect to 1A(red <-> 1A), and (green <-> 2A), (yellow <-> 3A), 
//!       (blue <-> 4A). 
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSStepMotorRun(unsigned long ulDir, unsigned long ulSteps)
{
    unsigned long i;
    //
    // Check the arguments.
    //
    xASSERT((ulDir == AMS_RUN_FORWARD) ||
	        (ulDir == MS_RUN_BACKWARD));

	xGPIOSPinWrite(sD3,1);
	xGPIOSPinWrite(sD11,1);

    if(ulDir == AMS_RUN_FORWARD)
	{
		for(i = 0; i < ulSteps; i++)
		{
			xGPIOSPinWrite(sD12,((g_ul42BYGHForward[i%8] >> 3) & 0x1));
			xGPIOSPinWrite(sD9,((g_ul42BYGHForward[i%8] >> 2) & 0x1));
			xGPIOSPinWrite(sD13,((g_ul42BYGHForward[i%8] >> 1) & 0x1));
			xGPIOSPinWrite(sD8,((g_ul42BYGHForward[i%8]) & 0x1));
			AMSDelay(g_ulStepsDelay);
		}
	}
	else
	{
		for(i = 0; i < ulSteps; i++)
		{
			xGPIOSPinWrite(sD12,((g_ul42BYGHForward[i%8]) & 0x1));
			xGPIOSPinWrite(sD9,((g_ul42BYGHForward[i%8] >> 1) & 0x1));
			xGPIOSPinWrite(sD13,((g_ul42BYGHForward[i%8] >> 2) & 0x1));
			xGPIOSPinWrite(sD8,((g_ul42BYGHForward[i%8] >> 3) & 0x1));
			AMSDelay(g_ulStepsDelay);
		}
	}
}

//*****************************************************************************
//
//! \brief Stop the 42BYGH step motor. 
//!
//! \param None
//! 
//! \return None.
//
//*****************************************************************************
void 
AMSStepMotorStop(void)
{
	xGPIOSPinWrite(sD3,0);
	xGPIOSPinWrite(sD11,0);
}

//*****************************************************************************
//
//! \brief Init the ADC of the motor shield for current get.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void
AMSMotorADCInit(void)
{
	unsigned long ulBufferIn[2] = {10,11};
	//
	// Select the ADC clock source
	//
    xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, 3);

    //
    // Enable Peripheral ADC0
    //
    xSysCtlPeripheralEnable2(sADC_BASE);

    //
    // Configure Some GPIO pins as ADC Mode
    //
    sA0PinTypeADC();
    sA1PinTypeADC();

    //
    // Enable the ADC
    //
    xADCEnable(sADC_BASE);

    //
    // ADC Channel0 convert once, Software tirgger.
    //
    //xADCConfigure(sADC_BASE, xADC_MODE_SCAN_CONTINUOUS, ADC_TRIGGER_PROCESSOR);
    ADCRegularConfigure(sADC_BASE, ADC_OP_SCAN, ADC_TRIGGER_PROCESSOR);
    ADCRegularConfigure(sADC_BASE, ADC_OP_CONTINUOUS, ADC_TRIGGER_PROCESSOR);
    ADCAutoInjectedEnable(sADC_BASE);

    //
    // Enable the channel2/3
    //
    //xADCStepConfigure(sADC_BASE, 0, 2);
    ADCConverLenSet(sADC_BASE, 0, 2);
    ADCSequenceIndexSet(sADC_BASE, 0, ulBufferIn);
//    xADCStepConfigure(sADC_BASE, 1, xADC_CTL_CH3);

    //
    // ADC start Convert
    //
    xADCProcessorTrigger(sADC_BASE);
}

//*****************************************************************************
//
//! \brief Init the ADC of the motor shield for current get.
//!
//! \param ulMotor is the selected motor channel.
//!
//! \return The Current Sensing value unit is mA.
//
//*****************************************************************************
unsigned long
AMSMotorCurrentGet(unsigned long ulMotor)
{
	unsigned long ulCurrentADCData;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == AMS_MOTOR_A) ||
	        (ulBase == AMS_MOTOR_B));

    if(ulMotor == AMS_MOTOR_A)
	{
    	ulCurrentADCData = ADCDataInjectedGet(sADC_BASE, 1) & 0xFFF;

	}
	else if(ulMotor == AMS_MOTOR_B)
	{
		ulCurrentADCData = ADCDataInjectedGet(sADC_BASE, 2) & 0xFFF;
	}
    ulCurrentADCData = ulCurrentADCData *2000;
    ulCurrentADCData = ulCurrentADCData >> 12;
}

//*****************************************************************************
//
//! \brief Dalay some time.
//!
//! \param ulDelay is the delay number of ms. 
//!
//! \return None.
//
//*****************************************************************************
void 
AMSDelay(unsigned long ulDelay)
{

    xSysCtlPeripheralEnable2(MS_DELAY_TIMER);

	//
	// Clear the status first
	//
    TimerFlagStatusClear(MS_DELAY_TIMER, xTIMER_INT_MATCH);

    // 
    // Config as periodic mode
    //        
    xTimerInitConfig(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_MODE_PERIODIC, 1000);
    xTimerIntEnable(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH);
    xTimerStart(MS_DELAY_TIMER, MS_DELAY_CHANNEL);
	
    while(ulDelay)
	{
	    while(!xTimerStatusGet(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH)); 
	    TimerFlagStatusClear(MS_DELAY_TIMER, xTIMER_INT_MATCH);
		ulDelay--;
	}

	xTimerStop(MS_DELAY_TIMER, MS_DELAY_CHANNEL);
	xSysCtlPeripheralDisable2(MS_DELAY_TIMER);
	  
}





