//*****************************************************************************
//
//! \file LCDKeypad.c
//! \brief Driver for Character LCD Keypad.
//! \version 2.1.1.0
//! \date 10/18/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xadc.h"
#include "coshining.h"
#include "LCDShield.h"

//*****************************************************************************
//
//! \brief Init the HD44780 LCD Keypad.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
KeypadButtonInit(void)
{
    //
    // Enable Peripheral ADC
    //
     xSysCtlPeripheralEnable(xSYSCTL_PERIPH_ADC0);
	
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
    xADCProcessorTrigger(xADC0_BASE);

}

//*****************************************************************************
//
//! \brief Get the button value of LCD Keypad
//!
//! \param None
//!
//! \return The button value of LCD Keypad.
//
//*****************************************************************************
int
KeypadButtonGet(void)
{
    unsigned long ulADCValue[5] = {0x100, 0x300, 0x500, 0x800, 0xB00};
    int k;
    unsigned long ulValueLength, ulData[8]; 
    
    ulValueLength = xADCDataGet(xADC0_BASE, ulData);
    ulData[0] = ulData[0] & 0xFFF;
    for (k = 0; k < 5; k++)
    {
        if (ulData[0] < ulADCValue[k])
        {
            return k;
        }
    }
		
		//
		// No valid key pressed
		//
    if (k >= 5)
    {
        k = -1;  
    }			
    return k;
    
}