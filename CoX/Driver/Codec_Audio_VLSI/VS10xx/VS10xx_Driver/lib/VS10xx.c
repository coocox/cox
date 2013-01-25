//*****************************************************************************
//
//! \file VS10xx.c
//! \brief basic driver source code for VS10xx
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
#include "xhw_gpio.h"
#include "xhw_spi.h"
#include "xgpio.h"
#include "xuart.h"
#include "xspi.h"
#include "hw_VS10xx.h"
#include "VS10xx.h"


//*****************************************************************************
//
//! \brief Macro of control lines operation.
//
//*****************************************************************************
#define VS10xx_XCS_SET          xGPIOSPinWrite(VS10xx_XCS_PIN,1)
#define VS10xx_XCS_CLR          xGPIOSPinWrite(VS10xx_XCS_PIN,0)
#define VS10xx_RST_SET          xGPIOSPinWrite(VS10xx_RST_PIN,1)
#define VS10xx_RST_CLR          xGPIOSPinWrite(VS10xx_RST_PIN,0)
#define VS10xx_XDCS_SET         xGPIOSPinWrite(VS10xx_XDCS_PIN,1)
#define VS10xx_XDCS_CLR         xGPIOSPinWrite(VS10xx_XDCS_PIN,0)
#define VS10xx_DREQ_READ()      xGPIOSPinRead(VS10xx_DREQ_PIN)
static unsigned long ulSysClk;
//*****************************************************************************
//
//! \brief Dedicated delay for VS10xx.
//!
//! \param t specify delay time.
//!
//! This function is to delay approximately t us.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxDelayus(unsigned long t)
{
    t=ulSysClk/6000000*t;
    xSysCtlDelay(t);
}

//*****************************************************************************
//
//! \brief Change SPI clock frequency.
//!
//! \param ulSpeedLevel SPI clock frequency.
//!
//! \return None.
//
//*****************************************************************************
void SpiClkFreqSet(unsigned long ulSpeedLevel)
{
    xSPIDisable(VS10xx_SPI_PORT);
    xSPIConfigSet(VS10xx_SPI_PORT, ulSpeedLevel,
    	    xSPI_MOTO_FORMAT_MODE_3 |
            xSPI_MODE_MASTER |
            xSPI_MSB_FIRST |
            xSPI_DATA_WIDTH8);
    xSPIEnable(VS10xx_SPI_PORT);
}

//*****************************************************************************
//
//! \brief Get VS10xx busy status.
//!
//! \param None
//!
//! \return 1 means busy, 0 means idle.
//
//*****************************************************************************
unsigned char VS10xxBusy(void)
{
	return( VS10xx_DREQ_READ()? 0 : 1 );
}

//*****************************************************************************
//
//! \brief Write data to VS10xx's 32 bytes data buffer.
//!
//! \param ucAddr register address.
//! \param usData register value.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxWriteCmd(unsigned char ucAddr, unsigned short usValue)
{
    while(VS10xxBusy());
    //
    // Set clock to low speed to ensure correct data transfer
    //
    SpiClkFreqSet( VS10xx_SPI_CLK_SLOW );

    VS10xx_XCS_CLR;
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, VS10XX_WRITE_CMD);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, ucAddr);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, usValue >> 8);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, (unsigned char)usValue);
    VS10xx_XCS_SET;
}

//*****************************************************************************
//
//! \brief Write data to VS10xx's 32 bytes data buffer.
//!
//! \param pucBuffer The source buffer of data to be written into VS10xx.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxWriteData(unsigned char *pucBuffer)
{
    //
    // set to a higher clock speed to send data fast
    // the clock shouldn't be too fast or VS10xx can't work properly
    //
    SpiClkFreqSet(VS10xx_SPI_CLK_FAST);

    while(VS10xxBusy());
    VS10xx_XDCS_CLR;
    xSPIDataWrite(VS10xx_SPI_PORT, pucBuffer, 32);
    VS10xx_XDCS_SET;
}

//*****************************************************************************
//
//! \brief Read VS10xx register value.
//!
//! \param ucAddr specifies the register address.
//!
//! \return 16 bit Value of the specified register.
//
//*****************************************************************************
unsigned short VS10xxReadReg(unsigned char ucAddr)
{

    unsigned short usTemp = 0;

    while(VS10xxBusy());
    //
    // Set clock to low speed to ensure correct data transfer
    //
    SpiClkFreqSet(VS10xx_SPI_CLK_SLOW);

    VS10xx_XCS_CLR;
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, VS10XX_READ_CMD);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, ucAddr);
    //
    // Read high 8bit
    //
    usTemp = xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0xff);
    usTemp = usTemp << 8;
    //
    // Read low 8bit
    //
    usTemp |= xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0xff);
    VS10xx_XCS_SET;
    return usTemp;
}

void VS10xxPreConfig(void)
{
    unsigned char ucRetry = 0;
    //
    // set the clock configuration register
    // SC_MULT = 3, CLKI = 3 * XTALI
    // SC_ADD = 3, Multiplier addition = 1.5¡Á
    // SC_FREQ = 0, XTALI is running at 12.288MHz
    //
    do{
        VS10xxWriteCmd(SCI_CLOCKF, 0X9800);
        VS10xxDelayus(2000);
        if(ucRetry++ > 100)break;
    }while(VS10xxReadReg(SCI_CLOCKF) != 0X9800);

    ucRetry = 0;
    //
    // Set the sample rate and channel register(optional)
    // 48kHz, 2 channel stereo
    //
    do{
        VS10xxWriteCmd(SCI_AUDATA, 0XBB81);
        VS10xxDelayus(2000);
        if(ucRetry++ > 100)break;
    }while(VS10xxReadReg(SCI_AUDATA) != 0XBB81);
    //
    // Set default volume
    //
    VS10xxWriteCmd(SCI_VOL, 0x4141);
    VS10xxResetDecodeTime();
    VS10xxDelayus(20000);
}
//*****************************************************************************
//
//! \brief VS10xx soft reset.
//!
//! \param None.
//!
//! This function is to soft rest VS10xx and initialize it.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxSoftReset(void)
{
    unsigned char ucRetry = 0;

    while(VS10xxBusy());
    //
    // software reset, new mode
    //
    while(VS10xxReadReg(SCI_MODE) != 0x0804)
    {
        VS10xxWriteCmd(SCI_MODE, 0x0804);
        VS10xxDelayus(2000);
        if(ucRetry++ > 100)break;
    }

    while(VS10xxBusy());

    VS10xxPreConfig();
}

//*****************************************************************************
//
//! \brief VS10xx hard reset.
//!
//! \param None.
//!
//! This function is to hard rest VS10xx and initialize it.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxHardReset(void)
{
    VS10xx_RST_CLR;
    VS10xxDelayus(10000);
    VS10xx_RST_SET;
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0XFF);
    VS10xx_XDCS_SET;
    VS10xx_XCS_SET;
    while(VS10xxBusy());
    VS10xxDelayus(50000);
    VS10xxPreConfig();
}

static short g_sVolumeBalance = 0;

//*****************************************************************************
//
//! \brief VS10xx set volume.
//!
//! \param ucVol volume value, vary from 0(mute) to 254(full volume).
//!
//! This function is to set output sound volume of Vs10xx.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxSetVolume(unsigned char ucVol)
{
    unsigned short usTmp = 0;
    short sVol, sVolLeft, sVolRight;

    sVol=(unsigned short)ucVol;
    sVolLeft = sVolRight = sVol;
    sVolLeft -= g_sVolumeBalance;
    sVolRight += g_sVolumeBalance;

    if(sVolLeft < 0) sVolLeft = 0;
    if(sVolLeft > 0x00FE) sVolLeft = 0x00FE;

    if(sVolRight < 0) sVolRight = 0;
    if(sVolRight > 0x00FE) sVolRight = 0x00FE;

    sVolLeft = 254 - sVolLeft;
    sVolRight = 254 - sVolRight;

    usTmp = (unsigned short)sVolRight + ( ( (unsigned short)sVolLeft ) << 8);
    VS10xxWriteCmd(SCI_VOL, usTmp);
}

//*****************************************************************************
//
//! \brief VS10xx set volume directly.
//!
//! \param usVol specifies volume value which will be write to SCI_VOL register directly.
//!
//! This function is to set volume to register directly.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxSetVolume2(unsigned short usVol)
{
	VS10xxWriteCmd(SCI_VOL, usVol);
}

//*****************************************************************************
//
//! \brief VS10xx get volume.
//!
//! \param None
//!
//! This function is to get volume of Vs10xx. The higher 8 bits are the left channel
//! volume and the lower 8 bits are the right channel volume.
//!
//! \return volume value of two channel.
//
//*****************************************************************************
unsigned short VS10xxGetVolume( void )
{
	return (VS10xxReadReg( SCI_VOL ));
}

//*****************************************************************************
//
//! \brief VS10xx set volume balance.
//!
//! \param ucVol volume value, vary from 0(mute) to 254a(full volume).
//!
//! This function is to set volume balance of the two audio output channel.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxSetBalance(short sVolBalance)
{
    unsigned short usVolumeRD;
    unsigned short sVolumeTmp;

    //
    // change balance value
    //
    g_sVolumeBalance = sVolBalance;
    //
    // get original volume
    //
    usVolumeRD = VS10xxReadReg( SCI_VOL );
    //
    // calculate the average volume of the two channel
    //
    sVolumeTmp = ((usVolumeRD >> 8) + (usVolumeRD & 0x00FF)) >> 1;
    //
    // set volume
    //
    VS10xxSetVolume( sVolumeTmp );
}

//*****************************************************************************
//
//! \brief VS10xx set bass treble enhancement.
//!
//! \param sTrebleAmplitude specify treble gain, vary from -8 to 7(-12dB to 10.5dB step by 1.5dB).
//! \param usTrebleLimit specify the Lower threshold frequency of treble gain.
//! \param usBassAmplitude specify bass gain, vary from 0 to 15(0dB to 15dB step by 1dB).
//! \param usBassLimit specify the Lower threshold frequency of bass gain.
//!
//! This function is to set bass treble enhancement.
//! \e usTrebleLimit can be 0,1,2...15 specify the Lower threshold frequency of treble gain to 0kHz to 15kHz
//! \e usBassLimit can be 2,3,4...15 specify the Lower threshold frequency of bass gain to 20Hz to 150Hz
//!
//! \return None.
//
//*****************************************************************************
void VS10xxBassTrebleEnhance(short sTrebleAmplitude, unsigned short usTrebleLimit,
                             unsigned short usBassAmplitude, unsigned short usBassLimit)
{
    unsigned short usRegTmp;

    usRegTmp = VS10xxReadReg(SCI_BASS);
    if((sTrebleAmplitude>-9) && (sTrebleAmplitude<8) && (usTrebleLimit<16)
        && (usBassAmplitude < 15) && (usBassLimit<15) && (usBassLimit>2))
    {
         usRegTmp = (((unsigned short)(sTrebleAmplitude + 8)) << 12)
                     | (usTrebleLimit << 8)
                     | (usBassAmplitude << 4)
                     | usBassLimit;
         VS10xxWriteCmd(SCI_BASS, usRegTmp);
    }
}

//*****************************************************************************
//
//! \brief VS10xx Sine Test.
//!
//! \param ucFreq specify the frequency of sine wave.
//! \param ulTestTime specifies how long the test lasts. If ulTestTime==0 the test will not stop.
//!
//! This function is to do sine test to ensure the chip works normally.
//! ucFreq specify the frequency of sine wave. Bit 7:5 specifies the Fs sample rate
//! Bit7:5    Fs
//!   0       44100Hz
//!   1       48000Hz
//!   2       32000Hz
//!   3       22050Hz
//!   4       24000Hz
//!   5       16000Hz
//!   6       11025Hz
//!   7       12000Hz
//! Bit4:0 specifies sine skip speed S
//! the final sine frequency F = Fs*S/128
//!
//! \return None.
//
//*****************************************************************************
void VS10xxSineTest(unsigned char ucFreq, unsigned long ulTestTime)
{
    //
    // request entering test mode
    //
    VS10xxWriteCmd(SCI_MODE, 0x0820);
    while(VS10xxBusy());
    //
    // send test sequence bytes
    //
    VS10xx_XDCS_CLR;
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x53);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0xef);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x6e);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, ucFreq);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    VS10xx_XDCS_SET;

    xSysCtlDelay(ulTestTime);
    //
    // Exit sine test
    //
    if(ulTestTime!=0)
    {
    	VS10xx_XDCS_CLR;
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x45);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x78);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x69);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x74);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    	xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0x00);
    	VS10xx_XDCS_SET;
    }
    VS10xxDelayus(50000);
}


//FOR WAV HEAD0 :0X7761 HEAD1:0X7665
//FOR MIDI HEAD0 :other info HEAD1:0X4D54
//FOR WMA HEAD0 :data speed HEAD1:0X574D
//FOR MP3 HEAD0 :data speed HEAD1:ID

const unsigned short usMp3BitRateArray[2][16] =
{
    {0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0},
    {0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0}
};
const unsigned short usMp3SampleRateArray[3][4]=
{
    {11025, 11025, 22050, 44100},
    {12000, 12000, 24000, 48000},
    {8000, 8000, 16000, 32000}
};

//*****************************************************************************
//
//! \brief VS10xx get audio information.
//!
//! \param AudioInfo the pointer of AudioFileInfo structure.
//!
//! This function is to get audio information. If the file is WAV and MIDI there is
//! only information about file type. If the file is WMA, the file information
//! contains bit rate of audio stream. Mp3 file has all the defined information
//! of AudioFileInfo.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxGetAudioInfo(AudioFileInfo *AudioInfo)
{
    unsigned short HEAD0;
    unsigned short HEAD1;
    HEAD0 = VS10xxReadReg(SCI_HDAT0);
    HEAD1 = VS10xxReadReg(SCI_HDAT1);
    switch(HEAD1)
    {
        case 0x7665:
            AudioInfo->eFileType = wav;
        case 0X4D54:
            AudioInfo->eFileType = midi;
        case 0X574D:
            {
                AudioInfo->eFileType = wma;
                AudioInfo->usBitRate = HEAD0/8;
             }
        default:
              {
                  if((HEAD1>>5)==2047)
                  {
                      AudioInfo->eFileType = mp3;
                      AudioInfo->ucMp3ID = ( HEAD1 & 0x18 ) >> 3;
                      AudioInfo->ucMp3Layer = 4 - ( (HEAD1&0x06) >> 1 );
                      if(AudioInfo->ucMp3ID == 3)
                      {
                          AudioInfo->usBitRate = usMp3BitRateArray[1][HEAD0>>12];
                      }
                      else
                      {
                          AudioInfo->usBitRate = usMp3BitRateArray[0][HEAD0>>12];
                      }
                      AudioInfo->ucSampleRate =
                          usMp3SampleRateArray[(HEAD0&0x0C00)>>10][AudioInfo->ucMp3ID];
                      AudioInfo->ucOtherInfo = (unsigned char)HEAD0;
                  }
                  else
                  {
                      AudioInfo->eFileType = other;
                  }
              }
      }
}

//*****************************************************************************
//
//! \brief VS10xx reset decode time.
//!
//! \param None.
//!
//! This function is to reset decode time to 0 in SCI_DECODE_TIME register.
//! It's recommended to call this function before start playing a new file.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxResetDecodeTime(void)
{
    VS10xxWriteCmd(SCI_DECODE_TIME, 0x0000);
    VS10xxWriteCmd(SCI_DECODE_TIME, 0x0000);
}

//*****************************************************************************
//
//! \brief VS10xx get decode time.
//!
//! \param None.
//!
//! This function is to get decode time from SCI_DECODE_TIME register.
//!
//! \return None.
//
//*****************************************************************************
unsigned short VS10xxGetDecodeTime(void)
{
    return VS10xxReadReg(SCI_DECODE_TIME);
}

//*****************************************************************************
//
//! \brief VS10xx initialization.
//!
//! \param None.
//!
//! This function is to initialize VS10xx.
//!
//! \return None.
//
//*****************************************************************************
void VS10xxInit(void)
{
    ulSysClk = xSysCtlClockGet();
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_SCK_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_MOSI_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_MISO_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_XCS_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_RST_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_XDCS_PIN));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS10xx_DREQ_PIN));
    xGPIOSPinDirModeSet(VS10xx_XCS_PIN, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(VS10xx_RST_PIN, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(VS10xx_XDCS_PIN, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(VS10xx_DREQ_PIN, xGPIO_DIR_MODE_IN);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeSPI(SPI_CLK, VS10xx_SCK_PIN);
    xSPinTypeSPI(SPI_MOSI, VS10xx_MOSI_PIN);
    xSPinTypeSPI(SPI_MISO, VS10xx_MISO_PIN);

    xSysCtlPeripheralEnable2(VS10xx_SPI_PORT);
    xSPIConfigSet(VS10xx_SPI_PORT, VS10xx_SPI_CLK_SLOW,
    	    xSPI_MOTO_FORMAT_MODE_3 |
            xSPI_MODE_MASTER |
            xSPI_MSB_FIRST |
            xSPI_DATA_WIDTH8);
    xSPISSSet( VS10xx_SPI_PORT, xSPI_SS_SOFTWARE, xSPI_SS0 );

//    SPISSModeConfig(VS10xx_SPI_PORT, SPI_CR1_SSM);
//    SPISSIConfig(VS10xx_SPI_PORT, SPI_CR1_SSI);
    xSPIEnable(VS10xx_SPI_PORT);
    VS10xx_XDCS_SET;
    VS10xx_XCS_SET;
    VS10xx_RST_CLR;
    xSPISingleDataReadWrite( VS10xx_SPI_PORT, 0xFF);
    //
    // Reset VS10xx
    //
    VS10xxDelayus(50000);
    VS10xx_RST_SET;
    VS10xxSoftReset();
    while(VS10xxBusy());
    VS10xxPreConfig();
}






