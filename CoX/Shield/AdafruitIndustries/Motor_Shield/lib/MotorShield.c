//*****************************************************************************
//
//! \file MotorTest.c
//! \brief Driver for the Motor controller Test
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
#include "xhw_pwm.h"
#include "xpwm.h"
#include "xhw_timer.h"
#include "xtimer.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "MotorShield.h"

//
//! Step Motor 42BYGH403AA run forward pulse data in 8 pat
//
static unsigned long g_ul42BYGHForward[2][8] = {{0x02, 0x0a, 0x08, 0x0c, 0x04, 0x14, 0x10, 0x12}, 
                                                {0x01, 0x41, 0x40, 0x60,0x20, 0xa0, 0x80, 0x81}};

//
//! Step Motor 42BYGH403AA run reversal pulse data in 8 pat
//
static unsigned long g_ul42BYGHReversal[2][8] = {{0x12, 0x10, 0x14, 0x04, 0x0c, 0x08, 0x0a, 0x02},
                                                 {0x81, 0x80, 0xa0, 0x20, 0x60, 0x40, 0x41, 0x01}};

//
//! Step Motor stepper number
//
static unsigned long g_ul42BYGHStepper = MS_STEPPER_NUM1;

//
//! 74HC595 latch state
//
static unsigned long g_ul74HC595LatchState = 0;

//
//! Step motor steps delay
//
static unsigned long g_ulStepsDelay = 0;

//*****************************************************************************
//
//! \brief Init the PWM corresponding pins, and enable the corresponding port.
//!
//! \param ulBase is the selected PWM.
//! \param ulChannel is the selected pwm channel.
//!
//! The \e ulBase parameter can be one of the values:
//! \b sPWMA_BASE, \b sPWMB_BASE.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b MS_CHANNEL_PWM0A, \b MS_CHANNEL_PWM2A,
//! \b MS_CHANNEL_PWM0B, \b PWM_CHANNEL_PWM2B.
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void 
MSDCMotorPWMInit(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == sPWMA_BASE) || 
	        (ulBase == sPWMB_BASE));
    xASSERT((ulChannel == MS_CHANNEL_PWM0A) || 
			(ulChannel == MS_CHANNEL_PWM2A) ||
			(ulChannel == MS_CHANNEL_PWM0B) ||
			(ulChannel == MS_CHANNEL_PWM2B));

    MS74HC595PinInit();

    //
	// Enable the corresponding	port
	//
	switch(ulChannel)
	{
    	case MS_CHANNEL_PWM0A:
     	{
	        //
	    	// Enable the corresponding port and configure function pin
	    	//
	        xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD6));
		    sD6PinTypePWM();

			//
			// Set both motor pin to 0;
			//
			MS74HC595DataSend(g_ul74HC595LatchState & (~0xa0));
		    break;
	    }
    	case MS_CHANNEL_PWM2A:
	    {
	        //
		    // Enable the corresponding port and configure function pin
		    //
	        xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD11));
		    sD11PinTypePWM();

			//
			// Set both motor pin to 0;
			//
			MS74HC595DataSend(g_ul74HC595LatchState & (~0x0c));
		    break;
	    }
	    case MS_CHANNEL_PWM0B:
	    {
	        //
		    // Enable the corresponding port and configure function pin
		    //
	        xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD5));
		    sD5PinTypePWM();

			//
			// Set both motor pin to 0;
			//
			MS74HC595DataSend(g_ul74HC595LatchState & (~0x41));
	    	break;
	    }
	    case MS_CHANNEL_PWM2B:
	    {
	        //
		    // Enable the corresponding port and configure function pin
		    //
	        xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD3));
		    sD10PinTypePWM();

			//
			// Set both motor pin to 0;
			//
			MS74HC595DataSend(g_ul74HC595LatchState & (~0x12));
	    	break;
	    }
	    default:
	    break;
	}

	//
	// Enable the corresponding PWM
	//
	xSysCtlPeripheralEnable2(ulBase);  

	    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure(ulBase, ulChannel, xPWM_TOGGLE_MODE |
                                         xPWM_OUTPUT_INVERTER_DIS |
                                         xPWM_DEAD_ZONE_DIS);

    //
    // Set CNR, Prescale and Divider
    //
    xPWMFrequencyConfig(ulBase, ulChannel, 
	      xPWM_FREQ_CONFIG(MS_PWMDIV_VALUE, MS_PWMPSR_VALUE, MS_PWMCNT_VALUE));

    //
    // Set CMR
    //
    xPWMDutySet(ulBase, ulChannel, 50);

    //
    // Set output enable
    //
    xPWMOutputEnable(ulBase, ulChannel);

    //
    // start PWM
    //
    xPWMStart(ulBase, ulChannel);
}

//*****************************************************************************
//
//! \brief Configure the PWM frecqurecy and output duty cycle.
//!
//! \param ulChannel is the selected pwm channel.
//! \param ulDir is the selection of Motor rev direction.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b PWM_CHANNEL_PWM0A, \b PWM_CHANNEL_PWM2A,
//! \b PWM_CHANNEL_PWM0B, \b PWM_CHANNEL_PWM2B.
//!
//! The \e ulDir parameter can be one of the values:
//! \b MS_RUN_FORWARD, \b MS_RUN_BACKWARD.
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void 
MSDCMotorRun(unsigned long ulChannel, unsigned long ulDir)
{
    //
    // Check the arguments.
    //
    xASSERT((ulChannel == MS_CHANNEL_PWM0A) || 
			(ulChannel == MS_CHANNEL_PWM2A) ||
			(ulChannel == MS_CHANNEL_PWM0B) ||
			(ulChannel == MS_CHANNEL_PWM2B));
    xASSERT((ulDir == MS_RUN_FORWARD) || 
			(ulDir == MS_RUN_BACKWARD));

    if(ulChannel == MS_CHANNEL_PWM0A)
	{
	    if(ulDir == MS_RUN_FORWARD)
		{
			//
			// Set both motor pin M4A to 1, M4B to 0;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x20) & (~0x80));
		}
		else
		{
			//
			// Set both motor pin M4A to 0, M4B to 1;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x80) & (~0x20));
		}
	}
	else if(ulChannel == MS_CHANNEL_PWM2A)
	{
	    if(ulDir == MS_RUN_FORWARD)
		{
			//
			// Set both motor pin M1A to 1, M1B to 0;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x04) & (~0x08));
		}
		else
		{
			//
			// Set both motor pin M1A to 0, M1B to 1;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x08) & (~0x04));
		}
	}
	else if(ulChannel == MS_CHANNEL_PWM0B)
	{
	    if(ulDir == MS_RUN_FORWARD)
		{
			//
			// Set both motor pin M3A to 1, M3B to 0;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x01) & (~0x40));
		}
		else
		{
			//
			// Set both motor pin M3A to 0, M3B to 1;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x40) & (~0x01));
		}
	}
	else
	{
	    if(ulDir == MS_RUN_FORWARD)
		{
			//
			// Set both motor pin M2A to 1, M2B to 0;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x02) & (~0x10));
		}
		else
		{
			//
			// Set both motor pin M2A to 0, M2B to 1;
			//
			MS74HC595DataSend((g_ul74HC595LatchState | 0x10) & (~0x02));
		}    
	}

}

//*****************************************************************************
//
//! \brief Set the DC motor speed.
//!
//! \param ulBase is the selected PWM.
//! \param ulChannel is the selected pwm channel.
//! \param ulDir is the selection of Motor rev direction.
//!
//! The \e ulBase parameter can be one of the values:
//! \b sPWMA_BASE, \b sPWMB_BASE.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b PWM_CHANNEL_PWM0A, \b PWM_CHANNEL_PWM2A,
//! \b PWM_CHANNEL_PWM0B, \b PWM_CHANNEL_PWM2B.
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
MSDCMotorSpeedSet(unsigned long ulBase, unsigned long ulChannel, 
                                        unsigned long ulSpeed)
{
    //
    // Check the arguments.
    //
    xASSERT((ulChannel == MS_CHANNEL_PWM0A) || 
			(ulChannel == MS_CHANNEL_PWM2A) ||
			(ulChannel == MS_CHANNEL_PWM0B) ||
			(ulChannel == MS_CHANNEL_PWM2B));

	//
	// Disable the pwm channel
	//
	xPWMStop(ulBase, ulChannel);

	//
	// Set the pwm frequency.
	//
	xPWMFrequencySet(ulBase, ulChannel, ulSpeed);

	//
	// Set the pwm duty as 50% .
	//
	xPWMDutySet(ulBase, ulChannel, 50);

	//
	// Enable the pwm channel
	//
	xPWMStart(ulBase, ulChannel);

}

//*****************************************************************************
//
//! \brief Disable the corresponding pwm output channel to stop the DC motor.
//!
//! \param ulChannel is the selected pwm channel.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b MS_CHANNEL_PWM0A, \b MS_CHANNEL_PWM2A,
//! \b MS_CHANNEL_PWM0B, \b MS_CHANNEL_PWM2B.
//!
//! \note None.
//! 
//! \return None.
//
//*****************************************************************************
void 
MSDCMotorStop(unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulChannel == MS_CHANNEL_PWM0A) || 
			(ulChannel == MS_CHANNEL_PWM2A) ||
			(ulChannel == MS_CHANNEL_PWM0B) ||
			(ulChannel == MS_CHANNEL_PWM2B));

	//
    // Set both motor pin to 0 to disable the motor
    //
    if(ulChannel == MS_CHANNEL_PWM0A)
	{
        //
		// Set both motor pin M4A to 0, M4B to 0;
		//
		MS74HC595DataSend(g_ul74HC595LatchState & ~(0x80 | 0x20));
	}
	else if(ulChannel == MS_CHANNEL_PWM2A)
	{
		//
		// Set both motor pin M1A to 0, M1B to 0;
		//
		MS74HC595DataSend(g_ul74HC595LatchState & ~(0x08 | 0x04));
	}
	else if(ulChannel == MS_CHANNEL_PWM0B)
	{
		//
		// Set both motor pin M3A to 0, M3B to 0;
		//
		MS74HC595DataSend(g_ul74HC595LatchState & ~(0x01 | 0x40));
	}
	else
	{
		//
		// Set both motor pin M2A to 1, M2B to 0;
	    //
		MS74HC595DataSend(g_ul74HC595LatchState & ~(0x02 | 0x10)); 
	}
}

//*****************************************************************************
//
//! \brief Init the 74HC595 connected pin 
//!
//! \note The data will parral out.
//! 
//! \return None.
//
//*****************************************************************************
void 
MS74HC595PinInit(void)
{
    //
    // Set PE2(DIR_CLK), PD3(DIR_SER), and PA6(DIR_LATCH) PD2(DIR_EN) as output
    //
    xGPIOSPinTypeGPIOOutput(sD4);
    xGPIOSPinTypeGPIOOutput(sD8);
    xGPIOSPinTypeGPIOOutput(sD12);
    xGPIOSPinTypeGPIOOutput(sD7);

	//
	// Disable the output, data serial in and latch register.
	//
	xGPIOSPinWrite(sD7, 1);
	xGPIOSPinWrite(sD4, 1);
	xGPIOSPinWrite(sD12, 1);

}

//*****************************************************************************
//
//! \brief Write data to 74HCT595N. 
//!
//! \param ucData is the serial in data. 
//!
//! \note The data will parral out.
//! 
//! \return None.
//
//*****************************************************************************
void 
MS74HC595DataSend(unsigned char ucData)
{
    unsigned char i = 0;   	   

	//
	// 74HC595 operation Output Disable 
	//
	xGPIOSPinWrite(sD7, 1);	
	//
	// Serial data in
	//
	for(i = 0; i < 8; i++)
	{
        //ucData = (0xF7 & (1<<i)) >> i;
		if(ucData & 0x80)
		{
		    xGPIOSPinWrite(sD8, 1);

		}
		else
		{
		    xGPIOSPinWrite(sD8, 0);
		}
        ucData = ucData << 1;

        xGPIOSPinWrite(sD4, 0);
        xSysCtlDelay(1);
        xGPIOSPinWrite(sD4, 1);
	}

	//
    // Latch Data to 74HC595
    //
    xGPIOSPinWrite(sD12, 0);
    xSysCtlDelay(1);
    xGPIOSPinWrite(sD12, 1);
	
    // 
    // 74HC595 operation Output Enable
    //
    xGPIOSPinWrite(sD7, 0);	   
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
MSStepMotorInit(unsigned long ulStepperNum)
{
    //
    // Check the arguments.
    //
    xASSERT((ulStepperNum == MS_STEPPER_NUM1) || 
	        (ulStepperNum == MS_STEPPER_NUM2));

    if(ulStepperNum == MS_STEPPER_NUM1)
	{
		xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD11));
	    xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD3));

        //
        // Set PC7(PWM2A), PE1(PWM2B) as output
        //
	    xGPIOSPinTypeGPIOOutput(sD11);
        xGPIOSPinTypeGPIOOutput(sD3);  

	    //
	    // Always enable the L293D(IC1) 1-2EN, 3-4EN
    	//
    	xGPIOSPinWrite(sD11, 1);
        xGPIOSPinWrite(sD3, 1);
	}
	else
	{
		xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD5));
	    xSysCtlPeripheralEnable2(xGPIOSPinToPeripheralId(sD6));

        //
        // Set sD5(PWM0A), SD6(PWM0B) as output
        //
	    xGPIOSPinTypeGPIOOutput(sD5);
        xGPIOSPinTypeGPIOOutput(sD6);  

	    //
	    // Always enable the L293D(IC2) 1-2EN, 3-4EN
    	//
    	xGPIOSPinWrite(sD5, 1);
        xGPIOSPinWrite(sD6, 1);	  
	    
	}
	g_ul42BYGHStepper = ulStepperNum;

	MS74HC595PinInit();
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
MSStepsDelaySet(unsigned long ulDelay)
{
    g_ulStepsDelay = ulDelay;
}

//*****************************************************************************
//
//! \brief Control the 42BYGH step motor roll direction and speed. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulDir is the selection of Step Motor running direction.
//! \param ulSteps is the motor rev step number.
//!
//! The \e ulDir parameter can be one of the values:
//! \b MS_RUN_FORWARD, \b MS_RUN_BACKWARD.
//! 
//! \note The 42BYGH step motor is drivered by ladyada mshield IC1. The red wire
//!       connect to 1A(red <-> 1A), and (green <-> 2A), (yellow <-> 3A), 
//!       (blue <-> 4A). 
//! 
//! \return None.
//
//*****************************************************************************
void 
MSStepMotorRun(unsigned long ulDir, unsigned long ulSteps)
{
    unsigned long i, j;
    //
    // Check the arguments.
    //
    xASSERT((ulDir == MS_RUN_FORWARD) || 
	        (ulDir == MS_RUN_BACKWARD));

    if(ulDir == MS_RUN_FORWARD)
	{
	    for(j = 0; j < ulSteps; j++)
		{
	        for(i = 0; i < 8; i++)
		    {
		        MS74HC595DataSend(g_ul42BYGHForward[g_ul42BYGHStepper][i]);
			    MSDelay(g_ulStepsDelay);
		    }
		}
	}
	else
	{
	    for(j = 0; j < ulSteps; j++)
		{
	        for(i = 0; i < 8; i++)
		    {
		        MS74HC595DataSend(g_ul42BYGHReversal[g_ul42BYGHStepper][i]);
			    MSDelay(g_ulStepsDelay);
		    }
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
MSStepMotorStop(void)
{
    MS74HC595DataSend(0x00);
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
MSDelay(unsigned long ulDelay)
{
    //
    // Set the timer clock
    //
    xSysCtlPeripheralClockSourceSet(MS_DELAY_CLKSRC, 1);

    xSysCtlPeripheralEnable2(MS_DELAY_TIMER);

	//
	// Clear the status first
	//
	xTIMERStatueClear(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH); 

    // 
    // Config as periodic mode
    //        
    xTimerInitConfig(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_MODE_PERIODIC, 1000);
    xTimerIntEnable(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH);
    xTimerStart(MS_DELAY_TIMER, MS_DELAY_CHANNEL);
	
    while(ulDelay)
	{
	    while(!xTimerStatusGet(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH)); 
		xTIMERStatueClear(MS_DELAY_TIMER, MS_DELAY_CHANNEL, xTIMER_INT_MATCH); 
		ulDelay--;
	}

	xTimerStop(MS_DELAY_TIMER, MS_DELAY_CHANNEL);
	xSysCtlPeripheralDisable2(MS_DELAY_TIMER);
	  
}





