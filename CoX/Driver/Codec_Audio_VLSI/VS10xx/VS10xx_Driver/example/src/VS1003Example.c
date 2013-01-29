//*****************************************************************************
//
//! \file VS1003Example.c
//! \brief VS1003 example source code
//! \version V1.0.0
//! \date 1/23/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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
#include "xhw_nvic.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "stdio.h"
#include "Joystick.h"
#include "VS1003Example.h"
#include "VS10xx.h"
#include "hw_CH376INC.h"
#include "CH376.h"
#include "CH376_FS.h"

unsigned char ucBuff[512];
unsigned char ucKeySelFlag = 0;
const unsigned char ucVolumeLevel[10] = { 0, 0x80, 0x98, 0xA8, 0xB1, 0xBE, 0xC8, 0xD0, 0xDF, 0xFE };
static unsigned char sucVolLevel = 3;
static short ssVolBalance = 0, ssTrebleA = 0, ssBassA = 0;

//*****************************************************************************
//
//! \brief Peripheral Initialization.
//!
//! \param None.
//!
//! This function is to Initialize joystick, LED, USART1, CH376, USB flash disk and VS1003.
//!
//! \return None.
//
//*****************************************************************************
void PeriphInit()
{
	unsigned char s;
	JoystickInit();
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(LED_PIN));
	xGPIOSPinDirModeSet(LED_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinWrite( LED_PIN, 0 );
	mInitSTDIO( );
	s = mInitCH376Host( );
	mStopIfError( s );
	while ( CH376DiskConnect( ) != USB_INT_SUCCESS )
	{
		xSysCtlDelay( 1000000 );
		printf("Waiting for USB flash disk to plug in...\n\r");
	}
	xSysCtlDelay( 2000000 );
	for ( s = 0; s < 10; s ++ )
	{
		xSysCtlDelay( 500000 );
	    if ( CH376DiskMount( ) == USB_INT_SUCCESS ) break;
	}
	VS10xxInit();
}

//*****************************************************************************
//
//! \brief VS1003 Example.
//!
//! \param None.
//!
//! This function is to give an example of using VS10xx to play audio file.
//! we use VS1003 as the decoder. This chip can decode WAV,MP3,WMA,MIDI audio
//! files and also can record audio. But we don't give out the record functions
//! since it relates much to file manipulation and seldom used. If you need this
//! function, please refer to VS10xx datasheet on VLSI's official page.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxExample(void)
{
	unsigned char i,s;
	unsigned short usDataCnt, usAudioDecTime = 0;
	unsigned int ulFileSize = 0, ulFileCursor = 0;
	AudioFileInfo tFLIF;
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay( 1000000 );
    PeriphInit();
    VS10xxSineTest(0x24, 5000000);
    VS10xxSineTest(0x85, 5000000);
    //
    // Open MP3 file
    //
    s = CH376FileOpen("/01.MP3");
    mStopIfError(s);
    //
    // Set start volume, balance and Bass Treble Enhancement
    //
    VS10xxSetVolume( 77 );
    VS10xxSetBalance( 0 );
    VS10xxBassTrebleEnhance(0, 12, 0, 10);
    //
    // Get file size. (Optional)
    //
    ulFileSize = CH376GetFileSize( );
    //
    // Single song loop
    //
    while( 1 )
    {
    	CH376ByteRead( ucBuff, 512, &usDataCnt );
    	//
    	// Send audio stream to VS1003
    	//
    	for(i=0;i<16;i++)
    	{
    		VS10xxWriteData( ucBuff + i*32 );
    	}
    	ulFileCursor += usDataCnt;
    	if(ulFileCursor == 4096)
    	{
    		//
    		// Get and print file information
    		//
    		VS10xxGetAudioInfo(&tFLIF);
    		printf("\n\rFile type: %d\n\rBit rate: %d kbps\n\rSample rate: %dHz",
    				tFLIF.eFileType, tFLIF.usBitRate, tFLIF.ucSampleRate);
    		printf("\n\rMP3 ID: %d\n\rMP3 layer: %d\n\rOther information: %x\n\r",
    				tFLIF.ucMp3ID, tFLIF.ucMp3Layer, tFLIF.ucOtherInfo);
    	}
    	if((ulFileCursor % 10240) == 0)
    	{
    		//
    		// Get and print decode time
    		//
    		usAudioDecTime = VS10xxGetDecodeTime();
    		printf("\rplayed time: %2d:%2ds", usAudioDecTime/60, usAudioDecTime%60);
    	}
    	//
    	// If file come to the end.
    	//
    	if( usDataCnt==0 )
    	{
    		ulFileCursor=0;
    		//
    		// Move file pointer to the beginning of the file
    		//
    		CH376ByteLocate( 0 );
    		//
    		// Reset decode time
    		//
    		VS10xxResetDecodeTime();
    	}
    	//
    	// Key scan
    	//
    	switch(JoystickKeyRead())
    	{
    		case JOYSTICK_KEY_SELECT:
    			ucKeySelFlag = !ucKeySelFlag;
    			if(ucKeySelFlag) xGPIOSPinWrite( LED_PIN, 1 );
    			else xGPIOSPinWrite( LED_PIN, 0 );
    			break;
    		case JOYSTICK_KEY_UP:
    			if(!ucKeySelFlag)
    			{
    				//
    				// Volume increase
    				//
    				if(sucVolLevel<9)
    					sucVolLevel++;
    				VS10xxSetVolume(ucVolumeLevel[sucVolLevel]);
    			}
    			else
    			{
    				//
    				// Treble increase
    				//
    				if(ssTrebleA < 7) ssTrebleA++;
    				VS10xxBassTrebleEnhance(ssTrebleA, 12, ssBassA, 10);
    			}
    			break;
    		case JOYSTICK_KEY_DOWN:
    			if(!ucKeySelFlag)
    			{
    				//
    				// Volume decrease
    				//
    				if(sucVolLevel!=0)
    					sucVolLevel--;
    				VS10xxSetVolume(ucVolumeLevel[sucVolLevel]);
    			}
    			else
    			{
    				//
    				// Treble decrease
    				//
    				if(ssTrebleA > -8)
    					ssTrebleA--;
    				VS10xxBassTrebleEnhance(ssTrebleA, 12, ssBassA, 10);
    			}
    			break;
    		case JOYSTICK_KEY_LEFT:
    			if(!ucKeySelFlag)
    			{
    				//
    				// Balance decrease
    				//
    				if(ssVolBalance>-254)
    					ssVolBalance--;
    				VS10xxSetBalance(ssVolBalance);
    			}
    			else
    			{
    				//
    				// bass decrease
    				//
    				if(ssBassA>0)
    					ssBassA--;
    				VS10xxBassTrebleEnhance(ssTrebleA, 12, ssBassA, 10);
    			}
    			break;
    		case JOYSTICK_KEY_RIGHT:
    			if(!ucKeySelFlag)
    			{
    				//
    				// balance increase
    				//
    				if(ssVolBalance<254) ssVolBalance++;
    				VS10xxSetBalance(ssVolBalance);
    			}
    			else
    			{
    				//
    				// Bass increase
    				//
    				if(ssBassA<15)
    				     ssBassA++;
    				VS10xxBassTrebleEnhance(ssTrebleA, 12, ssBassA, 10);
    			}
    			break;
    		default :
    			break;
    	}
    }
//    CH376FileClose(FALSE);
}
