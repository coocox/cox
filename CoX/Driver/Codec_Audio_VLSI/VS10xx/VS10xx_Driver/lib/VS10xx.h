//*****************************************************************************
//
//! \file VS10xx.h
//! \brief header file of  driver for VS10xx
//!        Configure this file to apply this driver to your application
//! \version V1.0.0
//! \date 1/23/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX All rights reserved.
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

#ifndef __VS10XX_H__
#define __VS10XX_H__
//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup CODECs
//! @{
//! \addtogroup Audio_Decoder
//! @{
//! \addtogroup VS10xx
//! @{
//! \addtogroup VS10xx_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup VS10xx_User_Config
//! VS10xx Interface Configure
//! @{
//
//*****************************************************************************

#define SPI_CLK                 SPI2CLK(APP)
#define SPI_MOSI                SPI2MOSI(APP)
#define SPI_MISO                SPI2MISO(FIN)
#define VS10xx_SPI_PORT         xSPI2_BASE
#define VS10xx_SCK_PIN          PB13
#define VS10xx_MOSI_PIN         PB15
#define VS10xx_MISO_PIN         PB14

//
//! Command CS
//
#define VS10xx_XCS_PIN          PC10
//
//! Hardware reset pin
//
#define VS10xx_RST_PIN          PD9
//
//! Data CS
//
#define VS10xx_XDCS_PIN         PC11
//
//! Data request output
//
#define VS10xx_DREQ_PIN         PC3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup VS10xx_SPI_Clock_Rate_Define
//! @{
//
//*****************************************************************************
#define VS10xx_XTAL                    12288000

#define VS10xx_SPI_CLK_FAST            4500000
#define VS10xx_SPI_CLK_MEDIUM          2250000
#define VS10xx_SPI_CLK_SLOW            1125000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Audio_File_Information
//! @{
//
//*****************************************************************************
typedef enum
{
        wav,
        wma,
        midi,
        mp3,
        other
}tFileType;

typedef struct
{
    tFileType eFileType;
    unsigned short usBitRate;
    unsigned char ucMp3ID;
    unsigned char ucMp3Layer;
    unsigned short ucSampleRate;
    unsigned char ucOtherInfo;
}AudioFileInfo;
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup VS10xx_Driver_API
//! Exported VS10xx Driver APIs
//! @{
//
//*****************************************************************************
extern unsigned short VS10xxReadReg(unsigned char ucAddr);
extern void VS10xxWriteCmd(unsigned char ucAddr, unsigned short usValue);
extern void VS10xxWriteData(unsigned char *pucBuffer);
extern void VS10xxInit(void);
extern void VS10xxHardReset(void);
extern void VS10xxSoftReset(void);
extern void VS10xxSineTest(unsigned char ucFreq, unsigned long ulTestTime);
extern unsigned short VS10xxGetDecodeTime(void);
extern void VS10xxResetDecodeTime(void);
extern void VS10xxGetAudioInfo(AudioFileInfo *AudioInfo);
extern void VS10xxSetBalance(short sVolBalance);
extern void VS10xxSetVolume(unsigned char ucVol);
extern void VS10xxSetVolume2(unsigned short usVol);
extern unsigned short VS10xxGetVolume( void );
extern void VS10xxBassTrebleEnhance(short sTrebleAmplitude, unsigned short usTrebleLimit,
                             unsigned short usBassAmplitude, unsigned short usBassLimit);
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif



