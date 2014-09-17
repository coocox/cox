/*****************************************************************************
 *      U S B  -  A D C - C O M P O N E N T
 ****************************************************************************/
/**
 * @file	: ADC_CALLBACK.h
 * @brief	: USB Audio Device Class Call Back Definitions
 * @version	: 1.1
 * @date	: 13. Mar. 2011
 * @author	: CooCox
 ****************************************************************************/


#ifndef __ADC_CALLBACK_H__
#define __ADC_CALLBACK_H__

#include "usb_enumerate.h"

/***********************************************************************
 * USB ADC call back function definition
 **********************************************************************/
typedef uint32_t (PFN_AUDIO_INIT_CALLBACK)  (void *dev);
typedef uint32_t (PFN_AUDIO_READ_CALLBACK)  (void *dev, uint8_t *rbuf, uint32_t rlen);
typedef uint32_t (PFN_AUDIO_WRITE_CALLBACK) (void *dev, uint8_t *wbuf, uint32_t wlen);

/**
 * @brief USB ADC Structure
 */
typedef struct
{
	USB_ENU_Dev     usb_enu;
	PFN_AUDIO_INIT_CALLBACK *Audio_Init;
	PFN_AUDIO_READ_CALLBACK *Audio_Read;
	PFN_AUDIO_WRITE_CALLBACK *Audio_write;
	PFN_AUDIO_INIT_CALLBACK *Audio_DeInit;

	void            *Audio_device;

	uint16_t VolCur;     /* Volume Current Value */
	uint16_t VolMin;     /* Volume Minimum Value */
	uint16_t VolMax;     /* Volume Maximum Value */
	uint16_t VolRes;     /* Volume Resolution    */
	uint8_t  Mute;
} USBADC_Dev;


/***********************************************************************
 * extern API of this component
 **********************************************************************/
extern uint32_t Audio_Read  (USBADC_Dev *dev, uint8_t *rbuf, uint32_t *len);
extern uint32_t Audio_Write (USBADC_Dev *dev, uint8_t *wbuf, uint32_t len);
extern void     Audio_Init  (USBADC_Dev *dev);
extern void     Audio_Connect(USBADC_Dev *dev,uint32_t con);
extern uint8_t  Audio_Configurated(USBADC_Dev *dev);
extern void     Audio_Event(USBADC_Dev *dev);

#endif  /* __ADC_CALLBACK_H__ */
