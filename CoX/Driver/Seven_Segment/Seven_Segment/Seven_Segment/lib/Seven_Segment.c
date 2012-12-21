//*****************************************************************************
//
//! \file Seven_Segment.C
//! \brief seven segment digital tubes Driver.
//! \version V2.1.1.0
//! \date 7/16/2012
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "seven_segment.h"

const unsigned long GPIO_LED_PIN[LEDn] = {LED_A_GPIO_PIN, LED_B_GPIO_PIN,                                
                                          LED_C_GPIO_PIN, LED_D_GPIO_PIN,
	                                  LED_E_GPIO_PIN, LED_F_GPIO_PIN,
	                                  LED_G_GPIO_PIN, LED_DP_GPIO_PIN};
const unsigned long GPIO_LED_PORT[LEDn] = {LED_A_GPIO_PORT, LED_B_GPIO_PORT,
					   LED_C_GPIO_PORT, LED_D_GPIO_PORT,
					   LED_E_GPIO_PORT, LED_F_GPIO_PORT,
					   LED_G_GPIO_PORT, LED_DP_GPIO_PORT};
const unsigned long GPIO_SEL_PIN[CHIP_SEL_NUM]={CHIP_SEL_1_GPIO_PIN,
                                                CHIP_SEL_2_GPIO_PIN,
						CHIP_SEL_3_GPIO_PIN,
						CHIP_SEL_4_GPIO_PIN};
const unsigned long GPIO_SEL_PORT[CHIP_SEL_NUM] = {CHIP_SEL_1_GPIO_PORT,
                                                   CHIP_SEL_2_GPIO_PORT,
						   CHIP_SEL_3_GPIO_PORT,
						   CHIP_SEL_4_GPIO_PORT};
//*****************************************************************************
//
//! \brief Initialize seven segment digital tubes.
//!
//! \param None
//!
//! This function initialize the seven segment digital tubes.
//! 
//! \return None.
//
//*****************************************************************************
void SevenSegmentInit (void)
{
    unsigned long ulI;
    for(ulI = 0; ulI < LEDn; ulI++)
    {
       xSysCtlPeripheralEnable2(GPIO_LED_PORT[ulI]);
       xGPIODirModeSet(GPIO_LED_PORT[ulI], 
                       GPIO_LED_PIN[ulI], 
                       GPIO_DIR_MODE_OUT);
    }
    
      for(ulI = 0; ulI < CHIP_SEL_NUM; ulI++)
    {
       xSysCtlPeripheralEnable2(GPIO_SEL_PORT[ulI]);
       xGPIODirModeSet(GPIO_SEL_PORT[ulI], 
                       GPIO_SEL_PIN[ulI], 
                       GPIO_DIR_MODE_OUT);
    }
    SevenLEDOff();
}

//*****************************************************************************
//
//! \brief Close the seven segment digital tubes.
//!
//! \param None
//!
//! This function is to close seven segment digital tubes.
//! 
//! \return None.
//
//*****************************************************************************
void SevenSegmentClear ()
{
    xGPIOPinWrite(GPIO_SEL_PORT[0], GPIO_SEL_PIN[0], 1);
    xGPIOPinWrite(GPIO_SEL_PORT[1], GPIO_SEL_PIN[1], 1);
    xGPIOPinWrite(GPIO_SEL_PORT[2], GPIO_SEL_PIN[2], 1);
    xGPIOPinWrite(GPIO_SEL_PORT[3], GPIO_SEL_PIN[3], 1);
}

//*****************************************************************************
//
//! \brief Turn the selected LED off.
//!
//! \param None
//!
//! This function is to Turn the slected LED off.
//! 
//! \return None.
//
//*****************************************************************************
void SevenLEDOff(void)
{
    xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 1);
    xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 1);
    xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 1);
    xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 1);
    xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
    xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
    xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 1);
    xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1); 
}

//*****************************************************************************
//
//! \brief Select the LED chip.
//!
//! \param usLED specifies the LED to be configured.
//!
//! This function is select the LED chip to configure.
//! 
//! \return None.
//
//*****************************************************************************
void LEDChipSel(unsigned short usLED)
{
    switch (usLED)
    {
      case LED_ONE:
        xGPIOPinWrite(GPIO_SEL_PORT[0], GPIO_SEL_PIN[0], 0);
        xGPIOPinWrite(GPIO_SEL_PORT[1], GPIO_SEL_PIN[1], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[2], GPIO_SEL_PIN[2], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[3], GPIO_SEL_PIN[3], 1);
	    break;

      case LED_TWO:
        xGPIOPinWrite(GPIO_SEL_PORT[0], GPIO_SEL_PIN[0], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[1], GPIO_SEL_PIN[1], 0);
        xGPIOPinWrite(GPIO_SEL_PORT[2], GPIO_SEL_PIN[2], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[3], GPIO_SEL_PIN[3], 1);
	    break;

      case LED_THREE:
        xGPIOPinWrite(GPIO_SEL_PORT[0], GPIO_SEL_PIN[0], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[1], GPIO_SEL_PIN[1], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[2], GPIO_SEL_PIN[2], 0);
        xGPIOPinWrite(GPIO_SEL_PORT[3], GPIO_SEL_PIN[3], 1);
	    break;

      case LED_FOUR:
        xGPIOPinWrite(GPIO_SEL_PORT[0], GPIO_SEL_PIN[0], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[1], GPIO_SEL_PIN[1], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[2], GPIO_SEL_PIN[2], 1);
        xGPIOPinWrite(GPIO_SEL_PORT[3], GPIO_SEL_PIN[3], 0);
	    break;

      case LED_ALL:
        xGPIOPinWrite(GPIO_SEL_PORT[0], GPIO_SEL_PIN[0], 0);
        xGPIOPinWrite(GPIO_SEL_PORT[1], GPIO_SEL_PIN[1], 0);
        xGPIOPinWrite(GPIO_SEL_PORT[2], GPIO_SEL_PIN[2], 0);
        xGPIOPinWrite(GPIO_SEL_PORT[3], GPIO_SEL_PIN[3], 0);
	    break;  

      default:
            break; 
    }	

    //
    // LED is off by default after chip select.
    //
    SevenLEDOff(); 
}

//*****************************************************************************
//
//! \brief Show the number on the Seven_Segment.
//!
//! \param usLED specifies the LED to be configured.
//! \param ucData the number to be showed.
//!
//! This function is to show a number.
//! 
//! \return the result.
//
//*****************************************************************************
xtBoolean SevenSegmentShow (unsigned short usLED, unsigned char ucData)
{
    SevenSegmentClear();
    LEDChipSel(usLED);

    switch (ucData)
    {
      case 0:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 1);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 1:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 1);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 1);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 1);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 2:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 1);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 3:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;
    
      case 4:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 1);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 1);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;
	
      case 5:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 1);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 6:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 1);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
             break;

      case 7:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 1);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 1);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 8:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 9:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 1);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 0xa:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 0xb:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 1);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 1);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 0xc:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 1);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 1);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 1);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 0xd:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 1);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 0);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 1);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 0xe:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 0);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 1);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 0);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      case 0xf:
        xGPIOPinWrite(GPIO_LED_PORT[0], GPIO_LED_PIN[0], 0);
        xGPIOPinWrite(GPIO_LED_PORT[1], GPIO_LED_PIN[1], 1);
        xGPIOPinWrite(GPIO_LED_PORT[2], GPIO_LED_PIN[2], 1);
        xGPIOPinWrite(GPIO_LED_PORT[3], GPIO_LED_PIN[3], 1);
        xGPIOPinWrite(GPIO_LED_PORT[4], GPIO_LED_PIN[4], 0);
        xGPIOPinWrite(GPIO_LED_PORT[5], GPIO_LED_PIN[5], 0);
        xGPIOPinWrite(GPIO_LED_PORT[6], GPIO_LED_PIN[6], 0);
        xGPIOPinWrite(GPIO_LED_PORT[7], GPIO_LED_PIN[7], 1);
            break;

      default:
            return xfalse;
    }
    return xtrue;
}

//*****************************************************************************
//
//! \brief display data on the Seven_Segment.
//!
//! \param usData The data need to display.
//! \param ucForm the data's form(decimal or hexadecimal ).
//!
//! This function is to display data on LED seven segment digital tubes.
//! 
//! \return the result.
//
//*****************************************************************************
xtBoolean SevenSegmentScan(unsigned long ulData, unsigned char ucForm)
{
    unsigned char ucUnits,ucTens,ucHundreds,ucThousands;

    if(ucForm == DECIMAL)
    {
      if(ulData > 9999) return xfalse;

      ucThousands = ulData/1000;
      ucHundreds  = (ulData%1000)/100;
      ucTens      = (ulData%100)/10;
      ucUnits     = (ulData%10);


      SevenSegmentShow(LED_ONE,ucUnits);
      xSysCtlDelay(72000);

      SevenSegmentShow(LED_TWO,ucTens);
      xSysCtlDelay(72000);

      SevenSegmentShow(LED_THREE,ucHundreds);
      xSysCtlDelay(72000);

      SevenSegmentShow(LED_FOUR,ucThousands);
      xSysCtlDelay(72000);

    }

    else if(ucForm == HEXADECIMAL)
    {
      if(ulData > 0xFFFF) return xfalse;

      ucThousands = (ulData >> 12)& 0x0F;
      ucHundreds  = (ulData >> 8 )& 0x0F;
      ucTens      = (ulData >> 4) & 0x0F;
      ucUnits     =  ulData       & 0x0F;


      SevenSegmentShow(LED_ONE,ucUnits);
      xSysCtlDelay(72000);

      SevenSegmentShow(LED_TWO,ucTens);
      xSysCtlDelay(72000);

      SevenSegmentShow(LED_THREE,ucHundreds);
      xSysCtlDelay(72000);

      SevenSegmentShow(LED_FOUR,ucThousands);
      xSysCtlDelay(72000);

    }
    else
      return xfalse;

    return xtrue;
}
