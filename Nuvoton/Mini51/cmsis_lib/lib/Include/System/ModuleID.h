/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright (c) Nuvoton Technology Corp. All rights reserved.                                             */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#ifndef __MODULE_ID_H__
#define __MODULE_ID_H__


typedef enum
{
    /* Module ID valid range: 0 ~ 255 */
    
    /* Driver: Module ID                    Module Name */
    MODULE_ID_DRVPROTECT        = 0,        /* DrvProtect */

    MODULE_ID_DRVADC            = 2,        /* DrvADC  */
    MODULE_ID_DRVAIC            = 4,        /* DrvAIC  */
    MODULE_ID_DRVAPU            = 6,        /* DrvAPU  */
    MODULE_ID_DRVAUDIOADC       = 8,        /* DrvAudioADC */
    MODULE_ID_DRVCACHE          = 10,       /* DrvCache */
    MODULE_ID_DRVCAN            = 11,       /* DrvCAN */
    MODULE_ID_DRVEBI            = 12,       /* DrvEBI */
    MODULE_ID_DRVEDMA           = 13,       /* DrvEDMA */
    MODULE_ID_DRVGDMA           = 14,       /* DrvGDMA */
    MODULE_ID_DRVFSC            = 15,       /* DrvFSC */
    MODULE_ID_DRVGE             = 16,       /* DrvGE  */
    MODULE_ID_DRVFMC            = 17,       /* DrvFMC */
    MODULE_ID_DRVGPIO           = 18,       /* DrvGPIO */
    
    MODULE_ID_DRVGPU            = 20,       /* DrvGPU */
    MODULE_ID_DRVI2C            = 22,       /* DrvI2C (S/W I2C for Non-UL; H/W I2C for UL) */
    MODULE_ID_DRVI2S            = 24,       /* DrvI2S */
    MODULE_ID_DRVI2SM           = 26,       /* DrvI2SM  */
    MODULE_ID_DRVMPU            = 28,       /* DrvMPU */
    MODULE_ID_DRVNAND           = 30,       /* DrvNAND */
    MODULE_ID_DRVNOR            = 32,       /* DrvNOR */
    MODULE_ID_DRVPDMA           = 33,       /* DrvPDMA */
    MODULE_ID_DRVPWM            = 34,       /* DrvPWM */
    MODULE_ID_DRVPS2            = 35,       /* DrvPS2 */
    MODULE_ID_DRVRTC            = 36,       /* DrvRTC */
    MODULE_ID_DRVSDCARD         = 38,       /* DrvSDCard */
    MODULE_ID_DRVSIO            = 39,       /* DrvSerialIO */

    MODULE_ID_DRVSPI            = 40,       /* DrvSPI */
    MODULE_ID_DRVSPIMS          = 41,       /* DrvSPIMS */
    MODULE_ID_DRVSPIFLASH       = 42,       /* DrvSPIFlash */
    MODULE_ID_DRVSPIM           = 43,       /* DrvSPIM */
    MODULE_ID_DRVSYS            = 44,       /* DrvSystem */
    MODULE_ID_DRVSPU            = 45,       /* DrvSPU */
    MODULE_ID_DRVTIMER          = 46,       /* DrvTimer */
    MODULE_ID_DRVUART           = 48,       /* DrvUART */
    MODULE_ID_DRVUSB            = 50,       /* DrvUSB */
    MODULE_ID_DRVUSBH           = 52,       /* DrvUSBH */
    MODULE_ID_DRVVDMA           = 54,       /* DrvVDMA */
    MODULE_ID_DRVVIDEOIN        = 56,       /* DrvVideoIn */
    MODULE_ID_DRVVPOST          = 58,       /* DrvVPOST */

    MODULE_ID_DRVVRAM           = 60,       /* DrvVRAM  */
    MODULE_ID_DRVW55U02         = 62,       /* DrvW55U02 */
    MODULE_ID_DRVI2CH           = 64,       /* DrvI2CH (H/W I2C for Non-UL) */
    MODULE_ID_DRVWDT            = 66,       /* DrvWDT  */
    MODULE_ID_DRVJPEG           = 68,       /* DrvJPEG */
    
    MODULE_ID_DRVZEROG          = 70,       /* DrvZeroG  */
    MODULE_ID_DRVSI2C           = 71,       /* DrvSI2C (S/W I2C for Non-UL) */

    /* Audio: Module ID                     Module Name */
    MODULE_ID_AEC               = 81,       /* AEC  */
    MODULE_ID_BEATDET           = 82,       /* BeatDetection */
    MODULE_ID_SNDEFF            = 83,       /* SoundEffect  */
    MODULE_ID_AUDIOSYN          = 84,       /* AudioSynthesizer */
    MODULE_ID_G726ADPCM         = 85,       /* G726ADPCM  */
    MODULE_ID_IMAADPCM          = 86,       /* IMAAdpcmCodec */
    MODULE_ID_MP3DEC            = 88,       /* MP3Decoder */
    MODULE_ID_PITCHCHANGE       = 90,       /* PitchChanger */
    MODULE_ID_WAVFILEUTIL       = 92,       /* WavFileUtil */
    MODULE_ID_WMADEC            = 96,       /* WMADecoder  */
    MODULE_ID_WMADECDRM         = 98,       /* WMADecoderWithDrm */
    MODULE_ID_AUDIOCTRL         = 100,      /* AudioCtrl */
    MODULE_ID_EQ                = 106,      /* Equalizer */
    MODULE_ID_OGGDEC            = 110,      /* OggDecoder */
    MODULE_ID_MP3ENC            = 112,      /* MP3Encoder */
    MODULE_ID_UADEC             = 114,      /* UltraAudioDec */
    MODULE_ID_ULSPEECHDEC       = 115,      /* UltraLowSpeechDec */
    MODULE_ID_USPEECHDEC        = 116,      /* UltraSpeechDec */
    MODULE_ID_SPEECHRECOG       = 118,      /* SpeechRecog */

    /* File System: Module ID               Module Name */
    MODULE_ID_FS                = 120,      /* FileSystem */
    
    /* Flash Lite: Module ID                Module Name */
    MODULE_ID_FL                = 128,      /* FlashLite */
    
    /* Communication: Module ID             Module Name */
    MODULE_ID_KEYPAD            = 130,      /* Keypad  */
    MODULE_ID_LWIP              = 132,      /* LwIP   */
    MODULE_ID_WLANMGR           = 134,      /* WLanMgr  */
    MODULE_ID_HTTPD             = 136,      /* HTTPD   */
    MODULE_ID_VIRTUALCOM        = 139,      /* VirtualCOM */

    /* Graphics: Module ID                  Module Name */
    MODULE_ID_GFXRESLDR         = 140,      /* GraphicsResLoader */
    MODULE_ID_GFXLIB            = 141,      /* GraphicsLib */
    MODULE_ID_IMGPROC           = 142,      /* ImageProcess */
    MODULE_ID_JPEG              = 144,      /* JPEGCodec */
    MODULE_ID_PNGDEC            = 146,      /* PNGCodec */
    MODULE_ID_BARCODE2D         = 148,      /* BarCode2D */  
    MODULE_ID_PTNRECOG          = 150,      /* PtnRecog */
    MODULE_ID_MOTIONDET         = 152,      /* MotionDection */
    
    /* Storage: Module ID                   Module Name */
    MODULE_ID_STORIF            = 160,      /* StorageInterface */
    MODULE_ID_SDCARD            = 161,      /* SDCard */
    MODULE_ID_SYSNAND           = 162,      /* SysNand */
    MODULE_ID_SPIFLASH          = 163,      /* SPIFlash */
    MODULE_ID_WTRIF             = 164,      /* WriterInterface */
    MODULE_ID_NORFLASH          = 165,      /* NORFlash */
    MODULE_ID_SYSNANDLITE       = 166,      /* SysNandLite */
    
    /* System: Module ID                    Module Name */
    MODULE_ID_INTMGR            = 180,      /* InterruptManager */
    MODULE_ID_BLKLDR            = 181,      /* BlockLoader */
    MODULE_ID_MEMMGR            = 182,      /* MemoryManager */
    MODULE_ID_EVTMGR            = 183,      /* EventManager */
    MODULE_ID_PROF              = 184,      /* Profiling  */
    MODULE_ID_PROGLDR           = 186,      /* ProgramLoader */
    MODULE_ID_SYSINFRA          = 188,      /* SysInfra */
    MODULE_ID_TIMERCTRL         = 190,      /* TimerCtrl */
    MODULE_ID_TIMEUTIL          = 192,      /* TimeUtil */
    MODULE_ID_CONPROGLDR        = 194,      /* ConsoleProgramLoader */
    
    /* USB: Module ID                       Module Name */
    MODULE_ID_USBCOREH          = 78,       /* USBCoreH */
    MODULE_ID_HID               = 220,      /* HID */
    MODULE_ID_MASSSTOR          = 222,      /* MassStor */
    MODULE_ID_MASSSTORHID       = 224,      /* MassStorHID */
    MODULE_ID_MASSSTORLITE      = 226,      /* MassStorLite */
    MODULE_ID_MTP               = 230,      /* MTP */
    MODULE_ID_USBINFRA          = 232,      /* USBInfra */
    MODULE_ID_UAC               = 234,      /* UAC */
    MODULE_ID_UAVC              = 236,      /* UAVC */
    MODULE_ID_UVC               = 238,      /* UVC */
    MODULE_ID_MASSSTORH         = 252,      /* MassStorH */
    MODULE_ID_HIDH              = 254,      /* HIDH */

    /* Security: Module ID                  Module Name */
    MODULE_ID_MSDRMPD           = 228,      /* MsDrmPd */
    
    /* Video: Module ID                     Module Name */
    MODULE_ID_AVICODEC          = 240,      /* AVICodec  */
    MODULE_ID_MJPEG             = 242,      /* MJpegCodec  */
    MODULE_ID_WIVICORE          = 244,      /* WiViCore */
    MODULE_ID_WIVI              = 246,      /* WiViDec */   
    MODULE_ID_AVCTRL            = 248,      /* AVControl */
    MODULE_ID_AVIUTIL           = 250,      /* AVIUtility */
    
    /* Wireless Toy                         Module Name */
    MODULE_ID_WTCHAN            = 168,      /* WTChannel */
    MODULE_ID_WTCMDSERV         = 170,      /* WTCMDService */
    MODULE_ID_WTDISPLAY         = 172,      /* WTDisplay */
    MODULE_ID_WTMEDIA           = 174,      /* WTMedia */
    MODULE_ID_WTSYS             = 176,      /* WTSystem  */
    MODULE_ID_WTTRANS           = 178,      /* WTTransport */
    
    // Module ID valid range: 0 ~ 255   
} E_SYSINFRA_MODULE_ID;


#endif /* __MODULE_ID_H__ */
